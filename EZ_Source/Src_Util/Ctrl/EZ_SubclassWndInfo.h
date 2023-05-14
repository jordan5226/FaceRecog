#pragma once

//  ==========================================================================
//  
//  ==========================================================================
#define EZSUBCLASSWNDINFOSIZE sizeof( EZ_SubclassWndInfo )

struct EZ_SubclassWndInfo
{
	//  Defined
	enum CTRL_SHOW
	{
		CMD_DEFAULT = -1,
		CMD_HIDE    = SW_HIDE,
		CMD_SHOW    = SW_SHOW,
	};

	//  Member
	INT                           m_iResID;				//  Resource ID
	INT                           m_iTableID;			//  Table ID
	EZ_SubclassWndInfo::CTRL_SHOW m_iCmdShow;			//  See EZ_SubclassWndInfo::CTRL_SHOW

	CWnd*                         m_pWnd;				//  Window
	TCHAR                         m_tzXMLNote[ 40 ];	//  XML Note

	//  Method
	;
};

typedef const EZ_SubclassWndInfo  C_EZSUBCLASSWNDINFO;
typedef       EZ_SubclassWndInfo* LPEZSUBCLASSWNDINFO;
typedef const EZ_SubclassWndInfo* LPCEZSUBCLASSWNDINFO;

//  ==========================================================================
//  
//  ==========================================================================
#define EZSUBCLASSWNDLINEINFOSIZE sizeof( EZ_SubclassWndLineInfo )

struct EZ_SubclassWndLineInfo
{
	//  Defined
	enum CTRL_TYPE
	{
		TYPE_STATIC = 0,
		TYPE_BUTTON,
		TYPE_CHECK,
		TYPE_SPIN,
		TYPE_EDIT,
		TYPE_COMBO,
		TYPE_DTPIKER,
	};

	//  Member
	INT                               m_iResID;				//  Resource ID
	INT                               m_iTableID;			//  Table ID
	EZ_SubclassWndInfo::CTRL_SHOW     m_iCmdShow;			//  See EZ_SubclassWndInfo::CTRL_SHOW

	CWnd*                             m_pWnd;				//  Window
	TCHAR                             m_tzXMLNote[ 40 ];	//  XML Note

	INT                               m_iPartnerID;			//  
	EZ_SubclassWndLineInfo::CTRL_TYPE m_iType;				//  See EZ_SubclassWndLineInfo::CTRL_TYPE

	//  Method
	;
};

typedef const EZ_SubclassWndLineInfo  C_EZSUBCLASSWNDLINEINFO;
typedef       EZ_SubclassWndLineInfo* LPEZSUBCLASSWNDLINEINFO;
typedef const EZ_SubclassWndLineInfo* LPCEZSUBCLASSWNDLINEINFO;
