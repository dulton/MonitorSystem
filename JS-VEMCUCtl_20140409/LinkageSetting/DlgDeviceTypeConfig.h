#pragma once
#include "afxcmn.h"
#include <vector>


// CDlgDeviceTypeConfig �Ի���

class CDlgDeviceTypeConfig : public CDialog
{
	DECLARE_DYNAMIC(CDlgDeviceTypeConfig)

public:
	CDlgDeviceTypeConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDeviceTypeConfig();

// �Ի�������
	enum { IDD = IDD_DIALOG_DEVICE_TYPE_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CBitmap* m_pBackBmp;
	CImageList m_imageList;
	CMultiTreeCtrl m_treeDeviceType;
	CMultiTreeCtrl m_treeSubSystem;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void InitControl();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void InitDeviceTypeTree();
	void InitSubSystemTree();
	void AddDeviceTypeToTree(std::vector<T_ASS_DEVICE_TYPE> vecDeviceType);
	void AddSubSystemToTree(std::vector<T_ASS_SUBSYSTEM> vecSubSystem);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
