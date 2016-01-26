#pragma once

#include "afxwin.h"
#include "EnBitmap.h"
#include "SkinButton.h"


// CDlgLogin �Ի���

class CDlgLogin : public CDialog
{
	DECLARE_DYNAMIC(CDlgLogin)

public:
	CDlgLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLogin();

public:
	BOOL LoadSkin();
	BOOL SetDlgRgn();

public:
	CEdit m_editUser;
	CEdit m_editPassword;
	CSkinButton m_btnLogIn;
	CSkinButton m_btnCancel;
	CSkinButton m_btnExit;
	CSkinButton m_btnModifyPassword;

public:
	CBrush    m_BgBrush;
	CEnBitmap  m_Bmp;
	BITMAP   m_bm;

public:
	int m_nUserID;
	CString m_Login_UserName;// ��½�û���
	CString m_Login_Password;// ��½����


// �Ի�������
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedLogin();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnNcHitTest(CPoint pt);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnEnChangeEditUser();
	afx_msg void OnEnChangeEditPassword();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedBtnModifyPassword();
	afx_msg void OnBnClickedCancel();
};
