#pragma once

#include "../../resource.h"
// CPropModemDlg �Ի���

class CPropModemDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropModemDlg)

public:
	CPropModemDlg();
	virtual ~CPropModemDlg();

// �Ի�������
	enum { IDD = IDD_LINK_MODEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	// ������id
	DWORD m_adptID;
	CString m_strPhone;
	// ����ʱ�䣬��
	DWORD m_dwtime;
public:
	void SetParam(char* descript ,DWORD adptid ,char *phone ,DWORD time) ;
	void GetParam(char* descript ,DWORD &adptid ,char *phone ,DWORD &time) ;
	virtual BOOL OnInitDialog();
private:
	// ����˵��
	CString m_strDescript;
};
