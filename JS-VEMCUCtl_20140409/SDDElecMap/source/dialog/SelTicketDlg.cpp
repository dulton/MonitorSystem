// SelTicketDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "sp_draw.h"
#include "dialog/SelTicketDlg.h"
#include "dialog/CreateTicketDlg.h"

// CSelTicketDlg �Ի���

IMPLEMENT_DYNAMIC(CSelTicketDlg, CDialog)
CSelTicketDlg::CSelTicketDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelTicketDlg::IDD, pParent)
{
	strcpy(m_TicketName,"");
}

CSelTicketDlg::~CSelTicketDlg()
{
}

void CSelTicketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NAMECOMBO, m_TicketNameBox);
}


BEGIN_MESSAGE_MAP(CSelTicketDlg, CDialog)
	ON_BN_CLICKED(IDC_NEWBUTTON, OnBnClickedCreatebutton)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CSelTicketDlg ��Ϣ�������

void CSelTicketDlg::SetTicketName(char* TicketName)
{
	ASSERT(strlen(TicketName)<33);
	strcpy(m_TicketName,TicketName);
}

char* CSelTicketDlg::GetTicketName(void)
{
	return m_TicketName;
}

BOOL CSelTicketDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	char chpath[MAX_PATH]; 
	GetModuleFileName(NULL,(LPSTR)chpath,sizeof(chpath));
	CString path;//=theApp.GetDirectory();
	path.Format("%s",chpath);
	path=path+"global\\Ticket\\OT\\*.txt";
	WIN32_FIND_DATA FileData; 
	HANDLE hSearch;
	BOOL fFinished = FALSE;
	char* taken;

	hSearch = FindFirstFile(path, &FileData);
	if (hSearch == INVALID_HANDLE_VALUE) 
    { 
        fFinished=TRUE;
    }

	while (!fFinished) 
    {
		taken=strtok(FileData.cFileName,".");
		if(taken!=NULL)
    		m_TicketNameBox.AddString(taken);

        if (!FindNextFile(hSearch, &FileData)) 
            fFinished = TRUE; 
    } 
 
    FindClose(hSearch);

	CString BoxName;
	int Count=m_TicketNameBox.GetCount();
	for(int i=0;i<Count;i++)
	{
		m_TicketNameBox.GetLBText(i,BoxName);
		if(strcmp(m_TicketName,BoxName)==0)
		{
			m_TicketNameBox.SetCurSel(i);
			break;
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣��OCX ����ҳӦ���� FALSE
}

void CSelTicketDlg::OnBnClickedCreatebutton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CCreateTicketDlg dlg;
	CString TicketName;
	if(dlg.DoModal()==IDOK)
	{
		TicketName=dlg.GetTicketName();
		m_TicketNameBox.AddString(TicketName);
	}

	CString BoxName;
	int Count=m_TicketNameBox.GetCount();
	for(int i=0;i<Count;i++)
	{
		m_TicketNameBox.GetLBText(i,BoxName);
		if(strcmp(BoxName,TicketName)==0)
		{
			m_TicketNameBox.SetCurSel(i);
			break;
		}
	}
}

void CSelTicketDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString BoxName;
	m_TicketNameBox.GetLBText(m_TicketNameBox.GetCurSel(),BoxName);

	if(strlen(BoxName)>=33)
	{
		AfxMessageBox("�ļ����Ƴ��Ȳ��ܳ���16�����֣�");
		return;
	}

	strcpy(m_TicketName,BoxName.Left(33));
	OnOK();
}
