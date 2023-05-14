#ifndef EZGETOSVERSION_H
#define EZGETOSVERSION_H

#pragma once

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
enum tagWin32OSType
{
	osWindowUnKnow = 0,
	osWindows32s,
	osWindowsNT3,
	osWindows95,
	osWindows98,
	osWindowsME,
	osWindowsNT4,
	osWindows2000,			//  ( dwMajorVersion == 5 ), ( dwMinorVersion == 0 )
	osWindowHomeSvr,		//  ( dwMajorVersion == 5 ), ( dwMinorVersion == 2 )
	osWindowsXP,			//  ( dwMajorVersion == 5 ), ( dwMinorVersion == 1 )
	osWindowsXPx64,			//  ( dwMajorVersion == 5 ), ( dwMinorVersion == 2 )
	osWindows2003Svr,		//  ( dwMajorVersion == 5 ), ( dwMinorVersion == 2 )
	osWindows2003SvrR2,		//  ( dwMajorVersion == 5 ), ( dwMinorVersion == 2 )
	osWindowsVista,			//  ( dwMajorVersion == 6 ), ( dwMinorVersion == 0 )
	osWindows2008Svr,		//  ( dwMajorVersion == 6 ), ( dwMinorVersion == 0 )
	osWindows2008SvrR2,		//  ( dwMajorVersion == 6 ), ( dwMinorVersion == 1 ), All Windows Server OSs after Win2008-R2 are only x64.
	osWindows7,				//  ( dwMajorVersion == 6 ), ( dwMinorVersion == 1 )
	osWindows7x64,			//  ( dwMajorVersion == 6 ), ( dwMinorVersion == 1 )
	osWindows2012Svr,		//  ( dwMajorVersion == 6 ), ( dwMinorVersion == 2 )
	osWindows8,				//  ( dwMajorVersion == 6 ), ( dwMinorVersion == 2 )
	osWindows8x64,			//  ( dwMajorVersion == 6 ), ( dwMinorVersion == 2 )
	osWindows10,			//  ( dwMajorVersion == 10 ), ( dwMinorVersion == 0 )
	osWindows10x64,			//  ( dwMajorVersion == 10 ), ( dwMinorVersion == 0 )
	osWindows2016,			//  ( dwMajorVersion == 10 ), ( dwMinorVersion == 0 )
	osWindowsHigher,
};

typedef const tagWin32OSType C_TAGWIN32OSTYPE;

enum tagSystemType
{
	sysTypeUnKnow = 0,
	sysTypeX86,
	sysTypeX64,	
};

typedef const tagSystemType C_TAGSYSTEMTYPE;

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
extern tagWin32OSType IsShellSysType();	//  Get OS Version	
extern tagSystemType  GetSystemType();	//  Get System Type( 32-bit/64-bit )	
extern BOOL			  IsRunOnWow64();	//  Vista/WinXP with SP2 以上才有作用

#endif	//  #ifndef EZGETOSVERSION_H