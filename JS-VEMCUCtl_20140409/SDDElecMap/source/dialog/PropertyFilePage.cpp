// PropertyFilePage.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "sp_draw.h"
#include "dialog/PropertyFilePage.h"


// CPropertyFilePage �Ի���

IMPLEMENT_DYNAMIC(CPropertyFilePage, CPropertyPage)
CPropertyFilePage::CPropertyFilePage()
	: CPropertyPage(CPropertyFilePage::IDD)
	, m_filename(_T(""))
	, m_filespecification(_T(""))
{
}

CPropertyFilePage::~CPropertyFilePage()
{
}

void CPropertyFilePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listbox);
	//DDX_Control(pDX, IDC_EDIT2, m_filename);
	//DDX_Control(pDX, IDC_EDIT1, m_filespecificaton);
	DDX_Text(pDX, IDC_EDIT2, m_filename);
	DDX_Text(pDX, IDC_EDIT1, m_filespecification);
}


BEGIN_MESSAGE_MAP(CPropertyFilePage, CPropertyPage)
	ON_LBN_SELCHANGE(IDC_LIST1, OnLbnSelchangeList1)
	//ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT2, OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT1, OnEnChangeEdit1)
END_MESSAGE_MAP()

void CPropertyFilePage::FillListBox(void)
{
	
	 CFileFind  filedir;
	 CString file;//=theApp.GetDirectory();
	 CString filename;
     file="C:\\sunpac\\par\\global\\FileLink\\*.*";
	 //file.Format("%s%s\\*.%s",theApp.GetDirectory(),m_path,m_ext);

	 m_listbox.ResetContent();
	 if (filedir.FindFile(file))
	 {
	   while (filedir.FindNextFile())
		{
			 filename=filedir.GetFileName();
			 m_listbox.AddString(filename);
		}
	  //filename=filedir.GetFileTitle();
	  filename =filedir.GetFileName ();
	  m_listbox.AddString(filename);
		filedir.Close();
	}
}

// CPropertyFilePage ��Ϣ�������

void CPropertyFilePage::OnLbnSelchangeList1()
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

void CPropertyFilePage::Getfile(char* filename,char* ename)
{
	ASSERT(filename!=NULL);
	ASSERT(ename!=NULL);
	if (filename==NULL || ename==NULL) return;
	filename[0]=0x00;
	ename[0]=0x00;
	if (m_filename.IsEmpty()) return;
	strcpy(filename,m_filename);
	strcpy (ename ,m_filespecification );

}

BOOL CPropertyFilePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
  FillListBox ();
   UpdateData (FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣��OCX ����ҳӦ���� FALSE
}



void CPropertyFilePage::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	UpdateData (TRUE);

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
void CPropertyFilePage::Setfile(char *filename,char*ename)
{
   
	ASSERT(filename !=NULL);
	ASSERT(ename!=NULL);
	 if(filename ==NULL ||ename ==NULL)
		 return ;
  //if(m_filename =="" || m_filespecification =="")
  //  return ;
  m_filename =filename;
  m_filespecification =ename;
 //  if(m_filename =="" || m_filespecification =="")
 //	  return ;

   //UpdateData(FALSE);


}





void CPropertyFilePage::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
    UpdateData (TRUE);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
