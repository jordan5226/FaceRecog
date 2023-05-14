#include "StdAfx.h"
#include "EZ_MemoryBmp.h"

//  ==========================================================================
//  
//  ==========================================================================
EZ_MemoryBmp::EZ_MemoryBmp() : m_pBmpBuf( NULL ), m_hBitmap( NULL )
{
	::memset( &this->m_bmpHeader, 0, sizeof( BITMAPINFOHEADER ) );
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_MemoryBmp::~EZ_MemoryBmp()
{
	this->ReleaseBmp();
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_MemoryBmp& EZ_MemoryBmp::operator = ( const EZ_MemoryBmp& memBmp )
{
	if ( this != &memBmp )
	{
		this->m_pBmpBuf = memBmp.m_pBmpBuf;
		this->m_hBitmap = memBmp.m_hBitmap;

		::memcpy( &this->m_bmpHeader, &memBmp.m_bmpHeader, sizeof( BITMAPINFOHEADER ) );
	}

	return *this;
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_MemoryBmp& EZ_MemoryBmp::operator = ( LPCEZMEMORYBMP lpMemBmp )
{
	if ( lpMemBmp && ( this != lpMemBmp ) )
	{
		this->m_pBmpBuf = lpMemBmp->m_pBmpBuf;
		this->m_hBitmap = lpMemBmp->m_hBitmap;

		::memcpy( &this->m_bmpHeader, &lpMemBmp->m_bmpHeader, sizeof( BITMAPINFOHEADER ) );
	}

	return *this;
}

//  ==========================================================================
//  CreateBmp
//  ==========================================================================
C_BOOL EZ_MemoryBmp::CreateBmp( CDC* lpDC, LPCBITMAPINFO lpBitmap )
{
	this->ReleaseBmp();

	if ( lpBitmap )
	{
		HDC hDC = ( lpDC ? lpDC->GetSafeHdc() : NULL );

		{
			this->m_hBitmap = ::CreateDIBSection( hDC, lpBitmap, DIB_RGB_COLORS, ( void** )&this->m_pBmpBuf, NULL, 0 );

			::memcpy( &this->m_bmpHeader, &lpBitmap->bmiHeader, sizeof( BITMAPINFOHEADER ) );
		}
	}

	return ( this->m_hBitmap != NULL );
}

C_BOOL EZ_MemoryBmp::CreateBmp( CDC* lpDC, LPEZBITMAPINFO lpBitmap )
{
	this->ReleaseBmp();

	if ( lpBitmap )
	{
		HDC hDC = ( lpDC ? lpDC->GetSafeHdc() : NULL );

		{
			this->m_hBitmap = ::CreateDIBSection( hDC, ( LPBITMAPINFO )lpBitmap, DIB_RGB_COLORS, ( void** )&this->m_pBmpBuf, NULL, 0 );

			::memcpy( &this->m_bmpHeader, &lpBitmap->m_Header, sizeof( BITMAPINFOHEADER ) );
		}
	}

	return ( this->m_hBitmap != NULL );
}

C_BOOL EZ_MemoryBmp::CreateBmp( CDC* lpDC, C_INT iWidth, C_INT iHeight )
{
	this->ReleaseBmp();

	{
		this->m_hBitmap = ::CreateCompatibleBitmap( ( lpDC ? lpDC->GetSafeHdc() : NULL ), iWidth, iHeight );

		::SetBitmapHeader( this->m_bmpHeader, iWidth, iHeight, 24 );
	}

	return ( this->m_hBitmap != NULL );
}

C_BOOL EZ_MemoryBmp::CreateBmp( CDC* lpDC, C_INT iWidth, C_INT iHeight, C_INT iPlanes, C_INT iBitsPerPel, C_BOOL bDIBSection )
{
	this->ReleaseBmp();

	if ( bDIBSection )
	{	//  Creaet DIB Section Bitmap
		BITMAPINFO bmpInfo;

		::SetBitmapHeader( bmpInfo.bmiHeader, iWidth, iHeight, iBitsPerPel );

		return this->CreateBmp( lpDC, &bmpInfo );
	}
	else
	{	//  Creaet Normal Bitmap  
		this->m_hBitmap = ::CreateBitmap( iWidth, iHeight, iPlanes, iBitsPerPel, NULL );

		::SetBitmapHeader( this->m_bmpHeader, iWidth, iHeight, iBitsPerPel );

		return ( this->m_hBitmap != NULL );
	}
}

//  ==========================================================================
//  ReleaseBmp
//  ==========================================================================
void EZ_MemoryBmp::ReleaseBmp()
{
	SAFE_DELETE_OBJECT ( this->m_hBitmap );

	this->m_pBmpBuf = NULL;

	::memset( &this->m_bmpHeader, 0, sizeof( BITMAPINFOHEADER ) );
}
