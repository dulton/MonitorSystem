#pragma once


// CDlgPicFilePath �Ի���

class CDlgPicFilePath : public CDialog
{
	DECLARE_DYNAMIC(CDlgPicFilePath)

public:
	CDlgPicFilePath(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPicFilePath();

public:
	CString m_FilePath;

// �Ի�������
	enum { IDD = IDD_DIALOG_PICFILEPATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedFile();
};
