
// stdafx.cpp : source file that includes just the standard includes
// FaceRecog.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

//  ==========================================================================
//   Global Variable
//  ==========================================================================
HCURSOR				g_hOSHand             = ::LoadCursor(NULL, IDC_HAND);
HCURSOR				g_hOSSizeAll          = ::LoadCursor(NULL, IDC_SIZEALL);
HCURSOR				g_hOSSizeNESW         = ::LoadCursor(NULL, IDC_SIZENESW);
HCURSOR				g_hOSSizeNS           = ::LoadCursor(NULL, IDC_SIZENS);
HCURSOR				g_hOSSizeNWSE         = ::LoadCursor(NULL, IDC_SIZENWSE);
HCURSOR				g_hOSSizeWE           = ::LoadCursor(NULL, IDC_SIZEWE);
CString				g_strStyleIniFullPath = FACERECOG_RES_INI_FULLPATH;
CString				g_strStylePath        = FACERECOG_RES_INI_PATH;
