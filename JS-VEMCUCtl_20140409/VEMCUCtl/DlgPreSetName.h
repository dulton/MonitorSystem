#pragma once


// CDlgPreSetName �Ի���

class CDlgPreSetName : public CDialog
{
	DECLARE_DYNAMIC(CDlgPreSetName)

public:
	CDlgPreSetName(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPreSetName();

public:
	CString m_PreSetName;

// �Ի�������
	enum { IDD = IDD_DIALOG_PRESET_NAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedModifyName();
	afx_msg void OnBnClickedDeleteName();
};
