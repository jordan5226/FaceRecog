#pragma once

#ifdef _WINDOWS
#include <AfxWin.h>
#else //  WIN32
#include <Windows.h>
#endif 

//  ==========================================================================
//  
//  ==========================================================================
struct EZ_3DPOINT
{
	int m_X;
	int m_Y;
	int m_Z;
};

typedef const EZ_3DPOINT C_EZ3DPOINT;

//  ==========================================================================
//  
//  ==========================================================================
struct EZ_SIZE
{
	int m_Width;
	int m_Height;
	int m_BitCount;
};

typedef const EZ_SIZE C_EZSIZE;

//  ==========================================================================
//  
//  ==========================================================================
struct EZ_COLOR
{
	int m_R;
	int m_G;
	int m_B;
};

typedef const EZ_COLOR C_EZCOLOR;

//  ==========================================================================
//  
//  ==========================================================================
struct EZ_DATE
{
	int m_Year;
	int m_Month;
	int m_Day;
};

typedef const EZ_DATE C_EZDATE;

//  ==========================================================================
//  
//  ==========================================================================
struct EZ_TIME
{
	int m_Hour;
	int m_Minute;
	int m_Second;
};

typedef const EZ_TIME C_EZTIME;

//  ==========================================================================
//  
//  ==========================================================================
struct EZ_DSTBIAS
{
	int m_Bias;
	int m_StandardBias;
	int m_DaylightBias;
};

typedef const EZ_DSTBIAS C_EZDSTBIAS;

//  ==========================================================================
//  
//  ==========================================================================
struct EZ_CAMERA
{
	int m_DST;
	int m_Audio;
	int m_Number;
};

typedef const EZ_CAMERA  C_EZCAMERA;
typedef       EZ_CAMERA* LPEZCAMERA;
typedef const EZ_CAMERA* LPCEZCAMERA;

//  ==========================================================================
//  
//  ==========================================================================
struct EZ_MESSAGE
{
	int m_Message;
	int m_WParam;
	int m_LParam;
};

typedef const EZ_MESSAGE  C_EZMESSAGE;
typedef       EZ_MESSAGE* LPEZMESSAGE;
typedef const EZ_MESSAGE* LPCEZMESSAGE;

//  ==========================================================================
//  
//  ==========================================================================
struct EZ_3INT
{
	//  Variable
	union 
	{
		EZ_3DPOINT m_3DPoint;
		EZ_SIZE    m_Size;
		EZ_COLOR   m_Color;
		EZ_DATE    m_Date;
		EZ_TIME    m_Time;
		EZ_DSTBIAS m_DSTBias;
		EZ_CAMERA  m_Camera;
		EZ_MESSAGE m_Message;
	};

	//  Member
	EZ_3INT()
	{
		::memset( this, 0, sizeof( EZ_3INT ) );
	}

	~EZ_3INT()
	{
		;
	}

    EZ_3INT& operator = ( const EZ_3DPOINT& ez3DPoint )
	{
		::memcpy( &this->m_3DPoint, &ez3DPoint, sizeof( EZ_3DPOINT ) );

		return *this;
	}

    EZ_3INT& operator = ( const EZ_SIZE& ezSize )
	{
		::memcpy( &this->m_Size, &ezSize, sizeof( EZ_SIZE ) );

		return *this;
	}

    EZ_3INT& operator = ( const EZ_COLOR& ezColor )
	{
		::memcpy( &this->m_Color, &ezColor, sizeof( EZ_COLOR ) );

		return *this;
	}

    EZ_3INT& operator = ( const EZ_DATE& ezDate )
	{
		::memcpy( &this->m_Date, &ezDate, sizeof( EZ_DATE ) );

		return *this;
	}

    EZ_3INT& operator = ( const EZ_TIME& ezTime )
	{
		::memcpy( &this->m_Time, &ezTime, sizeof( EZ_TIME ) );

		return *this;
	}

    EZ_3INT& operator = ( const EZ_DSTBIAS& ezDSTBias )
	{
		::memcpy( &this->m_DSTBias, &ezDSTBias, sizeof( EZ_DSTBIAS ) );

		return *this;
	}

    EZ_3INT& operator = ( const EZ_CAMERA& ezCaemra )
	{
		::memcpy( &this->m_Camera, &ezCaemra, sizeof( EZ_CAMERA ) );

		return *this;
	}

    EZ_3INT& operator = ( const EZ_3INT& EZ3I )
	{
		if ( this != &EZ3I )
			::memcpy( this, &EZ3I, sizeof( EZ_3INT ) );
		return *this;
	}

    BOOL operator == ( const EZ_3INT& EZ3I ) const
	{
		if ( this == &EZ3I )
			return TRUE;

		return ( ( this->m_3DPoint.m_X == EZ3I.m_3DPoint.m_X ) &&
			     ( this->m_3DPoint.m_Y == EZ3I.m_3DPoint.m_Y ) &&
			     ( this->m_3DPoint.m_Z == EZ3I.m_3DPoint.m_Z ) );
	}

	void operator += ( const EZ_3INT& EZ3I )
	{
		if ( this != &EZ3I )
		{
			this->m_3DPoint.m_X += EZ3I.m_3DPoint.m_X;
			this->m_3DPoint.m_Y += EZ3I.m_3DPoint.m_Y;
			this->m_3DPoint.m_Z += EZ3I.m_3DPoint.m_Z;
		}
	}

	void operator -= ( const EZ_3INT& EZ3I )
	{
		if ( this != &EZ3I )
		{
			this->m_3DPoint.m_X -= EZ3I.m_3DPoint.m_X;
			this->m_3DPoint.m_Y -= EZ3I.m_3DPoint.m_Y;
			this->m_3DPoint.m_Z -= EZ3I.m_3DPoint.m_Z;
		}
	}

	void Empty()
	{
		::memset( this, 0, sizeof( EZ_3INT ) );
	}
};

typedef const EZ_3INT  C_EZ3INT;
typedef       EZ_3INT* LPEZ3INT;
typedef const EZ_3INT* LPCEZ3INT;
