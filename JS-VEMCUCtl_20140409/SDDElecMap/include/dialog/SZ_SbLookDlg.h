#pragma once
#include "../../resource.h"
typedef  __declspec(dllexport) int  ShowEms(int* devptype,int* emstype,char *devid,char *Rdevid,HWND parent);
// CSZ_SbLookDlg �Ի���

class CSZ_SbLookDlg : public CDialog
{
	DECLARE_DYNAMIC(CSZ_SbLookDlg)

public:
	CSZ_SbLookDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSZ_SbLookDlg();

// �Ի�������
	enum { IDD = IDD_SZ_SBLOOK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString m_sbinfo;
	CString m_sbbh;
public:
	void SetInfo(char* Info, char* Sbbh);
	void GetInfo(char* Info, char* Sbbh);
	afx_msg void OnBnClickedButton1();
};
