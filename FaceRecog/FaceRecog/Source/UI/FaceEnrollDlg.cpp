// FaceEnrollDlg.cpp : ��{���
//

#include "stdafx.h"
#include "FaceEnrollDlg.h"
#include "afxdialogex.h"


// FaceEnrollDlg ��ܮ�

IMPLEMENT_DYNAMIC(FaceEnrollDlg, CDialogEx)

FaceEnrollDlg::FaceEnrollDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx( IDD, pParent )
	, m_face_name(_T(""))
{

}

FaceEnrollDlg::~FaceEnrollDlg()
{
}

void FaceEnrollDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FACE_NAME, m_face_name);
}


BEGIN_MESSAGE_MAP(FaceEnrollDlg, CDialogEx)
END_MESSAGE_MAP()


// FaceEnrollDlg �����B�z�{��
