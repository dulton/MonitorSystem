// YMcCurvePage2.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "sp_draw.h"
#include <Shlwapi.h>
#include "dialog/YMcCurvePage2.h"


// CYMcCurvePage2 �Ի���

IMPLEMENT_DYNAMIC(CYMcCurvePage2, CPropertyPage)
CYMcCurvePage2::CYMcCurvePage2()
	: CPropertyPage(CYMcCurvePage2::IDD)
	, m_ename(_T(""))
	, m_cname(_T(""))
	, m_nColor(0) 
{
	m_nEditIndex = -1 ;
}

CYMcCurvePage2::~CYMcCurvePage2()
{
}

void CYMcCurvePage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_CurveList);
	DDX_Text(pDX, IDC_EDIT1, m_ename);
	DDV_MaxChars(pDX, m_ename, 16);
	DDX_Text(pDX, IDC_EDIT2, m_cname);
	DDV_MaxChars(pDX, m_cname, 8);
	DDX_Control(pDX, IDC_STATIC_COLOR, m_stColor);
}


BEGIN_MESSAGE_MAP(CYMcCurvePage2, CPropertyPage)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, OnNMClickList2)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_STN_CLICKED(IDC_STATIC_COLOR, OnStnClickedStaticColor)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
END_MESSAGE_MAP()


// CYMcCurvePage2 ��Ϣ�������

BOOL CYMcCurvePage2::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	DrawListTitle() ;

	SetList(&curvearray) ;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣��OCX ����ҳӦ���� FALSE
}

void CYMcCurvePage2::DrawListTitle()
{
	m_CurveList.InsertColumn(0,"���",LVCFMT_CENTER,50,0);
	m_CurveList.InsertColumn(1,"Ӣ����",LVCFMT_CENTER,60,1);
	m_CurveList.InsertColumn(2,"������",LVCFMT_CENTER,60,2);
	m_CurveList.InsertColumn(3,"��ɫ",LVCFMT_CENTER,50,3);
	m_CurveList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
}

void CYMcCurvePage2::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int iItem=pNMListView->iItem;
	if (iItem==-1)
	{
		return;
	}
	m_nEditIndex=iItem ;
	CString str;
	str.Format("��%d�����߲���",iItem+1);
	GetDlgItem(IDC_STATIC)->SetWindowText(str);
	ymcurve_info *pSingleCurve=GetCurSingleLine(iItem);
	m_ename = pSingleCurve->ename ;
	m_cname = pSingleCurve->cname ;
	m_nColor = pSingleCurve->color ;
	UpdateData(FALSE);
	m_stColor.SetColor(m_nColor) ;
	*pResult = 0;
}

ymcurve_info* CYMcCurvePage2::GetCurSingleLine(int singleline)
{
	ymcurve_info *pTempCurve;
	pTempCurve = &curvearray.GetAt(singleline) ;
	return pTempCurve;
}

void CYMcCurvePage2::SetList(CurveInfo *pCurvearray)
{
	m_CurveList.DeleteAllItems();
	ymcurve_info *pTempCurve;
	int i;
	CString strtext;
	int curvecount=pCurvearray->GetCount();
	for (i=0; i<curvecount; i++)
	{
		pTempCurve=&pCurvearray->GetAt(i);
		strtext.Format("%d",i+1);
		m_CurveList.InsertItem(i,strtext);

		strtext.Format("%s",pTempCurve->ename);
		m_CurveList.SetItemText(i,1,strtext);

		strtext.Format("%s",pTempCurve->cname);
		m_CurveList.SetItemText(i,2,strtext);
	}
}

//�������
void CYMcCurvePage2::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_CurveList.GetItemCount()>=8)
	{
		AfxMessageBox("���ܳ���8��");
		return;
	}
	CString str;
	str.Format("%d",m_CurveList.GetItemCount()+1);
	m_CurveList.InsertItem(m_CurveList.GetItemCount(),str);
	ymcurve_info newcurve;
	strcpy(newcurve.ename ,"") ;
	strcpy(newcurve.cname ,"") ;
	newcurve.color = RGB(0,0,0) ;
	curvearray.Add(newcurve);
}

void CYMcCurvePage2::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CPropertyPage::OnOK();
}

void CYMcCurvePage2::OnStnClickedStaticColor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//ɾ������
void CYMcCurvePage2::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int delindex =(int) m_CurveList.GetFirstSelectedItemPosition()-1;
	if (delindex==-1)
	{
		AfxMessageBox("��ѡ��Ҫɾ��������");
		return;
	}
	curvearray.RemoveAt(delindex) ;
	int i = curvearray.GetCount() ;
	SetList(&curvearray) ;
}

//�ύ
void CYMcCurvePage2::OnBnClickedButton1()
{
	if (m_nEditIndex==-1)
	{
		AfxMessageBox("��ѡ��Ҫ�ύ������");
		return;
	}
	if(curvearray.GetCount() < 1)
	{
		AfxMessageBox("�����������") ;
		return ;
	}

	UpdateData();

	ymcurve_info newcurve ;
	strcpy(newcurve.ename ,m_ename) ;
	strcpy(newcurve.cname ,m_cname) ;
	m_stColor.GetColor(&m_nColor);
	newcurve.color = m_nColor ;

	curvearray.SetAt(m_nEditIndex,newcurve);
	SetList(&curvearray) ;

}

void CYMcCurvePage2::OnBnClickedButton4()
{
	char dllf[256],s[256],myename[17],mycname[33];
 	HINSTANCE hmydll;
 	sprintf(dllf,YC_FINDDOTDLLNAME);
 	hmydll=LoadLibrary(dllf);
 	if (hmydll==NULL)
	{
 		sprintf(s,"%s ����ʧ�ܣ�",dllf);
 		AfxMessageBox(s);
 		return;
 	}

 	ShowFindDotDlg * pf;
 	pf=(ShowFindDotDlg *)::GetProcAddress(hmydll,"ShowFindDotDlg");
 	if (pf==NULL)
	{
 		sprintf(s,"%s ���뺯��ShowFindDotDlg ʧ�ܣ�",dllf);
 		AfxMessageBox(s);
 		FreeLibrary(hmydll);
 		hmydll=NULL;
 		return;
 	}

 	CWnd * pp=this->GetParent();
	BYTE dotkind=0;

	dotkind = 3 ;
 	if ((*pf)(dotkind,myename,mycname))
 	{
 		UpdateData(true);
 		m_ename=myename;
		char tempchar[9] ;
		StrCpyN(tempchar ,mycname ,9) ;
		m_cname = tempchar ;
		
 		UpdateData(false);
 	}
 
 	FreeLibrary(hmydll);
}
