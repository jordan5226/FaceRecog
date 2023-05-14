
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions





#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif




//  ==========================================================================
//  Global Definition
//  ==========================================================================
#define FACERECOG_RES_INI_FULLPATH		( EZ_Mutex::gm_WorkPath + _T( "FaceRecogRes\\FaceRecogRes.ini" ) )
#define FACERECOG_RES_INI_PATH			( EZ_Mutex::gm_WorkPath + _T( "FaceRecogRes\\" ) )
#define FACERECOG_XML_FILE				( EZ_Mutex::gm_WorkPath + _T( "FaceRecogRes\\FaceRecog.xml" ) )
#define FACERECOG_EXPORTS				1
#define EZ_MY_PROJECT					1


//  ==========================================================================
//  Global Include
//  ==========================================================================
#include "resource.h"
#include "..\..\EZ_Source\EZDefined.h"
#include "..\..\EZ_Source\Src_Util\Thread\EZ_Mutex.h"
#include "..\..\EZ_Source\Src_Util\Thread\EZ_Event.h"
#include "..\..\EZ_Source\Src_Util\EZ_TemplateVectorArray.h"


//  ==========================================================================
//  Global Variable
//  ==========================================================================
extern HCURSOR				g_hOSHand;
extern HCURSOR				g_hOSSizeAll;
extern HCURSOR				g_hOSSizeNESW;
extern HCURSOR				g_hOSSizeNS;
extern HCURSOR				g_hOSSizeNWSE;
extern HCURSOR				g_hOSSizeWE;
extern CString				g_strStyleIniFullPath;            // 指定UI風格的INI配置文件路徑
extern CString				g_strStylePath;

#pragma warning(disable: 4819)
