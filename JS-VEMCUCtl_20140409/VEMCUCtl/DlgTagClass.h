#pragma once

#include "afxwin.h"
#include "SkinButton.h"


// CDlgTagClass �Ի���

class CDlgTagClass : public CDialog
{
	DECLARE_DYNAMIC(CDlgTagClass)

public:
	CDlgTagClass(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTagClass();

public:
	BOOL LoadSkin();

public:
	CBitmap m_Bmp;

public:
	CSkinButton m_btnModify;
	CSkinButton m_btnCancel;

public:
	HTREEITEM m_hTreeItem;
	CString m_strStationName;
	CString m_strStationNum;
	CString m_strClass;

// �Ի�������
	enum { IDD = IDD_DIALOG_TAG_CLASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnModify();
	afx_msg void OnBnClickedBtnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnNcHitTest(CPoint point);
};
