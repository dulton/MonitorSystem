#pragma once

#include <afxwin.h>
#include "../../resource.h"
// CSelTicketDlg �Ի���

class CSelTicketDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelTicketDlg)

public:
	CSelTicketDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSelTicketDlg();

// �Ի�������
	enum { IDD = IDD_SELTICKETDLG };

protected:
	char m_TicketName[33];
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void SetTicketName(char* TicketName);
	char* GetTicketName(void);
	virtual BOOL OnInitDialog();
private:
	CComboBox m_TicketNameBox;
public:
	afx_msg void OnBnClickedCreatebutton();
	afx_msg void OnBnClickedOk();

};
