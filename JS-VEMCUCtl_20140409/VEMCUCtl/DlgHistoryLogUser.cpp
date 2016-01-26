// DlgHistoryLogUser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "VEMCUCtlDlg.h"
#include "DlgHistoryLogUser.h"
#include "DlgSelectUser.h"
#include "VMTypeDefine.h"


// CDlgHistoryLogUser �Ի���

IMPLEMENT_DYNAMIC(CDlgHistoryLogUser, CDialog)

CDlgHistoryLogUser::CDlgHistoryLogUser(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHistoryLogUser::IDD, pParent)
{
	m_Brush.CreateSolidBrush(RGB(210,224,237)); 
}

CDlgHistoryLogUser::~CDlgHistoryLogUser()
{
}

void CDlgHistoryLogUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HL_NODE_NAME, m_strNodeName);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_HL_STARTDAY, m_StartDay);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_HL_STARTTIME, m_StartTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_HL_STOPDAY, m_StopDay);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_HL_STOPTIME, m_StopTime);
	DDX_Control(pDX, IDC_LIST_HISTORYLOG_USER, m_ListCtrl_UserLog);
	DDX_Control(pDX, IDC_COMBO_HL_TYPE, m_ComboType);
	DDX_Control(pDX, IDC_COMBO_HL_SUB_TYPE, m_ComboSubType);
	DDX_Control(pDX, IDC_BUTTON_HL_CHOOSENODE, m_btnSelectNode);
	DDX_Control(pDX, IDC_BUTTON_HL_QUERY, m_btnQuery);
}


BEGIN_MESSAGE_MAP(CDlgHistoryLogUser, CDialog)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_HL_QUERY, &CDlgHistoryLogUser::OnBnClickedButtonHlQuery)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_HL_CHOOSENODE, &CDlgHistoryLogUser::OnBnClickedButtonHlChoosenode)
END_MESSAGE_MAP()


// CDlgHistoryLogUser ��Ϣ�������

BOOL CDlgHistoryLogUser::OnInitDialog()
{
	CDialog::OnInitDialog();

	//////////////////////////////////////////////////////////////////////////
	InitControl();

	LoadSkin();


	return TRUE; 
}

BOOL CDlgHistoryLogUser::InitControl()
{
	// ��ѯ����б�����Ҫ��ʾ���а����ˣ���ʼʱ�䡢����ʱ�䡢����ͷ���ơ�
	DWORD dwStyle;
	dwStyle = m_ListCtrl_UserLog.GetStyle();
	dwStyle = LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT;
	m_ListCtrl_UserLog.SetExtendedStyle(dwStyle);

	InitControlList();

	m_strNodeName = "ȫ���û�";

//	m_ComboType.InsertString(0, "��������");
	m_ComboType.InsertString(0,"����˲���");
	m_ComboType.InsertString(1,"�ͻ��˲���");
	m_ComboType.InsertString(2,"��������˲���");
	m_ComboType.SetCurSel(0);

	m_ComboSubType.InsertString(0, "���з�����");
	m_ComboSubType.SetCurSel(0);

	CTime	nowtime	= CTime::GetCurrentTime();
	CTime	StartTime(nowtime.GetYear(), nowtime.GetMonth(),nowtime.GetDay(), 0, 0, 0);
	CTime	StopTime(nowtime.GetYear(), nowtime.GetMonth(), nowtime.GetDay(), 23, 59, 59);

	//��ʼʱ���ʼ��
	m_StartDay = StartTime;
	m_StartTime = StartTime;
	m_StopDay  = StopTime;
	m_StopTime  = StopTime;

	UpdateData(FALSE);

	return TRUE;
}

BOOL CDlgHistoryLogUser::InitControlList()
{
	m_ListCtrl_UserLog.DeleteAllItems();
	while(m_ListCtrl_UserLog.DeleteColumn(0));
	
	m_ListCtrl_UserLog.InsertColumn(0,"�û�����");
	m_ListCtrl_UserLog.SetColumnWidth(0,100);
	m_ListCtrl_UserLog.InsertColumn(1,"�û���ַ");
	m_ListCtrl_UserLog.SetColumnWidth(1,100);
	m_ListCtrl_UserLog.InsertColumn(2,"����ʱ��");
	m_ListCtrl_UserLog.SetColumnWidth(2,140);
	m_ListCtrl_UserLog.InsertColumn(3,"��������");
	m_ListCtrl_UserLog.SetColumnWidth(3,60);
	m_ListCtrl_UserLog.InsertColumn(4,"���ݿ����");
	m_ListCtrl_UserLog.SetColumnWidth(4,230);
	m_ListCtrl_UserLog.InsertColumn(5,"��ע");
	m_ListCtrl_UserLog.SetColumnWidth(5,500);
	
	return TRUE;
}

BOOL CDlgHistoryLogUser::InitControlList2()
{
	m_ListCtrl_UserLog.DeleteAllItems();
	while(m_ListCtrl_UserLog.DeleteColumn(0));

	UpdateData(FALSE);

	m_ListCtrl_UserLog.InsertColumn(0,"�û�����");
	m_ListCtrl_UserLog.SetColumnWidth(0,100);
	m_ListCtrl_UserLog.InsertColumn(1,"�û���ַ");
	m_ListCtrl_UserLog.SetColumnWidth(1,100);
	m_ListCtrl_UserLog.InsertColumn(2,"����ʱ��");
	m_ListCtrl_UserLog.SetColumnWidth(2,140);
	m_ListCtrl_UserLog.InsertColumn(3,"��������");
	m_ListCtrl_UserLog.SetColumnWidth(3,120);
	m_ListCtrl_UserLog.InsertColumn(4,"�����");
	m_ListCtrl_UserLog.SetColumnWidth(4,110);
	m_ListCtrl_UserLog.InsertColumn(5,"���վ��");
	m_ListCtrl_UserLog.SetColumnWidth(5,180);
	m_ListCtrl_UserLog.InsertColumn(6,"���վ����");
	m_ListCtrl_UserLog.SetColumnWidth(6,180);
	m_ListCtrl_UserLog.InsertColumn(7,"����ͷ��");
	m_ListCtrl_UserLog.SetColumnWidth(7,180);
	m_ListCtrl_UserLog.InsertColumn(8,"����ͷ����");
	m_ListCtrl_UserLog.SetColumnWidth(8,200);

	UpdateData(FALSE);

	return TRUE;
}

BOOL CDlgHistoryLogUser::InitControlList3()
{
	m_ListCtrl_UserLog.DeleteAllItems();
	while(m_ListCtrl_UserLog.DeleteColumn(0));

	UpdateData(FALSE);

	m_ListCtrl_UserLog.InsertColumn(0,"�û�����");
	m_ListCtrl_UserLog.SetColumnWidth(0,100);
	m_ListCtrl_UserLog.InsertColumn(1,"�û���ַ");
	m_ListCtrl_UserLog.SetColumnWidth(1,100);
	m_ListCtrl_UserLog.InsertColumn(2,"����ʱ��");
	m_ListCtrl_UserLog.SetColumnWidth(2,140);
	m_ListCtrl_UserLog.InsertColumn(3,"��������");
	m_ListCtrl_UserLog.SetColumnWidth(3,140);

	UpdateData(FALSE);

	return TRUE;
}

BOOL CDlgHistoryLogUser::LoadSkin()
{
	m_btnSelectNode.LoadBitmap(IDB_BITMAP_SELECT_NODE);
	m_btnQuery.LoadBitmap(IDB_BITMAP_QUERY);

	m_ListCtrl_UserLog.SetHeaderHeight(1.2f);          //����ͷ���߶�
	m_ListCtrl_UserLog.SetHeaderFontHW(12,0);         //����ͷ������߶�,�Ϳ��,0��ʾȱʡ������Ӧ 
	m_ListCtrl_UserLog.SetHeaderTextColor(RGB(58,77,93)); //����ͷ��������ɫ
	m_ListCtrl_UserLog.SetHeaderBKColor(195,248,250,3); //����ͷ������ɫ

	m_ListCtrl_UserLog.SetTextColor(RGB(36, 162, 146));
	m_ListCtrl_UserLog.SetBkColor(RGB(239, 246, 253));
	m_ListCtrl_UserLog.SetTextBkColor(RGB(239, 246, 253));
	m_ListCtrl_UserLog.SetRowHeigt(15);               //�����и߶�
	m_ListCtrl_UserLog.SetFontHW(12,0);               //��������߶ȣ��Ϳ��,0��ʾȱʡ���

// 	m_ListCtrl_UserLog.SetHeaderHeight(1.2f);          //����ͷ���߶�
// 	m_ListCtrl_UserLog.SetHeaderFontHW(16,0);         //����ͷ������߶�,�Ϳ��,0��ʾȱʡ������Ӧ 
// 	m_ListCtrl_UserLog.SetHeaderTextColor(RGB(58,77,93)); //����ͷ��������ɫ
// 	m_ListCtrl_UserLog.SetHeaderBKColor(162,197,227,3); //����ͷ������ɫ
// 
// 	m_ListCtrl_UserLog.SetTextColor(RGB(36, 162, 146));
// 	m_ListCtrl_UserLog.SetBkColor(RGB(239, 246, 253));
// 	m_ListCtrl_UserLog.SetTextBkColor(RGB(239, 246, 253));
// 	m_ListCtrl_UserLog.SetRowHeigt(25);               //�����и߶�
// 	m_ListCtrl_UserLog.SetFontHW(15,0);               //��������߶ȣ��Ϳ��,0��ʾȱʡ���

	return TRUE;
}

void CDlgHistoryLogUser::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//////////////////////////////////////////////////////////////////////////


}

BOOL CDlgHistoryLogUser::OnEraseBkgnd(CDC* pDC)
{
	//////////////////////////////////////////////////////////////////////////
// 	CRect   rect;
// 	GetClientRect(&rect);
// 
// 	pDC->FillRect (rect, &m_Brush);

	return TRUE;
}

void CDlgHistoryLogUser::OnBnClickedButtonHlQuery()
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

	m_ListCtrl_UserLog.DeleteAllItems();

	int nSelectIndex = m_ComboType.GetCurSel();

	if (nSelectIndex == 0)    //����˲���
		SearchAndSetHistoryListInfo(s_starttime,s_stoptime,(char *)(LPCTSTR)m_strNodeName);
	else if(nSelectIndex == 1)    //�ͻ��˲���
		SearchAndSetHistoryListInfo2(s_starttime,s_stoptime,(char *)(LPCTSTR)m_strNodeName);
	else if(nSelectIndex == 2)    //����ϵͳ����˲���
		SearchAndSetHistoryListInfo3(s_starttime,s_stoptime,(char *)(LPCTSTR)m_strNodeName);
	//�ָ����Ϊ����״̬
	AfxGetApp()->DoWaitCursor(0);
}

/*
	���ܣ���ѯ����ϵͳ������¼
		1.listcontrol��ʼ��
		2.��ȡ����
		3.����ѯ�������ӱ���ȡ��������¼��־
		4.����¼��ӵ�listcontrol��
*/
BOOL CDlgHistoryLogUser::SearchAndSetHistoryListInfo3(char *szStartTime,char *szStopTime,char *szSelectUserName)
{
	//listControl��ʼ��
	InitControlList3();
	
	//��ȡ����
	char szYear[8] = {0};
	szYear[0] = szStartTime[0];
	szYear[1] = szStartTime[1];
	szYear[2] = szStartTime[2];
	szYear[3] = szStartTime[3];
	CString strTableName = "";
	strTableName.Format("ass_user_operate_log_%s",szYear);

	//ƴ��sql�ַ���
	char sql_buf[1024] = {0};
	if (strcmp(szSelectUserName,"ȫ���û�") == 0)
	{
		sprintf_s(sql_buf,"SELECT a.id, a.user_id, b.user_name, a.ip_address, a.operate_time, a.operate_action "
			" FROM %s AS a LEFT JOIN ct_user AS b ON a.user_id = b.user_id", strTableName.GetBuffer());
	}
	else
	{
		sprintf_s(sql_buf,"SELECT a.id, a.user_id, b.user_name, a.ip_address, a.operate_time, a.operate_action "
			" FROM %s AS a LEFT JOIN ct_user AS b ON a.user_id = b.user_id where b.user_name='%s'", strTableName.GetBuffer(), szSelectUserName);
	}

	//ȡ������¼���ݣ���ӵ�listcontrol��
	COLORREF BKColor;
	COLORREF TextColor;
	BKColor = RGB(207,235,250);
	TextColor = RGB(168,0,0);
	MYSQL_RES *res;
	MYSQL_ROW row;
	int nCount = 0;
	if (!mysql_query(g_mySqlData, sql_buf))
	{
		res = mysql_store_result(g_mySqlData);

		while ( row = mysql_fetch_row( res ) )
		{
			if (nCount >= 1000)
			{
				MessageBox("�û�������־����1000��,���������޷���ʾ��\r\n����С��ѯ��Χ��","�ȵ���Ƶ����");
				break;
			}

			ASS_USER_OPERATE_LOG tAssUserOperateLog;
			tAssUserOperateLog.id = atoi(row[0]);
			tAssUserOperateLog.user_id = atoi(row[1]);
			sprintf_s(tAssUserOperateLog.szUserName,"%s",row[2]);
			sprintf_s(tAssUserOperateLog.ip_address,"%s",row[3]);
			sprintf_s(tAssUserOperateLog.operate_time,"%s",row[4]);
			sprintf_s(tAssUserOperateLog.operate_action,"%s",row[5]);

			m_ListCtrl_UserLog.InsertItem(nCount,tAssUserOperateLog.szUserName);
			m_ListCtrl_UserLog.SetItemText(nCount,1,tAssUserOperateLog.ip_address);
			m_ListCtrl_UserLog.SetItemText(nCount,2,tAssUserOperateLog.operate_time);
			m_ListCtrl_UserLog.SetItemText(nCount,3,tAssUserOperateLog.operate_action);

			m_ListCtrl_UserLog.SetRowColor(nCount,BKColor);
			m_ListCtrl_UserLog.SetRowTextColor(nCount,TextColor);

			nCount++;
		}

		mysql_free_result( res ) ;
	}

	//���ûȡ�����ݣ�����һ�������ݵ�listcontrol
	if (m_ListCtrl_UserLog.GetItemCount() == 0)
	{
		m_ListCtrl_UserLog.InsertItem(nCount,"��");
		m_ListCtrl_UserLog.SetItemText(nCount,1,"��");
		m_ListCtrl_UserLog.SetItemText(nCount,2,"��");
		m_ListCtrl_UserLog.SetItemText(nCount,3,"��");
	}

	return TRUE;
}

void CDlgHistoryLogUser::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	//////////////////////////////////////////////////////////////////////////

	CRect rect(0,0,0,0), rc;
	CWnd *pWnd;

	GetClientRect(rc);

	// *****************************************������İ�ť
	pWnd = GetDlgItem(IDC_LIST_HISTORYLOG_USER); //ϵͳ��־
	if(pWnd)
	{
		rect.left = rc.left + 5;
		rect.right = rc.right - 5;
		rect.top = rc.top + 150;
		rect.bottom = rc.bottom - 5;

		pWnd->MoveWindow(rect);
	}

}

HBRUSH CDlgHistoryLogUser::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CDlgHistoryLogUser::OnDtnDatetimechangeDatetimepickerHlStartday(NMHDR *pNMHDR, LRESULT *pResult)
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


void CDlgHistoryLogUser::OnDtnDatetimechangeDatetimepickerHlStarttime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);


	*pResult = 0;
}


void CDlgHistoryLogUser::OnDtnDatetimechangeDatetimepickerHlStopday(NMHDR *pNMHDR, LRESULT *pResult)
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


void CDlgHistoryLogUser::OnDtnDatetimechangeDatetimepickerHlStoptime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);


	*pResult = 0;
}

void CDlgHistoryLogUser::OnBnClickedButtonHlChoosenode()
{
	CDlgSelectUser DlgSelectUser;

	if (DlgSelectUser.DoModal() == IDOK)
	{
		m_strNodeName = DlgSelectUser.m_strUserName;
		UpdateData(FALSE);
	}
}

BOOL CDlgHistoryLogUser::SearchAndSetHistoryListInfo(char *szStartTime,char *szStopTime,char *szSelectUserName)
{
	if (szStartTime == NULL||szStopTime == NULL)
		return FALSE;

	InitControlList();

	char sql_buf[512] = {0};
	bool result=false;

	char szYear[8] = {0};
	int nYear = 2013;

	MYSQL_RES * res = NULL ;
	MYSQL_ROW	row ;

	char szUserName[256] = {0};
	char szIpAddress[64] = {0};
	char szDateTime[64] = {0};
	char szOperateType[64] = {0};
	char szDbTableName[256] = {0};
	char szNotes[512] = {0};
	int    nOperateType = 0;
	
	COLORREF BKColor;
	COLORREF TextColor;

	BKColor = RGB(207,235,250);
	TextColor = RGB(168,0,0);

	szYear[0] = szStartTime[0];
	szYear[1] = szStartTime[1];
	szYear[2] = szStartTime[2];
	szYear[3] = szStartTime[3];
	szYear[4] = 0;

	nYear = atoi(szYear);

	int nCount = 0;

	int nLoginType = g_userpower.logintype;
	int nUserType = g_userpower.usertype;
	int nUserID = g_userpower.userID;

	if (strcmp(szSelectUserName,"ȫ���û�") == 0)
	{
		//���û�������ʷ��־
		if (nLoginType == VM_USER_TYPE_SD_LOGIN)
		{
			if(nUserType == VM_USER_TYPE_SD_SJ_LEADER||nUserType == VM_USER_TYPE_SD_SJ_ADMIN)
			{
				sprintf_s(sql_buf, sizeof(sql_buf),"SELECT t1.user_name, t1.ip_addr, t1.time, t1.operate_type, t1.db_name, t1.notes "
					"FROM history_manager_operate_log_%04d AS t1,ct_user AS t2 WHERE t2.login_type=0 AND t1.user_name=t2.user_name AND t1.time >= '%s' AND t1.time <= '%s' ORDER BY t1.time desc",nYear,szStartTime,szStopTime);
			}
			else
			{
				sprintf_s(sql_buf, sizeof(sql_buf),"SELECT user_name, ip_addr, time, operate_type, db_name, notes "
					"FROM history_manager_operate_log_%04d where time >= '%s' AND time <= '%s' AND user_name='%s' ORDER BY time desc",nYear,szStartTime,szStopTime,g_userpower.username);
			}
		}
		else if (nLoginType == VM_USER_TYPE_SJ_LOGIN)
		{
			if(nUserType == VM_USER_TYPE_SD_SJ_LEADER||nUserType == VM_USER_TYPE_SD_SJ_ADMIN)
			{
				sprintf_s(sql_buf, sizeof(sql_buf),"SELECT t1.user_name, t1.ip_addr, t1.time, t1.operate_type, t1.db_name, t1.notes "
					"FROM history_manager_operate_log_%04d AS t1,ct_user AS t2 WHERE t2.login_type=1 AND t1.user_name=t2.user_name AND t1.time >= '%s' AND t1.time <= '%s' ORDER BY t1.time desc",nYear,szStartTime,szStopTime);
			}
			else
			{
				sprintf_s(sql_buf, sizeof(sql_buf),"SELECT user_name, ip_addr, time, operate_type, db_name, notes "
					"FROM history_manager_operate_log_%04d where time >= '%s' AND time <= '%s' AND user_name='%s' ORDER BY time desc",nYear,szStartTime,szStopTime,g_userpower.username);
			}
		}
		else if (nLoginType == VM_USER_TYPE_ADMIN_LOGIN)
		{
			sprintf_s(sql_buf, sizeof(sql_buf),"SELECT t1.user_name, t1.ip_addr, t1.time, t1.operate_type, t1.db_name, t1.notes "
				"FROM history_manager_operate_log_%04d AS t1,ct_user AS t2 WHERE t1.user_name=t2.user_name AND t1.time >= '%s' AND t1.time <= '%s' ORDER BY t1.time desc",nYear,szStartTime,szStopTime);
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		//���û�������ʷ��־
		sprintf_s(sql_buf, sizeof(sql_buf),"SELECT user_name, ip_addr, time, operate_type, db_name, notes "
			"FROM history_manager_operate_log_%04d where time >= '%s' AND time <= '%s' AND user_name='%s' ORDER BY time desc",nYear,szStartTime,szStopTime,szSelectUserName);
	}

	if (!mysql_query(g_mySqlData, sql_buf))
	{
		res = mysql_store_result(g_mySqlData);

		while ( row = mysql_fetch_row( res ) )
		{
			if (nCount >= 1000)
			{
				MessageBox("�û�������־����1000��,���������޷���ʾ��\r\n����С��ѯ��Χ��","�ȵ���Ƶ����");
				break;
			}

			sprintf_s(szUserName,"%s", row[0]);
			sprintf_s(szIpAddress, "%s", row[1]);
			sprintf_s(szDateTime, "%s", row[2]);
			nOperateType = atoi(row[3]);
			sprintf_s(szDbTableName,"%s",row[4]);
			sprintf_s(szNotes,"%s",row[5]);

			switch (nOperateType)
			{
			case 1:
				{
					sprintf_s(szOperateType,"%s","���");
				}
				break;

			case 2:
				{
					sprintf_s(szOperateType,"%s","�޸�");
				}
				break;

			case 3:
				{
					sprintf_s(szOperateType,"%s","ɾ��");
				}
				break;
				
			default:
				{
					sprintf_s(szOperateType,"%s","δ֪");
				}
				break;
			}

			m_ListCtrl_UserLog.InsertItem(nCount,szUserName);
			m_ListCtrl_UserLog.SetItemText(nCount,1,szIpAddress);
			m_ListCtrl_UserLog.SetItemText(nCount,2,szDateTime);
			m_ListCtrl_UserLog.SetItemText(nCount,3,szOperateType);
			m_ListCtrl_UserLog.SetItemText(nCount,4,szDbTableName);
			m_ListCtrl_UserLog.SetItemText(nCount,5,szNotes);

			m_ListCtrl_UserLog.SetRowColor(nCount,BKColor);
			m_ListCtrl_UserLog.SetRowTextColor(nCount,TextColor);

			nCount++;
		}
		mysql_free_result( res ) ;
	}

	if (m_ListCtrl_UserLog.GetItemCount() == 0)
	{
		m_ListCtrl_UserLog.InsertItem(nCount,"��");
		m_ListCtrl_UserLog.SetItemText(nCount,1,"��");
		m_ListCtrl_UserLog.SetItemText(nCount,2,"��");
		m_ListCtrl_UserLog.SetItemText(nCount,3,"��");
		m_ListCtrl_UserLog.SetItemText(nCount,4,"��");
		m_ListCtrl_UserLog.SetItemText(nCount,5,"��");
	}

	return TRUE;
}

BOOL CDlgHistoryLogUser::SearchAndSetHistoryListInfo2(char *szStartTime,char *szStopTime,char *szSelectUserName)
{
	if (szStartTime == NULL||szStopTime == NULL)
		return FALSE;

	InitControlList2();

	char sql_buf[512] = {0};
	bool result=false;

	char szYear[8] = {0};
	int nYear = 2013;

	MYSQL_RES * res = NULL ;
	MYSQL_ROW	row ;

	char szUserName[256] = {0};
	char szIpAddress[64] = {0};
	char szDateTime[64] = {0};
	char szOperateType[64] = {0};
	char szOperateResult[64] = {0};
	char szNodeName[256] = {0};
	char szStationName[256] = {0};
	char szStationNum[256] = {0};
	char szCameraName[256] = {0};
	char szCameraNum[256] = {0};
	int    nOperateType = 0;
	int    nOperateResult = 0;

	COLORREF BKColor;
	COLORREF TextColor;

	BKColor = RGB(207,235,250);
	TextColor = RGB(168,0,0);

	szYear[0] = szStartTime[0];
	szYear[1] = szStartTime[1];
	szYear[2] = szStartTime[2];
	szYear[3] = szStartTime[3];
	szYear[4] = 0;

	nYear = atoi(szYear);

	int nCount = 0;

	int nLoginType = g_userpower.logintype;
	int nUserType = g_userpower.usertype;
	int nUserID = g_userpower.userID;

	if (strcmp(szSelectUserName,"ȫ���û�") == 0)
	{
		//���û�������ʷ��־
		if (nLoginType == VM_USER_TYPE_SD_LOGIN)
		{
			if (nUserType == VM_USER_TYPE_SD_SJ_LEADER||nUserType == VM_USER_TYPE_SD_SJ_ADMIN)
			{
				sprintf_s(sql_buf, sizeof(sql_buf),"SELECT t1.user_name, t1.client_ip, t1.time, t1.operate_type, t1.operate_result, t1.node_name, t1.station_name, t1.station_code, t1.camera_name, t1.camera_code "
					"FROM ct_history_client_video_log_%04d AS t1,ct_user AS t2 where t2.login_type=0 AND t1.user_name=t2.user_name AND t1.time >= '%s' AND t1.time <= '%s' ORDER BY t1.time desc",nYear,szStartTime,szStopTime);
			}
			else
			{
				sprintf_s(sql_buf, sizeof(sql_buf),"SELECT user_name, client_ip, time, operate_type, operate_result, node_name, station_name, station_code, camera_name, camera_code "
					"FROM ct_history_client_video_log_%04d where time >= '%s' AND time <= '%s' AND user_name='%s' ORDER BY time desc",nYear,szStartTime,szStopTime,g_userpower.username);
			}
		}
		else if (nLoginType == VM_USER_TYPE_SJ_LOGIN)
		{
			if (nUserType == VM_USER_TYPE_SD_SJ_LEADER||nUserType == VM_USER_TYPE_SD_SJ_ADMIN)
			{
				sprintf_s(sql_buf, sizeof(sql_buf),"SELECT t1.user_name, t1.client_ip, t1.time, t1.operate_type, t1.operate_result, t1.node_name, t1.station_name, t1.station_code, t1.camera_name, t1.camera_code "
					"FROM ct_history_client_video_log_%04d AS t1,ct_user AS t2 where t2.login_type=1 AND t1.user_name=t2.user_name AND t1.time >= '%s' AND t1.time <= '%s' ORDER BY t1.time desc",nYear,szStartTime,szStopTime);
			}
			else
			{
				sprintf_s(sql_buf, sizeof(sql_buf),"SELECT user_name, client_ip, time, operate_type, operate_result, node_name, station_name, station_code, camera_name, camera_code "
					"FROM ct_history_client_video_log_%04d where time >= '%s' AND time <= '%s' AND user_name='%s' ORDER BY time desc",nYear,szStartTime,szStopTime,g_userpower.username);
			}
		}
		else if (nLoginType == VM_USER_TYPE_ADMIN_LOGIN)
		{
			sprintf_s(sql_buf, sizeof(sql_buf),"SELECT t1.user_name, t1.client_ip, t1.time, t1.operate_type, t1.operate_result, t1.node_name, t1.station_name, t1.station_code, t1.camera_name, t1.camera_code "
				"FROM ct_history_client_video_log_%04d AS t1,ct_user AS t2 where t1.user_name=t2.user_name AND t1.time >= '%s' AND t1.time <= '%s' ORDER BY t1.time desc",nYear,szStartTime,szStopTime);
		}
	}
	else
	{
		//���û�������ʷ��־
		sprintf_s(sql_buf, sizeof(sql_buf),"SELECT user_name, client_ip, time, operate_type, operate_result, node_name, station_name, station_code, camera_name, camera_code "
			"FROM ct_history_client_video_log_%04d where time >= '%s' AND time <= '%s' AND user_name='%s' ORDER BY time desc",nYear,szStartTime,szStopTime,szSelectUserName);
	}

	if (!mysql_query(g_mySqlData, sql_buf))
	{
		res = mysql_store_result(g_mySqlData);

		while ( row = mysql_fetch_row( res ) )
		{
			if (nCount >= 1000)
			{
				MessageBox("�û�������־����1000��,���������޷���ʾ��\r\n����С��ѯ��Χ��","�ȵ���Ƶ����");
				break;
			}

			sprintf_s(szUserName,"%s", row[0]);
			sprintf_s(szIpAddress, "%s", row[1]);
			sprintf_s(szDateTime, "%s", row[2]);
			nOperateType = atoi(row[3]);
			nOperateResult = atoi(row[4]);
			sprintf_s(szNodeName,"%s",row[5]);
			sprintf_s(szStationName,"%s",row[6]);
			sprintf_s(szStationNum,"%s",row[7]);
			sprintf_s(szCameraName,"%s",row[8]);
			sprintf_s(szCameraNum,"%s",row[9]);

			switch (nOperateType)
			{
			case WM_DEVICE_VIDEO_TALK_OPERATE_RESULT_FAIL:
				{
					sprintf_s(szOperateType,"%s","��Ƶ�쳣�ر�");
				}
				break;

			case WM_DEVICE_VIDEO_TALK_OPERATE_RESULT_SUCCESS:
				{
					sprintf_s(szOperateType,"%s","��Ƶ������");
				}
				break;

			case WM_DEVICE_VIDEO_OPERATE_RESULT_NOTAG_OFFLINE_VIDEO:
				{
					sprintf_s(szOperateType,"%s","����������ͷ��Ƶ");
				}
				break;

			case WM_DEVICE_VIDEO_OPERATE_RESULT_NOTAG_ONLINE_VIDEO:
				{
					sprintf_s(szOperateType,"%s","����Ƶ");
				}
				break;

			case WM_DEVICE_VIDEO_OPERATE_RESULT_TAG_ONLINE_VIDEO:
				{
					sprintf_s(szOperateType,"%s","�򿪱�עȱ����Ƶ");
				}
				break;

			case WM_DEVICE_VIDEO_OPERATE_RESULT_TAG_OFFLINE_VIDEO:
				{
					sprintf_s(szOperateType,"%s","�򿪱�ע����������Ƶ");
				}
				break;

			default:
				{
					sprintf_s(szOperateType,"%s","δ֪");
				}
				break;
			}

			m_ListCtrl_UserLog.InsertItem(nCount,szUserName);
			m_ListCtrl_UserLog.SetItemText(nCount,1,szIpAddress);
			m_ListCtrl_UserLog.SetItemText(nCount,2,szDateTime);
			m_ListCtrl_UserLog.SetItemText(nCount,3,szOperateType);
			m_ListCtrl_UserLog.SetItemText(nCount,4,szNodeName);
			m_ListCtrl_UserLog.SetItemText(nCount,5,szStationName);
			m_ListCtrl_UserLog.SetItemText(nCount,6,szStationNum);
			m_ListCtrl_UserLog.SetItemText(nCount,7,szCameraName);
			m_ListCtrl_UserLog.SetItemText(nCount,8,szCameraNum);

			m_ListCtrl_UserLog.SetRowColor(nCount,BKColor);
			m_ListCtrl_UserLog.SetRowTextColor(nCount,TextColor);

			nCount++;
		}

		mysql_free_result( res ) ;
	}

	if (m_ListCtrl_UserLog.GetItemCount() == 0)
	{
		m_ListCtrl_UserLog.InsertItem(nCount,"��");
		m_ListCtrl_UserLog.SetItemText(nCount,1,"��");
		m_ListCtrl_UserLog.SetItemText(nCount,2,"��");
		m_ListCtrl_UserLog.SetItemText(nCount,3,"��");
		m_ListCtrl_UserLog.SetItemText(nCount,4,"��");
		m_ListCtrl_UserLog.SetItemText(nCount,5,"��");
		m_ListCtrl_UserLog.SetItemText(nCount,6,"��");
		m_ListCtrl_UserLog.SetItemText(nCount,7,"��");
		m_ListCtrl_UserLog.SetItemText(nCount,8,"��");
	}

	return TRUE;
}
