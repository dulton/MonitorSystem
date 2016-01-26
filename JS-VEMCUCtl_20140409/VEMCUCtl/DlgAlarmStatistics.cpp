// DlgAlarmStatistics.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "DlgAlarmStatistics.h"
#include "AssDBOperate.h"


// CDlgAlarmStatistics �Ի���

IMPLEMENT_DYNAMIC(CDlgAlarmStatistics, CDialog)

CDlgAlarmStatistics::CDlgAlarmStatistics(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmStatistics::IDD, pParent)
{

}

CDlgAlarmStatistics::~CDlgAlarmStatistics()
{
}

void CDlgAlarmStatistics::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ALARM_STATISTICS, m_lstAlarmStatistics);
}


BEGIN_MESSAGE_MAP(CDlgAlarmStatistics, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CDlgAlarmStatistics::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// CDlgAlarmStatistics ��Ϣ�������

BOOL CDlgAlarmStatistics::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitControl();

	InitAlarmStatisticsList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgAlarmStatistics::InitControl()
{
	DWORD dwStyle;
	dwStyle = m_lstAlarmStatistics.GetStyle();
	dwStyle = LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT ;

	m_lstAlarmStatistics.SetExtendedStyle(dwStyle);
	m_lstAlarmStatistics.SetBkColor(RGB(239,246,253));
	m_lstAlarmStatistics.SetTextBkColor(RGB(0xfe,0xFF,0xc6));

	//��ʼ���б���ֶ�
	CRect winrc;
	GetClientRect(winrc);

	int nWidth = winrc.Width();

	m_lstAlarmStatistics.DeleteAllItems();
	while(m_lstAlarmStatistics.DeleteColumn(0));

	m_lstAlarmStatistics.InsertColumn(0,"���");
	m_lstAlarmStatistics.SetColumnWidth(0,nWidth*0.3);
	m_lstAlarmStatistics.InsertColumn(1,"���վ����");
	m_lstAlarmStatistics.SetColumnWidth(1,nWidth*0.3);
	m_lstAlarmStatistics.InsertColumn(2,"�澯��������");
	m_lstAlarmStatistics.SetColumnWidth(2,nWidth*0.3);
}

void CDlgAlarmStatistics::InitAlarmStatisticsList()
{
	std::vector<ALARM_STATISTICS> vecAlarmStatistics = GetAlarmStatisticsInfo();

	InsertAlarmStatisticsToList(vecAlarmStatistics);

}

void CDlgAlarmStatistics::InsertAlarmStatisticsToList(std::vector<ALARM_STATISTICS> vecAlarmStatistics)
{
	int nIndex = 0;
	for (size_t t=0; t<vecAlarmStatistics.size(); t++)
	{
		CString strIndex = "";
		strIndex.Format("%d",nIndex);
		m_lstAlarmStatistics.InsertItem(nIndex,strIndex);
		m_lstAlarmStatistics.SetItemText(nIndex,1,vecAlarmStatistics.at(t).szStationName);
		m_lstAlarmStatistics.SetItemText(nIndex,2,IntToCString(vecAlarmStatistics.at(t).nAlarmCount));

		nIndex++;
	}
}

void CDlgAlarmStatistics::OnBnClickedButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}
