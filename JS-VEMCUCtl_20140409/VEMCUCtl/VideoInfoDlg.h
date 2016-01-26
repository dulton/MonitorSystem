#pragma once

#include "EnBitmap.h"
#include "VMTypeDataDefine.h"

// CVideoInfoDlg �Ի���

class CVideoInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CVideoInfoDlg)

public:
	CVideoInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVideoInfoDlg();

public:
	BOOL SetVideoInfo(char *pszVideoInfo);
	BOOL SetArrowInfo(int nIndex,int nStartX,int nStartY,int nStopX,int nStopY);
	BOOL SetFontInfo(int nWidth,int nHeight,int nWeight);
	BOOL SetBrushColor(COLORREF color);
	BOOL SetPenInfo(int nWidth,COLORREF color);
	BOOL HideVideoInfo();
	BOOL ShowVideoInfo(int x,int y,bool bFlag=false);
	BOOL ShowArrowLine(CDC *pDC);
	BOOL ShowArrowLineOne(CDC *pDC);
	BOOL ShowArrowLineTwo(CDC *pDC);
	BOOL ClearVideoArrowTextInfo();

public:
	CFont   m_font; 
	CPen    m_pen;
	HBRUSH m_hBrush;
	POINT  m_ptWin;
	char     m_szVideoInfo[256];
	BOOL   m_bVideoInfoShowFlag;
	BOOL   m_bVideoArrowShowFlag;

	//ָʾ��ͷ
	VMArrowLine m_OneArrowLine;
	VMArrowLine m_TwoArrowLine;

// �Ի�������
	enum { IDD = IDD_VIDEO_INFO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};
