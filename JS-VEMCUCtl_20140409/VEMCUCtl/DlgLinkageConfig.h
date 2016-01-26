#pragma once
#include "afxwin.h"


// CDlgLinkageConfig �Ի���

class CDlgLinkageConfig : public CDialog
{
	DECLARE_DYNAMIC(CDlgLinkageConfig)

public:
	CDlgLinkageConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLinkageConfig();

// �Ի�������
	enum { IDD = IDD_DIALOG_LINKAGE_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	void InitComboShowType();
	void InitComboShowVideo();
	void InitComboChangeTime();
	void InitAllCheckBox();
	int GetShowTypeByShowTypeText(char *pShowTypeText);
	void SetControlInfoToLinkageConfig(T_ASS_LINKAGE_CONFIG* pAssLinkageConfig);
	int GetShowVideoByShowVideoTetxt(char *pShowVideoText);
	CComboBox m_comboLinkageShowType;
	CComboBox m_comboShowVideo;
	CComboBox m_comboChangeTime;
	CButton m_checkSecurity;
	CButton m_checkFire;
	CButton m_checkDoorAlarm;
	CButton m_checkDoorAction;
};
