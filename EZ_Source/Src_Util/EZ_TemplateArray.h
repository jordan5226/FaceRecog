#pragma once

//  ==========================================================================
//  
//  ==========================================================================
#define ARRARY_EXTEND_VALUE 64

//  ==========================================================================
//  
//  ==========================================================================
#if defined ( EZ_MY_PROJECT )

#include "..\EZDefined.h"

#else

#ifndef C_BOOL
#define C_BOOL const BOOL;
#endif

#ifndef C_INT
#define C_INT const INT;
#endif

#ifndef C_UINT
#define C_UINT const UINT;
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE( p ) { if ( p ) { delete p; p = NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY( p ) { if ( p ) { delete [] p; p = NULL; } }
#endif

#endif

//  ==========================================================================
//  
//  ==========================================================================
#if 0
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#endif

//  ==========================================================================
//  �γ~�G�@�� Array ��
//
//  �`�N�ƶ��G1. �ũ���СA�n��i�H�A���ݦۦ�Ѻc����A�b���� RemoveAll �e
//            2. �e�q�����N�|�۰��X�R�A�G�ϥ� GetPointerAt ��Ф��x�s���� ( �]���x�s�Ŷ��|�ܰ� )�C
//               ( ���D�ƥ��ϥ� SetSize ���͸��j�Ŷ��A�Ϩ䤣�| ReCreate Array Space )
//  ==========================================================================
template < class OBJECT, UINT IS_STABLE_SIZE = 0, UINT INITIAL_BUFFER_SIZE = ARRARY_EXTEND_VALUE >

class EZ_Array_Version1
{
private:
	//  ��Ƥj�p ..
	UINT    m_ObjSize;
	//  �ثe�ƶq ..
	UINT    m_Size;
	//  �̤j�e�q ..
	UINT    m_MaxSize;
	//  ��ƩҦb�B ..
	OBJECT* m_pData;
public:
	//  ==========================================================================
	// 
	//  ==========================================================================
	EZ_Array_Version1() : m_ObjSize( sizeof( OBJECT ) ), m_Size( 0 ), m_MaxSize( 0 ), m_pData( NULL )
	{ 
		this->Create_Array_Space( INITIAL_BUFFER_SIZE );
	}
	
	//  ==========================================================================
	// 
	//  ==========================================================================
	EZ_Array_Version1( const EZ_Array_Version1& ezArray ) : m_ObjSize( sizeof( OBJECT ) ), m_Size( 0 ), 
		                                                    m_MaxSize( 0 ), m_pData( NULL )
	{
		*this = ezArray;
	}
	
	//  ==========================================================================
	// 
	//  ==========================================================================
	virtual ~EZ_Array_Version1()
	{ 
		// this->m_OBJECTSize
		this->Release_Array_Space();
	}
	
	//  ==========================================================================
	//  ����ƻs�@�� ..
	//  ==========================================================================
	EZ_Array_Version1& operator = ( const EZ_Array_Version1& ezArray )
	{
		if ( this != &ezArray )
		{
			if ( this->m_MaxSize < ezArray.m_MaxSize ) 
				this->Create_Array_Space( ezArray.m_MaxSize );
			
			if ( IS_STABLE_SIZE == 0 )
			{
				for ( UINT i = 0; i < ezArray.m_Size; i++ )
					this->m_pData[ i ] = ezArray.m_pData[ i ];
			}
			else
			{
				::memcpy( this->m_pData, ezArray.m_pData, ( ezArray.m_Size * this->m_ObjSize ) );
			}
			
			this->m_Size = ezArray.m_Size;
		}
		
		return *this;
	}

	//  ==========================================================================
	//  
	//  ==========================================================================
	EZ_Array_Version1& operator += ( const EZ_Array_Version1& ezArray )
	{
		if ( this != &ezArray )
		{
			for ( UINT i = 0; i < ezArray.m_Size; i++ )
				this->Add( ezArray.GetPointerAt( i ) );
		}
		
		return *this;
	}

	//  ==========================================================================
	//  
	//  ==========================================================================
	BOOL operator != ( const EZ_Array_Version1& ezArray )
	{
		if ( this == &ezArray || ( ( this->m_Size == 0 ) && ( ezArray.m_Size == 0 ) ) )
			return FALSE;

		if ( this->m_Size != ezArray.m_Size )
			return TRUE;
		
		for ( UINT i = 0; i < ezArray.m_Size; i++ )
		{
			if ( this->Linear_Find( ezArray.GetPointerAt( i ) ) < 0 )
				return TRUE;
		}
		
		return FALSE;
	}

	//  ==========================================================================
	//  �إߪŶ� ( Size => �Ŷ��j�p ) ..
	//  ==========================================================================
	BOOL Create_Array_Space( const UINT iSize )
	{
		this->Release_Array_Space();

		this->m_pData   = new OBJECT [ iSize ];
		this->m_Size    = 0;
		this->m_MaxSize = 0;
		
		if ( this->m_pData )
		{
			this->m_MaxSize = iSize;
			return TRUE;
		}

		return FALSE;
	}

	//  ==========================================================================
	//  �R���Ŷ� ..
	//  ==========================================================================
	void Release_Array_Space()
	{
		if ( this->m_pData )
		{
			delete [] this->m_pData;
			this->m_pData = NULL;
		}

		this->m_MaxSize = 0;
		this->m_Size    = 0;
	}

	//  ==========================================================================
	//  �W�[�@����� ..
	//  ==========================================================================
	INT Append( const OBJECT objData )
	{
		ASSERT ( this->m_Size <= this->m_MaxSize );
		
		if ( this->m_Size == this->m_MaxSize )
		{
			if ( !this->Add_Buffer( ARRARY_EXTEND_VALUE ) )
				return -1;
		}
		
		this->m_pData[ this->m_Size ] = objData;
		this->m_Size++;
		
		return ( this->m_Size - 1 );
	}

	//  ==========================================================================
	//  �W�[�@����� ..
	//  ==========================================================================
	INT Add( const OBJECT& objData )
	{
		ASSERT ( this->m_Size <= this->m_MaxSize );
		
		if ( this->m_Size == this->m_MaxSize )
		{
			if ( !this->Add_Buffer( ARRARY_EXTEND_VALUE ) )
				return -1;
		}
		
		this->m_pData[ this->m_Size ] = objData;
		this->m_Size++;
		
		return ( this->m_Size - 1 );
	}
	
	//  ==========================================================================
	//  �W�[�@����� ..
	//  ==========================================================================
	OBJECT* Add( const OBJECT* lpData = NULL )
	{
		if ( this->m_Size >= this->m_MaxSize )
		{
			if ( !this->Add_Buffer( ARRARY_EXTEND_VALUE ) )
				return NULL;
		}
		
		if ( lpData ) 
			this->m_pData[ this->m_Size ] = *lpData;

		this->m_Size++;

		return &this->m_pData[ ( this->m_Size - 1 ) ];
	}

	//  ==========================================================================
	//  �R���Y����� ( Index => �R�����@����� ) ..
	//  ==========================================================================
	BOOL Del( const UINT iIndex )
	{
		ASSERT ( iIndex < this->m_Size );
		
		if ( this->m_Size == 0 )
		{   //  �Ӷê��� ..
			return FALSE;
		}
		else if ( this->m_Size > ( iIndex + 1 ) )
		{   //  �h����� ..
			if ( IS_STABLE_SIZE == 0 )
			{
				for ( UINT i = iIndex; i < ( this->m_Size - 1 ); i++ )
					this->m_pData[ i ] = this->m_pData[ i + 1 ];
			}
			else
			{
				const INT iCopySize = ( this->m_Size - ( iIndex + 1 ) );
				::memmove( &this->m_pData[ iIndex ], &this->m_pData[ ( iIndex + 1 ) ], ( iCopySize * this->m_ObjSize ) );
			}
		}
		
		//  �p�G�O�̧����A�h������@�Y�i ..
		this->m_Size--;

		return TRUE;
	}

	//  ==========================================================================
	//  �R���Y����� ( Value => �R���M Value �ۦP����� ) ..
	//  ==========================================================================
	BOOL DelValue( const OBJECT& objData )
	{
		const INT iResult = this->Linear_Find( objData );
		
		return ( ( iResult >= 0 ) ? this->Del( iResult ) : FALSE );
	}
	
	//  ==========================================================================
	//  ���J�@����� ( Index => ���J�b���@����Ƥ��e, Data => ��� ) ..
	//  ==========================================================================
	OBJECT* InsertBefore( const UINT iIndex, const OBJECT& objData )
	{
		return this->InsertBefore( iIndex, &objData );
	}

	//  ==========================================================================
	//  ���J�@����� ( Index => ���J�b���@����Ƥ��e, Data => ��� ) ..
	//  ==========================================================================
	OBJECT* InsertBefore( const UINT iIndex, const OBJECT* lpData = NULL )
	{
		if ( ( this->m_Size == 0 ) || ( iIndex >= this->m_Size ) )
			return this->Add( lpData );

		if ( this->m_Size >= this->m_MaxSize )
		{
			if ( !this->Add_Buffer( ARRARY_EXTEND_VALUE ) )
				return NULL;
		}

		if ( IS_STABLE_SIZE == 0 )
		{
			for ( INT i = ( INT )( this->m_Size - 1 ); i >= ( INT )iIndex; i-- )
				this->m_pData[ ( i + 1 ) ] = this->m_pData[ i ];
		}
		else
		{
			::memmove( &this->m_pData[ ( iIndex + 1 ) ], &this->m_pData[ iIndex ], ( this->m_ObjSize * ( this->m_Size - iIndex ) ) );
		}

		if ( lpData ) 
			this->m_pData[ iIndex ] = *lpData;

		this->m_Size++;

		return &this->m_pData[ iIndex ];
	}

	//  ==========================================================================
	//  ���J�@����� ( Index => ���J�b���@����Ƥ���, Data => ��� ) ..
	//  ==========================================================================
	OBJECT* InsertAfter( const UINT iIndex, const OBJECT& objData )
	{
		return this->InsertBefore( ( iIndex + 1 ), objData );
	}

	//  ==========================================================================
	//  ���J�@����� ( Index => ���J�b���@����Ƥ���, Data => ��� ) ..
	//  ==========================================================================
	OBJECT* InsertAfter( const UINT iIndex, const OBJECT* lpData = NULL )
	{
		return this->InsertBefore( ( iIndex + 1 ), lpData );
	}
	
	//  ==========================================================================
	//  ��M��� ( Linear Search ) ..
	//  ==========================================================================
	INT Linear_Find( const OBJECT& objData ) const
	{
		for ( UINT i = 0; i < this->m_Size; i++ )
		{
			if ( this->m_pData[ i ] == objData )
				return i;
		}
		
		return -1;
	}

	INT Linear_Find_From_End( const OBJECT& objData ) const
	{
		for ( INT i = ( this->m_Size - 1 ); i >= 0; i-- )
		{
			if ( this->m_pData[ i ] == objData )
				return i;
		}
		
		return -1;
	}

	OBJECT* Linear_Find( OBJECT* lpData ) const
	{
		for ( UINT i = 0; i < this->m_Size; i++ )
		{
			if ( this->m_pData[ i ] == *lpData )
				return &this->m_pData[ i ];
		}
		
		return NULL;
	}

	OBJECT* Linear_Find_From_End( OBJECT* lpData ) const
	{
		for ( INT i = ( this->m_Size - 1 ); i >= 0; i-- )
		{
			if ( this->m_pData[ i ] == *lpData )
				return &this->m_pData[ i ];
		}
		
		return NULL;
	}

	INT Linear_Find_Prev( const OBJECT& objData ) const
	{
		if ( this->m_Size > 0 )
		{
			for ( UINT i = 0; i < this->m_Size; i++ )
			{
				if ( this->m_pData[ i ] == objData )
					return i;
				
				if ( this->m_pData[ i ] > objData )
					return ( ( i == 0 ) ? -1 : ( i - 1 ) );
			}

			return ( this->m_Size - 1 );
		}

		return -1;
	}

	INT Linear_Find_Next( const OBJECT& objData ) const
	{
		if ( this->m_Size > 0 )
		{
			for ( UINT i = 0; i < this->m_Size; i++ )
			{
				if ( this->m_Array[ i ] == objData )
					return i;

				if ( this->m_Array[ i ] > objData )
					return i;
			}
		}

		return -1;
	}

	//  ==========================================================================
	//  ��M��� ( Binary Search ) ..
	//  ==========================================================================
	INT Binary_Find( const OBJECT& objData, const INT iStart = 0, INT iEnd = -1 ) const
	{
		if ( iEnd < 0 ) iEnd = ( this->m_Size - 1 );

		const INT iMiddle = ( ( iStart + iEnd ) >> 1 );

		if ( this->m_pData[ iMiddle ] == objData )
			return iMiddle;

		if ( this->m_pData[ iMiddle ] > objData )
			return ( ( iStart >= iMiddle ) ? -1 : this->Binary_Find( objData, iStart, ( iMiddle - 1 ) ) );

		return ( ( iEnd <= iMiddle ) ? -1 : this->Binary_Find( objData, ( iMiddle + 1 ), iEnd ) );
	}

	OBJECT* Binary_Find( OBJECT* lpData, const INT iStart = 0, INT iEnd = -1 ) const
	{
		if ( iEnd < 0 ) iEnd = ( this->m_Size - 1 );

		const INT iMiddle = ( ( iStart + iEnd ) >> 1 );

		if ( this->m_pData[ iMiddle ] == *lpData )
			return &this->m_pData[ iMiddle ];

		if ( this->m_pData[ iMiddle ] > *lpData )
			return ( ( iStart >= iMiddle ) ? NULL : this->Binary_Find( lpData, iStart, ( iMiddle - 1 ) ) );

		return ( ( iEnd <= iMiddle ) ? NULL : this->Binary_Find( lpData, ( iMiddle + 1 ), iEnd ) );
	}

	//  ==========================================================================
	//  �u�ʱƧ� ( Smaller To Bigger ) ..
	//  ==========================================================================
	BOOL Linear_Sort_S2B()
	{
		if ( this->m_Size <= 1 ) 
			return TRUE;
		
		for ( UINT i = 0, j = 0; i < ( this->m_Size - 1 ); i++ )
		{
			for ( j = ( i + 1 ); j < this->m_Size; j++ )
			{
				if ( this->m_pData[ i ] > this->m_pData[ j ] )
					this->Swap( i, j );
			}
		}
		
		return TRUE;
	}
	
	//  ==========================================================================
	//  �u�ʱƧ� ( Bigger To Smaller ) ..
	//  ==========================================================================
	BOOL Linear_Sort_B2S()
	{
		if ( this->m_Size <= 1 ) 
			return TRUE;
		
		for ( UINT i = 0, j = 0; i < ( this->m_Size - 1 ); i++ )
		{
			for ( j = ( i + 1 ); j < this->m_Size; j++ )
			{
				if ( this->m_pData[ i ] < this->m_pData[ j ] )
					this->Swap( i, j );
			}
		}
		
		return TRUE;
	}

	//  ==========================================================================
	//  ��ƥ洫 ..
	//  ==========================================================================
	void Swap( const INT iNum1, const INT iNum2 )
	{
		OBJECT objTemp         = this->m_pData[ iNum1 ];
		this->m_pData[ iNum1 ] = this->m_pData[ iNum2 ];
		this->m_pData[ iNum2 ] = objTemp;
	}
	
	//  ==========================================================================
	//  
	//  ==========================================================================
	BOOL Is_Different( const EZ_Array_Version1& ezArray ) const
	{
		if ( this->m_Size == ezArray.m_Size )
		{
			for ( UINT i = 0; i < this->m_Size; i++ )
			{
				if ( ezArray.Linear_Find( this->m_pData[ i ] ) < 0 )
					return TRUE;
			}

			return FALSE;
		}

		return TRUE;
	}
private:
	//  ==========================================================================
	//  �X�R�Ŷ� ..
	//  ==========================================================================
	BOOL Add_Buffer( const UINT iAddBufSize )
	{
		//  �s���}�C�j�p ..
		const UINT iNewSize = ( this->m_MaxSize + iAddBufSize );
		
		//  �S����ƮɡA�������Ͱ}�C ..
		if ( 0 == this->m_Size ) 
			return this->Create_Array_Space( iNewSize );
				
		//  �N��Ӫ���ƽƻs�^�h ..
		OBJECT* lpNewData = new OBJECT [ iNewSize ];

		if ( lpNewData )
		{
			if ( IS_STABLE_SIZE == 0 )
			{
				for ( UINT i = 0; i < this->m_Size; i++ )
					lpNewData[ i ] = this->m_pData[ i ];
			}
			else
			{
				::memcpy( lpNewData, this->m_pData, ( this->m_Size * this->m_ObjSize ) );
			}

			delete [] this->m_pData;

			this->m_pData   = lpNewData;
			this->m_MaxSize = iNewSize;
			lpNewData       = NULL;

			return TRUE;
		}

		return FALSE;	
	}
	
	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
public:
	//
	inline BOOL ArrayIsFull() const
	{
		return ( this->m_Size == this->m_MaxSize );
	}

	//  ���o�ثe�x�s�Ŷ��h�� ..
	inline UINT GetSize() const 
	{ 
		return this->m_Size; 
	}

	//  ���o�ثe�̤j�x�s�Ŷ��h�� ..
	inline UINT GetMaxSize() const
	{
		return this->m_MaxSize;
	}

	//  �R��������� ..
	inline void RemoveAll() 
	{ 
		this->m_Size = 0; 
	}

	//  �O�_���Ū� ..
    inline BOOL Is_Empty() const 
	{ 
		return ( this->m_Size == 0 ); 
	}

	//  �]�w��� ..
	inline void SetAt( const UINT iIndex, OBJECT objData ) 
	{ 
		this->m_pData[ iIndex ] = objData; 
	}

	//  ���o��� ..
	inline OBJECT GetAt( const UINT iIndex ) const 
	{ 
		return this->m_pData[ iIndex ]; 
	}

	inline void GetAt( const UINT iIndex, OBJECT& objData ) const 
	{ 
		objData = this->m_pData[ iIndex ]; 
	}

	inline OBJECT* GetPointerAt( const UINT iIndex ) const 
	{ 
		return &this->m_pData[ iIndex ]; 
	}

	//  ���o�_�l��� ..
	inline OBJECT* BeginPointer() const 
	{ 
		return ( ( this->m_Size > 0 ) ? &this->m_pData[ 0 ] : NULL );
	}

	inline BOOL Begin( OBJECT& objData, BOOL bDelete = FALSE )
	{ 
		if ( this->m_Size > 0 )
		{
			objData = this->m_pData[ 0 ];
			
			if ( bDelete ) this->Del( 0 );

			return TRUE;
		}

		return FALSE;
	}

	//  ���o������� ..
	inline OBJECT* EndPointer() const 
	{ 
		return ( ( this->m_Size > 0 ) ? &this->m_pData[ ( this->m_Size - 1 ) ] : NULL );
	}

	inline BOOL End( OBJECT& objData, BOOL bDelete = FALSE )
	{ 
		if ( this->m_Size > 0 )
		{
			objData = this->m_pData[ ( this->m_Size - 1 ) ];
			
			if ( bDelete ) this->Del( ( this->m_Size - 1 ) );

			return TRUE;
		}

		return FALSE;
	}

	//  �]�w�Ŷ��j�p ..
	inline void SetSize( const UINT iNewSize ) 
	{ 
		this->Create_Array_Space( iNewSize ); 
	}
};

//  ==========================================================================
//  �γ~�G�@�� Array ��
//
//  �`�N�ƶ��G1. �ũ���СA�n��i�H�A���ݦۦ�Ѻc����A�b���� RemoveAll
//            2. �e�q�����N�|�۰��X�R�A�G�ϥ� GetPointerAt ��Ф��x�s���� ( �]���x�s�Ŷ��|�ܰ� )�C
//               ( ���D�ƥ��ϥ� SetSize ���͸��j�Ŷ��A�Ϩ䤣�| ReCreate Array Space )
//
//  �ܼƻ����G1. OBJECT              => ���x�s����
//            2. IS_STABLE_SIZE      => ����O�_�O�T�w�j�p�� ( �i�����ϥ� memcopy �����h�� )
//            3. INITIAL_BUFFER_SIZE => Array ��l�j�p
//  ==========================================================================
template < class OBJECT, const UINT IS_STABLE_SIZE = 0, const UINT INITIAL_BUFFER_SIZE = ARRARY_EXTEND_VALUE >

class EZ_Index_Array1
{
private:
	//  Data Size
	UINT    m_ObjSize;
	//  Now Size
	UINT    m_Size;
	//  Max Size
	UINT    m_MaxSize;
	//  Index Array
	UINT*   m_pIndex;
	//  Data
	OBJECT* m_pData;
public:
	//  ==========================================================================
	// 
	//  ==========================================================================
	EZ_Index_Array1() : m_ObjSize( sizeof( OBJECT ) ), m_Size( 0 ),
		                m_MaxSize( 0 ), m_pIndex( NULL ), m_pData( NULL )
	{ 
		this->Create_Array_Space( INITIAL_BUFFER_SIZE );
	}
	
	//  ==========================================================================
	// 
	//  ==========================================================================
	EZ_Index_Array1( const EZ_Index_Array1& ezArray ) : m_ObjSize( sizeof( OBJECT ) ), m_Size( 0 ), 
				                                        m_MaxSize( 0 ), m_pIndex( NULL ), m_pData( NULL )
	{
		*this = ezArray;
	}
	
	//  ==========================================================================
	// 
	//  ==========================================================================
	virtual ~EZ_Index_Array1()
	{ 
		// this->m_ObjSize
		this->Release_Array_Space();
	}
	
	//  ==========================================================================
	//  
	//  ==========================================================================
	EZ_Index_Array1& operator = ( const EZ_Index_Array1& ezArray )
	{
		if ( this != &ezArray )
		{
			if ( this->m_MaxSize < ezArray.m_MaxSize )
			{
				//  Create Buffer
				this->Create_Array_Space( ezArray.m_MaxSize );

				//  Set Index
				::memcpy( this->m_pIndex, ezArray.m_pIndex, ( ezArray.m_MaxSize * sizeof( UINT ) ) );

				//  Copy Data
				if ( IS_STABLE_SIZE == 0 )
				{
					for ( UINT i = 0; i < ezArray.m_Size; i++ )
						this->m_pData[ this->m_pIndex[ i ] ] = ezArray.m_pData[ ezArray.m_pIndex[ i ] ];
				}
				else
					::memcpy( this->m_pData, ezArray.m_pData, ( ezArray.m_MaxSize * this->m_ObjSize ) );
			}
			else
			{
				for ( UINT i = 0; i < ezArray.m_Size; i++ )
					this->m_pData[ this->m_pIndex[ i ] ] = ezArray.m_pData[ ezArray.m_pIndex[ i ] ];
			}

			this->m_Size = ezArray.m_Size;
		}
		
		return *this;
	}

	//  ==========================================================================
	//  
	//  ==========================================================================
	EZ_Index_Array1& operator += ( const EZ_Index_Array1& ezArray )
	{
		if ( this != &ezArray )
		{
			for ( UINT i = 0; i < ezArray.m_Size; i++ )
				this->Add( ezArray.GetPointerAt( i ) );
		}
		
		return *this;
	}

	//  ==========================================================================
	//  
	//  ==========================================================================
	BOOL operator != ( const EZ_Index_Array1& ezArray )
	{
		if ( this == &ezArray || ( ( this->m_Size == 0 ) && ( ezArray.m_Size == 0 ) ) )
			return FALSE;

		if ( this->m_Size != ezArray.m_Size )
			return TRUE;
		
		for ( UINT i = 0; i < ezArray.m_Size; i++ )
		{
			if ( this->Linear_Find( ezArray.GetPointerAt( i ) ) < 0 )
				return TRUE;
		}
		
		return FALSE;
	}
	
	//  ==========================================================================
	//  �إߪŶ� ( Size => �Ŷ��j�p ) ..
	//  ==========================================================================
	BOOL Create_Array_Space( const UINT iSize )
	{
		//  Release Memory
		this->Release_Array_Space();
		
		//  Allocate Memory
		this->m_pIndex = new UINT   [ iSize ];
		this->m_pData  = new OBJECT [ iSize ];

		if ( !this->m_pData || !this->m_pIndex )
		{
			this->Release_Array_Space();
			return FALSE;
		}

		//  Set Data
		this->m_Size    = 0;
		this->m_MaxSize = iSize;

		for ( UINT i = 0; i < this->m_MaxSize; i++ )
			this->m_pIndex[ i ] = i;

		return TRUE;
	}

	//  ==========================================================================
	//  �R���Ŷ� ..
	//  ==========================================================================
	void Release_Array_Space()
	{
		if ( this->m_pIndex )
		{
			delete [] this->m_pIndex;
			this->m_pIndex = NULL;
		}
		
		if ( this->m_pData )
		{
			delete [] this->m_pData;
			this->m_pData = NULL;
		}
		
		this->m_MaxSize = 0;
		this->m_Size    = 0;
	}

	//  ==========================================================================
	//  �W�[�@����� ..
	//  ==========================================================================
	INT Add( const OBJECT& objData )
	{
		ASSERT ( this->m_Size <= this->m_MaxSize );
		
		if ( this->m_Size == this->m_MaxSize )
		{
			if ( !this->Add_Buffer( INITIAL_BUFFER_SIZE ) )
				return -1;
		}
		
		this->m_pData[ this->m_pIndex[ this->m_Size ] ] = objData;
		this->m_Size++;
		
		return ( this->m_Size - 1 );
	}
	
	//  ==========================================================================
	//  �W�[�@����� ..
	//  ==========================================================================
	OBJECT* Add( const OBJECT* lpData )
	{
		return ( lpData ? &this->m_pData[ this->m_pIndex[ this->Add( *lpData ) ] ] : this->Add() );
	}

	//  ==========================================================================
	//  �W�[�@����� ..
	//  ==========================================================================
	OBJECT* Add()
	{
		if ( this->m_Size == this->m_MaxSize )
		{
			if ( !this->Add_Buffer( INITIAL_BUFFER_SIZE ) )
				return NULL;
		}
		
		this->m_Size++;
		return &this->m_pData[ this->m_pIndex[ ( this->m_Size - 1 ) ] ];
	}

	//  ==========================================================================
	//  �R���Y����� ( Index => �R�����@����� ) ..
	//  ==========================================================================
	BOOL Del( const UINT iIndex )
	{
		ASSERT ( iIndex < this->m_Size );
		
		if ( this->m_Size == 0 )
		{   //  �Ӷê��� ..
			return FALSE;
		}
		
		if ( this->m_Size > ( iIndex + 1 ) )
		{   //  �h����� ..
			const UINT iRealIndex = this->m_pIndex[ iIndex ];
			const INT  iCopySize  = ( this->m_Size - ( iIndex + 1 ) );

			::memmove( &this->m_pIndex[ iIndex ], &this->m_pIndex[ ( iIndex + 1 ) ], ( iCopySize * sizeof( UINT ) ) );

			this->m_pIndex[ ( this->m_Size - 1 ) ] = iRealIndex;
		}
		
		//  �p�G�O�̧����A�h������@�Y�i ..
		this->m_Size--;

		return TRUE;
	}

	//  ==========================================================================
	//  �R���Y����� ( Value => �R���M Value �ۦP����� ) ..
	//  ==========================================================================
	BOOL DelValue( const OBJECT& objData )
	{
		const INT iResult = this->Linear_Find( objData );

		return ( ( iResult >= 0 ) ? this->Del( iResult ) : FALSE );
	}

	//  ==========================================================================
	//  ���J�@����� ( Index => ���J�b���@����Ƥ��e ) ..
	//  ==========================================================================
	OBJECT* InsertBefore( const UINT iIndex, const OBJECT& objData )
	{
		return this->InsertBefore( iIndex, &objData );
	}

	//  ==========================================================================
	//  ���J�@����� ( Index => ���J�b���@����Ƥ��e ) ..
	//  ==========================================================================
	OBJECT* InsertBefore( const UINT iIndex, const OBJECT* lpData = NULL )
	{
		//  Don't need to Insert
		if ( ( this->m_Size == 0 ) || ( iIndex >= this->m_Size ) ) 
			return this->Add( lpData );

		//  Create Buffer
		if ( ( this->m_Size + 1 ) > this->m_MaxSize )
		{
			if ( !this->Add_Buffer( INITIAL_BUFFER_SIZE ) )
				return NULL;
		}

		//  Insert
		const INT iLast = this->m_pIndex[ this->m_Size ];
		const INT iSize = ( ( this->m_Size - iIndex ) * sizeof( UINT ) );
		::memmove( ( this->m_pIndex + iIndex + 1 ), ( this->m_pIndex + iIndex ), iSize );
		this->m_pIndex[ iIndex ] = iLast;

		//  Set Data
		this->m_Size++;

		if ( lpData ) this->m_pData[ this->m_pIndex[ iIndex ] ] = *lpData;

        return &this->m_pData[ this->m_pIndex[ iIndex ] ];
	}

	//  ==========================================================================
	//  ���J�@����� ( Index => ���J�b���@����Ƥ���, Data => ��� ) ..
	//  ==========================================================================
	OBJECT* InsertAfter( const UINT iIndex, const OBJECT& objData )
	{
		return this->InsertAfter( iIndex, &objData );
	}

	//  ==========================================================================
	//  ���J�@����� ( Index => ���J�b���@����Ƥ���, Data => ��� ) ..
	//  ==========================================================================
	OBJECT* InsertAfter( const UINT iIndex, const OBJECT* lpData = NULL )
	{
		//  Don't need to Insert
		if ( ( this->m_Size == 0 ) || ( iIndex == ( this->m_Size - 1 ) ) ) 
			return this->Add( lpData );

		//  Create Buffer
		if ( ( this->m_Size + 1 ) > this->m_MaxSize )
		{
			if ( !this->Add_Buffer( INITIAL_BUFFER_SIZE ) )
				return NULL;
		}

		//  Insert
		const INT iIndex = this->m_pIndex[ this->m_Size ];
		const INT iSize  = ( ( this->m_Size - ( iIndex + 1 ) ) * sizeof( UINT ) );
		::memmove( ( this->m_pIndex + iIndex + 2 ), ( this->m_pIndex + iIndex + 1 ), iSize );
		this->m_pIndex[ iIndex + 1 ] = iIndex;

		//  Set Data
		this->m_Size++;

		if ( lpData ) this->m_pData[ this->m_pIndex[ iIndex + 1 ] ] = *lpData;

        return &this->m_pData[ this->m_pIndex[ iIndex + 1 ] ];
	}
	
	//  ==========================================================================
	//  ��M��� ( Linear Search ) ..
	//  ==========================================================================
	INT Linear_Find( const OBJECT& objData ) const
	{
		for ( UINT i = 0; i < this->m_Size; i++ )
		{
			if ( this->m_pData[ this->m_pIndex[ i ] ] == objData )
				return i;
		}
		
		return -1;
	}

	INT Linear_Find_From_End( const OBJECT& objData ) const
	{
		for ( INT i = ( this->m_Size - 1 ); i >= 0; i-- )
		{
			if ( this->m_pData[ this->m_pIndex[ i ] ] == objData )
				return i;
		}
		
		return -1;
	}

	OBJECT* Linear_Find( OBJECT* lpData ) const
	{
		for ( UINT i = 0; i < this->m_Size; i++ )
		{
			if ( this->m_pData[ this->m_pIndex[ i ] ] == *lpData )
				return &this->m_pData[ this->m_pIndex[ i ] ];
		}
		
		return NULL;
	}

	OBJECT* Linear_Find_From_End( OBJECT* lpData ) const
	{
		for ( INT i = ( this->m_Size - 1 ); i >= 0; i-- )
		{
			if ( this->m_pData[ this->m_pIndex[ i ] ] == *lpData )
				return &this->m_pData[ this->m_pIndex[ i ] ];
		}
		
		return NULL;
	}

	INT Linear_Find_Prev( const OBJECT& objData ) const
	{
		if ( this->m_Size > 0 )
		{
			for ( UINT i = 0; i < this->m_Size; i++ )
			{
				if ( this->m_pData[ this->m_pIndex[ i ] ] == objData )
					return this->m_pIndex[ i ];
				
				if ( this->m_pData[ this->m_pIndex[ i ] ] > objData )
					return ( ( i == 0 ) ? -1 : this->m_pIndex[ ( i - 1 ) ] );
			}

			return this->m_pIndex[ ( this->m_Size - 1 ) ];
		}

		return -1;
	}

	//  ==========================================================================
	//  ��M��� ( Binary Search ) ..
	//  ==========================================================================
	INT Binary_Find( const OBJECT& objData, const INT iStart = 0, INT iEnd = -1 ) const
	{
		if ( iEnd < 0 ) iEnd = ( this->m_Size - 1 );

		const INT iMiddle = ( ( iStart + iEnd ) >> 1 );

		if ( this->m_pData[ this->m_pIndex[ iMiddle ] ] == objData )
			return iMiddle;
		
		if ( this->m_pData[ this->m_pIndex[ iMiddle ] ] > objData )
			return ( ( iStart >= iMiddle ) ? -1 : this->Binary_Find( objData, iStart, ( iMiddle - 1 ) ) );

		return ( ( iEnd <= iMiddle ) ? -1 : this->Binary_Find( objData, ( iMiddle + 1 ), iEnd ) );
	}

	OBJECT* Binary_Find( OBJECT* lpData, const INT iStart = 0, INT iEnd = -1 ) const
	{
		if ( iEnd < 0 ) iEnd = ( this->m_Size - 1 );

		const INT iMiddle = ( ( iStart + iEnd ) >> 1 );

		if ( this->m_pData[ this->m_pIndex[ iMiddle ] ] == *lpData )
			return &this->m_pData[ this->m_pIndex[ iMiddle ] ];
		
		if ( this->m_pData[ this->m_pIndex[ iMiddle ] ] > *lpData )
			return ( ( iStart >= iMiddle ) ? NULL : this->Binary_Find( lpData, iStart, ( iMiddle - 1 ) ) );

		return ( ( iEnd <= iMiddle ) ? NULL : this->Binary_Find( lpData, ( iMiddle + 1 ), iEnd ) );
	}

	//  ==========================================================================
	//  �u�ʱƧ� ( Smaller To Bigger ) ..
	//  ==========================================================================
	BOOL Linear_Sort_S2B()
	{
		if ( this->m_Size <= 1 ) return TRUE;
		
		for ( UINT i = 0, j = 0, Temp = 0; i < ( this->m_Size - 1 ); i++ )
		{
			for ( j = ( i + 1 ); j < this->m_Size; j++ )
			{		
				if ( this->m_pData[ this->m_pIndex[ i ] ] > this->m_pData[ this->m_pIndex[ j ] ] )
					this->Swap( i, j );
			}
		}
		
		return TRUE;
	}

	//  ==========================================================================
	//  �u�ʱƧ� ( Bigger To Smaller ) ..
	//  ==========================================================================
	BOOL Linear_Sort_B2S()
	{
		if ( this->m_Size <= 1 ) return TRUE;
		
		for ( UINT i = 0, j = 0, Temp = 0; i < ( this->m_Size - 1 ); i++ )
		{
			for ( j = ( i + 1 ); j < this->m_Size; j++ )
			{		
				if ( this->m_pData[ this->m_pIndex[ i ] ] < this->m_pData[ this->m_pIndex[ j ] ] )
					this->Swap( i, j );
			}
		}
		
		return TRUE;
	}

	//  ==========================================================================
	//  ��ƥ洫 ..
	//  ==========================================================================
	void Swap( const INT iNum1, const INT iNum2 )
	{
		const INT iTemp         = this->m_pIndex[ iNum1 ];
		this->m_pIndex[ iNum1 ] = this->m_pIndex[ iNum2 ];
		this->m_pIndex[ iNum2 ] = iTemp;
	}

	//  ==========================================================================
	//  
	//  ==========================================================================
	BOOL Is_Different( const EZ_Index_Array1& ezArray ) const
	{
		if ( this->m_Size == ezArray.m_Size )
		{
			for ( UINT i = 0; i < this->m_Size; i++ )
			{
				if ( ezArray.Linear_Find( this->m_pData[ this->m_pIndex[ i ] ] ) < 0 )
					return TRUE;
			}

			return FALSE;
		}

		return TRUE;
	}

private:
	//  ==========================================================================
	//  �X�R�Ŷ�
	//  ==========================================================================
	BOOL Add_Buffer( const UINT iBufferSize )
	{
		//  �s���}�C�j�p ..
		const UINT iNewSize = ( this->m_MaxSize + iBufferSize );
		
		//  �S����ƮɡA�������Ͱ}�C ..
		if ( 0 == this->m_Size ) return this->Create_Array_Space( iNewSize );
		
		//  ���ͰO����Ŷ� ..
		UINT*   lpNewIndex = new UINT   [ iNewSize ];
		OBJECT* lpNewData  = new OBJECT [ iNewSize ];
		
		if ( !lpNewIndex || !lpNewData ) 
		{
			if ( lpNewIndex ) 
			{
				delete [] lpNewIndex;
				lpNewIndex = NULL;
			}

			if ( lpNewData )
			{
				delete [] lpNewData;
				lpNewData = NULL;
			}

			return FALSE;
		}

		//  �N��Ӫ����޸�ƽƻs�^�h ..
		::memcpy( lpNewIndex, this->m_pIndex, ( this->m_MaxSize * sizeof( UINT ) ) );

		for ( UINT i = this->m_MaxSize; i < iNewSize; i++ )
			lpNewIndex[ i ] = i;

		//  �N��Ӫ���ƽƻs�^�h ..
		if ( IS_STABLE_SIZE == 0 )
		{
			for ( UINT i = 0; i < this->m_Size; i++ )
				lpNewData[ lpNewIndex[ i ] ] = this->m_pData[ lpNewIndex[ i ] ];
		}
		else
		{
			::memcpy( lpNewData, this->m_pData, ( this->m_MaxSize * this->m_ObjSize ) );
		}
		
		SAFE_DELETE_ARRAY ( this->m_pIndex );
		SAFE_DELETE_ARRAY ( this->m_pData  );

		this->m_pIndex = lpNewIndex;
		this->m_pData  = lpNewData;

		lpNewIndex = NULL;
		lpNewData  = NULL;

		this->m_MaxSize = iNewSize;
		
		return TRUE;
	}
	
	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
public:
	//
	inline BOOL ArrayIsFull() const
	{
		return ( this->m_Size == this->m_MaxSize );
	}

	//  ���o�ثe�x�s�Ŷ��h�� ..
	inline UINT GetSize() const 
	{ 
		return this->m_Size; 
	}

	//  ���o�ثe�̤j�x�s�Ŷ��h�� ..
	inline UINT GetMaxSize() const
	{
		return this->m_MaxSize;
	}

	//  �R��������� ..
	inline void RemoveAll() 
	{ 
		this->m_Size = 0; 
	}

	//  �O�_���Ū� ..
    inline BOOL Is_Empty() const 
	{ 
		return ( this->m_Size == 0 ); 
	}

	//  �]�w��� ..
	inline void SetAt( const UINT iIndex, OBJECT objData ) 
	{ 
		this->m_pData[ this->m_pIndex[ iIndex ] ] = objData; 
	}

	inline void SetAt( const UINT iIndex, const OBJECT* lpData ) 
	{ 
		this->m_pData[ this->m_pIndex[ iIndex ] ] = *lpData; 
	}

	//  ���o��� ..
	inline OBJECT GetAt( const UINT iIndex ) const 
	{ 
		return this->m_pData[ this->m_pIndex[ iIndex ] ]; 
	}

	inline void GetAt( const UINT iIndex, OBJECT& objData ) const 
	{ 
		objData = this->m_pData[ this->m_pIndex[ iIndex ] ]; 
	}

	//  ���o��ƪ����� ..
	inline OBJECT* GetPointerAt( const UINT iIndex ) const 
	{ 
		return &this->m_pData[ this->m_pIndex[ iIndex ] ]; 
	}

	//  ���o�_�l��� ..
	inline OBJECT* BeginPointer() const 
	{ 
		return ( ( this->m_Size > 0 ) ? &this->m_pData[ this->m_pIndex[ 0 ] ] : NULL );
	}

	inline BOOL Begin( OBJECT& objData, BOOL bDelete = FALSE )
	{ 
		if ( this->m_Size > 0 )
		{
			objData = this->m_pData[ this->m_pIndex[ 0 ] ];
			
			if ( bDelete ) this->Del( 0 );

			return TRUE;
		}

		return FALSE;
	}

	//  ���o������� ..
	inline OBJECT* EndPointer() const 
	{ 
		return ( ( this->m_Size > 0 ) ? &this->m_pData[ this->m_pIndex[ ( this->m_Size - 1 ) ] ] : NULL );
	}

	inline BOOL End( OBJECT& objData, BOOL bDelete = FALSE )
	{ 
		if ( this->m_Size > 0 )
		{
			objData = this->m_pData[ this->m_pIndex[ ( this->m_Size - 1 ) ] ];
			
			if ( bDelete ) this->Del( ( this->m_Size - 1 ) );

			return TRUE;
		}

		return FALSE;
	}

	//  �]�w�Ŷ��j�p ..
	inline void SetSize( const UINT iNewSize ) 
	{ 
		this->Create_Array_Space( iNewSize ); 
	}
};
