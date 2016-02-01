// DlgAlarmInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "DlgAlarmInfo.h"
#include "xappany.h"
#include "VEMCUCtlDlg.h"
#include "CameraVideoOperate.h"
#include "SipCall.h"
#include "DlgLinkageConfig.h"

#include "SDDElecMap/DLLInterface.h"
#include "DlgTreeElecMap.h"

#include "DlgCameraAndControl.h"
#include "DlgAlarmStatistics.h"

// CDlgAlarmInfo �Ի���

IMPLEMENT_DYNAMIC(CDlgAlarmInfo, CDialog)

CDlgAlarmInfo::CDlgAlarmInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmInfo::IDD, pParent)
{
	m_nLinkageCameraInfoCount = 0;
	memset(m_tLinkageCameraInfo, 0, sizeof(T_LINKAGE_CAMERA_INFO)*MAX_DEV_RELATION_CAMERA);
	menuMain.CreatePopupMenu();
	pPopMenu.CreatePopupMenu();

	//��ȡ����������Ϣ
	memset(&m_tAssLinkageConfig, 0, sizeof(T_ASS_LINKAGE_CONFIG));
	GetLinkageConfig(&m_tAssLinkageConfig);

	m_strLastLinkageEventTime.Format("1977-01-01 00:00:00");
}

CDlgAlarmInfo::~CDlgAlarmInfo()
{
	if (m_pBackBmp != NULL)
	{
		delete m_pBackBmp;
	}

	//FreeRealAlarmInfoList();
	//FreeDealAlarmInfoList();
	//FreeLocalDealAlarmInfoList();
	//FreeLocalHidelAlarmInfoList();
}

void CDlgAlarmInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REAL_ALARM_INFO, m_lstRealAlarmInfo);
	DDX_Control(pDX, IDC_LIST_DEAL_ALARM_INFO, m_lstDealAlarmInfo);
	DDX_Control(pDX, IDC_LIST_LOCAL_DEAL_ALARM_INFO, m_lstLocalDealAlarmInfo);
	DDX_Control(pDX, IDC_LIST_LOCAL_HIDE_ALARM_INFO, m_lstLocalHideAlarmInfo);
	DDX_Control(pDX, IDC_LIST_REAL_EX_ALARM_INFO, m_lstRealExAlarmInfo);
	DDX_Control(pDX, IDC_LIST_LINKAGE_ACTION, m_lstLinkageAction);
	//DDX_Control(pDX, IDC_BUTTON_REALTIME_EX_ALARM, m_btnReal);
	DDX_Control(pDX, IDC_BUTTON_REALTIME_EX_ALARM, m_btnRealTime);
	DDX_Control(pDX, IDC_BUTTON_REALTIME_ALARM, m_unDealAlarm);
	DDX_Control(pDX, IDC_BUTTON_PROCESSED_ALARM, m_btnHaveDealAlarm);
	DDX_Control(pDX, IDC_BUTTON_PROCESSED_HISTORY, m_btnLocalDealAlarm);
	DDX_Control(pDX, IDC_BUTTON_HIDING_ALARM, m_btnHideAlarm);
	DDX_Control(pDX, IDC_BUTTON_LINKAGE, m_btnLinkageInfo);
	DDX_Control(pDX, IDC_BUTTON_LINKAGE_CONFIG, m_btnLinkageConfig);
	DDX_Control(pDX, IDC_BUTTON_ALARM_SUBSCRIBE, m_btnSubscribeAlarm);
	DDX_Control(pDX, IDC_BTN_SHOW_ALARM, m_btnShowAlarm);
	DDX_Control(pDX, IDC_BUTTON_ALARM_STATISTICS, m_btnAlarmStatistics);
}


BEGIN_MESSAGE_MAP(CDlgAlarmInfo, CDialog)
	ON_WM_SIZE()
	ON_COMMAND_RANGE(1246, 1246, OnControlButton)//��ط��ĳ�1246����Ϊ��ֹ��������ť�¼�Ҳ�������ˣ�
	ON_BN_CLICKED(IDC_BTN_SHOW_ALARM, &CDlgAlarmInfo::OnBnClickedBtnShowAlarm)
	ON_BN_CLICKED(IDC_BUTTON_REALTIME_ALARM, &CDlgAlarmInfo::OnBnClickedButtonRealtimeAlarm)
	ON_BN_CLICKED(IDC_BUTTON_PROCESSED_ALARM, &CDlgAlarmInfo::OnBnClickedButtonProcessedAlarm)
	ON_BN_CLICKED(IDC_BUTTON_PROCESSED_HISTORY, &CDlgAlarmInfo::OnBnClickedButtonProcessedHistory)
	ON_BN_CLICKED(IDC_BUTTON_HIDING_ALARM, &CDlgAlarmInfo::OnBnClickedButtonHidingAlarm)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_SUBSCRIBE, &CDlgAlarmInfo::OnBnClickedButtonAlarmSubscribe)
	ON_WM_TIMER()
	ON_NOTIFY(NM_RCLICK, IDC_LIST_REAL_ALARM_INFO, &CDlgAlarmInfo::OnNMRClickListRealAlarmInfo)
	ON_COMMAND_RANGE(ID_LINKAGE_INFO1, ID_LINKAGE_INFO16, &CDlgAlarmInfo::OnClickLinkageCamera)
	ON_COMMAND(ID_PROCESS_ALARM, &CDlgAlarmInfo::OnClickProcessAlarm)
	ON_COMMAND(ID_HIDE_ALARM, &CDlgAlarmInfo::OnClickHideAlarm)
	ON_COMMAND(ID_RECOVER_ALARM, &CDlgAlarmInfo::OnClickRecoverAlarm)
	ON_COMMAND(ID_COMPLETE_PROCESS_ALARM, &CDlgAlarmInfo::OnClickCompleteProcessAlarm)
	ON_COMMAND(ID_CANCEL_HIDE_ALARM, &CDlgAlarmInfo::OnClickCancelHideAlarm)
	ON_COMMAND(ID_DELETE_LINKAGE_RECORD, &CDlgAlarmInfo::OnClickDeleteLinkageRecord)
	ON_COMMAND(ID_REMOVE_ALL_ITEMS, &CDlgAlarmInfo::OnClickRemoveAllItems)
	ON_COMMAND(ID_SHOW_ELECMAP, &CDlgAlarmInfo::OnClickOpenElecMap)
	ON_COMMAND(ID_OPEN_VIDEO, &CDlgAlarmInfo::OnClickOpenVideo)
	ON_BN_CLICKED(IDC_BUTTON_REALTIME_EX_ALARM, &CDlgAlarmInfo::OnBnClickedButtonRealtimeExAlarm)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_REAL_EX_ALARM_INFO, &CDlgAlarmInfo::OnNMRClickListRealExAlarmInfo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_DEAL_ALARM_INFO, &CDlgAlarmInfo::OnNMRClickListDealAlarmInfo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_LOCAL_DEAL_ALARM_INFO, &CDlgAlarmInfo::OnNMRClickListLocalDealAlarmInfo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_LOCAL_HIDE_ALARM_INFO, &CDlgAlarmInfo::OnNMRClickListLocalHideAlarmInfo)
	ON_BN_CLICKED(IDC_BUTTON_LINKAGE, &CDlgAlarmInfo::OnBnClickedButtonLinkage)
	ON_BN_CLICKED(IDC_BUTTON_LINKAGE_CONFIG, &CDlgAlarmInfo::OnBnClickedButtonLinkageConfig)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_LINKAGE_ACTION, &CDlgAlarmInfo::OnNMRClickListLinkageAction)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_ALARM_STATISTICS, &CDlgAlarmInfo::OnBnClickedButtonAlarmStatistics)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
int alarm_client_cb(NETHANDLE handle,char* buf,int len,void* user)
{
	//����յ���¼���سɹ���Ϣ���򽫵�¼�ɹ��¼���Ϊtrue
	if (buf!=NULL&&len>0)
	{
		printf("�յ�����˴��������ݣ�%s\n",buf);
		char *buf1="hello server!\n";
		ComSendNet(handle,NULL,0,0,0,0,0,buf1,strlen(buf1),1);
	}

	return len;
}

// CDlgAlarmInfo ��Ϣ�������
int CDlgAlarmInfo::CreateAlarmClient()
{
	NETHANDLE hTcpServerHandle = TRUE;
	
	return hTcpServerHandle;
}

int CDlgAlarmInfo::SendLoginRequest()
{
	int ret = TRUE;

	return ret;
}

//����Э��ת����
BOOL CDlgAlarmInfo::ReadProtocolTable()
{
	BOOL ret = TRUE;

	return ret;
}

//������Ҫ���и澯����
BOOL CDlgAlarmInfo::SendGetAlarmDataRequest()
{
	BOOL ret = TRUE;

	return ret;
}

BOOL CDlgAlarmInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	//��ʼ���б��ֶκ���ʽ
	InitAllListStyleAndColumn();

	//����Щ�澯��ӵ�list�ؼ��У�ʹ�ö�ʱ������ֹ�������ʱ��ס
	SetTimer(1,1000,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgAlarmInfo::InitAllListStyleAndColumn()
{
	m_pBackBmp = new CBitmap;
	m_pBackBmp->LoadBitmap(IDB_BITMAP_VIEW_OUT_TOP_BK);

	DWORD dwStyle;
	dwStyle = m_lstDealAlarmInfo.GetStyle();
	dwStyle = LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT ;

	m_lstDealAlarmInfo.SetExtendedStyle(dwStyle);
	m_lstDealAlarmInfo.SetBkColor(RGB(239,246,253));
	m_lstDealAlarmInfo.SetTextBkColor(RGB(0xfe,0xFF,0xc6));

	dwStyle = m_lstRealAlarmInfo.GetStyle();
	dwStyle = LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT ;

	m_lstRealAlarmInfo.SetExtendedStyle(dwStyle);
	m_lstRealAlarmInfo.SetBkColor(RGB(239,246,253));
	m_lstRealAlarmInfo.SetTextBkColor(RGB(0xfe,0xFF,0xc6));

	dwStyle = m_lstRealExAlarmInfo.GetStyle();
	dwStyle = LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT ;

	m_lstRealExAlarmInfo.SetExtendedStyle(dwStyle);
	m_lstRealExAlarmInfo.SetBkColor(RGB(239,246,253));
	m_lstRealExAlarmInfo.SetTextBkColor(RGB(0xfe,0xFF,0xc6));

	dwStyle = m_lstLocalDealAlarmInfo.GetStyle();
	dwStyle = LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT ;

	m_lstLocalDealAlarmInfo.SetExtendedStyle(dwStyle);
	m_lstLocalDealAlarmInfo.SetBkColor(RGB(239,246,253));
	m_lstLocalDealAlarmInfo.SetTextBkColor(RGB(0xfe,0xFF,0xc6));

	dwStyle = m_lstLocalHideAlarmInfo.GetStyle();
	dwStyle = LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT ;

	m_lstLocalHideAlarmInfo.SetExtendedStyle(dwStyle);
	m_lstLocalHideAlarmInfo.SetBkColor(RGB(239,246,253));
	m_lstLocalHideAlarmInfo.SetTextBkColor(RGB(0xfe,0xFF,0xc6));

	dwStyle = m_lstLinkageAction.GetStyle();
	dwStyle = LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT ;

	m_lstLinkageAction.SetExtendedStyle(dwStyle);
	m_lstLinkageAction.SetBkColor(RGB(239,246,253));
	m_lstLinkageAction.SetTextBkColor(RGB(0xfe,0xFF,0xc6));

	//��ʼ���б���ֶ�
	CRect winrc;
	GetClientRect(winrc);

	int nWidth = winrc.Width();

	m_lstRealAlarmInfo.DeleteAllItems();
	while(m_lstRealAlarmInfo.DeleteColumn(0));

	m_lstRealAlarmInfo.InsertColumn(0,"���վ����");
	m_lstRealAlarmInfo.SetColumnWidth(0,nWidth*0.1);
	m_lstRealAlarmInfo.InsertColumn(1,"�澯�豸����");
	m_lstRealAlarmInfo.SetColumnWidth(1,nWidth*0.15);
	m_lstRealAlarmInfo.InsertColumn(2,"�澯����");
	m_lstRealAlarmInfo.SetColumnWidth(2,nWidth*0.1);
	m_lstRealAlarmInfo.InsertColumn(3,"�澯����ʱ��");
	m_lstRealAlarmInfo.SetColumnWidth(3,nWidth*0.15);
	m_lstRealAlarmInfo.InsertColumn(4,"�Ƿ������Ƶ");
	m_lstRealAlarmInfo.SetColumnWidth(4,nWidth*0.2);
	m_lstRealAlarmInfo.InsertColumn(5,"���ȼ�");
	m_lstRealAlarmInfo.SetColumnWidth(5,nWidth*0.1);
	m_lstRealAlarmInfo.InsertColumn(6,"����״̬");
	m_lstRealAlarmInfo.SetColumnWidth(6,nWidth*0.1);

	m_lstRealExAlarmInfo.DeleteAllItems();
	while(m_lstRealExAlarmInfo.DeleteColumn(0));

	m_lstRealExAlarmInfo.InsertColumn(0,"���վ����");
	m_lstRealExAlarmInfo.SetColumnWidth(0,nWidth*0.1);
	m_lstRealExAlarmInfo.InsertColumn(1,"�澯�豸����");
	m_lstRealExAlarmInfo.SetColumnWidth(1,nWidth*0.15);
	m_lstRealExAlarmInfo.InsertColumn(2,"�澯����");
	m_lstRealExAlarmInfo.SetColumnWidth(2,nWidth*0.1);
	m_lstRealExAlarmInfo.InsertColumn(3,"�澯����ʱ��");
	m_lstRealExAlarmInfo.SetColumnWidth(3,nWidth*0.15);
	m_lstRealExAlarmInfo.InsertColumn(4,"�Ƿ������Ƶ");
	m_lstRealExAlarmInfo.SetColumnWidth(4,nWidth*0.2);
	m_lstRealExAlarmInfo.InsertColumn(5,"���ȼ�");
	m_lstRealExAlarmInfo.SetColumnWidth(5,nWidth*0.1);
	m_lstRealExAlarmInfo.InsertColumn(6,"����״̬");
	m_lstRealExAlarmInfo.SetColumnWidth(6,nWidth*0.1);

	m_lstDealAlarmInfo.DeleteAllItems();
	while(m_lstDealAlarmInfo.DeleteColumn(0));

	m_lstDealAlarmInfo.InsertColumn(0,"���վ����");
	m_lstDealAlarmInfo.SetColumnWidth(0,nWidth*0.1);
	m_lstDealAlarmInfo.InsertColumn(1,"�澯�豸����");
	m_lstDealAlarmInfo.SetColumnWidth(1,nWidth*0.1);
	m_lstDealAlarmInfo.InsertColumn(2,"�澯����");
	m_lstDealAlarmInfo.SetColumnWidth(2,nWidth*0.1);
	m_lstDealAlarmInfo.InsertColumn(3,"�澯����ʱ��");
	m_lstDealAlarmInfo.SetColumnWidth(3,nWidth*0.1);
	m_lstDealAlarmInfo.InsertColumn(4,"�澯����ʱ��");
	m_lstDealAlarmInfo.SetColumnWidth(4,nWidth*0.1);
	m_lstDealAlarmInfo.InsertColumn(5,"�Ƿ������Ƶ");
	m_lstDealAlarmInfo.SetColumnWidth(5,nWidth*0.1);
	m_lstDealAlarmInfo.InsertColumn(6,"���ȼ�");
	m_lstDealAlarmInfo.SetColumnWidth(6,nWidth*0.1);
	m_lstDealAlarmInfo.InsertColumn(7,"����״̬");
	m_lstDealAlarmInfo.SetColumnWidth(7,nWidth*0.1);
	m_lstDealAlarmInfo.InsertColumn(8,"������Ա");
	m_lstDealAlarmInfo.SetColumnWidth(8,nWidth*0.1);

	m_lstLocalDealAlarmInfo.DeleteAllItems();
	while(m_lstLocalDealAlarmInfo.DeleteColumn(0));

	m_lstLocalDealAlarmInfo.InsertColumn(0,"���վ����");
	m_lstLocalDealAlarmInfo.SetColumnWidth(0,nWidth*0.1);
	m_lstLocalDealAlarmInfo.InsertColumn(1,"�澯�豸����");
	m_lstLocalDealAlarmInfo.SetColumnWidth(1,nWidth*0.1);
	m_lstLocalDealAlarmInfo.InsertColumn(2,"�澯����");
	m_lstLocalDealAlarmInfo.SetColumnWidth(2,nWidth*0.1);
	m_lstLocalDealAlarmInfo.InsertColumn(3,"�澯����ʱ��");
	m_lstLocalDealAlarmInfo.SetColumnWidth(3,nWidth*0.1);
	m_lstLocalDealAlarmInfo.InsertColumn(4,"�澯����ʱ��");
	m_lstLocalDealAlarmInfo.SetColumnWidth(4,nWidth*0.1);
	m_lstLocalDealAlarmInfo.InsertColumn(5,"�Ƿ������Ƶ");
	m_lstLocalDealAlarmInfo.SetColumnWidth(5,nWidth*0.1);
	m_lstLocalDealAlarmInfo.InsertColumn(6,"���ȼ�");
	m_lstLocalDealAlarmInfo.SetColumnWidth(6,nWidth*0.1);
	m_lstLocalDealAlarmInfo.InsertColumn(7,"����״̬");
	m_lstLocalDealAlarmInfo.SetColumnWidth(7,nWidth*0.1);
	m_lstLocalDealAlarmInfo.InsertColumn(8,"������Ա");
	m_lstLocalDealAlarmInfo.SetColumnWidth(8,nWidth*0.1);

	m_lstLocalHideAlarmInfo.DeleteAllItems();
	while(m_lstLocalHideAlarmInfo.DeleteColumn(0));

	m_lstLocalHideAlarmInfo.InsertColumn(0,"���վ����");
	m_lstLocalHideAlarmInfo.SetColumnWidth(0,nWidth*0.1);
	m_lstLocalHideAlarmInfo.InsertColumn(1,"�澯�豸����");
	m_lstLocalHideAlarmInfo.SetColumnWidth(1,nWidth*0.1);
	m_lstLocalHideAlarmInfo.InsertColumn(2,"�澯����");
	m_lstLocalHideAlarmInfo.SetColumnWidth(2,nWidth*0.1);
	m_lstLocalHideAlarmInfo.InsertColumn(3,"�澯����ʱ��");
	m_lstLocalHideAlarmInfo.SetColumnWidth(3,nWidth*0.1);
	m_lstLocalHideAlarmInfo.InsertColumn(4,"�澯����ʱ��");
	m_lstLocalHideAlarmInfo.SetColumnWidth(4,nWidth*0.1);
	m_lstLocalHideAlarmInfo.InsertColumn(5,"�Ƿ������Ƶ");
	m_lstLocalHideAlarmInfo.SetColumnWidth(5,nWidth*0.1);
	m_lstLocalHideAlarmInfo.InsertColumn(6,"���ȼ�");
	m_lstLocalHideAlarmInfo.SetColumnWidth(6,nWidth*0.1);
	m_lstLocalHideAlarmInfo.InsertColumn(7,"����״̬");
	m_lstLocalHideAlarmInfo.SetColumnWidth(7,nWidth*0.1);
	m_lstLocalHideAlarmInfo.InsertColumn(8,"������Ա");
	m_lstLocalHideAlarmInfo.SetColumnWidth(8,nWidth*0.1);

	m_lstLinkageAction.DeleteAllItems();
	while(m_lstLinkageAction.DeleteColumn(0));

	m_lstLinkageAction.InsertColumn(0,"�豸��");
	m_lstLinkageAction.SetColumnWidth(0,nWidth*0.2);
	m_lstLinkageAction.InsertColumn(1,"�����豸��");
	m_lstLinkageAction.SetColumnWidth(1,nWidth*0.2);
	m_lstLinkageAction.InsertColumn(2,"�����豸����");
	m_lstLinkageAction.SetColumnWidth(2,nWidth*0.2);
	m_lstLinkageAction.InsertColumn(3,"��������");
	m_lstLinkageAction.SetColumnWidth(3,nWidth*0.1);
	m_lstLinkageAction.InsertColumn(4,"Ԥ��λ���");
	m_lstLinkageAction.SetColumnWidth(4,nWidth*0.1);
	m_lstLinkageAction.InsertColumn(5,"����ʱ��");
	m_lstLinkageAction.SetColumnWidth(5,nWidth*0.2);

	//���ð�ť��ɫ
	InitDlgButtonColor(m_hWnd);

	m_btnShowAlarm.SetBitmaps(IDB_BITMAP_SHOW_CONTROL2, RGB(0,0,0));
}

void CDlgAlarmInfo::InitRealAlarmInfoList()
{
	FreeRealAlarmInfoList();
	int yx_index = 0;
	char sql_buf[1024]={0x0};
	MYSQL_RES* res;
	MYSQL_ROW row;

	//ȡ��ǰ��
	CTime time = CTime::GetCurrentTime();
	int nYear = time.GetYear();

	sprintf_s(sql_buf,"select a.rvu_id,a.dev_id,a.start_time,a.alarm_level,a.type,a.process_status,b.station_id,IFNULL(c.name,''),IFNULL(c.relation_video_status,0),d.station_name_videoplant,a.id from ass_alarm_%d a" 
		" left join ass_rvu b on a.rvu_id=b.rvu_id" 
		" left join ass_rvu_sm c on a.dev_id=c.id" 
		" left join ob_d5000_station d on b.station_id=d.station_id" 
		" where a.process_status=1 and (a.dev_id not in (select dev_id from ass_alarm_hide where user_id=%d))",nYear,g_userpower.userID);
	if (!mysql_query(g_mySqlData,sql_buf))
	{
		res = mysql_store_result(g_mySqlData);
		while (row = mysql_fetch_row(res))
		{
			ACS_ALARM_INFO *pAlarmInfo = new ACS_ALARM_INFO;
			pAlarmInfo->nDevId = atoi(row[1]);
			sprintf_s(pAlarmInfo->szAlarmStartTime,"%s",row[2]);
			pAlarmInfo->nPriorLevel = atoi(row[3]);
			pAlarmInfo->nAlarmType = atoi(row[4]);
			pAlarmInfo->nStatus = atoi(row[5]);
			pAlarmInfo->nStationId = atoi(row[6]);
			sprintf_s(pAlarmInfo->szDevName,"%s",row[7]);
			pAlarmInfo->nRelationVideo = atoi(row[8]);
			sprintf_s(pAlarmInfo->szStationName,"%s",row[9]);
			pAlarmInfo->nId = atoi(row[10]);

			m_lstRealAlarmInfo.InsertItem(yx_index,pAlarmInfo->szStationName);
			m_lstRealAlarmInfo.SetItemText(yx_index,1,pAlarmInfo->szDevName);

			char szAlarmTypeText[32]={0};
			GetAlarmTypeText(szAlarmTypeText,pAlarmInfo->nAlarmType);
			m_lstRealAlarmInfo.SetItemText(yx_index,2,szAlarmTypeText);

			m_lstRealAlarmInfo.SetItemText(yx_index,3,pAlarmInfo->szAlarmStartTime);

			char szRelationVideoText[32]={0};
			GetRelationVideoText(szRelationVideoText,pAlarmInfo->nRelationVideo);
			m_lstRealAlarmInfo.SetItemText(yx_index,4,szRelationVideoText);

			char szPriorLeveText[32]={0};
			sprintf_s(szPriorLeveText,"%d",pAlarmInfo->nPriorLevel);
			m_lstRealAlarmInfo.SetItemText(yx_index,5,szPriorLeveText);

			char szProcessStatusText[32]={0};
			GetProcessStatusText(szProcessStatusText,pAlarmInfo->nStatus);
			m_lstRealAlarmInfo.SetItemText(yx_index,6,szProcessStatusText);

			m_lstRealAlarmInfo.SetItemData(yx_index,(DWORD_PTR)pAlarmInfo);

			yx_index++;
		}
		mysql_free_result(res);
	}
}

CString CDlgAlarmInfo::GetProcessStatusText(int nProcessStatus)
{
	CString strText;
	if (nProcessStatus == 0)
	{
		strText = "�Ѵ���";
	} 
	else
	{
		strText = "δ����";
	}
	return strText;
}

void CDlgAlarmInfo::GetProcessStatusText(char *szProcessStatusText,int nProcessStatus)
{
	if (nProcessStatus == 0)
	{
		sprintf_s(szProcessStatusText,32,"�Ѵ���");
	} 
	else
	{
		sprintf_s(szProcessStatusText,32,"δ����");
	}
}

void CDlgAlarmInfo::GetRelationVideoText(char *szRelationVideoText,int nRelationVideo)
{
	if (nRelationVideo == 0)
	{
		sprintf_s(szRelationVideoText,32,"�޹�����Ƶ");
	} 
	else
	{
		sprintf_s(szRelationVideoText,32,"�ѹ�����Ƶ");
	}
}

void CDlgAlarmInfo::FreeRealAlarmInfoList()
{
	int nNum = m_lstRealAlarmInfo.GetItemCount();
	for (int i=0; i<nNum; i++)
	{
		ACS_ALARM_INFO* pDeviceInfo = (ACS_ALARM_INFO*)m_lstRealAlarmInfo.GetItemData(i);
		if (pDeviceInfo != NULL)
		{
			delete pDeviceInfo;
			pDeviceInfo = NULL;
			m_lstRealAlarmInfo.SetItemData(i,(DWORD_PTR)pDeviceInfo);
		}
	}
	m_lstRealAlarmInfo.DeleteAllItems();
}

void CDlgAlarmInfo::FreeRealExAlarmInfoList()
{
	int nNum = m_lstRealExAlarmInfo.GetItemCount();
	for (int i=0; i<nNum; i++)
	{
		ACS_ALARM_INFO* pDeviceInfo = (ACS_ALARM_INFO*)m_lstRealExAlarmInfo.GetItemData(i);
		if (pDeviceInfo != NULL)
		{
			delete pDeviceInfo;
			pDeviceInfo = NULL;
			m_lstRealExAlarmInfo.SetItemData(i,(DWORD_PTR)pDeviceInfo);
		}
	}
	m_lstRealExAlarmInfo.DeleteAllItems();
}

void CDlgAlarmInfo::FreeDealAlarmInfoList()
{
	int nNum = m_lstDealAlarmInfo.GetItemCount();
	for (int i=0; i<nNum; i++)
	{
		ACS_ALARM_INFO* pDeviceInfo = (ACS_ALARM_INFO*)m_lstDealAlarmInfo.GetItemData(i);
		if (pDeviceInfo != NULL)
		{
			delete pDeviceInfo;
			pDeviceInfo = NULL;
			m_lstDealAlarmInfo.SetItemData(i,(DWORD_PTR)pDeviceInfo);
		}
	}
	m_lstDealAlarmInfo.DeleteAllItems();
}

void CDlgAlarmInfo::InitDealAlarmInfoList()
{
	FreeDealAlarmInfoList();
	int yx_index = 0;
	char sql_buf[1024]={0x0};
	MYSQL_RES* res;
	MYSQL_ROW row;

	//ȡ��ǰ��
	CTime time = CTime::GetCurrentTime();
	int nYear = time.GetYear();

	sprintf_s(sql_buf,"select a.rvu_id,a.dev_id,a.start_time,a.alarm_level,a.type,a.process_status,b.station_id,c.name, "
		" c.relation_video_status,d.station_name_videoplant,a.process_time,a.process_person,a.id from ass_alarm_%d a" 
		" left join ass_rvu b on a.rvu_id=b.rvu_id" 
		" left join ass_rvu_sm c on a.dev_id=c.id" 
		" left join ob_d5000_station d on b.station_id=d.station_id" 
		" where a.process_status=0",nYear);
	if (!mysql_query(g_mySqlData,sql_buf))
	{
		res = mysql_store_result(g_mySqlData);
		while (row = mysql_fetch_row(res))
		{
			ACS_ALARM_INFO *pAlarmInfo = new ACS_ALARM_INFO;
			pAlarmInfo->nDevId = atoi(row[1]);
			sprintf_s(pAlarmInfo->szAlarmStartTime,"%s",row[2]);
			pAlarmInfo->nPriorLevel = atoi(row[3]);
			pAlarmInfo->nAlarmType = atoi(row[4]);
			pAlarmInfo->nStatus = atoi(row[5]);
			pAlarmInfo->nStationId = atoi(row[6]);
			sprintf_s(pAlarmInfo->szDevName,"%s",row[7]);
			pAlarmInfo->nRelationVideo = atoi(row[8]);
			sprintf_s(pAlarmInfo->szStationName,"%s",row[9]);
			sprintf_s(pAlarmInfo->szAlarmProcessTime,"%s",row[10]);
			sprintf_s(pAlarmInfo->szAlarmProcessUser,"%s",row[11]);
			pAlarmInfo->nId = atoi(row[12]);

			m_lstDealAlarmInfo.InsertItem(yx_index,pAlarmInfo->szStationName);
			m_lstDealAlarmInfo.SetItemText(yx_index,1,pAlarmInfo->szDevName);

			char szAlarmTypeText[32]={0};
			GetAlarmTypeText(szAlarmTypeText,pAlarmInfo->nAlarmType);
			m_lstDealAlarmInfo.SetItemText(yx_index,2,szAlarmTypeText);

			m_lstDealAlarmInfo.SetItemText(yx_index,3,pAlarmInfo->szAlarmStartTime);
			m_lstDealAlarmInfo.SetItemText(yx_index,4,pAlarmInfo->szAlarmProcessTime);

			char szRelationVideoText[32]={0};
			GetRelationVideoText(szRelationVideoText,pAlarmInfo->nRelationVideo);
			m_lstDealAlarmInfo.SetItemText(yx_index,5,szRelationVideoText);

			char szPriorLeveText[32]={0};
			sprintf_s(szPriorLeveText,"%d",pAlarmInfo->nPriorLevel);
			m_lstDealAlarmInfo.SetItemText(yx_index,6,szPriorLeveText);

			char szProcessStatusText[32]={0};
			GetProcessStatusText(szProcessStatusText,pAlarmInfo->nStatus);
			m_lstDealAlarmInfo.SetItemText(yx_index,7,szProcessStatusText);

			m_lstDealAlarmInfo.SetItemText(yx_index,8,pAlarmInfo->szAlarmProcessUser);

			m_lstDealAlarmInfo.SetItemData(yx_index,(DWORD_PTR)pAlarmInfo);

			yx_index++;
		}
		mysql_free_result(res);
	}
}

void CDlgAlarmInfo::InitLocalDealAlarmInfoList()
{
	FreeLocalDealAlarmInfoList();
	int yx_index = 0;
	char sql_buf[1024]={0x0};
	MYSQL_RES* res;
	MYSQL_ROW row;

	//ȡ��ǰ��
	CTime time = CTime::GetCurrentTime();
	int nYear = time.GetYear();

	sprintf_s(sql_buf,"select a.rvu_id,a.dev_id,a.start_time,a.alarm_level,a.type,a.process_status,b.station_id,c.name, "
		" c.relation_video_status,d.station_name_videoplant,a.process_time,a.process_person,a.id from ass_alarm_%d a" 
		" left join ass_rvu b on a.rvu_id=b.rvu_id" 
		" left join ass_rvu_sm c on a.dev_id=c.id" 
		" left join ob_d5000_station d on b.station_id=d.station_id" 
		" where a.process_status=0 and a.process_person='%s'",nYear,g_userpower.username);
	if (!mysql_query(g_mySqlData,sql_buf))
	{
		res = mysql_store_result(g_mySqlData);
		while (row = mysql_fetch_row(res))
		{
			ACS_ALARM_INFO *pAlarmInfo = new ACS_ALARM_INFO;
			pAlarmInfo->nDevId = atoi(row[1]);
			sprintf_s(pAlarmInfo->szAlarmStartTime,"%s",row[2]);
			pAlarmInfo->nPriorLevel = atoi(row[3]);
			pAlarmInfo->nAlarmType = atoi(row[4]);
			pAlarmInfo->nStatus = atoi(row[5]);
			pAlarmInfo->nStationId = atoi(row[6]);
			sprintf_s(pAlarmInfo->szDevName,"%s",row[7]);
			pAlarmInfo->nRelationVideo = atoi(row[8]);
			sprintf_s(pAlarmInfo->szStationName,"%s",row[9]);
			sprintf_s(pAlarmInfo->szAlarmProcessTime,"%s",row[10]);
			sprintf_s(pAlarmInfo->szAlarmProcessUser,"%s",row[11]);
			pAlarmInfo->nId = atoi(row[12]);

			m_lstLocalDealAlarmInfo.InsertItem(yx_index,pAlarmInfo->szStationName);
			m_lstLocalDealAlarmInfo.SetItemText(yx_index,1,pAlarmInfo->szDevName);

			char szAlarmTypeText[32]={0};
			GetAlarmTypeText(szAlarmTypeText,pAlarmInfo->nAlarmType);
			m_lstLocalDealAlarmInfo.SetItemText(yx_index,2,szAlarmTypeText);

			m_lstLocalDealAlarmInfo.SetItemText(yx_index,3,pAlarmInfo->szAlarmStartTime);
			m_lstLocalDealAlarmInfo.SetItemText(yx_index,4,pAlarmInfo->szAlarmProcessTime);

			char szRelationVideoText[32]={0};
			GetRelationVideoText(szRelationVideoText,pAlarmInfo->nRelationVideo);
			m_lstLocalDealAlarmInfo.SetItemText(yx_index,5,szRelationVideoText);

			char szPriorLeveText[32]={0};
			sprintf_s(szPriorLeveText,"%d",pAlarmInfo->nPriorLevel);
			m_lstLocalDealAlarmInfo.SetItemText(yx_index,6,szPriorLeveText);

			char szProcessStatusText[32]={0};
			GetProcessStatusText(szProcessStatusText,pAlarmInfo->nStatus);
			m_lstLocalDealAlarmInfo.SetItemText(yx_index,7,szProcessStatusText);

			m_lstLocalDealAlarmInfo.SetItemText(yx_index,8,pAlarmInfo->szAlarmProcessUser);

			m_lstLocalDealAlarmInfo.SetItemData(yx_index,(DWORD_PTR)pAlarmInfo);

			yx_index++;
		}
		mysql_free_result(res);
	}
}

void CDlgAlarmInfo::FreeLocalDealAlarmInfoList()
{
	int nNum = m_lstLocalDealAlarmInfo.GetItemCount();
	for (int i=0; i<nNum; i++)
	{
		ACS_ALARM_INFO* pDeviceInfo = (ACS_ALARM_INFO*)m_lstLocalDealAlarmInfo.GetItemData(i);
		if (pDeviceInfo != NULL)
		{
			delete pDeviceInfo;
			pDeviceInfo = NULL;
			m_lstLocalDealAlarmInfo.SetItemData(i,(DWORD_PTR)pDeviceInfo);
		}
	}
	m_lstLocalDealAlarmInfo.DeleteAllItems();
}

void CDlgAlarmInfo::InitLocalHideAlarmInfoList()
{
	FreeLocalHidelAlarmInfoList();
	int yx_index = 0;
	char sql_buf[1024]={0x0};
	MYSQL_RES* res;
	MYSQL_ROW row;

	//ȡ��ǰ��
	CTime time = CTime::GetCurrentTime();
	int nYear = time.GetYear();

	sprintf_s(sql_buf,"select a.rvu_id,a.dev_id,a.start_time,a.alarm_level,a.type,a.process_status,b.station_id,c.name, "
		" c.relation_video_status,d.station_name_videoplant,a.process_time,a.process_person,a.id from ass_alarm_%d a" 
		" left join ass_rvu b on a.rvu_id=b.rvu_id" 
		" left join ass_rvu_sm c on a.dev_id=c.id" 
		" left join ob_d5000_station d on b.station_id=d.station_id" 
		" where a.process_status=1 and (a.dev_id in (select dev_id from ass_alarm_hide where user_id=%d))",nYear,g_userpower.userID);
	if (!mysql_query(g_mySqlData,sql_buf))
	{
		res = mysql_store_result(g_mySqlData);
		while (row = mysql_fetch_row(res))
		{
			ACS_ALARM_INFO *pAlarmInfo = new ACS_ALARM_INFO;
			pAlarmInfo->nDevId = atoi(row[1]);
			sprintf_s(pAlarmInfo->szAlarmStartTime,"%s",row[2]);
			pAlarmInfo->nPriorLevel = atoi(row[3]);
			pAlarmInfo->nAlarmType = atoi(row[4]);
			pAlarmInfo->nStatus = atoi(row[5]);
			pAlarmInfo->nStationId = atoi(row[6]);
			sprintf_s(pAlarmInfo->szDevName,"%s",row[7]);
			pAlarmInfo->nRelationVideo = atoi(row[8]);
			sprintf_s(pAlarmInfo->szStationName,"%s",row[9]);
			sprintf_s(pAlarmInfo->szAlarmProcessTime,"%s",row[10]);
			sprintf_s(pAlarmInfo->szAlarmProcessUser,"%s",row[11]);
			pAlarmInfo->nId = atoi(row[12]);

			m_lstLocalHideAlarmInfo.InsertItem(yx_index,pAlarmInfo->szStationName);
			m_lstLocalHideAlarmInfo.SetItemText(yx_index,1,pAlarmInfo->szDevName);

			char szAlarmTypeText[32]={0};
			GetAlarmTypeText(szAlarmTypeText,pAlarmInfo->nAlarmType);
			m_lstLocalHideAlarmInfo.SetItemText(yx_index,2,szAlarmTypeText);

			m_lstLocalHideAlarmInfo.SetItemText(yx_index,3,pAlarmInfo->szAlarmStartTime);
			m_lstLocalHideAlarmInfo.SetItemText(yx_index,4,pAlarmInfo->szAlarmProcessTime);

			char szRelationVideoText[32]={0};
			GetRelationVideoText(szRelationVideoText,pAlarmInfo->nRelationVideo);
			m_lstLocalHideAlarmInfo.SetItemText(yx_index,5,szRelationVideoText);

			char szPriorLeveText[32]={0};
			sprintf_s(szPriorLeveText,"%d",pAlarmInfo->nPriorLevel);
			m_lstLocalHideAlarmInfo.SetItemText(yx_index,6,szPriorLeveText);

			char szProcessStatusText[32]={0};
			GetProcessStatusText(szProcessStatusText,pAlarmInfo->nStatus);
			m_lstLocalHideAlarmInfo.SetItemText(yx_index,7,szProcessStatusText);

			m_lstLocalHideAlarmInfo.SetItemText(yx_index,8,pAlarmInfo->szAlarmProcessUser);

			m_lstLocalHideAlarmInfo.SetItemData(yx_index,(DWORD_PTR)pAlarmInfo);

			yx_index++;
		}
		mysql_free_result(res);
	}
}

void CDlgAlarmInfo::FreeLocalHidelAlarmInfoList()
{
	int nNum = m_lstLocalHideAlarmInfo.GetItemCount();
	for (int i=0; i<nNum; i++)
	{
		ACS_ALARM_INFO* pDeviceInfo = (ACS_ALARM_INFO*)m_lstLocalHideAlarmInfo.GetItemData(i);
		if (pDeviceInfo != NULL)
		{
			delete pDeviceInfo;
			pDeviceInfo = NULL;
			m_lstLocalHideAlarmInfo.SetItemData(i,(DWORD_PTR)pDeviceInfo);
		}
	}
	m_lstLocalHideAlarmInfo.DeleteAllItems();
}

void CDlgAlarmInfo::FreeLinkageActionList()
{
	int nNum = m_lstLinkageAction.GetItemCount();
	for (int i=0; i<nNum; i++)
	{
		ASS_LINKAGE_LIST_ITEM* pDeviceInfo = (ASS_LINKAGE_LIST_ITEM*)m_lstLinkageAction.GetItemData(i);
		delete pDeviceInfo;
		pDeviceInfo = NULL;
		m_lstLinkageAction.SetItemData(i,(DWORD_PTR)pDeviceInfo);
	}
	m_lstLinkageAction.DeleteAllItems();
}

void CDlgAlarmInfo::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	int nButtonJianxi = 2;//ÿ����ť֮��ļ�϶Ϊ��������
	// TODO: �ڴ˴������Ϣ����������
	CWnd *pWnd = NULL;
	CRect winrc,button_rect,list_rect,showAlarm_rect;

	int button_height = 30;
	int button_width = 100;
	int hideAlarmInfoHeight = 8;
	GetClientRect(&winrc);

	//ʵʱ��澯�б�
	pWnd = GetDlgItem(IDC_LIST_REAL_EX_ALARM_INFO);
	if (pWnd != NULL)
	{
		list_rect.top = winrc.top+button_height+hideAlarmInfoHeight;
		list_rect.bottom = winrc.bottom ;
		list_rect.left = winrc.left;
		list_rect.right = winrc.right;
		pWnd->MoveWindow(list_rect);

		pWnd->ShowWindow(SW_SHOW);
	}

	//δ����澯�б�
	pWnd = GetDlgItem(IDC_LIST_REAL_ALARM_INFO);
	if (pWnd != NULL)
	{
		list_rect.top = winrc.top+button_height+hideAlarmInfoHeight;
		list_rect.bottom = winrc.bottom ;
		list_rect.left = winrc.left;
		list_rect.right = winrc.right;
		pWnd->MoveWindow(list_rect);

		pWnd->ShowWindow(SW_SHOW);
	}

	//�Ѵ���澯�б�
	pWnd = GetDlgItem(IDC_LIST_DEAL_ALARM_INFO);
	if (pWnd != NULL)
	{
		list_rect.top = winrc.top+button_height+hideAlarmInfoHeight;
		list_rect.bottom = winrc.bottom ;
		list_rect.left = winrc.left;
		list_rect.right = winrc.right;
		pWnd->MoveWindow(list_rect);

		pWnd->ShowWindow(SW_HIDE);
	}

	////�����Ѵ���澯�б�
	//pWnd = GetDlgItem(IDC_LIST_LOCAL_DEAL_ALARM_INFO);
	//if (pWnd != NULL)
	//{
	//	list_rect.top = winrc.top+button_height+hideAlarmInfoHeight;
	//	list_rect.bottom = winrc.bottom ;
	//	list_rect.left = winrc.left;
	//	list_rect.right = winrc.right;
	//	pWnd->MoveWindow(list_rect);

	//	pWnd->ShowWindow(SW_HIDE);
	//}

	//�������θ澯�б�
	pWnd = GetDlgItem(IDC_LIST_LOCAL_HIDE_ALARM_INFO);
	if (pWnd != NULL)
	{
		list_rect.top = winrc.top+button_height+hideAlarmInfoHeight;
		list_rect.bottom = winrc.bottom ;
		list_rect.left = winrc.left;
		list_rect.right = winrc.right;
		pWnd->MoveWindow(list_rect);

		pWnd->ShowWindow(SW_HIDE);
	}

	pWnd = GetDlgItem(IDC_LIST_LINKAGE_ACTION);
	if (pWnd != NULL)
	{
		list_rect.top = winrc.top+button_height+hideAlarmInfoHeight;
		list_rect.bottom = winrc.bottom ;
		list_rect.left = winrc.left;
		list_rect.right = winrc.right;
		pWnd->MoveWindow(list_rect);

		pWnd->ShowWindow(SW_HIDE);
	}

	pWnd = GetDlgItem(IDC_BUTTON_REALTIME_EX_ALARM);
	if (pWnd != NULL)
	{
		button_rect.top = winrc.top+hideAlarmInfoHeight;
		button_rect.bottom = button_rect.top + button_height;
		button_rect.left = winrc.left + nButtonJianxi;
		button_rect.right = button_rect.left + button_width;
		pWnd->MoveWindow(button_rect);

		pWnd->ShowWindow(SW_SHOW);
	}

	pWnd = GetDlgItem(IDC_BUTTON_REALTIME_ALARM);
	if (pWnd != NULL)
	{
		button_rect.top = winrc.top+hideAlarmInfoHeight;
		button_rect.bottom = button_rect.top + button_height;
		button_rect.left = button_rect.right + nButtonJianxi;
		button_rect.right = button_rect.left + button_width;
		pWnd->MoveWindow(button_rect);

		pWnd->ShowWindow(SW_SHOW);
	}

	pWnd = GetDlgItem(IDC_BUTTON_PROCESSED_ALARM);
	if (pWnd != NULL)
	{
		button_rect.top = winrc.top+hideAlarmInfoHeight;
		button_rect.bottom = button_rect.top + button_height;
		button_rect.left = button_rect.right + nButtonJianxi;
		button_rect.right = button_rect.left + button_width;
		pWnd->MoveWindow(button_rect);

		pWnd->ShowWindow(SW_SHOW);
	}

	//pWnd = GetDlgItem(IDC_BUTTON_PROCESSED_HISTORY);
	//if (pWnd != NULL)
	//{
	//	button_rect.top = winrc.top+hideAlarmInfoHeight;
	//	button_rect.bottom = button_rect.top + button_height;
	//	button_rect.left = button_rect.right;
	//	button_rect.right = button_rect.left + button_width;
	//	pWnd->MoveWindow(button_rect);

	//	pWnd->ShowWindow(SW_SHOW);
	//}

	pWnd = GetDlgItem(IDC_BUTTON_HIDING_ALARM);
	if (pWnd != NULL)
	{
		button_rect.top = winrc.top+hideAlarmInfoHeight;
		button_rect.bottom = button_rect.top + button_height;
		button_rect.left = button_rect.right + nButtonJianxi;
		button_rect.right = button_rect.left + button_width;
		pWnd->MoveWindow(button_rect);

		pWnd->ShowWindow(SW_SHOW);
	}

	pWnd = GetDlgItem(IDC_BUTTON_LINKAGE);
	if (pWnd != NULL)
	{
		button_rect.top = winrc.top+hideAlarmInfoHeight;
		button_rect.bottom = button_rect.top + button_height;
		button_rect.left = button_rect.right + nButtonJianxi;
		button_rect.right = button_rect.left + button_width;
		pWnd->MoveWindow(button_rect);

		pWnd->ShowWindow(SW_SHOW);
	}

	pWnd = GetDlgItem(IDC_BUTTON_ALARM_STATISTICS);
	if (pWnd != NULL)
	{
		button_rect.top = winrc.top+hideAlarmInfoHeight;
		button_rect.bottom = button_rect.top + button_height;
		button_rect.left = button_rect.right + nButtonJianxi;
		button_rect.right = button_rect.left + button_width;
		pWnd->MoveWindow(button_rect);
		pWnd->ShowWindow(SW_SHOW);
	}

	//�澯���ģ���������
	pWnd = GetDlgItem(IDC_BUTTON_ALARM_SUBSCRIBE);
	if (pWnd != NULL)
	{
		button_rect.top = winrc.top+hideAlarmInfoHeight;
		button_rect.bottom = button_rect.top + button_height;
		button_rect.left = winrc.right - button_width;
		button_rect.right = button_rect.left + button_width;
		pWnd->MoveWindow(button_rect);

		pWnd->ShowWindow(SW_SHOW);
	}

	//��������
	pWnd = GetDlgItem(IDC_BUTTON_LINKAGE_CONFIG);
	if (pWnd != NULL)
	{
		button_rect.top = winrc.top+hideAlarmInfoHeight;
		button_rect.bottom = button_rect.top + button_height;
		button_rect.left = button_rect.left - button_width - nButtonJianxi;
		button_rect.right = button_rect.left + button_width;
		pWnd->MoveWindow(button_rect);

		pWnd->ShowWindow(SW_SHOW);
	}

	pWnd = GetDlgItem(IDC_BTN_SHOW_ALARM);
	if (pWnd != NULL)
	{
		showAlarm_rect.top = winrc.top;
		showAlarm_rect.bottom = winrc.top + hideAlarmInfoHeight;
		showAlarm_rect.left = (winrc.right+winrc.left)/2 - 20;
		showAlarm_rect.right = showAlarm_rect.left + 40;
		pWnd->MoveWindow(showAlarm_rect);

		pWnd->ShowWindow(SW_SHOW);
	}
}

//����ؿ��ư�ť����Ϣ���͵����Ի�����д���
void CDlgAlarmInfo::OnControlButton(UINT nID)
{
	AfxGetMainWnd()->PostMessage(OM_CONTROLBUTTON, nID,VEM_CONTROL_BUTTON_MESSAGE_TYPE_ALARM);
}

void CDlgAlarmInfo::OnBnClickedBtnShowAlarm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//this->ShowWindow(SW_HIDE);
}

void CDlgAlarmInfo::AlarmListShowHideControl(int nID)
{
	GetDlgItem(IDC_LIST_REAL_ALARM_INFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LIST_DEAL_ALARM_INFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LIST_LOCAL_DEAL_ALARM_INFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LIST_LOCAL_HIDE_ALARM_INFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LIST_REAL_EX_ALARM_INFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LIST_LINKAGE_ACTION)->ShowWindow(SW_HIDE);

	GetDlgItem(nID)->ShowWindow(SW_SHOW);
	
	//��ǰ��ʾ�����ĸ��б�
	m_nSelectedList = nID;
}

void CDlgAlarmInfo::OnBnClickedButtonRealtimeAlarm()
{
	AlarmListShowHideControl(IDC_LIST_REAL_ALARM_INFO);
}

void CDlgAlarmInfo::OnBnClickedButtonProcessedAlarm()
{
	AlarmListShowHideControl(IDC_LIST_DEAL_ALARM_INFO);
}

void CDlgAlarmInfo::OnBnClickedButtonProcessedHistory()
{
	AlarmListShowHideControl(IDC_LIST_LOCAL_DEAL_ALARM_INFO);
}

void CDlgAlarmInfo::OnBnClickedButtonHidingAlarm()
{
	AlarmListShowHideControl(IDC_LIST_LOCAL_HIDE_ALARM_INFO);
}

void CDlgAlarmInfo::OnBnClickedButtonAlarmSubscribe()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (g_pMainDlg != NULL)
	{
		if (g_pMainDlg->m_pDlgAlarmSubscribe == NULL)
		{
			g_pMainDlg->m_pDlgAlarmSubscribe = new CDlgAlarmSubscribe();
			if (g_pMainDlg->m_pDlgAlarmSubscribe == NULL)
				return;

			g_pMainDlg->m_pDlgAlarmSubscribe->Create(IDD_DIALOG_ALARM_SUBSCRIBE, g_pMainDlg);
			g_pMainDlg->m_pDlgAlarmSubscribe->CenterWindow();
		}

		g_pMainDlg->m_pDlgAlarmSubscribe->ShowWindow(SW_SHOW);
	}
}

void CDlgAlarmInfo::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		{
			KillTimer(nIDEvent);

			InitRealAlarmInfoList();
			InitDealAlarmInfoList();
			//InitLocalDealAlarmInfoList();
			InitLocalHideAlarmInfoList();
		}
		break;
	}

	CDialog::OnTimer(nIDEvent);
}

//δ����澯�б�
void CDlgAlarmInfo::OnNMRClickListRealAlarmInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_lstRealAlarmInfo.GetFirstSelectedItemPosition();

	if (pos == NULL)
		return;

	int index = m_lstRealAlarmInfo.GetNextSelectedItem(pos);

	if (index < 0)
		return;

	m_nIndex = index;
	ACS_ALARM_INFO* pAlarmInfo = (ACS_ALARM_INFO*)m_lstRealAlarmInfo.GetItemData(index);
	memcpy(&m_tAlarmInfo,pAlarmInfo,sizeof(ACS_ALARM_INFO));

	//��ȡ��dev_id��������Ƶ
	T_LINKAGE_CAMERA_INFO tCameraCode[MAX_DEV_RELATION_CAMERA];
	memset(tCameraCode, 0, sizeof(T_LINKAGE_CAMERA_INFO)*MAX_DEV_RELATION_CAMERA);
	int nCameraCount = 0;
	GetCameraCodeByDevId(pAlarmInfo->nDevId, tCameraCode, &nCameraCount);

	//�����˵�
	PopRightMenu(tCameraCode, nCameraCount);

	*pResult = 0;
}

//����devId��ȡ������cameraCode
void CDlgAlarmInfo::GetCameraCodeByDevId(int nDevId, T_LINKAGE_CAMERA_INFO *tCameraCode, int *nCount)
{
	char sql_buf[1024] = {0x0};
	MYSQL_RES* res;
	MYSQL_ROW row;
	int nCameraCount = 0;

	sprintf_s(sql_buf,1024,"select camera_code,dev_id,camera_preset_id,preset_name from ass_camerapreset where dev_id=%d", nDevId);
	if (!mysql_query(g_mySqlData,sql_buf))
	{
		res = mysql_store_result(g_mySqlData);
		while (row = mysql_fetch_row(res))
		{
			sprintf_s(tCameraCode[nCameraCount].szCameraCode,64,"%s",row[0]);
			tCameraCode[nCameraCount].nDevId = atoi(row[1]);
			tCameraCode[nCameraCount].nPresetId = atoi(row[2]);
			sprintf_s(tCameraCode[nCameraCount].szPresetName,64,"%s",row[3]);

			nCameraCount++;

			if (nCameraCount == 16)
			{
				break;
			}
		}
		mysql_free_result(res);
	}

	*nCount = nCameraCount;
}

void CDlgAlarmInfo::PopRightMenu(T_LINKAGE_CAMERA_INFO *tCameraCode, int nCount)
{
	if (pPopMenu != NULL)
	{
		pPopMenu.DestroyMenu();
		pPopMenu.CreatePopupMenu();
	}

	if (menuMain != NULL)
	{
		menuMain.DestroyMenu();
		menuMain.CreatePopupMenu();
	}
	
	memset(m_tLinkageCameraInfo, 0, sizeof(T_LINKAGE_CAMERA_INFO)*MAX_DEV_RELATION_CAMERA);
	memcpy(m_tLinkageCameraInfo,tCameraCode,sizeof(T_LINKAGE_CAMERA_INFO)*MAX_DEV_RELATION_CAMERA);

	for (int i = 0;i<nCount;i++)
	{
		pPopMenu.AppendMenu(MF_STRING,ID_LINKAGE_INFO1+i,tCameraCode[i].szPresetName);
	}

	if (nCount == 0)
	{
		pPopMenu.AppendMenu(MF_STRING,ID_LINKAGE_INFO1,"(��)");
		pPopMenu.EnableMenuItem(0,MF_BYPOSITION|MF_DISABLED|MF_GRAYED);
	}

	//���ݲ�ͬ�б���ʾ��ͬ�Ĳ˵�
	if (m_nSelectedList == IDC_LIST_REAL_ALARM_INFO)
	{
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,(UINT)pPopMenu.m_hMenu,"������Ƶ");
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,ID_SHOW_ELECMAP,"�ڵ��ӵ�ͼչʾʵʱ��Ϣ");
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,ID_PROCESS_ALARM,"����澯");
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,ID_HIDE_ALARM,"���θ澯");
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,ID_REMOVE_ALL_ITEMS,"����б�");
	}
	if (m_nSelectedList == IDC_LIST_REAL_EX_ALARM_INFO)
	{
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,(UINT)pPopMenu.m_hMenu,"������Ƶ");
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,ID_SHOW_ELECMAP,"�ڵ��ӵ�ͼչʾʵʱ��Ϣ");
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,ID_PROCESS_ALARM,"����澯");
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,ID_HIDE_ALARM,"���θ澯");
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,ID_REMOVE_ALL_ITEMS,"����б�");
	}
	if (m_nSelectedList == IDC_LIST_DEAL_ALARM_INFO)
	{
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,(UINT)pPopMenu.m_hMenu,"������Ƶ");
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,ID_SHOW_ELECMAP,"�ڵ��ӵ�ͼչʾʵʱ��Ϣ");
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,ID_RECOVER_ALARM,"�ָ��澯");
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,ID_COMPLETE_PROCESS_ALARM,"��ɴ���");
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,ID_REMOVE_ALL_ITEMS,"����б�");
	}
	if (m_nSelectedList == IDC_LIST_LOCAL_HIDE_ALARM_INFO)
	{
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,(UINT)pPopMenu.m_hMenu,"������Ƶ");
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,ID_SHOW_ELECMAP,"�ڵ��ӵ�ͼչʾʵʱ��Ϣ");
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,ID_CANCEL_HIDE_ALARM,"ȡ������");
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,ID_REMOVE_ALL_ITEMS,"����б�");
	}
	if (m_nSelectedList == IDC_LIST_LINKAGE_ACTION)
	{
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,(UINT)pPopMenu.m_hMenu,"������Ƶ");
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,ID_SHOW_ELECMAP,"�ڵ��ӵ�ͼչʾʵʱ��Ϣ");
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,ID_DELETE_LINKAGE_RECORD,"ɾ������������¼");
		menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,ID_REMOVE_ALL_ITEMS,"����б�");
	}

	CPoint point;
	GetCursorPos(&point);

	menuMain.TrackPopupMenu(TPM_RIGHTBUTTON,point.x,point.y,this);
}

void CDlgAlarmInfo::OnClickLinkageCamera( UINT nID )
{
	if (nID>ID_LINKAGE_INFO16||nID<ID_LINKAGE_INFO1)
	{
		return;
	}

	//������ͷ
	OpenCamera(m_tLinkageCameraInfo[nID-ID_LINKAGE_INFO1].szCameraCode);

	//ת��Ԥ��λ������ɷ������ת
	//ToPreset(&m_tLinkageCameraInfo[nID-ID_LINKAGE_INFO1]);
}

void CDlgAlarmInfo::GetCameraInfoByCameraCode(_T_NODE_INFO* pNodeInfo,char *szCameraCode)
{
	char sql_buf[1024] = {0};
	MYSQL_RES * res = NULL;
	MYSQL_ROW	row ;
	int camera_type = -1;
	int decode_tag = 0;
	int camera_status = 0;
	int streamless = 0;
	int anfang_flag = 0;
	char camera_name[64]={0};
	int diagnosis_flag = 0;
	char szDvrType[32] = {0};
	sprintf_s(sql_buf, "SELECT a.camera_id, a.camera_code, a.camera_name, a.camera_type,a.camera_decodetag,a.camera_status,a.streamless,t2.anfang_flag as anfang_flag," 
		" t1.id,t1.dvr_type,t1.dvr_id,t1.dvr_ip,t1.link_port,t2.channel,t1.adminuser,t1.adminpasswd,t1.station_group,t1.station_name,t1.station_seq,t2.camera_id" 
		" FROM ob_d5000_camera_station_%d a " 
		" left join video_camera t2 on a.camera_code=t2.camera_id " 
		" left join video_dvr t1 on t2.dvr_id=t1.dvr_id" 
		" where a.camera_code='%s'", m_tAlarmInfo.nStationId,szCameraCode);

	if (!mysql_query(g_mySqlData, sql_buf))
	{
		res = mysql_store_result(g_mySqlData);

		if ( row = mysql_fetch_row( res ) )
		{
			camera_type = atoi(row[3]);
			if (camera_type <= 0||camera_type > 8)
				return;

			decode_tag = atoi(row[4]);
			camera_status = atoi(row[5]);
			streamless = atoi(row[6]);
			anfang_flag = atoi(row[7]);
			sprintf_s(camera_name,64,"%s",row[2]);

			sprintf (pNodeInfo->node_name, "%s", row[2]);
			sprintf(pNodeInfo->node_num, "%s", row[1]);

			pNodeInfo->node_id = m_tAlarmInfo.nStationId;
			pNodeInfo->node_status = camera_status;
			pNodeInfo->node_streamless = streamless;
			pNodeInfo->node_longitude = 0;
			pNodeInfo->node_latitude = 0;
			pNodeInfo->node_type = 3;

			if (decode_tag == 1)
			{
				decode_tag = 150;
			}

			if (pNodeInfo->node_type == 2)//վ��
			{
				//��¼��һ��վ������
				if (strlen(g_VideoPageViewInfo.szFirstStationName) == 0)
				{
					strcpy_s(g_VideoPageViewInfo.szFirstStationName,sizeof(g_VideoPageViewInfo.szFirstStationName)-1,pNodeInfo->node_name);
				}
			}

			pNodeInfo->node_decodetag = decode_tag;
			sprintf(pNodeInfo->node_station, "%s", m_tAlarmInfo.szStationName);

			_T_CAMERA_INFO * pCameraDvrInfo = NULL;
			_T_DVR_INFO * pDvrInfo = NULL;
			pCameraDvrInfo = &pNodeInfo->camera_info;
			pDvrInfo = &pCameraDvrInfo->dvr_info;

			pDvrInfo->dvr_id = atoi(row[8]);
			strcpy_s(szDvrType,sizeof(szDvrType),row[9]);
			pDvrInfo->dvr_type = AppGetCameraDvrType(szDvrType);
			strcpy_s(pDvrInfo->dvr_num,sizeof(pDvrInfo->dvr_num),row[10]);
			strcpy_s(pDvrInfo->dvr_ip,sizeof(pDvrInfo->dvr_ip),row[11]);
			pDvrInfo->dvr_port = atoi(row[12]);
			pCameraDvrInfo->channel = atoi(row[13]);
			strcpy_s(pDvrInfo->dvr_user,sizeof(pDvrInfo->dvr_user),row[14]);
			strcpy_s(pDvrInfo->dvr_password,sizeof(pDvrInfo->dvr_password),row[15]);
			strcpy_s(pDvrInfo->station_num,sizeof(pDvrInfo->station_num),row[16]);
			strcpy_s(pDvrInfo->station_name,sizeof(pDvrInfo->station_name),row[17]);
			pDvrInfo->station_id = atoi(row[18]);
			strcpy_s(pCameraDvrInfo->camera_num,sizeof(pCameraDvrInfo->camera_num),row[19]);
		}
		mysql_free_result(res) ;
	}
}

void CDlgAlarmInfo::OpenCamera(char *szCameraCode)
{
	if (g_TuneCycle_MehtodInfo.bState == true)
	{
		MessageBox("��ǰ������Ѳ״̬","��ƵԤ��",MB_ICONWARNING);
		return;
	}

	if (g_VideoPageViewInfo.nStatus == AUTOVIDEO_PAGEVIEW_STATUS_RUNNING)
	{
		MessageBox("��ǰ�����˹��Զ�Ѳ��״̬","��ƵԤ��",MB_ICONWARNING);
		return;
	}

	_T_NODE_INFO pNodeInfo;
	memset(&pNodeInfo,0,sizeof(_T_NODE_INFO));
	GetCameraInfoByCameraCode(&pNodeInfo,szCameraCode);

	// ��ʾ�ýڵ�Ϊ����ͷ,����Ƶ
	VIDEO_SIP_CALL_SERVER_INFO VideoSipCallServerInfo;
	memset(&VideoSipCallServerInfo,0,sizeof(VideoSipCallServerInfo));

	if (IsCameraVideoLinkByVideoPlatform(g_nClientVideoLinkType,pNodeInfo.node_decodetag))//�ͻ�����Ƶ���ӷ�ʽ
	{
		VideoSipCallServerInfo.nType = 1;//ͨ������ƽ̨
		VideoSipCallServerInfo.nDecodeTag = pNodeInfo.node_decodetag;
	}
	else
	{
		VideoSipCallServerInfo.nType = 2;//ֱ������ǰ���豸
		VideoSipCallServerInfo.nDecodeTag = pNodeInfo.camera_info.dvr_info.dvr_type;
	}

	VideoSipCallServerInfo.nStatus = pNodeInfo.node_status;
	VideoSipCallServerInfo.nStreamless = pNodeInfo.node_streamless;
	strcpy_s(VideoSipCallServerInfo.szCode,sizeof(VideoSipCallServerInfo.szCode),pNodeInfo.node_num);

	if (g_pMainDlg != NULL&&g_pMainDlg->m_iFocuseWindowID >= 0&&g_pMainDlg->m_iFocuseWindowID < g_pMainDlg->m_FormsNum)
	{
		VideoSipCallServerInfo.nScreenId = g_pMainDlg->m_iFocuseWindowID;
	}
	else
	{
		VideoSipCallServerInfo.nScreenId = 0;
	}

	strcpy_s(VideoSipCallServerInfo.szName,sizeof(VideoSipCallServerInfo.szName),pNodeInfo.node_name);
	strcpy_s(VideoSipCallServerInfo.szStation,sizeof(VideoSipCallServerInfo.szStation),pNodeInfo.node_station);
	memcpy(&VideoSipCallServerInfo.server_node_info,&pNodeInfo,sizeof(VideoSipCallServerInfo.server_node_info));

	int nOperate_type = WM_DEVICE_VIDEO_OPERATE_RESULT_NOTAG_ONLINE_VIDEO;
	int nOperate_result = WM_DEVICE_VIDEO_OPERATE_RESULT_NOTAG_ONLINE_VIDEO;

	if (pNodeInfo.node_status == 0)
	{
		nOperate_type = WM_DEVICE_VIDEO_OPERATE_RESULT_NOTAG_OFFLINE_VIDEO;
		nOperate_result = WM_DEVICE_VIDEO_OPERATE_RESULT_NOTAG_OFFLINE_VIDEO;
	}
	else if (pNodeInfo.node_status == 2)
	{
		nOperate_type = WM_DEVICE_VIDEO_OPERATE_RESULT_TAG_ONLINE_VIDEO;
		nOperate_result = WM_DEVICE_VIDEO_OPERATE_RESULT_TAG_ONLINE_VIDEO;
	}
	else if (pNodeInfo.node_status == 3)
	{
		nOperate_type = WM_DEVICE_VIDEO_OPERATE_RESULT_TAG_OFFLINE_VIDEO;
		nOperate_result = WM_DEVICE_VIDEO_OPERATE_RESULT_TAG_OFFLINE_VIDEO;
	}

	g_ThreadVideoOperateNumberInfo.DeviceVideoInNumerAdd();

	g_pMainDlg->ThreadPoolDispatchTask(ThreadMakeCallCameraServer,(void *)&VideoSipCallServerInfo,sizeof(VideoSipCallServerInfo),2);

	memcpy(&m_pCameraNodeInfo,&pNodeInfo,sizeof(_T_NODE_INFO));

	return;
}

void CDlgAlarmInfo::ToPreset(T_LINKAGE_CAMERA_INFO *pLinkageCameraInfo)
{
	int nRet = DvrPtzControl_Devsdk(m_pCameraNodeInfo.camera_info.dvr_info.dvr_ip,
		m_pCameraNodeInfo.camera_info.dvr_info.dvr_port,
		m_pCameraNodeInfo.camera_info.dvr_info.dvr_name,
		m_pCameraNodeInfo.camera_info.dvr_info.dvr_password,
		m_pCameraNodeInfo.camera_info.dvr_info.dvr_type,
		m_pCameraNodeInfo.camera_info.dvr_info.dvr_id,
		m_pCameraNodeInfo.camera_info.channel,
		GOTOPRESET,pLinkageCameraInfo->nPresetId);

	if (nRet == FALSE)
	{
		MessageBox("ת��Ԥ��λʧ�ܣ�","����ϵͳ");
		return ;
	}
}

void CDlgAlarmInfo::OnClickProcessAlarm()
{
	if(MessageBox("ȷ��Ҫ�������澯���Ϊ�Ѵ�����","�澯����" ,MB_ICONEXCLAMATION|MB_OKCANCEL)==IDCANCEL)
		return;

	//�������ݿ�ĸ澯��¼�ֶδ���״̬��������Ա������ʱ��
	if (!UpdataDBRecord(&m_tAlarmInfo))
		return;

	//���Ѵ���澯��¼�м���������¼
	InsertRecordToDealList(&m_tAlarmInfo);

	//ɾ��������¼
	DeleteRecordFromRealList(&m_tAlarmInfo);
}

bool CDlgAlarmInfo::UpdataDBRecord(ACS_ALARM_INFO *pAlarmInfo)
{
	char sql_buf[1024] = {0};
	//ȡ����
	CTime time = CTime::GetCurrentTime();
	int nYear = time.GetYear();
	//ȡ����ʱ��
	char szProcessAlarmTime[128] = {0};
	sprintf(szProcessAlarmTime, "%04d-%02d-%02d %02d:%02d:%02d",
		time.GetYear(), time.GetMonth(), time.GetDay(),
		time.GetHour(), time.GetMinute(), time.GetSecond());
	//ȡ������Ա
	char szUserName[32] = {0};
	sprintf(szUserName, "%s",g_userpower.username);
	//ƴsql���
	sprintf_s(sql_buf, "UPDATE ass_alarm_%d SET process_status=%d,process_person='%s',process_time='%s' WHERE dev_id=%d and start_time='%s'",
		nYear,0,szUserName,szProcessAlarmTime,pAlarmInfo->nDevId,pAlarmInfo->szAlarmStartTime);

	if (mysql_query(g_mySqlData, sql_buf))
	{
		return false;
	}
	
	//�����ڴ�����
	pAlarmInfo->nStatus = 0;
	sprintf_s(pAlarmInfo->szAlarmProcessTime,32,szProcessAlarmTime);
	sprintf_s(pAlarmInfo->szAlarmProcessUser,32,szUserName);
}

bool CDlgAlarmInfo::UpdataCompleteProcessRecordToDB(ACS_ALARM_INFO *pAlarmInfo)
{
	char sql_buf[1024] = {0};
	//ȡ����
	CTime time = CTime::GetCurrentTime();
	int nYear = time.GetYear();
	//ȡ����ʱ��
	char szProcessAlarmTime[128] = {0};
	sprintf(szProcessAlarmTime, "%04d-%02d-%02d %02d:%02d:%02d",
		time.GetYear(), time.GetMonth(), time.GetDay(),
		time.GetHour(), time.GetMinute(), time.GetSecond());
	//ȡ������Ա
	char szUserName[32] = {0};
	sprintf(szUserName, "%s",g_userpower.username);
	//ƴsql���
	sprintf_s(sql_buf, "UPDATE ass_alarm_%d SET process_status=%d,process_person='%s',process_time='%s' WHERE dev_id=%d and start_time='%s'",
		nYear,2,szUserName,szProcessAlarmTime,pAlarmInfo->nDevId,pAlarmInfo->szAlarmStartTime);

	if (mysql_query(g_mySqlData, sql_buf))
	{
		return false;
	}
}



void CDlgAlarmInfo::InsertRecordToDealList(ACS_ALARM_INFO *pAlarmInfo)
{
	InsertDealListOneRecord(0,pAlarmInfo);
}

void CDlgAlarmInfo::InsertDealListOneRecord(int nIndex,ACS_ALARM_INFO *pAlarmInfo)
{
	ACS_ALARM_INFO *pNewAlarmInfo = new ACS_ALARM_INFO;
	memcpy(pNewAlarmInfo,pAlarmInfo,sizeof(ACS_ALARM_INFO));

	m_lstDealAlarmInfo.InsertItem(nIndex,pNewAlarmInfo->szStationName);
	m_lstDealAlarmInfo.SetItemText(nIndex,1,pNewAlarmInfo->szDevName);

	char szAlarmTypeText[32]={0};
	GetAlarmTypeText(szAlarmTypeText,pNewAlarmInfo->nAlarmType);
	m_lstDealAlarmInfo.SetItemText(nIndex,2,szAlarmTypeText);

	m_lstDealAlarmInfo.SetItemText(nIndex,3,pNewAlarmInfo->szAlarmStartTime);
	m_lstDealAlarmInfo.SetItemText(nIndex,4,pNewAlarmInfo->szAlarmProcessTime);

	char szRelationVideoText[32]={0};
	GetRelationVideoText(szRelationVideoText,pNewAlarmInfo->nRelationVideo);
	m_lstDealAlarmInfo.SetItemText(nIndex,5,szRelationVideoText);

	char szPriorLeveText[32]={0};
	sprintf_s(szPriorLeveText,"%d",pNewAlarmInfo->nPriorLevel);
	m_lstDealAlarmInfo.SetItemText(nIndex,6,szPriorLeveText);

	char szProcessStatusText[32]={0};
	GetProcessStatusText(szProcessStatusText,pNewAlarmInfo->nStatus);
	m_lstDealAlarmInfo.SetItemText(nIndex,7,szProcessStatusText);

	m_lstDealAlarmInfo.SetItemText(nIndex,8,pNewAlarmInfo->szAlarmProcessUser);

	m_lstDealAlarmInfo.SetItemData(nIndex,(DWORD_PTR)pNewAlarmInfo);
}

void CDlgAlarmInfo::DeleteRecordFromRealList(ACS_ALARM_INFO *pAlarmInfo)
{
	if (m_nSelectedList == IDC_LIST_REAL_ALARM_INFO)
	{
		FreeListOneRecord(m_nIndex,&m_lstRealAlarmInfo);
	}
	if (m_nSelectedList == IDC_LIST_REAL_EX_ALARM_INFO)
	{
		FreeListOneRecord(m_nIndex,&m_lstRealExAlarmInfo);
	}
	
}

void CDlgAlarmInfo::DeleteListOneRecord(int nIndex,CListCtrl *list)
{
	list->DeleteItem(nIndex);
}

void CDlgAlarmInfo::FreeLinkageActionListOneRecord(int nIndex)
{
	ASS_LINKAGE_LIST_ITEM* pLinkageListItem = (ASS_LINKAGE_LIST_ITEM*)m_lstLinkageAction.GetItemData(nIndex);
	if (pLinkageListItem != NULL)
	{
		delete pLinkageListItem;
		pLinkageListItem = NULL;
		m_lstLinkageAction.SetItemData(nIndex,(DWORD_PTR)pLinkageListItem);
	}
	m_lstLinkageAction.DeleteItem(nIndex);
}

void CDlgAlarmInfo::FreeListOneRecord(int nIndex,CListCtrl *list)
{
	ACS_ALARM_INFO* pAlarmInfo = (ACS_ALARM_INFO*)list->GetItemData(nIndex);
	if (pAlarmInfo != NULL)
	{
		delete pAlarmInfo;
		pAlarmInfo = NULL;
		list->SetItemData(nIndex,(DWORD_PTR)pAlarmInfo);
	}
	list->DeleteItem(nIndex);
}

void CDlgAlarmInfo::InsertRecodeToLocalDealList(ACS_ALARM_INFO *pAlarmInfo)
{
	InsertLocalDealListOneRecord(0,pAlarmInfo);
}

void CDlgAlarmInfo::InsertLocalDealListOneRecord(int nIndex,ACS_ALARM_INFO *pAlarmInfo)
{
	m_lstLocalDealAlarmInfo.InsertItem(nIndex,pAlarmInfo->szStationName);
	m_lstLocalDealAlarmInfo.SetItemText(nIndex,1,pAlarmInfo->szDevName);

	char szAlarmTypeText[32]={0};
	GetAlarmTypeText(szAlarmTypeText,pAlarmInfo->nAlarmType);
	m_lstLocalDealAlarmInfo.SetItemText(nIndex,2,szAlarmTypeText);

	m_lstLocalDealAlarmInfo.SetItemText(nIndex,3,pAlarmInfo->szAlarmStartTime);
	m_lstLocalDealAlarmInfo.SetItemText(nIndex,4,pAlarmInfo->szAlarmProcessTime);

	char szRelationVideoText[32]={0};
	GetRelationVideoText(szRelationVideoText,pAlarmInfo->nRelationVideo);
	m_lstLocalDealAlarmInfo.SetItemText(nIndex,5,szRelationVideoText);

	char szPriorLeveText[32]={0};
	sprintf_s(szPriorLeveText,"%d",pAlarmInfo->nPriorLevel);
	m_lstLocalDealAlarmInfo.SetItemText(nIndex,6,szPriorLeveText);

	char szProcessStatusText[32]={0};
	GetProcessStatusText(szProcessStatusText,pAlarmInfo->nStatus);
	m_lstLocalDealAlarmInfo.SetItemText(nIndex,7,szProcessStatusText);

	m_lstLocalDealAlarmInfo.SetItemText(nIndex,8,pAlarmInfo->szAlarmProcessUser);

	m_lstLocalDealAlarmInfo.SetItemData(nIndex,(DWORD_PTR)pAlarmInfo);
}

void CDlgAlarmInfo::OnBnClickedButtonRealtimeExAlarm()
{
	AlarmListShowHideControl(IDC_LIST_REAL_EX_ALARM_INFO);
}

void CDlgAlarmInfo::OnClickHideAlarm()
{
	int nDevId = m_tAlarmInfo.nDevId;
	int nUserId = g_userpower.userID;

	//�����ݿ��в������μ�¼������������
	//if (!InsertHideAlarmInfoToDB(nDevId,nUserId))
	//{
	//	MessageBox("����ʧ��!");
	//	return;
	//}

	//֪ͨ�����
	SendHideAlarmMessageToServer(nUserId,nDevId,HIDE_DEV);
	//����Ҫ�ȴ��澯���ķ�����Ϣ���سɹ�
	if (!WaitTimeOut(&g_CommonEvent, 2*1000))
	{
		MessageBox("���γɹ���");
	}
	else
	{
		MessageBox("���������س�ʱ��");
	}
}

void CDlgAlarmInfo::SendHideAlarmMessageToServer(int nUserId,int nDevId,int nAction)
{
	g_pACSClient->SendHideDevRequest(nUserId,nDevId,nAction);
}

bool CDlgAlarmInfo::InsertHideAlarmInfoToDB(int nDevId,int nUserId)
{
	char sql_buf[1024] = {0};
	sprintf_s(sql_buf, "insert into ass_alarm_hide(user_id,dev_id) values(%d,%d)",
		nUserId,nDevId);

	if (mysql_query(g_mySqlData, sql_buf))
	{
		return false;
	}
}

void CDlgAlarmInfo::OnNMRClickListRealExAlarmInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_lstRealExAlarmInfo.GetFirstSelectedItemPosition();

	if (pos == NULL)
		return;

	int index = m_lstRealExAlarmInfo.GetNextSelectedItem(pos);

	if (index < 0)
		return;

	m_nIndex = index;
	ACS_ALARM_INFO* pAlarmInfo = (ACS_ALARM_INFO*)m_lstRealExAlarmInfo.GetItemData(index);
	memcpy(&m_tAlarmInfo,pAlarmInfo,sizeof(ACS_ALARM_INFO));

	//��ȡ��dev_id��������Ƶ
	T_LINKAGE_CAMERA_INFO tCameraCode[MAX_DEV_RELATION_CAMERA];
	memset(tCameraCode, 0, sizeof(T_LINKAGE_CAMERA_INFO)*MAX_DEV_RELATION_CAMERA);
	int nCameraCount = 0;
	GetCameraCodeByDevId(pAlarmInfo->nDevId, tCameraCode, &nCameraCount);

	//�����˵�
	PopRightMenu(tCameraCode, nCameraCount);

	*pResult = 0;
}

void CDlgAlarmInfo::OnNMRClickListDealAlarmInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_lstDealAlarmInfo.GetFirstSelectedItemPosition();

	if (pos == NULL)
		return;

	int index = m_lstDealAlarmInfo.GetNextSelectedItem(pos);

	if (index < 0)
		return;

	m_nIndex = index;
	ACS_ALARM_INFO* pAlarmInfo = (ACS_ALARM_INFO*)m_lstDealAlarmInfo.GetItemData(index);
	memcpy(&m_tAlarmInfo,pAlarmInfo,sizeof(ACS_ALARM_INFO));

	//��ȡ��dev_id��������Ƶ
	T_LINKAGE_CAMERA_INFO tCameraCode[MAX_DEV_RELATION_CAMERA];
	memset(tCameraCode, 0, sizeof(T_LINKAGE_CAMERA_INFO)*MAX_DEV_RELATION_CAMERA);
	int nCameraCount = 0;
	GetCameraCodeByDevId(pAlarmInfo->nDevId, tCameraCode, &nCameraCount);

	//�����˵�
	PopRightMenu(tCameraCode, nCameraCount);

	*pResult = 0;
}

void CDlgAlarmInfo::OnNMRClickListLocalDealAlarmInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_lstLocalDealAlarmInfo.GetFirstSelectedItemPosition();

	if (pos == NULL)
		return;

	int index = m_lstLocalDealAlarmInfo.GetNextSelectedItem(pos);

	if (index < 0)
		return;

	m_nIndex = index;
	ACS_ALARM_INFO* pAlarmInfo = (ACS_ALARM_INFO*)m_lstLocalDealAlarmInfo.GetItemData(index);
	memcpy(&m_tAlarmInfo,pAlarmInfo,sizeof(ACS_ALARM_INFO));

	//��ȡ��dev_id��������Ƶ
	T_LINKAGE_CAMERA_INFO tCameraCode[MAX_DEV_RELATION_CAMERA];
	memset(tCameraCode, 0, sizeof(T_LINKAGE_CAMERA_INFO)*MAX_DEV_RELATION_CAMERA);
	int nCameraCount = 0;
	GetCameraCodeByDevId(pAlarmInfo->nDevId, tCameraCode, &nCameraCount);

	//�����˵�
	PopRightMenu(tCameraCode, nCameraCount);

	*pResult = 0;
}

void CDlgAlarmInfo::OnNMRClickListLocalHideAlarmInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_lstLocalHideAlarmInfo.GetFirstSelectedItemPosition();

	if (pos == NULL)
		return;

	int index = m_lstLocalHideAlarmInfo.GetNextSelectedItem(pos);

	if (index < 0)
		return;

	m_nIndex = index;
	ACS_ALARM_INFO* pAlarmInfo = (ACS_ALARM_INFO*)m_lstLocalHideAlarmInfo.GetItemData(index);
	memcpy(&m_tAlarmInfo,pAlarmInfo,sizeof(ACS_ALARM_INFO));

	//��ȡ��dev_id��������Ƶ
	T_LINKAGE_CAMERA_INFO tCameraCode[MAX_DEV_RELATION_CAMERA];
	memset(tCameraCode, 0, sizeof(T_LINKAGE_CAMERA_INFO)*MAX_DEV_RELATION_CAMERA);
	int nCameraCount = 0;
	GetCameraCodeByDevId(pAlarmInfo->nDevId, tCameraCode, &nCameraCount);

	//�����˵�
	PopRightMenu(tCameraCode, nCameraCount);

	*pResult = 0;
}

void CDlgAlarmInfo::OnClickRecoverAlarm()
{
	//�������ݿ�״̬
	UpdataRecoverAlarmStatusToDB(UN_PROCESS_ALARM,&m_tAlarmInfo);

	//�������澯���뵽δ�����б���
	InsertRecodeToRealList(&m_tAlarmInfo);

	//���Ѵ����б���ɾ��������¼
	FreeListOneRecord(m_nIndex, &m_lstDealAlarmInfo);
}

void CDlgAlarmInfo::InsertRecodeToRealList(ACS_ALARM_INFO* pAlarmInfo)
{
	InsertRealListOneRecord(0,pAlarmInfo);
}

void CDlgAlarmInfo::InsertRealExListOneRecord(int nIndex, ACS_ALARM_INFO* pAlarmInfo)
{
	ACS_ALARM_INFO *pNewAlarmInfo = new ACS_ALARM_INFO;
	memcpy(pNewAlarmInfo,pAlarmInfo,sizeof(ACS_ALARM_INFO));

	m_lstRealExAlarmInfo.InsertItem(nIndex,pNewAlarmInfo->szStationName);
	m_lstRealExAlarmInfo.SetItemText(nIndex,1,pNewAlarmInfo->szDevName);

	char szAlarmTypeText[32]={0};
	GetAlarmTypeText(szAlarmTypeText,pNewAlarmInfo->nAlarmType);
	m_lstRealExAlarmInfo.SetItemText(nIndex,2,szAlarmTypeText);

	m_lstRealExAlarmInfo.SetItemText(nIndex,3,pNewAlarmInfo->szAlarmStartTime);

	char szRelationVideoText[32]={0};
	GetRelationVideoText(szRelationVideoText,pNewAlarmInfo->nRelationVideo);
	m_lstRealExAlarmInfo.SetItemText(nIndex,4,szRelationVideoText);

	char szPriorLeveText[32]={0};
	sprintf_s(szPriorLeveText,"%d",pNewAlarmInfo->nPriorLevel);
	m_lstRealExAlarmInfo.SetItemText(nIndex,5,szPriorLeveText);

	char szProcessStatusText[32]={0};
	GetProcessStatusText(szProcessStatusText,pNewAlarmInfo->nStatus);
	m_lstRealExAlarmInfo.SetItemText(nIndex,6,szProcessStatusText);

	m_lstRealExAlarmInfo.SetItemData(nIndex,(DWORD_PTR)pNewAlarmInfo);
}

void CDlgAlarmInfo::ProcessPushAlarmData(char* pPushAlarm, int nCount)
{
	PUSH_ALARM_RESPONSE *pPushAlarmInfo= (PUSH_ALARM_RESPONSE*)pPushAlarm;

	//�л����澯�б�
	AlarmListShowHideControl(IDC_LIST_REAL_EX_ALARM_INFO);

	for (int i=0;i<nCount;i++)
	{
		//������ת����ACS_ALARM_INFO����
		ACS_ALARM_INFO tAlarmInfo;
		ConvertPushAlarmToAlarmInfo(pPushAlarmInfo, &tAlarmInfo);

		//����InsertRealListOneRecord����������
		InsertRealExListOneRecord(0, &tAlarmInfo);

		pPushAlarmInfo++;
	}
}

void CDlgAlarmInfo::ProcessLinkageRealtimeInfo(char* pLinkageRealtimeInfo, int nCount)
{
	LINKAGE_REALTIME_INFO_RESPONSE *pLinkageRealtime= (LINKAGE_REALTIME_INFO_RESPONSE*)pLinkageRealtimeInfo;

	//�л��������б�
	AlarmListShowHideControl(IDC_LIST_LINKAGE_ACTION);

	for (int i=0;i<nCount;i++)
	{
		//������ת����ASS_LINKAGE_LIST_ITEM����
		ASS_LINKAGE_LIST_ITEM tLinkageListItem;
		memset(&tLinkageListItem, 0, sizeof(ASS_LINKAGE_LIST_ITEM));
		ConvertLinkageRealtimeInfoToLinkageListItem(pLinkageRealtime, &tLinkageListItem);

		//����InsertLinkageActionListOneRecord����������
		InsertLinkageActionListOneRecord(0, &tLinkageListItem);

		//�Զ����������¼�
		AutoProcessLinkageAction(&tLinkageListItem);

		pLinkageRealtime++;
	}
}

void CDlgAlarmInfo::AutoProcessLinkageAction(ASS_LINKAGE_LIST_ITEM *pLinkageRealtimeInfo)
{
	//��������һ�������¼���ʱ��
	double nTime = CheckLastLinkageMessageTime(pLinkageRealtimeInfo->szStartTime, m_strLastLinkageEventTime.GetBuffer());

	//��������¼��л�ʱ��
	if (nTime > m_tAssLinkageConfig.nChangeTime)
	{
		//����Ƕ໭��չʾ
		if (m_tAssLinkageConfig.nShowType == LINKAGE_SHOW_TYPE_MULTIVIDEO)
		{
			if (m_tAssLinkageConfig.nShowVideo == 1)
			{
				//������ͷ
				OpenCamera(pLinkageRealtimeInfo->szCamreaCode);
			}

		}

		if (m_tAssLinkageConfig.nShowType == LINKAGE_SHOW_TYPE_ELECMAP)
		{
			//����������ʾ���ӵ�ͼ������λ��
			ShowElecMapOnMainDlgAndChangePosition(pLinkageRealtimeInfo);
			
			if (m_tAssLinkageConfig.nShowVideo == 1)
			{
				//�򿪵��ӵ�ͼ�������Ƶ
				g_pMainDlg->m_pDlgCameraAndControl->OpenCamera(pLinkageRealtimeInfo->szCamreaCode);
			}
		}

		//���浱ǰ����ʱ��
		SaveCurrentLinkageTime(pLinkageRealtimeInfo->szStartTime);
	}
	else
	{
		
	}
}

void CDlgAlarmInfo::ShowElecMapOnMainDlgAndChangePosition(ASS_LINKAGE_LIST_ITEM *pLinkageRealtimeInfo)
{
	//�򿪵��ӵ�ͼ
	ACS_DEV_INFO tDevInfo;
	GetDevInfoByDevId(&tDevInfo, pLinkageRealtimeInfo->nDevId);

	int nRet = OpenASceneElecMapBySM(tDevInfo.nRvuId, tDevInfo.nSmId);
	if (nRet == 2)
	{
		MessageBox("û�в鵽���豸�ĵ��ӵ�ͼ��");
		return;
	}
	//OpenASceneElecMap("500kV�����ű�_�����豸");

	//���豸״̬�������ӵ�ͼ

	//�������ڷ��ʹ򿪵��ӵ�ͼ���ں���Ƶ�ƿ��ƴ��ڵ���Ϣ
	g_pMainDlg->PostMessage(OM_CONTROLBUTTON, IDC_MENU_ELECMAP, VEM_CONTROL_BUTTON_MESSAGE_TYPE_MENU);
}

void CDlgAlarmInfo::SaveCurrentLinkageTime(char *szCurrentTime)
{
	m_strLastLinkageEventTime.Format("%s", szCurrentTime);
}

void CDlgAlarmInfo::ConvertLinkageRealtimeInfoToLinkageListItem(LINKAGE_REALTIME_INFO_RESPONSE *pLinkageRealtimeInfo, ASS_LINKAGE_LIST_ITEM *pLinkageListItem)
{
	ACS_DEV_INFO tDevInfo;
	memset(&tDevInfo, 0, sizeof(ACS_DEV_INFO));
	GetDevInfoByDevId(&tDevInfo, pLinkageRealtimeInfo->nDevID);

	ASS_CAMERA_INFO tCameraInfo;
	memset(&tCameraInfo, 0, sizeof(ASS_CAMERA_INFO));
	GetCameraNameByCameraCode(&tCameraInfo, pLinkageRealtimeInfo->szCamreaCode);

	pLinkageListItem->nDevId = pLinkageRealtimeInfo->nDevID;
	pLinkageListItem->nPresetNum = pLinkageRealtimeInfo->nPresetNum;
	sprintf_s(pLinkageListItem->szCamreaCode, 32, pLinkageRealtimeInfo->szCamreaCode);
	sprintf_s(pLinkageListItem->szCameraName, 32, tCameraInfo.szCameraName);
	sprintf_s(pLinkageListItem->szDevName, 32, tDevInfo.szDevName);
	sprintf_s(pLinkageListItem->szStartTime, 32, pLinkageRealtimeInfo->szStartTime);
}

//����һ������ʵʱ��Ϣ����
void CDlgAlarmInfo::InsertLinkageActionListOneRecord(int nIndex, ASS_LINKAGE_LIST_ITEM *pAssLinkageRealtimeInfo)
{
	ASS_LINKAGE_LIST_ITEM *pLinkageListItem = new ASS_LINKAGE_LIST_ITEM;
	memcpy(pLinkageListItem, pAssLinkageRealtimeInfo, sizeof(ASS_LINKAGE_LIST_ITEM));

	m_lstLinkageAction.InsertItem(nIndex, pLinkageListItem->szDevName);
	m_lstLinkageAction.SetItemText(nIndex, 1, pLinkageListItem->szCameraName);
	m_lstLinkageAction.SetItemText(nIndex, 2, "����ͷ");
	m_lstLinkageAction.SetItemText(nIndex, 3, "תԤ��λ");

	CString strPresetNum = "";
	strPresetNum.Format("%d", pLinkageListItem->nPresetNum);
	m_lstLinkageAction.SetItemText(nIndex, 4, strPresetNum.GetBuffer());

	m_lstLinkageAction.SetItemText(nIndex, 5, pLinkageListItem->szStartTime);

	m_lstLinkageAction.SetItemData(nIndex,(DWORD_PTR)pLinkageListItem);
}

void CDlgAlarmInfo::ConvertPushAlarmToAlarmInfo(PUSH_ALARM_RESPONSE *pPushAlarm, ACS_ALARM_INFO *pAlarmInfo)
{
	ACS_DEV_INFO tDevInfo;
	GetDevInfoByDevId(&tDevInfo, pPushAlarm->nDevId);

	ACS_STATION_INFO tStationInfo;
	GetStationInfoByStationId(&tStationInfo, pPushAlarm->nStationId);

	pAlarmInfo->nAlarmType = pPushAlarm->nAlarmType;
	pAlarmInfo->nDevId = tDevInfo.nDevId;
	pAlarmInfo->nPriorLevel = pPushAlarm->nPriorLevel;
	pAlarmInfo->nRelationVideo = tDevInfo.nRelationVideo;
	pAlarmInfo->nStationId = tStationInfo.nStationId;
	pAlarmInfo->nStatus = 1;//δ����
	sprintf_s(pAlarmInfo->szAlarmStartTime, 32, pPushAlarm->szAlarmStartTime);
	sprintf_s(pAlarmInfo->szDevName, 32, tDevInfo.szDevName);
	sprintf_s(pAlarmInfo->szStationName, 32, tStationInfo.szStationName);
}

void CDlgAlarmInfo::InsertRealListOneRecord(int nIndex, ACS_ALARM_INFO* pAlarmInfo)
{
	ACS_ALARM_INFO *pNewAlarmInfo = new ACS_ALARM_INFO;
	memcpy(pNewAlarmInfo,pAlarmInfo,sizeof(ACS_ALARM_INFO));

	m_lstRealAlarmInfo.InsertItem(nIndex,pNewAlarmInfo->szStationName);
	m_lstRealAlarmInfo.SetItemText(nIndex,1,pNewAlarmInfo->szDevName);

	char szAlarmTypeText[32]={0};
	GetAlarmTypeText(szAlarmTypeText,pNewAlarmInfo->nAlarmType);
	m_lstRealAlarmInfo.SetItemText(nIndex,2,szAlarmTypeText);

	m_lstRealAlarmInfo.SetItemText(nIndex,3,pNewAlarmInfo->szAlarmStartTime);

	char szRelationVideoText[32]={0};
	GetRelationVideoText(szRelationVideoText,pNewAlarmInfo->nRelationVideo);
	m_lstRealAlarmInfo.SetItemText(nIndex,4,szRelationVideoText);

	char szPriorLeveText[32]={0};
	sprintf_s(szPriorLeveText,"%d",pNewAlarmInfo->nPriorLevel);
	m_lstRealAlarmInfo.SetItemText(nIndex,5,szPriorLeveText);

	char szProcessStatusText[32]={0};
	GetProcessStatusText(szProcessStatusText,pNewAlarmInfo->nStatus);
	m_lstRealAlarmInfo.SetItemText(nIndex,6,szProcessStatusText);

	m_lstRealAlarmInfo.SetItemData(nIndex,(DWORD_PTR)pNewAlarmInfo);
}



bool CDlgAlarmInfo::UpdataRecoverAlarmStatusToDB(int nStatus, ACS_ALARM_INFO* pAlarmInfo)
{
	//ȡ����
	CTime time = CTime::GetCurrentTime();
	int nYear = time.GetYear();

	char sql_buf[1024] = {0};
	//ƴsql���
	sprintf_s(sql_buf, "UPDATE ass_alarm_%d SET process_status=%d WHERE id=%d",
		nYear,nStatus,pAlarmInfo->nId);

	if (mysql_query(g_mySqlData, sql_buf))
	{
		return false;
	}

	//�����ڴ�����
	pAlarmInfo->nStatus = nStatus;
}

void CDlgAlarmInfo::OnClickCompleteProcessAlarm()
{
	//�������ݿ�����
	UpdataCompleteProcessRecordToDB(&m_tAlarmInfo);

	//ɾ����¼
	FreeListOneRecord(m_nIndex,&m_lstDealAlarmInfo);
}

void CDlgAlarmInfo::OnClickCancelHideAlarm()
{
	//֪ͨ�����
	int nDevId = m_tAlarmInfo.nDevId;
	int nUserId = g_userpower.userID;

	SendHideAlarmMessageToServer(nUserId,nDevId,CANCEL_HIDE_DEV);

	//ɾ��������¼
	FreeListOneRecord(m_nIndex,&m_lstLocalHideAlarmInfo);
}

void CDlgAlarmInfo::OnBnClickedButtonLinkage()
{
	AlarmListShowHideControl(IDC_LIST_LINKAGE_ACTION);
}

void CDlgAlarmInfo::OnBnClickedButtonLinkageConfig()
{
	//�����������ô���
	CDlgLinkageConfig dlgLinkageConfig;
	if (dlgLinkageConfig.DoModal() == IDOK)
	{
		MessageBox("���óɹ���");

		//��������������Ϣ
		GetLinkageConfig(&m_tAssLinkageConfig);
	}
}

void CDlgAlarmInfo::OnClickDeleteLinkageRecord()
{
	//ɾ��������¼
	FreeLinkageActionListOneRecord(m_nIndex);
}

void CDlgAlarmInfo::OnNMRClickListLinkageAction(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	POSITION pos = m_lstLinkageAction.GetFirstSelectedItemPosition();

	if (pos == NULL)
		return;

	int index = m_lstLinkageAction.GetNextSelectedItem(pos);

	if (index < 0)
		return;

	m_nIndex = index;
	ASS_LINKAGE_LIST_ITEM* pLinkageListItem = (ASS_LINKAGE_LIST_ITEM*)m_lstLinkageAction.GetItemData(index);
	memcpy(&m_tLinkageListItem,pLinkageListItem,sizeof(ASS_LINKAGE_LIST_ITEM));

	//��ȡ��dev_id��������Ƶ
	T_LINKAGE_CAMERA_INFO tCameraCode[MAX_DEV_RELATION_CAMERA];
	memset(tCameraCode, 0, sizeof(T_LINKAGE_CAMERA_INFO)*MAX_DEV_RELATION_CAMERA);
	int nCameraCount = 0;
	GetCameraCodeByDevId(pLinkageListItem->nDevId, tCameraCode, &nCameraCount);

	//�����˵�
	PopRightMenu(tCameraCode, nCameraCount);
	*pResult = 0;
}

void CDlgAlarmInfo::OnClickRemoveAllItems()
{
	if (m_nSelectedList == IDC_LIST_LINKAGE_ACTION)
	{
		FreeLinkageActionList();
	}
	if (m_nSelectedList == IDC_LIST_LOCAL_DEAL_ALARM_INFO)
	{
		FreeLocalDealAlarmInfoList();
	}
	if (m_nSelectedList == IDC_LIST_LOCAL_HIDE_ALARM_INFO)
	{
		FreeLocalHidelAlarmInfoList();
	}
	if (m_nSelectedList == IDC_LIST_REAL_ALARM_INFO)
	{
		FreeRealAlarmInfoList();
	}
	if (m_nSelectedList == IDC_LIST_REAL_EX_ALARM_INFO)
	{
		FreeRealExAlarmInfoList();
	}
}

void CDlgAlarmInfo::OnClickOpenElecMap()
{
	//�򿪵��ӵ�ͼ
	ACS_DEV_INFO tDevInfo;
	if (m_nSelectedList == IDC_LIST_LINKAGE_ACTION)
	{
		GetDevInfoByDevId(&tDevInfo, m_tLinkageListItem.nDevId);
	}
	else
	{
		GetDevInfoByDevId(&tDevInfo, m_tAlarmInfo.nDevId);
	}

	int nRet = OpenASceneElecMapBySM(tDevInfo.nRvuId, tDevInfo.nSmId);
	if (nRet != ERROR_NONE)
	{
		MessageBox("û�в鵽���豸�ĵ��ӵ�ͼ��");
		return;
	}

	g_pMainDlg->PostMessage(OM_CONTROLBUTTON, 1286, VEM_CONTROL_BUTTON_MESSAGE_TYPE_MENU);
}

void CDlgAlarmInfo::OnClickOpenVideo()
{
	MessageBox("����Ƶ!");
}
BOOL CDlgAlarmInfo::OnEraseBkgnd(CDC* pDC)
{
	CDC srcDC;
	srcDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBmp;
	BITMAP bmp;
	CRect winrc;

	GetClientRect(&winrc);

	pOldBmp = srcDC.SelectObject(m_pBackBmp);
	m_pBackBmp->GetBitmap(&bmp);
	pDC->StretchBlt(0,0,winrc.Width(),winrc.Height(),
		&srcDC,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	srcDC.SelectObject(pOldBmp);
	return TRUE;

	return CDialog::OnEraseBkgnd(pDC);
}

void CDlgAlarmInfo::OnBnClickedButtonAlarmStatistics()
{
	CDlgAlarmStatistics dlgAlarmStatistics;
	if (dlgAlarmStatistics.DoModal() == IDOK)
	{
		return;
	}
}
