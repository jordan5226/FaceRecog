#pragma once

#include "..\EZ_BitmapInfo.h"

//  ==========================================================================
//  Memory Bitmap
//  ==========================================================================
class EZ_MemoryBmp
{
public:
	LPBYTE           m_pBmpBuf;
	HBITMAP          m_hBitmap;
	BITMAPINFOHEADER m_bmpHeader;

public:
	EZ_MemoryBmp();
	virtual ~EZ_MemoryBmp();

	EZ_MemoryBmp& operator = ( const EZ_MemoryBmp&   memBmp );
	EZ_MemoryBmp& operator = ( const EZ_MemoryBmp* lpMemBmp );

	virtual C_BOOL CreateBmp( CDC* lpDC, LPCBITMAPINFO lpBitmap );
	virtual C_BOOL CreateBmp( CDC* lpDC, LPEZBITMAPINFO lpBitmap );
	virtual C_BOOL CreateBmp( CDC* lpDC, C_INT iWidth, C_INT iHeight );
	virtual C_BOOL CreateBmp( CDC* lpDC, C_INT iWidth, C_INT iHeight, C_INT iPlanes, C_INT iBitsPerPel, C_BOOL bDIBSection = FALSE );
	virtual void   ReleaseBmp();

	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
public:
	inline operator HBITMAP () const
	{
		return this->m_hBitmap;
	}

	inline operator CSize () const
	{
		return CSize( this->m_bmpHeader.biWidth, this->m_bmpHeader.biHeight );
	}

	inline operator CRect () const
	{
		return CRect( 0, 0, this->m_bmpHeader.biWidth, this->m_bmpHeader.biHeight );
	}

	inline HBITMAP GetHBitmap() const
	{
		return this->m_hBitmap;
	}

	inline LPBYTE GetBitmapBuf() const
	{
		return this->m_pBmpBuf;
	}

	inline BITMAPINFOHEADER& GetBitmapHeader()
	{
		return this->m_bmpHeader;
	}
};

typedef const EZ_MemoryBmp  C_EZMEMORYBMP;
typedef       EZ_MemoryBmp* LPEZMEMORYBMP;
typedef const EZ_MemoryBmp* LPCEZMEMORYBMP;
