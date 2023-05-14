#include "StdAfx.h"
#include "EZ_Mutex.h"
#include "..\..\EZDefined.h"

//  ==========================================================================
//  
//  ==========================================================================
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//  ==========================================================================
//  Lock
//  ==========================================================================
C_BOOL LockMutex( HANDLE hMutex, C_UINT uiTimeout )
{
	//  Error !
	if ( !hMutex )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_Mutex ] LockMutex - NULL !\n" ) );
		return FALSE;
	}

	//  
	DWORD dwResult = ::WaitForSingleObject( hMutex, ( DWORD )uiTimeout );

	switch ( dwResult )
	{
	case WAIT_OBJECT_0:
		;
		return TRUE;

	case WAIT_ABANDONED:
		{   
			//  Abandoned was another AP locked,
			//  Before unlocked, AP already exit or close ( so equal locked ),
			//  call lock again, check it was exist.
			if ( ::WaitForSingleObject( hMutex, ( DWORD )uiTimeout ) == WAIT_OBJECT_0 )
			{   //  For free WAIT_ABANDONED
				::ReleaseMutex( hMutex );

				return TRUE;
			}

			//  Show message let user Reboot windows
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_Mutex ] LockMutex - WAIT_ABANDONED !\n" ) );
		}
		return FALSE;

	case WAIT_TIMEOUT:
		{
			if ( uiTimeout >= 2000 )
				::EZOutputDebugString( _T( "$$$ [ 235-EZ_Mutex ] LockMutex - WAIT_TIMEOUT ! ( Timer : %d )\n" ), uiTimeout );
		}
		return FALSE;

	default:
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_Mutex ] LockMutex - UnKnow ! ( Result : %d )\n" ), dwResult );
		return FALSE;
	}
}

//  ==========================================================================
//  UnLock
//  ==========================================================================
C_BOOL UnlockMutex( HANDLE hMutex )
{
	//  Error !
	if ( !hMutex )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_Mutex ] UnlockMutex - NULL !\n" ) );
		return FALSE;
	}

	//  
	C_BOOL bResult = ::ReleaseMutex( hMutex );

	if ( bResult )
	{
		;
		return TRUE;
	}
	else
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_Mutex ] UnlockMutex - Failed !\n" ) );
		return FALSE;
	}
}

//  ==========================================================================
//  Create Mutex
//  ==========================================================================
HANDLE EZ_CreateMutex( LPSECURITY_ATTRIBUTES lpSecAttr, C_BOOL bInitOwner, LPCTSTR lpMtxName, BOOL bGlobal, UINT* lpLastError )
{
	CString strMtxName = _T( "" );

	strMtxName.Format( _T( "%s" ), lpMtxName );

	return ::EZ_CreateMutex( lpSecAttr, bInitOwner, strMtxName, bGlobal, lpLastError );
}

HANDLE EZ_CreateMutex( LPSECURITY_ATTRIBUTES lpSecAttr, C_BOOL bInitOwner, CString& strMtxName, BOOL bGlobal, UINT* lpLastError )
{
	HANDLE hMutex = NULL;

	{
		//  Open or Create Mutex
		if ( strMtxName.IsEmpty() )
			hMutex = ::CreateMutex( lpSecAttr, bInitOwner, strMtxName );
		else
		{
			//  Set Real Mutex Name
			CString strTmpName = strMtxName;

			strTmpName.MakeLower();

			if ( strTmpName.Find( _T( "global\\" ) ) >= 0 )
				bGlobal = TRUE;
			else if ( bGlobal )
				strMtxName.Insert( 0, _T( "Global\\" ) );

			//  Open Mutex
			hMutex = ::OpenMutex( ( SYNCHRONIZE | WRITE_OWNER | MUTEX_ALL_ACCESS | MUTEX_MODIFY_STATE ), FALSE, strMtxName );

			if ( hMutex == NULL )
			{
				//  Alloc Temp Security Attributes
				BOOL bAllocMem = ( lpSecAttr == NULL );

				if ( bAllocMem )
					lpSecAttr = EZ_Mutex::AllocSecurityAttribute();

				//  Create Mutex
				hMutex = ::CreateMutex( lpSecAttr, bInitOwner, strMtxName );

				//  Free Temp Security Attributes
				if ( bAllocMem )
					EZ_Mutex::FreeSecurityAttribute( lpSecAttr );
			}
		}

		//  Get Last Error
		if ( !hMutex && lpLastError )
			*lpLastError = ::GetLastError();
	}

	return hMutex;
}

//  ==========================================================================
//  
//  ==========================================================================
#if defined ( _UNICODE )
C_BOOL           EZ_Mutex::gm_bUnicode   = TRUE;
C_TAGWIN32OSTYPE EZ_Mutex::gm_iOSVersion = ::IsShellSysType();
#else
C_BOOL           EZ_Mutex::gm_bUnicode   = FALSE;
C_TAGWIN32OSTYPE EZ_Mutex::gm_iOSVersion = ::IsShellSysType();
#endif

#if defined ( EZ_MY_PROJECT )
CString EZ_Mutex::gm_strModuleName = _T( "" );
CString EZ_Mutex::gm_WorkPath      = ::GetWorkPath( NULL, &EZ_Mutex::gm_strModuleName );
CString EZ_Mutex::gm_WindowPath    = ::GetWindowPath();
CString EZ_Mutex::gm_ComAppPath    = ::GetComAppDataPath( NULL, TRUE );
CString EZ_Mutex::gm_ComAppExPath  = ::GetComAppNamePath( EZ_Mutex::gm_ComAppPath, EZ_Mutex::gm_WorkPath );
#else
CString EZ_Mutex::gm_strModuleName = _T( "" );
CString EZ_Mutex::gm_WorkPath      = _T( "" );
CString EZ_Mutex::gm_WindowPath    = _T( "" );
CString EZ_Mutex::gm_ComAppPath    = _T( "" );
CString EZ_Mutex::gm_ComAppExPath  = _T( "" );
#endif

//  ==========================================================================
//  
//  ==========================================================================
EZ_Mutex::EZ_Mutex( C_BOOL bInitOwner, LPCTSTR lpMtxName, LPSECURITY_ATTRIBUTES lpSecAttr, C_BOOL bGlobal ) 
		: m_bDumpMsg( FALSE ), m_iLockCount( 0 ), m_iLockedThreadID( 0 ), m_iLastError( ERROR_SUCCESS ), m_hObject( NULL )
		, m_strName( _T( "" ) ), m_strDumpText( _T( "" ) ), m_strIniFile( _T( "" ) )
{
	if ( lpMtxName ) this->m_strName.Format( _T( "%s" ), lpMtxName );

	this->m_hObject = ::EZ_CreateMutex( lpSecAttr, bInitOwner, this->m_strName, bGlobal, &this->m_iLastError );
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_Mutex::~EZ_Mutex()
{
	this->DeleteObject();

	//  this->m_bDumpMsg
}

//  ==========================================================================
//  Lock
//  ==========================================================================
C_BOOL EZ_Mutex::Lock( C_UINT uiTimeout )
{
	BOOL bLocked = FALSE;

	{
		//  Dump Message
		DWORD   dwThreadID = 0;
		CString strMsg     = _T( "" );

		if ( this->m_bDumpMsg )
		{
			dwThreadID = ::GetCurrentThreadId();

			strMsg.Format( _T( "$$$ [ 235-EZ_Mutex ] Lock - Start ! ( Dump : %s, Thread ID : %d, TickCnt : %d )" ), this->m_strDumpText, dwThreadID, ::GetTickCount() );

			this->DumpMessage( dwThreadID, strMsg );
		}

		//  Lock
		try
		{
			bLocked = ::LockMutex( this->m_hObject, uiTimeout );

			if ( bLocked )
			{
				if ( this->m_iLockCount <= 0 )
					this->m_iLockedThreadID = ( this->m_bDumpMsg ? dwThreadID : ::GetCurrentThreadId() );

				this->m_iLockCount++;
			}
		}
		catch ( ... )
		{
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_Mutex ] Lock - Exception !\n" ) );
		}

		//  Dump Message
		if ( this->m_bDumpMsg )
		{
			strMsg.Format( _T( "$$$ [ 235-EZ_Mutex ] Lock - Stop ! ( Dump : %s, Thread ID : %d, TickCnt : %d, Result : %d, LockCnt : %d )" ), 
				this->m_strDumpText, dwThreadID, ::GetTickCount(), bLocked, this->m_iLockCount );

			this->DumpMessage( dwThreadID, strMsg );
		}
	}

	return bLocked;
}

//  ==========================================================================
//  UnLock
//  ==========================================================================
C_BOOL EZ_Mutex::Unlock()
{
	BOOL bUnLocked = FALSE;

	{
		//  Dump Message
		DWORD   dwThreadID = 0;
		CString strMsg     = _T( "" );

		if ( this->m_bDumpMsg )
		{
			dwThreadID = ::GetCurrentThreadId();

			strMsg.Format( _T( "$$$ [ 235-EZ_Mutex ] Unlock - Start ! ( Dump : %s, Thread ID : %d, TickCnt : %d )" ), this->m_strDumpText, dwThreadID, ::GetTickCount() );

			this->DumpMessage( dwThreadID, strMsg );
		}

		//  Unlock
		try
		{
			if ( this->m_iLockCount <= 0 )
				::EZOutputDebugString( _T( "$$$ [ 235-EZ_Mutex ] Unlock - WTF ! ( LockCnt : %d )\n" ), this->m_iLockCount );
			else
			{
				this->m_iLockCount--;

				if ( this->m_iLockCount == 0 ) this->m_iLockedThreadID = 0;
			}

			bUnLocked = ::UnlockMutex( this->m_hObject );

			if ( !bUnLocked ) ::EZOutputDebugString( _T( "$$$ [ 235-EZ_Mutex ] Unlock - Failed !\n" ) );
		}
		catch ( ... )
		{
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_Mutex ] Unlock - Exception !\n" ) );
		}

		//  Dump Message
		if ( this->m_bDumpMsg )
		{
			strMsg.Format( _T( "$$$ [ 235-EZ_Mutex ] Unlock - Stop ! ( Dump : %s, Thread ID : %d, TickCnt : %d, Result : %d )" ), 
				this->m_strDumpText, dwThreadID, ::GetTickCount(), bUnLocked );

			this->DumpMessage( dwThreadID, strMsg );
		}
	}

	return bUnLocked;
}

//  ==========================================================================
//  DumpMessage
//  ==========================================================================
void EZ_Mutex::DumpMessage( DWORD dwThreadID, CString& strMessage )
{
	if ( this->m_strIniFile.IsEmpty() )
	{
		strMessage.Append( _T( "\n" ) );

		::EZOutputDebugString( strMessage );
	}
	else
	{
		CString strKeyName = _T( "" );

		strKeyName.Format( _T( "Thread-ID ( %d )" ), dwThreadID );

		::WritePrivateProfileString( this->m_strDumpText, strKeyName, strMessage, this->m_strIniFile );
	}
}

//  ==========================================================================
//  Alloc ( Static )
//  ==========================================================================
EZ_Mutex* EZ_Mutex::Alloc( C_BOOL bInitOwn, LPCTSTR lpName, LPSECURITY_ATTRIBUTES lpSecAttr, C_BOOL bGlobal )
{
	EZ_Mutex* lpMutex = NULL;

	{
#if !defined ( _USE_TRY_CATCH_ )
		lpMutex = ( new EZ_Mutex( bInitOwn, lpName, lpSecAttr, bGlobal ) );

		if ( !lpMutex ) ::EZOutputDebugString( _T( "$$$ [ 235-EZ_Mutex ] Alloc - NULL !\n" ) );
#else
		TRY
		{
			lpMutex = new EZ_Mutex( bInitOwn, lpName, lpSecAttr, bGlobal );
		}
		CATCH ( CMemoryException, e )
		{
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_Mutex ] Alloc - Exception !\n" ) );
		}
		END_CATCH;	
#endif
	}

	return lpMutex;
}

//  ==========================================================================
//  AllocSecurityAttribute ( Static )
//  ==========================================================================
LPSECURITY_ATTRIBUTES EZ_Mutex::AllocSecurityAttribute()
{
	//  
	LPSECURITY_ATTRIBUTES lpSecAttr = new SECURITY_ATTRIBUTES;

	if ( lpSecAttr )
		::memset( lpSecAttr, 0, sizeof( SECURITY_ATTRIBUTES ) );
	else
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_Mutex ] AllocSecurityAttribute - AllocAttributes !\n" ) );
		return NULL;
	}

	//  
	lpSecAttr->nLength              = sizeof( SECURITY_ATTRIBUTES );
	lpSecAttr->lpSecurityDescriptor = ( LPVOID )( new char [ SECURITY_DESCRIPTOR_MIN_LENGTH ] );

	if ( lpSecAttr->lpSecurityDescriptor == NULL )
	{
		EZ_Mutex::FreeSecurityAttribute( lpSecAttr );

		::EZOutputDebugString( _T( "$$$ [ 235-EZ_Mutex ] AllocSecurityAttribute - AllocDescriptor !\n" ) );
	}
	else if ( ::InitializeSecurityDescriptor( lpSecAttr->lpSecurityDescriptor, SECURITY_DESCRIPTOR_REVISION ) == FALSE )
	{
		EZ_Mutex::FreeSecurityAttribute( lpSecAttr );

		::EZOutputDebugString( _T( "$$$ [ 235-EZ_Mutex ] AllocSecurityAttribute - InitializeSecurityDescriptor !\n" ) );
	}
	else if ( ::SetSecurityDescriptorDacl( lpSecAttr->lpSecurityDescriptor, TRUE, 0, FALSE ) == FALSE )
	{
		EZ_Mutex::FreeSecurityAttribute( lpSecAttr );

		::EZOutputDebugString( _T( "$$$ [ 235-EZ_Mutex ] AllocSecurityAttribute - SetSecurityDescriptorDacl !\n" ) );
	}

	return lpSecAttr;
}

//  ==========================================================================
//  FreeSecurityAttribute ( Static )
//  ==========================================================================
void EZ_Mutex::FreeSecurityAttribute( LPSECURITY_ATTRIBUTES& lpSecurityAtt )
{
	if ( lpSecurityAtt )
	{
		if ( lpSecurityAtt->lpSecurityDescriptor )
		{
			delete [] lpSecurityAtt->lpSecurityDescriptor;
			lpSecurityAtt->lpSecurityDescriptor = NULL;
		}

		delete lpSecurityAtt;
		lpSecurityAtt = NULL;
	}
}

//  ==========================================================================
//  GetIniPath ( Static )
//  ==========================================================================
CString EZ_Mutex::GetIniPath( LPCTSTR lpFileName, EZ_Mutex::DEFAULT_PATH iDefaultPath )
{
	CString strRetPath = _T( "" );

	{
		//  Get Path
		switch ( iDefaultPath )
		{
		default:
			{
				ASSERT ( 0 );
			}

		case EZ_Mutex::DEFAULT_PATH_WORK:
			strRetPath = EZ_Mutex::gm_WorkPath;
			break;

		case EZ_Mutex::DEFAULT_PATH_WINDOW:
			strRetPath = EZ_Mutex::gm_WindowPath;
			break;

		case EZ_Mutex::DEFAULT_PATH_APPDATA:
			strRetPath = EZ_Mutex::gm_ComAppPath;
			break;
		}

		//  Add FileName
		if ( lpFileName )
		{
#if _MSC_VER > 1400
			strRetPath.Append( lpFileName );
#else
			strRetPath += CString( lpFileName );
#endif
		}
	}

	return strRetPath;
}
