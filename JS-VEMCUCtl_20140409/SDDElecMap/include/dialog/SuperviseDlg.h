#pragma once

#include "../../Resource.h"

// CSuperviseDlg �Ի���

typedef BOOL _stdcall ShowFindDotDlg(int kind,char * ename,char * cname); 

class CSuperviseDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CSuperviseDlg)

public:
	CSuperviseDlg();
	virtual ~CSuperviseDlg();

// �Ի�������
	enum { IDD = IDD_SUPERVISE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strEname;
	void SetProp(CString ename, CString des, bool isAudio);
	void GetProp(char* ename, char* des, bool &isAudio);
	CString m_strDescript;
	afx_msg void OnBnClickedButton1();
};
