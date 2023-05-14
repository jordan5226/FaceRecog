#pragma once

//  ==========================================================================
//  Defined
//  ==========================================================================
#include "..\..\EZWndFun.h"
#include "EZ_GetOSVersion.h"

#if defined ( EZ_MY_PROJECT )

#include "..\..\EZDefined.h"

#else

#ifndef C_BOOL
#define C_BOOL const BOOL
#endif

#ifndef C_INT
#define C_INT const INT
#endif

#ifndef C_UINT
#define C_UINT const UINT
#endif

#ifndef SAFE_CLOSE_HANDLE
#define SAFE_CLOSE_HANDLE( p ) { if ( p ) { ::CloseHandle( p ); p = NULL; } }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE( p ) { if ( p ) { delete p; p = NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY( p ) { if ( p ) { delete [] p; p = NULL; } }
#endif

#endif

//  ==========================================================================
//  Global Function
//  ==========================================================================
extern C_BOOL LockMutex( HANDLE hMutex, C_UINT uiTimeout = INFINITE );
extern C_BOOL UnlockMutex( HANDLE hMutex );

extern HANDLE EZ_CreateMutex( LPSECURITY_ATTRIBUTES lpSecAttr, C_BOOL bInitOwner, LPCTSTR  lpMtxName,  BOOL bGlobal = FALSE, UINT* lpLastError = NULL );
extern HANDLE EZ_CreateMutex( LPSECURITY_ATTRIBUTES lpSecAttr, C_BOOL bInitOwner, CString& strMtxName, BOOL bGlobal = FALSE, UINT* lpLastError = NULL );

//  ==========================================================================
//  EZ_Mutex
//  ==========================================================================
class EZ_Mutex
{
public:
	enum DEFAULT_PATH
	{
		DEFAULT_PATH_WORK = 0,
		DEFAULT_PATH_WINDOW,
		DEFAULT_PATH_APPDATA,
	};

protected:
	BOOL                    m_bDumpMsg;			//  
	INT                     m_iLockCount;		//  
	UINT                    m_iLockedThreadID;	//  
	UINT                    m_iLastError;		//  
	HANDLE                  m_hObject;			//  
	CString					m_strName;			//  
	CString                 m_strDumpText;		//  
	CString                 m_strIniFile;		//  

public:
	static C_BOOL           gm_bUnicode;		//  
	static C_TAGWIN32OSTYPE gm_iOSVersion;		//  OS Version
	static CString          gm_strModuleName;	//  Module Name ( exp : "EZ-VMS.exe" )
	static CString          gm_WorkPath;		//  Work Directory ( exp : "C:\EZNVR\" )
	static CString          gm_WindowPath;		//  Windows Directory ( exp : "C:\Windows\" )
	static CString          gm_ComAppPath;		//  Common AppData Directory ( exp : "C:\Documents and Settings\All Users\Application Data\EZvision\" )
	static CString          gm_ComAppExPath;	//  Common AppData App Directory ( exp : "C:\Documents and Settings\All Users\Application Data\EZvision\EZNVR\" )

public:
	EZ_Mutex( C_BOOL bInitOwn = FALSE, LPCTSTR lpMtxName = NULL, LPSECURITY_ATTRIBUTES lpSecAttr = NULL, C_BOOL bGlobal = FALSE );
	virtual ~EZ_Mutex();

	virtual C_BOOL Lock( C_UINT uiTimeout = INFINITE );
	virtual C_BOOL Unlock();

protected:
	virtual void   DumpMessage( DWORD dwThreadID, CString& strMessage );

	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
public:
	inline operator HANDLE () const
	{
		return this->m_hObject;
	}

	inline HANDLE GetSafeHandle() const
	{
		return this->m_hObject;
	}

	inline UINT GetErrorCode() const
	{
		return this->m_iLastError;
	}

	inline LPCTSTR GetName() const
	{
		return this->m_strName;
	}

	inline void DeleteObject()
	{
		SAFE_CLOSE_HANDLE ( this->m_hObject );

		if ( this->m_iLockCount > 0 )
			::EZOutputDebugString( "$$$ [ 235-EZ_Mutex ] DeleteObject - Locked ! ( Name : '%s', Thread : %d, Count : %d )\n", this->m_strName, this->m_iLockedThreadID, this->m_iLockCount );

		this->m_iLockCount      = 0;
		this->m_iLockedThreadID = 0;
		this->m_iLastError      = ERROR_SUCCESS;

		this->m_strName.Empty();
		this->m_strDumpText.Empty();
		this->m_strIniFile.Empty();
	}

	inline void EnableDumpMsg( LPCTSTR lpExtendDisplayText = NULL, LPCTSTR lpIniFile = NULL )
	{
		this->m_bDumpMsg    = TRUE;
		this->m_strDumpText = ( lpExtendDisplayText ? lpExtendDisplayText : _T( "Unknow" ) );
		this->m_strIniFile  = ( lpIniFile           ? lpIniFile           : _T( ""       ) );
	}

	inline void DisableDumpMsg()
	{
		this->m_bDumpMsg = FALSE;
	}

	//  ==========================================================================
	//  Static Function
	//  ==========================================================================
public:
	static void Initial()
	{
		;
	}

	static void UnInitial()
	{
		EZ_Mutex::gm_WindowPath.Empty();
		EZ_Mutex::gm_WindowPath.FreeExtra();

		EZ_Mutex::gm_WorkPath.Empty();
		EZ_Mutex::gm_WorkPath.FreeExtra();

		EZ_Mutex::gm_ComAppPath.Empty();
		EZ_Mutex::gm_ComAppPath.FreeExtra();

		EZ_Mutex::gm_ComAppExPath.Empty();
		EZ_Mutex::gm_ComAppExPath.FreeExtra();
	}

	static EZ_Mutex* Alloc( C_BOOL bInitOwn, LPCTSTR lpName = NULL, LPSECURITY_ATTRIBUTES lpSecAttr = NULL, C_BOOL bGlobal = FALSE );

	static LPSECURITY_ATTRIBUTES AllocSecurityAttribute();
	static void                  FreeSecurityAttribute( LPSECURITY_ATTRIBUTES& lpSecurityAtt );

	static CString GetIniPath( LPCTSTR lpIniFile, EZ_Mutex::DEFAULT_PATH iDefaultPath = EZ_Mutex::DEFAULT_PATH_WINDOW );
};

typedef const EZ_Mutex  C_EZMUTEX;
typedef       EZ_Mutex* LPEZMUTEX;
typedef const EZ_Mutex* LPCEZMUTEX;

//  ==========================================================================
//  EZ_MutexLock
//  ==========================================================================
class EZ_MutexLock
{
protected:
	BOOL      m_bLocked;
	HANDLE    m_hMutex;
	LPEZMUTEX m_pMutex;

public:
	EZ_MutexLock( HANDLE hMutex, DWORD dwTimer = INFINITE ) : m_bLocked( FALSE ), m_hMutex( hMutex ), m_pMutex( NULL )
	{
		if ( this->m_hMutex ) this->m_bLocked = ::LockMutex( this->m_hMutex, dwTimer );
	}

	EZ_MutexLock( LPEZMUTEX lpMutex, DWORD dwTimer = INFINITE ) : m_bLocked( FALSE ), m_hMutex( NULL ), m_pMutex( lpMutex )
	{
		if ( this->m_pMutex ) this->m_bLocked = this->m_pMutex->Lock( dwTimer );
	}

	~EZ_MutexLock()
	{
		if ( this->m_bLocked )
		{
			if ( this->m_pMutex )
			{
				if ( !this->m_pMutex->Unlock() )
					::OutputDebugString( _T( "$$$ [ 235-EZ_MutexLock ] Unlock - Object::Failed !\n" ) );
			}
			else if ( this->m_hMutex )
			{
				if ( !::UnlockMutex( this->m_hMutex ) )
					::OutputDebugString( _T( "$$$ [ 235-EZ_MutexLock ] Unlock - Handle::Failed !\n" ) );
			}
			else
			{
				::OutputDebugString( _T( "$$$ [ 235-EZ_MutexLock ] Unlock - Handle::NULL !\n" ) );
			}

			//this->m_bLocked = FALSE;
		}
	}

	inline const BOOL IsLocked() const
	{
		return this->m_bLocked;
	}
};
