#include "stdafx.h"
#include <htmlhelp.h>
#include "explainstc.h"
#include "..\..\EZDefined.h"

//  ==========================================================================
//  
//  ==========================================================================
#pragma comment( lib, "Htmlhelp.Lib" )

//  ==========================================================================
//  
//  ==========================================================================
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//  ==========================================================================
//  
//  ==========================================================================
BEGIN_MESSAGE_MAP( CExplainStc, CStatic )
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_CAPTURECHANGED()
END_MESSAGE_MAP()

//  ==========================================================================
//  
//  ==========================================================================
CExplainStc::CExplainStc( CWnd* lpParent ) 
		   : CStatic(), m_bUseExpain( false ), m_blButtonDown( false ), m_bInRect( false ), m_bUseIcon( false ), m_TextColor( _DEF_STC_COLOR )
		   , m_hicon( NULL ), m_hCursor( NULL ), m_pParent( lpParent ), m_TextRect( 0, 0, 0, 0 ), m_Font(), m_FontNormal()
		   , m_strText( _T( "" ) ), m_FontChar( _DEF_STC_FONTCHAR ), m_strExplain( _T( "" ) ), m_strExplain2( _T( "" ) )	   
{
	;
}

//  ==========================================================================
//  
//  ==========================================================================
CExplainStc::~CExplainStc()
{
	if ( this->m_Font.GetSafeHandle() )
		this->m_Font.DeleteObject();

	if ( this->m_FontNormal.GetSafeHandle() )
		this->m_FontNormal.DeleteObject();
}

//  ==========================================================================
//  OnCreate ( Window Message )
//  ==========================================================================
int CExplainStc::OnCreate( LPCREATESTRUCT lpCreateStruct ) 
{
	if ( CStatic::OnCreate( lpCreateStruct ) == -1 )
		return -1;
	
	if ( !m_pParent )
		m_pParent = GetParent();

	return 0;
}

//  ==========================================================================
//  
//  ==========================================================================
void CExplainStc::OnMouseMove( UINT nFlags, CPoint point ) 
{
	if ( !m_bUseExpain )
	{
		CStatic::OnMouseMove( nFlags, point );
		return;
	}

	if ( m_TextRect.PtInRect( point ) )
	{
		if ( !m_bInRect )
		{   //  Mouse In
			TRACE("SetCapture\n");

			SetCapture();
			m_bInRect = true;
			InvalidateRect( NULL );
		}
	}
	else
	{	//  Mouse Out
		TRACE ( "ReleaseCapture\n" );

		ReleaseCapture();
		m_bInRect = false;

		if ( m_pParent )
		{
			CRect Rect( m_TextRect );

			ClientToScreen( &Rect );

			if ( m_bUseIcon )
				InvalidateRect( NULL );
			else
			{
				m_pParent->ScreenToClient( &Rect );
				m_pParent->InvalidateRect( Rect  );
			}
		}
		else
		{
			InvalidateRect( NULL );
		}
	}

	CStatic::OnMouseMove( nFlags, point );
}

//  ==========================================================================
//  
//  ==========================================================================
void CExplainStc::OnPaint() 
{
	if ( m_bUseIcon && m_hicon )
	{   //  device context for painting	
		CPaintDC dc( this ); 
		dc.DrawIcon( 0, 0, m_hicon );
	}
	else if ( m_bUseExpain )
	{   //  device context for painting
		CPaintDC dc( this ); 

		CFont* pOldFont;
		CString strText;
		CRect Rect;
		GetWindowText(strText);

		if(m_bInRect)
		{
			pOldFont=dc.SelectObject(&m_Font);
			dc.SetTextColor(m_TextColor);
		}
		else
		{
			pOldFont=dc.SelectObject(&m_FontNormal);
			dc.SetTextColor(_DEF_STC_COLOR_NORMAL);
		}
		if(m_strText!=strText)
		{
			m_strText=strText;
			CSize sz=dc.GetOutputTextExtent(m_strText);
			Rect.SetRect(0,0,sz.cx,sz.cy);
			if(m_TextRect!=Rect)
			{
				SetWindowPos( 0, 0, 0,sz.cx,sz.cy,SWP_NOZORDER|SWP_NOMOVE);
				m_TextRect=Rect;
			}
		}

		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(m_strText,m_TextRect,DT_LEFT);
		dc.SelectObject(pOldFont);
		TRACE("OnPaint Explain: %s\n",m_strText);
	}
	else
		CStatic::OnPaint();
}

//  ==========================================================================
//  
//  ==========================================================================
void CExplainStc::OnLButtonDown( UINT nFlags, CPoint point ) 
{
	m_blButtonDown = true;

	CStatic::OnLButtonDown( nFlags, point );
}

//  ==========================================================================
//  
//  ==========================================================================
void CExplainStc::OnLButtonUp( UINT nFlags, CPoint point ) 
{
	if ( m_blButtonDown && m_bUseExpain && m_TextRect.PtInRect( point ) )
		ShowExplain();

	m_blButtonDown = false;

	CStatic::OnLButtonUp( nFlags, point );
}

//  ==========================================================================
//  OnSetCursor
//  ==========================================================================
BOOL CExplainStc::OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message ) 
{
	if ( !this->m_bUseExpain )
		return CStatic::OnSetCursor( pWnd, nHitTest, message );
	else
	{
		if ( this->m_hCursor && ( ::GetCursor() != this->m_hCursor ) )
			::SetCursor( this->m_hCursor );

		return TRUE;
	}
}

//  ==========================================================================
//  
//  ==========================================================================
void CExplainStc::OnCaptureChanged( CWnd *pWnd ) 
{
	m_bInRect = false;

	if ( m_pParent )
	{
		CRect Rect( m_TextRect );

		ClientToScreen( &Rect );

		if ( m_bUseIcon )
			InvalidateRect( NULL );
		else
		{
			m_pParent->ScreenToClient( &Rect );
			m_pParent->InvalidateRect( Rect  );
		}
	}
	else
	{
		InvalidateRect( NULL );
	}

	CStatic::OnCaptureChanged(pWnd);
}

//  ==========================================================================
//  
//  ==========================================================================
bool CExplainStc::SetExplain(LPCTSTR lpszString,COLORREF STCColor,int nSTCSize,BYTE nSTCCharSet,LPCTSTR lpszSTCFontName)
{
//Create Font
	if(!::IsWindow(m_hWnd))
		return false;

	CDC* pDC=GetDC();
	if(!pDC)
		return false;
	CFont* pOldFont;

	int nLPSY	=	pDC->GetDeviceCaps(LOGPIXELSY);

	int nHeight = -MulDiv(nSTCSize,nLPSY, 72);
	if(m_Font.m_hObject)
		m_Font.DeleteObject();

	BOOL bRet=m_Font.CreateFont(nHeight,0,0,0,FW_NORMAL,
				0,1,0,nSTCCharSet,
				OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
				DEFAULT_PITCH,lpszSTCFontName);

	if(m_FontNormal.m_hObject)
		m_FontNormal.DeleteObject();

	bRet=m_FontNormal.CreateFont(nHeight,0,0,0,FW_NORMAL,
				0,0,0,nSTCCharSet,
				OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
				DEFAULT_PITCH,lpszSTCFontName);

	m_TextColor=STCColor;

	m_strExplain = ( lpszString ? lpszString : _T( "" ) );

	GetWindowText(m_strText);
	pOldFont=pDC->SelectObject(&m_Font);
	CSize sz=pDC->GetOutputTextExtent(m_strText);
	m_TextRect.SetRect(0,0,sz.cx,sz.cy);


	if(m_bUseIcon)
	{
		CRect rc;
		GetWindowRect(&rc);
		m_TextRect.SetRect(0,0,rc.Width(),rc.Height());
	}
	else
		SetWindowPos( 0, 0, 0,sz.cx,sz.cy,SWP_NOZORDER|SWP_NOMOVE );

	pDC->SelectObject(pOldFont);

	ReleaseDC(pDC);

	//m_hCursor = AfxGetApp()->LoadCursor(IDD_PWSET_CUR_HAND);

	m_bUseExpain=bRet?true:false;

	return m_bUseExpain;
}

//  ==========================================================================
//  
//  ==========================================================================
void CExplainStc::ShowExplain( const BOOL bRTLStyle, HWND hwndCallerWnd )
{
	// Load help text from String Table
	if(m_strExplain.IsEmpty())
		return;
	CRect rect;
	GetWindowRect(rect);
	POINT pt;
	pt.x=rect.right;
	pt.y=rect.bottom;

	if(m_bUseIcon)
		pt.y=rect.bottom+10;

	HH_POPUP hPop; // HTML Help popup structure

	// Initialize structure to NULLs	
	memset(&hPop, 0, sizeof(hPop)); 

	// Set size of structure
	hPop.cbStruct         = sizeof(hPop);
	//hPop.hinst            = ::AfxGetApp()->m_hInstance;
	hPop.clrBackground    = CExplainStc::DEFAULT_BACKGROUND_COLOR;// Yellow background color
	hPop.clrForeground    = -1; // Font color	
	hPop.rcMargins.left   = 5;			 
	hPop.rcMargins.bottom = 10;
	hPop.rcMargins.right  = 10;
	hPop.rcMargins.top	  = 5;

	pt.x+=hPop.rcMargins.left;
	pt.y+=hPop.rcMargins.top;
	hPop.pt               = pt;	
	hPop.pszText          = m_strExplain; // Message from String Table
	hPop.pszFont          = this->m_FontChar; // Font

	TRACE( "Show Explain: %s\n", m_strExplain );

#if _MSC_VER > 1300
	HWND hWnd = ::HtmlHelp( hwndCallerWnd, NULL, HH_DISPLAY_TEXT_POPUP, ( DWORD_PTR )&hPop );
#else
	HWND hWnd = ::HtmlHelp( hwndCallerWnd, NULL, HH_DISPLAY_TEXT_POPUP, ( DWORD     )&hPop );
#endif

	if ( hWnd )
	{
		// 
		if ( bRTLStyle )
		{
#if _MSC_VER > 1300
			LONG_PTR lExStyle = ( ::GetWindowLongPtr( hWnd, GWL_EXSTYLE ) | WS_EX_RTLREADING | WS_EX_LAYOUTRTL );

			::SetWindowLongPtr( hWnd, GWL_EXSTYLE, lExStyle );
#else
			LONG_PTR lExStyle = ( ::GetWindowLong( hWnd, GWL_EXSTYLE ) | WS_EX_RTLREADING | WS_EX_LAYOUTRTL );

			::SetWindowLong( hWnd, GWL_EXSTYLE, lExStyle );
#endif
		}

		//  
		::SetWindowPos( hWnd, HWND_TOPMOST, pt.x, pt.y, 0, 0, SWP_NOSIZE );
		::ShowWindow( hWnd, SW_HIDE );
		::ShowWindow( hWnd, SW_SHOW );
	}

	if ( !m_strExplain2.IsEmpty() )
	{
		AfxGetApp()->BeginWaitCursor();

		Sleep(4000);	
		hPop.cbStruct         = sizeof(hPop);	
		hPop.clrBackground    = CExplainStc::DEFAULT_BACKGROUND_COLOR;// Yellow background color
		hPop.clrForeground    = -1; // Font color	
		hPop.rcMargins.left   = 5;			 
		hPop.rcMargins.bottom = 10;
		hPop.rcMargins.right  = 10;
		hPop.rcMargins.top	  = 5;

		hPop.pt               = pt;	
		hPop.pszText          = m_strExplain2; // Message from String Table
		hPop.pszFont          = this->m_FontChar; // Font

#if _MSC_VER > 1300
		hWnd = ::HtmlHelp( hwndCallerWnd, NULL, HH_DISPLAY_TEXT_POPUP, ( DWORD_PTR )&hPop );
#else
		hWnd = ::HtmlHelp( hwndCallerWnd, NULL, HH_DISPLAY_TEXT_POPUP, ( DWORD     )&hPop );
#endif

		if ( hWnd )
		{
			// 
			if ( bRTLStyle )
			{
#if _MSC_VER > 1300
				LONG_PTR lExStyle = ( ::GetWindowLongPtr( hWnd, GWL_EXSTYLE ) | WS_EX_RTLREADING | WS_EX_LAYOUTRTL );

				::SetWindowLongPtr( hWnd, GWL_EXSTYLE, lExStyle );
#else
				LONG_PTR lExStyle = ( ::GetWindowLong( hWnd, GWL_EXSTYLE ) | WS_EX_RTLREADING | WS_EX_LAYOUTRTL );

				::SetWindowLong( hWnd, GWL_EXSTYLE, lExStyle );
#endif
			}

			//  
			::SetWindowPos( hWnd, HWND_TOPMOST, pt.x, pt.y, 0, 0, SWP_NOSIZE );
			::ShowWindow( hWnd, SW_HIDE );
			::ShowWindow( hWnd, SW_SHOW );
		}

		AfxGetApp()->EndWaitCursor();
	}

	TRACE( "End Show Explain: %s\n", m_strExplain );
}
