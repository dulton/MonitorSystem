#include "stdafx.h"
#include "AssTreeOperate.h"
#include <vector>

//��ȡѡ�е����ڵ�
std::vector<HTREEITEM> GetCheckItem(CTreeCtrl *pTreeCtrl)
{
	std::vector<HTREEITEM> vecSelectedItems;
	HTREEITEM root = NULL;
	HTREEITEM hCilidItem = NULL;
	if (pTreeCtrl != NULL)
	{
		HTREEITEM root = pTreeCtrl->GetRootItem();
		if (pTreeCtrl->GetCheck(root))
		{
			hCilidItem = pTreeCtrl->GetChildItem(root);
			while(hCilidItem)
			{
				if (pTreeCtrl->GetCheck(hCilidItem))
				{
					vecSelectedItems.push_back(hCilidItem);
				}
			}
		}
	}
	return vecSelectedItems;
}

void CheckToTree(CTreeCtrl *pTreeCtrl, HTREEITEM hItem)
{
	//if (hItem != NULL)
	//{
	//	hCilidItem = pTreeCtrl->GetChildItem(root);
	//	while(hCilidItem)
	//	{
	//		if (pTreeCtrl->GetCheck(hCilidItem))
	//		{
	//			vecSelectedItems.push_back(hCilidItem);
	//		}
	//	}

	//}
}

//���վ����ʼ��
void GlobalInitStationTree(CTreeCtrl *pTreeCtrl)
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
				hMainItem = pTreeCtrl->InsertItem("ȫ��", 1, 1, TVI_ROOT, hMainItem);
				GlobalSetCameraNodeInfo(pTreeCtrl,
					hMainItem,
					"",
					"",
					0,
					1,
					0,
					0,
					0,
					0,
					0,
					"");
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

				hChildItem = pTreeCtrl->InsertItem(g_tStationNode_Info[i].node_name, 7, 7, hMainItem);
				GlobalSetCameraNodeInfo(pTreeCtrl,
					hChildItem,
					"",
					"",
					0,
					1,
					0,
					0,
					0,
					0,
					1,
					"");

				for (ns = 0; ns < g_nStation_Num; ns ++)
				{
					if (g_tStation_Info[ns].node_id == g_tStationNode_Info[i].node_id)
					{
						if (strlen(g_tStation_Info[ns].notes) != 0)
							sprintf_s(szStationShowName,sizeof(szStationShowName),"%s(%s)",g_tStation_Info[ns].station_name_videoplant,g_tStation_Info[ns].notes);
						else
							strcpy_s(szStationShowName,sizeof(szStationShowName),g_tStation_Info[ns].station_name_videoplant);

						nStationStatus = GlobalCheckStationCurrentStatus2(g_tStation_Info[ns].station_id);
						if (nStationStatus != 0)
							hStationItem = pTreeCtrl->InsertItem(szStationShowName, 8, 8, hChildItem);
						else
							hStationItem = pTreeCtrl->InsertItem(szStationShowName, 10, 10, hChildItem);

						GlobalSetCameraNodeInfo(pTreeCtrl,
							hStationItem,
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
							hChildItem1 = pTreeCtrl->InsertItem(g_tStationNode_Info[j].node_name, 7, 7, hChildItem);
						else
							hChildItem1 = hChildItem;

						GlobalSetCameraNodeInfo(pTreeCtrl,
							hChildItem1,
							"",
							"",
							0,
							1,
							0,
							0,
							0,
							0,
							1,
							"");

						for (ns = 0; ns < g_nStation_Num; ns ++)
						{
							if (g_tStation_Info[ns].node_id == g_tStationNode_Info[j].node_id)
							{
								if (strlen(g_tStation_Info[ns].notes) != 0)
									sprintf_s(szStationShowName,sizeof(szStationShowName),"%s(%s)",g_tStation_Info[ns].station_name_videoplant,g_tStation_Info[ns].notes);
								else
									strcpy_s(szStationShowName,sizeof(szStationShowName),g_tStation_Info[ns].station_name_videoplant);

								nStationStatus = GlobalCheckStationCurrentStatus2(g_tStation_Info[ns].station_id);
								if (nStationStatus != 0)
									hStationItem = pTreeCtrl->InsertItem(szStationShowName, 8, 8, hChildItem1);
								else
									hStationItem = pTreeCtrl->InsertItem(szStationShowName, 10, 10, hChildItem1);

								GlobalSetCameraNodeInfo(pTreeCtrl,
									hStationItem,
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
								hChildItem2 = pTreeCtrl->InsertItem(g_tStationNode_Info[k].node_name, 7, 7, hChildItem1);
								GlobalSetCameraNodeInfo(pTreeCtrl,
									hChildItem2,
									"",
									"",
									0,
									1,
									0,
									0,
									0,
									0,
									1,
									"");

								for (ns = 0; ns < g_nStation_Num; ns ++)
								{
									if (g_tStation_Info[ns].node_id == g_tStationNode_Info[k].node_id)
									{
										if (strlen(g_tStation_Info[ns].notes) != 0)
											sprintf_s(szStationShowName,sizeof(szStationShowName),"%s(%s)",g_tStation_Info[ns].station_name_videoplant,g_tStation_Info[ns].notes);
										else
											strcpy_s(szStationShowName,sizeof(szStationShowName),g_tStation_Info[ns].station_name_videoplant);

										nStationStatus = GlobalCheckStationCurrentStatus2(g_tStation_Info[ns].station_id);
										if (nStationStatus != 0)
											hStationItem = pTreeCtrl->InsertItem(szStationShowName, 8, 8, hChildItem2);
										else
											hStationItem = pTreeCtrl->InsertItem(szStationShowName, 10, 10, hChildItem2);

										GlobalSetCameraNodeInfo(pTreeCtrl,
											hStationItem,
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

		hMainItem = pTreeCtrl->GetRootItem();
		if (hMainItem != NULL)
		{
			hChildItem = pTreeCtrl->GetChildItem(hMainItem);
			if (hChildItem != NULL)
			{
				pTreeCtrl->SortChildren(hChildItem);//����
				hChildItem1 = pTreeCtrl->GetChildItem(hChildItem);
				if (hChildItem1 != NULL)
				{
					pTreeCtrl->EnsureVisible(hChildItem1);
				}
			}
		}

		hChildItem = pTreeCtrl->GetNextSiblingItem(hChildItem);
		while(hChildItem != NULL)
		{
			pTreeCtrl->SortChildren(hChildItem);//����
			hChildItem1 = pTreeCtrl->GetChildItem(hChildItem);
			while(hChildItem1 != NULL)
			{
				pTreeCtrl->SortChildren(hChildItem1);
				hChildItem1 = pTreeCtrl->GetNextSiblingItem(hChildItem1);
			}
			hChildItem = pTreeCtrl->GetNextSiblingItem(hChildItem);
		}
	}
	catch(...)
	{

	}
}

void GlobalSetCameraNodeInfo(CTreeCtrl *pTreeCtrl, HTREEITEM hItem, char* ItemName, char* Itemnum, int StationOrCameraID,int ItemStatus,int Streamless,float ItemLongitude, float ItemLatitude, int ItemDecodeTag, int Itemtype, char* stationname)
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

		pTreeCtrl->SetItemData(hItem, (DWORD_PTR)pNodeInfo);
	}
	catch(...)
	{

	}
}

int GlobalCheckStationCurrentStatus2(int nStationId)
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
void GlobalDeleteCameraChildTreeListInfo(CTreeCtrl *pTreeCtrl, HTREEITEM hItem)
{
	HTREEITEM	hChildItem = NULL;
	_T_NODE_INFO *pNodeInfo = NULL;
	DWORD_PTR pInfo = NULL;

	try
	{
		hChildItem = pTreeCtrl->GetChildItem(hItem);
		while(hChildItem != NULL)
		{
			pInfo = pTreeCtrl->GetItemData(hChildItem);
			if (pInfo != NULL)
			{
				pNodeInfo = (_T_NODE_INFO *)pInfo;
				delete pNodeInfo;
				pInfo = NULL;
				pNodeInfo = NULL;
				pTreeCtrl->SetItemData(hChildItem,NULL);
			}

			GlobalDeleteCameraChildTreeListInfo(pTreeCtrl, hChildItem);
			hChildItem = pTreeCtrl->GetNextSiblingItem(hChildItem);
		}
	}
	catch(...)
	{

	}
}

//ɾ������ͷ�б���
void GlobalDeleteCameraTreeList(CTreeCtrl *pTreeCtrl)
{
	HTREEITEM	hMainItem = NULL;
	_T_NODE_INFO *pNodeInfo = NULL;
	DWORD_PTR pInfo = NULL;

	try
	{
		//�����б�
		hMainItem = pTreeCtrl->GetRootItem();
		while(hMainItem != NULL)
		{
			pInfo = pTreeCtrl->GetItemData(hMainItem);
			if (pInfo != NULL)
			{
				pNodeInfo = (_T_NODE_INFO *)pInfo;
				delete pNodeInfo;
				pInfo = NULL;
				pNodeInfo = NULL;
				pTreeCtrl->SetItemData(hMainItem,NULL);
			}

			GlobalDeleteCameraChildTreeListInfo(pTreeCtrl, hMainItem);
			hMainItem = pTreeCtrl->GetNextSiblingItem(hMainItem);
		}
	}
	catch(...)
	{

	}

	pTreeCtrl->DeleteAllItems();
}