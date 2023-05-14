#pragma once

#include <AfxWin.h>
#include <Mmsystem.h>

//  ==========================================================================
//  
//  ==========================================================================
#if defined ( EZ_MY_PROJECT )

#include "..\EZDefined.h"

#else

#ifndef C_BOOL
#define C_BOOL const BOOL
#endif

#ifndef C_INT
#define C_INT const INT
#endif

#ifndef C_UINT
#define C_UINT const UINT
#endif

#ifndef C_LONGLONG
#define C_LONGLONG const LONGLONG
#endif

#endif

//  ==========================================================================
//  Defined
//  ==========================================================================
#define COUNTER_MILLISEC  1000		//  1 Sec  = 1000 MilliSec
#define COUNTER_MICROSEC  1000000	//  1 MSec = 1000 MicroSec
//#define COUNTER_AMICROSEC 1000		//  

//  ==========================================================================
//  EZ_PerformanceCounter
//  ==========================================================================
class EZ_PerformanceCounter
{
public:
	LARGE_INTEGER        m_liCounter;
	static LARGE_INTEGER gm_liFrequency;

public:
	EZ_PerformanceCounter( __in C_BOOL bGetCounter = FALSE );
	virtual ~EZ_PerformanceCounter();

	EZ_PerformanceCounter& operator = ( __in const EZ_PerformanceCounter& pfCounter );

	virtual C_INT operator - ( __in const EZ_PerformanceCounter& pfCounter ) const;

	virtual void GetCounterNow();
	
	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
public:
	inline void Empty()
	{
		this->m_liCounter.QuadPart = 0;
	}

	inline C_BOOL IsEmpty() const
	{
		return ( this->m_liCounter.QuadPart == 0 );
	}

	inline C_INT GetMilliSeconds() const
	{
		EZ_PerformanceCounter pfStop( TRUE );

		return EZ_PerformanceCounter::GetMilliSeconds( this->m_liCounter.QuadPart, pfStop.m_liCounter.QuadPart );
	}

	inline C_INT GetMilliSeconds( __in C_LONGLONG& llTickStart ) const
	{
		return EZ_PerformanceCounter::GetMilliSeconds( llTickStart, this->m_liCounter.QuadPart );
	}

	inline C_INT GetMilliSeconds( __in const EZ_PerformanceCounter& pfStart ) const
	{
		return EZ_PerformanceCounter::GetMilliSeconds( pfStart.m_liCounter.QuadPart, this->m_liCounter.QuadPart );
	}

	inline C_LONGLONG GetMicroSeconds() const
	{
		EZ_PerformanceCounter pfStop( TRUE );

		return EZ_PerformanceCounter::GetMicroSeconds( this->m_liCounter.QuadPart, pfStop.m_liCounter.QuadPart );
	}

	inline C_LONGLONG GetMicroSeconds( __in C_LONGLONG& llTickStart ) const
	{
		return EZ_PerformanceCounter::GetMicroSeconds( llTickStart, this->m_liCounter.QuadPart );
	}

	inline C_LONGLONG GetMicroSeconds( __in const EZ_PerformanceCounter& pfStart ) const
	{
		return EZ_PerformanceCounter::GetMicroSeconds( pfStart.m_liCounter.QuadPart, this->m_liCounter.QuadPart );
	}

	//  ==========================================================================
	//  Static Function
	//  ==========================================================================
public:
	static C_INT GetMilliSeconds( __in C_LONGLONG& llTickStart, __in LONGLONG llTicksStop )
	{
		llTicksStop -= llTickStart;
		
		if ( EZ_PerformanceCounter::gm_liFrequency.QuadPart > 1 ) { llTicksStop *= COUNTER_MILLISEC; llTicksStop /= EZ_PerformanceCounter::gm_liFrequency.QuadPart; }

		return ( INT )llTicksStop;
	}

	static C_INT GetMilliSeconds( __in const LARGE_INTEGER& liStart, __in const LARGE_INTEGER& liStop )
	{
		return EZ_PerformanceCounter::GetMilliSeconds( liStart.QuadPart, liStop.QuadPart );
	}

	static C_INT GetMilliSeconds( __in const EZ_PerformanceCounter& pfStart, __in const EZ_PerformanceCounter& pfStop )
	{
		return EZ_PerformanceCounter::GetMilliSeconds( pfStart.m_liCounter.QuadPart, pfStop.m_liCounter.QuadPart );
	}

	static C_LONGLONG GetMicroSeconds( __in C_LONGLONG& llTickStart, __in LONGLONG llTicksStop )
	{
		llTicksStop -= llTickStart; 
		
		if ( EZ_PerformanceCounter::gm_liFrequency.QuadPart > 1 ) { llTicksStop *= COUNTER_MICROSEC; llTicksStop /= EZ_PerformanceCounter::gm_liFrequency.QuadPart; }

		return llTicksStop;
	}

	static void GetFrequency();
};

typedef const EZ_PerformanceCounter  C_EZPERFORMANCECOUNTER;
typedef       EZ_PerformanceCounter* LPEZPERFORMANCECOUNTER;
typedef const EZ_PerformanceCounter* LPCEZPERFORMANCECOUNTER;

//  ==========================================================================
//  EZ_PerformanceCounterV2
//  ==========================================================================
class EZ_PerformanceCounterV2
{
public:
	EZ_PerformanceCounter m_pfStart;
	EZ_PerformanceCounter m_pfStop;

public:
	EZ_PerformanceCounterV2( __in C_BOOL bStart = FALSE ) : m_pfStart( bStart ), m_pfStop( FALSE )
	{
		;
	}

	virtual ~EZ_PerformanceCounterV2()
	{
		//  this->m_pfStart
		//  this->m_pfStop
	}

	virtual void Empty()
	{
		this->m_pfStart.Empty();
		this->m_pfStop.Empty();
	}

	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
public:
	inline void Start()
	{
		this->m_pfStart.GetCounterNow();

		this->m_pfStop = this->m_pfStart;
	}

	inline C_INT Stop()
	{
		this->m_pfStop.GetCounterNow();

		return EZ_PerformanceCounter::GetMilliSeconds( this->m_pfStart.m_liCounter.QuadPart, this->m_pfStop.m_liCounter.QuadPart );
	}
};

typedef const EZ_PerformanceCounterV2  C_EZPERFORMANCECOUNTERV2;
typedef       EZ_PerformanceCounterV2* LPEZPERFORMANCECOUNTERV2;
typedef const EZ_PerformanceCounterV2* LPCEZPERFORMANCECOUNTERV2;

//  ==========================================================================
//  EZ_TimeCounter
//  ==========================================================================
class EZ_TimeCounter
{
public:
	UINT m_iCounter;

public:
	EZ_TimeCounter( __in C_BOOL bGetCounter = TRUE ) : m_iCounter( ( bGetCounter ? ::timeGetTime() : 0 ) )
	{
		;
	}

	virtual ~EZ_TimeCounter()
	{
		//  this->m_iCounter
	}

	EZ_TimeCounter& operator = ( __in const EZ_TimeCounter& timeCounter )
	{
		if ( this != &timeCounter )
			this->m_iCounter = timeCounter.m_iCounter;

		return *this;
	}

	virtual void GetCounterNow()
	{
		this->m_iCounter = ::timeGetTime();
	}

	virtual C_INT GetMilliSeconds() const
	{
		EZ_TimeCounter tcStop( TRUE );

		return tcStop.GetMilliSeconds( this->m_iCounter );
	}

	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
public:
	inline void Empty()
	{
		this->m_iCounter = 0;
	}

	inline C_BOOL IsEmpty() const
	{
		return ( this->m_iCounter == 0 );
	}

	inline C_INT GetMilliSeconds( __in C_UINT& nTickStart ) const
	{
		return ( INT )( this->m_iCounter - nTickStart );
	}

	inline C_INT GetMilliSeconds( __in const EZ_TimeCounter& tcStart ) const
	{
		return this->GetMilliSeconds( tcStart.m_iCounter );
	}
};

typedef const EZ_TimeCounter  C_EZTIMECOUNTER;
typedef       EZ_TimeCounter* LPEZTIMECOUNTER;
typedef const EZ_TimeCounter* LPCEZTIMECOUNTER;
