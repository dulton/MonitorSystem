#pragma once

#include "afxwin.h"
#include "../../Resource.h"

#define			SHQ_E_NOERROR					0
#define			SHQ_E_NOTLOADDLL				1
#define			SHQ_E_NOTFINDSERVER				2
#define			SHQ_E_OTHER						3
#define         SHQ_E_NOTCOMPUTERNAME           4

#pragma pack(push,before_serverinfo,1)
typedef struct
{
	BYTE wServerNum;           //��������Ŀ
	CHAR stMainServer[64];     //����������
	CHAR stBackServer[64];     //����������
	BYTE bMainServer;          //���������������
	BYTE bBackServer;          //���������������
} DLLSERVERINFO;
#pragma pack(pop,before_serverinfo,8)

// CMNP_SHXGDlg �Ի���

class CMNP_SHXGDlg : public CDialog
{
	DECLARE_DYNAMIC(CMNP_SHXGDlg)

public:
	CMNP_SHXGDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMNP_SHXGDlg();

// �Ի�������
	enum { IDD = IDD_MNP_SHXG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void InitNode(void);
	void InitLine(void);
	void InitUnit(void);
protected:
	BYTE m_Node;
	BYTE m_Line;
	BYTE m_Unit;
	int ErrorCode;
	char MainServerName[64];
	char BackServerName[64];
public:
	void SetNode(BYTE node);
	void SetLine(BYTE line);
	void SetUnit(BYTE unit);
	BYTE GetNode(void);
	BYTE GetLine(void);
	BYTE GetUnit(void);
	char* GetServerName(void);
	int GetServerInfo(void);
	CComboBox m_NodeBox;
	CComboBox m_LineBox;
	CComboBox m_UnitBox;
	void ShowError(void);
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeNodecombo();
	afx_msg void OnCbnSelchangeLinecombo();
};
