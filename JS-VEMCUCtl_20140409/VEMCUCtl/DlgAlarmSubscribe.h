#pragma once
#include "afxcmn.h"


// CDlgAlarmSubscribe �Ի���

class CDlgAlarmSubscribe : public CDialog
{
	DECLARE_DYNAMIC(CDlgAlarmSubscribe)

public:
	CDlgAlarmSubscribe(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAlarmSubscribe();

// �Ի�������
	enum { IDD = IDD_DIALOG_ALARM_SUBSCRIBE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int CheckStationCurrentStatus2(int nStationId);
	void SetCameraNodeInfo(HTREEITEM hItem, char* ItemName, char* Itemnum, int StationOrCameraID,int ItemStatus,int Streamless,float ItemLongitude, float ItemLatitude, int ItemDecodeTag, int Itemtype, char* stationname);
	void InitAlarmSubscribeList();
	void InitAlarmSubscribeStationTree();
	void InitControl();
	CListCtrl m_lstAlarmSubscribe;
	CTreeCtrl m_treeAlarmSubscribeStation;
	afx_msg void OnBnClickedButtonAlarmSubscribeOk();
	afx_msg void OnBnClickedButtonAlarmSubscribeCancel();
	afx_msg void OnNMClickTreeAlarmSubscribeStation(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemclickListAlarmSubscribe(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListAlarmSubscribe(NMHDR *pNMHDR, LRESULT *pResult);
};
