#include "stdafx.h"
#include "EZ_StringCast.h"


wchar_t* EZStrCast::MultiByteToWideChar( _In_ const char* lpszStr, _In_ const int iCodePage/* = CP_ACP*/ )
{
	int    iNeedSize = ::MultiByteToWideChar( iCodePage, 0, lpszStr, -1, NULL, 0 );
	WCHAR* pWideBuf  = new WCHAR[ iNeedSize + 1 ];

	::memset( pWideBuf, 0, sizeof( WCHAR ) * ( iNeedSize + 1 ) );

	::MultiByteToWideChar( iCodePage, 0, lpszStr, -1, pWideBuf, iNeedSize );

	return pWideBuf;
}

char* EZStrCast::WideCharToMultiByte( _In_ const wchar_t* lpwzStr, _In_ const int iCodePage/* = CP_ACP*/ )
{
	int   iNeedSize = ::WideCharToMultiByte( iCodePage, 0, lpwzStr, -1, NULL, 0, NULL, NULL );
	char* pBuf      = new char[ iNeedSize + 1 ];

	::memset( (void*)pBuf, 0, sizeof(char) * ( iNeedSize + 1 ) );

	::WideCharToMultiByte( iCodePage, 0, lpwzStr, -1, pBuf, iNeedSize, NULL, NULL );

	return pBuf;
}

std::wstring EZStrCast::MByte2WChar( _In_ const char* lpszStr, _In_ const int iCodePage/* = CP_ACP*/ )
{
	std::string str = lpszStr;

	return EZStrCast::MByte2WChar( str, iCodePage );
}

std::wstring EZStrCast::MByte2WChar( _In_ const std::string& str, _In_ const int iCodePage/* = CP_ACP*/ )
{
	WCHAR* pWideBuf = EZStrCast::MultiByteToWideChar( str.c_str(), iCodePage );

	std::wstring wstrReturn( pWideBuf );
	delete[] pWideBuf;

	return wstrReturn;
}

CStringW EZStrCast::MByte2WChar( _In_ const CStringA& str, _In_ const int iCodePage/* = CP_ACP*/ )
{
	WCHAR* pWideBuf = EZStrCast::MultiByteToWideChar( (LPCSTR)str, iCodePage );

	CStringW wstrReturn( pWideBuf );
	delete[] pWideBuf;

	return wstrReturn;
}

std::string EZStrCast::WChar2MByte( _In_ const wchar_t* lpwzStr, _In_ const int iCodePage/* = CP_ACP*/ )
{
	std::wstring wstr = lpwzStr;

	return EZStrCast::WChar2MByte( wstr, iCodePage );
}

std::string EZStrCast::WChar2MByte( _In_ const std::wstring& wstr, _In_ const int iCodePage/* = CP_ACP*/ )
{
	char* pBuf = EZStrCast::WideCharToMultiByte( wstr.c_str(), iCodePage );

	std::string strReturn( pBuf );
	delete[] pBuf;

	return strReturn;
}

CStringA EZStrCast::WChar2MByte( _In_ const CStringW& wstr, _In_ const int iCodePage/* = CP_ACP*/ )
{
	char* pBuf = EZStrCast::WideCharToMultiByte( (LPCWSTR)wstr, iCodePage );

	CStringA strReturn( pBuf );
	delete[] pBuf;

	return strReturn;
}

//  ==========================================================================
//  Ansi2UTF_8
//  ==========================================================================
void EZStrCast::Ansi2UTF_8( _Inout_ CStringA& strBuf )
{
	CStringW wstrTmp = L"";

	wstrTmp = EZStrCast::MByte2WChar( strBuf );
	strBuf  = EZStrCast::WChar2MByte( wstrTmp, CP_UTF8 );
}

void EZStrCast::Ansi2UTF_8( _Inout_ std::string& strBuf )
{
	std::wstring wstrTmp = L"";

	wstrTmp = EZStrCast::MByte2WChar( strBuf );
	strBuf  = EZStrCast::WChar2MByte( wstrTmp, CP_UTF8 );
}

void EZStrCast::Ansi2UTF_8( _Inout_ char* lpszBuf, _In_ const int iBufSize )
{
	WCHAR* pWideBuf = EZStrCast::MultiByteToWideChar( lpszBuf );
	char*  pBuf     = EZStrCast::WideCharToMultiByte( pWideBuf, CP_UTF8 );

	if( iBufSize > (INT)::strlen( pBuf ) )
		::strcpy_s( lpszBuf, iBufSize, pBuf );

	if( pWideBuf )
	{
		delete[] pWideBuf;
		pWideBuf = NULL;
	}
	
	if( pBuf )
	{
		delete[] pBuf;
		pBuf = NULL;
	}
}

//  ==========================================================================
//  ToSqlString
//  ==========================================================================
std::string EZStrCast::ToSqlString( const char* s )
{
	return std::string("'") + s + "'";
}

std::string EZStrCast::ToSqlString( const SYSTEMTIME& t )
{
	char buf[ 64 ] = { 0 };

	StringCchPrintfA( buf, 64, "'%04d-%02d-%02d %02d:%02d:%02d.%03d'",
		t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds );

	return buf;
}

//  ==========================================================================
//  ToLikeString
//  ==========================================================================
std::string EZStrCast::ToLikeString( const char* str )
{
	bool        bEQ = true;
	std::string s   = str;

	if ( s[ 0 ] == '*' )
	{
		bEQ    = false;
		s[ 0 ] = '%';
	}

	if ( s[ s.length() - 1 ] == '*' )
	{
		bEQ                 = false;
		s[ s.length() - 1 ] = '%';
	}

	return ( bEQ ? std::string(" = '") : std::string(" like '") ) + s + "'";
}
