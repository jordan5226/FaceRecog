#pragma once

#include "..\..\EZDefined.h"
#include "..\EZ_TemplateVectorArray.h"

//  ==========================================================================
//  
//  ==========================================================================
#ifndef LANG_SERBIAN_LATIN
#define LANG_SERBIAN_LATIN LANG_SERBIAN
#endif

//  ==========================================================================
//  
//  ==========================================================================
struct LANG_EXTAR_INFO
{
	//  Member
	BOOL    m_bRTLStyle;	//  ¥ª¥kÄA­Ë
	UINT    m_iPrimaryID;	//  GetSystemDefaultLangID
	UINT    m_iSubID;		//  GetSystemDefaultLangID
	UINT    m_iCharSet;		//  Font's Charset
	CString m_strCountry;	//  Language Name
	CString m_strTag;		//  XML ©w¸qªº TAG
	CString m_strFont;		//  Font Name
	CString m_strNeroLan;	//  Nero Language
	CString m_strLocale;	//  System locale

	//  Method
	LANG_EXTAR_INFO( C_INT iPriID = 0, C_INT iSubID = 0 ) 
		: m_bRTLStyle( FALSE ), m_iPrimaryID( iPriID ), m_iSubID( iSubID ), m_iCharSet( 0 ), m_strCountry( _T( "" ) )
		, m_strTag( _T( "" ) ), m_strFont( _T( "" ) ), m_strNeroLan( _T( "ENG" ) ), m_strLocale( _T( "english" ) )
	{
		;
	}

	~LANG_EXTAR_INFO()
	{
		;
	}

	LANG_EXTAR_INFO& operator = ( const LANG_EXTAR_INFO& infoLangExtra )
	{
		if ( this != &infoLangExtra )
		{
			this->m_bRTLStyle  = infoLangExtra.m_bRTLStyle;
			this->m_iPrimaryID = infoLangExtra.m_iPrimaryID;
			this->m_iSubID     = infoLangExtra.m_iSubID;
			this->m_iCharSet   = infoLangExtra.m_iCharSet;
			this->m_strCountry = infoLangExtra.m_strCountry;
			this->m_strTag     = infoLangExtra.m_strTag;
			this->m_strFont    = infoLangExtra.m_strFont;
			this->m_strNeroLan = infoLangExtra.m_strNeroLan;
			this->m_strLocale  = infoLangExtra.m_strLocale;
		}

		return *this;
	}

	C_BOOL operator == ( const LANG_EXTAR_INFO& infoLangExtra ) const
	{
		BOOL bResult = TRUE;

		if ( this != &infoLangExtra )
		{
			bResult = ( ( this->m_iPrimaryID == infoLangExtra.m_iPrimaryID ) && 
						( this->m_iSubID     == infoLangExtra.m_iSubID     ) );
		}

		return bResult;
	}

	void Empty()
	{
		this->m_bRTLStyle  = 0;
		this->m_iPrimaryID = 0;
		this->m_iSubID     = 0;
		this->m_iCharSet   = 0;
		this->m_strNeroLan = _T( "ENG" );
		this->m_strLocale  = _T( "english" );

		this->m_strCountry.Empty();
		this->m_strTag.Empty();
		this->m_strFont.Empty();
	}
};

typedef const LANG_EXTAR_INFO  C_LANGEXTARINFO;
typedef       LANG_EXTAR_INFO* LPLANGEXTARINFO;
typedef const LANG_EXTAR_INFO* LPCLANGEXTARINFO;

typedef EZ_Vector_Array1 < LANG_EXTAR_INFO > LANGEXTARINFOARRAY;

typedef const LANGEXTARINFOARRAY  C_LANGEXTARINFOARRAY;
typedef       LANGEXTARINFOARRAY* LPLANGEXTARINFOARRAY;
typedef const LANGEXTARINFOARRAY* LPCLANGEXTARINFOARRAY;
