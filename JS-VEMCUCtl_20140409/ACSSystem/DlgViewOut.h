#pragma once
#include "afxwin.h"
#include "ViewChannel.h"
#include "label.h"

// CDlgViewOut �Ի���

class CDlgViewOut : public CDialog
{
	DECLARE_DYNAMIC(CDlgViewOut)

public:
	CDlgViewOut(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgViewOut();

	// �Ի�������
	enum { IDD = IDD_DIALOG_VIEW_OUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:
	void DrawSelectedWindowFrame(BOOL bSelected);
	void DrawRect(CDC *pDC,RECT &rect);

public:
	//��Ƶ��ʾ����
	CViewChannel m_ViewChannel;

	//����ID
	int m_nWinID;

	//�Ƿ�ѡ��
	BOOL m_bSelected;

	//����������ͼ
	CBitmap m_titleBk;

	BITMAP m_bmBk;

	//������ˢ
	CBrush m_brush;

	//Camera��Ϣ
	CAMERA_INFO m_camera_info;

	//LoginID
	int m_nLoginID;

	//PlayID
	int m_nPlayID;

	//dvr����
	int m_nDvrType;

	//��Ƶ���ڱ����������������
	CLabel m_strCameraName;

	//�Ƿ�����ƹ�
	BOOL m_bLightRelating;

	//�ƹ������������
	CString  m_strLightCode;
};
