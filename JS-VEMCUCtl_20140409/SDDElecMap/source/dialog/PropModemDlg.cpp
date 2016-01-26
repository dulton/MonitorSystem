// PropModemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "sp_draw.h"
#include "dialog/PropModemDlg.h"


// CPropModemDlg �Ի���

IMPLEMENT_DYNAMIC(CPropModemDlg, CPropertyPage)
CPropModemDlg::CPropModemDlg()
	: CPropertyPage(CPropModemDlg::IDD)
	, m_adptID(0)
	, m_strPhone(_T(""))
	, m_dwtime(0)
	, m_strDescript(_T(""))
{
}

CPropModemDlg::~CPropModemDlg()
{
}

void CPropModemDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_adptID);
	DDX_Text(pDX, IDC_EDIT2, m_strPhone);
	DDV_MaxChars(pDX, m_strPhone, 12);
	DDX_Text(pDX, IDC_EDIT3, m_dwtime);
	DDX_Text(pDX, IDC_EDIT4, m_strDescript);
}


BEGIN_MESSAGE_MAP(CPropModemDlg, CPropertyPage)
END_MESSAGE_MAP()

void CPropModemDlg::SetParam(char* descript ,DWORD adptid ,char *phone ,DWORD time)
{            
	m_adptID	= adptid ;
	m_dwtime	= time ;
	m_strPhone = phone ;	
	m_strDescript	= descript ;
	
}
void CPropModemDlg::GetParam(char* descript ,DWORD &adptid ,char *phone ,DWORD &time)
{
	adptid	=   m_adptID ;	
	time  	=   m_dwtime ;	
	strcpy(phone ,m_strPhone) ;	
	strcpy(descript ,m_strDescript) ;
}
// CPropModemDlg ��Ϣ�������

BOOL CPropModemDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ�� 
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣��OCX ����ҳӦ���� FALSE
}
