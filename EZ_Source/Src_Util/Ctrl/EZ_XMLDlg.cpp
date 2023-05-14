#include "stdafx.h"
#include "EZ_XMLDlg.h"

//  ==========================================================================
//  
//  ==========================================================================
IMPLEMENT_DYNAMIC( EZ_XMLWnd, CWnd );

BEGIN_MESSAGE_MAP( EZ_XMLWnd, CWnd )
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

//  ==========================================================================
//  
//  ==========================================================================
EZ_XMLWnd::EZ_XMLWnd( LPEZLANGUAGE lpXMLObj, C_BOOL bRTLCheck ) : CWnd(), m_bRTLCheck( bRTLCheck ), m_pXMLObj( lpXMLObj )
{
	;
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_XMLWnd::~EZ_XMLWnd()
{
	//  this->m_bRTLCheck
	//  this->m_pXMLObj
}

//  ==========================================================================
//  Create ( Window Function )
//  ==========================================================================
BOOL EZ_XMLWnd::Create( CWnd* lpParentWnd, UINT nID, RECT& rcClient, LPCTSTR lpCaption, C_INT iStyle )
{
	LPCTSTR lpClassName = ::AfxRegisterWndClass( CS_DBLCLKS, ::LoadCursor( NULL, IDC_ARROW ), NULL, NULL );

	return ( lpParentWnd ? CWnd::Create( lpClassName, lpCaption, iStyle, rcClient, lpParentWnd, nID ) : FALSE );
}

//  ==========================================================================
//  OnCreate ( Window Message )
//  ==========================================================================
INT EZ_XMLWnd::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	C_INT iResult = CWnd::OnCreate( lpCreateStruct );

	if ( iResult >= 0 )
	{
		//  Open XML
		;

		//  RTL Style ?
		if ( this->m_bRTLCheck )
		{
#if ( defined( RES_ARB ) || defined( RES_HEB ) || defined( RES_PRS ) )
			this->ModifyStyleEx( 0, ( WS_EX_LAYOUTRTL | WS_EX_RTLREADING ), 0 );
#else
			if ( this->m_pXMLObj && this->m_pXMLObj->IsRTLStyle() )
				this->ModifyStyleEx( 0, ( WS_EX_LAYOUTRTL | WS_EX_RTLREADING ), 0 );
#endif
		}
	}

	return iResult;
}

//  ==========================================================================
//  OnDestroy ( Window Message )
//  ==========================================================================
void EZ_XMLWnd::OnDestroy()
{
	{
		;
	}

	CWnd::OnDestroy();
}

//  ==========================================================================
//  LoadText ( Static )
//  ==========================================================================
CString EZ_XMLWnd::LoadText( LPEZLANGUAGE lpXMLObj, LPCTSTR lpTextXMLID, C_INT iTextResID )
{
	CString strReturn = _T( "" );

	if ( lpXMLObj && lpXMLObj->HasOpen() )
		strReturn = lpXMLObj->LoadString( lpTextXMLID, iTextResID );
	else if ( iTextResID > 0 )
		strReturn.LoadString( iTextResID );

	return strReturn;
}

CString EZ_XMLWnd::LoadText( LPEZLANGUAGE lpXMLObj, LPCTSTR lpTextXMLID, LPCTSTR lpDefaultText )
{
	CString strReturn = _T( "" );

	{
		if ( lpXMLObj && lpXMLObj->HasOpen() ) 
			strReturn = lpXMLObj->LoadString( lpTextXMLID, 0 );

		if ( strReturn.IsEmpty() && lpDefaultText )
			strReturn.Format( _T( "%s" ), lpDefaultText );
	}

	return strReturn;
}

//  ==========================================================================
//  MessageBox ( Static )
//  ==========================================================================
INT EZ_XMLWnd::MessageBox( LPEZLANGUAGE lpXMLObj, CWnd* lpWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT nType )
{
#if ( defined( RES_ARB ) || defined( RES_HEB ) || defined( RES_PRS ) )
	nType |= MB_RTLREADING;
#else
	if ( lpXMLObj && lpXMLObj->IsRTLStyle() )
		nType |= MB_RTLREADING;
#endif

	return ( lpWnd ? lpWnd->MessageBox( lpText, lpCaption, nType ) : ::AfxMessageBox( lpText, nType ) );
}

INT EZ_XMLWnd::MessageBox( LPEZLANGUAGE lpXMLObj, CWnd* lpWnd, LPCTSTR lpTextID, INT iTextID, LPCTSTR lpCaption, UINT nType )
{
	CString strText = _T( "" );

	if ( lpXMLObj && lpXMLObj->HasOpen() )
		strText = lpXMLObj->LoadString( lpTextID, iTextID );
	else if ( iTextID > 0 )
		strText.LoadString( iTextID );

	return EZ_XMLWnd::MessageBox( lpXMLObj, lpWnd, strText, lpCaption, nType );
}

INT EZ_XMLWnd::MessageBox( LPEZLANGUAGE lpXMLObj, CWnd* lpWnd, LPCTSTR lpTextID, INT iTextID, LPCTSTR lpCaptionID, INT iCaptionID, UINT nType )
{
	CString strCaption = _T( "" ), strText = _T( "" );

	if ( lpXMLObj && lpXMLObj->HasOpen() )
	{
		strCaption = lpXMLObj->LoadString( lpCaptionID, iCaptionID );
		strText    = lpXMLObj->LoadString( lpTextID,    iTextID    );
	}
	else
	{
		if ( iCaptionID > 0 )
			strCaption.LoadString( iCaptionID );

		if ( iTextID > 0 )
			strText.LoadString( iTextID );
	}

	return EZ_XMLWnd::MessageBox( lpXMLObj, lpWnd, strText, strCaption, nType );
}

INT EZ_XMLWnd::MessageBox( LPEZLANGUAGE lpXMLObj, CWnd* lpWnd, LPCTSTR lpTextID, LPCTSTR lpDefaultText, LPCTSTR lpCaptionID, LPCTSTR lpDefaultCaption, UINT nType )
{
	CString strCaption = _T( "" ), strText = _T( "" );

	{
		if ( lpXMLObj && lpXMLObj->HasOpen() )
		{
			strCaption = lpXMLObj->LoadString( lpCaptionID, 0 );
			strText    = lpXMLObj->LoadString( lpTextID,    0 );
		}

		if ( strCaption.IsEmpty() && lpDefaultCaption )
			strCaption.Format( _T( "%s" ), lpDefaultCaption );

		if ( strText.IsEmpty() && lpDefaultText )
			strText.Format( _T( "%s" ), lpDefaultText );
	}

	return EZ_XMLWnd::MessageBox( lpXMLObj, lpWnd, strText, strCaption, nType );
}

//  ==========================================================================
//  
//  ==========================================================================
IMPLEMENT_DYNAMIC( EZ_XMLDlg, CDialog );

BEGIN_MESSAGE_MAP( EZ_XMLDlg, CDialog )
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

//  ==========================================================================
//  
//  ==========================================================================
EZ_XMLDlg::EZ_XMLDlg( C_INT iDlgID, EZ_XMLDlg* lpParentWnd, C_BOOL bRTLCheck )
		 : CDialog( iDlgID, lpParentWnd ), m_bRTLCheck( bRTLCheck ), m_pXMLObj( ( lpParentWnd ? lpParentWnd->m_pXMLObj : NULL ) )
{
	;
}

EZ_XMLDlg::EZ_XMLDlg( C_INT iDlgID, HWND hParentWnd, LPEZLANGUAGE lpXMLObj, C_BOOL bRTLCheck )
		 : CDialog( iDlgID, ( hParentWnd ? CWnd::FromHandle( hParentWnd ) : NULL ) ), m_bRTLCheck( bRTLCheck ), m_pXMLObj( lpXMLObj )
{
	;
}

EZ_XMLDlg::EZ_XMLDlg( C_INT iDlgID, CWnd* lpParentWnd, LPEZLANGUAGE lpXMLObj, C_BOOL bRTLCheck )
		 : CDialog( iDlgID, lpParentWnd ), m_bRTLCheck( bRTLCheck ), m_pXMLObj( lpXMLObj )
{
	;
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_XMLDlg::~EZ_XMLDlg()
{
	//  this->m_bRTLCheck
	//  this->m_pXMLObj
}

//  ==========================================================================
//  PeekMessage ( Window Function )
//  ==========================================================================
void EZ_XMLDlg::PeekMessage( HWND hWnd, C_INT iMsgID, C_BOOL bRemoved )
{
	//  Error !
	if ( !hWnd )
	{
		;
		return;
	}

	//  
	C_INT iFlag = ( bRemoved ? PM_REMOVE : PM_NOREMOVE );

	for ( MSG msg; ; )
	{
		if ( !::IsWindow( hWnd ) )
		{
			;
			break;
		}

		if ( !::PeekMessage( &msg, hWnd, iMsgID, iMsgID, iFlag ) )
		{
			;
			break;
		}
	}
}

//  ==========================================================================
//  MinMaxInt ( Window Function )
//  ==========================================================================
void EZ_XMLDlg::MinMaxInt( CDataExchange* lpDX, int iValue, int iMinVal, int iMaxVal )
{
	//  Instend of XML String
	BOOL bString = FALSE;

	if ( this->m_pXMLObj && this->m_pXMLObj->HasOpen() )
	{
		ASSERT ( iMinVal <= iMaxVal );

		if ( ( iValue < iMinVal ) || ( iValue > iMaxVal ) )
		{
			CString strFormat = this->m_pXMLObj->LoadString( _T( "IDS_INTEGER_RANGE" ), 0 );

			if ( !strFormat.IsEmpty() )
			{
				CString strText = _T( "" );

				strText.Format( strFormat, iMinVal, iMaxVal );

				bString = ( ::AfxMessageBox( strText, MB_OK ) == IDOK );
			}
		}
	}

	//  
	if ( bString )
		lpDX->Fail();
	else
		DDV_MinMaxInt( lpDX, iValue, iMinVal, iMaxVal );
}

//  ==========================================================================
//  OnCreate ( Window Message )
//  ==========================================================================
INT EZ_XMLDlg::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	C_INT iResult = CDialog::OnCreate( lpCreateStruct );

	if ( iResult >= 0 )
	{
		//  Open XML
		this->OpenXML();

		//  RTL Style ?
		if ( this->m_bRTLCheck )
		{
#if ( defined( RES_ARB ) || defined( RES_HEB ) || defined( RES_PRS ) )
			this->ModifyStyleEx( 0, ( WS_EX_LAYOUTRTL | WS_EX_RTLREADING ), 0 );
#else
			if ( this->m_pXMLObj && this->m_pXMLObj->IsRTLStyle() )
				this->ModifyStyleEx( 0, ( WS_EX_LAYOUTRTL | WS_EX_RTLREADING ), 0 );
#endif
		}
	}

	return iResult;
}

//  ==========================================================================
//  OnDestroy ( Window Message )
//  ==========================================================================
void EZ_XMLDlg::OnDestroy()
{
	{
		;
	}

	CDialog::OnDestroy();
}

//  ==========================================================================
//  OpenXML
//  ==========================================================================
void EZ_XMLDlg::OpenXML( LPCTSTR lpXMLFile, C_EZ_LANG_ID iLanguageID )
{
	//  Error !
	if ( !lpXMLFile )
	{
		::EZOutputDebugString( _T( "\n" ) );
		return;
	}
	else if ( !this->m_pXMLObj )
	{
		::EZOutputDebugString( _T( "\n" ) );
		return;
	}

	//  Open XML ?
	this->m_pXMLObj->Close();

	{
		CDC* lpDC = ( CDialog::GetSafeHwnd() ? CDialog::GetDC() : NULL );

		if ( !this->m_pXMLObj->Open( lpXMLFile, iLanguageID, lpDC ) )
			::EZOutputDebugString( _T( "\n" ) );

		if ( lpDC ) { CDialog::ReleaseDC( lpDC ); lpDC = NULL; }
	}

	//  RTL Style ?
	if ( this->m_bRTLCheck && this->GetSafeHwnd() )
	{
#if ( defined( RES_ARB ) || defined( RES_HEB ) || defined( RES_PRS ) )
		this->ModifyStyleEx( 0, ( WS_EX_LAYOUTRTL | WS_EX_RTLREADING ), 0 );
#else
		if ( this->m_pXMLObj->IsRTLStyle() )
			this->ModifyStyleEx( 0, ( WS_EX_LAYOUTRTL | WS_EX_RTLREADING ), 0 );
#endif
	}
}

//  ==========================================================================
//  ShowHtmlHelp
//  ==========================================================================
void EZ_XMLDlg::ShowHtmlHelp( LPCTSTR lpText, CSize& csSize )
{
	//
	CPoint cpMouse( 0, 0 );

	::GetCursorPos( &cpMouse );

	::ScreenToClient( this->GetSafeHwnd(), &cpMouse );

	//
	CExplainStc ceHelp( this );

	if ( ceHelp.Create( _T( "Explain" ), WS_CHILD, CRect( cpMouse.x, cpMouse.y, csSize.cx, csSize.cy ), this ) )
	{
		if ( ceHelp.SetExplain( lpText, this->m_pXMLObj->GetFont() ) )
		{
			if ( this->m_pXMLObj->IsRTLStyle() )
				ceHelp.ShowExplain( TRUE, ::GetDesktopWindow() );
			else
			{
#if ( defined( RES_HEB ) || defined( RES_ARB ) || defined( RES_PRS ) )
				ceHelp.ShowExplain( TRUE, ::GetDesktopWindow() );
#else
				ceHelp.ShowExplain( FALSE );
#endif
			}
		}
	}
}

void EZ_XMLDlg::ShowHtmlHelp( C_INT iTextResID, LPCTSTR lpTextXMLID, CSize& csSize )
{
	CString strText = _T( "" );
	
	if ( this->m_pXMLObj && this->m_pXMLObj->HasOpen() )
		strText = this->m_pXMLObj->LoadString( lpTextXMLID, iTextResID );
	else if ( iTextResID > 0 )
		strText.LoadString( iTextResID );

	this->ShowHtmlHelp( strText, csSize );
}

//  ==========================================================================
//  Localize Ctrl ( Static )
//  ==========================================================================
BOOL EZ_XMLDlg::Localize( LPEZLANGUAGE lpXMLObj, CDialog* lpDlg, CDataExchange* lpDX, C_BOOL bRTLCheck, LPBYTE lpLocalizeAry, C_INT iCount, C_INT iSize )
{
	//  Error !
	if ( !lpDlg || !lpLocalizeAry || ( iCount <= 0 ) )
	{
		;
		return FALSE;
	}

	//  Subclass and Set Text
	C_INT               iFlagEx       = ( WS_EX_LAYOUTRTL | WS_EX_RTLREADING );
	CFont*              lpFont        = NULL;
	LPEZSUBCLASSWNDINFO lpSWndInfoAry = NULL;
	CString             strXMLNote    = _T( "" );
	CString             strText       = _T( "" );

	for ( INT i = 0; i < iCount; i++, lpLocalizeAry += iSize )
	{
		//  Get Window
		lpSWndInfoAry = ( LPEZSUBCLASSWNDINFO )lpLocalizeAry;

		if ( lpSWndInfoAry->m_iResID == 0 )
			lpSWndInfoAry->m_pWnd = lpDlg;
		else if ( lpSWndInfoAry->m_pWnd )
		{
			if ( !lpDX )
			{
				;
				continue;
			}
			else if ( !lpSWndInfoAry->m_pWnd->GetSafeHwnd() )
			{
				DDX_Control( lpDX, lpSWndInfoAry->m_iResID, *lpSWndInfoAry->m_pWnd );

				if ( !lpSWndInfoAry->m_pWnd->GetSafeHwnd() )
				{
					;
					continue;
				}
			}

			if ( lpSWndInfoAry->m_iCmdShow != EZ_SubclassWndInfo::CMD_DEFAULT )
				lpSWndInfoAry->m_pWnd->ShowWindow( lpSWndInfoAry->m_iCmdShow );
		}
		else
		{
			lpSWndInfoAry->m_pWnd = lpDlg->GetDlgItem( lpSWndInfoAry->m_iResID );

			if ( !lpSWndInfoAry->m_pWnd || !lpSWndInfoAry->m_pWnd->GetSafeHwnd() )
			{
				;
				continue;
			}

			if ( lpSWndInfoAry->m_iCmdShow != EZ_SubclassWndInfo::CMD_DEFAULT )
				lpSWndInfoAry->m_pWnd->ShowWindow( lpSWndInfoAry->m_iCmdShow );
		}

		//  
		if ( lpXMLObj )
		{
			//  Is RTL Style ?
			if ( bRTLCheck && lpXMLObj->IsRTLStyle() )
				lpSWndInfoAry->m_pWnd->ModifyStyleEx( 0, iFlagEx, 0 );

			//  Set Font
			lpFont = lpXMLObj->GetFont();

			if ( lpFont ) lpSWndInfoAry->m_pWnd->SetFont( lpFont );

			//  Set Text
			if ( ::_tcslen( lpSWndInfoAry->m_tzXMLNote ) > 0 )
			{
				strXMLNote.Format( _T( "%s" ), lpSWndInfoAry->m_tzXMLNote );

				strText = lpXMLObj->LoadString( strXMLNote, lpSWndInfoAry->m_iTableID );

				if ( !strText.IsEmpty() ) lpSWndInfoAry->m_pWnd->SetWindowText( strText );
			}
		}
	}

	return TRUE;
}

BOOL EZ_XMLDlg::Localize( LPEZLANGUAGE lpXMLObj, CDialog* lpDlg, CDataExchange* lpDX, C_BOOL bRTLCheck, LPEZSUBCLASSWNDLINEINFO lpSubclassWndLineAry, C_INT iCount )
{
	//  Error !
	if ( !EZ_XMLDlg::Localize( lpXMLObj, lpDlg, lpDX, bRTLCheck, ( LPBYTE )lpSubclassWndLineAry, iCount, EZSUBCLASSWNDLINEINFOSIZE ) )
	{
		;
		return FALSE;
	}

	//  Resized
	C_INT   iMoveFlag    = ( SWP_NOZORDER | SWP_NOSIZE );
	C_INT   iResizedFlag = ( SWP_NOZORDER | SWP_NOMOVE );
	CFont*  lpWndFont    = NULL;
	CFont*  lpDCFont     = NULL;
	CDC*    lpWndDC      = NULL;
	CWnd*   lpPartnerWnd = NULL;
	CString strText      = _T( "" );

	CSize csTextLen( 0, 0 );
	CRect crWnd( 0, 0, 0, 0 );
	CRect crPrevWnd( 0, 0, 0, 0 );
	CRect crPartnerWnd( 0, 0, 0, 0 );

	for ( INT i = 0, iCtrlLen; i < iCount; i++, crPrevWnd = crWnd )
	{
		//  
		if ( !lpSubclassWndLineAry[ i ].m_pWnd )
		{
			;
			continue;
		}

		//  
		crWnd.SetRectEmpty();

		lpSubclassWndLineAry[ i ].m_pWnd->GetWindowRect( &crWnd );

		lpDlg->ScreenToClient( &crWnd );

		//  
		lpWndDC = lpSubclassWndLineAry[ i ].m_pWnd->GetDC();

		if ( lpWndDC )
		{
			//  
			lpWndFont = lpSubclassWndLineAry[ i ].m_pWnd->GetFont();
			lpDCFont  = ( lpWndFont ? lpWndDC->SelectObject( lpWndFont ) : NULL );

			switch ( lpSubclassWndLineAry[ i ].m_iType )
			{
			case EZ_SubclassWndLineInfo::TYPE_STATIC:
			case EZ_SubclassWndLineInfo::TYPE_BUTTON:
				{
					lpSubclassWndLineAry[ i ].m_pWnd->GetWindowText( strText );

					csTextLen = lpWndDC->GetTextExtent( strText );

					lpSubclassWndLineAry[ i ].m_pWnd->SetWindowPos( NULL, 0, 0, ( csTextLen.cx + 4 ), crWnd.Height(), iResizedFlag );
				}
				break;

			case EZ_SubclassWndLineInfo::TYPE_CHECK:
				{
					lpSubclassWndLineAry[ i ].m_pWnd->GetWindowText( strText );

					csTextLen = lpWndDC->GetTextExtent( strText );
					iCtrlLen  = max ( ::GetSystemMetrics( SM_CXSMICON ), 24 );

					lpSubclassWndLineAry[ i ].m_pWnd->SetWindowPos( NULL, 0, 0, ( csTextLen.cx + iCtrlLen + 4 ), crWnd.Height(), iResizedFlag );
				}
				break;

			case EZ_SubclassWndLineInfo::TYPE_SPIN:
			case EZ_SubclassWndLineInfo::TYPE_EDIT:
			case EZ_SubclassWndLineInfo::TYPE_COMBO:
			case EZ_SubclassWndLineInfo::TYPE_DTPIKER:
			default:
				{
					//  Nothing
				}
				break;
			}

			//  Restore
			if ( lpDCFont ) lpWndDC->SelectObject( lpDCFont );

			lpSubclassWndLineAry[ i ].m_pWnd->ReleaseDC( lpWndDC );

			//  Get Real Width and Height
			lpSubclassWndLineAry[ i ].m_pWnd->GetWindowRect( &crWnd );

			lpDlg->ScreenToClient( &crWnd );
		}

		//  Set Position
		if ( !crPrevWnd.IsRectEmpty() )
		{
			//
			if ( ( lpSubclassWndLineAry[ i ].m_iType != EZ_SubclassWndLineInfo::TYPE_SPIN ) && ( lpSubclassWndLineAry[ i ].m_iType != EZ_SubclassWndLineInfo::TYPE_DTPIKER ) )
			{
				crPrevWnd.right += 6;

				if ( lpSubclassWndLineAry[ i ].m_iPartnerID != 0 )
				{
					lpPartnerWnd = lpDlg->GetDlgItem( lpSubclassWndLineAry[ i ].m_iPartnerID );

					if ( lpPartnerWnd )
					{
						lpPartnerWnd->GetWindowRect( &crPartnerWnd );

						lpDlg->ScreenToClient( &crPartnerWnd );

						if ( crPartnerWnd.left > crPrevWnd.right )
							crPrevWnd.right = crPartnerWnd.left;
					}
				}
			}

			lpSubclassWndLineAry[ i ].m_pWnd->SetWindowPos( NULL, crPrevWnd.right, crWnd.top, 0, 0, iMoveFlag );

			//  Get Real Pos X and Y
			lpSubclassWndLineAry[ i ].m_pWnd->GetWindowRect( &crWnd );

			lpDlg->ScreenToClient( &crWnd );
		}
	}

	return TRUE;
}

//  ==========================================================================
//  Localize Menu ( Static )
//  ==========================================================================
void EZ_XMLDlg::Localize( LPEZLANGUAGE lpXMLObj, CMenu* lpMenu, C_INT iSize, LPEZMODIFYMENUINFO lpData )
{
	if ( lpXMLObj && lpMenu && ( iSize > 0 ) && lpData )
	{
		C_INT   iFlagEx[ 4 ] = { MF_CHECKED, MF_UNCHECKED, MF_ENABLED, MF_GRAYED };
		CMenu*  lpSubMenu    = NULL;
		CString strText      = _T( "" );
		
		for ( INT i = 0, j, iState; i < iSize; i++ )
		{
			strText = lpXMLObj->LoadString( lpData[ i ].m_strXMLNote, lpData[ i ].m_iTableID );

			if ( !strText.IsEmpty() )
			{
				//  Check Item Has MF_CHECKED / MF_UNCHECKED / MF_ENABLED / MF_GRAYED Flags
				for ( iState = lpMenu->GetMenuState( lpData[ i ].m_iResID, lpData[ i ].m_iModifyFlag ), j = 0; j < 4; j++ )
				{
					if ( ( iState & iFlagEx[ j ] ) > 0 )
						lpData[ i ].m_iModifyFlag |= iFlagEx[ j ];
				}

				//  Set Item Text
				lpData[ i ].m_iModifyFlag |= MF_STRING;

				if ( ( lpData[ i ].m_iModifyFlag & MF_POPUP ) == 0 )
					lpMenu->ModifyMenu( lpData[ i ].m_iResID, lpData[ i ].m_iModifyFlag, lpData[ i ].m_iResID, strText );
				else
				{
					lpSubMenu = lpMenu->GetSubMenu( ( ( ( lpData[ i ].m_iModifyFlag & MF_BYPOSITION ) == 0 ) ? i : lpData[ i ].m_iResID ) );

					if ( lpSubMenu )
						lpMenu->ModifyMenu( lpData[ i ].m_iResID, lpData[ i ].m_iModifyFlag, ( UINT_PTR )lpSubMenu->GetSafeHmenu(), strText );
					else
					{
						ASSERT ( 0 );
					}
				}
			}
		}
	}
}

void EZ_XMLDlg::Localize( LPEZLANGUAGE lpXMLObj, CMenu* lpMenu, C_INT iSize, LPEZMODIFYMENUFTINFO lpData )
{
	if ( lpXMLObj && lpMenu && ( iSize > 0 ) && lpData )
	{
		C_INT   iFlagEx[ 4 ] = { MF_CHECKED, MF_UNCHECKED, MF_ENABLED, MF_GRAYED };
		CMenu*  lpSubMenu    = NULL;
		CString strText      = _T( "" );
		CString strFormat    = _T( "" );
		
		for ( INT i = 0, j, iState; i < iSize; i++ )
		{
			strFormat = lpXMLObj->LoadString( lpData[ i ].m_strXMLNote, lpData[ i ].m_iTableID );

			if ( !strFormat.IsEmpty() )
			{
				//  Check Item Has MF_CHECKED / MF_UNCHECKED / MF_ENABLED / MF_GRAYED Flags
				strText.Format( strFormat, lpData[ i ].m_strExtend );

				for ( iState = lpMenu->GetMenuState( lpData[ i ].m_iResID, lpData[ i ].m_iModifyFlag ), j = 0; j < 4; j++ )
				{
					if ( ( iState & iFlagEx[ j ] ) > 0 )
						lpData[ i ].m_iModifyFlag |= iFlagEx[ j ];
				}

				//  Set Item Text
				lpData[ i ].m_iModifyFlag |= MF_STRING;

				if ( ( lpData[ i ].m_iModifyFlag & MF_POPUP ) == 0 )
					lpMenu->ModifyMenu( lpData[ i ].m_iResID, lpData[ i ].m_iModifyFlag, lpData[ i ].m_iResID, strText );
				else
				{
					lpSubMenu = lpMenu->GetSubMenu( ( ( ( lpData[ i ].m_iModifyFlag & MF_BYPOSITION ) == 0 ) ? i : lpData[ i ].m_iResID ) );

					if ( lpSubMenu )
						lpMenu->ModifyMenu( lpData[ i ].m_iResID, lpData[ i ].m_iModifyFlag, ( UINT_PTR )lpSubMenu->GetSafeHmenu(), strText );
					else
					{
						ASSERT ( 0 );
					}
				}
			}
		}
	}
}

//  ==========================================================================
//  ShowBalloonTip ( Static )
//  ==========================================================================
void EZ_XMLDlg::ShowBalloonTip( CEdit& ctrlEdit, LPCTSTR lpAppName, LPCTSTR lpText )
{ 
#if ( defined ( UNICODE ) && defined ( _USE_BALLOONTIP_ ) )
	ctrlEdit.ShowBalloonTip( lpAppName, lpText, TTI_WARNING );
#else
	if ( lpAppName )
		::MessageBox( ctrlEdit.GetSafeHwnd(), lpText, lpAppName, MB_ICONINFORMATION );
	else
		::AfxMessageBox( lpText, MB_ICONINFORMATION );
#endif
}

void EZ_XMLDlg::ShowBalloonTip( CEdit& ctrlEdit, LPEZLANGUAGE lpXMLObj, LPCTSTR lpAppName, C_INT iRangeMin, C_INT iRangeMax, CString strResFmtTxt, C_INT iResFmtID )
{
	//  
	CString strFormat = _T( "" );

	if ( lpXMLObj && lpXMLObj->HasOpen() )
		strFormat = lpXMLObj->LoadString( strResFmtTxt, iResFmtID );
	else if ( iResFmtID > 0 )
		strFormat.LoadString( iResFmtID );

	//  
	if ( strFormat.IsEmpty() )
		strFormat = _T( "Please input between %d ~ %d" );

	//  
	CString strText = _T( "" );

	strText.Format( strFormat, iRangeMin, iRangeMax );

	EZ_XMLDlg::ShowBalloonTip( ctrlEdit, lpAppName, strText );
}

//  ==========================================================================
//  ShowRangeMessage ( Static )
//  ==========================================================================
void EZ_XMLDlg::ShowRangeMessage( HWND hMsgWnd, LPEZLANGUAGE lpXMLObj, LPCTSTR lpAppName, C_INT iRangeMin, C_INT iRangeMax, CString strResFmtTxt, C_INT iResFmtID )
{
	//  
	CString strFormat = _T( "" );
	
	if ( lpXMLObj && lpXMLObj->HasOpen() )
		strFormat = lpXMLObj->LoadString( strResFmtTxt, iResFmtID );
	else if ( iResFmtID > 0 )
		strFormat.LoadString( iResFmtID );
	
	//  
	if ( strFormat.IsEmpty() )
		strFormat = _T( "Please input between %d ~ %d" );

	//  
	CString strText = _T( "" );

	strText.Format( strFormat, iRangeMin, iRangeMax );

	::MessageBox( hMsgWnd, strText, lpAppName, MB_ICONINFORMATION );
}
