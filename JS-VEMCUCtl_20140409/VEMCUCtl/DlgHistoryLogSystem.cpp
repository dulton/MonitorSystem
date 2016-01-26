// DlgHistoryLogSystem.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "VEMCUCtlDlg.h"
#include "DlgHistoryLogSystem.h"


// CDlgHistoryLogSystem �Ի���

IMPLEMENT_DYNAMIC(CDlgHistoryLogSystem, CDialog)

CDlgHistoryLogSystem::CDlgHistoryLogSystem(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHistoryLogSystem::IDD, pParent)
{
	m_Brush.CreateSolidBrush(RGB(210,224,237)); 
}

CDlgHistoryLogSystem::~CDlgHistoryLogSystem()
{

}

void CDlgHistoryLogSystem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HL_NODE_NAME, m_strNodeName);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_HL_STARTDAY, m_StartDay);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_HL_STARTTIME, m_StartTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_HL_STOPDAY, m_StopDay);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_HL_STOPTIME, m_StopTime);
	DDX_Control(pDX, IDC_LIST_HISTORYLOG_SYSTEM, m_ListCtrl_SystemLog);
	DDX_Control(pDX, IDC_COMBO_HL_TYPE, m_ComboType);
	DDX_Control(pDX, IDC_COMBO_HL_SUB_TYPE, m_ComboSubType);
	DDX_Control(pDX, IDC_BUTTON_HL_CHOOSENODE, m_btnSelectNode);
	DDX_Control(pDX, IDC_BUTTON_HL_QUERY, m_btnQuery);
}


BEGIN_MESSAGE_MAP(CDlgHistoryLogSystem, CDialog)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_HL_QUERY, &CDlgHistoryLogSystem::OnBnClickedButtonHlQuery)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_HL_CHOOSENODE, &CDlgHistoryLogSystem::OnBnClickedButtonHlChoosenode)
END_MESSAGE_MAP()

// CDlgHistoryLogSystem ��Ϣ�������

BOOL CDlgHistoryLogSystem::OnInitDialog()
{
	CDialog::OnInitDialog();

	//////////////////////////////////////////////////////////////////////////
	InitControl();

	LoadSkin();

	return TRUE; 
}

BOOL CDlgHistoryLogSystem::InitControl()
{
	// ��ѯ����б�����Ҫ��ʾ���а����ˣ���ʼʱ�䡢����ʱ�䡢����ͷ���ơ�
	DWORD dwStyle;
	dwStyle = m_ListCtrl_SystemLog.GetStyle();
	dwStyle = LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT;
	m_ListCtrl_SystemLog.SetExtendedStyle(dwStyle);

	m_ListCtrl_SystemLog.InsertColumn(0,"����������");
	m_ListCtrl_SystemLog.SetColumnWidth(0,120);
	m_ListCtrl_SystemLog.InsertColumn(1,"����������");
	m_ListCtrl_SystemLog.SetColumnWidth(1,120);
	m_ListCtrl_SystemLog.InsertColumn(2,"������״̬");
	m_ListCtrl_SystemLog.SetColumnWidth(2,120);
	m_ListCtrl_SystemLog.InsertColumn(3,"CPUʹ����");
	m_ListCtrl_SystemLog.SetColumnWidth(3,120);
	m_ListCtrl_SystemLog.InsertColumn(4,"�ڴ�ʹ����");
	m_ListCtrl_SystemLog.SetColumnWidth(4,120);
	m_ListCtrl_SystemLog.InsertColumn(5,"�ڴ�ʹ����");
	m_ListCtrl_SystemLog.SetColumnWidth(5,120);
	m_ListCtrl_SystemLog.InsertColumn(6,"����ʹ����");
	m_ListCtrl_SystemLog.SetColumnWidth(6,120);
	m_ListCtrl_SystemLog.InsertColumn(7,"����ʱ��");
	m_ListCtrl_SystemLog.SetColumnWidth(7,120);

	m_ComboType.InsertString(0, "��������");
	m_ComboType.SetCurSel(0);

	m_ComboSubType.InsertString(0, "���з�����");
	m_ComboSubType.SetCurSel(0);

	CTime	nowtime	= CTime::GetCurrentTime();
	CTime	StartTime(nowtime.GetYear(), nowtime.GetMonth(), nowtime.GetDay(), 0, 0, 0);
	CTime	StopTime(nowtime.GetYear(), nowtime.GetMonth(), nowtime.GetDay(), 23, 59, 59);

	//��ʼʱ���ʼ��
	m_StartDay = StartTime;
	m_StartTime = StartTime;
	m_StopDay  = StopTime;
	m_StopTime  = StopTime;

	UpdateData(FALSE);

	return TRUE;
}

BOOL CDlgHistoryLogSystem::LoadSkin()
{
	m_btnSelectNode.LoadBitmap(IDB_BITMAP_SELECT_NODE);
	m_btnQuery.LoadBitmap(IDB_BITMAP_QUERY);

	m_ListCtrl_SystemLog.SetHeaderHeight(1.2f);          //����ͷ���߶�
	m_ListCtrl_SystemLog.SetHeaderFontHW(12,0);         //����ͷ������߶�,�Ϳ��,0��ʾȱʡ������Ӧ 
	m_ListCtrl_SystemLog.SetHeaderTextColor(RGB(58,77,93)); //����ͷ��������ɫ
	m_ListCtrl_SystemLog.SetHeaderBKColor(195,248,250,3); //����ͷ������ɫ

	m_ListCtrl_SystemLog.SetTextColor(RGB(36, 162, 146));
	m_ListCtrl_SystemLog.SetBkColor(RGB(239, 246, 253));
	m_ListCtrl_SystemLog.SetTextBkColor(RGB(239, 246, 253));
	m_ListCtrl_SystemLog.SetRowHeigt(15);               //�����и߶�
	m_ListCtrl_SystemLog.SetFontHW(12,0);               //��������߶ȣ��Ϳ��,0��ʾȱʡ���

// 	m_ListCtrl_SystemLog.SetHeaderHeight(1.2f);          //����ͷ���߶�
// 	m_ListCtrl_SystemLog.SetHeaderFontHW(16,0);         //����ͷ������߶�,�Ϳ��,0��ʾȱʡ������Ӧ 
// 	m_ListCtrl_SystemLog.SetHeaderTextColor(RGB(58,77,93)); //����ͷ��������ɫ
// 	m_ListCtrl_SystemLog.SetHeaderBKColor(162,197,227,3); //����ͷ������ɫ
// 
// 	m_ListCtrl_SystemLog.SetTextColor(RGB(36, 162, 146));
// 	m_ListCtrl_SystemLog.SetBkColor(RGB(239, 246, 253));
// 	m_ListCtrl_SystemLog.SetTextBkColor(RGB(239, 246, 253));
// 	m_ListCtrl_SystemLog.SetRowHeigt(25);               //�����и߶�
// 	m_ListCtrl_SystemLog.SetFontHW(15,0);               //��������߶ȣ��Ϳ��,0��ʾȱʡ���

	return TRUE;
}

void CDlgHistoryLogSystem::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//////////////////////////////////////////////////////////////////////////


}

BOOL CDlgHistoryLogSystem::OnEraseBkgnd(CDC* pDC)
{
	//////////////////////////////////////////////////////////////////////////
	//CRect   rect;
	//GetClientRect(&rect);

	//pDC->FillRect (rect, &m_Brush);

	return TRUE;
}

void CDlgHistoryLogSystem::OnBnClickedButtonHlQuery()
{
	UpdateData(true);

	int i = 0, j = 0;
	char s_starttime[128]={0};
	char s_stoptime[128]={0};

	CTime starttime(m_StartDay.GetYear(), m_StartDay.GetMonth(), m_StartDay.GetDay(),
		m_StartTime.GetHour(), m_StartTime.GetMinute(), m_StartTime.GetSecond());
	CTime stoptime(m_StopDay.GetYear(), m_StopDay.GetMonth(), m_StopDay.GetDay(),
		m_StopTime.GetHour(), m_StopTime.GetMinute(), m_StopTime.GetSecond());

	if (stoptime <= starttime)
	{
		MessageBox("ʱ��ѡ����󣺿�ʼʱ����ڽ���ʱ��","��Ƶ����");
		return;
	}

	sprintf(s_starttime, "%04d-%02d-%02d %02d:%02d:%02d",
		m_StartDay.GetYear(), m_StartDay.GetMonth(), m_StartDay.GetDay(),
		m_StartTime.GetHour(), m_StartTime.GetMinute(), m_StartTime.GetSecond());
	sprintf(s_stoptime, "%04d-%02d-%02d %02d:%02d:%02d",
		m_StopDay.GetYear(), m_StopDay.GetMonth(), m_StopDay.GetDay(),
		m_StopTime.GetHour(), m_StopTime.GetMinute(), m_StopTime.GetSecond());

	//���Ϊ�ȴ�״̬
	AfxGetApp()->DoWaitCursor(1); 

	m_ListCtrl_SystemLog.DeleteAllItems();

	int nSelectIndex = m_ComboType.GetCurSel();

	SearchAndSetHistoryListInfo(s_starttime,s_stoptime);

	//�ָ����Ϊ����״̬
	AfxGetApp()->DoWaitCursor(0);
}

void CDlgHistoryLogSystem::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	//////////////////////////////////////////////////////////////////////////
	CRect rect(0,0,0,0), rc;
	CWnd *pWnd;

	GetClientRect(rc);

	// *****************************************������İ�ť
	pWnd = GetDlgItem(IDC_LIST_HISTORYLOG_SYSTEM); //ϵͳ��־
	if(pWnd)
	{
		rect.left = rc.left + 5;
		rect.right = rc.right - 5;
		rect.top = rc.top + 150;
		rect.bottom = rc.bottom - 5;

		pWnd->MoveWindow(rect);
	}
}

HBRUSH CDlgHistoryLogSystem::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	//////////////////////////////////////////////////////////////////////////

	if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(10,10,10));
		return m_Brush;
	}

	//////////////////////////////////////////////////////////////////////////
	return hbr;
}


void CDlgHistoryLogSystem::OnDtnDatetimechangeDatetimepickerHlStartday(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	char str[64];
	CTime	nowtime;
	GetDlgItemText(IDC_DATETIMEPICKER_HL_STARTDAY,str,64);
	if ((memcmp(str,"1971-",5) < 0)||(memcmp(str,"2037-",5) > 0))
	{
		nowtime	= CTime::GetCurrentTime();
		CTime	StartTime(nowtime.GetYear(), nowtime.GetMonth(), 1, 0, 0, 0);
		m_StartDay = StartTime;
		m_StartTime = StartTime;
		UpdateData(false);
	}

	*pResult = 0;
}


void CDlgHistoryLogSystem::OnDtnDatetimechangeDatetimepickerHlStarttime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);


	*pResult = 0;
}


void CDlgHistoryLogSystem::OnDtnDatetimechangeDatetimepickerHlStopday(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	char str[64];
	CTime	nowtime;
	GetDlgItemText(IDC_DATETIMEPICKER_HL_STOPDAY,str,64);
	if ((memcmp(str,"1971-",5) < 0)||(memcmp(str,"2037-",5) > 0))
	{	
		nowtime	= CTime::GetCurrentTime();
		CTime	StopTime(nowtime.GetYear(), nowtime.GetMonth(), nowtime.GetDay(), 23, 59, 59);
		m_StopDay  = StopTime;
		m_StopTime  = StopTime;
		UpdateData(false);
	}


	*pResult = 0;
}


void CDlgHistoryLogSystem::OnDtnDatetimechangeDatetimepickerHlStoptime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);


	*pResult = 0;
}

void CDlgHistoryLogSystem::OnBnClickedButtonHlChoosenode()
{

}

BOOL CDlgHistoryLogSystem::SearchAndSetHistoryListInfo(char *szStartTime,char *szStopTime)
{
	if (szStartTime == NULL||szStopTime == NULL)
		return FALSE;

	char sql_buf[512] = {0};
	bool result=false;

	MYSQL_RES * res = NULL ;
	MYSQL_ROW	row ;

	char szServerName[256] = {0};
	char szServerType[64] = {0};
	char szServerState[64] = {0};
	char szCpuUseRate[64] = {0};
	char szMemoryUseRate[64] = {0};
	char szMemoryUse[64] = {0};
	char szDiscUse[64] = {0};
	char szUpdateTime[64] = {0};

	COLORREF BKColor;
	COLORREF TextColor;

	BKColor = RGB(207,235,250);
	TextColor = RGB(168,0,0);

	int nCount = 0;

	//��������ʷ��־
	sprintf_s(sql_buf, sizeof(sql_buf),"SELECT server_name, server_type, server_state, cpu_use_rate, memory_use_rate, memory_use, disk_use,"
		"time FROM history_server_load_state where time >= '%s' AND time <= '%s' ORDER BY time desc",szStartTime,szStopTime);

	if (!mysql_query(g_mySqlData, sql_buf))
	{
		res = mysql_store_result(g_mySqlData);

		while ( row = mysql_fetch_row( res ) )
		{
			if (nCount >= 300)
				break;

			sprintf_s(szServerName,"%s", row[0]);
			sprintf_s(szServerType, "%s", row[1]);
			sprintf_s(szServerState, "%s", row[2]);
			sprintf_s(szCpuUseRate,"%s%%",row[3]);
			sprintf_s(szMemoryUseRate,"%s%%",row[4]);
			sprintf_s(szMemoryUse,"%sK",row[5]);
			sprintf_s(szDiscUse,"%sK",row[6]);
			sprintf_s(szUpdateTime,"%s",row[7]);

			//////////////////////////////////////////////////////////////////////////
			if (strcmp(szServerType,"1") == 0)//����
			{
				sprintf_s(szServerType,"����������");
			}

			if (strcmp(szServerState,"1") == 0)//״̬
			{
				sprintf_s(szServerState,"����");
			}
			else if (strcmp(szServerState,"0") == 0)
			{
				sprintf_s(szServerState,"����");
			}

			if (strcmp(szMemoryUse,"0K") == 0&&strcmp(szDiscUse,"0K") == 0)//������
			{
				sprintf_s(szServerState,"����");
			}
			//////////////////////////////////////////////////////////////////////////

			m_ListCtrl_SystemLog.InsertItem(nCount,szServerName);
			m_ListCtrl_SystemLog.SetItemText(nCount,1,szServerType);
			m_ListCtrl_SystemLog.SetItemText(nCount,2,szServerState);
			m_ListCtrl_SystemLog.SetItemText(nCount,3,szCpuUseRate);
			m_ListCtrl_SystemLog.SetItemText(nCount,4,szMemoryUseRate);
			m_ListCtrl_SystemLog.SetItemText(nCount,5,szMemoryUse);
			m_ListCtrl_SystemLog.SetItemText(nCount,6,szDiscUse);
			m_ListCtrl_SystemLog.SetItemText(nCount,7,szUpdateTime);

			m_ListCtrl_SystemLog.SetRowColor(nCount,BKColor);
			m_ListCtrl_SystemLog.SetRowTextColor(nCount,TextColor);

			nCount++;
		}
		mysql_free_result( res ) ;
	}

	return TRUE;
}
