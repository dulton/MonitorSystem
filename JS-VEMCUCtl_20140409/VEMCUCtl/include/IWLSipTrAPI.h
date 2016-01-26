#ifndef __IWL_SIP_STACK_SIPTRAPI_H__
#define __IWL_SIP_STACK_SIPTRAPI_H__

typedef enum __e_RtMethodType
{
	E_RT_METHOD_TYPE_UNDEFINED				= -1,
	E_RT_METHOD_TYPE_MESSAGE				= 0,
	E_RT_METHOD_TYPE_INFO					= 1,
	E_RT_METHOD_TYPE_OPTIONS				= 2,
	E_RT_METHOD_TYPE_NOTIFY					= 3,
	E_RT_METHOD_TYPE_UPDATE					= 4,
	E_RT_METHOD_TYPE_REGISTER				= 5,
} E_RtMethodType;

typedef enum  __e_RtTransactionState
{ 
	E_RT_TRANSC_STATE_UNDEFINED				= -1,	//��Ч
	E_RT_TRANSC_STATE_IDLE					= 0,	//����
	E_RT_TRANSC_C_STATE_OK					= 1,	//���н��ܷ��͵�����(UAC)
	E_RT_TRANSC_C_STATE_FAIL				= 2,	//���оܾ����͵�����(UAC)
	E_RT_TRANSC_C_STATE_PROCEEDING			= 3,	//�������ڴ�������  (UAC)
	E_RT_TRANSC_S_STATE_RECV_REQ			= 4,	//�յ����з�������  (UAS)
	E_RT_TRANSC_S_STATE_WAIT_USER_PEOCESS	= 5,	//�ȴ��û���������  (UAS)
	E_RT_TRANSC_S_STATE_USER_ACK_ARRIVED	= 6,	//��Ӧ��Ϣ���ͳɹ�  (UAS)
	E_RT_TRANSC_S_STATE_USER_ACK_DISCARD	= 7,	//��Ӧ��Ϣ����ʧ��  (UAS)
	E_RT_TRANSC_S_STATE_SET_PASSWORD		= 8,	//�ȴ��û�Ϊע��������������(UAS)
} E_RtTransactionState; 

typedef enum __e_RtTransactionStateReason
{
	E_RT_TRANSC_REASON_UNDEFINED			= -1,	//��Ч
	E_RT_TRANSC_REASON_NORMAL				= 0,	//����
	E_RT_TRANSC_REASON_FAIL_REDIRECTION		= 1,	//3xx��Ϣ (UAC)
	E_RT_TRANSC_REASON_FAIL_REJECT			= 2,	//4xx��Ϣ (UAC)
	E_RT_TRANSC_REASON_FAIL_SERVER			= 3,	//5xx��Ϣ (UAC)
	E_RT_TRANSC_REASON_FAIL_GLOBAL			= 4,	//6xx��Ϣ (UAC)
	E_RT_TRANSC_REASON_FAIL_NETWORK			= 5,	//�������(UAC)
	E_RT_TRANSC_REASON_FAIL_CANCEL			= 6,	//����ȡ��(UAC)
	E_RT_TRANSC_REASON_FAIL_TIMEOUT			= 7,	//��ʱ    (UAC)
} E_RtTransactionStateReason; 

class RTAPI IRtTransactionCBSink
{
public:
	virtual	void StateChangeEvent(
		OUT unsigned int				nTID,
		OUT E_RtTransactionState		eState,
		OUT E_RtTransactionStateReason	eReason,
		OUT void*						pAppData
		) = 0;

	virtual ~IRtTransactionCBSink() = 0;
};

class RTAPI IRtTransactionAPI
{
public:
	virtual int ProduceTID( //���в�������������
		INOUT int*				pnTID, 
		IN    void*				pAppData
		) = 0;

	virtual int Cancel(  //����ȡ����������
		IN  int					nTID
		) = 0;

	virtual int Reject( //���оܾ���������
		IN  int					nTID,
		IN	E_RtRejectCode		eCode
		) = 0;

	virtual int SendResponseCode( //���з�����Ӧ����
		IN  int					nTID, 
		IN  int					nCode
		) = 0;

	virtual int Terminate( //���л򱻽���ֹ����(���ݵ�ǰ״̬����������ʽ,�Ƽ�)
		IN  int					nTID
		) = 0;

	virtual int SetAppData( //����APP����
		IN    int				nTID, 
		INOUT void*				pAppData
		) = 0;
	
	virtual int Make( //���з�������
		IN  int					nTID,
		IN  const char*			pszDestUri,						//���е��˺Ż��ַ
		IN  E_RtMethodType		eMethodType,					//����ķ�������
		IN  const char*			pszBody,						//��Ϣ������
		IN  unsigned int		nBodyLen,						//��Ϣ�峤��
		IN  const char*			pszUserAgent = NULL,			//User-Agent
		IN  char*				pszAppHeaderName1 = NULL,		//��һ���Զ���ͷ
		IN  char*				pszAppHeaderValue1 = NULL,		//��һ���Զ���ֵ
		IN  char*				pszAppHeaderName2 = NULL,		//�ڶ����Զ���ͷ
		IN  char*				pszAppHeaderValue2 = NULL,		//�ڶ����Զ���ֵ
		IN  char*				pszLocalUsername = NULL,		//ǿ�Ƹ���Fromͷ��User (ȱʡNULLʱ: ��ע����Ϊ�����˺�,δע����ΪUnknown)
		IN	char*				pszBodyType = NULL,				//��Ϣ������,��ʽΪ"������/������",�������ȱʡΪtext/plain
		IN	char*				pszFromHost = NULL,				//ǿ�Ƹ���Fromͷ��Host (ȱʡNULLʱ: ��ע����ΪCMS��ַ,δע����Ϊ���˵�ַ)
		IN	char*				pszToHost = NULL				//ǿ�Ƹ���Toͷ��Host   (ȱʡNULLʱ: ��ע����ΪCMS��ַ,δע����ΪpszDestUri������Hostֵ)
		) = 0;		
	
	virtual int Accept( //���н�������
		IN  int					nTID, 
		IN  const char*			pszBody = NULL,					//��Ϣ������
		IN  unsigned int		nBodyLen = 0,					//��Ϣ�峤��
		IN	char*				pszBodyType = NULL,				//��Ϣ������,��ʽ��"������/������",�������ȱʡΪtext/plain
		IN  const char*			pRegName = NULL,				//����յ�����Ϣ��Register,������������д,���ڹ���Contact,��ͨ��GetRegisterInfo()�����Ϣ
		IN  const char*			pRegAddress = NULL,				//����յ�����Ϣ��Register,������������д,���ڹ���Contact,��ͨ��GetRegisterInfo()�����Ϣ
		IN  int					nRegRefreshTime = 50			//����յ�����Ϣ��Register,������������д,���ڹ���Contact,��ͨ��GetRegisterInfo()�����Ϣ
		) = 0;
	
	virtual int GetReceiverInfo( //��ñ�����Ϣ
		IN    int				nTID,
		INOUT T_RtSipUrlInfo*	pReceiver
		) = 0;

	virtual int GetSenderInfo( //���������Ϣ
		IN    int				nTID,
		INOUT T_RtSipUrlInfo*	pSender
		) = 0;

	virtual int GetRemoteBody( //��öԷ�����Ϣ��
		IN    int				nTID, 
		INOUT char*				pBodyStr,
		IN    int				nBodyLen,
		INOUT int*				pActualLen,
		INOUT char*				pContentType = NULL
		) = 0;
	
	virtual int GetMethod( //��÷���
		IN    int				nTID, 
		INOUT E_RtMethodType*	peMethod
		) = 0;
	
	virtual int GetDirection( //��ú��з���
		IN	  int				nTID, 
		INOUT E_RtDirection*	peDirection
		) = 0;
	
	virtual int GetCurrentState( //��õ�ǰ״̬
		IN    int					nTID, 
		INOUT E_RtTransactionState*	peState
		) = 0;

	virtual int GetAppData( //���APP����
		IN    int				nTID, 
		OUT   void**			ppAppData
		) = 0;

	virtual int GetValueForHeaderName( //���ָ��ͷ��ֵ(��������CALL-ID,FROM,TO,CONTENT-TYPE)
		IN    int				nTID,
		IN	  char*				pHeaderName,
		INOUT char*				pValueBuffer,
		IN	  int				nValueBufferLen,
		INOUT int*				pActualLen
		) = 0;

	virtual int SetPassword( //����Ϊע��������������
		IN    int				nTID,
		IN	  char*				pszPassword
		) = 0;

	virtual int GetRegisterInfo( //���л��ע���������Ϣ
		IN	  int				nTID,
		INOUT T_RtSipUrlInfo*	pSender,
		INOUT unsigned*			pnExpires
		) = 0;

	virtual ~IRtTransactionAPI() = 0;
};

#endif
