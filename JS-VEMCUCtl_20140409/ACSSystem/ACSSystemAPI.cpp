#include "stdafx.h"
#include "ACSSystem.h"
#include "ACSSystemAPI.h"
#include "ACSSystemDlg.h"

CALLBACKACSSYSTEMOPENDVIDEOID callbackacssystemopenvideoid = NULL;

//����ACSSystem��API
BOOL ACSSystem_SetAPI(void* pConfigInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	try
	{
		g_pConfigInfo = (VEM_USER_CONFIG_INFO*)pConfigInfo;
	}

	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}

//����dll����λ��
BOOL ACSSystem_SetDlgPosition(CRect rect)
{
	if (g_pMainDlg != NULL)
	{
		g_pMainDlg->MoveWindow(rect);
	}
	return TRUE;
}


//��ʾ������
BOOL ACSSystem_ShowWindow(HWND hParentWnd,BOOL bShow)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CWnd* pParentWnd = NULL;

	try
	{
		if (g_pMainDlg == NULL)
		{
			g_pMainDlg = new CACSSystemDlg;

			if (g_pMainDlg != NULL)
			{
				if (hParentWnd != NULL)
				{
					pParentWnd = CWnd::FromHandle(hParentWnd);
				}

				g_pMainDlg->Create(IDD_ACSSYSTEM_DIALOG,pParentWnd);
			}
		}

		if (g_pMainDlg != NULL)
		{
			g_pMainDlg->ShowWindow(bShow?SW_SHOW:SW_HIDE);
		}
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

//��Ҫ��������ͨ��dll�ӿ����ﴫ��pMSG
BOOL ACSSystem_PreTranslateMessage(MSG* pMSG)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (g_pMainDlg == NULL)
	{
		return TRUE;
	}

	try
	{
		if (g_pMainDlg != NULL)
		{
			g_pMainDlg->PreTranslateMessage(pMSG);
		}
	}
	catch(...)
	{
		return FALSE;
	}

	return TRUE;
}

//��ACSSystem���û�ȡopenvideo��id�Ļص�����
BOOL ACSSystem_SetCallbackGetOpenVideoId(CALLBACKACSSYSTEMOPENDVIDEOID GetACSSystemOpenDVideoIdCB)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	callbackacssystemopenvideoid = GetACSSystemOpenDVideoIdCB;
	return TRUE;
}

//�����豸ʵʱ����
void ACSSystem_ProcessSMRealData(char* pSmRealData, int nCount)
{
	g_pMainDlg->RefreshYXListRealData(pSmRealData, nCount);
}
