//  ==========================================================================
//  Include File
//  ==========================================================================
#include "StdAfx.h"
#include <Vfw.h>

#include <Winbase.h>
#include <ObjBase.h>
#include "EZ_Thread.h"
#include "..\EZ_Counter.h"

//  ==========================================================================
//  Link Library
//  ==========================================================================
#pragma comment( lib, "Ole32.lib" )
#pragma comment( lib, "Winmm.lib" )
#pragma comment( lib, "Vfw32.lib" )

//  ==========================================================================
//  
//  ==========================================================================
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400 
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef STACK_SIZE_PARAM_IS_A_RESERVATION
#define STACK_SIZE_PARAM_IS_A_RESERVATION 0x00010000
#endif

//  ====================================================================================================
//  ====================================================================================================
//  ===============  EZ_Thread Function Begin  =========================================================
//  ====================================================================================================
//  ====================================================================================================

//  ==========================================================================
//  
//  ==========================================================================
EZ_Thread::EZ_Thread( LPCTSTR lpMutexName, C_BOOL bResetWaitTimer, C_BOOL bResetEvent, C_UINT uiComFlag ) 
		 : m_bInto( FALSE ), m_bResetWT( bResetWaitTimer ), m_bResetEvent( bResetEvent ), m_iEventCnt( 0 ), m_iComFlag( uiComFlag ), m_iStackKBytes( 0 )
		 , m_iThreadID( 0 ), m_lReserve( 0 ), m_llWaitTimer( 0 ), m_hWait( NULL ), m_hEvent( NULL ), m_hExit( NULL ), m_hThread( NULL )
		 , m_pMutex( new EZ_Mutex( FALSE, lpMutexName, NULL, FALSE ) )
{
	this->m_liSysTime.QuadPart = 0;
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_Thread::~EZ_Thread()
{
	this->Release_Thread();

	SAFE_DELETE ( this->m_pMutex );

	//  this->m_bInto
	//  this->m_bResetWT
	//  this->m_bResetEvent

	//  this->m_iComFlag
	//  this->m_iStackKBytes
	//  this->m_lReserve

	//  this->m_llWaitTimer
	//  this->m_liSysTime
}

//  ==========================================================================
//  Initial Thread
//  ==========================================================================
void EZ_Thread::Initial_Thread( LPEZTHREADFUNCTION lpFunction, VOID* lpUserData, C_INT iEventCnt, C_BOOL bAllocWaitEvent )
{
	//  Create Exit Event
	if ( this->m_hExit ) 
		::ResetEvent( this->m_hExit );
	else
	{
		this->m_hExit = ::EZ_CreateEvent( NULL, TRUE, FALSE, NULL, FALSE );

		if ( !this->m_hExit ) ::EZOutputDebugString( _T( "$$$ [ 235-EZ_Thread ] Initial_Thread - EZ_CreateEvent::Exit !\n" ) );
	}

	//  Create Event
	if ( this->m_hEvent && ( iEventCnt > this->m_iEventCnt ) )
		this->CloseEvent();

	if ( this->m_hEvent )
	{
		for ( INT i = 0; i < this->m_iEventCnt; i++ )
		{
			if ( this->m_hEvent[ i ] )
				::ResetEvent( this->m_hEvent[ i ] );
		}
	}
	else if ( iEventCnt > 0 )
	{
		this->m_iEventCnt = 0;
		this->m_hEvent    = new HANDLE [ iEventCnt ];

		if ( this->m_hEvent )
		{
			this->m_iEventCnt = iEventCnt;

			for ( INT i = 0; i < this->m_iEventCnt; i++ )
			{
				this->m_hEvent[ i ] = ::EZ_CreateEvent( NULL, this->m_bResetEvent, FALSE, NULL, FALSE );

				if ( !this->m_hEvent[ i ] ) ::EZOutputDebugString( _T( "$$$ [ 235-EZ_Thread ] Initial_Thread - EZ_CreateEvent::Event !\n" ) );
			}
		}
	}
	else
	{
		this->m_iEventCnt = 0;
		this->m_hEvent    = NULL;
	}

	//  Create Wait-Timer-Thread
	if ( this->m_hWait ) 
		::CancelWaitableTimer( this->m_hWait );
	else if ( bAllocWaitEvent )
	{
		this->m_hWait = ::EZ_CreateWaitableTimer( NULL, this->m_bResetWT, NULL, FALSE );

		if ( !this->m_hWait ) ::EZOutputDebugString( _T( "$$$ [ 235-EZ_Thread ] Initial_Thread - EZ_CreateWaitableTimer !\n" ) );
	}

	//  Release Old Thread
	if ( this->m_hThread )
	{
		if ( this->m_iThreadID != 0 )
		{
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_Thread ] Initial_Thread - Exit !\n" ) );
			return;
		}

		SAFE_CLOSE_HANDLE ( this->m_hThread );
	}

	//  Create New Thread
	this->m_bInto = FALSE;

	{
		INT iStackSize = 0;
		INT iFlags     = 0;

		if ( ( this->m_iStackKBytes > 0 ) && ( EZ_Mutex::gm_iOSVersion >= osWindowsXP ) )
		{
			iStackSize = ( this->m_iStackKBytes * 1024 );
			iFlags     = STACK_SIZE_PARAM_IS_A_RESERVATION;
		}

#if defined ( _USING_BEGIN_THREAD_ )
		uintptr_t iValue = ::_beginthreadex( NULL, iStackSize, lpFunction, lpUserData, iFlags, &this->m_iThreadID );

		if ( iValue == -1 )				//太多執行緒
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_Thread ] Initial_Thread - _beginthreadex ! ( -1 )\n" ) );
		else if ( iValue == EINVAL )	//引數無效或堆疊大小不正確
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_Thread ] Initial_Thread - _beginthreadex ! ( EINVAL )\n" ) );
		else if ( iValue == 0 )			//沒有足夠的資源 (例如記憶體) 
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_Thread ] Initial_Thread - _beginthreadex ! ( NULL )\n" ) );
		else
		{
			if ( this->m_iThreadID == 0 )
				::EZOutputDebugString( _T( "$$$ [ 235-EZ_Thread ] Initial_Thread - _beginthreadex ! ( ThreadID : 0 )\n" ) );

			this->m_hThread = ( HANDLE )iValue;
		}
#else
		this->m_hThread = ::CreateThread( NULL, iStackSize, lpFunction, lpUserData, iFlags, &this->m_iThreadID );

		if ( !this->m_hThread )
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_Thread ] Initial_Thread - CreateThread ! ( NULL )\n" ) );
		else if ( this->m_iThreadID == 0 )
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_Thread ] Initial_Thread - CreateThread ! ( ThreadID : 0 )\n" ) );
#endif
	}
}

//  ==========================================================================
//  Release Thread
//  ==========================================================================
void EZ_Thread::Release_Thread()
{	
	C_BOOL bLocked = this->Lock();

	{
		//  Release Thread
		this->m_iThreadID = 0;

		SAFE_CLOSE_HANDLE ( this->m_hThread );

		//  Release Event
		this->CloseEvent();

		//  Release Wait-Event
		SAFE_CLOSE_HANDLE ( this->m_hWait );

		//  Release Exit-Event
		SAFE_CLOSE_HANDLE ( this->m_hExit );
	}

	if ( bLocked ) this->Unlock();
}

//  ==========================================================================
//  設定觸發離開事件
//  ==========================================================================
void EZ_Thread::Set_Exit_Event( INT iWaittingQuitMSec, C_BOOL bReleaseThread )
{
	//  Sent Exit Event
	if ( this->m_hExit )
		::SetEvent( this->m_hExit );

	//  Wait Thread Quit ?
	if ( iWaittingQuitMSec >= 1 )
	{
		EZ_PerformanceCounterV2 pmCounterV2( TRUE );

		for ( BOOL bExit = FALSE, bLocked; ; ::Sleep( 100 ) )
		{
			//  Thread has Exit ?
			if ( !this->m_hThread )
			{
				;
				break;
			}
			else if ( WAIT_OBJECT_0 == ::WaitForSingleObject( this->m_hThread, 15 ) )
			{
				;
				break;
			}

			//  Check Thread Status
			bLocked = this->Lock( 1 );

			if ( this->m_iThreadID == 0 )
				bExit = TRUE;
			else if ( !this->m_bInto )
			{
#if 0
				bExit = TRUE;

				::TerminateThread( this->m_hThread, 0 );
#endif
			}

			if ( bLocked ) this->Unlock();

			//  Exit ?
			if ( bExit )
			{
				iWaittingQuitMSec = 0;
				break;
			}

			//  Timeout ?
			if ( iWaittingQuitMSec > 1 )
			{
				if ( pmCounterV2.Stop() >= iWaittingQuitMSec )
				{
					;
					break;
				}
			}
		}
	}

	//  Release Thread ?
	if ( bReleaseThread )
	{
		if ( iWaittingQuitMSec <= 0 )
			::Sleep( 250 );

		this->Release_Thread();
	}
}

//  ==========================================================================
//  設定 Wait 時間 ( 毫秒 )
//  ==========================================================================
void EZ_Thread::Start_MilliSec_Wait_Timer1( LPCINT lpMilliSec )
{
	//  Error !
	if ( !lpMilliSec )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_Thread ] Start_MilliSec_Wait_Timer1 - Error !\n" ) );
		return;
	}

	//  
	if ( !this->m_hWait )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_Thread ] Start_MilliSec_Wait_Timer1 - NoHandle !\n" ) );
		return;
	}

	//  10 秒 == -100000000
	this->m_llWaitTimer = ( *lpMilliSec * EZ_Thread::TIMER_BASE_MILLISEC );

	::memset( &this->m_liSysTime, 0, sizeof( LARGE_INTEGER ) );

	this->m_liSysTime.QuadPart = -this->m_llWaitTimer;

	//  Set Timer
	::CancelWaitableTimer( this->m_hWait );

	if ( !::SetWaitableTimer( this->m_hWait, &this->m_liSysTime, 0, NULL, NULL, FALSE ) )
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_Thread ] Start_MilliSec_Wait_Timer1 - Fail ! ( Timer : %d )\n" ), *lpMilliSec );
}

//  ==========================================================================
//  設定 Wait 時間 ( 毫秒 )
//  ==========================================================================
void EZ_Thread::Start_MilliSec_Wait_Timer2( LPCLONGLONG lpMilliSec )
{
	//  Error !
	if ( !lpMilliSec )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_Thread ] Start_MilliSec_Wait_Timer2 - Error !\n" ) );
		return;
	}

	//  10 秒 == -100000000
	this->m_llWaitTimer = ( *lpMilliSec * EZ_Thread::TIMER_BASE_MILLISEC );

	::memset( &this->m_liSysTime, 0, sizeof( LARGE_INTEGER ) );

	this->m_liSysTime.QuadPart = -this->m_llWaitTimer;
	
	//  Set Timer
	if ( this->m_hWait )
	{
		::CancelWaitableTimer( this->m_hWait );

		if ( !::SetWaitableTimer( this->m_hWait, &this->m_liSysTime, 0, NULL, NULL, FALSE ) )
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_Thread ] Start_MilliSec_Wait_Timer1 - Fail ! ( Timer : %llu )\n" ), *lpMilliSec );
	}
}

//  ==========================================================================
//  設定 Wait 時間 ( 微秒 )
//  ==========================================================================
void EZ_Thread::Start_MicroSec_Wait_Timer( LPCLONGLONG lpMicroSec )
{   
	//  Error !
	if ( !lpMicroSec )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_Thread ] Start_MicroSec_Wait_Timer - Error !\n" ) );
		return;
	}

	//  10 秒 == -100000000
	this->m_llWaitTimer = ( *lpMicroSec * EZ_Thread::TIMER_BASE_MICROSEC );

	::memset( &this->m_liSysTime, 0, sizeof( LARGE_INTEGER ) );

	this->m_liSysTime.QuadPart = -this->m_llWaitTimer;

	//  Set Timer
	if ( this->m_hWait )
	{
		::CancelWaitableTimer( this->m_hWait );

		if ( !::SetWaitableTimer( this->m_hWait, &this->m_liSysTime, 0, NULL, NULL, FALSE ) )
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_Thread ] Start_MicroSec_Wait_Timer - Fail ! ( Timer : %llu )\n" ), *lpMicroSec );
	}
}

//  ==========================================================================
//  Close Event
//  ==========================================================================
void EZ_Thread::CloseEvent()
{
	if ( this->m_hEvent )
	{
		for ( INT i = 0; i < this->m_iEventCnt; i++ )
		{
			if ( this->m_hEvent[ i ] )
			{
				::ResetEvent( this->m_hEvent[ i ] );

				::CloseHandle( this->m_hEvent[ i ] );

				this->m_hEvent[ i ] = NULL;
			}
		}

		delete [] this->m_hEvent;
		this->m_hEvent = NULL;
	}

	this->m_iEventCnt = 0;
}

//  ==========================================================================
//  Get Stack Size
//  ==========================================================================
void EZ_Thread::GetStackSize( LPCTSTR lpKeyName, C_UINT uiStackKBytes )
{
	CString strIniFile = ( EZ_Mutex::gm_WindowPath + _T( "EZDebug61.ini" ) );
	C_INT   uiEnable   = ( C_INT )::GetPrivateProfileInt( _T( "Stack" ), lpKeyName, -1, strIniFile );

	if ( uiEnable < 0 )
		::WritePrivateProfileString( _T( "Stack" ), lpKeyName, _T( "1" ), strIniFile );

	this->m_iStackKBytes = ( ( uiEnable == 0 ) ? 0 : uiStackKBytes );
}

//  ==========================================================================
//  Thread Process
//  ==========================================================================
EZTHREADRETURN EZ_Thread::Thread_Process()
{
	BOOL bExit = FALSE;

	{
		//  偵測是否上層在執行緒尚未進入時～便決定離開了!
		if ( this->Lock() )
		{
			if ( this->m_iThreadID == 0 )
				bExit = TRUE;
			else
				this->m_bInto = TRUE;

			this->Unlock();
		}

		//  
		if ( !bExit )
		{
			//  COM Init
#if _MSC_VER > 1300
			const HRESULT hr = ::CoInitializeEx( NULL, this->m_iComFlag );
#else
			const HRESULT hr = ::CoInitialize( NULL );
#endif

			::AVIFileInit();

			//  Do Something
			this->Thread_Function();

			//  COM Uninit
			::AVIFileExit();

			if ( hr == S_OK ) 
				::CoUninitialize();
		}

		//  
#if 0
		if ( this->Lock() )
		{
			this->m_bInto = FALSE;

			this->Unlock();
		}
#endif
	}

	return 0;
}

EZTHREADRETURN EZ_Thread::Thread_Process( C_INT iIndex )
{
	BOOL bExit = FALSE;

	{
		//  偵測是否上層在執行緒尚未進入時～便決定離開了!
		if ( this->Lock() )
		{
			if ( this->m_iThreadID == 0 )
				bExit = TRUE;
			else
				this->m_bInto = TRUE;

			this->Unlock();
		}

		//  進入工作函式
		if ( !bExit )
		{
			//  COM Init
#if _MSC_VER > 1300
			const HRESULT hr = ::CoInitializeEx( NULL, this->m_iComFlag );
#else
			const HRESULT hr = ::CoInitialize( NULL );
#endif

			::AVIFileInit();

			//  Do Something
			this->Thread_Function( iIndex );

			//  COM Uninit
			::AVIFileExit();

			if ( hr == S_OK ) 
				::CoUninitialize();
		}

		//  
#if 0
		if ( this->Lock() )
		{
			this->m_bInto = FALSE;

			this->Unlock();
		}
#endif
	}

	return 0;
}
