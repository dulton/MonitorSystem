#pragma once

#include "../../Resource.h"

// CPowerNameDlg �Ի���

class CPowerNameDlg : public CDialog
{
	DECLARE_DYNAMIC(CPowerNameDlg)

public:
	CPowerNameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPowerNameDlg();

// �Ի�������
	enum { IDD = IDD_POWERNAMEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_Name;
	void SetName(char *name,char *id);
	void GetName(char *name,char *id);
	CString m_strID;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
};
