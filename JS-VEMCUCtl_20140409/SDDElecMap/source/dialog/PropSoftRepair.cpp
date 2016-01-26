// PropSoftRepair.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "sp_draw.h"
#include "dialog/PropSoftRepair.h"


// CPropSoftRepair �Ի���

IMPLEMENT_DYNAMIC(CPropSoftRepair, CPropertyPage)
CPropSoftRepair::CPropSoftRepair()
	: CPropertyPage(CPropSoftRepair::IDD)
	, m_strDes(_T(""))
	, m_strEname(_T(""))
{
}

CPropSoftRepair::~CPropSoftRepair()
{
}

void CPropSoftRepair::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_strDes);
	DDX_Text(pDX, IDC_EDIT1, m_strEname);
}


BEGIN_MESSAGE_MAP(CPropSoftRepair, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CPropSoftRepair ��Ϣ�������

void CPropSoftRepair::OnBnClickedButton1()//����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true) ;
	char cEname[17] ;
	char cDescribe[33] ;

	HINSTANCE hInstance = LoadLibrary("C:\\SUNPAC\\DLL\\FindDot.dll") ;
	if(!hInstance)
	{
		AfxMessageBox("dll����ʧ��") ;
		return ;
	}
	pShowFindDot=(ShowFindDotDlg*)GetProcAddress(hInstance,"ShowFindDotDlg");

	
	if (pShowFindDot==NULL)
	{
		AfxMessageBox("���ú���ʧ��");
		FreeLibrary(hInstance);
		hInstance=NULL;
		return;
	}

	if ((*pShowFindDot)(2,cEname,cDescribe))
	{
		m_strEname = cEname ;
	}

	FreeLibrary(hInstance);
	UpdateData(false) ;

}

void CPropSoftRepair::GetParam(char* ename ,char* des)
{
	strcpy(ename ,m_strEname) ;
	strcpy(des ,m_strDes) ;
}

void CPropSoftRepair::SetParam(char* ename ,char* des)
{
	m_strEname = ename ;
	m_strDes = des ;
}
