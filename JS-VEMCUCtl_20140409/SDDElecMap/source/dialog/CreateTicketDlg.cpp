// CreateTicketDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "sp_draw.h"
#include "dialog/CreateTicketDlg.h"


// CCreateTicketDlg �Ի���

IMPLEMENT_DYNAMIC(CCreateTicketDlg, CDialog)

CCreateTicketDlg::CCreateTicketDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateTicketDlg::IDD, pParent)
	, m_TicketName(_T(""))
{

}

CCreateTicketDlg::~CCreateTicketDlg()
{

}

void CCreateTicketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEMPLATEBOX, m_TemplateBox);
	DDX_Control(pDX, IDC_OBJECTBOX, m_ObjectBox);
	DDX_CBString(pDX, IDC_TICKETNAMEEDIT, m_TicketName);
}

BEGIN_MESSAGE_MAP(CCreateTicketDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CCreateTicketDlg ��Ϣ�������

BOOL CCreateTicketDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//////////////////////////////////////////////////////////////////////////
	char chpath[MAX_PATH];  
	GetModuleFileName(NULL,(LPSTR)chpath,sizeof(chpath));
	CString path;// = theApp.GetDirectory();
	path.Format("%s",chpath);
	path = path+"global\\Ticket\\TL\\*.txt";
	WIN32_FIND_DATA FileData; 
	HANDLE hSearch;
	BOOL fFinished = FALSE;
	char* taken;

	hSearch = FindFirstFile(path, &FileData);
	if (hSearch == INVALID_HANDLE_VALUE) 
    { 
        fFinished = TRUE;
    }

	while (!fFinished) 
    {
		taken = strtok(FileData.cFileName,".");
		if(taken != NULL)
    		m_TemplateBox.AddString(taken);

        if (!FindNextFile(hSearch, &FileData)) 
            fFinished = TRUE; 
    } 
 
    FindClose(hSearch);

    //path = theApp.GetDirectory();
	GetModuleFileName(NULL,(LPSTR)chpath,sizeof(chpath));
	path.Format("%s",chpath);
	path = path+"global\\Ticket\\OB\\*.txt";
	fFinished = FALSE;

	hSearch = FindFirstFile(path, &FileData);
	if (hSearch == INVALID_HANDLE_VALUE) 
    { 
        fFinished = TRUE;
    }

	while (!fFinished) 
    {
		taken = strtok(FileData.cFileName,".");
		if(taken != NULL)
    		m_ObjectBox.AddString(taken);

        if (!FindNextFile(hSearch, &FileData)) 
            fFinished = TRUE; 
    } 
 
    FindClose(hSearch);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣��OCX ����ҳӦ���� FALSE
}

CString CCreateTicketDlg::GetTicketName(void)
{
	return m_TicketName;
}

void CCreateTicketDlg::OnBnClickedOk()
{
	if(m_TemplateBox.GetCurSel() < 0)
	{
		AfxMessageBox("��ѡ�����ģ�壡");
		return;
	}

	if(m_ObjectBox.GetCurSel() < 0)
	{
		AfxMessageBox("��ѡ���������");
		return;
	}

	UpdateData();

	if(m_TicketName == "")
	{
		AfxMessageBox("���������Ʊ���ƣ�");
		return;
	}

	if(strlen(m_TicketName) >= 33)
	{
		AfxMessageBox("�ļ����Ƴ��Ȳ��ܳ���16�����֣�");
		return;
	}

	WIN32_FIND_DATA FileData; 
	HANDLE hSearch;
	char chpath[MAX_PATH]; 
	GetModuleFileName(NULL,(LPSTR)chpath,sizeof(chpath));
	CString path;
	path.Format("%s",chpath);
	//CString path = theApp.GetDirectory();

	path = path+"global\\Ticket\\OT\\"+m_TicketName+".txt";
	hSearch = FindFirstFile(path, &FileData);
	if (hSearch != INVALID_HANDLE_VALUE) 
	{
		AfxMessageBox("�ò���Ʊ�Ѵ��ڣ��������������Ʊ���ƣ�");
		FindClose(hSearch);
		return;
	}

	FindClose(hSearch);

	if(!TestTemplateAndObjects())
	{
		AfxMessageBox("����ģ��Ͳ�������ƥ�䣡������ѡ��");
		return;
	}

	CreateTicket();

	OnOK();
}

BOOL CCreateTicketDlg::TestTemplateAndObjects(void)
{
	CString BoxName;
	m_TemplateBox.GetLBText(m_TemplateBox.GetCurSel(),BoxName);

	char chpath[MAX_PATH]; 
	GetModuleFileName(NULL,(LPSTR)chpath,sizeof(chpath));
	CString TemplateFileName;// = theApp.GetDirectory();
	TemplateFileName.Format("%s",chpath);
	TemplateFileName+="global\\Ticket\\TL\\"+BoxName+".txt";

	m_ObjectBox.GetLBText(m_ObjectBox.GetCurSel(),BoxName);
	CString ObjectFileName;// = theApp.GetDirectory();
	ObjectFileName.Format("%s",chpath);
	ObjectFileName += "global\\Ticket\\OB\\"+BoxName+".txt";

	int TemplateCount=0,ObjectCount=0;
	char TemplateStr[255];
	ObjectCount = GetPrivateProfileInt("Content","Count",0,ObjectFileName);

	char Temp[32];
	CString Tempstr;
	int count = GetPrivateProfileInt("Content","Count",0,TemplateFileName);	
	for(int i = 0;i < count;i++)
	{
		sprintf(Temp,"Content%d",i);
		GetPrivateProfileString("Content",Temp,"",TemplateStr,sizeof(char)*255,TemplateFileName);
		Tempstr = TemplateStr;
		if(Tempstr.Find("__")!=-1)
			TemplateCount++;
	}

	if(TemplateCount != ObjectCount) 
		return FALSE;

	return TRUE;
}

void CCreateTicketDlg::CreateTicket(void)
{
	CString BoxName;
	m_TemplateBox.GetLBText(m_TemplateBox.GetCurSel(),BoxName);

	char chpath[MAX_PATH]; 
	GetModuleFileName(NULL,(LPSTR)chpath,sizeof(chpath));
	CString TemplateFileName;// = theApp.GetDirectory();
	TemplateFileName.Format("%s",chpath);
	TemplateFileName += "global\\Ticket\\TL\\"+BoxName+".txt";

	m_ObjectBox.GetLBText(m_ObjectBox.GetCurSel(),BoxName);
	CString ObjectFileName;// = theApp.GetDirectory();
	ObjectFileName.Format("%s",chpath);
	ObjectFileName += "global\\Ticket\\OB\\"+BoxName+".txt";

	CString TicketFileName;// = theApp.GetDirectory();
	TicketFileName.Format("%s",chpath);
	TicketFileName += "global\\Ticket\\OT\\"+m_TicketName+".txt";

	char Temp[32];
	char TemplateContent[255],ObjectContent[255];
	CString TemplateStr;
	int ObjectCount=0;
	int count = GetPrivateProfileInt("Content","Count",0,TemplateFileName);
	sprintf(Temp,"%d",count);
	WritePrivateProfileString("Content","Count",Temp,TicketFileName);
	
	for(int i = 0;i < count;i++)
	{
		sprintf(Temp,"Content%d",i);
		GetPrivateProfileString("Content",Temp,"",TemplateContent,sizeof(char)*255,TemplateFileName);
		TemplateStr = TemplateContent;
		int Index = TemplateStr.Find("__");
		if(Index != -1)
		{
			sprintf(Temp,"Content%d",ObjectCount);
			GetPrivateProfileString("Content",Temp,"",ObjectContent,sizeof(char)*255,ObjectFileName);
			TemplateStr.Delete(Index,2);
			TemplateStr.Insert(Index,ObjectContent);
			ObjectCount++;
		}
		sprintf(Temp,"Content%d",i);
		WritePrivateProfileString("Content",Temp,TemplateStr,TicketFileName);
	}
}
