#ifndef __XML_API__
#define __XML_API__


#define   CODE_LEN	20
#define	TIME_LEN	22

#define MAX_ALARM_NOTIFY_NUM		100
#define MAX_STATUS_NOTIFY_NUM		300


#define SIP_DEFAULT					0
#define SIP_NOTIFY_ALARM			1
#define SIP_NOTIFY_STATUS			2


// ======����֪ͨ����======
// ֪ͨ�澯
typedef struct _notify_alarm 
{
	char	code[CODE_LEN];
	char	name[64];
	int	type;
	char	StartTime[TIME_LEN];
	char	stationname[64];
	int	flag;
}NOTIFY_ALARM;

// ֪ͨ״̬
typedef struct _notify_status 
{
	char	code[CODE_LEN];
	char	name[64];
	int	status;
}NOTIFY_STATUS;


// �����澯֪ͨ
extern int ParseNotifyAlarm(NOTIFY_ALARM notify_alarm[], int num, const char *strXML);

// ����״̬֪ͨ
extern int ParseNotifyStatus(NOTIFY_STATUS notify_status[], int num, const char *strXML);

// ��ȡ����XML���ͺ�������
extern int GetXmlTypeNum(const char *strXML, int *type, int *num);

/************************************************************************
*��Ƶ������Ϣ
************************************************************************/
#define  LINKAGE_DEVICE_CODE_LEN 64
#define  LINKAGE_DEVICE_NAME_LEN 256
#define  LINKAGE_STATION_NAME_LEN 256
#define  LINKAGE_TIME_LEN 64
#define  LINKAGE_ALARM_CONTENT_LEN 512
#define  LINKAGE_STATE_INFO_LEN 128
#define  LINKAGE_VALUE_INFO_LEN 64
#define  LINKAGE_TYPE_LEN  64
#define  LINKAGE_TYPE_NAME_LEN  256
#define  LINKAGE_TYPE_VALUE_LEN  256
#define  VIDEO_USER_NAME_LEN 64
#define  VIDEO_STATION_NAME_LEN 256
#define  VIDEO_DEVICE_NAME_LEN 256
#define  VIDEO_PRESET_NAME_LEN 256
#define  VIDEO_DEVICE_CODE_LEN 64
#define  VIDEO_SCENE_NAME_LEN 256
#define  VIDEO_LINKAGE_INFO_LEN 64
#define  LINKAGE_CONTENT_LEN 512
#define  LINKAGE_ID_LEN 64

//////////////////////////////////////////////////////////////////////////
//��Ƶ������Ϣ����
#define  VIDEO_LINKAGE_INFO_UNDEFINE_TYPE 0
#define  VIDEO_LINKAGE_INFO_TYPE 1
#define  VIDEO_ALARM_LINKAGE_INFO_TYPE 2
#define  VIDEO_STATE_LINKAGE_INFO_TYPE 3
#define  VIDEO_CAMERA_CONTROL_NOTIFY_INFO_TYPE  4
#define  VIDEO_WEATHER_WARNING_INFO_TYPE 5
#define  VIDEO_WEATHER_FORECAST_INFO_TYPE 6

//////////////////////////////////////////////////////////////////////////
//����ͷ��Ϣ--http--xml-����--����
typedef struct _VIDEO_LINKAGE_CAMERA_INFO_ 
{
	char	szCode[LINKAGE_DEVICE_CODE_LEN];
	char	szName[LINKAGE_DEVICE_NAME_LEN];
	int	nDecodeTag;
	char szPresetName[VIDEO_PRESET_NAME_LEN];
	int    nPresetId;
	int    nFromX1;
	int    nFromY1;
	int    nToX1;
	int    nToY1;
	int    nFromX2;
	int    nFromY2;
	int    nToX2;
	int    nToY2;
	char szSceneName[VIDEO_SCENE_NAME_LEN];
}VIDEO_LINKAGE_CAMERA_INFO;

//�ֶ���Ѳ������--http--xml-����--����
typedef struct _VIDEO_LINKAGE_INFO_ 
{
	char	szStationName[LINKAGE_STATION_NAME_LEN];
	char	szDeviceName[LINKAGE_DEVICE_NAME_LEN];
	int	nType; //1:�ֶ� 2:Ѳ��
	int    nScreenId;
	char szTime[LINKAGE_TIME_LEN];
	char szLinkageStationName[LINKAGE_STATION_NAME_LEN];
	int    nLinkNum;
	VIDEO_LINKAGE_CAMERA_INFO *pLinkageCameraInfo;
}VIDEO_LINKAGE_INFO;


//�澯����--http--xml--����--����
typedef struct _VIDEO_ALARM_LINKAGE_INFO_ 
{
	char	szStationName[LINKAGE_STATION_NAME_LEN];
	char	szDeviceName[LINKAGE_DEVICE_NAME_LEN];
	char szAlarmType[LINKAGE_TYPE_LEN];//�澯���쳣����λ��Խ�ޡ���֪�ͱ�������
	char szTime[LINKAGE_TIME_LEN];
	char szContent[LINKAGE_ALARM_CONTENT_LEN];
	char szLinkageStationName[LINKAGE_STATION_NAME_LEN];
	int    nLinkNum;
	VIDEO_LINKAGE_CAMERA_INFO *pLinkageCameraInfo;
}VIDEO_ALARM_LINKAGE_INFO;


//״̬����--http--xml--����--����
typedef struct _VIDEO_STATE_LINKAGE_INFO_ 
{
	char	szStationName[LINKAGE_STATION_NAME_LEN];
	char	szDeviceName[LINKAGE_DEVICE_NAME_LEN];
	char	szDeviceType[LINKAGE_TYPE_LEN];//��ѹ�������ء���բ���ݿ�������·��ĸ�ߡ������
	char szState[LINKAGE_STATE_INFO_LEN];//������λ���쳣��λ��Խ�ޡ���֪�����������ȶ�������
	char szTime[LINKAGE_TIME_LEN];
	char szContent[LINKAGE_ALARM_CONTENT_LEN];
	char szValue1[LINKAGE_VALUE_INFO_LEN];
	char szValue2[LINKAGE_VALUE_INFO_LEN];
	char szLinkageStationName[LINKAGE_STATION_NAME_LEN];
	int    nLinkNum;
	VIDEO_LINKAGE_CAMERA_INFO *pLinkageCameraInfo;
}VIDEO_STATE_LINKAGE_INFO;

//////////////////////////////////////////////////////////////////////////
//�ƾ�����--tcp--����
typedef struct _VIDEO_CAMERA_CONTROL_INFO_ 
{
	char szUserName[VIDEO_USER_NAME_LEN];
	char	szStationName[VIDEO_STATION_NAME_LEN];
	char	szDeviceName[VIDEO_DEVICE_NAME_LEN];
	char	szDeviceCode[VIDEO_DEVICE_CODE_LEN];
	int    nCommand;
	int    nCommandPara1;
	int    nCommandPara2;
	int    nCommandPara3;
}VIDEO_CAMERA_CONTROL_INFO;

//////////////////////////////////////////////////////////////////////////
//�ƾ�����֪ͨ��Ϣ--http--xml--����--����
typedef struct _VIDEO_CAMERA_CONTROL_NOTIFY_INFO_ 
{
	char	szStationName[VIDEO_STATION_NAME_LEN];
	char	szDeviceName[VIDEO_DEVICE_NAME_LEN];
	char	szDeviceCode[VIDEO_DEVICE_CODE_LEN];
	char szUserName[VIDEO_USER_NAME_LEN];
}VIDEO_CAMERA_CONTROL_NOTIFY_INFO;

//����澯
typedef struct _VIDEO_WEATHER_WARNING_INFO_
{
	char  szStationID[LINKAGE_ID_LEN];
	char szWeatherType[LINKAGE_TYPE_LEN];
	char szTypeName[LINKAGE_TYPE_NAME_LEN];
	char szWarnValue[LINKAGE_TYPE_VALUE_LEN];
	char szTime[LINKAGE_TIME_LEN];
	char szLinkageStationName[LINKAGE_STATION_NAME_LEN];
	int    nLinkNum;
	VIDEO_LINKAGE_CAMERA_INFO *pLinkageCameraInfo;
}VIDEO_WEATHER_WARNING_INFO;


//����Ԥ��
typedef struct _VIDEO_WEATHER_FORECAST_INFO_
{
	char  szID[LINKAGE_ID_LEN];
	char szWeatherType[LINKAGE_TYPE_LEN];
	char szTypeName[LINKAGE_TYPE_NAME_LEN];
	char szWeatherLevel[VIDEO_LINKAGE_INFO_LEN];
	char szAreaType[VIDEO_LINKAGE_INFO_LEN];
	char szCityID[VIDEO_LINKAGE_INFO_LEN];
	char szCountyID[VIDEO_LINKAGE_INFO_LEN];
	char szContent[LINKAGE_CONTENT_LEN];
	char szStartTime[LINKAGE_TIME_LEN];
	char szStopTime[LINKAGE_TIME_LEN];
	char szLinkageStationName[LINKAGE_STATION_NAME_LEN];
	int    nLinkNum;
	VIDEO_LINKAGE_CAMERA_INFO *pLinkageCameraInfo;
}VIDEO_WEATHER_FORECAST_INFO;


//�õ�Xml��Ϣ����
int GetXmlInfoType(char *strXml,int nLen);

// �����ֶ���Ѳ������
int ParseLinkageInfo(VIDEO_LINKAGE_INFO *pVideoLinkageInfo,const char *strXML);

// �����澯����
int ParseAlarmLinkageInfo(VIDEO_ALARM_LINKAGE_INFO *pVideoLinkageInfo,const char *strXML);

// ����״̬����
int ParseStateLinkageInfo(VIDEO_STATE_LINKAGE_INFO *pVideoLinkageInfo,const char *strXML);

// �����ƾ�����֪ͨ��Ϣ
int ParseCameraControlInfo(VIDEO_CAMERA_CONTROL_NOTIFY_INFO *pCameraControlNotifyInfo,const char *strXML);

// ��������澯����
int ParseWeatherWarningLinkageInfo(VIDEO_WEATHER_WARNING_INFO *pVideoLinkageInfo,const char *strXML);

// ��������Ԥ������
int ParseWeatherForecastLinkageInfo(VIDEO_WEATHER_FORECAST_INFO *pVideoLinkageInfo,const char *strXML);



#endif
