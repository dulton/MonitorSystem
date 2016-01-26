#include "stdafx.h"
#include "CameraVideoOperate.h"
#include "VEMCUCtl.h"
#include "VEMCUCtlDlg.h"


/************************************************************************
*
* ��������ͷ
*
************************************************************************/
BOOL MakeCallCameraByViewType(int nWinID,char* szCameraNum,char* szCameraName,int nViewType,int nDecodeTag,int nCameraStatus,int nStreamless,char* szStationName,int NodeType,void *pNodeInfo,char *szNotes)
{
	try
	{
		if (nViewType == 0)//ͨ������ƽ̨����Ƶ
		{
			return OpenViewCameraVideoByVideoPlatform(nWinID,szCameraNum,szCameraName,nDecodeTag,nCameraStatus,nStreamless,szStationName,NodeType,pNodeInfo,szNotes);
		}
		else if (nViewType == 1)//ֱ��ͨ��ǰ���豸����Ƶ
		{
			return OpenViewCameraVideoByDirectDevice(nWinID,szCameraNum,szCameraName,nDecodeTag,nCameraStatus,nStreamless,szStationName,NodeType,pNodeInfo,szNotes);
		}

		return FALSE;
	}
	catch(...)
	{

	}

	return FALSE;
}

//�жϲ��Ŵ����Ƿ�����Ƶ��
int CheckViewVideoIsOpen(int nWinID)
{
	int nResult = 0;

	try
	{
		if (nWinID < 0||nWinID >= MAXVIEWCH)
			return -1;

		g_DlgVideoView[nWinID].m_VideoViewOutInfo.Lock();

		if (g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nCameraCallStatus == VM_VIEW_OUT_CAMERA_CALL_STATUS_CALLING
			||g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nCameraCallStatus == VM_VIEW_OUT_CAMERA_CALL_STATUS_TALKING)
		{
			if (g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nVideoViewType == 1)
				nResult = 1;
			else if (g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nVideoViewType == 2)
				nResult = 2;
		}

		g_DlgVideoView[nWinID].m_VideoViewOutInfo.UnLock();
		
		return nResult;
	}
	catch(...)
	{

	}

	return -1;
}

//�ж�����ͷ��Ƶ�Ƿ񱻴�
int CheckCameraVideoIsOpen(char *szCameraNum,int &nWinID)
{
	int nIndex = 0;
	int nResult = 0;

	try
	{
		nWinID = 0;

		for (nIndex = 0;nIndex < MAXVIEWCH;nIndex++)
		{
			g_DlgVideoView[nIndex].m_VideoViewOutInfo.Lock();

			if (strcmp(g_DlgVideoView[nIndex].m_VideoViewOutInfo.m_szCameraCallNum,szCameraNum) == 0)
			{
				nWinID = nIndex;
				if (g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nCameraCallStatus == VM_VIEW_OUT_CAMERA_CALL_STATUS_CALLING
					||g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nCameraCallStatus == VM_VIEW_OUT_CAMERA_CALL_STATUS_TALKING)
				{
					if (g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nVideoViewType == 1)
						nResult = 1;
					else if (g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nVideoViewType == 2)
						nResult = 2;
				}

				g_DlgVideoView[nIndex].m_VideoViewOutInfo.UnLock();
				return nResult;
			}

			g_DlgVideoView[nIndex].m_VideoViewOutInfo.UnLock();
		}
		return 0;
	}
	catch(...)
	{

	}
	return -1;
}

//�ر�ָ�����ڵ���Ƶ
BOOL CloseViewVideoByWinID(int nWinID,int nViewType)
{
	try
	{
		if (nViewType == 1)//�ر�ͨ������ƽ̨�򿪵���Ƶ
		{
			return CloseViewPlatformVideoByWinID(nWinID);
		}
		else if (nViewType == 2)//�ر�ֱ�Ӵ򿪵�ǰ����Ƶ
		{
			return CloseViewDeviceVideoByWinID(nWinID);
		}

		return FALSE;
	}
	catch(...)
	{

	}
	return FALSE;
}

//�ر�ָ������ͨ������ƽ̨�򿪵���Ƶ
BOOL CloseViewPlatformVideoByWinID(int nWinID)
{
	try
	{
		if (nWinID < 0||nWinID >= MAXVIEWCH)
			return FALSE;

		int nCallId = -1;
		BOOL bResult = FALSE;

		g_DlgVideoView[nWinID].m_VideoViewOutInfo.Lock();
		if (g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nVideoViewType == 1)
		{
			nCallId = g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nCallid;
			bResult = TRUE;
		}
		g_DlgVideoView[nWinID].m_VideoViewOutInfo.UnLock();

		if (bResult == FALSE||nCallId < 0)
			return FALSE;

		//���Ԥ��λ��Ϣ��ʾ����
		ClearVideoPresetLineInfoDlg(nWinID);

		//ֹͣ������Ϣ��ʾ
		StopVideoWinCurrentWeather(nWinID);

		//ֹͣ¼��
		CloseVideoRecordByWinRecordFlag(nWinID);

		//ֹͣ��Ƶ
		CloseVideoAudioByWinRecordFlag(nWinID);

		//ֹͣ��Ƶ
		if (nCallId >= 0)
		{
			g_VMLog.WriteVmLog("CloseViewPlatformVideoByWinID----nWinID=%d,m_Callid=%d",nWinID,nCallId);

			if (g_DlgVideoView[nWinID].m_hCallResultNotifyEvent != NULL)
			{
				ResetEvent(g_DlgVideoView[nWinID].m_hCallResultNotifyEvent);
				AppHangupCallIdByPlatform(nCallId);
				WaitForSingleObject(g_DlgVideoView[nWinID].m_hCallResultNotifyEvent,2*1000);
			}
			else
			{
				AppHangupCallIdByPlatform(nCallId);
			}
		}

		//�����Ϣ,ˢ�´���
		g_DlgVideoView[nWinID].CloseViewChannel();

		return TRUE;
	}
	catch(...)
	{

	}
	return FALSE;
}

//�ر�ָ������ͨ��ֱ���豸�򿪵���Ƶ
BOOL CloseViewDeviceVideoByWinID(int nWinID)
{
	try
	{
		if (nWinID < 0||nWinID >= MAXVIEWCH)
			return FALSE;

		int nVideoSdkId = -1;
		BOOL bResult = FALSE;

		g_DlgVideoView[nWinID].m_VideoViewOutInfo.Lock();
		if (g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nVideoViewType == 2)
		{
			nVideoSdkId = g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nVideoSdkId;
			bResult = TRUE;
		}
		g_DlgVideoView[nWinID].m_VideoViewOutInfo.UnLock();

		if (bResult == FALSE||nVideoSdkId < 0)
			return FALSE;

		//���Ԥ��λ��Ϣ��ʾ����
		ClearVideoPresetLineInfoDlg(nWinID);

		//ֹͣ������Ϣ��ʾ
		StopVideoWinCurrentWeather(nWinID);

		//ֹͣ¼��
		CloseVideoRecordByWinRecordFlag(nWinID);

		//ֹͣ��Ƶ
		CloseVideoAudioByWinRecordFlag(nWinID);

		//ֹͣ��Ƶ
		if (nVideoSdkId >= 0)
		{
			AppHangupCallByDirectDevice(nVideoSdkId);
		}

		//�����Ϣ,ˢ�´���
		g_DlgVideoView[nWinID].CloseViewChannel();

		return TRUE;
	}
	catch(...)
	{

	}
	return FALSE;
}

//���ָ�����ڵ���Ϣ
BOOL ClearViewPlatformAndDeviceInfoByWinID(int nWinID)
{
	try
	{
		if (nWinID < 0||nWinID >= MAXVIEWCH)
			return FALSE;

		//���Ԥ��λ������Ϣ
		ClearVideoPresetLineInfoDlg(nWinID);

		//ֹͣ������Ϣ��ʾ
		StopVideoWinCurrentWeather(nWinID);

		//ֹͣ¼��
		CloseVideoRecordByWinRecordFlag(nWinID);

		//ֹͣ��Ƶ
		CloseVideoAudioByWinRecordFlag(nWinID);

		//�����Ϣ,ˢ�´���
		g_DlgVideoView[nWinID].CloseViewChannel();

		return TRUE;
	}
	catch(...)
	{

	}
	return FALSE;
}

//�ر�¼��
BOOL CloseVideoRecordByWinRecordFlag(int nWinID)
{
	try
	{
		if (g_DlgVideoView[nWinID].m_bRecordFlag != FALSE)
		{
			g_DlgVideoView[nWinID].OnStopRecord();
			g_DlgVideoView[nWinID].m_bRecordFlag = FALSE;
		}
		return TRUE;
	}
	catch(...)
	{

	}
	return FALSE;
}

//�ر���Ƶ
BOOL CloseVideoAudioByWinRecordFlag(int nWinID)
{
	try
	{
		if (g_DlgVideoView[nWinID].m_CallidVoice != -1)
		{
			g_DlgVideoView[nWinID].OnBnClickedButtonOpenvoice();
		}
		return TRUE;
	}
	catch(...)
	{

	}
	return FALSE;
}

// �õ�һ������
int GetViewCameraVideoIdleWin()
{
	int nResult = 0;

	try
	{
		for (int i = 0;i < MAXVIEWCH;i++)
		{
			nResult = CheckViewVideoIsOpen(i);
			if (nResult == 0)
				return i;
		}
		return -1;
	}
	catch(...)
	{

	}
	return -1;
}

// �õ���ǰѡ�񴰿�
int GetViewCameraVideoCurrentWin()
{
	try
	{
		if (g_pMainDlg == NULL)
			return -1;

		if(g_pMainDlg->m_iFocuseWindowID >= 0&&g_pMainDlg->m_iFocuseWindowID < MAXVIEWCH)
			return g_pMainDlg->m_iFocuseWindowID;
		
		return -1;
	}
	catch(...)
	{

	}
	return -1;
}

// ͨ������ƽ̨������ͷ��Ƶ
BOOL OpenViewCameraVideoByVideoPlatform(int nWinID,char* szCameraNum,char* szCameraName,int nDecodeTag,int nCameraStatus,int nStreamless,char* szStationName,int NodeType,void *pNodeInfo,char *szNotes)
{
	_T_NODE_INFO *pCameraNodeInfo = NULL;
	_T_NODE_PRESET_INFO *pPresetNodeInfo = NULL;

	char	szShowName[256] = {0};
	memset(szShowName, 0, sizeof(szShowName));

	RECT VideoRect;
	memset(&VideoRect,0,sizeof(VideoRect));

	int nResult = 0;
	int nVideoWinID = 0;

	try
	{
		if (nWinID < 0||nWinID >= MAXVIEWCH)
			return FALSE;

		if (szCameraNum == NULL||strlen(szCameraNum) == 0)
			return FALSE;

		if (g_pMainDlg == NULL)
			return FALSE;

		//���Ϊ�ȴ�״̬
		AfxGetApp()->DoWaitCursor(1); 

		g_VMLog.WriteVmLog("OpenViewCameraVideoByVideoPlatform-----nWinID=%d,szCameraNum=%s,szCameraName=%s,nDecodeTag=%d",nWinID,szCameraNum,szCameraName,nDecodeTag);

		do 
		{
			nResult = CheckCameraVideoIsOpen(szCameraNum,nVideoWinID);
			g_VMLog.WriteVmLog("OpenViewCameraVideoByVideoPlatform---1--nResult=%d,nWinID=%d,szCameraNum=%s",nResult,nVideoWinID,szCameraNum);
			if (nResult > 0)
			{
				if (nWinID == nVideoWinID&&nResult == 1)
				{
					//�ָ����Ϊ����״̬
					AfxGetApp()->DoWaitCursor(0);
					return UpdateViewCameraVideoShowInfo(nWinID,szCameraNum,szCameraName,nCameraStatus,nStreamless,szStationName,NodeType,pNodeInfo);
				}

				g_VMLog.WriteVmLog("OpenViewCameraVideoByVideoPlatform---2--nResult=%d,nWinID=%d,szCameraNum=%s",nResult,nVideoWinID,szCameraNum);

				if(CloseViewVideoByWinID(nVideoWinID,nResult) == FALSE)
					break;

				ClearVideoTagAndOffLineInfoDlg(nVideoWinID);
			}

			g_VMLog.WriteVmLog("OpenViewCameraVideoByVideoPlatform---3--nResult=%d,nWinID=%d,szCameraNum=%s",nResult,nVideoWinID,szCameraNum);

			nResult = CheckViewVideoIsOpen(nWinID);
			g_VMLog.WriteVmLog("OpenViewCameraVideoByVideoPlatform---1--nResult=%d,nWinID=%d",nResult,nWinID);
			if (nResult > 0)
			{
				if(CloseViewVideoByWinID(nWinID,nResult) == FALSE)
					break;

				g_VMLog.WriteVmLog("OpenViewCameraVideoByVideoPlatform---2--nResult=%d,nWinID=%d",nResult,nWinID);

				ClearVideoTagAndOffLineInfoDlg(nWinID);
			}

			g_VMLog.WriteVmLog("OpenViewCameraVideoByVideoPlatform---3--nResult=%d,nWinID=%d",nResult,nWinID);

			if (NodeType == 1)
			{
				pCameraNodeInfo = (_T_NODE_INFO *)pNodeInfo;
			}
			else if (NodeType == 2||NodeType == 3)
			{
				pPresetNodeInfo = (_T_NODE_PRESET_INFO *)pNodeInfo;
			}

			if (pPresetNodeInfo != NULL)
			{
				if (szNotes != NULL&&strlen(szNotes) != 0)
				{
					sprintf(szShowName, "%s",szNotes);
				}
				else
				{
					sprintf(szShowName, "%s-%s",szStationName,pPresetNodeInfo->preset_name);
				}
			}
			else
			{
				if (szNotes != NULL&&strlen(szNotes) != 0)
				{
					sprintf(szShowName, "%s",szNotes);
				}
				else
				{
					sprintf(szShowName, "%s-%s",szStationName,szCameraName);
				}
			}

			//���ô�������ͷ��Ϣ
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.Lock();
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nVideoViewType = 1;                                   // ͨ������ƽ̨����
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nCameraCallStatus = VM_VIEW_OUT_CAMERA_CALL_STATUS_CALLING;						                        // ��ǰͨ�����ڲ�����Ƶ
			strcpy(g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szCameraCallNum, szCameraNum);	// ����ͷ����
			strcpy(g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szCameraName, szCameraName);      // ����ͷ����
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nDecodeTag = nDecodeTag;			            // ����ͷ��������
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nCameraStatus = nCameraStatus;			    // ����ͷ״̬
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nCameraStreamless = nStreamless;			    // ����ͷ����״̬
			strcpy(g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szStationName,szStationName);         // վ������
			strcpy(g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szNotes, szShowName);
			if (pPresetNodeInfo != NULL)
			{
				strcpy(g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_preset_name,pPresetNodeInfo->preset_name);
				g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_preset_id = pPresetNodeInfo->preset_id;

				g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_line1_from_x = pPresetNodeInfo->line1_from_x;
				g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_line1_from_y = pPresetNodeInfo->line1_from_y;
				g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_line1_to_x = pPresetNodeInfo->line1_to_x;
				g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_line1_to_y = pPresetNodeInfo->line1_to_y;

				g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_line2_from_x = pPresetNodeInfo->line2_from_x;
				g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_line2_from_y = pPresetNodeInfo->line2_from_y;
				g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_line2_to_x = pPresetNodeInfo->line2_to_x;
				g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_line2_to_y = pPresetNodeInfo->line2_to_y;
			}
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.UnLock();
			
			//������Ƶ����֪ͨ�¼�
			if (g_DlgVideoView[nWinID].m_hCallResultNotifyEvent != NULL)
			{
				ResetEvent(g_DlgVideoView[nWinID].m_hCallResultNotifyEvent);
			}
			
			//��Ƶ�򿪱�־
			g_DlgVideoView[nWinID].m_Pic.m_video_opened = true;

			g_DlgVideoView[nWinID].m_Pic.GetWindowRect(&VideoRect);

			//��ʾԤ��λָʾ��
			if (pPresetNodeInfo != NULL&&NodeType == 3)
			{
				ShowVideoPresetLineInfoDlg(nWinID,&VideoRect,(void *)pPresetNodeInfo);
			}

			//��ʾ"�ѱ�עȱ��"��"ͨ���ж�"��־
			ShowVideoTagInfoDlg(nWinID,nCameraStatus,&VideoRect);
			
			//��ʾ����
			g_DlgVideoView[nWinID].ShowCurrentVideoFlow();

			//��ʾ��־��ť
			g_DlgVideoView[nWinID].m_btnTypeFlag.SetIndex(0);
			g_DlgVideoView[nWinID].m_btnTypeFlag.ShowWindow(SW_SHOW);

			//��̨����
			g_DlgVideoView[nWinID].m_bYTControl = true;

			g_DlgVideoView[nWinID].m_strStation.SetText(szShowName);

			//��ָ�����ڴ򿪱��վ�ĵ�ǰ������Ϣ
			StartVideoWinCurrentWeather(nWinID,szStationName);

			//����
			if (AppVideoMakeCallByPlatform(nWinID) < 0)
			{
				g_DlgVideoView[nWinID].m_strStation.SetText("����");

				//��������
				g_DlgVideoView[nWinID].HideCurrentVideoFlow();

				//�����ʾ��Ϣ
				ClearVideoPresetLineAndTagInfoDlg(nWinID);

				//ֹͣ������Ϣ��ʾ
				StopVideoWinCurrentWeather(nWinID);

				//ֹͣ¼��
				CloseVideoRecordByWinRecordFlag(nWinID);

				//ֹͣ��Ƶ
				CloseVideoAudioByWinRecordFlag(nWinID);

				//�����Ϣ,ˢ�´���
				g_DlgVideoView[nWinID].CloseViewChannel();
				break;
			}

			//�ȴ���Ƶ��
			if (g_DlgVideoView[nWinID].m_hCallResultNotifyEvent != NULL)
			{
				WaitForSingleObject(g_DlgVideoView[nWinID].m_hCallResultNotifyEvent,1000*2);
			}

			//�ָ����Ϊ����״̬
			AfxGetApp()->DoWaitCursor(0);
			
			return TRUE;

		} while (FALSE);

		//�ָ����Ϊ����״̬
		AfxGetApp()->DoWaitCursor(0);

		return FALSE;
	}
	catch(...)
	{

	}
	return FALSE;
}

// ֱ��ͨ��ǰ���豸������ͷ��Ƶ
BOOL OpenViewCameraVideoByDirectDevice(int nWinID,char* szCameraNum,char* szCameraName,int nDvrType,int nCameraStatus,int nStreamless,char* szStationName,int NodeType,void *pNodeInfo,char *szNotes)
{
	_T_NODE_INFO *pCameraNodeInfo = NULL;
	_T_NODE_PRESET_INFO *pPresetNodeInfo = NULL;

	_T_DVR_INFO * pDvrInfo = NULL;
	_T_CAMERA_INFO *pCameraInfo = NULL;

	char	szShowName[256] = {0};
	memset(szShowName, 0, sizeof(szShowName));

	RECT VideoRect;
	memset(&VideoRect,0,sizeof(VideoRect));

	int nResult = 0;
	int nVideoWinID = 0;

	try
	{
		if (nWinID < 0||nWinID >= MAXVIEWCH)
			return FALSE;

		if (pNodeInfo == NULL||szCameraNum == NULL||strlen(szCameraNum) == 0)
			return FALSE;

		if (g_pMainDlg == NULL)
			return FALSE;

		//���Ϊ�ȴ�״̬
		AfxGetApp()->DoWaitCursor(1); 

		g_VMLog.WriteVmLog("OpenViewCameraVideoByDirectDevice-----nWinID=%d,szCameraNum=%s,szCameraName=%s,nDvrType=%d",nWinID,szCameraNum,szCameraName,nDvrType);

		do 
		{
			nResult = CheckCameraVideoIsOpen(szCameraNum,nVideoWinID);
			g_VMLog.WriteVmLog("OpenViewCameraVideoByDirectDevice---1--nResult=%d,nWinID=%d,szCameraNum=%s",nResult,nVideoWinID,szCameraNum);
			if (nResult > 0)
			{
				if (nWinID == nVideoWinID&&nResult == 2)
				{
					//�ָ����Ϊ����״̬
					AfxGetApp()->DoWaitCursor(0);
					return UpdateViewCameraVideoShowInfo(nWinID,szCameraNum,szCameraName,nCameraStatus,nStreamless,szStationName,NodeType,pNodeInfo);
				}

				g_VMLog.WriteVmLog("OpenViewCameraVideoByDirectDevice--2---nResult=%d,nWinID=%d,szCameraNum=%s",nResult,nVideoWinID,szCameraNum);

				if(CloseViewVideoByWinID(nVideoWinID,nResult) == FALSE)
					break;

				ClearVideoTagAndOffLineInfoDlg(nVideoWinID);
			}

			nResult = CheckViewVideoIsOpen(nWinID);
			g_VMLog.WriteVmLog("OpenViewCameraVideoByDirectDevice--1---nResult=%d,nWinID=%d",nResult,nWinID);
			if (nResult > 0)
			{
				if(CloseViewVideoByWinID(nWinID,nResult) == FALSE)
					break;

				g_VMLog.WriteVmLog("OpenViewCameraVideoByDirectDevice--2---nResult=%d,nWinID=%d",nResult,nWinID);

				ClearVideoTagAndOffLineInfoDlg(nWinID);
			}

			g_VMLog.WriteVmLog("OpenViewCameraVideoByDirectDevice--3---nResult=%d,nWinID=%d",nResult,nWinID);


			if (NodeType == 1)
			{
				pCameraNodeInfo = (_T_NODE_INFO *)pNodeInfo;
				pCameraInfo = &pCameraNodeInfo->camera_info;
			}
			else if (NodeType == 2||NodeType == 3)
			{
				pPresetNodeInfo = (_T_NODE_PRESET_INFO *)pNodeInfo;
				pCameraInfo = &pPresetNodeInfo->camera_info;
			}
			else
			{
				break;
			}

			if (pPresetNodeInfo != NULL)
			{
				if (szNotes != NULL&&strlen(szNotes) != 0)
				{
					sprintf(szShowName, "%s",szNotes);
				}
				else
				{
					sprintf(szShowName, "%s-%s",szStationName,pPresetNodeInfo->preset_name);
				}
			}
			else
			{
				if (szNotes != NULL&&strlen(szNotes) != 0)
				{
					sprintf(szShowName, "%s",szNotes);
				}
				else
				{
					sprintf(szShowName, "%s-%s",szStationName,szCameraName);
				}
			}

			//DVR��Ϣ
			pDvrInfo = &pCameraInfo->dvr_info;

			//���ô�������ͷ��Ϣ
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.Lock();
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nVideoViewType = 2;                                   // ֱ��ͨ��ǰ���豸����Ƶ
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nCameraCallStatus = VM_VIEW_OUT_CAMERA_CALL_STATUS_CALLING;				// ��ǰͨ�����ڲ�����Ƶ                              
			strcpy(g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szCameraCallNum, szCameraNum);	// ����ͷ����
			strcpy(g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szCameraName, szCameraName);      // ����ͷ����
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nDvrType = nDvrType;			                        // ����ͷ���볧������
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nCameraStatus = nCameraStatus;			    // ����ͷ״̬
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nCameraStreamless = nStreamless;              // ����ͷ����״̬
			strcpy(g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szStationName,szStationName);         // վ������
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nDvrId = pDvrInfo->dvr_id;
			strcpy_s(g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szDvrIP,sizeof(g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szDvrIP),pDvrInfo->dvr_ip);
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nDvrPort = pDvrInfo->dvr_port;
			strcpy_s(g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szDvrUserName,sizeof(g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szDvrUserName),pDvrInfo->dvr_user);
			strcpy_s(g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szDvrPassword,sizeof(g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szDvrPassword),pDvrInfo->dvr_password);
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nCameraChannel = pCameraInfo->channel;
			strcpy(g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szNotes, szShowName);
			if (pPresetNodeInfo != NULL)
			{
				strcpy(g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_preset_name,pPresetNodeInfo->preset_name);
				g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_preset_id = pPresetNodeInfo->preset_id;

				g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_line1_from_x = pPresetNodeInfo->line1_from_x;
				g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_line1_from_y = pPresetNodeInfo->line1_from_y;
				g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_line1_to_x = pPresetNodeInfo->line1_to_x;
				g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_line1_to_y = pPresetNodeInfo->line1_to_y;

				g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_line2_from_x = pPresetNodeInfo->line2_from_x;
				g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_line2_from_y = pPresetNodeInfo->line2_from_y;
				g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_line2_to_x = pPresetNodeInfo->line2_to_x;
				g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_line2_to_y = pPresetNodeInfo->line2_to_y;
			}
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.UnLock();

			//������Ƶ����֪ͨ�¼�
			if (g_DlgVideoView[nWinID].m_hCallResultNotifyEvent != NULL)
			{
				ResetEvent(g_DlgVideoView[nWinID].m_hCallResultNotifyEvent);
			}

			//��Ƶ�򿪱�־
			g_DlgVideoView[nWinID].m_Pic.m_video_opened = true;
			g_DlgVideoView[nWinID].m_Pic.GetWindowRect(&VideoRect);

			//��ʾԤ��λָʾ��
			if (pPresetNodeInfo != NULL&&NodeType == 3)
			{
				ShowVideoPresetLineInfoDlg(nWinID,&VideoRect,(void *)pPresetNodeInfo);
			}

			//��ʾ"�ѱ�עȱ��"��"ͨ���ж�"��־
			ShowVideoTagInfoDlg(nWinID,nCameraStatus,&VideoRect);

			//��ʾ����
			g_DlgVideoView[nWinID].ShowCurrentVideoFlow();

			//��ʾ��־��ť
			g_DlgVideoView[nWinID].m_btnTypeFlag.SetIndex(0);
			g_DlgVideoView[nWinID].m_btnTypeFlag.ShowWindow(SW_SHOW);
			g_DlgVideoView[nWinID].m_btnTypeFlag.Invalidate(TRUE);

			//��̨����
			g_DlgVideoView[nWinID].m_bYTControl = true;

			g_DlgVideoView[nWinID].m_strStation.SetText(szShowName);

			Sleep(200);

			//��ָ�����ڴ򿪱��վ�ĵ�ǰ������Ϣ
			StartVideoWinCurrentWeather(nWinID,szStationName);

			if (nDvrType == DEVTYPE_AXIS&&g_pMainDlg != NULL)//��Ѷʿʱ
			{
				g_pMainDlg->PostMessage(WM_DEVICE_VIDEO_STATUS_ONLINE_NOTIFY_MESSAGE,nWinID,NULL);
			}

			nResult = AppVideoMakeCallByDirectDevice(nWinID);

			if (nResult < 0)//����ʧ��
			{
				ClearViewPlatformAndDeviceInfoByWinID(nWinID);

				g_DlgVideoView[nWinID].m_strStation.SetText("����");

				if (g_pMainDlg != NULL)
				{
					g_pMainDlg->SetTimer(TIMER_VIDEO_ERROR_REASON_VIDEO_CHANNEL_0_TIMER+nWinID,2*1000,NULL);
				}
				break;
			}

			//�ȴ���Ƶ��
			if (g_DlgVideoView[nWinID].m_hCallResultNotifyEvent != NULL)
			{
				WaitForSingleObject(g_DlgVideoView[nWinID].m_hCallResultNotifyEvent,1000*2);
			}

			//�ָ����Ϊ����״̬
			AfxGetApp()->DoWaitCursor(0);

			return TRUE;

		} while (FALSE);

		//�ָ����Ϊ����״̬
		AfxGetApp()->DoWaitCursor(0);

		return FALSE;
	}
	catch(...)
	{

	}
	return FALSE;
}

BOOL UpdateViewCameraVideoShowInfo(int nWinID,char* szCameraNum,char* szCameraName,int nCameraStatus,int nStreamless,char* szStationName,int NodeType,void *pNodeInfo,char *szNotes)
{
	_T_NODE_INFO *pCameraNodeInfo = NULL;
	_T_NODE_PRESET_INFO *pPresetNodeInfo = NULL;

	char	szShowName[256] = {0};
	memset(szShowName, 0, sizeof(szShowName));

	RECT VideoRect;
	memset(&VideoRect,0,sizeof(VideoRect));

	int nResult = 0;
	int nVideoWinID = 0;

	try
	{
		if (nWinID < 0||nWinID >= MAXVIEWCH)
			return FALSE;

		if (szCameraNum == NULL||strlen(szCameraNum) == 0)
			return FALSE;

		if (g_pMainDlg == NULL)
			return FALSE;

		//���Ϊ�ȴ�״̬
		AfxGetApp()->DoWaitCursor(1); 

		do 
		{
			//��ʾ����
			g_DlgVideoView[nWinID].ShowCurrentVideoFlow();

			//��ʾ��־��ť
			g_DlgVideoView[nWinID].m_btnTypeFlag.SetIndex(0);
			g_DlgVideoView[nWinID].m_btnTypeFlag.ShowWindow(SW_SHOW);

			//��̨����
			g_DlgVideoView[nWinID].m_bYTControl = true;

			if (NodeType == 1)
			{
				pCameraNodeInfo = (_T_NODE_INFO *)pNodeInfo;
			}
			else if (NodeType == 2||NodeType == 3)
			{
				pPresetNodeInfo = (_T_NODE_PRESET_INFO *)pNodeInfo;
			}

			if (pPresetNodeInfo != NULL)
			{
				if (szNotes != NULL&&strlen(szNotes) != 0)
				{
					sprintf(szShowName, "%s",szNotes);
				}
				else
				{
					sprintf(szShowName, "%s-%s",szStationName,pPresetNodeInfo->preset_name);
				}	
			}
			else
			{
				if (szNotes != NULL&&strlen(szNotes) != 0)
				{
					sprintf(szShowName, "%s",szNotes);
				}
				else
				{
					sprintf(szShowName, "%s-%s",szStationName,szCameraName);
				}
			}

			//���ô�������ͷ��Ϣ
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.Lock();
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nCameraStatus = nCameraStatus;			    // ����ͷ״̬
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nCameraStreamless = nStreamless;			    // ����ͷ����״̬
			strcpy(g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szNotes, szShowName);
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.UnLock();

			Sleep(200);

			//��ָ�����ڴ򿪱��վ�ĵ�ǰ������Ϣ
			StartVideoWinCurrentWeather(nWinID,szStationName);

			g_DlgVideoView[nWinID].m_Pic.GetWindowRect(&VideoRect);

			//��ʾԤ��λָʾ��
			if (pPresetNodeInfo != NULL&&NodeType == 3)
			{
				ShowVideoPresetLineInfoDlg(nWinID,&VideoRect,(void *)pPresetNodeInfo);
			}

			//��ʾ"�ѱ�עȱ��"��"ͨ���ж�"��־
			ShowVideoTagInfoDlg(nWinID,nCameraStatus,&VideoRect);

			//�ָ����Ϊ����״̬
			AfxGetApp()->DoWaitCursor(0);

			return TRUE;

		} while (FALSE);

		//�ָ����Ϊ����״̬
		AfxGetApp()->DoWaitCursor(0);

		return FALSE;
	}
	catch(...)
	{

	}
	return FALSE;
}

BOOL StartVideoWinCurrentWeather(int nWinID,char *szStationName)
{
	BOOL bResult = FALSE;

	try
	{
		if (nWinID < 0||nWinID >= MAXVIEWCH)
			return FALSE;

		if (g_pMainDlg == NULL)
			return FALSE;

		//��������Ѳ���˹��Զ�Ѳ��ʱ������ѯ��ǰ������Ϣ
		if (g_TuneCycle_MehtodInfo.bState == true||g_VideoPageViewInfo.nStatus == AUTOVIDEO_PAGEVIEW_STATUS_RUNNING)
			return FALSE;

		int nIndex = g_pMainDlg->GetStationIndexByStationName(szStationName);
		if (nIndex >= 0)
		{
			if (g_nCurrentWeatherDataWinInfoTypeFlag != 0)
			{
				if(strlen(g_tStation_Info[nIndex].station_code_weather) > 2)
				{
					int nStationId = atoi(g_tStation_Info[nIndex].station_code_weather);
					bResult = g_pMainDlg->StartVideoWinWeatherCurrentInfo(nWinID,"jsepc@dp",nStationId,4570);
				}
			}
			else
			{
				if (strlen(g_tStation_Info[nIndex].station_code_microclimate) > 2)
				{
					int nComCode = atoi(g_tStation_Info[nIndex].station_code_microclimate);
					bResult = g_pMainDlg->StartVideoWinMicroWeatherCurrentInfo(nWinID,"jsepc@dp",nComCode,"SUBSTATION",1560);
				}
			}
			g_DlgVideoView[nWinID].m_strWeather.Invalidate(TRUE);
		}
		return bResult;
	}
	catch(...)
	{

	}
	return FALSE;
}

BOOL StopVideoWinCurrentWeather(int nWinID)
{
	try
	{
		if (nWinID < 0||nWinID >= MAXVIEWCH)
			return FALSE;

		if (g_pMainDlg == NULL)
			return FALSE;

		if (g_nCurrentWeatherDataWinInfoTypeFlag != 0)
			return g_pMainDlg->StopVideoWinWeatherCurrentInfo(nWinID);
		else
			return g_pMainDlg->StopVideoWinMicroWeatherCurrentInfo(nWinID);

		return FALSE;
	}
	catch(...)
	{

	}
	return FALSE;
}

BOOL ShowVideoPresetLineInfoDlg(int nWinID,RECT *pRect,void *pNodeInfo)
{
	_T_NODE_PRESET_INFO * pPresetNodeInfo = NULL;

	try
	{
		if (pRect == NULL||pNodeInfo == NULL)
			return FALSE;

		if (nWinID < 0||nWinID >= MAXVIEWCH)
			return FALSE;

		if (g_pMainDlg == NULL)
			return FALSE;

		pPresetNodeInfo = (_T_NODE_PRESET_INFO *)pNodeInfo;

		g_DlgVideoView[nWinID].SetLineInfo(
			pPresetNodeInfo->line1_from_x,pPresetNodeInfo->line1_from_y,
			pPresetNodeInfo->line1_to_x,pPresetNodeInfo->line1_to_y,
			pPresetNodeInfo->line2_from_x,pPresetNodeInfo->line2_from_y,
			pPresetNodeInfo->line2_to_x,pPresetNodeInfo->line2_to_y);

		g_pMainDlg->ModifyVideoInfoDlg(nWinID,pRect,TRUE,
			pPresetNodeInfo->line1_from_x,pPresetNodeInfo->line1_from_y,
			pPresetNodeInfo->line1_to_x,pPresetNodeInfo->line1_to_y,
			pPresetNodeInfo->line2_from_x,pPresetNodeInfo->line2_from_y,
			pPresetNodeInfo->line2_to_x,pPresetNodeInfo->line2_to_y);

		return TRUE;
	}
	catch(...)
	{

	}
	return FALSE;
}

//���Ԥ��λ������Ϣ
BOOL ClearVideoPresetLineInfoDlg(int nWinID)
{
	try
	{
		if (nWinID < 0||nWinID >= MAXVIEWCH)
			return FALSE;

		g_VideoInfoDlg[nWinID].ClearVideoArrowTextInfo();
		g_VideoInfoDlg[nWinID].Invalidate(TRUE);
		g_VideoInfoDlg[nWinID].ShowWindow(SW_HIDE);

		return TRUE;
	}
	catch(...)
	{

	}
	return FALSE;
}

//�����Ǻ��жϻ�����Ϣ
BOOL ClearVideoTagAndOffLineInfoDlg(int nWinID)
{
	try
	{
		if (nWinID < 0||nWinID >= MAXVIEWCH)
			return FALSE;

		g_VideoTagInfoDlg[nWinID].m_bVideoInfoShowFlag = FALSE;
		g_VideoTagInfoDlg[nWinID].Invalidate(TRUE);
		g_VideoTagInfoDlg[nWinID].ShowWindow(SW_HIDE);

		return TRUE;
	}
	catch(...)
	{

	}
	return FALSE;
}

BOOL ClearVideoPresetLineAndTagInfoDlg(int nWinID)
{
	try
	{
		if (nWinID < 0||nWinID >= MAXVIEWCH)
			return FALSE;

		g_VideoInfoDlg[nWinID].ClearVideoArrowTextInfo();
		g_VideoInfoDlg[nWinID].Invalidate(TRUE);
		g_VideoInfoDlg[nWinID].ShowWindow(SW_HIDE);

		g_VideoTagInfoDlg[nWinID].m_bVideoInfoShowFlag = FALSE;
		g_VideoTagInfoDlg[nWinID].Invalidate(TRUE);
		g_VideoTagInfoDlg[nWinID].ShowWindow(SW_HIDE);

		return TRUE;
	}
	catch(...)
	{

	}
	return FALSE;
}

BOOL ShowVideoTagInfoDlg(int nWinID,int nCameraStatus,RECT *pRect)
{
	try
	{
		if (nWinID < 0||nWinID >= MAXVIEWCH)
			return FALSE;

		if (pRect == NULL)
			return FALSE;

		if (g_pMainDlg == NULL)
			return FALSE;

		if (nCameraStatus == 0)
		{
			//g_VideoTagInfoDlg[nWinID].SetVideoInfoCurrentIndex(0);
			//g_pMainDlg->ModifyVideoTagInfoDlg(nWinID,pRect,TRUE);
		}
		else if (nCameraStatus == 1)
		{
			g_VideoTagInfoDlg[nWinID].SetVideoInfoCurrentIndex(1);
			g_VideoTagInfoDlg[nWinID].m_bVideoInfoShowFlag = FALSE;
			g_pMainDlg->ModifyVideoTagInfoDlg(nWinID,pRect,FALSE);
		}
		else if (nCameraStatus == 2)
		{
			g_VideoTagInfoDlg[nWinID].SetVideoInfoCurrentIndex(2);
			g_pMainDlg->ModifyVideoTagInfoDlg(nWinID,pRect,TRUE);
		}
		else if (nCameraStatus == 3)
		{
			g_VideoTagInfoDlg[nWinID].SetVideoInfoCurrentIndex(2);
			g_pMainDlg->ModifyVideoTagInfoDlg(nWinID,pRect,TRUE);
		}

		return TRUE;
	}
	catch(...)
	{

	}
	return FALSE;
}

// ͨ������ƽ̨��������Ƶ����
int AppVideoMakeCallByPlatform(int nWinID)
{
	int nCallID = -1;
	int nDecodeTag = 0;
	char szDecodeTag[64] = {0};
	char szCallUrl[256] = {0};
	char szCallNum[32] = {0};
	
	try
	{
		if (nWinID < 0|| nWinID >= MAXVIEWCH)
			return -1;

		memset(szDecodeTag,0,sizeof(szDecodeTag));
		memset(szCallUrl,0,sizeof(szCallUrl));
		memset(szCallNum,0,sizeof(szCallNum));

		g_pCallAPI->ProduceCID(&nCallID);
		if (nCallID < 0) 
			return -1;

		app_CurUacCh = AppGetIdleUacID();
		if (app_CurUacCh < 0)
			return -1;

		app_UacCh[app_CurUacCh].nSipCallID = nCallID;

		g_DlgVideoView[nWinID].m_VideoViewOutInfo.Lock();
		g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nCallid = nCallID;
		nDecodeTag = g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nDecodeTag;
		strcpy_s(szCallNum,sizeof(szCallNum),g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szCameraCallNum);
		g_DlgVideoView[nWinID].m_VideoViewOutInfo.UnLock();

		if (nDecodeTag <= 0||strlen(szCallNum) == 0)
			return -1;

		sprintf_s(szDecodeTag,"%d",nDecodeTag);
		sprintf(szCallUrl, "%s@%s:%d",szCallNum, app_RegCh.reg_server,app_RegCh.reg_serverport);

		g_pCallAPI->Make(nCallID,szCallUrl, szDecodeTag, NULL,app_RegCh.reg_user, (void*)&g_tLocalAudio,0,"CIF=1;4CIF=1;F=1;K=1",0,0,0,0,2);

		return 0;
	}
	catch(...)
	{

	}
	return -1;
}

void AppHangupCallIdByPlatform(int nCallId)
{
	try
	{
		if (nCallId >= 0&&g_pCallAPI != NULL)
		{
			g_pCallAPI->Hangup(nCallId);
		}
	}
	catch(...)
	{

	}
}

// ֱ����ǰ���豸��������Ƶ����
int AppVideoMakeCallByDirectDevice(int nWinID)
{
	int nResult = 0;
	int nID = 0;

	int nDvrType = 0;
	int nDvrId = -1;
	int nDvrPort = 0;
	int nChannel = -1;
	char szCallNum[64] = {0};
	char szDvrIP[32] = {0};
	char szUser[64] = {0};
	char szPassword[64] = {0};
	char szUrl[1024] = {0};

	try
	{
		if (nWinID < 0|| nWinID >= MAXVIEWCH)
			return -1;

		memset(szCallNum,0,sizeof(szCallNum));
		memset(szDvrIP,0,sizeof(szDvrIP));
		memset(szUser,0,sizeof(szUser));
		memset(szPassword,0,sizeof(szPassword));

		g_DlgVideoView[nWinID].m_VideoViewOutInfo.Lock();
		nID = GetID_DevSdk();
		g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nVideoSdkId = nID;
		nDvrType = g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nDvrType;
		nDvrId = g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nDvrId;
		nDvrPort = g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nDvrPort;
		nChannel = g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nCameraChannel;
		strcpy_s(szCallNum,sizeof(szCallNum),g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szCameraCallNum);
		strcpy_s(szDvrIP,sizeof(szDvrIP),g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szDvrIP);
		strcpy_s(szUser,sizeof(szUser),g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szDvrUserName);
		strcpy_s(szPassword,sizeof(szPassword),g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_szDvrPassword);
		g_DlgVideoView[nWinID].m_VideoViewOutInfo.UnLock();

		g_VMLog.WriteVmLog("OpenVideo_DevSdk start szDvrIP:%s ,nDvrType:%d,nDvrId:%d,nChannel:%d,nID=%d,nWinID=%d",szDvrIP,nDvrType,nDvrId,nChannel,nID,nWinID);

		if (strlen(szCallNum) == 0||strlen(szDvrIP) == 0||nDvrPort <= 0
			||nChannel < 0||strlen(szUser) == 0||strlen(szPassword) == 0)
		{
			return -1;
		}
		
		if(nDvrType == DEVTYPE_AXIS)
		{
			sprintf(szUrl,"axrtsphttp://%s:%d/mpeg4/media.amp",szDvrIP,nDvrPort);
			g_DlgVideoView[nWinID].m_AxisView.Stop();

			// Set username and password
			g_DlgVideoView[nWinID].m_AxisView.put_MediaUsername(szUser);
			g_DlgVideoView[nWinID].m_AxisView.put_MediaPassword(szPassword);

			// Set the media URL and the media type
			g_DlgVideoView[nWinID].m_AxisView.put_MediaURL(szUrl);

			// Starts the download of the mpeg4 stream from the Axis camera/video server
			g_DlgVideoView[nWinID].m_AxisView.Play(); 

			g_DlgVideoView[nWinID].m_AxisView.ShowWindow(SW_SHOW);
			g_DlgVideoView[nWinID].m_Pic.ShowWindow(SW_HIDE);
			g_DlgVideoView[nWinID].Invalidate();
			nResult = 0;
		}
		else
		{
			//nResult = g_pstruDevPlayVideoSdkFuns.fun_OpenVideo_DevSdk(szDvrIP,nDvrPort,szUser,szPassword,nDvrType,nDvrId,nChannel,nID,g_DlgVideoView[nWinID].m_Pic.GetSafeHwnd());
			nResult = OpenVideo_DevSdk(szDvrIP,nDvrPort,szUser,szPassword,nDvrType,nDvrId,nChannel,nID,g_DlgVideoView[nWinID].m_Pic.GetSafeHwnd());
		}
		
		g_VMLog.WriteVmLog("OpenVideo_DevSdk end");

		if (nResult == OPENVIDEO_SUCCESS)
			return 0;

		return -1;
	}
	catch(...)
	{
		g_VMLog.WriteVmLog("AppVideoMakeCallByDirectDevice�쳣!");
	}
	return -1;
}

int AppHangupCallByDirectDevice(int nID)
{
	try
	{
		if (nID < 0)
			return -1;

		g_VMLog.WriteVmLog("AppHangupCallByDirectDevice-------nID=%d",nID);
		
		CloseVideo_DevSdk(nID);

		return 0;
	}
	catch(...)
	{

	}
	return -1;
}

int AppGetCameraDvrType(char *szType)
{
	try
	{
		if (szType == NULL||strlen(szType) == 0)
			return -1;

		if (stricmp(szType,"Hik") == 0||stricmp(szType,"HikRVU") == 0||stricmp(szType,"HikMOBO") == 0)
			return DEVTYPE_HK;
		else if (stricmp(szType,"DH") == 0||stricmp(szType,"DHRVU") == 0||stricmp(szType,"DHMOBO") == 0)
			return DEVTYPE_DH;
		else if (stricmp(szType,"DL") == 0||stricmp(szType,"DLRVU") == 0||stricmp(szType,"DLMOBO") == 0)
			return DEVTYPE_DL;
		else if (stricmp(szType,"MOBO1") == 0)
			return DEVTYPE_MOBOTIX;
		else if (stricmp(szType,"AXIS") == 0)
			return DEVTYPE_AXIS;
		else
			return -1;
	}
	catch(...)
	{

	}
	return -1;
}

//ȡ�����߶�������
BOOL AppCancelRestartCameraVideo(int nWinID)
{
	try
	{
		if (nWinID < 0||nWinID >= MAXVIEWCH)
			return FALSE;

		if (g_pMainDlg != NULL)
			g_pMainDlg->KillTimer(TIMER_VIDEO_ERROR_REASON_VIDEO_CHANNEL_0_TIMER+nWinID);

		g_DlgVideoView[nWinID].m_VideoViewOutInfo.Lock();
		g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nSetProblemCameraFlag = 0;
		g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nProblemRestartCount = 0;
		g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_bSetNrDecodeProblemFlag = FALSE;
		g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nNrDecodeProblemRestartCount = 0;	
		g_DlgVideoView[nWinID].m_VideoViewOutInfo.UnLock();

		return TRUE;
	}
	catch(...)
	{

	}

	return FALSE;
}

//���ö��߶�������
BOOL AppSetRestartCameraVideo(int nWinID)
{
	try
	{
		if (nWinID < 0||nWinID >= MAXVIEWCH)
			return FALSE;

		g_DlgVideoView[nWinID].m_VideoViewOutInfo.Lock();

		if (g_nClientVideoLinkType == 0)
		{
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nProblemRestartCount = 1;//��������
		}
		else if (g_nClientVideoLinkType == 1)
		{
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nProblemRestartCount = 1;//��������
		}
		else if (g_nClientVideoLinkType == 2)
		{
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nProblemRestartCount = 1;//��������
		}
		else if (g_nClientVideoLinkType == 3)
		{
			g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nProblemRestartCount = 2;//��������
		}

		g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nSetProblemCameraFlag = 1;//�����豸����

		g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_nNrDecodeProblemRestartCount = 2;//��������ƽ̨�������������Դ���
		g_DlgVideoView[nWinID].m_VideoViewOutInfo.m_bSetNrDecodeProblemFlag = FALSE;//����ƽ̨�����������־

		g_DlgVideoView[nWinID].m_VideoViewOutInfo.UnLock();

		return TRUE;
	}
	catch(...)
	{

	}

	return FALSE;

}

void AppTestAndDisplayCallThreadIDInfo(char *szInfo)
{
	try
	{
		DWORD dwThreadId = GetCurrentThreadId();

		if (szInfo != NULL&&strlen(szInfo) > 0)
		{
			g_VMLog.WriteVmLog("AppTestAndDisplayCallThreadIDInfo--�߳�ID=%d--%s",dwThreadId,szInfo);
		}
		else
		{
			g_VMLog.WriteVmLog("AppTestAndDisplayCallThreadIDInfo--�߳�ID=%d",dwThreadId);
		}
	}
	catch(...)
	{

	}
}

//��������ʱ��
void AppTestAndDisplayTickCountInfo(char *szInfo)
{
	try
	{
		static DWORD dwOldTickCount = 0;
		DWORD dwTickCount = GetTickCount();

		if (szInfo != NULL&&strlen(szInfo) > 0)
		{
			g_VMLog.WriteVmLog("AppTestAndDisplayTickCountInfo--TickCount=%d--Span=%d--%s",dwTickCount,dwTickCount-dwOldTickCount,szInfo);
		}
		else
		{
			g_VMLog.WriteVmLog("AppTestAndDisplayTickCountInfo--TickCount=%d--Span=%d",dwTickCount,dwTickCount-dwOldTickCount);
		}

		dwOldTickCount = dwTickCount;
	}
	catch(...)
	{

	}
}