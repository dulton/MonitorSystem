
// VEMCUCtlDlg.h : ͷ�ļ�
//
#pragma once

#include "DlgMenu.h"				// �˵�����
#include "DlgLogin.h"
#include "DlgPageServer.h"
#include "DlgViewOut.h"
#include "DlgRecFilePath.h"
#include "DlgPicFilePath.h"
#include "DlgReplay.h"
#include "DlgHistoryLog.h"
#include "DlgSelectDevice.h"
#include "DlgShowControl.h"
#include "DlgShowPageServer.h"
#include "DlgLinkageServer.h"
#include "DlgShowLinkageServer.h"
#include "DlgPageViewInfo.h"
#include "DlgDeviceOnlineInfo.h"
#include "VideoTagInfoDlg.h"
#include "DlgAlarmInfo.h"
#include "DlgShowAlarm.h"
#include "DlgDeviceLedger.h"
#include "DlgStationSelect.h"
#include "DlgAlarmSubscribe.h"

#include "xappany.h"
#include "GWPlay.h"
#include "TCPServerClient.h"
#include "SystemTray.h"
#include "VMTypeDataDefine.h"
#include "WeatherDataWinShowInfo.h"
#include "VideoExcelReportPipeServer.h"
#include "VideoExcelRecordReportPipeServer.h"
#include "ACSSystemClient.h"
#include "DlgColumn1.h"
#include "DlgColumn2.h"
#include "DlgAlarmPreview.h"

//////////////////////////////////////////////////////////////////////////
#define VEM_WIN_ITEM_TYPE_UNDEFINED 0
#define VEM_WIN_ITEM_TYPE_MULTIVIEW 1
#define VEM_WIN_ITEM_TYPE_REPLAY 2
#define VEM_WIN_ITEM_TYPE_MANAGE 3
#define VEM_WIN_ITEM_TYPE_HISTORY_LOG 4
#define VEM_WIN_ITEM_TYPE_ASSISTANCE 5
#define VEM_WIN_ITEM_TYPE_LINKAGE_SETTING 6
#define VEM_WIN_ITEM_TYPE_DEVICE_LEDGER 7
#define VEM_WIN_ITEM_TYPE_ALARM_PREVIEW 8

//////////////////////////////////////////////////////////////////////////
#define  VEM_CONTROL_BUTTON_MESSAGE_TYPE_DEFAULT 0
#define  VEM_CONTROL_BUTTON_MESSAGE_TYPE_MAIN 1
#define  VEM_CONTROL_BUTTON_MESSAGE_TYPE_MENU 2
#define  VEM_CONTROL_BUTTON_MESSAGE_TYPE_PAGESERVER 3
#define  VEM_CONTROL_BUTTON_MESSAGE_TYPE_LINKAGESERVER 4
#define  VEM_CONTROL_BUTTON_MESSAGE_TYPE_ALARM 5
#define  VEM_CONTROL_BUTTON_MESSAGE_TYPE_LINKAGEEVENT 6

//////////////////////////////////////////////////////////////////////////
#define  MAX_STATION_USER_POWER_NUM  (4*1024)
#define  MAX_STATION_USER_POWER_CAMERA_NUM (2*1024)
#define  MAX_STATION_USER_POWER_YWB_NUM (2*1024)

//////////////////////////////////////////////////////////////////////////
#define  VM_HOT_KEY_PRIOR_PAGE   1188
#define  VM_HOT_KEY_NEXT_PAGE 2288
#define  VM_HOT_KEY_EXPORT_REPORT 3688 

//////////////////////////////////////////////////////////////////////////
#define  AUTOVIDEO_PAGEVIEW_STATUS_INIT 0
#define  AUTOVIDEO_PAGEVIEW_STATUS_RUNNING 1
#define  AUTOVIDEO_PAGEVIEW_STATUS_PAUSE 2

//add by wx 2015.11.16  for elecmap
class CDlgTreeElecMap;
class CDlgCameraAndControl;

// CVEMCUCtlDlg �Ի���
class CVEMCUCtlDlg : public CDialog
{
// ����
public:
	CVEMCUCtlDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CVEMCUCtlDlg();

public:
	BOOL DialogInit();
	LRESULT OnDefaultControlButton(WPARAM wParam, LPARAM lParam);
	LRESULT OnMainControlButton(WPARAM wParam, LPARAM lParam);
	LRESULT OnMenuControlButton(WPARAM wParam, LPARAM lParam);
	LRESULT OnPageServerControlButton(WPARAM wParam, LPARAM lParam);
	LRESULT OnLinkageServerControlButton(WPARAM wParam, LPARAM lParam);
	LRESULT OnAlarmControlButton(WPARAM wParam, LPARAM lParam);
	void CheckRelationLinkageListCount();
	void CheckAndSetYtLockState();
	BOOL CheckMenuVideoTagIsDisplay(int iWinID);
	BOOL SearchProcessByName(char * pProcessName);//�ڽ��̱��в��ҽ���
	BOOL  CheckAndUpdateSystemSoftware();//��Ⲣ�������
	BOOL  VideoPageAutoView(); //�˹��Զ���ƵѲ��
	
public:
	BOOL InitVemAllWeatherInfo();
	BOOL UnInitVemAllWeatherInfo();
	BOOL InitVemWeatherInfo(int nIndex);//0:��ǰ����,1:��ʷ����,2:��ʷ�澯,3:̨��澯,4:��ǰ΢����,5:��ʷ΢����
	BOOL StartVemWeatherInfo(int nIndex);
	BOOL StopVemWeatherInfo(int nIndex);
	BOOL UnInitVemWeatherInfo(int nIndex);

	BOOL VemSendCurrentWeatherInfoRequest(int nIndex,char *szUserKey,int nStationID,int nTimeRange);
	BOOL VemSendHistoryWeatherInfoRequest(int nIndex,char *szUserKey,int nStationID,char *szStartTime,char *szStopTime,char *szSortColumn,int nPageRecords,int nPageIndex);
	BOOL VemSendHistoryWarningInfoRequest(int nIndex,char *szUserKey,int nStationID,char *szStartTime,char *szStopTime,char *szSortColumn,int nPageRecords,int nPageIndex);
	BOOL VemSendTyphoonInfoRequest(int nIndex,char *szUserKey,int nTFID,char *szStartTime,char *szStopTime,char *szSortColumn,int nPageRecords,int nPageIndex);
	BOOL VemSendCurrentMicroWeatherInfoRequest(int nIndex,char *szUserKey,int nComCode,char *szComType,int nTimeRange);
	BOOL VemSendHistoryMicroWeatherInfoRequest(int nIndex,char *szUserKey,int nComCode,char *szComType,char *szStartTime,char *szStopTime,char *szSortColumn,int nPageRecords,int nPageIndex);

	void   ShowVideoWinWeatherCurrentInfoOnTimer();//ʵʱ����ʱˢ��
	void   ShowVideoWinWeatherCurrentInfoOnTimer2();//ʵʱ����ʱˢ��-�ڴ�����ʾ
	BOOL StartVideoWinWeatherCurrentInfo(int nIndex,char *szUserKey,int nStationId,int nTimeRange);
	BOOL StopVideoWinWeatherCurrentInfo(int nIndex);

	void   ShowVideoWinMicroWeatherCurrentInfoOnTimer();//ʵʱ΢����ʱˢ��
	void   ShowVideoWinMicroWeatherCurrentInfoOnTimer2();//ʵʱ΢����ʱˢ��-�ڴ�����ʾ
	BOOL StartVideoWinMicroWeatherCurrentInfo(int nIndex,char *szUserKey,int nComCode,char *szComType,int nTimeRange);
	BOOL StopVideoWinMicroWeatherCurrentInfo(int nIndex);

	void   ShowVideoWinWeatherCurrentInfoOnTimerByFlag();
	BOOL StopVideoWinWeatherCurrentInfoByFlag(int nIndex);

	BOOL StartVideoWinWeatherHistoryInfo(int nIndex,char *szUserKey,int nStationId,char *szStartTime,char *szStopTime);//��ʷ����
	BOOL StopVideoWinWeatherHistoryInfo(int nIndex);

	int      GetStationIndexByStationName(char *szStationName);
	int      GetStationIndexByStationCode(char *szStationCode);
	int      GetStationIndexByD5000StationName(char *szD5000StationName);
	int      GetStationNodeInfoByNodeId(int nNodeId);

	void    VemStopCurrentVideo();//�رյ�ǰ��Ƶ
	void    VemStopAllVideo();//�ر�ȫ����Ƶ

	void    CheckShowVideoFlow();//��ʾ��Ƶ����

	BOOL StartSubscribeCameraPresenceInfo();//ͨ�����ķ�ʽ�õ�����ͷ״̬
	BOOL StartSearchCameraPresenceInfo();//ͨ����Ѳ��ʽ�õ�����ͷ״̬
	BOOL StopSearchCameraPresenceInfo();//ͨ����Ѳ��ʽ�õ�����ͷ״̬
	BOOL SearchCameraPresenceInfo(int nStationId,char *szStationNum);//ͨ����Ѳ��ʽ�õ�����ͷ״̬
	
	BOOL StartViewChannelPrevVideoByIndex(int nIndex);
	BOOL QuickStartViewChannelPrevVideoByIndex(int nIndex);

	bool CreateUserStationViewHistoryTable(char *szUserStationViewHistoryTableName);
	bool UpdateUserStationViewHistoryTable(char *szUserStationViewHistoryTableName);
	bool UpdateStationCameraVideoInfo();

	int   GetDeviceIpAddressType(_T_CAMERA_INFO *pCameraInfo);

public:
	BOOL KillProcessByName(char * pProcessName);//���ݽ������رս���
	BOOL TerminateProcess(char *szFileName);//�رս���

	//////////////////////////////////////////////////////////////////////////
	BOOL  CheckAndOpenVideoExcelReport();
	BOOL VideoExcelReportPipeInit();
	BOOL VideoExcelReportPipeUnInit();

	BOOL   VideoExcelReportFreshUserInfo(int nUserId);
	BOOL   VideoExcelReportShowReport();
	BOOL   VideoExcelReportHideReport();
	BOOL   VideoExcelReportExitReport();

	//////////////////////////////////////////////////////////////////////////
	BOOL  CheckAndOpenVideoExcelRecordReport();
	BOOL VideoExcelRecordReportPipeInit();
	BOOL VideoExcelRecordReportPipeUnInit();

	BOOL   VideoExcelRecordReportFreshUserInfo(int nUserId);
	BOOL   VideoExcelRecordReportShowReport();
	BOOL   VideoExcelRecordReportHideReport();
	BOOL   VideoExcelRecordReportExitReport();

public:
	HANDLE m_hVideoExcelReportPipe;
	bool m_bVideoExcelReportPipeInitFlag;

	HANDLE m_hVideoExcelRecordReportPipe;
	bool m_bVideoExcelRecordReportPipeInitFlag;

public:
	void	SetFullScreen(void);// ���ô���ȫ��
	void	InitScreen(void);// ���ش��ڸ�����ɲ���
	bool GetLocalIpAddress(char *szLocalIpAddress);//�Զ��õ����˵�IP��ַ
	bool TestLinkServerIpAddress(IN_ADDR* pInAddr);
	bool	 ReadIniFile(void);// ��ȡ�����ļ�
	int	SetFilterToInt(char* strValue);// ������־�ȼ�Ϊ����
	bool	 ConnectMySql(void);// �������ݿ�
	bool	DisConnectMySql(void);// �Ͽ����ݿ�
	bool CreateUserStationViewTable();//�����û�Ѳ��Ȩ�ޱ�
	bool GetUserStationViewPower();
	BOOL GetUserStationViewPower2();
	bool CheckUserYwbViewPower2(int nYwbId);
	bool CheckUserStationViewPower(HTREEITEM hTreeItem,int nType);
	void	SetForms(int num,BOOL bFlag = FALSE);// ���ö໭��
	void	SetLinkageForms(int num);
	void	InitPreviewWnd(int iPreviewNum);// �������ô�����Ŀ
	void	DrawFocusChannel(int iChannel, BOOL bDraw);// ����ѡ����Ƶ����߿���ɫ
	void	DrawRect(int iWinID, int nHighLight);// ��������Ƶ������߿�

	BOOL LoadSkin();

	BOOL ModifyVideoInfoDlg(int nIndex,RECT *pRect,	BOOL bShowFlag,
		int line1_from_x,int line1_from_y,int line1_to_x,int line1_to_y,
		int line2_from_x,int line2_from_y,int line2_to_x,int line2_to_y);

	BOOL ModifyVideoTagInfoDlg(int nIndex,RECT *pRect,	BOOL bShowFlag);

	BOOL ShowVideoInfoDlgByFlag(int nIndex);
	BOOL ModifyVideoInfoDlgWithView(int nIndex);

	//���Һ���
	int   SearchIndexCallByCID(int nCid);

	//6����
	BOOL SetVideoPreviewWndSix(RECT &rc,BOOL bFullScreenFlag);

	//������Ƶ��ʾ��Ϣ
	BOOL HideVideoInfoDlg(int nIndex);
	BOOL HideAllVideoInfoDlg();

	//�����Ƶ��ʾ��Ϣ
	BOOL ClearVideoInfoDlgInfo(int nIndex);

	//�̳߳�
	BOOL InitThreadPool();//0��:��������1��:��ѯ����2��:����Ƶ��3��:��Ӧsip����4��:�����ر���Ƶ
	BOOL FreeThreadPool();
	BOOL ThreadPoolDispatchTask(void (*pFun)(void *), void *arg,int argsize,int key=0);

	//TCP����
	BOOL InitTcpServerClient();
	BOOL UnInitTcpServerClient();

	/******************** ���ҽӿڲ��� ***************************/
	void	PlayClose(int win);                                                        // �رղ���ͨ��
	void	DefaultViewSetting();                                                   // ����Ĭ����Ƶ����
	void	SetViewSetting();                                                          // ���õ�ǰ��Ƶ����
	void	ExitDlg();                                                                        // �ͻ����˳�����

	/*************************************��������SDK*********************************/
	int    GetGWCode(int *pCode);     //�õ��Ѿ���װ�Ľ���SDK
	bool InitGWSDK();                         //��ʼ����������SDK
	bool UninitGWSDK();                    //����ʼ����������SDK

	/*************************************��Ѳ����*********************************/
	void	TuneCycle();             //��Ѳ�������߳�
	void	TuneCycleThread();  //��Ѳ����
	void	TuneCycleStart();     //��Ѳ��ʼ
	void	TuneCycleEnd();      //��Ѳ����
	void	SetPreSet();             // ����Ԥ�õ�
	int   MoveToPreSet();     // �Ƶ�Ԥ�õ�
	void OpenCurPageVideo(HTREEITEM hTreeCameraItem);//�򿪵�ǰ�ֶ���Ѳҳ��Ƶ

	/*************************************�����б���ʾ����*********************************/
	void	ShowLargeRelationList();// ��ʾ��С�������б�
	void	ShowSmallRelationList();// ��ʾ�Ŵ�������б�

	void DisplayLinkageServerRelationListByFlag(BOOL bFlag);//���ݱ�־��ʾ�����б�
	void DisplayShowLinkageServerByFlag(BOOL bFlag);//���ݱ�־��ʾ������ť

	BOOL GetProgramAppPath();//�õ�����������Ŀ¼
	BOOL GetFileVersionInfoFromFile(char *szVersion,int nLen);//�������ļ��ж�ȡ�汾��Ϣ
	BOOL GetFileVersionInfoFromApp(char *szVersion,int nLen);//�õ�������İ汾��Ϣ
	BOOL GetProgramAppVersionInfo();//�õ�����İ汾��Ϣ

public:
	/*******************���Ӵ��ڶ���*************************/
	CDlgMenu		*m_pDlgMenu;
	CDlgPageServer	*m_pDlgPageServer;
	CDlgHistoryLog	*m_pDlgHistoryLog;
	CDlgSelectDevice *m_pDlgSelectDevice;
	CDlgShowControl *m_pDlgShowControl;
	CDlgShowPageServer *m_pDlgShowPageServer;
	CDlgLinkageServer *m_pDlgLinkageServer;
	CDlgShowLinkageServer *m_pDlgShowLinkageServer;
	CDlgPageViewInfo *m_pDlgPageViewInfo;
	CDlgRecFilePath	 *m_pDlgRecFilePath;
	CDlgPicFilePath *m_pDlgPicFilePath;
	CDlgShowAlarm *m_pDlgShowAlarm;//��ʾ�澯չʾ���ڵİ�ť
	CDlgAlarmInfo *m_pDlgAlarmInfo;
	CDlgDeviceLedger *m_pDlgDeviceLedger;
	CDlgStationSelect *m_pDlgStationSelect;
	CDlgAlarmSubscribe *m_pDlgAlarmSubscribe;
	CDlgColumn1 *m_pDlgColumn1;
	CDlgColumn2 *m_pDlgColumn2;
	CDlgAlarmPreview *m_pDlgAlarmPreview;

	CDlgTreeElecMap* m_pDlgTreeElecMap;
	CDlgCameraAndControl *m_pDlgCameraAndControl;

	//////////////////////////////////////////////////////////////////////////
	int		m_FormsNum;					//��ǰ���ڷ�����Ŀ
	int		m_iPreviewNum;				//֮ǰ���ڷ�����Ŀ
	int		m_iFocuseWindowID;		//���㴰��
	bool	    m_bShowTempFavorite;	//�Ƿ���ʾ�ղؼжԻ���
	bool  	m_bShowRealTalk;
	int		m_nControlWidth;		// �����������
	int       m_nMenuHight;         // �˵����߶�
	int       m_nLinkageWidth;     //�Ҳ��������ڿ��
	int       m_nPageViewInfoHeight; //�ֶ���Ѳ�����߶�
	int		m_nAlarmHeight;	//�澯չʾ���ڸ߶�

	//��ʾ��������Ƶ��Ϣ����
	BOOL		  m_bMultiFullScreen;	//�໭��ȫ��
	BOOL		  m_bFullScreen;			//�Ƿ�ȫ��
	BOOL          m_bMenuFlag;            //�Ƿ���ʾ����
	BOOL          m_bLinkageServerFlag; //�Ƿ���ʾ����
	BOOL          m_bPageServerFlag;   //�Ƿ���ʾ�б��ƾ�����
	BOOL          m_bPageViewInfoFlag; //�Ƿ���ʾ�ֶ���Ѳ����
	int			   m_nFullScreen;				//��ǰ�໭��ȫ��ģʽ
	int                m_nMenuItemIndex; //��ǰѡ���Ӵ���
	WINDOWPLACEMENT m_OldWndpl;				//�ݴ����������ȫ��ǰ�Ĵ�С
	WINDOWPLACEMENT m_chWndpl;					//�ݴ����������ȫ��ǰ�Ĵ�С

	//////////////////////////////////////////////////////////////////////////
	CBitmap   m_ViewOutVideoBGBmp;
	BITMAP    m_ViewOutVideoBGBm;

	//////////////////////////////////////////////////////////////////////////
	int m_nYtCommand;
	char m_szYtCommandName[64];
	
// �Ի�������
	enum { IDD = IDD_VEMCUCTL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	LRESULT OnControlButton(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMenuItemExitVideo();
	afx_msg void OnMenuStopAllVideo();
	afx_msg void OnMenuitemStartRec();
	afx_msg void OnMenuitemStopRec();
	afx_msg void OnMenuitemCapture();
	afx_msg void OnMenuitemMultifullScreen();
	afx_msg void OnMenuitemExitmultifullScreen();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMenuItemShow();
	afx_msg void OnMenuItemExit();
	afx_msg void OnMenuitemTagCamera();
	afx_msg void OnMenuitemCancelcamera();
	LRESULT OnChannelChange(WPARAM wParam, LPARAM lParam);
	LRESULT OnDBLChannel(WPARAM wParam, LPARAM lParam);
	LRESULT OnRightClickChannel(WPARAM wParam, LPARAM lParam);
	LRESULT StartYtControl(WPARAM iCommandID, LPARAM iMove);
	afx_msg LRESULT OnExitUsbVideoMSGHandler(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnInitUsbVideoMSGHandler(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSubOK(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSubFail(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	LRESULT OnVideoLinkageManualMessageHandler(WPARAM wParam, LPARAM lParam);
	LRESULT OnVideoLinkageAlarmMessageHandler(WPARAM wParam, LPARAM lParam);
	LRESULT OnVideoLinkageStateMessageHandler(WPARAM wParam, LPARAM lParam);
	LRESULT OnVideoCameraControlNotifyMessageHandler(WPARAM wParam, LPARAM lParam);
	LRESULT OnDeviceVideoErrorReasonNotifyMessageHandler(WPARAM wParam, LPARAM lParam);
	LRESULT OnDeviceVideoTalkNotifyMessageHandler(WPARAM wParam, LPARAM lParam);
	LRESULT OnDeviceVideoCloseMessageHandler(WPARAM wParam, LPARAM lParam);
	LRESULT OnDeviceVideoQuickRestartMessageHandler(WPARAM wParam, LPARAM lParam);
	LRESULT OnDeviceVideoStatusOnlineNotifyMessageHandler(WPARAM wParam, LPARAM lParam);
	LRESULT OnVideoLinkageWeatherWarningMessageHandler(WPARAM wParam, LPARAM lParam);
	LRESULT OnVideoLinkageWeatherForecastMessageHandler(WPARAM wParam, LPARAM lParam);
	LRESULT OnUpdateUserViewCameraStatusMessageHandler(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	void SetDevPlayVideoSdk();
	BOOL InitAssClient();
	//�����ݱ�video_camera�����һ��anfang_flag�ֶΣ������ж�����ͷ�Ƿ��ǰ�������ͷ
	BOOL AddAnFangFlagToVideoCamera();
	void ACSSystemConfig();
	void LinkageSettingConfig();
	void HideAllDialog();
	LRESULT OnElecMapOpenCameraMessageHandler(WPARAM wParam, LPARAM lParam);
};

/****************************************************************/
extern CDlgViewOut    g_DlgVideoView[MAXVIEWCH];
extern CVideoInfoDlg  g_VideoInfoDlg[MAXVIEWCH];
extern CVideoTagInfoDlg g_VideoTagInfoDlg[MAXVIEWCH];

/****************************************************************/
//�汾�����ļ�����
extern char g_FileDataInfo[2*1024];

//��ʾ��ǰ�汾��Ϣ,��ʼ��Ϊ����汾
extern char g_szCurrentVersion[2*1024];

//����·��
extern char g_szAppPath[MAX_PATH];

/****************************************************************/
extern CACSSystemClient *g_pACSClient;
extern CGWPlay g_GWPlay;
extern CTcpServerClient g_TcpServerClient;
extern CVEMCUCtlDlg	*g_pMainDlg;
extern int					g_nWin_Height;
extern int					g_nWin_Width;

//�ͻ�����Ƶ���ӷ�ʽ,0��ʾֻ������ƽ̨,1��ʾֱ�ӷ���ǰ���豸,2��ʾ����һ�κ�����豸,3��ʾ�������κ�����豸
extern int  g_nClientVideoLinkType;

//��ƵѲ���̼߳���
extern VM_THTEAD_VIDEO_OPERATE_NUMBER_INFO g_ThreadVideoOperateNumberInfo;

//////////////////////////////////////////////////////////////////////////
//������ʾ����
extern int g_nCurrentWeatherDataWinInfoTypeFlag;//0:��ʾ��ʾ΢����,1:��ʾ��ʾ����

//��ǰ����
extern HANDLE  g_hWeatherCurrentInfoEvent;
extern int            g_nWeatherCurrentInfoType;
extern time_t      g_WeatherCurrentInfoTime;
extern int            g_nWeatherCurrentInfoIndex;

//��ʷ����
extern HANDLE  g_hWeatherHistoryInfoEvent;
extern int           g_nWeatherHistoryInfoType ;
extern time_t      g_WeatherHistoryInfoTime;
extern int           g_nWeatherHistoryInfoIndex;

//��ʷ�澯
extern HANDLE  g_hWeatherHistoryWarningInfoEvent;
extern int           g_nWeatherHistoryWarningInfoType;
extern time_t      g_WeatherHistoryWarningInfoTime;
extern int           g_nWeatherHistoryWarningInfoIndex;

//̨��澯
extern HANDLE  g_hWeatherTyphoonWarningInfoEvent;
extern int           g_nWeatherTyphoonWarningInfoType;
extern time_t      g_WeatherTyphoonWarningInfoTime;
extern int           g_nWeatherTyphoonWarningInfoIndex;

//��ǰ΢����
extern HANDLE  g_hMicroWeatherCurrentInfoEvent;
extern int           g_nMicroWeatherCurrentInfoType;
extern time_t      g_MicroWeatherCurrentInfoTime;
extern int           g_nMicroWeatherCurrentInfoIndex;

//��ʷ΢����
extern HANDLE  g_hMicroWeatherHistoryInfoEvent ;
extern int           g_nMicroWeatherHistoryInfoType;
extern time_t      g_MicroWeatherHistoryInfoTime;
extern int           g_nMicroWeatherHistoryInfoIndex;

//ץͼ·��
extern char   g_PictureSaveFilepath[256];

//////////////////////////////////////////////////////////////////////////
//�û�Ѳ��
extern int  g_nUserStationViewStationCount;//�û�ҪѲ��վ����
extern int  g_nUserStationViewStationId[MAX_STATION_USER_POWER_NUM];//�û�ҪѲ��վ��ID��
extern int  g_nUserStationViewStationVoltageClass[MAX_STATION_USER_POWER_NUM];//�û�ҪѲ��վ��ĵ�ѹ�ȼ�
extern char  g_szUserStationViewStationNum[MAX_STATION_USER_POWER_NUM][64];//�û�ҪѲ��վ�����
extern char  g_szUserStationViewStationName[MAX_STATION_USER_POWER_NUM][256];//�û�ҪѲ��վ������
extern int  g_nUserStationViewStationCameraCount[MAX_STATION_USER_POWER_NUM];//�û�ҪѲ��վ�������ͷ��
extern int  g_nUserStationViewStationNoCheckCameraCount[MAX_STATION_USER_POWER_NUM];//�û�Ѳ��վ���δѲ�ӵ�����ͷ��
extern char g_szUserStationViewOneStationCameraNum[MAX_STATION_USER_POWER_CAMERA_NUM][64];//��ʱ����,������ͷ��Ϣͬ��ʹ��,�û�Ѳ��վ�������ͷ����
extern int  g_nUserStationViewOneStationCameraCount;//��ʱ����,������ͷ��Ϣͬ��ʹ��,�û�Ѳ��վ�������ͷ����
extern char g_szCurrentStationCameraNum[MAX_STATION_USER_POWER_CAMERA_NUM][64];//��ʱ����,������ͷ��Ϣͬ��ʹ��,��ǰվ�������ͷ����
extern int  g_nCurrentStationCameraStatus[MAX_STATION_USER_POWER_CAMERA_NUM];//��ʱ����,������ͷ��Ϣͬ��ʹ��,��ǰվ�������ͷ״̬
extern int  g_nCurrentStationCameraCount;//��ʱ����,������ͷ��Ϣͬ��ʹ��,��ǰվ�������ͷ����

//////////////////////////////////////////////////////////////////////////

extern T_CURRENT_WEATHER_DATA_WIN_INFO g_CurrentWeatherDataWinInfo[MAXVIEWCH];
extern T_HISTORY_WEATHER_DATA_WIN_INFO g_HistoryWeatherDataWinInfo[MAXVIEWCH];
extern T_CURRENT_MICRO_WEATHER_DATA_WIN_INFO g_CurrentMicroWeatherDataWinInfo[MAXVIEWCH];
extern int   g_nViewOutVideoTypeFlag;//��Ƶ��ť��ʾ����

//////////////////////////////////////////////////////////////////////////
BOOL SendVideoYTControlInfo(char *szInfo,int nInfoLen,int nFlag=0);
BOOL IsCameraVideoLinkByVideoPlatform(int VideoLinkType,int nCameraType);

//////////////////////////////////////////////////////////////////////////
unsigned __stdcall _CameraStatusSearchThread(void *arg);
unsigned __stdcall _CameraStatusSearchThread2(void *arg);

//////////////////////////////////////////////////////////////////////////
extern int  g_nUserStationViewYwbId[MAX_STATION_USER_POWER_YWB_NUM];//�û�ҪѲ����ά��ID��
extern int  g_nUserStationViewYwbCount;//�û�ҪѲ����ά����

/////////////////////////////////////////////////////////////////////////
extern CEvent g_AcsSubscribeAlarmEvent;
extern CEvent g_CommonEvent;
