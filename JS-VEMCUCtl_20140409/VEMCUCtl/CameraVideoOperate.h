#ifndef _CAMERA_VIDEO_OPERATE_H_
#define _CAMERA_VIDEO_OPERATE_H_

//////////////////////////////////////////////////////////////////////////
//NodeType��ʾ�������,1:��ʾserver���,2:��ʾpreset���,3:��ʾ��Ԥ��λpreset���
BOOL MakeCallCameraByViewType(int nWinID,char *szCameraNum,char* szCameraName,int nViewType,int nDecodeTag,int nCameraStatus,int nStreamless,char* szStationName,int NodeType=0,void *pNodeInfo = NULL,char *szNotes = NULL);// ��������ͷ

//�жϲ��Ŵ����Ƿ�����Ƶ��
int      CheckViewVideoIsOpen(int nWinID);

//�ж�����ͷ��Ƶ�Ƿ񱻴�
int      CheckCameraVideoIsOpen(char *szCameraNum,int &nWinID);

//�ر�ָ�����ڵ���Ƶ
BOOL CloseViewVideoByWinID(int nWinID,int nViewType);

//�ر�ָ������ͨ������ƽ̨�򿪵���Ƶ
BOOL CloseViewPlatformVideoByWinID(int nWinID);

//�ر�ָ������ͨ��ֱ���豸�򿪵���Ƶ
BOOL CloseViewDeviceVideoByWinID(int nWinID);

//���ָ�����ڵ���Ϣ
BOOL ClearViewPlatformAndDeviceInfoByWinID(int nWinID);

//�ر�¼��
BOOL CloseVideoRecordByWinRecordFlag(int nWinID);

//�ر���Ƶ
BOOL CloseVideoAudioByWinRecordFlag(int nWinID);

// �õ�һ������
int GetViewCameraVideoIdleWin();

// �õ���ǰѡ�񴰿�
int GetViewCameraVideoCurrentWin();

// ͨ������ƽ̨��������ͷ
BOOL OpenViewCameraVideoByVideoPlatform(int nWinID,char* szCameraNum,char* szCameraName,int nDecodeTag,int nCameraStatus,int nStreamless,char* szStationName,int NodeType=0,void *pNodeInfo = NULL,char *szNotes = NULL);

// ֱ����ǰ������ͷ����
BOOL OpenViewCameraVideoByDirectDevice(int nWinID,char* szCameraNum,char* szCameraName,int nDvrType,int nCameraStatus,int nStreamless,char* szStationName,int NodeType,void *pNodeInfo,char *szNotes = NULL);

// ���º�����ʾ��Ϣ
BOOL UpdateViewCameraVideoShowInfo(int nWinID,char* szCameraNum,char* szCameraName,int nCameraStatus,int nStreamless,char* szStationName,int NodeType,void *pNodeInfo,char *szNotes = NULL);

//��ָ���Ĵ��ڴ򿪲���ʾ������Ϣ
BOOL StartVideoWinCurrentWeather(int nWinID,char *szStationName);

//�ر�ָ���Ĵ��ڵ�������Ϣ
BOOL StopVideoWinCurrentWeather(int nWinID);

//��ʾԤ��λ������Ϣ
BOOL ShowVideoPresetLineInfoDlg(int nWinID,RECT *pRect,void *pNodeInfo);

//���Ԥ��λ������Ϣ
BOOL ClearVideoPresetLineInfoDlg(int nWinID);

//�����Ǻ��жϻ�����Ϣ
BOOL ClearVideoTagAndOffLineInfoDlg(int nWinID);

//���Ԥ��λ������Ϣ�������Ǻ��жϻ�����Ϣ
BOOL ClearVideoPresetLineAndTagInfoDlg(int nWinID);

//��ʾ��ע��Ϣ
BOOL ShowVideoTagInfoDlg(int nWinID,int nCameraStatus,RECT *pRect);

// ͨ������ƽ̨��������Ƶ����
int AppVideoMakeCallByPlatform(int nWinID);

//����CallId�Ҷ�ͨ������ƽ̨����ĺ���
void AppHangupCallIdByPlatform(int nCallId);

// ֱ����ǰ���豸��������Ƶ����
int AppVideoMakeCallByDirectDevice(int nWinID);

// �Ҷ�ֱ����ǰ���豸�������Ƶ����
int AppHangupCallByDirectDevice(int nID);

//�����ַ������ͣ��õ�DVR����������
int AppGetCameraDvrType(char *szType);

//ȡ�����߶�������
BOOL AppCancelRestartCameraVideo(int nWinID);

//���ö��߶�������
BOOL AppSetRestartCameraVideo(int nWinID);

//����
void AppTestAndDisplayCallThreadIDInfo(char *szInfo);

//��������ʱ��
void AppTestAndDisplayTickCountInfo(char *szInfo);

#endif