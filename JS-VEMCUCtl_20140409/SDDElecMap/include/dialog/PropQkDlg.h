#pragma once
#include "../../resource.h"
#include "afxcmn.h"


// CPropQkDlg �Ի���

class CPropQkDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropQkDlg)

public:
	CPropQkDlg();
	virtual ~CPropQkDlg();

// �Ի�������
	enum { IDD = IDD_PROP_QK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	// ����˵��
	CString m_strDes;
	CString m_strName;
public:
	virtual BOOL OnInitDialog();
private:
	void InitColum(void);
	CListCtrl m_ctlList;
	void FillList(void);
public:
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	void GetParam(char* ename, char* des);
	void SetParam(char* ename, char* des);
};
