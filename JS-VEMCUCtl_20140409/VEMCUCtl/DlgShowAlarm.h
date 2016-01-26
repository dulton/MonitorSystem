#pragma once
#include "EnBitmap.h"

// CDlgShowAlarm �Ի���

class CDlgShowAlarm : public CDialog
{
	DECLARE_DYNAMIC(CDlgShowAlarm)

public:
	CEnBitmap m_Bitmap;
	BITMAP m_Bm;
	HRGN m_hbmpRgn;

public:
	BOOL	m_bMouseIn;
	BOOL	m_bDown;

public:
	CDlgShowAlarm(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgShowAlarm();

// �Ի�������
	enum { IDD = IDD_DIALOG_SHOW_ALARM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
