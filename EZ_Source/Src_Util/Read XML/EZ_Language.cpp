#include "stdafx.h"
#include "EZ_Language.h"
#include "..\Thread\EZ_Mutex.h"

//  ==========================================================================
//  
//  ==========================================================================
CString EZ_Language::gm_LangNoteText[ EZ_LANG_COUNT ] =
{
	_T( "EN"  ), _T( "SC"  ), _T( "TC"  ), _T( "FRA" ), _T( "GEM" ), _T( "JPN" ), _T( "POL" ), _T( "PTU" ), _T( "RUS" ), _T( "SPN" ),
	_T( "ARB" ), _T( "HEB" ), _T( "HUN" ), _T( "CZH" ), _T( "ITA" ), _T( "NLD" ), _T( "DAN" ), _T( "TAI" ), _T( "SRL" ), _T( "PRS" ), 
	_T( "EN"  ),
};

//  ==========================================================================
//  
//  ==========================================================================
EZ_Language::EZ_Language( C_EZ_LANG_ID langID, C_INT iSubID ) 
		   : EZ_MSXMLInterface(), m_bRTLStyle( FALSE ), m_iLangExID( iSubID ), m_iLangID( langID ), m_pNewFont( NULL ), m_aryLangExInfo()
{
	;
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_Language::~EZ_Language()
{  
	this->Close();
}

//  ==========================================================================
//  Open
//  ==========================================================================
C_BOOL EZ_Language::Open( LPCTSTR lpFileName, EZ_LANG_ID iEZLangID, CDC* lpDC )
{
	C_BOOL bResult = EZ_MSXMLInterface::Open( lpFileName );

	if ( bResult ) 
	{
		//  Get Newest Language
		this->ReadNewestLanguage();

		//  Get User Defined Default Language ID
		INT        iSubID      = 0;
		EZ_LANG_ID ezUDLangID = EZ_LANG_DEFA;

		if ( this->ReadUDDefaultLanID( ezUDLangID, iSubID ) )
			iEZLangID = ezUDLangID;

		//  Get Correct Language ID
		if ( iEZLangID == EZ_LANG_DEFA )
			this->GetOSLangID();
		else if ( iEZLangID <= EZ_LANG_NEWEST )
			this->SetCurLangID( iEZLangID, iSubID );
		else
		{
			this->m_bRTLStyle = FALSE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_ENG;
		}	

		//  Create Font
		this->CreateFont( lpDC );
	}

	return bResult;
}

//  ==========================================================================
//  Close
//  ==========================================================================
void EZ_Language::Close()
{
	EZ_MSXMLInterface::Close();

	{
		this->m_bRTLStyle = FALSE;
		this->m_iLangExID = 0;
		this->m_iLangID   = EZ_LANG_ENG;

		this->ReleaseFont();

		this->m_aryLangExInfo.RemoveAll();
	}
}

//  ==========================================================================
//  GetOSLangID
//  ==========================================================================
void EZ_Language::GetOSLangID()
{
	INT               iPrimaryID = 0;
	INT               iSubID     = 0;
	const EZ_LANG_ID iEZLangID = EZ_Language::GetSystemLanguage( iPrimaryID, iSubID );

	if ( iEZLangID != EZ_LANG_NEWEST )
		this->SetCurLangID( iEZLangID );
	else
	{ 
		this->SetCurLangID( EZ_LANG_ENG );

		for ( INT iSize = this->m_aryLangExInfo.GetSize(), i = 0; i < iSize; i++ )
		{
			LPLANGEXTARINFO lpLangInfo = this->m_aryLangExInfo.GetPointerAt( i );

			if ( lpLangInfo && ( lpLangInfo->m_iPrimaryID == iPrimaryID ) && ( lpLangInfo->m_iSubID == iSubID ) )
			{
				this->m_bRTLStyle = lpLangInfo->m_bRTLStyle;
				this->m_iLangExID = i;
				this->m_iLangID   = EZ_LANG_NEWEST;
				break;
			}
		}
	}
}

//  ==========================================================================
//  SetCurLangID
//  ==========================================================================
void EZ_Language::SetCurLangID( C_EZ_LANG_ID ezLangID, C_INT iSubID )
{
	switch ( ezLangID )
	{
	case EZ_LANG_DEFA:
		{
			this->GetOSLangID();
		}
		break;

	case EZ_LANG_ENG:
		{	//  英文 ( English )
			this->m_bRTLStyle = FALSE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_ENG;
		}
		break;

	case EZ_LANG_SC:
		{	//  簡體中文 ( Simipl. Chinese )
			this->m_bRTLStyle = FALSE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_SC;
		}
		break;

	case EZ_LANG_TC:
		{	//  繁體中文 ( Trad.   Chinese )
			this->m_bRTLStyle = FALSE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_TC;
		}
		break;

	case EZ_LANG_FRA:
		{	//  法文 ( French )
			this->m_bRTLStyle = FALSE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_FRA;
		}
		break;

	case EZ_LANG_GER:
		{	//  德文 ( German )
			this->m_bRTLStyle = FALSE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_GER;
		}
		break;

	case EZ_LANG_JPN:
		{	//  日文 ( Japanese )
			this->m_bRTLStyle = FALSE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_JPN;
		}
		break;

	case EZ_LANG_POL:
		{	//  波蘭文 ( Polish )
			this->m_bRTLStyle = FALSE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_POL;
		}
		break;

	case EZ_LANG_PTU:
		{	//  巴西, 葡萄牙文 ( Portuguese )
			this->m_bRTLStyle = FALSE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_PTU;
		}
		break;

	case EZ_LANG_RUS:
		{	//  俄文 ( Russian )
			this->m_bRTLStyle = FALSE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_RUS;
		}
		break;

	case EZ_LANG_SPN:
		{	//  西班牙文 ( Spanish )
			this->m_bRTLStyle = FALSE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_SPN;
		}
		break;

	case EZ_LANG_ARB:
		{	//  阿拉伯文 ( Arabic )
			this->m_bRTLStyle = TRUE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_ARB;
		}
		break;

	case EZ_LANG_HEB:
		{	//  希伯來文 ( Hebrew )
			this->m_bRTLStyle = TRUE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_HEB;
		}
		break;

	case EZ_LANG_HUN:
		{	//  匈牙利文 ( Hungarian )
			this->m_bRTLStyle = FALSE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_HUN;
		}
		break;

	case EZ_LANG_CZE:
		{	//  捷克文 ( Czech )
			this->m_bRTLStyle = FALSE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_CZE;
		}
		break;

	case EZ_LANG_ITA:
		{	//  義大利文 ( Italian )
			this->m_bRTLStyle = FALSE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_ITA;
		}
		break;

	case EZ_LANG_NLD:
		{	//  荷蘭文 ( Dutch )
			this->m_bRTLStyle = FALSE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_NLD;
		}
		break;

	case EZ_LANG_DAN:
		{	//  丹麥文 ( Danish )
			this->m_bRTLStyle = FALSE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_DAN;
		}
		break;

	case EZ_LANG_TAI:
		{	//  泰文 ( Thailand )
			this->m_bRTLStyle = FALSE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_TAI;
		}
		break;

	case EZ_LANG_SRL:
		{	//  南斯拉夫文 ( Serbian )
			this->m_bRTLStyle = FALSE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_SRL;
		}
		break;

	case EZ_LANG_PRS:
		{	//  波斯文 ( Persian )
			this->m_bRTLStyle = TRUE;
			this->m_iLangExID = 0;
			this->m_iLangID   = EZ_LANG_PRS;
		}
		break;

	case EZ_LANG_NEWEST:
		{
			LPLANGEXTARINFO lpLanExInfo = this->m_aryLangExInfo.GetPointerAt( iSubID );

			if ( lpLanExInfo )
			{
				this->m_bRTLStyle = lpLanExInfo->m_bRTLStyle;
				this->m_iLangExID = iSubID;
				this->m_iLangID   = EZ_LANG_NEWEST;
			}
			else
			{
				this->m_bRTLStyle = FALSE;
				this->m_iLangExID = 0;
				this->m_iLangID   = EZ_LANG_ENG;
			}
		}
		break;

	case EZ_LANG_COUNT:
	default:
		{	//  Error 
			ASSERT ( 0 );
		}
		break;
	}
}

//  ==========================================================================
//  ReadNewestLanguage
//  ==========================================================================
void EZ_Language::ReadNewestLanguage()
{
	//  
	this->m_aryLangExInfo.RemoveAll();

	//  
	CString         strNoteID = _T( "IDS_NEW_LANGUAGE" );
	CString         strDataID = _T( "" );
	CString         strBuffer = _T( "" );
	LANG_EXTAR_INFO infoLangEx;

	for ( INT i = 1; ; i++ )
	{
		//  
		infoLangEx.Empty();

		//  Get Language Name
		strDataID.Format( _T( "LAN_NAME_%d" ), i );

		EZ_MSXMLInterface::GetText( infoLangEx.m_strCountry, strNoteID, strDataID );

		if ( infoLangEx.m_strCountry.IsEmpty() )
		{
			;
			break;
		}

		//  
		if ( this->m_aryLangExInfo.Linear_Find( infoLangEx ) >= 0 )
		{
			;
			continue;
		}

		//  Get Primary ID
		strDataID.Format( _T( "LAN_OS_PRIID_%d" ), i );

		EZ_MSXMLInterface::GetText( strBuffer, strNoteID, strDataID );

		if ( !strBuffer.IsEmpty() )
			infoLangEx.m_iPrimaryID = _ttoi( strBuffer );

		//  Get Sub ID
		strDataID.Format( _T( "LAN_OS_SUBID_%d" ), i );

		EZ_MSXMLInterface::GetText( strBuffer, strNoteID, strDataID );

		if ( !strBuffer.IsEmpty() )
			infoLangEx.m_iSubID = _ttoi( strBuffer );

		//  Get Tag
		strDataID.Format( _T( "LAN_XMLID_%d" ), i );

		EZ_MSXMLInterface::GetText( infoLangEx.m_strTag, strNoteID, strDataID );

		//  Get Font Name
		strDataID.Format( _T( "LAN_FONT_%d" ), i );

		EZ_MSXMLInterface::GetText( infoLangEx.m_strFont, strNoteID, strDataID );

		//  Get Font's Charset
		strDataID.Format( _T( "LAN_FONTCHARSET_%d" ), i );

		EZ_MSXMLInterface::GetText( strBuffer, strNoteID, strDataID );

		if ( !strBuffer.IsEmpty() )
			infoLangEx.m_iCharSet = _ttoi( strBuffer );

		//  Get RTL Style ?
		strDataID.Format( _T( "LAN_RIGHTLEFT_%d" ), i );

		EZ_MSXMLInterface::GetText( strBuffer, strNoteID, strDataID );

		if ( !strBuffer.IsEmpty() )
			infoLangEx.m_bRTLStyle = _ttoi( strBuffer );

		//  Get System Locale
		strDataID.Format( _T( "LAN_SYSLOCALE_%d" ), i );

		EZ_MSXMLInterface::GetText( infoLangEx.m_strLocale, strNoteID, strDataID );

		if ( infoLangEx.m_strLocale.IsEmpty() )
			infoLangEx.m_strLocale = _T( "english" );

		//  Get Nero's Language Text
		strDataID.Format( _T( "LAN_NEROLAN_%d" ), i );

		EZ_MSXMLInterface::GetText( infoLangEx.m_strNeroLan, strNoteID, strDataID );

		if ( infoLangEx.m_strNeroLan.IsEmpty() )
			infoLangEx.m_strNeroLan = _T( "ENG" );

		//  Add to Array
		this->m_aryLangExInfo.Add( infoLangEx );
	}
}

//  ==========================================================================
//  GetText
//  ==========================================================================
void EZ_Language::GetText( CString& strReturn, CString& strChildID, C_BOOL bGetEngNode )
{
	CString strLanID[ 2 ] = { this->TranLangCode(), _T( "EN" ) };

	for ( INT i = 0; i < 2; i++ )
	{
		EZ_MSXMLInterface::GetText( strReturn, strChildID, strLanID[ i ] );

		if ( !strReturn.IsEmpty() || !bGetEngNode )
		{
			;
			break;
		}
	}
}

void EZ_Language::GetText( CString& strReturn, CString& strChildID, C_INT iChildID, C_BOOL bGetEngNode )
{
	//  Load XML
	if ( this->HasOpen() )
		this->GetText( strReturn, strChildID, bGetEngNode );
	else
		strReturn.Empty();

	//  Load Resouce
	if ( strReturn.IsEmpty() && ( iChildID > 0 ) )
		strReturn.LoadString( iChildID );
}

//  ==========================================================================
//  GetText
//  ==========================================================================
void EZ_Language::GetText( CString& strReturn, CString& strParentID, CString& strChildID, C_BOOL bGetEngNode )
{
	CString strLanID[ 2 ] = { this->TranLangCode(), _T( "EN" ) };

	for ( INT i = 0; i < 2; i++ )
	{
		EZ_MSXMLInterface::GetText( strReturn, strParentID, strChildID, strLanID[ i ] );

		if ( !strReturn.IsEmpty() || !bGetEngNode )
		{
			;
			break;
		}
	}
}

void EZ_Language::GetText( CString& strReturn, CString& strParentID, CString& strChildID, C_INT iChildID, C_BOOL bGetEngNode )
{
	//  Load XML
	if ( !this->HasOpen() )
		strReturn.Empty();
	else if ( strParentID.IsEmpty() )
		this->GetText( strReturn, strChildID, bGetEngNode );
	else
		this->GetText( strReturn, strParentID, strChildID, bGetEngNode );	

	//  Load Resouce
	if ( strReturn.IsEmpty() && ( iChildID > 0 ) )
		strReturn.LoadString( iChildID );
}

//  ==========================================================================
//  ReadUDDefaultLanID
//  ==========================================================================
C_BOOL EZ_Language::ReadUDDefaultLanID( EZ_LANG_ID& iEZLangID, INT& iSubID ) const
{
	BOOL bResult = FALSE;

	{
		//  Get Ini File
		CString strIniFile = _T( "" );

		strIniFile.Format( _T( "%s\\EZBRAND.INI" ), EZ_Mutex::gm_WindowPath );

		//  
		TCHAR szUDDLanID[ 32 ] = _T( "" );

		if ( ::GetPrivateProfileString( _T( "General" ), _T( "Lang" ), _T( "" ), szUDDLanID, 32, strIniFile ) > 0 )
		{
			//  Check Part 1
			for ( INT i = 0; i < EZ_LANG_COUNT; i++ )
			{
				if ( EZ_Language::gm_LangNoteText[ i ].CompareNoCase( szUDDLanID ) == 0 )
				{
					bResult    = TRUE;
					iSubID     = 0;
					iEZLangID = ( EZ_LANG_ID )i;
					break;
				}
			}

			//  Check Part 2
			if ( !bResult )
			{
				C_INT           iSize       = this->m_aryLangExInfo.GetSize();
				LPLANGEXTARINFO lpLanExInfo = NULL;

				for ( INT i = 0; i < iSize; i++ )
				{
					lpLanExInfo = this->m_aryLangExInfo.GetPointerAt( i );

					if ( lpLanExInfo && ( lpLanExInfo->m_strTag.CompareNoCase( szUDDLanID ) == 0 ) )
					{
						bResult    = TRUE;
						iSubID     = i;
						iEZLangID = EZ_LANG_NEWEST;
						break;
					}
				}
			}
		}
	}

	return bResult;
}

//  ==========================================================================
//  TranLangCode
//  ==========================================================================
CString EZ_Language::TranLangCode( C_INT iMainID, C_INT iSubID ) const
{
	if ( ( iMainID <= EZ_LANG_DEFA ) || ( EZ_LANG_COUNT <= iMainID ) )
	{
		;
		return EZ_Language::gm_LangNoteText[ 0 ];
	}
	else if ( iMainID != EZ_LANG_NEWEST )
	{
		;
		return EZ_Language::gm_LangNoteText[ iMainID ];
	}
	else
	{
		LPLANGEXTARINFO lpLangInfo = this->m_aryLangExInfo.GetPointerAt( iSubID );

		return ( lpLangInfo ? lpLangInfo->m_strTag : EZ_Language::gm_LangNoteText[ 0 ] );
	}
}

//  ==========================================================================
//  CreateFont
//  ==========================================================================
void EZ_Language::CreateFont( C_INT iMainID, C_INT iSubID, C_INT iFontSize, CDC* lpDC )
{
	//  Remove Old Font
	this->ReleaseFont();

	//  Create New Font
	LPLANGEXTARINFO lpLangInfo = NULL;
	LOGFONT         logFont    = { 0 };

	for ( INT i = 0, nPixelY; i < 3; i++ )
	{
		//  Set Font
		if ( i == 2 )
		{
			//logFont.lfWeight         = FW_MEDIUM;
			//logFont.lfCharSet        = DEFAULT_CHARSET;
			//logFont.lfPitchAndFamily = ( VARIABLE_PITCH | FF_MODERN );

			::_tcscpy_s( logFont.lfFaceName, LF_FACESIZE, _T( "System" ) );
		}
		else if ( i == 1 )
		{
			//logFont.lfWeight         = FW_MEDIUM;
			logFont.lfCharSet        = DEFAULT_CHARSET;
			logFont.lfPitchAndFamily = ( VARIABLE_PITCH | FF_MODERN );

			//::_tcscpy_s( logFont.lfFaceName, LF_FACESIZE, _T( "Arial" ) );
		}
		else if ( iMainID == EZ_LANG_NEWEST )
		{
			//  
			EZ_Language::SetFont( logFont, iFontSize, EZ_LANG_ENG );

			//  
			lpLangInfo = this->m_aryLangExInfo.GetPointerAt( iSubID );

			if ( lpLangInfo )
			{
				logFont.lfCharSet = ( ( lpLangInfo->m_iCharSet > 0 ) ? lpLangInfo->m_iCharSet : DEFAULT_CHARSET );

				::_tcscpy_s( logFont.lfFaceName, lpLangInfo->m_strFont );
			}
		}
		else
		{
			if ( !EZ_Language::SetFont( logFont, iFontSize, ( EZ_LANG_ID )iMainID ) )
			{
				;
				continue;
			}
		}

		//  
		if ( lpDC && ( logFont.lfHeight > 0 ) )
		{
			nPixelY = lpDC->GetDeviceCaps( LOGPIXELSY );

			logFont.lfHeight = -MulDiv( logFont.lfHeight, nPixelY, 72 );
		}
		else
		{
#if defined ( _SUPPORT_4K_MONITOR_ )	//  For 4K ( Update to x64 Version )
			NONCLIENTMETRICS dtNonclientmetrics;

			dtNonclientmetrics.cbSize = sizeof( NONCLIENTMETRICS );

			::SystemParametersInfo( SPI_GETNONCLIENTMETRICS, dtNonclientmetrics.cbSize, &dtNonclientmetrics, 0 );

			logFont = dtNonclientmetrics.lfMessageFont;
#endif
		}

		//  Create Font
		this->m_pNewFont = new CFont();

		if ( !this->m_pNewFont )
		{	//  Alloc Fail
			;
			break;
		}
		else if ( this->m_pNewFont->CreateFontIndirect( &logFont ) )
		{	//  Success !
			;
			break;
		}
		else
		{	//  Failed ! ( Try Again )
			delete this->m_pNewFont;
			this->m_pNewFont = NULL;
		}
	}
}

//  ==========================================================================
//  ReleaseFont
//  ==========================================================================
void EZ_Language::ReleaseFont()
{
	if ( this->m_pNewFont )
	{
		if ( this->m_pNewFont->GetSafeHandle() )
			this->m_pNewFont->DeleteObject();

		delete this->m_pNewFont;
		this->m_pNewFont = NULL;
	}
}

//  ==========================================================================
//  GetSystemLocale
//  ==========================================================================
CString EZ_Language::GetSystemLocale() const
{
	CString strReturn = _T( "" );

	{
#ifdef SYSTEM_LOCATE
		strReturn.Format( "%s", SYSTEM_LOCATE );
#else
		if ( ( this->m_iLangID <= EZ_LANG_DEFA ) || ( EZ_LANG_COUNT <= this->m_iLangID ) )
			strReturn = _T( "english" );
		else if ( this->m_iLangID == EZ_LANG_NEWEST )
		{
			LPLANGEXTARINFO lpLanExInfo = this->m_aryLangExInfo.GetPointerAt( this->m_iLangExID );

			strReturn = ( lpLanExInfo ? lpLanExInfo->m_strLocale : _T( "english" ) );
		}
		else
		{
			CString strSysLocale[ EZ_LANG_COUNT ] = 
			{
				_T( "english" ), _T( "chs" ), _T( "cht" ), _T( "fra" ), _T( "deu" ), 
				_T( "jpn" ),     _T( "plk" ), _T( "ptg" ), _T( "rus" ), _T( "esp" ), 
				_T( "arb" ),     _T( "heb" ), _T( "hun" ), _T( "csy" ), _T( "ita" ), 
				_T( "nld" ),     _T( "dan" ), _T( "tai" ), _T( "srl" ), _T( "english" ), 
				_T( "english" ), 
			};

			strReturn = strSysLocale[ this->m_iLangID ];
		}
#endif
	}

	return strReturn;
}

//  ==========================================================================
//  GetNeroLanguage
//  ==========================================================================
CString EZ_Language::GetNeroLanguage() const
{
	CString strReturn = _T( "" );

	{
#ifdef NERO_LANGUAGE
		strReturn.Format( "%s", NERO_LANGUAGE );
#else
		if ( ( this->m_iLangID <= EZ_LANG_DEFA ) || ( EZ_LANG_COUNT <= this->m_iLangID ) )
			strReturn = _T( "ENG" );
		else if ( this->m_iLangID == EZ_LANG_NEWEST )
		{
			LPLANGEXTARINFO lpLanExInfo = this->m_aryLangExInfo.GetPointerAt( this->m_iLangExID );

			strReturn = ( lpLanExInfo ? lpLanExInfo->m_strNeroLan : _T( "ENG" ) );
		}
		else
		{
			CString strLanguage[ EZ_LANG_COUNT ] = 
			{
				_T( "ENG" ), _T( "CHS" ), _T( "CHT" ), _T( "FRA" ), _T( "DEU" ), 
				_T( "JPN" ), _T( "PLK" ), _T( "PTG" ), _T( "RUS" ), _T( "ESP" ), 
				_T( "ARA" ), _T( "HEB" ), _T( "HUN" ), _T( "CSY" ), _T( "ITA" ), 
				_T( "NLD" ), _T( "DAN" ), _T( "THA" ), _T( "SRL" ), _T( "ENG" ), 
				_T( "ENG" ), 
			};

			strReturn = strLanguage[ this->m_iLangID ];
		}
#endif
	}

	return strReturn;
}

//  ==========================================================================
//  GetSystemLanguage ( Static )
//  ==========================================================================
const EZ_LANG_ID EZ_Language::GetSystemLanguage( INT& iPrimaryID, INT& iSubID )
{
	const LANGID iLangID = ::GetSystemDefaultLangID();

	{
		iPrimaryID = PRIMARYLANGID ( iLangID );
		iSubID     = SUBLANGID( iLangID );

		switch ( iPrimaryID )
		{
		case LANG_ENGLISH:		//  英文 ..
		case LANG_KANNADA:		//  加拿大 ..
			return EZ_LANG_ENG;

		case LANG_CHINESE:		//  中文 ..
			{
				switch ( iSubID )
				{
				case SUBLANG_CHINESE_TRADITIONAL:	//  台灣 ..
				case SUBLANG_CHINESE_HONGKONG:		//  香港 ..
					return EZ_LANG_TC;

				case SUBLANG_CHINESE_SIMPLIFIED:	//  中國 ..
				case SUBLANG_CHINESE_SINGAPORE:		//  新加坡 ..
				default:							//  UnKnow
					return EZ_LANG_SC;
				}
			}
			break;

		case LANG_FRENCH:		//  法文 ..
			return EZ_LANG_FRA;

		case LANG_GERMAN:		//  德文 ..
			return EZ_LANG_GER;

		case LANG_JAPANESE:		//  日文 ..
			return EZ_LANG_JPN;

		case LANG_POLISH:		//  波蘭文 ..
			return EZ_LANG_POL;

		case LANG_PORTUGUESE:	//  葡萄牙文 ..
			return EZ_LANG_PTU;

		case LANG_RUSSIAN:		//  俄文 ..
			return EZ_LANG_RUS;

		case LANG_SPANISH:		//  西班牙文 ..
			return EZ_LANG_SPN;

		case LANG_ARABIC:		//  阿拉伯文 ..
			return EZ_LANG_ARB;

		case LANG_HEBREW:		//  希伯來文 ..
			return EZ_LANG_HEB;

		case LANG_HUNGARIAN:	//  匈牙利文 ..
			return EZ_LANG_HUN;

		case LANG_CZECH:		//  捷克文 ..
			return EZ_LANG_CZE;

		case LANG_ITALIAN:		//  義大利文 ..
			return EZ_LANG_ITA;

		case LANG_DUTCH:		//  荷蘭文 ..
			return EZ_LANG_NLD;

		case LANG_DANISH:		//  丹麥文 ..
			return EZ_LANG_DAN;

		case LANG_THAI:			//  泰文 ..
			return EZ_LANG_TAI;

		case LANG_SERBIAN:		//  塞爾維亞文 ..
			return EZ_LANG_SRL;

		case LANG_FARSI:		//  波斯文 ( LANG_PERSIAN ) ..
			return EZ_LANG_PRS;

		default:				//  Newest
			return EZ_LANG_NEWEST;
		}
	}
}

//  ==========================================================================
//  SetFont ( Static )
//  ==========================================================================
C_BOOL EZ_Language::SetFont( LOGFONT& logFont, C_INT iFontSize, EZ_LANG_ID iEZLangID )
{
	//  Get Language
	INT iPrimaryID = 0, iSubID = 0;

	if ( iEZLangID >= EZ_LANG_NEWEST )
	{
		;
		return FALSE;
	}
	else if ( iEZLangID == EZ_LANG_DEFA )
	{
		iEZLangID = EZ_Language::GetSystemLanguage( iPrimaryID, iSubID );

		if ( ( iEZLangID <= EZ_LANG_DEFA ) || ( EZ_LANG_NEWEST <= iEZLangID ) )
			iEZLangID = EZ_LANG_ENG;
	}

	//  Set Font
	::memset( &logFont, 0, sizeof( LOGFONT ) );

	logFont.lfHeight        = iFontSize;
	logFont.lfOutPrecision  = OUT_DEFAULT_PRECIS;
	logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logFont.lfQuality       = DEFAULT_QUALITY;
	
	switch ( iEZLangID )
	{
	case EZ_LANG_DEFA:		//  Unknow
	case EZ_LANG_NEWEST:	//  Newest
	default:
		{
			::EZOutputDebugString( _T( "\n" ) );
		}

	case EZ_LANG_ENG:	//  English
	case EZ_LANG_FRA:	//  France
	case EZ_LANG_GER:	//  Germany
	case EZ_LANG_POL:	//  Poland
	case EZ_LANG_PTU:	//  Brazil
	case EZ_LANG_SPN:	//  Spain
	case EZ_LANG_HUN:	//  Hungarian
	case EZ_LANG_CZE:	//  Czech
	case EZ_LANG_ITA:	//  Italy
	case EZ_LANG_NLD:	//  Dutch
	case EZ_LANG_DAN:	//  Danish
	case EZ_LANG_SRL:	//  Serbian
	case EZ_LANG_PRS:	//  Persian
		{
			logFont.lfWeight         = FW_MEDIUM;
			logFont.lfCharSet        = DEFAULT_CHARSET;
			logFont.lfPitchAndFamily = ( VARIABLE_PITCH | FF_MODERN );

			::_tcscpy_s( logFont.lfFaceName, LF_FACESIZE, _T( "Arial" ) );
		}
		break;

	case EZ_LANG_SC:	//  China
		{
			logFont.lfWeight         = FW_MEDIUM;
			logFont.lfCharSet        = GB2312_CHARSET;
			logFont.lfPitchAndFamily = ( VARIABLE_PITCH | FF_MODERN );

			::_tcscpy_s( logFont.lfFaceName, LF_FACESIZE, _T( "冼极" ) );
		}
		break;

	case EZ_LANG_TC:	//  Taiwan
		{
			logFont.lfWeight         = FW_MEDIUM;
			logFont.lfCharSet        = CHINESEBIG5_CHARSET;
			logFont.lfPitchAndFamily = ( VARIABLE_PITCH | FF_MODERN );

			::_tcscpy_s( logFont.lfFaceName, LF_FACESIZE, _T( "新細明體" ) );
		}
		break;

	case EZ_LANG_JPN:	//  Japan
		{
			logFont.lfWeight         = FW_LIGHT;
			logFont.lfCharSet        = SHIFTJIS_CHARSET;
			logFont.lfPitchAndFamily = ( VARIABLE_PITCH | FF_MODERN );

			::_tcscpy_s( logFont.lfFaceName, LF_FACESIZE, _T( "MS UI Gothic" ) );
		}
		break;

	case EZ_LANG_RUS:	//  Russian
		{
			logFont.lfWeight         = FW_MEDIUM;
			logFont.lfCharSet        = RUSSIAN_CHARSET;
			logFont.lfPitchAndFamily = ( VARIABLE_PITCH | FF_MODERN );

			::_tcscpy_s( logFont.lfFaceName, LF_FACESIZE, _T( "Arial" ) );
		}				
		break;

	case EZ_LANG_ARB:	//  Arabic
		{
			logFont.lfWeight         = FW_MEDIUM;
			logFont.lfCharSet        = ARABIC_CHARSET;
			logFont.lfPitchAndFamily = ( VARIABLE_PITCH | FF_MODERN );

			::_tcscpy_s( logFont.lfFaceName, LF_FACESIZE, _T( "Simplified Arabic" ) );
		}
		break;

	case EZ_LANG_HEB:	//  Hebrew
		{
			logFont.lfWeight         = FW_MEDIUM;
			logFont.lfCharSet        = HEBREW_CHARSET;
			logFont.lfPitchAndFamily = ( VARIABLE_PITCH | FF_MODERN );

			::_tcscpy_s( logFont.lfFaceName, LF_FACESIZE, _T( "Arial" ) );
		}
		break;

	case EZ_LANG_TAI:	//  Thailand
		{
			logFont.lfWeight         = FW_MEDIUM;
			logFont.lfCharSet        = THAI_CHARSET;
			logFont.lfPitchAndFamily = ( VARIABLE_PITCH | FF_MODERN );

			::_tcscpy_s( logFont.lfFaceName, LF_FACESIZE, _T( "Tahoma" ) );
		}
		break;
	}

	return TRUE;
}
