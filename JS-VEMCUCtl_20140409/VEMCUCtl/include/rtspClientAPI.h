#ifndef __RTSP_CLIENT_API_DLL__
#define __RTSP_CLIENT_API_DLL__

#if defined (_WIN32) || defined (_WIN64)
	#define RTSPAPI       __declspec(dllexport)
	#define RTSPCALLCONV  __stdcall
#else
	#define RTSPAPI
	#define RTSPCALLCONV
#endif

/**************************************************************
 *	 
 *   RTSP Macro Defined
 *
 *************************************************************/
typedef enum __e_RtspRes
{
	E_RTSP_OK							= 1,   //�ɹ�
	E_RTSP_ERROR_UNKNOWN				= -1,  //δ֪����
	E_RTSP_ERROR_OUTOFRESOURCES			= -2,  //û����Դ����
	E_RTSP_ERROR_BADPARAM				= -3,  //��������
	E_RTSP_ERROR_UNINITIALIZED			= -4,  //δ��ʼ��
} E_RtspRes;

typedef struct __t_RtspConfig
{
	bool			bStreamUsingTCP;		//�Ƿ�ʹ��TCP������
	bool			bPlayContinuously;		//�Ƿ�ѭ������
} T_RtspConfig;

typedef enum __e_MsgType
{
	E_MSG_TYPE_SEND_MSG			= 1,	// client���ͳ�ȥ����Ϣ
	E_MSG_TYPE_RECV_MSG			= 2,	// client���յ�����Ϣ
};

typedef void(* pfnRecvRTPData)(int nid, void* data, int datalen, void* context);	//��������CALLBACK

typedef void(* pfnSendRecvMsg)(int msgtype, char* msg, int msglen, void* context);	//���ͺͽ��յ�rtsp��Ϣ

/**************************************************************
 *	 
 *   RTSP Engineer Manager
 *
 *************************************************************/
class RTSPAPI IRtspClientAPI;
class RTSPAPI CRtspEngineer
{
public:
	static CRtspEngineer* Instance();
	virtual ~CRtspEngineer();

	E_RtspRes InitEngineer(T_RtspConfig* pCfg);
	void	  SetCallback(pfnRecvRTPData fnHandler, void* pContext);
	void	  SetMsgCallback(pfnSendRecvMsg fnHandler, void* pContext);

	E_RtspRes StartEngineer();
	void	  StopEngineer();

	E_RtspRes GetInterface(IRtspClientAPI** ppv);

protected:
	CRtspEngineer();

private:
	static CRtspEngineer* m_pInstance;
	IRtspClientAPI*		  m_pClientAPI;
};

/**************************************************************
 *	 
 *   RTSP Client Interface API
 *
 *************************************************************/
class RTSPAPI IRtspClientAPI
{
public:
	virtual E_RtspRes ProduceID(int* pnID) = 0;

	virtual E_RtspRes Play(int nID, char* pURL, char* header, int headerlen, bool bUseRtsip=false, int nStartPort=0) = 0;
	virtual E_RtspRes Stop(int nID) = 0;
	virtual E_RtspRes Speed(int nID, float scale) = 0;
	virtual E_RtspRes Pause(int nID) = 0;
	virtual E_RtspRes AdjustPos(int nID, int nPos) = 0;
	virtual E_RtspRes Resume(int nID) = 0;

	virtual char*	  GetDescribeResponseBody(int nID) = 0; //���Describe��Ӧ�е�SDP��XML����
};

#endif
