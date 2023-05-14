
// Face_Recognize.h : PROJECT_NAME 應用程序的主頭文件
//
#include "stdafx.h"
#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含「stdafx.h」以生成 PCH 文件"
#endif


#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/dnn.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <opencv.hpp>
#include "..\EZ_Source\Src_Util\Thread\EZ_Thread.h"
#include "..\EZ_Source\Src_Util\EZ_SystemTime.h"

using namespace dlib;
using namespace std;

// ----------------------------------------------------------------------------------------

// The next bit of code defines a ResNet network.  It's basically copied
// and pasted from the dnn_imagenet_ex.cpp example, except we replaced the loss
// layer with loss_metric and made the network somewhat smaller.  Go read the introductory
// dlib DNN examples to learn what all this stuff means.
//
// Also, the dnn_metric_learning_on_images_ex.cpp example shows how to train this network.
// The dlib_faces_db_recognition_resnet_model_v1 model used by this example was trained using
// essentially the code shown in dnn_metric_learning_on_images_ex.cpp except the
// mini-batches were made larger (35x15 instead of 5x5), the iterations without progress
// was set to 10000, the jittering you can see below in jitter_image() was used during
// training, and the training dataset consisted of about 3 million images instead of 55.
template <template <int, template<typename>class, int, typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual = add_prev1<block<N, BN, 1, tag1<SUBNET>>>;

template <template <int, template<typename>class, int, typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual_down = add_prev2<avg_pool<2, 2, 2, 2, skip1<tag2<block<N, BN, 2, tag1<SUBNET>>>>>>;

template <int N, template <typename> class BN, int stride, typename SUBNET>
using block = BN<con<N, 3, 3, 1, 1, relu<BN<con<N, 3, 3, stride, stride, SUBNET>>>>>;

template <int N, typename SUBNET> using ares = relu<residual<block, N, affine, SUBNET>>;
template <int N, typename SUBNET> using ares_down = relu<residual_down<block, N, affine, SUBNET>>;

template <typename SUBNET> using alevel0 = ares_down<256, SUBNET>;
template <typename SUBNET> using alevel1 = ares<256, ares<256, ares_down<256, SUBNET>>>;
template <typename SUBNET> using alevel2 = ares<128, ares<128, ares_down<128, SUBNET>>>;
template <typename SUBNET> using alevel3 = ares<64, ares<64, ares<64, ares_down<64, SUBNET>>>>;
template <typename SUBNET> using alevel4 = ares<32, ares<32, ares<32, SUBNET>>>;

using anet_type = loss_metric<fc_no_bias<128, avg_pool_everything<
	alevel0<
	alevel1<
	alevel2<
	alevel3<
	alevel4<
	max_pool<3, 3, 2, 2, relu<affine<con<32, 7, 7, 2, 2,
	input_rgb_image_sized<150>
	>>>>>>>>>>>>;

using face_pair = std::pair<matrix<rgb_pixel>, std::string>;

// ----------------------------------------------------------------------------------------

// tagFACEINFO
struct tagFACEINFO
{
	enum
	{
		TIME_FACE_ALLIVE = 5000,
	};

	CStringA		m_strName;
	string			m_strFileName;
	CRect			m_rcRegion;
	cv::Mat			m_matFace;
	EZ_SystemTime	m_ezTime;

	tagFACEINFO() : m_strName( "" ), m_strFileName( "" ), m_rcRegion( 0, 0, 0, 0 ), m_ezTime( FALSE )
	{
		m_matFace.release();
	}

	BOOL ComparePosition( LONG lLeft, LONG lTop, LONG lRight, LONG lBottom )
	{
		if( ( ::abs( lLeft - m_rcRegion.left ) <= 50 ) &&
			( ::abs( lTop - m_rcRegion.top ) <= 50 ) &&
			( ::abs( lRight - m_rcRegion.right ) <= 50 ) &&
			( ::abs( lBottom - m_rcRegion.bottom ) <= 50 ) )
			return TRUE; // Same Face

		return FALSE;
	}

	void UpdatePosition( LONG lLeft, LONG lTop, LONG lRight, LONG lBottom )
	{
		if( ( ::abs( lLeft - m_rcRegion.left ) > 25 ) ||
			( ::abs( lTop - m_rcRegion.top ) > 25 ) ||
			( ::abs( lRight - m_rcRegion.right ) > 25 ) ||
			( ::abs( lBottom - m_rcRegion.bottom ) > 25 ) )
			this->m_rcRegion.SetRect( lLeft, lTop, lRight, lBottom );
	}
};

typedef tagFACEINFO						FACEINFO;
typedef FACEINFO* LPFACEINFO;
typedef EZ_Vector_Array1< LPFACEINFO >	FACEINFOPTRARRAY;

//
class CFaceRecogEngineCallback
{
public:
	CFaceRecogEngineCallback() {}
	virtual void OnNoMatch( cv::Mat& matFace ) { ; }
};

typedef CFaceRecogEngineCallback	FACERECOGENGCB;
typedef CFaceRecogEngineCallback*	LPFACERECOGENGCB;

// CFaceRecogEngine
class CFaceRecogEngine : public EZ_Thread
{
public:
	enum EVENT
	{
		EVENT_RECOG = 0,
		EVENT_COUNT
	};

	typedef struct tagFACEDESC
	{
		string					m_strName;
		string					m_strFileName;
		matrix< rgb_pixel >		m_mtxChip;
		matrix< float, 0, 1 >	m_mtxFeature;
	} FACE_DESC;

	//
	shape_predictor				m_SP;
	anet_type					m_DNN;
	std::vector< FACE_DESC >	m_arrFaceDesc;

	//
	INT					m_iTextH;
	UINT				m_nFaceDetectCount;
	LPBYTE				m_pBuffer;
	LPFACERECOGENGCB	m_lpFaceEngCB;
	FACEINFOPTRARRAY	m_arrFaceInfoPtr;
	EZ_Mutex			m_mxFace;

	CFaceRecogEngine();
	explicit CFaceRecogEngine( int depth );
	~CFaceRecogEngine();

	int		LoadFaces( void );
	INT		DetectFace( cv::Mat& frame );
	void	InitDetectFace();

	inline void SetTextHeight( int iHeight ) { this->m_iTextH = iHeight; }
	inline void SetFaceRecogEngineCallback( LPFACERECOGENGCB lpCallback ) { this->m_lpFaceEngCB = lpCallback; }

protected:
	virtual void	Uninit();
	virtual void	Thread_Function();
	virtual void	DrawText( int iX, int iY, CStringA& strName, cv::Mat& frame );
	virtual void	DrawRect( cv::Mat& frame, int iLeft, int iTop, int iRight, int iBottom );
	virtual BOOL	RecognizeFace( LPFACEINFO lpFaceInfo );

};

extern CFaceRecogEngine g_oFaceEng;