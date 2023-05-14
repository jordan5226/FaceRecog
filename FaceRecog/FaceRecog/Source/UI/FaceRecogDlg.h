#pragma once
#include <opencv.hpp>
#include "..\..\..\..\EZ_Source\Src_Util\Ctrl\EZ_ThreadXMLDlg.h"
#include "..\..\..\..\EZ_Source\Src_Util\Ctrl\EZ_MemoryDC.h"
#include "..\..\..\..\EZ_Source\Src_Util\EZ_TemplateVectorArray.h"
#include "..\FaceRecog\FaceRecogEngine.h"

#define TMP_IMG_PATH	EZ_Mutex::gm_WorkPath + _T("cap.jpg")
#define SAV_IMG_FOLDER	EZ_Mutex::gm_WorkPath + _T("faces\\")
#define _RENDER_TO_DC_	1

// CFaceRecogDlg 對話框
class CFaceRecogDlg : public EZ_ThreadXMLDlg, public CFaceRecogEngineCallback
{
	DECLARE_DYNAMIC( CFaceRecogDlg );
	// Attributes
public:
	enum
	{
		IDD = IDD_FACERECOG,
		MSG_DISPLAY_FRAME = ( WM_USER + 1000 ),
		MSG_CLOSE = ( WM_USER + 1001 ),
	};

	enum EVENT
	{
		EVENT_CAP = 0,
		EVENT_COUNT
	};

protected:
	volatile BOOL		m_bStopCapture;
	HICON				m_hIcon;
	cv::Mat				m_matFrame;
#if _RENDER_TO_DC_
	CRect				m_rcFrame;
	BITMAPINFOHEADER	m_bih;
	EZ_MemoryDC			m_dcMem;
#endif

	// Methods
public:
	CFaceRecogDlg( CWnd* lpParent = NULL );	// 標準構造函數
	~CFaceRecogDlg();
	void RecordFace( cv::Mat& matFace );

	// Callback ( CFaceRecogEngineCallback )
	virtual void OnNoMatch( cv::Mat& matFace );

protected:
	virtual void	DoDataExchange( CDataExchange* pDX );	// DDX/DDV 支持
	virtual BOOL	OnInitDialog();
	virtual void	Thread_Function();
	virtual BOOL	CreateMemDC( C_INT iWidth, C_INT iHeight, C_INT iBitsPerPel );
	virtual void	DrawFrame( cv::Mat& matFrame );

	//
	afx_msg void	OnClose();
	afx_msg void	OnBnClickedDetect();
	afx_msg void	OnBnClickedClose();
	afx_msg void	OnSysCommand( UINT nID, LPARAM lParam );
	afx_msg void	OnPaint();
	afx_msg HCURSOR	OnQueryDragIcon();
	afx_msg LRESULT	OnMsgDisplayFrame( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT	OnMsgClose( WPARAM wParam, LPARAM lParam );

	DECLARE_MESSAGE_MAP()

};
