#pragma once

#include "EZ_Mutex.h"
#include "EZ_Event.h"
#include "EZ_WaitTimer.h"

//  ==========================================================================
//  Fix Memory Leaks when you using C/C++ Runtime library in thread
//  ==========================================================================
#define _USING_BEGIN_THREAD_	1

#if defined ( _USING_BEGIN_THREAD_ )

#include <Process.h>

typedef unsigned int ( __stdcall * PSTARTADDRESS )( void * );

typedef PSTARTADDRESS LPEZTHREADFUNCTION;
typedef unsigned int  EZTHREADRETURN;

#else

typedef LPTHREAD_START_ROUTINE LPEZTHREADFUNCTION;
typedef unsigned long          EZTHREADRETURN;

#endif

//  ==========================================================================
//  Defined
//  ==========================================================================
#define UI_DEFAULT_THREAD_COM_FLAG		( COINIT_APARTMENTTHREADED | COINIT_SPEED_OVER_MEMORY )

#if _MSC_VER > 1300
#define OTHER_DEFAULT_THREAD_COM_FLAG	COINIT_MULTITHREADED
#else
#define OTHER_DEFAULT_THREAD_COM_FLAG	COINIT_APARTMENTTHREADED
#endif

//  ==========================================================================
//  ==========================================================================
//  ===========================  ¥Î³~¡GMultiThread  ==========================
//  ==========================================================================
//  ==========================================================================
class EZ_Thread
{
public:
	enum 
	{ 
		TIMER_BASE_MILLISEC  = 10000,
		TIMER_BASE_MICROSEC  = 10,
		DEFAULT_EVENT_COUNT  = 5,
		DEFAULT_STACK_KBYTES = 512,
		MIN_STACK_KBYTES     = 256,
	};

public:
	BOOL           m_bInto;			//  Into Thread
	BOOL           m_bResetWT;		//  Reset Wait Timer ?
	BOOL           m_bResetEvent;	//  Reset Event ?

	INT            m_iEventCnt;		//  Event Count
	UINT           m_iComFlag;		//  Flag
	UINT           m_iStackKBytes;	//  Thread Stack K-Bytes ( Default 1 MB )

	EZTHREADRETURN m_iThreadID;		//  Thread-ID
	ULONG          m_lReserve;		//  Reserve

	LONGLONG       m_llWaitTimer;	//  Wait Timer
	LARGE_INTEGER  m_liSysTime;		//  

	HANDLE         m_hWait;			//  Wait Handle
	HANDLE*        m_hEvent;		//  Event Handle
	HANDLE         m_hExit;			//  Exit Handle
	HANDLE         m_hThread;		//  Thread Handle
	LPEZMUTEX      m_pMutex;		//  Mutex Handle

public:
	EZ_Thread( LPCTSTR lpMutexName = NULL, C_BOOL bResetWaitTimer = FALSE, C_BOOL bResetEvent = TRUE, C_UINT uiComFlag = OTHER_DEFAULT_THREAD_COM_FLAG );
	virtual ~EZ_Thread();

	virtual void Initial_Thread( LPEZTHREADFUNCTION lpFunction, LPVOID lpUserData, C_INT iEventCnt, C_BOOL bAllocWaitEvent );
	virtual void Release_Thread();

	virtual void Set_Exit_Event( INT iWaittingQuitMSec /* 0 is No, 1 is INFINITE, > 1 is MSec */, C_BOOL bReleaseThread );

	virtual void Start_MilliSec_Wait_Timer1( LPCINT      lpMilliSec );
	virtual void Start_MilliSec_Wait_Timer2( LPCLONGLONG lpMilliSec );

	virtual void Start_MicroSec_Wait_Timer( LPCLONGLONG lpMicroSec );
	
	virtual EZTHREADRETURN Thread_Process();
	virtual EZTHREADRETURN Thread_Process( C_INT iIndex );
	virtual void           GetStackSize( LPCTSTR lpKeyName, C_UINT uiStackKBytes = EZ_Thread::DEFAULT_STACK_KBYTES );

protected:
	virtual void CloseEvent();

	//  ==========================================================================
	//  Easy Function
	//  ==========================================================================
public:
	virtual void Thread_Function() 
	{
		;
	}

	virtual void Thread_Function( C_INT iIndex ) 
	{
		;
	}

	virtual void SetEvents()
	{
		for ( INT i = 0; i < this->m_iEventCnt; i++ )
			this->SetEvent( i );
	}

	virtual void ResetEvents()
	{
		for ( INT i = 0; i < this->m_iEventCnt; i++ )
			this->ResetEvent( i );
	}

	virtual void SetStackSize( C_UINT uiStackKBytes = EZ_Thread::DEFAULT_STACK_KBYTES )
	{
		this->m_iStackKBytes = uiStackKBytes;
	}

	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
public:
	//  Initial Thread
	inline void Initial_Thread( LPVOID lpUserData, C_INT iEventCnt = EZ_Thread::DEFAULT_EVENT_COUNT ) 
	{
		::EZOutputDebugString( _T("lpUserData: 0x%x\n"), lpUserData );
		this->Initial_Thread( EZ_Thread::InitialThreadProc, lpUserData, iEventCnt, TRUE ); 
	}

	inline void Initial_Thread( LPEZTHREADFUNCTION lpFunction, LPVOID lpUserData )
	{
		this->Initial_Thread( lpFunction, lpUserData, EZ_Thread::DEFAULT_EVENT_COUNT, TRUE );
	}

	inline void Initial_Thread( LPEZTHREADFUNCTION lpFunction, LPVOID lpUserData, C_INT iEventCnt )
	{
		this->Initial_Thread( lpFunction, lpUserData, iEventCnt, TRUE );
	}

	//  Lock, Unlock
	inline BOOL Lock( C_UINT uiTimeout = INFINITE ) const 
	{
		return ( this->m_pMutex ? this->m_pMutex->Lock( uiTimeout ) : FALSE ); 
	}

	inline BOOL Unlock() const
	{
		return ( this->m_pMutex ? this->m_pMutex->Unlock() : FALSE );
	}

	//  Start, Cancel Wait Timer
	inline void Start_MilliSec_Wait_Timer1( C_INT iMilliSec )
	{
		this->Start_MilliSec_Wait_Timer1( ( LPCINT )&iMilliSec );
	}

	inline void Start_MilliSec_Wait_Timer2( C_LONGLONG llMilliSec )
	{
		this->Start_MilliSec_Wait_Timer2( ( LPCLONGLONG )&llMilliSec );
	}

	inline void Start_MicroSec_Wait_Timer( C_LONGLONG llMicroSec )
	{
		this->Start_MicroSec_Wait_Timer( ( LPCLONGLONG )&llMicroSec );
	}

	inline void Cancel_Wait_Timer()
	{
		if ( this->m_hWait ) 
			::CancelWaitableTimer( this->m_hWait );
	}

	//  Set, Reset Event
	inline C_BOOL SetEvent( C_INT iEventID )
	{
		return ( this->m_hEvent ? ::SetEvent( this->m_hEvent[ iEventID ] ) : FALSE );
	}

	inline C_BOOL ResetEvent( C_INT iEventID )
	{
		return ( this->m_hEvent ? ::ResetEvent( this->m_hEvent[ iEventID ] ) : FALSE );
	}

	//  ==========================================================================
	//  Static Function
	//  ==========================================================================
protected:
	static EZTHREADRETURN __stdcall InitialThreadProc( LPVOID lpUserData )
	{
		return ( lpUserData ? ( ( EZ_Thread* )lpUserData )->Thread_Process() : 0 );
	}
};

typedef const EZ_Thread  C_EZTHREAD;
typedef       EZ_Thread* LPEZTHREAD;
typedef const EZ_Thread* LPCEZTHREAD;
