#pragma once
#include "../../resource.h"
typedef BOOL _stdcall ShowFindDotDlg(int kind,char * ename,char * cname);

// CPropYxBindDlg �Ի���

class CPropYxBindDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropYxBindDlg)

public:
	CPropYxBindDlg();
	virtual ~CPropYxBindDlg();

// �Ի�������
	enum { IDD = IDD_PROP_YXBIND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString m_strName;
	ShowFindDotDlg *pShowFindDot;

public:
	afx_msg void OnBnClickedButton1();
	void GetParam(char* ename ,char* des);
	void SetParam(char* ename ,char* des) ;
private:
	CString m_strDescript;
};
