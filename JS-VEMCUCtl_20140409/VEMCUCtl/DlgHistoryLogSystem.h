#pragma once

#include "afxwin.h"
#include "SkinButton.h"
#include "VMListCtrl.h"

// CDlgHistoryLogSystem �Ի���

class CDlgHistoryLogSystem : public CDialog
{
	DECLARE_DYNAMIC(CDlgHistoryLogSystem)

public:
	CDlgHistoryLogSystem(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgHistoryLogSystem();

public:
	BOOL LoadSkin();
	BOOL InitControl();
	BOOL SearchAndSetHistoryListInfo(char *szStartTime,char *szStopTime);

public:
	// ѡ��ڵ�ı���
	CString m_strNodeName;
	// ��ѯ��������ʼʱ��
	CTime m_StartDay;
	// ��ѯ��������ʼʱ��
	CTime m_StartTime;
	// ��ѯ��������������
	CTime m_StopDay;
	// ��ѯ����������ʱ��
	CTime m_StopTime;
	// ��ѯ����ļ��б�
	CVMListCtrl m_ListCtrl_SystemLog;
	// ��������
	CComboBox m_ComboType;
	// �����ȼ�
	CComboBox m_ComboSubType;

	CSkinButton m_btnSelectNode;
	CSkinButton m_btnQuery;

public:
	CBrush m_Brush;

// �Ի�������
	enum { IDD = IDD_DIALOG_HISTORYLOG_SYSTEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButtonHlQuery();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDtnDatetimechangeDatetimepickerHlStartday(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerHlStarttime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerHlStopday(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerHlStoptime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonHlChoosenode();
};
