// DlgPicFilePath.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "DlgPicFilePath.h"
#include "DirDialog.h"


// CDlgPicFilePath �Ի���

IMPLEMENT_DYNAMIC(CDlgPicFilePath, CDialog)

CDlgPicFilePath::CDlgPicFilePath(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPicFilePath::IDD, pParent)
	, m_FilePath(_T("C:\\capture"))
{

}

CDlgPicFilePath::~CDlgPicFilePath()
{
}

void CDlgPicFilePath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILEPATH, m_FilePath);
}


BEGIN_MESSAGE_MAP(CDlgPicFilePath, CDialog)
	ON_BN_CLICKED(IDC_FILE, &CDlgPicFilePath::OnBnClickedFile)
END_MESSAGE_MAP()


// CDlgPicFilePath ��Ϣ�������

void CDlgPicFilePath::OnBnClickedFile()
{
	CDirDialog   dlgDir;   

	dlgDir.m_strTitle = _T("ѡ��ץͼ�ļ�·��");   
	UpdateData(TRUE);   
	dlgDir.m_strSelDir = "C:\\";
	dlgDir.m_strWindowTitle = _T("Ŀ¼ѡ��");

	if (dlgDir.DoBrowse(this) == IDOK)
	{
		m_FilePath = dlgDir.m_strPath;
		UpdateData(FALSE);
	}

	TRACE("%s", m_FilePath);
}
