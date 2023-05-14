#pragma once

#include "EZ_XMLDlg.h"
#include "..\Thread\EZ_Thread.h"

//  ==========================================================================
//  EZ_ThreadXMLWnd
//  ==========================================================================
class EZ_ThreadXMLWnd : public EZ_XMLWnd, protected EZ_Thread
{
protected:
	;

public:
	EZ_ThreadXMLWnd( LPEZLANGUAGE lpXMLLanguage = NULL, C_BOOL bRTLCheck = TRUE )
		: EZ_XMLWnd( lpXMLLanguage, bRTLCheck ), EZ_Thread()
	{
		;
	}

	virtual ~EZ_ThreadXMLWnd()
	{
		;
	}

	virtual void Initial_Thread( C_INT iEventCnt, C_BOOL bAllocWaitEvent = TRUE )
	{
		EZ_Thread::Initial_Thread( EZ_ThreadXMLWnd::InitialThreadProc, this, iEventCnt, bAllocWaitEvent );
	}

protected:
	afx_msg void OnDestroy()
	{
		if ( EZ_Thread::m_hExit )
			EZ_Thread::Set_Exit_Event( TRUE, TRUE );

		EZ_XMLWnd::OnDestroy();
	}

	static EZTHREADRETURN __stdcall InitialThreadProc( LPVOID lpUserData ) 
	{ 
		return ( lpUserData ? ( ( EZ_ThreadXMLWnd* )lpUserData )->Thread_Process() : 0 );
	}
};

typedef const EZ_ThreadXMLWnd  C_EZTHREADXMLWND;
typedef       EZ_ThreadXMLWnd* LPEZTHREADXMLWND;
typedef const EZ_ThreadXMLWnd* LPCEZTHREADXMLWND;

//  ==========================================================================
//  EZ_ThreadXMLDlg
//  ==========================================================================
class EZ_ThreadXMLDlg : public EZ_XMLDlg, protected EZ_Thread
{
protected:
	;

public:
	EZ_ThreadXMLDlg( C_INT iDlgID, HWND hParentWnd = NULL, LPEZLANGUAGE lpXMLLanguage = NULL, C_BOOL bRTLCheck = TRUE )
		: EZ_XMLDlg( iDlgID, hParentWnd, lpXMLLanguage, bRTLCheck ), EZ_Thread()
	{
		;
	}

	EZ_ThreadXMLDlg( C_INT iDlgID, CWnd* lpParentWnd = NULL, LPEZLANGUAGE lpXMLLanguage = NULL, C_BOOL bRTLCheck = TRUE )
		: EZ_XMLDlg( iDlgID, lpParentWnd, lpXMLLanguage, bRTLCheck ), EZ_Thread()
	{
		;
	}

	virtual ~EZ_ThreadXMLDlg()
	{
		;
	}

	virtual void Initial_Thread( C_INT iEventCnt, C_BOOL bAllocWaitEvent = TRUE )
	{
		EZ_Thread::Initial_Thread( EZ_ThreadXMLDlg::InitialThreadProc, this, iEventCnt, bAllocWaitEvent );
	}

protected:
	afx_msg void OnDestroy()
	{
		if ( EZ_Thread::m_hExit )
			EZ_Thread::Set_Exit_Event( TRUE, TRUE );

		EZ_XMLDlg::OnDestroy();
	}

	static EZTHREADRETURN __stdcall InitialThreadProc( LPVOID lpUserData ) 
	{ 
		return ( lpUserData ? ( ( EZ_ThreadXMLDlg* )lpUserData )->Thread_Process() : 0 );
	}
};

typedef const EZ_ThreadXMLDlg  C_EZTHREADXMLDLG;
typedef       EZ_ThreadXMLDlg* LPEZTHREADXMLDLG;
typedef const EZ_ThreadXMLDlg* LPCEZTHREADXMLDLG;

//  ==========================================================================
//  EZ_ThreadLanguageDlg
//  ==========================================================================
class EZ_ThreadLanguageDlg : public EZ_ThreadXMLDlg
{
protected:
	CLanguage m_xmlLanguage;

public:
	EZ_ThreadLanguageDlg( C_INT iDlgID, HWND hParentWnd = NULL, C_BOOL bRTLCheck = TRUE )
		: EZ_ThreadXMLDlg( iDlgID, hParentWnd, &m_xmlLanguage, bRTLCheck ), m_xmlLanguage()
	{
		;
	}

	EZ_ThreadLanguageDlg( C_INT iDlgID, CWnd* lpParentWnd = NULL, C_BOOL bRTLCheck = TRUE )
		: EZ_ThreadXMLDlg( iDlgID, lpParentWnd, &m_xmlLanguage, bRTLCheck ), m_xmlLanguage()
	{
		;
	}

	virtual ~EZ_ThreadLanguageDlg()
	{
		this->CloseXML();
	}

	virtual void OpenXML( LPCTSTR lpXMLFile, C_EZ_LANG_ID iLanguageID = EZ_LANG_DEFA )
	{
		//  Open XML ?
		this->CloseXML();

		{
			CDC* lpDC = ( EZ_ThreadXMLDlg::GetSafeHwnd() ? EZ_ThreadXMLDlg::GetDC() : NULL );

			if ( !this->m_xmlLanguage.Open( lpXMLFile, ( EZ_LANG_ID )iLanguageID, lpDC ) )
				::EZOutputDebugString( _T( "\n" ) );

			if ( lpDC ) { EZ_ThreadXMLDlg::ReleaseDC( lpDC ); lpDC = NULL; }
		}

		//  RTL Style ?
		if ( EZ_ThreadXMLDlg::m_bRTLCheck && EZ_ThreadXMLDlg::GetSafeHwnd() )
		{
#if ( defined( RES_ARB ) || defined( RES_HEB ) || defined( RES_PRS ) )
			EZ_ThreadXMLDlg::ModifyStyleEx( 0, ( WS_EX_LAYOUTRTL | WS_EX_RTLREADING ), 0 );
#else
			if ( this->m_xmlLanguage.IsRTLStyle() )
				EZ_ThreadXMLDlg::ModifyStyleEx( 0, ( WS_EX_LAYOUTRTL | WS_EX_RTLREADING ), 0 );
#endif
		}
	}

	virtual void CloseXML()
	{
		this->m_xmlLanguage.Close();
	}

	virtual LPEZLANGUAGE GetXMLLanguage()
	{
		return &this->m_xmlLanguage;
	}

protected:
	afx_msg void OnDestroy()
	{
		this->CloseXML();

		EZ_ThreadXMLDlg::OnDestroy();
	}
};

typedef const EZ_ThreadLanguageDlg  C_EZTHREADLANGUAGEDLG;
typedef       EZ_ThreadLanguageDlg* LPEZTHREADLANGUAGEDLG;
typedef const EZ_ThreadLanguageDlg* LPCEZTHREADLANGUAGEDLG;
