#ifndef __IWL_SIP_STACK_PORTAPI_H__
#define __IWL_SIP_STACK_PORTAPI_H__

typedef struct __t_RtCommConfigParam 
{
	int		maxUserFd;		//����豸�����
	int		maxUserTimers;	//���ʱ����
} T_RtCommConfigParam;

class RTAPI CRtCommEngineer 
{
public:
	static CRtCommEngineer*	Instance();
	virtual ~CRtCommEngineer();
	
	int	  Init(IN T_RtCommConfigParam* pCfg);
	int	  Start();
	int   Stop();

protected:
	CRtCommEngineer();
	
private:
	static CRtCommEngineer*	m_pInstance;
};

#if defined (_WIN32)
	#define RT_COMM_INT64			__int64
	#define RT_COMM_UINT64			unsigned __int64
	#define RT_INT64_SUFFIX(_n)		_n ## i64
	#define RT_UINT64_SUFFIX(_n)	_n ## Ui64
#else
	#define RT_COMM_INT64			signed long long
	#define RT_COMM_UINT64			unsigned long long
	#define RT_INT64_SUFFIX(_n)		_n ## LL
	#define RT_UINT64_SUFFIX(_n)	_n ## ULL
#endif

class RTAPI CRtCommSData 
{
public:
	static char* I64UtoA(IN RT_COMM_UINT64 num64, INOUT char* pBuf);  //64λ�ַ���(����ֵΪNULL��ʾʧ�ܣ���ͬ)
	static char* I64toA(IN RT_COMM_INT64 num64, INOUT char* pBuf);    //64λ�ַ���
	static char* I64toHex(IN RT_COMM_UINT64 num64, INOUT char* pBuf); //64λHex�ַ���
};

typedef struct __t_RtClock
{
	unsigned int sec;	//��
	unsigned int usec;	//΢��(1s = 1000ms = 1000*1000us = 1000*1000*1000ns)
} T_RtClock;

typedef struct __t_RtNTP
{
	unsigned int msw;	//��32λ
	unsigned int lsw;	//��32λ
} T_RtNTP;

typedef struct __t_RtTm
{
	unsigned	 tm_nsec;	//����(��֮���ʣ��ֵ���������)
	int			 tm_sec;	//��	   [0-60]
	int			 tm_min;	//��       [0-59]
	int			 tm_hour;	//ʱ	   [0-23]
	int			 tm_mday;	//��	   [1-31]
	int			 tm_mon;	//��	   [0-11]
	int			 tm_year;	//��	   (Year-1900)
	int			 tm_wday;	//��       [0-6]
	int			 tm_yday;	//�ڼ���   [0-365]
	int			 tm_isdst;	//�������� [-1/0/1]
} T_RtTm;

class RTAPI CRtCommTime
{
public:
	/* ----------------   ����ʱ�Ӻ���  ----------------- */
	static unsigned int  GetSecond4Power(); //����Կ�������������
	static unsigned int  GetMilli4Power();	//����Կ��������ĺ�����
	static RT_COMM_INT64 GetNano4Power();	//����Կ���������������

	/* -----------------   ʱ�Ӻ���  ----------------- */
	static int  GetClock( //��õ�ǰʱ��
		INOUT T_RtClock*	t);
	
	static int	SetClock( //����ʱ��
		IN	  T_RtClock*	t);	

	static int  ConstructClockFrom64( //ͨ�����빹��ʱ��
		IN    RT_COMM_INT64	nNanosecs,
		INOUT T_RtClock*	t);

	static RT_COMM_INT64 ConvertClockTo64( //ת����64λ����ʱ�ӷ���
		IN	  T_RtClock*	t);	

	static int ConvertClockToNTP( //ת����NTP
		IN    T_RtClock&	clock, 
		INOUT T_RtNTP&		ntp);

	static int ConvertNTPToClock( //ת����Clock
		IN	  T_RtNTP&		ntp, 
		INOUT T_RtClock&	clock);

	static int  CompareClock( //�Ƚ�ʱ��(t1>t2����1)
		IN	  T_RtClock*	t1, 
		IN	  T_RtClock*	t2);

	static int  ClockAdd( //����ʱ��
		INOUT T_RtClock*	t, 
		IN    int			nSec,
		IN    int			nUs); 
		
	/* -----------------   ʱ�亯��  ----------------- */
	static int GetLocalTm( //��ñ���ʱ��
		IN    T_RtClock*	t, 
		INOUT T_RtTm*		pTM);

	static int GetUtcTm( //���UTCʱ��
		IN    T_RtClock*	t, 
		INOUT T_RtTm*		pTM);

	static int TmAsctime( //��ʱ��ת����[week month day hour:min:sec year]
		IN    T_RtTm*		pTM,
		INOUT char*			pBuffer,
		IN    int			nBufferLen);
};

typedef struct __t_RtRTProfile
{
	char			szEncodeName[56];	//�ñ��������,��"H264"
	int				nMediaType;			//�ñ����ý������(0=Audio, 1=Video)
	unsigned int	nClockRate;			//�ñ���Ĳ���Ƶ��,��"90000"
	char			szRateDesc[56];		//�ñ��������˵��(����Ƶ������,һ������ֵ)
	double			fBandwidth;			//�ñ���Ĵ���˵��(kb/s,����Ƶ������)
	E_RtDynPtMedia	eDyncMedia;			//����̬PT��ֵ��Ч�����������򷵻�E_RT_DPT_MEDIA_UNDEFINED
} T_RtRTProfile;

class RTAPI CRtCommParse 
{
public:
	static int GetH264FmtpConfig( //����H264��SPS��PPS��fmtp���� [[�������漴�ܵ���]]
		IN	  unsigned char*	pszAnnexB,			//������AnnexB��,��0x000001 or 0x00000001 ��ʼ��SPS+PPS NALu
		IN	  unsigned int		nAnnexBLen,			//AnnexB����
		INOUT char*				pFmtpConfig,		//���FMTP��,��ʽΪprofile-level-id=<6�ֽ�>;packetization-mode=1;sprop-parameter-sets=<64λ����ֵ>
		IN	  int				nFmtpConfigLen);	//�������100���ֽ�

	static int ParseRtpProfile( //����RTP Profile�Ķ��� [[�������漴�ܵ���]]
		IN    const int			nPayload,
		INOUT T_RtRTProfile&	tProfile);
	
	static int ParseSipUri( //����SipUri�ɽṹ [[��SIP������������Ч]]
		IN    const char*		pszString, 
		INOUT T_RtSipUrlInfo&	tSipUrl);

	static bool GetMasterAddr(char* pMasterAddr); //��ñ���������ַ
};


class RTAPI CRtCommLog 
{
public:
	static void PError(char* buffer, ...);	
	static void PWarning(char* buffer, ...);
	static void PInfo(char* buffer, ...);
	static void PDebug(char* buffer, ...);
	static void PDbgView(char* buffer, ...); //����Ϣ�����DebugView��(��Windows���׼���)
};


#if defined (_WIN32) || defined (_WIN64)
	typedef struct __t_RtThread
	{
		void*		 h;
		unsigned	 id;
	} T_RtThread;
#else
	typedef pthread_t T_RtThread;
#endif

typedef void* (*pfnThreadEv)(void* pContext); //�̻߳ص�����

class RTAPI CRtCommThread 
{
public:	
	static T_RtThread*	Create(IN pfnThreadEv pFunc, IN void* pAppContext); //�����߳�
	static int			Join(IN T_RtThread* pThread); //�ȴ��߳��˳�(һֱ����)
	static int			Exit(); //�˳��߳�,���ڴ��߳��ڲ�����������ֹ(�ͷ�����Ч����һ��),�����ڷǱ��߳��е���!
};


/**************************************************************
 *	 
 *   LZAri ѹ �� �� �� �� [�������漴�ܵ���]
 *
 * 1) ע����ʵ���������Compress��Uncompress����һ��, 
 *    ֮���������, �����ظ�ʹ��.
 *
 * 2) �����ñ������Թ����SIP��Ϣ��(����MTU)����ѹ������,
 *    ƽ��1500���ֽ�ѹ����370���ֽ�, ѹ���ͽ�ѹʱ�� 1ms.
 *
 *************************************************************/
RT_DECLARE_HANDLE(RtCommAriHandle);

class RTAPI CRtCommAri
{
public:
	CRtCommAri();
	~CRtCommAri();

	int  Compress(
		IN	   const char*		pInBuffer,
		IN	   int				nInLength,  //��Ҫ��Buffer�Ľ�����'\0'��������
		OUT    const BYTE*&		pOutBuffer, //����ʱ��Ҫ�����ڴ�,ɾ������ʱ���ͷ�
		INOUT  int*				pnOutLength);

	int  Uncompress( 
		IN     const char*		pInBuffer,
		IN	   int				nInLength,
		OUT    const BYTE*&		pOutBuffer, //����ʱ��Ҫ�����ڴ�,ɾ������ʱ���ͷ�
		INOUT  int*				pnOutLength);

private:
	RtCommAriHandle m_pAri;
	int				m_nComplite;
};


RT_DECLARE_HANDLE(RtCommMutexHandle);

class RTAPI CRtCommMutex 
{
public:
	CRtCommMutex();
	~CRtCommMutex();
	
	void Lock();
	void Unlock();
	
private:
	RtCommMutexHandle m_pMutex;
	bool			  m_bUseCommEg;	
};


RT_DECLARE_HANDLE(RtCommTimerHandle);

typedef void (*pfnTimerEv)(void* pContext);

class RTAPI CRtCommTimer 
{
public:
	CRtCommTimer();
	~CRtCommTimer();

	// ��nMiliTimeOutʱ�䵽��, pfnTimerEv��������ִ��, pfnTimerEv�������������Timer����, ��Դ���������, 
	// �����Ҫ, ����pfnTimerEv�������ٴε���Set����, ���Ǳ��뱣֤Set���ٵ��ò���������������.
	int Set( 
		IN unsigned int nMiliTimeOut, 
		IN pfnTimerEv	pCallbackFunc, 
		IN void*		pContext);

	int Release(int nReplay = 20); //����Timer��ע�ⲻҪ��pfnTimerEv�����ڵ�����������ζֱ��return����

	int GetTTL(INOUT unsigned int* pnTTL); //���Timer��ʣ������ʱ��

private:
	RtCommTimerHandle m_pTimer;
	bool			  m_bUseCommEg;	
};


/**************************************************************
 *	 
 *   �� �� �� �� [�������漴�ܵ���]
 *
 *************************************************************/
RT_DECLARE_HANDLE(RtCommQueueHandle);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ��
 �� ���ڶ�����Ϣ�ṹ�Ķ���:
 ��
 ��	1) T_RT_FIFOMSGITEM.Msg�Ķ������չ, ����Ժ���������;
 ��
 ��	2) T_RT_FIFOMSGHEAD.wDataLen��ֵ��ʾT_RT_FIFOMSGITEM.Msg�ĳ���;
 ��
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef struct __t_RT_FIFOMSGHEAD
{
	unsigned int		ucCommand;	//�������,��SIP״ֵ̬
	unsigned int		wParam;		//��Ų���,��SIP CALL-ID,���鴫ֵ
	unsigned int		wDataLen;	//���MSG�����ݳ���
} T_RT_FIFOMSGHEAD, *P_RT_FIFOMSGHEAD;

typedef struct __t_RT_FIFOMSGITEM
{
	T_RT_FIFOMSGHEAD	Head;
	union
	{
		long			lParam;		//�ò������鴫ָ��
		unsigned char	ucN[4500];
	} Msg;
} T_RT_FIFOMSGITEM, *P_RT_FIFOMSGITEM;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ��
 �� ���ڶ��̵߳��ö��е�ע��:
 ��
 ��	1) ���ֻ��һ���̸߳���Read, һ���̸߳���Write, ��ô�������;
 ��
 ��	2) ���Read�ж���߳��ڲ���, ���ڲ���ǰ���û���ÿ��Read�̼߳���, Write��Ϊһ��;
 ��
 �� 3) AppendMsg()����һ������Ҫ��, ����Read���������Write��, �����֤����, ��ʹ��TryAppendMsg+UpdateAppendMsg;
 ��
 �� 4) AppendMsg()�в���dwBytes, ��ʽ����(�����׳���): sizeof(T_RT_FIFOMSGHEAD) + xxxxx.Head.wDataLen;
 ��
 �� 5) һЩ�߼������û��������, ������Ϊ����������д����ʧ��, �Ƕ����ð�, ������ն��е�;
 ��
 �� 6) ������г���ʱ, ������Լ���Ҫ�ĳ���, ���鲻Ҫ����0x1E00000(30M Bytes).
 �� 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class RTAPI CRtCommQueue 
{
public:
	CRtCommQueue( //����FIFO, Name�ַ�С��16, ����ָ���ݳش�С
		IN char*				pszQueueName,
		IN unsigned long		dwQueueMaxSize);

	~CRtCommQueue(); //�ͷ�FIFO

	void Reset(); //��ն���������

	unsigned long GetFreeBytes(); //���ض��еĿ��೤��
	
	unsigned long GetWrittenBytes(); //���ض�����д��ĳ���


	/* -------------------- �����ݶ��в������� -------------------- */

	int Append( //�����д��ָ�����ȵ�����, ��ʶ�����ݸ�ʽ, ���Զ���תָ��
		IN unsigned long		dwBytes,
		IN unsigned char*		pucItem);

	int AppendAtEnd( //����о���д����, �����еײ�����
		IN    unsigned long		dwBytes,
		IN	  unsigned char*	pucItem,
		INOUT unsigned long*	lpNumberOfBytesWritten); //����д���ʵ�����ݳ���

	int Pop( //�Ӷ�����ȡָ�����ȵ�����,�������������С�ڲ���dwBufferBytesָ���ĳ����򷵻�ʵ�����ݳ���
		INOUT unsigned char*	pucBuffer,
		IN    unsigned long		dwBufferBytes,
		INOUT unsigned long*	lpNumberOfBytesReadden); //���ض����ʵ�����ݳ���


	/* -------------------- ��Ϣ���ݶ��в������� -------------------- */

	int AppendMsg( //�����д��ָ�����ȵ�����
		IN unsigned long		dwBytes,  //ӦΪ: sizeof(T_RT_FIFOMSGHEAD)+pItem->Head.wDataLen
		IN unsigned char*		pucItem); //ӦΪ: T_RT_FIFOMSGITEM* �����ݿ�ͷָ��ֵ

	P_RT_FIFOMSGITEM PopMsg(); //ȡ����������Ϣ

	
	/* ����2����������ʹ��, �������Ч�� */
	P_RT_FIFOMSGITEM TryAppendMsg(IN unsigned long dwBytes);    //��ѯ�����ܷ���ָ������(sizeof(T_RT_FIFOMSGHEAD)+pItem->Head.wDataLen)����Ϣ,�����,���ص�ǰ��Ԫ������ָ����򷵻�NULL
	void			 UpdateAppendMsg(IN unsigned long dwBytes); //����ָ���ĳ��ȵ�����, ӦΪ: sizeof(T_RT_FIFOMSGHEAD)+pItem->Head.wDataLen


	/* ����2����������ʹ��, �������Ч�� */
	P_RT_FIFOMSGITEM TryPopMsg();	  //��ѯ�������Ƿ�������Ϣ,�����򷵻�ָ��,�������¶�����Ϣ,���򷵻�NULL
	void			 RemoveCurMsg();  //��ͨ��TryPopMsg()ȡ������Ϣ�Ӷ�����Ĩȥ

private:
	RtCommQueueHandle m_pQueue;
};

/**************************************************************
 *	 
 *   RTP �� �� �� ��
 *
 *************************************************************/
RT_DECLARE_HANDLE(RtRtpSessionHandle);

typedef void(* pfnRtRtpRecv)(
	void*				pData,
	int					nDatalen,
	unsigned char		cPT, 
	void*				pContext, 
	bool				bMark,
	unsigned int		nTimestamp,
	unsigned int		nSeqNumber);

typedef void(* pfnRtRtcpRecv)(
	E_RtMediaType			eMediaType,
	E_RtRtcpPacketType		ePacketType,
	unsigned int			dwSecondTime,
	const char*				pszSenderAddress,
	const T_RtQOS4*			pQos,
	void*					pContext);

class RTAPI CRtRtpSession
{
public:
	static int Create( //����
		IN  const char*				pszLocalIP,		//���ص�ַ,���Ҫ��Ѩ,ָ��ֵΪ0
		IN  const unsigned short	nLocalPort,		//���ض˿�
		IN  const double			nClock,			//����Ƶ��
		IN  const unsigned int		nPayload,		//��������
		IN  const unsigned int		nTimestampInc,	//ʱ�������
		IN  const bool				bFastRtp,		//�Ƿ�ʹ�ÿ���RTP(RTCP���Լ�����,���԰����ж�������)
		IN  const E_RtMediaType		eMediaType,		//ý������
		OUT RtRtpSessionHandle*		phSession);		//Session�������
	
	static void Destroy( //����
		IN  RtRtpSessionHandle		hSession);
	
	static void SetReadRtpCB( //RTP���ݻص�����
		IN  RtRtpSessionHandle		hSession,
		IN  const pfnRtRtpRecv		myBackcall,
		IN  void*					pContext);
	
	static void SetReadRtcpCB( //RTCP���ݻص�����
		IN	RtRtpSessionHandle		hSession,
		IN  const pfnRtRtcpRecv		myBackcall,
		IN  void*					pContext);
};

#endif


