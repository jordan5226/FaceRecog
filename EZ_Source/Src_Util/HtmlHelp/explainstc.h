#if !defined(AFX_EXPLAINSTC_H__9D920605_C595_11D6_8A48_0050BA713ED9__INCLUDED_)
#define AFX_EXPLAINSTC_H__9D920605_C595_11D6_8A48_0050BA713ED9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Afxwin.h>

//  ==========================================================================
//  
//  ==========================================================================
#define _DEF_STC_COLOR_NORMAL	RGB(0,0,0)
#define _DEF_STC_COLOR			RGB(0,0,255)
#define _DEF_STC_SIZE			9

#ifdef RES_BIG5 //  �c�餤��
#define _DEF_STC_CHARSET	CHINESEBIG5_CHARSET
#define _DEF_STC_FONTNAME	_T( "�s�ө���" )
#define _DEF_STC_FONTCHAR   _T( "�s�ө���, 9, , , " )

#elif RES_PTU   //  �������
#define _DEF_STC_CHARSET	DEFAULT_CHARSET
#define _DEF_STC_FONTNAME	_T( "Arial" )
#define _DEF_STC_FONTCHAR   _T( "Arial, 9, , , " )

#elif RES_SPN   //  ��Z����
#define _DEF_STC_CHARSET	DEFAULT_CHARSET
#define _DEF_STC_FONTNAME	_T( "Arial" )
#define _DEF_STC_FONTCHAR   _T( "Arial, 9, , , " )

#elif RES_POL   //  �i����
#define _DEF_STC_CHARSET	DEFAULT_CHARSET
#define _DEF_STC_FONTNAME	_T( "Arial" )
#define _DEF_STC_FONTCHAR   _T( "Arial, 9, , , " )

#elif RES_RUS   //  �X��
#define _DEF_STC_CHARSET	RUSSIAN_CHARSET
#define _DEF_STC_FONTNAME	_T( "Arial" )
#define _DEF_STC_FONTCHAR   _T( "Arial, 9, , , " )

#elif RES_GB    //  ²�餤��
#define _DEF_STC_CHARSET	GB2312_CHARSET
#define _DEF_STC_FONTNAME	_T( "����" )
#define _DEF_STC_FONTCHAR   _T( "����, 9, , , " )

#elif RES_GER   //  �w��
#define _DEF_STC_CHARSET	DEFAULT_CHARSET
#define _DEF_STC_FONTNAME	_T( "Arial" )
#define _DEF_STC_FONTCHAR   _T( "Arial, 9, , , " )

#elif RES_SJIS  //  ���
#define _DEF_STC_CHARSET	SHIFTJIS_CHARSET
#define _DEF_STC_FONTNAME	_T( "MS UI Gothic" )
#define _DEF_STC_FONTCHAR   _T( "MS UI Gothic, 9, , , " )

#elif RES_FRA   //  �k��
#define _DEF_STC_CHARSET	DEFAULT_CHARSET
#define _DEF_STC_FONTNAME	_T( "Arial" )
#define _DEF_STC_FONTCHAR   _T( "Arial, 9, , , " )

#elif RES_KOR   //  ����
#define _DEF_STC_CHARSET	JOHAB_CHARSET
#define _DEF_STC_FONTNAME	_T( "����" )
#define _DEF_STC_FONTCHAR   _T( "����, 9, , , " )

#elif RES_FIN   //  ������
#define _DEF_STC_CHARSET	DEFAULT_CHARSET
#define _DEF_STC_FONTNAME	_T( "Arial" )
#define _DEF_STC_FONTCHAR   _T( "Arial, 9, , , " )

#elif RES_NOR   //  ���¤�
#define _DEF_STC_CHARSET	DEFAULT_CHARSET
#define _DEF_STC_FONTNAME	_T( "Arial" )
#define _DEF_STC_FONTCHAR   _T( "Arial, 9, , , " )

#elif RES_ARB   //  ���ԧB��
#define _DEF_STC_CHARSET	ARABIC_CHARSET
#define _DEF_STC_FONTNAME	_T( "Arial" )
#define _DEF_STC_FONTCHAR   _T( "Arial, 9, , , " )
#define  RES_LAYOUTRTL      1

#elif RES_HEB   //  �ƧB�Ӥ�
#define _DEF_STC_CHARSET	HEBREW_CHARSET
#define _DEF_STC_FONTNAME	_T( "Arial" )
#define _DEF_STC_FONTCHAR   _T( "Arial, 9, , , " )
#define  RES_LAYOUTRTL      1

#elif RES_HUN   //  �I���Q��
#define _DEF_STC_CHARSET	DEFAULT_CHARSET
#define _DEF_STC_FONTNAME	_T( "Arial" )
#define _DEF_STC_FONTCHAR   _T( "Arial, 9, , , " )

#elif RES_DAN   //  ������
#define _DEF_STC_CHARSET	DEFAULT_CHARSET
#define _DEF_STC_FONTNAME	_T( "Arial" )
#define _DEF_STC_FONTCHAR   _T( "Arial, 9, , , " )

#elif RES_SRL   //  �n���ԤҤ�
#define _DEF_STC_CHARSET	DEFAULT_CHARSET
#define _DEF_STC_FONTNAME	_T( "Arial" )
#define _DEF_STC_FONTCHAR   _T( "Arial, 9, , , " )

#elif RES_CZH   //  ���J��
#define _DEF_STC_CHARSET	DEFAULT_CHARSET
#define _DEF_STC_FONTNAME	_T( "Arial" )
#define _DEF_STC_FONTCHAR   _T( "Arial, 9, , , " )

#elif RES_TAI   //  ����
#define _DEF_STC_CHARSET	THAI_CHARSET
#define _DEF_STC_FONTNAME	_T( "Tahoma" )
#define _DEF_STC_FONTCHAR   _T( "Tahoma, 9, , , " )

#elif RES_NLD   //  ������
#define _DEF_STC_CHARSET	DEFAULT_CHARSET
#define _DEF_STC_FONTNAME	_T( "Arial" )
#define _DEF_STC_FONTCHAR   _T( "Arial, 9, , , " )

#else // RES_ASCI  //  �^��
#define _DEF_STC_CHARSET	DEFAULT_CHARSET
#define _DEF_STC_FONTNAME	_T( "Arial" )
#define _DEF_STC_FONTCHAR   _T( "Arial, 9, , , " )

#endif

//  ==========================================================================
//  CExplainStc window
//  ==========================================================================
class CExplainStc : public CStatic
{
public:
	enum 
	{
		DEFAULT_BACKGROUND_COLOR = RGB(255, 255, 208),
	};

	DECLARE_MESSAGE_MAP()

protected:
	bool	 m_bUseExpain;
	bool	 m_blButtonDown;
	bool	 m_bInRect;
	bool	 m_bUseIcon;

	COLORREF m_TextColor;
	HICON	 m_hicon;
	HCURSOR  m_hCursor;
	CWnd*    m_pParent;

	CRect    m_TextRect;
	CFont	 m_Font;
	CFont	 m_FontNormal;

	CString  m_strText;
	CString  m_FontChar;
	CString	 m_strExplain;
	CString  m_strExplain2;

public:
	CExplainStc( CWnd* pParent = NULL );
	virtual ~CExplainStc();

	virtual bool SetExplain( LPCTSTR lpszString, COLORREF STCColor = _DEF_STC_COLOR, 
		int nSTCSize = _DEF_STC_SIZE, BYTE nSTCCharSet = _DEF_STC_CHARSET, LPCTSTR lpszSTCFontName = _DEF_STC_FONTNAME );
	
#ifdef RES_LAYOUTRTL
	virtual void ShowExplain( const BOOL bRTLStyle = TRUE,  HWND hwndCallerWnd = NULL /*::GetTopWindow( NULL )*/ );
#else
	virtual void ShowExplain( const BOOL bRTLStyle = FALSE, HWND hwndCallerWnd = NULL /*::GetTopWindow( NULL )*/ );
#endif

protected:
	afx_msg void OnPaint();
	afx_msg void OnCaptureChanged( CWnd *pWnd );
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );
	afx_msg int  OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	afx_msg BOOL OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message );

	//  ==========================================================================
	//  Easy Function
	//  ==========================================================================
public:
	virtual bool SetExplain( LPCTSTR lpszString, CFont* lpFont )
	{
		bool bResult = false;

		if ( !lpFont )
			bResult = this->SetExplain( lpszString );
		else
		{
			LOGFONT logFont;

			if ( lpFont->GetLogFont( &logFont ) )
			{
				this->m_FontChar.Format( _T( "%s, %d, , , " ), logFont.lfFaceName, _DEF_STC_SIZE );

				bResult = this->SetExplain( lpszString, _DEF_STC_COLOR, _DEF_STC_SIZE, logFont.lfCharSet, logFont.lfFaceName );
			}
		}

		return bResult;
	}

	virtual bool SetExplain2( LPCTSTR lpszString )
	{
		if ( lpszString )
			this->m_strExplain2.Format( _T( "%s" ), lpszString );
		else
			this->m_strExplain2.Format( _T( "%s" ), _T( "" )   );

		return true;
	}
};

#endif
