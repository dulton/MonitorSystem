#pragma once
#include "afxwin.h"

// CDlgPreSet �Ի���

class CDlgPreSet : public CDialog
{
	DECLARE_DYNAMIC(CDlgPreSet)

public:
	CDlgPreSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPreSet();

// �Ի�������
	enum { IDD = IDD_DIALOG_PRESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void DisplayPresetName();

public:
	CComboBox m_Combo_PreSet;
	void OnControlButton(UINT nID);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void OnBnClickedButtonModifyName();
};
