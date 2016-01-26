
// VEMCUCtl.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "VEMCUCtlDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CVEMCUCtlApp

BEGIN_MESSAGE_MAP(CVEMCUCtlApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CVEMCUCtlApp ����

CVEMCUCtlApp::CVEMCUCtlApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CVEMCUCtlApp ����

CVEMCUCtlApp theApp;

HANDLE g_hAppMutex = NULL;

// CVEMCUCtlApp ��ʼ��

BOOL CVEMCUCtlApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// �������ڴ洢���õ�ע�����
	SetRegistryKey(_T("�ȵ���"));

	g_hAppMutex = CreateMutex(NULL,FALSE,"JS-VEMCUCtl");
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		if (g_hAppMutex != NULL)
		{
			CloseHandle(g_hAppMutex);
			g_hAppMutex = NULL;
		}

		MessageBox(NULL,"�ͻ�����������,������С��������λ��,��ͨ������������ͼ���Ҽ��ķ�ʽ������ʾ���������ͼ��ʱ,��������������йرս���\"VEMCUCtl.exe\",�����������ͻ��ˡ�","��Ƶ����ϵͳ",MB_OK);
		return FALSE;
	}

	CVEMCUCtlDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{

	}
	else if (nResponse == IDCANCEL)
	{

	}

	if (g_hAppMutex != NULL)
	{
		CloseHandle(g_hAppMutex);
		g_hAppMutex = NULL;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
