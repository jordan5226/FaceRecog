#pragma once


// FaceEnrollDlg ��ܮ�

class FaceEnrollDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FaceEnrollDlg)

// Attributes
public:
	enum { IDD = IDD_FACEENROLL };

private:
	CString m_face_name;

// Methods
public:
	FaceEnrollDlg(CWnd* pParent = NULL);   // �зǺc�y���
	virtual ~FaceEnrollDlg();

	CString Get_face_name(void)
	{
		return m_face_name;
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ���

	DECLARE_MESSAGE_MAP()

};
