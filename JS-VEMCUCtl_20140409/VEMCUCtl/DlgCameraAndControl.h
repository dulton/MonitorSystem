#pragma once
#include "resource.h"

#include "DlgResizeHelper.h"
#include "afxwin.h"
#include "afxcmn.h"

class CViewChannel;

#define OM_MESSAGE_CAMERA_CONTROL (WM_USER + 301)
// CDlgCameraAndControl �Ի���

class CDlgCameraAndControl : public CDialog
{
	DECLARE_DYNAMIC(CDlgCameraAndControl)

public:
	CDlgCameraAndControl(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCameraAndControl();

// �Ի�������
	enum { IDD = IDD_DIALOG_CAMERA_AND_CONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DlgResizeHelper m_resizeHelper;

	DECLARE_MESSAGE_MAP()
private:
	int m_nOpenCameraId;	//�򿪵���ƵID
	bool m_bOpenFlag;//��ǰ�Ƿ��������ͷ
	ASS_CAMERA_INFO m_tAssCameraInfo;//��Ա����
	int m_nSpeed;//��̨�ٶ�
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void OpenCamera(char *szCameraCode);
	void CloseCamera(int nID);
	void SetCameraOpenStatus(bool bFlag);
	CStatic m_staticCameraWnd;
	afx_msg void OnBnClickedButtonUp();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg LRESULT OnStartYTControl(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT GetAlarmInfoByStationIdHandle(WPARAM wParam,LPARAM lParam);
	afx_msg void OnClickDlgCameraAndControlCloseVideo();
	void ProcessRClickCamera();
	void PopClickCameraRightMenu();
	void SetControlBackgroundColor();
	void InitCtrl();
	CComboBox m_comboSpeed;
	afx_msg void OnCbnSelchangeComboSpeed();
	CViewChannel *m_pViewChannel;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	CString SpellCondition(int nStationId);
	void AddAlarmInfoToList(std::vector<ACS_ALARM_INFO> vecAlarmInfo);
	CListCtrl m_lstAlarm;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
