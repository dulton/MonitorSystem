#pragma once


// CDlgColumn1 �Ի���

class CDlgColumn1 : public CDialog
{
	DECLARE_DYNAMIC(CDlgColumn1)

public:
	CDlgColumn1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgColumn1();

// �Ի�������
	enum { IDD = IDD_DIALOG_COLUMN1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
