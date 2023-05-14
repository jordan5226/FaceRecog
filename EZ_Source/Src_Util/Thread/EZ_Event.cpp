#include "StdAfx.h"
#include "EZ_Event.h"

//  ==========================================================================
//  
//  ==========================================================================
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//  ==========================================================================
//  EZ_CreateEvent
//  ==========================================================================
HANDLE EZ_CreateEvent( LPSECURITY_ATTRIBUTES lpSecAttr, C_BOOL bManualReset, C_BOOL bInitState, LPCTSTR lpName, BOOL bGlobal, UINT* lpLastError )
{
	HANDLE hEvent = NULL;

	{
		//  Open or Create Event
		if ( !lpName || ( ::_tcslen( lpName ) == 0 ) )
			hEvent = ::CreateEvent( lpSecAttr, bManualReset, bInitState, lpName );
		else
		{
			//  Get Event Name
			CString strName = _T( "" );

			strName.Format( _T( "%s" ), lpName );

			if ( bGlobal )
			{
				if ( strName.Find( _T( "Global\\" ) ) < 0 )
					strName.Format( _T( "Global\\%s" ), lpName );
			}
			else
			{
				if ( strName.Find( _T( "Global\\" ) ) >= 0 )
					bGlobal = TRUE;
			}

			//  Open Event
			hEvent = ::OpenEvent( ( SYNCHRONIZE | WRITE_OWNER | EVENT_ALL_ACCESS | EVENT_MODIFY_STATE ), FALSE, strName );

			if ( !hEvent )
			{
				//  Alloc Temp Security Attributes
				BOOL bAllocMem = ( lpSecAttr == NULL );

				if ( bAllocMem )
					lpSecAttr = EZ_Event::AllocSecurityAttribute();

				//  Create Event
				hEvent = ( lpSecAttr ? ::CreateEvent( lpSecAttr, bManualReset, bInitState, strName ) : NULL );

				//  Free Temp Security Attributes
				if ( bAllocMem )
					EZ_Event::FreeSecurityAttribute( lpSecAttr );
			}
		}

		//  Get Error Code
		if ( !hEvent && lpLastError )
			*lpLastError = ::GetLastError();
	}

	return hEvent;
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_Event::EZ_Event( C_BOOL bInitOwn, C_BOOL bManualReset, LPCTSTR lpName, LPSECURITY_ATTRIBUTES lpSecAttr, C_BOOL bGlobal ) 
		: m_iLastError( ERROR_SUCCESS ), m_hObject( NULL )
{
	this->m_hObject = ::EZ_CreateEvent( lpSecAttr, bManualReset, bInitOwn, lpName, bGlobal, &this->m_iLastError );
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_Event::~EZ_Event()
{
	this->DeleteObject();
}

//  ==========================================================================
//  Create
//  ==========================================================================
C_BOOL EZ_Event::Create( C_BOOL bInitOwn, C_BOOL bManualReset, LPCTSTR lpName, LPSECURITY_ATTRIBUTES lpSecAttr, C_BOOL bGlobal )
{
	this->DeleteObject();

	this->m_hObject = ::EZ_CreateEvent( lpSecAttr, bManualReset, bInitOwn, lpName, bGlobal, &this->m_iLastError );

	return ( this->m_hObject != NULL );
}

//  ==========================================================================
//  AllocSecurityAttribute ( Static )
//  ==========================================================================
LPSECURITY_ATTRIBUTES EZ_Event::AllocSecurityAttribute()
{
	LPSECURITY_ATTRIBUTES lpSecAttr = new SECURITY_ATTRIBUTES;

	if ( lpSecAttr != NULL )
	{ 
		::memset( lpSecAttr, 0, sizeof( SECURITY_ATTRIBUTES ) );

		lpSecAttr->nLength              = sizeof( SECURITY_ATTRIBUTES );
		lpSecAttr->lpSecurityDescriptor = ( LPVOID )( new char [ SECURITY_DESCRIPTOR_MIN_LENGTH ] );

		if ( lpSecAttr->lpSecurityDescriptor == NULL )
			EZ_Event::FreeSecurityAttribute( lpSecAttr );
		else if ( ::InitializeSecurityDescriptor( lpSecAttr->lpSecurityDescriptor, SECURITY_DESCRIPTOR_REVISION ) == FALSE )
			EZ_Event::FreeSecurityAttribute( lpSecAttr );
		else if ( ::SetSecurityDescriptorDacl( lpSecAttr->lpSecurityDescriptor, TRUE, 0, FALSE ) == FALSE )
			EZ_Event::FreeSecurityAttribute( lpSecAttr );
	}

	return lpSecAttr;
}

//  ==========================================================================
//  FreeSecurityAttribute ( Static )
//  ==========================================================================
void EZ_Event::FreeSecurityAttribute( LPSECURITY_ATTRIBUTES& lpSecurityAtt )
{
#if 1
	if ( lpSecurityAtt )
	{
		if ( lpSecurityAtt->lpSecurityDescriptor )
		{
			delete [] lpSecurityAtt->lpSecurityDescriptor;
			lpSecurityAtt->lpSecurityDescriptor = NULL;
		}

		delete lpSecurityAtt;
		lpSecurityAtt = NULL;
	}
#else
	if ( lpSecurityAtt )
	{
		SAFE_DELETE_ARRAY ( lpSecurityAtt->lpSecurityDescriptor );
	}

	SAFE_DELETE ( lpSecurityAtt );
#endif
}
