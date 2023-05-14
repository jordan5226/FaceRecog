#pragma once

#include "..\..\EZDefined.h"

//  ==========================================================================
//  XML Interface
//  ==========================================================================
#define _USE_MSXML3_ 1

#if defined ( _USE_MSXML3_ )

#import <msxml3.dll>

using namespace MSXML2;

#define IXMLDOMINTERFACE   L"Msxml2.DOMDocument"
#define IXMLDOMELEMENTPTR  MSXML2::IXMLDOMElementPtr
#define IXMLDOMDOCUMENTPTR MSXML2::IXMLDOMDocumentPtr
#define IXMLDOMNODEPTR     MSXML2::IXMLDOMNodePtr

#elif defined ( _USE_MSXML2_ )

#import <msxml2.dll>

using namespace MSXML2;

#define IXMLDOMINTERFACE   L"Msxml2.DOMDocument"
#define IXMLDOMELEMENTPTR  MSXML2::IXMLDOMElementPtr
#define IXMLDOMDOCUMENTPTR MSXML2::IXMLDOMDocumentPtr
#define IXMLDOMNODEPTR     MSXML2::IXMLDOMNodePtr

#else

#import <msxml.dll>

using namespace MSXML;

#define IXMLDOMINTERFACE   L"Msxml.DOMDocument"
#define IXMLDOMELEMENTPTR  MSXML::IXMLDOMElementPtr
#define IXMLDOMDOCUMENTPTR MSXML::IXMLDOMDocumentPtr
#define IXMLDOMNODEPTR     MSXML::IXMLDOMNodePtr

#endif

//  ==========================================================================
//  
//  ==========================================================================
class EZ_MSXMLInterface
{
protected:
	BOOL               m_bCreate;
	BOOL               m_bOpenOK;
	IXMLDOMELEMENTPTR  m_pElement;
	IXMLDOMDOCUMENTPTR m_pXMLDom;

public:
	EZ_MSXMLInterface();
	virtual ~EZ_MSXMLInterface();

	virtual C_BOOL Open( LPCTSTR lpFileName );
	virtual C_BOOL OpenNew( LPCTSTR lpTagName );
	virtual C_BOOL Save( LPCTSTR lpFileName );
	virtual void   Close();

	virtual IXMLDOMNODEPTR InsertNote(                                    LPCTSTR lpChild );
	virtual IXMLDOMNODEPTR InsertNote(                  LPCTSTR lpParent, LPCTSTR lpChild );
	virtual IXMLDOMNODEPTR InsertNote( LPCTSTR lpGrand, LPCTSTR lpParent, LPCTSTR lpChild );

	virtual C_BOOL RemoveNote(                                    LPCTSTR lpChild );
	virtual C_BOOL RemoveNote(                  LPCTSTR lpParent, LPCTSTR lpChild );
	virtual C_BOOL RemoveNote( LPCTSTR lpGrand, LPCTSTR lpParent, LPCTSTR lpChild );

	virtual IXMLDOMNODEPTR FindNote(                                    LPCTSTR lpChild );
	virtual IXMLDOMNODEPTR FindNote(                  LPCTSTR lpParent, LPCTSTR lpChild );
	virtual IXMLDOMNODEPTR FindNote( LPCTSTR lpGrand, LPCTSTR lpParent, LPCTSTR lpChild );

	virtual void GetText( CString& strReturn,                                    LPCTSTR lpChild );
	virtual void GetText( CString& strReturn,                  LPCTSTR lpParent, LPCTSTR lpChild );
	virtual void GetText( CString& strReturn, LPCTSTR lpGrand, LPCTSTR lpParent, LPCTSTR lpChild );

protected:
	virtual C_BOOL Create();

	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
public:
	inline C_BOOL HasOpen() const
	{ 
		return this->m_bOpenOK; 
	}

	//  ==========================================================================
	//  Static Function
	//  ==========================================================================
public:
	static BOOL StringToString( C_BOOL bSrcUnicode, LPCTSTR lpSrcBuf, C_BOOL bDstUnicode, C_INT iDstSize, LPTSTR lpDstBuf, C_INT iCodePage = CP_ACP )
	{
		try
		{
			if ( bSrcUnicode != bDstUnicode )
			{
				if ( bSrcUnicode )
					::WideCharToMultiByte( iCodePage, 0, ( LPCWSTR )lpSrcBuf, -1, ( LPSTR )lpDstBuf, iDstSize, NULL, NULL );
				else
					::MultiByteToWideChar( iCodePage, 0, ( LPCSTR )lpSrcBuf, -1, ( LPWSTR )lpDstBuf, iDstSize );
			}
			else if ( bSrcUnicode )
			{
#if _MSC_VER > 1300
				::wcscpy_s( ( LPWSTR )lpDstBuf, iDstSize, ( LPCWSTR )lpSrcBuf );
#else
				::wcscpy(   ( LPWSTR )lpDstBuf,           ( LPCWSTR )lpSrcBuf );
#endif
			}
			else
			{
#if _MSC_VER > 1300
				::strcpy_s( ( LPSTR )lpDstBuf, iDstSize, ( LPCSTR )lpSrcBuf );
#else
				::strcpy(   ( LPSTR )lpDstBuf,           ( LPCSTR )lpSrcBuf );
#endif
			}

			return TRUE;
		}
		catch ( ... )
		{
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_MSXMLInterface ] StringToString - Error !" ) );

			return FALSE;
		}
	}

	static BOOL StringToString( const CStringA& strSrc, C_BOOL bDstUnicode, C_INT iDstSize, LPTSTR lpDstBuf, C_INT iCodePage = CP_ACP )
	{
		return EZ_MSXMLInterface::StringToString( FALSE, ( LPCTSTR )( LPCSTR )strSrc, bDstUnicode, iDstSize, lpDstBuf, iCodePage );
	}

	static BOOL StringToString( const CStringW& strSrc, C_BOOL bDstUnicode, C_INT iDstSize, LPTSTR lpDstBuf, C_INT iCodePage = CP_ACP )
	{
		return EZ_MSXMLInterface::StringToString( TRUE, ( LPCTSTR )( LPCWSTR )strSrc, bDstUnicode, iDstSize, lpDstBuf, iCodePage );
	}

	static BOOL StringToString( C_BOOL bSrcUnicode, LPCTSTR lpSrcBuf, C_INT iDstSize, CStringA& strDst, C_INT iCodePage = CP_ACP )
	{
		BOOL bResult = EZ_MSXMLInterface::StringToString( bSrcUnicode, lpSrcBuf, FALSE, iDstSize, ( LPTSTR )strDst.GetBuffer( iDstSize ), iCodePage );

		strDst.ReleaseBuffer();

		return bResult;
	}

	static BOOL StringToString( C_BOOL bSrcUnicode, LPCTSTR lpSrcBuf, C_INT iDstSize, CStringW& strDst, C_INT iCodePage = CP_ACP )
	{
		BOOL bResult = EZ_MSXMLInterface::StringToString( bSrcUnicode, lpSrcBuf, TRUE, iDstSize, ( LPTSTR )strDst.GetBuffer( iDstSize ), iCodePage );

		strDst.ReleaseBuffer();

		return bResult;
	}

	static BOOL MultiByteToWideChar( LPCSTR lpMBBuf, C_INT iWCSize, LPWSTR lpWCBuf, C_INT iMBSize = -1, C_INT iCodePage = CP_ACP )
	{
		try
		{
			::MultiByteToWideChar( iCodePage, 0, lpMBBuf, iMBSize, lpWCBuf, iWCSize );

			return TRUE;
		}
		catch ( ... )
		{
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_MSXMLInterface ] MultiByteToWideChar - Error !" ) );

			return FALSE;
		}
	}

	static BOOL WideCharToMultiByte( LPCWSTR lpWCBuf, C_INT iMBSize, LPSTR lpMBBuf, C_INT iWCSize = -1, C_INT iCodePage = CP_ACP )
	{
		try
		{
			::WideCharToMultiByte( iCodePage, 0, lpWCBuf, iWCSize, lpMBBuf, iMBSize, NULL, NULL );

			return TRUE;
		}
		catch ( ... )
		{
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_MSXMLInterface ] WideCharToMultiByte - Error !" ) );

			return FALSE;
		}
	}
};

typedef const EZ_MSXMLInterface  C_EZMSXMLINTERFACE;
typedef       EZ_MSXMLInterface* LPEZMSXMLINTERFACE;
typedef const EZ_MSXMLInterface* LPCEZMSXMLINTERFACE;
