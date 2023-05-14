#pragma once

#include <AfxWin.h>
#include <Vfw.h>

//  ==========================================================================
//  Defined
//  ==========================================================================
#if defined ( EZ_MY_PROJECT )

#include "..\EZDefined.h"

#else

#ifndef C_BYTE
#define C_BYTE  const BYTE;
#define LPBYTE        BYTE*;
#define LPCBYTE const BYTE*;
#endif

#ifndef C_BOOL
#define C_BOOL const BOOL;
#endif

#ifndef C_INT
#define C_INT const INT;
#endif

#ifndef C_BITMAPINFOHEADER
#define C_BITMAPINFOHEADER  const BITMAPINFOHEADER;
#define LPBITMAPINFOHEADER        BITMAPINFOHEADER*;
#define LPCBITMAPINFOHEADER const BITMAPINFOHEADER*;
#endif

#ifndef C_BITMAPINFO
#define C_BITMAPINFO  const BITMAPINFO;
#define LPBITMAPINFO        BITMAPINFO*;
#define LPCBITMAPINFO const BITMAPINFO*;
#endif

#ifndef C_CRECT
#define C_CRECT const CRect;
#endif

#endif

//  ==========================================================================
//  Global Function
//  ==========================================================================
extern C_BOOL CreateAlignedBuf( LPBYTE& lpData, C_INT iDataSize );
extern void   ReleaseAlignedBuf( LPBYTE& lpData );

extern BITMAPINFO* CreateBitmapInfoBuf( const int iWidth, const int iHeight, LPBYTE lpData, const BOOL bYUY2, const BOOL bTransRGB24 );
extern void        ReleaseBitmapInfoBuf( BITMAPINFO*& lpBitmapInfo );

extern void   SetBitmapHeader( BITMAPINFOHEADER& bmiHeader, C_INT iWidth, C_INT iHeight, C_INT iBitCount, C_INT iCompress = 0 );
extern void   SaveBmpFile( LPCSTR lpFileName, LPBYTE lpRgb, int iWidth, int iHeight );

//  ==========================================================================
//  EZ_BitmapInfo
//  ==========================================================================
struct EZ_BitmapInfo
{
	//  Variable
	union
	{
		BITMAPINFOHEADER m_Header;
		BYTE             m_Buffer[ 48 ];
	};

	BYTE m_Colors[ 1 ];

	//  Member
	EZ_BitmapInfo();
	~EZ_BitmapInfo();

	//  ==========================================================================
	//  Easy Function
	//  ==========================================================================
public:
	void SetBitmap( LPCBITMAPINFO lpBitmap )
	{
		this->SetHeader( &lpBitmap->bmiHeader );

		::memcpy( this->m_Colors, ( LPBYTE )lpBitmap->bmiColors, lpBitmap->bmiHeader.biSizeImage );
	}

	void SetBitmap( LPCBITMAPINFOHEADER lpHeader, LPCBYTE lpData )
	{
		this->SetHeader( lpHeader );

		::memcpy( this->m_Colors, lpData, lpHeader->biSizeImage );
	}

	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
public:
	inline void SetHeader( LPCBITMAPINFOHEADER lpHeader )
	{
		if ( lpHeader )
			::memcpy( &this->m_Header, lpHeader, sizeof( BITMAPINFOHEADER ) );
	}

	inline void SetHeader( C_BITMAPINFOHEADER& bmiHeader )
	{
		::memcpy( &this->m_Header, &bmiHeader, sizeof( BITMAPINFOHEADER ) );
	}

	inline void SetHeader( C_INT iWidth, C_INT iHeight, C_INT iBitCount )
	{
		::SetBitmapHeader( this->m_Header, iWidth, iHeight, iBitCount );
	}

	inline C_BOOL Render( HDRAWDIB hDibDraw, HDC hDC, C_CRECT& crDst, C_CRECT* lpSrc = NULL )
	{
		return EZ_BitmapInfo::Render( hDibDraw, hDC, &this->m_Header, this->m_Colors, crDst, lpSrc );
	}

	//  ==========================================================================
	//  Static Function
	//  ==========================================================================
public:
	static C_BOOL Render( HDRAWDIB hDibDraw, HDC hDC, LPBITMAPINFOHEADER lpHeader, LPBYTE lpData, C_CRECT& crDst, C_CRECT* lpSrc = NULL );

	static C_BOOL         CreateEZBitmapInfoBuf( EZ_BitmapInfo*& lpBitmapInfo, C_INT iColorsSize );
	static EZ_BitmapInfo* CreateEZBitmapInfoBuf( const int iWidth, const int iHeight, LPBYTE lpData, const BOOL bYUY2, const BOOL bTransRGB24 );
	static void           ReleaseEZBitmapInfoBuf( EZ_BitmapInfo*& lpBitmapInfo );

	static void LoadImage( LPCTSTR lpImgFile, BITMAPINFO*&    lpBitmap );
	static void LoadImage( LPCTSTR lpImgFile, EZ_BitmapInfo*& lpBitmap );
};

typedef const EZ_BitmapInfo  C_EZBITMAPINFO;
typedef       EZ_BitmapInfo* LPEZBITMAPINFO;
typedef const EZ_BitmapInfo* LPCEZBITMAPINFO;
