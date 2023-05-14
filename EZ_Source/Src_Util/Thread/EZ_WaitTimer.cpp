#include "StdAfx.h"
#include "EZ_WaitTimer.h"

//  ==========================================================================
//  
//  ==========================================================================
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//  ==========================================================================
//  Create Waitable Timer
//  ==========================================================================
HANDLE EZ_CreateWaitableTimer( LPSECURITY_ATTRIBUTES lpSecAttr, C_BOOL bManualReset, LPCTSTR lpName, C_BOOL bGlobal )
{
	HANDLE hTimer = NULL;

	if ( ( bGlobal == FALSE ) || ( lpName == NULL ) || ( ::_tcslen( lpName ) == 0 ) )
		hTimer = ::CreateWaitableTimer( lpSecAttr, bManualReset, lpName );
	else
	{
		//  Get Timer Name
		CString strName = _T( "" );

		strName.Format( _T( "%s" ), lpName );

		if ( strName.Find( _T( "Global\\" ) ) < 0 )
			strName.Format( _T( "Global\\%s" ), lpName );

		//  Open Timer
		C_UINT uiFlag = ( SYNCHRONIZE | WRITE_OWNER | TIMER_ALL_ACCESS | TIMER_MODIFY_STATE );
		HANDLE hTimer = ::OpenWaitableTimer( uiFlag, FALSE, strName );

		if ( hTimer == NULL )
		{
			//  Alloc Temp Security Attributes
			BOOL bAllocMem = ( lpSecAttr == NULL );

			if ( bAllocMem )
				lpSecAttr = EZ_WaitTimer::AllocSecurityAttribute();

			//  Create Waitable Timer
			hTimer = ( lpSecAttr ? ::CreateWaitableTimer( lpSecAttr, bManualReset, strName ) : NULL );

			//  Free Temp Security Attributes
			if ( bAllocMem )
				EZ_WaitTimer::FreeSecurityAttribute( lpSecAttr );
		}
	}

	return hTimer;
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_WaitTimer::EZ_WaitTimer( LPSECURITY_ATTRIBUTES lpSecAttr, C_BOOL bManualReset, LPCTSTR lpName, C_BOOL bGlobal ) 
            : m_hTimer( ::EZ_CreateWaitableTimer( lpSecAttr, bManualReset, lpName, bGlobal ) ), m_llTimer( 0 ), m_liSysTime()
{
#if 1
	this->m_liSysTime.QuadPart = 0;
#else
	::memset( &this->m_liSysTime, 0, sizeof( LARGE_INTEGER ) );
#endif
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_WaitTimer::~EZ_WaitTimer()
{
	this->Release();

	//  this->m_llTimer
	//  this->m_liSysTime
}

//  ==========================================================================
//  Initial
//  ==========================================================================
void EZ_WaitTimer::Initial( LPSECURITY_ATTRIBUTES lpSecAttr, C_BOOL bManualReset, LPCTSTR lpName, C_BOOL bGlobal )
{
	if ( !this->m_hTimer ) this->m_hTimer = ::EZ_CreateWaitableTimer( lpSecAttr, bManualReset, lpName, bGlobal );
}

//  ==========================================================================
//  Release
//  ==========================================================================
void EZ_WaitTimer::Release()
{
	SAFE_CLOSE_HANDLE ( this->m_hTimer );
}

//  ==========================================================================
//  設定 Wait 時間 ( 毫秒 )
//  ==========================================================================
void EZ_WaitTimer::Start_MilliSec_Wait_Timer1( LPCINT lpMilliSec )
{   
	ASSERT ( this->m_hTimer && lpMilliSec );

	//  Cancel Timer
	::CancelWaitableTimer( this->m_hTimer );

	//  
	this->m_llTimer = ( *lpMilliSec * EZ_WaitTimer::QUAD_PART_BASE );

	//  10 秒 == -100000000
	::memset( &this->m_liSysTime, 0, sizeof( LARGE_INTEGER ) );

	this->m_liSysTime.QuadPart = -this->m_llTimer;

	//  Set Timer
	if ( !::SetWaitableTimer( this->m_hTimer, &this->m_liSysTime, 0, NULL, NULL, FALSE ) )
	{
		TRACE ( "$$$ Set Wait Timer Fail, Timer : %d ( EZ_Thread::Start_Wait_Timer )\n", *lpMilliSec );
	}
}

//  ==========================================================================
//  設定 Wait 時間 ( 毫秒 )
//  ==========================================================================
void EZ_WaitTimer::Start_MilliSec_Wait_Timer2( LPCLONGLONG lpMilliSec )
{
	ASSERT ( this->m_hTimer && lpMilliSec );

	//  Cancel Timer
	::CancelWaitableTimer( this->m_hTimer );

	//  10 秒 == -100000000
	this->m_llTimer = ( *lpMilliSec * EZ_WaitTimer::QUAD_PART_BASE );

	//  10 秒 == -100000000
	::memset( &this->m_liSysTime, 0, sizeof( LARGE_INTEGER ) );

	this->m_liSysTime.QuadPart = -this->m_llTimer;
	
	//  Set Timer
	if ( !::SetWaitableTimer( this->m_hTimer, &this->m_liSysTime, 0, NULL, NULL, FALSE ) )
	{
		TRACE ( "$$$ Set Wait Timer Fail, Timer : %d ( EZ_Thread::Start_Wait_Timer )\n", *lpMilliSec );
	}
}

//  ==========================================================================
//  設定 Wait 時間 ( 微秒 )
//  ==========================================================================
void EZ_WaitTimer::Start_MicroSec_Wait_Timer( LPCLONGLONG lpMicroSec )
{   
	ASSERT ( this->m_hTimer && lpMicroSec );

	//  Cancel Timer
	::CancelWaitableTimer( this->m_hTimer );

	//  Set Timer
	this->m_llTimer = *lpMicroSec;

	//  10 秒 == -100000000
	::memset( &this->m_liSysTime, 0, sizeof( LARGE_INTEGER ) );

	this->m_liSysTime.QuadPart = -this->m_llTimer;

	//  Set Timer
	if ( !::SetWaitableTimer( this->m_hTimer, &this->m_liSysTime, 0, NULL, NULL, FALSE ) )
	{
		TRACE ( "$$$ Set Wait Timer Fail, Timer : %d ( EZ_Thread::Start_Wait_Timer )\n", *lpMicroSec );
	}
}

//  ==========================================================================
//  Alloc Security Attribute
//  ==========================================================================
LPSECURITY_ATTRIBUTES EZ_WaitTimer::AllocSecurityAttribute()
{
	LPSECURITY_ATTRIBUTES lpSecAttr = new SECURITY_ATTRIBUTES;

	if ( lpSecAttr != NULL )
	{ 
		::memset( lpSecAttr, 0, sizeof( SECURITY_ATTRIBUTES ) );

		lpSecAttr->nLength              = sizeof( SECURITY_ATTRIBUTES );
		lpSecAttr->lpSecurityDescriptor = ( LPVOID )( new char [ SECURITY_DESCRIPTOR_MIN_LENGTH ] );

		if ( lpSecAttr->lpSecurityDescriptor == NULL )
			EZ_WaitTimer::FreeSecurityAttribute( lpSecAttr );
		else 
		{
			if ( ::InitializeSecurityDescriptor( lpSecAttr->lpSecurityDescriptor, SECURITY_DESCRIPTOR_REVISION ) == FALSE )
				EZ_WaitTimer::FreeSecurityAttribute( lpSecAttr );
			else
			{
				if ( ::SetSecurityDescriptorDacl( lpSecAttr->lpSecurityDescriptor, TRUE, 0, FALSE ) == FALSE )
					EZ_WaitTimer::FreeSecurityAttribute( lpSecAttr );
			}
		}
	}

	return lpSecAttr;
}

//  ==========================================================================
//  Free Security Attribute
//  ==========================================================================
void EZ_WaitTimer::FreeSecurityAttribute( LPSECURITY_ATTRIBUTES& lpSecurityAtt )
{
	if ( lpSecurityAtt ) { SAFE_DELETE_ARRAY ( lpSecurityAtt->lpSecurityDescriptor ); }

	SAFE_DELETE ( lpSecurityAtt );
}
