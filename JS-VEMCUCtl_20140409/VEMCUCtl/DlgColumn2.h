#pragma once


// CDlgColumn2 �Ի���

class CDlgColumn2 : public CDialog
{
	DECLARE_DYNAMIC(CDlgColumn2)

public:
	CDlgColumn2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgColumn2();

// �Ի�������
	enum { IDD = IDD_DIALOG_COLUMN2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
