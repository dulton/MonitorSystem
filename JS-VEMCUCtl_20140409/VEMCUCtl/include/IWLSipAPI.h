#ifndef __IWL_SIP_STACK_SIPAPI_H__
#define __IWL_SIP_STACK_SIPAPI_H__

#include <list>

#if !defined(BYTE)
	#define BYTE unsigned char
#endif

#if !defined(FALSE)
	#define FALSE	0
	#define TRUE	1
#endif

#if !defined(IN)
	#define IN    //�����߷����ڴ�
#endif

#if !defined(OUT)
	#define OUT   //��������������ڴ�
#endif

#if !defined(INOUT)
	#define INOUT //�����߷����ڴ�
#endif

#if defined (_WIN32) || defined (_WIN64)
	#define RTAPI       __declspec(dllexport)
	#define RTCALLCONV  __stdcall
#else
	#define RTAPI
	#define RTCALLCONV
#endif

#define RT_DECLARE_HANDLE(_handleName) \
	typedef struct { int unused; } _handleName##__ ; \
	typedef const _handleName##__* _handleName; \
	typedef _handleName*  LP##_handleName

class RTAPI IRtCallCBSink;
class RTAPI IRtRegClientCBSink;
class RTAPI IRtTransactionCBSink;
class RTAPI IRtEventCBSink;

class RTAPI IRtCallAPI;
class RTAPI IRtRegClientAPI;
class RTAPI IRtTransactionAPI;
class RTAPI IRtSdpAPI;
class RTAPI IRtEventAPI;

typedef enum __e_RtSipResultCode
{
	E_RT_OK							= 1,	//�ɹ�
	E_RT_ERROR_UNKNOWN				= -1,	//δ֪����
	E_RT_ERROR_OUTOFRESOURCES		= -2,	//û����Դ����
	E_RT_ERROR_BADPARAM				= -3,	//��������
	E_RT_ERROR_NULLPTR				= -4,	//ָ��Ϊ��
	E_RT_ERROR_NOTSUPPORTED			= -7,	//����������
	E_RT_ERROR_UNINITIALIZED		= -8,	//δ��ʼ��
	E_RT_ERROR_NETWORK_PROBLEM		= -11,	//�����쳣
	E_RT_ERROR_INVALID_HANDLE		= -12,	//��Ч�ľ��
	E_RT_ERROR_NOT_FOUND			= -13,	//�������ҵ�
	E_RT_ERROR_INSUFFICIENT_BUFFER	= -14,	//������ڴ�ߴ�̫С
	E_RT_ERROR_OBJ_EXISTED			= -15,	//�����Ѵ���
	E_RT_ERROR_UNAUTHED				= -16,	//δ��֤
} E_RtSipResultCode;

typedef enum __e_RtDirection
{
	E_RT_DIRECTION_UNDEFINED		= -1,
	E_RT_DIRECTION_IN				= 0,	//���еı��л�����Ľ�����
	E_RT_DIRECTION_OUT				= 1,	//���е����л�����ķ�����
} E_RtDirection;

typedef enum __e_RtRejectCode
{
	E_RT_REJECT_UNDEFINED			= -1,
	E_RT_REJECT_NORMAL				= 0,	//�ܾ�
	E_RT_REJECT_SERVER_ERROR		= 1,	//����������
	E_RT_REJECT_GLOBAL_ERROR		= 2,	//ȫ�ִ���
} E_RtRejectCode; 

typedef enum __e_RtTransportType
{
	E_RT_TRANSPORT_UNDEFINED		= -1,
	E_RT_TRANSPORT_UDP				= 0,
	E_RT_TRANSPORT_TCP				= 1,		
	E_RT_TRANSPORT_TLS				= 2,
	E_RT_TRANSPORT_SCTP				= 3,
	E_RT_TRANSPORT_RTP				= 4,
} E_RtTransportType;

typedef enum  __e_RtTransportAddressType
{
    E_RT_TRANSADDRESS_UNDEFINED		= -1,
	E_RT_TRANSADDRESS_IP4			= 0,
	E_RT_TRANSADDRESS_IP6			= 1,
} E_RtTransportAddressType;

typedef struct __t_RtSipUrlInfo
{
    char						szUser[64];
	char						szHost[52];
    unsigned					portNum;
    E_RtTransportType			eTransport;
	E_RtTransportAddressType	eAddrType;
} T_RtSipUrlInfo;

typedef enum __e_RtIID
{
	E_IID_ISIPCALL,				//���нӿ�
	E_IID_ISIPTRANS,			//����ӿ�
	E_IID_ISIPREG,				//ע��ӿ�
	E_IID_ISIPEVENT,			//�¼��ӿ�
	E_IID_ISDPSTACK,			//SDP �ӿ�
	E_IID_ISIPUNKNOW,			//��Ч
} E_RtIID; 

typedef enum __e_RtDynPtMedia
{
	E_RT_DPT_MEDIA_UNDEFINED	= -1,
	E_RT_DPT_MEDIA_H264,		//H264
	E_RT_DPT_MEDIA_MPEG4,		//MPEG4
	E_RT_DPT_MEDIA_AVS,			//AVS-P2
	E_RT_DPT_MEDIA_HIK264,		//����
	E_RT_DPT_MEDIA_DAH264,		//��
	E_RT_DPT_MEDIA_DAL264,		//����
	E_RT_DPT_MEDIA_RFC2833,		//DTMF
	E_RT_DPT_MEDIA_SPEEX_8K,	//8k  SPEEX
	E_RT_DPT_MEDIA_SPEEX_16K,	//16k SPEEX
	E_RT_DPT_MEDIA_AMR_8K,		//8k  AMR
	E_RT_DPT_MEDIA_AMR_16K,		//16k AMR
	E_RT_DPT_MEDIA_H263_1998,	//H263v2
	E_RT_DPT_MEDIA_H263_2000,	//H263v3
} E_RtDynPtMedia; 

typedef enum __e_RtMediaType
{
	E_RT_MEDIA_TYPE_UNDEFINED	= -1,
	E_RT_MEDIA_TYPE_AUDIO,		//����
	E_RT_MEDIA_TYPE_VIDEO,		//��Ƶ
	E_RT_MEDIA_TYPE_APP,		//Ӧ�ù���
	E_RT_MEDIA_TYPE_CONTROL,	//������
} E_RtMediaType;

typedef enum __e_RtRtcpPacketType
{ 
	E_RT_RTCP_PACKET_SR,
	E_RT_RTCP_PACKET_RR,
	E_RT_RTCP_PACKET_SDES,
	E_RT_RTCP_PACKET_BYE,
	E_RT_RTCP_PACKET_APP,
	E_RT_RTCP_PACKET_UNKNOWN,
} E_RtRtcpPacketType;

typedef struct __t_RtQOS4
{
	unsigned int			nFractionLost;		//���ն˵�ƽ��������
	unsigned int			nLostCount;			//���ն˵Ķ�������
	unsigned int			nIntervalJitter;	//���ն˵�Jitter����(����)
	unsigned int			nLocalJitter;		//���˸����㷨�ó���Jitter��ֵ(����)
	float					fLocalRoundtrip;	//���˸����㷨�ó���ƽ����·ʱ��(����)
	float					fLocalBandwidth;	//���˸����㷨�ó��Ĵ���(kbps)
} T_RtQOS4;

typedef struct __t_RtStackCallBack
{
	IRtCallCBSink*			pCallSink;
	IRtRegClientCBSink*		pRegClientSink;
	IRtTransactionCBSink*	pTransactionSink;
	IRtEventCBSink*			pEventSink;
} T_RtStackCallBack;

typedef enum __e_RtStackLogFilters
{
	RT_SIP_LOG_INFO			= 0x02,	//����
	RT_SIP_LOG_WARN			= 0x04,	//����,һ�㲻�������̽���
	RT_SIP_LOG_ERROR		= 0x08,	//����,һ�㵼������ʧ�ܻ������ش���
	RT_SIP_LOG_EXCEP	    = 0x10,	//�쳣,һ���ڿ������������Ӧ����������
	RT_RTP_LOG				= 0x20,	//RTP,�������ļ�,���鲿��ʱ��Ҫ����
} E_RtStackLogFilters; 

typedef struct __t_RtStackConfigParam
{
	char	szLocalUdpAddress[56];	//ջ��UDP��ַ��"0.0.0.0"��ʾʹ�ö�Ѩ
	int		nLocalUdpPort;			//ջ��UDP�˿ڣ�����0��ʾ5060
	bool	bTcpEnabled;			//�Ƿ�����TCP��trueʹ�ã�false��ʹ��
	char	szLocalTcpAddress[56];	//TCP��ַ��"0.0.0.0"��ʾʹ�ö�Ѩ
	int		nLocalTcpPort;			//TCP�˿ڣ�����0��ʾ5060
	char	szObdProxyAddress[56];  //�����������ַ(ȱʡ��ʹ��)
    int		nObdProxyPort;			//����������˿�
	char	szDnsServerList[256];	//DNS�������б�(ip1:port1;ip2:port2;...�ձ�ʾ��������������)
	bool	bManualProv;			//�ֶ�������ʱ��Ӧ�������������ó�false

	int		nMaxRegister;			//����û���
	int		nMaxCall;				//��������
	int		nMaxTransactions;		//���������
	int		nProcessingThreads;		//�����߳���(������ʾʹ�õ��߳�, >0�û��̶����ö��߳���Ŀ)
	int		nLogLevel;				//��־�ȼ�(0x0:����־����ȼ�����λ�������: RT_SIP_LOG_INFO|RT_SIP_LOG_ERROR)
	char	szLogBaseName[56];		//��־�ļ�������(����·�������·����ջ���Զ�׷��_n.log)

	bool	bUseJRtpCall;			//true��ʾʹ��"rtpģʽ"��false��ʾʹ��"non-rtpģʽ"
	int		nMinRtpPort;			//RTP�˿���Сֵ(��bUseJRtpCall=true��Ч)
	int		nMaxRtpPort;			//RTP�˿����ֵ(��bUseJRtpCall=true��Ч)
	bool	bUseFastRtpProcess;		//ʹ�ÿ���RTP����(��bUseJRtpCall=true��Ч, ���Ϊtrue, RTCP����Ӧ�ò���������)
	bool	bRecvRtpUseLoop;		//ʹ��Loopģʽ����RTP����(���鲻Ҫ��Ϊtrue, ��Loopģʽ��RTCPҲ��APP��������)

	int		nNatHoleMilliSecond;	//NAT�ϻ�ʱ��,����(���ڱ������ע�������λ��NAT����Ч)
	bool	bEnServerAuth;			//�Ƿ������������֤����(Ĭ�ϲ�����)
	int		nFirstNotifyTimer;		//�����ߵȴ���һ��NOTIFY���������
	int		nDivPacketMode;			//�Ǳ�׼�����͸�ʽ: 0=ֱ�ӷ���, 1=��nDivBorderֵ�ָ��
	int		nDivBorder;				//RTP������󳤶�,ȡֵ��ΧӦС��MTU
} T_RtStackConfigParam;

class RTAPI CRtSipStackManager
{
public:
	static CRtSipStackManager*	Instance();
	virtual ~CRtSipStackManager();

	int	  InitEngineer(IN T_RtStackConfigParam* pCfg); //��ʼ������

	int   SetModuleCallback(IN T_RtStackCallBack* pSinkList); //���ûص�
	
	int	  StartEngineer(); //��������

	int   StopEngineer();  //�ر�����

	int	  QueryInterface(IN const E_RtIID& IID, OUT void** ppv); //��ѯ�ӿ���ָ��

	int   SetSpecMediaPayload(IN E_RtDynPtMedia eMedia, IN int pt); //������̬PTֵ

protected:
	CRtSipStackManager();

private:
	IRtCallAPI*					m_pCall;
	IRtRegClientAPI*			m_pRegClient;
	IRtTransactionAPI*			m_pTransaction;
	IRtSdpAPI*					m_pSdp;
	IRtEventAPI*				m_pEvent;
	static CRtSipStackManager*	m_pInstance;
};

#endif
