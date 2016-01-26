#pragma once
#include "afxcmn.h"


// CDlgStationSelect �Ի���

class CDlgStationSelect : public CDialog
{
	DECLARE_DYNAMIC(CDlgStationSelect)

public:
	CDlgStationSelect(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgStationSelect();

// �Ի�������
	enum { IDD = IDD_DIALOG_STATION_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	_T_NODE_INFO m_tStationNode;
public:
	afx_msg void OnBnClickedButtonStationSelect();
	virtual BOOL OnInitDialog();
	int CheckStationCurrentStatus2(int nStationId);
	void SetCameraNodeInfo(HTREEITEM hItem, char* ItemName, char* Itemnum, int StationOrCameraID,int ItemStatus,int Streamless,float ItemLongitude, float ItemLatitude, int ItemDecodeTag, int Itemtype, char* stationname);
	void InitStationSelectTree();
	void SetParentWindow(int nParentWindow);
	void UpdateAlarmReplayDeviceCombox(int nStationId);
	void DeleteCameraTreeList();
	void DeleteCameraChildTreeListInfo(HTREEITEM hItem);
	CTreeCtrl m_treeStationSelect;
	int m_nParentWindow;	//0��ʾ�豸̨�˴򿪵ģ�1��ʾ�澯�طŴ򿪵�
};
