#pragma once

//  ==========================================================================
//  EZ_ModifyMenuInfo
//  ==========================================================================
struct EZ_ModifyMenuInfo
{
	//  Member
	INT     m_iResID;
	INT     m_iModifyFlag;
	INT     m_iTableID;
	CString m_strXMLNote;

	//  Method
	;
};

typedef const EZ_ModifyMenuInfo  C_EZMODIFYMENUINFO;
typedef       EZ_ModifyMenuInfo* LPEZMODIFYMENUINFO;
typedef const EZ_ModifyMenuInfo* LPCEZMODIFYMENUINFO;

//  ==========================================================================
//  EZ_ModifyMenuFormatInfo
//  ==========================================================================
struct EZ_ModifyMenuFormatInfo
{
	//  Member
	INT     m_iResID;
	INT     m_iModifyFlag;
	INT     m_iTableID;
	CString m_strXMLNote;
	CString m_strExtend;

	//  Method
	;
};

typedef const EZ_ModifyMenuFormatInfo  C_EZMODIFYMENUFTINFO;
typedef       EZ_ModifyMenuFormatInfo* LPEZMODIFYMENUFTINFO;
typedef const EZ_ModifyMenuFormatInfo* LPCEZMODIFYMENUFTINFO;

//  ==========================================================================
//  EZ_ModifyMenuFormatInfoEx
//  ==========================================================================
struct EZ_ModifyMenuFormatInfoEx
{
	//  Member
	INT     m_iResID;
	INT     m_iModifyFlag;
	INT     m_iTableID;
	CString m_strXMLNote;
	CString m_strExtend;
	CString m_strDefault;

	//  Method
	;
};

typedef const EZ_ModifyMenuFormatInfo  C_EZMODIFYMENUFTINFO;
typedef       EZ_ModifyMenuFormatInfo* LPEZMODIFYMENUFTINFO;
typedef const EZ_ModifyMenuFormatInfo* LPCEZMODIFYMENUFTINFO;
