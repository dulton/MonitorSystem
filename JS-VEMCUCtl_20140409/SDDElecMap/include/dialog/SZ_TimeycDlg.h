#pragma once

#include "../../resource.h"
// CSZ_TimeycDlg �Ի���

class CSZ_TimeycDlg : public CDialog
{
	DECLARE_DYNAMIC(CSZ_TimeycDlg)

public:
	CSZ_TimeycDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSZ_TimeycDlg();

// �Ի�������
	enum { IDD = SZ_TIMEYCDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString m_info;
	char m_cinfo[33];
public:
	virtual BOOL OnInitDialog();
	void SetData(char* newVal);
	void GetData(char* retVal);
	afx_msg void OnBnClickedOk();
};
