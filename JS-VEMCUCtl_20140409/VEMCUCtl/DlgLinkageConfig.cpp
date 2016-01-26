// DlgLinkageConfig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "DlgLinkageConfig.h"
#include "AssDBOperate.h"


// CDlgLinkageConfig �Ի���

IMPLEMENT_DYNAMIC(CDlgLinkageConfig, CDialog)

CDlgLinkageConfig::CDlgLinkageConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLinkageConfig::IDD, pParent)
{

}

CDlgLinkageConfig::~CDlgLinkageConfig()
{
}

void CDlgLinkageConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LINKAGE_SHOW_TYPE, m_comboLinkageShowType);
	DDX_Control(pDX, IDC_COMBO_SHOW_VIDEO, m_comboShowVideo);
	DDX_Control(pDX, IDC_COMBO_CHANGE_TIME, m_comboChangeTime);
	DDX_Control(pDX, IDC_CHECK_SECURITY, m_checkSecurity);
	DDX_Control(pDX, IDC_CHECK_FIRE, m_checkFire);
	DDX_Control(pDX, IDC_CHECK_DOOR_ALARM, m_checkDoorAlarm);
	DDX_Control(pDX, IDC_CHECK_DOOR_ACTION, m_checkDoorAction);
}


BEGIN_MESSAGE_MAP(CDlgLinkageConfig, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgLinkageConfig::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgLinkageConfig ��Ϣ�������

void CDlgLinkageConfig::OnBnClickedOk()
{
	//��ȡ�ؼ���Ϣ
	T_ASS_LINKAGE_CONFIG tAssLinkageConfig;
	SetControlInfoToLinkageConfig(&tAssLinkageConfig);

	//���
	InsertLinkageConfigInfoToDB(&tAssLinkageConfig);

	OnOK();
}

void CDlgLinkageConfig::SetControlInfoToLinkageConfig(T_ASS_LINKAGE_CONFIG* pAssLinkageConfig)
{
	//��ȡ�ؼ���ֵ
	CString strShowType = "";
	m_comboLinkageShowType.GetLBText(m_comboLinkageShowType.GetCurSel(),strShowType);

	CString strShowVideo = "";
	m_comboShowVideo.GetLBText(m_comboShowVideo.GetCurSel(),strShowVideo);

	CString strChangeTime = "";
	m_comboChangeTime.GetLBText(m_comboChangeTime.GetCurSel(),strChangeTime);

	int nSecurity = m_checkSecurity.GetCheck();
	int nFire = m_checkFire.GetCheck();
	int nDoorAlarm = m_checkDoorAlarm.GetCheck();
	int nDoorAction = m_checkDoorAction.GetCheck();

	pAssLinkageConfig->nUserId = g_userpower.userID;
	pAssLinkageConfig->nShowType = GetShowTypeByShowTypeText(strShowType.GetBuffer());
	pAssLinkageConfig->nShowVideo = GetShowVideoByShowVideoTetxt(strShowVideo.GetBuffer());
	pAssLinkageConfig->nChangeTime = atoi(strChangeTime);
	pAssLinkageConfig->nSecurity = nSecurity;
	pAssLinkageConfig->nFire = nFire;
	pAssLinkageConfig->nDoorAlarm = nDoorAlarm;
	pAssLinkageConfig->nDoorAction = nDoorAction;
}

int CDlgLinkageConfig::GetShowVideoByShowVideoTetxt(char *pShowVideoText)
{
	if (strcmp(pShowVideoText,"��") == 0)
	{
		return 0;
	}
	if (strcmp(pShowVideoText,"��") == 0)
	{
		return 1;
	}
}

int CDlgLinkageConfig::GetShowTypeByShowTypeText(char *pShowTypeText)
{
	if (strcmp(pShowTypeText,"�໭��չʾ") == 0)
	{
		return 0;
	}
	if (strcmp(pShowTypeText,"���ӵ�ͼչʾ") == 0)
	{
		return 1;
	}
}

BOOL CDlgLinkageConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	//��ʼ��չʾ��ʽ
	InitComboShowType();

	//��ʼ���Ƿ���ʾ��Ƶ
	InitComboShowVideo();

	//��ʼ���л�ʱ��
	InitComboChangeTime();

	//��ʼ������Դ��Ĭ��Ϊȫ����ѡ
	InitAllCheckBox();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgLinkageConfig::InitComboShowType()
{
	m_comboLinkageShowType.ResetContent();
	m_comboLinkageShowType.AddString("�໭��չʾ");
	m_comboLinkageShowType.AddString("���ӵ�ͼչʾ");
	m_comboLinkageShowType.SetCurSel(0);
}

void CDlgLinkageConfig::InitComboShowVideo()
{
	m_comboShowVideo.ResetContent();
	m_comboShowVideo.AddString("��");
	m_comboShowVideo.AddString("��");
	m_comboShowVideo.SetCurSel(0);
}

void CDlgLinkageConfig::InitComboChangeTime()
{
	m_comboChangeTime.ResetContent();
	for (int i=5;i<=60;i+=5)
	{
		CString strText = "";
		strText.Format("%d",i);
		m_comboChangeTime.AddString(strText);
	}
	m_comboChangeTime.SetCurSel(0);
}

void CDlgLinkageConfig::InitAllCheckBox()
{
	m_checkSecurity.SetCheck(TRUE);
	m_checkFire.SetCheck(TRUE);
	m_checkDoorAlarm.SetCheck(TRUE);
	m_checkDoorAction.SetCheck(TRUE);
}
