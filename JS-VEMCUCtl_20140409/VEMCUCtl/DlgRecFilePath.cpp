// DlgRecFilePath.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "DlgRecFilePath.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


// CDlgRecFilePath �Ի���

IMPLEMENT_DYNAMIC(CDlgRecFilePath, CDialog)

CDlgRecFilePath::CDlgRecFilePath(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecFilePath::IDD, pParent)
{
	m_Filepath = _T("C:\\");
}

CDlgRecFilePath::~CDlgRecFilePath()
{
}

void CDlgRecFilePath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILEPATH, m_Filepath);
}


BEGIN_MESSAGE_MAP(CDlgRecFilePath, CDialog)
	ON_BN_CLICKED(IDC_FILE, OnFile)	
END_MESSAGE_MAP()


// CDlgRecFilePath ��Ϣ�������

void CDlgRecFilePath::OnFile() 
{
	CDirDialog   dlgDir;   
    
    dlgDir.m_strTitle = _T("ѡ��¼���ļ�·��");   
    UpdateData(TRUE);   
    dlgDir.m_strSelDir = "C:\\";
    dlgDir.m_strWindowTitle = _T("Ŀ¼ѡ��");
   
	if (dlgDir.DoBrowse(this) == IDOK)
	{
		m_Filepath = dlgDir.m_strPath;
		UpdateData(FALSE);
	}

	TRACE("%s", m_Filepath);
}
