#pragma once

#include "afxwin.h"
#include "../../resource.h"
// CMcCurveImportDialog �Ի���

class CMcCurveImportDialog : public CDialog
{
	DECLARE_DYNAMIC(CMcCurveImportDialog)

public:
	CMcCurveImportDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMcCurveImportDialog();

// �Ի�������
	enum { IDD = IDD_MCCURVEIMPORTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
public:
	CString strfilepath;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox m_Sectionlist;
	CString m_strSelsection;
	afx_msg void OnLbnSelchangeList1();
	CString m_strinlist;
	LPCTSTR GetSelSection();
	afx_msg void OnLbnDblclkList1();
};
