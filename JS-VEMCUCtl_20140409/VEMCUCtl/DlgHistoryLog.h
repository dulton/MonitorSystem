#pragma once

#include "SkinButton.h"
#include "DlgHistoryLogSystem.h"
#include "DlgHistoryLogUser.h"
#include "DlgHistoryLogRelation.h"
#include "DlgHistoryLogVideoError.h"
#include "DlgHistoryLogAlarm.h"
#include "DlgHLDevice.h"
#include "afxwin.h"


// CDlgHistoryLog �Ի���
class CDlgHistoryLog : public CDialog
{
	DECLARE_DYNAMIC(CDlgHistoryLog)

public:
	CDlgHistoryLog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgHistoryLog();

// �Ի�������
	enum { IDD = IDD_DIALOG_HISTORYLOG };

public:
	CDlgHistoryLogRelation m_DlgHlRelation;//��Ƶ������־
	CDlgHistoryLogSystem   m_DlgHlSystem;//ϵͳ������־
	CDlgHistoryLogUser       m_DlgHlUser;//�û�������־
	CDlgHistoryLogVideoError m_DlgHlVideoError;//��Ƶ�����־
	CDlgHistoryLogAlarm m_DlgHlAlarm;//�澯��־
	CDlgHLDevice m_dlgHlDevice;//ǰ����ʷ�澯��־

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CSkinButton	m_btnSelSystem;
	CSkinButton   m_btnSelOperate;
	CSkinButton	m_btnSelRelation;
	CSkinButton   m_btnVideoError;
	CBrush     m_Brush;
	CBitmap   m_UpBmp;
	BITMAP    m_UpBm;

public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonHlSystem();
	afx_msg void OnBnClickedButtonHlOperate();
	afx_msg void OnBnClickedButtonHlRelation();
	afx_msg void OnBnClickedButtonHlVideoError();
	afx_msg void OnBnClickedButtonAlarmHistory();
	afx_msg void OnBnClickedButtonHlDevice();
	void SelectBtnControl(CSkinButton* btn);
	void ShowDialog(int nID);
	CSkinButton m_btnAlarmHistory;
	CSkinButton m_btnDeviceData;
};
