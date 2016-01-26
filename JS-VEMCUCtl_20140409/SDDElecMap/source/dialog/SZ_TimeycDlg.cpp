// SZ_TimeycDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "sp_draw.h"
#include "dialog/SZ_TimeycDlg.h"


// CSZ_TimeycDlg �Ի���

IMPLEMENT_DYNAMIC(CSZ_TimeycDlg, CDialog)
CSZ_TimeycDlg::CSZ_TimeycDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSZ_TimeycDlg::IDD, pParent)
	, m_info(_T(""))
{
	strcpy(m_cinfo,"");
}

CSZ_TimeycDlg::~CSZ_TimeycDlg()
{
}

void CSZ_TimeycDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SZ_INFO, m_info);
}


BEGIN_MESSAGE_MAP(CSZ_TimeycDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CSZ_TimeycDlg ��Ϣ�������

BOOL CSZ_TimeycDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_info=m_cinfo;
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣��OCX ����ҳӦ���� FALSE
}

void CSZ_TimeycDlg::SetData(char* newVal)
{
	memcpy(m_cinfo,newVal,33);
	m_cinfo[32]=0;
}

void CSZ_TimeycDlg::GetData(char* retVal)
{
	strcpy(retVal,m_cinfo);
}

void CSZ_TimeycDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	strncpy(m_cinfo,m_info,32);
	m_cinfo[32]=0;
	OnOK();
}
