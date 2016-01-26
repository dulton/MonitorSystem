// DlgDeviceLedger.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "VEMCUCtlDlg.h"
#include "DlgDeviceLedger.h"

CDlgDeviceLedger *g_pDlgDeviceLedger = NULL;


// CDlgDeviceLedger �Ի���

IMPLEMENT_DYNAMIC(CDlgDeviceLedger, CDialog)

CDlgDeviceLedger::CDlgDeviceLedger(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDeviceLedger::IDD, pParent)
{

}

CDlgDeviceLedger::~CDlgDeviceLedger()
{
}

void CDlgDeviceLedger::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DEVICE_LEDGER, m_lstDeviceLedger);
	DDX_Control(pDX, IDC_DEVICE_LEDGER_STATION_TREE, m_treeDeviceLedgerStation);
	DDX_Control(pDX, IDC_BUTTON_DEVICE_LEDGER_QUERY, m_btnDeviceLedger);
}


BEGIN_MESSAGE_MAP(CDlgDeviceLedger, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_LEDGER_QUERY, &CDlgDeviceLedger::OnBnClickedButtonDeviceLedgerQuery)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_STATION, &CDlgDeviceLedger::OnBnClickedButtonSelectStation)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_LEDGER_EXPORT, &CDlgDeviceLedger::OnBnClickedButtonDeviceLedgerExport)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_LEDGER_STATISTICAL, &CDlgDeviceLedger::OnBnClickedButtonDeviceLedgerStatistical)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDlgDeviceLedger ��Ϣ�������

//ƴ��ѡ��ı��վ������
CString CDlgDeviceLedger::GetQueryCondition(std::vector<HTREEITEM> vecSelectedItems)
{
	_T_NODE_INFO* pNodeInfo = NULL;
	CString strCondition = "where 1=2";

	for (size_t t = 0; t < vecSelectedItems.size(); t++)
	{
		HTREEITEM item = vecSelectedItems.at(t);
		pNodeInfo = (_T_NODE_INFO*)m_treeDeviceLedgerStation.GetItemData(item);

		//����Ǳ��վ
		if (pNodeInfo->node_type == 2)
		{
			int nStationId = pNodeInfo->node_id;
			CString strStationIdText;
			strStationIdText.Format(" or a.station_id=%d",nStationId);
			strCondition += strStationIdText;
		}
	}

	return strCondition;
}

void CDlgDeviceLedger::AddDeviceLedgersToList(std::vector<_T_ASS_DEVICE_LEDGER_> vecDeviceLedgers)
{
	int nIndex = 0;
	for (size_t t = 0; t < vecDeviceLedgers.size(); t++)
	{
		CString strIndex = "";
		strIndex.Format("%d",nIndex);
		m_lstDeviceLedger.InsertItem(nIndex,strIndex);

		m_lstDeviceLedger.SetItemText(nIndex,1,vecDeviceLedgers.at(t).szStationName);
		m_lstDeviceLedger.SetItemText(nIndex,2,vecDeviceLedgers.at(t).device_name);
		m_lstDeviceLedger.SetItemText(nIndex,3,vecDeviceLedgers.at(t).device_manufacturer);
		m_lstDeviceLedger.SetItemText(nIndex,4,vecDeviceLedgers.at(t).device_ip);
		m_lstDeviceLedger.SetItemText(nIndex,5,IntToCString(vecDeviceLedgers.at(t).device_port));
		m_lstDeviceLedger.SetItemText(nIndex,6,vecDeviceLedgers.at(t).login_username);
		m_lstDeviceLedger.SetItemText(nIndex,7,vecDeviceLedgers.at(t).login_password);
		m_lstDeviceLedger.SetItemText(nIndex,8,vecDeviceLedgers.at(t).protocol_type);
		m_lstDeviceLedger.SetItemText(nIndex,9,vecDeviceLedgers.at(t).device_type);
		m_lstDeviceLedger.SetItemText(nIndex,10,vecDeviceLedgers.at(t).harddisk_capacity);
		m_lstDeviceLedger.SetItemText(nIndex,11,IntToCString(vecDeviceLedgers.at(t).analog_video_num));
		m_lstDeviceLedger.SetItemText(nIndex,12,IntToCString(vecDeviceLedgers.at(t).net_video_num));

		nIndex++;
	}

	if (nIndex == 0)
	{
		m_lstDeviceLedger.InsertItem(nIndex,"������");

		m_lstDeviceLedger.SetItemText(nIndex,1,"������");
		m_lstDeviceLedger.SetItemText(nIndex,2,"������");
		m_lstDeviceLedger.SetItemText(nIndex,3,"������");
		m_lstDeviceLedger.SetItemText(nIndex,4,"������");
		m_lstDeviceLedger.SetItemText(nIndex,5,"������");
		m_lstDeviceLedger.SetItemText(nIndex,6,"������");
		m_lstDeviceLedger.SetItemText(nIndex,7,"������");
		m_lstDeviceLedger.SetItemText(nIndex,8,"������");
		m_lstDeviceLedger.SetItemText(nIndex,9,"������");
		m_lstDeviceLedger.SetItemText(nIndex,10,"������");
		m_lstDeviceLedger.SetItemText(nIndex,11,"������");
		m_lstDeviceLedger.SetItemText(nIndex,12,"������");
	}
}

void CDlgDeviceLedger::OnBnClickedButtonDeviceLedgerQuery()
{
	//���֮ǰ������
	m_lstDeviceLedger.DeleteAllItems();

	//��ȡ����ѡ�еı��վ
	std::vector<HTREEITEM> vecSelectedStationItems;
	m_treeDeviceLedgerStation.GetCheckItems(vecSelectedStationItems, m_treeDeviceLedgerStation.GetRootItem());

	//ƴ�ӳ���ѯ����
	CString strCondition = GetQueryCondition(vecSelectedStationItems);

	//��ѯ���ݿ�
	std::vector<_T_ASS_DEVICE_LEDGER_> vecDeviceLedgers = GetDeviceLedgersFromDB(strCondition);

	//��ӵ��б�
	AddDeviceLedgersToList(vecDeviceLedgers);
}

BOOL CDlgDeviceLedger::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitControl();

	InitStationTree(&m_treeDeviceLedgerStation);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgDeviceLedger::InitStationTree(CTreeCtrl *pTreeCtrl)
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
				SetCameraNodeInfo(pTreeCtrl,
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
				SetCameraNodeInfo(pTreeCtrl,
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

						nStationStatus = CheckStationCurrentStatus2(g_tStation_Info[ns].station_id);
						if (nStationStatus != 0)
							hStationItem = pTreeCtrl->InsertItem(szStationShowName, 8, 8, hChildItem);
						else
							hStationItem = pTreeCtrl->InsertItem(szStationShowName, 10, 10, hChildItem);

						SetCameraNodeInfo(pTreeCtrl,
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

						SetCameraNodeInfo(pTreeCtrl,
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

								nStationStatus = CheckStationCurrentStatus2(g_tStation_Info[ns].station_id);
								if (nStationStatus != 0)
									hStationItem = pTreeCtrl->InsertItem(szStationShowName, 8, 8, hChildItem1);
								else
									hStationItem = pTreeCtrl->InsertItem(szStationShowName, 10, 10, hChildItem1);

								SetCameraNodeInfo(pTreeCtrl,
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
								SetCameraNodeInfo(pTreeCtrl,
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

										nStationStatus = CheckStationCurrentStatus2(g_tStation_Info[ns].station_id);
										if (nStationStatus != 0)
											hStationItem = pTreeCtrl->InsertItem(szStationShowName, 8, 8, hChildItem2);
										else
											hStationItem = pTreeCtrl->InsertItem(szStationShowName, 10, 10, hChildItem2);

										SetCameraNodeInfo(pTreeCtrl,
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

void CDlgDeviceLedger::SetCameraNodeInfo(CTreeCtrl *pTreeCtrl, HTREEITEM hItem, char* ItemName, char* Itemnum, int StationOrCameraID,int ItemStatus,int Streamless,float ItemLongitude, float ItemLatitude, int ItemDecodeTag, int Itemtype, char* stationname)
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

int CDlgDeviceLedger::CheckStationCurrentStatus2(int nStationId)
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
void CDlgDeviceLedger::DeleteCameraChildTreeListInfo(CTreeCtrl *pTreeCtrl, HTREEITEM hItem)
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

			DeleteCameraChildTreeListInfo(pTreeCtrl, hChildItem);
			hChildItem = pTreeCtrl->GetNextSiblingItem(hChildItem);
		}
	}
	catch(...)
	{

	}
}

//ɾ������ͷ�б���
void CDlgDeviceLedger::DeleteCameraTreeList(CTreeCtrl *pTreeCtrl)
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

			DeleteCameraChildTreeListInfo(pTreeCtrl, hMainItem);
			hMainItem = pTreeCtrl->GetNextSiblingItem(hMainItem);
		}
	}
	catch(...)
	{

	}

	pTreeCtrl->DeleteAllItems();
}

void CDlgDeviceLedger::InitControl()
{
	m_imageList.Create(IDB_BITMAP_TREE,16,0,RGB(255,0,255));
	m_treeDeviceLedgerStation.SetImageList(&m_imageList, TVSIL_NORMAL);

	DWORD dwStyle;
	dwStyle = m_lstDeviceLedger.GetStyle();
	dwStyle = LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT ;

	m_lstDeviceLedger.SetExtendedStyle(dwStyle);
	m_lstDeviceLedger.SetBkColor(RGB(239,246,253));
	m_lstDeviceLedger.SetTextBkColor(RGB(0xfe,0xFF,0xc6));

	m_lstDeviceLedger.DeleteAllItems();
	while(m_lstDeviceLedger.DeleteColumn(0));

	CRect rect;
	GetWindowRect(&rect);

	int nWidth = rect.right - rect.left;

	m_lstDeviceLedger.InsertColumn(0,"���");
	m_lstDeviceLedger.SetColumnWidth(0,nWidth*0.05);
	m_lstDeviceLedger.InsertColumn(1,"�豸����");
	m_lstDeviceLedger.SetColumnWidth(1,nWidth*0.1);
	m_lstDeviceLedger.InsertColumn(2,"�豸����");
	m_lstDeviceLedger.SetColumnWidth(2,nWidth*0.1);
	m_lstDeviceLedger.InsertColumn(3,"�豸IP");
	m_lstDeviceLedger.SetColumnWidth(3,nWidth*0.1);
	m_lstDeviceLedger.InsertColumn(4,"�豸�˿�");
	m_lstDeviceLedger.SetColumnWidth(4,nWidth*0.1);
	m_lstDeviceLedger.InsertColumn(5,"��½�û���");
	m_lstDeviceLedger.SetColumnWidth(5,nWidth*0.1);
	m_lstDeviceLedger.InsertColumn(6,"��½����");
	m_lstDeviceLedger.SetColumnWidth(6,nWidth*0.1);
	m_lstDeviceLedger.InsertColumn(7,"Э������");
	m_lstDeviceLedger.SetColumnWidth(7,nWidth*0.1);
	m_lstDeviceLedger.InsertColumn(8,"�豸����");
	m_lstDeviceLedger.SetColumnWidth(8,nWidth*0.1);
	m_lstDeviceLedger.InsertColumn(9,"Ӳ������");
	m_lstDeviceLedger.SetColumnWidth(9,nWidth*0.1);
	m_lstDeviceLedger.InsertColumn(10,"ģ����Ƶ����");
	m_lstDeviceLedger.SetColumnWidth(10,nWidth*0.1);
	m_lstDeviceLedger.InsertColumn(11,"������Ƶ����");
	m_lstDeviceLedger.SetColumnWidth(11,nWidth*0.1);

	InitButtonColor(GetDlgItem(IDC_BUTTON_DEVICE_LEDGER_QUERY));
}
void CDlgDeviceLedger::OnBnClickedButtonSelectStation()
{
	
}

void CDlgDeviceLedger::OnBnClickedButtonDeviceLedgerExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CDlgDeviceLedger::OnBnClickedButtonDeviceLedgerStatistical()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CDlgDeviceLedger::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect winrc,static_rect,list_rect;
	GetClientRect(&winrc);

	int nWidth = cx;
	int nHeight = cy;

	int nStaticStationTextHeight = 30;
	int nStaticStationTextWidth = cx * 0.15;

	int nStationTreeWidth = cx * 0.15;
	int nStationTreeHeight = cy - nStaticStationTextHeight;

	int nButtonHeight = 30;
	int nButtonWidth = 100;

	int nDeviceListWidth = cx * 0.85;
	int nDeviceListHeight = cy - nButtonHeight;

	int nJianXi = 7;//���ߵļ�϶

	CWnd* pWnd = NULL;
	//���վ�ı�
	//pWnd = GetDlgItem(IDC_STATIC_DEVICE_LEDGER_STATION);
	//if (pWnd != NULL)
	//{
	//	static_rect.top = winrc.top;
	//	static_rect.bottom = static_rect.top + nStaticStationTextHeight;
	//	static_rect.left = winrc.left;
	//	static_rect.right = static_rect.left + nStaticStationTextWidth;
	//	pWnd->MoveWindow(static_rect);
	//}

	//���վ��
	pWnd = GetDlgItem(IDC_DEVICE_LEDGER_STATION_TREE);
	if (pWnd != NULL)
	{
		static_rect.top = winrc.top;
		static_rect.bottom = static_rect.top + nStationTreeHeight;
		static_rect.left = winrc.left;
		static_rect.right = static_rect.left + nStationTreeWidth;
		pWnd->MoveWindow(static_rect);
	}

	//��ѯ��ť
	pWnd = GetDlgItem(IDC_BUTTON_DEVICE_LEDGER_QUERY);
	if (pWnd != NULL)
	{
		static_rect.top = winrc.top;
		static_rect.bottom = static_rect.top + nButtonHeight;
		static_rect.left = static_rect.right + nJianXi;
		static_rect.right = static_rect.left + nButtonWidth;
		pWnd->MoveWindow(static_rect);
	}

	//�б�
	pWnd = GetDlgItem(IDC_LIST_DEVICE_LEDGER);
	if (pWnd != NULL)
	{
		static_rect.top = static_rect.bottom;
		static_rect.bottom = static_rect.top + nDeviceListHeight;
		static_rect.left = static_rect.left;
		static_rect.right = static_rect.left + nDeviceListWidth;
		pWnd->MoveWindow(static_rect);
	}


}

BOOL CDlgDeviceLedger::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;

	return CDialog::OnEraseBkgnd(pDC);
}
