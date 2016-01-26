#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "BtnST.h"


// CDlgAlarmPreview �Ի���

class CDlgAlarmPreview : public CDialog
{
	DECLARE_DYNAMIC(CDlgAlarmPreview)

public:
	CDlgAlarmPreview(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAlarmPreview();

// �Ի�������
	enum { IDD = IDD_DIALOG_ALARM_PREVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonQuery();
	void InitControl();
	void InitStationtree();
	afx_msg void OnNMDblclkListAlarm(NMHDR *pNMHDR, LRESULT *pResult);
	void InitAlarmListColumnAndWidth();
	CString GetQueryCondition(std::vector<HTREEITEM> vecSelectedItems);
	void AddStationAlarmToList(std::vector<_T_ASS_SUBSYSTEM_ALARM_COUNT> vecSubSystemAlarmCount);
	//�����Ҽ��˵�
	void PopRightMenu();
	afx_msg void OnClickViewDetail();//�鿴��ϸ
	afx_msg void OnClickProcessAll();//����ȫ��
	CButtonST m_btnQuery;
	CListCtrl m_lstAlarm;
	CMultiTreeCtrl m_treeStation;
	afx_msg void OnNMRClickListAlarm(NMHDR *pNMHDR, LRESULT *pResult);
private:
	int m_nStationId;
	CImageList m_imageList;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
};
