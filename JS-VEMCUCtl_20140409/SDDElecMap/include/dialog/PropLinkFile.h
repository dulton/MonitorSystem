#pragma once

#include "afxwin.h"
#include "sp_draw.h"

// CPropLinkFile �Ի���

class CPropLinkFile : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropLinkFile)

public:
	CPropLinkFile();
	virtual ~CPropLinkFile();

// �Ի�������
	enum { IDD = IDD_LINK_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString m_filename;			//�ļ���
	CString m_ext;					//�ļ���չ��
	CString m_path;					//�ļ����·��
public:
	CListBox m_listbox;
	CButton m_Btn_Advance;
	virtual BOOL OnInitDialog();
private:
	void FillListBox(void);
public:
	void Setfile(LPCSTR path, LPCSTR filename, LPCSTR ext);
	void Getfile(char* filename);
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedButton1();
};
