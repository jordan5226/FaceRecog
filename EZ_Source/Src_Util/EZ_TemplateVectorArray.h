#pragma once

#include <Vector>    //  Vector
#include <Algorithm> //  Sort Function

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
//  
//  ==========================================================================
template < class OBJECT >

class EZ_Vector_Array1
{
protected:
	std::vector < OBJECT > m_aryVector;

public:
	//  ==========================================================================
	// 
	//  ==========================================================================
	EZ_Vector_Array1()
	{
		//  this->m_aryVector
	}

	EZ_Vector_Array1( const EZ_Vector_Array1& aryVector )
	{
		*this = aryVector;
	}

	//  ==========================================================================
	// 
	//  ==========================================================================
	~EZ_Vector_Array1()
	{ 
		//  this->m_aryVector
	}

	//  ==========================================================================
	//  operator =
	//  ==========================================================================
	EZ_Vector_Array1& operator = ( const EZ_Vector_Array1& aryVector )
	{
		if ( this != &aryVector )
		{
			this->RemoveAll();

			*this += aryVector;
		}

		return *this;
	}

	EZ_Vector_Array1& operator = ( LPVOID lpSrcArray )
	{
		if ( lpArray )
		{
			std::vector < OBJECT >* lpVectorAry = ( std::vector < OBJECT >* )lpSrcArray;

			{
				*this = *lpVectorAry;
			}
		}

		return *this;
	}

	//  ==========================================================================
	//  operator +=
	//  ==========================================================================
	EZ_Vector_Array1& operator += ( const EZ_Vector_Array1& aryVector )
	{
		if ( this != &aryVector )
		{
			C_INT iSize = aryVector.GetSize();

			for ( INT i = 0; i < iSize; i++ )
				this->m_aryVector.push_back( aryVector.m_aryVector[ i ] );
		}

		return *this;
	}

	EZ_Vector_Array1& operator += ( LPVOID lpSrcArray )
	{
		if ( lpArray )
		{
			std::vector < OBJECT >* lpVectorAry = ( std::vector < OBJECT >* )lpSrcArray;

			{
				*this += *lpVectorAry;
			}
		}

		return *this;
	}

	//  ==========================================================================
	//  operator -=
	//  ==========================================================================
	EZ_Vector_Array1& operator -= ( const EZ_Vector_Array1& aryVector )
	{
		if ( this != &aryVector )
		{
			for ( INT i = ( aryVector.GetSize() - 1 ), j, iSize; i >= 0; i-- )
			{
				for ( iSize = ( INT )this->m_aryVector.size(), j = 0; j < iSize; j++ )
				{
					if ( aryVector.m_aryVector[ i ] == this->m_aryVector[ j ] )
					{
						this->Del( j );
						break;
					}
				}
			}
		}

		return *this;
	}

	EZ_Vector_Array1& operator -= ( LPVOID lpSrcArray )
	{
		if ( lpArray )
		{
			std::vector < OBJECT >* lpVectorAry = ( std::vector < OBJECT >* )lpSrcArray;

			{
				*this -= *lpVectorAry;
			}
		}

		return *this;
	}

	//  ==========================================================================
	//  operator !=
	//  ==========================================================================
	C_BOOL operator != ( const EZ_Vector_Array1& aryVector )
	{
		return this->Is_Different( aryVector );
	}

	//  ==========================================================================
	//  加入一筆資料 ( .. )
	//  ==========================================================================
	C_INT Add( const OBJECT& dtObject )
	{
		this->m_aryVector.push_back( dtObject );

		return ( INT )( this->m_aryVector.size() - 1 );
	}

	OBJECT* Add( const OBJECT* lpData = NULL )
	{
		this->m_aryVector.push_back( ( lpData ? *lpData : OBJECT() ) );

		return this->EndPointer();
	}

	C_INT Append( const OBJECT& dtObject )
	{
		return this->Add( dtObject );
	}

	OBJECT* Append( const OBJECT* lpData = NULL )
	{
		return this->Add( lpData );
	}

	//  ==========================================================================
	//  加入某筆資料 ( dtObject => 當沒有 dtObject 時加入 )
	//  ==========================================================================
	C_BOOL AddValue( const OBJECT& dtObject )
	{
		C_INT iResult = this->Linear_Find( dtObject );

		return ( ( iResult < 0 ) ? ( this->Add( dtObject ) >= 0 ) : FALSE );
	}

	//  ==========================================================================
	//  加入多筆資料 ( .. )
	//  ==========================================================================
	C_INT AddArray( C_INT iArrayCnt, const OBJECT* lpObjectAry, C_BOOL bFromEnd )
	{
		//
		if ( ( iArrayCnt <= 0 ) || !lpObjectAry )
			return 0;

		//
		INT iCount = 0;

		if ( bFromEnd )
		{
			for ( INT i = ( iArrayCnt - 1 ); i >= 0; i-- )
			{
				if ( this->Add( lpObjectAry[ i ] ) >= 0 )
					iCount++;
			}
		}
		else
		{
			for ( INT i = 0; i < iArrayCnt; i++ )
			{
				if ( this->Add( lpObjectAry[ i ] ) >= 0 )
					iCount++;
			}
		}

		return iCount;
	}

	//  ==========================================================================
	//  移除某筆資料 ( iIndex => 移除哪一筆資料 )
	//  ==========================================================================
	C_BOOL Del( C_UINT iIndex )
	{
		BOOL bResult = TRUE;

		if ( iIndex >= this->GetSize() )
			bResult = FALSE;
		else
			this->m_aryVector.erase( ( this->m_aryVector.begin() + iIndex ) );

		return bResult;
	}

	C_BOOL Remove( C_UINT iIndex )
	{
		return this->Del( iIndex );
	}

	//  ==========================================================================
	//  移除某筆資料 ( dtObject => 移除和 dtObject 相同的資料 )
	//  ==========================================================================
	C_BOOL DelValue( const OBJECT& dtObject )
	{
		C_INT iResult = this->Linear_Find( dtObject );

		return ( ( iResult >= 0 ) ? this->Del( iResult ) : FALSE );
	}

	//  ==========================================================================
	//  刪除某筆資料 ( iIndex => 刪除哪一筆資料 )
	//  ==========================================================================
	C_BOOL Free( C_UINT iIndex )
	{
		OBJECT dtObject = this->GetAt( iIndex );

		if ( dtObject )
		{
			SAFE_DELETE ( dtObject );
		}

		return this->Del( iIndex );
	}

	//  ==========================================================================
	//  移除某筆資料 ( objData => 移除和 objData 相同的資料 )
	//  ==========================================================================
	C_BOOL FreeValue( const OBJECT& dtObject )
	{
		C_INT iResult = this->Linear_Find( dtObject );

		return ( ( iResult >= 0 ) ? this->Free( iResult ) : FALSE );
	}

	//  ==========================================================================
	//  刪除所有資料 ( .. )
	//  ==========================================================================
	void FreeAll()
	{
		C_INT  iSize    = this->GetSize();
		OBJECT dtObject = NULL;

		for ( INT i = 0; i < iSize; i++ )
		{
			dtObject = this->GetAt( i );

			SAFE_DELETE ( dtObject );
		}

		this->RemoveAll();
	}

	//  ==========================================================================
	//  刪除所有陣列資料 ( .. )
	//  ==========================================================================
	void FreeArrayAll()
	{
		C_INT  iSize    = this->GetSize();
		OBJECT dtObject = NULL;

		for ( INT i = 0; i < iSize; i++ )
		{
			dtObject = this->GetAt( i );

			SAFE_DELETE_ARRAY ( dtObject );
		}

		this->RemoveAll();
	}

	//  ==========================================================================
	//  插入某筆資料 ( iIndex => 插入在哪一筆資料之前, lpData / objData => 資料 )
	//  ==========================================================================
	OBJECT* InsertBefore( C_INT iIndex, const OBJECT* lpObject = NULL )
	{
		C_INT iSize = this->GetSize();

		if ( ( iSize == 0 ) || ( iIndex >= iSize ) )
			return this->Add( lpObject );

		this->m_aryVector.insert( ( this->m_aryVector.begin() + iIndex ), ( lpObject ? *lpObject : OBJECT() ) );

		return this->GetPointerAt( iIndex );
	}

	OBJECT* InsertBefore( C_INT iIndex, const OBJECT& dtObject )
	{
		return this->InsertBefore( iIndex, &dtObject );
	}

	OBJECT InsertBefore_Ptr( INT iIndex, const OBJECT dtObject )
	{
		C_INT iSize = this->GetSize();

		if ( ( iSize == 0 ) || ( iIndex >= iSize ) )
			iIndex = this->Add( dtObject );
		else
			this->m_aryVector.insert( ( this->m_aryVector.begin() + iIndex ), dtObject );

		return this->GetAt( iIndex );
	}

	//  ==========================================================================
	//  插入某筆資料 ( iIndex => 插入在哪一筆資料之後, lpData / objData => 資料 )
	//  ==========================================================================
	OBJECT* InsertAfter( C_INT iIndex, const OBJECT* lpObject = NULL )
	{
		return this->InsertBefore( ( iIndex + 1 ), lpObject );
	}

	OBJECT* InsertAfter( C_INT iIndex, const OBJECT& dtObject )
	{
		return this->InsertBefore( ( iIndex + 1 ), dtObject );
	}

	OBJECT InsertAfter_Ptr( C_INT iIndex, const OBJECT dtObject )
	{
		return this->InsertBefore_Ptr( ( iIndex + 1 ), dtObject );
	}

	//  ==========================================================================
	//  找尋資料 ( Linear Search )
	//  ==========================================================================
	C_INT Linear_Find( const OBJECT& dtObject, C_INT iStart = 0 ) const
	{
		C_INT iSize = this->GetSize();

		for ( INT i = iStart; i < iSize; i++ )
		{
			if ( this->m_aryVector[ i ] == dtObject )
				return i;
		}

		return -1;
	}

	C_INT Linear_Find_Ptr( const OBJECT& dtObject, C_INT iStart = 0 ) const
	{
		C_INT iSize = this->GetSize();

		for ( INT i = iStart; i < iSize; i++ )
		{
			if ( *this->m_aryVector[ i ] == *dtObject )
				return i;
		}

		return -1;
	}

	C_INT Linear_Find_From_End( const OBJECT& dtObject ) const
	{
		for ( INT i = ( this->GetSize() - 1 ); i >= 0; i-- )
		{
			if ( this->m_aryVector[ i ] == dtObject )
				return i;
		}

		return -1;
	}

	C_INT Linear_Find_From_End_Ptr( const OBJECT& dtObject ) const
	{
		for ( INT i = ( this->GetSize() - 1 ); i >= 0; i-- )
		{
			if ( *this->m_aryVector[ i ] == *dtObject )
				return i;
		}

		return -1;
	}

	C_INT Linear_Find_Prev( const OBJECT& dtObject ) const
	{
		//  
		C_INT iSize = this->GetSize();

		if ( iSize <= 0 )
			return -1;

		//
		for ( INT i = 0; i < iSize; i++ )
		{
			if ( this->m_aryVector[ i ] == dtObject )
				return i;

			if ( this->m_aryVector[ i ] > dtObject )
				return ( ( i == 0 ) ? -1 : ( i - 1 ) );
		}

		return ( iSize - 1 );
	}

	C_INT Linear_Find_Next( const OBJECT& dtObject ) const
	{
		//  
		C_INT iSize = this->GetSize();

		if ( iSize <= 0 )
			return -1;

		//
		for ( INT i = 0; i < iSize; i++ )
		{
			if ( this->m_aryVector[ i ] == dtObject )
				return i;

			if ( this->m_aryVector[ i ] > dtObject )
				return i;
		}

		return -1;
	}

	OBJECT* Linear_Find( OBJECT* lpObject, INT* lpIndex = NULL ) const
	{
		for ( INT i = 0, iSize = this->GetSize(); i < iSize; i++ )
		{
			if ( this->m_aryVector[ i ] == *lpObject )
			{
				if ( lpIndex )
					*lpIndex = i;

				return ( OBJECT* )&this->m_aryVector[ i ];
			}
		}

		return NULL;
	}

	OBJECT Linear_Find_Ptr( OBJECT* lpObject ) const
	{
		for ( INT i = 0, iSize = this->GetSize(); i < iSize; i++ )
		{
			if ( *this->m_aryVector[ i ] == **lpObject )
				return ( OBJECT )this->m_aryVector[ i ];
		}

		return NULL;
	}

	OBJECT* Linear_Find_From_End( OBJECT* lpObject ) const
	{
		for ( INT i = ( this->GetSize() - 1 ); i >= 0; i-- )
		{
			if ( this->m_aryVector[ i ] == *lpObject )
				return ( OBJECT* )&this->m_aryVector[ i ];
		}

		return NULL;
	}

	//  ==========================================================================
	//  找尋資料 ( Binary Search )
	//  ==========================================================================
	C_INT Binary_Find( const OBJECT& dtObject, C_INT iStart = 0, INT iEnd = -1 ) const
	{
		//  
		if ( iEnd < 0 ) 
			iEnd = ( this->GetSize() - 1 );

		//  
		C_INT iMiddle = ( ( iStart + iEnd ) >> 1 );

		if ( this->m_aryVector[ iMiddle ] == dtObject )
			return iMiddle;

		//  
		if ( this->m_aryVector[ iMiddle ] > dtObject )
			return ( ( iStart >= iMiddle ) ? -1 : this->Binary_Find( dtObject, iStart, ( iMiddle - 1 ) ) );

		//  
		return ( ( iEnd <= iMiddle ) ? -1 : this->Binary_Find( dtObject, ( iMiddle + 1 ), iEnd ) );
	}

	OBJECT* Binary_Find( OBJECT* lpObject, C_INT iStart = 0, INT iEnd = -1 ) const
	{
		//  
		if ( iEnd < 0 ) 
			iEnd = ( this->GetSize() - 1 );

		//  
		C_INT iMiddle = ( ( iStart + iEnd ) >> 1 );

		if ( this->m_aryVector[ iMiddle ] == *lpObject )
			return ( OBJECT* )&this->m_Array[ iMiddle ];

		//  
		if ( this->m_aryVector[ iMiddle ] > *lpObject )
			return ( ( iStart >= iMiddle ) ? NULL : this->Binary_Find( lpObject, iStart, ( iMiddle - 1 ) ) );

		//  
		return ( ( iEnd <= iMiddle ) ? NULL : this->Binary_Find( lpObject, ( iMiddle + 1 ), iEnd ) );
	}

	//  ==========================================================================
	//  取得所有資料的指標
	//  ==========================================================================
	void GetPointerArray( EZ_Vector_Array1 < OBJECT* >& aryVectorPtr )
	{
		//
		aryVectorPtr.RemoveAll();

		//
		OBJECT* lpObject = NULL;

		for ( INT iSize = this->GetSize(), i = 0; i < iSize; i++ )
		{
			lpObject = this->GetPointerAt( i );

			if ( aryVectorPtr.Add( lpObject ) < 0 )
			{
				ASSERT ( 0 );
			}
		}
	}

	//  ==========================================================================
	//  線性排序 ( Smaller To Bigger )
	//  ==========================================================================
	void Linear_Sort_S2B()
	{
		sort( this->m_aryVector.begin(), this->m_aryVector.end(), EZ_Vector_Array1::TemplateVector_SortS2B );
	}

	void Linear_Sort_S2B_Ptr()
	{
		sort( this->m_aryVector.begin(), this->m_aryVector.end(), EZ_Vector_Array1::TemplateVector_SortS2B_Ptr );
	}

	//  ==========================================================================
	//  線性排序 ( Bigger To Smaller )
	//  ==========================================================================
	void Linear_Sort_B2S()
	{
		sort( this->m_aryVector.begin(), this->m_aryVector.end(), EZ_Vector_Array1::TemplateVector_SortB2S );
	}

	void Linear_Sort_B2S_Ptr()
	{
		sort( this->m_aryVector.begin(), this->m_aryVector.end(), EZ_Vector_Array1::TemplateVector_SortB2S_Ptr );
	}

	//  ==========================================================================
	//  資料交換 ( .. )
	//  ==========================================================================
	void Swap( C_INT iIdx1, C_INT iIdx2 )
	{
		OBJECT dtObject            = this->m_aryVector[ iIdx1 ];
		this->m_aryVector[ iIdx1 ] = this->m_aryVector[ iIdx2 ];
		this->m_aryVector[ iIdx2 ] = dtObject;
	}

	//  ==========================================================================
	//  資料是否不同 ( .. )
	//  ==========================================================================
	C_BOOL IsDifferent( const EZ_Vector_Array1& aryVector ) const
	{
		//  
		if ( this == &aryVector )
			return FALSE;

		//
		C_INT iSize = this->GetSize();

		if ( iSize != aryVector.GetSize() )
			return TRUE;

		//
		for ( INT i = 0; i < iSize; i++ )
		{
			if ( aryVector.Linear_Find( this->m_aryVector[ i ] ) < 0 )
				return TRUE;
		}

		return FALSE;
	}

	//  ==========================================================================
	//  Inline Function
	//  ==========================================================================
public: 
	inline void ReSize( C_INT iNowSize )
	{	//  重新配置陣列大小 ( .. )
		this->m_aryVector.resize( iNowSize );
	}

	inline void* GetVectorPointer()
	{	//  取得資料陣列指標 ( .. )
		return &this->m_aryVector;
	}

	inline C_BOOL ArrayIsFull() const
	{	//  資料是否已滿 ( .. )
		return ( this->GetSize() >= this->m_aryVector.capacity() );
	}

	inline C_UINT GetSize() const 
	{	//  取得目前儲存空間多寡 ( .. )
		return ( C_UINT )this->m_aryVector.size(); 
	}

	inline void RemoveAll() 
	{	//  刪除全部資料 ( .. )
		this->m_aryVector.clear();
	}

	inline C_BOOL Is_Empty() const 
	{	//  是否為空的 ( .. )
		return ( C_BOOL )this->m_aryVector.empty(); 
	}

	inline OBJECT* BeginPointer() const 
	{	//  取得起始資料 ( .. )
		return ( ( this->GetSize() > 0 ) ? ( OBJECT* )&this->m_aryVector[ 0 ] : NULL );
	}

	inline OBJECT Begin_Ptr() const 
	{	//  取得起始資料 ( .. )
		return ( ( this->GetSize() > 0 ) ? ( OBJECT )this->m_aryVector[ 0 ] : NULL );
	}

	inline C_BOOL Begin( OBJECT& dtObject, C_BOOL bDelete = FALSE )
	{	//  取得起始資料 ( .. )
		//
		C_INT iSize = this->GetSize();

		if ( iSize <= 0 ) 
			return FALSE;

		//
		dtObject = this->m_aryVector[ 0 ];

		return ( bDelete ? this->Del( 0 ) : TRUE );
	}

	inline OBJECT* EndPointer() const 
	{	//  取得結尾資料 ( .. )
		C_INT iSize = this->GetSize();

		return ( ( iSize > 0 ) ? ( OBJECT* )&this->m_aryVector[ ( iSize - 1 ) ] : NULL );
	}

	inline OBJECT End_Ptr() const 
	{	//  取得結尾資料 ( .. )
		C_INT iSize = this->GetSize();

		return ( ( iSize > 0 ) ? ( OBJECT )this->m_aryVector[ ( iSize - 1 ) ] : NULL );
	}

	inline C_BOOL End( OBJECT& objData, C_BOOL bDelete = FALSE )
	{	//  取得結尾資料 ( .. )
		//  
		C_INT iSize = this->GetSize();

		if ( iSize <= 0 ) 
			return FALSE;

		//  
		objData = this->m_aryVector[ ( iSize - 1 ) ];

		return ( bDelete ? this->Del( ( iSize - 1 ) ) : TRUE );
	}

	inline OBJECT GetAt( C_UINT iIndex ) const 
	{	//  取得資料 ( .. )
		if ( iIndex < this->GetSize() )
			return this->m_aryVector[ iIndex ];
		else
		{
			ASSERT ( 0 );

			return OBJECT();
		}
	}

	inline C_BOOL GetAt( C_UINT iIndex, OBJECT& objData ) const 
	{	//  取得資料 ( .. )
		if ( iIndex < this->GetSize() )
		{
			objData = this->m_aryVector[ iIndex ];

			return TRUE;
		}
		else
		{
			ASSERT ( 0 );

			return FALSE;
		}
	}

	inline OBJECT* GetPointerAt( C_UINT iIndex ) const 
	{	//  取得資料 ( .. )
		if ( iIndex < this->GetSize() )
			return ( OBJECT* )&this->m_aryVector[ iIndex ];
		else
		{
			ASSERT ( 0 );

			return NULL;
		}
	}

	inline OBJECT* GetData() const
	{	//  取得資料 ( .. )
		return ( ( this->GetSize() > 0 ) ? ( OBJECT* )&this->m_aryVector[ 0 ] : NULL );
	}

	inline C_BOOL SetAt( C_UINT iIndex, OBJECT objData ) 
	{	//  設定資料 ( .. )
		if ( iIndex < this->GetSize() )	
		{
			this->m_aryVector[ iIndex ] = objData; 

			return TRUE;
		}
		else
		{
			ASSERT ( 0 );

			return FALSE;
		}
	}

	inline C_BOOL SetAt_Ptr( C_UINT iIndex, OBJECT objData ) 
	{	//  設定資料 ( .. )
		if ( iIndex < this->GetSize() )
		{
			*this->m_aryVector[ iIndex ] = *objData; 

			return TRUE;
		}
		else
		{
			ASSERT ( 0 );

			return FALSE;
		}
	}

	inline C_BOOL SetAt( C_UINT iIndex, const OBJECT* lpData ) 
	{	//  設定資料 ( .. )
		if ( iIndex < this->GetSize() )
		{
			this->m_aryVector[ iIndex ] = *lpData; 

			return TRUE;
		}
		else
		{
			ASSERT ( 0 );

			return FALSE;
		}
	}

	inline C_BOOL DelLast()
	{	//  刪除節尾資料 ( .. )
		C_UINT uiSize = this->GetSize();

		return ( ( uiSize > 0 ) ? this->Del( ( uiSize - 1 ) ) : FALSE );
	}

	//  ==========================================================================
	//  Static Function
	//  ==========================================================================
private:
	static BOOL TemplateVector_SortS2B( OBJECT& dtObject1, OBJECT& dtObject2 )
	{
		return ( dtObject1 < dtObject2 );
	}

	static BOOL TemplateVector_SortS2B_Ptr( OBJECT& dtObject1, OBJECT& dtObject2 )
	{
		return ( *dtObject1 < *dtObject2 );
	}

	static BOOL TemplateVector_SortB2S( OBJECT& dtObject1, OBJECT& dtObject2 )
	{
		return ( dtObject1 > dtObject2 );
	}

	static BOOL TemplateVector_SortB2S_Ptr( OBJECT& dtObject1, OBJECT& dtObject2 )
	{
		return ( *dtObject1 > *dtObject2 );
	}
};

//  ==========================================================================
//  INT Vector Array
//  ==========================================================================
typedef EZ_Vector_Array1 < INT > EZINTVECTORARRAY;

typedef const EZINTVECTORARRAY  C_EZINTVECTORARRAY;
typedef       EZINTVECTORARRAY* LPEZINTVECTORARRAY;
typedef const EZINTVECTORARRAY* LPCEZINTVECTORARRAY;

//  ==========================================================================
//  UINT Vector Array
//  ==========================================================================
typedef EZ_Vector_Array1 < UINT > EZUINTVECTORARRAY;

typedef const EZUINTVECTORARRAY  C_EZUINTVECTORARRAY;
typedef       EZUINTVECTORARRAY* LPEZUINTVECTORARRAY;
typedef const EZUINTVECTORARRAY* LPCEZUINTVECTORARRAY;

//  ==========================================================================
//  HANDLE Vector Array
//  ==========================================================================
typedef EZ_Vector_Array1 < HANDLE > EZHANDLEVECTORARRAY;

typedef const EZHANDLEVECTORARRAY  C_EZHANDLEVECTORARRAY;
typedef       EZHANDLEVECTORARRAY* LPEZHANDLEVECTORARRAY;
typedef const EZHANDLEVECTORARRAY* LPCEZHANDLEVECTORARRAY;

//  ==========================================================================
//  SYSTEMTIME Vector Array
//  ==========================================================================
typedef EZ_Vector_Array1 < SYSTEMTIME > EZSYSTEMTIMEVECTORARRAY;

typedef const EZSYSTEMTIMEVECTORARRAY  C_EZSYSTEMTIMEVECTORARRAY;
typedef       EZSYSTEMTIMEVECTORARRAY* LPEZSYSTEMTIMEVECTORARRAY;
typedef const EZSYSTEMTIMEVECTORARRAY* LPCEZSYSTEMTIMEVECTORARRAY;
