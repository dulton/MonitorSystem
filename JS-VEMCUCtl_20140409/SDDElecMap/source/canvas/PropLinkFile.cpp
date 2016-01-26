// PropLinkFile.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "sp_draw.h"
#include "canvas/PropLinkFile.h"

// CPropLinkFile �Ի���

IMPLEMENT_DYNAMIC(CPropLinkFile, CPropertyPage)
CPropLinkFile::CPropLinkFile()
	: CPropertyPage(CPropLinkFile::IDD)
	, m_filename(_T(""))
	, m_path(_T(""))
	, m_ext(_T(""))
{

}

CPropLinkFile::~CPropLinkFile()
{

}

void CPropLinkFile::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_filename);
	DDV_MaxChars(pDX, m_filename, 32);
	DDX_Control(pDX, IDC_LIST1, m_listbox);
	DDX_Control(pDX, IDC_BUTTON1, m_Btn_Advance);
}


BEGIN_MESSAGE_MAP(CPropLinkFile, CPropertyPage)
	ON_LBN_SELCHANGE(IDC_LIST1, OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CPropLinkFile ��Ϣ�������

BOOL CPropLinkFile::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	FillListBox();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣��OCX ����ҳӦ���� FALSE
}

void CPropLinkFile::FillListBox(void)
{
	 CFileFind  filedir;
	 CString file="";//theApp.GetDirectory();
	 CString filename;

	 char chpath[MAX_PATH];  
	 GetModuleFileName(NULL,(LPSTR)chpath,sizeof(chpath));
	 file.Format("%s%s\\*.%s",chpath,m_path,m_ext);//theApp.GetDirectory()

	 m_listbox.ResetContent();
	 if (filedir.FindFile(file))
	 {
	   while (filedir.FindNextFile())
		{
			 filename=filedir.GetFileTitle();
			 m_listbox.AddString(filename);
		}
	  filename=filedir.GetFileTitle();
	  m_listbox.AddString(filename);
		filedir.Close();
	}

}

void CPropLinkFile::Setfile(LPCSTR path, LPCSTR filename, LPCSTR ext)
{
	if (strlen(path)>0) 
	  m_path=path;
	if (strlen(filename)>0)
		m_filename=filename;
	if (strlen(ext)>0)
		m_ext=ext;
}

void CPropLinkFile::Getfile(char* filename)
{
	ASSERT(filename!=NULL);
	if (filename==NULL) return;
	filename[0]=0x00;
	if (m_filename.IsEmpty()) return;
	strcpy(filename,m_filename);
}

void CPropLinkFile::OnLbnSelchangeList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int pos=m_listbox.GetCurSel();
	CString filename;
	if (pos>=0)
	{
		m_listbox.GetText(pos,filename);
		m_filename=filename;
	}
	UpdateData(FALSE);
}

void CPropLinkFile::OnBnClickedButton1()
{
	CString str;
	UpdateData(TRUE);
	char chpath[MAX_PATH];  
	GetModuleFileName(NULL,(LPSTR)chpath,sizeof(chpath));
	str.Format("%s%s\\%s.%s",chpath,m_path,m_filename,m_ext);//theApp.GetDirectory()
	ShellExecute(NULL,"open",str,NULL,NULL,SW_SHOWNORMAL);
}
