// TiaoGzTjDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "sp_draw.h"
#include "dialog/TiaoGzTjDlg.h"


// CTiaoGzTjDlg �Ի���

IMPLEMENT_DYNAMIC(CTiaoGzTjDlg, CDialog)
CTiaoGzTjDlg::CTiaoGzTjDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTiaoGzTjDlg::IDD, pParent)
{
	memset(m_id,0,sizeof(char)*33);
}

CTiaoGzTjDlg::~CTiaoGzTjDlg()
{
}

void CTiaoGzTjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_type);
	DDX_Control(pDX, IDC_COMBO2, m_name);
}


BEGIN_MESSAGE_MAP(CTiaoGzTjDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CTiaoGzTjDlg ��Ϣ�������

BOOL CTiaoGzTjDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
      MainPath="C:\\SUNPAC\\";
	  InitData();
	  SetTypeBox();
	  SetNameBox();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣��OCX ����ҳӦ���� FALSE
}
void CTiaoGzTjDlg::InitData()
{
	InitPower();
	InitLine();
}

void CTiaoGzTjDlg::InitPower()
{
	m_PowerTdTj.RemoveAll();
	S_SGTJ powertd;
	
	CString FileName;
	FileName=MainPath+"Par\\global\\SgTjEdit.ini";
	int nCount=0;
	nCount=GetPrivateProfileInt("sys","PowerCount",0,FileName);
	for(int i=0;i<nCount;i++)
	{
		memset(&powertd,0,sizeof(S_SGTJ));
		CString section;
		section.Format("Power%d",i);
		char StrValue[256];
		memset(StrValue,0,sizeof(char)*256);
		GetPrivateProfileString(section,"Name","",StrValue,sizeof(char)*256,FileName);
		strcpy(powertd.cname,StrValue);
		memset(StrValue,0,sizeof(char)*256);
		GetPrivateProfileString(section,"Switch","",StrValue,sizeof(char)*256,FileName);
		strcpy(powertd.ename,StrValue);
		m_PowerTdTj.Add(powertd);
	}
}

void CTiaoGzTjDlg::InitLine()
{
	m_LineTdTj.RemoveAll();
	S_SGTJ linetd;
	
	CString FileName;
	FileName=MainPath+"Par\\global\\SgTjEdit.ini";
	int nCount=0;
	nCount=GetPrivateProfileInt("sys","OutLineCount",0,FileName);
	for(int i=0;i<nCount;i++)
	{
		memset(&linetd,0,sizeof(S_SGTJ));
		CString section;
		section.Format("OutLine%d",i);
		char StrValue[256];
		memset(StrValue,0,sizeof(char)*256);
		GetPrivateProfileString(section,"Name","",StrValue,sizeof(char)*256,FileName);
		strcpy(linetd.cname,StrValue);
		memset(StrValue,0,sizeof(char)*256);
		GetPrivateProfileString(section,"Switch","",StrValue,sizeof(char)*256,FileName);
		strcpy(linetd.ename,StrValue);
		m_LineTdTj.Add(linetd);
	}
}

void CTiaoGzTjDlg::SetTypeBox()
{
	m_type.ResetContent();
	if(m_Type==1)
	{
		m_type.AddString("��Դ����ͳ��");
	}
	else if(m_Type==2)
	{
		m_type.AddString("��·����ͳ��");
	}
	else
	{
		m_type.AddString("��Դ����ͳ��");
		m_type.AddString("��·����ͳ��");
	}
	m_type.SetCurSel(0);
}

void CTiaoGzTjDlg::SetNameBox()
{
	m_name.ResetContent();
	int index=-1;
	
	index=m_type.GetCurSel();
	if(index==-1)return;
	CString str;
	m_type.GetLBText(index,str);
	if(strcmp(str,"��Դ����ͳ��")==0)
	{
		int count=m_PowerTdTj.GetCount();
		S_SGTJ powertd;
		for(int i=0;i<count;i++)
		{
			memset(&powertd,0,sizeof(S_SGTJ));
			powertd=m_PowerTdTj.GetAt(i);
			m_name.AddString(powertd.cname);
		}
	}
	else if(strcmp(str,"��·����ͳ��")==0)
	{
		int count = m_LineTdTj.GetCount();
		S_SGTJ linetd;
		for(int i = 0;i<count; i++)
		{
			memset(&linetd,0,sizeof(S_SGTJ));
			linetd=m_LineTdTj.GetAt(i);
			m_name.AddString(linetd.cname);
		}
	}
	UpdateData(FALSE);
}

void CTiaoGzTjDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetNameBox();
}

void CTiaoGzTjDlg::SetType(BYTE type)
{
	m_Type=type;
}

void CTiaoGzTjDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int index=-1;
	index=m_name.GetCurSel();
	m_name.GetLBText(index,m_id);
	OnOK();
}
