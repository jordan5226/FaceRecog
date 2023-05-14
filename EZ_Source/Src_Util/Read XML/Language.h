#pragma once

#include "EZ_Language.h"

//  ==========================================================================
//  
//  ==========================================================================
class CLanguage : public EZ_Language
{
public:
	CLanguage( C_EZ_LANG_ID langID = EZ_LANG_DEFA ) : EZ_Language( langID, 0 )
	{
		;
	}

	virtual ~CLanguage()
	{
		EZ_Language::Close();
	}
	
	inline CString LoadString( CString strStringID )
	{
		CString strReturn = _T( "" );

		EZ_Language::GetText( strReturn, strStringID, this->IsEngLanID() );

		return strReturn;
	}

	inline CString LoadString( CString strStringID, C_INT iStringID )
	{
		CString strReturn = _T( "" );

		EZ_Language::GetText( strReturn, strStringID, iStringID, this->IsEngLanID() );

		return strReturn;
	}

	inline CString LoadString( CString strTableID, CString strStringID )
	{
		CString strReturn = _T( "" );

		EZ_Language::GetText( strReturn, strTableID, strStringID, this->IsEngLanID() );

		return strReturn;
	}

	inline CString LoadString( CString strTableID, CString strStringID, C_INT iStringID )
	{
		CString strReturn = _T( "" );

		EZ_Language::GetText( strReturn, strTableID, strStringID, iStringID, this->IsEngLanID() );

		return strReturn;
	}
};

typedef const CLanguage  C_EZLANGUAGE;
typedef       CLanguage* LPEZLANGUAGE;
typedef const CLanguage* LPCEZLANGUAGE;
