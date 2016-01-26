#pragma once

#include "canvas/LineProp.h"

// CPropYcCurveOther �Ի���

class CPropYcCurveOther : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropYcCurveOther)

public:
	CPropYcCurveOther();
	virtual ~CPropYcCurveOther();

	CStaticColor  m_CtrlPlanColor;
	CStaticColor  m_CtrlYestordayColor;


// �Ի�������
	enum { IDD =  NULL};//IDD_YCCURVEPAGE3
private:
	/*
	BYTE m_bHasPlan;
	BYTE m_bShowPlan;
	BYTE m_bHasYestorday;
    */
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedPlan();
	afx_msg void OnStnClickedYestorday();
	void SetProp(BYTE bHasPlan, BYTE bShowPlan, COLORREF colorPlan, BYTE bHasYestorday, COLORREF colorYestorday);
	void GetProp(BYTE& bHasPlan, BYTE& bShowPlan, COLORREF& colorPlan, BYTE& bHasYestorday, COLORREF& colorYestorday);
	BOOL m_bHasPlan;
	BOOL m_bShowPlan;
	BOOL m_bHasYestorday;
	virtual BOOL OnInitDialog();
};
