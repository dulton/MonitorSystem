#pragma once

#include "afxwin.h"
#include "../../resource.h"
// CPowerGzTJSetDlg �Ի���

class CPowerGzTJSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CPowerGzTJSetDlg)

public:
	CPowerGzTJSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPowerGzTJSetDlg();

// �Ի�������
	enum { IDD = IDD_POWERTGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_Check;
	CString m_Ename1;
	CString m_Power1;
	CString m_Power2;
	void SetName(char *s1,char *s2,char *s3,BOOL check);
	void GetName(char *s1,char *s2,char *s3,BOOL *check);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheck1();
	CStatic m_Static;
	CEdit m_Edit;
	CButton m_Btn;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
