#ifndef __IWL_SIP_STACK_SIPCALLAPI_H_
#define __IWL_SIP_STACK_SIPCALLAPI_H_

RT_DECLARE_HANDLE(RtSubsHandle);

typedef enum  __e_RtCallState
{
	E_RT_CALL_STATE_UNDEFINED				= -1,	//��Ч
	E_RT_CALL_STATE_IDLE					= 0,	//����
	E_RT_CALL_STATE_TALKING					= 1,	//ͨ��
	E_RT_CALL_STATE_TERMINATED				= 2,	//��ֹ
	E_RT_CALL_STATE_INVITING				= 3,	//���ں���	  (����״̬)
	E_RT_CALL_STATE_PROCEEDING				= 4,	//Զ�����ڴ���(����״̬)
	E_RT_CALL_STATE_RECV_CALL				= 5,	//�յ�����	  (����״̬)
	E_RT_CALL_STATE_OFFERING				= 6,	//����		  (����״̬)
	E_RT_CALL_STATE_WAIT_TALKING			= 7,	//�ȴ�����ͨ��(����״̬)
} E_RtCallState;

typedef enum __e_RtCallStateReason
{	
	E_RT_CALL_REASON_UNDEFINED				= -1,	
	E_RT_CALL_REASON_NORMAL					= 0,	//������״̬Ǩ��
	E_RT_CALL_REASON_LOCAL_CANCEL			= 1,	//����ȡ������(����)
	E_RT_CALL_REASON_REMOTE_CANCEL			= 2,	//Զ��ȡ������(����)
	E_RT_CALL_REASON_LOCAL_HANGUP			= 3,	//���عһ�
	E_RT_CALL_REASON_REMOTE_HANGUP			= 4,	//Զ�˹һ�
	E_RT_CALL_REASON_FAIL_REDIRECTED		= 5,	//3xx��Ϣ(����,��Ҫ������һ��ַ����)
	E_RT_CALL_REASON_FAIL_REJECT			= 6,	//4xx��Ϣ(����,�����ܾ�)
	E_RT_CALL_REASON_FAIL_SERVER			= 7,	//5xx��Ϣ(����,������˹���)
	E_RT_CALL_REASON_FAIL_GLOBAL			= 8,	//6xx��Ϣ(����,��ȫ���������)
	E_RT_CALL_REASON_NETWORK_ERROR			= 9,	//�������
	E_RT_CALL_REASON_UNAUTHENTICATED		= 10,	//��Ȩʧ��(����)
	E_RT_CALL_REASON_RECV_180				= 11,	//�յ�180ָʾ����(����)
	E_RT_CALL_REASON_RECV_181				= 12,	//�յ�181ָʾ������ת��(����)
	E_RT_CALL_REASON_RECV_182				= 13,	//�յ�182ָʾ���б������Ŷ�(����)
	E_RT_CALL_REASON_RECV_183				= 14,	//�յ�183ָʾ����(����)
	E_RT_CALL_REASON_WAIT_PICKUP_TIMEOUT	= 15,	//�ȴ�����ժ����ʱ(����)
	E_RT_CALL_REASON_LOCAL_TIMEOUT			= 16,	//���˴���ʱ
	E_RT_CALL_REASON_LOCAL_FAILURE			= 17,	//������ΪĳЩ�߼�ʧ��(�ڴ治��,���ݴ����)
} E_RtCallStateReason;

typedef struct __t_RtSipMixerBody 
{
	 char			szMaster[56];	//������,��application
	 char			szSubs[56];		//������,��SDP
	 char			szBody[2048];	//��Ϣ��
	 unsigned int	nBodyLen;		//��Ϣ�峤��
} T_RtSipMixerBody;

class RTAPI IRtCallCBSink
{
public:
	virtual	void StateChangeEvent( //״̬Ǩ��
		OUT unsigned int			nCID,
		OUT E_RtCallState			eState,
		OUT E_RtCallStateReason		eReason,
		OUT void*					pAppData
		) = 0; 

	virtual	void RecvOutboundDtmfEvent( //�յ�����DTMF
		OUT unsigned int			nCID,
		OUT char					nDtmfChar,	//DTMF�ַ�
		OUT void*					pAppData
		) = 0;

	virtual void RecvReferEvent( //���������¼�
		OUT unsigned int			nOwnerCID,
		OUT RtSubsHandle			hSubs,		//����������
		OUT char*					pReferTo,	//����ĵ�������Ϣ
		OUT void*					pAppData
		) = 0;

	virtual void JRtpRecvMediaData(	//�յ�RTP(����ʹ��Rtpģʽ��Ч)
		OUT int						nCID,
		OUT void*					pData,
		OUT int						nDataLen,
		OUT E_RtMediaType			eMediaType,
		OUT unsigned int			nMediaPayload,	//*dynamic payload maybe is unmatch in local maybe)
		OUT bool					bMark, 
		OUT unsigned int			nTimestamp,
		OUT unsigned int			nSeqNo
		) = 0;

	virtual void JRtpRecvRtcpData( //�յ�RTCP(����ʹ��Rtpģʽ��Ч)
		OUT int						nCID,
		OUT E_RtMediaType			eMediaType,
		OUT E_RtRtcpPacketType		eType,
		OUT unsigned int			dwSecond,
		OUT const char*				pSenderAddress,
		OUT const T_RtQOS4*			pQos
		) = 0;

	virtual ~IRtCallCBSink() = 0;
};

class RTAPI IRtCallAPI 
{
public:	
	/*
	 * ������ģʽ�Ĺ��ú���
	 */
	virtual int ProduceCID( //����Ϊ��������CID
		INOUT int*				pCID
		) = 0;
	
	virtual int Reject( //���оܾ�����
		IN    int				nCID, 
		IN    E_RtRejectCode	eReasonCode,
		IN    const char*		pszConfPlainText = NULL,
		IN    const int			nConfPlainTextLen = 0,
		IN    char*				pszBodyType = NULL	//��ʽ"[������]/[������]",���������Ϣ�岻��������Ϊtext/plain
		) = 0;

	virtual int Hangup( //�һ�,���κ�״̬�¶��ɵ���,ջ���������������ͺ�����Ϣ
		IN    int				nCID,
		IN    bool				bTerminated = false
		) = 0;

	virtual int SendDtmfByOutbound( //���ʹ���DTMF
		IN    int				nCID,
		IN    char				szChar
		) = 0;

	virtual int SendResponseCode( //���з���������Ӧ
		IN    int				nCID, 
		IN    int				nCode
		) = 0;
	
	virtual int SendProvisionalCode( //���з�����ʱ��Ӧ(���������ֶ�������ʱ��Ӧ������ñ�����)
		IN    int				nCID, 
		IN    int				nCode,
		IN    bool				bReliable, //�Ƿ��Ϳɿ���ʱ��Ӧ
		IN    const RtSdpHandle	hSdp
		) = 0;
	   
	virtual int GetAppData( //��ô��������
		IN	  int				nCID,
		OUT   void**			ppAppData
		) = 0;
		
	virtual int SetAppData( //���ô��������
		IN	  int				nCID,
		IN    void*				pAppData
		) = 0;
	
	virtual int GetCalleeHost( //��ȡ���е�ַ
		IN	  int				nCID,
		INOUT char*				pAddrBuffer,
		IN	  int				nAddrBufferLen,
		INOUT int*				pActualLen
		) = 0;

	virtual int GetCalleeUser( //��ȡ�����û���
		IN	  int				nCID,
		INOUT char*				pUsernameBuffer,
		IN	  int				nUsernameBufferLen,
		INOUT int*				pActualLen
		) = 0;
	   
	virtual int GetCallerHost( //��ȡ���е�ַ
		IN	  int				nCID,
		INOUT char*				pAddrBuffer,
		IN	  int				nAddrBufferLen,
		INOUT int*				pActualLen
		) = 0;
	   
	virtual int GetCallerUser( //��ȡ�����û���
		IN	  int				nCID,
		INOUT char*				pUsernameBuffer,
		IN	  int				nUsernameBufferLen,
		INOUT int*				pActualLen
		) = 0;
	   
	virtual int GetCurrentState( //��ȡ��ǰ״̬
		IN	  int				nCID,
		INOUT E_RtCallState*	peState
		) = 0;
	
	virtual int GetDirection( //��ȡ���˵ĺ��з���
		IN	  int				nCID,
		INOUT E_RtDirection*	peDirect
		) = 0;

	virtual int GetRemoteBodyMediaType( //���Զ����Ϣ������
		IN    int				nCID,
		INOUT char*				pBuffer,
		IN    int				nBufferLen,
		INOUT int*				pActualLen
		) = 0;

	virtual int GetRemoteBody( //���Զ����Ϣ������
		IN    int				nCID,
		INOUT char*				pBuffer,
		IN    int				nBufferLen,
		INOUT int*				pActualLen
		) = 0;
	
	virtual int GetBoundaryBodyList( //���Զ�������Ϣ��
		IN	  int							nCID,
		INOUT std::list<T_RtSipMixerBody>&	lst
		) = 0;

	virtual int GetCallID( //��ȡCALL-ID
		IN	  int				nCID,
		INOUT char*				pszBuffer,
		IN	  int				bufLen,
		INOUT int*				pActualLen
		) = 0;

	virtual int GetFromTag( //��ȡFROM Tag
		IN	  int				nCID,
		INOUT char*				pszBuffer,
		IN	  int				bufLen,
		INOUT int*				pActualLen
		) = 0;

	virtual int GetValueForHeaderName( //����ض���Ϣͷ�ֶ�ֵ
		IN    int				nCID,
		IN	  char*				pHeaderName, //��������CALL-ID,From,Toͷ�ֶ�
		INOUT char*				pValueBuffer,
		IN	  int				nValueBufferLen,
		INOUT int*				pActualLen
		) = 0;

	virtual int GetResponseCode( //���л�ȡ������Ӧ��
		IN    int				nCID,
		INOUT int*				pnCode,
		INOUT char*				pszReason,   //ԭ������
		IN	  int				nReasonBufferLen
		) = 0;

	/*
	 * �������麯��
	 */
	virtual int ReferAccept( //����Refer���󲢷������
		IN    RtSubsHandle		hRtSubs,		//RecvReferEvent�ص��ṩ�þ��ֵ
		IN    const char*		pszCallee,
		IN    const RtSdpHandle	hSdp,
		IN	  const char*		pszConfPlainText,
		IN    const int			nConfPlainTextLen,
		IN    char*				pszBodyType,	//��Ϣ������,��ʽ��"[������]/[������]",���������Ϣ�岻��������Ϊtext/plain
		IN    char*				pszUserAgent,	//User-Agent Header Value
		IN    char*				pszSubject,		//Subject Header Value
		IN    char*				pszRequire,		//Require Header Value
		IN    char*				pszServer,		//Server Header Value
		IN    char*				pszLocalName,
		IN    void*				pAppData,
		INOUT int*				pnCID			//�º��е�CIDֵ
		) = 0;
	
	virtual int ReferAccept( //����Refer����, ֮�������ReferConnectCall()�������
		IN    RtSubsHandle		hRtSubs,		//RecvReferEvent�ص��ṩ�þ��ֵ
		INOUT int*				pnCID			//�º��е�CIDֵ
		) = 0;	
	
	virtual int ReferConnectCall( //ͨ��Refer����һ�����
		IN    int				nCID,
		IN    const char*		pszCallee,
		IN    const RtSdpHandle	hSdp,
		IN	  const char*		pszConfPlainText,
		IN    const int			nConfPlainTextLen,
		IN    char*				pszBodyType,	//��Ϣ������,��ʽ��"[������]/[������]",���������Ϣ�岻��������Ϊtext/plain
		IN    char*				pszUserAgent,	//User-Agent Header Value
		IN    char*				pszSubject,		//Subject Header Value
		IN    char*				pszRequire,		//Require Header Value
		IN    char*				pszServer,		//Server Header Value
		IN    char*				pszLocalName,
		IN    void*				pAppData
		) = 0;
	
	virtual int ReferSendNotify( //����һ��Refer������NOTIFY
		IN    RtSubsHandle		hRtSubs,
		IN    int				nStateCode
		) = 0;
	
	virtual int ReferReject( //�ܾ�Refer����
		IN    RtSubsHandle		hRtSubs,
		IN    unsigned int		nRejectCode
		) = 0;
	
	virtual int ReferTerminated( //��ֹRefer����
		IN    RtSubsHandle		hRtSubs
		) = 0;
	
	virtual int ReferSendRefer( //����һ��Refer����
		IN	  int				nCID,
		IN	  char*				pszReferTo,
		OUT   RtSubsHandle*		phRtSubs
		) = 0;


	/*
	 * �� NoRtp ģʽʹ�ú���
	 */
	virtual int MakeForPlain( //���к���
		IN  const int			nCID,
		IN  const char*			pszCallee,			//���к���,ע������д�Զ��˺�,δע������д�Է�IP��ַ
		IN  const char*			pRawBody,			//��Ϣ��,pRawBody[0]��Ӧ����0x0,����λ������0x0����
		IN	unsigned int		nBodyLen,			//��Ϣ�峤��
		IN	char*				pszBodyType,		//��ʽ��"[������]/[������]",�����������Ϊapplication/SDP
		IN  char*				pszUserAgent,		//NULL���޸�SIPͷ
		IN  char*				pszLocalUsername,	//��������,NULL:��ע��ʱΪ����ע���˺�,δע��ʱ��ΪUnknown
		IN  void*				pAppData,			//Ӧ�ò�APP����
		IN	char*				pszFromHost = NULL,	//ǿ�Ƹ���Fromͷ��Host (ȱʡNULLʱ: ��ע����ΪCMS��ַ,δע����Ϊ���˵�ַ)
		IN	char*				pszToHost = NULL	//ǿ�Ƹ���Toͷ��Host   (ȱʡNULLʱ: ��ע����ΪCMS��ַ,δע����ΪpszCallee��Host��ַ)
		) = 0;

	virtual int MakeForSdp( //���к���
		IN  const int			nCID,
		IN  const char*			pszCallee,
		IN	const RtSdpHandle	hSdp,
		IN  char*				pszUserAgent,
		IN  char*				pszLocalUsername,
		IN  void*				pAppData,
		IN	char*				pszFromHost = NULL,
		IN	char*				pszToHost = NULL
		) = 0;

	virtual int PickupForPlain( //����ժ��
		IN  int					nCID,
		IN  const char*			pRawBody,
		IN  unsigned int		nBodyLen,
		IN  char*				pszBodyType
		) = 0;

	virtual int PickupForSdp( //����ժ��
		IN  int					nCID,
		IN  const RtSdpHandle 	hSdp
		) = 0;


	/*
	 * �� RTP ģʽʹ�ú���
	 */	
	virtual int Make( //����
		IN  const int			nCID,
		IN  const char*			pszCallee,					//���к���,ע������д�Զ��˺�,δע������д�Է�IP��ַ
		IN  const char*			pszMediaCapaSet,			//ý�弯,�Զ��ŷָ�,��[0,8,100]
		IN  char*				pszUserAgent,				//NULL���޸�SIPͷ
		IN  char*				pszLocalUsername,			//��������,NULL:��ע��ʱΪ����ע���˺�,δע��ʱ�򲹳�ΪUnknown
		IN  void*				pAppData,					//Ӧ�ò�͸����������ָ��
		IN  char*				pszVideoCustomAttr = NULL,	//�û��Զ������Ƶ����
		IN  char*				pszFmtpInfo = NULL,			//FMTP��Ϣֵ,���ڱ�׼H264��MPEG4ʱ��ʽΪ:profile-level-id=<6�ֽ�>;packetization-mode=1;sprop-parameter-sets=<64λ����ֵ>
		IN  char*				pszAppHeaderName1 = NULL,	//�û��Զ�����չSIPͷ(��һ��)
		IN  char*				pszAppHeaderValue1 = NULL,	//�û��Զ�����չSIPͷ��ֵ(��һ��)
		IN  char*				pszAppHeaderName2 = NULL,	//�û��Զ�����չSIPͷ(�ڶ���)
		IN  char*				pszAppHeaderValue2 = NULL,	//�û��Զ�����չSIPͷ��ֵ(�ڶ���)
		IN  const int			nSendRecvMode = 0,			//RTP����ģʽ,0-SendRecv, 1-SendOnly, 2-RecvOnly 
		IN	char*				pszFromHost = NULL,			//ǿ�Ƹ���Fromͷ��Host (ȱʡNULLʱ: ��ע����ΪCMS��ַ,δע����Ϊ���˵�ַ)
		IN	char*				pszToHost = NULL			//ǿ�Ƹ���Toͷ��Host   (ȱʡNULLʱ: ��ע����ΪCMS��ַ,δע����ΪpszCallee��Host��ַ)
		) = 0;	
	
	virtual int Pickup( //����ժ��
		IN  int					nCID,
		IN  const char*			pszMediaCapaSet = NULL,		//ý�弯,�Զ��ŷָ�,��[0,8,100](��ȡ����ֵ, ΪNULL��ƥ������������)
		IN  char*				pszVideoCustomAttr = NULL,	//�û��Զ������Ƶ����
		IN  char*				pszFmtpInfo = NULL			//FMTP��Ϣֵ, ���ڱ�׼H264��MPEG4ʱ��ʽΪ:profile-level-id=<6�ֽ�>;packetization-mode=1;sprop-parameter-sets=<64λ����ֵ>
		) = 0;	

	virtual int PacketSend( //����RTP��(�Ǳ�׼��Ƶ��Ӧ���ñ�����,��׼H264Ӧ����PacketSendH264AnnexB����)
		IN	int					nCID,
		IN	E_RtMediaType		eMediaType,
		IN	char*				pszBuffer, 
		IN	int					nBufferLen,
		IN  bool				bSetMark = false //�Ա�׼��Ƶ��,bSetMark��Ч,һ֡���ݽ���������Markλ
		) = 0;	

	virtual int PacketSendH264AnnexB( //���ͱ�׼H264��Ƶ��,���������MTU����bUseFUA=true,��RFC3984����FU-A��Ƭ
		IN	  int				nCID,
		IN	  unsigned char*	pszBuffer,		//������AnnexB��λ������ 
		IN	  unsigned int		nBufferLen,		//AnnexB����
		IN    bool				bUseFUA = true	//������false,���������ݶ೤������RTP������,�������nDivBorderֵ����FUA��Ƭ
		) = 0;	

	virtual int GetRequestMediaType( //��������ý������,�����п���ͨ��״̬�µ���������֪���ս�����ý����·,����Ҳ����OFFERING�����Ի�֪������������
		IN	  int				nCID,
		INOUT bool*				pbHasAudio,
		INOUT bool*				pbHasVideo
		) = 0;
	
	virtual int GetCurrentPayload( //��ȡЭ�̺��ý���������
		IN	  int				nCID,
		IN	  E_RtMediaType		eMediaType,
		INOUT int*				pnPt //* auto-adapt for dynamic pt, return rtp's packet value 
		) = 0;  

	virtual int GetRemoteMediaInfo( //���Զ��ý����Ϣ,��������[0,8,100]
		IN	  int				nCID,
		INOUT char*				pBuffer,
		IN    int				nBufferLen,
		INOUT int*				pnConnMode //0-SendRecv, 1-SendOnly, 2-RecvOnly 
		) = 0;

	virtual int GetVideoChannelNumber( //����û��ض�����Ƶ��Ϣ
		IN	  int				nCID,
		INOUT char*				pBuffer,
		IN    int				nBufferLen
		) = 0;
	
	virtual int GetFmtpConfig( //���FMTP����(�����ڱ�׼H264),���ظ�ʽ:profile-level-id=<6�ֽ�>;packetization-mode=1;sprop-parameter-sets=<64λ����ֵ>��ʽ
		IN	  int				nCID,
		INOUT char*				pBuffer,
		IN    int				nBufferLen
		) = 0;


	virtual	int Redirect( //���и���ת����Ӧ�������
		IN    int				nCID
		) = 0;

	virtual int Hold( //������б���
		IN    int				nCID
		) = 0;
	
	virtual	int	Transfer( //�������ת��
		IN    int				nCID,
		IN    char*				szReferToUrl
		) = 0;	

	
	virtual int UdpSendByRtpSocket( //ͨ������RTP�˿ڷ���UDP����Զ��RTP�˿�(��Ϊջ������Holeý����·,һ��������ñ�����)
		IN	  int				nCID,
		IN	  E_RtMediaType		eMediaType
		) = 0;

	virtual int UdpSendByRtcpSocket( //ͨ������RTCP�˿ڷ���UDP����Զ��RTCP�˿�(��Ϊջ������Holeý����·,һ��������ñ�����)
		IN	  int				nCID,
		IN	  E_RtMediaType		eMediaType
		) = 0;

	virtual int PacketRecv( //��ѯģʽ����RTP��,����������������Ŀ,AfterPacketRecv()�������׵���
		IN	  int				nCID, 
		IN	  E_RtMediaType		eMediaType,
		INOUT int*				pnPt,
		OUT	  unsigned char**	ppBuffer,		//����Buffer,Ӧ�ò���������ڴ�
		INOUT int*				pnBufferLen,
		INOUT bool*				pbMark,
		INOUT unsigned int*		pnTimestamp,
		INOUT unsigned int*		pnSeqNo,
		OUT   void**			phRtpSession,	//ΪAfterPacketRecv()�ṩ����
		OUT   void**			phRtpPackage	//ΪAfterPacketRecv()�ṩ����
		) = 0;

	virtual void AfterPacketRecv( //����PacketRecv�����󣬱�����ñ�����ɾ��������Դ
		IN    void*				hRtpSession,
		IN    void*				hRtpPackage
		) = 0;

	virtual void SetAudioSampleTimePerRTP( //������Ƶһ�β���ʱ��, ����
		IN	  int				nCID,
		IN    int				nMillis
		) = 0;

	virtual void SetVideoSampleTimePerRTP( //������Ƶһ֡����ʱ��, ����
		IN	  int				nCID,
		IN    int				nMillis
		) = 0;

	virtual ~IRtCallAPI() = 0;
};

#endif 
