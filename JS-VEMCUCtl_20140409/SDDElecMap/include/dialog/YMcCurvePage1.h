#pragma once

#include "../../resource.h"

// CYMcCurvePage1 �Ի���

class CYMcCurvePage1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CYMcCurvePage1)

public:
	CYMcCurvePage1();
	virtual ~CYMcCurvePage1();

// �Ի�������
	enum { IDD = IDD_YMCURVEPAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ����
	CString m_strmcename;
	float m_fLeftcoord;
	float m_fTopcoord;
	float m_fXlen;
	float m_fYlen;
	// Сʱ����
	DWORD m_hMin;
	DWORD m_hMax;
	DWORD m_hScale;
	// ������
	DWORD m_dMin;
	DWORD m_dMax;
	DWORD m_dScale;
	// ������
	DWORD m_mMin;
	DWORD m_mMax;
	DWORD m_mScale;
	// ������
	DWORD m_yMin;
	DWORD m_yMax;
	DWORD m_yScale;
	// �����ᵥλ
	CString m_unit;
};
