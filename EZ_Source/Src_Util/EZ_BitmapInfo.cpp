#include "stdafx.h"
#include "EZ_BitmapInfo.h"

#if defined ( _USE_GDI_PLUS_DLL_ )
#include <AtlImage.h>
#endif

#if defined ( _SUPPORT_DDRAW_TRANS_FUNCTION_ )
#include "..\Dll_DDraw\EZDDrawLoader.h"
#endif

//  ==========================================================================
//  
//  ==========================================================================
#pragma comment( lib, "Vfw32.lib" )

//  ==========================================================================
//  
//  ==========================================================================
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//  ==========================================================================
//  SaveBmpFile
//  ==========================================================================
void SaveBmpFile( LPCSTR lpFileName, LPBYTE lpRgb, int iWidth, int iHeight )
{
	//  
	unsigned char szFileHeader[ 54 ] = 
	{
		0x42, 0x4D, 0xCA, 0x90, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	};

	szFileHeader[  0 ] = 0x42; szFileHeader[  1 ] = 0x4D; szFileHeader[  2 ] = 0xCA; szFileHeader[  3 ] = 0x90;
	szFileHeader[  4 ] = 0x02; szFileHeader[  5 ] = 0x00; szFileHeader[  6 ] = 0x00; szFileHeader[  7 ] = 0x00;
	szFileHeader[  8 ] = 0x00; szFileHeader[  9 ] = 0x00; szFileHeader[ 10 ] = 0x36; szFileHeader[ 11 ] = 0x00;
	szFileHeader[ 12 ] = 0x00; szFileHeader[ 13 ] = 0x00;

	//  
	BITMAPINFOHEADER* lpBmpHeader = ( BITMAPINFOHEADER* )( szFileHeader + 14 );

	::memset( ( LPBYTE )lpBmpHeader, 0, sizeof( BITMAPINFOHEADER ) );

	lpBmpHeader->biWidth     = iWidth;
	lpBmpHeader->biHeight    = iHeight;
	lpBmpHeader->biBitCount  = 24;
	lpBmpHeader->biPlanes    = 1;
	lpBmpHeader->biSize      = 40;
	lpBmpHeader->biSizeImage = ( lpBmpHeader->biWidth * lpBmpHeader->biHeight * ( lpBmpHeader->biBitCount / 8 ) );

	//  
	FILE* fp = NULL;

	if ( ( ::fopen_s( &fp, lpFileName, "wb" ) == 0 ) && fp )
	{
		::fwrite( szFileHeader, 1, 54, fp );
		::fwrite( lpRgb, 1, lpBmpHeader->biSizeImage, fp );
		::fclose( fp );
	}
}

//  ==========================================================================
//  SetBitmapHeader ( Global )
//  ==========================================================================
void SetBitmapHeader( BITMAPINFOHEADER& bmiHeader, C_INT iWidth, C_INT iHeight, C_INT iBitCount, C_INT iCompress )
{
	::memset( &bmiHeader, 0, sizeof( BITMAPINFOHEADER ) );

	bmiHeader.biSize        = sizeof( BITMAPINFOHEADER );
	bmiHeader.biWidth       = iWidth;
	bmiHeader.biHeight      = iHeight;
	bmiHeader.biPlanes      = 1;
	bmiHeader.biBitCount    = iBitCount;
	bmiHeader.biCompression = iCompress;
	bmiHeader.biSizeImage   = ( iWidth * iHeight * ( iBitCount >> 3 ) );
}

//  ==========================================================================
//  CreateAlignedBuf ( Global )
//  ==========================================================================
C_BOOL CreateAlignedBuf( LPBYTE& lpData, C_INT iDataSize )
{
	//
	::ReleaseAlignedBuf( lpData );

	//
#ifdef _USE_TRY_CATCH_
	try
	{
#endif

#if _MSC_VER > 1300
#ifdef _DEBUG
		lpData = ( LPBYTE )( _aligned_malloc_dbg( iDataSize, 16, NULL, 0 ) );
#else
		lpData = ( LPBYTE )( _aligned_malloc( iDataSize, 16 ) );
#endif
#else
		lpData = new BYTE [ iDataSize ];
#endif

		return ( lpData != NULL );

#ifdef _USE_TRY_CATCH_
	}
	catch ( ... )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_BitmapInfo ] CreateAlignedBuf - Fail !\n" ) );
		return FALSE;
	}
#endif
}

//  ==========================================================================
//  ReleaseAlignedBuf ( Global )
//  ==========================================================================
void ReleaseAlignedBuf( LPBYTE& lpData )
{
	if ( lpData )
	{
#ifdef _USE_TRY_CATCH_
		try
		{
#endif

#if _MSC_VER > 1300
#ifdef _DEBUG
			_aligned_free_dbg( ( void* )lpData );
#else
			_aligned_free( ( void* )lpData );
#endif
#else
			delete [] lpData;
#endif

#ifdef _USE_TRY_CATCH_
		}
		catch ( ... )
		{
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_BitmapInfo ] ReleaseAlignedBuf - Fail !\n" ) );
		}
#endif

		lpData = NULL;
	}
}

//  ==========================================================================
//  CreateBitmapInfoBuf ( Global )
//  ==========================================================================
BITMAPINFO* CreateBitmapInfoBuf( const int iWidth, const int iHeight, LPBYTE lpData, const BOOL bYUY2, const BOOL bTransRGB24 )
{
	const int   iBasicSize   = ( iWidth * iHeight );
	BITMAPINFO* lpBitmapInfo = NULL;

	if ( !bYUY2 )
	{	//  RGB24 Data
		const int iColorsSize = ( iBasicSize * 3 );

		if ( ::CreateAlignedBuf( ( LPBYTE& )lpBitmapInfo, ( iColorsSize + 48 ) ) )
		{
			::SetBitmapHeader( lpBitmapInfo->bmiHeader, iWidth, iHeight, 24 ); lpBitmapInfo->bmiHeader.biClrImportant = 0;

			if ( lpData ) ::memcpy_s( lpBitmapInfo->bmiColors, iColorsSize, lpData, iColorsSize );
		}
	}
	else if ( bTransRGB24 )
	{	//  YUY2 Trans RGB24 Data
#if defined ( _SUPPORT_DDRAW_TRANS_FUNCTION_ )
		const int iColorsSize = ( iBasicSize * 3 );

		if ( ::CreateAlignedBuf( ( LPBYTE& )lpBitmapInfo, ( iColorsSize + 48 ) ) )
		{
			::SetBitmapHeader( lpBitmapInfo->bmiHeader, iWidth, iHeight, 24 ); lpBitmapInfo->bmiHeader.biClrImportant = 0;

			if ( lpData ) EZDDrawV2Dll::ColorTransYUY2toRGB24( iWidth, iHeight, lpData, ( LPBYTE )lpBitmapInfo->bmiColors );
		}
#endif
	}
	else
	{	//  YUY2 Data
		const int iColorsSize = ( iBasicSize * 2 );

		if ( ::CreateAlignedBuf( ( LPBYTE& )lpBitmapInfo, ( iColorsSize + 48 ) ) )
		{
			::SetBitmapHeader( lpBitmapInfo->bmiHeader, iWidth, iHeight, 24 ); lpBitmapInfo->bmiHeader.biClrImportant = 5;

			if ( lpData ) ::memcpy_s( lpBitmapInfo->bmiColors, iColorsSize, lpData, iColorsSize );
		}
	}

	return lpBitmapInfo;
}

//  ==========================================================================
//  ReleaseBitmapInfoBuf ( Global )
//  ==========================================================================
void ReleaseBitmapInfoBuf( BITMAPINFO*& lpBitmapInfo )
{
	LPBYTE lpData = ( LPBYTE )lpBitmapInfo;

	::ReleaseAlignedBuf( lpData );

	lpBitmapInfo = NULL;
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_BitmapInfo::EZ_BitmapInfo()
{
	::memset( this, 0, sizeof( EZ_BitmapInfo ) );
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_BitmapInfo::~EZ_BitmapInfo()
{
	;
}

//  ==========================================================================
//  Render ( Static )
//  ==========================================================================
C_BOOL EZ_BitmapInfo::Render( HDRAWDIB hDibDraw, HDC hDC, LPBITMAPINFOHEADER lpHeader, LPBYTE lpData, C_CRECT& crDst, C_CRECT* lpSrc )
{
	ASSERT ( hDibDraw && hDC && lpHeader && lpData );

#ifdef _USE_TRY_CATCH_
	try
	{
#endif

		CRect crSource( 0, 0, lpHeader->biWidth, lpHeader->biHeight );

		if ( lpSrc )
		{
			INT iWidth = lpSrc->Width(), iHeight = lpSrc->Height();

			if ( ( lpSrc->left >= 0 ) && ( lpSrc->top >= 0 ) && ( iWidth <= lpHeader->biWidth ) && ( iHeight <= lpHeader->biHeight ) )
				crSource.SetRect( lpSrc->left, lpSrc->top, iWidth, iHeight );
			else
			{
				ASSERT ( 0 );
			}
		}

		return ::DrawDibDraw( hDibDraw, hDC, crDst.left, crDst.top, crDst.Width(), crDst.Height(), 
			lpHeader, lpData, crSource.left, crSource.top, crSource.right, crSource.bottom, 0 );

#ifdef _USE_TRY_CATCH_
	}
	catch ( ... )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_BitmapInfo ] Render - Fail !\n" ) );
		return FALSE;
	}
#endif
}

//  ==========================================================================
//  CreateEZBitmapInfoBuf ( Static )
//  ==========================================================================
C_BOOL EZ_BitmapInfo::CreateEZBitmapInfoBuf( LPEZBITMAPINFO& lpBitmap, C_INT iColorsSize )
{
	//  
	EZ_BitmapInfo::ReleaseEZBitmapInfoBuf( lpBitmap );

	//  
	LPBYTE lpData = NULL;
	
	if ( ::CreateAlignedBuf( lpData, ( iColorsSize + 48 ) ) )
	{
		lpBitmap = ( LPEZBITMAPINFO )lpData;
		return TRUE;
	}
	else
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_BitmapInfo ] CreateEZBitmapInfoBuf - Fail !\n" ) );
		return FALSE;
	}
}

EZ_BitmapInfo* EZ_BitmapInfo::CreateEZBitmapInfoBuf( const int iWidth, const int iHeight, LPBYTE lpData, const BOOL bYUY2, const BOOL bTransRGB24 )
{
	const int      iBasicSize   = ( iWidth * iHeight );
	EZ_BitmapInfo* lpBitmapInfo = NULL;

	if ( !bYUY2 )
	{	//  RGB24 Data
		const int iColorsSize = ( iBasicSize * 3 );

		if ( EZ_BitmapInfo::CreateEZBitmapInfoBuf( lpBitmapInfo, iColorsSize ) )
		{
			lpBitmapInfo->SetHeader( iWidth, iHeight, 24 ); lpBitmapInfo->m_Header.biClrImportant = 0;

			if ( lpData ) ::memcpy_s( lpBitmapInfo->m_Colors, iColorsSize, lpData, iColorsSize );
		}
	}
	else if ( bTransRGB24 )
	{	//  YUY2 Trans RGB24 Data
#if defined ( _SUPPORT_DDRAW_TRANS_FUNCTION_ )
		const int iColorsSize = ( iBasicSize * 3 );

		if ( EZ_BitmapInfo::CreateEZBitmapInfoBuf( lpBitmapInfo, iColorsSize ) )
		{
			lpBitmapInfo->SetHeader( iWidth, iHeight, 24 ); lpBitmapInfo->m_Header.biClrImportant = 0;

			if ( lpData ) EZDDrawV2Dll::ColorTransYUY2toRGB24( iWidth, iHeight, lpData, lpBitmapInfo->m_Colors );
		}
#endif
	}
	else
	{	//  YUY2 Data
		const int iColorsSize = ( iBasicSize * 2 );

		if ( EZ_BitmapInfo::CreateEZBitmapInfoBuf( lpBitmapInfo, iColorsSize ) )
		{
			lpBitmapInfo->SetHeader( iWidth, iHeight, 24 ); lpBitmapInfo->m_Header.biClrImportant = 5;

			if ( lpData ) ::memcpy_s( lpBitmapInfo->m_Colors, iColorsSize, lpData, iColorsSize );
		}
	}

	return lpBitmapInfo;
}

//  ==========================================================================
//  ReleaseEZBitmapInfoBuf ( Static )
//  ==========================================================================
void EZ_BitmapInfo::ReleaseEZBitmapInfoBuf( LPEZBITMAPINFO& lpBitmap )
{
	LPBYTE lpData = ( LPBYTE )lpBitmap;

	::ReleaseAlignedBuf( lpData );

	lpBitmap = NULL;
}

//  ==========================================================================
//  LoadImage ( Static )
//  ==========================================================================
void EZ_BitmapInfo::LoadImage( LPCTSTR lpImgFile, BITMAPINFO*& lpBitmap )
{
	//  Free Old
	if ( lpBitmap )
	{
		LPBYTE lpBmpTmp = ( LPBYTE )lpBitmap;

		SAFE_DELETE_ARRAY ( lpBmpTmp );

		lpBitmap = NULL;
	}

	//  Load and Alloc New
#if defined ( _USE_GDI_PLUS_DLL_ )
	CImage objImage;

	if ( SUCCEEDED ( objImage.Load( lpImgFile ) ) )
	{  
		C_INT  iWidth     = objImage.GetWidth();
		C_INT  iHeight    = objImage.GetHeight();
		C_INT  iBitCount  = objImage.GetBPP();
		C_INT  iPitch     = objImage.GetPitch();
		C_INT  iLineBytes = ( iWidth * ( iBitCount >> 3 ) );
		C_INT  iImgSize   = ( iLineBytes * iHeight );
		LPVOID lpBits     = objImage.GetBits();

#ifdef _USE_TRY_CATCH_
		try
		{
#endif

			lpBitmap = ( BITMAPINFO* )( new BYTE [ ( iImgSize + sizeof( BITMAPINFOHEADER ) ) ] );

			if ( lpBitmap )
			{
				//  
				::SetBitmapHeader( lpBitmap->bmiHeader, iWidth, iHeight, iBitCount );

				//  GetPitch() 如果是負數，則點陣圖為由下而上的 DIB，而且其原點位於左下角。如果是正數，則點陣圖為由上而下的 DIB，而且其原點是左上角。
				//  GetBits() 取得點陣圖之緩衝區指標。如果點陣圖為由下而上 DIB，從緩衝區的結尾的索引點。如果點陣圖為由上而下的 DIB，緩衝區的第一個位元組的索引點。
				if ( iPitch >= 0 )
					::memcpy_s( lpBitmap->bmiColors, iImgSize, lpBits, iImgSize );
				else
				{
					LPBYTE lpDstBuf = ( LPBYTE )lpBitmap->bmiColors, lpSrcBuf = ( LPBYTE )lpBits;

					for ( INT iLine = 0; iLine < iHeight; iLine++ )
					{
						::memcpy_s( lpDstBuf, iLineBytes, lpSrcBuf, iLineBytes );

						lpDstBuf += iLineBytes;
						lpSrcBuf -= iLineBytes;
					}
				}			
			}

#ifdef _USE_TRY_CATCH_
		}
		catch ( ... )
		{
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_BitmapInfo ] LoadImage - Fail !\n" ) );
		}
#endif
	}
#endif
}

void EZ_BitmapInfo::LoadImage( LPCTSTR lpImgFile, EZ_BitmapInfo*& lpBitmap )
{
	//  Free Old
	if ( lpBitmap )
	{
		LPBYTE lpBmpTmp = ( LPBYTE )lpBitmap;

		SAFE_DELETE_ARRAY ( lpBmpTmp );

		lpBitmap = NULL;
	}

	//  Load and Alloc New
#if defined ( _USE_GDI_PLUS_DLL_ )
	CImage objImage;

	if ( SUCCEEDED ( objImage.Load( lpImgFile ) ) )
	{  
		C_INT  iWidth     = objImage.GetWidth();
		C_INT  iHeight    = objImage.GetHeight();
		C_INT  iBitCount  = objImage.GetBPP();
		C_INT  iPitch     = objImage.GetPitch();
		C_INT  iLineBytes = ( iWidth * ( iBitCount >> 3 ) );
		C_INT  iImgSize   = ( iLineBytes * iHeight );
		LPVOID lpBits     = objImage.GetBits();

#ifdef _USE_TRY_CATCH_
		try
		{
#endif

			lpBitmap = ( EZ_BitmapInfo* )( new BYTE [ ( iImgSize + 48 ) ] );

			if ( lpBitmap )
			{
				//  
				::SetBitmapHeader( lpBitmap->m_Header, iWidth, iHeight, iBitCount );

				//  GetPitch() 如果是負數，則點陣圖為由下而上的 DIB，而且其原點位於左下角。如果是正數，則點陣圖為由上而下的 DIB，而且其原點是左上角。
				//  GetBits() 取得點陣圖之緩衝區指標。如果點陣圖為由下而上 DIB，從緩衝區的結尾的索引點。如果點陣圖為由上而下的 DIB，緩衝區的第一個位元組的索引點。
				if ( iPitch >= 0 )
					::memcpy_s( lpBitmap->m_Colors, iImgSize, lpBits, iImgSize );
				else
				{
					LPBYTE lpDstBuf = ( LPBYTE )lpBitmap->m_Colors, lpSrcBuf = ( LPBYTE )lpBits;

					for ( INT iLine = 0; iLine < iHeight; iLine++ )
					{
						::memcpy_s( lpDstBuf, iLineBytes, lpSrcBuf, iLineBytes );

						lpDstBuf += iLineBytes;
						lpSrcBuf -= iLineBytes;
					}
				}			
			}

#ifdef _USE_TRY_CATCH_
		}
		catch ( ... )
		{
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_BitmapInfo ] LoadImage - Fail !\n" ) );
		}
#endif
	}
#endif
}
