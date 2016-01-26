#ifndef __IWL_SIP_STACK_SIPREGAPI_H__
#define __IWL_SIP_STACK_SIPREGAPI_H__

typedef enum __e_RtRegClientState
{
	E_RT_REG_STATE_UNDEFINED				= -1, //��Ч
	E_RT_REG_STATE_IDLE						= 0,  //����
	E_RT_REG_STATE_PROCEEDING				= 1,  //����ע��
	E_RT_REG_STATE_OK						= 2,  //ע��ɹ�
	E_RT_REG_STATE_FAILED					= 3,  //ע��ʧ��
} E_RtRegClientState;

typedef enum __e_RtRegClientStateReason
{	
	E_RT_REG_REASON_UNDEFINED				= -1,
	E_RT_REG_REASON_NORMAL					= 0,  //����
	E_RT_REG_REASON_FAIL_UNAUTH				= 1,  //δͨ������������֤	
	E_RT_REG_REASON_FAIL_REDIRECTION		= 2,  //3xx��Ϣ(��Ҫ������һ��ַע��)
	E_RT_REG_REASON_FAIL_REJECT				= 3,  //4xx��Ϣ(�����ܾ�)
	E_RT_REG_REASON_FAIL_SERVER				= 4,  //5xx��Ϣ(������˹���)
	E_RT_REG_REASON_FAIL_GLOBAL				= 5,  //6xx��Ϣ(��ȫ���������)
	E_RT_REG_REASON_FAIL_TIMEOUT			= 6,  //��ʱ,��32s��û���յ���Ӧ
	E_RT_REG_REASON_FAIL_NETWORK			= 7	  //��ʧ��ԭ���ж��ֿ���: �����������/�����ڵķ�����/Զ���������
} E_RtRegClientStateReason;


class RTAPI IRtRegClientCBSink 
{
public:
	virtual	void StateChangeEvent(
		OUT unsigned int				nRID,
		OUT E_RtRegClientState			eState,
		OUT E_RtRegClientStateReason	eReason,
		OUT void*						pAppData
		) = 0;

	virtual ~IRtRegClientCBSink() = 0;
};

class RTAPI IRtRegClientAPI
{
public:
	virtual int Make( //��ע��
		IN    const char*			pszServer,
		IN    const char*			pszUsername,
		IN    const char*			pszPassword,
		IN    const int				nExpires, 
		IN    const char*			pszUserAgent,
		IN    void*					pAppData,
		INOUT int*					pnRID,
		IN    const char*			pszFromHost = NULL,	//ǿ�Ƹ���Fromͷ��Host(ȱʡNULLʱ:Ϊ��������ַ)
		IN    const char*			pszToHost = NULL	//ǿ�Ƹ���Toͷ��Host(ȱʡNULLʱ:Ϊ��������ַ)
		) = 0;	 
	
	virtual int MakeEx( //���ܿص���ע��(����Ҫ������ͬ��ַ�ķ���������ע��ʱʹ��)
		IN    const char*			pszServer,
		IN    const char*			pszUsername,
		IN    const char*			pszPassword,
		IN    const int				nExpires,
		IN    const char*			pszUserAgent,
		IN    void*					pAppData,
		INOUT int*					pnRID,
		IN    const char*			pszFromHost = NULL,
		IN    const char*			pszToHost = NULL
		) = 0; 
	
	virtual int Unregister( //ȡ��ע��
		IN    int					nRID
		) = 0; 
	
	virtual int Terminate( //ǿ����ֹע��
		IN    int					nRID
		) = 0;  
	
	virtual int GetExpiresTTL( //��ø�ע��ʣ��ʱ��(ms)
		IN    int					nRID, 
		INOUT unsigned*				pnTTL
		) = 0; 
	
	virtual int GetExpiresTime( //���ע����Ч��ʱ��
		IN    int					nRID, 
		INOUT int*					pnExpires
		) = 0;
	
	virtual int SetExpiresTime( //����ע����Ч��ʱ��
		IN    int					nRID, 
		IN    int					nExpires
		) = 0;
	
	virtual int GetAppData(  //���Ӧ�ò������
		IN    int					nRID, 
		OUT   void**				ppAppData
		) = 0; 
	
	virtual int SetAppData(  //����Ӧ�ò������
		IN    int					nRID, 
		IN    void*					pAppData
		) = 0; 
	
	virtual int GetServerInfo( //��÷�������Ϣ
		IN    int					nRID,
		INOUT char*					pszServerAddr,
		IN    unsigned				nBufferLen,
		INOUT unsigned*				pnBufferActualLen,
		INOUT unsigned*				pnServerPort
		) = 0;
	
	virtual int GetUserInfo( //��ñ���ע���û���Ϣ
		IN    int					nRID,
		INOUT char*					pszUsername,
		IN    unsigned				nBufferLen,
		INOUT unsigned*				pnBufferActualLen
		) = 0;
	
	virtual int GetCurrentState( //��õ�ǰ״̬
		IN    int					nRID, 
		INOUT E_RtRegClientState*	peState
		) = 0; 

	virtual ~IRtRegClientAPI() = 0;
};

#endif
