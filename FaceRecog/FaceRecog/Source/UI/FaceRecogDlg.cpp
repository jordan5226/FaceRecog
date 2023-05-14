#include "stdafx.h"
#include "FaceRecogDlg.h"
#include "afxdialogex.h"
#include <opencv2\highgui\highgui_c.h>	// For cvGetWindowHandle
#include "..\FaceRecog\FaceRecogEngine.h"
#include "FaceEnrollDlg.h"
#include "..\..\..\..\EZ_Source\Src_Util\EZ_Counter.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace dlib;
using namespace std;
using namespace cv;

// CFaceRecogDlg 對話框
IMPLEMENT_DYNAMIC( CFaceRecogDlg, EZ_ThreadXMLDlg );

BEGIN_MESSAGE_MAP( CFaceRecogDlg, EZ_ThreadXMLDlg )
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED( IDC_BTN_DETECT, &CFaceRecogDlg::OnBnClickedDetect )
	ON_BN_CLICKED( IDC_BTN_CLOSE, &CFaceRecogDlg::OnBnClickedClose )
	ON_MESSAGE( MSG_DISPLAY_FRAME, CFaceRecogDlg::OnMsgDisplayFrame )
	ON_MESSAGE( MSG_CLOSE, CFaceRecogDlg::OnMsgClose )
END_MESSAGE_MAP()

CFaceRecogDlg::CFaceRecogDlg( CWnd* lpParent/* =NULL*/ ) : EZ_ThreadXMLDlg( IDD, lpParent ), m_bStopCapture( FALSE )
#if _RENDER_TO_DC_
, m_rcFrame( 0, 0, 0, 0 )
#endif
{
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
#if _RENDER_TO_DC_
	::memset( &m_bih, 0, sizeof( m_bih ) );
#endif
}

CFaceRecogDlg::~CFaceRecogDlg()
{
	EZ_ThreadXMLDlg::Set_Exit_Event( TRUE, TRUE );

	if( EZ_ThreadXMLDlg::Lock() )
	{
		m_matFrame.release();
#if _RENDER_TO_DC_
		m_dcMem.ReleaseDC();
#endif
		EZ_ThreadXMLDlg::Unlock();
	}
}

void CFaceRecogDlg::DoDataExchange( CDataExchange* pDX )
{
	EZ_ThreadXMLDlg::DoDataExchange( pDX );
}

// CFaceRecogDlg 消息處理程序

BOOL CFaceRecogDlg::OnInitDialog()
{
	EZ_ThreadXMLDlg::OnInitDialog();

	// 設置此對話框的圖標。  當應用程序主窗口不是對話框時，框架將自動
	//  執行此操作
	SetIcon( m_hIcon, TRUE );		// 設置大圖標
	SetIcon( m_hIcon, FALSE );		// 設置小圖標

	// TODO: 在此添加額外的初始化代碼
	::g_oFaceEng.SetFaceRecogEngineCallback( this );

	// Get Text Size
	CDC* pDC = this->GetDC();
	
	if( pDC )
	{
		CSize sizeText( 0, 0 );
		CFont ftName;

		if( !ftName.GetSafeHandle() )
		{	// Create Name Text Font
			LOGFONT logFont;
			::memset( &logFont, 0, sizeof( LOGFONT ) );
			CFont* lpSystemFont = CFont::FromHandle( ( HFONT )::GetStockObject( DEFAULT_GUI_FONT ) );
			lpSystemFont->GetLogFont( &logFont );
			logFont.lfHeight = -::MulDiv( 35, ::GetDeviceCaps( pDC->GetSafeHdc(), LOGPIXELSY ), 72 );
			ftName.CreateFontIndirect( &logFont );
		}

		pDC->SelectObject( &ftName );

		CString strName( _T( "測試名稱" ) );
		sizeText = pDC->GetTextExtent( strName );

		g_oFaceEng.SetTextHeight( sizeText.cy );
	}

	//
#if _RENDER_TO_DC_
	GetDlgItem( IDC_STATIC_IMAGE )->GetWindowRect( m_rcFrame );
	this->ScreenToClient( m_rcFrame );
#endif

	return TRUE;  // 除非將焦點設置到控件，否則返回 TRUE
}

void CFaceRecogDlg::OnSysCommand( UINT nID, LPARAM lParam )
{
	EZ_ThreadXMLDlg::OnSysCommand( nID, lParam );
}

// 如果向對話框添加最小化按鈕，則需要下面的代碼
//  來繪製該圖標。  對於使用文檔/視圖模型的 MFC 應用程序，
//  這將由框架自動完成。

void CFaceRecogDlg::OnPaint()
{
	if( IsIconic() )
	{
		CPaintDC dc( this ); // 用於繪製的設備上下文

		SendMessage( WM_ICONERASEBKGND, reinterpret_cast< WPARAM >( dc.GetSafeHdc() ), 0 );

		// 使圖標在工作區矩形中居中
		int cxIcon = GetSystemMetrics( SM_CXICON );
		int cyIcon = GetSystemMetrics( SM_CYICON );
		CRect rect;
		GetClientRect( &rect );
		int x = ( rect.Width() - cxIcon + 1 ) / 2;
		int y = ( rect.Height() - cyIcon + 1 ) / 2;

		// 繪製圖標
		dc.DrawIcon( x, y, m_hIcon );
	}
	else
	{
#if _RENDER_TO_DC_
		CPaintDC dc( this );
		dc.SetStretchBltMode( COLORONCOLOR );

		if( EZ_ThreadXMLDlg::Lock() )
		{
			if( this->m_dcMem.GetSafeHdc() )
				dc.BitBlt( m_rcFrame.left, m_rcFrame.top, m_rcFrame.Width(), m_rcFrame.Height(), this->m_dcMem, 0, 0, SRCCOPY );

			EZ_ThreadXMLDlg::Unlock();
		}
#else
		EZ_ThreadXMLDlg::OnPaint();
#endif
	}
}

//當用戶拖動最小化窗口時系統調用此函數取得光標
//顯示。
HCURSOR CFaceRecogDlg::OnQueryDragIcon()
{
	return static_cast< HCURSOR >( m_hIcon );
}

LRESULT CFaceRecogDlg::OnMsgDisplayFrame( WPARAM wParam, LPARAM lParam )
{
#if _RENDER_TO_DC_
	this->InvalidateRect( m_rcFrame, FALSE );
#else
	if( EZ_ThreadXMLDlg::Lock( 30 ) )
	{
		try
		{
			imshow( "view", m_matFrame );
		}
		catch( cv::Exception& e )
		{
			;
		}

		EZ_ThreadXMLDlg::Unlock();
	}
#endif

	return 0;
}

LRESULT CFaceRecogDlg::OnMsgClose( WPARAM wParam, LPARAM lParam )
{
#if !_RENDER_TO_DC_
	if( m_bStopCapture )
		destroyWindow( "view" );
#endif

	this->EndDialog( IDOK );
	return 0;
}

void CFaceRecogDlg::RecordFace( cv::Mat& matFace )
{
	INT_PTR nRes;
	FaceEnrollDlg dlgFaceRecord;
	nRes = dlgFaceRecord.DoModal();
	if( IDOK == nRes )
	{
		CString strCapPath( TMP_IMG_PATH );
		char    szCapPath[ MAX_PATH ] = { 0 };

		// Unicode to ANSI
		EZ_MSXMLInterface::StringToString( EZ_Mutex::gm_bUnicode, strCapPath, FALSE, MAX_PATH, ( LPTSTR )szCapPath, CP_UTF8 );

		// Save Captured Face
		cv::imwrite( szCapPath, matFace );

		// Move Captured Face Image To Face Database
		UpdateData( TRUE );

		CString strFullFilePath;
		strFullFilePath.Format( _T( "%s%s.jpg" ), SAV_IMG_FOLDER, dlgFaceRecord.Get_face_name() );
		::MoveFile( strCapPath, strFullFilePath );
	}
}

void CFaceRecogDlg::OnNoMatch( cv::Mat& matFace )
{
	this->RecordFace( matFace );
}

void CFaceRecogDlg::OnBnClickedDetect()
{
	// Start Thread
	EZ_ThreadXMLDlg::Initial_Thread( EVENT_COUNT );

	//
#if _RENDER_TO_DC_
	this->GetDlgItem( IDC_STATIC_IMAGE )->ShowWindow( SW_HIDE );
#else
	namedWindow( "view", WINDOW_FULLSCREEN );
	HWND hWnd = ( HWND )cvGetWindowHandle( "view" );
	HWND hParent = ::GetParent( hWnd );
	::SetParent( hWnd, GetDlgItem( IDC_STATIC_IMAGE )->m_hWnd );
	::ShowWindow( hParent, SW_HIDE );
#endif

	//
	this->SetWindowText( _T( "Detecting..." ) );
	this->SetEvent( EVENT_CAP );
}

void CFaceRecogDlg::OnBnClickedClose()
{
	if( EZ_Thread::m_hThread )
		m_bStopCapture = TRUE;
	else
		this->PostMessage( MSG_CLOSE, 0, 0 );
}

//  ==========================================================================
//  Thread_Function
//  ==========================================================================
void CFaceRecogDlg::Thread_Function()
{
	C_DWORD nEventCnt = EVENT_COUNT + 1;
	HANDLE  hEvent[ nEventCnt ] =
	{
		EZ_ThreadXMLDlg::m_hExit,				//  Exit Event		
		EZ_ThreadXMLDlg::m_hEvent[ EVENT_CAP ],	//  Capture Video
	};

	EZ_PerformanceCounterV2 ezCounter( FALSE );

	for( INT iWait, iExit = 0; iExit <= 0; )
	{
		iWait = ::WaitForMultipleObjects( nEventCnt, hEvent, FALSE, INFINITE );

		switch( iWait )
		{
		case ( WAIT_OBJECT_0 + 1 ):		//  Capture Video
			{
				::ResetEvent( EZ_ThreadXMLDlg::m_hEvent[ EVENT_CAP ] );

				g_oFaceEng.InitDetectFace();

				VideoCapture cap( 0 );

				ezCounter.Start();

			CAPTURE:
				if( !cap.isOpened() )
				{
					if( !m_bStopCapture )
						::AfxMessageBox( _T( "Please check your USB camera's interface num." ) );

					this->PostMessage( MSG_CLOSE, 0, 0 );
					break;
				}

				// Detect
				while( true )
				{
					if( EZ_ThreadXMLDlg::Lock() )
					{
						//
						if( m_bStopCapture )
						{
							cap.release();
							m_matFrame.release();
							this->PostMessage( MSG_CLOSE, 0, 0 );
							EZ_ThreadXMLDlg::Unlock();
							break;
						}

						//
						cap >> m_matFrame;

						if( !m_matFrame.empty() )
						{
							int iRet = g_oFaceEng.DetectFace( m_matFrame );

#if _RENDER_TO_DC_
							this->DrawFrame( m_matFrame );
#endif
							this->PostMessage( MSG_DISPLAY_FRAME, 0, 0 );
					
							if( 1 == iRet )
							{
								// save the capture face to the project directory
								//cv::imwrite( TMP_IMG_PATH, face );
								EZ_ThreadXMLDlg::Unlock();
								break;
							}
							else if( iRet < 0 )
							{
								;
							}
						}

						EZ_ThreadXMLDlg::Unlock();
					}

					//
#if !_RENDER_TO_DC_
					int c = waitKey( 10 );
					if( ( char )c == 'c' ) { break; }
#endif
				}

				// Recognize
				if( !m_bStopCapture )
				{
					if( ezCounter.Stop() > 200 )
					{
						g_oFaceEng.SetEvent( CFaceRecogEngine::EVENT_RECOG );
						ezCounter.Start();
					}
				}

				//
				if( EZ_ThreadXMLDlg::Lock() )
				{
					m_matFrame.release();
					EZ_ThreadXMLDlg::Unlock();
				}
				goto CAPTURE;
			}
			break;

		case WAIT_OBJECT_0: 			// Exit
			{
				iExit = 1;

				if( EZ_ThreadXMLDlg::Lock() )
				{
					EZ_ThreadXMLDlg::m_iThreadID = 0;

					EZ_ThreadXMLDlg::Unlock();
				}
			}
			continue;
		}

	}
}

void CFaceRecogDlg::OnClose()
{
	this->OnBnClickedClose();
}

BOOL CFaceRecogDlg::CreateMemDC( C_INT iWidth, C_INT iHeight, C_INT iBitsPerPel )
{
	BOOL bRet = TRUE;
#if _RENDER_TO_DC_
	if( EZ_ThreadXMLDlg::Lock() )
	{
		if( !m_dcMem.GetSafeHdc() )
		{
			bRet = m_dcMem.CreateDC( NULL, iWidth, iHeight, 1, iBitsPerPel, TRUE );
			m_dcMem.SetStretchBltMode( COLORONCOLOR );
		}

		EZ_ThreadXMLDlg::Unlock();
	}
#endif
	return bRet;
}

void CFaceRecogDlg::DrawFrame( cv::Mat& matFrame )
{
#if _RENDER_TO_DC_
	if( !this->CreateMemDC( matFrame.cols, matFrame.rows, matFrame.channels() << 3 ) )
	{
		::EZOutputDebugString( _T("[ FaceRecog ] CFaceRecogDlg::DrawFrame - Create memory DC failed!\n") );
		return;
	}

	if( EZ_ThreadXMLDlg::Lock() )
	{
		if( matFrame.channels() == 3 || matFrame.channels() == 4 )
		{
			m_bih.biSize          = sizeof( BITMAPINFOHEADER );
			m_bih.biBitCount      = matFrame.channels() << 3;
			m_bih.biHeight        = -matFrame.rows;
			m_bih.biWidth         = matFrame.cols;
			m_bih.biPlanes        = 1;
			m_bih.biCompression   = BI_RGB;
			m_bih.biSizeImage     = matFrame.channels() * matFrame.cols * matFrame.rows;
			m_bih.biXPelsPerMeter = 0;
			m_bih.biYPelsPerMeter = 0;
			m_bih.biClrUsed       = 0;
			m_bih.biClrImportant  = 0;

			m_dcMem.StretchDIBits( &m_bih, matFrame.data, 0, 0, m_matFrame.cols, m_matFrame.rows, DIB_RGB_COLORS, SRCCOPY );
		}
		else
		{
			// Not support
		}

		EZ_ThreadXMLDlg::Unlock();
	}
#endif
}
