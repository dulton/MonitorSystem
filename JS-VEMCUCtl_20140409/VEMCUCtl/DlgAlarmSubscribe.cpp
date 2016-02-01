// DlgAlarmSubscribe.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "DlgAlarmSubscribe.h"
#include "VEMCUCtlDlg.h"


// CDlgAlarmSubscribe �Ի���

IMPLEMENT_DYNAMIC(CDlgAlarmSubscribe, CDialog)

CDlgAlarmSubscribe::CDlgAlarmSubscribe(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmSubscribe::IDD, pParent)
{

}

CDlgAlarmSubscribe::~CDlgAlarmSubscribe()
{
}

void CDlgAlarmSubscribe::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ALARM_SUBSCRIBE, m_lstAlarmSubscribe);
	DDX_Control(pDX, IDC_TREE_ALARM_SUBSCRIBE_STATION, m_treeAlarmSubscribeStation);
}

BEGIN_MESSAGE_MAP(CDlgAlarmSubscribe, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_SUBSCRIBE_OK, &CDlgAlarmSubscribe::OnBnClickedButtonAlarmSubscribeOk)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_SUBSCRIBE_CANCEL, &CDlgAlarmSubscribe::OnBnClickedButtonAlarmSubscribeCancel)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_SUBSCRIBE_STATION, &CDlgAlarmSubscribe::OnNMClickTreeAlarmSubscribeStation)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CDlgAlarmSubscribe::OnHdnItemclickListAlarmSubscribe)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ALARM_SUBSCRIBE, &CDlgAlarmSubscribe::OnNMClickListAlarmSubscribe)
END_MESSAGE_MAP()


// CDlgAlarmSubscribe ��Ϣ�������

BOOL CDlgAlarmSubscribe::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitControl();

	InitAlarmSubscribeList();

	InitAlarmSubscribeStationTree();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgAlarmSubscribe::InitAlarmSubscribeStationTree()
{
	try
	{
		int i = 0, j = 0, k = 0;
		int ns = 0;

		HTREEITEM	hMainItem = NULL;
		HTREEITEM	hChildItem = NULL, hChildItem1 = NULL, hChildItem2 = NULL;
		HTREEITEM	hStationItem = NULL;
		HTREEITEM	hCameraItem = NULL;
		BOOL b500kVFlag = FALSE;//��Ϊ500kVʱ������ʾ������м���㣬ֱ����ʾ���վ��

		int nStationStatus = 0;//���վ״̬
		char szStationShowName[256] = {0};
		memset(szStationShowName,0,sizeof(szStationShowName));

		// ��Ӹ��ڵ�
		for (i = 0; i < g_TotalSysNum; i ++)
		{
			if (g_SystemInfo[i].localdomain == 1)
			{
				hMainItem = m_treeAlarmSubscribeStation.InsertItem("ȫ��", 1, 1, TVI_ROOT, hMainItem);
				break;
			}
		}

		//��ӱ��վ�м�ڵ��վ��ڵ�
		for (i = 0; i < g_nStationNode_Num; i ++)
		{
			if (g_tStationNode_Info[i].parent_id == g_tStationNode_Info[i].node_id&&g_tStationNode_Info[i].login_type == 0)	//��һ���м�ڵ�--500kV,220kV,110kV��
			{
				//if (strcmp(g_tStationNode_Info[i].node_name,"220kV") == 0)//����ʾ220kV
				//	continue;

				//if (strcmp(g_tStationNode_Info[i].node_name,"110kV") == 0)//����ʾ110kV
				//	continue;

				if (strcmp(g_tStationNode_Info[i].node_name,"500kV") == 0)//����ʾ������м���㣬ֱ����ʾ���վ
					b500kVFlag = TRUE;
				else
					b500kVFlag = FALSE;

				hChildItem = m_treeAlarmSubscribeStation.InsertItem(g_tStationNode_Info[i].node_name, 7, 7, hMainItem);

				for (ns = 0; ns < g_nStation_Num; ns ++)
				{
					if (g_tStation_Info[ns].node_id == g_tStationNode_Info[i].node_id)
					{
						if (strlen(g_tStation_Info[ns].notes) != 0)
							sprintf_s(szStationShowName,sizeof(szStationShowName),"%s(%s)",g_tStation_Info[ns].station_name_videoplant,g_tStation_Info[ns].notes);
						else
							strcpy_s(szStationShowName,sizeof(szStationShowName),g_tStation_Info[ns].station_name_videoplant);

						nStationStatus = CheckStationCurrentStatus2(g_tStation_Info[ns].station_id);
						if (nStationStatus != 0)
							hStationItem = m_treeAlarmSubscribeStation.InsertItem(szStationShowName, 8, 8, hChildItem);
						else
							hStationItem = m_treeAlarmSubscribeStation.InsertItem(szStationShowName, 10, 10, hChildItem);

						SetCameraNodeInfo(hStationItem,
							g_tStation_Info[ns].station_name_videoplant,
							g_tStation_Info[ns].station_code_videoplant,
							g_tStation_Info[ns].station_id,
							1,
							0,
							0,
							0,
							0,
							2,
							g_tStation_Info[ns].station_name_videoplant);
					}
				}

				for (j = 0; j < g_nStationNode_Num; j ++)//�ڶ����м�ڵ�--�Ͼ��С�������
				{
					if (g_tStationNode_Info[j].parent_id == g_tStationNode_Info[i].node_id && g_tStationNode_Info[j].parent_id != g_tStationNode_Info[j].node_id)	// �ڶ����м�ڵ�
					{
						if (b500kVFlag == FALSE)
							hChildItem1 = m_treeAlarmSubscribeStation.InsertItem(g_tStationNode_Info[j].node_name, 7, 7, hChildItem);
						else
							hChildItem1 = hChildItem;

						for (ns = 0; ns < g_nStation_Num; ns ++)
						{
							if (g_tStation_Info[ns].node_id == g_tStationNode_Info[j].node_id)
							{
								if (strlen(g_tStation_Info[ns].notes) != 0)
									sprintf_s(szStationShowName,sizeof(szStationShowName),"%s(%s)",g_tStation_Info[ns].station_name_videoplant,g_tStation_Info[ns].notes);
								else
									strcpy_s(szStationShowName,sizeof(szStationShowName),g_tStation_Info[ns].station_name_videoplant);

								nStationStatus = CheckStationCurrentStatus2(g_tStation_Info[ns].station_id);
								if (nStationStatus != 0)
									hStationItem = m_treeAlarmSubscribeStation.InsertItem(szStationShowName, 8, 8, hChildItem1);
								else
									hStationItem = m_treeAlarmSubscribeStation.InsertItem(szStationShowName, 10, 10, hChildItem1);

								SetCameraNodeInfo(hStationItem,
									g_tStation_Info[ns].station_name_videoplant,
									g_tStation_Info[ns].station_code_videoplant,
									g_tStation_Info[ns].station_id,
									1,
									0,
									0,
									0,
									0,
									2,
									g_tStation_Info[ns].station_name_videoplant);
							}
						}

						for (k = 0; k < g_nStationNode_Num; k++)//�������м�ڵ�
						{
							if (g_tStationNode_Info[k].parent_id == g_tStationNode_Info[j].node_id && g_tStationNode_Info[k].parent_id != g_tStationNode_Info[k].node_id)	// �������м�ڵ�
							{
								hChildItem2 = m_treeAlarmSubscribeStation.InsertItem(g_tStationNode_Info[k].node_name, 7, 7, hChildItem1);

								for (ns = 0; ns < g_nStation_Num; ns ++)
								{
									if (g_tStation_Info[ns].node_id == g_tStationNode_Info[k].node_id)
									{
										if (strlen(g_tStation_Info[ns].notes) != 0)
											sprintf_s(szStationShowName,sizeof(szStationShowName),"%s(%s)",g_tStation_Info[ns].station_name_videoplant,g_tStation_Info[ns].notes);
										else
											strcpy_s(szStationShowName,sizeof(szStationShowName),g_tStation_Info[ns].station_name_videoplant);

										nStationStatus = CheckStationCurrentStatus2(g_tStation_Info[ns].station_id);
										if (nStationStatus != 0)
											hStationItem = m_treeAlarmSubscribeStation.InsertItem(szStationShowName, 8, 8, hChildItem2);
										else
											hStationItem = m_treeAlarmSubscribeStation.InsertItem(szStationShowName, 10, 10, hChildItem2);

										SetCameraNodeInfo(hStationItem,
											g_tStation_Info[ns].station_name_videoplant,
											g_tStation_Info[ns].station_code_videoplant,
											g_tStation_Info[ns].station_id,
											1,
											0,
											0,
											0,
											0,
											2,
											g_tStation_Info[ns].station_name_videoplant);
									}
								}
							}
						}
					}
				}
			}
		}

		hMainItem = m_treeAlarmSubscribeStation.GetRootItem();
		if (hMainItem != NULL)
		{
			hChildItem = m_treeAlarmSubscribeStation.GetChildItem(hMainItem);
			if (hChildItem != NULL)
			{
				m_treeAlarmSubscribeStation.SortChildren(hChildItem);//����
				hChildItem1 = m_treeAlarmSubscribeStation.GetChildItem(hChildItem);
				if (hChildItem1 != NULL)
				{
					m_treeAlarmSubscribeStation.EnsureVisible(hChildItem1);
				}
			}
		}

		hChildItem = m_treeAlarmSubscribeStation.GetNextSiblingItem(hChildItem);
		while(hChildItem != NULL)
		{
			m_treeAlarmSubscribeStation.SortChildren(hChildItem);//����
			hChildItem1 = m_treeAlarmSubscribeStation.GetChildItem(hChildItem);
			while(hChildItem1 != NULL)
			{
				m_treeAlarmSubscribeStation.SortChildren(hChildItem1);
				hChildItem1 = m_treeAlarmSubscribeStation.GetNextSiblingItem(hChildItem1);
			}
			hChildItem = m_treeAlarmSubscribeStation.GetNextSiblingItem(hChildItem);
		}
	}
	catch(...)
	{

	}
}

void CDlgAlarmSubscribe::SetCameraNodeInfo(HTREEITEM hItem, char* ItemName, char* Itemnum, int StationOrCameraID,int ItemStatus,int Streamless,float ItemLongitude, float ItemLatitude, int ItemDecodeTag, int Itemtype, char* stationname)
{
	_T_NODE_INFO *pNodeInfo = NULL;

	try
	{
		pNodeInfo = new _T_NODE_INFO;
		memset(pNodeInfo, 0, sizeof(_T_NODE_INFO));

		sprintf (pNodeInfo->node_name, "%s", ItemName);
		sprintf(pNodeInfo->node_num, "%s", Itemnum);

		pNodeInfo->node_id = StationOrCameraID;
		pNodeInfo->node_status = ItemStatus;
		pNodeInfo->node_streamless = Streamless;
		pNodeInfo->node_longitude = ItemLongitude;
		pNodeInfo->node_latitude = ItemLatitude;
		pNodeInfo->node_type = Itemtype;

		if (ItemDecodeTag == 1)
		{
			ItemDecodeTag = 150;
		}

		if (Itemtype == 2)//վ��
		{
			//��¼��һ��վ������
			if (strlen(g_VideoPageViewInfo.szFirstStationName) == 0)
			{
				strcpy_s(g_VideoPageViewInfo.szFirstStationName,sizeof(g_VideoPageViewInfo.szFirstStationName)-1,ItemName);
			}
		}

		pNodeInfo->node_decodetag = ItemDecodeTag;
		sprintf(pNodeInfo->node_station, "%s", stationname);

		m_treeAlarmSubscribeStation.SetItemData(hItem, (DWORD_PTR)pNodeInfo);
	}
	catch(...)
	{

	}
}

int CDlgAlarmSubscribe::CheckStationCurrentStatus2(int nStationId)
{
	int nStationStatus = 1;

	try
	{
		for (int i = 0;i < g_nStation_Num;i++)
		{
			if (g_tStation_Info[i].station_id == nStationId)
			{
				if (g_tStation_Info[i].station_video_status == 0)
					nStationStatus = 0;
			}
		}
		return nStationStatus;
	}
	catch(...)
	{

	}
	return nStationStatus;
}

void CDlgAlarmSubscribe::InitAlarmSubscribeList()
{
	m_lstAlarmSubscribe.DeleteAllItems();
	char sql_buf[1024] = {0};
	MYSQL_RES * res = NULL;
	MYSQL_ROW	row ;

	//��ȡ�Ѷ��ĸ澯��Ϣ
	sprintf_s(sql_buf, "SELECT "
		"a.id, "
		"c.station_name_videoplant as station_name, "
		"b.user_name "
		"FROM "
		"ass_alarm_subscribe AS a "
		"LEFT JOIN ct_user AS b ON a.user_id = b.user_id "
		"LEFT JOIN ob_d5000_station AS c ON a.station_id = c.station_id order by a.id");
	
	int nIndex = 0;

	if (!mysql_query(g_mySqlData, sql_buf))
	{
		res = mysql_store_result(g_mySqlData);

		while ( row = mysql_fetch_row( res ) )
		{
			m_lstAlarmSubscribe.InsertItem(nIndex,row[0]);
			m_lstAlarmSubscribe.SetItemText(nIndex,1,row[1]);
			m_lstAlarmSubscribe.SetItemText(nIndex,2,row[2]);

			nIndex++;
		}

		//���û�鵽����
		int nCount = 0;
		nCount = m_lstAlarmSubscribe.GetItemCount();
		if (nCount == 0)
		{
			m_lstAlarmSubscribe.InsertItem(nCount,"������");;
			m_lstAlarmSubscribe.SetItemText(nCount,1,"������");
			m_lstAlarmSubscribe.SetItemText(nCount,2,"������");
		}
		mysql_free_result(res) ;
	}
}

void CDlgAlarmSubscribe::InitControl()
{
	DWORD dwStyle;
	dwStyle = m_lstAlarmSubscribe.GetStyle();
	dwStyle = LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT ;

	m_lstAlarmSubscribe.SetExtendedStyle(dwStyle);
	m_lstAlarmSubscribe.SetBkColor(RGB(239,246,253));
	m_lstAlarmSubscribe.SetTextBkColor(RGB(0xfe,0xFF,0xc6));

	m_lstAlarmSubscribe.DeleteAllItems();
	while(m_lstAlarmSubscribe.DeleteColumn(0));

	int nWidth = 1024;

	m_lstAlarmSubscribe.InsertColumn(0,"�澯����ID");
	m_lstAlarmSubscribe.SetColumnWidth(0,nWidth*0.2);
	m_lstAlarmSubscribe.InsertColumn(1,"���վ");
	m_lstAlarmSubscribe.SetColumnWidth(1,nWidth*0.4);
	m_lstAlarmSubscribe.InsertColumn(2,"�û���");
	m_lstAlarmSubscribe.SetColumnWidth(2,nWidth*0.4);

	//��������ť������
	GetDlgItem(IDC_BUTTON_ALARM_SUBSCRIBE_OK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ALARM_SUBSCRIBE_CANCEL)->EnableWindow(FALSE);
}

void CDlgAlarmSubscribe::OnBnClickedButtonAlarmSubscribeOk()
{
	HTREEITEM hItem = m_treeAlarmSubscribeStation.GetSelectedItem();
	if (hItem == NULL)
	{
		MessageBox("��ѡ����վ��㣡","�澯����");
		return;
	}

	// �жϽڵ��Ǻ������ͽڵ�
	_T_NODE_INFO *pNodeInfo = (_T_NODE_INFO *)(m_treeAlarmSubscribeStation.GetItemData(hItem));

	if (pNodeInfo == NULL)
		return;

	if(pNodeInfo->node_type != 2)
	{
		MessageBox("��ѡ����վ��㣡","�澯����");
		return;
	}

	//ȡ���վid,��ǰ�û�id
	int nStationId = pNodeInfo->node_id;
	int nUserId = g_userpower.userID;

	//�������ݿ�
	char sql_buf[1024]={0x0};
	MYSQL_RES	* res;
	//�жϸ��û��Ƿ��Ĺ��ñ��վ�ĸ澯
	int rnum = 0;
	sprintf_s(sql_buf,"select * from ass_alarm_subscribe where user_id='%d' and station_id='%d'",nUserId,nStationId);
	if (!mysql_query(g_mySqlData, sql_buf))
	{
		res = mysql_store_result(g_mySqlData);
		rnum = mysql_num_rows(res);
		mysql_free_result( res ) ;
	}

	if (rnum > 0)
	{
		MessageBox("�Ѷ��Ĺ��ø澯","�澯����");
		return ;
	}
	else
	{
		//�����������ͱ��վ������Ϣ
		g_pACSClient->SendSubscribeAlarmRequest(nUserId,nStationId);

		//����Ҫ�ȴ��澯���ķ�����Ϣ���سɹ�
		if (!WaitTimeOut(&g_CommonEvent, 2*1000*1000))
		{
			InitAlarmSubscribeList();
		}
		else
		{
			MessageBox("���������س�ʱ��");
		}
	}
}

void CDlgAlarmSubscribe::OnBnClickedButtonAlarmSubscribeCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION ps =m_lstAlarmSubscribe.GetFirstSelectedItemPosition();
	int nIndex  = -1;

	int nNodeId = -1;

	if (ps == NULL)
	{
		MessageBox("��ѡ��Ҫɾ���ĸ澯���ģ�","�澯����");
		return;
	}

	while (ps != NULL)
	{
		//��ȡ������id
		nIndex = m_lstAlarmSubscribe.GetNextSelectedItem(ps);
		int nDingYueId = atoi(m_lstAlarmSubscribe.GetItemText(nIndex,0));

		//��ȡ������Ϣͨ������id��
		T_ASS_SUBSCRIBE_INFO tAssSubscribeInfo;
		GetSubscribeInfoById(&tAssSubscribeInfo, nDingYueId);

		//֪ͨ�����
		g_pACSClient->SendCancelSubscribeAlarmRequest(tAssSubscribeInfo.nUserId, tAssSubscribeInfo.nStatiionId);
		if (!WaitTimeOut(&g_CommonEvent, 2*1000))
		{
			m_lstAlarmSubscribe.DeleteItem(nIndex);
			ps = m_lstAlarmSubscribe.GetFirstSelectedItemPosition();
		}
		else
		{
			MessageBox("���������س�ʱ��");
		}
	}
}

void CDlgAlarmSubscribe::OnNMClickTreeAlarmSubscribeStation(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	GetDlgItem(IDC_BUTTON_ALARM_SUBSCRIBE_OK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ALARM_SUBSCRIBE_CANCEL)->EnableWindow(FALSE);
}

void CDlgAlarmSubscribe::OnHdnItemclickListAlarmSubscribe(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

void CDlgAlarmSubscribe::OnNMClickListAlarmSubscribe(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	GetDlgItem(IDC_BUTTON_ALARM_SUBSCRIBE_OK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ALARM_SUBSCRIBE_CANCEL)->EnableWindow(TRUE);
}
