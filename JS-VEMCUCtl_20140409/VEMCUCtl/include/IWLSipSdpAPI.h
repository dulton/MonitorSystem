#ifndef __IWL_SIP_STACK_SIPSDPAPI_H__
#define __IWL_SIP_STACK_SIPSDPAPI_H__

RT_DECLARE_HANDLE(RtSdpHandle);			//SDP���
RT_DECLARE_HANDLE(RtSdpMediaHandle);	//ý��ξ��

typedef enum __e_RtSdpConnMode
{
	E_RT_SDPCONNMODE_UNDEFINED = 0,		//��Ч
	E_RT_SDPCONNMODE_SENDONLY,			//������
	E_RT_SDPCONNMODE_RECVONLY,			//������
	E_RT_SDPCONNMODE_SENDRECV,			//ͬʱ���ͺͽ���
} E_RtSdpConnMode;

class RTAPI IRtSdpAPI
{
public:
	virtual	int Construct( //����SDP
		OUT RtSdpHandle*		phSdp
		) = 0;

	virtual	int Construct( //��String�й���SDP
		IN    char*				pSdpBuffer, 
		IN    int*				pSdpBufferLen,
		OUT   RtSdpHandle*		phSdp
		) = 0;

	virtual int Destruct( //����SDP
		IN    const RtSdpHandle	hSdp
		) = 0;

	virtual int ConstructCopy( //��������SDP
		OUT   RtSdpHandle*		phDest, 
		IN    const RtSdpHandle	hSrc
		) = 0;

	virtual int EncodeToBuf( //��SDP�����String
		IN  const RtSdpHandle	hSdp, 
		IN  char*				pBuf, 
		IN  int					nLen
		) = 0;

	virtual int SetBoundaryLine( //���������Ĭ��ֵ(o, s, i, u, c, t, ������m��)
		IN const RtSdpHandle	hSdp,
		IN const char*			pAddress
		) = 0;

	virtual int SetOrigin( //����o��
		IN const RtSdpHandle	hSdp,
		IN const char*			pUsername,
		IN const char*			pSessionID,
		IN const char*			pSessionVer,
		IN const char*			pAddress //��֧��Internet��IPv4��ʽ
		) = 0;

	virtual int GetOrigin( //���o��
		IN    const RtSdpHandle	hSdp,
		INOUT char*				pUsername,		//����bufferLen > 56
		INOUT char*				pSessionID,		//����bufferLen > 56
		INOUT char*				pSessionVer,	//����bufferLen > 32
		INOUT char*				pAddress		//����bufferLen > 56
		) = 0;

	virtual int SetSLine( //����s��
		IN  const RtSdpHandle	hSdp,
		IN  const char*			pSessionName
		) = 0;

	virtual const char* GetSLine( //���s��
		IN const RtSdpHandle	hSdp
		) = 0; 


	virtual int SetILine( //����i��
		IN  const RtSdpHandle	hSdp,
		IN  const char*			pInfoName
		) = 0;

	virtual const char* GetILine( //���i��
		IN const RtSdpHandle	hSdp
		) = 0; 


	virtual int SetULine( //����uri��
		IN  const RtSdpHandle	hSdp,
		IN  const char*			pUriAddr
		) = 0;

	virtual const char*	GetULine( //���uri��
		IN const RtSdpHandle	hSdp
		) = 0; 


	virtual int SetCLine( //����c��
		IN  const RtSdpHandle	hSdp,
		IN  const char*			pAddress
		) = 0;

	virtual const char*	GetCLine( //���c��IPv4��ַ
		IN const RtSdpHandle	hSdp
		) = 0; 


	virtual int SetTLine( //����t��
		IN  const RtSdpHandle	hSdp,
		IN  unsigned int		nStart,
		IN  unsigned int		nStop
		) = 0;

	virtual int GetTLine( //���t��
		IN    const RtSdpHandle	hSdp,
		INOUT unsigned int*		pnStart,
		INOUT unsigned int*		pnStop
		) = 0;

	virtual void ClearAllMediaDescr( //������е�m��
		IN const RtSdpHandle	hSdp
		) = 0; 

	virtual unsigned int GetNumOfMediaDescr( //���m�и���
		IN const RtSdpHandle	hSdp
		) = 0; 


	/* -------------------- ý��β������� -------------------- */
			
	virtual RtSdpMediaHandle GetMediaDescr( //���ָ����m�о��
		IN const RtSdpHandle	hSdp, 
		IN int					nIndex
		) = 0; 

	virtual RtSdpMediaHandle AddMediaDescr( //����m��
		IN  const RtSdpHandle	hSdp,
		IN  E_RtMediaType		eMediaType,
		IN  unsigned int		nRtpPort,
		IN  E_RtTransportType	eProtocol
		) = 0;

	
	virtual E_RtMediaType MediaGetType( //���m������
		IN  const RtSdpMediaHandle	hMedia
		) = 0; 

	virtual E_RtTransportType MediaGetProtocol( //���m��Э��
		IN  const RtSdpMediaHandle	hMedia
		) = 0; 

	virtual unsigned int MediaGetPort( //���m�ж˿�
		IN  const RtSdpMediaHandle	hMedia
		) = 0; 

	virtual unsigned int MediaGetNumOfPt( //���m����pt��
		IN  const RtSdpMediaHandle	hMedia
		) = 0; 

	virtual int MediaGetPt( //���m��ָ����ptֵ
		IN  const RtSdpMediaHandle	hMedia, 
		IN  int						nIndex
		) = 0; 

	virtual int MediaSetConnMode( //����һ������ģʽ
		IN  const RtSdpMediaHandle	hMedia,
		IN  E_RtSdpConnMode			eConnMode
		) = 0;
	
	virtual E_RtSdpConnMode MediaGetConnMode( //�������ģʽ
		IN  const RtSdpMediaHandle	hMedia
		) = 0; 

	
	virtual int MediaAddPt( //��m��������һ��ptֵ(��MediaAddRtpmap()��������ʹ��)
		IN  const RtSdpMediaHandle	hMedia, 
		IN  int						nPayload
		) = 0; 

	virtual int MediaAddFormat( //��m��������һ����PT��ֵ(��MediaAddAttr()��������ʹ��)
		IN  const RtSdpMediaHandle	hMedia, 
		IN  const char*				pFormat
		) = 0; 

	virtual unsigned int MediaGetNumOfRtpmap( //���rtpmap���͵�a�и���
		IN  const RtSdpMediaHandle	hMedia
		) = 0; 

	virtual unsigned int MediaGetNumOfAttr( //��÷Ǳ�׼���͵�a�и���(������rtpmap��conn mode��)
		IN  const RtSdpMediaHandle	hMedia
		) = 0; 


	/* -------------------- a�в������� -------------------- */

	virtual int MediaGetAttr( //���ָ����a��(�������ڻ��rtpmap��conn mode��)
		IN const RtSdpMediaHandle	hMedia,
		IN    int					nIndex,
		INOUT char*					pszName,		//����bufferLen > 32
		INOUT char*					pszValue		//����bufferLen > 120
		) = 0;	

	virtual int MediaAddAttr( //�����µ�a��
		IN  const RtSdpMediaHandle	hMedia,
		IN  char*					pszName,
		IN 	char*					pszValue
		) = 0; 
	
	virtual int MediaGetRtpmap( //���ָ����rtpmap����a��
		IN    const RtSdpMediaHandle hMedia,
		IN    int					 nIndex,
		INOUT int*					 pnPayload,
		INOUT char*					 pszEncodeName,	//����bufferLen > 16
		INOUT int*					 pnRate
		) = 0;
	
	virtual int MediaAddRtpmap( //�����µ�rtpmap����a��
		IN  const RtSdpMediaHandle	hMedia,
		IN	int						nPayload,
		IN  char*					pszEncodeName,
		IN 	int						nRate
		) = 0; 

	virtual ~IRtSdpAPI() = 0;
};

#endif
