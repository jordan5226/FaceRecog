#pragma once

#include <Excpt.h>
#include <ATLComTime.h>
#include "EZFunction_TByte.h"

//  ==========================================================================
//  Window Class Defined
//  ==========================================================================
typedef const HCURSOR   C_HCURSOR;
typedef const HGLOBAL   C_HGLOBAL;
typedef const HGDIOBJ   C_HGDIOBJ;
typedef const HTREEITEM C_HTREEITEM;
typedef const HINSTANCE C_HINSTANCE;
typedef const HWND      C_HWND;
typedef const WPARAM    C_WPARAM;
typedef const LPARAM    C_LPARAM;

typedef const CSize        C_CSIZE;
typedef const CRect        C_CRECT;
typedef const CString      C_CSTRING;
typedef const CStringArray C_CSTRINGARRAY;
typedef const GUID         C_GUID;
typedef const CFileStatus  C_CFILESTATUS;

typedef const CPoint   C_CPOINT;
typedef       CPoint*  LPCPOINT;
typedef const LPCPOINT LPCCPOINT;

typedef const CTimeSpan  C_CTIMESPAN;
typedef       CTimeSpan* LPCTIMESPAN;
typedef const CTimeSpan* LPCCTIMESPAN;

typedef const CTime  C_CTIME;
typedef       CTime* LPCTIME;
typedef const CTime* LPCCTIME;

typedef const COleDateTimeSpan  C_COLEDATETIMESPAN;
typedef       COleDateTimeSpan* LPCOLEDATETIMESPAN;
typedef const COleDateTimeSpan* LPCCOLEDATETIMESPAN;

typedef const COleDateTime  C_COLEDATETIME;
typedef       COleDateTime* LPCOLEDATETIME;
typedef const COleDateTime* LPCCOLEDATETIME;

typedef const CMenu   C_CMENU;
typedef       CMenu*  LPCMENU;
typedef const LPCMENU LPCCMENU;

typedef const CWnd   C_CWND;
typedef       CWnd*  LPCWND;
typedef const LPCWND LPCCWND;

typedef const DEVNAMES   C_DEVNAMES;
typedef       DEVNAMES*  LPDEVNAMES;
typedef const LPDEVNAMES LPCDEVNAMES;

typedef const LPDEVMODE    LPCDEVMODE;
typedef const LPNMTREEVIEW LPCNMTREEVIEW;

//  ==========================================================================
//  Safe Delete
//  ==========================================================================
#ifndef SAFE_DELETE_WINDOW
#define SAFE_DELETE_WINDOW( p ) { if ( p ) { if ( p->GetSafeHwnd() ) p->DestroyWindow(); delete p; p = NULL; } }
#endif

//  ==========================================================================
//  Window Bug
//  ==========================================================================
#ifndef LANG_SERBIAN_LATIN
#define LANG_SERBIAN_LATIN LANG_SERBIAN
#endif

#ifndef WS_EX_LAYOUTRTL
#define WS_EX_LAYOUTRTL 0x00400000L
#endif

#ifndef INVALID_FILE_ATTRIBUTES
#define INVALID_FILE_ATTRIBUTES ( ( DWORD )-1 )
#endif

//  ==========================================================================
//  Message Box
//  ==========================================================================
#ifdef _WINDOWS
#ifndef MESSAGEBOX
#if ( defined( RES_ARB ) || defined( RES_HEB ) || defined( RES_PRS ) )
#define MESSAGEBOX( hWnd, szText, szTitle, nType ) ::MessageBox( hWnd, szText, szTitle, ( nType | MB_RTLREADING ) )
#else
#define MESSAGEBOX( hWnd, szText, szTitle, nType ) ::MessageBox( hWnd, szText, szTitle, nType )
#endif
#endif
#endif

//  ==========================================================================
//  GetWindowPath
//  ==========================================================================
inline void GetWindowPath( CString& strWindowPath )
{
	::GetWindowPath( strWindowPath.GetBuffer( MAX_PATH ), MAX_PATH );

	strWindowPath.ReleaseBuffer();
}

inline CString GetWindowPath()
{
	CString strWindowPath = _T( "" );

	::GetWindowPath( strWindowPath );

	return strWindowPath;
}

//  ==========================================================================
//  GetWorkPath
//  ==========================================================================
inline void GetWorkPath( const HINSTANCE hInstance, CString& strModulePath, CString* lpModuleName = NULL )
{
	LPTSTR lpModulePathBuf = strModulePath.GetBuffer( MAX_PATH );

	if ( !lpModuleName )
		::GetWorkPath( hInstance, lpModulePathBuf, MAX_PATH, NULL, 0 );
	else
	{
		LPTSTR lpModuleNameBuf = lpModuleName->GetBuffer( MAX_PATH );

		::GetWorkPath( hInstance, lpModulePathBuf, MAX_PATH, lpModuleNameBuf, MAX_PATH );

		lpModuleName->ReleaseBuffer();
	}

	strModulePath.ReleaseBuffer();
}

inline CString GetWorkPath( const HINSTANCE hInstance, CString* lpModuleName = NULL )
{
	CString strModulePath = _T( "" );

	::GetWorkPath( hInstance, strModulePath, lpModuleName );

	return strModulePath;
}

//  ==========================================================================
//  GetComAppDataPath
//  ==========================================================================
inline void GetComAppDataPath( const HWND hOwner, const BOOL bCommon, CString& strComAppDataPath )
{
	::GetComAppPath( hOwner, strComAppDataPath.GetBuffer( MAX_PATH ), MAX_PATH, bCommon );

	strComAppDataPath.ReleaseBuffer();
}

inline CString GetComAppDataPath( const HWND hOwner, const BOOL bCommon )
{
	CString strComAppDataPath = _T( "" );
	
	::GetComAppDataPath( hOwner, bCommon, strComAppDataPath );

	return strComAppDataPath;
}

//  ==========================================================================
//  GetComAppNamePath
//  ==========================================================================
inline void GetComAppNamePath( const CString& strComAppDataPath, CString strWorkPath, CString& strComAppNamePath )
{
#if _MSC_VER > 1400
	strWorkPath = strWorkPath.TrimRight( _T( "\\" ) );
#else
	strWorkPath.TrimRight( _T( "\\" ) );
#endif

	{
		CString strIniFile  = _T( "" );
		CString strPathName = _T( "" );

		for ( INT iFind; ; )
		{
			strIniFile.Format( _T( "%s\\EZAppSetting.ini" ), strWorkPath );

			::GetPrivateProfileString( _T( "Setting" ), _T( "PathName" ), _T( "" ), strPathName.GetBuffer( MAX_PATH ), MAX_PATH, strIniFile );

			strPathName.ReleaseBuffer();

			if ( !strPathName.IsEmpty() )
			{
				strComAppNamePath.Format( _T( "%s%s\\" ), strComAppDataPath, strPathName );
				break;
			}
			else
			{
				iFind = strWorkPath.ReverseFind( '\\' );

				if ( iFind < 0 )
				{
					strComAppNamePath = strComAppDataPath;
					break;
				}

				strWorkPath = strWorkPath.Left( iFind );
			}
		}
	}
}

inline CString GetComAppNamePath( const CString& strComAppDataPath, const CString& strWorkPath )
{
	CString strComAppNamePath = _T( "" );

	::GetComAppNamePath( strComAppDataPath, strWorkPath, strComAppNamePath );

	return strComAppNamePath;
}

//  ==========================================================================
//  WritePrivateProfileInt
//  ==========================================================================
inline BOOL WritePrivateProfileIntA( LPCSTR lpAppName, LPCSTR lpKeyName, const INT iValue, LPCSTR lpFileName )
{
	CStringA strValue = "";

	strValue.Format( "%d", iValue );

	return ::WritePrivateProfileStringA( lpAppName, lpKeyName, strValue, lpFileName );
}

inline BOOL WritePrivateProfileIntW( LPCWSTR lpAppName, LPCWSTR lpKeyName, const INT iValue, LPCWSTR lpFileName )
{
	CStringW strValue = L"";

	strValue.Format( L"%d", iValue );

	return ::WritePrivateProfileStringW( lpAppName, lpKeyName, strValue, lpFileName );
}

#ifdef UNICODE
#define WritePrivateProfileInt	WritePrivateProfileIntW
#else
#define WritePrivateProfileInt  WritePrivateProfileIntA
#endif

//  ==========================================================================
//  EZOutputDebugString
//
//  lpFormat => it must hasn't "%" word, exp : "100 %%", because it will crashed.
//  ==========================================================================
inline void EZOutputDebugString( _In_ _Printf_format_string_ LPCSTR lpFormat, ... )
{
	//  
	va_list argList;

	va_start( argList, lpFormat );

	//  
	CStringA strMsg = "";

	strMsg.FormatV( lpFormat, argList );

	::OutputDebugStringA( strMsg );
}

inline void EZOutputDebugString( _In_ _Printf_format_string_ LPCWSTR lpFormat, ... )
{
	//  
	va_list argList;

	va_start( argList, lpFormat );

	//  
	CStringW strMsg = L"";

	strMsg.FormatV( lpFormat, argList );

	::OutputDebugStringW( strMsg );
}

//  ==========================================================================
//  EZOutputDebugString
//
//  lpFormat => it must hasn't "%" word, exp : "100 %%", because it will crashed.
//  ==========================================================================
inline BOOL EZDumpDebugMessage( BOOL bDumpMessage, _In_ _Printf_format_string_ LPCSTR lpFormat, ... )
{
	if ( bDumpMessage )
	{
		//  
		va_list argList;

		va_start( argList, lpFormat );

		//  
		CStringA strMsg = "";

		strMsg.FormatV( lpFormat, argList );

		::OutputDebugStringA( strMsg );
	}

	return bDumpMessage;
}

inline BOOL EZDumpDebugMessage( BOOL bDumpMessage, _In_ _Printf_format_string_ LPCWSTR lpFormat, ... )
{
	if ( bDumpMessage )
	{
		//  
		va_list argList;

		va_start( argList, lpFormat );

		//  
		CStringW strMsg = L"";

		strMsg.FormatV( lpFormat, argList );

		::OutputDebugStringW( strMsg );
	}

	return bDumpMessage;
}

//  ==========================================================================
//  EZFilterException
//  ==========================================================================
inline int EZFilterException( unsigned int iCode, struct _EXCEPTION_POINTERS* lpException ) 
{
	switch ( iCode )
	{
	case EXCEPTION_ACCESS_VIOLATION:	//  Access Violation
	case EXCEPTION_STACK_OVERFLOW:		//  Stack Overflow
	case EXCEPTION_INVALID_HANDLE:		//  Invalid Handle
		{
			;
		}
		return EXCEPTION_EXECUTE_HANDLER;

	default:
		{
			;
		}
		return EXCEPTION_CONTINUE_SEARCH;
	}
}

#define EZ_FILTER_EXCEPT EZFilterException( GetExceptionCode(), GetExceptionInformation() ) 

//  ==========================================================================
//  EZFilterException
//  ==========================================================================
inline int GetDeviceCapsByWnd( HWND hWnd, const int nIndex )
{
	int nVal = -1;
	HDC hDC  = ::GetDC( hWnd );

	if ( hDC )
	{
		nVal = ::GetDeviceCaps( hDC, nIndex );

		::ReleaseDC( hWnd, hDC );
	}

	return nVal;
}
