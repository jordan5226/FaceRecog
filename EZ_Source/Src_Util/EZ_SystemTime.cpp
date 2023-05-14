#include "StdAfx.h"
#include <Locale.h>
#include "EZ_SystemTime.h"

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
EZ_SystemTime::EZ_SystemTime( C_BOOL bGetCurrentTime ) : m_Time()
{
	if ( bGetCurrentTime )
		EZ_SystemTime::Get_OS_Time( this->m_Time );
	else
		this->Empty();
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_SystemTime::EZ_SystemTime( const time_t tTime, C_BOOL bCTime ) : m_Time()
{
	this->Set_Full_Time( tTime, bCTime );
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_SystemTime::EZ_SystemTime( C_INT iYear, C_INT iMonth, C_INT iDay ) : m_Time()
{
	this->Set_Date( iYear, iMonth, iDay ), this->Set_Time( 0, 0, 0, 0 );
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_SystemTime::EZ_SystemTime( C_INT iHour, C_INT iMinute, C_INT iSecond, C_INT iMillisecond ) : m_Time()
{
	this->Set_Date( 2000, 1, 1 ), this->Set_Time( iHour, iMinute, iSecond, iMillisecond );
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_SystemTime::EZ_SystemTime( C_INT iDate, C_INT iHour, C_INT iMinute, C_INT iSecond, C_INT iMillisecond ) : m_Time()
{
	this->Set_Date( iDate ); this->Set_Time( iHour, iMinute, iSecond, iMillisecond );
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_SystemTime::EZ_SystemTime( C_INT iYear, C_INT iMonth, C_INT iDay, C_INT iHour, C_INT iMinute, C_INT iSecond, C_INT iMillisecond ) : m_Time()
{
	this->Set_Date( iYear, iMonth, iDay ), this->Set_Time( iHour, iMinute, iSecond, iMillisecond );
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_SystemTime::EZ_SystemTime( LPCSTR lpTime ) : m_Time()
{
	EZ_SystemTime::Get_Time( lpTime, this->m_Time );
}

EZ_SystemTime::EZ_SystemTime( LPCWSTR lpTime ) : m_Time()
{
	EZ_SystemTime::Get_Time( lpTime, this->m_Time );
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_SystemTime::EZ_SystemTime( const CStringA& strTime ) : m_Time()
{
	EZ_SystemTime::Get_Time( strTime, this->m_Time );
}

EZ_SystemTime::EZ_SystemTime( const CStringW& strTime ) : m_Time()
{
	EZ_SystemTime::Get_Time( strTime, this->m_Time );
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_SystemTime::EZ_SystemTime( const SYSTEMTIME& stTime ) : m_Time( stTime )
{
	;
}

EZ_SystemTime::EZ_SystemTime( const SYSTEMTIME* lpTime ) : m_Time()
{
	*this = lpTime;
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_SystemTime::EZ_SystemTime( const struct tm& tmTime ) : m_Time()
{
	*this = tmTime;
}

EZ_SystemTime::EZ_SystemTime( const struct tm* lpTime ) : m_Time()
{
	if ( !lpTime )
		this->Empty();
	else
		*this = *lpTime;
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_SystemTime::EZ_SystemTime( __in const timeval& tvTime, __in C_BOOL bCTime ) : m_Time()
{
	this->Set_Full_Time( tvTime, bCTime );
}

EZ_SystemTime::EZ_SystemTime( __in const timeval* lpTime, __in C_BOOL bCTime )
{
	if ( !lpTime )
		this->Empty();
	else
		this->Set_Full_Time( *lpTime, bCTime );
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_SystemTime::EZ_SystemTime( const COleDateTime& oleTime ) : m_Time()
{
	*this = oleTime;
}

EZ_SystemTime::EZ_SystemTime( const COleDateTime* lpTime ) : m_Time()
{
	*this = lpTime;
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_SystemTime::EZ_SystemTime( const EZ_SystemTime& dtTime ) : m_Time()
{
	*this = dtTime;
}

EZ_SystemTime::EZ_SystemTime( const EZ_SystemTime* lpTime ) : m_Time()
{
	*this = lpTime;
}

//  ==========================================================================
//  
//  ==========================================================================
EZ_SystemTime::~EZ_SystemTime()
{
	//  this->m_Time
}

//  ==========================================================================
//  operator =
//  ==========================================================================
EZ_SystemTime& EZ_SystemTime::operator = ( LPCSTR lpTime )
{
	EZ_SystemTime::Get_Time( lpTime, this->m_Time );

	return *this;
}

EZ_SystemTime& EZ_SystemTime::operator = ( LPCWSTR lpTime )
{
	EZ_SystemTime::Get_Time( lpTime, this->m_Time );

	return *this;
}

EZ_SystemTime& EZ_SystemTime::operator = ( const CStringA& strTime )
{
	EZ_SystemTime::Get_Time( strTime, this->m_Time );

	return *this;
}

EZ_SystemTime& EZ_SystemTime::operator = ( const CStringW& strTime )
{
	EZ_SystemTime::Get_Time( strTime, this->m_Time );

	return *this;
}

//  ==========================================================================
//  operator =
//  ==========================================================================
EZ_SystemTime& EZ_SystemTime::operator = ( const SYSTEMTIME& stTime )
{
	if ( &this->m_Time != &stTime )
		::memcpy( &this->m_Time, &stTime, sizeof( SYSTEMTIME ) );

	return *this;
}

EZ_SystemTime& EZ_SystemTime::operator = ( const SYSTEMTIME* lpTime )
{
	if ( !lpTime )
		this->Empty();
	else
		*this = *lpTime;

	return *this;
}

//  ==========================================================================
//  operator =
//  ==========================================================================
EZ_SystemTime& EZ_SystemTime::operator = ( const struct tm& tmTime )
{
	{
		this->m_Time.wYear         = ( tmTime.tm_year + 1900 );
		this->m_Time.wMonth        = ( tmTime.tm_mon  + 1    );
		this->m_Time.wDayOfWeek    = tmTime.tm_wday;
		this->m_Time.wDay          = tmTime.tm_mday;
		this->m_Time.wHour         = tmTime.tm_hour;
		this->m_Time.wMinute       = tmTime.tm_min;
		this->m_Time.wSecond       = tmTime.tm_sec;
		this->m_Time.wMilliseconds = 0;
	}

	return *this;
}

EZ_SystemTime& EZ_SystemTime::operator = ( const struct tm* lpTime )
{
	if ( !lpTime )
		this->Empty();
	else
	{
		this->m_Time.wYear         = ( lpTime->tm_year + 1900 );
		this->m_Time.wMonth        = ( lpTime->tm_mon  + 1    );
		this->m_Time.wDayOfWeek    = lpTime->tm_wday;
		this->m_Time.wDay          = lpTime->tm_mday;
		this->m_Time.wHour         = lpTime->tm_hour;
		this->m_Time.wMinute       = lpTime->tm_min;
		this->m_Time.wSecond       = lpTime->tm_sec;
		this->m_Time.wMilliseconds = 0;
	}

	return *this;
}

//  ==========================================================================
//  operator =
//  ==========================================================================
EZ_SystemTime& EZ_SystemTime::operator = ( const COleDateTime& oleTime )
{
	{
		this->m_Time.wYear         = oleTime.GetYear();
		this->m_Time.wMonth        = oleTime.GetMonth();
		this->m_Time.wDayOfWeek    = oleTime.GetDayOfWeek();
		this->m_Time.wDay          = oleTime.GetDay();
		this->m_Time.wHour         = oleTime.GetHour();
		this->m_Time.wMinute       = oleTime.GetMinute();
		this->m_Time.wSecond       = oleTime.GetSecond();
		this->m_Time.wMilliseconds = 0;
	}

	return *this;
}

EZ_SystemTime& EZ_SystemTime::operator = ( const COleDateTime* lpTime )
{
	if ( !lpTime )
		this->Empty();
	else
	{
		this->m_Time.wYear         = lpTime->GetYear();
		this->m_Time.wMonth        = lpTime->GetMonth();
		this->m_Time.wDayOfWeek    = lpTime->GetDayOfWeek();
		this->m_Time.wDay          = lpTime->GetDay();
		this->m_Time.wHour         = lpTime->GetHour();
		this->m_Time.wMinute       = lpTime->GetMinute();
		this->m_Time.wSecond       = lpTime->GetSecond();
		this->m_Time.wMilliseconds = 0;
	}

	return *this;
}

//  ==========================================================================
//  operator =
//  ==========================================================================
EZ_SystemTime& EZ_SystemTime::operator = ( const EZ_SystemTime& dtTime )
{
	if ( this != &dtTime ) 
		this->m_Time = dtTime.m_Time;

	return *this;
}

EZ_SystemTime& EZ_SystemTime::operator = ( const EZ_SystemTime* lpTime )
{
	if ( !lpTime )
		this->Empty();
	else
		*this = *lpTime;

	return *this;
}

//  ==========================================================================
//  operator ==
//  ==========================================================================
C_BOOL EZ_SystemTime::operator == ( LPCSTR lpTime ) const
{
	if ( !lpTime ) return FALSE;

	CStringA strTmp = this->Time_To_StringA();

	return ( strTmp == lpTime );
}

C_BOOL EZ_SystemTime::operator == ( LPCWSTR lpTime ) const
{
	if ( !lpTime ) return FALSE;

	CStringW strTmp = this->Time_To_StringW();

	return ( strTmp == lpTime );
}

//  ==========================================================================
//  operator ==
//  ==========================================================================
C_BOOL EZ_SystemTime::operator == ( const CStringA& strTime ) const
{
	CStringA strTmp = this->Time_To_StringA();

	return ( strTmp == strTime );
}

C_BOOL EZ_SystemTime::operator == ( const CStringW& strTime ) const
{
	CStringW strTmp = this->Time_To_StringW();

	return ( strTmp == strTime );
}

//  ==========================================================================
//  operator ==
//  ==========================================================================
C_BOOL EZ_SystemTime::operator == ( const SYSTEMTIME& stTime ) const
{
	return ( ( this->m_Time.wYear         == stTime.wYear         ) && ( this->m_Time.wMonth  == stTime.wMonth  ) && 
			 ( this->m_Time.wDay          == stTime.wDay          ) && ( this->m_Time.wHour   == stTime.wHour   ) && 
			 ( this->m_Time.wMinute       == stTime.wMinute       ) && ( this->m_Time.wSecond == stTime.wSecond ) && 
			 ( this->m_Time.wMilliseconds == stTime.wMilliseconds ) );
}

C_BOOL EZ_SystemTime::operator == ( const EZ_SystemTime& dtTime ) const
{
	return ( ( this->m_Time.wYear         == dtTime.m_Time.wYear         ) && ( this->m_Time.wMonth  == dtTime.m_Time.wMonth  ) && 
			 ( this->m_Time.wDay          == dtTime.m_Time.wDay          ) && ( this->m_Time.wHour   == dtTime.m_Time.wHour   ) && 
			 ( this->m_Time.wMinute       == dtTime.m_Time.wMinute       ) && ( this->m_Time.wSecond == dtTime.m_Time.wSecond ) && 
			 ( this->m_Time.wMilliseconds == dtTime.m_Time.wMilliseconds ) );
}

//  ==========================================================================
//  operator !=
//  ==========================================================================
C_BOOL EZ_SystemTime::operator != ( LPCSTR lpTime ) const
{
	if ( !lpTime ) return FALSE;
	
	CStringA strTmp = this->Time_To_StringA();

	return ( strTmp != lpTime );
}

C_BOOL EZ_SystemTime::operator != ( LPCWSTR lpTime ) const
{
	if ( !lpTime ) return FALSE;
	
	CStringW strTmp = this->Time_To_StringW();

	return ( strTmp != lpTime );
}

//  ==========================================================================
//  operator !=
//  ==========================================================================
C_BOOL EZ_SystemTime::operator != ( const CStringA& strTime ) const
{
	CStringA strTmp = this->Time_To_StringA();

	return ( strTmp != strTime );
}

C_BOOL EZ_SystemTime::operator != ( const CStringW& strTime ) const
{
	CStringW strTmp = this->Time_To_StringW();

	return ( strTmp != strTime );
}

//  ==========================================================================
//  operator !=
//  ==========================================================================
C_BOOL EZ_SystemTime::operator != ( const SYSTEMTIME& stTime ) const
{
	return ( ( this->m_Time.wYear         != stTime.wYear         ) || ( this->m_Time.wMonth  != stTime.wMonth  ) || 
			 ( this->m_Time.wDay          != stTime.wDay          ) || ( this->m_Time.wHour   != stTime.wHour   ) || 
			 ( this->m_Time.wMinute       != stTime.wMinute       ) || ( this->m_Time.wSecond != stTime.wSecond ) || 
			 ( this->m_Time.wMilliseconds != stTime.wMilliseconds ) );
}

C_BOOL EZ_SystemTime::operator != ( const EZ_SystemTime& dtTime ) const
{
	return ( ( this->m_Time.wYear         != dtTime.m_Time.wYear         ) || ( this->m_Time.wMonth  != dtTime.m_Time.wMonth  ) ||
			 ( this->m_Time.wDay          != dtTime.m_Time.wDay          ) || ( this->m_Time.wHour   != dtTime.m_Time.wHour   ) ||
			 ( this->m_Time.wMinute       != dtTime.m_Time.wMinute       ) || ( this->m_Time.wSecond != dtTime.m_Time.wSecond ) ||
			 ( this->m_Time.wMilliseconds != dtTime.m_Time.wMilliseconds ) );
}

//  ==========================================================================
//  operator <
//  ==========================================================================
C_BOOL EZ_SystemTime::operator < ( LPCSTR lpTime ) const
{
	if ( !lpTime ) return FALSE;
	
	CStringA strTmp = this->Time_To_StringA();

	return ( strTmp < lpTime );
}

C_BOOL EZ_SystemTime::operator < ( LPCWSTR lpTime ) const
{
	if ( !lpTime ) return FALSE;
	
	CStringW strTmp = this->Time_To_StringW();

	return ( strTmp < lpTime );
}

//  ==========================================================================
//  operator <
//  ==========================================================================
C_BOOL EZ_SystemTime::operator < ( const CStringA& strTime ) const
{
	CStringA strTmp = this->Time_To_StringA();

	return ( strTmp < strTime );
}

C_BOOL EZ_SystemTime::operator < ( const CStringW& strTime ) const
{
	CStringW strTmp = this->Time_To_StringW();

	return ( strTmp < strTime );
}

//  ==========================================================================
//  operator <
//  ==========================================================================
C_BOOL EZ_SystemTime::operator < ( const SYSTEMTIME& stTime ) const
{
	if ( this->m_Time.wYear < stTime.wYear ) 
		return TRUE;
	else if ( this->m_Time.wYear > stTime.wYear )
		return FALSE;

	if ( this->m_Time.wMonth < stTime.wMonth ) 
		return TRUE;
	else if ( this->m_Time.wMonth > stTime.wMonth ) 
		return FALSE;

	if ( this->m_Time.wDay < stTime.wDay ) 
		return TRUE;
	else if ( this->m_Time.wDay > stTime.wDay ) 
		return FALSE;

	if ( this->m_Time.wHour < stTime.wHour ) 
		return TRUE;
	else if ( this->m_Time.wHour > stTime.wHour ) 
		return FALSE;

	if ( this->m_Time.wMinute < stTime.wMinute ) 
		return TRUE;
	else if ( this->m_Time.wMinute > stTime.wMinute ) 
		return FALSE;

	if ( this->m_Time.wSecond < stTime.wSecond ) 
		return TRUE;
	else if ( this->m_Time.wSecond > stTime.wSecond ) 
		return FALSE;

	if ( this->m_Time.wMilliseconds < stTime.wMilliseconds ) 
		return TRUE;

	return FALSE;
}

C_BOOL EZ_SystemTime::operator < ( const EZ_SystemTime& dtTime ) const
{
	return EZ_SystemTime::operator < ( dtTime.m_Time );
}

//  ==========================================================================
//  operator <=
//  ==========================================================================
C_BOOL EZ_SystemTime::operator <= ( LPCSTR lpTime ) const
{
	if ( !lpTime ) return FALSE;
	
	CStringA strTmp = this->Time_To_StringA();

	return ( strTmp <= lpTime );
}

C_BOOL EZ_SystemTime::operator <= ( LPCWSTR lpTime ) const
{
	if ( !lpTime ) return FALSE;
	
	CStringW strTmp = this->Time_To_StringW();

	return ( strTmp <= lpTime );
}

//  ==========================================================================
//  operator <=
//  ==========================================================================
C_BOOL EZ_SystemTime::operator <= ( const CStringA& strTime ) const
{
	CStringA strTmp = this->Time_To_StringA();

	return ( strTmp <= strTime );
}

C_BOOL EZ_SystemTime::operator <= ( const CStringW& strTime ) const
{
	CStringW strTmp = this->Time_To_StringW();

	return ( strTmp <= strTime );
}

//  ==========================================================================
//  operator <=
//  ==========================================================================
C_BOOL EZ_SystemTime::operator <= ( const SYSTEMTIME& stTime ) const
{
	if ( this->m_Time.wYear < stTime.wYear ) 
		return TRUE;
	else if ( this->m_Time.wYear > stTime.wYear )
		return FALSE;

	if ( this->m_Time.wMonth < stTime.wMonth ) 
		return TRUE;
	else if ( this->m_Time.wMonth > stTime.wMonth ) 
		return FALSE;

	if ( this->m_Time.wDay < stTime.wDay ) 
		return TRUE;
	else if ( this->m_Time.wDay > stTime.wDay ) 
		return FALSE;

	if ( this->m_Time.wHour < stTime.wHour ) 
		return TRUE;
	else if ( this->m_Time.wHour > stTime.wHour ) 
		return FALSE;

	if ( this->m_Time.wMinute < stTime.wMinute ) 
		return TRUE;
	else if ( this->m_Time.wMinute > stTime.wMinute ) 
		return FALSE;

	if ( this->m_Time.wSecond < stTime.wSecond ) 
		return TRUE;
	else if ( this->m_Time.wSecond > stTime.wSecond ) 
		return FALSE;

	if ( this->m_Time.wMilliseconds <= stTime.wMilliseconds ) 
		return TRUE;

	return FALSE;
}

C_BOOL EZ_SystemTime::operator <= ( const EZ_SystemTime& dtTime ) const
{
	return EZ_SystemTime::operator <= ( dtTime.m_Time );
}

//  ==========================================================================
//  operator >
//  ==========================================================================
C_BOOL EZ_SystemTime::operator > ( LPCSTR lpTime ) const
{
	if ( !lpTime ) return FALSE;
	
	CStringA strTmp = this->Time_To_StringA();

	return ( strTmp > lpTime );
}

C_BOOL EZ_SystemTime::operator > ( LPCWSTR lpTime ) const
{
	if ( !lpTime ) return FALSE;
	
	CStringW strTmp = this->Time_To_StringW();

	return ( strTmp > lpTime );
}

//  ==========================================================================
//  operator >
//  ==========================================================================
C_BOOL EZ_SystemTime::operator > ( const CStringA& strTime ) const
{
	CStringA strTmp = this->Time_To_StringA();

	return ( strTmp > strTime );
}

C_BOOL EZ_SystemTime::operator > ( const CStringW& strTime ) const
{
	CStringW strTmp = this->Time_To_StringW();

	return ( strTmp > strTime );
}

//  ==========================================================================
//  operator >
//  ==========================================================================
C_BOOL EZ_SystemTime::operator > ( const SYSTEMTIME& stTime ) const
{
	if ( this->m_Time.wYear > stTime.wYear ) 
		return TRUE;
	else if ( this->m_Time.wYear < stTime.wYear )
		return FALSE;

	if ( this->m_Time.wMonth > stTime.wMonth ) 
		return TRUE;
	else if ( this->m_Time.wMonth < stTime.wMonth ) 
		return FALSE;

	if ( this->m_Time.wDay > stTime.wDay ) 
		return TRUE;
	else if ( this->m_Time.wDay < stTime.wDay ) 
		return FALSE;

	if ( this->m_Time.wHour > stTime.wHour ) 
		return TRUE;
	else if ( this->m_Time.wHour < stTime.wHour ) 
		return FALSE;

	if ( this->m_Time.wMinute > stTime.wMinute ) 
		return TRUE;
	else if ( this->m_Time.wMinute < stTime.wMinute ) 
		return FALSE;

	if ( this->m_Time.wSecond > stTime.wSecond ) 
		return TRUE;
	else if ( this->m_Time.wSecond < stTime.wSecond ) 
		return FALSE;

	if ( this->m_Time.wMilliseconds > stTime.wMilliseconds ) 
		return TRUE;

	return FALSE;
}

C_BOOL EZ_SystemTime::operator > ( const EZ_SystemTime& dtTime ) const
{
	return EZ_SystemTime::operator > ( dtTime.m_Time );
}

//  ==========================================================================
//  operator >=
//  ==========================================================================
C_BOOL EZ_SystemTime::operator >= ( LPCSTR lpTime ) const
{
	if ( !lpTime ) return FALSE;
	
	CStringA strTmp = this->Time_To_StringA();

	return ( strTmp >= lpTime );
}

C_BOOL EZ_SystemTime::operator >= ( LPCWSTR lpTime ) const
{
	if ( !lpTime ) return FALSE;
	
	CStringW strTmp = this->Time_To_StringW();

	return ( strTmp >= lpTime );
}

//  ==========================================================================
//  operator >=
//  ==========================================================================
C_BOOL EZ_SystemTime::operator >= ( const CStringA& strTime ) const
{
	CStringA strTmp = this->Time_To_StringA();

	return ( strTmp >= strTime );
}

C_BOOL EZ_SystemTime::operator >= ( const CStringW& strTime ) const
{
	CStringW strTmp = this->Time_To_StringW();

	return ( strTmp >= strTime );
}

//  ==========================================================================
//  operator >=
//  ==========================================================================
C_BOOL EZ_SystemTime::operator >= ( const SYSTEMTIME& stTime ) const
{
	if ( this->m_Time.wYear > stTime.wYear ) 
		return TRUE;
	else if ( this->m_Time.wYear < stTime.wYear )
		return FALSE;

	if ( this->m_Time.wMonth > stTime.wMonth ) 
		return TRUE;
	else if ( this->m_Time.wMonth < stTime.wMonth ) 
		return FALSE;

	if ( this->m_Time.wDay > stTime.wDay ) 
		return TRUE;
	else if ( this->m_Time.wDay < stTime.wDay ) 
		return FALSE;

	if ( this->m_Time.wHour > stTime.wHour ) 
		return TRUE;
	else if ( this->m_Time.wHour < stTime.wHour ) 
		return FALSE;

	if ( this->m_Time.wMinute > stTime.wMinute ) 
		return TRUE;
	else if ( this->m_Time.wMinute < stTime.wMinute ) 
		return FALSE;

	if ( this->m_Time.wSecond > stTime.wSecond ) 
		return TRUE;
	else if ( this->m_Time.wSecond < stTime.wSecond ) 
		return FALSE;

	if ( this->m_Time.wMilliseconds >= stTime.wMilliseconds ) 
		return TRUE;

	return FALSE;
}

C_BOOL EZ_SystemTime::operator >= ( const EZ_SystemTime& dtTime ) const
{
	return EZ_SystemTime::operator >= ( dtTime.m_Time );
}

//  ==========================================================================
//  operator -
//  ==========================================================================
C_INT EZ_SystemTime::operator - ( const CStringA& strTime ) const
{
	return ( C_INT )this->Subtract( strTime );
}

C_INT EZ_SystemTime::operator - ( const CStringW& strTime ) const
{
	return ( C_INT )this->Subtract( strTime );
}

C_INT EZ_SystemTime::operator - ( const SYSTEMTIME& stTime ) const
{	
	return ( C_INT )this->Subtract( stTime );
}

C_INT EZ_SystemTime::operator - ( const COleDateTime& oleTime ) const
{
	return ( C_INT )this->Subtract( oleTime );
}

C_INT EZ_SystemTime::operator - ( const EZ_SystemTime& dtTime ) const
{	
	return ( C_INT )this->Subtract( dtTime );
}

//  ==========================================================================
//  Set_Date
//  ==========================================================================
void EZ_SystemTime::Set_Date( C_INT iDate )
{
	CString strDate = _T( "" );

	strDate.Format( _T( "%08d" ), iDate );

	this->Set_Date( strDate );
}

void EZ_SystemTime::Set_Date( C_INT iYear, C_INT iMonth, C_INT iDay )
{
	this->m_Time.wYear      = iYear;
	this->m_Time.wMonth     = iMonth;
	this->m_Time.wDayOfWeek = 0;
	this->m_Time.wDay       = iDay;
}

void EZ_SystemTime::Set_Date( const SYSTEMTIME& stTime )
{
	this->m_Time.wYear      = stTime.wYear;
	this->m_Time.wMonth     = stTime.wMonth;
	this->m_Time.wDayOfWeek = 0;
	this->m_Time.wDay       = stTime.wDay;
}

void EZ_SystemTime::Set_Date( const EZ_SystemTime& dtTime )
{
	this->m_Time.wYear      = dtTime.m_Time.wYear;
	this->m_Time.wMonth     = dtTime.m_Time.wMonth;
	this->m_Time.wDayOfWeek = 0;
	this->m_Time.wDay       = dtTime.m_Time.wDay;
}

void EZ_SystemTime::Set_Date( const CStringA& strDate, C_BOOL bHasDash )
{
	this->m_Time.wYear      = ::atoi( strDate.Left( 4 ) );
	this->m_Time.wDayOfWeek = 0;

	if ( !bHasDash )
	{	//  ⊿Τ '/'
		this->m_Time.wMonth = ::atoi( strDate.Mid( 4, 2 ) );
		this->m_Time.wDay   = ::atoi( strDate.Mid( 6, 2 ) );
	}
	else  
	{	//  Τ '/'	
		this->m_Time.wMonth = ::atoi( strDate.Mid( 5, 2 ) );
		this->m_Time.wDay   = ::atoi( strDate.Mid( 8, 2 ) );
	}
}

void EZ_SystemTime::Set_Date( const CStringW& strDate, C_BOOL bHasDash )
{
	this->m_Time.wYear      = ::_wtoi( strDate.Left( 4 ) );
	this->m_Time.wDayOfWeek = 0;

	if ( !bHasDash )
	{	//  ⊿Τ '/'
		this->m_Time.wMonth = ::_wtoi( strDate.Mid( 4, 2 ) );
		this->m_Time.wDay   = ::_wtoi( strDate.Mid( 6, 2 ) );
	}
	else  
	{	//  Τ '/'	
		this->m_Time.wMonth = ::_wtoi( strDate.Mid( 5, 2 ) );
		this->m_Time.wDay   = ::_wtoi( strDate.Mid( 8, 2 ) );
	}
}

//  ==========================================================================
//  Get_Date
//  ==========================================================================
C_UINT EZ_SystemTime::Get_Date() const
{
	return EZ_SystemTime::Get_Date( this->m_Time );
}

void EZ_SystemTime::Get_Date( INT& iYear, INT& iMonth, INT& iDay ) const
{
	iYear  = this->m_Time.wYear;
	iMonth = this->m_Time.wMonth;
	iDay   = this->m_Time.wDay;
}

void EZ_SystemTime::Get_Date( SYSTEMTIME& stTime ) const
{
	stTime.wYear      = this->m_Time.wYear;
	stTime.wMonth     = this->m_Time.wMonth;
	stTime.wDayOfWeek = this->m_Time.wDayOfWeek;
	stTime.wDay       = this->m_Time.wDay;
}

void EZ_SystemTime::Get_Date( EZ_SystemTime& dtTime ) const
{
	dtTime.m_Time.wYear      = this->m_Time.wYear;
	dtTime.m_Time.wMonth     = this->m_Time.wMonth;
	dtTime.m_Time.wDayOfWeek = this->m_Time.wDayOfWeek;
	dtTime.m_Time.wDay       = this->m_Time.wDay;
}

void EZ_SystemTime::Get_Date( CStringA& strDate, C_BOOL bSlash ) const
{
	EZ_SystemTime::Get_String( &this->m_Time, strDate, ( bSlash ? EZ_SystemTime::FORMAT_DATE_STANDARD : EZ_SystemTime::FORMAT_DATE_STRING ) );
}

void EZ_SystemTime::Get_Date( CStringW& strDate, C_BOOL bSlash ) const
{
	EZ_SystemTime::Get_String( &this->m_Time, strDate, ( bSlash ? EZ_SystemTime::FORMAT_DATE_STANDARD : EZ_SystemTime::FORMAT_DATE_STRING ) );
}

//  ==========================================================================
//  Set_Time
//  ==========================================================================
void EZ_SystemTime::Set_Time( C_UINT iTime )
{
	CString strTime = _T( "" );

	strTime.Format( _T( "%09d" ), iTime );

	this->Set_Time( strTime );
}

void EZ_SystemTime::Set_Time( C_INT iHour, C_INT iMiniute, C_INT iSecond, C_INT iMSec )
{
	this->m_Time.wHour         = iHour;
	this->m_Time.wMinute       = iMiniute;
	this->m_Time.wSecond       = iSecond;
	this->m_Time.wMilliseconds = iMSec;
}

void EZ_SystemTime::Set_Time( const SYSTEMTIME& stTime )
{
	this->m_Time.wHour         = stTime.wHour;
	this->m_Time.wMinute       = stTime.wMinute;
	this->m_Time.wSecond       = stTime.wSecond;
	this->m_Time.wMilliseconds = stTime.wMilliseconds;
}

void EZ_SystemTime::Set_Time( const EZ_SystemTime& dtTime )
{
	this->m_Time.wHour         = dtTime.m_Time.wHour;
	this->m_Time.wMinute       = dtTime.m_Time.wMinute;
	this->m_Time.wSecond       = dtTime.m_Time.wSecond;
	this->m_Time.wMilliseconds = dtTime.m_Time.wMilliseconds;
}

void EZ_SystemTime::Set_Time( const CStringA& strTime )
{
	this->m_Time.wHour         = ::atoi( strTime.Left( 2 ) );
	this->m_Time.wMinute       = ::atoi( strTime.Mid( 2, 2 ) );
	this->m_Time.wSecond       = ::atoi( strTime.Mid( 4, 2 ) );
	this->m_Time.wMilliseconds = ::atoi( strTime.Mid( 6, 3 ) );
}

void EZ_SystemTime::Set_Time( const CStringW& strTime )
{
	this->m_Time.wHour         = ::_wtoi( strTime.Left( 2 ) );
	this->m_Time.wMinute       = ::_wtoi( strTime.Mid( 2, 2 ) );
	this->m_Time.wSecond       = ::_wtoi( strTime.Mid( 4, 2 ) );
	this->m_Time.wMilliseconds = ::_wtoi( strTime.Mid( 6, 3 ) );
}

//  ==========================================================================
//  Get_Time
//  ==========================================================================
C_UINT EZ_SystemTime::Get_Time() const
{
	return ( ( this->m_Time.wHour * 10000000 ) + ( this->m_Time.wMinute * 100000 ) + ( this->m_Time.wSecond * 1000 ) + ( this->m_Time.wMilliseconds ) );
}

void EZ_SystemTime::Get_Time( INT& iHour, INT& iMiniute, INT& iSecond, INT& iMSec ) const
{
	iHour    = this->m_Time.wHour;
	iMiniute = this->m_Time.wMinute;
	iSecond  = this->m_Time.wSecond;
	iMSec    = this->m_Time.wMilliseconds;
}

void EZ_SystemTime::Get_Time( SYSTEMTIME& stTime ) const
{
	stTime.wHour         = this->m_Time.wHour;
	stTime.wMinute       = this->m_Time.wMinute;
	stTime.wSecond       = this->m_Time.wSecond;
	stTime.wMilliseconds = this->m_Time.wMilliseconds;
}

void EZ_SystemTime::Get_Time( EZ_SystemTime& dtTime ) const
{
	dtTime.m_Time.wHour         = this->m_Time.wHour;
	dtTime.m_Time.wMinute       = this->m_Time.wMinute;
	dtTime.m_Time.wSecond       = this->m_Time.wSecond;
	dtTime.m_Time.wMilliseconds = this->m_Time.wMilliseconds;
}

void EZ_SystemTime::Get_Time( CStringA& strTime ) const
{
	EZ_SystemTime::Get_String( &this->m_Time, strTime, EZ_SystemTime::FORMAT_TIME_STRING );
}

void EZ_SystemTime::Get_Time( CStringW& strTime ) const
{
	EZ_SystemTime::Get_String( &this->m_Time, strTime, EZ_SystemTime::FORMAT_TIME_STRING );
}

//  ==========================================================================
//  ぱ
//  ==========================================================================
void EZ_SystemTime::Add_Day( C_INT iValue )
{
	//  獶猭把计 ..
	if ( iValue < 0 ) 
	{
		this->Sub_Day( -iValue );
		return;
	}

	//  Total-Second = Day * 24h * 60m * 60s
	C_INT iMSec = this->m_Time.wMilliseconds;

	try
	{
		COleDateTime oleDateTime( this->m_Time );
	
		oleDateTime                += COleDateTimeSpan( iValue, 0, 0, 0 );
		*this                       = oleDateTime;
		this->m_Time.wMilliseconds  = iMSec;
	}
	catch ( ... )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Add_Day - Error !" ) );
	}
}

//  ==========================================================================
//  
//  ==========================================================================
void EZ_SystemTime::Add_Hour( C_INT iValue )
{
	//  獶猭把计 ..
	if ( iValue < 0 ) 
	{
		this->Sub_Hour( -iValue );
		return;
	}
	
	//  Total-Second = Hour * 60m * 60s
	C_INT iMSec = this->m_Time.wMilliseconds;

	try
	{
		COleDateTime oleDateTime( this->m_Time );

		oleDateTime                += COleDateTimeSpan( 0, iValue, 0, 0 );
		*this                       = oleDateTime;
		this->m_Time.wMilliseconds  = iMSec;
	}
	catch ( ... )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Add_Hour - Error !" ) );
	}
}

//  ==========================================================================
//  だ
//  ==========================================================================
void EZ_SystemTime::Add_Minute( C_INT iValue )
{
	//  獶猭把计 ..
	if ( iValue < 0 ) 
	{
		this->Sub_Minute( -iValue );
		return;
	}
	
	//  Total-Second = Minute * 60s
	C_INT iMSec = this->m_Time.wMilliseconds;

	try
	{
		COleDateTime oleDateTime( this->m_Time );

		oleDateTime                += COleDateTimeSpan( 0, 0, iValue, 0 );
		*this                       = oleDateTime;
		this->m_Time.wMilliseconds  = iMSec;
	}
	catch ( ... )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Add_Minute - Error !" ) );
	}
}

//  ==========================================================================
//  
//  ==========================================================================
void EZ_SystemTime::Add_Second( C_INT iValue )
{
	//  獶猭把计 ..
	if ( iValue < 0 ) 
	{
		this->Sub_Second( -iValue );
		return;
	}

	//  Total-Second = Second
	C_INT iMSec = this->m_Time.wMilliseconds;

	try
	{
		COleDateTime oleDateTime( this->m_Time );

		oleDateTime                += COleDateTimeSpan( 0, 0, 0, iValue );
		*this                       = oleDateTime;
		this->m_Time.wMilliseconds  = iMSec;
	}
	catch ( ... )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Add_Second - Error !" ) );
	}
}

//  ==========================================================================
//  睝
//  ==========================================================================
void EZ_SystemTime::Add_MSecond( INT iValue )
{
	//  獶猭把计 ..
	if ( iValue < 0 ) 
	{
		this->Sub_MSecond( -iValue );
		return;
	}

	//  
	iValue += this->m_Time.wMilliseconds;

	if ( iValue < 1000 )
		this->m_Time.wMilliseconds = ( WORD )iValue;
	else
	{
		this->m_Time.wMilliseconds = ( WORD )( iValue % 1000 );

		this->Add_Second( ( iValue / 1000 ) );
	}
}

void EZ_SystemTime::Add_Int64_MSecond( INT64 iValue )
{
	//  獶猭把计 ..
	if ( iValue < 0 ) 
	{
		//this->Sub_MSecond( -Value );
		return;
	}

	//  
	iValue += this->m_Time.wMilliseconds;

	if ( iValue < 1000 )
		this->m_Time.wMilliseconds = ( WORD )iValue;
	else
	{
		this->m_Time.wMilliseconds = ( WORD )( iValue % 1000 );

		this->Add_Second( ( C_INT )( iValue / 1000 ) );
	}
}

void EZ_SystemTime::Add_UInt64_MSecond( UINT64 iValue )
{
	iValue += this->m_Time.wMilliseconds;

	if ( iValue < 1000 )
		this->m_Time.wMilliseconds = ( WORD )iValue;
	else
	{
		this->m_Time.wMilliseconds = ( WORD )( iValue % 1000 );

		this->Add_Second( ( C_INT )( iValue / 1000 ) );
	}
}

//  ==========================================================================
//  琿丁
//  ==========================================================================
void EZ_SystemTime::Add( C_INT iAddHour, C_INT iAddMin, C_INT iAddSec, C_INT iAddMSec )
{
	//  Add Some Time
	if ( ( iAddHour > 0 ) || ( iAddMin > 0 ) || ( iAddSec > 0 ) )
	{
		C_INT iMSec = this->m_Time.wMilliseconds;

		try
		{
			COleDateTime oleDateTime( this->m_Time );

			oleDateTime                += COleDateTimeSpan( 0, iAddHour, iAddMin, iAddSec );
			*this                       = oleDateTime;
			this->m_Time.wMilliseconds  = iMSec;
		}
		catch ( ... )
		{
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Add - Error !" ) );
			return;
		}
	}

	//  Add MS
	if ( iAddMSec > 0 ) this->Add_MSecond( iAddMSec );
}

//  ==========================================================================
//  搭ぱ
//  ==========================================================================
void EZ_SystemTime::Sub_Day( C_INT iValue )
{
	//  獶猭把计 ..
	if ( iValue < 0 )
	{
		this->Add_Day( -iValue );
		return;
	}
	
	//  Total-Second = Day * 24h * 60m * 60s
	C_INT iMSec = this->m_Time.wMilliseconds;

	try
	{
		COleDateTime oleDateTime( this->m_Time );

		oleDateTime                -= COleDateTimeSpan( iValue, 0, 0, 0 );
		*this                       = oleDateTime;
		this->m_Time.wMilliseconds  = iMSec;
	}
	catch ( ... )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Sub_Day - Error !" ) );
	}
}

//  ==========================================================================
//  搭
//  ==========================================================================
void EZ_SystemTime::Sub_Hour( C_INT iValue )
{
	//  獶猭把计 ..
	if ( iValue < 0 )
	{
		this->Add_Hour( -iValue );
		return;
	}

	//  花ì镑 ..
	if ( this->m_Time.wHour >= iValue )
	{
		this->m_Time.wHour -= iValue;
		return;
	}

	//  Total-Second = Hour * 60m * 60s
	C_INT iMSec = this->m_Time.wMilliseconds;

	try
	{
		COleDateTime oleDateTime( this->m_Time );

		oleDateTime                -= COleDateTimeSpan( 0, iValue, 0, 0 );
		*this                       = oleDateTime;
		this->m_Time.wMilliseconds  = iMSec;
	}
	catch ( ... )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Sub_Hour - Error !" ) );
	}
}

//  ==========================================================================
//  搭だ
//  ==========================================================================
void EZ_SystemTime::Sub_Minute( C_INT iValue )
{
	//  獶猭把计 ..
	if ( iValue < 0 )
	{
		this->Add_Minute( -iValue );
		return;
	}

	//  花ì镑 ..
	if ( this->m_Time.wMinute >= iValue )
	{
		this->m_Time.wMinute -= iValue;
		return;
	}

	//  Total-Second = Minute * 60s
	C_INT iMSec = this->m_Time.wMilliseconds;

	try
	{
		COleDateTime oleDateTime( this->m_Time );

		oleDateTime                -= COleDateTimeSpan( 0, 0, iValue, 0 );
		*this                       = oleDateTime;
		this->m_Time.wMilliseconds  = iMSec;
	}
	catch ( ... )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Sub_Minute - Error !" ) );
	}
}

//  ==========================================================================
//  搭
//  ==========================================================================
void EZ_SystemTime::Sub_Second( C_INT iValue )
{
	//  獶猭把计 ..
	if ( iValue < 0 )
	{
		this->Add_Second( -iValue );
		return;
	}

	//  花ì镑 ..
	if ( this->m_Time.wSecond >= iValue )
	{
		this->m_Time.wSecond -= iValue;
		return;
	}

	//  Total-Second = Second
	C_INT iMSec = this->m_Time.wMilliseconds;

	try
	{
		COleDateTime oleDateTime( this->m_Time );

		oleDateTime                -= COleDateTimeSpan( 0, 0, 0, iValue );
		*this                       = oleDateTime;
		this->m_Time.wMilliseconds  = iMSec;
	}
	catch ( ... )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Sub_Second - Error !" ) );
	}
}

//  ==========================================================================
//  搭睝 ..
//  ==========================================================================
void EZ_SystemTime::Sub_MSecond( C_INT iValue )
{
	//  獶猭把计 ..
	if ( iValue < 0 )
	{
		this->Add_MSecond( -iValue );
		return;
	}
	
	//  花ì镑 ..
	if ( this->m_Time.wMilliseconds >= iValue )
	{
		this->m_Time.wMilliseconds -= iValue;
		return;
	}

	//  畉ず钡搭ぃ璶ノ埃猭蛤猭 ..
	if ( iValue <= 1000 )
	{   
		this->Sub_Second( 1 );

		this->m_Time.wMilliseconds += ( 1000 - iValue );

		return;
	}

	//  ㄢ花ゑ ..
	C_UINT uiMSec = ( iValue % 1000 );

	if ( uiMSec <= this->m_Time.wMilliseconds )
	{
		this->Sub_Second( ( iValue / 1000 ) );

		this->m_Time.wMilliseconds -= uiMSec;
	}
	else
	{
		this->m_Time.wMilliseconds += ( 1000 - uiMSec );

		this->Sub_Second( ( ( iValue / 1000 ) + 1 ) );
	}
}

void EZ_SystemTime::Sub_Int64_MSecond( C_INT64& iValue )
{
	//  獶猭把计 ..
	if ( iValue < 0 )
	{
		//this->Add_MSecond( -iValue );
		return;
	}
	
	//  花ì镑 ..
	if ( ( C_INT64 )this->m_Time.wMilliseconds >= iValue )
	{
		this->m_Time.wMilliseconds -= ( WORD )iValue;
		return;
	}

	//  畉ず钡搭ぃ璶ノ埃猭蛤猭 ..
	if ( iValue <= 1000 )
	{   
		this->Sub_Second( 1 );

		this->m_Time.wMilliseconds += ( WORD )( 1000 - iValue );

		return;
	}

	//  ㄢ花ゑ ..
	C_UINT uiMSec = ( C_UINT )( iValue % 1000 );

	if ( uiMSec <= this->m_Time.wMilliseconds )
	{
		this->Sub_Second( ( C_INT )( iValue / 1000 ) );

		this->m_Time.wMilliseconds -= uiMSec;
	}
	else
	{
		this->m_Time.wMilliseconds += ( 1000 - uiMSec );

		this->Sub_Second( ( ( C_INT )( iValue / 1000 ) + 1 ) );
	}
}

void EZ_SystemTime::Sub_UInt64_MSecond( C_UINT64& iValue )
{
	//  花ì镑 ..
	if ( ( C_UINT64 )this->m_Time.wMilliseconds >= iValue )
	{
		this->m_Time.wMilliseconds -= ( WORD )iValue;
		return;
	}

	//  畉ず钡搭ぃ璶ノ埃猭蛤猭 ..
	if ( iValue <= 1000 )
	{   
		this->Sub_Second( 1 );

		this->m_Time.wMilliseconds += ( 1000 - ( WORD )iValue );

		return;
	}

	//  ㄢ花ゑ ..
	C_UINT uiMSec = ( C_UINT )( iValue % 1000 );

	if ( uiMSec <= this->m_Time.wMilliseconds )
	{
		this->Sub_Second( ( C_INT )( iValue / 1000 ) );

		this->m_Time.wMilliseconds -= ( WORD )uiMSec;
	}
	else
	{
		this->m_Time.wMilliseconds += ( WORD )( 1000 - uiMSec );

		this->Sub_Second( ( C_INT )( ( iValue / 1000 ) + 1 ) );
	}
}

//  ==========================================================================
//  搭琘琿丁
//  ==========================================================================
void EZ_SystemTime::Sub( C_INT iSubHour, C_INT iSubMin, C_INT iSubSec, C_INT iSubMSec )
{
	//  Add Some Time
	if ( ( iSubHour > 0 ) || ( iSubMin > 0 ) || ( iSubSec > 0 ) )
	{
		C_INT iMSec = this->m_Time.wMilliseconds;

		try
		{
			COleDateTime ctNowTime( this->m_Time );

			ctNowTime                  -= COleDateTimeSpan( 0, iSubHour, iSubMin, iSubSec );
			*this                       = ctNowTime;
			this->m_Time.wMilliseconds  = iMSec;
		}
		catch ( ... )
		{
			::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Sub - Error !" ) );
			return;
		}
	}

	//  Add MS
	if ( iSubMSec > 0 ) this->Sub_MSecond( iSubMSec );
}

//  ==========================================================================
//  Subtract
//  ==========================================================================
void EZ_SystemTime::Subtract( const SYSTEMTIME& stTime, COleDateTimeSpan& oleDTSpan ) const
{
	try
	{
		COleDateTime oleDateTime1 = this->m_Time;
		COleDateTime oleDateTime2 = stTime;

		oleDTSpan = ( oleDateTime1 - oleDateTime2 );
	}
	catch ( ... )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Subtract - Error !" ) );
	}
}

void EZ_SystemTime::Subtract( const EZ_SystemTime& dtTime, COleDateTimeSpan& oleDTSpan ) const
{
	this->Subtract( dtTime.m_Time, oleDTSpan );
}

void EZ_SystemTime::Subtract( const CStringA& strTime, COleDateTimeSpan& oleDTSpan ) const
{
	EZ_SystemTime dtTime = strTime;

	this->Subtract( dtTime.m_Time, oleDTSpan );
}

void EZ_SystemTime::Subtract( const CStringW& strTime, COleDateTimeSpan& oleDTSpan ) const
{
	EZ_SystemTime dtTime = strTime;

	this->Subtract( dtTime.m_Time, oleDTSpan );
}

//  ==========================================================================
//  Subtract ( Return Value : Total MilliSeconds )
//  ==========================================================================
LONGLONG EZ_SystemTime::Subtract( const SYSTEMTIME& stTime ) const
{
	LONGLONG llTotalMSec( 0 );

	EZ_SystemTime::GetMilliSeconds( stTime, this->m_Time, llTotalMSec );

	return llTotalMSec;
}

LONGLONG EZ_SystemTime::Subtract( const EZ_SystemTime& dtTime ) const
{
	return EZ_SystemTime::Subtract( dtTime.m_Time );
}

LONGLONG EZ_SystemTime::Subtract( const CStringA& strTime ) const
{ 
	EZ_SystemTime dtTime = strTime;

	return EZ_SystemTime::Subtract( dtTime.m_Time );
}

LONGLONG EZ_SystemTime::Subtract( const CStringW& strTime ) const
{ 
	EZ_SystemTime dtTime = strTime;

	return EZ_SystemTime::Subtract( dtTime.m_Time );
}

//  ==========================================================================
//  ら戳琌
//  ==========================================================================
C_BOOL EZ_SystemTime::Is_Equal_Date( C_INT iDate ) const
{
	C_INT iTmpDate = this->Get_Date();

	return ( iTmpDate == iDate );
}

C_BOOL EZ_SystemTime::Is_Equal_Date( const EZ_DATE& stDate ) const
{
	return ( ( this->m_Time.wYear  == stDate.m_Year  ) && 
		     ( this->m_Time.wMonth == stDate.m_Month ) && 
		     ( this->m_Time.wDay   == stDate.m_Day   ) );
}

C_BOOL EZ_SystemTime::Is_Equal_Date( const SYSTEMTIME& stDate ) const
{
	return ( ( this->m_Time.wYear  == stDate.wYear  ) && 
		     ( this->m_Time.wMonth == stDate.wMonth ) && 
		     ( this->m_Time.wDay   == stDate.wDay   ) );
}

C_BOOL EZ_SystemTime::Is_Equal_Date( const EZ_SystemTime& dtDate ) const
{
	return ( ( this->m_Time.wYear  == dtDate.m_Time.wYear  ) && 
		     ( this->m_Time.wMonth == dtDate.m_Time.wMonth ) && 
		     ( this->m_Time.wDay   == dtDate.m_Time.wDay   ) );
}

C_BOOL EZ_SystemTime::Is_Equal_Date( const CStringA& strDate ) const
{
	return ( ( this->m_Time.wYear  == ( WORD )::atoi( strDate.Left( 4 )   ) ) && 
			 ( this->m_Time.wMonth == ( WORD )::atoi( strDate.Mid( 4, 2 ) ) ) && 
			 ( this->m_Time.wDay   == ( WORD )::atoi( strDate.Mid( 6, 2 ) ) ) );
}

C_BOOL EZ_SystemTime::Is_Equal_Date( const CStringW& strDate ) const
{
	return ( ( this->m_Time.wYear  == ( WORD )::_wtoi( strDate.Left( 4 )   ) ) && 
			 ( this->m_Time.wMonth == ( WORD )::_wtoi( strDate.Mid( 4, 2 ) ) ) && 
			 ( this->m_Time.wDay   == ( WORD )::_wtoi( strDate.Mid( 6, 2 ) ) ) );
}

//  ==========================================================================
//  丁琌
//  ==========================================================================
C_BOOL EZ_SystemTime::Is_Equal_Time( const SYSTEMTIME& stTime ) const
{
	return ( ( this->m_Time.wHour         == stTime.wHour         ) && 
		     ( this->m_Time.wMinute       == stTime.wMinute       ) && 
		     ( this->m_Time.wSecond       == stTime.wSecond       ) &&
	         ( this->m_Time.wMilliseconds == stTime.wMilliseconds ) );
}

C_BOOL EZ_SystemTime::Is_Equal_Time( const EZ_TIME& stTime ) const
{
	return ( ( this->m_Time.wHour   == stTime.m_Hour   ) && 
		     ( this->m_Time.wMinute == stTime.m_Minute ) && 
		     ( this->m_Time.wSecond == stTime.m_Second ) );
}

C_BOOL EZ_SystemTime::Is_Equal_Time( const EZ_SystemTime& dtTime ) const
{
	return ( ( this->m_Time.wHour         == dtTime.m_Time.wHour         ) && 
		     ( this->m_Time.wMinute       == dtTime.m_Time.wMinute       ) && 
		     ( this->m_Time.wSecond       == dtTime.m_Time.wSecond       ) &&
	         ( this->m_Time.wMilliseconds == dtTime.m_Time.wMilliseconds ) );
}

C_BOOL EZ_SystemTime::Is_Equal_Time( const CStringA& strTime ) const
{
	return ( ( this->m_Time.wHour         == ( WORD )::atoi( strTime.Left( 2 )   ) ) && 
		     ( this->m_Time.wMinute       == ( WORD )::atoi( strTime.Mid( 2, 2 ) ) ) && 
		     ( this->m_Time.wSecond       == ( WORD )::atoi( strTime.Mid( 4, 2 ) ) ) &&
	         ( this->m_Time.wMilliseconds == ( WORD )::atoi( strTime.Mid( 6, 3 ) ) ) );
}

C_BOOL EZ_SystemTime::Is_Equal_Time( const CStringW& strTime ) const
{
	return ( ( this->m_Time.wHour         == ( WORD )::_wtoi( strTime.Left( 2 )   ) ) && 
		     ( this->m_Time.wMinute       == ( WORD )::_wtoi( strTime.Mid( 2, 2 ) ) ) && 
		     ( this->m_Time.wSecond       == ( WORD )::_wtoi( strTime.Mid( 4, 2 ) ) ) &&
	         ( this->m_Time.wMilliseconds == ( WORD )::_wtoi( strTime.Mid( 6, 3 ) ) ) );
}

//  ==========================================================================
//  丁琌, ┛菠 MSec
//  ==========================================================================
C_BOOL EZ_SystemTime::Is_Equal_Time_NoMSec( const SYSTEMTIME& stTime ) const
{
	return ( ( this->m_Time.wHour   == stTime.wHour   ) && 
		     ( this->m_Time.wMinute == stTime.wMinute ) && 
		     ( this->m_Time.wSecond == stTime.wSecond ) );
}

C_BOOL EZ_SystemTime::Is_Equal_Time_NoMSec( const EZ_SystemTime& dtTime ) const
{
	return ( ( this->m_Time.wHour   == dtTime.m_Time.wHour   ) && 
		     ( this->m_Time.wMinute == dtTime.m_Time.wMinute ) && 
		     ( this->m_Time.wSecond == dtTime.m_Time.wSecond ) );
}

C_BOOL EZ_SystemTime::Is_Equal_Time_NoMSec( const CStringA& strTime ) const
{
	return ( ( this->m_Time.wHour   == ( WORD )::atoi( strTime.Left( 2 )   ) ) && 
		     ( this->m_Time.wMinute == ( WORD )::atoi( strTime.Mid( 2, 2 ) ) ) && 
		     ( this->m_Time.wSecond == ( WORD )::atoi( strTime.Mid( 4, 2 ) ) ) );
}

C_BOOL EZ_SystemTime::Is_Equal_Time_NoMSec( const CStringW& strTime ) const
{
	return ( ( this->m_Time.wHour   == ( WORD )::_wtoi( strTime.Left( 2 )   ) ) && 
		     ( this->m_Time.wMinute == ( WORD )::_wtoi( strTime.Mid( 2, 2 ) ) ) && 
		     ( this->m_Time.wSecond == ( WORD )::_wtoi( strTime.Mid( 4, 2 ) ) ) );
}

//  ==========================================================================
//  丁锣Θ﹃篈
//  ==========================================================================
CString EZ_SystemTime::Time_To_String() const
{
	CString strTime = _T( "" );

	EZ_SystemTime::Get_String( &this->m_Time, strTime, EZ_SystemTime::FORMAT_FULL_STRING );

	return strTime;
}

CStringA EZ_SystemTime::Time_To_StringA() const
{
	CStringA strTime = "";

	EZ_SystemTime::Get_String( &this->m_Time, strTime, EZ_SystemTime::FORMAT_FULL_STRING );

	return strTime;
}

CStringW EZ_SystemTime::Time_To_StringW() const
{
	CStringW strTime = L"";

	EZ_SystemTime::Get_String( &this->m_Time, strTime, EZ_SystemTime::FORMAT_FULL_STRING );

	return strTime;
}

//  ==========================================================================
//  丁锣Θ﹃篈
//  ==========================================================================
CString EZ_SystemTime::Get_Time_String( CString strFormat ) const
{
	CString strTime = _T( "" );

	this->Get_Time_String( strFormat, strTime );

	return strTime;
}

CStringA EZ_SystemTime::Get_Time_StringA( CStringA strFormat ) const
{
	CStringA strTime = "";

	this->Get_Time_StringA( strFormat, strTime );

	return strTime;
}

CStringW EZ_SystemTime::Get_Time_StringW( CStringW strFormat ) const
{
	CStringW strTime = L"";

	this->Get_Time_StringW( strFormat, strTime );

	return strTime;
}

//  ==========================================================================
//  丁锣Θ﹃篈
//  ==========================================================================
void EZ_SystemTime::Get_Time_String( CString strFormat, CString& strTime ) const
{
	//  Empty
	strTime.Empty();

	//  Set String
	C_SYSTEMTIME stTime     = { 2222, 2, 2, 2, 2, 2, 2, 2 };
	CString      strTemp    = _T( "" );
	C_INT        iFormatLen = strFormat.GetLength();

	for ( INT i = 0; i < iFormatLen; i++, strTime += strTemp, strTemp.Empty() )
	{
		switch ( strFormat[ i ] )
		{
		case 'O':
			{	//  OS Setting
				if ( this->Is_Empty() )
				{
#if ( defined( RES_ARB ) || defined( RES_HEB ) || defined( RES_PRS ) )
					strTemp = COleDateTime( stTime ).Format( ( LOCALE_NOUSEROVERRIDE | VAR_DATEVALUEONLY ) );
#else
					::GetDateFormat( LOCALE_USER_DEFAULT, DATE_SHORTDATE, &stTime, NULL, strTemp.GetBuffer( MAX_PATH ), MAX_PATH );
					strTemp.ReleaseBuffer();
#endif

					strTemp.Replace( '2', '-' );
					strTemp.Replace( '0', '-' );
				}
				else
				{
#if ( defined( RES_ARB ) || defined( RES_HEB ) || defined( RES_PRS ) )
					strTemp = COleDateTime( this->m_Time ).Format( ( LOCALE_NOUSEROVERRIDE | VAR_DATEVALUEONLY ) );
#else
					::GetDateFormat( LOCALE_USER_DEFAULT, DATE_SHORTDATE, &this->m_Time, NULL, strTemp.GetBuffer( MAX_PATH ), MAX_PATH );
					strTemp.ReleaseBuffer();
#endif
				}
			}
			break;

		case 'o':
			{	//  OS Setting
				if ( this->Is_Empty() )
				{
					::GetTimeFormat( LOCALE_USER_DEFAULT, ( TIME_FORCE24HOURFORMAT | TIME_NOTIMEMARKER ), &stTime, NULL, strTemp.GetBuffer( MAX_PATH ), MAX_PATH );
					strTemp.ReleaseBuffer();

					strTemp.Replace( '2', '-' );
					strTemp.Replace( '0', '-' );

					if ( ( strFormat[ ( i + 1 ) ] == 'a' ) || ( strFormat[ ( i + 1 ) ] == 'A' ) )
					{
#if _MSC_VER > 1300
						strTemp.Append( _T( ".---" ) );
#else
						strTemp += _T( ".---" );
#endif
						
						i++;
					}
				}
				else
				{
					::GetTimeFormat( LOCALE_USER_DEFAULT, ( TIME_FORCE24HOURFORMAT | TIME_NOTIMEMARKER ), &this->m_Time, NULL, strTemp.GetBuffer( MAX_PATH ), MAX_PATH );
					strTemp.ReleaseBuffer();

					if ( ( strFormat[ ( i + 1 ) ] == 'a' ) || ( strFormat[ ( i + 1 ) ] == 'A' ) )
					{
#if _MSC_VER > 1300
						strTemp.AppendFormat( _T( ".%03d" ), this->m_Time.wMilliseconds );
#else
						strTemp.Format( _T( "%s.%03d" ), strTemp, this->m_Time.wMilliseconds );
#endif

						i++;
					}
				}
			}
			break;

		case 'Y':
		case 'y':
			{	//  Year
				strTemp.Format( _T( "%04d" ), this->m_Time.wYear );
			}
			break;

		case 'M':
			{	//  Month
				strTemp.Format( _T( "%02d" ), this->m_Time.wMonth );
			}
			break;

		case 'D':
		case 'd':
			{	//  Day
				strTemp.Format( _T( "%02d" ), this->m_Time.wDay );
			}
			break;

		case 'H':
		case 'h':
			{	//  Hour
				strTemp.Format( _T( "%02d" ), this->m_Time.wHour );
			}
			break;

		case 'm':
			{	//  Minute
				strTemp.Format( _T( "%02d" ), this->m_Time.wMinute );
			}
			break;

		case 'S':
			{	//  Second
				strTemp.Format( _T( "%02d" ), this->m_Time.wSecond );
			}
			break;

		case 's':
			{	//  MilliSecond
				strTemp.Format( _T( "%03d" ), this->m_Time.wMilliseconds );
			}
			break;

		default:
			{	//  No Match
				strTemp = strFormat[ i ];
			}
			break;
		}
	}
}

void EZ_SystemTime::Get_Time_StringA( CStringA strFormat, CStringA& strTime ) const
{
#if defined ( _UNICODE )
	{
		//  
		CStringW strFormatW = L"";

		::MultiByteToWideChar( CP_ACP, 0, strFormat, -1, strFormatW.GetBuffer( MAX_PATH ), MAX_PATH );
		strFormatW.ReleaseBuffer();

		//
		CStringW strTimeW = L"";

		this->Get_Time_String( strFormatW, strTimeW );

		//
		::WideCharToMultiByte( CP_ACP, 0, strTimeW, -1, strTime.GetBuffer( MAX_PATH ), MAX_PATH, NULL, NULL );
		strTime.ReleaseBuffer();
	}
#else
	this->Get_Time_String( strFormat, strTime );
#endif
}

void EZ_SystemTime::Get_Time_StringW( CStringW strFormat, CStringW& strTime ) const
{
#if defined ( _UNICODE )
	this->Get_Time_String( strFormat, strTime );
#else
	{
		//
		CStringA strFormatA = "";

		::WideCharToMultiByte( CP_ACP, 0, strFormat, -1, strFormatA.GetBuffer( MAX_PATH ), MAX_PATH, NULL, NULL );
		strFormatA.ReleaseBuffer();

		//
		CStringA strTimeA = "";

		this->Get_Time_String( strFormatA, strTimeA );

		//
		::MultiByteToWideChar( CP_ACP, 0, strTimeA, -1, strTime.GetBuffer( MAX_PATH ), MAX_PATH );
		strTime.ReleaseBuffer();
	}	
#endif
}

//  ==========================================================================
//  Get_Full_Time
//  ==========================================================================
SYSTEMTIME EZ_SystemTime::Get_Full_Time() const
{ 
	return this->m_Time;
}

void EZ_SystemTime::Get_Full_Time( __out SYSTEMTIME& stTime ) const
{ 
	stTime = this->m_Time; 
}

void EZ_SystemTime::Get_Full_Time( __out struct tm& tmTime, __in const INT iDST ) const
{
	tmTime.tm_sec   =   this->m_Time.wSecond;			/* seconds after the minute - [0,59] */
	tmTime.tm_min   =   this->m_Time.wMinute;			/* minutes after the hour - [0,59] */
	tmTime.tm_hour  =   this->m_Time.wHour;				/* hours since midnight - [0,23] */
	tmTime.tm_mday  =   this->m_Time.wDay;				/* day of the month - [1,31] */
	tmTime.tm_mon   = ( this->m_Time.wMonth - 1   );	/* months since January - [0,11] */
	tmTime.tm_year  = ( this->m_Time.wYear - 1900 );	/* years since 1900 */
	tmTime.tm_wday  = 0;								/* days since Sunday - [0,6] */
	tmTime.tm_yday  = 0;								/* days since January 1 - [0,365] */
	tmTime.tm_isdst = iDST;								/* daylight savings time flag */
}

time_t EZ_SystemTime::Get_Full_Time( __in const BOOL bCTime, __in const INT iDST ) const
{
	if ( bCTime )
		return CTime( this->m_Time, iDST ).GetTime();
	else
	{
		struct tm tmTime = { 0 };

		this->Get_Full_Time( tmTime, iDST );

		return ::mktime( &tmTime );
	}
}

//  ==========================================================================
//  Set_Full_Time
//  ==========================================================================
int EZ_SystemTime::Set_Full_Time( __in const time_t tTime, __in C_BOOL bCTime )
{
	if ( bCTime )
	{
		CTime( tTime ).GetAsSystemTime( this->m_Time );
		return -1;
	}
	else
	{
		struct tm tmTime = { 0 };

		::localtime_s( &tmTime, &tTime );

		*this = tmTime;

		return tmTime.tm_isdst;
	}
}

int EZ_SystemTime::Set_Full_Time( __in const timeval& tvTime, __in C_BOOL bCTime )
{
	const int iDST = this->Set_Full_Time( ( time_t )tvTime.tv_sec, bCTime );

	this->m_Time.wMilliseconds = ( WORD )( tvTime.tv_usec / 1000 );

	return iDST;
}

void EZ_SystemTime::Set_Full_Time( __in C_INT iDate, __in C_INT iHour, __in C_INT iMinute, __in C_INT iSecond, __in C_INT iMSec )
{ 
	this->Set_Date( iDate ); 

	this->Set_Time( iHour, iMinute, iSecond, iMSec ); 
}

void EZ_SystemTime::Set_Full_Time( __in const CString& strDate, __in C_INT iHour, __in C_INT iMinute, __in C_INT iSecond, __in C_INT iMSec )
{ 
	this->Set_Date( strDate ); 

	this->Set_Time( iHour, iMinute, iSecond, iMSec ); 
}

void EZ_SystemTime::Set_Full_Time( __in const SYSTEMTIME& stDate, __in C_INT iHour, __in C_INT iMinute, __in C_INT iSecond, __in C_INT iMSec )
{ 
	this->Set_Date( stDate ); 

	this->Set_Time( iHour, iMinute, iSecond, iMSec );
}

//  ==========================================================================
//  Get_Time ( Static )
//  ==========================================================================
void EZ_SystemTime::Get_Time( LPCSTR lpTime, SYSTEMTIME& stTime )
{
	//  
	::memset( &stTime, 0, sizeof( SYSTEMTIME ) );

	if ( !lpTime )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Get_Time - NULL !\n" ) );
		return;
	}

	//
	size_t tLength = ::strlen( lpTime );

	if ( tLength <= 0 )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Get_Time - Empty !\n" ) );
		return;
	}

	//  
	C_INT iSize         = sizeof( char );
	char  szTmpBuf[ 8 ] = "";

	switch ( tLength )
	{
	case 17:
		{	//  YYYYMMDDHHmmSSsss
			//  M-Sec
			::memcpy( szTmpBuf, ( lpTime + 14 ), ( 3 * iSize ) );
			szTmpBuf[ 3 ] = '\0';

			stTime.wMilliseconds = ::atoi( szTmpBuf );
		}

	case 14:
		{	//  YYYYMMDDHHmmSS
			//  Year
			::memcpy( szTmpBuf, lpTime, ( 4 * iSize ) );
			szTmpBuf[ 4 ] = '\0';

			stTime.wYear = ::atoi( szTmpBuf );

			//  Month
			::memcpy( szTmpBuf, ( lpTime + 4 ), ( 2 * iSize ) );
			szTmpBuf[ 2 ] = '\0';

			stTime.wMonth = ::atoi( szTmpBuf );

			//  Day
			::memcpy( szTmpBuf, ( lpTime + 6 ), ( 2 * iSize ) );
			szTmpBuf[ 2 ] = '\0';

			stTime.wDay = ::atoi( szTmpBuf );

			//  Hour
			::memcpy( szTmpBuf, ( lpTime + 8 ), ( 2 * iSize ) );
			szTmpBuf[ 2 ] = '\0';

			stTime.wHour = ::atoi( szTmpBuf );

			//  Minute
			::memcpy( szTmpBuf, ( lpTime + 10 ), ( 2 * iSize ) );
			szTmpBuf[ 2 ] = '\0';

			stTime.wMinute = ::atoi( szTmpBuf );

			//  Second
			::memcpy( szTmpBuf, ( lpTime + 12 ), ( 2 * iSize ) );
			szTmpBuf[ 2 ] = '\0';

			stTime.wSecond = ::atoi( szTmpBuf );
		}
		break;

	case 9:
		{	//  HHmmSSsss
			//  Set Date
			stTime.wYear      = 2000;
			stTime.wMonth     = 1;
			stTime.wDayOfWeek = 0;
			stTime.wDay       = 1;

			//  Hour
			::memcpy( szTmpBuf, lpTime, ( 2 * iSize ) );
			szTmpBuf[ 2 ] = '\0';

			stTime.wHour = ::atoi( szTmpBuf );

			//  Minute
			::memcpy( szTmpBuf, ( lpTime + 2 ), ( 2 * iSize ) );
			szTmpBuf[ 2 ] = '\0';

			stTime.wMinute = ::atoi( szTmpBuf );

			//  Second
			::memcpy( szTmpBuf, ( lpTime + 4 ), ( 2 * iSize ) );
			szTmpBuf[ 2 ] = '\0';

			stTime.wSecond = ::atoi( szTmpBuf );

			//  M-Sec
			::memcpy( szTmpBuf, ( lpTime + 6 ), ( 3 * iSize ) );
			szTmpBuf[ 3 ] = '\0';

			stTime.wMilliseconds = ::atoi( szTmpBuf );
		}
		break;

	case 8:
		{	//  YYYYMMDD
			//  Year
			::memcpy( szTmpBuf, lpTime, ( 4 * iSize ) );
			szTmpBuf[ 4 ] = '\0';

			stTime.wYear = ::atoi( szTmpBuf );

			//  Month
			::memcpy( szTmpBuf, ( lpTime + 4 ), ( 2 * iSize ) );
			szTmpBuf[ 2 ] = '\0';

			stTime.wMonth = ::atoi( szTmpBuf );

			//  Day
			::memcpy( szTmpBuf, ( lpTime + 6 ), ( 2 * iSize ) );
			szTmpBuf[ 2 ] = '\0';

			stTime.wDay = ::atoi( szTmpBuf );
		}
		break;
	}
}

void EZ_SystemTime::Get_Time( LPCWSTR lpTime, SYSTEMTIME& stTime )
{
	//  
	::memset( &stTime, 0, sizeof( SYSTEMTIME ) );

	if ( !lpTime )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Get_Time - NULL !\n" ) );
		return;
	}

	//
	size_t tLength = ::wcslen( lpTime );

	if ( tLength <= 0 )
	{
		::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Get_Time - Empty !\n" ) );
		return;
	}

	//  
	C_INT iSize         = sizeof( WCHAR );
	WCHAR wzTmpBuf[ 8 ] = L"";

	switch ( tLength )
	{
	case 17:
		{	//  YYYYMMDDHHmmSSsss
			//  M-Sec
			::memcpy( wzTmpBuf, ( lpTime + 14 ), ( 3 * iSize ) );
			wzTmpBuf[ 3 ] = '\0';

			stTime.wMilliseconds = ::_wtoi( wzTmpBuf );
		}

	case 14:
		{	//  YYYYMMDDHHmmSS
			//  Year
			::memcpy( wzTmpBuf, lpTime, ( 4 * iSize ) );
			wzTmpBuf[ 4 ] = '\0';

			stTime.wYear = ::_wtoi( wzTmpBuf );

			//  Month
			::memcpy( wzTmpBuf, ( lpTime + 4 ), ( 2 * iSize ) );
			wzTmpBuf[ 2 ] = '\0';

			stTime.wMonth = ::_wtoi( wzTmpBuf );

			//  Day
			::memcpy( wzTmpBuf, ( lpTime + 6 ), ( 2 * iSize ) );
			wzTmpBuf[ 2 ] = '\0';

			stTime.wDay = ::_wtoi( wzTmpBuf );

			//  Hour
			::memcpy( wzTmpBuf, ( lpTime + 8 ), ( 2 * iSize ) );
			wzTmpBuf[ 2 ] = '\0';

			stTime.wHour = ::_wtoi( wzTmpBuf );

			//  Minute
			::memcpy( wzTmpBuf, ( lpTime + 10 ), ( 2 * iSize ) );
			wzTmpBuf[ 2 ] = '\0';

			stTime.wMinute = ::_wtoi( wzTmpBuf );

			//  Second
			::memcpy( wzTmpBuf, ( lpTime + 12 ), ( 2 * iSize ) );
			wzTmpBuf[ 2 ] = '\0';

			stTime.wSecond = ::_wtoi( wzTmpBuf );
		}
		break;

	case 9:
		{	//  HHmmSSsss
			//  Set Date
			stTime.wYear      = 2000;
			stTime.wMonth     = 1;
			stTime.wDayOfWeek = 0;
			stTime.wDay       = 1;

			//  Hour
			::memcpy( wzTmpBuf, lpTime, ( 2 * iSize ) );
			wzTmpBuf[ 2 ] = '\0';

			stTime.wHour = ::_wtoi( wzTmpBuf );

			//  Minute
			::memcpy( wzTmpBuf, ( lpTime + 2 ), ( 2 * iSize ) );
			wzTmpBuf[ 2 ] = '\0';

			stTime.wMinute = ::_wtoi( wzTmpBuf );

			//  Second
			::memcpy( wzTmpBuf, ( lpTime + 4 ), ( 2 * iSize ) );
			wzTmpBuf[ 2 ] = '\0';

			stTime.wSecond = ::_wtoi( wzTmpBuf );

			//  M-Sec
			::memcpy( wzTmpBuf, ( lpTime + 6 ), ( 3 * iSize ) );
			wzTmpBuf[ 3 ] = '\0';

			stTime.wMilliseconds = ::_wtoi( wzTmpBuf );
		}
		break;

	case 8:
		{	//  YYYYMMDD
			//  Year
			::memcpy( wzTmpBuf, lpTime, ( 4 * iSize ) );
			wzTmpBuf[ 4 ] = '\0';

			stTime.wYear = ::_wtoi( wzTmpBuf );

			//  Month
			::memcpy( wzTmpBuf, ( lpTime + 4 ), ( 2 * iSize ) );
			wzTmpBuf[ 2 ] = '\0';

			stTime.wMonth = ::_wtoi( wzTmpBuf );

			//  Day
			::memcpy( wzTmpBuf, ( lpTime + 6 ), ( 2 * iSize ) );
			wzTmpBuf[ 2 ] = '\0';

			stTime.wDay = ::_wtoi( wzTmpBuf );
		}
		break;

	default:
		{
			::EZOutputDebugString( L"$$$ [ 235-EZ_SystemTime ] Get_Time - Illegal ! ( Time : '%s' )\n", lpTime );
		}
		break;
	}
}

//  ==========================================================================
//  Get_String ( Static )
//  ==========================================================================
CString EZ_SystemTime::Get_String( const SYSTEMTIME* lpTime, const EZ_SystemTime::FORMAT iFormat )
{
	CString strTime = _T( "" );

	EZ_SystemTime::Get_String( lpTime, strTime, iFormat );

	return strTime;
}

CStringA EZ_SystemTime::Get_StringA( const SYSTEMTIME* lpTime, const EZ_SystemTime::FORMAT iFormat )
{
	CStringA strTime = "";

	EZ_SystemTime::Get_String( lpTime, strTime, iFormat );

	return strTime;
}

CStringW EZ_SystemTime::Get_StringW( const SYSTEMTIME* lpTime, const EZ_SystemTime::FORMAT iFormat )
{
	CStringW strTime = L"";

	EZ_SystemTime::Get_String( lpTime, strTime, iFormat );

	return strTime;
}

void EZ_SystemTime::Get_String( const SYSTEMTIME* lpTime, CStringA& strTime, const EZ_SystemTime::FORMAT iFormat )
{
	switch ( iFormat )
	{
	case EZ_SystemTime::FORMAT_FULL_STRING:
		{	//  Always '20190101000000000'
			if ( lpTime )
				strTime.Format( "%04d%02d%02d%02d%02d%02d%03d", lpTime->wYear, lpTime->wMonth, lpTime->wDay, lpTime->wHour, lpTime->wMinute, lpTime->wSecond, lpTime->wMilliseconds );
			else
				strTime.Format( "00000000000000000" );
		}
		break;

	case EZ_SystemTime::FORMAT_FULL_STANDARD:
		{	//  Always '2019/01/01 00:00:00.000'
			if ( lpTime )
				strTime.Format( "%04d/%02d/%02d %02d:%02d:%02d.%03d", lpTime->wYear, lpTime->wMonth, lpTime->wDay, lpTime->wHour, lpTime->wMinute, lpTime->wSecond, lpTime->wMilliseconds );
			else
				strTime.Format( "0000/00/00 00:00:00.000" );
		}
		break;

	case EZ_SystemTime::FORMAT_FULL_SYSTEM:
		{	//  It will be '2019/01/01 00:00:00.000' or '01/01/2019 00:00:00.000'
			if ( !lpTime )
				::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Get_String - UnSupport ! ( Format : 'FORMAT_FULL_SYSTEM' )\n" ) );
			else if ( ( lpTime->wYear == 0 ) || ( lpTime->wMonth == 0 ) || ( lpTime->wDay == 0 ) )
				strTime.Format( "%04d/%02d/%02d %02d:%02d:%02d.%03d", lpTime->wYear, lpTime->wMonth, lpTime->wDay, lpTime->wHour, lpTime->wMinute, lpTime->wSecond, lpTime->wMilliseconds );
			else
			{
				::GetDateFormatA( LOCALE_USER_DEFAULT, DATE_SHORTDATE, lpTime, NULL, strTime.GetBuffer( MAX_PATH ), MAX_PATH );
				strTime.ReleaseBuffer();

				strTime.AppendFormat( " %02d:%02d:%02d.%03d", lpTime->wHour, lpTime->wMinute, lpTime->wSecond, lpTime->wMilliseconds );
			}
		}
		break;

	case EZ_SystemTime::FORMAT_DATE_STRING:
		{	//  Always '20190101'
			if ( lpTime )
				strTime.Format( "%04d%02d%02d", lpTime->wYear, lpTime->wMonth, lpTime->wDay );
			else
				strTime.Format( "00000000" );
		}
		break;

	case EZ_SystemTime::FORMAT_DATE_STANDARD:
		{	//  Always '2019/01/01'
			if ( lpTime )
				strTime.Format( "%04d/%02d/%02d", lpTime->wYear, lpTime->wMonth, lpTime->wDay );
			else
				strTime.Format( "0000/00/00" );
		}
		break;

	case EZ_SystemTime::FORMAT_DATE_SYSTEM:
		{	//  It will be '2019/01/01' or '01/01/2019'
			strTime.Empty();

			::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Get_String - UnSupport ! ( Format : 'FORMAT_DATE_SYSTEM' )\n" ) );
		}
		break;

	case EZ_SystemTime::FORMAT_TIME_STRING:
		{	//  Always '000000000'
			if ( lpTime )
				strTime.Format( "%02d%02d%02d%03d", lpTime->wHour, lpTime->wMinute, lpTime->wSecond, lpTime->wMilliseconds );
			else
				strTime.Format( "000000000" );
		}
		break;

	case EZ_SystemTime::FORMAT_TIME_STANDARD:
		{	//  Always '00:00:00.000'
			//  Same EZ_SystemTime::FORMAT_TIME_SYSTEM
		}

	case EZ_SystemTime::FORMAT_TIME_SYSTEM:
		{	//  Always '00:00:00.000'
			if ( lpTime )
				strTime.Format( "%02d:%02d:%02d.%03d", lpTime->wHour, lpTime->wMinute, lpTime->wSecond, lpTime->wMilliseconds );
			else
				strTime.Format( "00:00:00.000" );
		}
		break;

	default:
		{	//  UnKnow
			strTime.Empty();

			::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Get_String - UnKnow ! ( Format : '%d' )\n" ), iFormat );
		}
		break;
	}
}

void EZ_SystemTime::Get_String( const SYSTEMTIME* lpTime, CStringW& strTime, const EZ_SystemTime::FORMAT iFormat )
{
	switch ( iFormat )
	{
	case EZ_SystemTime::FORMAT_FULL_STRING:
		{	//  Always '20190101000000000'
			if ( lpTime )
				strTime.Format( L"%04d%02d%02d%02d%02d%02d%03d", lpTime->wYear, lpTime->wMonth, lpTime->wDay, lpTime->wHour, lpTime->wMinute, lpTime->wSecond, lpTime->wMilliseconds );
			else
				strTime.Format( L"00000000000000000" );
		}
		break;

	case EZ_SystemTime::FORMAT_FULL_STANDARD:
		{	//  Always '2019/01/01 00:00:00.000'
			if ( lpTime )
				strTime.Format( L"%04d/%02d/%02d %02d:%02d:%02d.%03d", lpTime->wYear, lpTime->wMonth, lpTime->wDay, lpTime->wHour, lpTime->wMinute, lpTime->wSecond, lpTime->wMilliseconds );
			else
				strTime.Format( L"0000/00/00 00:00:00.000" );
		}
		break;

	case EZ_SystemTime::FORMAT_FULL_SYSTEM:
		{	//  It will be '2019/01/01 00:00:00.000' or '01/01/2019 00:00:00.000'
			if ( !lpTime )
				::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Get_String - UnSupport ! ( Format : 'FORMAT_FULL_SYSTEM' )\n" ) );
			else if ( ( lpTime->wYear == 0 ) || ( lpTime->wMonth == 0 ) || ( lpTime->wDay == 0 ) )
				strTime.Format( L"%04d/%02d/%02d %02d:%02d:%02d.%03d", lpTime->wYear, lpTime->wMonth, lpTime->wDay, lpTime->wHour, lpTime->wMinute, lpTime->wSecond, lpTime->wMilliseconds );
			else
			{
				::GetDateFormatW( LOCALE_USER_DEFAULT, DATE_SHORTDATE, lpTime, NULL, strTime.GetBuffer( MAX_PATH ), MAX_PATH );
				strTime.ReleaseBuffer();

				strTime.AppendFormat( L" %02d:%02d:%02d.%03d", lpTime->wHour, lpTime->wMinute, lpTime->wSecond, lpTime->wMilliseconds );
			}
		}
		break;

	case EZ_SystemTime::FORMAT_DATE_STRING:
		{	//  Always '20190101'
			if ( lpTime )
				strTime.Format( L"%04d%02d%02d", lpTime->wYear, lpTime->wMonth, lpTime->wDay );
			else
				strTime.Format( L"00000000" );
		}
		break;

	case EZ_SystemTime::FORMAT_DATE_STANDARD:
		{	//  Always '2019/01/01'
			if ( lpTime )
				strTime.Format( L"%04d/%02d/%02d", lpTime->wYear, lpTime->wMonth, lpTime->wDay );
			else
				strTime.Format( L"0000/00/00" );
		}
		break;

	case EZ_SystemTime::FORMAT_DATE_SYSTEM:
		{	//  It will be '2019/01/01' or '01/01/2019'
			//  UnSupport Now
		}
		break;

	case EZ_SystemTime::FORMAT_TIME_STRING:
		{	//  Always '000000000'
			if ( lpTime )
				strTime.Format( L"%02d%02d%02d%03d", lpTime->wHour, lpTime->wMinute, lpTime->wSecond, lpTime->wMilliseconds );
			else
				strTime.Format( L"000000000" );
		}
		break;

	case EZ_SystemTime::FORMAT_TIME_STANDARD:
		{	//  Always '00:00:00.000'
			//  Same EZ_SystemTime::FORMAT_TIME_SYSTEM
		}

	case EZ_SystemTime::FORMAT_TIME_SYSTEM:
		{	//  Always '00:00:00.000'
			if ( lpTime )
				strTime.Format( L"%02d:%02d:%02d.%03d", lpTime->wHour, lpTime->wMinute, lpTime->wSecond, lpTime->wMilliseconds );
			else
				strTime.Format( L"00:00:00.000" );
		}
		break;

	default:
		{	//  UnKnow
			strTime.Empty();

			::EZOutputDebugString( _T( "$$$ [ 235-EZ_SystemTime ] Get_String - UnKnow ! ( Format : '%d' )\n" ), iFormat );
		}
		break;
	}
}

//  ==========================================================================
//  GetDays ( Static )
//  ==========================================================================
C_INT EZ_SystemTime::GetDays( const SYSTEMTIME& stStartTime, const SYSTEMTIME& stEndTime )
{
	COleDateTimeSpan ctSpan( COleDateTime( stEndTime ) - COleDateTime( stStartTime ) );
	
	return ( C_INT )ctSpan.GetTotalDays();
}

C_INT EZ_SystemTime::GetDays( const CStringA& strStartTime, const CStringA& strEndTime )
{
	EZ_SystemTime dtStartTime = strStartTime, dtEndTime = strEndTime;

	return EZ_SystemTime::GetDays( dtStartTime, dtEndTime );
}

C_INT EZ_SystemTime::GetDays( const CStringW& strStartTime, const CStringW& strEndTime )
{
	EZ_SystemTime dtStartTime = strStartTime, dtEndTime = strEndTime;

	return EZ_SystemTime::GetDays( dtStartTime, dtEndTime );
}

//  ==========================================================================
//  GetMinutes ( Static )
//  ==========================================================================
C_INT EZ_SystemTime::GetMinutes( const SYSTEMTIME& stStartTime, const SYSTEMTIME& stEndTime )
{
	COleDateTimeSpan ctSpan( COleDateTime( stEndTime ) - COleDateTime( stStartTime ) );

	return ( C_INT )ctSpan.GetTotalMinutes();
}

C_INT EZ_SystemTime::GetMinutes( const CStringA& strStartTime, const CStringA& strEndTime )
{
	EZ_SystemTime dtStartTime = strStartTime, dtEndTime = strEndTime;

	return EZ_SystemTime::GetMinutes( dtStartTime, dtEndTime );
}

C_INT EZ_SystemTime::GetMinutes( const CStringW& strStartTime, const CStringW& strEndTime )
{
	EZ_SystemTime dtStartTime = strStartTime, dtEndTime = strEndTime;

	return EZ_SystemTime::GetMinutes( dtStartTime, dtEndTime );
}

//  ==========================================================================
//  GetSeconds ( Static )
//  ==========================================================================
C_INT EZ_SystemTime::GetSeconds( __in const SYSTEMTIME& stTime )
{
	return ( ( stTime.wHour * 3600 ) + ( stTime.wMinute * 60 ) + stTime.wSecond );
}

C_INT EZ_SystemTime::GetSeconds( const SYSTEMTIME& stStartTime, const SYSTEMTIME& stEndTime )
{
	LONGLONG llTotalSec( 0 );

	EZ_SystemTime::GetSeconds( stStartTime, stEndTime, llTotalSec );
	
	return ( C_INT )llTotalSec;
}

C_INT EZ_SystemTime::GetSeconds( const CStringA& strStartTime, const CStringA& strEndTime )
{
	LONGLONG llTotalSec( 0 );

	EZ_SystemTime::GetSeconds( strStartTime, strEndTime, llTotalSec );

	return ( C_INT )llTotalSec;
}

C_INT EZ_SystemTime::GetSeconds( const CStringW& strStartTime, const CStringW& strEndTime )
{
	LONGLONG llTotalSec( 0 );

	EZ_SystemTime::GetSeconds( strStartTime, strEndTime, llTotalSec );

	return ( C_INT )llTotalSec;
}

//  ==========================================================================
//  GetSeconds ( Static )
//  ==========================================================================
void EZ_SystemTime::GetSeconds( const SYSTEMTIME& stStartTime, const SYSTEMTIME& stEndTime, LONGLONG& llTotalSec )
{
	COleDateTimeSpan ctSpan( COleDateTime( stEndTime ) - COleDateTime( stStartTime ) );
	
	llTotalSec = ( LONGLONG )ctSpan.GetTotalSeconds();
}

void EZ_SystemTime::GetSeconds( const CStringA& strStartTime, const CStringA& strEndTime, LONGLONG& llTotalSec )
{
	EZ_SystemTime dtStartTime = strStartTime, dtEndTime = strEndTime;

	EZ_SystemTime::GetSeconds( dtStartTime, dtEndTime, llTotalSec );
}

void EZ_SystemTime::GetSeconds( const CStringW& strStartTime, const CStringW& strEndTime, LONGLONG& llTotalSec )
{
	EZ_SystemTime dtStartTime = strStartTime, dtEndTime = strEndTime;

	EZ_SystemTime::GetSeconds( dtStartTime, dtEndTime, llTotalSec );
}

//  ==========================================================================
//  GetMilliSeconds ( Static )
//  ==========================================================================
C_INT EZ_SystemTime::GetMilliSeconds( const SYSTEMTIME& stStartTime, const SYSTEMTIME& stEndTime )
{
	LONGLONG llTotalMS( 0 );

	EZ_SystemTime::GetMilliSeconds( stStartTime, stEndTime, llTotalMS );

	return ( INT )llTotalMS;
}

C_INT EZ_SystemTime::GetMilliSeconds( const CStringA& strStartTime, const CStringA& strEndTime )
{
	LONGLONG llTotalMS( 0 );

	EZ_SystemTime::GetMilliSeconds( strStartTime, strEndTime, llTotalMS );

	return ( INT )llTotalMS;
}

C_INT EZ_SystemTime::GetMilliSeconds( const CStringW& strStartTime, const CStringW& strEndTime )
{
	LONGLONG llTotalMS( 0 );

	EZ_SystemTime::GetMilliSeconds( strStartTime, strEndTime, llTotalMS );

	return ( INT )llTotalMS;
}

//  ==========================================================================
//  GetMilliSeconds ( Static )
//  ==========================================================================
void EZ_SystemTime::GetMilliSeconds( const SYSTEMTIME& stStartTime, const SYSTEMTIME& stEndTime, LONGLONG& llTotalMS )
{
	COleDateTimeSpan ctSpan( COleDateTime( stEndTime ) - COleDateTime( stStartTime ) );

	llTotalMS  = ( LONGLONG )ctSpan.GetTotalSeconds();
	llTotalMS *= 1000;
	llTotalMS += stEndTime.wMilliseconds;
	llTotalMS -= stStartTime.wMilliseconds;
}

void EZ_SystemTime::GetMilliSeconds( const CStringA& strStartTime, const CStringA& strEndTime, LONGLONG& llTotalMS )
{
	EZ_SystemTime dtStartTime = strStartTime, dtEndTime = strEndTime;

	EZ_SystemTime::GetMilliSeconds( dtStartTime, dtEndTime, llTotalMS );
}

void EZ_SystemTime::GetMilliSeconds( const CStringW& strStartTime, const CStringW& strEndTime, LONGLONG& llTotalMS )
{
	EZ_SystemTime dtStartTime = strStartTime, dtEndTime = strEndTime;

	EZ_SystemTime::GetMilliSeconds( dtStartTime, dtEndTime, llTotalMS );
}

//  ==========================================================================
//  GetOSMonth ( Static )
//  ==========================================================================
void EZ_SystemTime::GetOSMonth( EZVCSTRINGARRAY& aryMonth )
{
	//  
	aryMonth.RemoveAll();

	//  
	SYSTEMTIME stTime         = { 2011, 1, 0, 1, 0, 0, 0, 0 };
	TCHAR      szMonth[ 128 ] = _T( "" );

	for ( INT i = 0; i < 12; i++ )
	{
		stTime.wMonth = ( i + 1 );

		::GetDateFormat( LOCALE_USER_DEFAULT, LOCALE_USE_CP_ACP, &stTime, _T( "MMM" ), szMonth, 128 );

		aryMonth.Add( szMonth );
	}
}

//  ==========================================================================
//  GetOSWeek ( Static )
//  ==========================================================================
void EZ_SystemTime::GetOSWeek( EZVCSTRINGARRAY& aryWeek )
{
	//  
	aryWeek.RemoveAll();

	//  
	SYSTEMTIME stTime        = { 2012, 7, 0, 1, 0, 0, 0, 0 };
	TCHAR      szWeek[ 128 ] = _T( "" );

	for ( INT i = 0; i < 7; i++ )
	{
		stTime.wDay = ( i + 1 );

		::GetDateFormat( LOCALE_USER_DEFAULT, LOCALE_USE_CP_ACP, &stTime, _T( "ddd" ), szWeek, 128 );

		aryWeek.Add( szWeek );
	}
}

//  =============================================================================================
//  =============================================================================================
//  =============================================================================================
//  =============================================================================================
//  =============================================================================================

//  ==========================================================================
//  
//  ==========================================================================
MediaSpan::MediaSpan( C_BOOL bGetCurrentTime ) : m_StartTime( bGetCurrentTime ), m_EndTime( bGetCurrentTime )
{
	;
}

MediaSpan::MediaSpan( const SYSTEMTIME& stStartTime, const SYSTEMTIME& stEndTime ) : m_StartTime( stStartTime ), m_EndTime( stEndTime )
{
	;
}

MediaSpan::MediaSpan( const EZ_SystemTime& dtStartTime, const EZ_SystemTime& dtEndTime ) : m_StartTime( dtStartTime ), m_EndTime( dtEndTime )
{
	;
}

MediaSpan::MediaSpan( const struct tm& tmStart, const struct tm& tmEnd ) : m_StartTime( tmStart ), m_EndTime( tmEnd )
{
	;
}

MediaSpan::MediaSpan( LPCSTR lpStartTime, LPCSTR lpEndTime ) : m_StartTime( lpStartTime ), m_EndTime( lpEndTime )
{
	;
}

MediaSpan::MediaSpan( LPCWSTR lpStartTime, LPCWSTR lpEndTime ) : m_StartTime( lpStartTime ), m_EndTime( lpEndTime )
{
	;
}

MediaSpan::MediaSpan( const CStringA& strStartTime, const CStringA& strEndTime ) : m_StartTime(), m_EndTime()
{
	this->m_StartTime = strStartTime;
	this->m_EndTime = strEndTime;
}

MediaSpan::MediaSpan( const CStringW& strStartTime, const CStringW& strEndTime ) : m_StartTime(), m_EndTime()
{
	this->m_StartTime = strStartTime;
	this->m_EndTime = strEndTime;
}

MediaSpan::MediaSpan( C_MEDIASPAN& msTime ) : m_StartTime( msTime.m_StartTime ), m_EndTime( msTime.m_EndTime )
{
	;
}

MediaSpan::MediaSpan( LPCMEDIASPAN lpTime ) : m_StartTime(), m_EndTime()
{
	MediaSpan::operator = ( lpTime );
}

//  ==========================================================================
//  
//  ==========================================================================
MediaSpan::~MediaSpan() 
{
	//  this->m_StartTime
	//  this->m_EndTime
}

//  ==========================================================================
//  operator =
//  ==========================================================================
MediaSpan& MediaSpan::operator = ( C_MEDIASPAN& msTime )
{
	if ( this != &msTime )
	{
		this->m_StartTime = msTime.m_StartTime;
		this->m_EndTime   = msTime.m_EndTime;
	}
	
	return *this;
}

MediaSpan& MediaSpan::operator = ( LPCMEDIASPAN lpTime )
{
	if ( lpTime && ( this != lpTime ) )
	{
		this->m_StartTime = lpTime->m_StartTime;
		this->m_EndTime   = lpTime->m_EndTime;
	}
	
	return *this;
}

//  ==========================================================================
//  operator ==
//  ==========================================================================
BOOL MediaSpan::operator == ( C_MEDIASPAN& msTime ) const
{
	return ( ( this->m_StartTime == msTime.m_StartTime ) && ( this->m_EndTime == msTime.m_EndTime ) );
}

//  ==========================================================================
//  operator !=
//  ==========================================================================
BOOL MediaSpan::operator != ( C_MEDIASPAN& msTime ) const
{
	return ( ( this->m_StartTime != msTime.m_StartTime ) || ( this->m_EndTime != msTime.m_EndTime ) );
}

//  ==========================================================================
//  Set_Time
//  ==========================================================================
void MediaSpan::Set_Time( const SYSTEMTIME& stStartTime, const SYSTEMTIME& stEndTime )
{
	this->m_StartTime = stStartTime;
	this->m_EndTime   = stEndTime;
}

void MediaSpan::Set_Time( C_EZSYSTEMTIME& dtStartTime, C_EZSYSTEMTIME& dtEndTime )
{
	this->m_StartTime = dtStartTime;
	this->m_EndTime   = dtEndTime;
}

void MediaSpan::Set_Time( const struct tm& tmStart, const struct tm& tmEnd )
{
	this->m_StartTime = tmStart;
	this->m_EndTime   = tmEnd;
}

void MediaSpan::Set_Time( const CStringA& strStartTime, const CStringA& strEndTime )
{
	this->m_StartTime = strStartTime;
	this->m_EndTime   = strEndTime;
}

void MediaSpan::Set_Time( const CStringW& strStartTime, const CStringW& strEndTime )
{
	this->m_StartTime = strStartTime;
	this->m_EndTime   = strEndTime;
}

//  ==========================================================================
//  Get_Time
//  ==========================================================================
void MediaSpan::Get_Time( SYSTEMTIME& stStartTime, SYSTEMTIME& stEndTime ) const
{
	::memcpy( &stStartTime, &this->m_StartTime.m_Time, sizeof( SYSTEMTIME ) );
	::memcpy( &stEndTime,   &this->m_EndTime.m_Time,   sizeof( SYSTEMTIME ) );
}

void MediaSpan::Get_Time( EZ_SystemTime& stStartTime, EZ_SystemTime& stEndTime ) const
{
	stStartTime = this->m_StartTime;
	stEndTime   = this->m_EndTime;
}

void MediaSpan::Get_Time( struct tm& tmStart, struct tm& tmEnd ) const
{
	this->m_StartTime.Get_Full_Time( tmStart );
	this->m_EndTime.Get_Full_Time( tmEnd );
}

void MediaSpan::Get_Time( CStringA& strStartTime, CStringA& strEndTime ) const
{
	EZ_SystemTime::Get_String( &this->m_StartTime.m_Time, strStartTime, EZ_SystemTime::FORMAT_FULL_STRING );
	EZ_SystemTime::Get_String( &this->m_EndTime.m_Time,   strEndTime,   EZ_SystemTime::FORMAT_FULL_STRING );
}

void MediaSpan::Get_Time( CStringW& strStartTime, CStringW& strEndTime ) const
{
	EZ_SystemTime::Get_String( &this->m_StartTime.m_Time, strStartTime, EZ_SystemTime::FORMAT_FULL_STRING );
	EZ_SystemTime::Get_String( &this->m_EndTime.m_Time,   strEndTime,   EZ_SystemTime::FORMAT_FULL_STRING );
}

//  ==========================================================================
//  Is_Between_Date
//  ==========================================================================
C_BOOL MediaSpan::Is_Between_Date( C_UINT iDate ) const
{
	C_UINT iStartDate = this->m_StartTime.Get_Date(), iEndDate = this->m_EndTime.Get_Date();

	return ( ( iStartDate <= iDate ) && ( iDate <= iEndDate ) );
}

C_BOOL MediaSpan::Is_Between_Date( C_EZSYSTEMTIME& stTime ) const
{
	C_UINT iDate = stTime.Get_Date();

	return this->Is_Between_Date( iDate );
}

//  ==========================================================================
//  Merge
//  ==========================================================================
void MediaSpan::Merge( const MediaSpan& msTime )
{
	if ( this->m_StartTime > msTime.m_StartTime )
		this->m_StartTime = msTime.m_StartTime;

	if ( this->m_EndTime < msTime.m_EndTime )
		this->m_EndTime = msTime.m_EndTime;
}

//  ==========================================================================
//  Swap
//  ==========================================================================
void MediaSpan::Swap()
{
	if ( this->m_StartTime > this->m_EndTime )
	{
		EZ_SystemTime dtTemp( this->m_StartTime );

		this->m_StartTime = this->m_EndTime;
		this->m_EndTime   = dtTemp;
	}
}
