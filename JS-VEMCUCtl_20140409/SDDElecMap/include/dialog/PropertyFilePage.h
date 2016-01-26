#pragma once

#include <afxwin.h>
#include "../../Resource.h"

// CPropertyFilePage �Ի���

class CPropertyFilePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropertyFilePage)

public:
	CPropertyFilePage();
	virtual ~CPropertyFilePage();

// �Ի�������
	enum { IDD = IDD_LINKFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listbox;
	//CEdit m_filename;
	//CEdit m_filespecificaton;
	CString m_filename;
	CString m_filespecification;
private:
	void FillListBox(void);

public:
	void Getfile(char* filename,char*ename);
	void Setfile(char *filename,char*ename);
public:
	afx_msg void OnLbnSelchangeList1();
	virtual BOOL OnInitDialog();
	//afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit1();
};
