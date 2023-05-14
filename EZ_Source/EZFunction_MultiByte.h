#pragma once

#include "EZFunction_TByte.h"

//  ==========================================================================
//  EZStrcpy
//  ==========================================================================
inline BOOL EZStrcpyA( LPSTR lpDstBuf, const UINT iDstBufSize, LPCSTR lpSrcBuf )
{
	BOOL bResult = TRUE;

	try 
	{
#if _MSC_VER > 1400
		bResult = ( ::strcpy_s( lpDstBuf, iDstBufSize, lpSrcBuf ) == 0 );
#else
		::strcpy( lpDstBuf, lpSrcBuf );
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
inline void EZStrcatA( LPSTR lpDstBuf, const UINT iDstBufSize, LPCSTR lpSrcBuf )
{
	try 
	{
#if _MSC_VER > 1400
		::strcat_s( lpDstBuf, iDstBufSize, lpSrcBuf );
#else
		::strcat(   lpDstBuf,              lpSrcBuf );
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
inline const INT EZStrcmpiA( LPCSTR lpDstBuf, LPCSTR lpSrcBuf )
{
	INT iResult = -1;

	try 
	{
		iResult = ::_strcmpi(  lpDstBuf, lpSrcBuf );
	}
	catch ( ... )
	{
		;
	}

	return iResult;
}

//  ==========================================================================
//  EZSetCurrentDirectoryA
//  ==========================================================================
inline const BOOL EZSetCurrentDirectoryA( LPCSTR lpNewDir, const BOOL bRestore = TRUE, const UINT iOldBufSize = 0, LPSTR lpOldDir = NULL )
{
	BOOL bResult = FALSE;

	if ( lpNewDir && ( ::strlen( lpNewDir ) > 0 ) )
	{
		//  Get Old Directory
		char szOldDir[ MAX_PATH ] = "";

		::GetCurrentDirectoryA( MAX_PATH, szOldDir );

		//  Set to New Directory
		bResult = ::SetCurrentDirectoryA( lpNewDir );

		//  Restore to Old Directory ?
		const UINT iOldDirLength = ( const UINT )::strlen( szOldDir );

		if ( iOldDirLength > 0 )
		{
			if ( bRestore )
				::SetCurrentDirectoryA( szOldDir );

			if ( lpOldDir && ( iOldBufSize > 0 ) )
			{
				if ( iOldBufSize > iOldDirLength )
					::EZStrcpyA( lpOldDir, iOldBufSize, szOldDir );
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
