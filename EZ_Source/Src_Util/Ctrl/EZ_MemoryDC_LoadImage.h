#if defined ( _USE_GDI_PLUS_DLL_ )

//  ==========================================================================
//  LoadImageList
//  ==========================================================================
#if ( _WIN32_WINNT >= 0x0600 )
HIMAGELIST LoadImageList( const WORD nResID, const int nFixSize, const COLORREF crMask )
{
	//  
	HINSTANCE  hInstance = ::AfxGetInstanceHandle();
	HIMAGELIST hImgList  = ::ImageList_LoadImage( hInstance, MAKEINTRESOURCE( nResID ), 0, 0, crMask, IMAGE_BITMAP, ( LR_CREATEDIBSECTION | LR_LOADTRANSPARENT ) );

	if ( hImgList == NULL )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] LoadImageList - ImageList_LoadImage ! ( ResID : %d )\n" ), nResID );
		return NULL;
	}

	//  
	int nCnt = ::ImageList_GetImageCount( hImgList );
	int nCX  = 0;
	int nCY  = 0;

	::ImageList_GetIconSize( hImgList, &nCX, &nCY );

	if ( nFixSize == nCY )
	{
#if ( defined ( _DEBUG ) || defined ( _RSEDBG ) )
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] LoadImageList - ImageList_LoadImage ! ( ResID : %d, ImgCnt : %d  )\n" ), nResID, nCnt );
#endif

		return hImgList;
	}

	//  
	const int  nFlags      = ( ILC_COLOR24 | ILC_MASK | ILC_HIGHQUALITYSCALE );
	HIMAGELIST hImgListNew = ::ImageList_Create( nFixSize, nFixSize, nFlags, nCnt, 0 );

	if ( hImgListNew == NULL )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] LoadImageList - ImageList_Create ! ( ImgWidth : %d, ImgCnt : %d )\n" ), nFixSize, nCnt );
		return hImgList;
	}

	//  
	HICON hIcon = NULL;

	for ( int i = 0; i < nCnt; i++ )
	{
		hIcon = ::ImageList_GetIcon( hImgList, i, 0 );

		if ( !hIcon )
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] LoadImageList - ImageList_GetIcon ! ( Index : %d )\n" ), i );
		else if ( ::ImageList_AddIcon( hImgListNew, hIcon ) < 0 )
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] LoadImageList - ImageList_AddIcon ! ( Index : %d )\n" ), i );
	}

	::ImageList_Destroy( hImgList );

	return hImgListNew;
}
#endif

//  ==========================================================================
//  
//  ==========================================================================
EZ_CriticalSectionImage::EZ_CriticalSectionImage() : CImage(), EZ_CriticalSection()
{
	;
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_CriticalSectionImage::~EZ_CriticalSectionImage()
{
	this->Destroy();
}

//  ==========================================================================
//  Destroy
//  ==========================================================================
void EZ_CriticalSectionImage::Destroy()
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  Destroy
#if defined ( _USE_TRY_CATCH_ )
	try
#endif
	{
		CImage::Destroy();
	}
#if defined ( _USE_TRY_CATCH_ )
	catch ( ... )
	{
		::OutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] Destroy - Exception !\n" ) );
	}
#endif
}

//  ==========================================================================
//  LoadFromResource
//  ==========================================================================
void EZ_CriticalSectionImage::LoadFromResource( HINSTANCE hInstance, UINT nIDResource )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  LoadFromResource
#if defined ( _USE_TRY_CATCH_ )
	try
#endif
	{
		CImage::LoadFromResource( hInstance, nIDResource );
	}
#if defined ( _USE_TRY_CATCH_ )
	catch ( ... )
	{
		::OutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] LoadFromResource - Exception ! ( ID : '' )\n" ) );
	}
#endif
}

void EZ_CriticalSectionImage::LoadFromResource( HINSTANCE hInstance, LPCTSTR lpResourceName )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  LoadFromResource
#if defined ( _USE_TRY_CATCH_ )
	try
#endif
	{
		CImage::LoadFromResource( hInstance, lpResourceName );
	}
#if defined ( _USE_TRY_CATCH_ )
	catch ( ... )
	{
		::OutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] LoadFromResource - Exception ! ( Name : '' )\n" ) );
	}
#endif
}

//  ==========================================================================
//  LoadFromResPNG
//  ==========================================================================
BOOL EZ_CriticalSectionImage::LoadFromResPNG( HINSTANCE hInstance, UINT nIDResource )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  LoadFromResource
	BOOL bResult = FALSE;

#if defined ( _USE_TRY_CATCH_ )
	try
#endif
	{
		bResult = EZ_CriticalSectionImage::LoadFromResPNG( *this, hInstance, nIDResource );
	}
#if defined ( _USE_TRY_CATCH_ )
	catch ( ... )
	{
		::OutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] LoadFromResPNG - Exception ! ( ID : '' )\n" ) );
	}
#endif

	return bResult;
}

BOOL EZ_CriticalSectionImage::LoadFromResPNG( HINSTANCE hInstance, LPCTSTR lpResourceName )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  LoadFromResource
	BOOL bResult = FALSE;

#if defined ( _USE_TRY_CATCH_ )
	try
#endif
	{
		bResult = EZ_CriticalSectionImage::LoadFromResPNG( *this, hInstance, lpResourceName );
	}
#if defined ( _USE_TRY_CATCH_ )
	catch ( ... )
	{
		::OutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] LoadFromResPNG - Exception ! ( Name : '' )\n" ) );
	}
#endif

	return bResult;
}

//  ==========================================================================
//  Load
//  ==========================================================================
HRESULT EZ_CriticalSectionImage::Load( LPCTSTR lpFileName )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  Load
	HRESULT hResult = S_FALSE;

#if defined ( _USE_TRY_CATCH_ )
	try
#endif
	{
		hResult = CImage::Load( lpFileName );
	}
#if defined ( _USE_TRY_CATCH_ )
	catch ( ... )
	{
		::OutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] Load - Exception ! ( File : '' )\n" ) );
	}
#endif

	return hResult;
}

//  ==========================================================================
//  Draw
//  ==========================================================================
BOOL EZ_CriticalSectionImage::Draw( HDC hDestDC, const POINT& ptDest )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  Draw ( 32 BPP Image 須強制用 AlphaBlend 繪製，才能有正常透明背景 )
	BOOL bResult = FALSE;

#if defined ( _USE_TRY_CATCH_ )
	try
#endif
	{
		if ( CImage::GetBPP() != 32 )
			bResult = CImage::Draw( hDestDC, ptDest );
		else
		{
			BLENDFUNCTION dtBlendFun;

			dtBlendFun.BlendOp             = AC_SRC_OVER;
			dtBlendFun.BlendFlags          = 0;
			dtBlendFun.SourceConstantAlpha = 0xFF;
			dtBlendFun.AlphaFormat         = AC_SRC_ALPHA;

			bResult = ::AlphaBlend( hDestDC, ptDest.x, ptDest.y, CImage::GetWidth(), CImage::GetHeight(),
				CImage::GetDC(), 0, 0, CImage::GetWidth(), CImage::GetHeight(), dtBlendFun );
			CImage::ReleaseDC();
		}
	}
#if defined ( _USE_TRY_CATCH_ )
	catch ( ... )
	{
		::OutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] Draw - Exception ! ( POINT )\n" ) );
	}
#endif

	return bResult;
}

BOOL EZ_CriticalSectionImage::Draw( HDC hDestDC, const RECT& rcDest )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  Draw
	BOOL bResult = FALSE;

#if defined ( _USE_TRY_CATCH_ )
	try
#endif
	{
		if ( CImage::GetBPP() != 32 )
			bResult = CImage::Draw( hDestDC, rcDest );
		else
		{
			BLENDFUNCTION dtBlendFun;

			dtBlendFun.BlendOp             = AC_SRC_OVER;
			dtBlendFun.BlendFlags          = 0;
			dtBlendFun.SourceConstantAlpha = 0xFF;
			dtBlendFun.AlphaFormat         = AC_SRC_ALPHA;

			bResult = ::AlphaBlend( hDestDC, rcDest.left, rcDest.top, ( rcDest.right - rcDest.left ), ( rcDest.bottom - rcDest.top ),
				CImage::GetDC(), 0, 0, CImage::GetWidth(), CImage::GetHeight(), dtBlendFun );
			CImage::ReleaseDC();
		}
	}
#if defined ( _USE_TRY_CATCH_ )
	catch ( ... )
	{
		::OutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] Draw - Exception ! ( RECT )\n" ) );
	}
#endif

	return bResult;
}

BOOL EZ_CriticalSectionImage::Draw( HDC hDestDC, int xDest, int yDest )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  Draw
	BOOL bResult = FALSE;

#if defined ( _USE_TRY_CATCH_ )
	try
#endif
	{
		if ( CImage::GetBPP() != 32 )
			bResult = CImage::Draw( hDestDC, xDest, yDest );
		else
		{
			BLENDFUNCTION dtBlendFun;

			dtBlendFun.BlendOp             = AC_SRC_OVER;
			dtBlendFun.BlendFlags          = 0;
			dtBlendFun.SourceConstantAlpha = 0xFF;
			dtBlendFun.AlphaFormat         = AC_SRC_ALPHA;

			bResult = ::AlphaBlend( hDestDC, xDest, yDest, CImage::GetWidth(), CImage::GetHeight(),
				CImage::GetDC(), 0, 0, CImage::GetWidth(), CImage::GetHeight(), dtBlendFun );
			CImage::ReleaseDC();
		}
	}
#if defined ( _USE_TRY_CATCH_ )
	catch ( ... )
	{
		::OutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] Draw - Exception ! ( INT )\n" ) );
	}
#endif

	return bResult;
}

BOOL EZ_CriticalSectionImage::Draw( HDC hDestDC, const RECT& rcDest, const RECT& rcSrc )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  Draw
	BOOL bResult = FALSE;

#if defined ( _USE_TRY_CATCH_ )
	try
#endif
	{
		if ( CImage::GetBPP() != 32 )
			bResult = CImage::Draw( hDestDC, rcDest, rcSrc );
		else
		{
			BLENDFUNCTION dtBlendFun;

			dtBlendFun.BlendOp             = AC_SRC_OVER;
			dtBlendFun.BlendFlags          = 0;
			dtBlendFun.SourceConstantAlpha = 0xFF;
			dtBlendFun.AlphaFormat         = AC_SRC_ALPHA;

			bResult = ::AlphaBlend( hDestDC, rcDest.left, rcDest.top, ( rcDest.right - rcDest.left ), ( rcDest.bottom - rcDest.top ),
				CImage::GetDC(), rcSrc.left, rcSrc.top, ( rcSrc.right - rcSrc.left ), ( rcSrc.bottom - rcSrc.top ), dtBlendFun );
			CImage::ReleaseDC();
		}
	}
#if defined ( _USE_TRY_CATCH_ )
	catch ( ... )
	{
		::OutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] Draw - Exception ! ( RECT, RECT )\n" ) );
	}
#endif

	return bResult;
}

BOOL EZ_CriticalSectionImage::Draw( HDC hDestDC, int xDest, int yDest, int nDestWidth, int nDestHeight )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  Draw
	BOOL bResult = FALSE;

#if defined ( _USE_TRY_CATCH_ )
	try
#endif
	{
		if ( CImage::GetBPP() != 32 )
			bResult = CImage::Draw( hDestDC, xDest, yDest, nDestWidth, nDestHeight );
		else
		{
			BLENDFUNCTION dtBlendFun;

			dtBlendFun.BlendOp             = AC_SRC_OVER;
			dtBlendFun.BlendFlags          = 0;
			dtBlendFun.SourceConstantAlpha = 0xFF;
			dtBlendFun.AlphaFormat         = AC_SRC_ALPHA;

			bResult = ::AlphaBlend( hDestDC, xDest, yDest, nDestWidth, nDestHeight,
				CImage::GetDC(), 0, 0, CImage::GetWidth(), CImage::GetHeight(), dtBlendFun );
			CImage::ReleaseDC();
		}
	}
#if defined ( _USE_TRY_CATCH_ )
	catch ( ... )
	{
		::OutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] Draw - Exception ! ( INT, INT, INT, INT )\n" ) );
	}
#endif

	return bResult;
}

BOOL EZ_CriticalSectionImage::Draw( HDC hDestDC, int xDest, int yDest, int nDestWidth, int nDestHeight, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  Draw
	BOOL bResult = FALSE;

#if defined ( _USE_TRY_CATCH_ )
	try
#endif
	{
		if ( CImage::GetBPP() != 32 )
			bResult = CImage::Draw( hDestDC, xDest, yDest, nDestWidth, nDestHeight, xSrc, ySrc, nSrcWidth, nSrcHeight );
		else
		{
			BLENDFUNCTION dtBlendFun;

			dtBlendFun.BlendOp             = AC_SRC_OVER;
			dtBlendFun.BlendFlags          = 0;
			dtBlendFun.SourceConstantAlpha = 0xFF;
			dtBlendFun.AlphaFormat         = AC_SRC_ALPHA;

			bResult = ::AlphaBlend( hDestDC, xDest, yDest, nDestWidth, nDestHeight,
				CImage::GetDC(), xSrc, ySrc, nSrcWidth, nSrcHeight, dtBlendFun );
			CImage::ReleaseDC();
		}
	}
#if defined ( _USE_TRY_CATCH_ )
	catch ( ... )
	{
		::OutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] Draw - Exception ! ( INT, INT, INT, INT, INT, INT, INT, INT )\n" ) );
	}
#endif

	return bResult;
}

//  ==========================================================================
//  IsNull
//  ==========================================================================
bool EZ_CriticalSectionImage::IsNull()
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  IsNull
	bool bResult = false;

#if defined ( _USE_TRY_CATCH_ )
	try
#endif
	{
		bResult = CImage::IsNull();
	}
#if defined ( _USE_TRY_CATCH_ )
	catch ( ... )
	{
		::OutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] IsNull - Exception !\n" ) );
	}
#endif

	return bResult;
}

//  ==========================================================================
//  GetWidth
//  ==========================================================================
int EZ_CriticalSectionImage::GetWidth()
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  GetWidth
	int iWidth = 0;

#if defined ( _USE_TRY_CATCH_ )
	try
#endif
	{
		iWidth = CImage::GetWidth();
	}
#if defined ( _USE_TRY_CATCH_ )
	catch ( ... )
	{
		::OutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] GetWidth - Exception !\n" ) );
	}
#endif

	return iWidth;
}

//  ==========================================================================
//  GetHeight
//  ==========================================================================
int EZ_CriticalSectionImage::GetHeight()
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  GetHeight
	int iHeight = 0;

#if defined ( _USE_TRY_CATCH_ )
	try
#endif
	{
		iHeight = CImage::GetHeight();
	}
#if defined ( _USE_TRY_CATCH_ )
	catch ( ... )
	{
		::OutputDebugString( _T( "$$$ [ 235-EZ_CriticalSectionImage ] GetHeight - Exception !\n" ) );
	}
#endif

	return iHeight;
}

//  ==========================================================================
//  Process32BPP
//  ==========================================================================
void EZ_CriticalSectionImage::Process32BPP( C_BOOL bInvertOpacity, C_BOOL bPreMultiply, const COLORREF crTransparentClr )
{
	//  
	if ( CImage::IsNull() || ( CImage::GetBPP() != 32 ) )
	{
		;
		return;
	}

	//  
	BYTE byRed   = 0;
	BYTE byGreen = 0;
	BYTE byBlue  = 0;

	if ( crTransparentClr != -1 )
	{
		byRed   = GetRValue( crTransparentClr );
		byGreen = GetEZalue( crTransparentClr );
		byBlue  = GetBValue( crTransparentClr );
	}

	//  
	C_INT  iWidth  = CImage::GetWidth();
	C_INT  iHeight = CImage::GetHeight();
	LPBYTE lpByte  = NULL;

	for ( INT i = 0, j/*, k, iValue*/; i < iWidth; ++i )
	{
		for ( j = 0 ; j < iHeight; ++j )
		{
			lpByte = ( LPBYTE )CImage::GetPixelAddress( i, j );

			if ( bInvertOpacity )
			{	//  若需要反轉透明度 ( 255 = 不透明, 0 = 透明 )
				lpByte[ 3 ] = ( 255 - lpByte[ 3 ] );
			}

			if ( crTransparentClr != -1 )
			{	//  若有指定透明色遮罩
				if ( ( byBlue == lpByte[ 0 ] ) && ( byGreen == lpByte[ 1 ] ) && ( byRed == lpByte[ 2 ] ) )
					lpByte[ 0 ] = lpByte[ 1 ] = lpByte[ 2 ] = lpByte[ 3 ] = 0;
			}

			if ( bPreMultiply )
			{	//  使用 CImage 載入 PNG 或 BMP 若未做預乘處理，需要進行轉換才能得到正常背景透明的圖片
#if 0
				for ( k = 0; k < 3; k++ )
				{
					iValue       = lpByte[ k ];
					iValue      *= lpByte[ 3 ];
					iValue      += 127;
					iValue      /= 255;
					lpByte[ k ]  = ( BYTE )iValue;
				}
#else
				lpByte[ 0 ] = ( ( ( lpByte[ 0 ] * lpByte[ 3 ] ) + 127 ) / 255 );
				lpByte[ 1 ] = ( ( ( lpByte[ 1 ] * lpByte[ 3 ] ) + 127 ) / 255 );
				lpByte[ 2 ] = ( ( ( lpByte[ 2 ] * lpByte[ 3 ] ) + 127 ) / 255 );
#endif
			}
		}
	}
}

//  ==========================================================================
//  GetHeader ( Static )
//  ==========================================================================
void EZ_CriticalSectionImage::GetHeader( CImage& objImage, BITMAPINFOHEADER& infoBmpHeader )
{
	infoBmpHeader.biSize          = sizeof( BITMAPINFOHEADER );
	infoBmpHeader.biWidth         = objImage.GetWidth();
	infoBmpHeader.biHeight        = objImage.GetHeight();
	infoBmpHeader.biPlanes        = 1;
	infoBmpHeader.biBitCount      = objImage.GetBPP();
	infoBmpHeader.biCompression   = 0;
	infoBmpHeader.biSizeImage     = ( infoBmpHeader.biWidth * infoBmpHeader.biHeight * ( infoBmpHeader.biBitCount >> 3 ) );
	infoBmpHeader.biXPelsPerMeter = 0;
	infoBmpHeader.biYPelsPerMeter = 0;
	infoBmpHeader.biClrUsed       = 0;
	infoBmpHeader.biClrImportant  = 0;
}

//  ==========================================================================
//  LoadFromResPNG ( Static )
//  ==========================================================================
BOOL EZ_CriticalSectionImage::LoadFromResPNG( CImage& objImage, HINSTANCE hInstance, UINT nIDResource )
{
	return EZ_CriticalSectionImage::LoadFromResPNG( objImage, hInstance, MAKEINTRESOURCE( nIDResource ) );
}

BOOL EZ_CriticalSectionImage::LoadFromResPNG( CImage& objImage, HINSTANCE hInstance, LPCTSTR lpResourceName )
{
	//  
	if ( hInstance == NULL )
	{
		hInstance = ::AfxFindResourceHandle( lpResourceName, _T( "PNG" ) );
		;
	}

	//  
	HRSRC hRSrc = ::FindResource( hInstance, lpResourceName, _T( "PNG" ) );

	if ( hRSrc == NULL )
	{
		;
		return FALSE;
	}

	//  
	HGLOBAL hGlobal = LoadResource( hInstance, hRSrc );

	if ( hGlobal == NULL )
	{
		;
		return FALSE;
	}

	//  
	LPBYTE lpBuffer = ( LPBYTE )::LockResource( hGlobal );

	if ( lpBuffer == NULL )
	{
		::FreeResource( hGlobal );
		return FALSE;
	}

	//  
	BOOL bResult = FALSE;

	{
		UINT    uiSize = ::SizeofResource( hInstance, hRSrc );
		HGLOBAL hRes   = ::GlobalAlloc( GMEM_MOVEABLE, uiSize );

		if ( hRes != NULL )
		{
			//  
			LPVOID lpResBuffer = ::GlobalLock( hRes );

			if ( lpResBuffer )
			{
				::memcpy( lpResBuffer, lpBuffer, uiSize );

				::GlobalUnlock( hRes );
			}

			//  
			IStream* lpStream = NULL;

			if ( ::CreateStreamOnHGlobal( hRes, TRUE, &lpStream ) == S_OK )
			{
				objImage.Destroy();

				if ( objImage.Load( lpStream ) == S_OK )
					bResult = TRUE;

				lpStream->Release();
			}

			::GlobalFree( hRes );
		}

		::UnlockResource( hGlobal );
		::FreeResource( hGlobal );
	}

	return bResult;
}

#endif

//  ==========================================================================
//  AlphaBlend to Dst-DC
//  ==========================================================================
C_BOOL EZ_MemoryDC::AlphaBlend( HDC hDstDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, C_INT iAlpha )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  AlphaBlend
	BOOL bResult = FALSE;

	if ( this->m_pMemDC && hDstDC )
	{
		//
		BLENDFUNCTION funBlend;

		funBlend.BlendOp             = AC_SRC_OVER;
		funBlend.BlendFlags          = 0;
		funBlend.SourceConstantAlpha = iAlpha;
		funBlend.AlphaFormat         = AC_SRC_ALPHA;

		//
#if defined ( _USE_TRY_CATCH_ )
		try
#endif
		{
			bResult = ::AlphaBlend( hDstDC, XDest, YDest, nDestWidth, nDestHeight, *this->m_pMemDC, XSrc, YSrc, nSrcWidth, nSrcHeight, funBlend );
		}
#if defined ( _USE_TRY_CATCH_ )
		catch ( ... )
		{
			::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] AlphaBlendToDstDC - Exception !\n" ) );
		}
#endif
	}

	return bResult;
}

//  ==========================================================================
//  AlphaBlend by Src-DC
//  ==========================================================================
C_BOOL EZ_MemoryDC::AlphaBlend( C_INT XSrc, C_INT YSrc, C_INT nSrcWidth, C_INT nSrcHeight, HDC hSrcDC, C_INT XDest, C_INT YDest, C_INT nDestWidth, C_INT nDestHeight, C_INT iAlpha )
{
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  AlphaBlend
	BOOL bResult = FALSE;

	if ( this->m_pMemDC && hSrcDC )
	{
		//
		BLENDFUNCTION funBlend;

		funBlend.BlendOp             = AC_SRC_OVER;
		funBlend.BlendFlags          = 0;
		funBlend.SourceConstantAlpha = iAlpha;
		funBlend.AlphaFormat         = AC_SRC_ALPHA;

		//
#if defined ( _USE_TRY_CATCH_ )
		try
#endif
		{
			bResult = ::AlphaBlend( *this->m_pMemDC, XDest, YDest, nDestWidth, nDestHeight, hSrcDC, XSrc, YSrc, nSrcWidth, nSrcHeight, funBlend );
		}
#if defined ( _USE_TRY_CATCH_ )
		catch ( ... )
		{
			::OutputDebugString( _T( "$$$ [ 235-EZ_MemoryDC ] AlphaBlendFromSrcDC - Exception !\n" ) );
		}
#endif
	}

	return bResult;
}

//  ==========================================================================
//  Load Image
//  ==========================================================================
C_BOOL EZ_MemoryDC::LoadImage( LPCTSTR lpImgFile, CDC* lpDC )
{	
	BOOL bResult = FALSE;

#if defined ( _USE_GDI_PLUS_DLL_ )
	if ( lpImgFile && ( ::_tcslen( lpImgFile ) > 0 ) )
	{
		CImage objImage;

		if ( objImage.Load( lpImgFile ) == 0 )
		{
			if ( this->CreateDC( lpDC, objImage.GetWidth(), objImage.GetHeight(), 1, objImage.GetBPP(), TRUE ) ) 
			{
				this->SetStretchBltMode( COLORONCOLOR );
				this->SetBkMode( TRANSPARENT );

				if ( objImage.Draw( this->GetSafeHdc(), 0, 0 ) )
					bResult = TRUE;
				else
					this->ReleaseDC();
			}
		}
	}
#endif

	return bResult;
}

C_BOOL EZ_MemoryDC::LoadImage( LPCTSTR lpImgFile, CDC* lpDC, LPBITMAPINFO& lpBitmap, C_BOOL bDecodeBuf )
{	
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  LoadImage
	BOOL bResult = FALSE;

	if ( this->LoadImage( lpImgFile, lpDC ) )
	{
		C_INT iImageSize = ( EZ_MemoryBmp::m_bmpHeader.biWidth * EZ_MemoryBmp::m_bmpHeader.biHeight * 4 );
		C_INT iAllocSize = ( bDecodeBuf ? ( iImageSize + 1024 ) : iImageSize );

		{
			bResult = ::CreateAlignedBuf( ( LPBYTE& )lpBitmap, iAllocSize );

			if ( bResult )
			{
				::memcpy( &lpBitmap->bmiHeader, &( EZ_MemoryBmp::m_bmpHeader ), sizeof( BITMAPINFOHEADER ) );

				::memcpy( lpBitmap->bmiColors, this->GetBitmapBuf(), lpBitmap->bmiHeader.biSizeImage );
			}
		}
	}

	return bResult;
}

C_BOOL EZ_MemoryDC::LoadImage( LPCTSTR lpImgFile, CDC* lpDC, LPEZBITMAPINFO& lpBitmap, C_BOOL bDecodeBuf )
{	
	//  Lock ( Into ) and Unlock ( Exit )
	EZ_CriticalSectionLock csLock( *this );

	//  LoadImage
	BOOL bResult = FALSE;

	if ( this->LoadImage( lpImgFile, lpDC ) )
	{
		C_INT iImageSize = ( EZ_MemoryBmp::m_bmpHeader.biWidth * EZ_MemoryBmp::m_bmpHeader.biHeight * 4 );
		C_INT iAllocSize = ( bDecodeBuf ? ( iImageSize + 1024 ) : iImageSize );

		{
			bResult = EZ_BitmapInfo::CreateEZBitmapInfoBuf( lpBitmap, iAllocSize );

			if ( bResult )
			{
				//  Copy Header
				lpBitmap->SetHeader( EZ_MemoryBmp::m_bmpHeader );

				//  Copy Data
				::memcpy( lpBitmap->m_Colors, this->GetBitmapBuf(), lpBitmap->m_Header.biSizeImage );
			}
		}
	}

	return bResult;
}
