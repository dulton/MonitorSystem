#ifndef _SIP_CALL_H_
#define _SIP_CALL_H_


typedef struct _VIDEO_SIP_CALL_SERVER_INFO_STRUCT_
{
	int   nType;//1:ͨ������ƽ̨����,2:ֱ�Ӻ���ǰ���豸,3:ͨ������ƽ̨����,4:ͨ��ֱ�Ӻ���ǰ���豸����
	char szName[256];
	char szCode[64];
	char szStation[256];
	int    nDecodeTag;
	int    nScreenId;
	HTREEITEM hItem;
	int    nStatus;
	int    nStreamless;
	char szReason[256];
	_T_NODE_INFO server_node_info;
}VIDEO_SIP_CALL_SERVER_INFO;

typedef struct _VIDEO_SIP_CALL_PRESET_INFO_STRUCT_
{
	int   nType;//1:ͨ������ƽ̨��һ����������,2:ͨ������ƽ̨��Ԥ��λ����,3:ֱ����������ǰ���豸,4:��Ԥ��λֱ�Ӻ���ǰ���豸
	char szName[256];
	char szCode[64];
	char szStation[256];
	int    nDecodeTag;
	int    nScreenId;
	HTREEITEM hItem;
	int    nStatus;
	int    nStreamless;
	char szReason[256];
	_T_NODE_PRESET_INFO preset_node_info;
}VIDEO_SIP_CALL_PRESET_INFO;


typedef struct _SIP_STATE_HANDLER_INFO_
{
	int nCID;
	char szCallerNum[64];
	char szCalleeNum[64];
	int   nDirection;
	char Sps[512];
	int  nSpsLen;
	int nReason;
	int nVideoPayload;
	int nAudioPayload;
	void *pAppData;
}SIP_STATE_HANDLER_INFO;

//������Ƶ����
void ThreadMakeCallCameraServer(void *arg);

//������Ƶ���в�ת��Ԥ��λ
void ThreadMakeCallCameraPreset(void *arg);

//������Ƶ����
void ThreadVideoLinkageMakeCall(void *arg);


//����״̬����
void ThreadSipStateHandlerTalking(void *arg);

//���н���
void ThreadSipStateHandlerTerminate(void *arg);

//������������
void ThreadStopCurrentVideo(void *arg);

//��������ȫ������
void ThreadStopAllVideo(void *arg);

//��������ֱ���豸����
void ThreadStopDirectDeviceVideo(void *arg);

//��������ƽ̨����
void ThreadStopPlatformVideoByCallId(void *arg);




#endif