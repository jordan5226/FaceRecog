#include "StdAfx.h"
#include "EZ_MemoryDC.h"

//  ==========================================================================
//  
//  ==========================================================================
EZ_MemoryDC::EZ_MemoryDC() : EZ_CriticalSection(), EZ_MemoryBmp(), m_hOldBmp( NULL ), m_pMemDC( NULL )
{
	;
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_MemoryDC::~EZ_MemoryDC()
{
	this->ReleaseDC();
}

//  ==========================================================================
//  Create DC
//  ==========================================================================
C_BOOL EZ_MemoryDC::CreateDC( CDC* lpDC, LPCBITMAPINFO lpBitmap )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  Delete DC
	this->ReleaseDC();

	//  Alloc DC
	this->m_pMemDC = new CDC;

	if ( !this->m_pMemDC || !this->m_pMemDC->CreateCompatibleDC( lpDC ) )
		this->ReleaseDC();
	else if ( !EZ_MemoryBmp::CreateBmp( ( lpDC ? lpDC : this->m_pMemDC ), lpBitmap ) )
		this->ReleaseDC();
	else
	{
		this->m_hOldBmp = ( HBITMAP )::SelectObject( *this->m_pMemDC, EZ_MemoryBmp::m_hBitmap );

		this->m_pMemDC->SetStretchBltMode( COLORONCOLOR );
		this->m_pMemDC->SetBkMode( TRANSPARENT );
	}

	//  Result ?
	return ( this->m_pMemDC != NULL );
}

C_BOOL EZ_MemoryDC::CreateDC( CDC* lpDC, LPEZBITMAPINFO lpBitmap )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  Delete DC
	this->ReleaseDC();

	//  Alloc DC
	this->m_pMemDC = new CDC;

	if ( !this->m_pMemDC || !this->m_pMemDC->CreateCompatibleDC( lpDC ) )
		this->ReleaseDC();
	else if ( !EZ_MemoryBmp::CreateBmp( ( lpDC ? lpDC : this->m_pMemDC ), lpBitmap ) )
		this->ReleaseDC();
	else
	{
		this->m_hOldBmp = ( HBITMAP )::SelectObject( *this->m_pMemDC, EZ_MemoryBmp::m_hBitmap );

		this->m_pMemDC->SetStretchBltMode( COLORONCOLOR );
		this->m_pMemDC->SetBkMode( TRANSPARENT );
	}

	//  Result ?
	return ( this->m_pMemDC != NULL );
}

C_BOOL EZ_MemoryDC::CreateDC( CDC* lpDC, C_INT iWidth, C_INT iHeight )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  Delete DC
	this->ReleaseDC();

	//  Alloc DC
	this->m_pMemDC = new CDC;

	if ( !this->m_pMemDC || !this->m_pMemDC->CreateCompatibleDC( lpDC ) )
		this->ReleaseDC();
	else if ( !EZ_MemoryBmp::CreateBmp( ( lpDC ? lpDC : this->m_pMemDC ), iWidth, iHeight ) ) 
		this->ReleaseDC();
	else
	{
		this->m_hOldBmp = ( HBITMAP )::SelectObject( *this->m_pMemDC, EZ_MemoryBmp::m_hBitmap );

		;
	}

	//  Result ?
	return ( this->m_pMemDC != NULL );
}

C_BOOL EZ_MemoryDC::CreateDC( CDC* lpDC, C_INT iWidth, C_INT iHeight, C_INT iPlanes, C_INT iBitsPerPel, C_BOOL bDIBSection )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  Create DC
	if ( bDIBSection )
	{	//  Creaet DIB Section Bitmap
		BITMAPINFO bmpInfo;

		::memset( &bmpInfo.bmiHeader, 0, sizeof( BITMAPINFOHEADER ) );

		bmpInfo.bmiHeader.biSize          = sizeof( BITMAPINFOHEADER ); 
		bmpInfo.bmiHeader.biWidth         = iWidth; 
		bmpInfo.bmiHeader.biHeight        = iHeight; 
		bmpInfo.bmiHeader.biSizeImage     = ( iWidth * iHeight * ( iBitsPerPel >> 3 ) );
		bmpInfo.bmiHeader.biPlanes        = iPlanes; 
		bmpInfo.bmiHeader.biBitCount      = iBitsPerPel; 
		bmpInfo.bmiHeader.biCompression   = 0; 
		bmpInfo.bmiHeader.biXPelsPerMeter = 0; 
		bmpInfo.bmiHeader.biYPelsPerMeter = 0; 
		bmpInfo.bmiHeader.biClrUsed       = 0; 
		bmpInfo.bmiHeader.biClrImportant  = 0;

		return this->CreateDC( lpDC, &bmpInfo );
	}
	else
	{	//  Creaet Normal Bitmap
		//  Delete DC
		this->ReleaseDC();

		//  Alloc DC
		this->m_pMemDC = new CDC;

		if ( !this->m_pMemDC || !this->m_pMemDC->CreateCompatibleDC( lpDC ) )
			this->ReleaseDC();
		else if ( !EZ_MemoryBmp::CreateBmp( ( lpDC ? lpDC : this->m_pMemDC ), iWidth, iHeight, iPlanes, iBitsPerPel, bDIBSection ) ) 
			this->ReleaseDC();
		else
		{
			this->m_hOldBmp = ( HBITMAP )::SelectObject( *this->m_pMemDC, EZ_MemoryBmp::m_hBitmap );

			;
		}

		//  Result ?
		return ( this->m_pMemDC != NULL );
	}
}

//  ==========================================================================
//  Release DC
//  ==========================================================================
void EZ_MemoryDC::ReleaseDC()
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  Delete DC
	if ( this->m_pMemDC && this->m_pMemDC->GetSafeHdc() )
	{
		if ( this->m_hOldBmp )
			this->m_pMemDC->SelectObject( this->m_hOldBmp );

		this->m_pMemDC->DeleteDC();
	}

	SAFE_DELETE ( this->m_pMemDC );

	//  Delete Bitmap
	EZ_MemoryBmp::ReleaseBmp();

	//  Clear Information
	this->m_hOldBmp = NULL;
}

//  ==========================================================================
//  BitBlt to Dst-DC
//  ==========================================================================
C_BOOL EZ_MemoryDC::BitBlt( HDC hDstDC, C_INT xDst, C_INT yDst, C_INT nDstWidth, C_INT nDstHeight, C_INT xSrc, C_INT ySrc, C_UINT dwRop )
{
	BOOL bResult = FALSE;

	if ( hDstDC )
	{
		//  Lock ( Into ) and Unlock ( Exit )
		EZ_CriticalSectionLock csLock( *this );

		//  BitBlt
		if ( this->m_pMemDC )
		{
#if defined ( _USE_TRY_CATCH_ )
			try
#endif
			{
				bResult = ::BitBlt( hDstDC, xDst, yDst, nDstWidth, nDstHeight, *this->m_pMemDC, xSrc, ySrc, dwRop );
			}
#if defined ( _USE_TRY_CATCH_ )
			catch ( ... )
			{
				::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] BitBltToDstDC - Error !\n" ) );
			}
#endif
		}
	}

	return bResult;
}

//  ==========================================================================
//  BitBlt by Src-DC
//
//  PS. hSrcDC can be set to NULL, if dwRop specifies a raster operation that does not include a source
//  ==========================================================================
C_BOOL EZ_MemoryDC::BitBlt( C_INT xSrc, C_INT ySrc, HDC hSrcDC, C_INT xDst, C_INT yDst, C_INT nDstWidth, C_INT nDstHeight, C_UINT dwRop )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  BitBlt
	BOOL bResult = FALSE;

	if ( this->m_pMemDC )
	{
#if defined ( _USE_TRY_CATCH_ )
		try
#endif
		{
			bResult = ::BitBlt( *this->m_pMemDC, xDst, yDst, nDstWidth, nDstHeight, hSrcDC, xSrc, ySrc, dwRop );
		}
#if defined ( _USE_TRY_CATCH_ )
		catch ( ... )
		{
			::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] BitBltFromSrcDB - Error !\n" ) );
		}
#endif
	}

	return bResult;
}

//  ==========================================================================
//  StretchBlt to Dst-DC
//  ==========================================================================
C_BOOL EZ_MemoryDC::StretchBlt( HDC hDstDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_UINT dwRop )
{
	BOOL bResult = FALSE;

	if ( hDstDC )
	{
		//  Lock ( Into ) and Unlock ( Exit )
		EZ_CriticalSectionLock csLock( *this );

		//  StretchBlt
		if ( this->m_pMemDC )
		{
#if defined ( _USE_TRY_CATCH_ )
			try
#endif
			{
				bResult = ::StretchBlt( hDstDC, XDest, YDest, nDestWidth, nDestHeight, *this->m_pMemDC, XSrc, YSrc, nSrcWidth, nSrcHeight, dwRop );
			}
#if defined ( _USE_TRY_CATCH_ )
			catch ( ... )
			{
				::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] StretchBltToDstDC - Error !\n" ) );
			}
#endif
		}
	}

	return bResult;
}

//  ==========================================================================
//  StretchBlt by Src-DC
//  ==========================================================================
C_BOOL EZ_MemoryDC::StretchBlt( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, HDC hSrcDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT dwRop )
{
	BOOL bResult = FALSE;

	if ( hSrcDC )
	{
		//  Lock ( Into ) and Unlock ( Exit )
		EZ_CriticalSectionLock csLock( *this );

		//  StretchBlt
		if ( this->m_pMemDC )
		{
#if defined ( _USE_TRY_CATCH_ )
			try
#endif
			{
				bResult = ::StretchBlt( *this->m_pMemDC, XDest, YDest, nDestWidth, nDestHeight, hSrcDC, XSrc, YSrc, nSrcWidth, nSrcHeight, dwRop );
			}
#if defined ( _USE_TRY_CATCH_ )
			catch ( ... )
			{
				::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] StretchBltFromSrcDC - Error !\n" ) );
			}
#endif
		}
	}

	return bResult;
}

//  ==========================================================================
//  StretchDIBits by Src-BitmapInfo
//  ==========================================================================
C_BOOL EZ_MemoryDC::StretchDIBits( LPCBITMAPINFOHEADER lpHeader, LPCBYTE lpData, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, 
								   C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT iUsage, C_UINT dwRop )
{  
	BOOL bResult = FALSE;

	if ( lpHeader && lpData )
	{
		//  Lock ( Into ) and Unlock ( Exit )
		EZ_CriticalSectionLock csLock( *this );

		//  StretchDIBits
		if ( this->m_pMemDC )
		{
#if defined ( _USE_TRY_CATCH_ )
			try
#endif
			{
				bResult = ( GDI_ERROR != ::StretchDIBits( *this->m_pMemDC, XDest, YDest, nDestWidth, nDestHeight,
					XSrc, YSrc, nSrcWidth, nSrcHeight, lpData, ( LPBITMAPINFO )lpHeader, iUsage, dwRop ) );
			}
#if defined ( _USE_TRY_CATCH_ )
			catch ( ... )
			{
				::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] StretchDIBits - Error !\n" ) );
			}
#endif
		}
	}

	return bResult;
}

//  ==========================================================================
//  MoveTo
//  ==========================================================================
C_BOOL EZ_MemoryDC::MoveTo( C_INT iMoveX, C_INT iMoveY )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  MoveTo
	BOOL bResult = FALSE;

	if ( this->m_pMemDC )
	{
#if defined ( _USE_TRY_CATCH_ )
		try
#endif
		{
			bResult = ::MoveToEx( *this->m_pMemDC, iMoveX, iMoveY, NULL );
		}
#if defined ( _USE_TRY_CATCH_ )
		catch ( ... )
		{
			::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] MoveTo - Error !\n" ) );
		}
#endif
	}

	return bResult;
}

//  ==========================================================================
//  Move2Line
//  ==========================================================================
C_BOOL EZ_MemoryDC::Move2Line( C_INT iMoveX, C_INT iMoveY, C_INT iLineX, C_INT iLineY )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  Move2Line
	BOOL bResult = FALSE;

	if ( this->m_pMemDC )
	{
#if defined ( _USE_TRY_CATCH_ )
		try
#endif
		{
			bResult = ( this->MoveTo( iMoveX, iMoveY ) ? this->m_pMemDC->LineTo( iLineX, iLineY ) : FALSE );
		}
#if defined ( _USE_TRY_CATCH_ )
		catch ( ... )
		{
			::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] Move2Line - Error !\n" ) );
		}
#endif
	}

	return bResult;
}

//  ==========================================================================
//  FrameRgn
//  ==========================================================================
C_BOOL EZ_MemoryDC::FrameRgn( CRgn* lpRgn, CBrush* lpBrush, C_INT iWidth, C_INT iHeight )
{
	BOOL bResult = FALSE;

	if ( lpRgn && lpBrush )
	{
		//  Lock ( Into ) and Unlock ( Exit )
		EZ_CriticalSectionLock csLock( *this );

		//  FrameRgn
		if ( this->m_pMemDC )
		{
#if defined ( _USE_TRY_CATCH_ )
			try
#endif
			{
				bResult = this->m_pMemDC->FrameRgn( lpRgn, lpBrush, iWidth, iHeight );
			}
#if defined ( _USE_TRY_CATCH_ )
			catch ( ... )
			{
				::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] FrameRgn - Error !\n" ) );
			}
#endif
		}
	}

	return bResult;
}

//  ==========================================================================
//  FrameRect
//  ==========================================================================
C_BOOL EZ_MemoryDC::FrameRect( CBrush& objBrush, CRect* lpRect )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  FrameRect
	BOOL bResult = FALSE;

	if ( this->m_pMemDC )
	{
#if defined ( _USE_TRY_CATCH_ )
		try
#endif
		{
			if ( lpRect )
				bResult = ::FrameRect( *this->m_pMemDC, lpRect, objBrush );
			else
			{
				CRect crBmp( 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight );

				bResult = ::FrameRect( *this->m_pMemDC, &crBmp, objBrush );
			}
		}
#if defined ( _USE_TRY_CATCH_ )
		catch ( ... )
		{
			::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] FrameRect - Error !\n" ) );
		}
#endif
	}

	return bResult;
}

//  ==========================================================================
//  FillRgn
//  ==========================================================================
C_BOOL EZ_MemoryDC::FillRgn( CRgn* lpRgn, CBrush* lpBrush )
{
	BOOL bResult = FALSE;

	if ( lpRgn && lpBrush )
	{
		//  Lock ( Into ) and Unlock ( Exit )
		EZ_CriticalSectionLock csLock( *this );

		//  FillRgn
		if ( this->m_pMemDC )
		{
#if defined ( _USE_TRY_CATCH_ )
			try
#endif
			{
				bResult = this->m_pMemDC->FillRgn( lpRgn, lpBrush );
			}
#if defined ( _USE_TRY_CATCH_ )
			catch ( ... )
			{
				::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] FillRgn - Error !\n" ) );
			}
#endif
		}
	}

	return bResult;
}

//  ==========================================================================
//  FillRect
//  ==========================================================================
C_BOOL EZ_MemoryDC::FillRect( CBrush& objBrush, CRect* lpRect )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  FillRect
	BOOL bResult = FALSE;

	if ( this->m_pMemDC )
	{
#if defined ( _USE_TRY_CATCH_ )
		try
#endif
		{
			if ( lpRect )
				bResult = ::FillRect( *this->m_pMemDC, lpRect, objBrush );
			else
			{
				CRect crBmp( 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight );

				bResult = ::FillRect( *this->m_pMemDC, &crBmp, objBrush );
			}
		}
#if defined ( _USE_TRY_CATCH_ )
		catch ( ... )
		{
			::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] FillRect - Error !\n" ) );
		}
#endif
	}

	return bResult;
}

C_BOOL EZ_MemoryDC::FillRect( COLORREF iBrushClr, CRect* lpRect )
{
	CBrush objBrush( iBrushClr );

	return this->FillRect( objBrush, lpRect );
}

//  ==========================================================================
//  FillSolidRect
//  ==========================================================================
void EZ_MemoryDC::FillSolidRect( COLORREF iBrushClr, CRect* lpRect )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  FillSolidRect
	if ( this->m_pMemDC )
	{
#if defined ( _USE_TRY_CATCH_ )
		try
#endif
		{
			if ( lpRect )
				this->m_pMemDC->FillSolidRect( lpRect, iBrushClr );
			else
			{
				CRect crBmp( 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight );

				this->m_pMemDC->FillSolidRect( &crBmp, iBrushClr );
			}
		}
#if defined ( _USE_TRY_CATCH_ )
		catch ( ... )
		{
			::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] FillSolidRect - Error !\n" ) );
		}
#endif
	}
}

//  ==========================================================================
//  DrawText
//  ==========================================================================
C_INT EZ_MemoryDC::DrawTextA( LPCSTR lpText, C_INT iTextLen, LPRECT lpRect, UINT nFormat, CFont* lpFont )
{
	//  Error !
	if ( !lpText )
	{
		;
		return 0;
	}

	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  DrawText
	INT iResult = 0;

	if ( this->m_pMemDC )
	{
		//  Get Draw Text Rect
		CRect crBmp( 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight );

		if ( lpRect ) crBmp = *lpRect;

		//  Draw Text and Set Font if Need.
#if defined ( _USE_TRY_CATCH_ )
		try
#endif
		{
			if ( !lpFont )
				iResult = ::DrawTextA( *this->m_pMemDC, lpText, iTextLen, &crBmp, nFormat );
			else
			{
				CFont* lpOldFont = this->m_pMemDC->SelectObject( lpFont );

				iResult = ::DrawTextA( *this->m_pMemDC, lpText, iTextLen, &crBmp, nFormat );

				this->m_pMemDC->SelectObject( lpOldFont );
			}
		}
#if defined ( _USE_TRY_CATCH_ )
		catch ( ... )
		{
			::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] DrawTextW - Error !\n" ) );
		}
#endif
	}

	return iResult;
}

C_INT EZ_MemoryDC::DrawTextW( LPCWSTR lpText, C_INT iTextLen, LPRECT lpRect, UINT nFormat, CFont* lpFont )
{
	//  Error !
	if ( !lpText )
	{
		;
		return 0;
	}

	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  DrawText
	INT iResult = 0;

	if ( this->m_pMemDC )
	{
		//  Get Draw Text Rect
		CRect crBmp( 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight );

		if ( lpRect ) crBmp = *lpRect;

		//  Draw Text and Set Font if Need.
#if defined ( _USE_TRY_CATCH_ )
		try
#endif
		{
			if ( !lpFont )
				iResult = ::DrawTextW( *this->m_pMemDC, lpText, iTextLen, &crBmp, nFormat );
			else
			{
				CFont* lpOldFont = this->m_pMemDC->SelectObject( lpFont );

				iResult = ::DrawTextW( *this->m_pMemDC, lpText, iTextLen, &crBmp, nFormat );

				this->m_pMemDC->SelectObject( lpOldFont );
			}
		}
#if defined ( _USE_TRY_CATCH_ )
		catch ( ... )
		{
			::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] DrawTextW - Error !\n" ) );
		}
#endif
	}

	return iResult;
}

C_INT EZ_MemoryDC::DrawTextT( LPCTSTR lpText, C_INT iTextLen, LPRECT lpRect, UINT nFormat, CFont* lpFont )
{
#if defined ( _UNICODE )
	return this->DrawTextW( ( LPCWSTR )lpText, iTextLen, lpRect, nFormat, lpFont );
#else
	return this->DrawTextA( ( LPCSTR  )lpText, iTextLen, lpRect, nFormat, lpFont );
#endif
}

//  ==========================================================================
//  TextOut
//  ==========================================================================
C_BOOL EZ_MemoryDC::TextOutA( C_INT iPosX, C_INT iPosY, LPCSTR lpText, C_INT iTextLen )
{
	//  Error !
	if ( !lpText )
	{
		;
		return FALSE;
	}

	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  TextOut
	BOOL bResult = FALSE;

	if ( this->m_pMemDC )
	{
#if defined ( _USE_TRY_CATCH_ )
		try
#endif
		{
			bResult = ::TextOutA( *this->m_pMemDC, iPosX, iPosY, lpText, iTextLen );
		}
#if defined ( _USE_TRY_CATCH_ )
		catch ( ... )
		{
			::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] TextOutA - Exception !\n" ) );
		}
#endif
	}

	return bResult;
}

C_BOOL EZ_MemoryDC::TextOutW( C_INT iPosX, C_INT iPosY, LPCWSTR lpText, C_INT iTextLen )
{
	//  Error !
	if ( !lpText )
	{
		;
		return FALSE;
	}

	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  TextOut
	BOOL bResult = FALSE;

	if ( this->m_pMemDC )
	{
#if defined ( _USE_TRY_CATCH_ )
		try
#endif
		{
			bResult = ::TextOutW( *this->m_pMemDC, iPosX, iPosY, lpText, iTextLen );
		}
#if defined ( _USE_TRY_CATCH_ )
		catch ( ... )
		{
			::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] TextOutW - Exception !\n" ) );
		}
#endif
	}

	return bResult;
}

C_BOOL EZ_MemoryDC::TextOutT( C_INT iPosX, C_INT iPosY, LPCTSTR lpText, C_INT iTextLen )
{
#if defined ( _UNICODE )
	return this->TextOutW( iPosX, iPosY, ( LPCWSTR )lpText, iTextLen );
#else
	return this->TextOutA( iPosX, iPosY, ( LPCSTR  )lpText, iTextLen );
#endif
}

//  ==========================================================================
//  GetTextExtent
//  ==========================================================================
C_BOOL EZ_MemoryDC::GetTextExtentA( LPCSTR lpText, CSize& csText )
{
	//  Error !
	csText.cx = csText.cy = 0;

	if ( !lpText )
	{
		;
		return FALSE;
	}

	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  GetTextExtent
	BOOL bResult = FALSE;

	if ( this->m_pMemDC )
	{
#if defined ( _USE_TRY_CATCH_ )
		try
#endif
		{
			bResult = ::GetTextExtentPoint32A( *this->m_pMemDC, lpText, ( INT )::strlen( lpText ), &csText );
		}
#if defined ( _USE_TRY_CATCH_ )
		catch ( ... )
		{
			::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] GetTextExtentA - Exception !\n" ) );
		}
#endif
	}

	return bResult;
}

C_BOOL EZ_MemoryDC::GetTextExtentW( LPCWSTR lpText, CSize& csText )
{
	//  Error !
	csText.cx = csText.cy = 0;

	if ( !lpText )
	{
		;
		return FALSE;
	}

	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  GetTextExtent
	BOOL bResult = FALSE;

	if ( this->m_pMemDC )
	{
#if defined ( _USE_TRY_CATCH_ )
		try
#endif
		{
			bResult = ::GetTextExtentPoint32W( *this->m_pMemDC, lpText, ( INT )::wcslen( lpText ), &csText );
		}
#if defined ( _USE_TRY_CATCH_ )
		catch ( ... )
		{
			::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] GetTextExtentW - Exception !\n" ) );
		}
#endif
	}

	return bResult;
}

C_BOOL EZ_MemoryDC::GetTextExtent( LPCTSTR lpText, CSize& csText )
{
#if defined ( _UNICODE )
	return this->GetTextExtentW( ( LPCWSTR )lpText, csText );
#else
	return this->GetTextExtentA( ( LPCSTR  )lpText, csText );
#endif
}

//  ==========================================================================
//  GetBitmap
//  ==========================================================================
C_BOOL EZ_MemoryDC::GetBitmap( BITMAP& dtBitmap )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  GetBitmap
	BOOL bResult = FALSE;

	if ( EZ_MemoryBmp::m_hBitmap )
	{
		CBitmap objBitmap;

		if ( objBitmap.Attach( EZ_MemoryBmp::m_hBitmap ) )
		{
			bResult = ( objBitmap.GetBitmap( &dtBitmap ) != 0 );

			objBitmap.Detach();
		}
	}

	return bResult;
}

//  ==========================================================================
//  SetStretchBltMode
//  ==========================================================================
INT EZ_MemoryDC::SetStretchBltMode( C_INT iStretchBltMode )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  SetStretchBltMode
	return ( this->m_pMemDC ? ::SetStretchBltMode( *this->m_pMemDC, iStretchBltMode ) : 0 );
}

//  ==========================================================================
//  SetBkMode
//  ==========================================================================
INT EZ_MemoryDC::SetBkMode( C_INT iBKMode )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  SetBkColor
	return ( this->m_pMemDC ? ::SetBkMode( *this->m_pMemDC, iBKMode ) : 0 );
}

//  ==========================================================================
//  SetLayout
//  ==========================================================================
DWORD EZ_MemoryDC::SetLayout( C_UINT dwNewLayout )
{
	DWORD dwOldLayout = GDI_ERROR;

	if ( dwNewLayout != GDI_ERROR )
	{
		//  Lock ( Into ) and Unlock ( Exit )
		EZ_CriticalSectionLock csLock( *this );

		//  SetLayout
		if ( this->m_pMemDC )
		{
#if _MSC_VER > 1400
			dwOldLayout = this->m_pMemDC->SetLayout( dwNewLayout );
#elif _MSC_VER > 1300
			dwOldLayout = ::SetLayout( *this->m_pMemDC, dwNewLayout );
#else
			dwOldLayout = this->m_pMemDC->SetLayout( dwNewLayout );
#endif
		}
	}

	return dwOldLayout;
}

//  ==========================================================================
//  SetTextColor
//  ==========================================================================
COLORREF EZ_MemoryDC::SetTextColor( C_COLORREF iNewTxtClr )
{
	COLORREF iOldTxtClr = CLR_INVALID;

	if ( iNewTxtClr != CLR_INVALID )
	{
		//  Lock ( Into ) and Unlock ( Exit )
		EZ_CriticalSectionLock csLock( *this );

		//  SetTextColor
		if ( this->m_pMemDC )
			iOldTxtClr = ::SetTextColor( *this->m_pMemDC, iNewTxtClr );
	}

	return iOldTxtClr;
}

//  ==========================================================================
//  SetBkColor
//  ==========================================================================
COLORREF EZ_MemoryDC::SetBkColor( C_COLORREF iNewBKClr )
{
	COLORREF iOldBKClr = CLR_INVALID;

	if ( iNewBKClr != CLR_INVALID )
	{
		//  Lock ( Into ) and Unlock ( Exit )
		EZ_CriticalSectionLock csLock( *this );

		//  SetBkColor
		if ( this->m_pMemDC )
			iOldBKClr = ::SetBkColor( *this->m_pMemDC, iNewBKClr );
	}

	return iOldBKClr;
}

//  ==========================================================================
//  SetPen
//  ==========================================================================
CPen* EZ_MemoryDC::SetPen( CPen* lpNewPen )
{
	CPen* lpOldPen = NULL;

	if ( lpNewPen )
	{
		//  Lock ( Into ) and Unlock ( Exit )
		EZ_CriticalSectionLock csLock( *this );

		//  SetBrush
		if ( this->m_pMemDC )
			lpOldPen = this->m_pMemDC->SelectObject( lpNewPen );
	}

	return lpOldPen;
}

//  ==========================================================================
//  SetFont
//  ==========================================================================
CFont* EZ_MemoryDC::SetFont( CFont* lpNewFont )
{
	CFont* lpOldFont = NULL;

	if ( lpNewFont )
	{
		//  Lock ( Into ) and Unlock ( Exit )
		EZ_CriticalSectionLock csLock( *this );

		//  SetBrush
		if ( this->m_pMemDC )
			lpOldFont = this->m_pMemDC->SelectObject( lpNewFont );
	}

	return lpOldFont;
}

//  ==========================================================================
//  SetBrush
//  ==========================================================================
CBrush* EZ_MemoryDC::SetBrush( CBrush* lpNewBrush )
{
	CBrush* lpOldBrush = NULL;

	if ( lpNewBrush )
	{
		//  Lock ( Into ) and Unlock ( Exit )
		EZ_CriticalSectionLock csLock( *this );

		//  SetBrush
		if ( this->m_pMemDC )
			lpOldBrush = this->m_pMemDC->SelectObject( lpNewBrush );
	}

	return lpOldBrush;
}

//  ==========================================================================
//  Support on Virtual Stdio 2003 or Higher
//  ==========================================================================
#if ( _MSC_VER > 1300 )
#include "EZ_MemoryDC_LoadImage.h"
#endif
