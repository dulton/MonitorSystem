#include "StdAfx.h"
#include <process.h>
#include "SipStateHandler.h"
#include "SipMediaHandler.h"
#include "SpsParse.h"
#include "GWPlayInfoDef.h"
#include "VEMCUCtl.h"
#include "VEMCUCtlDlg.h"
#include "SipCall.h"
#include "VMLog.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


/***************************************����״̬������غ���***********************************/


/********************************************************************************
*  
*  Caller(����),Callee(����)
*  E_RT_CALL_STATE_UNDEFINED = -1(��Ч)
*	����UNDEFINED״̬������
*
*********************************************************************************/
BOOL SipCallStatusUndefinedHandler(unsigned int nCID,E_RtCallStateReason eReason,void* pAppData)
{
	return TRUE;
}


/********************************************************************************
*
*  Caller(����),Callee(����)
*  E_RT_CALL_STATE_IDLE = 0(����)
*	����IDLE״̬������
*
*********************************************************************************/
BOOL SipCallStatusIdleHandler(unsigned int nCID,E_RtCallStateReason eReason,void* pAppData)
{
	return TRUE;
}


/********************************************************************************
*
*  Caller(����)
*  E_RT_CALL_STATE_INVITING = 3(����)
*	����INVITING״̬������
*
*********************************************************************************/
BOOL SipCallStatusInvitingHandler(unsigned int nCID,E_RtCallStateReason eReason,void* pAppData)
{
	return TRUE;
}


/********************************************************************************
*
*   Callee(����)
*   E_RT_CALL_STATE_OFFERING = 6(����)
*	����OFFERING״̬������
*
*********************************************************************************/
BOOL SipCallStatusOfferingHandler(unsigned int nCID,E_RtCallStateReason eReason,void* pAppData)
{
	return TRUE;
}


/********************************************************************************
*
*   Caller(����)
*   E_RT_CALL_STATE_PROCEEDING	= 4(Զ�˴����� Todo: ���Ӳ���״̬)
*	����PROCEEDING״̬������
*
*********************************************************************************/
BOOL SipCallStatusProceedingHandler(unsigned int nCID,E_RtCallStateReason eReason,void* pAppData)
{
	return TRUE;
}


/********************************************************************************
*
*   Callee(����)
*   E_RT_CALL_STATE_RECV_CALL= 5(�յ�����,@ע���޷��ٸ�״̬�¾ܾ�����)
*	����RECV_CALL״̬������
*
*********************************************************************************/
BOOL SipCallStatusRecvCallHandler(unsigned int nCID,E_RtCallStateReason eReason,void* pAppData)
{
	return TRUE;
}


/********************************************************************************
*
*  callee(����)
*  E_RT_CALL_STATE_WAIT_TALKING= 7(�ȴ�����ͨ��)
*	����WAIT_TALKING״̬������
*
*********************************************************************************/
BOOL SipCallStatusWaitTalkHandler(unsigned int nCID,E_RtCallStateReason eReason,void* pAppData)
{
	return TRUE;
}


/********************************************************************************
*
*   Caller(����),Callee(����)
*   E_RT_CALL_STATE_TALKING = 1(ͨ��)
*	����TALKING״̬������
*
*********************************************************************************/
BOOL SipCallStatusTalkingHandler(unsigned int nCID,E_RtCallStateReason eReason,void* pAppData)
{
	int nRetCode = 0;
	BOOL bResult = FALSE;
	int nUACID = -1;		//�Լ�������ʱ��ID��
	int nUASID = -1;		//�Լ��Ǳ���ʱ��ID��
	int nAudioPayload = -1;
	int nVideoPayload = -1;
	char szFmtpConfig[1024] = {0};
	E_RtDirection	eDirection; //���з���
	int nActualLen = 0;
	char *pSPS = NULL;
	char newSps[512] = {0};
	int    newSpsLen = 0;
	HANDLE hDecodeHandle = NULL;
	int nIndex = -1;

	char	szCalleeUser[50] = {0};
	char	szCalleeHost[50] = {0};
	char	szCallerUser[50] = {0};
	char	szCallerHost[50] = {0};

	nRetCode = g_pCallAPI->GetDirection(nCID, &eDirection);
	if(nRetCode != E_RT_OK)
	{
		g_pCallAPI->Hangup(nCID);
		return FALSE;
	}

	if(eDirection == E_RT_DIRECTION_OUT)
	{
		g_pCallAPI->GetCalleeUser(nCID,szCalleeUser,50,&nActualLen);
		g_pCallAPI->GetCalleeHost(nCID,szCalleeHost,50,&nActualLen);
	}
	else if (eDirection == E_RT_DIRECTION_IN)
	{
		g_pCallAPI->GetCallerUser(nCID,szCallerUser,50,&nActualLen);
		g_pCallAPI->GetCallerHost(nCID,szCallerHost,50,&nActualLen);
	}

	// ��ȡpayloadֵ
	g_pCallAPI->GetCurrentPayload(nCID,E_RT_MEDIA_TYPE_AUDIO,&nAudioPayload);
	g_pCallAPI->GetCurrentPayload(nCID,E_RT_MEDIA_TYPE_VIDEO,&nVideoPayload);

	// ��ȡfmtpֵ�����ڳ�ʼ�����Ž�����
	g_pCallAPI->GetFmtpConfig(nCID,szFmtpConfig,1024);

	g_VMLog.WriteVmLog("��������--0:nCID = %d,eReason = %d",nCID,eReason);
	
	//bResult = IsStandardH264Info(szFmtpConfig);
	if (nVideoPayload != 100)//100Ϊ��׼h264
	{
		pSPS = strstr(szFmtpConfig,"sprop-parameter-sets=");
		if (pSPS == NULL) return FALSE;
		
		pSPS += strlen("sprop-parameter-sets=");

		g_VMLog.WriteVmLog("pSPS=%s",pSPS);

		newSpsLen = SwitchSPS(pSPS,(BYTE *)newSps);

		//////////////////////////////////////////////////////////////////////////
		SIP_STATE_HANDLER_INFO SipStateHandlerInfo;
		memset(&SipStateHandlerInfo,0,sizeof(SipStateHandlerInfo));

		SipStateHandlerInfo.nCID = nCID;
		SipStateHandlerInfo.nDirection = (int)eDirection;
		strcpy_s(SipStateHandlerInfo.szCallerNum,sizeof(SipStateHandlerInfo.szCallerNum),szCallerUser);
		strcpy_s(SipStateHandlerInfo.szCalleeNum,sizeof(SipStateHandlerInfo.szCalleeNum),szCalleeUser);
		memcpy(SipStateHandlerInfo.Sps,newSps,newSpsLen);
		SipStateHandlerInfo.nSpsLen = newSpsLen;
		SipStateHandlerInfo.nVideoPayload = nVideoPayload;
		SipStateHandlerInfo.nReason = (int)eReason;
		SipStateHandlerInfo.pAppData = pAppData;

		g_VMLog.WriteVmLog("��������--1:nCID = %d,eReason = %d,nVideoPayload= %d,CalleeUser=%s",nCID,eReason,nVideoPayload,szCalleeUser);

		g_VMLog.WriteVmLog("SipStateHandlerInfo.nSpsLen=%d",SipStateHandlerInfo.nSpsLen);

		ThreadSipStateHandlerTalking(&SipStateHandlerInfo);

		g_VMLog.WriteVmLog("��������--2:nCID = %d,eReason = %d,nVideoPayload= %d,CalleeUser=%s",nCID,eReason,nVideoPayload,szCalleeUser);
	
	}
	else
	{
		//////////////////////////////////////////////////////////////////////////
		SIP_STATE_HANDLER_INFO SipStateHandlerInfo;
		memset(&SipStateHandlerInfo,0,sizeof(SipStateHandlerInfo));

		SipStateHandlerInfo.nCID = nCID;
		SipStateHandlerInfo.nDirection = (int)eDirection;
		strcpy_s(SipStateHandlerInfo.szCallerNum,sizeof(SipStateHandlerInfo.szCallerNum),szCallerUser);
		strcpy_s(SipStateHandlerInfo.szCalleeNum,sizeof(SipStateHandlerInfo.szCalleeNum),szCalleeUser);
		SipStateHandlerInfo.nSpsLen = 0;
		SipStateHandlerInfo.nVideoPayload = nVideoPayload;
		SipStateHandlerInfo.nReason = (int)eReason;
		SipStateHandlerInfo.pAppData = pAppData;

		g_VMLog.WriteVmLog("��������--1:nCID = %d,eReason = %d,nVideoPayload= %d,CalleeUser=%s",nCID,eReason,nVideoPayload,szCalleeUser);

		g_VMLog.WriteVmLog("SipStateHandlerInfo.nSpsLen=%d",SipStateHandlerInfo.nSpsLen);

		ThreadSipStateHandlerTalking(&SipStateHandlerInfo);

		g_VMLog.WriteVmLog("��������--2:nCID = %d,eReason = %d,nVideoPayload= %d,CalleeUser=%s",nCID,eReason,nVideoPayload,szCalleeUser);
	}

	return TRUE;
}


/********************************************************************************
*
*   Caller(����),Callee(����)
*   E_RT_CALL_STATE_TERMINATED = 2(��ֹ)
*	����TERMINATED״̬������
*
*********************************************************************************/
BOOL SipCallStatusTerminatedHandler(unsigned int nCID,E_RtCallStateReason eReason,void* pAppData)
{
	if (g_pMainDlg == NULL)
		return FALSE;

	//////////////////////////////////////////////////////////////////////////
	SIP_STATE_HANDLER_INFO SipStateHandlerInfo;
	memset(&SipStateHandlerInfo,0,sizeof(SipStateHandlerInfo));

	SipStateHandlerInfo.nCID = nCID;
	SipStateHandlerInfo.nReason = (int)eReason;
	SipStateHandlerInfo.pAppData = pAppData;

	g_VMLog.WriteVmLog("��������--1:nCID = %d,eReason = %d",nCID,eReason);

	ThreadSipStateHandlerTerminate(&SipStateHandlerInfo);

	g_VMLog.WriteVmLog("��������--2:nCID = %d,eReason = %d",nCID,eReason);


	return TRUE;
}


/***************************************����״̬������غ���***********************************/


/********************************************************************************
*
*  Sender,Receiver
*  E_RT_TRANSC_STATE_UNDEFINED= -1(��Ч)
*	����UNDEFINED״̬������
*
*********************************************************************************/
BOOL SipTransStatusUndefinedHandler(unsigned int nTID,E_RtTransactionStateReason eReason,void* pAppData)
{
	return TRUE;
}


/********************************************************************************
*
*   Sender,Receiver
*   E_RT_TRANSC_STATE_IDLE = 0(����)
*	����IDLE״̬������
*
*********************************************************************************/
BOOL SipTransStatusIdleHandler(unsigned int nTID,E_RtTransactionStateReason eReason,void* pAppData)
{
	return TRUE;
}


/********************************************************************************
*
*  Sender
*  E_RT_TRANSC_C_STATE_OK= 1(�ɹ�)
*	����OK״̬������
*
*********************************************************************************/
BOOL SipTransStatusOKHandler(unsigned int nTID,E_RtTransactionStateReason eReason,void* pAppData)
{
	return TRUE;
}


/********************************************************************************
*
*  Sender
*  E_RT_TRANSC_C_STATE_FAIL = 2(ʧ��)
*	����FAIL״̬������
*
*********************************************************************************/
BOOL SipTransStatusFailHandler(unsigned int nTID,E_RtTransactionStateReason eReason,void* pAppData)
{

	return TRUE;
}

/********************************************************************************
*
*  Sender
*  E_RT_TRANSC_C_STATE_PROCEEDING = 3(���������)
*	����PROCEEDING״̬������
*
*********************************************************************************/
BOOL SipTransStatusProceedingHandler(unsigned int nTID,E_RtTransactionStateReason eReason,void* pAppData)
{
	return TRUE;
}


/********************************************************************************
*
*  Receiver
*  E_RT_TRANSC_S_STATE_RECV_REQ = 4(�յ�����)
*	����RECV_REQ״̬������
*
*********************************************************************************/
BOOL SipTransStatusRecvReqHandler(unsigned int nTID,E_RtTransactionStateReason eReason,void* pAppData)
{
	return TRUE;
}


/********************************************************************************
*
*  Receiver
*  E_RT_TRANSC_S_STATE_WAIT_USER_PEOCESS = 5(�ȴ��û�����)
*	����WAIT_USER_PROCESS״̬������
*
*********************************************************************************/
BOOL SipTransStatusWaitUserProcessHandler(unsigned int nTID,E_RtTransactionStateReason eReason,void* pAppData)
{
	return TRUE;
}


/********************************************************************************
*
*  Receiver
*  E_RT_TRANSC_S_STATE_USER_ACK_ARRIVED = 6(��Ӧ���ʹ�)
*	����USER_ACK_ARRIVED״̬������
*
*********************************************************************************/
BOOL SipTransStatusUserAckArrivedHandler(unsigned int nTID,E_RtTransactionStateReason eReason,void* pAppData)
{
	return TRUE;
}


/********************************************************************************
*
*  Receiver
*  E_RT_TRANSC_S_STATE_USER_ACK_DISCARD = 7(��Ӧ��Ϣ��ʧ)
*	����USER_ACK_DISCARD״̬������
*
*********************************************************************************/
BOOL SipTransStatusUserAckDiscardHandler(unsigned int nTID,E_RtTransactionStateReason eReason,void* pAppData)
{
	return TRUE;
}



