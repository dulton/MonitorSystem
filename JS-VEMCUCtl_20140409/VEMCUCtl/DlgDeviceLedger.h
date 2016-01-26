#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "BtnST.h"


// CDlgDeviceLedger �Ի���

class CDlgDeviceLedger : public CDialog
{
	DECLARE_DYNAMIC(CDlgDeviceLedger)

public:
	CDlgDeviceLedger(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDeviceLedger();

// �Ի�������
	enum { IDD = IDD_DIALOG_DEVICE_LEDGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDeviceLedgerQuery();
	virtual BOOL OnInitDialog();
	void InitControl();
	afx_msg void OnBnClickedButtonSelectStation();
	CListCtrl m_lstDeviceLedger;
	afx_msg void OnBnClickedButtonDeviceLedgerExport();
	afx_msg void OnBnClickedButtonDeviceLedgerStatistical();
	void InitStationTree(CTreeCtrl *pTreeCtrl);
	void DeleteCameraChildTreeListInfo(CTreeCtrl *pTreeCtrl, HTREEITEM hItem);
	void DeleteCameraTreeList(CTreeCtrl *pTreeCtrl);
	int CheckStationCurrentStatus2(int nStationId);
	void SetCameraNodeInfo(CTreeCtrl *pTreeCtrl, HTREEITEM hItem, char* ItemName, char* Itemnum, int StationOrCameraID,int ItemStatus,int Streamless,float ItemLongitude, float ItemLatitude, int ItemDecodeTag, int Itemtype, char* stationname);
public:
	CImageList m_imageList;
	_T_NODE_INFO m_tStationNode;//ѡ��ı��վ
	CMultiTreeCtrl m_treeDeviceLedgerStation;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CString GetQueryCondition(std::vector<HTREEITEM> vecSelectedItems);
	void AddDeviceLedgersToList(std::vector<_T_ASS_DEVICE_LEDGER_> vecDeviceLedgers);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CButtonST m_btnDeviceLedger;
};

extern CDlgDeviceLedger *g_pDlgDeviceLedger;