// SDDElecMap.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "SDDElecMap.h"
#include "SDDElecMapDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSDDElecMapApp

BEGIN_MESSAGE_MAP(CSDDElecMapApp, CWinApp)
END_MESSAGE_MAP()


// CSDDElecMapApp ����

CSDDElecMapApp::CSDDElecMapApp()
{
	
}


// Ψһ��һ�� CSDDElecMapApp ����

CSDDElecMapApp theApp;


// CSDDElecMapApp ��ʼ��

BOOL CSDDElecMapApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	CoInitialize(NULL);

	AfxEnableControlContainer();

	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	return TRUE;
}

CString CSDDElecMapApp::getCurrentAppPath()
{
	CString path; 
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH);

	path.ReleaseBuffer(); 
	int pos = path.ReverseFind('\\'); 
	path = path.Left(pos);

#ifdef _DEBUG
	int pos_Debug = path.ReverseFind('\\');
	path = path.Left(pos_Debug);
	path += "\\SDDElecMap\\";
#else
	path += "\\";
#endif

	return path;
}
