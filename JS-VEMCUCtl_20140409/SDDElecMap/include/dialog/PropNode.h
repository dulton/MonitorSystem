#pragma once

#include "../../resource.h"
// CPropNode �Ի���

class CPropNode : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropNode)

public:
	void GetNodeParam(char text[],char NodeCaption[],BOOL& bNodesoe,BOOL& bNodeyc,BOOL& bNodeycspecial,
		BOOL& bNodediandu,BOOL& bNodeEpd);

	void SetNodeParam(char text[],char NodeCaption[],BOOL bNodesoe,BOOL bNodeyc,BOOL bNodeycspecial,
		BOOL bNodediandu,BOOL bNodeEpd);

	CPropNode();
	virtual ~CPropNode();

// �Ի�������
	enum { IDD = IDD_NODE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	// SOE��ѯ
	BOOL m_NodeSoe;
	// EPD��ѯ
	BOOL m_NodeEpd;
	// ����˵��
	CString m_KZCaption;
	// ��Ԫ��
	CString m_NodeNameCaption;
	// ң���ѯ
	BOOL m_NodeYC;
	// ң��Խ�޲�ѯ
	BOOL m_NodeYX;
	// SOE��ѯ
	BOOL m_NodeDiandu;
	afx_msg void OnBnClickedButton1();
};
