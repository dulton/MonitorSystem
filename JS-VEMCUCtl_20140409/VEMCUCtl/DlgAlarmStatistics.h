#pragma once
#include "afxcmn.h"


// CDlgAlarmStatistics �Ի���

class CDlgAlarmStatistics : public CDialog
{
	DECLARE_DYNAMIC(CDlgAlarmStatistics)

public:
	CDlgAlarmStatistics(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAlarmStatistics();

// �Ի�������
	enum { IDD = IDD_DIALOG_ALARM_STATISTICS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void InitAlarmStatisticsList();
	afx_msg void OnBnClickedButtonClose();
	void InsertAlarmStatisticsToList(std::vector<ALARM_STATISTICS> vecAlarmStatistics);
	void InitControl();
	CListCtrl m_lstAlarmStatistics;
};
