#ifdef DEVPLAYVIDEOSDK_EXPORTS
#define DEVPLAYVIDEOSDKLIB __declspec(dllexport)
#else
#define DEVPLAYVIDEOSDKLIB __declspec(dllimport)
#endif

#define	DEVTYPE_HK					110		//����
#define	DEVTYPE_DH					111		//��
#define	DEVTYPE_DL					112		//����
#define DEVTYPE_MOBOTIX				113		//mobotix
#define DEVTYPE_AXIS				114		//AXIS

#define OPENVIDEO_SUCCESS			0		// ����Ƶ�ɹ�
#define OPENVIDEO_LOADDLLERROR		1		// ���ز���SDKʧ��
#define OPENVIDEO_FINDDVRTYPEERROR	2		// û���ҵ������ͽ����
#define OPENVIDEO_LOGINDVRERROR		3		// ��½DVRʧ��
#define OPENVIDEO_PLAYERROR			4		// ����Ƶʧ��

#define CLOSEIRISSTOP		0x0101	//��Ȧ��ֹͣ
#define CLOSEIRIS			0x0102	//��Ȧ��
#define OPENIRIS			0x0103	//��Ȧ��
#define OPENIRISSTOP		0x0104	//��Ȧ��ֹͣ
#define FOCUSNEARSTOP		0x0201	//���۽�ֹͣ
#define FOCUSNEAR			0x0202	//���۽�
#define FOCUSFARSTOP		0x0203	//Զ�۽�ֹͣ
#define FOCUSFAR			0x0204  //Զ�۽�
#define ZOOMINSTOP			0x0301  //��Сֹͣ
#define ZOOMIN				0x0302	//��С
#define ZOOMOUTSTOP			0x0303	//�Ŵ�ֹͣ
#define ZOOMOUT				0x0304	//�Ŵ�
#define TILTUPSTOP			0x0401	//����ֹͣ
#define	TILTUP				0x0402	//����
#define TILTDOWNSTOP		0x0403	//����ֹͣ
#define TILTDOWN			0x0404  //����
#define PANRIGHTSTOP		0x0501	//��תֹͣ
#define PANRIGHT			0x0502	//��ת
#define PANLEFTSTOP			0x0503	//��תֹͣ
#define PANLEFT				0x0504	//��ת
#define SETPRESET			0x0601	//Ԥ��λ����
#define GOTOPRESET			0x0602	//Ԥ��λ����
#define CLEPRESET			0x0603	//Ԥ��λɾ��
#define UPLEFTSTOP			0x0701	//���Ϸ����˶�ֹͣ
#define UPLEFT				0x0702	//���Ϸ����˶�
#define DOWNLEFTSTOP		0x0703	//���·����˶�ֹͣ
#define DOWNLEFT			0x0704	//���·����˶�
#define UPRIGHTSTOP			0x0801	//���Ϸ����˶�ֹͣ
#define UPRIGHT				0x0802	//���Ϸ����˶�
#define DOWNRIGHTSTOP		0x0803	//���·����˶�ֹͣ
#define DOWNRIGHT			0x0804	//���·����˶�

#define FILENAME_MAXLEN		512
#define	TIME_MAXLEN			32

typedef struct _sdk_time{
	unsigned long year;
	unsigned long month;
	unsigned long day;
	unsigned long hour;
	unsigned long minute;
	unsigned long second;
}SDKTIME,*PSDKTIME;

typedef struct _record_item {
	char	FileName[FILENAME_MAXLEN];
	char	BeginTime[TIME_MAXLEN];
	char	EndTime[TIME_MAXLEN];
	int		size;
}RECORDITEM,*PRECORDITEM;

typedef int (*CALLBACKGETDEVSTATE) (unsigned short dvrid,bool state);
typedef int (*CALLBACKGETPOS) (unsigned short dvrid,unsigned short channel,int pos);
typedef int (*CALLBACKOPENVIDEO) (int  id, int nresult);
typedef int (*CALLBACKCLOSEVIDEO)(int id);
typedef int (*CALLBACKGETFILEPOS) (unsigned short dvrid,unsigned short channel,int pos);
typedef int (*CALLBACKPLAYFILEPOS) (LONG id,int pos);


#ifdef __cplusplus
extern "C" {
#endif
	DEVPLAYVIDEOSDKLIB  bool	Init_DevSdk();
	DEVPLAYVIDEOSDKLIB  bool	Exit_DevSdk(); 
	DEVPLAYVIDEOSDKLIB  int 	GetID_DevSdk(); 
	DEVPLAYVIDEOSDKLIB  int		OpenVideo_DevSdk(char* ip,unsigned short port, char* user, char* password,unsigned short dvrtype,unsigned short dvrid,unsigned short channel,int id ,HWND playwnd);
	DEVPLAYVIDEOSDKLIB  void	 CloseVideo_DevSdk(int id);
	DEVPLAYVIDEOSDKLIB  bool	 DvrPtzControl_Devsdk(char* ip,unsigned short port, char* user, char* password,unsigned short dvrtype,unsigned short dvrid,unsigned short channel,unsigned short control,unsigned short speed);
	DEVPLAYVIDEOSDKLIB  bool	 GetRecordFileInfo_DevSdk(char* ip,unsigned short port, char* user, char* password,unsigned short dvrtype,unsigned short dvrid,unsigned short channel,SDKTIME starttime,SDKTIME stoptime,void** info,int* num);
	DEVPLAYVIDEOSDKLIB  bool FreeRecordFileInfo_DevSdk(unsigned short dvrtype,void* info);
	DEVPLAYVIDEOSDKLIB  bool	 StartPlayBack_DevSdk(char* ip,unsigned short port, char* user, char* password,unsigned short dvrtype,unsigned short dvrid,unsigned short channel,RECORDITEM info,HWND playwnd);
	DEVPLAYVIDEOSDKLIB  void	 StopPlayBack_DevSdk(unsigned short dvrid,unsigned short channel);
	DEVPLAYVIDEOSDKLIB  bool	 PausePlayBack_DevSdk(unsigned short dvrid,unsigned short channel);
	DEVPLAYVIDEOSDKLIB  bool	 ReStartPlayBack_DevSdk(unsigned short dvrid,unsigned short channel);
	DEVPLAYVIDEOSDKLIB  bool 	FastPlayBack_DevSdk(unsigned short dvrid,unsigned short channel);
	DEVPLAYVIDEOSDKLIB  bool 	SlowPlayBack_DevSdk(unsigned short dvrid,unsigned short channel);
	DEVPLAYVIDEOSDKLIB  bool	 SetPosPlayBack_DevSdk(unsigned short dvrid,unsigned short channel,int pos);
	DEVPLAYVIDEOSDKLIB  bool    StartDownLoadFile_DevSdk(char* ip,unsigned short port, char* user, char* password,unsigned short dvrtype,unsigned short dvrid,unsigned short channel,RECORDITEM info,char* localfile);
	DEVPLAYVIDEOSDKLIB  bool    StopDownLoadFile_DevSdk(unsigned short dvrid,unsigned short channel);
	DEVPLAYVIDEOSDKLIB  LONG    StartPlayLocalFile_DevSdk(unsigned short dvrtype,char* file,HWND playhwnd);
	DEVPLAYVIDEOSDKLIB  bool    StopPlayLocalFile_DevSdk(LONG id);
	DEVPLAYVIDEOSDKLIB  bool	PausePlayLocalFile_DevSdk(LONG id);
	DEVPLAYVIDEOSDKLIB  bool	ReStartPlayLocalFile_DevSdk(LONG id);
	DEVPLAYVIDEOSDKLIB  bool	FastPlayLocalFile_DevSdk(LONG id);
	DEVPLAYVIDEOSDKLIB  bool	SlowPlayLocalFile_DevSdk(LONG id);
	DEVPLAYVIDEOSDKLIB  bool	SetPosPlayLocalFile_DevSdk(LONG id,int pos);
	DEVPLAYVIDEOSDKLIB  bool	SetCallbackGetDevState(CALLBACKGETDEVSTATE GetDevState);
	DEVPLAYVIDEOSDKLIB  bool	SetCallbackGetPlayBackPos(CALLBACKGETPOS GetPlayBackPos);
	DEVPLAYVIDEOSDKLIB  bool	SetCallbackOpenVideo(CALLBACKOPENVIDEO OpenVideo);
	DEVPLAYVIDEOSDKLIB  bool    SetCallbackCloseVideo(CALLBACKCLOSEVIDEO CloseVideo);
	DEVPLAYVIDEOSDKLIB  bool    SetCallbackGetLocalFilePos(CALLBACKGETFILEPOS GetFilePos);
	DEVPLAYVIDEOSDKLIB  bool    SetCallbackPlayLocalFilePos(CALLBACKPLAYFILEPOS GetFilePos);
	DEVPLAYVIDEOSDKLIB  bool	 CaptureLocalPicture(int id,char *szPicFileName);
	DEVPLAYVIDEOSDKLIB  bool	 StartRecordLocalFile(int id,char *szRecordFileName);
	DEVPLAYVIDEOSDKLIB  bool	 StopRecordLocalFile(int id);

#ifdef __cplusplus
}
#endif
