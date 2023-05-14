#include "stdafx.h"
#include "io.h"
#include "facedetect-dll.h" // libfacedetection include
#include "dlib\opencv\cv_image.h"
#include "FaceRecogEngine.h"
#include "..\UI\PutText.h"	// 繪製中文字在CV圖像上
#include "..\..\..\..\EZ_Source\Src_Util\EZ_StringCast.h"
//#include <opencv2\imgproc\types_c.h>	// For compile CV_BGR2GRAY

using namespace dlib;
using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DETECT_BUFFER_SIZE	0x20000
#define _RECORD_FACE_		0

// ----------------------------------------------------------------------------------------
CFaceRecogEngine::CFaceRecogEngine() : EZ_Thread()
, m_nFaceDetectCount( 0 ), m_iTextH( 0 ), m_pBuffer( NULL ), m_lpFaceEngCB( NULL ), m_mxFace( EZ_Mutex( FALSE, NULL, NULL, FALSE ) )
{
	EZ_Thread::Initial_Thread( this, EVENT_COUNT );
}

CFaceRecogEngine::CFaceRecogEngine( int depth ) : EZ_Thread()
, m_nFaceDetectCount( 0 ), m_iTextH( 0 ), m_pBuffer( NULL ), m_lpFaceEngCB( NULL ), m_mxFace( EZ_Mutex( FALSE, NULL, NULL, FALSE ) )
{
	m_arrFaceDesc.reserve( depth );
	EZ_Thread::Initial_Thread( this, EVENT_COUNT );
}

CFaceRecogEngine::~CFaceRecogEngine()
{
	this->Uninit();
}

void CFaceRecogEngine::Uninit()
{
	EZ_Thread::Set_Exit_Event( 1, TRUE );

	if( EZ_Thread::Lock() )
	{
		SAFE_DELETE_ARRAY( m_pBuffer );
		m_arrFaceInfoPtr.FreeAll();
		EZ_Thread::Unlock();
	}

}

int CFaceRecogEngine::LoadFaces( void )
{
	long long  hFile = 0;	// Type long long under Win10; long under Win7
	struct     _finddata_t fileinfo;

	frontal_face_detector detector = get_frontal_face_detector();
	// We will also use a face landmarking model to align faces to a standard pose:  (see face_landmark_detection_ex.cpp for an introduction)
	deserialize( "shape_predictor_68_face_landmarks.dat" ) >> m_SP;

	// And finally we load the DNN responsible for face recognition.
	deserialize( "dlib_face_recognition_resnet_model_v1.dat" ) >> m_DNN;

	if( ( hFile = _findfirst( ".\\faces\\*.jpg", &fileinfo ) ) != -1 )
	{
		do
		{
			if( ( fileinfo.attrib & _A_ARCH ) )
			{
				if( strcmp( fileinfo.name, "." ) != 0 && strcmp( fileinfo.name, ".." ) != 0 )
				{
					if( !strcmp( strstr( fileinfo.name, "." ) + 1, "jpg" ) )
					{
						matrix<rgb_pixel> img;
						char path[ 260 ];
						sprintf_s( path, ".\\faces\\%s", fileinfo.name );
						load_image( img, path );
						image_window win( img );

						for( auto face : detector( img ) )
						{
							auto shape = m_SP( img, face );
							matrix<rgb_pixel> face_chip;
							extract_image_chip( img, get_face_chip_details( shape, 150, 0.25 ), face_chip );
							// get_face_chip_details: 對齊人臉特徵點。將檢測到的目標圖片標準化為150*150像素大小，並對人臉進行旋轉居中
							// extract_image_chip: 根據計算出的相似變換的矩陣location，從原始圖像img中得到變換後的圖像塊chip，使用interp插值方法

							// Record the all this face's information
							FACE_DESC sigle_face;
							sigle_face.m_mtxChip = face_chip;

							// Get Picture Human Name
							string strName = fileinfo.name;
							size_t iFind = strName.find_last_of( '\\' );
							strName = strName.substr( iFind + 1 );
							iFind = strName.find_first_of( '_' );

							if( string::npos != iFind )
								strName = strName.substr( 0, iFind );
							else
							{
								iFind = strName.find_last_of( ".jpg" );
								strName = strName.substr( 0, ( iFind - 3 ) );
							}

							sigle_face.m_strName = strName;

							//
							std::vector<matrix<rgb_pixel>> face_chip_vec;
							std::vector<matrix<float, 0, 1>> face_all;

							face_chip_vec.push_back( move( face_chip ) );

							// Asks the DNN to convert each face image in faces into a 128D vector
							face_all = m_DNN( face_chip_vec );

							// Get the feature of this person
							std::vector<matrix<float, 0, 1>>::iterator iter_begin = face_all.begin(),
								iter_end = face_all.end();
							if( face_all.size() > 1 ) break;
							sigle_face.m_mtxFeature = *iter_begin;

							//all the person description into vector
							m_arrFaceDesc.push_back( sigle_face );

							win.add_overlay( face );
						}
					}
					else
					{
						EZOutputDebugString( _T( "[ FaceRecog ] CFaceRecogEngine::LoadFaces - This file is not image file! ( File: '%s' )\n" ), fileinfo.name );
					}
				}
			}
		} while( _findnext( hFile, &fileinfo ) == 0 );

		_findclose( hFile );
	}

	return 1;
}

void CFaceRecogEngine::Thread_Function()
{
	C_DWORD nEventCnt = EVENT_COUNT + 1;
	HANDLE  hEvent[ nEventCnt ] =
	{
		EZ_Thread::m_hExit,					//  Exit Event		
		EZ_Thread::m_hEvent[ EVENT_RECOG ],	//  Recognize Face
	};

	BOOL       bRecog = FALSE;
	LPFACEINFO lpFaceInfo = NULL;

	for( INT iWait, iExit = 0; iExit <= 0; )
	{
		iWait = ::WaitForMultipleObjects( nEventCnt, hEvent, FALSE, INFINITE );

		switch( iWait )
		{
		case ( WAIT_OBJECT_0 + 1 ):		// Recognize Face
			{
				::ResetEvent( EZ_Thread::m_hEvent[ EVENT_RECOG ] );

				bRecog = FALSE;

				if( m_mxFace.Lock() )
				{
					::EZOutputDebugString( _T( "[ FaceRecog ] CFaceRecog::Thread_Function - TODO: RecognizeFace ( Cnt: %d )\n" ), m_arrFaceInfoPtr.GetSize() );
					EZ_SystemTime stCurTime( TRUE );

					for( INT i = ( INT )m_arrFaceInfoPtr.GetSize() - 1; i >= 0; --i )
					{
						lpFaceInfo = m_arrFaceInfoPtr.GetAt( i );

						if( lpFaceInfo )
						{
							if( !lpFaceInfo->m_strName.IsEmpty() )
							{
								if( stCurTime - lpFaceInfo->m_ezTime <= FACEINFO::TIME_FACE_ALLIVE )
								{
									bRecog = TRUE;
									continue;
								}
							}
							else if( this->RecognizeFace( lpFaceInfo ) )
							{
								bRecog = TRUE;
								continue;
							}
						}

						m_arrFaceInfoPtr.Free( i );
					}

					::EZOutputDebugString( _T( "[ FaceRecog ] CFaceRecog::Thread_Function - ENDDO: RecognizeFace\n" ) );
					m_mxFace.Unlock();
				}

				if( EZ_Thread::Lock() )
				{
					if( bRecog )
						m_nFaceDetectCount = 0;
					EZ_Thread::Unlock();
				}
			}
			break;

		case WAIT_OBJECT_0: 			// Exit
			{
				iExit = 1;

				if( EZ_Thread::Lock() )
				{
					EZ_Thread::m_iThreadID = 0;

					EZ_Thread::Unlock();
				}
			}
			continue;
		}

	}
}

void CFaceRecogEngine::DrawText( int iX, int iY, CStringA& strName, cv::Mat& frame )
{
	if( strName.IsEmpty() )
		return;

	// Draw Text
	Point pt( iX, ( iY - m_iTextH ) );
	::PutTextZH( frame, strName, pt, cv::Scalar( 0, 255, 255 ), 35, "Arial" );
}

void CFaceRecogEngine::DrawRect( cv::Mat& frame, int iLeft, int iTop, int iRight, int iBottom )
{
	cv::rectangle( frame, Point( iLeft, iTop ), Point( iRight, iBottom ), Scalar( 230, 255, 0 ), 3 );
}

int CFaceRecogEngine::DetectFace( cv::Mat& frame )
{
	Mat gray;
	Mat face;
	int iRet = -1;

	if( frame.empty() || !frame.data ) return -1;

	cvtColor( frame, gray, COLOR_BGR2GRAY/*CV_BGR2GRAY*/ );
	int* pResults = NULL;

	if( EZ_Thread::Lock() )
	{
		if( !m_pBuffer )
		{
			m_pBuffer = new BYTE[ DETECT_BUFFER_SIZE ];
			if( !m_pBuffer )
			{
				fprintf( stderr, "Can not alloc buffer.\n" );
				EZ_Thread::Unlock();
				return -1;
			}
		}

		pResults = facedetect_multiview_reinforce( m_pBuffer, ( LPBYTE )( gray.ptr( 0 ) ), gray.cols, gray.rows, ( int )gray.step, 1.2f, 2, 95, 0, 1 );
		// min_neighbors: 檢測出的人臉信心值，越大越有可能是人臉

		if( !pResults )
		{	// Face is moving, and reset the detect count
			m_nFaceDetectCount = 0;
			EZ_Thread::Unlock();
			return -1;
		}

		EZ_Thread::Unlock();
	}

	if( !pResults )
	{
		if( m_mxFace.Lock() )
		{
			m_arrFaceInfoPtr.FreeAll();
			m_mxFace.Unlock();
		}
		::EZOutputDebugString( _T( "[ FaceRecog ] CFaceRecog::CaptureFace - Face is move out.\n" ) );
	}

	//
	BOOL bHasFace = FALSE;
	BOOL bLock    = FALSE;

	try
	{
		for( int i = 0; i < ( pResults ? *pResults : 0 ); i++ )	// Loop for multiple faces
		{
			short* p = ( ( short* )( pResults + 1 ) ) + 6 * i;
			int x = p[ 0 ];
			int y = p[ 1 ];
			int w = p[ 2 ];
			int h = p[ 3 ];
			int neighbors = p[ 4 ];

			Rect_<float> face_rect = Rect_<float>( x, y, w, h );
			face = frame( face_rect );

			//
			if( !face.empty() && face.data )
			{
				bHasFace = TRUE;

				::EZOutputDebugString( _T( "[ FaceRecog ] CFaceRecog::CaptureFace - (1)Detected Face Index: %d\n" ), i );

				if( bLock = EZ_Thread::Lock( 0 ) )
				{
					BOOL       bFound = FALSE;
					LPFACEINFO lpFaceInfo = NULL;
					Point      right( x + w, y + h );

					::EZOutputDebugString( _T( "[ FaceRecog ] CFaceRecog::CaptureFace - (2)TODO: Find neighbor Face\n" ) );
					for( UINT n = 0, nCnt = m_arrFaceInfoPtr.GetSize(); n < nCnt; ++n )
					{
						lpFaceInfo = m_arrFaceInfoPtr.GetAt( n );

						if( lpFaceInfo && lpFaceInfo->ComparePosition( x, y, right.x, right.y ) )
						{	// Found same face
							bFound = TRUE;
							::EZOutputDebugString( _T( "[ FaceRecog ] CFaceRecog::CaptureFace - (2.1)Found neighbor Face!\n" ) );

							// Update
							lpFaceInfo->UpdatePosition( x, y, right.x, right.y );
							lpFaceInfo->m_matFace.release();
							lpFaceInfo->m_matFace = face.clone();

							// Draw name text align the face rectangle
							this->DrawText( lpFaceInfo->m_rcRegion.left, lpFaceInfo->m_rcRegion.top, lpFaceInfo->m_strName, frame );

							// Draw face rectangle
							this->DrawRect( frame, lpFaceInfo->m_rcRegion.left, lpFaceInfo->m_rcRegion.top,
								lpFaceInfo->m_rcRegion.right, lpFaceInfo->m_rcRegion.bottom );
							::EZOutputDebugString( _T( "[ FaceRecog ] CFaceRecog::CaptureFace - (2.2)Draw rectangle Idx: %d ( Width: %d, Height: %d )\n" ), i, lpFaceInfo->m_rcRegion.Width(), lpFaceInfo->m_rcRegion.Height() );

							break;
						}
					}
					::EZOutputDebugString( _T( "[ FaceRecog ] CFaceRecog::CaptureFace - (2)ENDDO: Find neighbor Face\n" ) );

					if( !bFound )
					{	// Not found
						lpFaceInfo = new FACEINFO();
						lpFaceInfo->m_rcRegion.SetRect( x, y, right.x, right.y );
						lpFaceInfo->m_matFace = face.clone();
						m_arrFaceInfoPtr.Add( lpFaceInfo );

						// Draw face rectangle
						this->DrawRect( frame, lpFaceInfo->m_rcRegion.left, lpFaceInfo->m_rcRegion.top,
							lpFaceInfo->m_rcRegion.right, lpFaceInfo->m_rcRegion.bottom );
						::EZOutputDebugString( _T( "[ FaceRecog ] CFaceRecog::CaptureFace - (3)Draw rectangle Idx: %d ( Width: %d, Height: %d )\n" ), i, w, h );
					}

					EZ_Thread::Unlock();
				}
				else
				{
					this->DrawRect( frame, x, y, x + w, y + h );
					::EZOutputDebugString( _T( "[ FaceRecog ] CFaceRecog::CaptureFace - Lock 2 timeout ( i: %d )\n" ), i );
				}
			}
		}
	}
	catch( cv::Exception& e )
	{
		if( bLock )
			EZ_Thread::Unlock();
	}

	if( !bHasFace )
	{
		if( EZ_Thread::Lock() )
		{
			m_nFaceDetectCount = 0;
			EZ_Thread::Unlock();
		}

		::EZOutputDebugString( _T( "[ FaceRecog ] CFaceRecog::CaptureFace - Valid face doesn't detect.\n" ) );
		return -1;
	}

	if( EZ_Thread::Lock() )
	{
		if( m_nFaceDetectCount++ > 12 )
		{	// Detected Continuous Face
			::EZOutputDebugString( _T( "[ FaceRecog ] CFaceRecog::CaptureFace - Detected Continuous Face\n" ) );
			iRet = 1;
		}
		else if( m_nFaceDetectCount > 0 )
		{	// Detected Face
			iRet = 0;
		}

		EZ_Thread::Unlock();
	}

	return iRet;
}

void CFaceRecogEngine::InitDetectFace()
{
	if( EZ_Thread::Lock() )
	{
		m_nFaceDetectCount = 0;
		EZ_Thread::Unlock();
	}
}

BOOL CFaceRecogEngine::RecognizeFace( LPFACEINFO lpFaceInfo )
{	// Locked By Caller
	if( !lpFaceInfo )
		return FALSE;

	BOOL bRet = FALSE;

	// Mat to dlib image
	matrix<rgb_pixel> matFaceRGB;
	dlib::assign_image( matFaceRGB, cv_image<rgb_pixel>( lpFaceInfo->m_matFace ) );

	frontal_face_detector          detector = get_frontal_face_detector();
	std::vector<matrix<rgb_pixel>> arrFaceRGB;

	for( auto face : detector( matFaceRGB ) )
	{
		auto shape = this->m_SP( matFaceRGB, face );
		matrix<rgb_pixel> matFaceRGBChip;
		extract_image_chip( matFaceRGB, get_face_chip_details( shape, 150, 0.25 ), matFaceRGBChip );
		// get_face_chip_details: 對齊人臉特徵點。將檢測到的目標圖片標準化為150*150像素大小，並對人臉進行旋轉居中
		// extract_image_chip: 根據計算出的相似變換的矩陣location，從原始圖像img中得到變換後的圖像塊chip，使用interp插值方法
		arrFaceRGB.push_back( move( matFaceRGBChip ) );
	}

	if( arrFaceRGB.size() != 1 )
	{
		EZOutputDebugString( _T( "[ FaceRecog ] CFaceRecogEngine::RecognizeFace - Face capture meets an error! Face numbers: %d\n" ), arrFaceRGB.size() );
		arrFaceRGB.clear();
		return FALSE;
	}

	// Use DNN and get the capture face's feature with 128D vector
	std::vector<matrix<float, 0, 1>> arrFaceDesc = this->m_DNN( arrFaceRGB );

	// Browse the face feature from the database, and find the match one
	size_t nMin_Idx = this->m_arrFaceDesc.size();
	float  fMin_Len = 0.45f;

	for( size_t n = 0; n < this->m_arrFaceDesc.size(); ++n )
	{
		auto len = length( arrFaceDesc[ 0 ] - this->m_arrFaceDesc[ n ].m_mtxFeature );

		if( len < fMin_Len )
		{
			fMin_Len = len;
			nMin_Idx = n;
		}
		else
		{
			EZOutputDebugString( _T( "[ FaceRecog ] CFaceRecogEngine::RecognizeFace - This face from database does not match the captured face, continue!\n" ) );
		}
	}

	// Find the most similar face
	if( nMin_Idx != this->m_arrFaceDesc.size() )
	{
		lpFaceInfo->m_strName     = this->m_arrFaceDesc[ nMin_Idx ].m_strName.c_str();
		lpFaceInfo->m_strFileName = this->m_arrFaceDesc[ nMin_Idx ].m_strFileName;
		lpFaceInfo->m_ezTime.Get_Current_Time();
		bRet = TRUE;
	}
	else
	{
#if _RECORD_FACE_
		if( ::MessageBox( NULL, CString("No similar faces found. Save it?"), NULL, MB_YESNO ) == IDYES )
		{
			if( m_lpFaceEngCB )
				m_lpFaceEngCB->OnNoMatch( lpFaceInfo->m_matFace );
		}
#endif
		bRet = FALSE;
	}

	arrFaceRGB.clear();
	arrFaceDesc.clear();

	return bRet;
}
