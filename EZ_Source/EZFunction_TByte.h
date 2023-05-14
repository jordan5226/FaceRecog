#pragma once

#include <Icm.h>		//  Get struct RGBCOLOR
#include <MMSystem.h>	//  Get struct Waveformat ( MmReg.h is on top. VC60 Complier will error )
#include <MmReg.h>		//  Get wave flag
#include <ShlObj.h>		//  Use Function SHGetSpecialFolderPath()
#include <ShlwApi.h>	//  Use Function PathRemoveFileSpec()
#include <Assert.h>		//  Use Function assert()

#pragma comment( lib, "ShlwApi.lib" )

//  ==========================================================================
//  EZSleep
//  ==========================================================================
inline void EZSleep( const UINT uiSleepMS )
{
	if ( uiSleepMS >= 15 )
		::Sleep( uiSleepMS );
	else
	{
		MMRESULT hResult = ::timeBeginPeriod( 1 );

		::Sleep( uiSleepMS );

		if ( TIMERR_NOERROR == hResult )
			::timeEndPeriod( 1 );
	}
}

//  ==========================================================================
//  EZStrcpy
//  ==========================================================================
inline BOOL EZStrcpy( LPTSTR lpDstBuf, const UINT iDstBufSize, LPCTSTR lpSrcBuf )
{
	BOOL bResult = TRUE;

	try 
	{
#if _MSC_VER > 1400
		bResult = ( ::_tcscpy_s( lpDstBuf, iDstBufSize, lpSrcBuf ) == 0 );
#else
		::_tcscpy( lpDstBuf, lpSrcBuf );
#endif
	}
	catch ( ... )
	{
		bResult = FALSE;
	}

	return bResult;
}

//  ==========================================================================
//  EZStrcat
//  ==========================================================================
inline void EZStrcat( LPTSTR lpDstBuf, const UINT iDstBufSize, LPCTSTR lpSrcBuf )
{
	try 
	{
#if _MSC_VER > 1400
		::_tcscat_s( lpDstBuf, iDstBufSize, lpSrcBuf );
#else
		::_tcscat(   lpDstBuf,              lpSrcBuf );
#endif
	}
	catch ( ... )
	{
		;
	}
}

//  ==========================================================================
//  EZStrcmpi
//  ==========================================================================
inline const INT EZStrcmpi( LPCTSTR lpDstBuf, LPCTSTR lpSrcBuf )
{
	INT iResult = -1;

	try 
	{
		iResult = ::_tcsicmp( lpDstBuf, lpSrcBuf );
	}
	catch ( ... )
	{
		;
	}

	return iResult;
}

//  ==========================================================================
//  EZMemcpy
//  ==========================================================================
inline void EZMemcpy( LPVOID lpDstBuf, const UINT iDstBufSize, LPCVOID lpSrcBuf, const UINT iSrcBufSize )
{
	try 
	{
#if _MSC_VER > 1400
		::memcpy_s( lpDstBuf, iDstBufSize, lpSrcBuf, iSrcBufSize );
#else
		::memcpy(   lpDstBuf,              lpSrcBuf, iSrcBufSize );
#endif
	}
	catch ( ... )
	{
		;
	}
}

//  ==========================================================================
//  GetWorkPath
//  ==========================================================================
inline void GetWorkPath( HINSTANCE hInstance, LPTSTR lpPathBuf, const UINT iPathBufSize, LPTSTR lpFileBuf, const UINT iFileBufSize )
{
	//  Get Module Name
	CString strModule = _T( "" );

	{
		LPTSTR lpModule = strModule.GetBuffer( MAX_PATH );

		{
			DWORD dwLength = ::GetModuleFileName( hInstance, lpModule, MAX_PATH );

			lpModule[ dwLength ] = '\0';
		}

		strModule.ReleaseBuffer();
	}

	//  Get Path
	if ( lpPathBuf && ( iPathBufSize > 0 ) )
	{
		::EZStrcpy( lpPathBuf, iPathBufSize, strModule );

		::PathRemoveFileSpec( lpPathBuf );

		{
			size_t tPathLen = ::_tcslen( lpPathBuf );

			if ( ( tPathLen > 0 ) && ( lpPathBuf[ ( tPathLen - 1 ) ] != '\\' ) )
				::EZStrcat( lpPathBuf, iPathBufSize, _T( "\\" ) );
		}
	}

	//  Get File
	if ( lpFileBuf && ( iFileBufSize > 0 ) )
	{
		int iFileFind = strModule.ReverseFind( '\\' );

		if ( iFileFind < 0 )
			::EZStrcpy( lpFileBuf, iFileBufSize, strModule );
		else
		{
			CString strFile = strModule.Right( ( strModule.GetLength() - ( iFileFind + 1 ) ) );

			::EZStrcpy( lpFileBuf, iFileBufSize, strFile );
		}
	}
}

//  ==========================================================================
//  GetComAppPath
//  ==========================================================================
inline void GetComAppPath( HWND hOwner, LPTSTR lpBuffer, const UINT iBufSize, const BOOL bCommon = TRUE )
{
	if ( lpBuffer && ( iBufSize > 0 ) )
	{
		const INT iCSIDL = ( bCommon ? CSIDL_COMMON_APPDATA : CSIDL_LOCAL_APPDATA );

		if ( ::SHGetSpecialFolderPath( hOwner, lpBuffer, iCSIDL, TRUE ) )
		{  
			//  Get Company Path
			if ( lpBuffer[ ( ::_tcslen( lpBuffer ) - 1 ) ] == '\\' )
				::EZStrcat( lpBuffer, iBufSize, _T(   "EZvision\\" ) );
			else
				::EZStrcat( lpBuffer, iBufSize, _T( "\\EZvision\\" ) );

			//  Create Folder
			if ( ERROR_SUCCESS != ::SHCreateDirectoryEx( hOwner, lpBuffer, NULL ) )
			{
				;
			}
		}
	}
}

//  ==========================================================================
//  GetWindowPath
//  ==========================================================================
inline void GetWindowPath( LPTSTR lpBuffer, const UINT iBufSize )
{
	if ( lpBuffer && ( iBufSize > 0 ) )
	{
		const UINT uiLength = ::GetWindowsDirectory( lpBuffer, iBufSize );

		if ( ( uiLength == 0 ) || ( uiLength > iBufSize ) )
			lpBuffer[ 0 ] = '\0';
		else
		{
			if ( lpBuffer[ ( uiLength - 1 ) ] != '\\' )
				::EZStrcat( lpBuffer, iBufSize, _T( "\\" ) );
		}
	}
}

//  ==========================================================================
//  EZSetCurrentDirectory
//  ==========================================================================
inline const BOOL EZSetCurrentDirectory( LPCTSTR lpNewDir, const BOOL bRestore = TRUE, const UINT iOldBufSize = 0, LPTSTR lpOldDir = NULL )
{
	BOOL bResult = FALSE;

	if ( lpNewDir && ( ::_tcslen( lpNewDir ) > 0 ) )
	{
		//  Get Old Directory
		TCHAR tzOldDir[ MAX_PATH ] = _T( "" );
		DWORD dwOldDirLen          = ::GetCurrentDirectory( MAX_PATH, tzOldDir );

		//  Set to New Directory
		bResult = ::SetCurrentDirectory( lpNewDir );

		//  Restore to Old Directory ?
		tzOldDir[ dwOldDirLen ] = '\0';

		if ( dwOldDirLen > 0 )
		{
			if ( bRestore )
				::SetCurrentDirectory( tzOldDir );

			if ( lpOldDir )
			{
				if ( iOldBufSize > dwOldDirLen )
					::EZStrcpy( lpOldDir, iOldBufSize, tzOldDir );
				else
				{
					::EZMemcpy( lpOldDir, iOldBufSize, tzOldDir, iOldBufSize );
					lpOldDir[ ( iOldBufSize - 1 ) ] = '\0';
				}
			}
		}
	}

	return bResult;
}
