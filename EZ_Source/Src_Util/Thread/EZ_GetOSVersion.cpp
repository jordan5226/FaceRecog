#include "Stdafx.h"
#include <Winnt.h>
#include <Windows.h>
#include <Winuser.h>
#include "EZ_GetOSVersion.h"

//  ==========================================================================
//  Link Library
//  ==========================================================================
#pragma comment( lib, "User32.lib" )

//  ==========================================================================
//  Defined
//  ==========================================================================
#ifndef VER_SUITE_WH_SERVER
#define VER_SUITE_WH_SERVER 0x00008000
#endif

#ifndef SM_SERVERR2
#define SM_SERVERR2 89
#endif

#ifndef VER_NT_WORKSTATION
#define VER_NT_WORKSTATION 0x0000001
#endif

#ifndef PROCESSOR_ARCHITECTURE_AMD64
#define PROCESSOR_ARCHITECTURE_AMD64 9
#endif

#ifndef PROCESSOR_ARCHITECTURE_IA64
#define PROCESSOR_ARCHITECTURE_IA64 6
#endif

#ifndef PROCESSOR_ARCHITECTURE_INTEL
#define PROCESSOR_ARCHITECTURE_INTEL 0
#endif

//
typedef void ( WINAPI *LPFN_PGNSI )( LPSYSTEM_INFO );				//  For GetNativeSystemInfo
typedef BOOL ( WINAPI *LPFN_ISWOW64PROCESS) ( HANDLE, PBOOL );		//  For IsWow64Process
typedef LONG ( WINAPI *pfnRTLGETVERSION )( RTL_OSVERSIONINFOEXW* );	//  For RtlGetVersion

//  ==========================================================================
//  Determines whether the current process is running under WOW64.
//  ==========================================================================
BOOL IsRunOnWow64()
{
	BOOL bIsWow64 = FALSE;

	{
		//  IsWow64Process is not available on all supported versions of Windows.
		//  Use GetModuleHandle to get a handle to the DLL that contains the function
		//  and GetProcAddress to get a pointer to the function if available.
		LPFN_ISWOW64PROCESS lpfnIsWow64Process = ( LPFN_ISWOW64PROCESS )::GetProcAddress( ::GetModuleHandle( _T( "kernel32.dll" ) ), "IsWow64Process" );

		//  
		if ( NULL != lpfnIsWow64Process )
		{	//  只有當64-bit OS下, 利用WOW64技術模擬執行32-bit app.時才會Return TRUE. Otherwise return FALSE.
			if ( !lpfnIsWow64Process( ::GetCurrentProcess(), &bIsWow64 ) )
			{
				::OutputDebugString( TEXT( "Failed to call IsWow64Process.\n" ) );
				return FALSE;
			}
		}
	}

	return ( bIsWow64 == TRUE );
}

//  ==========================================================================
//  Get System Type Info. ( 32-bit or 64-bit ) 
//  ==========================================================================
tagSystemType GetSystemType()
{	
	//  Get System Info.
	SYSTEM_INFO infoSystem;

	::memset( &infoSystem, 0, sizeof( SYSTEM_INFO ) );	

	//  Call GetNativeSystemInfo if supported or GetSystemInfo otherwise.
	LPFN_PGNSI lpGNSI = ( LPFN_PGNSI )::GetProcAddress( ::GetModuleHandle( _T( "kernel32.dll" ) ), "GetNativeSystemInfo" );

	if ( NULL != lpGNSI )
		lpGNSI( &infoSystem );
	else
		::GetSystemInfo( &infoSystem );	//  如果只呼GetSystemInfo, 在WOW64下會Return X86 Type(32-bit)

	//	 ..
	if ( ( infoSystem.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ) || ( infoSystem.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 ) )
		return sysTypeX64;		//  x64 ( AMD or Intel )
	else if ( infoSystem.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL )
		return sysTypeX86;		//  x86
	else
		return sysTypeUnKnow;	//  UnKnow
}

//  ==========================================================================
//  Get OS Version
//  ==========================================================================
tagWin32OSType IsShellSysType()
{
	//  Get OS Verion Info
	OSVERSIONINFOEX osVersionInfo;

	::memset( &osVersionInfo, 0, sizeof( OSVERSIONINFOEX ) );

	osVersionInfo.dwOSVersionInfoSize = sizeof( OSVERSIONINFOEX );

	if ( !::GetVersionEx( ( OSVERSIONINFO* )&osVersionInfo ) )
	{
		osVersionInfo.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );

		if ( !::GetVersionEx( ( OSVERSIONINFO* )&osVersionInfo ) ) 
			return osWindowUnKnow;
	}

	//  
	const UINT uiWinVer = ::GetVersion();

	if ( !( uiWinVer & 0x80000000 ) )
	{
		//  Higher
		if ( osVersionInfo.dwMajorVersion > 10L )
		{
			;
			return osWindowsHigher;
		}

		//  Windows Vista, Server 2008 ( R1, R2 ), Windows 7 ( 32, 64 ), Server 2012, Windows 8 ( 32, 64 ), Windows 10 ( 32, 64 ), Server 2016
		if ( osVersionInfo.dwMajorVersion == 6L )
		{
#if 1//_MSC_VER > 1300
			BYTE szProductType = osVersionInfo.wProductType;
#else
			BYTE szProductType = HIBYTE( osVersionInfo.wReserved[ 1 ] );
#endif

			switch ( osVersionInfo.dwMinorVersion )
			{
			default:	//  UnKnow
				return osWindowUnKnow;

			case 0L:	//  Vista or Server 2008 R1
				return ( ( szProductType == VER_NT_WORKSTATION ) ? osWindowsVista : osWindows2008Svr );

			case 1L:	//  Windows 7 or Server 2008 R2
				{
					if ( szProductType != VER_NT_WORKSTATION )
						return osWindows2008SvrR2;
					else if ( ::GetSystemType() == sysTypeX64 )
						return osWindows7x64;
					else 
						return osWindows7;
				}
				break;

			case 2L:	//  Windows 8 or Server 2012 R1 ; Windows 8.1 or Server 2012 R2 ; Windows 10 ; Server 2016
				{
					// 以 RtlGetVersion 獲取真正的版本號
					pfnRTLGETVERSION     fnRtlGetVersion   = NULL;
					RTL_OSVERSIONINFOEXW rtl_osVersionInfo = { 0 };

					rtl_osVersionInfo.dwOSVersionInfoSize = sizeof( RTL_OSVERSIONINFOEXW );

					fnRtlGetVersion = (pfnRTLGETVERSION)GetProcAddress( GetModuleHandle( _T("ntdll.dll") ), "RtlGetVersion" );

					if( fnRtlGetVersion )
					{
						fnRtlGetVersion( &rtl_osVersionInfo );

						//  Windows 10 ( 32, 64 ), Server 2016
						if ( rtl_osVersionInfo.dwMajorVersion == 10L )
						{
#if 1//_MSC_VER > 1300
							BYTE szProductType = rtl_osVersionInfo.wProductType;
#else
							BYTE szProductType = HIBYTE( rtl_osVersionInfo.wReserved[ 1 ] );
#endif

							switch ( rtl_osVersionInfo.dwMinorVersion )
							{
							default:
								return osWindowsHigher;

							case 0L:
								{
									if ( szProductType != VER_NT_WORKSTATION )
										return osWindows2016;
									else if ( ::GetSystemType() == sysTypeX64 )
										return osWindows10x64;
									else 
										return osWindows10;
								}
								break;
							}
						}

						//  Windows 8 or Server 2012 R1 ; Windows 8.1 or Server 2012 R2
						if ( rtl_osVersionInfo.dwMajorVersion == 6L )
						{
#if 1//_MSC_VER > 1300
							BYTE szProductType = rtl_osVersionInfo.wProductType;
#else
							BYTE szProductType = HIBYTE( rtl_osVersionInfo.wReserved[ 1 ] );
#endif

							switch ( rtl_osVersionInfo.dwMinorVersion )
							{
							case 2L:
							case 3L:
								{
									if ( szProductType != VER_NT_WORKSTATION )
										return osWindows2012Svr;
									else if ( ::GetSystemType() == sysTypeX64 )
										return osWindows8x64;
									else
										return osWindows8;
								}
								break;
							}
						}
					}
				}
				break;
			}
		}

		//  Windows Server 2003 ( R1, R2 ), Windows XP ( 32, 64 ), Windows 2000, Windows Home Server
		if ( osVersionInfo.dwMajorVersion == 5L )
		{  
			switch ( osVersionInfo.dwMinorVersion )
			{
			default: //  UnKnow
				return osWindowUnKnow;

			case 0L: //  Windows 2000
				return osWindows2000;

			case 1L: //  Windows XP ( 32 Bit )
				return osWindowsXP;

			case 2L:
				{
					//  Windows Home Server
#if 1//_MSC_VER > 1300 
					if ( osVersionInfo.wSuiteMask     == VER_SUITE_WH_SERVER )
#else
					if ( osVersionInfo.wReserved[ 0 ] == VER_SUITE_WH_SERVER )
#endif
					{
						return osWindowHomeSvr;
					}

					//  Windows XP ( 64 Bit )
#if 1//_MSC_VER > 1300 
					if ( osVersionInfo.wProductType              == VER_NT_WORKSTATION )
#else
					if ( HIBYTE ( osVersionInfo.wReserved[ 1 ] ) == VER_NT_WORKSTATION )
#endif
					{
						if ( ::GetSystemType() == sysTypeX64 )
							return osWindowsXPx64;
					}

					//  Windows 2003 Server ( R1, R2 )
					return ( ( ::GetSystemMetrics( SM_SERVERR2 ) == 0 ) ? osWindows2003Svr : osWindows2003SvrR2 );
				}
			}
		}

		//  Windows NT
		if ( osVersionInfo.dwMajorVersion == 4L )
			return osWindowsNT4;

		//  Windows NT
		if ( osVersionInfo.dwMajorVersion == 3L )
			return osWindowsNT3;
	}
	else if ( LOBYTE( LOWORD( uiWinVer ) ) & 4 )
	{
		return osWindows32s;
	}
	else if ( osVersionInfo.dwMajorVersion == 4L ) 
	{
		switch ( osVersionInfo.dwMinorVersion )
		{
		default:	//  UnKnow
			return osWindowUnKnow;

		case 0L:	//  Windows 95
			return osWindows95;

		case 10L:	//  Windows 98
			return osWindows98;

		case 90L:	//  Windows Me
			return osWindowsME;
		}
	}

	//  Unknow
	return osWindowUnKnow;
}
