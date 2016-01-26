// MNP_SHXGDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "sp_draw.h"
#include "dialog/MNP_SHXGDlg.h"


// CMNP_SHXGDlg �Ի���

IMPLEMENT_DYNAMIC(CMNP_SHXGDlg, CDialog)
CMNP_SHXGDlg::CMNP_SHXGDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMNP_SHXGDlg::IDD, pParent)
	, m_Node(0)
	, m_Line(0)
	, m_Unit(0)
{
}

CMNP_SHXGDlg::~CMNP_SHXGDlg()
{
}

void CMNP_SHXGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NODECOMBO, m_NodeBox);
	DDX_Control(pDX, IDC_LINECOMBO, m_LineBox);
	DDX_Control(pDX, IDC_UNITCOMBO, m_UnitBox);
}


BEGIN_MESSAGE_MAP(CMNP_SHXGDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_NODECOMBO, OnCbnSelchangeNodecombo)
	ON_CBN_SELCHANGE(IDC_LINECOMBO, OnCbnSelchangeLinecombo)
END_MESSAGE_MAP()


// CMNP_SHXGDlg ��Ϣ�������

BOOL CMNP_SHXGDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitNode();
	InitLine();
	InitUnit();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣��OCX ����ҳӦ���� FALSE
}

void CMNP_SHXGDlg::InitNode(void)
{
	CString FileName;
	CHAR ComputerName[64];
	CHAR ReadBuffer[32*1024];
	CString Des="";
	char nodestr[128];
	int nodenum;
	char Num[16];
	DWORD size=sizeof(char)*64;

	GetComputerName(ComputerName,&size);
	CString servername=GetServerName();
	if(strcmp(ComputerName,servername)==0)
	{
		FileName="C:\\sunpac\\par\\global\\Node.node";
	}
	else
	{
    	FileName=servername;
    	FileName="\\\\"+FileName;
    	FileName=FileName+"\\par$\\global\\Node.node";
	}

	int count=GetPrivateProfileSection("node",ReadBuffer,32*1024,FileName);	
	int i=0;
	for( i=0;i<count;i++)
	{
		if((ReadBuffer[i]==0) || (i==count-1))
		{
			if(i==count-1)
			{
				Des=Des+ReadBuffer[i];
			}
			if(sscanf(Des.Left(255),"node%d=%s",&nodenum,nodestr)==2)
			{
				sprintf(Num,"%03d",nodenum);
				m_NodeBox.AddString(Num);
		        strcpy(Num,"");				
			}
			Des="";
		}
		else
		    Des=Des+ReadBuffer[i];
	}

	if(m_NodeBox.GetCount()>0)
	{    
		for(i=0;i<m_NodeBox.GetCount();i++)
		{
			sprintf(Num,"%03d",m_Node);
			m_NodeBox.GetLBText(i,nodestr);
			if(strcmp(nodestr,Num)==0) 
			{
				m_NodeBox.SetCurSel(i);
				break;
			}
		}
	}
}

void CMNP_SHXGDlg::InitLine(void)
{
	UpdateData();
	int index=m_NodeBox.GetCurSel();
	if (index<0) return;

	for(int i=m_LineBox.GetCount()-1;i>-1;i--)
		m_LineBox.DeleteString(i);

	CString nodestr;
	m_NodeBox.GetLBText(index,nodestr);
	int node;
	if(sscanf(nodestr,"%d",&node)!=1)
	    	return;

	CString FileName;
	CHAR ComputerName[64];
	CHAR ReadBuffer[32*1024];
	CString Des="";
	char linestr[128];
	int linenum;
	char Num[16];
	DWORD size=sizeof(char)*64;

	GetComputerName(ComputerName,&size);
	sprintf(Num,"N%03d.line",node);
	CString servername=GetServerName();
	if(strcmp(ComputerName,servername)==0)
	{
		FileName="C:\\sunpac\\par\\global\\";		
		FileName=FileName+Num;
	}
	else
	{
    	FileName=servername;
    	FileName="\\\\"+FileName;
    	FileName=FileName+"\\par$\\global\\";
		FileName=FileName+Num;
	}

	int count=GetPrivateProfileSection("line",ReadBuffer,32*1024,FileName);	
	int i=0;
	for( i=0;i<count;i++)
	{
		if((ReadBuffer[i]==0) || (i==count-1))
		{
			if(i==count-1)
			{
				Des=Des+ReadBuffer[i];
			}

			if(sscanf(Des.Left(255),"line%d=%s",&linenum,linestr)==2)
			{
				sprintf(Num,"%03d",linenum);
				m_LineBox.AddString(Num);
		        strcpy(Num,"");				
			}
			Des="";
		}
		else
		    Des=Des+ReadBuffer[i];
	}

	if(m_LineBox.GetCount()>0)
	{
		for(i=0;i<m_LineBox.GetCount();i++)
		{
			sprintf(Num,"%03d",m_Line);
			m_LineBox.GetLBText(i,linestr);
			if(strcmp(linestr,Num) ==0)
			{
				m_LineBox.SetCurSel(i);
				break;
			}
		}
	}
}

void CMNP_SHXGDlg::InitUnit(void)
{
	CString FileName;
	CString tempstr;
	CHAR ComputerName[64];
	CHAR ReadBuffer[32*1024];
	CString Des="";
	char unitstr[128];
	int unitnum;
	char Num[16];
	DWORD size=sizeof(char)*64;

	for(int i=m_UnitBox.GetCount()-1;i>-1;i--)
		m_UnitBox.DeleteString(i);

	UpdateData();
	int index=m_NodeBox.GetCurSel();
	if (index<0) return;

	CString nodestr;
	m_NodeBox.GetLBText(index,nodestr);
	int node;
	if(sscanf(nodestr,"%d",&node)!=1)
	    	return;
	
	index=m_LineBox.GetCurSel();
	if(index<0) return;

	CString linestr;
	m_LineBox.GetLBText(index,linestr);
	int line;
	if(sscanf(linestr,"%d",&line)!=1)
		return;

	GetComputerName(ComputerName,&size);
	sprintf(Num,"N%03dL%03d.unit",node,line);
	CString servername=GetServerName();
	if(strcmp(ComputerName,servername)==0)
	{
		FileName="C:\\sunpac\\par\\global\\";		
		FileName=FileName+Num;
	}
	else
	{
    	FileName=servername;
    	FileName="\\\\"+FileName;
    	FileName=FileName+"\\par$\\global\\";
		FileName=FileName+Num;
	}


	int count=GetPrivateProfileSection("unit",ReadBuffer,32*1024,FileName);	
	int i=0;
	for( i=0;i<count;i++)
	{
		if((ReadBuffer[i]==0) || (i==count-1))
		{
			if(i==count-1)
			{
				Des=Des+ReadBuffer[i];
			}
			if(sscanf(Des.Left(255),"unit%d=%s",&unitnum,unitstr)==2)
			{
				sprintf(Num,"%03d",unitnum);
				m_UnitBox.AddString(Num);
				strcpy(Num,"");	
			}
			Des="";
		}
		else
		    Des=Des+ReadBuffer[i];
	}

	if(m_UnitBox.GetCount()>0)
	{
		for(i=0;i<m_UnitBox.GetCount();i++)
		{
			sprintf(Num,"%03d",m_Unit);
			m_UnitBox.GetLBText(i,unitstr);
			if(strcmp(unitstr,Num) ==0)
			{
				m_UnitBox.SetCurSel(i);
				break;
			}
		}
	}
}

void CMNP_SHXGDlg::SetNode(BYTE node)
{
	m_Node=node;
}

void CMNP_SHXGDlg::SetLine(BYTE line)
{
	m_Line=line;
}

void CMNP_SHXGDlg::SetUnit(BYTE unit)
{
	m_Unit=unit;
}

BYTE CMNP_SHXGDlg::GetNode(void)
{
	return m_Node;
}

BYTE CMNP_SHXGDlg::GetLine(void)
{
	return m_Line;
}

BYTE CMNP_SHXGDlg::GetUnit(void)
{
	return m_Unit;
}

char* CMNP_SHXGDlg::GetServerName(void)
{
	int serverinfo=GetServerInfo();//��÷�����״̬
	if((serverinfo!=1) && (serverinfo!=2) && (serverinfo!=3)) //���޷�����
	{
		ErrorCode=SHQ_E_NOTFINDSERVER;
		ShowError();
		return NULL;
	}

	switch(serverinfo)
	{
	case 1://���򵥻�
		return MainServerName;
		break;
	case 2://��
		return BackServerName;
		break;
	default:		
		ErrorCode=SHQ_E_OTHER;
		ShowError();
		return NULL;
	}
}

int CMNP_SHXGDlg::GetServerInfo(void)
{
	int servercount=GetPrivateProfileInt("server","count",0,"C:\\sunpac\\par\\global\\sunsys.ini");
	if(servercount==0)   //����״̬
	{
		DWORD size=sizeof(char)*64;
		if(GetComputerName(MainServerName,&size)==0)
		{
			ErrorCode=SHQ_E_NOTCOMPUTERNAME;
			return 0;
		}
		return 1;    //����״̬
	}	
	GetPrivateProfileString("server","server0","",MainServerName,sizeof(char)*64,"C:\\sunpac\\par\\global\\sunsys.ini");
	//�������������
	GetPrivateProfileString("server","server1","",BackServerName,sizeof(char)*64,"C:\\sunpac\\par\\global\\sunsys.ini");
	//��ñ���������

	/************���Ӷ�̬���ӿ�****************/
	DLLSERVERINFO m_serverinfo;
	typedef BOOL _stdcall TGetServerInfo(DLLSERVERINFO* p_Info);
	TGetServerInfo *pGetServerInfo = NULL;
	HINSTANCE dllhandle;
	dllhandle = LoadLibrary("C:\\sunpac\\dll\\Sp_ServerInfo.dll");
	if(dllhandle==0) 
	{
		ErrorCode=SHQ_E_NOTLOADDLL;
		return 0;
	}
	pGetServerInfo=(TGetServerInfo*)::GetProcAddress(dllhandle,"GetServerInfo");
	if(pGetServerInfo==NULL)
	{
		FreeLibrary(dllhandle);
		ErrorCode=SHQ_E_NOTLOADDLL;
		return 0;
	}
	/************���Ӷ�̬���ӿ�****************/

	if(!(*pGetServerInfo)(&m_serverinfo))
	{
		ErrorCode=SHQ_E_OTHER;
		FreeLibrary(dllhandle);
		return 0;
	}
	else
	{
		FreeLibrary(dllhandle);
		if(m_serverinfo.wServerNum==0) return 0;//��������������ȷ
		if(m_serverinfo.bMainServer==1)
		{
			//������������
			if(_stricmp(m_serverinfo.stMainServer,MainServerName)==0)//����������
				return 1;
			else if(_stricmp(m_serverinfo.stMainServer,BackServerName)==0)//�Ǳ�������
				return 2;
			else 
			{
				ErrorCode=SHQ_E_NOTFINDSERVER;
				return 0;
			}
		}
		else 
		{
			ErrorCode=SHQ_E_NOTFINDSERVER;
			return 0;
		}
	}
}

void CMNP_SHXGDlg::ShowError(void)
{
	switch(ErrorCode)
	{
		case SHQ_E_NOTLOADDLL:
			AfxMessageBox("�޷����Ӷ�̬���ӿ�!");
			break;
		case SHQ_E_NOTFINDSERVER:
			AfxMessageBox("û�ҵ�������!");
			break;
		case SHQ_E_OTHER:
			AfxMessageBox("�����쳣����!");
			break;
		case SHQ_E_NOTCOMPUTERNAME:
			AfxMessageBox("�޷���û�����!");
			break;
		default:
			break;
	}
}

void CMNP_SHXGDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	int index=m_NodeBox.GetCurSel();
	if(index<0)
	{
		AfxMessageBox("��ѡ��ڵ㣡");
		return;
	}
	CString nodestr;
	m_NodeBox.GetLBText(index,nodestr);
	sscanf(nodestr,"%d",&m_Node);
	
	index=m_LineBox.GetCurSel();
	if(index<0)
	{
		AfxMessageBox("��ѡ����·��");
		return;
	}
	CString linestr;
	m_LineBox.GetLBText(index,linestr);
	sscanf(linestr,"%d",&m_Line);

	index=m_UnitBox.GetCurSel();
	if(index<0)
	{
		AfxMessageBox("��ѡ��Ԫ��");
		return;
	}
	CString unitstr;
	m_UnitBox.GetLBText(index,unitstr);
	sscanf(unitstr,"%d",&m_Unit);
	OnOK();
}

void CMNP_SHXGDlg::OnCbnSelchangeNodecombo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	InitLine();
	InitUnit();
}

void CMNP_SHXGDlg::OnCbnSelchangeLinecombo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	InitUnit();
}
