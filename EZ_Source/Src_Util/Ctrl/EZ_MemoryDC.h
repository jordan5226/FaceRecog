#pragma once

#include <Wingdi.h>
#include "EZ_MemoryBmp.h"
#include "..\Thread\EZ_CriticalSection.h"

#if defined ( _USE_GDI_PLUS_DLL_ )

#include <AtlImage.h>

//  ==========================================================================
//  
//  ==========================================================================
#if ( _WIN32_WINNT >= 0x0600 )
extern HIMAGELIST LoadImageList( const WORD nResID, const int nFixSize, const COLORREF crMask );
#endif

//  ==========================================================================
//  EZ_CriticalSectionImage
//  ==========================================================================
class EZ_CriticalSectionImage : protected CImage, public EZ_CriticalSection
{
protected:
	;

public:
	EZ_CriticalSectionImage();
	virtual ~EZ_CriticalSectionImage();

	virtual HRESULT Load( LPCTSTR lpFileName );
	virtual void    Destroy();

	virtual void LoadFromResource( HINSTANCE hInstance, LPCTSTR lpResourceName );
	virtual void LoadFromResource( HINSTANCE hInstance, UINT    nIDResource    );

	virtual BOOL LoadFromResPNG( HINSTANCE hInstance, UINT    nIDResource    );
	virtual BOOL LoadFromResPNG( HINSTANCE hInstance, LPCTSTR lpResourceName );

	virtual BOOL Draw( HDC hDestDC, const POINT& ptDest );
	virtual BOOL Draw( HDC hDestDC, const RECT& rcDest );
	virtual BOOL Draw( HDC hDestDC, int xDest, int yDest );
	virtual BOOL Draw( HDC hDestDC, const RECT& rcDest, const RECT& rcSrc );
	virtual BOOL Draw( HDC hDestDC, int xDest, int yDest, int nDestWidth, int nDestHeight );
	virtual BOOL Draw( HDC hDestDC, int xDest, int yDest, int nDestWidth, int nDestHeight, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight );

	virtual bool IsNull();
	virtual int  GetWidth();
	virtual int  GetHeight();

protected:
	virtual void Process32BPP( C_BOOL bInvertOpacity = FALSE, C_BOOL bPreMultiply = FALSE, const COLORREF crTransparentClr = -1 );

public:
	static void GetHeader( CImage& objImage, BITMAPINFOHEADER& infoBmpHeader );

	static BOOL LoadFromResPNG( CImage& objImage, HINSTANCE hInstance, UINT    nIDResource    );
	static BOOL LoadFromResPNG( CImage& objImage, HINSTANCE hInstance, LPCTSTR lpResourceName );
};

typedef const EZ_CriticalSectionImage  C_EZEZCRITICALSECTIONIMAGE;
typedef       EZ_CriticalSectionImage* LPEZEZCRITICALSECTIONIMAGE;
typedef const EZ_CriticalSectionImage* LPCEZEZCRITICALSECTIONIMAGE;

#endif

//  ==========================================================================
//  Memory DC
//  ==========================================================================
class EZ_MemoryDC : public EZ_CriticalSection, public EZ_MemoryBmp
{
public:
	HBITMAP m_hOldBmp;
	CDC*    m_pMemDC;

public:
	EZ_MemoryDC();
	virtual ~EZ_MemoryDC();

	EZ_MemoryDC& operator = ( const EZ_MemoryDC& dcMemory );
	EZ_MemoryDC& operator = ( const EZ_MemoryDC* lpMemDC  );

	//  Create / Release DC
	virtual C_BOOL CreateDC( CDC* lpDC, LPCBITMAPINFO  lpBitmap );
	virtual C_BOOL CreateDC( CDC* lpDC, LPEZBITMAPINFO lpBitmap );

	virtual C_BOOL CreateDC( CDC* lpDC, C_INT iWidth, C_INT iHeight );
	virtual C_BOOL CreateDC( CDC* lpDC, C_INT iWidth, C_INT iHeight, C_INT iPlanes, C_INT iBitsPerPel, C_BOOL bDIBSection = FALSE );

	virtual void   ReleaseDC();

	//  BitBlt to Dst-DC
	virtual C_BOOL BitBlt( HDC hDstDC, C_INT xDst, C_INT yDst, C_INT nDstWidth, C_INT nDstHeight, C_INT xSrc, C_INT ySrc, C_UINT dwRop );	

	//  BitBlt by Src-DC
	virtual C_BOOL BitBlt( C_INT xSrc, C_INT ySrc, HDC hSrcDC, C_INT xDst, C_INT yDst, C_INT nDstWidth, C_INT nDstHeight, C_UINT dwRop );	

	//  StretchBlt to Dst-DC
	virtual C_BOOL StretchBlt( HDC hDstDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_UINT dwRop );

	//  StretchBlt by Src-DC
	virtual C_BOOL StretchBlt( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, HDC hSrcDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT dwRop );

	//  StretchDIBits by Src-BitmapInfo
	virtual C_BOOL StretchDIBits( LPCBITMAPINFOHEADER lpHeader, LPCBYTE lpData, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, 
		C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT iUsage, C_UINT dwRop );

	//  Line and Move
	virtual C_BOOL MoveTo(    C_INT iMoveX, C_INT iMoveY );
	virtual C_BOOL Move2Line( C_INT iMoveX, C_INT iMoveY, C_INT iLineX, C_INT iLineY );

	//  Other Draw
	virtual C_BOOL FrameRgn( CRgn* lpRgn, CBrush* lpBrush, C_INT iWidth, C_INT iHeight );
	virtual C_BOOL FrameRect( CBrush& cbObject, CRect* lpRect = NULL );

	virtual C_BOOL FillRgn( CRgn* lpRgn, CBrush* lpBrush );
	virtual C_BOOL FillRect( CBrush& cbObject, CRect* lpRect = NULL );
	virtual C_BOOL FillRect( COLORREF clrBrush, CRect* lpRect = NULL );
	virtual void   FillSolidRect( COLORREF clrBrush, CRect* lpRect = NULL );

	virtual C_INT  DrawTextA( LPCSTR  lpText, C_INT iTextLen, LPRECT lpRect, UINT nFormat, CFont* lpFont = NULL );
	virtual C_INT  DrawTextW( LPCWSTR lpText, C_INT iTextLen, LPRECT lpRect, UINT nFormat, CFont* lpFont = NULL );
	virtual C_INT  DrawTextT( LPCTSTR lpText, C_INT iTextLen, LPRECT lpRect, UINT nFormat, CFont* lpFont = NULL );

	virtual C_BOOL TextOutA( C_INT iPosX, C_INT iPosY, LPCSTR  lpText, C_INT iTextLen );
	virtual C_BOOL TextOutW( C_INT iPosX, C_INT iPosY, LPCWSTR lpText, C_INT iTextLen );
	virtual C_BOOL TextOutT( C_INT iPosX, C_INT iPosY, LPCTSTR lpText, C_INT iTextLen );

	virtual C_BOOL GetTextExtentA( LPCSTR  lpText, CSize& csText );
	virtual C_BOOL GetTextExtentW( LPCWSTR lpText, CSize& csText );
	virtual C_BOOL GetTextExtent(  LPCTSTR lpText, CSize& csText );

	//  
	virtual C_BOOL GetBitmap( BITMAP& dtBitmap );

	//  Select Object
	virtual INT      SetBkMode( C_INT iMode );
	virtual INT      SetStretchBltMode( C_INT iMode );
	virtual DWORD    SetLayout( C_UINT dwLayout );

	virtual COLORREF SetTextColor( C_COLORREF clrNewTxt );
	virtual COLORREF SetBkColor( C_COLORREF clrNewBK );

	virtual CPen*   SetPen(   CPen*   lpNewPen   );
	virtual CFont*  SetFont(  CFont*  lpNewFont  );
	virtual CBrush* SetBrush( CBrush* lpNewBrush );

	//  ==========================================================================
	//  Support on Virtual Stdio 2003 or Higher
	//  ==========================================================================
#if ( _MSC_VER > 1300 )
	//  Load Image
	virtual C_BOOL LoadImage( LPCTSTR lpImgFile, CDC* lpDC );
	virtual C_BOOL LoadImage( LPCTSTR lpImgFile, CDC* lpDC, LPBITMAPINFO&   lpBitmap, C_BOOL bDecodeBuf = TRUE );
	virtual C_BOOL LoadImage( LPCTSTR lpImgFile, CDC* lpDC, LPEZBITMAPINFO& lpBitmap, C_BOOL bDecodeBuf = TRUE );

	//  AlphaBlend to Dst-DC
	virtual C_BOOL AlphaBlend( HDC hDstDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_INT iAlpha );

	//  AlphaBlend by Src-DC
	virtual C_BOOL AlphaBlend( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, HDC hSrcDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT iAlpha );
#endif

	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
public:
	//
	inline operator CDC* () const	{ return this->m_pMemDC; }
	inline operator HDC  () const	{ return ( this->m_pMemDC ? this->m_pMemDC->GetSafeHdc() : NULL ); }

	//  Get Pointer
	inline CDC* GetDC() const		{ return this->m_pMemDC; }
	inline HDC  GetSafeHdc() const	{ return ( this->m_pMemDC ? this->m_pMemDC->GetSafeHdc() : NULL ); }

	//  
	inline C_INT DrawText( C_BOOL bUnicode, LPCTSTR lpText, C_INT iTextLen, LPRECT lpRect, UINT nFormat, CFont* lpFont = NULL )
	{ if ( bUnicode ) return this->DrawTextW( ( LPCWSTR )lpText, iTextLen, lpRect, nFormat, lpFont ); else return this->DrawTextA( ( LPCSTR )lpText, iTextLen, lpRect, nFormat, lpFont ); }

	inline C_BOOL TextOut( C_INT iPosX, C_INT iPosY, C_BOOL bUnicode, LPCTSTR lpText, C_INT iTextLen )
	{ if ( bUnicode ) return this->TextOutW( iPosX, iPosY, ( LPCWSTR )lpText, iTextLen ); else return this->TextOutA( iPosX, iPosY, ( LPCSTR )lpText, iTextLen ); }

	inline C_BOOL GetTextExtent( C_BOOL bUnicode, LPCTSTR lpText, CSize& csText )
	{ if ( bUnicode ) return this->GetTextExtentW( ( LPCWSTR )lpText, csText ); else return this->GetTextExtentA( ( LPCSTR )lpText, csText ); }

	inline CSize GetTextExtent( LPCTSTR lpText ) 
	{ CSize csText( 0, 0 ); this->GetTextExtent( lpText, csText ); return csText; }

	//  BitBlt to Dst-DC
	inline C_BOOL BitBlt( HDC hDstDC, C_INT xDst, C_INT yDst, C_INT nDstWidth, C_INT nDstHeight, C_UINT dwRop );	

	inline C_BOOL BitBlt( CDC* lpDstDC, C_UINT dwRop );	
	inline C_BOOL BitBlt( CDC* lpDstDC, C_INT xDst, C_INT yDst, C_INT nDstWidth, C_INT nDstHeight,                         C_UINT dwRop );	
	inline C_BOOL BitBlt( CDC* lpDstDC, C_INT xDst, C_INT yDst, C_INT nDstWidth, C_INT nDstHeight, C_INT xSrc, C_INT ySrc, C_UINT dwRop );	

	inline C_BOOL BitBlt( EZ_MemoryDC& dcDst, C_INT xDst, C_INT yDst, C_INT nDstWidth, C_INT nDstHeight,                         C_UINT dwRop );	
	inline C_BOOL BitBlt( EZ_MemoryDC& dcDst, C_INT xDst, C_INT yDst, C_INT nDstWidth, C_INT nDstHeight, C_INT xSrc, C_INT ySrc, C_UINT dwRop );	

	//  BitBlt by Src-DC
	inline C_BOOL BitBlt( C_INT xSrc, C_INT ySrc, HDC hSrcDC, C_UINT dwRop );

	inline C_BOOL BitBlt( C_INT xSrc, C_INT ySrc, CDC* lpSrcDC,                                                            C_UINT dwRop );
	inline C_BOOL BitBlt( C_INT xSrc, C_INT ySrc, CDC* lpSrcDC, C_INT xDst, C_INT yDst, C_INT nDstWidth, C_INT nDstHeight, C_UINT dwRop );

	inline C_BOOL BitBlt( C_INT xSrc, C_INT ySrc, EZ_MemoryDC& dcSrc,                                                            C_UINT dwRop );
	inline C_BOOL BitBlt( C_INT xSrc, C_INT ySrc, EZ_MemoryDC& dcSrc, C_INT xDst, C_INT yDst, C_INT nDstWidth, C_INT nDstHeight, C_UINT dwRop );

	//  StretchBlt ( Src-DC to Dst-DC ) or ( Dst-DC from Src-DC )
	inline C_BOOL StretchBlt( C_BOOL bSrcDC, EZ_MemoryDC& dcMemory, C_UINT dwRop );

	//  StretchBlt to Dst-DC
	inline C_BOOL StretchBlt( HDC hDstDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT dwRop );

	inline C_BOOL StretchBlt( CDC* lpDstDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight,                                                            C_UINT dwRop );
	inline C_BOOL StretchBlt( CDC* lpDstDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_UINT dwRop );

	inline C_BOOL StretchBlt( EZ_MemoryDC& dcDst, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight,                                                            C_UINT dwRop );
	inline C_BOOL StretchBlt( EZ_MemoryDC& dcDst, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_UINT dwRop );

	//  StretchBlt by Src-DC
	inline C_BOOL StretchBlt( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, HDC hSrcDC, C_UINT dwRop );
	
	inline C_BOOL StretchBlt( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, CDC* lpSrcDC,                                                                C_UINT dwRop );
	inline C_BOOL StretchBlt( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, CDC* lpSrcDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT dwRop );

	inline C_BOOL StretchBlt( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, EZ_MemoryDC& dcSrc,                                                                C_UINT dwRop );
	inline C_BOOL StretchBlt( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, EZ_MemoryDC& dcSrc, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT dwRop );

	//  StretchDIBits by Src-BitmapInfo
	inline C_BOOL StretchDIBits(                                                            EZ_MemoryDC& dcSrc,                                                                C_UINT iUsage, C_UINT dwRop );
	inline C_BOOL StretchDIBits(                                                            EZ_MemoryDC& dcSrc, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT iUsage, C_UINT dwRop );
	inline C_BOOL StretchDIBits( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, EZ_MemoryDC& dcSrc,                                                                C_UINT iUsage, C_UINT dwRop );
	inline C_BOOL StretchDIBits( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, EZ_MemoryDC& dcSrc, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT iUsage, C_UINT dwRop );

	inline C_BOOL StretchDIBits( LPCBITMAPINFOHEADER lpHeader, LPCBYTE lpData,                                                            C_UINT iUsage, C_UINT dwRop );
	inline C_BOOL StretchDIBits( LPCBITMAPINFOHEADER lpHeader, LPCBYTE lpData, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_UINT iUsage, C_UINT dwRop );
	
	inline C_BOOL StretchDIBits( LPCBITMAPINFO lpBitmap,                                                                                                                           C_UINT iUsage, C_UINT dwRop );
	inline C_BOOL StretchDIBits( LPCBITMAPINFO lpBitmap, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight,                                                                C_UINT iUsage, C_UINT dwRop );
	inline C_BOOL StretchDIBits( LPCBITMAPINFO lpBitmap, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT iUsage, C_UINT dwRop );

	inline C_BOOL StretchDIBits( LPEZBITMAPINFO lpBitmap,                                                                                                                           C_UINT iUsage, C_UINT dwRop );
	inline C_BOOL StretchDIBits( LPEZBITMAPINFO lpBitmap, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight,                                                                C_UINT iUsage, C_UINT dwRop );
	inline C_BOOL StretchDIBits( LPEZBITMAPINFO lpBitmap, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT iUsage, C_UINT dwRop );

	//  AlphaBlend to Dst-DC
#if ( _MSC_VER > 1300 )
	inline C_BOOL AlphaBlend( HDC hDstDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT iAlpha );

	inline C_BOOL AlphaBlend( CDC* lpDstDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight,                                                            C_INT iAlpha );
	inline C_BOOL AlphaBlend( CDC* lpDstDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_INT iAlpha );

	inline C_BOOL AlphaBlend( EZ_MemoryDC& dcDst, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight,                                                            C_INT iAlpha );
	inline C_BOOL AlphaBlend( EZ_MemoryDC& dcDst, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_INT iAlpha );
#endif

	//  AlphaBlend by Src-DC
#if ( _MSC_VER > 1300 )
	inline C_BOOL AlphaBlend( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, HDC hSrcDC, C_INT iAlpha );

	inline C_BOOL AlphaBlend( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, CDC* lpSrcDC,                                                                C_INT iAlpha );
	inline C_BOOL AlphaBlend( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, CDC* lpSrcDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT iAlpha );

	inline C_BOOL AlphaBlend( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, EZ_MemoryDC& dcSrc,                                                                C_INT iAlpha );
	inline C_BOOL AlphaBlend( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, EZ_MemoryDC& dcSrc, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT iAlpha );
#endif
};

typedef const EZ_MemoryDC  C_EZMEMORYDC;
typedef       EZ_MemoryDC* LPEZMEMORYDC;
typedef const EZ_MemoryDC* LPCEZMEMORYDC;

//  ==========================================================================
//  BitBlt to Dst-DC
//  ==========================================================================
C_BOOL EZ_MemoryDC::BitBlt( HDC hDstDC, C_INT xDst, C_INT yDst, C_INT nDstWidth, C_INT nDstHeight, C_UINT dwRop )
{
	return ( hDstDC ? this->BitBlt( hDstDC, xDst, yDst, nDstWidth, nDstHeight, 0, 0, dwRop ) : FALSE );
}

C_BOOL EZ_MemoryDC::BitBlt( CDC* lpDstDC, C_UINT dwRop )
{
	return ( lpDstDC ? this->BitBlt( *lpDstDC, 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, 0, 0, dwRop ) : FALSE );
}

C_BOOL EZ_MemoryDC::BitBlt( CDC* lpDstDC, C_INT xDst, C_INT yDst, C_INT nDstWidth, C_INT nDstHeight, C_UINT dwRop )
{
	return ( lpDstDC ? this->BitBlt( *lpDstDC, xDst, yDst, nDstWidth, nDstHeight, 0, 0, dwRop ) : FALSE );
}

C_BOOL EZ_MemoryDC::BitBlt( CDC* lpDstDC, C_INT xDst, C_INT yDst, C_INT nDstWidth, C_INT nDstHeight, C_INT xSrc, C_INT ySrc, C_UINT dwRop )
{
	return ( lpDstDC ? this->BitBlt( *lpDstDC, xDst, yDst, nDstWidth, nDstHeight, xSrc, ySrc, dwRop ) : FALSE );
}

C_BOOL EZ_MemoryDC::BitBlt( EZ_MemoryDC& dcDst, C_INT xDst, C_INT yDst, C_INT nDstWidth, C_INT nDstHeight, C_UINT dwRop )
{
	return this->BitBlt( dcDst.GetSafeHdc(), xDst, yDst, nDstWidth, nDstHeight, 0, 0, dwRop );
}

C_BOOL EZ_MemoryDC::BitBlt( EZ_MemoryDC& dcDst, C_INT xDst, C_INT yDst, C_INT nDstWidth, C_INT nDstHeight, C_INT xSrc, C_INT ySrc, C_UINT dwRop )
{
	return this->BitBlt( dcDst.GetSafeHdc(), xDst, yDst, nDstWidth, nDstHeight, xSrc, ySrc, dwRop );
}

//  ==========================================================================
//  BitBlt by Src-DC
//
//  PS. hSrcDC can be set to NULL, if dwRop specifies a raster operation that does not include a source
//  ==========================================================================
C_BOOL EZ_MemoryDC::BitBlt( C_INT xSrc, C_INT ySrc, HDC hSrcDC, C_UINT dwRop )
{
#if 1	
	return this->BitBlt( xSrc, ySrc, hSrcDC, 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, dwRop );
#else
	return ( hSrcDC ? this->BitBlt( xSrc, ySrc, hSrcDC, 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, dwRop ) : FALSE );
#endif
}

C_BOOL EZ_MemoryDC::BitBlt( C_INT xSrc, C_INT ySrc, CDC* lpSrcDC, C_UINT dwRop )
{
#if 1
	return this->BitBlt( xSrc, ySrc, ( lpSrcDC ? lpSrcDC->GetSafeHdc() : NULL ), 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, dwRop );
#else
	return ( lpSrcDC ? this->BitBlt( xSrc, ySrc, *lpSrcDC, 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, dwRop ) : FALSE );
#endif
}

C_BOOL EZ_MemoryDC::BitBlt( C_INT xSrc, C_INT ySrc, CDC* lpSrcDC, C_INT xDst, C_INT yDst, C_INT nDstWidth, C_INT nDstHeight, C_UINT dwRop )
{
#if 1
	return this->BitBlt( xSrc, ySrc, ( lpSrcDC ? lpSrcDC->GetSafeHdc() : NULL ), xDst, yDst, nDstWidth, nDstHeight, dwRop );
#else
	return ( lpSrcDC ? this->BitBlt( xSrc, ySrc, *lpSrcDC, xDst, yDst, nDstWidth, nDstHeight, dwRop ) : FALSE );
#endif
}

C_BOOL EZ_MemoryDC::BitBlt( C_INT xSrc, C_INT ySrc, EZ_MemoryDC& dcSrc, C_UINT dwRop )
{
	return this->BitBlt( xSrc, ySrc, dcSrc.GetSafeHdc(), 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, dwRop );
}

C_BOOL EZ_MemoryDC::BitBlt( C_INT xSrc, C_INT ySrc, EZ_MemoryDC& dcSrc, C_INT xDst, C_INT yDst, C_INT nDstWidth, C_INT nDstHeight, C_UINT dwRop )
{
	return this->BitBlt( xSrc, ySrc, dcSrc.GetSafeHdc(), xDst, yDst, nDstWidth, nDstHeight, dwRop );
}

//  ==========================================================================
//  StretchBlt to Dst-DC
//  ==========================================================================
C_BOOL EZ_MemoryDC::StretchBlt( C_BOOL bSrcDC, EZ_MemoryDC& dcMemory, C_UINT dwRop )
{
	if ( bSrcDC )
	{
		return this->StretchBlt( 0, 0, dcMemory.m_bmpHeader.biWidth, dcMemory.m_bmpHeader.biHeight, dcMemory.GetSafeHdc(), 
			0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, dwRop );
	}
	else
	{
		return this->StretchBlt( dcMemory.GetSafeHdc(), 0, 0, dcMemory.m_bmpHeader.biWidth, dcMemory.m_bmpHeader.biHeight, 
			0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, dwRop );
	}
}

//  ==========================================================================
//  StretchBlt to Dst-DC
//  ==========================================================================
C_BOOL EZ_MemoryDC::StretchBlt( HDC hDstDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT dwRop )
{
	return ( hDstDC ? this->StretchBlt( hDstDC, XDest, YDest, nDestWidth, nDestHeight, 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, dwRop ) : FALSE );
}

C_BOOL EZ_MemoryDC::StretchBlt( CDC* lpDstDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT dwRop )
{
	return ( lpDstDC ? this->StretchBlt( *lpDstDC, XDest, YDest, nDestWidth, nDestHeight, 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, dwRop ) : FALSE );
}

C_BOOL EZ_MemoryDC::StretchBlt( CDC* lpDstDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_UINT dwRop )
{
	return ( lpDstDC ? this->StretchBlt( *lpDstDC, XDest, YDest, nDestWidth, nDestHeight, XSrc, YSrc, nSrcWidth, nSrcHeight, dwRop ) : FALSE );
}

C_BOOL EZ_MemoryDC::StretchBlt( EZ_MemoryDC& dcDst, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT dwRop )
{
	return this->StretchBlt( dcDst.GetSafeHdc(), XDest, YDest, nDestWidth, nDestHeight, 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, dwRop );
}

C_BOOL EZ_MemoryDC::StretchBlt( EZ_MemoryDC& dcDst, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_UINT dwRop )
{
	return this->StretchBlt( dcDst.GetSafeHdc(), XDest, YDest, nDestWidth, nDestHeight, XSrc, YSrc, nSrcWidth, nSrcHeight, dwRop );
}

//  ==========================================================================
//  StretchBlt by Src-DC
//  ==========================================================================
C_BOOL EZ_MemoryDC::StretchBlt( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, HDC hSrcDC, C_UINT dwRop )
{
	return ( hSrcDC ? this->StretchBlt( XSrc, YSrc, nSrcWidth, nSrcHeight, hSrcDC, 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, dwRop ) : FALSE );
}

C_BOOL EZ_MemoryDC::StretchBlt( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, CDC* lpSrcDC, C_UINT dwRop )
{
	return ( lpSrcDC ? this->StretchBlt( XSrc, YSrc, nSrcWidth, nSrcHeight, *lpSrcDC, 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, dwRop ) : FALSE );
}

C_BOOL EZ_MemoryDC::StretchBlt( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, CDC* lpSrcDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT dwRop )
{
	return ( lpSrcDC ? this->StretchBlt( XSrc, YSrc, nSrcWidth, nSrcHeight, *lpSrcDC, XDest, YDest, nDestWidth, nDestHeight, dwRop ) : FALSE );
}

C_BOOL EZ_MemoryDC::StretchBlt( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, EZ_MemoryDC& dcSrc, C_UINT dwRop )
{
	return this->StretchBlt( XSrc, YSrc, nSrcWidth, nSrcHeight, dcSrc.GetSafeHdc(), 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, dwRop );
}

C_BOOL EZ_MemoryDC::StretchBlt( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, EZ_MemoryDC& dcSrc, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT dwRop )
{
	return this->StretchBlt( XSrc, YSrc, nSrcWidth, nSrcHeight, dcSrc.GetSafeHdc(), XDest, YDest, nDestWidth, nDestHeight, dwRop );
}

//  ==========================================================================
//  StretchDIBits by Src-BitmapInfo
//  ==========================================================================
C_BOOL EZ_MemoryDC::StretchDIBits( EZ_MemoryDC& dcSrc, C_UINT iUsage, C_UINT dwRop )
{
	return this->StretchDIBits( &dcSrc.m_bmpHeader, dcSrc.m_pBmpBuf, 0, 0, dcSrc.m_bmpHeader.biWidth, dcSrc.m_bmpHeader.biHeight, 
		0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, iUsage, dwRop );
}

C_BOOL EZ_MemoryDC::StretchDIBits( EZ_MemoryDC& dcSrc, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT iUsage, C_UINT dwRop )
{
	return this->StretchDIBits( &dcSrc.m_bmpHeader, dcSrc.m_pBmpBuf, 0, 0, dcSrc.m_bmpHeader.biWidth, dcSrc.m_bmpHeader.biHeight, XDest, YDest, nDestWidth, nDestHeight, iUsage, dwRop );
}

C_BOOL EZ_MemoryDC::StretchDIBits( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, EZ_MemoryDC& dcSrc, C_UINT iUsage, C_UINT dwRop )
{
	return this->StretchDIBits( &dcSrc.m_bmpHeader, dcSrc.m_pBmpBuf, XSrc, YSrc, nSrcWidth, nSrcHeight, 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, iUsage, dwRop );
}

C_BOOL EZ_MemoryDC::StretchDIBits( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, EZ_MemoryDC& dcSrc, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT iUsage, C_UINT dwRop )
{
	return this->StretchDIBits( &dcSrc.m_bmpHeader, dcSrc.m_pBmpBuf, XSrc, YSrc, nSrcWidth, nSrcHeight, XDest, YDest, nDestWidth, nDestHeight, iUsage, dwRop );
}

C_BOOL EZ_MemoryDC::StretchDIBits( LPCBITMAPINFOHEADER lpHeader, LPCBYTE lpData, C_UINT iUsage, C_UINT dwRop )
{
	return ( lpHeader ? this->StretchDIBits( lpHeader, lpData, 0, 0, lpHeader->biWidth, lpHeader->biHeight, 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, iUsage, dwRop ) : FALSE );
}

C_BOOL EZ_MemoryDC::StretchDIBits( LPCBITMAPINFOHEADER lpHeader, LPCBYTE lpData, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_UINT iUsage, C_UINT dwRop )
{
	return ( lpHeader ? this->StretchDIBits( lpHeader, lpData, XSrc, YSrc, nSrcWidth, nSrcHeight, 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, iUsage, dwRop ) : FALSE );
}

C_BOOL EZ_MemoryDC::StretchDIBits( LPCBITMAPINFO lpBitmap, C_UINT iUsage, C_UINT dwRop )
{
	return ( lpBitmap ? this->StretchDIBits( &lpBitmap->bmiHeader, ( LPBYTE )lpBitmap->bmiColors, 0, 0, lpBitmap->bmiHeader.biWidth, lpBitmap->bmiHeader.biHeight, 
		0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, iUsage, dwRop ) : FALSE );
}

C_BOOL EZ_MemoryDC::StretchDIBits( LPCBITMAPINFO lpBitmap, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_UINT iUsage, C_UINT dwRop )
{
	return ( lpBitmap ? this->StretchDIBits( &lpBitmap->bmiHeader, ( LPBYTE )lpBitmap->bmiColors, XSrc, YSrc, nSrcWidth, nSrcHeight, 
		0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, iUsage, dwRop ) : FALSE );
}

C_BOOL EZ_MemoryDC::StretchDIBits( LPCBITMAPINFO lpBitmap, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT iUsage, C_UINT dwRop )
{
	return ( lpBitmap ? this->StretchDIBits( &lpBitmap->bmiHeader, ( LPBYTE )lpBitmap->bmiColors, XSrc, YSrc, nSrcWidth, nSrcHeight, XDest, YDest, nDestWidth, nDestHeight, iUsage, dwRop ) : FALSE );
}

C_BOOL EZ_MemoryDC::StretchDIBits( LPEZBITMAPINFO lpBitmap, C_UINT iUsage, C_UINT dwRop )
{
	return ( lpBitmap ? this->StretchDIBits( &lpBitmap->m_Header, lpBitmap->m_Colors, 0, 0, lpBitmap->m_Header.biWidth, lpBitmap->m_Header.biHeight, 
		0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, iUsage, dwRop ) : FALSE );
}

C_BOOL EZ_MemoryDC::StretchDIBits( LPEZBITMAPINFO lpBitmap, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_UINT iUsage, C_UINT dwRop )
{
	return ( lpBitmap ? this->StretchDIBits( &lpBitmap->m_Header, lpBitmap->m_Colors, XSrc, YSrc, nSrcWidth, nSrcHeight, 
		0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, iUsage, dwRop ) : FALSE );
}

C_BOOL EZ_MemoryDC::StretchDIBits( LPEZBITMAPINFO lpBitmap, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_UINT iUsage, C_UINT dwRop )
{
	return ( lpBitmap ? this->StretchDIBits( &lpBitmap->m_Header, lpBitmap->m_Colors, XSrc, YSrc, nSrcWidth, nSrcHeight, XDest, YDest, nDestWidth, nDestHeight, iUsage, dwRop ) : FALSE );
}

//  ==========================================================================
//  AlphaBlend to Dst-DC
//  ==========================================================================
#if ( _MSC_VER > 1300 )

C_BOOL EZ_MemoryDC::AlphaBlend( HDC hDstDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT iAlpha )
{
	return ( hDstDC ? this->AlphaBlend( hDstDC, XDest, YDest, nDestWidth, nDestHeight, 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, iAlpha ) : FALSE );
}

C_BOOL EZ_MemoryDC::AlphaBlend( CDC* lpDstDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT iAlpha )
{
	return ( lpDstDC ? this->AlphaBlend( *lpDstDC, XDest, YDest, nDestWidth, nDestHeight, 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, iAlpha ) : FALSE );
}

C_BOOL EZ_MemoryDC::AlphaBlend( CDC* lpDstDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_INT iAlpha )
{
	return ( lpDstDC ? this->AlphaBlend( *lpDstDC, XDest, YDest, nDestWidth, nDestHeight, XSrc, YSrc, nSrcWidth, nSrcHeight, iAlpha ) : FALSE );
}

C_BOOL EZ_MemoryDC::AlphaBlend( EZ_MemoryDC& dcDst, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT iAlpha )
{
	return this->AlphaBlend( dcDst.GetSafeHdc(), XDest, YDest, nDestWidth, nDestHeight, 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, iAlpha );
}

C_BOOL EZ_MemoryDC::AlphaBlend( EZ_MemoryDC& dcDst, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_INT iAlpha )
{
	return this->AlphaBlend( dcDst.GetSafeHdc(), XDest, YDest, nDestWidth, nDestHeight, XSrc, YSrc, nSrcWidth, nSrcHeight, iAlpha );
}

#endif

//  ==========================================================================
//  AlphaBlend by Src-DC
//  ==========================================================================
#if ( _MSC_VER > 1300 )

C_BOOL EZ_MemoryDC::AlphaBlend( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, HDC hSrcDC, C_INT iAlpha )
{
	return ( hSrcDC ? this->AlphaBlend( XSrc, YSrc, nSrcWidth, nSrcHeight, hSrcDC, 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, iAlpha ) : FALSE );
}

C_BOOL EZ_MemoryDC::AlphaBlend( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, CDC* lpSrcDC, C_INT iAlpha )
{
	return ( lpSrcDC ? this->AlphaBlend( XSrc, YSrc, nSrcWidth, nSrcHeight, *lpSrcDC, 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, iAlpha ) : FALSE );
}

C_BOOL EZ_MemoryDC::AlphaBlend( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, CDC* lpSrcDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT iAlpha )
{
	return ( lpSrcDC ? this->AlphaBlend( XSrc, YSrc, nSrcWidth, nSrcHeight, *lpSrcDC, XDest, YDest, nDestWidth, nDestHeight, iAlpha ) : FALSE );
}

C_BOOL EZ_MemoryDC::AlphaBlend( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, EZ_MemoryDC& dcSrc, C_INT iAlpha )
{
	return this->AlphaBlend( XSrc, YSrc, nSrcWidth, nSrcHeight, dcSrc.GetSafeHdc(), 0, 0, EZ_MemoryBmp::m_bmpHeader.biWidth, EZ_MemoryBmp::m_bmpHeader.biHeight, iAlpha );
}

C_BOOL EZ_MemoryDC::AlphaBlend( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, EZ_MemoryDC& dcSrc, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT iAlpha )
{
	return this->AlphaBlend( XSrc, YSrc, nSrcWidth, nSrcHeight, dcSrc.GetSafeHdc(), XDest, YDest, nDestWidth, nDestHeight, iAlpha );
}

#endif
