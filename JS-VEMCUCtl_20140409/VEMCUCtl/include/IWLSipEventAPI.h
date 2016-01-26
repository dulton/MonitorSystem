#ifndef __IWL_SIP_STACK_SIPEVENTAPI_H_
#define __IWL_SIP_STACK_SIPEVENTAPI_H_

typedef enum  __e_RtEventState
{
	E_RT_EVENT_STATE_UNDEFINED				= -1,	//��Ч
	E_RT_EVENT_STATE_IDLE					= 0,	//����
	E_RT_EVENT_STATE_SUER_PROCEEDING		= 1,	//�����ѷ���(������)
	E_RT_EVENT_STATE_SUER_EXPIRE_ALERT		= 2,	//���ļ�������(������)
	E_RT_EVENT_STATE_SUER_NOTIFY_RCVD		= 3,	//�յ��¼�(������)
	E_RT_EVENT_STATE_PUER_RCVD				= 5,	//���������յ�(������)
	E_RT_EVENT_STATE_PUER_WAIT_PROCESS		= 6,	//�ȴ�����������(������)
	E_RT_EVENT_STATE_PUER_REFRESH_WAIT_PROCESS = 7,	//�ȴ�����ˢ�¶�������(������)
	E_RT_EVENT_STATE_ACTIVATED				= 9,	//���ļ���(������+������)
	E_RT_EVENT_STATE_TERMINATED				= 10,	//���Ľ���(������+������)
} E_RtEventState;

typedef enum __e_RtEventStateReason
{	
	E_RT_EVENT_REASON_UNDEFINED				= -1,	
	E_RT_EVENT_REASON_NORMAL				= 0,
	E_RT_EVENT_REASON_REMOTE				= 1,	//Զ�˽���
	E_RT_EVENT_REASON_LOCAL					= 2,	//���˽���
	E_RT_EVENT_REASON_UNKNOW				= 3,	//����ȷԭ��
} E_RtEventStateReason;

typedef enum __e_RtEventSubsState
{	
	E_RT_EVENT_SUBSSTATE_UNDEFINED			= -1,
	E_RT_EVENT_SUBSSTATE_ACTIVE				= 1,	//���Ļ
	E_RT_EVENT_SUBSSTATE_PENDING			= 2,	//���ĵȴ�����
	E_RT_EVENT_SUBSSTATE_TERMINATED			= 3,	//������ֹ
} E_RtEventSubsState;


class RTAPI IRtEventCBSink
{
public:
	virtual	void StateChangeEvent(
		OUT unsigned int			nSID,
		OUT E_RtEventState			eState,
		OUT E_RtEventStateReason	eReason,
		OUT void*					pAppData
		) = 0;

	virtual ~IRtEventCBSink() = 0;
};

class RTAPI IRtEventAPI
{
public:
	// ***** �� �� �� �� �� �� ****** //
	
	virtual int  ProduceSID(
		INOUT int*				pnSID
		) = 0;

	virtual int MakeSubs( //�����߷���һ���¶���
		IN  int					nSID,
		IN  const char*			pszDestUri,			//������URI,�Զ˵��˺Ż�IP��ַ
		IN  const char*			pszBody,			//�������Ϣ��
		IN  unsigned int		nBodyLen,			//��Ϣ��ĳ���
		IN  char*				pszLocalName,		//ǿ�Ƹ���Fromͷ��User(NULLʱ:��ע��Ϊ�����˺�,δע����ΪUnknown)
		IN  unsigned int		nExpireSecond,		//ע����Ч��,��λ��
		IN  const char*			pszEvent,			//���ĵ��¼�����,�����ʽ:eventPackageX.eventTemplateY
		IN  void*				pAppData,			//Ӧ�ò�APP����
		IN  char*				pszBodyType,		//��Ϣ������,��ʽ��"[������]/[������]",���������Ϣ�岻��������Ϊtext/plain
		IN	char*				pszFromHost = NULL,	//ǿ�Ƹ���Fromͷ��Host (ȱʡNULLʱ: ��ע����ΪCMS��ַ,δע����Ϊ���˵�ַ)
		IN	char*				pszToHost = NULL	//ǿ�Ƹ���Toͷ��Host   (ȱʡNULLʱ: ��ע����ΪCMS��ַ,δע����ΪpszDestUri��Host��ַ)
		) = 0; 

	virtual int RefreshSubs( //������ˢ�¶���(��E_RT_EVENT_STATE_SUER_EXPIRE_ALERT�µ���)
		IN  int					nSID,
		IN  unsigned int		nExpireSecond,
		IN  const char*			pszBody,
		IN  unsigned int		nBodyLen,
		IN  char*				pszBodyType			//��Ϣ������,��ʽ��"[������]/[������]",���������Ϣ�岻��������Ϊtext/plain
		) = 0; 

	virtual int Unsubscribe( //������ȡ������
		IN  int					nSID
		) = 0;

	virtual int AcceptSubs( //�����߽��ܶ���
		IN  int					nSID, 
		IN  int					nRefreshTime = -1, //������Ч��,����-1��ʾ��SUBSCRIBE������ʱ��Ϊ��	
		IN  const char*			pszBody = NULL,    //��Ӧ����Ϣ��
		IN  unsigned int		nBodyLen = 0,	   //��Ϣ�峤��
		IN  char*				pszBodyType = NULL //��Ϣ������,��ʽ��"[������]/[������]",���������Ϣ�岻��������Ϊtext/plain
		) = 0; 

	virtual int RejectSubs( //�����߾ܾ�����
		IN  int					nSID, 
		IN  unsigned int		nCode,
		IN  const char*			pszBody = NULL,
		IN  const int			nBodyLen = 0,
		IN  char*				pszBodyType = NULL //��Ϣ������,��ʽ��"[������]/[������]",���������Ϣ�岻��������Ϊtext/plain
		) = 0; 

	virtual int TerminatedSubs( //���Ľ���(����ݵ�ǰ״̬������δ���)
		IN  int					nSID
		) = 0;

	/*
	 * �������� E_RT_EVENT_STATE_PUER_WAIT_PROCESS �� E_RT_EVENT_STATE_PUER_REFRESH_WAIT_PROCESS ״̬�µ���
	 */
	virtual int GetRemoteBody4Subs( //���Subs���̵�BODY����
		IN    int				nSID,
		INOUT char*				pBuffer,
		IN    int				nBufferLen,
		INOUT int*				pActualLen
		) = 0;


	// ***** ͨ ֪ �� �� �� �� ****** //

	virtual int MakeNotify( //������֪ͨ�¼�����
		IN  int					nSID,
		IN  const char*			pszBody, 
		IN  unsigned int		nBodyLen,
		IN  E_RtEventSubsState	eSubstate,
		IN  char*				pszBodyType //��Ϣ������,��ʽ��"[������]/[������]",���������Ϣ�岻��������Ϊtext/plain
		) = 0; 

	/*
	 * ��������E_RT_EVENT_STATE_SUER_NOTIFY_RCVD״̬�µ���
	 */
	virtual int GetRemoteBody4Notify( //���Notify���̵�BODY����
		IN    int				nSID,
		INOUT char*				pBuffer,
		IN    int				nBufferLen,
		INOUT int*				pActualLen
		) = 0;


	// ***** ͨ �� �� �� �� �� ****** //

	virtual int GetAppData( //���Ӧ�ò�����
		IN	  int				nSID,
		OUT   void**			ppAppData
		) = 0;
		
	virtual int SetAppData( //����Ӧ�ò������
		IN	  int				nSID,
		IN	  void*				pAppData
		) = 0;
	
	virtual int GetSuerInfo( //��ö�������Ϣ
		IN    int				nSID,
		INOUT T_RtSipUrlInfo*	pSuer
		) = 0;
	
	virtual int GetPuerInfo( //��÷�������Ϣ
		IN    int				nSID,
		INOUT T_RtSipUrlInfo*	pPuer
		) = 0;

	virtual int GetCurrentState( //��ȡ��ǰ״̬
		IN	  int				nSID,
		INOUT E_RtEventState*	pState
		) = 0;

	virtual int GetExpiresVal( //��ö�����Ч��
		IN	  int				nSID,
		INOUT int*				pnExpires
		) = 0;

	virtual ~IRtEventAPI() = 0;
};

#endif
