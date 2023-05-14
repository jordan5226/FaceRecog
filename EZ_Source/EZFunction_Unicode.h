#pragma once

#include "EZFunction_TByte.h"

//  ==========================================================================
//  EZStrcpy
//  ==========================================================================
inline BOOL EZStrcpyW( LPWSTR lpDstBuf, const UINT iDstBufSize, LPCWSTR lpSrcBuf )
{
	BOOL bResult = TRUE;

	try 
	{
#if _MSC_VER > 1400
		bResult = ( ::wcscpy_s( lpDstBuf, iDstBufSize, lpSrcBuf ) == 0 );
#else
		::wcscpy( lpDstBuf, lpSrcBuf );
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
inline void EZStrcatW( LPWSTR lpDstBuf, const UINT iDstBufSize, LPCWSTR lpSrcBuf )
{
	try 
	{
#if _MSC_VER > 1400
		::wcscat_s( lpDstBuf, iDstBufSize, lpSrcBuf );
#else
		::wcscat(   lpDstBuf,              lpSrcBuf );
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
inline const INT EZStrcmpiW( LPCWSTR lpDstBuf, LPCWSTR lpSrcBuf )
{
	INT iResult = -1;

	try 
	{
		iResult = ::_wcsicmp( lpDstBuf, lpSrcBuf );
	}
	catch ( ... )
	{
		;
	}

	return iResult;
}

//  ==========================================================================
//  EZSetCurrentDirectoryW
//  ==========================================================================
inline const BOOL EZSetCurrentDirectoryW( LPCWSTR lpNewDir, const BOOL bRestore = TRUE, const UINT iOldBufSize = 0, LPWSTR lpOldDir = NULL )
{
	BOOL bResult = FALSE;

	if ( lpNewDir && ( ::wcslen( lpNewDir ) > 0 ) )
	{
		//  Get Old Directory
		wchar_t szOldDir[ MAX_PATH ] = L"";

		::GetCurrentDirectoryW( MAX_PATH, szOldDir );

		//  Set to New Directory
		bResult = ::SetCurrentDirectoryW( lpNewDir );

		//  Restore to Old Directory ?
		const UINT iOldDirLength = ( const UINT )::wcslen( szOldDir );

		if ( iOldDirLength > 0 )
		{
			if ( bRestore )
				::SetCurrentDirectoryW( szOldDir );

			if ( lpOldDir && ( iOldBufSize > 0 ) )
			{
				if ( iOldBufSize > iOldDirLength )
					::EZStrcpyW( lpOldDir, iOldBufSize, szOldDir );
				else
				{
					::EZMemcpy( lpOldDir, iOldBufSize, szOldDir, iOldBufSize );
					lpOldDir[ ( iOldBufSize - 1 ) ] = '\0';
				}
			}
		}
	}

	return bResult;
}
