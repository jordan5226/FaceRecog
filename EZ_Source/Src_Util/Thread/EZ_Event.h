#pragma once

//  ==========================================================================
//  Defined
//  ==========================================================================
#if defined ( EZ_MY_PROJECT )

#include "..\..\EZDefined.h"

#else

#ifndef C_BOOL
#define C_BOOL const BOOL
#endif

#ifndef SAFE_CLOSE_HANDLE
#define SAFE_CLOSE_HANDLE( p ) { if ( p ) { ::CloseHandle( p ); p = NULL; } }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE( p ) { if ( p ) { delete p; p = NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY( p ) { if ( p ) { delete [] p; p = NULL; } }
#endif

#endif

//  ==========================================================================
//  Global Function
//  ==========================================================================
extern HANDLE EZ_CreateEvent( LPSECURITY_ATTRIBUTES lpSecAttr, C_BOOL bManualReset, C_BOOL bInitState, LPCTSTR lpName, BOOL bGlobal = FALSE, UINT* lpLastError = NULL );

//  ==========================================================================
//  EZ_Event
//  ==========================================================================
class EZ_Event
{
protected:
	UINT   m_iLastError;
	HANDLE m_hObject;

public:
	EZ_Event( C_BOOL bInitOwn = FALSE, C_BOOL bManualReset = FALSE, LPCTSTR lpName = NULL, LPSECURITY_ATTRIBUTES lpSecAttr = NULL, C_BOOL bGlobal = FALSE );
	virtual ~EZ_Event();

	virtual C_BOOL Create( C_BOOL bInitOwn = FALSE, C_BOOL bManualReset = FALSE, LPCTSTR lpName = NULL, LPSECURITY_ATTRIBUTES lpSecAttr = NULL, C_BOOL bGlobal = FALSE );

	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
public:
	inline operator HANDLE () const
	{
		return this->m_hObject;
	}

	inline HANDLE GetSafeHandle() const
	{
		return this->m_hObject;
	}

	inline UINT GetErrorCode() const
	{
		return this->m_iLastError;
	}

	inline C_BOOL SetEvent()
	{
		return ( this->m_hObject ? ::SetEvent( this->m_hObject ) : FALSE );
	}

	inline C_BOOL ResetEvent()
	{
		return ( this->m_hObject ? ::ResetEvent( this->m_hObject ) : FALSE );
	}

	inline C_BOOL PulseEvent()
	{ 
		return ( this->m_hObject ? ::PulseEvent( this->m_hObject ) : FALSE );
	}

	inline void DeleteObject()
	{
		this->m_iLastError = ERROR_SUCCESS;

		SAFE_CLOSE_HANDLE ( this->m_hObject );
	}

	//  ==========================================================================
	//  Static Function
	//  ==========================================================================
public:
	static EZ_Event* Alloc( C_BOOL bInitOwn, C_BOOL bManualReset, LPCTSTR lpName = NULL, LPSECURITY_ATTRIBUTES lpSecAttr = NULL, C_BOOL bGlobal = FALSE )
	{
		EZ_Event* lpEvent = NULL;

		{
#if !defined ( _USE_TRY_CATCH_ )
			lpEvent = new EZ_Event( bInitOwn, bManualReset, lpName, lpSecAttr, bGlobal );
#else
			TRY
			{
				lpEvent = new EZ_Event( bInitOwn, bManualReset, lpName, lpSecAttr, bGlobal );
			}
			CATCH ( CMemoryException, e )
			{
				::EZOutputDebugString( _T( "$$$ [ 235-EZ_Event ] Alloc - Fail !\n" ) );
			}
			END_CATCH;
#endif
		}

		return lpEvent;
	}

    static LPSECURITY_ATTRIBUTES AllocSecurityAttribute();
	static void                  FreeSecurityAttribute( LPSECURITY_ATTRIBUTES& lpSecAttr );
};

typedef const EZ_Event   C_EZEVENT;
typedef       EZ_Event*  LPEZEVENT;
typedef       EZ_Event** LPPEZEVENT;
typedef const EZ_Event*  LPCEZEVENT;
typedef const EZ_Event** LPPCEZEVENT;
