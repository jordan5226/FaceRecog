#include "stdafx.h"
#include <ComUtil.h>
#include "EZ_MSXMLInterface.h"

//  ==========================================================================
//  
//  ==========================================================================
#pragma comment( lib, "Comsuppw.lib" )

//  ==========================================================================
//  
//  ==========================================================================
EZ_MSXMLInterface::EZ_MSXMLInterface() : m_bCreate( FALSE ), m_bOpenOK( FALSE ), 
					m_pElement( NULL ), m_pXMLDom( NULL )
{
	;
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_MSXMLInterface::~EZ_MSXMLInterface()
{  
	this->Close();
}

//  ==========================================================================
//  Create
//  ==========================================================================
C_BOOL EZ_MSXMLInterface::Create()
{
	if ( !this->m_bCreate )
	{
		this->m_bCreate = SUCCEEDED ( this->m_pXMLDom.CreateInstance( IXMLDOMINTERFACE ) );

		if ( this->m_bCreate )
		{
			//  
			this->m_pXMLDom->async = VARIANT_FALSE;

			//  保留空白字元 ( Exp : " Exit " )
			HRESULT hrRes = this->m_pXMLDom->put_preserveWhiteSpace( VARIANT_TRUE );
			ASSERT ( S_OK == hrRes );
		}
	}

	return this->m_bCreate;
}

//  ==========================================================================
//  Open
//  ==========================================================================
C_BOOL EZ_MSXMLInterface::Open( LPCTSTR lpFileName )
{
	this->Close();

	if ( lpFileName && ( ::GetFileAttributes( lpFileName ) != INVALID_FILE_ATTRIBUTES ) )
	{
		if ( this->Create() )
		{
			VARIANT_BOOL bResult = this->m_pXMLDom->load( lpFileName );

			if ( ( bResult != E_INVALIDARG ) && ( this->m_pXMLDom->parseError->GeterrorCode() == 0 ) )
			{
				this->m_pElement = this->m_pXMLDom->GetdocumentElement();
				this->m_bOpenOK  = ( this->m_pElement != NULL );
			}
		}
	}

	return this->m_bOpenOK;
}

//  ==========================================================================
//  OpenNew
//  ==========================================================================
C_BOOL EZ_MSXMLInterface::OpenNew( LPCTSTR lpTagName )
{
	this->Close();

	if ( lpTagName && this->Create() )
	{
		//  
		TCHAR tzXMLDescription[ 128 ] = _T( "" );

		::wsprintf( tzXMLDescription, _T( "<?xml version=\"1.0\" encoding=\"UTF-8\"?><%s></%s>" ), lpTagName, lpTagName );

		//  
		VARIANT_BOOL bResult = this->m_pXMLDom->loadXML( tzXMLDescription );

		if ( ( bResult != E_INVALIDARG ) && ( this->m_pXMLDom->parseError->GeterrorCode() == 0 ) )
		{
			this->m_pElement = this->m_pXMLDom->GetdocumentElement();
			this->m_bOpenOK  = ( this->m_pElement != NULL );
		}
	}

	return this->m_bOpenOK;
}

//  ==========================================================================
//  Close
//  ==========================================================================
void EZ_MSXMLInterface::Close()
{
	if ( this->m_bCreate )
		this->m_pXMLDom.Release();

	this->m_bCreate  = FALSE;
	this->m_bOpenOK  = FALSE;
	this->m_pElement = NULL;
	this->m_pXMLDom  = NULL;
}

//  ==========================================================================
//  Save
//  ==========================================================================
C_BOOL EZ_MSXMLInterface::Save( LPCTSTR lpFileName )
{
	BOOL bResult = FALSE;

	if ( this->m_bCreate && this->m_bOpenOK )
		bResult = SUCCEEDED ( this->m_pXMLDom->save( lpFileName ) );

	return bResult;
}

//  ==========================================================================
//  InsertNote
//  ==========================================================================
IXMLDOMNODEPTR EZ_MSXMLInterface::InsertNote( LPCTSTR lpChild )
{
	IXMLDOMNODEPTR lpRetNote = NULL;
	
	if ( this->m_pElement )
	{
		_variant_t     intType     = ( long )1;
		IXMLDOMNODEPTR lpChildNote = this->m_pXMLDom->createNode( intType, lpChild, _T( "" ) );
		
		lpRetNote = ( lpChildNote ? this->m_pElement->appendChild( lpChildNote ) : NULL );
	}
	
	return lpRetNote;
}

IXMLDOMNODEPTR EZ_MSXMLInterface::InsertNote( LPCTSTR lpParent, LPCTSTR lpChild )
{
	IXMLDOMNODEPTR lpRetNote = NULL;
	
	if ( this->m_pElement )
	{
		IXMLDOMNODEPTR lpParentNote = this->m_pElement->selectSingleNode( lpParent );
		
		if ( lpParentNote != NULL ) 
		{
			_variant_t     intType     = ( long )1;
			IXMLDOMNODEPTR lpChildNote = this->m_pXMLDom->createNode( intType, lpChild, _T( "" ) );
			
			lpRetNote = ( lpChildNote ? lpParentNote->appendChild( lpChildNote ) : NULL );
		}
	}
	
	return lpRetNote;
}

IXMLDOMNODEPTR EZ_MSXMLInterface::InsertNote( LPCTSTR lpGrand, LPCTSTR lpParent, LPCTSTR lpChild )
{
	IXMLDOMNODEPTR lpRetNote = NULL;

	if ( this->m_pElement )
	{
		IXMLDOMNODEPTR lpGrandNote = this->m_pElement->selectSingleNode( lpGrand );

		if ( lpGrandNote != NULL ) 
		{
			IXMLDOMNODEPTR lpParentNote = lpGrandNote->selectSingleNode( lpParent );

			if ( lpParentNote != NULL ) 
			{
				_variant_t     intType     = ( long )1;
				IXMLDOMNODEPTR lpChildNote = this->m_pXMLDom->createNode( intType, lpChild, _T( "" ) );

				lpRetNote = ( lpChildNote ? lpParentNote->appendChild( lpChildNote ) : NULL );
			}
		}
	}

	return lpRetNote;
}

//  ==========================================================================
//  Save
//  ==========================================================================
C_BOOL EZ_MSXMLInterface::RemoveNote( LPCTSTR lpChild )
{
	BOOL bResult = FALSE;

	if ( this->m_pElement )
	{
		IXMLDOMNODEPTR lpChildNote = this->m_pElement->selectSingleNode( lpChild );

		if ( lpChildNote )
			bResult = ( this->m_pElement->removeChild( lpChildNote ) != NULL );
	}

	return bResult;
}

C_BOOL EZ_MSXMLInterface::RemoveNote( LPCTSTR lpParent, LPCTSTR lpChild )
{
	BOOL bResult = FALSE;

	if ( this->m_pElement )
	{
		IXMLDOMNODEPTR lpParentNote = this->m_pElement->selectSingleNode( lpParent );

		if ( lpParentNote )
		{
			IXMLDOMNODEPTR lpChildNote = lpParentNote->selectSingleNode( lpChild );

			if ( lpChildNote )
				bResult = ( lpParentNote->removeChild( lpChildNote ) != NULL );
		}
	}

	return bResult;
}

C_BOOL EZ_MSXMLInterface::RemoveNote( LPCTSTR lpGrand, LPCTSTR lpParent, LPCTSTR lpChild )
{
	BOOL bResult = FALSE;

	if ( this->m_pElement )
	{
		IXMLDOMNODEPTR lpGrandNote = this->m_pElement->selectSingleNode( lpGrand );

		if ( lpGrandNote )
		{
			IXMLDOMNODEPTR lpParentNote = lpGrandNote->selectSingleNode( lpParent );

			if ( lpParentNote )
			{
				IXMLDOMNODEPTR lpChildNote = lpParentNote->selectSingleNode( lpChild );

				if ( lpChildNote )
					bResult = ( lpParentNote->removeChild( lpChildNote ) != NULL );
			}
		}
	}

	return bResult;
}

//  ==========================================================================
//  FindNote
//  ==========================================================================
IXMLDOMNODEPTR EZ_MSXMLInterface::FindNote( LPCTSTR lpChild )
{
	return ( this->m_pElement ? this->m_pElement->selectSingleNode( lpChild ) : NULL );
}

IXMLDOMNODEPTR EZ_MSXMLInterface::FindNote( LPCTSTR lpParent, LPCTSTR lpChild )
{
	IXMLDOMNODEPTR lpChildNote = NULL;

	if ( this->m_pElement != NULL ) 
	{
		IXMLDOMNODEPTR lpParentNote = this->m_pElement->selectSingleNode( lpParent );

		if ( lpParentNote != NULL ) 
			lpChildNote = lpParentNote->selectSingleNode( lpChild );
	}

	return lpChildNote;
}

IXMLDOMNODEPTR EZ_MSXMLInterface::FindNote( LPCTSTR lpGrand, LPCTSTR lpParent, LPCTSTR lpChild )
{
	IXMLDOMNODEPTR lpChildNote = NULL;

	if ( this->m_pElement != NULL ) 
	{
		IXMLDOMNODEPTR lpGrandNote = this->m_pElement->selectSingleNode( lpGrand );

		if ( lpGrandNote != NULL )
		{
			IXMLDOMNODEPTR lpParentNote = lpGrandNote->selectSingleNode( lpParent );

			if ( lpParentNote != NULL ) 
				lpChildNote = lpParentNote->selectSingleNode( lpChild );
		}
	}

	return lpChildNote;
}

//  ==========================================================================
//  GetText
//  ==========================================================================
void EZ_MSXMLInterface::GetText( CString& strReturn, LPCTSTR lpChild )
{
	//  
	strReturn.Empty();

	if ( this->m_pElement == NULL ) 
	{	
		;
		return;
	}

	//  
	IXMLDOMNODEPTR lpChildNote = this->m_pElement->selectSingleNode( lpChild );

	if ( lpChildNote == NULL )
	{
		;
		return;
	}

	//  
	_bstr_t bszText = lpChildNote->Gettext();
	INT     iLength = bszText.length();

	if ( iLength <= 0 )
	{
		;
		return;
	}

	//  
#if defined ( UNICODE )
	strReturn.Format( L"%s", ( LPCWSTR )bszText );
#else
	iLength += 4;
	iLength *= 2;

	EZ_MSXMLInterface::WideCharToMultiByte( bszText, iLength, strReturn.GetBuffer( iLength ) );

	strReturn.ReleaseBuffer();
#endif
}

void EZ_MSXMLInterface::GetText( CString& strReturn, LPCTSTR lpParent, LPCTSTR lpChild )
{
	//  
	strReturn.Empty();

	if ( this->m_pElement == NULL ) 
	{
		;
		return;
	}

	//  
	IXMLDOMNODEPTR lpParentNote = this->m_pElement->selectSingleNode( lpParent );

	if ( lpParentNote == NULL ) 
	{	
		;
		return;
	}

	//  
	IXMLDOMNODEPTR lpChildNote = lpParentNote->selectSingleNode( lpChild );

	if ( lpChildNote == NULL )
	{
		;
		return;
	}

	//  
	_bstr_t bszText = lpChildNote->Gettext();
	INT     iLength = bszText.length();

	if ( iLength <= 0 )
	{
		;
		return;
	}

	//  
#if defined ( UNICODE )
	strReturn.Format( L"%s", ( LPCWSTR )bszText );
#else
	iLength += 4;
	iLength *= 2;

	EZ_MSXMLInterface::WideCharToMultiByte( bszText, iLength, strReturn.GetBuffer( iLength ) );

	strReturn.ReleaseBuffer();
#endif
}

void EZ_MSXMLInterface::GetText( CString& strReturn, LPCTSTR lpGrand, LPCTSTR lpParent, LPCTSTR lpChild )
{
	//  
	strReturn.Empty();

	if ( this->m_pElement == NULL ) 
	{
		;
		return;
	}

	//  
	IXMLDOMNODEPTR lpGrandNote = this->m_pElement->selectSingleNode( lpGrand );

	if ( lpGrandNote == NULL )
	{
		;
		return;
	}

	//  
	IXMLDOMNODEPTR lpParentNote = lpGrandNote->selectSingleNode( lpParent );

	if ( lpParentNote == NULL ) 
	{	
		;
		return;
	}

	//  
	IXMLDOMNODEPTR lpChildNote = lpParentNote->selectSingleNode( lpChild );

	if ( lpChildNote == NULL )
	{
		;
		return;
	}

	//  
	_bstr_t bszText = lpChildNote->Gettext();
	INT     iLength = bszText.length();

	if ( iLength <= 0 )
	{
		;
		return;
	}

	//  
#if defined ( UNICODE )
	strReturn.Format( L"%s", ( LPCWSTR )bszText );
#else
	iLength += 4;
	iLength *= 2;

	EZ_MSXMLInterface::WideCharToMultiByte( bszText, iLength, strReturn.GetBuffer( iLength ) );

	strReturn.ReleaseBuffer();
#endif
}
