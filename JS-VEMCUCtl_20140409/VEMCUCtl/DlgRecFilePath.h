#pragma once

#include "DirDialog.h"

// CDlgRecFilePath �Ի���
class CDlgRecFilePath : public CDialog
{
	DECLARE_DYNAMIC(CDlgRecFilePath)

public:
	CDlgRecFilePath(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgRecFilePath();

public:
	CString	m_Filepath;

// �Ի�������
	enum { IDD = IDD_DIALOG_RECFILEPATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnFile();
};
