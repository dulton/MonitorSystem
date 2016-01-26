// SuperviseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "sp_draw.h"
#include "dialog/SuperviseDlg.h"


// CSuperviseDlg �Ի���

IMPLEMENT_DYNAMIC(CSuperviseDlg, CPropertyPage)
CSuperviseDlg::CSuperviseDlg()
	: CPropertyPage(CSuperviseDlg::IDD)
	, m_strEname(_T(""))
	, m_strDescript(_T(""))
{
}

CSuperviseDlg::~CSuperviseDlg()
{
}

void CSuperviseDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strEname);
	DDX_Text(pDX, IDC_EDIT2, m_strDescript);
}


BEGIN_MESSAGE_MAP(CSuperviseDlg, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CSuperviseDlg ��Ϣ�������

void CSuperviseDlg::SetProp(CString ename, CString des, bool isAudio)
{
	m_strEname = ename;
	m_strDescript = des;
}

void CSuperviseDlg::GetProp(char* ename, char* des, bool &isAudio)
{
	strcpy(ename, m_strEname);
	strcpy(des, m_strDescript);
}

void CSuperviseDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char myename[17],mycname[33];
 	HINSTANCE hmydll;
 	hmydll=LoadLibrary("c:\\sunpac\\dll\\Finddot.dll");
 	if (hmydll==NULL)
	{
 		AfxMessageBox("Finddot.dl����ʧ�ܣ�");
 		return;
 	}
 	ShowFindDotDlg * pf;
 	pf = (ShowFindDotDlg *)::GetProcAddress(hmydll,"ShowFindDotDlg");
 	if (pf==NULL)
	{
 		AfxMessageBox("���뺯��ShowFindDotDlg ʧ�ܣ�");
 		FreeLibrary(hmydll);
 		hmydll=NULL;
 		return;
 	}

 	if ((*pf)(0,myename,mycname))
 	{
 		UpdateData(true);
 		m_strEname = myename;
 		UpdateData(false);
 	}
 
 	FreeLibrary(hmydll);

}
