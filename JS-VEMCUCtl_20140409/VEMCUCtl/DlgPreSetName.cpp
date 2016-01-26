// DlgPreSetName.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "VEMCUCtlDlg.h"
#include "DlgPreSetName.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CDlgPreSetName �Ի���

IMPLEMENT_DYNAMIC(CDlgPreSetName, CDialog)

CDlgPreSetName::CDlgPreSetName(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreSetName::IDD, pParent)
	, m_PreSetName(_T(""))
{

}

CDlgPreSetName::~CDlgPreSetName()
{
}

void CDlgPreSetName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NEWPRESETNAME, m_PreSetName);
	DDV_MaxChars(pDX, m_PreSetName, 64);
}


BEGIN_MESSAGE_MAP(CDlgPreSetName, CDialog)
	ON_BN_CLICKED(IDC_MODIFYNAME, &CDlgPreSetName::OnBnClickedModifyName)
	ON_BN_CLICKED(IDC_DELETENAME, &CDlgPreSetName::OnBnClickedDeleteName)
END_MESSAGE_MAP()


// CDlgPreSetName ��Ϣ�������

// �޸�Ԥ��λ����
void CDlgPreSetName::OnBnClickedModifyName()
{

}

// ɾ��Ԥ��λ����
void CDlgPreSetName::OnBnClickedDeleteName()
{

}