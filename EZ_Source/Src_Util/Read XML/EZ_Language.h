#pragma once

#include "EZ_ExLangData.h"
#include "EZ_MSXMLInterface.h"

//  ==========================================================================
//  Language ID
//  ==========================================================================
enum EZ_LANG_ID
{
	EZ_LANG_DEFA = -1,	//  -1 : Default ( Operating System )
	EZ_LANG_ENG = 0,	//  00 : 英文 ( English )
	EZ_LANG_SC,		//  01 : 簡體中文 ( Simipl. Chinese )
	EZ_LANG_TC,		//  02 : 繁體中文 ( Trad.   Chinese )
	EZ_LANG_FRA,		//  03 : 法文 ( French )
	EZ_LANG_GER,		//  04 : 德文 ( German )
	EZ_LANG_JPN,		//  05 : 日文 ( Japanese )
	EZ_LANG_POL,		//  06 : 波蘭文 ( Polish )
	EZ_LANG_PTU,		//  07 : 巴西, 葡萄牙文 ( Portuguese )
	EZ_LANG_RUS,		//  08 : 俄文 ( Russian )
	EZ_LANG_SPN,		//  09 : 西班牙文 ( Spanish )
	EZ_LANG_ARB,		//  10 : 阿拉伯文 ( Arabic )
	EZ_LANG_HEB,		//  11 : 希伯來文 ( Hebrew )
	EZ_LANG_HUN,		//  12 : 匈牙利文 ( Hungarian )
	EZ_LANG_CZE,		//  13 : 捷克文 ( Czech )
	EZ_LANG_ITA,		//  14 : 義大利文 ( Italian )
	EZ_LANG_NLD,		//  15 : 荷蘭文 ( Dutch )
	EZ_LANG_DAN,		//  16 : 丹麥文 ( Danish )
	EZ_LANG_TAI,		//  17 : 泰文 ( Thailand )
	EZ_LANG_SRL,		//  18 : 南斯拉夫文 ( Serbian )
	EZ_LANG_PRS,		//  19 : 波斯文 ( Persian )
	EZ_LANG_NEWEST,	//  20 : Newest
	EZ_LANG_COUNT,		//  
	EZ_LANG_SYSTEM,	//  
};

typedef const EZ_LANG_ID C_EZ_LANG_ID;

//  ==========================================================================
//  Language Defined
//  ==========================================================================
#ifdef RES_BIG5 //  繁體中文 ( Trad-Chinese )

#define XML_LANGUAGE_NUMBER EZ_LANG_TC
#define NERO_LANGUAGE       _T( "CHT" )
#define SYSTEM_LOCATE       _T( "cht" )

#elif  RES_GB   //  簡體中文 ( Sim-Chinese )

#define XML_LANGUAGE_NUMBER EZ_LANG_SC
#define NERO_LANGUAGE       _T( "CHS" )
#define SYSTEM_LOCATE       _T( "chs" )

#elif  RES_SJIS //  日文 ( Japan )

#define XML_LANGUAGE_NUMBER EZ_LANG_JPN
#define NERO_LANGUAGE       _T( "JPN" )
#define SYSTEM_LOCATE       _T( "jpn" )

#elif  RES_SPN  //  西班牙文 ( Spain )

#define XML_LANGUAGE_NUMBER EZ_LANG_SPN
#define NERO_LANGUAGE       _T( "ESP" )
#define SYSTEM_LOCATE       _T( "esp" )

#elif  RES_PTU  //  葡萄牙文 ( Portugal )

#define XML_LANGUAGE_NUMBER EZ_LANG_PTU
#define NERO_LANGUAGE       _T( "PTG" )
#define SYSTEM_LOCATE       _T( "ptg" )

#elif  RES_GER  //  德文 ( Germany )

#define XML_LANGUAGE_NUMBER EZ_LANG_GER
#define NERO_LANGUAGE       _T( "DEU" )
#define SYSTEM_LOCATE       _T( "deu" )

#elif  RES_FRA  //  法文 ( France )

#define XML_LANGUAGE_NUMBER EZ_LANG_FRA
#define NERO_LANGUAGE       _T( "FRA" )
#define SYSTEM_LOCATE       _T( "fra" )

#elif  RES_POL  //  波蘭文 ( Poland )

#define XML_LANGUAGE_NUMBER EZ_LANG_POL
#define NERO_LANGUAGE       _T( "PLK" )
#define SYSTEM_LOCATE       _T( "plk" )

#elif  RES_RUS  //  俄文 ( Russian )

#define XML_LANGUAGE_NUMBER EZ_LANG_RUS
#define NERO_LANGUAGE       _T( "RUS" )
#define SYSTEM_LOCATE       _T( "rus" )

#elif  RES_ARB  //  阿拉伯文 ( Arabic )

#define XML_LANGUAGE_NUMBER EZ_LANG_ARB
#define NERO_LANGUAGE       _T( "ARA" )
#define SYSTEM_LOCATE       _T( "arb" )

#elif  RES_HEB  //  希伯來文 ( Hebrew )

#define XML_LANGUAGE_NUMBER EZ_LANG_HEB
#define NERO_LANGUAGE       _T( "HEB" )
#define SYSTEM_LOCATE       _T( "heb" )

#elif  RES_HUN  //  匈牙利文 ( Hungarian )

#define XML_LANGUAGE_NUMBER EZ_LANG_HUN
#define NERO_LANGUAGE       _T( "HUN" )
#define SYSTEM_LOCATE       _T( "hun" )

#elif  RES_ITA  //  義大利文 ( Italy )

#define XML_LANGUAGE_NUMBER EZ_LANG_ITA
#define NERO_LANGUAGE       _T( "ITA" )
#define SYSTEM_LOCATE       _T( "ita" )

#elif  RES_DAN  //  丹麥文 ( Danish )

#define XML_LANGUAGE_NUMBER EZ_LANG_DAN
#define NERO_LANGUAGE       _T( "DAN" )
#define SYSTEM_LOCATE       _T( "dan" )

#elif  RES_SRL  //  南斯拉夫文 ( Serbian )

#define XML_LANGUAGE_NUMBER EZ_LANG_SRL
#define NERO_LANGUAGE       _T( "SRL" )
#define SYSTEM_LOCATE       _T( "srl" )

#elif  RES_CZH  //  捷克文 ( Czech )

#define XML_LANGUAGE_NUMBER EZ_LANG_CZE
#define NERO_LANGUAGE       _T( "CSY" )
#define SYSTEM_LOCATE       _T( "csy" )

#elif  RES_TAI  //  泰文 ( Thailand )

#define XML_LANGUAGE_NUMBER EZ_LANG_TAI
#define NERO_LANGUAGE       _T( "THA" )
#define SYSTEM_LOCATE       _T( "tai" )

#elif  RES_NLD  //  荷蘭文 ( Dutch )

#define XML_LANGUAGE_NUMBER EZ_LANG_NLD
#define NERO_LANGUAGE       _T( "NLD" )
#define SYSTEM_LOCATE       _T( "nld" )

#elif  RES_PRS  //  波斯文 ( Persian )

#define XML_LANGUAGE_NUMBER EZ_LANG_PRS
#define NERO_LANGUAGE       "ENG"
#define SYSTEM_LOCATE       _T( "english" )

#elif  RES_ASCI //  英文 ( English )

#define XML_LANGUAGE_NUMBER EZ_LANG_ENG
#define NERO_LANGUAGE       _T( "ENG" )
#define SYSTEM_LOCATE       _T( "english" )

#else           //  未知 ( Window OS )

#define XML_LANGUAGE_NUMBER EZ_LANG_DEFA

#endif

//  ==========================================================================
//  
//  ==========================================================================
class EZ_Language : public EZ_MSXMLInterface
{
protected:
	BOOL               m_bRTLStyle;
	INT                m_iLangExID;
	EZ_LANG_ID        m_iLangID;
	CFont*             m_pNewFont;
	LANGEXTARINFOARRAY m_aryLangExInfo;
	static CString     gm_LangNoteText[ EZ_LANG_COUNT ];

public:
	EZ_Language( C_EZ_LANG_ID langID = XML_LANGUAGE_NUMBER, C_INT iSubID = 0 );
	virtual ~EZ_Language();	
	
	virtual C_BOOL  Open( LPCTSTR lpFileName, EZ_LANG_ID ezLangID = XML_LANGUAGE_NUMBER, CDC* lpDC = NULL );
	virtual void    Close();

    virtual void    SetCurLangID( C_EZ_LANG_ID ezLangID, C_INT iSubID = 0 );
	virtual void    GetOSLangID();

	virtual void    GetText( CString& strReturn, CString& strChildID,                 C_BOOL bGetEngNode );
	virtual void    GetText( CString& strReturn, CString& strChildID, C_INT iChildID, C_BOOL bGetEngNode );

	virtual void    GetText( CString& strReturn, CString& strParentID, CString& strChildID,                 C_BOOL bGetEngNode );
	virtual void    GetText( CString& strReturn, CString& strParentID, CString& strChildID, C_INT iChildID, C_BOOL bGetEngNode );

	virtual void    CreateFont( C_INT iMainID, C_INT iSubID, C_INT iFontSize, CDC* lpDC = NULL );
	virtual void    ReleaseFont();

	virtual CString GetNeroLanguage() const;
	virtual CString GetSystemLocale() const;

protected:
	virtual void    ReadNewestLanguage();
	virtual CString TranLangCode( C_INT iMainID, C_INT iSubID = 0 ) const;
	virtual C_BOOL  ReadUDDefaultLanID( EZ_LANG_ID& ezLangID, INT& iSubID ) const;

	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
public:
	virtual void CreateFont( CDC* lpDC )
	{
		this->CreateFont( this->m_iLangID, this->m_iLangExID, -12, lpDC );
	}

	virtual void CreateFont( C_INT iFontSize, CDC* lpDC )
	{
		this->CreateFont( this->m_iLangID, this->m_iLangExID, iFontSize, lpDC );
	}

	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
public:
	inline C_BOOL IsRTLStyle() const
	{
		return this->m_bRTLStyle;
	}

	inline C_BOOL IsEngLanID() const
	{
		return ( this->m_iLangID != EZ_LANG_ENG );
	}

	inline C_INT GetMakeNewestLangID() const
	{
		LPLANGEXTARINFO lpLanExInfo = this->m_aryLangExInfo.GetPointerAt( this->m_iLangExID );

		return ( lpLanExInfo ? MAKEWORD ( lpLanExInfo->m_iPrimaryID, lpLanExInfo->m_iSubID ) : 0 );
	}

	inline C_EZ_LANG_ID GetCurLangID() const 
	{ 
		return this->m_iLangID;
	}

	inline C_INT FindNewestLanguage( C_INT iPriID, C_INT iSubID ) const
	{
		return this->m_aryLangExInfo.Linear_Find( LANG_EXTAR_INFO( iPriID, iSubID ) );
	}

	inline CFont* GetFont() const
	{ 
		return this->m_pNewFont; 
	}

	inline CString TranLangCode() const
	{
		return this->TranLangCode( this->m_iLangID, this->m_iLangExID );
	}

	//  ==========================================================================
	//  Static Function
	//  ==========================================================================
public:
	static void Initial()
	{
		;
	}

	static void UnInitial()
	{
		for ( INT i = 0; i < EZ_LANG_COUNT; i++ )
			EZ_Language::gm_LangNoteText[ i ].Empty();
	}

	static const EZ_LANG_ID GetSystemLanguage( INT& iPrimaryID, INT& iSubID );

	static C_BOOL SetFont( LOGFONT& logFont, C_INT iFontSize, EZ_LANG_ID iEZLangID = EZ_LANG_DEFA );
};

typedef const EZ_Language  C_EZBASICLAN;
typedef       EZ_Language* LPEZBASICLAN;
typedef const EZ_Language* LPCEZBASICLAN;
