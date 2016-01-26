// DlgAddDeviceLedger.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LinkageSetting.h"
#include "DBExcute.h"
#include "PtuDlg.h"


// CDlgAddDeviceLedger �Ի���

IMPLEMENT_DYNAMIC(CDlgAddDeviceLedger, CDialog)

CDlgAddDeviceLedger::CDlgAddDeviceLedger(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddDeviceLedger::IDD, pParent)
{
	m_nDeviceId = 0;
	memset(&m_tDeviceLedger, 0, sizeof(_T_ASS_DEVICE_LEDGER_));
}

CDlgAddDeviceLedger::~CDlgAddDeviceLedger()
{
}

void CDlgAddDeviceLedger::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DEV_FACTORY_NAME, m_comboDevFactory);
	DDX_Control(pDX, IDC_EDIT_DEV_NAME, m_edtDevName);
	DDX_Control(pDX, IDC_EDIT_DEV_IP, m_edtDevIp);
	DDX_Control(pDX, IDC_EDIT_DEV_PORT, m_edtDevPort);
	DDX_Control(pDX, IDC_EDIT_DEV_USER, m_edtDevUser);
	DDX_Control(pDX, IDC_EDIT_DEV_PASSWORD, m_edtDevPassword);
	DDX_Control(pDX, IDC_EDIT_DEV_PROTOCOL, m_edtDevProcotol);
	DDX_Control(pDX, IDC_EDIT_DEV_TYPE, m_edtDevType);
	DDX_Control(pDX, IDC_EDIT_DEV_HARDDISK, m_edtDevHarddish);
	DDX_Control(pDX, IDC_EDIT_DEV_AV_NUM, m_edtDevAVNum);
	DDX_Control(pDX, IDC_EDIT_DV_NUM, m_edtDVNum);
}


BEGIN_MESSAGE_MAP(CDlgAddDeviceLedger, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgAddDeviceLedger::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgAddDeviceLedger::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgAddDeviceLedger ��Ϣ�������

BOOL CDlgAddDeviceLedger::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgAddDeviceLedger::SetDeviceLedger(_T_ASS_DEVICE_LEDGER_* pDeviceLedger)
{
	memcpy(&m_tDeviceLedger, pDeviceLedger, sizeof(_T_ASS_DEVICE_LEDGER_));
}

void CDlgAddDeviceLedger::InitControlData()
{
	CString device_name = "";
	CString device_manufacturer = "";
	CString device_ip = "";
	CString device_port = "";
	CString login_username = "";
	CString login_password = "";
	CString protocol_type = "";
	CString device_type = "";
	CString harddisk_capacity = "";
	CString analog_video_num = "";
	CString net_video_num = "";

	m_edtDevName.SetWindowText(device_name);
	m_comboDevFactory.SetWindowText(device_manufacturer);
	m_edtDevIp.SetWindowText(device_ip);
	m_edtDevPort.SetWindowText(device_port);
	m_edtDevUser.SetWindowText(login_username);
	m_edtDevPassword.SetWindowText(login_password);
	m_edtDevProcotol.SetWindowText(protocol_type);
	m_edtDevType.SetWindowText(device_type);
	m_edtDevHarddish.SetWindowText(harddisk_capacity);
	m_edtDevAVNum.SetWindowText(analog_video_num);
	m_edtDVNum.SetWindowText(net_video_num);

	InitComBox();

	m_edtDevName.EnableWindow(TRUE);

	m_nDeviceId = 0;
}

void CDlgAddDeviceLedger::InitControl()
{
	CString device_name = "";
	CString device_manufacturer = "";
	CString device_ip = "";
	CString device_port = "";
	CString login_username = "";
	CString login_password = "";
	CString protocol_type = "";
	CString device_type = "";
	CString harddisk_capacity = "";
	CString analog_video_num = "";
	CString net_video_num = "";

	device_name.Format("%s",m_tDeviceLedger.device_name);
	device_manufacturer.Format("%s",m_tDeviceLedger.device_manufacturer);
	device_ip.Format("%s",m_tDeviceLedger.device_ip);
	device_port.Format("%d",m_tDeviceLedger.device_port);
	login_username.Format("%s",m_tDeviceLedger.login_username);
	login_password.Format("%s",m_tDeviceLedger.login_password);
	protocol_type.Format("%s",m_tDeviceLedger.protocol_type);
	device_type.Format("%s",m_tDeviceLedger.device_type);
	harddisk_capacity.Format("%s",m_tDeviceLedger.harddisk_capacity);
	analog_video_num.Format("%d",m_tDeviceLedger.analog_video_num);
	net_video_num.Format("%d",m_tDeviceLedger.net_video_num);

	m_edtDevName.SetWindowText(device_name);
	m_comboDevFactory.SetWindowText(device_manufacturer);
	m_edtDevIp.SetWindowText(device_ip);
	m_edtDevPort.SetWindowText(device_port);
	m_edtDevUser.SetWindowText(login_username);
	m_edtDevPassword.SetWindowText(login_password);
	m_edtDevProcotol.SetWindowText(protocol_type);
	m_edtDevType.SetWindowText(device_type);
	m_edtDevHarddish.SetWindowText(harddisk_capacity);
	m_edtDevAVNum.SetWindowText(analog_video_num);
	m_edtDVNum.SetWindowText(net_video_num);

	m_edtDevName.EnableWindow(FALSE);

	m_nDeviceId = m_tDeviceLedger.id;
}

void CDlgAddDeviceLedger::InitComBox()
{
	m_comboDevFactory.AddString("����");
	m_comboDevFactory.AddString("��");
	m_comboDevFactory.AddString("����");
	m_comboDevFactory.AddString("����");
	m_comboDevFactory.AddString("����");
	m_comboDevFactory.AddString("Mobo");
	m_comboDevFactory.AddString("AXIS");
	m_comboDevFactory.SetCurSel(0);
}

int CDlgAddDeviceLedger::SaveDeviceLedger()
{
	CString device_name = "";
	CString device_manufacturer = "";
	CString device_ip = "";
	CString device_port = "";
	CString login_username = "";
	CString login_password = "";
	CString protocol_type = "";
	CString device_type = "";
	CString harddisk_capacity = "";
	CString analog_video_num = "";
	CString net_video_num = "";

	m_edtDevName.GetWindowText(device_name);
	m_comboDevFactory.GetWindowText(device_manufacturer);
	m_edtDevIp.GetWindowText(device_ip);
	m_edtDevPort.GetWindowText(device_port);
	m_edtDevUser.GetWindowText(login_username);
	m_edtDevPassword.GetWindowText(login_password);
	m_edtDevProcotol.GetWindowText(protocol_type);
	m_edtDevType.GetWindowText(device_type);
	m_edtDevHarddish.GetWindowText(harddisk_capacity);
	m_edtDevAVNum.GetWindowText(analog_video_num);
	m_edtDVNum.GetWindowText(net_video_num);

	if (device_name == ""||
		device_manufacturer == ""||
		device_ip == ""||
		device_port == ""||
		login_username == ""||
		login_password == ""||
		protocol_type == "")
	{
		MessageBox("��������Ϊ��!");
		return -1;
	}

	//���
	char sql_buf[1024]={0x0};
	MYSQL_RES	* res;
	int rnum = 0;
	//�ж��Ƿ��Ѿ���ӹ����豸
	sprintf_s(sql_buf,"select * from ass_device_ledger where station_id='%d' and device_name='%s'",m_nStationId,device_name);
	if (!mysql_query(g_LinkageSettingMysql, sql_buf))
	{
		res = mysql_store_result(g_LinkageSettingMysql);
		rnum = mysql_num_rows(res);
		mysql_free_result( res ) ;
	}
	//��ӹ�
	int ret;
	if (rnum > 0)
	{
		MessageBox("�ñ��վ�Ѿ���ӹ����豸!");
		return -1;
	}
	//û��ӹ�
	else
	{
		sprintf_s(sql_buf,"INSERT INTO ass_device_ledger (station_id,device_name,device_manufacturer,device_ip,device_port,login_username, "
			" login_password,protocol_type,device_type,harddisk_capacity,analog_video_num,net_video_num) " 
			" VALUES (%d,'%s','%s','%s','%d','%s','%s','%s','%s','%s','%d','%d')",
			m_nStationId,device_name,device_manufacturer,device_ip,atoi(device_port),login_username,login_password,protocol_type,device_type,
			harddisk_capacity,atoi(analog_video_num),atoi(net_video_num));
		ret = mysql_query(g_LinkageSettingMysql, sql_buf);
	}
	if (!ret)
	{
		MessageBox("�豸��ӳɹ�","����ϵͳ");

		//д������¼
		CString strText = "";
		strText.Format("����豸�ɹ���%s", device_name);
		WriteAssUserOperateLogPre(strText.GetBuffer());
	}
	else
	{
		MessageBox("�豸���ʧ��,�������ݿ�����","����ϵͳ");

		//д������¼
		CString strText = "";
		strText.Format("����豸ʧ�ܣ�%s", device_name);
		WriteAssUserOperateLogPre(strText.GetBuffer());

		return -1;
	}
	return 0;
}

int CDlgAddDeviceLedger::EditDeviceLedger(int nDevId)
{
	CString device_name = "";
	CString device_manufacturer = "";
	CString device_ip = "";
	CString device_port = "";
	CString login_username = "";
	CString login_password = "";
	CString protocol_type = "";
	CString device_type = "";
	CString harddisk_capacity = "";
	CString analog_video_num = "";
	CString net_video_num = "";

	m_edtDevName.GetWindowText(device_name);
	m_comboDevFactory.GetWindowText(device_manufacturer);
	m_edtDevIp.GetWindowText(device_ip);
	m_edtDevPort.GetWindowText(device_port);
	m_edtDevUser.GetWindowText(login_username);
	m_edtDevPassword.GetWindowText(login_password);
	m_edtDevProcotol.GetWindowText(protocol_type);
	m_edtDevType.GetWindowText(device_type);
	m_edtDevHarddish.GetWindowText(harddisk_capacity);
	m_edtDevAVNum.GetWindowText(analog_video_num);
	m_edtDVNum.GetWindowText(net_video_num);

	if (device_name == ""||
		device_manufacturer == ""||
		device_ip == ""||
		device_port == ""||
		login_username == ""||
		login_password == ""||
		protocol_type == "")
	{
		MessageBox("��������Ϊ��!");
		return -1;
	}

	//����
	char sql_buf[1024]={0x0};
	MYSQL_RES	* res;
	int ret;
	sprintf_s(sql_buf,"UPDATE ass_device_ledger set device_name='%s',device_ip='%s',device_port='%d',device_manufacturer='%s', "
		" device_type='%s',login_username='%s',login_password='%s',protocol_type='%s',harddisk_capacity='%s', "
		" analog_video_num='%d',net_video_num='%d' where station_id='%d' and id=%d",
		device_name,device_ip,atoi(device_port),device_manufacturer,device_type,login_username,login_password,protocol_type,
		harddisk_capacity,atoi(analog_video_num),atoi(net_video_num),m_nStationId,nDevId);
	ret = mysql_query(g_LinkageSettingMysql, sql_buf);
	if (!ret)
	{
		MessageBox("�豸���³ɹ�","����ϵͳ");

		//д������¼
		CString strText = "";
		strText.Format("�޸��豸�ɹ���%s", device_name);
		WriteAssUserOperateLogPre(strText.GetBuffer());
	}
	else
	{
		MessageBox("�豸����ʧ��,�������ݿ�����","����ϵͳ");

		//д������¼
		CString strText = "";
		strText.Format("�޸��豸ʧ�ܣ�%s", device_name);
		WriteAssUserOperateLogPre(strText.GetBuffer());

		return -1;
	}
	return 0;
}

void CDlgAddDeviceLedger::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = 0;
	//���
	if (m_nDeviceId == 0)
	{
		ret = SaveDeviceLedger();
	}
	//�޸�
	else
	{
		ret = EditDeviceLedger(m_nDeviceId);
	}

	if (ret != 0)
	{
		return;
	}

	//�򸸴��������ɵ���Ϣ
	g_pMainDlg->m_pDeviceLedgerDlg->PostMessage(WM_ADD_DEVICE_LEDGER_COMPLETED, 0, 0);
	OnOK();
}

void CDlgAddDeviceLedger::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
