#pragma once
//#include "sp_draw.h"
#include "../../resource.h"

// CDlgStationAssistPng �Ի���

class CDlgStationAssistPng : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgStationAssistPng)

public:
	CDlgStationAssistPng(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgStationAssistPng();

public:
	CString m_strPngName;
	float m_fRotateAngle;
	BOOL m_bCheckHorizontalStretch;
	BOOL m_bCheckVerticalStretch;

// �Ի�������
	enum { IDD = IDD_DLG_STATION_ASSIST_PNG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnSelectPng();
	virtual void OnOK();
};
