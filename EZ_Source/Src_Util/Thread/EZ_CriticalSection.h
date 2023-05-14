#pragma once

//  ==========================================================================
//  EZ_CriticalSection
//  ==========================================================================
class EZ_CriticalSection
{
protected:
	CRITICAL_SECTION m_csObject;

public:
	EZ_CriticalSection( CRITICAL_SECTION* lpSection = NULL ) : m_csObject()
	{
		if ( lpSection )
			::memcpy( &this->m_csObject, lpSection, sizeof( CRITICAL_SECTION ) );
		else
			::memset( &this->m_csObject, 0,         sizeof( CRITICAL_SECTION ) );

		::InitializeCriticalSection( &this->m_csObject );
	}

	virtual ~EZ_CriticalSection()
	{
		this->DeleteObject();
	}

	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
public:
	inline operator CRITICAL_SECTION& ()
	{
		return this->m_csObject;
	}

	inline void DeleteObject()
	{
		::DeleteCriticalSection( &this->m_csObject );
	}

	inline void Lock()
	{
		::EnterCriticalSection( &this->m_csObject );
	}

	inline void Unlock()
	{
		::LeaveCriticalSection( &this->m_csObject );
	}

	//  ==========================================================================
	//  Static Function
	//  ==========================================================================
public:
	static EZ_CriticalSection* Alloc( CRITICAL_SECTION* lpSrcCS = NULL )
	{
		EZ_CriticalSection* lpDstCS = NULL;

		{
#if !defined ( _USE_TRY_CATCH_ )
			lpDstCS = new EZ_CriticalSection( lpSrcCS );
#else
			TRY
			{
				lpDstCS = new EZ_CriticalSection( lpSrcCS );
			}
			CATCH ( CMemoryException, e )
			{
				::EZOutputDebugString( _T( "$$$ [ 235-EZ_CriticalSection ] Alloc - Fail !\n" ) );
			}
			END_CATCH;
#endif
		}

		return lpDstCS;
	}
};

typedef const EZ_CriticalSection  C_EZCRITICALSECTION;
typedef       EZ_CriticalSection* LPEZCRITICALSECTION;
typedef const EZ_CriticalSection* LPCEZCRITICALSECTION;

//  ==========================================================================
//  EZ_CriticalSectionLock
//  ==========================================================================
class EZ_CriticalSectionLock
{
protected:
	CRITICAL_SECTION& m_csObject;

public:
	EZ_CriticalSectionLock( CRITICAL_SECTION& csObject ) : m_csObject( csObject )
	{
		::EnterCriticalSection( &this->m_csObject );
	}

	virtual ~EZ_CriticalSectionLock()
	{
		::LeaveCriticalSection( &this->m_csObject );
	}
};

typedef const EZ_CriticalSection  C_EZCRITICALSECTIONLOCK;
typedef       EZ_CriticalSection* LPEZCRITICALSECTIONLOCK;
typedef const EZ_CriticalSection* LPCEZCRITICALSECTIONLOCK;
