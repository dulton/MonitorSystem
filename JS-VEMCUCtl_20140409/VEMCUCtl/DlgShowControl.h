#pragma once

#include "EnBitmap.h"


// CDlgShowControl �Ի���

class CDlgShowControl : public CDialog
{
	DECLARE_DYNAMIC(CDlgShowControl)

public:
	CDlgShowControl(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgShowControl();


public:
	CEnBitmap m_Bitmap;
	BITMAP m_Bm;
	HRGN m_hbmpRgn;

public:
	BOOL	m_bMouseIn;
	BOOL	m_bDown;

// �Ի�������
	enum { IDD = IDD_DIALOG_SHOW_CONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
