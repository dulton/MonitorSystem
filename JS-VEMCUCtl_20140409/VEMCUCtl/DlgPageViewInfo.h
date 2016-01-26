#pragma once

#include "afxwin.h"
#include "Label.h"
#include "SkinButton.h"

//////////////////////////////////////////////////////////////////////////
#define  VIEW_INFO_STATION_TYPE_ALL      1
#define  VIEW_INFO_STATION_TYPE_500KV  2
#define  VIEW_INFO_STATION_TYPE_220KV  3
#define  VIEW_INFO_STATION_TYPE_110KV  4
#define  VIEW_INFO_STATION_TYPE_35KV    5
#define  VIEW_INFO_STATION_TYPE_LINE     6


// CDlgPageViewInfo �Ի���

class CDlgPageViewInfo : public CDialog
{
	DECLARE_DYNAMIC(CDlgPageViewInfo)

public:
	CDlgPageViewInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPageViewInfo();

public:
	BOOL LoadSkin();

public:
	BOOL OpenFirstPageVideo(HTREEITEM hTreeStationItem);
	BOOL SetPageViewOnePageMaxCameraNum(int nNum);

	bool Lock();//����
	bool Unlock();//����
	bool SetPageViewInfo(char *pClientIp,char *pDBServerIp,int nDBServerPort,char *pDBName,char *pDBUserName,char *pDBUserPassword);//��Ա������ֵ
	bool ConnectMySql();	     // �������ݿ�
	bool DisConnectMySql();	// �Ͽ����ݿ�

	int OpenPreStationFirstPage();//����ֵ��-1Ϊû���ҵ���һ��վ�㣬0Ϊ����һ��վ��
	int OpenNextStationFirstPage(); //����ֵ��-1Ϊû���ҵ���һ��վ�㣬0Ϊ����һ��վ��

	void StartAutoVideoPageView();//��ʼ�˹��Զ���ƵѲ��
	void PauseAutoVideoPageView();//��ͣ�˹��Զ���ƵѲ��
	void ResumeAutoVideoPageView();//�����˹��Զ���ƵѲ��
	void StopAutoVideoPageView();//ֹͣ�˹��Զ���ƵѲ��

	BOOL GetStationInfo(int &nAllStationNum,int &nOffStationNum,int nStationType);
	BOOL GetStationCameraInfo(int nStationId,int &nAllCameraNum,int &nProblemCameraNum,int &nStationStatus);//�����ݿ��еõ�ʵʱ��վ���豸������Ϣ
	BOOL GetAndShowOnlineRateReportInfo(char *szTypeName);
	int GetStationNodeInfo(char *szTypeName,int *nNodeId,int nMaxNum,int nLineNodeId);
	int GetLineNodeInfo(char *szTypeName,int *nNodeId,int nMaxNum,int nLineNodeId);
	int GetLineNodeId();

	//////////////////////////////////////////////////////////////////////////
	//����ʷ���еõ�վ���豸��������Ϣ
	int Get500kVStationCameraInfoOnlineCameraNumFromHistory();
	int Get220kVStationCameraInfoOnlineCameraNumFromHistory();
	int Get110kVStationCameraInfoOnlineCameraNumFromHistory();
	int Get35kVStationCameraInfoOnlineCameraNumFromHistory();

	//����ʷ���еõ�վ���豸��������Ϣ,�뱨������Ϣһ��
	int Get500kVStationCameraInfoOnlineCameraNumFromViewHistory();
	int Get220kVStationCameraInfoOnlineCameraNumFromViewHistory();
	int Get110kVStationCameraInfoOnlineCameraNumFromViewHistory();
	int Get35kVStationCameraInfoOnlineCameraNumFromViewHistory();
	//////////////////////////////////////////////////////////////////////////

	BOOL CheckPageViewTickCount();

	BOOL StartDeviceOnlineRateReportInfo(char *szTypeName);
	BOOL StopDeviceOnlineRateReportInfo();

	//////////////////////////////////////////////////////////////////////////
	BOOL GetStationVideoReportCameraStreamlessStatus(int nStationId);
	BOOL GetStationVideoReportStatusCameraDailyInfo(int nUserId,int nStationId,int nYear,int nMonth,int nDay);
	BOOL GetStationVideoReportStatusCameraDailyInfo2(int nUserId,int nStationId,int nYear,int nMonth,int nDay);

	int  JoinStationReportCameraStatus(int nTagStatus,int nLineStatus);
	BOOL StationReportCameraIsOfflineStatus(int nCameraStatus,int nStreamless);

	//�ӵ������ʷ��¼��,�õ�վ���豸��������Ϣ,�뱨������Ϣһ��
	BOOL StatisticsOneStationVideoDailyInfo(int nStationId,int &nCameraCount,int &nOfflineCameraCount,int &nStationStatus);

public:
	CSkinButton m_btnPrePage;
	CSkinButton m_btnNextPage;
	CSkinButton m_btnExportReport;
	CSkinButton m_btnDeviceInfo;
	CSkinButton m_btnOnlineRateInfo;
	CSkinButton m_btnSetTime;
	CSkinButton m_btnPauseVideo;
	CSkinButton m_btnResumeVideo;
	CSkinButton m_btnStopVideo;

	CToolTipCtrl	m_tipTool;

	CBrush m_brush;

public:
	CLabel m_staticStationInfo;
	CLabel m_staticPageInfo;
	HTREEITEM m_hTreeStationItem;
	HTREEITEM m_hTreeCameraItem;
	int m_nPageType;
	int m_nTotalPageNum;
	int m_nCurrentPageIndex;
	int m_nTotalCameraNum;
	int m_nCurrentCameraIndex;
	DWORD m_dwPageViewTickCount;

public:
	bool m_bPageViewInfoInitFlag;
	CRITICAL_SECTION m_csPageViewInfoLock;
	char  m_szClientIp[64];
	char  m_szDBServerIp[64];
	int     m_nDBServerPort;
	char  m_szDBName[256];
	char  m_szDBUserName[256];
	char  m_szDBUserPassword[64];
	MYSQL *m_pMySql;
	bool m_bOnlineRateReportFlag;
	char m_szOnlineRateReportType[64];

	HANDLE m_hDeviceOnlineRateInfoThread;
	UINT m_uDeviceOnlineRateInfoThreadID;
	

// �Ի�������
	enum { IDD = IDD_DIALOG_PAGE_VIEW_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnPrePage();
	afx_msg void OnBnClickedBtnNextPage();
	afx_msg void OnBnClickedButtonSetTime();
	afx_msg void OnBnClickedButtonPauseVideo();
	afx_msg void OnBnClickedButtonResumeVideo();
	afx_msg void OnBnClickedButtonStopVideo();
	afx_msg void OnBnClickedBtnDeviceInfo();
	afx_msg void OnBnClickedBtnOnlineRateInfo();
	afx_msg void OnBnClickedBtnExportReport();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	LRESULT OnDeviceOnlineRateInfoUpdateMessageHandler(WPARAM wParam, LPARAM lParam);
};

//////////////////////////////////////////////////////////////////////////
extern int g_nPageViewOnePageMaxCameraNum;//Ѳ��һҳ�򿪵�����ͷ��

//////////////////////////////////////////////////////////////////////////
unsigned __stdcall _GetAndShowOnlineRateReportInfoThread(void *arg);//�õ�����ʾ������ͳ����Ϣ
