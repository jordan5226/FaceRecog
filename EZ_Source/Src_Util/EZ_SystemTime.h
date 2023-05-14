#pragma once

#include <AfxWin.h>
#include <WinSock2.h>
#include <ATLComTime.h>

#include "EZ_3IntUtil.h"
#include "..\EZWndFun.h"
#include "..\EZDefined.h"
#include "EZ_TemplateVectorArray.h"

//  ==========================================================================
//  
//  ==========================================================================
#if !defined ( EZ_MY_PROJECT )

#ifndef C_INT64
#define C_INT64 const INT64
#endif

#ifndef C_UINT64
#define C_UINT64 const UINT64
#endif

#endif

//  ==========================================================================
//  
//  ==========================================================================
typedef EZ_Vector_Array1 < CString > EZVCSTRINGARRAY;

typedef const EZVCSTRINGARRAY  C_EZVCSTRINGARRAY;
typedef const EZVCSTRINGARRAY* LPEZVCSTRINGARRAY;
typedef const EZVCSTRINGARRAY* LPCEZVCSTRINGARRAY;

typedef EZ_Vector_Array1 < CStringA > EZVCSTRINGAARRAY;

typedef const EZVCSTRINGAARRAY  C_EZVCSTRINGAARRAY;
typedef const EZVCSTRINGAARRAY* LPEZVCSTRINGAARRAY;
typedef const EZVCSTRINGAARRAY* LPCEZVCSTRINGAARRAY;

typedef EZ_Vector_Array1 < CStringW > EZVCSTRINGWARRAY;

typedef const EZVCSTRINGWARRAY  C_EZVCSTRINGWARRAY;
typedef const EZVCSTRINGWARRAY* LPEZVCSTRINGWARRAY;
typedef const EZVCSTRINGWARRAY* LPCEZVCSTRINGWARRAY;

//  ==========================================================================
//  ==========================================================================
//  ============================  用途：存放時間  ============================
//  ==========================================================================
//  ==========================================================================
struct EZ_SystemTime
{
	//  ==========================================================================
	//  
	//  ==========================================================================
	enum FORMAT
	{
		FORMAT_FULL_STRING = 0,	//  Always '20190101000000000'
		FORMAT_FULL_STANDARD,	//  Always '2019/01/01 00:00:00.000'
		FORMAT_FULL_SYSTEM,		//  It will be '2019/01/01 00:00:00.000' or '01/01/2019 00:00:00.000'

		FORMAT_DATE_STRING,		//  Always '20190101'
		FORMAT_DATE_STANDARD,	//  Always '2019/01/01'
		FORMAT_DATE_SYSTEM,		//  It will be '2019/01/01' or '01/01/2019'

		FORMAT_TIME_STRING,		//  Always '000000000'
		FORMAT_TIME_STANDARD,	//  Always '00:00:00.000'
		FORMAT_TIME_SYSTEM,		//  Always '00:00:00.000'
	};

	//  ==========================================================================
	//  Member
	//  ==========================================================================
	SYSTEMTIME m_Time;

	//  ==========================================================================
	//  Constructor, DeConstruction
	//  ==========================================================================
	EZ_SystemTime( __in C_BOOL bGetCurrentTime = FALSE );
	EZ_SystemTime( __in const time_t tTime, __in C_BOOL bCTime = TRUE );

	EZ_SystemTime( __in C_INT iYear, __in C_INT iMonth, __in C_INT iDay );
	EZ_SystemTime( __in C_INT iHour, __in C_INT iMinute, __in C_INT iSecond, __in C_INT iMillisecond );
	EZ_SystemTime( __in C_INT iDate, __in C_INT iHour, __in C_INT iMinute, __in C_INT iSecond, __in C_INT iMillisecond );
	EZ_SystemTime( __in C_INT iYear, __in C_INT iMonth, __in C_INT iDay, __in C_INT iHour, __in C_INT iMinute, __in C_INT iSecond, __in C_INT iMillisecond );

	EZ_SystemTime( __in LPCSTR  lpTime );
	EZ_SystemTime( __in LPCWSTR lpTime );

	EZ_SystemTime( __in const CStringA& strTime );
	EZ_SystemTime( __in const CStringW& strTime );

	EZ_SystemTime( __in const SYSTEMTIME& stTime );
	EZ_SystemTime( __in const SYSTEMTIME* lpTime );

	EZ_SystemTime( __in const struct tm& tmTime );
	EZ_SystemTime( __in const struct tm* lpTime );

	EZ_SystemTime( __in const timeval& tvTime, __in C_BOOL bCTime = TRUE );
	EZ_SystemTime( __in const timeval* lpTime, __in C_BOOL bCTime = TRUE );

	EZ_SystemTime( __in const COleDateTime& oleTime );
	EZ_SystemTime( __in const COleDateTime* lpTime  );

	EZ_SystemTime( __in const EZ_SystemTime& dtTime );
	EZ_SystemTime( __in const EZ_SystemTime* lpTime );

	~EZ_SystemTime();

	//  ==========================================================================
	//  operator =, ==, !=, <, <=, >, >=, -
	//  ==========================================================================
	EZ_SystemTime& operator = ( LPCSTR  lpTime );
	EZ_SystemTime& operator = ( LPCWSTR lpTime );

	EZ_SystemTime& operator = ( const CStringA& strTime );
	EZ_SystemTime& operator = ( const CStringW& strTime );

	EZ_SystemTime& operator = ( const SYSTEMTIME& stTime );
	EZ_SystemTime& operator = ( const SYSTEMTIME* lpTime );

	EZ_SystemTime& operator = ( const struct tm& tmTime );
	EZ_SystemTime& operator = ( const struct tm* lpTime );

	EZ_SystemTime& operator = ( const COleDateTime& oleTime );
	EZ_SystemTime& operator = ( const COleDateTime* lpTime  );

	EZ_SystemTime& operator = ( const EZ_SystemTime& dtTime );
	EZ_SystemTime& operator = ( const EZ_SystemTime* lpTime );

	C_BOOL operator == ( LPCSTR               lpTime  ) const;
	C_BOOL operator == ( LPCWSTR              lpTime  ) const;
	C_BOOL operator == ( const CStringA&      strTime ) const;
	C_BOOL operator == ( const CStringW&      strTime ) const;
	C_BOOL operator == ( const SYSTEMTIME&    stTime  ) const;
	C_BOOL operator == ( const EZ_SystemTime& dtTime  ) const;

	C_BOOL operator != ( LPCSTR               lpTime  ) const;
	C_BOOL operator != ( LPCWSTR              lpTime  ) const;
	C_BOOL operator != ( const CStringA&      strTime ) const;
	C_BOOL operator != ( const CStringW&      strTime ) const;
	C_BOOL operator != ( const SYSTEMTIME&    stTime  ) const;
	C_BOOL operator != ( const EZ_SystemTime& dtTime  ) const;

	C_BOOL operator < ( LPCSTR               lpTime  ) const;
	C_BOOL operator < ( LPCWSTR              lpTime  ) const;
	C_BOOL operator < ( const CStringA&      strTime ) const;
	C_BOOL operator < ( const CStringW&      strTime ) const;
	C_BOOL operator < ( const SYSTEMTIME&    stTime  ) const;
	C_BOOL operator < ( const EZ_SystemTime& dtTime  ) const;

	C_BOOL operator <= ( LPCSTR               lpTime  ) const;
	C_BOOL operator <= ( LPCWSTR              lpTime  ) const;
	C_BOOL operator <= ( const CStringA&      strTime ) const;
	C_BOOL operator <= ( const CStringW&      strTime ) const;
	C_BOOL operator <= ( const SYSTEMTIME&    stTime  ) const;
	C_BOOL operator <= ( const EZ_SystemTime& dtTime  ) const;

	C_BOOL operator > ( LPCSTR               lpTime  ) const;
	C_BOOL operator > ( LPCWSTR              lpTime  ) const;
	C_BOOL operator > ( const CStringA&      strTime ) const;
	C_BOOL operator > ( const CStringW&      strTime ) const;
	C_BOOL operator > ( const SYSTEMTIME&    stTime  ) const;
	C_BOOL operator > ( const EZ_SystemTime& dtTime  ) const;

	C_BOOL operator >= ( LPCSTR               lpTime  ) const;
	C_BOOL operator >= ( LPCWSTR              lpTime  ) const;
	C_BOOL operator >= ( const CStringA&      strTime ) const;
	C_BOOL operator >= ( const CStringW&      strTime ) const;
	C_BOOL operator >= ( const SYSTEMTIME&    stTime  ) const;
	C_BOOL operator >= ( const EZ_SystemTime& dtTime  ) const;

	C_INT operator - ( const CStringA&      strTime ) const;
	C_INT operator - ( const CStringW&      strTime ) const;
	C_INT operator - ( const SYSTEMTIME&    stTime  ) const;
	C_INT operator - ( const COleDateTime&  oleTime ) const;
	C_INT operator - ( const EZ_SystemTime& dtTime  ) const;

	//  ==========================================================================
	//  Set(Get) Date
	//  ==========================================================================
	void Set_Date( __in C_INT iDate );
	void Set_Date( __in C_INT iYear, __in C_INT iMonth, __in C_INT iDay );

	void Set_Date( __in const SYSTEMTIME&    stTime );
	void Set_Date( __in const EZ_SystemTime& dtTime );

	void Set_Date( __in const CStringA& strDate, __in C_BOOL bSlash = FALSE );
	void Set_Date( __in const CStringW& strDate, __in C_BOOL bSlash = FALSE );

	C_UINT Get_Date() const;
	void   Get_Date( __out INT& iYear, __out INT& iMonth, __out INT& iDay ) const;

	void Get_Date( __out SYSTEMTIME&    stTime ) const;
	void Get_Date( __out EZ_SystemTime& dtTime ) const;

	void Get_Date( __out CStringA& strDate, __in C_BOOL bSlash = FALSE ) const;
	void Get_Date( __out CStringW& strDate, __in C_BOOL bSlash = FALSE ) const;

	//  ==========================================================================
	//  Set(Get) Time
	//  ==========================================================================
	void Set_Time( __in C_UINT iTime );
	void Set_Time( __in C_INT iHour, __in C_INT iMiniute, __in C_INT iSecond, __in C_INT iMSec );

	void Set_Time( __in const SYSTEMTIME&    stTime );
	void Set_Time( __in const EZ_SystemTime& dtTime );

	void Set_Time( __in const CStringA& strTime );
	void Set_Time( __in const CStringW& strTime );

	C_UINT Get_Time() const;
	void   Get_Time( __out INT& iHour, __out INT& iMiniute, __out INT& iSecond, __out INT& iMSec ) const;

	void Get_Time( __out SYSTEMTIME&    stTime ) const;
	void Get_Time( __out EZ_SystemTime& dtTime ) const;

	void Get_Time( __out CStringA& strTime ) const;
	void Get_Time( __out CStringW& strTime ) const;

	//  ==========================================================================
	//  Add(Sub) Day, Hour, Minute, Second, MSecond
	//  ==========================================================================
	void Add( __in C_INT iAddHour = 0, __in C_INT iAddMin = 0, __in C_INT iAddSec = 0, __in C_INT iAddMSec = 1 );
	void Add_Day( __in C_INT iValue );
	void Add_Hour( __in C_INT iValue );
	void Add_Minute( __in C_INT iValue );
	void Add_Second( __in C_INT iValue );
	void Add_MSecond( __in INT iValue );
	void Add_Int64_MSecond( __in INT64 iValue );
	void Add_UInt64_MSecond( __in UINT64 iValue );
	
	void Sub( __in C_INT iHour = 0, __in C_INT iMin = 0, __in C_INT iSec = 0, __in C_INT iMSec = 1 );
	void Sub_Day( __in C_INT iValue );
	void Sub_Hour( __in C_INT iValue );
	void Sub_Minute( __in C_INT iValue );
	void Sub_Second( __in C_INT iValue );
	void Sub_MSecond( __in C_INT iValue );
	void Sub_Int64_MSecond( __in C_INT64& iValue );
	void Sub_UInt64_MSecond( __in C_UINT64& iValue );

	//  ==========================================================================
	//  Subtract
	//  ==========================================================================
	LONGLONG Subtract( __in const SYSTEMTIME&    stTime ) const;
	LONGLONG Subtract( __in const EZ_SystemTime& dtTime ) const;

	LONGLONG Subtract( __in const CStringA& strTime ) const;
	LONGLONG Subtract( __in const CStringW& strTime ) const;

	void Subtract( __in const SYSTEMTIME&    stTime, __out COleDateTimeSpan& oleDTSpan ) const;
	void Subtract( __in const EZ_SystemTime& dtTime, __out COleDateTimeSpan& oleDTSpan ) const;

	void Subtract( __in const CStringA& strTime, __out COleDateTimeSpan& oleDTSpan ) const;
	void Subtract( __in const CStringW& strTime, __out COleDateTimeSpan& oleDTSpan ) const;

	//  ==========================================================================
	//  Equal Date(Time)
	//  ==========================================================================
	C_BOOL Is_Equal_Date( __in C_INT iDate ) const;

	C_BOOL Is_Equal_Date( __in const EZ_DATE&       dtDate ) const;
	C_BOOL Is_Equal_Date( __in const SYSTEMTIME&    stDate ) const;
	C_BOOL Is_Equal_Date( __in const EZ_SystemTime& dtDate ) const;

	C_BOOL Is_Equal_Date( __in const CStringA& strDate ) const;
	C_BOOL Is_Equal_Date( __in const CStringW& strDate ) const;

	C_BOOL Is_Equal_Time( __in const EZ_TIME&       dtTime ) const;
	C_BOOL Is_Equal_Time( __in const SYSTEMTIME&    stTime ) const;
	C_BOOL Is_Equal_Time( __in const EZ_SystemTime& dtTime ) const;

	C_BOOL Is_Equal_Time( __in const CStringA& strTime ) const;
	C_BOOL Is_Equal_Time( __in const CStringW& strTime ) const;

	C_BOOL Is_Equal_Time_NoMSec( __in const SYSTEMTIME&    stTime ) const;
	C_BOOL Is_Equal_Time_NoMSec( __in const EZ_SystemTime& dtTime ) const;

	C_BOOL Is_Equal_Time_NoMSec( __in const CStringA& strTime ) const;
	C_BOOL Is_Equal_Time_NoMSec( __in const CStringW& strTime ) const;

	//  ==========================================================================
	//  SystemTime Conveter to String
	//  ==========================================================================
	CString  Time_To_String()  const;
	CStringA Time_To_StringA() const;
	CStringW Time_To_StringW() const;

	CString  Get_Time_String(  __in const CString  strFormat ) const;
	CStringA Get_Time_StringA( __in const CStringA strFormat ) const;
	CStringW Get_Time_StringW( __in const CStringW strFormat ) const;

	void Get_Time_String(  __in const CString  strFormat, __out CString&  strTime ) const;
	void Get_Time_StringA( __in const CStringA strFormat, __out CStringA& strTime ) const;
	void Get_Time_StringW( __in const CStringW strFormat, __out CStringW& strTime ) const;

	//  ==========================================================================
	//  SystemTime Conveter to tm
	//  ==========================================================================
	SYSTEMTIME Get_Full_Time() const;
	void       Get_Full_Time( __out SYSTEMTIME& stTime ) const;
	time_t     Get_Full_Time( __in  C_BOOL      bCTime, __in C_INT iDST = -1 ) const;
	void       Get_Full_Time( __out struct tm&  tmTime, __in C_INT iDST = 0  ) const;

	int Set_Full_Time( __in const time_t   tTime,  __in C_BOOL bCTime = TRUE );
	int Set_Full_Time( __in const timeval& tvTime, __in C_BOOL bCTime = TRUE );

	void Set_Full_Time( __in C_INT             iDate,   __in C_INT iHour, __in C_INT iMinute, __in C_INT iSecond, __in C_INT iMSec );
	void Set_Full_Time( __in const CString&    strDate, __in C_INT iHour, __in C_INT iMinute, __in C_INT iSecond, __in C_INT iMSec );
	void Set_Full_Time( __in const SYSTEMTIME& stDate,  __in C_INT iHour, __in C_INT iMinute, __in C_INT iSecond, __in C_INT iMSec );

	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
	inline operator const SYSTEMTIME& () const { return this->m_Time; }

	inline void Empty() { ::memset( &this->m_Time, 0, sizeof( SYSTEMTIME ) ); }

	inline C_BOOL Is_Empty() const { return ( this->Is_Date_Empty() && this->Is_Time_Empty() ); }

	inline C_BOOL Is_Date_Empty() const { return ( ( this->m_Time.wYear == 0 ) && ( this->m_Time.wMonth  == 0 ) && ( this->m_Time.wDay    == 0 )                                        ); }
	inline C_BOOL Is_Time_Empty() const { return ( ( this->m_Time.wHour == 0 ) && ( this->m_Time.wMinute == 0 ) && ( this->m_Time.wSecond == 0 ) && ( this->m_Time.wMilliseconds == 0 ) ); }

	inline C_BOOL Is_Equal_Full_Time(        __in const SYSTEMTIME& stTime ) const { return ( this->Is_Equal_Date( stTime ) && this->Is_Equal_Time( stTime )        ); }
	inline C_BOOL Is_Equal_Full_Time_NoMSec( __in const SYSTEMTIME& stTime ) const { return ( this->Is_Equal_Date( stTime ) && this->Is_Equal_Time_NoMSec( stTime ) ); }

	inline void Get_Current_Time() { EZ_SystemTime::Get_OS_Time( this->m_Time ); }

	inline CString  Get_String(  __in const EZ_SystemTime::FORMAT iFormat = EZ_SystemTime::FORMAT_FULL_STRING ) const { return EZ_SystemTime::Get_String(  &this->m_Time, iFormat ); }
	inline CStringA Get_StringA( __in const EZ_SystemTime::FORMAT iFormat = EZ_SystemTime::FORMAT_FULL_STRING ) const { return EZ_SystemTime::Get_StringA( &this->m_Time, iFormat ); }
	inline CStringW Get_StringW( __in const EZ_SystemTime::FORMAT iFormat = EZ_SystemTime::FORMAT_FULL_STRING ) const { return EZ_SystemTime::Get_StringW( &this->m_Time, iFormat ); }

	inline void Time_To_String( __out CStringA& strTime ) const	{ EZ_SystemTime::Get_String( &this->m_Time, strTime, EZ_SystemTime::FORMAT_FULL_STRING ); }
	inline void Time_To_String( __out CStringW& strTime ) const	{ EZ_SystemTime::Get_String( &this->m_Time, strTime, EZ_SystemTime::FORMAT_FULL_STRING ); }

	inline C_INT GetDayOfWeek() const	{ return ( COleDateTime( this->m_Time ).GetDayOfWeek() - 1 ); }

	inline void  Set_Year( __in C_INT iYear )	{ this->m_Time.wYear = ( WORD )iYear; }
	inline C_INT Get_Year() const				{ return this->m_Time.wYear;          }

	inline void  Set_Month( __in C_INT iMonth )	{ this->m_Time.wMonth = ( WORD )iMonth; }
	inline C_INT Get_Month() const				{ return this->m_Time.wMonth;           }

	inline void  Set_Day( __in C_INT iDay )	{ this->m_Time.wDay = ( WORD )iDay; }
	inline C_INT Get_Day() const			{ return this->m_Time.wDay;         }

	inline void  Set_Hour( __in C_INT iHour )	{ this->m_Time.wHour = ( WORD )iHour; }
	inline C_INT Get_Hour() const				{ return this->m_Time.wHour;          }

	inline void  Set_Minute( __in C_INT iMinute )	{ this->m_Time.wMinute = ( WORD )iMinute; }
	inline C_INT Get_Minute() const					{ return this->m_Time.wMinute;            }

	inline void  Set_Second( __in C_INT iSecond )	{ this->m_Time.wSecond = ( WORD )iSecond;           }
	inline C_INT Get_Second() const					{ return this->m_Time.wSecond;                      }
	inline C_INT Get_Seconds() const				{ return EZ_SystemTime::GetSeconds( this->m_Time ); }

	inline void  Set_MSecond( __in C_INT iMSecond )	{ this->m_Time.wMilliseconds = ( WORD )iMSecond; }
	inline C_INT Get_MSecond() const				{ return this->m_Time.wMilliseconds;             }

	//  ==========================================================================
	//  Static Function
	//  ==========================================================================
	static void Get_OS_Time( __out SYSTEMTIME&    stNowTime )	{ ::GetLocalTime( &stNowTime ); }
	static void Get_OS_Time( __out EZ_SystemTime& dtNowTime )	{ ::GetLocalTime( &dtNowTime.m_Time ); }

	static EZ_SystemTime Get_OS_Time()	{ EZ_SystemTime stNowTime; ::GetLocalTime( &stNowTime.m_Time ); return stNowTime; }

	static C_INT Get_Date( __in const SYSTEMTIME& stTime )	{ return ( ( stTime.wYear * 10000 ) + ( stTime.wMonth * 100 ) + stTime.wDay ); }

	static void Get_Time( __in LPCSTR  lpTime, __out SYSTEMTIME& stTime );
	static void Get_Time( __in LPCWSTR lpTime, __out SYSTEMTIME& stTime );

	static CString  Get_String(  __in const SYSTEMTIME* lpTime, __in const EZ_SystemTime::FORMAT iFormat = EZ_SystemTime::FORMAT_FULL_STRING );
	static CStringA Get_StringA( __in const SYSTEMTIME* lpTime, __in const EZ_SystemTime::FORMAT iFormat = EZ_SystemTime::FORMAT_FULL_STRING );
	static CStringW Get_StringW( __in const SYSTEMTIME* lpTime, __in const EZ_SystemTime::FORMAT iFormat = EZ_SystemTime::FORMAT_FULL_STRING );

	static void Get_String( __in const SYSTEMTIME* lpTime, __out CStringA& strTime, __in const EZ_SystemTime::FORMAT iFormat = EZ_SystemTime::FORMAT_FULL_STRING );
	static void Get_String( __in const SYSTEMTIME* lpTime, __out CStringW& strTime, __in const EZ_SystemTime::FORMAT iFormat = EZ_SystemTime::FORMAT_FULL_STRING );

	static C_INT GetDays( __in const SYSTEMTIME& stStartTime,  __in const SYSTEMTIME& stEndTime  );
	static C_INT GetDays( __in const CStringA&   strStartTime, __in const CStringA&   strEndTime );
	static C_INT GetDays( __in const CStringW&   strStartTime, __in const CStringW&   strEndTime );

	static C_INT GetMinutes( __in const SYSTEMTIME& stStartTime,  __in const SYSTEMTIME& stEndTime  );
	static C_INT GetMinutes( __in const CStringA&   strStartTime, __in const CStringA&   strEndTime );
	static C_INT GetMinutes( __in const CStringW&   strStartTime, __in const CStringW&   strEndTime );

	static C_INT GetSeconds( __in const SYSTEMTIME& stTime                                          );
	static C_INT GetSeconds( __in const SYSTEMTIME& stStartTime,  __in const SYSTEMTIME& stEndTime  );
	static C_INT GetSeconds( __in const CStringA&   strStartTime, __in const CStringA&   strEndTime );
	static C_INT GetSeconds( __in const CStringW&   strStartTime, __in const CStringW&   strEndTime );

	static void GetSeconds( __in const SYSTEMTIME& stStartTime,  __in const SYSTEMTIME& stEndTime,  __out LONGLONG& llTotalSec );
	static void GetSeconds( __in const CStringA&   strStartTime, __in const CStringA&   strEndTime, __out LONGLONG& llTotalSec );
	static void GetSeconds( __in const CStringW&   strStartTime, __in const CStringW&   strEndTime, __out LONGLONG& llTotalSec );

	static C_INT GetMilliSeconds( __in const SYSTEMTIME& stStartTime,  __in const SYSTEMTIME& stEndTime  );
	static C_INT GetMilliSeconds( __in const CStringA&   strStartTime, __in const CStringA&   strEndTime );
	static C_INT GetMilliSeconds( __in const CStringW&   strStartTime, __in const CStringW&   strEndTime );

	static void GetMilliSeconds( __in const SYSTEMTIME& stStartTime,  __in const SYSTEMTIME& stEndTime,  __out LONGLONG& llTotalMS );
	static void GetMilliSeconds( __in const CStringA&   strStartTime, __in const CStringA&   strEndTime, __out LONGLONG& llTotalMS );
	static void GetMilliSeconds( __in const CStringW&   strStartTime, __in const CStringW&   strEndTime, __out LONGLONG& llTotalMS );

	static void GetOSMonth( __out EZVCSTRINGARRAY& aryMonth );
	static void GetOSWeek(  __out EZVCSTRINGARRAY& aryWeek  );
};

typedef const EZ_SystemTime  C_EZSYSTEMTIME;
typedef       EZ_SystemTime* LPEZSYSTEMTIME;
typedef const EZ_SystemTime* LPCEZSYSTEMTIME;

typedef EZ_Vector_Array1 < EZ_SystemTime > EZSYSTEMTIMEARRAY;

typedef const EZSYSTEMTIMEARRAY  C_EZSYSTEMTIMEARRAY;
typedef const EZSYSTEMTIMEARRAY* LPEZSYSTEMTIMEARRAY;
typedef const EZSYSTEMTIMEARRAY* LPCEZSYSTEMTIMEARRAY;

//  ==========================================================================
//  ==========================================================================
//  =======================  用途：開啟媒體時的資訊用  =======================
//  ==========================================================================
//  ==========================================================================
struct MediaSpan
{
	//  ==========================================================================
	//  Member
	//  ==========================================================================
	EZ_SystemTime m_StartTime;
	EZ_SystemTime m_EndTime;

	//  ==========================================================================
	//  Constructor / DeConstruction
	//  ==========================================================================
	MediaSpan( __in C_BOOL bGetCurrentTime = FALSE );

	MediaSpan( __in const SYSTEMTIME&    stStartTime, __in const SYSTEMTIME&    stEndTime );
	MediaSpan( __in const EZ_SystemTime& dtStartTime, __in const EZ_SystemTime& dtEndTime );
	MediaSpan( __in const struct tm&     tmStartTime, __in const struct tm&     tmEndTime );

	MediaSpan( __in LPCSTR  lpStartTime, __in LPCSTR  lpEndTime );
	MediaSpan( __in LPCWSTR lpStartTime, __in LPCWSTR lpEndTime );

	MediaSpan( __in const CStringA& strStartTime, __in const CStringA& strEndTime );
	MediaSpan( __in const CStringW& strStartTime, __in const CStringW& strEndTime );

	MediaSpan( __in const MediaSpan& msTime );
	MediaSpan( __in const MediaSpan* lpTime );

	~MediaSpan();

	//  ==========================================================================
	//  operator =, ==, !=, <, <=, >, >=
	//  ==========================================================================
	MediaSpan& operator = ( __in const MediaSpan& msTime );
	MediaSpan& operator = ( __in const MediaSpan* lpTime );

	BOOL operator == ( __in const MediaSpan& msTime ) const;
	BOOL operator != ( __in const MediaSpan& msTime ) const;

	//  ==========================================================================
	//  Set(Get) Time
	//  ==========================================================================
	void Set_Time( __in  const SYSTEMTIME& stStartTime, __in  const SYSTEMTIME& stEndTime );
	void Get_Time( __out       SYSTEMTIME& stStartTime, __out       SYSTEMTIME& stEndTime ) const;

	void Set_Time( __in  C_EZSYSTEMTIME& dtStartTime, __in  C_EZSYSTEMTIME& dtEndTime );
	void Get_Time( __out  EZ_SystemTime& dtStartTime, __out  EZ_SystemTime& dtEndTime ) const;

	void Set_Time( __in   const struct tm& tmStartTime, __in  const struct tm& tmEndTime );
	void Get_Time( __out        struct tm& tmStartTime, __out       struct tm& tmEndTime ) const;

	void Set_Time( __in  const CStringA& strStartTime, __in  const CStringA& strEndTime );
	void Set_Time( __in  const CStringW& strStartTime, __in  const CStringW& strEndTime );
	void Get_Time( __out       CStringA& strStartTime, __out       CStringA& strEndTime ) const;
	void Get_Time( __out       CStringW& strStartTime, __out       CStringW& strEndTime ) const;

	//  ==========================================================================
	//  
	//  ==========================================================================
	C_BOOL Is_Between_Date( __in C_UINT          iDate  ) const;
	C_BOOL Is_Between_Date( __in C_EZSYSTEMTIME& stTime ) const;

	void Swap();
	void Merge( __in const MediaSpan& msTime );

	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
	inline void Empty() { this->m_StartTime.Empty(); this->m_EndTime.Empty(); }

	inline C_BOOL Is_Empty() const { return ( this->m_StartTime.Is_Empty() || this->m_EndTime.Is_Empty() ); }

	inline C_BOOL Is_Between_Time( __in C_EZSYSTEMTIME& stTime ) const { return ( ( this->m_StartTime <= stTime ) && ( stTime <= this->m_EndTime ) ); }

	inline C_BOOL Has_Touch( __in const MediaSpan& msTime ) const
	{
		return ( this->Is_Between_Time( msTime.m_StartTime ) || msTime.Is_Between_Time( this->m_StartTime ) ||
				 this->Is_Between_Time( msTime.m_EndTime   ) || msTime.Is_Between_Time( this->m_EndTime   ) );
	}

	inline C_BOOL Has_Touch( __in C_EZSYSTEMTIME& stStartTime, __in C_EZSYSTEMTIME& stEndTime ) const
	{ return ( this->Is_Between_Time( stStartTime ) || this->Is_Between_Time( stEndTime ) ); }

	inline C_BOOL Has_Touch( __in const CStringA& strStartTime, __in const CStringA& strEndTime ) const
	{ return ( this->Is_Between_Time( strStartTime ) || this->Is_Between_Time( strEndTime ) ); }

	inline C_BOOL Has_Touch( __in const CStringW& strStartTime, __in const CStringW& strEndTime ) const
	{ return ( this->Is_Between_Time( strStartTime ) || this->Is_Between_Time( strEndTime ) ); }

	inline C_BOOL Has_Touch_Date( __in const MediaSpan& msTime ) const
	{
		return ( this->Is_Between_Date( msTime.m_StartTime ) || msTime.Is_Between_Date( this->m_StartTime ) ||
				 this->Is_Between_Date( msTime.m_EndTime   ) || msTime.Is_Between_Date( this->m_EndTime   ) );
	}

	inline C_INT Get_Days() const { return EZ_SystemTime::GetDays( this->m_StartTime, this->m_EndTime ); }

	inline C_INT Get_Minutes() const { return EZ_SystemTime::GetMinutes( this->m_StartTime, this->m_EndTime ); }

	inline C_INT Get_Seconds() const { return EZ_SystemTime::GetSeconds( this->m_StartTime, this->m_EndTime ); }

	inline C_INT Get_MilliSeconds() const { return EZ_SystemTime::GetMilliSeconds( this->m_StartTime, this->m_EndTime ); }

	inline void Get_Date( __out INT& iStartDate, __out INT& iEndDate ) const
	{ iStartDate = this->m_StartTime.Get_Date(); iEndDate = this->m_EndTime.Get_Date(); }

	inline void Get_Date( __out CString& strStartDate, __out CString& strEndDate ) const
	{ this->m_StartTime.Get_Date( strStartDate ); this->m_EndTime.Get_Date( strEndDate ); }

	inline void Get_Full_Time( __out SYSTEMTIME& stStartTime, __out SYSTEMTIME& stEndTime ) const
	{ stStartTime = this->m_StartTime.m_Time; stEndTime = this->m_EndTime.m_Time; }

	inline LONGLONG Subtract() const { return this->m_EndTime.Subtract( this->m_StartTime ); }

	inline void Subtract( __out COleDateTimeSpan& oleDTSpan ) const { this->m_EndTime.Subtract( this->m_StartTime, oleDTSpan ); }
};

typedef const MediaSpan  C_MEDIASPAN;
typedef       MediaSpan* LPMEDIASPAN;
typedef const MediaSpan* LPCMEDIASPAN;

typedef EZ_Vector_Array1 < MediaSpan > EZMEDIASPANARRAY;

typedef const EZMEDIASPANARRAY  C_EZMEDIASPANARRAY;
typedef const EZMEDIASPANARRAY* LPEZMEDIASPANARRAY;
typedef const EZMEDIASPANARRAY* LPCEZMEDIASPANARRAY;
