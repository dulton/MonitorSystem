#ifndef __SIPUTIL_H__
#define __SIPUTIL_H__

#include ".\include\IWLSipAPI.h"
#include ".\include\IWLSipRegAPI.h"
#include ".\include\IWLSipTrAPI.h"
#include ".\include\IWLSipSdpAPI.h"
#include ".\include\IWLSipCallAPI.h"
#include ".\include\IWLPortAPI.h"
#include ".\include\IWLSipEventAPI.h"

#define SIP_CHANNEL_MAX_NUM 65535

static long read_num = 0;
static long write_num = 0;
static long recvrtp_num = 0;
static long sendrtp_num = 0;

//////////////////////////////////////////////////////////////////////////
// RTջ������

//ע����Ϣ(ÿ��)
typedef struct __t_App_RegClient_Info  
{
	int			reg_chid;						//ע���ͨ����
	int			reg_id;							//ע���ID��
	int			reg_state;					//ע���״̬
	int			reg_oldstate;				//ע��ɵ�״̬
	int			reg_expires;				    //ע�����Ч��
	int			reg_ttl;							//ע���ʣ��������
	char		    reg_server[50];			// ע��ķ�������ַ
	int			reg_serverport;			// ע��ķ������˿ں�
	char		    reg_user[50];				// ע����û�����
	char		    reg_password[50];		// ע����û�����
}T_App_RegClient_Info;

//������һ��SIPͨ��
typedef struct __t_App_Sip_Channel
{
	int			nUserChannelID;				//��ص���ϯͨ����ID
	int			nSipCallID;							//SIP��CID
	int			nAppSipCallState;				//SIP�����Ӧ��״̬
	char		    szSipCaller[50];					//SIP����е�����
	char		    szSipCallee[50];					//SIP����еı���
	int			nDevType;							//ͨ��������
}T_App_Sip_Channel; 

//������Ϣ(ÿ��)
typedef struct __t_App_Transaction_Info
{
	int		tran_chid;								//����ͨ����
	int		tran_id;								    //����ID��
	int		tran_state;								//����״̬
	int		tran_oldstate;							//����ɵ�״̬
	int		tran_direction;						//����ķ���
	char	    tran_caller[50];						//����������
	char	    tran_callee[50];						//���񱻽���
	char	    tran_last_msg[50];					//��Ϣ����
} T_App_Transaction_Info;

typedef struct __t_App_Subscribe_Info
{
	int		iSID;									        // ����ID��
	char	    stationcode[10][20];			    // ������Ϣ�и���վ��ı���
	int		istationnum;							// ���ĵ�վ�����
	int		istate;									    // ���ĵ�״̬
}T_App_Subscribe_Info;

typedef struct __t_App_Msg_List //��Ϣ�ṹ
{
	__t_App_Msg_List*	msg_next;
	char				msg_content[50];
} T_App_Msg_List;

typedef enum
{
	PCUM,
	G711,
	G723,
	G729,
	H264
}RTP_CODEC;

typedef struct _RTP_ACTION
{
	void(*ReadFromDev)(char* playload,int len,void* args);
	void(*WriteToDev)(char* playload,int len,void* args);
}RTP_ACTION;

typedef struct _THREAD_ARGS
{
	int call_id;
	RTP_CODEC codec;
	RTP_ACTION action;
}THREAD_ARGS;

//SDPЭ�̽ṹ
typedef struct __t_RtSdpAudioNeg
{
	int		nPayloadNumber;
	int		nPort;
	char	    szAddress[56];
	char  	szCalleeName[56];
} T_RtSdpAudioNeg;

//����RTP�Ķ˿ڻ��
typedef struct __t_RtpPortRange
{
	__t_RtpPortRange();
	~__t_RtpPortRange();

	unsigned short 	GetPort(unsigned increment); //��ÿյĶ˿�
	int				GetNumPorts() const;  //����������ֵ
	int				GetMaxPort(); //�������ֵ
	void			LoadConfig(unsigned short minValue = 1024, unsigned short maxValue = 65535); //���ö˿�����

private:
	__t_RtpPortRange(const __t_RtpPortRange&);
	__t_RtpPortRange& operator=(const __t_RtpPortRange&);	
	unsigned short	port, minport, maxport;

} T_RtpPortRange;

/*************************************Э��ջ��غ���***********************************/
// ��ʼ��SIPͨ��
void AppInitSipChannel(void);

// ����SIPЭ��ջ
int	AppStartSipStack();

// ֹͣSIPЭ��ջ
int	AppStopSipStack();

/***************************************ע����غ���***********************************/
// ������ע��
int	AppMakeReg(char* pszServer,char* pszUsername,char* pszPassword,int nExpires,char* pszUserAgent);
// ȡ��ע��
int	AppCancelReg();
// ��ֹע��
int	AppTerminateReg();

/***************************************������غ���***********************************/

// ���һ������״̬�ǿ��е�UACͨ��
int AppGetIdleUacID();

// �Ƿ�����Ч��ID
BOOL AppUacUasIDIsValid(int callid);

// ���ͨ��
BOOL AppClearUacUasID(int callid);

/***************************************������غ���***********************************/
// ����������
int	AppMakeTrans(char* pszDestAddr, E_RtMethodType eMethodType, char* pszBody, int iWinID);

// ��ȡ���е�����ͨ��
int	AppGetIdleTransCh();

/**************************************************************
*	 
*   ע���Callback���մ�����
*
*************************************************************/
class CSGSipRegisterClient : public IRtRegClientCBSink
{
public:
	void StateChangeEvent( 
		IN unsigned int					nRID,
		IN E_RtRegClientState			eState,
		IN E_RtRegClientStateReason		eReason,
		IN void*						pAppData);
};


/**************************************************************
*	 
*   ���е�Callback���մ�����
*
*************************************************************/

class CSGSipCall : public IRtCallCBSink
{
public:
	virtual	void StateChangeEvent(
		IN unsigned int				nCID,
		IN E_RtCallState			eState,
		IN E_RtCallStateReason	 eReason,
		IN void*					pAppData); 

	virtual	void RecvOutboundDtmfEvent( //����DTMF�յ�
		IN unsigned int		nCID,
		IN char				nDtmfChar,
		IN void*			pAppData);

	virtual void JRtpRecvMediaData(
		OUT int						nCID,
		OUT void*					pData,
		OUT int						nDataLen,
		OUT E_RtMediaType	nMediaType,
		OUT unsigned int		nMediaPayload,
		OUT bool					bMark,
		OUT unsigned int		nTimestamp,
		OUT unsigned int		nSeqNo);

	virtual void JRtpRecvRtcpData(
		OUT int						nCID,
		OUT E_RtMediaType			eMediaType,
		OUT E_RtRtcpPacketType	eType,
		OUT unsigned int			dwSecond,
		OUT const char*				pSenderAddress,
		OUT const T_RtQOS4*	pQos);

	virtual void RecvReferEvent( //Refer�¼��յ�
		IN unsigned int				nOwnerCID,
		IN RtSubsHandle				hSubs,
		IN char*					pReferTo,  //���ڴ��ڶ��󷵻ؼ�����
		IN void*					pAppData)
	{

	}
};


/**************************************************************
*	 
*   �¼���Callback���մ�����
*
*************************************************************/
class CSGSipEvent : public IRtEventCBSink
{
public:
	virtual	void StateChangeEvent(
		OUT unsigned int			nSID,
		OUT E_RtEventState			eState,
		OUT E_RtEventStateReason	eReason,
		OUT void*					pAppData);
};


/**************************************************************
*	 
*   �����Callback���մ�����
*
*************************************************************/
class CSGSipTransaction : public IRtTransactionCBSink
{
public:
	virtual	void StateChangeEvent(
		IN unsigned int					nTID,
		IN E_RtTransactionState			eState,
		IN E_RtTransactionStateReason	eReason,
		IN void*						pAppData);
};


/**************************************ȫ�ֱ�������***************************************/
extern T_RtStackConfigParam	app_StackCfg;						// Э��ջ������Ϣ
extern T_RtStackCallBack		    app_Callback;						// �ص��������

extern IRtRegClientAPI*			g_pRegClientAPI;				// ע��Ĵ���ӿں���
extern IRtCallAPI*				        g_pCallAPI;							// ���еĴ���ӿں���
extern IRtSdpAPI*				        g_pSdpAPI;							// SDP���еĴ���ӿں���
extern IRtTransactionAPI*		    g_pTransactionAPI;			// ����Ĵ���ӿں���
extern IRtEventAPI*				    g_pEventAPI;						// �����API

extern T_RtSdpAudioNeg	 g_tLocalAudio;			//������Ƶ��Ϣ(�˿ڲ�ʹ��)

extern T_App_RegClient_Info		app_RegCh;		// ע��ͨ���б�
extern T_App_Sip_Channel		app_UacCh[SIP_CHANNEL_MAX_NUM];		// ����ͨ���б�
extern T_App_Sip_Channel		app_UasCh[SIP_CHANNEL_MAX_NUM];		// ����ͨ���б�
extern T_App_Transaction_Info	app_TranCh[SIP_CHANNEL_MAX_NUM];	    // ����ͨ���б�
extern T_App_Subscribe_Info		app_SubCh[SIP_CHANNEL_MAX_NUM];		// ����ͨ���б�

extern int						app_CurRegCh;						// ��ǰ��ע��ͨ��
extern int						app_CurUacCh;						// ��ǰ������ͨ��
extern int						app_CurUasCh;						// ��ǰ�ı���ͨ��
extern int						app_CurTranCh;						// ��ǰ������ͨ��


#endif /*__SIPUTIL_H__*/

