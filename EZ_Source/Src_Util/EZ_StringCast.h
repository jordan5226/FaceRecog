#pragma once

#include <string>
#include <strsafe.h>
using namespace std;

#define ACL_MAX_STR_LENGTH			1024
#define ANSI2UNICODE( str )			EZStrCast::MByte2WChar( str )
#define M2W_UTF8( str )				EZStrCast::MByte2WChar( str, CP_UTF8 )
#define UNICODE2ANSI( wstr )		EZStrCast::WChar2MByte( wstr )
#define W2M_UTF8( wstr )			EZStrCast::WChar2MByte( wstr, CP_UTF8 )

class EZStrCast
{
public:
	EZStrCast() {}

	static wchar_t*		MultiByteToWideChar( _In_ const char* lpszStr,    _In_ const int iCodePage = CP_ACP );
	static char*		WideCharToMultiByte( _In_ const wchar_t* lpwzStr, _In_ const int iCodePage = CP_ACP );

	static std::string	WChar2MByte( _In_ const wchar_t* lpwzStr,   _In_ const int iCodePage = CP_ACP );
	static std::string	WChar2MByte( _In_ const std::wstring& wstr, _In_ const int iCodePage = CP_ACP );
	static CStringA		WChar2MByte( _In_ const CStringW& wstr,     _In_ const int iCodePage = CP_ACP );

	static std::wstring	MByte2WChar( _In_ const char* lpszStr,    _In_ const int iCodePage = CP_ACP );
	static std::wstring	MByte2WChar( _In_ const std::string& str, _In_ const int iCodePage = CP_ACP );
	static CStringW		MByte2WChar( _In_ const CStringA& str,    _In_ const int iCodePage = CP_ACP );

	static void			Ansi2UTF_8( _Inout_ CStringA& strBuf );
	static void			Ansi2UTF_8( _Inout_ std::string& strBuf );
	static void			Ansi2UTF_8( _Inout_ char* lpszBuf, _In_ const int iBufSize );

	static std::string	ToSqlString( const char* s );
	static std::string	ToSqlString( const SYSTEMTIME& t );
	static std::string	ToLikeString( const char* str );
};
