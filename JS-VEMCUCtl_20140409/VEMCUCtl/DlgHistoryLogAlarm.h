#pragma once
#include "skinbutton.h"
#include "DlgStationSelect.h"
#include "afxdtctl.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "VMListCtrl.h"


// CDlgHistoryLogAlarm �Ի���

class CDlgHistoryLogAlarm : public CDialog
{
	DECLARE_DYNAMIC(CDlgHistoryLogAlarm)

public:
	CDlgHistoryLogAlarm(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgHistoryLogAlarm();

// �Ի�������
	enum { IDD = IDD_DIALOG_HISTORYLOG_ALARM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	_T_NODE_INFO m_tStationNode;//ѡ��ı��վ
public:
	CSkinButton m_btnSelectNode;
	afx_msg void OnBnClickedButtonQuery();
	void SearchAlarmReplayHistoryVideo();
	BOOL InitControlListAlarm();
	void SearchAndAddToListControl(int nStationId, char* strDevName, char* szYear,char* szStartTime,char* szEndTime);
	void UpdateAlarmReplayDeviceCombox(int nStationId);
	CVMListCtrl m_listAlarmLog;
	CTime m_StartDay;
	CTime m_StartTime;
	CTime m_StopDay;
	CTime m_StopTime;
	virtual BOOL OnInitDialog();
	CComboBox m_comboDevice;
	afx_msg void OnBnClickedButtonHlChooseStation();
	void LoadSkin();
	void InitControl();
	CSkinButton m_btnQuery;
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
