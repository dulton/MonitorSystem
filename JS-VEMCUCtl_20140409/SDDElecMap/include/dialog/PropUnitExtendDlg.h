#pragma once

#include "../../resource.h"
// CPropUnitExtendDlg �Ի���

class CPropUnitExtendDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropUnitExtendDlg)

public:
	CPropUnitExtendDlg();
	virtual ~CPropUnitExtendDlg();

// �Ի�������
	enum { IDD = IDD_UNIT_EXTEND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString m_strDes;
	CString m_strEname;
	// �ٻ��¹ʱ���
	BOOL m_bUnExt_SGBW;
public:
	afx_msg void OnBnClickedButton1();
public:
	void GetUnitExtParam(char* des ,char* ename ,bool& bCallSGBW ,bool& bEventSGBW ,bool& bCallMC,bool& bRefresh,bool& bEpd) ;
	void SetUnitExtParam(char* des ,char* ename ,bool bCallSGBW ,bool bEventSGBW ,bool bCallMC,bool bRefresh,bool bEpd) ;
private:
	// �ٻ��¹ʱ���-�¼���
	BOOL m_bUnExt_SGBW_Event;
	// �ٻ�ë������
	BOOL m_bUnExt_MC;
	// ���ͻ���ˢ����Ϣ
	BOOL m_bRefresh;
public:
	// �Ƿ���Ҫepd��ѯ
	BOOL m_bEpd;
};
