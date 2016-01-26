#include "stdafx.h"
#include "SipUtil.h"
#include "SipUtilFunc.h"
#include "VEMCUCtl.h"
#include "VEMCUCtlDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//
T_RtStackConfigParam	app_StackCfg;
T_RtStackCallBack		    app_Callback;

IRtRegClientAPI*		   g_pRegClientAPI = NULL;
IRtTransactionAPI*		g_pTransactionAPI = NULL;
IRtCallAPI*				    g_pCallAPI = NULL;
IRtSdpAPI*				    g_pSdpAPI = NULL;
IRtEventAPI*			        g_pEventAPI = NULL;

T_RtSdpAudioNeg			g_tLocalAudio;			//������Ƶ��Ϣ(�˿ڲ�ʹ��)
T_RtpPortRange*			g_pRtpPortList;			//������Ƶ�˿�
int						        g_nCurrentRID = 0;    //ע����������һ��ID


T_App_RegClient_Info	 app_RegCh;
T_App_Sip_Channel		 app_UacCh[SIP_CHANNEL_MAX_NUM];
T_App_Sip_Channel		 app_UasCh[SIP_CHANNEL_MAX_NUM];
T_App_Transaction_Info	 app_TranCh[SIP_CHANNEL_MAX_NUM];
T_App_Subscribe_Info	 app_SubCh[SIP_CHANNEL_MAX_NUM];		// ����ͨ���б�

int						app_CurRegCh	= 0;
int						app_CurUacCh	= 0;
int						app_CurUasCh	= 0;
int						app_CurTranCh	= 0;


//////////////////////////////////////////////////////////////////////////
__t_RtpPortRange::__t_RtpPortRange():port(0),minport(0),maxport(0) 
{

}

__t_RtpPortRange::~__t_RtpPortRange()
{

}

unsigned short T_RtpPortRange::GetPort(unsigned increment)
{		
	unsigned p = 0;
	//ǰ��Ӧ�ü���
	{
		if (port < minport || port > (maxport-increment+1))
			port = minport;

		if (port == 0)
			return 0;

		if(increment % 2 == 0)
			port = port & 0xfffe;

		p = port;
		port = (unsigned)(port + increment);
	}

	return p;
}

int T_RtpPortRange::GetNumPorts() const
{
	return maxport - minport + 1;
}

int T_RtpPortRange::GetMaxPort()
{
	return maxport;
}

void T_RtpPortRange::LoadConfig(unsigned short minValue, unsigned short maxValue)
{
	if(minValue & 0x1)
		minValue++;

	if (minValue < 1024)
		minValue = 1024;
	else if (minValue > 65500)
		minValue = 65500;

	if (maxValue <= minValue)
		maxValue = minValue + 35;
	if (maxValue > 65535)
		maxValue = 65535;

	// ǰ��Ӧ�ü���
	{
		port = minport = (unsigned)minValue;
		maxport = (unsigned)maxValue;
	}
}

/**************************************************************
*	 
*   RTP Pt ����
*
*************************************************************/
typedef struct __t_RtRtpPayload
{
	int			nPt;
	char		szEncodeName[10];
	int			nMediaType;
	int			nClockRate;
} T_RtRtpPayload;

T_RtRtpPayload myPayloadTable[] =
{ 
	{0, "PCMU", 0, 8000},
	{4, "G723", 0, 8000},
	{8, "PCMA", 0, 8000},
	{18, "G729", 0, 8000},
	{0xFFFF, NULL, -1, -1}
};

T_RtRtpPayload* __GetRtpProfileByPayload(IN int nPt, IN T_RtRtpPayload* cvTable)
{
	T_RtRtpPayload* pTable = cvTable;

	if(pTable == NULL)
	{
		return NULL;
	}

	while(pTable->nPt != 0xFFFF)
	{
		if(nPt == pTable->nPt)
			return pTable;

		pTable++;
	}

	return NULL;
}


//ע��״̬�ı�ص�����
void CSGSipRegisterClient::StateChangeEvent(
	IN unsigned int			nRID, 
	IN E_RtRegClientState		eState,
	IN E_RtRegClientStateReason eReason,
	IN void*					pAppData)
{

	app_RegCh.reg_state = eState;
	int i = 0 ;

	switch(eState)
	{
	case E_RT_REG_STATE_IDLE:
		TRACE("Register IDLE(rid=%d)\n\n",nRID);
		break;

	case E_RT_REG_STATE_PROCEEDING:
		TRACE("Register Proceeding(rid=%d)\n\n",nRID);
		break;

	case E_RT_REG_STATE_OK:
		TRACE("Register OK(rid=%d)\n\n",nRID);
		break;

	case E_RT_REG_STATE_FAILED:
		TRACE("Register Fail(rid=%d, reason=%d)\n\n",nRID,eReason);
		break;

	default:
		break;
	}
}

void CSGSipCall::JRtpRecvMediaData(	//����ý�������յ�(����ʹ��JRtpģʽ��Ч)
								   OUT int						nCID,
								   OUT void*					pData,
								   OUT int						nDataLen,
								   OUT E_RtMediaType			nMediaType,
								   OUT unsigned int			nMediaPayload,
								   OUT bool					bMark,
								   OUT unsigned int			nTimestamp,
								   OUT unsigned int			nSeqNo)
{
	try
	{
		JRtpRecvMediaData_SipCall(nCID,pData,nDataLen,nMediaType,nMediaPayload,bMark,nTimestamp,nSeqNo);
		SystemLinkageSetting_SipCall_JRtpRecvMediaData(nCID,pData,nDataLen,nMediaType,nMediaPayload,bMark,nTimestamp,nSeqNo);
	}
	catch(...)
	{

	}
}

void CSGSipCall::JRtpRecvRtcpData(
								  OUT int						nCID,
								  OUT E_RtMediaType			eMediaType,
								  OUT E_RtRtcpPacketType		eType,
								  OUT unsigned int			dwSecond,
								  OUT const char*				pSenderAddress,
								  OUT const T_RtQOS4*			pQos)
{

}

void CSGSipCall::RecvOutboundDtmfEvent(
									   IN unsigned int		nCID, 
									   IN char				nDtmfChar,
									   IN void*			pAppData)
{

}

void CSGSipCall::StateChangeEvent(
								  IN unsigned int			     nCID,
								  IN E_RtCallState				 eState,
								  IN E_RtCallStateReason	 eReason,
								  IN void*						pAppData)
{
	try
	{
		StateChangeEvent_SipCall(nCID,eState,eReason,pAppData);
		SystemLinkageSetting_SipCall_StateChangeEvent(nCID,eState,eReason,pAppData);
	}
	catch(...)
	{

	}
	return;
}

void CSGSipEvent::StateChangeEvent(
								   OUT unsigned int			nSID,
								   OUT E_RtEventState			eState,
								   OUT E_RtEventStateReason	eReason,
								   OUT void*					pAppData)
{

	int i = 0;
	int rows = 0;

	switch(eState)
	{
	case E_RT_EVENT_STATE_SUER_EXPIRE_ALERT: //�ڸ�״̬����ˢ�¶���
		{
			g_pEventAPI->RefreshSubs(nSID, 3600, (char*)pAppData, strlen((char*)pAppData), "application/xml");
		}
		break;

	case E_RT_EVENT_STATE_SUER_NOTIFY_RCVD: //�ڸ�״̬��ȡNOTIFY�и澯����
		{
			char szNotifyXML[2000] = {0};
			int	 nActualLen = 0;

			g_pEventAPI->GetRemoteBody4Notify(nSID, szNotifyXML, sizeof(szNotifyXML), &nActualLen);

			TRACE(">> ������[sid=%d]���յ��澯����: [%s] \n\n", nSID, szNotifyXML);

			if (strlen(szNotifyXML) < 50)
				break;

			NOTIFY_STATUS	notify_status[MAX_STATUS_NOTIFY_NUM];

			// ����XML
			int nType = 0;
			int nNum = 0;	
			int nStationId = 0;

			GetXmlTypeNum(szNotifyXML, &nType, &nNum);

			if(nType != SIP_NOTIFY_STATUS)
				break;

			ParseNotifyStatus(notify_status, nNum, szNotifyXML);

			nStationId = (int)pAppData;
		}
		break;

	case E_RT_EVENT_STATE_PUER_RCVD: //�ڸ�״̬�²���ȥ���ջ�ܾ��澯
		{

		}
		break;

	case E_RT_EVENT_STATE_PUER_WAIT_PROCESS: //�ڸ�״̬������ջ�ܾ��澯,����ǽ��ջ�Ӧ����NOTIFY��Ϣ
		{
			char	 szXML[2048] = {0};
			int    nActualLen = 0;

			T_RtSipUrlInfo suer;

			g_pEventAPI->GetSuerInfo(nSID, &suer);
			g_pEventAPI->GetRemoteBody4Subs(nSID, szXML, sizeof(szXML), &nActualLen);

			TRACE(">> ������[sid=%d]���յ�[%s]����, ���ĵ�ַ��[%s:%d], SUBSCRIBE������[%s] \n\n",
				nSID, suer.szUser, suer.szHost, suer.portNum, szXML);

			g_pEventAPI->AcceptSubs(nSID, 3600);
			g_pEventAPI->MakeNotify(nSID, NULL, 0, E_RT_EVENT_SUBSSTATE_ACTIVE, "application/xml");
		}
		break;

	case E_RT_EVENT_STATE_PUER_REFRESH_WAIT_PROCESS: //ˢ�������յ����ȴ������ߴ������ջ�ܾ�
		{
			T_RtSipUrlInfo	suer;

			char szXML[1024] = {0};
			int    nActualLen = 0;

			g_pEventAPI->GetSuerInfo(nSID, &suer);
			g_pEventAPI->GetRemoteBody4Subs(nSID, szXML, sizeof(szXML), &nActualLen);

			TRACE(">> ������[sid=%d]���յ�[%s]ˢ�¶���, SUBSCRIBE������[%s] \n\n", nSID, suer.szUser, szXML);

			g_pEventAPI->AcceptSubs(nSID, -1);
			g_pEventAPI->MakeNotify(nSID, NULL, 0, E_RT_EVENT_SUBSSTATE_ACTIVE, "application/xml");
		}
		break;

	case E_RT_EVENT_STATE_ACTIVATED://���ļ���(������+������)

		TRACE(">> ���Ľ���: [sid=%d] \n\n", nSID);

		for (i = 0; i < SIP_CHANNEL_MAX_NUM; i ++)
		{
			if (nSID == app_SubCh[i].iSID)
			{
				app_SubCh[i].istate = E_RT_EVENT_STATE_ACTIVATED;

				break;
			}
		}
		break;

	case E_RT_EVENT_STATE_TERMINATED://���Ľ���(������+������)
		for (i = 0; i < SIP_CHANNEL_MAX_NUM; i ++)
		{
			if (nSID == app_SubCh[i].iSID)
			{
				app_SubCh[i].iSID = -1;
				app_SubCh[i].istate = E_RT_EVENT_STATE_TERMINATED;
				memset(app_SubCh[i].stationcode[0], 0, 20);

				break;
			}
		}
		break;

	default:
		break;
	}
}



void CSGSipTransaction::StateChangeEvent(IN unsigned int nTID, 
										 IN E_RtTransactionState eState, 
										 IN E_RtTransactionStateReason eReason, 
										 IN void* pAppData)
{
	try
	{
		StateChangeEvent_SipTrans(nTID,eState,eReason,pAppData);
		SystemLinkageSetting_SipTrans_StateChangeEvent(nTID,eState,eReason,pAppData);
	}
	catch(...)
	{

	}
	return;
}

/**************************************************************
*	 
*   SDP ����
*
*************************************************************/
int __GetRemoteSdpAndNegotiation(IN int nCID, OUT T_RtSdpAudioNeg* pNag)
{
	char	szBodyMediaType[56] = {0x0};
	char	szBody[1024] = {0x0};
	int		nRealLen = 0;
	int		nReturnCode = 0;

	if (pNag == NULL)
	{
		TRACE(">> The buffer is NULL\n\n");
		return -1;
	}

	//1. ���Զ��BODY������(��SDP����)
	nReturnCode = g_pCallAPI->GetRemoteBodyMediaType(nCID, szBodyMediaType, 56, &nRealLen);
	if(nReturnCode!=E_RT_OK || stricmp(szBodyMediaType, "application/SDP")!=0)
	{
		TRACE(">> The Remote Media not is SDP\n\n");
		return -1;
	}

	//2. ���Զ��BODY����
	nRealLen = 0;
	nReturnCode = g_pCallAPI->GetRemoteBody(nCID, szBody, 1024, &nRealLen);
	if(nReturnCode!=E_RT_OK || nRealLen==0)
	{
		TRACE(">> The Remote SDP is NULL\n\n");
		return -1;
	}

	//3. ����һ��SDP Handle
	RtSdpHandle	 hRemoteSDP = NULL;
	int			 nBodyLength = strlen(szBody);
	nReturnCode = g_pSdpAPI->Construct(szBody, &nBodyLength, &hRemoteSDP);
	if(nReturnCode != E_RT_OK)
	{
		TRACE(">> Construct SDP fail\n\n");
		return -1;
	}

	//4. ���c���е�ַ
	char*	pRemoteAddr = NULL;
	pRemoteAddr = (char*)g_pSdpAPI->GetCLine(hRemoteSDP);
	if(pRemoteAddr == NULL)
	{
		g_pSdpAPI->Destruct(hRemoteSDP);
		TRACE(">> The Remote SDP c line is invalid\n\n");
		return -1;
	}

	strcpy_s(pNag->szAddress, pRemoteAddr); //copy and assigned

	//5. ���m�и���
	int  nMediaNumber = 0;
	nMediaNumber = g_pSdpAPI->GetNumOfMediaDescr(hRemoteSDP);
	if(nMediaNumber < 1)
	{
		g_pSdpAPI->Destruct(hRemoteSDP);
		TRACE(">> Not found m line\n\n");
		return -1; 
	}

	//6. ����ÿ��m��
	RtSdpMediaHandle  hEveryMedia = NULL;
	bool  bNagResult = false;

	for(int j=0; j<nMediaNumber; j++)
	{
		//7. ����m�о��
		hEveryMedia = g_pSdpAPI->GetMediaDescr(hRemoteSDP, j);
		if(hEveryMedia == NULL)
		{
			TRACE(">> Get media handle is null\n\n");
			continue;
		}

		//8. ���m������
		E_RtMediaType  eMediaType;
		eMediaType = g_pSdpAPI->MediaGetType(hEveryMedia);
		if(eMediaType != E_RT_MEDIA_TYPE_AUDIO)
		{
			TRACE(">> Get media not is audio\n\n");
			continue;
		}

		//9. ���m��pt����
		int nMediaPtNumber = g_pSdpAPI->MediaGetNumOfPt(hEveryMedia);
		if(nMediaPtNumber < 1)
		{
			TRACE(">> Get media number is 0\n\n");
			continue;
		}

		//10. ���m�ж˿�
		pNag->nPort = g_pSdpAPI->MediaGetPort(hEveryMedia); //copy and assigned

		//11. ���m��������ģʽ��a��
		E_RtSdpConnMode eMode = g_pSdpAPI->MediaGetConnMode(hEveryMedia);

		//12. ����ptֵ(�ҵ�һ��ƥ������Ͼͷ���,���ǵ�policy���ҵ���һ����OK)
		int nFirstPayloadNumber = -1;
		for(int j2=0; j2<nMediaPtNumber; j2++)
		{
			nFirstPayloadNumber = g_pSdpAPI->MediaGetPt(hEveryMedia, j2);

			T_RtRtpPayload* pCurr = __GetRtpProfileByPayload(nFirstPayloadNumber, myPayloadTable);
			if(pCurr != NULL)
			{
				pNag->nPayloadNumber = nFirstPayloadNumber; //copy and assigned
				bNagResult = true;
				break;
			}
		}
	}

	g_pSdpAPI->Destruct(hRemoteSDP);

	if(bNagResult != true)
	{
		return -1;
	}

	return 0;
}

RtSdpHandle __ConstructSdpByComplete(IN int nCID, IN const T_RtSdpAudioNeg* pNeg)
{
	int			nRetCode = 0;
	RtSdpHandle	hLocalSdp = NULL;

	if(pNeg == NULL)
	{
		TRACE(">> Base parameter is NULL\n\n");
		return NULL;
	}

	//1. ����SDP Handle
	nRetCode = g_pSdpAPI->Construct(&hLocalSdp);
	if(nRetCode != E_RT_OK)
	{
		TRACE(">> Failed to construct a new sdp body handle\n\n");
		return NULL;
	}

	//2. ����Info��
	nRetCode = g_pSdpAPI->SetILine(hLocalSdp, "The EasyCall");
	if(nRetCode != E_RT_OK)
	{
		TRACE(">> Failed to set sdp info line\n\n");
		g_pSdpAPI->Destruct(hLocalSdp);
		return NULL;
	}

	//3. ����o��
	nRetCode = g_pSdpAPI->SetOrigin(hLocalSdp, "-", "1234", "4321", pNeg->szAddress);
	if(nRetCode != E_RT_OK)
	{
		TRACE(">> Failed to set sdp origin line\n\n");
		g_pSdpAPI->Destruct(hLocalSdp);
		return NULL;
	}

	//4. ����s��
	nRetCode = g_pSdpAPI->SetSLine(hLocalSdp, "The Inforware EasyCall - Session-5555");
	if(nRetCode != E_RT_OK)
	{
		TRACE(">> Failed to set sdp session name line\n\n");
		g_pSdpAPI->Destruct(hLocalSdp);
		return NULL;
	}

	//4. ����t��
	nRetCode = g_pSdpAPI->SetTLine(hLocalSdp, 0, 0);
	if(nRetCode != E_RT_OK)
	{
		TRACE(">> Failed to set sdp time line\n\n");
		g_pSdpAPI->Destruct(hLocalSdp);
		return NULL;
	}

	//5. ����m��
	RtSdpMediaHandle  hMyMediaType = NULL;
	int				  nLocalRtpPort = g_pRtpPortList->GetPort(2);
	hMyMediaType = g_pSdpAPI->AddMediaDescr(hLocalSdp, E_RT_MEDIA_TYPE_AUDIO, nLocalRtpPort, E_RT_TRANSPORT_RTP);
	{
		TRACE(">> Failed to set sdp m line\n\n");
		g_pSdpAPI->Destruct(hLocalSdp);
		return NULL;
	}

	//6. ���Pt��ֵ
	T_RtRtpPayload* pCurrentProfile = NULL;
	pCurrentProfile = __GetRtpProfileByPayload(pNeg->nPayloadNumber, myPayloadTable);
	if(pCurrentProfile == NULL)
	{
		TRACE(">> Payload is invalid\n\n");
		g_pSdpAPI->Destruct(hLocalSdp);
		return NULL;
	}

	//6. ����a��
	g_pSdpAPI->MediaAddPt(hMyMediaType, pNeg->nPayloadNumber);
	g_pSdpAPI->MediaAddRtpmap(hMyMediaType, pNeg->nPayloadNumber, pCurrentProfile->szEncodeName, pCurrentProfile->nClockRate);
	g_pSdpAPI->MediaSetConnMode(hMyMediaType, E_RT_SDPCONNMODE_SENDRECV);

	return hLocalSdp;
}

RtSdpHandle __ConstructSdpBySimple(IN int nCID, IN const T_RtSdpAudioNeg* pNeg)
{
	int			nRetCode = 0;
	RtSdpHandle	hLocalSdp = NULL;

	if(pNeg == NULL)
	{
		TRACE(">> Base parameter is NULL\n\n");
		return NULL;
	}

	nRetCode = g_pSdpAPI->Construct(&hLocalSdp);
	if(nRetCode != E_RT_OK)
	{
		TRACE(">> Failed to construct a new sdp body handle\n\n");
		return NULL;
	}

	nRetCode = g_pSdpAPI->SetBoundaryLine(hLocalSdp, pNeg->szAddress);
	if(nRetCode != E_RT_OK)
	{
		TRACE(">> Failed to set sdp time line\n\n");
		g_pSdpAPI->Destruct(hLocalSdp);
		return NULL;
	}

	RtSdpMediaHandle  hMyMediaType = NULL;
	int				  nLocalPort = g_pRtpPortList->GetPort(2);
	g_tLocalAudio.nPort = nLocalPort;

	hMyMediaType = g_pSdpAPI->AddMediaDescr(hLocalSdp, E_RT_MEDIA_TYPE_AUDIO, nLocalPort, E_RT_TRANSPORT_RTP);
	if(hMyMediaType == NULL)
	{
		TRACE(">> Failed to set sdp m line\n\n");
		g_pSdpAPI->Destruct(hLocalSdp);
		return NULL;
	}

	T_RtRtpPayload* pCurrentProfile = NULL;
	pCurrentProfile = __GetRtpProfileByPayload(pNeg->nPayloadNumber, myPayloadTable);
	if(pCurrentProfile == NULL)
	{
		TRACE(">> Payload is invalid\n\n");
		g_pSdpAPI->Destruct(hLocalSdp);
		return NULL;
	}

	g_pSdpAPI->MediaAddPt(hMyMediaType, pNeg->nPayloadNumber);
	g_pSdpAPI->MediaAddRtpmap(hMyMediaType, pNeg->nPayloadNumber, pCurrentProfile->szEncodeName, pCurrentProfile->nClockRate);
	g_pSdpAPI->MediaSetConnMode(hMyMediaType, E_RT_SDPCONNMODE_SENDRECV);

	return hLocalSdp;
}

//////////////////////////////////////////////////////////////////////////
//��ʼ��ջ����

/****************************************************************************
*
*								RTջ��ʼ������
*
****************************************************************************/
//��ʼ��ע��ͨ��
void AppInitSipChannel(void)
{
	memset(&app_StackCfg, 0, sizeof(T_RtStackConfigParam));
	memset(&app_Callback, 0, sizeof(T_RtStackCallBack));

	app_CurRegCh = 0;
	app_CurUacCh = 0;
	app_CurUasCh = 0;
	app_CurTranCh = 0;

	app_RegCh.reg_chid = 0;
	app_RegCh.reg_id = -1;
	app_RegCh.reg_expires = 0;
	app_RegCh.reg_ttl = 0;
	app_RegCh.reg_state = E_RT_REG_STATE_IDLE;
	app_RegCh.reg_oldstate = E_RT_REG_STATE_IDLE;
	memset(app_RegCh.reg_server,0,50);
	memset(app_RegCh.reg_user,0,50);

	for(int i=0; i<SIP_CHANNEL_MAX_NUM; i++)
	{
		app_UacCh[i].nSipCallID = -1;
		app_UacCh[i].nUserChannelID = -1;
		app_UacCh[i].nAppSipCallState = E_RT_CALL_STATE_IDLE;
		app_UacCh[i].nDevType = 0;
		memset(app_UacCh[i].szSipCallee,0,50);
		memset(app_UacCh[i].szSipCaller,0,50);

		app_UasCh[i].nSipCallID = -1;
		app_UasCh[i].nUserChannelID = -1;
		app_UasCh[i].nAppSipCallState = E_RT_CALL_STATE_IDLE;
		app_UasCh[i].nDevType = 0;
		memset(app_UasCh[i].szSipCallee,0,50);
		memset(app_UasCh[i].szSipCaller,0,50);

		app_TranCh[i].tran_chid = i;
		app_TranCh[i].tran_id = -1;
		app_TranCh[i].tran_direction = -1;
		app_TranCh[i].tran_state = E_RT_TRANSC_STATE_IDLE;
		app_TranCh[i].tran_oldstate = E_RT_TRANSC_STATE_IDLE;
		memset(app_TranCh[i].tran_caller,0,50);
		memset(app_TranCh[i].tran_callee,0,50);
		memset(app_TranCh[i].tran_last_msg,0,50);

		app_SubCh[i].iSID = -1;
		app_SubCh[i].istate = E_RT_EVENT_SUBSSTATE_UNDEFINED;
		app_SubCh[i].istationnum = 0;
		for (int j = 0; j < 10; j ++)
		{
			memset(app_SubCh[i].stationcode[j], 0 ,20);
		}
	}
}

/**************************************************************
*	 
*   ����SIPЭ��ջ
*
*************************************************************/
int AppStartSipStack(void)
{
	CRtSipStackManager * pStackMgr = NULL;
	int  nRetCode = 0;

	//���챾��RTP�˿ڷ�Χ
	g_pRtpPortList = new T_RtpPortRange();
	g_pRtpPortList->LoadConfig(app_StackCfg.nMinRtpPort, app_StackCfg.nMaxRtpPort);

	memset(&g_tLocalAudio, 0, sizeof(T_RtSdpAudioNeg));
	g_tLocalAudio.nPayloadNumber = 8;
	strcpy_s(g_tLocalAudio.szAddress, app_StackCfg.szLocalUdpAddress);

	//1. ��ʼ��SIPջ�Ĳ���and�ص�
	app_Callback.pRegClientSink = new CSGSipRegisterClient;
	app_Callback.pCallSink = new CSGSipCall;
	app_Callback.pTransactionSink = new CSGSipTransaction;
	app_Callback.pEventSink = new CSGSipEvent;

	//2. ���SIP Stack��Instance
	pStackMgr = CRtSipStackManager::Instance();
	if(pStackMgr == NULL)
	{
		TRACE("The SIP Stack interface class is invalid\n");
		return -1;
	}

	//3. ��ʼ��SIP Stack����
	nRetCode = pStackMgr->InitEngineer(&app_StackCfg);
	if(nRetCode != E_RT_OK)
	{
		TRACE("Initialize Stack Parameter fail\n");
		return -1;
	}

	//4. ����Callback����
	nRetCode = pStackMgr->SetModuleCallback(&app_Callback);
	if(nRetCode != E_RT_OK)
	{
		TRACE("Set Callback Interface fail\n");
		return -1;
	}

	//5. ����SIP Stack����
	nRetCode = pStackMgr->StartEngineer();
	if(nRetCode != E_RT_OK)
	{
		TRACE("The Sip Stack Start Fail\n");
		return -1;
	}

	//6. ������п��ų�����API�ӿ�
	nRetCode = pStackMgr->QueryInterface(E_IID_ISIPREG, (void**)&g_pRegClientAPI);
	if(nRetCode != E_RT_OK)
	{
		TRACE("The Sip Stack Query RegClient Module interface fail\n");
		return -1;
	}

	nRetCode = pStackMgr->QueryInterface(E_IID_ISIPTRANS, (void**)&g_pTransactionAPI);
	if(nRetCode != E_RT_OK)
	{
		TRACE("The Sip Stack Query Transaction Module interface fail\n");
		return -1;
	}

	nRetCode = pStackMgr->QueryInterface(E_IID_ISIPCALL, (void**)&g_pCallAPI);
	if(nRetCode != E_RT_OK)
	{
		TRACE("The Sip Stack Query Call Module interface fail\n");
		return -1;
	}

	nRetCode = pStackMgr->QueryInterface(E_IID_ISDPSTACK, (void**)&g_pSdpAPI);
	if(nRetCode != E_RT_OK)
	{
		TRACE("The Sip Stack Query SDP Stack interface fail\n");
		return -1;
	}

	nRetCode = pStackMgr->SetSpecMediaPayload(E_RT_DPT_MEDIA_HIK264, 100);//���ñ�׼H264��������E_RT_DPT_MEDIA_H264ʱ�������⣬��E_RT_DPT_MEDIA_HIK264����
	if(nRetCode != E_RT_OK)
	{
		TRACE("����H264��PTʧ��!\n");
		return -1;
	}

	nRetCode = pStackMgr->QueryInterface(E_IID_ISIPEVENT, (void**)&g_pEventAPI);
	if(nRetCode != E_RT_OK)
	{
		TRACE("The Sip Stack Query Event Stack interface fail\n");
		return -1;
	}

	return 0;
}

//ֹͣSIPЭ��ջ
int AppStopSipStack(void)
{
	CRtSipStackManager* pStackMgr = NULL;
	int nRetCode = 0;

	//���SIP Stack��Instance
	pStackMgr = CRtSipStackManager::Instance();
	if(pStackMgr == NULL)
	{
		TRACE("The SIP Stack interface class is invalid\n");
		return -1;
	}

	//ֹͣSIP Stack����
	nRetCode = pStackMgr->StopEngineer();
	if(nRetCode != E_RT_OK)
	{
		TRACE("The Sip Stack Stop Fail\n");
		return -1;
	}

	if (g_pRtpPortList != NULL)
	{
		delete g_pRtpPortList;
		g_pRtpPortList = NULL;
	}

	if (app_Callback.pRegClientSink != NULL)
	{
		delete app_Callback.pRegClientSink;
		app_Callback.pRegClientSink = NULL;
	}

	if (app_Callback.pTransactionSink != NULL)
	{
		delete app_Callback.pTransactionSink;
		app_Callback.pTransactionSink = NULL;
	}

	if (app_Callback.pCallSink != NULL)
	{
		delete app_Callback.pCallSink;
		app_Callback.pCallSink = NULL;
	}

	if (app_Callback.pEventSink != NULL)
	{
		delete app_Callback.pEventSink;
		app_Callback.pEventSink = NULL;
	}

	return 0;
}


/********************************************************************************
*
*										ע�ᴦ����
*
*********************************************************************************/

//������ע��
int AppMakeReg(char* pszServer,char* pszUsername,char* pszPassword,int nExpires,char* pszUserAgent)
{
	int	nRetCode = 0;
	//����һ���µ�ע�� 			
	nRetCode = g_pRegClientAPI->MakeEx(pszServer, pszUsername, pszPassword, nExpires, pszUserAgent, g_pRegClientAPI, &g_nCurrentRID);
	if(nRetCode != E_RT_OK || g_nCurrentRID < 1)
	{
		TRACE("Make a new register fail\n");
		return -1;
	}

	Sleep(100);

	app_RegCh.reg_id = g_nCurrentRID;
	app_RegCh.reg_expires = nExpires;
	strcpy_s(app_RegCh.reg_server,pszServer);
	strcpy_s(app_RegCh.reg_user,pszUsername);

	return nRetCode;
}

//ȡ��ע��
int AppCancelReg()
{
	int eRet = 0;
	
	int rid = app_RegCh.reg_id;
	
	if(rid == -1)
		return -1;

	if (app_RegCh.reg_state == E_RT_REG_STATE_OK)
	{
		eRet = g_pRegClientAPI->Unregister(rid);
	}

	if (app_RegCh.reg_state == E_RT_REG_STATE_PROCEEDING)
	{
		eRet = g_pRegClientAPI->Unregister(rid);
	}

	return eRet;
}

//��ֹע��
int AppTerminateReg()
{	
	int rid = app_RegCh.reg_id;
	
	if(rid == -1)
		return -1;

	g_pRegClientAPI->Terminate(rid);

	return 0;
}


int AppGetIdleUacID()
{
	for(int i=0; i<SIP_CHANNEL_MAX_NUM; i++)
	{
		if(app_UacCh[i].nAppSipCallState == E_RT_CALL_STATE_IDLE)
			return i;
	}

	return -1;
}

// �Ƿ�����Ч��ID
BOOL AppUacUasIDIsValid(int callid)
{
	for(int i=0; i<SIP_CHANNEL_MAX_NUM; i++)
	{
		if(app_UacCh[i].nSipCallID == callid)
		{
			return TRUE;
		}

		if(app_UasCh[i].nSipCallID == callid)
		{
			return TRUE;
		}
	}
	return FALSE;
}

// ���ͨ��
BOOL AppClearUacUasID(int callid)
{
	for(int i=0; i<SIP_CHANNEL_MAX_NUM; i++)
	{
		if(app_UacCh[i].nSipCallID == callid)
		{
			app_UacCh[i].nSipCallID = -1;
			app_UacCh[i].nAppSipCallState = E_RT_CALL_STATE_IDLE;
		}

		if(app_UasCh[i].nSipCallID == callid)
		{
			app_UasCh[i].nSipCallID = -1;
			app_UasCh[i].nAppSipCallState = E_RT_CALL_STATE_IDLE;
		}
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//��������
int AppMakeTrans(char* pszDestAddr, E_RtMethodType eMethodType, char* pszBody, int iWinID)
{
	int tc_id = AppGetIdleTransCh();
	int t_id = -1;

	g_pTransactionAPI->ProduceTID(&t_id,NULL);
	if(tc_id == -1 || t_id == -1)
		return -1;

	char callurl[256] = {0};
	sprintf(callurl, "%s@%s:%d", pszDestAddr, app_RegCh.reg_server, app_RegCh.reg_serverport);

	app_TranCh[tc_id].tran_id = t_id;
	g_pTransactionAPI->Make(t_id,callurl,eMethodType,pszBody,strlen(pszBody),0,0,0,0,0,app_RegCh.reg_user,"application/xml");

	return 0;
}

int AppGetIdleTransCh()
{
	for(int i=0; i<SIP_CHANNEL_MAX_NUM; i++)
	{
		if(app_TranCh[i].tran_state == E_RT_TRANSC_STATE_IDLE)
			return i;
	}
	return -1;
}
