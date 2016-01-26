// PowerNameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "sp_draw.h"
#include "dialog/PowerNameDlg.h"
#include "dialog/TiaoGzTjDlg.h"

// CPowerNameDlg �Ի���

IMPLEMENT_DYNAMIC(CPowerNameDlg, CDialog)
CPowerNameDlg::CPowerNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPowerNameDlg::IDD, pParent)
	, m_Name(_T(""))
	, m_strID(_T(""))
{
}

CPowerNameDlg::~CPowerNameDlg()
{
}

void CPowerNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	DDX_Text(pDX, IDC_EDIT2, m_strID);
}


BEGIN_MESSAGE_MAP(CPowerNameDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CPowerNameDlg ��Ϣ�������
void CPowerNameDlg::SetName(char *name,char *id)
{
	m_Name=name;
	m_strID=id;
}
void CPowerNameDlg::GetName(char *name,char *id)
{
	//UpdateData(true);
	strcpy(name,m_Name);
	strcpy(id,m_strID);
}

void CPowerNameDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CTiaoGzTjDlg dlg;
	dlg.SetType(2);
	if(dlg.DoModal()==IDOK)
	{
		m_strID=dlg.m_id;
		UpdateData(FALSE);
	}
	//
}

BOOL CPowerNameDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
  //  SetWindowText("ttt");
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣��OCX ����ҳӦ���� FALSE
}
