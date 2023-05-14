#pragma once

//  ==========================================================================
//   
//  ==========================================================================
#if defined ( _UNICODE )
#include "EZFunction_Unicode.h"
#else
#include "EZFunction_MultiByte.h"
#endif

#if ( defined ( _WIN32_WINNT ) || defined ( _WIN32_WINDOWS ) || defined ( _WINDOWS ) )
#include "EZWndFun.h"
#endif

//  ==========================================================================
//   
//  ==========================================================================
#ifndef C_CHAR
#define C_CHAR  const char
#endif

#ifndef C_BYTE
#define C_BYTE  const BYTE
#define LPCBYTE const BYTE*
#endif

#ifndef C_BOOL
#define C_BOOL  const BOOL
#define LPBOOL        BOOL*
#define LPCBOOL const LPBOOL
#endif

#ifndef C_WORD
#define C_WORD  const WORD
#define LPWORD        WORD*
#define LPCWORD const WORD*
#endif

#ifndef C_DWORD
#define C_DWORD  const DWORD
#define LPDWORD        DWORD*
#define LPCDWORD const DWORD*
#endif

#ifndef C_INT
#define C_INT  const INT
#define LPINT        INT*
#define LPCINT const INT*
#endif

#ifndef C_UINT
#define C_UINT  const UINT
#define LPUINT        UINT*
#define LPCUINT const UINT*
#endif

#ifndef C_INT32
#define C_INT32  const INT32
#define LPINT32        INT32*
#define LPCINT32 const INT32*
#endif

#ifndef C_UINT32
#define C_UINT32  const UINT32
#define LPUINT32        UINT32*
#define LPCUINT32 const UINT32*
#endif

#ifndef C_INT64
#define C_INT64  const INT64
#define LPINT64        INT64*
#define LPCINT64 const INT64*
#endif

#ifndef C_UINT64
#define C_UINT64  const UINT64
#define LPUINT64        UINT64*
#define LPCUINT64 const UINT64*
#endif

#ifndef C_LONG
#define C_LONG  const LONG
#define LPLONG        LONG*
#define LPCLONG const LONG*
#endif

#ifndef C_ULONG
#define C_ULONG  const ULONG
#define LPULONG        ULONG*
#define LPCULONG const ULONG*
#endif

#ifndef C_LONGLONG
#define C_LONGLONG  const LONGLONG
#define LPLONGLONG        LONGLONG*
#define LPCLONGLONG const LONGLONG*
#endif

#ifndef C_ULONGLONG
#define C_ULONGLONG  const ULONGLONG
#define LPULONGLONG        ULONGLONG*
#define LPCULONGLONG const ULONGLONG*
#endif

#ifndef C_FLOAT
#define C_FLOAT  const float
#define LPFLOAT        float*
#define LPCFLOAT const float*
#endif

#ifndef C_DOUBLE
#define C_DOUBLE  const double
#define LPDOUBLE        double*
#define LPCDOUBLE const double*
#endif

#ifndef C_SYSTEMTIME
#define C_SYSTEMTIME  const SYSTEMTIME
#define LPSYSTEMTIME        SYSTEMTIME*
#define LPCSYSTEMTIME const SYSTEMTIME*
#endif

#ifndef C_BITMAPINFOHEADER
#define C_BITMAPINFOHEADER  const BITMAPINFOHEADER
#define LPBITMAPINFOHEADER        BITMAPINFOHEADER*
#define LPCBITMAPINFOHEADER const BITMAPINFOHEADER*
#endif

#ifndef C_BITMAPINFO
#define C_BITMAPINFO  const BITMAPINFO
#define LPBITMAPINFO        BITMAPINFO*
#define LPCBITMAPINFO const BITMAPINFO*
#endif

typedef const COLORREF C_COLORREF;
typedef const RGBCOLOR C_RGBCOLOR;
typedef const HANDLE   C_HANDLE;
typedef const LRESULT  C_LRESULT;
typedef const HRESULT  C_HRESULT;
typedef const POINT    C_POINT;
typedef const RECT     C_RECT;

typedef       VOID** LPPVOID;
typedef const VOID** LPPCVOID;

//  ==========================================================================
//  Safe Delete
//  ==========================================================================
#ifndef SAFE_CLOSE_HANDLE
#define SAFE_CLOSE_HANDLE( p ) { if ( p ) { ::CloseHandle( p ); p = NULL; } }
#endif

#ifndef SAFE_DELETE_OBJECT
#define SAFE_DELETE_OBJECT( p ) { if ( p ) { ::DeleteObject( p ); p = NULL; } }
#endif

#ifndef SAFE_DELETE
#define DELETE_MEMORY( p ) { delete p; p = NULL; }
#define SAFE_DELETE( p )   { if ( p ) { DELETE_MEMORY( p ); } }
#endif

#ifndef SAFE_EMPTY_DELETE
#define SAFE_EMPTY_DELETE( p ) { if ( p ) { p->Empty(); delete p; p = NULL; } }
#endif

#ifndef SAFE_CLOSE_DELETE
#define SAFE_CLOSE_DELETE( p ) { if ( p ) { p->Close(); delete p; p = NULL; } }
#endif

#ifndef SAFE_RELEASE_DELETE
#define SAFE_RELEASE_DELETE( p ) { if ( p ) { p->Release(); delete p; p = NULL; } }
#endif

#ifndef SAFE_DISCONNECT_DELETE
#define SAFE_DISCONNECT_DELETE( p ) { if ( p ) { p->Disconnect(); delete p; p = NULL; } }
#endif

#ifndef SAFE_UNINIT_DELETE
#define SAFE_UNINIT_DELETE( p ) { if ( p ) { p->UnInit(); delete p; p = NULL; } }
#endif

#ifndef SAFE_UNINITIAL_DELETE
#define SAFE_UNINITIAL_DELETE( p ) { if ( p ) { p->UnInitial(); delete p; p = NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define DELETE_ARRAY_MEMORY( p ) { delete [] p; p = NULL; }
#define SAFE_DELETE_ARRAY( p )   { if ( p ) { DELETE_ARRAY_MEMORY( p ); } }
#endif

#ifndef SAFE_DELETE_ALIGNED
#define SAFE_DELETE_ALIGNED( p ) { if ( p ) { ::_aligned_free( p ); p = NULL; } }
#endif

#ifndef SAFE_FREE_LIB
#define SAFE_FREE_LIB( p ) { if ( p ) { ::FreeLibrary( p ); p = NULL; } }
#endif

//  ==========================================================================
//  Output Debug String
//  ==========================================================================
#ifdef _DEBUG

#define OUTPUTINFO( e )  { TRACE( e ); }
#define AFXCHECKMEMORY() {  ASSERT ( ::AfxCheckMemory()  ); }
#define CRTCHECKMEMORY() { _ASSERT ( ::_CrtCheckMemory() ); }
#define _USE_TRY_CATCH_  1

#elif _RSEDBG

#define OUTPUTINFO( e )  { ::OutputDebugString( e ); }
#define AFXCHECKMEMORY() {}
#define CRTCHECKMEMORY() {}
#define _USE_TRY_CATCH_  1

#else

#define OUTPUTINFO( e )  {}
#define AFXCHECKMEMORY() {}
#define CRTCHECKMEMORY() {}
#define _USE_TRY_CATCH_  1

#endif

//  ==========================================================================
//  Video Format
//  ==========================================================================
enum VIDEO_FORMAT
{
	VIDEO_FORMAT_UNKNOW = 0,
	VIDEO_FORMAT_RGB,
	VIDEO_FORMAT_MJPG,
	VIDEO_FORMAT_IR50,
	VIDEO_FORMAT_MPEG4,
	VIDEO_FORMAT_WMV3,
	VIDEO_FORMAT_EZX,
	VIDEO_FORMAT_EZV,
	VIDEO_FORMAT_MPEG2,
	VIDEO_FORMAT_MXPG,
	VIDEO_FORMAT_X264,
	VIDEO_FORMAT_XVID,
	VIDEO_FORMAT_X265,
	VIDEO_FORMAT_H265,
	VIDEO_FORMAT_NEWEST = 99,
};

typedef const VIDEO_FORMAT C_VIDEO_FORMAT;

//  ==========================================================================
//  Audio Format
//  ==========================================================================
enum AUDIO_FORMAT
{
	AUDIO_FORMAT_UNKNOW = 0,
	AUDIO_FORMAT_PCM,
	AUDIO_FORMAT_ADPCM,
	AUDIO_FORMAT_MP3,
	AUDIO_FORMAT_NEWEST = 99,
};

typedef const AUDIO_FORMAT C_AUDIO_FORMAT;

//  ==========================================================================
//  Video Size
//  ==========================================================================
enum VIDEO_FRAME_SIZE
{
	VIDEO_SIZE_320x120 = 0,
	VIDEO_SIZE_320x240,
	VIDEO_SIZE_352x120,
	VIDEO_SIZE_352x240,
	VIDEO_SIZE_352x144,
	VIDEO_SIZE_352x288,
	VIDEO_SIZE_360x120,
	VIDEO_SIZE_360x240,
	VIDEO_SIZE_360x144,
	VIDEO_SIZE_360x288,
	VIDEO_SIZE_480x360,
	VIDEO_SIZE_640x240,
	VIDEO_SIZE_640x480,
	VIDEO_SIZE_704x240,
	VIDEO_SIZE_704x480,
	VIDEO_SIZE_704x288,
	VIDEO_SIZE_704x576,
	VIDEO_SIZE_720x240,
	VIDEO_SIZE_720x480,
	VIDEO_SIZE_720x288,
	VIDEO_SIZE_720x576,
	VIDEO_SIZE_1280x720,
	VIDEO_SIZE_1280x960,
	VIDEO_SIZE_1280x1024,
	VIDEO_SIZE_1600x1200,
	VIDEO_SIZE_1920x1080,
	VIDEO_SIZE_1920x1200,
	VIDEO_SIZE_2560x1600,
	VIDEO_SIZE_2592x1944,
	VIDEO_SIZE_UNKNOW,
	VIDEO_SIZE_COUNT,
};

typedef const VIDEO_FRAME_SIZE C_VIDEO_FRAME_SIZE;

//  ==========================================================================
//  Item Flag
//  ==========================================================================
enum ITEM_FLAG
{
	ITEM_FLAG_FAILED = -1,
	ITEM_FLAG_DELETE = 0,
	ITEM_FLAG_EXIST,
	ITEM_FLAG_NOT_EXIST,
	ITEM_FLAG_READ,
	ITEM_FLAG_LOCKED,
	ITEM_FLAG_BACKUPING,
	ITEM_FLAG_RECORDING,
	ITEM_FLAG_UNLOCK,
	ITEM_FLAG_RECYCLED,
	ITEM_FLAG_COUNT,
};

typedef const ITEM_FLAG C_ITEM_FLAG;

//  ==========================================================================
//  File Flag
//  ==========================================================================
enum FILE_FLAG
{
	FILE_FLAG_AVI = 0,
	FILE_FLAG_AUD,
	FILE_FLAG_MPG,
	FILE_FLAG_VID,
	FILE_FLAG_UNKNOW,
	FILE_FLAG_COUNT,
};

typedef const FILE_FLAG C_FILE_FLAG;

//  ==========================================================================
//  File Flag
//  ==========================================================================
enum BACKUP_FILE_TYPE
{
	BACKUP_FT_OBJECT_INDEX = ( FILE_FLAG_UNKNOW + 1 ),
	BACKUP_FT_MDB_FILES,
	BACKUP_FT_LOG_FILES,
	BACKUP_FT_COPY_FILES,
	BACKUP_FT_COPY_FOLDER,
	BACKUP_FT_COPY_PREV_FOLDER,
	BACKUP_FT_AVI_FILE,
	BACKUP_FT_WAVE_FILE,
	BACKUP_FT_BOOKMARK, 
	BACKUP_FT_FACE_FILE,
	BACKUP_FT_MDB_AIJPG,
};

typedef const BACKUP_FILE_TYPE C_BACKUPFT;

//  ==========================================================================
//  Key
//  ==========================================================================
#define VK_NUM0 0x30
#define VK_NUM1 0x31
#define VK_NUM2 0x32
#define VK_NUM3 0x33
#define VK_NUM4 0x34
#define VK_NUM5 0x35
#define VK_NUM6 0x36
#define VK_NUM7 0x37
#define VK_NUM8 0x38
#define VK_NUM9 0x39
#define VK_A    0x41
#define VK_B    0x42
#define VK_C    0x43
#define VK_D    0x44
#define VK_E    0x45
#define VK_F    0x46
#define VK_G    0x47
#define VK_H    0x48
#define VK_I    0x49
#define VK_J    0x4a
#define VK_K    0x4b
#define VK_L    0x4c
#define VK_M    0x4d
#define VK_N    0x4e
#define VK_O    0x4f
#define VK_P    0x50
#define VK_Q    0x51
#define VK_R    0x52
#define VK_S    0x53
#define VK_T    0x54
#define VK_U    0x55
#define VK_V    0x56
#define VK_W    0x57
#define VK_X    0x58
#define VK_Y    0x59
#define VK_Z    0x5a

#define VK_ADD_TEXT      '+'
#define VK_SUBTRACT_TEXT '-'
#define VK_MULTIPLY_TEXT '*'
#define VK_DIVIDE_TEXT   '/'

//  ==========================================================================
//  Other Define
//  ==========================================================================
#define DEFAULT_FRAME_SIZE         (  720 *  576 * 3 )
#define MAX_FRAME_SIZE             ( 2592 * 1944 * 3 )
#define EXTEND_VIDEO_BUFFER        5120
#define EXTEND_AUDIO_BUFFER        2048
#define PACKDB_WRITE_ITEM_PER_TIME 100

//  ==========================================================================
//  FourCC Value
//  ==========================================================================
#define FOURCC_IV50  808801865	//  MAKEFOURCC( 'I', 'V', '5', '0' )
#define FOURCC_Iv50  808810057	//  MAKEFOURCC( 'I', 'v', '5', '0' )
#define FOURCC_iv50  808810089	//  MAKEFOURCC( 'i', 'v', '5', '0' )

#define FOURCC_WMV3  861293911	//  MAKEFOURCC( 'W', 'M', 'V', '3' )
#define FOURCC_wmv3  863399287	//  MAKEFOURCC( 'w', 'm', 'v', '3' )

#define FOURCC_XVID 1145656920	//  MAKEFOURCC( 'X', 'V', 'I', 'D' )
#define FOURCC_XVid 1684624984	//  MAKEFOURCC( 'X', 'V', 'i', 'd' )
#define FOURCC_xvid 1684633208	//  MAKEFOURCC( 'x', 'v', 'i', 'd' )

#define FOURCC_MPG4  877088845	//  MAKEFOURCC( 'M', 'P', 'G', '4' )
#define FOURCC_Mpg4  879194189	//  MAKEFOURCC( 'M', 'p', 'g', '4' )
#define FOURCC_mpg4  879194221	//  MAKEFOURCC( 'm', 'p', 'g', '4' )
#define FOURCC_MP42  842289229	//  MAKEFOURCC( 'M', 'P', '4', '2' )

#define FOURCC_MJPG 1196444237	//  MAKEFOURCC( 'M', 'J', 'P', 'G' )
#define FOURCC_MJpg 1735412301	//  MAKEFOURCC( 'M', 'J', 'p', 'g' )
#define FOURCC_Mjpg 1735420493	//  MAKEFOURCC( 'M', 'j', 'p', 'g' )
#define FOURCC_mjpg 1735420525	//  MAKEFOURCC( 'm', 'j', 'p', 'g' )

#define FOURCC_MXPG 1196447821	//  MAKEFOURCC( 'M', 'X', 'P', 'G' )
#define FOURCC_Mxpg 1735424077	//  MAKEFOURCC( 'M', 'x', 'p', 'g' )
#define FOURCC_mxpg 1735424109	//  MAKEFOURCC( 'm', 'x', 'p', 'g' )

#define FOURCC_X264  875967064	//  MAKEFOURCC( 'X', '2', '6', '4' )
#define FOURCC_x264  875967096	//  MAKEFOURCC( 'x', '2', '6', '4' )

#define FOURCC_HEVC 1129727304	//  MAKEFOURCC( 'H', 'E', 'V', 'C' )
#define FOURCC_hevc 1668703592	//  MAKEFOURCC( 'h', 'e', 'v', 'c' )

#define FOURCC_X265 892744280	//  MAKEFOURCC( 'X', '2', '6', '5' )
#define FOURCC_x265 892744312	//  MAKEFOURCC( 'x', '2', '6', '5' )

#define FOURCC_MP3	0x4148		//  MAKEFOURCC( 'M', 'P', '3', '.' )
#define FOURCC_PCM	0x0000		//  MAKEFOURCC( 'P', 'C', 'M', '.' )

//  ==========================================================================
//  Get Video Codec
//  ==========================================================================
inline VIDEO_FORMAT Get_Video_Codec( C_UINT fccHandler )
{
	switch ( fccHandler )
	{
	case FOURCC_X265:	//  X-265 ( v15.10 Support )
	case FOURCC_x265:
		return VIDEO_FORMAT_X265;

	case FOURCC_X264:	//  X-264 ( v8.5.0.0 Support )
	case FOURCC_x264:
		return VIDEO_FORMAT_X264;

	case FOURCC_XVID:	//  X-Vid ( v8.5.0.0 Support )
	case FOURCC_XVid:
	case FOURCC_xvid:
		return VIDEO_FORMAT_XVID;

	case FOURCC_WMV3:	//  WMV3 ( v8.5.0.0 Support )
	case FOURCC_wmv3: 
		return VIDEO_FORMAT_WMV3;

	case FOURCC_MXPG:	//  Mx-Jpeg ( v8.4.0.0 Support )
	case FOURCC_Mxpg:
	case FOURCC_mxpg:
		return VIDEO_FORMAT_MXPG;

	case FOURCC_MPG4:	//  EZ-Mpeg4 ( v6.0.0.0 Support )
	case FOURCC_Mpg4:
	case FOURCC_mpg4:
	case FOURCC_MP42:
		return VIDEO_FORMAT_MPEG4;

	case FOURCC_IV50:	//  IR-50 ( Wavelet, v6.0.0.0 Support )
	case FOURCC_Iv50:
	case FOURCC_iv50:
		return VIDEO_FORMAT_IR50;

	case FOURCC_MJPG:	//  Motion-Jpg ( v6.0.0.0 Support )
	case FOURCC_MJpg:
	case FOURCC_Mjpg:
	case FOURCC_mjpg:
		return VIDEO_FORMAT_MJPG;

	case 0:				//  UnKnow
		return VIDEO_FORMAT_UNKNOW;

	default:			//  Newest
		return VIDEO_FORMAT_NEWEST;
	}
}

//  ==========================================================================
//  Get Audio Codec
//  ==========================================================================
inline AUDIO_FORMAT Get_Audio_Codec( C_UINT uiFormatTag )
{
	switch ( uiFormatTag )
	{
	case FOURCC_MP3:			//  MP3
		return AUDIO_FORMAT_MP3;

	case WAVE_FORMAT_IMA_ADPCM:	//  ADPCM
		return AUDIO_FORMAT_ADPCM;

	case FOURCC_PCM:			//  PCM
		return AUDIO_FORMAT_PCM;

	default:					//  UnKnow
		return AUDIO_FORMAT_UNKNOW;
	}
}

//  ==========================================================================
//  Get Video Frame Size
//  ==========================================================================
inline VIDEO_FRAME_SIZE Get_Video_Frame_Size( LPCBITMAPINFOHEADER lpHeader )
{
	VIDEO_FRAME_SIZE videoSize = VIDEO_SIZE_UNKNOW;

	if ( lpHeader )
	{
		switch ( lpHeader->biWidth )
		{
		default:
			{
				videoSize = ( ( lpHeader->biWidth == 320 ) ? VIDEO_SIZE_320x240 : VIDEO_SIZE_UNKNOW );
			}
			break;

		case 352:
			{
				if ( lpHeader->biHeight == 288 )
					videoSize = VIDEO_SIZE_352x288;
				else if ( lpHeader->biHeight == 240 )
					videoSize = VIDEO_SIZE_352x240;
				else if ( lpHeader->biHeight == 144 )
					videoSize = VIDEO_SIZE_352x144;
				else if ( lpHeader->biHeight == 120 )
					videoSize = VIDEO_SIZE_352x120;
			}
			break;

		case 360:
			{
				if ( lpHeader->biHeight == 288 )
					videoSize = VIDEO_SIZE_360x288;
				else if ( lpHeader->biHeight == 240 )
					videoSize = VIDEO_SIZE_360x240;
				else if ( lpHeader->biHeight == 144 )
					videoSize = VIDEO_SIZE_360x144;
				else if ( lpHeader->biHeight == 120 )
					videoSize = VIDEO_SIZE_360x120;
			}
			break;

		case 480:
			{
				videoSize = ( ( lpHeader->biHeight == 360 ) ? VIDEO_SIZE_480x360 : VIDEO_SIZE_UNKNOW );
			}
			break;

		case 640:
			{
				if ( lpHeader->biHeight == 480 )
					videoSize = VIDEO_SIZE_640x480;
				else if ( lpHeader->biHeight == 240 )
					videoSize = VIDEO_SIZE_640x240;
			}
			break;

		case 704:  //  Stand Along Format
			{
				if ( lpHeader->biHeight == 576 )
					videoSize = VIDEO_SIZE_704x576;
				else if ( lpHeader->biHeight == 480 )
					videoSize = VIDEO_SIZE_704x480;
				else if ( lpHeader->biHeight == 288 )
					videoSize = VIDEO_SIZE_704x288;
				else if ( lpHeader->biHeight == 240 )
					videoSize = VIDEO_SIZE_704x240;
			}
			break;

		case 720:  
			{
				if ( lpHeader->biHeight == 576 )
					videoSize = VIDEO_SIZE_720x576;
				else if ( lpHeader->biHeight == 480 )
					videoSize = VIDEO_SIZE_720x480;
				else if ( lpHeader->biHeight == 288 )
					videoSize = VIDEO_SIZE_720x288;
				else if ( lpHeader->biHeight == 240 )
					videoSize = VIDEO_SIZE_720x240;
			}
			break;

		case 1280: // EZ-IP Format
			{
				if ( lpHeader->biHeight == 1024 )
					videoSize = VIDEO_SIZE_1280x1024;
				else if ( lpHeader->biHeight == 960 )
					videoSize = VIDEO_SIZE_1280x960;
				else if ( lpHeader->biHeight == 720 )
					videoSize = VIDEO_SIZE_1280x720;
			}
			break;

		case 1600: // EZ-IP Format
			{
				videoSize = ( ( lpHeader->biHeight == 1200 ) ? VIDEO_SIZE_1600x1200 : VIDEO_SIZE_UNKNOW );
			}
			break;

		case 1920: // EZ-IP Format
			{
				if ( lpHeader->biHeight == 1200 )
					videoSize = VIDEO_SIZE_1920x1200;
				else if ( lpHeader->biHeight == 1080 )
					videoSize = VIDEO_SIZE_1920x1080;
			}
			break;

		case 2560: // EZ-IP Format
			{
				videoSize = ( ( lpHeader->biHeight == 1600 ) ? VIDEO_SIZE_2560x1600 : VIDEO_SIZE_UNKNOW );
			}
			break;

		case 2592: // EZ-IP Format
			{
				videoSize = ( ( lpHeader->biHeight == 1944 ) ? VIDEO_SIZE_2592x1944 : VIDEO_SIZE_UNKNOW );
			}
			break;
		}
	}

	return videoSize;
}
