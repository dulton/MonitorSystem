#pragma once

#include "afxwin.h"
#include "SkinButton.h"
#include "VMListCtrl.h"


// CDlgHistoryLogRelation �Ի���

class CDlgHistoryLogRelation : public CDialog
{
	DECLARE_DYNAMIC(CDlgHistoryLogRelation)

public:
	CDlgHistoryLogRelation(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgHistoryLogRelation();

public:
	BOOL LoadSkin();
	BOOL InitControl();
	BOOL SearchAndSetHistoryListInfo(char * szType,char *szStartTime,char *szStopTime);

public:
	// ѡ��ڵ�ı���
	CString m_sChooseNodeName;
	// ��ѯ��������ʼʱ��
	CTime m_StartDay;
	// ��ѯ��������ʼʱ��
	CTime m_StartTime;
	// ��ѯ��������������
	CTime m_StopDay;
	// ��ѯ����������ʱ��
	CTime m_StopTime;
	// ��ѯ����ļ��б�
	CVMListCtrl m_ListCtrl_RelationLog;
	// ��������
	CComboBox m_ComboRelationType;
	// �����ȼ�
	CComboBox m_ComboRelationSubType;

	CSkinButton m_btnSelectNode;
	CSkinButton m_btnQuery;

public:
	CBrush m_Brush;

public:
	// �б�ڵ���Ϣ
	_T_NODE_INFO *m_pNodeInfo;

// �Ի�������
	enum { IDD = IDD_DIALOG_HISTORYLOG_RELATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnBnClickedButtonHlChooseNode();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonHlQuery();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDtnDatetimechangeDatetimepickerHlStartday(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerHlStarttime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerHlStopday(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerHlStoptime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
