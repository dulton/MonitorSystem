// ACSSystemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ACSSystem.h"
#include "ACSSystemDlg.h"
#include "DBExcute.h"
#include "ACSSystemAPI.h"
#include "RVUServerParse.h"

#define MAIN_BUTTON_WIDTH 140
#define MAIN_BUTTON_HIGHT 90

TSM g_t_TSM[MAX_SM_NUM_PER_STATION]={0x0};
int g_nTSM = 0;

TNODE g_t_TNODE[MAX_NODE_NUM_PER_STATION]={0x0};
int g_nTNODE = 0;

HANDLE g_hGetNodeEvent = NULL;

RVUConfig g_RVUConfig;

DBConfigParam g_DBConfigParam;
int g_bIsStationCU = 1;
int g_bIsRVUDevice = 1;
char g_szLoginName[32]={0x0};

char g_szLocalIPAddr[24]={0x0};
char g_szPTUServerIPAddr[24]={0x0};
int g_nPTUServerPort=0;
bool g_bLoginOK = false;

RECV_PACKET g_recv_packet;
int g_nDataLen = 0;

COMMONTHREADPOOL g_parse_rvu_thread;
COMMONTHREADPOOL g_read_real_data;

//////////////////////////////////////////////////////////////////////////
COMMONTHREADPOOL g_CommnThreadPool;
//////////////////////////////////////////////////////////////////////////
COMMONTHREADPOOL g_netopenthread;
COMMONTHREADPOOL g_parsexmlthread;
int g_nNetInitHandle = -1;
NETHANDLE g_ComNetHandle = -1;

VEM_USER_CONFIG_INFO* g_pConfigInfo = NULL;

CACSSystemDlg* g_pMainDlg = NULL;

_T_ASS_RVU_INFO_ g_tAssRVU[MAX_RVU_NUM_PER_STATION]; 
int g_nAssRVUNum = 0;

T_LINKAGE_CAMERA_INFO g_tLinkageCameraInfo[MAX_DEV_RELATION_CAMERA];
int g_nLinkageCameraInfoCount = 0;

void ReadRVUInfo()
{
	g_nAssRVUNum = 0;
	memset(&g_tAssRVU,0,sizeof(_T_ASS_RVU_INFO_)*MAX_RVU_NUM_PER_STATION);

	char sql_buf[1024]={0x0};

	MYSQL_RES* res;
	MYSQL_ROW row; 
	sprintf_s(sql_buf,1024,"%s","SELECT rvu_id,station_id,rvu_code,rvu_name,rvu_ip,rvu_port,rvu_username,rvu_password FROM ass_rvu");
	if (!mysql_query(&mysql_cameralist,sql_buf))
	{
		res = mysql_store_result(&mysql_cameralist);
		while (row = mysql_fetch_row(res))
		{
			g_tAssRVU[g_nAssRVUNum].rvu_id = atoi(row[0]);
			g_tAssRVU[g_nAssRVUNum].station_id = atoi(row[1]);
			sprintf_s(g_tAssRVU[g_nAssRVUNum].rvu_code,32,"%s",row[2]);
			sprintf_s(g_tAssRVU[g_nAssRVUNum].rvu_name,64,"%s",row[3]);
			sprintf_s(g_tAssRVU[g_nAssRVUNum].rvu_ip,16,"%s",row[4]);
			g_tAssRVU[g_nAssRVUNum].rvu_port = atoi(row[5]);
			sprintf_s(g_tAssRVU[g_nAssRVUNum].rvu_username,32,"%s",row[6]);
			sprintf_s(g_tAssRVU[g_nAssRVUNum].rvu_userpassword,32,"%s",row[7]);
			g_nAssRVUNum++;
		}
		mysql_free_result(res);
	}
}

// CACSSystemDlg �Ի���

IMPLEMENT_DYNAMIC(CACSSystemDlg, CDialog)

CACSSystemDlg::CACSSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CACSSystemDlg::IDD, pParent)
	,m_nRvuID(0)
{
	m_pViewOut = NULL;
	m_pStationNode = NULL;
	memset(g_tLinkageCameraInfo, 0, sizeof(T_LINKAGE_CAMERA_INFO)*MAX_DEV_RELATION_CAMERA);
}

CACSSystemDlg::~CACSSystemDlg()
{
	// TODO: �ڴ˴������Ϣ����������

	if (m_pViewOut!=NULL)
	{
		delete[] m_pViewOut;
		m_pViewOut = NULL;
	}

	FreeDVR();
}

void CACSSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_YX_DEVICE, m_ListYX);
	DDX_Control(pDX, IDC_CHECK_ALL_SUBSYSTEM, m_CheckAll);
	DDX_Control(pDX, IDC_CHECK_SECURITY_SYSTEM, m_CheckSecurity);
	DDX_Control(pDX, IDC_CHECK_FIRE_SYSTEM, m_CheckFire);
	DDX_Control(pDX, IDC_CHECK_DOOR_SYSTEM, m_CheckDoor);
	DDX_Control(pDX, IDC_STATIC_ELECMAP, m_staticElecmap);
	DDX_Control(pDX, IDC_COMBO_YT_SPEED, m_ComboYTSpeed);
	DDX_Control(pDX, IDC_TREE_STATION, m_treeStation);
}


BEGIN_MESSAGE_MAP(CACSSystemDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECK_ALL_SUBSYSTEM, &CACSSystemDlg::OnBnClickedCheckAllSubsystem)
	ON_BN_CLICKED(IDC_CHECK_SECURITY_SYSTEM, &CACSSystemDlg::OnBnClickedCheckSecuritySystem)
	ON_BN_CLICKED(IDC_CHECK_FIRE_SYSTEM, &CACSSystemDlg::OnBnClickedCheckFireSystem)
	ON_BN_CLICKED(IDC_CHECK_DOOR_SYSTEM, &CACSSystemDlg::OnBnClickedCheckDoorSystem)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_UP, &CACSSystemDlg::OnBnClickedButtonUp)
	ON_MESSAGE(OM_MESSAGE_MULTI_YTCONTROL,&CACSSystemDlg::OnStartYTControl)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_STATION, &CACSSystemDlg::OnNMDblclkTreeStation)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_YX_DEVICE, &CACSSystemDlg::OnNMDblclkListYxDevice)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_YX_DEVICE, &CACSSystemDlg::OnNMRClickListYxDevice)
	ON_COMMAND_RANGE(10001, 10016, &CACSSystemDlg::OnClickLinkageCamera)
	ON_COMMAND(ID_DLG_ACSSYSTEM_CLOSE_VIDEO, &CACSSystemDlg::OnClickACSSystemDlgCloseVideo)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void ReadRealDataThread(void* arg)
{
	CACSSystemDlg* pDlg = (CACSSystemDlg*)arg;
	while(true)
	{
		if (pDlg->m_pStationNode != NULL)
		{
			pDlg->RefreshYXList(pDlg->m_pStationNode->station_id);
			pDlg->RefreshYCList(pDlg->m_pStationNode->station_id);
		}
		Sleep(1000*5);
	}
}

// CACSSystemDlg ��Ϣ�������
BOOL CACSSystemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//���ڿؼ���ʼ��
	InitCtrl();

	g_pMainDlg = this;

	//��ô�������Ļ����ϵ�е�λ��
	ModifyStyle(0, WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
	ModifyStyleEx(0,  WS_EX_APPWINDOW);
	SetWindowText(_T("ACSSystem"));

	CRect WindowRect;
	GetWindowRect(&WindowRect);

	//��ÿͻ�������Ļ����ϵ�е�λ��
	CRect ClientRect;
	RepositionBars(0,0xffff,AFX_IDW_PANE_FIRST,reposQuery,&ClientRect);
	ClientToScreen(&ClientRect);
	//���ȫ����С����������������
	CRect rtClient;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rtClient,0);
	int nFullWidth = rtClient.Width();
	int nFullHeight = rtClient.Height();
	int nWidth = GetSystemMetrics(SM_CXSCREEN);
	int nHeight = GetSystemMetrics(SM_CYSCREEN);

	m_WndRect.left = 0;
	m_WndRect.right = nWidth;
	m_WndRect.top = 0 + MAIN_TITLE_HEIGHT + 7;
	m_WndRect.bottom = nHeight;

	WINDOWPLACEMENT wndpl;
	wndpl.length = sizeof(WINDOWPLACEMENT);
	wndpl.flags = 0;
	wndpl.showCmd = SW_HIDE;
	wndpl.rcNormalPosition = m_WndRect;

	SetWindowPlacement(&wndpl);

	if (InitDVR()==FALSE)
	{
		MessageBox("������ʼ��ʧ�ܣ�","����ϵͳ");
		exit(-1);
		return FALSE;
	}

	//�������ݿ�
	if (connectDB()<0)
	{
		MessageBox("�������ݿ�ʧ�ܣ������˳���","����ϵͳ");
		exit(-1);
	}

	//��ʼ�����վ�б�����
	InitStationList();

	g_hGetNodeEvent = CreateEvent(NULL,TRUE,NULL,NULL);

	ComInitThreadPool(&g_parse_rvu_thread,SINGLEFIFOTHREADPOOL|COPYARG,-1,1,100);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CACSSystemDlg::InitStationList()
{
	m_treeStation.DeleteAllItems();

	char sql_buf[1024]={0x0};

	MYSQL_RES	* res;
	MYSQL_ROW	row;

	int rnum = 0;
	sprintf_s(sql_buf, "%s","SHOW TABLES LIKE 'ob_d5000_station'");
	if (!mysql_query(&mysql_cameralist, sql_buf))
	{
		res = mysql_store_result(&mysql_cameralist);
		rnum = mysql_num_rows(res);
		mysql_free_result( res ) ;
	}

	if (rnum == 0)
	{
		MessageBox("û�б��վ��Ϣ����ʼ��ʧ��","����ϵͳ");
		return ;
	}

	HTREEITEM	hMainItem = NULL;
	hMainItem = m_treeStation.InsertItem("����ʡ������˾", 1, 1, TVI_ROOT, NULL);
	SetStationNodeInfo(hMainItem,-1,NULL,NULL,0,0);
	//վ��
	HTREEITEM hItem1 = NULL,hItem2 = NULL,hItem3 = NULL,hStationItem = NULL;
	char station_code[32]={0x0};
	char station_name[64]={0x0};
	//500kV
	hItem1 = m_treeStation.InsertItem("500kV���վ",7,7,hMainItem);
	SetStationNodeInfo(hItem1,-1,NULL,NULL,1,0);
	sprintf_s(sql_buf,"%s","SELECT station_id,station_name_videoplant,station_code_videoplant FROM ob_d5000_station "
		"where voltage_class = 500");
	if (!mysql_query(&mysql_cameralist,sql_buf))
	{
		res = mysql_store_result(&mysql_cameralist);
		while (row = mysql_fetch_row(res))
		{
			hItem2 = m_treeStation.InsertItem(row[1],8,8,hItem1);
			SetStationNodeInfo(hItem2,atoi(row[0]),row[2],row[1],2,0);
		}
		mysql_free_result(res);
	}

	//220kV
	hItem1 = m_treeStation.InsertItem("220kV���վ",7,7,hMainItem);
	SetStationNodeInfo(hItem1,-1,NULL,NULL,1,0);
	sprintf_s(sql_buf,"%s","SELECT station_id,station_name_videoplant,station_code_videoplant FROM ob_d5000_station "
		"where voltage_class = 220");
	if (!mysql_query(&mysql_cameralist,sql_buf))
	{
		res = mysql_store_result(&mysql_cameralist);
		while (row = mysql_fetch_row(res))
		{
			hItem2 = m_treeStation.InsertItem(row[1],8,8,hItem1);
			SetStationNodeInfo(hItem2,atoi(row[0]),row[2],row[1],2,0);
		}
		mysql_free_result(res);
	}

	//110kV
	hItem1 = m_treeStation.InsertItem("110kV���վ",7,7,hMainItem);
	SetStationNodeInfo(hItem1,-1,NULL,NULL,1,0);
	sprintf_s(sql_buf,"%s","SELECT station_id,station_name_videoplant,station_code_videoplant FROM ob_d5000_station "
		"where voltage_class = 110");
	if (!mysql_query(&mysql_cameralist,sql_buf))
	{
		res = mysql_store_result(&mysql_cameralist);
		while (row = mysql_fetch_row(res))
		{
			hItem2 = m_treeStation.InsertItem(row[1],8,8,hItem1);
			SetStationNodeInfo(hItem2,atoi(row[0]),row[2],row[1],2,0);
		}
		mysql_free_result(res);
	}
	//ƽ̨
}

void CACSSystemDlg::SetStationNodeInfo(HTREEITEM hItem,int station_id,char* station_code,char* station_name,int node_type,int connect_state)
{
	StationNode* pStationNode = NULL;
	pStationNode = new StationNode;
	memset(pStationNode,0,sizeof(StationNode));

	sprintf_s(pStationNode->station_code,"%s",station_code);
	sprintf_s(pStationNode->station_name,"%s",station_name);
	pStationNode->node_type = node_type;
	pStationNode->station_id = station_id;
	pStationNode->connect_ptu = connect_state;

	m_treeStation.SetItemData(hItem,(DWORD)pStationNode);
}

BOOL CACSSystemDlg::InitDVR()
{

	Init_DevSdk();

	return TRUE;
}

LRESULT CACSSystemDlg::OnStartYTControl(WPARAM wParam,LPARAM lParam)
{
	int ytcommand = 0;

	TRACE("-----iMove=%d,iCommandID=%d------\n\n",lParam,wParam);

	if (m_bVideoOpen == false)
	{
		return 0;
	}

	if(lParam == 0)
	{
		switch (wParam)
		{
		case 1://��̨������-����
			{
				DvrPtzControl_Devsdk(m_camera_info.ip_addr,m_camera_info.ip_port,m_camera_info.login_name,m_camera_info.login_password,
					m_camera_info.dvr_type,m_camera_info.dvr_id,m_camera_info.channel,TILTUPSTOP,5);
			}
			break;
		case 2://��̨������-����
			{
				DvrPtzControl_Devsdk(m_camera_info.ip_addr,m_camera_info.ip_port,m_camera_info.login_name,m_camera_info.login_password,
					m_camera_info.dvr_type,m_camera_info.dvr_id,m_camera_info.channel,TILTDOWNSTOP,5);
			}
			break;
		case 3://��̨������-����
			{
				DvrPtzControl_Devsdk(m_camera_info.ip_addr,m_camera_info.ip_port,m_camera_info.login_name,m_camera_info.login_password,
					m_camera_info.dvr_type,m_camera_info.dvr_id,m_camera_info.channel,PANLEFTSTOP,5);
			}
			break;
		case 4://��̨������-����
			{
				DvrPtzControl_Devsdk(m_camera_info.ip_addr,m_camera_info.ip_port,m_camera_info.login_name,m_camera_info.login_password,
					m_camera_info.dvr_type,m_camera_info.dvr_id,m_camera_info.channel,PANRIGHTSTOP,5);
			}
			break;
		case 5://����-����
			{
				DvrPtzControl_Devsdk(m_camera_info.ip_addr,m_camera_info.ip_port,m_camera_info.login_name,m_camera_info.login_password,
					m_camera_info.dvr_type,m_camera_info.dvr_id,m_camera_info.channel,ZOOMOUTSTOP,5);
			}
			break;
		case 6://��Զ-����
			{
				DvrPtzControl_Devsdk(m_camera_info.ip_addr,m_camera_info.ip_port,m_camera_info.login_name,m_camera_info.login_password,
					m_camera_info.dvr_type,m_camera_info.dvr_id,m_camera_info.channel,ZOOMINSTOP,5);
			}
			break;
		case 7://��̨���ƽ����-����
			{

			}
			break;
		case 8://��̨���ƽ���Զ-����
			{

			}
			break;
		case 9://��̨���ƹ�ȦС-����
			{

			}
			break;
		case 10://��̨���ƹ�Ȧ��-����
			{

			}
			break;
		case 11://���⿪
			{

			}
			break;
		case 12://�����
			{

			}
			break;
		case 13://���ȿ�
			{

			}
			break;
		case 14:// ���ȹ�
			{
				//ytcommand = 0x0c02;
			}
			break;
		case 15:// �ƹ⿪
			{
				//ytcommand = 0x0b01;
			}
			break;
		case 16:// �ƹ��
			{
				//ytcommand = 0x0b02;
			}
			break;
		case 17:// ��ˢ��
			{
				//ytcommand = 0x0a01;
			}
			break;
		case 18:// ��ˢ��
			{
				//ytcommand = 0x0a02;
			}
			break;
		case 19:
			{
				return 0;
			}
			break;
		}
	}
	else
	{
		switch (wParam)
		{
		case 1://��̨������-��ʼ
			{
				DvrPtzControl_Devsdk(m_camera_info.ip_addr,m_camera_info.ip_port,m_camera_info.login_name,m_camera_info.login_password,
					m_camera_info.dvr_type,m_camera_info.dvr_id,m_camera_info.channel,TILTUP,5);
			}
			break;
		case 2://��̨������-��ʼ
			{
				DvrPtzControl_Devsdk(m_camera_info.ip_addr,m_camera_info.ip_port,m_camera_info.login_name,m_camera_info.login_password,
					m_camera_info.dvr_type,m_camera_info.dvr_id,m_camera_info.channel,TILTDOWN,5);
			}
			break;
		case 3://��̨������-��ʼ
			{
				DvrPtzControl_Devsdk(m_camera_info.ip_addr,m_camera_info.ip_port,m_camera_info.login_name,m_camera_info.login_password,
					m_camera_info.dvr_type,m_camera_info.dvr_id,m_camera_info.channel,PANLEFT,5);
			}
			break;
		case 4://��̨������-��ʼ
			{
				DvrPtzControl_Devsdk(m_camera_info.ip_addr,m_camera_info.ip_port,m_camera_info.login_name,m_camera_info.login_password,
					m_camera_info.dvr_type,m_camera_info.dvr_id,m_camera_info.channel,PANRIGHT,5);
			}
			break;
		case 5://����-��ʼ
			{
				DvrPtzControl_Devsdk(m_camera_info.ip_addr,m_camera_info.ip_port,m_camera_info.login_name,m_camera_info.login_password,
					m_camera_info.dvr_type,m_camera_info.dvr_id,m_camera_info.channel,ZOOMOUT,5);
			}
			break;
		case 6://��Զ-��ʼ
			{
				DvrPtzControl_Devsdk(m_camera_info.ip_addr,m_camera_info.ip_port,m_camera_info.login_name,m_camera_info.login_password,
					m_camera_info.dvr_type,m_camera_info.dvr_id,m_camera_info.channel,ZOOMIN,5);
			}
			break;
		case 7://��̨���ƽ����-��ʼ
			{
				//ytcommand = 0x0302;
			}
			break;
		case 8://��̨���ƽ���Զ-��ʼ
			{
				//ytcommand = 0x0304;
			}
			break;
		case 9://��̨���ƹ�ȦС-��ʼ
			{
				//ytcommand = 0x0102;
			}
			break;
		case 10://��̨���ƹ�Ȧ��-��ʼ
			{
				//ytcommand = 0x0103;
			}
			break;
		case 11:// ���⿪
			{
				//ytcommand = 0x0d01;
			}
			break;
		case 12:// �����
			{
				//ytcommand = 0x0d02;
			}
			break;
		case 13:// ���ȿ�
			{
				//ytcommand = 0x0c01;
			}
			break;
		case 14:// ���ȹ�
			{
				//ytcommand = 0x0c02;
			}
			break;
		case 15:// �ƹ⿪
			{
				//ytcommand = 0x0b01;
			}
			break;
		case 16:// �ƹ��
			{
				//ytcommand = 0x0b02;
			}
			break;
		case 17:// ��ˢ��
			{
				//ytcommand = 0x0a01;

			}
			break;
		case 18:// ��ˢ��
			{
				//ytcommand = 0x0a02;
			}
			break;
		case 19:
			{
				return 0;
			}
			break;
		}
	}

	return 1;
}

void CACSSystemDlg::InitCtrl()
{
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP_TREE);
	m_ilTreeIcons.Create(16,16,ILC_MASK|ILC_COLOR24,0,1);
	m_ilTreeIcons.Add(&bmp,RGB(0,255,0));
	m_treeStation.SetImageList(&m_ilTreeIcons,TVSIL_NORMAL);

	DWORD dwStyle;
	dwStyle = m_ListYX.GetStyle();
	dwStyle = LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT ;

	m_ListYX.SetExtendedStyle(dwStyle);
	m_ListYX.SetBkColor(RGB(239,246,253));
	m_ListYX.SetTextBkColor(RGB(0xfe,0xFF,0xc6));

	CRect winrc;
	int nWidth = GetSystemMetrics(SM_CXSCREEN)*0.4;

	m_ListYX.DeleteAllItems();
	while(m_ListYX.DeleteColumn(0));

	m_ListYX.InsertColumn(0,"ң���豸����");
	m_ListYX.SetColumnWidth(0,nWidth*0.25);
	m_ListYX.InsertColumn(1,"��ǰֵ");
	m_ListYX.SetColumnWidth(1,nWidth*0.25);
	m_ListYX.InsertColumn(2,"�澯״̬");
	m_ListYX.SetColumnWidth(2,nWidth*0.25);
	m_ListYX.InsertColumn(3,"�Ƿ������Ƶ");
	m_ListYX.SetColumnWidth(3,nWidth*0.25);

	m_pViewOut = new CDlgViewOut;
	if (m_pViewOut != NULL)
	{
		m_pViewOut->Create(IDD_DIALOG_VIEW_OUT,this);
		m_pViewOut->m_nWinID = 0;
		m_pViewOut->m_ViewChannel.m_iWinID = 0;
	}

	CString strText = _T("");
	for (int i=0; i<16; i++)
	{
		strText.Format("%d",i+1);
		m_ComboYTSpeed.AddString(strText);
	}
	m_ComboYTSpeed.SetCurSel(4);
}

void CACSSystemDlg::RefreshYCList(int nStationId)
{

}

void CACSSystemDlg::RefreshYXList(int nStationId)
{
	FreeYXList();
	int yx_index = 0;
	char sql_buf[1024]={0x0};
	MYSQL_RES* res;
	MYSQL_ROW row;
	sprintf_s(sql_buf,"select a.dev_id,a.rvu_id,a.sm_id,a.node_id,a.enum_type,a.value,a.status,b.name,b.relation_video_status "
		" from ass_rvu_sm_realdata a "
		" left join ass_rvu_sm b on a.dev_id=b.id "
	    " where a.rvu_id in (select c.rvu_id from ass_rvu c where c.station_id=%d) ",nStationId);
	if (!mysql_query(&mysql_cameralist,sql_buf))
	{
		res = mysql_store_result(&mysql_cameralist);
		while (row = mysql_fetch_row(res))
		{
			T_SM_REALDATA *pRealData = new T_SM_REALDATA;
			pRealData->station_id = nStationId;
			pRealData->dev_id = atoi(row[0]);
			pRealData->rvu_id = atoi(row[1]);
			pRealData->sm_id = atoi(row[2]);
			pRealData->node_id = atoi(row[3]);
			pRealData->type = atoi(row[4]);
			pRealData->real_value = atoi(row[5]);
			pRealData->status = atoi(row[6]);
			sprintf_s(pRealData->dev_name,"%s",row[7]);
			pRealData->relation_video = atoi(row[8]);

			m_ListYX.InsertItem(yx_index,row[7]);
			m_ListYX.SetItemText(yx_index,1,row[5]);

			char szStatusText[32] = {0};
			GetStatusTextByStatus(szStatusText, pRealData->status);
			m_ListYX.SetItemText(yx_index, 2, szStatusText);

			char szRelateVideoText[32] = {0};
			GetRelateVideoText(szRelateVideoText, pRealData->relation_video);
			m_ListYX.SetItemText(yx_index, 3, szRelateVideoText);

			m_ListYX.SetItemData(yx_index,(DWORD_PTR)pRealData);
		}
		mysql_free_result(res);
	}
}

void CACSSystemDlg::FreeYXList()
{
	int nNum = m_ListYX.GetItemCount();
	for (int i=0; i<nNum; i++)
	{
		T_SM_REALDATA* pDeviceInfo = (T_SM_REALDATA*)m_ListYX.GetItemData(i);
		delete pDeviceInfo;
		pDeviceInfo = NULL;
		m_ListYX.SetItemData(i,(DWORD_PTR)pDeviceInfo);
	}
	m_ListYX.DeleteAllItems();
}

void CACSSystemDlg::FreeYCList()
{

}

void CACSSystemDlg::OnBnClickedCheckAllSubsystem()
{

}

void CACSSystemDlg::OnBnClickedCheckSecuritySystem()
{

}

void CACSSystemDlg::OnBnClickedCheckFireSystem()
{

}

void CACSSystemDlg::OnBnClickedCheckDoorSystem()
{

}

int CACSSystemDlg::OpenCamera(char* szCameraCode)
{
	if (m_bVideoOpen)
	{
		CloseCamera(m_nCurrentID);
		Sleep(1000);
	}

	char dvr_ip[32] = {0x0};
	char login_name[64] = {0x0};
	char login_password[32] = {0x0};
	int dvr_port = 0;
	int channel = 0;
	int dvr_type  = 0;
	char szDvrType[16] = {0x0};
	char szCameraName[32] = {0x0};
	//����camera_code��ȡdvr��Ϣ
	char sql_buf[1024] = {0x0};
	MYSQL_RES* res;
	MYSQL_ROW row;

	sprintf_s(sql_buf,1024,"select b.dvr_ip,b.tcp_port,b.dvr_type,b.adminpasswd,b.adminuser,a.channel,a.name from video_camera as a "
		" left join video_dvr as b on a.dvr_id=b.dvr_id where a.camera_id='%s'",szCameraCode);
	if (!mysql_query(&mysql_cameralist,sql_buf))
	{
		res = mysql_store_result(&mysql_cameralist);
		row = mysql_fetch_row(res);
		if (row != NULL)
		{
			sprintf_s(dvr_ip,"%s",row[0]);
			dvr_port = atoi(row[1]);
			sprintf_s(szDvrType,"%s",row[2]);
			sprintf_s(login_name,"%s",row[4]);
			sprintf_s(login_password,"%s",row[3]);
			channel = atoi(row[5]);
			sprintf_s(szCameraName,"%s",row[6]);
		}
		else
		{
			MessageBox("����DVR��Ϣʧ�ܣ�","����ϵͳ");
			mysql_free_result(res);
			return -1;
		}
		mysql_free_result(res);
	}
	else
	{
		MessageBox("����DVR��Ϣʧ�ܣ�","����ϵͳ");
		return -1;
	}

	if (stricmp(szDvrType,"HIK")==0)
	{
		dvr_type = DEVTYPE_HK;
	}
	else if (stricmp(szDvrType,"DH")==0)
	{
		dvr_type = DEVTYPE_DH;
	}
	else if (stricmp(szDvrType,"DL")==0)
	{
		dvr_type = DEVTYPE_DL;
	}
	else if (stricmp(szDvrType,"MOBO")==0)
	{
		dvr_type = DEVTYPE_MOBOTIX;
	}
	else
	{
		MessageBox("δ֪��DVR����","����ϵͳ");
		return -1;
	}

	m_nCurrentID = GetID_DevSdk();
	//��m_nCurrentID�������ó���
	if (callbackacssystemopenvideoid)
	{
		callbackacssystemopenvideoid(m_nCurrentID);
	}

	int nRes = OpenVideo_DevSdk(dvr_ip,dvr_port,login_name,login_password,dvr_type,1,channel,m_nCurrentID,m_pViewOut->m_ViewChannel.GetSafeHwnd());
	if (nRes != 0)
	{
		AfxMessageBox("����Ƶʧ�ܣ�");
		return -1;
	}

	m_camera_info.channel = channel;
	sprintf_s(m_camera_info.ip_addr,"%s",dvr_ip);
	sprintf_s(m_camera_info.login_name,"%s",login_name);
	sprintf_s(m_camera_info.login_password,"%s",login_password);
	m_camera_info.dvr_type = dvr_type;
	m_camera_info.ip_port = dvr_port;
	m_camera_info.dvr_id = 1;
	m_nDvrType = dvr_type;

	m_pViewOut->m_strCameraName.SetText(szCameraName);

	//��������ͷ�Ѵ򿪱�־
	m_bVideoOpen = true;
	m_pViewOut->m_ViewChannel.m_video_opened = true;
	return 0;
}

void CACSSystemDlg::CloseCamera(int nID)
{
	if (m_bVideoOpen)
	{
		CloseVideo_DevSdk(nID);
		m_pViewOut->m_ViewChannel.Invalidate();
		Sleep(1000);
		m_bVideoOpen = false;
		m_pViewOut->m_ViewChannel.m_video_opened = false;
	}
}

void CACSSystemDlg::OnSize(UINT nType, int cx, int cy)
{
	CWnd* pWnd = NULL;
	CRect button_rect,third_rect;

	int button_height = 30;
	int button_width = 100;

	int nWidth = cx;//GetSystemMetrics(SM_CXSCREEN);
	int nHeight = cy;//GetSystemMetrics(SM_CYSCREEN);

	int nEveryColumnInterval = 7;
	nWidth = nWidth - 7*2; 
	int nTotalColumn = 3;
	int nFirstColumnWidth = 0.15*nWidth;
	int nSecondColumnWidth = 0.55*nWidth;
	int nThirdColumnWidth = 0.3*nWidth;
	

	//��һ��
	//pWnd = GetDlgItem(IDC_STATIC_STATION);
	//if (pWnd != NULL)
	//{
	//	button_rect.top = 0;
	//	button_rect.bottom = button_rect.top + button_height;
	//	button_rect.left = 0;
	//	button_rect.right = button_rect.left + nFirstColumnWidth;
	//	pWnd->MoveWindow(button_rect);
	//}

	pWnd = GetDlgItem(IDC_TREE_STATION);
	if (pWnd != NULL)
	{
		button_rect.top = 0;
		button_rect.bottom = button_rect.top + nHeight;
		button_rect.left = 0;
		button_rect.right = button_rect.left + nFirstColumnWidth;
		pWnd->MoveWindow(button_rect);
	}

	////�ڶ���
	//pWnd = GetDlgItem(IDC_STATIC_SUBSYSTEM);
	//if (pWnd != NULL)
	//{
	//	button_rect.top = 0;
	//	button_rect.bottom = button_rect.top + button_height;
	//	button_rect.left = button_rect.right + nEveryColumnInterval;
	//	button_rect.right = button_rect.left + nSecondColumnWidth * 0.2;
	//	pWnd->MoveWindow(button_rect);
	//}

	//pWnd = GetDlgItem(IDC_CHECK_ALL_SUBSYSTEM);
	//if (pWnd != NULL)
	//{
	//	button_rect.top = button_rect.top;
	//	button_rect.bottom = button_rect.top + button_height;
	//	button_rect.left = button_rect.right;
	//	button_rect.right = button_rect.left + nSecondColumnWidth * 0.2;
	//	pWnd->MoveWindow(button_rect);
	//}

	//pWnd = GetDlgItem(IDC_CHECK_SECURITY_SYSTEM);
	//if (pWnd != NULL)
	//{
	//	button_rect.top = button_rect.top;
	//	button_rect.bottom = button_rect.top + button_height;
	//	button_rect.left = button_rect.right;
	//	button_rect.right = button_rect.left + nSecondColumnWidth * 0.2;
	//	pWnd->MoveWindow(button_rect);
	//}

	//pWnd = GetDlgItem(IDC_CHECK_FIRE_SYSTEM);
	//if (pWnd != NULL)
	//{
	//	button_rect.top = button_rect.top;
	//	button_rect.bottom = button_rect.top + button_height;
	//	button_rect.left = button_rect.right;
	//	button_rect.right = button_rect.left + nSecondColumnWidth * 0.2;
	//	pWnd->MoveWindow(button_rect);
	//}

	//pWnd = GetDlgItem(IDC_CHECK_DOOR_SYSTEM);
	//if (pWnd != NULL)
	//{
	//	button_rect.top = button_rect.top;
	//	button_rect.bottom = button_rect.top + button_height;
	//	button_rect.left = button_rect.right;
	//	button_rect.right = button_rect.left + nSecondColumnWidth * 0.2;
	//	pWnd->MoveWindow(button_rect);
	//}

	//pWnd = GetDlgItem(IDC_STATIC_YX_DEVICE);
	//if (pWnd != NULL)
	//{
	//	button_rect.top = button_rect.top + button_height;
	//	button_rect.bottom = button_rect.top + button_height;
	//	button_rect.left = button_rect.right - nSecondColumnWidth;
	//	button_rect.right = button_rect.left + button_width;
	//	pWnd->MoveWindow(button_rect);
	//}

	pWnd = GetDlgItem(IDC_LIST_YX_DEVICE);
	if (pWnd != NULL)
	{
		button_rect.top = 0;
		button_rect.bottom = nHeight;
		button_rect.left = button_rect.right + nEveryColumnInterval;
		button_rect.right = button_rect.left + nSecondColumnWidth;
		pWnd->MoveWindow(button_rect);
	}

	//������
	pWnd = m_pViewOut;
	if (pWnd != NULL)
	{
		third_rect.top = 0;
		third_rect.bottom = nHeight * 0.4;
		third_rect.left = button_rect.right + nEveryColumnInterval;
		third_rect.right = third_rect.left + nThirdColumnWidth;
		pWnd->MoveWindow(third_rect);
		pWnd->ShowWindow(SW_SHOW);
	}
	int nStaticLeft = third_rect.left;
	int nStaticRight = third_rect.right;

	pWnd = GetDlgItem(IDC_BUTTON_UP);
	if (pWnd != NULL)
	{
		third_rect.top = third_rect.bottom;
		third_rect.bottom = third_rect.top + button_height;
		third_rect.left = third_rect.left + ((third_rect.right - third_rect.left)/2 - button_width/2);
		third_rect.right = third_rect.left + button_width;
		pWnd->MoveWindow(third_rect);
	}
	int nStaticTop = third_rect.top;

	pWnd = GetDlgItem(IDC_BUTTON_LOCK);
	if (pWnd != NULL)
	{
		third_rect.top = third_rect.top + button_height;
		third_rect.bottom = third_rect.top + button_height;
		third_rect.left = third_rect.left;
		third_rect.right = third_rect.left + button_width;
		pWnd->MoveWindow(third_rect);
	}

	pWnd = GetDlgItem(IDC_BUTTON_DOWN);
	if (pWnd != NULL)
	{
		third_rect.top = third_rect.top + button_height;
		third_rect.bottom = third_rect.top + button_height;
		third_rect.left = third_rect.left;
		third_rect.right = third_rect.left + button_width;
		pWnd->MoveWindow(third_rect);
	}

	pWnd = GetDlgItem(IDC_BUTTON_LEFT);
	if (pWnd != NULL)
	{
		third_rect.top = third_rect.top - button_height;
		third_rect.bottom = third_rect.top + button_height;
		third_rect.left = third_rect.left - button_width;
		third_rect.right = third_rect.left + button_width;
		pWnd->MoveWindow(third_rect);
	}

	pWnd = GetDlgItem(IDC_BUTTON_RIGHT);
	if (pWnd != NULL)
	{
		third_rect.top = third_rect.top;
		third_rect.bottom = third_rect.top + button_height;
		third_rect.left = third_rect.left + button_width * 2;
		third_rect.right = third_rect.left + button_width;
		pWnd->MoveWindow(third_rect);
	}

	pWnd = GetDlgItem(IDC_BUTTON_ZOOM_IN);
	if (pWnd != NULL)
	{
		third_rect.top = third_rect.top + button_height;
		third_rect.bottom = third_rect.top + button_height;
		third_rect.left = third_rect.left - button_width * 2;
		third_rect.right = third_rect.left + button_width;
		pWnd->MoveWindow(third_rect);
	}

	pWnd = GetDlgItem(IDC_BUTTON_ZOOM_OUT);
	if (pWnd != NULL)
	{
		third_rect.top = third_rect.top;
		third_rect.bottom = third_rect.top + button_height;
		third_rect.left = third_rect.left + button_width * 2;
		third_rect.right = third_rect.left + button_width;
		pWnd->MoveWindow(third_rect);
	}

	pWnd = GetDlgItem(IDC_STATIC_YT_SPEED);
	if (pWnd != NULL)
	{
		third_rect.top = third_rect.top + button_height;
		third_rect.bottom = third_rect.top + button_height;
		third_rect.left = third_rect.left - button_width * 2;
		third_rect.right = third_rect.left + button_width;
		pWnd->MoveWindow(third_rect);
	}

	pWnd = GetDlgItem(IDC_COMBO_YT_SPEED);
	if (pWnd != NULL)
	{
		third_rect.top = third_rect.top;
		third_rect.bottom = third_rect.top + button_height;
		third_rect.left = third_rect.left + button_width * 2;
		third_rect.right = third_rect.left + button_width;
		pWnd->MoveWindow(third_rect);
	}
	int nStaticBottom = third_rect.bottom;

	pWnd = GetDlgItem(IDC_STATIC_ELECMAP);
	if (pWnd != NULL)
	{
		third_rect.top = nStaticTop;
		third_rect.bottom = nStaticBottom;
		third_rect.left = nStaticLeft;
		third_rect.right = nStaticRight;
		pWnd->MoveWindow(third_rect);
	}
}

void CACSSystemDlg::OnDestroy()
{
	CDialog::OnDestroy();

}

BOOL CACSSystemDlg::FreeDVR()
{
	Exit_DevSdk();

	disconnectDB();

	return TRUE;
}

void CACSSystemDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnClose();
}

void CACSSystemDlg::OnBnClickedButtonUp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CACSSystemDlg::ProcessRClickCamera()
{
	PopClickCameraRightMenu();
}

void CACSSystemDlg::PopClickCameraRightMenu()
{
	CMenu menuMain;
	menuMain.CreatePopupMenu();

	menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,ID_DLG_ACSSYSTEM_CLOSE_VIDEO,"�ر���Ƶ");

	CPoint point;
	GetCursorPos(&point);

	menuMain.TrackPopupMenu(TPM_RIGHTBUTTON,point.x,point.y,this);
}

void CACSSystemDlg::OnClickACSSystemDlgCloseVideo()
{
	CloseCamera(m_nCurrentID);
}

BOOL CACSSystemDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_RBUTTONDOWN)
	{
		if (pMsg->hwnd == m_pViewOut->m_ViewChannel.GetSafeHwnd())
		{
			ProcessRClickCamera();
		}
	}
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_UP)->GetSafeHwnd())
		{
			this->PostMessage(OM_MESSAGE_MULTI_YTCONTROL,1,1);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_DOWN)->GetSafeHwnd())
		{
			this->PostMessage(OM_MESSAGE_MULTI_YTCONTROL,2,1);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_LEFT)->GetSafeHwnd())
		{
			this->PostMessage(OM_MESSAGE_MULTI_YTCONTROL,3,1);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_RIGHT)->GetSafeHwnd())
		{
			this->PostMessage(OM_MESSAGE_MULTI_YTCONTROL,4,1);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_ZOOM_IN)->GetSafeHwnd())
		{
			this->PostMessage(OM_MESSAGE_MULTI_YTCONTROL,5,1);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_ZOOM_OUT)->GetSafeHwnd())
		{
			this->PostMessage(OM_MESSAGE_MULTI_YTCONTROL,6,1);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_LOCK)->GetSafeHwnd())
		{
			this->PostMessage(OM_MESSAGE_MULTI_YTCONTROL,19,1);
		}
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_UP)->GetSafeHwnd())
		{
			this->PostMessage(OM_MESSAGE_MULTI_YTCONTROL,1,0);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_DOWN)->GetSafeHwnd())
		{
			this->PostMessage(OM_MESSAGE_MULTI_YTCONTROL,2,0);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_LEFT)->GetSafeHwnd())
		{
			this->PostMessage(OM_MESSAGE_MULTI_YTCONTROL,3,0);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_RIGHT)->GetSafeHwnd())
		{
			this->PostMessage(OM_MESSAGE_MULTI_YTCONTROL,4,0);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_ZOOM_IN)->GetSafeHwnd())
		{
			this->PostMessage(OM_MESSAGE_MULTI_YTCONTROL,5,0);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_ZOOM_OUT)->GetSafeHwnd())
		{
			this->PostMessage(OM_MESSAGE_MULTI_YTCONTROL,6,0);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_LOCK)->GetSafeHwnd())
		{
			this->PostMessage(OM_MESSAGE_MULTI_YTCONTROL,19,0);
		}
	}
	
	return FALSE;//����ú�������TRUE���򲻻�Ѹ���Ϣ�ַ������ں�������Ҳ�����Ƿ����TranslateMessage()��DispatchMessage()
	return CDialog::PreTranslateMessage(pMsg);
}

void CACSSystemDlg::OnNMDblclkTreeStation(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	try
	{
		HTREEITEM hItem = NULL;
		StationNode *pNodeInfo = NULL;

		// ���ҵ��е��������Ŀ
		hItem = m_treeStation.GetSelectedItem();
		if (hItem == NULL)
			return;

		pNodeInfo = (StationNode *)m_treeStation.GetItemData(hItem);
		//2��ʾ���վ
		if (pNodeInfo == NULL||pNodeInfo->node_type != 2)
			return;

		//���ó�Ա�������̺߳�������ʹ�����
		m_pStationNode = pNodeInfo;
		m_nRvuID = GetRvuIDByStationID(m_pStationNode->station_id);

		//��ȡ���վ�������豸��ʵʱ���ݣ��豸���ƣ����ͣ�ֵ���Ƿ������Ƶ���Ƿ�澯
		RefreshYXList(m_pStationNode->station_id);

		//֪ͨ����˵�ǰ�鿴�ı��վ��Ȼ������ֻ����������վʵʱ��Ϣ
		SendSubscribeStationRequest(g_pConfigInfo->nUserId, m_pStationNode->station_id);

		//�򿪵��ӵ�ͼ
		OpenASceneElecMap(m_pStationNode->station_name);
	}
	catch(...)
	{

	}
}

//���ͱ��վ����ʵʱ��Ϣ����
BOOL CACSSystemDlg::SendSubscribeStationRequest(int nUserId, int nStationId)
{
	char send_buf[1024] ={0};

	//ƴ������
	sprintf_s(send_buf,"<?xml version=1.0 encoding=GB2312?> <HTTP_XML EventType=Request_Subscribe_Station>"
		"<Item UserID='%d' StationID='%d' /></HTTP_XML>",nUserId, nStationId);

	//��������
	int ret = ComSendNet(g_pConfigInfo->nAcsTcpHandle,g_pConfigInfo->szAcsServerIp,g_pConfigInfo->nAcsServerPort,0,0,0,0,send_buf,sizeof(send_buf),0);
	if (ret)
		return FALSE;
}

//����˴�����ʵʱ���ݸ���listcontrol
void CACSSystemDlg::RefreshYXListRealData(char* pSmRealData, int nCount)
{
	PUSH_DATA_RESPONSE *pTSmRealData = (PUSH_DATA_RESPONSE*)pSmRealData;

	//�����ǰ��ʾ�����ݲ��Ǵ������ı��վ�ģ��򷵻�
	if (m_nRvuID != pTSmRealData[0].nRvuId)
		return;

	int nNum = m_ListYX.GetItemCount();

	CString strText = "";
	//����������������
	for (int i=0;i<nCount;i++)
	{
		bool bFind = false;
		int nRvuID = pTSmRealData[i].nRvuId;
		int nSmID = pTSmRealData[i].nSmId;
		int nNodeID = pTSmRealData[i].nNodeId;
		//����listcontrol����
		for (int j=0; j<nNum; j++)
		{
			T_SM_REALDATA* pDeviceInfo = (T_SM_REALDATA*)m_ListYX.GetItemData(j);
			if (pDeviceInfo->rvu_id == nRvuID && pDeviceInfo->sm_id == nSmID && pDeviceInfo->node_id == nNodeID)
			{
				//�����ı�
				strText.Format("%f",pTSmRealData[i].fValue);
				m_ListYX.SetItemText(j,1,strText);
				if (pTSmRealData[i].nStatus == 0 || pTSmRealData[i].nStatus ==4)
					strText.Format("�޸澯");
				else
					strText.Format("�и澯");
				m_ListYX.SetItemText(j,2,strText);

				//���¼�¼ָ�������
				pDeviceInfo->real_value = pTSmRealData[i].fValue;
				pDeviceInfo->status = pTSmRealData[i].nStatus;

				//���ҵ�������ѭ��
				bFind = true;
				break;
			}
		}

		if (bFind == false)
		{
			//û�ҵ�����ӵ��б���
			T_SM_REALDATA tSMRealData;
			//ͨ��ʵʱ���ݻ�ȡ
			GetSMRealDataInfoByPushDataResponse(&tSMRealData, &pTSmRealData[i]);
			InsertSmRealDataToYXList(0, &tSMRealData);
		}

		
	}
}

void CACSSystemDlg::InsertSmRealDataToYXList(int nIndex, T_SM_REALDATA *pSMRealData)
{
	T_SM_REALDATA *pRealData = new T_SM_REALDATA;
	memcpy(pRealData, pSMRealData, sizeof(T_SM_REALDATA));

	m_ListYX.InsertItem(nIndex, pRealData->dev_name);

	CString strValue = "";
	strValue.Format("%f", pRealData->real_value);
	m_ListYX.SetItemText(nIndex, 1, strValue);

	char szStatusText[32] = {0};
	GetStatusTextByStatus(szStatusText, pRealData->status);
	m_ListYX.SetItemText(nIndex, 2, szStatusText);

	char szRelateVideoText[32] = {0};
	GetRelateVideoText(szRelateVideoText, pRealData->relation_video);
	m_ListYX.SetItemText(nIndex, 3, szRelateVideoText);

	m_ListYX.SetItemData(nIndex,(DWORD_PTR)pRealData);
}

void CACSSystemDlg::OnNMDblclkListYxDevice(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	if (m_bVideoOpen == true)
	{
		CloseVideo_DevSdk(m_nCurrentID);
		m_pViewOut->m_ViewChannel.Invalidate();
		Sleep(1000);
	}

	POSITION pos = m_ListYX.GetFirstSelectedItemPosition();

	if (pos == NULL)
		return;

	int index = m_ListYX.GetNextSelectedItem(pos);

	if (index < 0)
		return;

	T_SM_REALDATA* pRealData = (T_SM_REALDATA*)m_ListYX.GetItemData(index);

	//���û�а���Ƶ���򷵻�
	if (pRealData->relation_video == 0)
	{
		return;
	}
	else
	{
		//��ȡdev_id�󶨵�����ͷ
		T_LINKAGE_CAMERA_INFO tCameraCode[MAX_DEV_RELATION_CAMERA];
		memset(tCameraCode, 0, sizeof(T_LINKAGE_CAMERA_INFO)*MAX_DEV_RELATION_CAMERA);
		int nCameraCount = 0;
		GetCameraCodeByDevId(m_pStationNode->station_id, pRealData->dev_id, tCameraCode, &nCameraCount);

		//����Ƶ
		if (tCameraCode[0].szCameraCode != NULL)
		{
			OpenCamera(tCameraCode[0].szCameraCode);
		}
	}

	//����Ƶ��������ʾ�澯��Ϣ
}

void CACSSystemDlg::OnNMRClickListYxDevice(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	POSITION pos = m_ListYX.GetFirstSelectedItemPosition();

	if (pos == NULL)
		return;

	int index = m_ListYX.GetNextSelectedItem(pos);

	if (index < 0)
		return;

	T_SM_REALDATA* pRealData = (T_SM_REALDATA*)m_ListYX.GetItemData(index);

	//�����˵�
	T_LINKAGE_CAMERA_INFO tCameraCode[MAX_DEV_RELATION_CAMERA];
	memset(tCameraCode, 0, sizeof(T_LINKAGE_CAMERA_INFO)*MAX_DEV_RELATION_CAMERA);
	int nCameraCount = 0;
	GetCameraCodeByDevId(m_pStationNode->station_id, pRealData->dev_id, tCameraCode, &nCameraCount);

	PopRightMenu(tCameraCode, nCameraCount);
}

void CACSSystemDlg::PopRightMenu(T_LINKAGE_CAMERA_INFO *tCameraCode, int nCount)
{
	CMenu pPopMenu;
	CMenu menuMain;
	menuMain.CreatePopupMenu();
	pPopMenu.CreatePopupMenu();

	memset(g_tLinkageCameraInfo, 0, sizeof(T_LINKAGE_CAMERA_INFO)*MAX_DEV_RELATION_CAMERA);
	memcpy(g_tLinkageCameraInfo,tCameraCode,sizeof(T_LINKAGE_CAMERA_INFO)*MAX_DEV_RELATION_CAMERA);

	for (int i = 0;i<nCount;i++)
	{
		pPopMenu.AppendMenu(MF_STRING,ID_LINKAGE_INFO1+i,tCameraCode[i].szPresetName);
	}

	if (nCount == 0)
	{
		pPopMenu.AppendMenu(MF_STRING,ID_LINKAGE_INFO1,"(��)");
		pPopMenu.EnableMenuItem(0,MF_BYPOSITION|MF_DISABLED|MF_GRAYED);
	}

	menuMain.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,(UINT)pPopMenu.m_hMenu,"�ѹ�����Ƶ");

	CPoint point;
	GetCursorPos(&point);

	menuMain.TrackPopupMenu(TPM_RIGHTBUTTON,point.x,point.y,this);
}

void CACSSystemDlg::OnClickLinkageCamera( UINT nID )
{
	if (nID>ID_LINKAGE_INFO16||nID<ID_LINKAGE_INFO1)
	{
		return;
	}

	//������ͷ
	OpenCamera(g_tLinkageCameraInfo[nID-ID_LINKAGE_INFO1].szCameraCode);

	//ת��Ԥ��λ
	ToPreset(&g_tLinkageCameraInfo[nID-ID_LINKAGE_INFO1]);
}

void CACSSystemDlg::ToPreset(T_LINKAGE_CAMERA_INFO *pLinkageCameraInfo)
{
	if (m_bVideoOpen == false)
	{
		return;
	}

	int nRet = DvrPtzControl_Devsdk(m_camera_info.ip_addr,m_camera_info.ip_port,m_camera_info.login_name,
		m_camera_info.login_password,m_camera_info.dvr_type,m_camera_info.dvr_id,
		m_camera_info.channel,GOTOPRESET,pLinkageCameraInfo->nPresetId);

	if (nRet == FALSE)
	{
		MessageBox("ת��Ԥ��λʧ�ܣ�","����ϵͳ");
		return ;
	}
}
BOOL CACSSystemDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;

	return CDialog::OnEraseBkgnd(pDC);
}
