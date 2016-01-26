
// SDDElecMapDlg.h : ͷ�ļ�
//

#pragma once
#include "resource.h"
#include "afxcmn.h"

class CElecMapView;
class CElecMapDoc;

class CTreeViewer;
struct tagHMID;
// CSDDElecMapDlg �Ի���
class CSDDElecMapDlg : public CDialog
{
// ����
public:
	CSDDElecMapDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SDDELECMAP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	CElecMapView* getCurrentViewInstance() const;
	CElecMapDoc*  getCurrentDocInstance() const;
	CMultiDocTemplate* m_multiDocTemplate;

public:

	//open a scene map by scene name.
	BOOL openASceneElecMap(const CString& strSceneName);

	//open a scene map by rvu_id, sm_id.
	BOOL openASceneElecMap(const int rvuID, const int smID);

	//set position of the dialog.
	void setDlgPosition(CRect rect);

	//post message to main dialog to open entity referenced video.
	void postMessageToOpenVideo(CString strCameraID);

	//update the entity status and show it.
	//BOOL UpdateTyStatus(const CString strSceneName);
	//BOOL UpdateTyStatus(const CString strSceneName, TYPE_DEVICE typeDevice);

	//update some entity in station
	BOOL	updateEntityInStation( char *pRealData, int nCount );

public:
	CCreateContext context;

private:
	CElecMapView* m_pElecMapView;
	CElecMapDoc*  m_pElecMapDoc;
	
	//��ͼ����Χ
	CRect RectTargetCtrl;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()

public:
	//menu message
	afx_msg void OnSaveMapFile();
	afx_msg void OnOpenMapFile();
};

extern CSDDElecMapDlg* g_pMainDlg;
