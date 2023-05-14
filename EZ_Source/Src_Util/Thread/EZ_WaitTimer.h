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

#ifndef C_INT
#define C_INT const INT
#endif

#ifndef LPCINT
#define LPCINT const INT*
#endif

#ifndef C_UINT
#define C_UINT const UINT
#endif

#ifndef C_LONGLONG
#define C_LONGLONG const LONGLONG
#endif

#ifndef LPCLONGLONG
#define LPCLONGLONG const LONGLONG*
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
extern HANDLE EZ_CreateWaitableTimer( LPSECURITY_ATTRIBUTES lpSecAttr, C_BOOL bManualReset, LPCTSTR lpName, C_BOOL bGlobal = FALSE );

//  ==========================================================================
//  EZ_WaitTimer
//  ==========================================================================
class EZ_WaitTimer
{
public:
	enum 
	{
		QUAD_PART_BASE = 10000,
	};

protected:
	HANDLE        m_hTimer;
	LONGLONG      m_llTimer;
	LARGE_INTEGER m_liSysTime;

public:
	EZ_WaitTimer( LPSECURITY_ATTRIBUTES lpSecAttr, C_BOOL bManualReset, LPCTSTR lpName, C_BOOL bGlobal = FALSE );
	virtual ~EZ_WaitTimer();

	virtual void Initial( LPSECURITY_ATTRIBUTES lpSecAttr, C_BOOL bManualReset, LPCTSTR lpName, C_BOOL bGlobal = FALSE );
	virtual void Release();

	virtual void Start_MilliSec_Wait_Timer1( LPCINT      lpMilliSec );
	virtual void Start_MilliSec_Wait_Timer2( LPCLONGLONG lpMilliSec );

	virtual void Start_MicroSec_Wait_Timer( LPCLONGLONG lpMicroSec );
	
	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
public:
	inline operator HANDLE () const
	{
		return this->m_hTimer;
	}

	inline HANDLE GetSafeHandle() const
	{
		return this->m_hTimer;
	}

	inline void Cancel_Wait_Timer()
	{ 
		if ( this->m_hTimer ) ::CancelWaitableTimer( this->m_hTimer );
	}

	inline void Start_MilliSec_Wait_Timer1( C_INT iMilliSec )
	{
		this->Start_MilliSec_Wait_Timer1( ( LPCINT )&iMilliSec );
	}

	inline void Start_MilliSec_Wait_Timer2( C_LONGLONG llMilliSec )
	{
		this->Start_MilliSec_Wait_Timer2( ( LPCLONGLONG )&llMilliSec );
	}
 
	inline void Start_MicroSec_Wait_Timer( C_LONGLONG llMicroSec )
	{
		this->Start_MicroSec_Wait_Timer( ( LPCLONGLONG )&llMicroSec );
	}

	//  ==========================================================================
	//  Static Function
	//  ==========================================================================
public:
	static EZ_WaitTimer* Alloc( C_BOOL bManualReset, LPSECURITY_ATTRIBUTES lpSecAttr = NULL, LPCTSTR lpName = NULL, C_BOOL bGlobal = FALSE )
	{
		EZ_WaitTimer* lpTimer = NULL;

		{
#if !defined ( _USE_TRY_CATCH_ )
			lpTimer = ( new EZ_WaitTimer( lpSecAttr, bManualReset, lpName, bGlobal ) );
#else
			TRY
			{
				lpTimer = ( new EZ_WaitTimer( lpSecAttr, bManualReset, lpName, bGlobal ) );
			}
			CATCH ( CMemoryException, e )
			{
				::EZOutputDebugString( _T( "$$$ [ 235-EZ_WaitTimer ] Alloc - Fail !\n" ) );
			}
			END_CATCH;
#endif
		}

		return lpTimer;
	}

    static LPSECURITY_ATTRIBUTES AllocSecurityAttribute();
	static void                  FreeSecurityAttribute( LPSECURITY_ATTRIBUTES& lpSecAttr );
};

typedef const EZ_WaitTimer  C_EZWAITTIMER;
typedef       EZ_WaitTimer* LPEZWAITTIMER;
typedef const EZ_WaitTimer* LPCEZWAITTIMER;
