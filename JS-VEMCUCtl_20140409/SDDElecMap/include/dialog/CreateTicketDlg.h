#pragma once
#include "afxwin.h"
#include "../../resource.h"
// CCreateTicketDlg �Ի���

class CCreateTicketDlg : public CDialog
{
	DECLARE_DYNAMIC(CCreateTicketDlg)

public:
	CCreateTicketDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCreateTicketDlg();

// �Ի�������
	enum { IDD = IDD_CREATETICKETDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	CComboBox m_TemplateBox;
	CComboBox m_ObjectBox;
	CString m_TicketName;
public:
	CString GetTicketName(void);
	BOOL TestTemplateAndObjects(void);
	void CreateTicket(void);
	afx_msg void OnBnClickedOk();
};
