// PropKXAreaTypeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "sp_draw.h"
#include "dialog/PropKXAreaTypeDlg.h"
#include "dialog/BmpSelectPage.h"

// CPropKXAreaTypeDlg �Ի���

IMPLEMENT_DYNAMIC(CPropKXAreaTypeDlg, CPropertyPage)
CPropKXAreaTypeDlg::CPropKXAreaTypeDlg()
	: CPropertyPage(CPropKXAreaTypeDlg::IDD)
	, m_strBmpName1(_T(""))
	, m_strBmpName2(_T(""))
	,colV1(0)
	,colV2(0)
{
}

CPropKXAreaTypeDlg::~CPropKXAreaTypeDlg()
{
}

void CPropKXAreaTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strBmpName1);
	DDX_Text(pDX, IDC_EDIT2, m_strBmpName2);
}


BEGIN_MESSAGE_MAP(CPropKXAreaTypeDlg, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
END_MESSAGE_MAP()


// CPropKXAreaTypeDlg ��Ϣ�������

BOOL CPropKXAreaTypeDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	HWND hwnd;

	GetDlgItem(IDC_STATIC_V1_COLOR,&hwnd);
	m_VCol1.SubclassWindow(hwnd);
	m_VCol1.SetColor(colV1);
	
	GetDlgItem(IDC_STATIC_V2_COLOR,&hwnd);
	m_VCol2.SubclassWindow(hwnd);
	m_VCol2.SetColor(colV2);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣��OCX ����ҳӦ���� FALSE
}

void CPropKXAreaTypeDlg::OnBnClickedButton1()//����λͼ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL bl ;
	COLORREF color ;

	CPropertySheet sheet( _T("λͼ���..") );
	CBmpSelectPage dlg;
	dlg.SetContent(m_strBmpName1,FALSE,RGB(0,0,0));
	sheet.AddPage( (CPropertyPage*)&dlg );

	if (sheet.DoModal() == IDOK)
	{
		m_strBmpName1=dlg.GetContent(bl,color);
		UpdateData(FALSE);
	}
}

void CPropKXAreaTypeDlg::OnBnClickedButton2()//ʧ��λͼ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL bl ;
	COLORREF color ;

	CPropertySheet sheet( _T("λͼ���..") );
	CBmpSelectPage dlg;
	dlg.SetContent(m_strBmpName2,FALSE,RGB(0,0,0));
	sheet.AddPage( (CPropertyPage*)&dlg );

	if (sheet.DoModal() == IDOK)
	{
		m_strBmpName2=dlg.GetContent(bl,color);
		UpdateData(FALSE);
	}
}
void CPropKXAreaTypeDlg::GetParam(COLORREF* col1 ,COLORREF* col2 ,char* bmpName1 ,char* bmpName2)
{
	*col1 = colV1 ;
	*col2 = colV2 ;
	strcpy(bmpName1 ,m_strBmpName1) ;
	strcpy(bmpName2 ,m_strBmpName2) ;
	
}

void CPropKXAreaTypeDlg::SetParam(COLORREF col1 ,COLORREF col2 ,char* bmpName1 ,char* bmpName2)
{
	colV1 = col1 ;
	colV2 = col2 ;
	m_strBmpName1 = bmpName1 ;
	m_strBmpName2 = bmpName2 ;
}

void CPropKXAreaTypeDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	m_VCol1.GetColor(&colV1) ;
	m_VCol2.GetColor(&colV2) ;
	CPropertyPage::OnOK();
}
