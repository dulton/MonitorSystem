#pragma once
#include "../../resource.h"
// CPropYZTYDlg �Ի���

class CPropYZTYDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropYZTYDlg)

public:
	CPropYZTYDlg();
	virtual ~CPropYZTYDlg();

// �Ի�������
	enum { IDD = IDD_PROP_YZTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	// ��ѹ������ʽ
	int m_nUp_action;
	// ��ѹ������ʽ
	int m_nDown_action;
	// ��ͣ������ʽ
	int m_nStop_action;
	// ֱ��
	int m_nZK;
public:
	void SetParam(char text[], char Yknameup[], char Yknamedown[], char Yknamestop[], int bVTup,int bVTdown,int bVTstop, char Yxname_FK[]);
	void GetParam(char text[], char Yknameup[], char Yknamedown[], char Yknamestop[], int &bVTup, int &bVTdown, int &bVTstop, char Yxname_FK[]);
private:
	// ����˵��
	CString m_strName;
	// ��ѹң�ص�
	CString m_strUpName;
	// ��ѹң�ص�
	CString m_strDownName;
	// ��ͣң�ص�
	CString m_strStopName;
	// ������
	CString m_strFK;
public:
	afx_msg void OnBnClickedButton1();
private:
	// 0-��ѹ��1-��ѹ��2-��ͣ��3-������
	int m_nType;
	void AddName(int nType);
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
