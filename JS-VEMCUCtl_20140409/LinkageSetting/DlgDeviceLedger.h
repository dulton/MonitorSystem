#pragma once
#include "afxcmn.h"
#include "DlgAddDeviceLedger.h"


// CDlgDeviceLedger �Ի���

class CDlgDeviceLedger : public CDialog
{
	DECLARE_DYNAMIC(CDlgDeviceLedger)
private:
	StationNode* m_pStationNode;
	CBitmap* m_pBackBmp;
	CDlgAddDeviceLedger* m_pAddDeviceLedger;

public:
	CDlgDeviceLedger(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDeviceLedger();

// �Ի�������
	enum { IDD = IDD_DIALOG_DEVICE_LEDGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void SetStationNode(StationNode* pStationNode);
public:
	CTreeCtrl m_treeDeviceList;
	CImageList m_ilTreeIcons;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void InitDeviceList(StationNode* pNodeInfo);
	void ExpandAllItem(CTreeCtrl* pTreeList,HTREEITEM hTreeItem);
	void FreeAllTreeItem(CTreeCtrl* pTreeList,HTREEITEM hTreeItem);
	void SetTreeNodeInfo(CTreeCtrl* pTreeList,HTREEITEM hItem,int nNodeId,int nNodeType,char* szNodeName,int nParentId,char* szNodeCode);
	afx_msg void OnBnClickedButtonAddDevice();
	void FreeDeviceListTree();
	void DeleteDeviceListTreeChildInfo(HTREEITEM hItem);
	afx_msg void OnNMDblclkTreeDeviceList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonEditDevice();
	afx_msg void OnBnClickedButtonDelDevice();
	afx_msg LRESULT OnAddDeviceLedgerCompletedHandler(WPARAM wParam, LPARAM lParam);
	void EmptyEditControl();
	void InitCtrl();
	void InitDeviceLedgerListByStation(StationNode* pNodeInfo);
	CListCtrl m_lstDeviceLedger;
};
