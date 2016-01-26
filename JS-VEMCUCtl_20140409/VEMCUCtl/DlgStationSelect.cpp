// DlgStationSelect.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "DlgStationSelect.h"
#include "DlgDeviceLedger.h"
#include "DlgReplay.h"


// CDlgStationSelect �Ի���

IMPLEMENT_DYNAMIC(CDlgStationSelect, CDialog)

CDlgStationSelect::CDlgStationSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStationSelect::IDD, pParent)
{
}

CDlgStationSelect::~CDlgStationSelect()
{
	//DeleteCameraTreeList();
}

void CDlgStationSelect::SetParentWindow(int nParentWindow)
{
	m_nParentWindow = nParentWindow;
}

void CDlgStationSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_STATION_SELECT_LIST, m_treeStationSelect);
}


BEGIN_MESSAGE_MAP(CDlgStationSelect, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_STATION_SELECT, &CDlgStationSelect::OnBnClickedButtonStationSelect)
END_MESSAGE_MAP()


// CDlgStationSelect ��Ϣ�������

void CDlgStationSelect::OnBnClickedButtonStationSelect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTreeCtrl *pList = (CTreeCtrl *)GetDlgItem(IDC_TREE_STATION_SELECT_LIST);

	HTREEITEM hItem = pList->GetSelectedItem();
	if (hItem == NULL)
		return;

	//���ѡ�����ȫ��,ֱ�ӷ���
	if(m_treeStationSelect.GetItemText(hItem)=="ȫ��")
	{
		sprintf_s(m_tStationNode.node_station,"ȫ��");
		m_tStationNode.node_id = 0;
		return;
		/*
		if (m_nParentWindow == 1)
		{
			g_pDlgReplay->m_nStationId = 0;//0��ʾȫ��
			g_pDlgReplay->GetDlgItem(IDC_EDIT_ALARM_REPLAY_STATION)->SetWindowText("ȫ��");
			//���combox�ؼ�Ϊ�����豸
			CComboBox* pComboAlarmDevice = (CComboBox*)g_pDlgReplay->GetDlgItem(IDC_COMBO_ALARM_DEVICE);
			pComboAlarmDevice->ResetContent();
			pComboAlarmDevice->AddString("�����豸");
			pComboAlarmDevice->SetCurSel(0);
			ShowWindow(SW_HIDE);
			return;
		}
		*/
	}

	// �жϽڵ��Ǻ������ͽڵ�
	_T_NODE_INFO * pNodeInfo = (_T_NODE_INFO *)(pList->GetItemData(hItem));
	if (pNodeInfo == NULL)
		return;

	if (pNodeInfo->node_type != 2)
	{
		MessageBox("��ѡ����վ","�ȵ���Ƶ����",MB_OK);
		return;
	}

	memcpy(&m_tStationNode,pNodeInfo,sizeof(_T_NODE_INFO));

	DeleteCameraTreeList();

	OnOK();

	/*
	//�豸̨�˴��ڴ򿪵ģ������豸̨�˴��ڵ��ı�
	if (m_nParentWindow == 0)
	{
		g_pDlgDeviceLedger->GetDlgItem(IDC_EDIT_STATION_SELECT)->SetWindowText(pNodeInfo->node_name);
	}
	//�澯�طŴ��ڴ򿪵ģ����ø澯�طŴ��ڵ��ı�,ͬʱ����һ���豸�б�
	if (m_nParentWindow == 1)
	{
		g_pDlgReplay->m_nStationId = pNodeInfo->node_id;
		g_pDlgReplay->GetDlgItem(IDC_EDIT_ALARM_REPLAY_STATION)->SetWindowText(pNodeInfo->node_name);
		//���¸澯�طŴ��ڵ�combox�ؼ��е��豸
		UpdateAlarmReplayDeviceCombox(pNodeInfo->node_id);
	}
	*/

	
}

void CDlgStationSelect::UpdateAlarmReplayDeviceCombox(int nStationId)
{
	CComboBox* pComboAlarmDevice = (CComboBox*)g_pDlgReplay->GetDlgItem(IDC_COMBO_ALARM_DEVICE);
	pComboAlarmDevice->ResetContent();
	pComboAlarmDevice->AddString("�����豸");

	char sql_buf[1024] = {0};
	MYSQL_RES *res;
	MYSQL_ROW row ;
	sprintf_s(sql_buf, "select a.name from ass_rvu_sm a where a.rvu_id in (select b.rvu_id from ass_rvu b where b.station_id=%d)",nStationId);
	if (!mysql_query(g_mySqlData, sql_buf))
	{
		res = mysql_store_result(g_mySqlData);

		while (row = mysql_fetch_row(res))
		{
			pComboAlarmDevice->AddString(row[0]);
		}
		mysql_free_result(res) ;
	}
	pComboAlarmDevice->SetCurSel(0);
}

BOOL CDlgStationSelect::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitStationSelectTree();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgStationSelect::InitStationSelectTree()
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
				hMainItem = m_treeStationSelect.InsertItem("ȫ��", 1, 1, TVI_ROOT, hMainItem);
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

				hChildItem = m_treeStationSelect.InsertItem(g_tStationNode_Info[i].node_name, 7, 7, hMainItem);

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
							hStationItem = m_treeStationSelect.InsertItem(szStationShowName, 8, 8, hChildItem);
						else
							hStationItem = m_treeStationSelect.InsertItem(szStationShowName, 10, 10, hChildItem);

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
							hChildItem1 = m_treeStationSelect.InsertItem(g_tStationNode_Info[j].node_name, 7, 7, hChildItem);
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
									hStationItem = m_treeStationSelect.InsertItem(szStationShowName, 8, 8, hChildItem1);
								else
									hStationItem = m_treeStationSelect.InsertItem(szStationShowName, 10, 10, hChildItem1);

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
								hChildItem2 = m_treeStationSelect.InsertItem(g_tStationNode_Info[k].node_name, 7, 7, hChildItem1);

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
											hStationItem = m_treeStationSelect.InsertItem(szStationShowName, 8, 8, hChildItem2);
										else
											hStationItem = m_treeStationSelect.InsertItem(szStationShowName, 10, 10, hChildItem2);

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

		hMainItem = m_treeStationSelect.GetRootItem();
		if (hMainItem != NULL)
		{
			hChildItem = m_treeStationSelect.GetChildItem(hMainItem);
			if (hChildItem != NULL)
			{
				m_treeStationSelect.SortChildren(hChildItem);//����
				hChildItem1 = m_treeStationSelect.GetChildItem(hChildItem);
				if (hChildItem1 != NULL)
				{
					m_treeStationSelect.EnsureVisible(hChildItem1);
				}
			}
		}

		hChildItem = m_treeStationSelect.GetNextSiblingItem(hChildItem);
		while(hChildItem != NULL)
		{
			m_treeStationSelect.SortChildren(hChildItem);//����
			hChildItem1 = m_treeStationSelect.GetChildItem(hChildItem);
			while(hChildItem1 != NULL)
			{
				m_treeStationSelect.SortChildren(hChildItem1);
				hChildItem1 = m_treeStationSelect.GetNextSiblingItem(hChildItem1);
			}
			hChildItem = m_treeStationSelect.GetNextSiblingItem(hChildItem);
		}
	}
	catch(...)
	{

	}
}

void CDlgStationSelect::SetCameraNodeInfo(HTREEITEM hItem, char* ItemName, char* Itemnum, int StationOrCameraID,int ItemStatus,int Streamless,float ItemLongitude, float ItemLatitude, int ItemDecodeTag, int Itemtype, char* stationname)
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

		m_treeStationSelect.SetItemData(hItem, (DWORD_PTR)pNodeInfo);
	}
	catch(...)
	{

	}
}

int CDlgStationSelect::CheckStationCurrentStatus2(int nStationId)
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

//ɾ������ͷ�����ӽڵ���Ϣ
void CDlgStationSelect::DeleteCameraChildTreeListInfo(HTREEITEM hItem)
{
	HTREEITEM	hChildItem = NULL;
	_T_NODE_INFO *pNodeInfo = NULL;
	DWORD_PTR pInfo = NULL;

	try
	{
		hChildItem = m_treeStationSelect.GetChildItem(hItem);
		while(hChildItem != NULL)
		{
			pInfo = m_treeStationSelect.GetItemData(hChildItem);
			if (pInfo != NULL)
			{
				pNodeInfo = (_T_NODE_INFO *)pInfo;
				delete pNodeInfo;
				pInfo = NULL;
				pNodeInfo = NULL;
				m_treeStationSelect.SetItemData(hChildItem,NULL);
			}

			DeleteCameraChildTreeListInfo(hChildItem);
			hChildItem = m_treeStationSelect.GetNextSiblingItem(hChildItem);
		}
	}
	catch(...)
	{

	}
}

//ɾ������ͷ�б���
void CDlgStationSelect::DeleteCameraTreeList()
{
	HTREEITEM	hMainItem = NULL;
	_T_NODE_INFO *pNodeInfo = NULL;
	DWORD_PTR pInfo = NULL;

	try
	{
		//�����б�
		hMainItem = m_treeStationSelect.GetRootItem();
		while(hMainItem != NULL)
		{
			pInfo = m_treeStationSelect.GetItemData(hMainItem);
			if (pInfo != NULL)
			{
				pNodeInfo = (_T_NODE_INFO *)pInfo;
				delete pNodeInfo;
				pInfo = NULL;
				pNodeInfo = NULL;
				m_treeStationSelect.SetItemData(hMainItem,NULL);
			}

			DeleteCameraChildTreeListInfo(hMainItem);
			hMainItem = m_treeStationSelect.GetNextSiblingItem(hMainItem);
		}
	}
	catch(...)
	{

	}

	m_treeStationSelect.DeleteAllItems();
}