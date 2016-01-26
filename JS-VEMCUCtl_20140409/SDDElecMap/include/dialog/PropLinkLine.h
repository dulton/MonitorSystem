#pragma once
#include "../../resource.h"
// CPropLine �Ի���

class CPropLinkLine : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropLinkLine)

public:
	void GetLineParam(char text[],char LineCaption[],BOOL& bLinesoe,BOOL& bLineyc,BOOL& bLineycspecial,
		BOOL& bLinediandu,BOOL& bLineEpd);

	void SetLineParam(char text[],char LineCaption[],BOOL bLinesoe,BOOL bLineyc,BOOL bLineycspecial,
		BOOL bLinediandu,BOOL bLineEpd);

	CPropLinkLine();
	virtual ~CPropLinkLine();

// �Ի�������
	enum { IDD = IDD_LINK_LINE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	// SOE��ѯ
	BOOL m_LineSoe;
	// EPD��ѯ
	BOOL m_LineEpd;
	// ����˵��
	CString m_KZCaption;
	// ��Ԫ��
	CString m_LineNameCaption;
	// ң���ѯ
	BOOL m_LineYC;
	// ң��Խ�޲�ѯ
	BOOL m_LineYX;
	// SOE��ѯ
	BOOL m_LineDiandu;
	afx_msg void OnBnClickedButton1();
};
