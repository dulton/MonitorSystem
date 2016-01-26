// PropYcCurveOther.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "sp_draw.h"
#include "PropYcCurveOther.h"


// CPropYcCurveOther �Ի���

IMPLEMENT_DYNAMIC(CPropYcCurveOther, CPropertyPage)
CPropYcCurveOther::CPropYcCurveOther()
	: CPropertyPage(CPropYcCurveOther::IDD)
	, m_bHasPlan(FALSE)
	, m_bShowPlan(FALSE)
	, m_bHasYestorday(FALSE)
{
	m_CtrlPlanColor.m_Color=RGB(255,255,255);
	m_CtrlYestordayColor.m_Color=RGB(127,127,127);

}

CPropYcCurveOther::~CPropYcCurveOther()
{
}

void CPropYcCurveOther::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK2, m_bHasPlan);
	DDX_Check(pDX, IDC_CHECK1, m_bShowPlan);
	DDX_Check(pDX, IDC_CHECK6, m_bHasYestorday);
}


BEGIN_MESSAGE_MAP(CPropYcCurveOther, CPropertyPage)
	ON_STN_CLICKED(IDC_PLAN, OnStnClickedPlan)
	ON_STN_CLICKED(IDC_YESTORDAY, OnStnClickedYestorday)
END_MESSAGE_MAP()


// CPropYcCurveOther ��Ϣ�������

void CPropYcCurveOther::OnStnClickedPlan()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_CtrlPlanColor.Invalidate();
	

}

void CPropYcCurveOther::OnStnClickedYestorday()
{
	
	m_CtrlYestordayColor.Invalidate();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

/*
*		CStaticColor  m_CtrlPlanColor;
CStaticColor  m_CtrlYestordayColor;


// �Ի�������
enum { IDD = IDD_YCCURVEPAGE3 };
private:
BYTE m_bHasPlan;
BYTE m_bShowPlan;
BYTE m_bShowYestorday;

 */

void CPropYcCurveOther::SetProp(BYTE bHasPlan, BYTE bShowPlan, COLORREF colorPlan, BYTE bHasYestorday, COLORREF colorYestorday)
{
	m_bHasPlan=bHasPlan;
	m_bShowPlan=bShowPlan;
	m_bHasYestorday=bHasYestorday;
	m_CtrlPlanColor.m_Color=colorPlan;
	m_CtrlYestordayColor.m_Color=colorYestorday;
}

void CPropYcCurveOther::GetProp(BYTE& bHasPlan, BYTE& bShowPlan, COLORREF& colorPlan, BYTE& bHasYestorday, COLORREF& colorYestorday)
{
	bHasPlan=(BYTE)m_bHasPlan;
	bShowPlan=(BYTE)m_bShowPlan;
	bHasYestorday=(BYTE)m_bHasYestorday;
	colorPlan=m_CtrlPlanColor.m_Color;
	colorYestorday=m_CtrlYestordayColor.m_Color;
}

BOOL CPropYcCurveOther::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_CtrlPlanColor.SubclassDlgItem(IDC_PLAN,this);
	m_CtrlYestordayColor.SubclassDlgItem(IDC_YESTORDAY,this);
	m_CtrlPlanColor.Invalidate();
	m_CtrlYestordayColor.Invalidate();


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣��OCX ����ҳӦ���� FALSE
}
