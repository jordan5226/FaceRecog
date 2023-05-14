#pragma once

#include "EZ_ModifyMenuInfo.h"
#include "EZ_SubclassWndInfo.h"
#include "..\Read XML\Language.h"
#include "..\HtmlHelp\Explainstc.h"

//  ==========================================================================
//  
//  ==========================================================================
#define _USE_BALLOONTIP_	1

//  ==========================================================================
//  EZ_XMLWnd
//  ==========================================================================
class EZ_XMLWnd : public CWnd
{
public:
	DECLARE_DYNAMIC ( EZ_XMLWnd );

	DECLARE_MESSAGE_MAP()

protected:
	BOOL         m_bRTLCheck;
	LPEZLANGUAGE m_pXMLObj;

public:
	EZ_XMLWnd( LPEZLANGUAGE lpXMLObj = NULL, C_BOOL bRTLCheck = TRUE );
	virtual ~EZ_XMLWnd();

	virtual BOOL Create( CWnd* lpParentWnd, UINT nID, RECT& rcClient, LPCTSTR lpCaption, C_INT iStyle );

	//  ==========================================================================
	//  Window Message
	//  ==========================================================================
protected:
	afx_msg void OnDestroy();
	afx_msg INT  OnCreate( LPCREATESTRUCT lpCreateStruct );

	//  ==========================================================================
	//  Easy Function
	//  ==========================================================================
public:
	virtual BOOL Create( HWND hParentWnd, UINT nID, RECT& rcClient )
	{
		C_INT iStyle = ( WS_CHILDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS );

		return this->Create( ( hParentWnd ? CWnd::FromHandle( hParentWnd ) : NULL ), nID, rcClient, _T( "" ), iStyle );
	}

	virtual BOOL Create( HWND hParentWnd, UINT nID, RECT& rcClient, LPCTSTR lpCaption )
	{
		C_INT iStyle = ( WS_CHILDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS );

		return this->Create( ( hParentWnd ? CWnd::FromHandle( hParentWnd ) : NULL ), nID, rcClient, lpCaption, iStyle );
	}

	virtual BOOL Create( CWnd* lpParentWnd, UINT nID, RECT& rcClient )
	{
		C_INT iStyle = ( WS_CHILDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS );

		return this->Create( lpParentWnd, nID, rcClient, _T( "" ), iStyle );
	}

	virtual BOOL Create( CWnd* lpParentWnd, UINT nID, RECT& rcClient, LPCTSTR lpCaption )
	{
		C_INT iStyle = ( WS_CHILDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS );

		return this->Create( lpParentWnd, nID, rcClient, lpCaption, iStyle );
	}

protected:
#ifdef _DEBUG
	virtual void AssertValid() const
	{
		CWnd::AssertValid();
	}

	virtual void Dump( CDumpContext& dc ) const 
	{ 
		CWnd::Dump( dc ); 
	}
#endif

	afx_msg BOOL OnEraseBkgnd( CDC* lpDC )
	{
		return TRUE;
	}

	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
public:
	inline C_BOOL IsRTLStyle() const
	{
		return ( this->m_pXMLObj ? this->m_pXMLObj->IsRTLStyle() : FALSE );
	}

	inline C_EZ_LANG_ID GetXMLID() const
	{
		return ( this->m_pXMLObj ? this->m_pXMLObj->GetCurLangID() : EZ_LANG_DEFA );
	}

	inline LPCEZLANGUAGE GetXMLObjPtr() const
	{
		return this->m_pXMLObj;
	}

	inline INT MessageBox( LPCTSTR lpText, LPCTSTR lpCaption, UINT nType )
	{
		return EZ_XMLWnd::MessageBox( this->m_pXMLObj, this, lpText, lpCaption, nType );
	}

	inline INT MessageBox( LPCTSTR lpTextID, INT iTextID, LPCTSTR lpCaptionID, INT iCaptionID, UINT nType )
	{
		return EZ_XMLWnd::MessageBox( this->m_pXMLObj, this, lpTextID, iTextID, lpCaptionID, iCaptionID, nType );
	}

	inline INT MessageBox( LPCTSTR lpTextID, LPCTSTR lpDefaultText, LPCTSTR lpCaptionID, LPCTSTR lpDefaultCaption, UINT nType )
	{
		return EZ_XMLWnd::MessageBox( lpTextID, lpDefaultText, lpCaptionID, lpDefaultCaption, nType );
	}

	inline CString LoadText( LPCTSTR lpString, C_INT iResID = 0 )
	{
		return EZ_XMLWnd::LoadText( this->m_pXMLObj, lpString, iResID );
	}

	inline CString LoadText( LPCTSTR lpString, LPCTSTR lpDefaultText )
	{
		return EZ_XMLWnd::LoadText( this->m_pXMLObj, lpString, lpDefaultText );
	}

	//  ==========================================================================
	//  Static Function
	//  ==========================================================================
public:
	static CString LoadText( LPEZLANGUAGE lpXMLObj, LPCTSTR lpTextXMLID, C_INT   iTextResID    );
	static CString LoadText( LPEZLANGUAGE lpXMLObj, LPCTSTR lpTextXMLID, LPCTSTR lpDefaultText );

	static INT MessageBox( LPEZLANGUAGE lpXMLObj, CWnd* lpWnd, LPCTSTR lpText,                          LPCTSTR lpCaption,                             UINT nType );
	static INT MessageBox( LPEZLANGUAGE lpXMLObj, CWnd* lpWnd, LPCTSTR lpTextID, INT     iTextID,       LPCTSTR lpCaption,                             UINT nType );
	static INT MessageBox( LPEZLANGUAGE lpXMLObj, CWnd* lpWnd, LPCTSTR lpTextID, INT     iTextID,       LPCTSTR lpCaptionID, INT     iCaptionID,       UINT nType );
	static INT MessageBox( LPEZLANGUAGE lpXMLObj, CWnd* lpWnd, LPCTSTR lpTextID, LPCTSTR lpDefaultText, LPCTSTR lpCaptionID, LPCTSTR lpDefaultCaption, UINT nType );
};

typedef const EZ_XMLWnd  C_EZXMLWND;
typedef       EZ_XMLWnd* LPEZXMLWND;
typedef const EZ_XMLWnd* LPCEZXMLWND;

//  ==========================================================================
//  EZ_XMLDlg
//  ==========================================================================
class EZ_XMLDlg : public CDialog
{
public:
	DECLARE_DYNAMIC ( EZ_XMLDlg );

	DECLARE_MESSAGE_MAP()

protected:
	BOOL         m_bRTLCheck;
	LPEZLANGUAGE m_pXMLObj;

public:
	EZ_XMLDlg( C_INT iDlgID, EZ_XMLDlg* lpParentWnd,                        C_BOOL bRTLCheck = TRUE );
	EZ_XMLDlg( C_INT iDlgID, HWND       hParentWnd,  LPEZLANGUAGE lpXMLObj, C_BOOL bRTLCheck = TRUE );
	EZ_XMLDlg( C_INT iDlgID, CWnd*      lpParentWnd, LPEZLANGUAGE lpXMLObj, C_BOOL bRTLCheck = TRUE );
	virtual ~EZ_XMLDlg();

	virtual void OpenXML( LPCTSTR lpXMLFile, C_EZ_LANG_ID iLanguageID = EZ_LANG_DEFA );

	virtual void ShowHtmlHelp( LPCTSTR lpText, CSize& csSize = CSize( 200, 50 ) );
	virtual void ShowHtmlHelp( C_INT iTextResID, LPCTSTR lpTextXMLID, CSize& csSize = CSize( 200, 50 ) );

	virtual void MinMaxInt( CDataExchange* lpDX, int value, int minVal, int maxVal );

	//  ==========================================================================
	//  Window Message
	//  ==========================================================================
protected:
	afx_msg void OnDestroy();
	afx_msg INT  OnCreate( LPCREATESTRUCT lpCreateStruct );

	//  ==========================================================================
	//  Easy Function
	//  ==========================================================================
protected:
#ifdef _DEBUG
	virtual void AssertValid() const
	{
		CDialog::AssertValid();
	}

	virtual void Dump( CDumpContext& dc ) const 
	{ 
		CDialog::Dump( dc ); 
	}
#endif

	virtual void OpenXML()
	{
		;
	}

	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
public:
	inline C_BOOL IsRTLStyle() const
	{
		return ( this->m_pXMLObj ? this->m_pXMLObj->IsRTLStyle() : FALSE );
	}

	inline C_EZ_LANG_ID GetXMLID() const
	{
		return ( this->m_pXMLObj ? this->m_pXMLObj->GetCurLangID() : EZ_LANG_DEFA );
	}

	inline LPCEZLANGUAGE GetXMLObjPtr() const
	{
		return this->m_pXMLObj;
	}

	inline void Localize( CDataExchange* lpDX, LPEZSUBCLASSWNDINFO lpSubclassWndAry, C_INT iCount )
	{
		EZ_XMLDlg::Localize( this->m_pXMLObj, this, lpDX, this->m_bRTLCheck, ( LPBYTE )lpSubclassWndAry, iCount, EZSUBCLASSWNDINFOSIZE );
	}

	inline void Localize( CDataExchange* lpDX, LPEZSUBCLASSWNDLINEINFO lpSubclassWndLineAry, C_INT iCount )
	{
		EZ_XMLDlg::Localize( this->m_pXMLObj, this, lpDX, this->m_bRTLCheck, lpSubclassWndLineAry, iCount );
	}

	inline void Localize( CMenu* lpMenu, C_INT iSize, LPEZMODIFYMENUINFO lpModifyMenuInfo )
	{
		EZ_XMLDlg::Localize( this->m_pXMLObj, lpMenu, iSize, lpModifyMenuInfo );
	}

	inline void Localize( CMenu* lpMenu, C_INT iSize, LPEZMODIFYMENUFTINFO lpModifyMenuFmtInfo )
	{
		EZ_XMLDlg::Localize( this->m_pXMLObj, lpMenu, iSize, lpModifyMenuFmtInfo );
	}

	inline void ShowBalloonTip( CEdit& ctrlEdit, LPCTSTR lpAppName, C_INT iRangeMin, C_INT iRangeMax, CString strResFmtTxt = _T( "IDS_MIN_MAX_RANGE" ), C_INT iResFmtID = 0 )
	{
		EZ_XMLDlg::ShowBalloonTip( ctrlEdit, EZ_XMLDlg::m_pXMLObj, lpAppName, iRangeMin, iRangeMax, strResFmtTxt, iResFmtID );
	}

	inline INT MessageBox( LPCTSTR lpText, LPCTSTR lpCaption, UINT nType )
	{
		return EZ_XMLWnd::MessageBox( this->m_pXMLObj, this, lpText, lpCaption, nType );
	}

	inline INT MessageBox( LPCTSTR lpTextID, INT iTextID, LPCTSTR lpCaption, UINT nType )
	{
		return EZ_XMLWnd::MessageBox( this->m_pXMLObj, this, lpTextID, iTextID, lpCaption, nType );
	}

	inline INT MessageBox( LPCTSTR lpTextID, INT iTextID, LPCTSTR lpCaptionID, INT iCaptionID, UINT nType )
	{
		return EZ_XMLWnd::MessageBox( this->m_pXMLObj, this, lpTextID, iTextID, lpCaptionID, iCaptionID, nType );
	}

	inline INT MessageBox( LPCTSTR lpTextID, LPCTSTR lpDefaultText, LPCTSTR lpCaptionID, LPCTSTR lpDefaultCaption, UINT nType )
	{
		return EZ_XMLWnd::MessageBox( this->m_pXMLObj, this, lpTextID, lpDefaultText, lpCaptionID, lpDefaultCaption, nType );
	}

	inline void ShowRangeMessage( LPCTSTR lpAppName, C_INT iRangeMin, C_INT iRangeMax, CString strResFmtTxt = _T( "IDS_MIN_MAX_RANGE" ), C_INT iResFmtID = 0 )
	{
		EZ_XMLDlg::ShowRangeMessage( this->GetSafeHwnd(), EZ_XMLDlg::m_pXMLObj, lpAppName, iRangeMin, iRangeMax, strResFmtTxt, iResFmtID );
	}

	inline CString LoadText( LPCTSTR lpString, C_INT iResID = 0 )
	{
		return EZ_XMLWnd::LoadText( this->m_pXMLObj, lpString, iResID );
	}

	inline CString LoadText( LPCTSTR lpString, LPCTSTR lpDefaultText )
	{
		return EZ_XMLWnd::LoadText( this->m_pXMLObj, lpString, lpDefaultText );
	}

	//  ==========================================================================
	//  Static Function
	//  ==========================================================================
public:
	static void PeekMessage( HWND hWnd, C_INT iMsgID, C_BOOL bRemoved );

	static BOOL Localize( LPEZLANGUAGE lpXMLObj, CDialog* lpDlg, CDataExchange* lpDX, C_BOOL bRTLCheck, LPBYTE                  lpLocalizeAry,        C_INT iCount, C_INT iSize );
	static BOOL Localize( LPEZLANGUAGE lpXMLObj, CDialog* lpDlg, CDataExchange* lpDX, C_BOOL bRTLCheck, LPEZSUBCLASSWNDLINEINFO lpSubclassWndLineAry, C_INT iCount );

	static void Localize( LPEZLANGUAGE lpXMLObj, CMenu* lpMenu, C_INT iSize, LPEZMODIFYMENUINFO   lpModifyMenuInfo    );
	static void Localize( LPEZLANGUAGE lpXMLObj, CMenu* lpMenu, C_INT iSize, LPEZMODIFYMENUFTINFO lpModifyMenuFmtInfo );

	static void ShowBalloonTip( CEdit& ctrlEdit,                        LPCTSTR lpAppName,                                   LPCTSTR lpText                                                        );
	static void ShowBalloonTip( CEdit& ctrlEdit, LPEZLANGUAGE lpXMLObj, LPCTSTR lpAppName, C_INT iRangeMin, C_INT iRangeMax, CString strResFmtTxt = _T( "IDS_MIN_MAX_RANGE" ), C_INT iResFmtID = 0 );

	static void ShowRangeMessage( HWND hMsgWnd, LPEZLANGUAGE lpXMLObj, LPCTSTR lpAppName, C_INT iRangeMin, C_INT iRangeMax, CString strResFmtTxt = _T( "IDS_MIN_MAX_RANGE" ), C_INT iResFmtID = 0 );
};

typedef const EZ_XMLDlg  C_EZXMLDLG;
typedef       EZ_XMLDlg* LPEZXMLDLG;
typedef const EZ_XMLDlg* LPCEZXMLDLG;

//  ==========================================================================
//  EZ_LanguageDlg
//  ==========================================================================
class EZ_LanguageDlg : public EZ_XMLDlg
{
protected:
	CLanguage m_xmlLanguage;

public:
	EZ_LanguageDlg( C_INT iDlgID, HWND hParentWnd = NULL, C_BOOL bRTLCheck = TRUE )
		: EZ_XMLDlg( iDlgID, hParentWnd, &m_xmlLanguage, bRTLCheck ), m_xmlLanguage()
	{
		;
	}

	EZ_LanguageDlg( C_INT iDlgID, CWnd* lpParentWnd = NULL, C_BOOL bRTLCheck = TRUE )
		: EZ_XMLDlg( iDlgID, lpParentWnd, &m_xmlLanguage, bRTLCheck ), m_xmlLanguage()
	{
		;
	}

	virtual ~EZ_LanguageDlg()
	{
		this->CloseXML();
	}

	afx_msg void OnDestroy()
	{
		this->CloseXML();

		EZ_XMLDlg::OnDestroy();
	}

	virtual void OpenXML( LPCTSTR lpXMLFile, C_EZ_LANG_ID iLanguageID = EZ_LANG_DEFA )
	{
		//  Open XML ?
		this->CloseXML();

		{
			CDC* lpDC = ( EZ_XMLDlg::GetSafeHwnd() ? EZ_XMLDlg::GetDC() : NULL );

			if ( !this->m_xmlLanguage.Open( lpXMLFile, ( EZ_LANG_ID )iLanguageID, lpDC ) )
				::EZOutputDebugString( _T( "\n" ) );

			if ( lpDC ) { EZ_XMLDlg::ReleaseDC( lpDC ); lpDC = NULL; }
		}

		//  RTL Style ?
		if ( EZ_XMLDlg::m_bRTLCheck && EZ_XMLDlg::GetSafeHwnd() )
		{
#if ( defined( RES_ARB ) || defined( RES_HEB ) || defined( RES_PRS ) )
			EZ_XMLDlg::ModifyStyleEx( 0, ( WS_EX_LAYOUTRTL | WS_EX_RTLREADING ), 0 );
#else
			if ( this->m_xmlLanguage.IsRTLStyle() )
				EZ_XMLDlg::ModifyStyleEx( 0, ( WS_EX_LAYOUTRTL | WS_EX_RTLREADING ), 0 );
#endif
		}
	}

	virtual void CloseXML()
	{
		this->m_xmlLanguage.Close();
	}
};

typedef const EZ_LanguageDlg  C_EZLANGUAGEDLG;
typedef       EZ_LanguageDlg* LPEZLANGUAGEDLG;
typedef const EZ_LanguageDlg* LPCEZLANGUAGEDLG;
