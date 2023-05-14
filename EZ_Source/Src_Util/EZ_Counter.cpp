#include "StdAfx.h"
#include "EZ_Counter.h"

//  ==========================================================================
//  
//  ==========================================================================
#pragma comment( lib, "Winmm.lib" )

//  ==========================================================================
//  
//  ==========================================================================
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//  ==========================================================================
//  
//  ==========================================================================
LARGE_INTEGER EZ_PerformanceCounter::gm_liFrequency = { 1 };

//  ==========================================================================
//  
//  ==========================================================================
EZ_PerformanceCounter::EZ_PerformanceCounter( C_BOOL bGetCounter )
{
	if ( bGetCounter )
		this->GetCounterNow();
	else
		this->m_liCounter.QuadPart = 0;
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_PerformanceCounter::~EZ_PerformanceCounter()
{
	//  this->m_liCounter
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_PerformanceCounter& EZ_PerformanceCounter::operator = ( const EZ_PerformanceCounter& pfCounter )
{
	if ( this != &pfCounter )
		this->m_liCounter.QuadPart = pfCounter.m_liCounter.QuadPart;

	return *this;
}

//  ==========================================================================
//  
//  ==========================================================================
C_INT EZ_PerformanceCounter::operator - ( const EZ_PerformanceCounter& pfCounter ) const
{
	return this->GetMilliSeconds( pfCounter.m_liCounter.QuadPart );
}

//  ==========================================================================
//  GetCounterNow
//  ==========================================================================
void EZ_PerformanceCounter::GetCounterNow()
{
	if ( EZ_PerformanceCounter::gm_liFrequency.QuadPart == 1 )
		this->m_liCounter.QuadPart = ::GetTickCount64();
	else if ( !::QueryPerformanceCounter( &this->m_liCounter ) )
		this->m_liCounter.QuadPart = 0;
}

//  ==========================================================================
//  GetFrequency ( Stataic )
//  ==========================================================================
void EZ_PerformanceCounter::GetFrequency()
{
	if ( !::QueryPerformanceFrequency( &EZ_PerformanceCounter::gm_liFrequency ) )
		EZ_PerformanceCounter::gm_liFrequency.QuadPart = 1;
}
