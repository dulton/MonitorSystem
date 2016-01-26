#include "stdafx.h"
#include "VEMCUCtl.h"
#include "VEMCUCtlDlg.h"
#include "CameraVideoOperate.h"
#include "SipCall.h"
#include "VMLog.h"

void ThreadMakeCallCameraServer(void *arg)
{
	g_ThreadVideoOperateNumberInfo.DeviceVideoOutNumerAdd();

	if (arg == NULL)
		return;

	try
	{
		VIDEO_SIP_CALL_SERVER_INFO *pVideoSipCallServerInfo = (VIDEO_SIP_CALL_SERVER_INFO*)arg;
		_T_NODE_INFO *pServerNodeInfo = &pVideoSipCallServerInfo->server_node_info;

		if (g_pMainDlg == NULL)
			return;

		g_VMLog.WriteVmLog("�߳�--��ʼ����--1--ThreadMakeCallCameraServer--����:%d,Tag:%d,���к���:%s,��������:%s",pVideoSipCallServerInfo->nType,pVideoSipCallServerInfo->nDecodeTag,pVideoSipCallServerInfo->szCode,pVideoSipCallServerInfo->szName);

		switch(pVideoSipCallServerInfo->nType)
		{
		case 1://1:ͨ������ƽ̨����
			{
				AppCancelRestartCameraVideo(pVideoSipCallServerInfo->nScreenId);
				AppSetRestartCameraVideo(pVideoSipCallServerInfo->nScreenId);

				MakeCallCameraByViewType(pVideoSipCallServerInfo->nScreenId,
					pVideoSipCallServerInfo->szCode,
					pVideoSipCallServerInfo->szName,
					0,
					pVideoSipCallServerInfo->nDecodeTag,
					pVideoSipCallServerInfo->nStatus,
					pVideoSipCallServerInfo->nStreamless,
					pVideoSipCallServerInfo->szStation,
					0,
					NULL,
					pVideoSipCallServerInfo->szReason);

			}
			break;

		case 2://2:ֱ�Ӻ���ǰ���豸
			{
				AppCancelRestartCameraVideo(pVideoSipCallServerInfo->nScreenId);
				AppSetRestartCameraVideo(pVideoSipCallServerInfo->nScreenId);

				MakeCallCameraByViewType(pVideoSipCallServerInfo->nScreenId,
					pVideoSipCallServerInfo->szCode,
					pVideoSipCallServerInfo->szName,
					1,
					pVideoSipCallServerInfo->nDecodeTag,
					pVideoSipCallServerInfo->nStatus,
					pVideoSipCallServerInfo->nStreamless,
					pVideoSipCallServerInfo->szStation,
					1,
					pServerNodeInfo,
					pVideoSipCallServerInfo->szReason);
			}
			break;

		case 3://3:ͨ������ƽ̨����
			{
				MakeCallCameraByViewType(pVideoSipCallServerInfo->nScreenId,
					pVideoSipCallServerInfo->szCode,
					pVideoSipCallServerInfo->szName,
					0,
					pVideoSipCallServerInfo->nDecodeTag,
					pVideoSipCallServerInfo->nStatus,
					pVideoSipCallServerInfo->nStreamless,
					pVideoSipCallServerInfo->szStation,
					0,
					NULL,
					pVideoSipCallServerInfo->szReason);
			}
			break;

		case 4://4:ͨ��ֱ�Ӻ���ǰ���豸����
			{
				MakeCallCameraByViewType(pVideoSipCallServerInfo->nScreenId,
					pVideoSipCallServerInfo->szCode,
					pVideoSipCallServerInfo->szName,
					1,
					pVideoSipCallServerInfo->nDecodeTag,
					pVideoSipCallServerInfo->nStatus,
					pVideoSipCallServerInfo->nStreamless,
					pVideoSipCallServerInfo->szStation,
					1,
					pServerNodeInfo,
					pVideoSipCallServerInfo->szReason);

			}
			break;

		default:
			break;
		}

		g_VMLog.WriteVmLog("�߳�--��ʼ����--2--ThreadMakeCallCameraServer--����:%d,Tag:%d,���к���:%s,��������:%s",pVideoSipCallServerInfo->nType,pVideoSipCallServerInfo->nDecodeTag,pVideoSipCallServerInfo->szCode,pVideoSipCallServerInfo->szName);
	}
	catch(...)
	{

	}
}

//������Ƶ���в�ת��Ԥ��λ
void ThreadMakeCallCameraPreset(void *arg)
{
	g_ThreadVideoOperateNumberInfo.DeviceVideoOutNumerAdd();

	if (arg == NULL)
		return;

	try
	{
		VIDEO_SIP_CALL_PRESET_INFO *pVideoSipCallPresetInfo = (VIDEO_SIP_CALL_PRESET_INFO*)arg;
		_T_NODE_PRESET_INFO *pPresetNodeInfo = &pVideoSipCallPresetInfo->preset_node_info;

		if (g_pMainDlg == NULL)
			return;

		g_VMLog.WriteVmLog("�߳�--��ʼ����--1--ThreadMakeCallCameraPreset--����:%d,���к���:%s,��������:%s",pVideoSipCallPresetInfo->nType,pVideoSipCallPresetInfo->szCode,pVideoSipCallPresetInfo->szName);

		switch (pVideoSipCallPresetInfo->nType)
		{
		case 1://1:ͨ������ƽ̨����
			{
				AppCancelRestartCameraVideo(pVideoSipCallPresetInfo->nScreenId);
				AppSetRestartCameraVideo(pVideoSipCallPresetInfo->nScreenId);

				MakeCallCameraByViewType(pVideoSipCallPresetInfo->nScreenId,
					                                              pVideoSipCallPresetInfo->szCode,
																  pVideoSipCallPresetInfo->szName,
																  0,
																  pVideoSipCallPresetInfo->nDecodeTag,
																  pVideoSipCallPresetInfo->nStatus,
																  pVideoSipCallPresetInfo->nStreamless,
																  pVideoSipCallPresetInfo->szStation,
																  0,
																  NULL,
																  pVideoSipCallPresetInfo->szReason);
			}
			break;

		case 2://2:ֱ�Ӻ���ǰ���豸
			{
				AppCancelRestartCameraVideo(pVideoSipCallPresetInfo->nScreenId);
				AppSetRestartCameraVideo(pVideoSipCallPresetInfo->nScreenId);

				MakeCallCameraByViewType(pVideoSipCallPresetInfo->nScreenId,
					                                              pVideoSipCallPresetInfo->szCode,
																  pVideoSipCallPresetInfo->szName,
																  0,
																  pVideoSipCallPresetInfo->nDecodeTag,
																  pVideoSipCallPresetInfo->nStatus,
																  pVideoSipCallPresetInfo->nStreamless,
																  pVideoSipCallPresetInfo->szStation,
																  3,
																  pPresetNodeInfo,
																  pVideoSipCallPresetInfo->szReason);
			}
			break;

		case 3://3:ͨ������ƽ̨����
			{
				MakeCallCameraByViewType(pVideoSipCallPresetInfo->nScreenId,
					                                              pVideoSipCallPresetInfo->szCode,
																  pVideoSipCallPresetInfo->szName,
																  1,
																  pVideoSipCallPresetInfo->nDecodeTag,
																  pVideoSipCallPresetInfo->nStatus,
																  pVideoSipCallPresetInfo->nStreamless,
																  pVideoSipCallPresetInfo->szStation,
																  2,
																  pPresetNodeInfo,
																  pVideoSipCallPresetInfo->szReason);
			}
			break;

		case 4://4:ͨ��ֱ�Ӻ���ǰ���豸����
			{
				MakeCallCameraByViewType(pVideoSipCallPresetInfo->nScreenId,
					                                              pVideoSipCallPresetInfo->szCode,
																  pVideoSipCallPresetInfo->szName,
																  1,
																  pVideoSipCallPresetInfo->nDecodeTag,
																  pVideoSipCallPresetInfo->nStatus,
																  pVideoSipCallPresetInfo->nStreamless,
																  pVideoSipCallPresetInfo->szStation,
																  3,
																  pPresetNodeInfo,
																  pVideoSipCallPresetInfo->szReason);
			}
			break;

		default:
			break;
		}

		g_VMLog.WriteVmLog("�߳�--��ʼ����--2--ThreadMakeCallCameraPreset--����:%d,���к���:%s,��������:%s",pVideoSipCallPresetInfo->nType,pVideoSipCallPresetInfo->szCode,pVideoSipCallPresetInfo->szName);

		//////////////////////////////////////////////////////////////////////////
		Sleep(500);

		if (pPresetNodeInfo->preset_id >= 0)
		{
			char szInfo[1024] = {0};

			sprintf(szInfo, "<ctrlcamera user=\"admin\" station=\"%s\" name=\"%s\" code=\"%s\" CommandName=\"Ԥ��λ����\" command=\"1538\" CommandPara1=\"%d\" CommandPara2=\"0\" CommandPara3=\"0\" srcip=\"%s\"/>",
				pPresetNodeInfo->node_station,pPresetNodeInfo->node_name,pPresetNodeInfo->node_num, pPresetNodeInfo->preset_id,app_StackCfg.szLocalUdpAddress);

			SendVideoYTControlInfo(szInfo,strlen(szInfo));
		}

		//////////////////////////////////////////////////////////////////////////
	}
	catch(...)
	{

	}
}

void ThreadVideoLinkageMakeCall(void *arg)
{
	g_ThreadVideoOperateNumberInfo.DeviceVideoOutNumerAdd();

	if (arg == NULL)
		return;

	try
	{
		VIDEO_SIP_CALL_PRESET_INFO *pVideoSipCallPresetInfo = (VIDEO_SIP_CALL_PRESET_INFO*)arg;
		_T_NODE_PRESET_INFO *pPresetNodeInfo = &pVideoSipCallPresetInfo->preset_node_info;

		if (g_pMainDlg == NULL)
			return;

		g_VMLog.WriteVmLog("�߳�--��ʼ����--1--ThreadVideoLinkageMakeCall--����:%d,���к���:%s,��������:%s",pVideoSipCallPresetInfo->nType,pVideoSipCallPresetInfo->szCode,pVideoSipCallPresetInfo->szName);

		switch (pVideoSipCallPresetInfo->nType)
		{
		case 1://1:ͨ������ƽ̨����
			{
				AppCancelRestartCameraVideo(pVideoSipCallPresetInfo->nScreenId);
				AppSetRestartCameraVideo(pVideoSipCallPresetInfo->nScreenId);

				MakeCallCameraByViewType(pVideoSipCallPresetInfo->nScreenId,
					pVideoSipCallPresetInfo->szCode,
					pVideoSipCallPresetInfo->szName,
					0,
					pVideoSipCallPresetInfo->nDecodeTag,
					pVideoSipCallPresetInfo->nStatus,
					pVideoSipCallPresetInfo->nStreamless,
					pVideoSipCallPresetInfo->szStation,
					0,
					NULL,
					pVideoSipCallPresetInfo->szReason);
			}
			break;

		case 2://2:ֱ�Ӻ���ǰ���豸
			{
				AppCancelRestartCameraVideo(pVideoSipCallPresetInfo->nScreenId);
				AppSetRestartCameraVideo(pVideoSipCallPresetInfo->nScreenId);

				MakeCallCameraByViewType(pVideoSipCallPresetInfo->nScreenId,
					pVideoSipCallPresetInfo->szCode,
					pVideoSipCallPresetInfo->szName,
					0,
					pVideoSipCallPresetInfo->nDecodeTag,
					pVideoSipCallPresetInfo->nStatus,
					pVideoSipCallPresetInfo->nStreamless,
					pVideoSipCallPresetInfo->szStation,
					3,
					pPresetNodeInfo,
					pVideoSipCallPresetInfo->szReason);
			}
			break;

		case 3://3:ͨ������ƽ̨����
			{
				MakeCallCameraByViewType(pVideoSipCallPresetInfo->nScreenId,
					pVideoSipCallPresetInfo->szCode,
					pVideoSipCallPresetInfo->szName,
					1,
					pVideoSipCallPresetInfo->nDecodeTag,
					pVideoSipCallPresetInfo->nStatus,
					pVideoSipCallPresetInfo->nStreamless,
					pVideoSipCallPresetInfo->szStation,
					2,
					pPresetNodeInfo,
					pVideoSipCallPresetInfo->szReason);
			}
			break;

		case 4://4:ͨ��ֱ�Ӻ���ǰ���豸����
			{
				MakeCallCameraByViewType(pVideoSipCallPresetInfo->nScreenId,
					pVideoSipCallPresetInfo->szCode,
					pVideoSipCallPresetInfo->szName,
					1,
					pVideoSipCallPresetInfo->nDecodeTag,
					pVideoSipCallPresetInfo->nStatus,
					pVideoSipCallPresetInfo->nStreamless,
					pVideoSipCallPresetInfo->szStation,
					3,
					pPresetNodeInfo,
					pVideoSipCallPresetInfo->szReason);
			}
			break;

		default:
			break;
		}

		g_VMLog.WriteVmLog("�߳�--��ʼ����--2--ThreadVideoLinkageMakeCall--����:%d,���к���:%s,��������:%s",pVideoSipCallPresetInfo->nType,pVideoSipCallPresetInfo->szCode,pVideoSipCallPresetInfo->szName);
	}
	catch(...)
	{

	}
}

//����״̬����
void ThreadSipStateHandlerTalking(void *arg)
{
	if (arg == NULL)
		return;

	try
	{
		SIP_STATE_HANDLER_INFO *pSipStateHandlerInfo = (SIP_STATE_HANDLER_INFO*)arg;

		int nCID = pSipStateHandlerInfo->nCID;

		int nIndex = g_pMainDlg->SearchIndexCallByCID(nCID);

		bool bDecodeResult = false;

		g_VMLog.WriteVmLog("�߳�--�����Ự:nIndex = %d,nCID = %d",nIndex,nCID);

		if (nIndex < 0)
		{
			if (AppUacUasIDIsValid(nCID) != FALSE)
			{
				AppHangupCallIdByPlatform(nCID);
			}
			return;
		}

		GW_PLAY_CHANNEL_INFO  *pPlayChannelInfo = g_DlgVideoView[nIndex].m_pPlayChannelInfo;
		if (pPlayChannelInfo == NULL)
			return;

		g_VMLog.WriteVmLog("�߳�--��ʼ����--1:nIndex = %d,nCID = %d,nVideoPlayload = %d,CalleeUser=%s",nIndex,nCID,pSipStateHandlerInfo->nVideoPayload,pSipStateHandlerInfo->szCalleeNum);

		pPlayChannelInfo->Lock();

		pPlayChannelInfo->StopPlay();

		pPlayChannelInfo->SetData(NULL,NULL,-1,pSipStateHandlerInfo->nVideoPayload,pSipStateHandlerInfo->Sps,pSipStateHandlerInfo->nSpsLen,NULL,NULL,-1);

		bDecodeResult = pPlayChannelInfo->StartPlay();

		pPlayChannelInfo->m_nCid = nCID;

		pPlayChannelInfo->Unlock();

		g_VMLog.WriteVmLog("�߳�--��ʼ����--2:nIndex = %d,nCID = %d,CalleeUser=%s",nIndex,nCID,pSipStateHandlerInfo->szCalleeNum);

		if (g_DlgVideoView[nIndex].m_hCallResultNotifyEvent != NULL)
		{
			SetEvent(g_DlgVideoView[nIndex].m_hCallResultNotifyEvent);
		}

		if (bDecodeResult == false)
		{
			g_DlgVideoView[nIndex].m_VideoViewOutInfo.Lock();
			g_DlgVideoView[nIndex].m_VideoViewOutInfo.m_bSetNrDecodeProblemFlag = TRUE;
			g_DlgVideoView[nIndex].m_VideoViewOutInfo.UnLock();
			AppHangupCallIdByPlatform(nCID);
		}
	}
	catch(...)
	{

	}
}

//���н���
void ThreadSipStateHandlerTerminate(void *arg)
{
	if (arg == NULL)
		return;

	try
	{
		SIP_STATE_HANDLER_INFO *pSipStateHandlerInfo = (SIP_STATE_HANDLER_INFO*)arg;

		int nCID = pSipStateHandlerInfo->nCID;

		int nIndex = g_pMainDlg->SearchIndexCallByCID(nCID);
		E_RtCallStateReason eReason = (E_RtCallStateReason)pSipStateHandlerInfo->nReason;

		g_VMLog.WriteVmLog("�߳�--��������:nWinID = %d,nCID = %d,eReason = %d",nIndex,nCID,eReason);

		AppClearUacUasID(nCID);

		if (nIndex >=0&&nIndex < MAXVIEWCH)
		{
			g_DlgVideoView[nIndex].ClearViewChannelInfo();

			if (eReason == E_RT_CALL_REASON_LOCAL_CANCEL||eReason == E_RT_CALL_REASON_LOCAL_HANGUP)
			{
				g_DlgVideoView[nIndex].OnStopRecord();
				g_pMainDlg->StopVideoWinWeatherCurrentInfoByFlag(nIndex);

				g_DlgVideoView[nIndex].FlashChannel();

				g_DlgVideoView[nIndex].m_VideoViewOutInfo.Lock();
				if (g_DlgVideoView[nIndex].m_VideoViewOutInfo.m_bSetNrDecodeProblemFlag != FALSE)
				{
					g_pMainDlg->PostMessage(WM_DEVICE_VIDEO_QUICK_RESTART_MESSAGE,(WPARAM)nIndex,(LPARAM)eReason);
				}
				else if (g_DlgVideoView[nIndex].m_VideoViewOutInfo.m_bVideoFlowProblemFlag != FALSE)
				{
					g_pMainDlg->SetTimer(TIMER_VIDEO_ERROR_REASON_VIDEO_CHANNEL_0_TIMER+nIndex,1000,NULL);
				}
				g_DlgVideoView[nIndex].m_VideoViewOutInfo.UnLock();
			}
			else
			{
				g_DlgVideoView[nIndex].OnStopRecord();
				g_pMainDlg->StopVideoWinWeatherCurrentInfoByFlag(nIndex);
				g_pMainDlg->PostMessage(WM_DEVICE_VIDEO_CLOSE_MESSAGE,(WPARAM)nIndex,(LPARAM)eReason);
			}

			g_VMLog.WriteVmLog("�߳�--��������--1:nWinID= %d,nCID = %d",nIndex,nCID);

			g_DlgVideoView[nIndex].m_pPlayChannelInfo->Lock();
			g_DlgVideoView[nIndex].m_pPlayChannelInfo->m_nCid = -1;
			g_DlgVideoView[nIndex].m_pPlayChannelInfo->StopPlay();
			g_DlgVideoView[nIndex].m_pPlayChannelInfo->Unlock();

			g_VMLog.WriteVmLog("�߳�--��������--2:nWinID = %d,nCID = %d",nIndex,nCID);

			if (g_DlgVideoView[nIndex].m_hCallResultNotifyEvent != NULL)
			{
				SetEvent(g_DlgVideoView[nIndex].m_hCallResultNotifyEvent);
			}
		}

	}
	catch(...)
	{

	}
}

//������������
void ThreadStopCurrentVideo(void *arg)
{
	if (arg == NULL)
		return;

	int nIndex = 0;

	try
	{
		if (g_pMainDlg == NULL)
			return;

		nIndex = *(int *)arg;
		if (nIndex != g_pMainDlg->m_iFocuseWindowID)
			return;

		g_pMainDlg->VemStopCurrentVideo();

		Sleep(100);
	}
	catch(...)
	{

	}
}

//��������ȫ������
void ThreadStopAllVideo(void *arg)
{
	if(arg == NULL)
		return;

	int nIndex = 0;

	try
	{
		if (g_pMainDlg == NULL)
			return;

		nIndex = *(int *)arg;
		if (nIndex != g_pMainDlg->m_iFocuseWindowID)
			return;

		g_pMainDlg->VemStopAllVideo();
		Sleep(200);
	}
	catch(...)
	{

	}
}

//��������ֱ���豸����
void ThreadStopDirectDeviceVideo(void *arg)
{
	try
	{
		int nID = *(int*)arg;
		AppHangupCallByDirectDevice(nID);
	}
	catch(...)
	{

	}
}

//��������ƽ̨����
void ThreadStopPlatformVideoByCallId(void *arg)
{
	try
	{
		int nCallID = *(int*)arg;

		if (nCallID >= 0)
		{
			AppHangupCallIdByPlatform(nCallID);
		}
	}
	catch(...)
	{

	}
}