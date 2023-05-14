#pragma once

#include "..\EZ_SystemTime.h"
#include "..\Thread\EZ_Thread.h"
#include "..\EZ_TemplateVectorArray.h"

//  ==========================================================================
//  Keep Live Thread
//  ==========================================================================
class EZ_KeepLiveThread : public EZ_Thread
{
public:
	enum OTHER
	{
		TIMER_UPDATE_KEEPLIVE = 10000,
	};

public:
	BOOL                m_bExit;
	INT                 m_iWaitCmdID;
	INT                 m_iCmdSubID;

protected:
	EZ_SystemTime       m_stKeepLive;
	EZHANDLEVECTORARRAY m_aryWaitObjects;

public:
	EZ_KeepLiveThread() : EZ_Thread(), m_bExit( FALSE ), m_iWaitCmdID( -1 ), m_iCmdSubID( -1 ), m_stKeepLive( TRUE ), m_aryWaitObjects()
	{
		;
	}

	virtual ~EZ_KeepLiveThread()
	{
		this->m_aryWaitObjects.RemoveAll();

		//  this->m_bExit
		//  this->m_iWaitCmdID
		//  this->m_iCmdSubID
		//  this->m_stKeepLive
	}

	virtual void Init( __in LPVOID lpUserData, __in C_BOOL bStartKeepLive, __in C_INT iEventCnt = EZ_Thread::DEFAULT_EVENT_COUNT )
	{
		EZ_Thread::Initial_Thread( lpUserData, iEventCnt );

		this->m_bExit = FALSE;

		if ( ( EZ_Thread::m_iThreadID > 0 ) && bStartKeepLive )
			this->StartKeepLive();
	}

	virtual void Init( __in LPEZTHREADFUNCTION lpFunction, __in LPVOID lpUserData, __in C_INT iEventCnt, __in C_BOOL bStartKeepLive )
	{
		EZ_Thread::Initial_Thread( lpFunction, lpUserData, iEventCnt );

		this->m_bExit = FALSE;

		if ( ( EZ_Thread::m_iThreadID > 0 ) && bStartKeepLive )
			this->StartKeepLive();
	}

	virtual C_BOOL UnInit( __in C_INT iWaittingQuitMSec /* 0 = No, 1 = INFINITE, > 1 = MSec */, __in C_BOOL bReleaseThread )
	{
		{
			this->StopKeepLive();

			this->m_bExit = TRUE;

			if ( EZ_Thread::m_hExit )
				EZ_Thread::Set_Exit_Event( iWaittingQuitMSec, bReleaseThread );
		}

		return TRUE;
	}

	virtual void AddWaitObjects( __in HANDLE hObject, __in C_BOOL bFirst )
	{
		if ( bFirst ) this->m_aryWaitObjects.RemoveAll();

		this->m_aryWaitObjects.Add( hObject );
	}

	virtual void StartWaitObjects( __in UINT iWaitTimer = INFINITE )	//  Update Time Before
	{
		if ( EZ_Thread::Lock() )
		{
			this->m_iWaitCmdID = this->m_iCmdSubID = -1;

			this->UpdateKeepLive();

			EZ_Thread::Unlock();
		}

		this->m_iWaitCmdID = ::WaitForMultipleObjects( this->m_aryWaitObjects.GetSize(), this->m_aryWaitObjects.GetData(), FALSE, iWaitTimer );
	}

	virtual void StartWaitObjectsAf( __in UINT iWaitTimer = INFINITE )	//  Update Time After
	{
		if ( EZ_Thread::Lock() )
		{
			this->m_iWaitCmdID = this->m_iCmdSubID = -1;

			this->ResetKeepLive();

			EZ_Thread::Unlock();
		}

		this->m_iWaitCmdID = ::WaitForMultipleObjects( this->m_aryWaitObjects.GetSize(), this->m_aryWaitObjects.GetData(), FALSE, iWaitTimer );

		this->UpdateKeepLive();
	}

	virtual void StopWaitObjects()
	{
		this->m_iWaitCmdID = this->m_iCmdSubID = -1;

		//this->UpdateKeepLive();
	}

	virtual void StartKeepLive()
	{
		if ( EZ_Thread::Lock() )
		{
			EZ_Thread::Start_MilliSec_Wait_Timer1( EZ_KeepLiveThread::TIMER_UPDATE_KEEPLIVE );

			EZ_Thread::Unlock();
		}
	}

	virtual void StopKeepLive()
	{
		if ( EZ_Thread::Lock() )
		{
			EZ_Thread::Cancel_Wait_Timer();

			EZ_Thread::Unlock();
		}
	}

	virtual void UpdateKeepLive()
	{
		if ( EZ_Thread::Lock() )
		{
			this->m_stKeepLive.Get_Current_Time();

			EZ_Thread::Unlock();
		}
	}

	virtual void ResetKeepLive()
	{
		if ( EZ_Thread::Lock() )
		{
			this->m_stKeepLive.Empty();

			EZ_Thread::Unlock();
		}
	}

	virtual C_INT GetKeepLiveSecs( __in C_EZSYSTEMTIME& stNow, __out INT& iWaitCmdID, __out INT& iCmdSubID )
	{
		//  
		if ( stNow.Is_Empty() )
		{
			iWaitCmdID = iCmdSubID = -1;
			return 0;
		}

		//  
		INT iSeconds = 0;

		if ( EZ_Thread::Lock() )
		{
			iWaitCmdID = this->m_iWaitCmdID;
			iCmdSubID  = this->m_iCmdSubID;

			if ( this->m_stKeepLive.Is_Empty() )
				iSeconds = 0;
			else if ( this->m_stKeepLive < stNow )
				iSeconds = EZ_SystemTime::GetSeconds( this->m_stKeepLive, stNow );

			EZ_Thread::Unlock();
		}

		return iSeconds;
	}

	virtual C_BOOL IsDead( __in C_EZSYSTEMTIME& stNow, __out INT& iWaitCmdID, __out INT& iCmdSubID, __in C_INT iDeadSeconds )
	{
		C_INT iSeconds = this->GetKeepLiveSecs( stNow, iWaitCmdID, iCmdSubID );

		return ( iSeconds >= iDeadSeconds );
	}

	static C_BOOL TerminateMySelf()
	{
		HANDLE hProcess = ::GetCurrentProcess();

		if ( !hProcess )
		{
			::EZOutputDebugString( _T( "\n" ) );
			return FALSE;
		}
		else if ( !::TerminateProcess( hProcess, 999 /* Exit Code */ ) )
		{
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_KeepLiveThread ] TerminateMySelf - TerminateProcess !\n" ) );
			return FALSE;
		}
		else
		{
			;
			return TRUE;
		}
	}
};

typedef const EZ_KeepLiveThread  C_EZKEEPLIVETHREAD;
typedef       EZ_KeepLiveThread* LPEZKEEPLIVETHREAD;
typedef const EZ_KeepLiveThread* LPCEZKEEPLIVETHREAD;
