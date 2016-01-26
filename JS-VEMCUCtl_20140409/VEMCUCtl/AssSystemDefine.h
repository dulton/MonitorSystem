/*
	����ϵͳ��ص�ȫ�ֶ���
*/
#ifndef _ASSSYSTEM_DEFINE_H_
#define _ASSSYSTEM_DEFINE_H_

////////////////////////////����ϵͳ���//////////////////////////////////////////////
#define ACS_LOGIN_SERVER_REQUEST                 1001   //��¼����
#define ACS_LOGIN_SERVER_RESPONSE                1002   //��¼��Ӧ

#define ACS_BEATHEART_REQUEST 1003    //��������
#define ACS_BEATHEART_RESPONSE  1004	//��������

#define ACS_PUSH_DATA_RESPONSE 1005	//��������

#define ACS_SUBSCRIBE_STATION_REQUEST 1006	//���վ����
#define ACS_SUBSCRIBE_STATION_RESPONSE 1007

#define ACS_Hide_DEV_REQUEST 1008    //�豸����
#define ACS_Hide_DEV_RESPONSE 1009

#define ACS_SUBSCRIBE_ALARM_REQUEST 1010 //�澯����
#define ACS_SUBSCRIBE_ALARM_RESPONSE 1011 //�澯����

#define ACS_PUSH_ALARM_RESPONSE 1012 //�澯����

#define ACS_LINKAGE_REALTIME_INFO_RESPONSE 1013 //����ʵʱ��Ϣ

#define ACS_DEVICE_REALDATA_COUNT 1024	//һ��������1024���豸ʵʱ����
#define ACS_PUSH_ALARM_COUNT 1024 //һ��������1024���澯��������
#define ACS_LINKAGE_REALTIME_INFO_COUNT 1024 //һ��������1024������ʵʱ����


#define ACS_RECVBUFSIZE							1024*1024
#define ACS_SOCKETRECVBUFSIZE					1024*1024*16
#define ACS_SOCKETSENDBUFSIZE					1024*1024*16

#define MAX_DEV_RELATION_CAMERA 16  //ÿ���豸����������Ƶ����

#define PRESETNUMMIN (5)
#define PRESETNUMMAX (10)

///////////////////////////////////////�Ҽ��˵�/////////////////////////////////////////
#define ID_LINKAGE_INFO1 (10011)
#define ID_LINKAGE_INFO2 (ID_LINKAGE_INFO1+1)
#define ID_LINKAGE_INFO3 (ID_LINKAGE_INFO1+2)
#define ID_LINKAGE_INFO4 (ID_LINKAGE_INFO1+3)
#define ID_LINKAGE_INFO5 (ID_LINKAGE_INFO1+4)
#define ID_LINKAGE_INFO6 (ID_LINKAGE_INFO1+5)
#define ID_LINKAGE_INFO7 (ID_LINKAGE_INFO1+6)
#define ID_LINKAGE_INFO8 (ID_LINKAGE_INFO1+7)
#define ID_LINKAGE_INFO9 (ID_LINKAGE_INFO1+8)
#define ID_LINKAGE_INFO10 (ID_LINKAGE_INFO1+9)
#define ID_LINKAGE_INFO11 (ID_LINKAGE_INFO1+10)
#define ID_LINKAGE_INFO12 (ID_LINKAGE_INFO1+11)
#define ID_LINKAGE_INFO13 (ID_LINKAGE_INFO1+12)
#define ID_LINKAGE_INFO14 (ID_LINKAGE_INFO1+13)
#define ID_LINKAGE_INFO15 (ID_LINKAGE_INFO1+14)
#define ID_LINKAGE_INFO16 (ID_LINKAGE_INFO1+15)

#define ID_HIDE_ALARM 10040	//���θ澯
#define ID_COMPLETE_PROCESS_ALARM 10050	//��ɴ���
#define ID_RECOVER_ALARM 10060	//�ָ��澯
#define ID_CANCEL_HIDE_ALARM 10070	//ȡ������
#define ID_DELETE_LINKAGE_RECORD 10071 //ɾ��������¼
#define ID_REMOVE_ALL_ITEMS 10072 //����б�
#define ID_SHOW_ELECMAP 10073	//��ʾ���ӵ�ͼ
#define ID_PROCESS_ALARM 10074	//����澯
#define ID_OPEN_VIDEO 10075	//����Ƶ
#define ID_DLG_CAMERA_AND_CONTROL_CLOSE_VIDEO 10076 //�ر���Ƶ

#define ID_DLG_ALARM_PREVIEW_VIEW_DETAIL 10077//�鿴��ϸ
#define ID_DLG_ALARM_PREVIEW_PROCESS_ALL 10078//ȫ������
#define ID_DLG_STATION_ALARM_DELETE_SELECTED_ITEMS 10079 //ɾ��ѡ����
///////////////////////////////////////////////////////////////////////////////////////////
#define HIDE_DEV 1	//�豸����
#define CANCEL_HIDE_DEV 0	//ȡ���豸����

#define PROCESS_ALARM 0 //�Ѵ���ĸ澯
#define UN_PROCESS_ALARM 1//δ����ĸ澯
#define COMPLETE_PROCESS_ALARM 2 //��ɴ���ĸ澯

//////////////////////////////////////////////////////////////////////////////////////////
#define LINKAGE_CAMERA 2  //2��ʾ�����豸����Ϊ����ͷ
#define LINKAGE_DOOR 1 //1��ʾ�����豸Ϊ�Ž�

#define LINKAGE_ACTION_OPEN 1 //��
#define LINKAGE_ACTION_CLOSE 2 //�ر�
#define LINKAGE_ACTION_PRESET 3 //תԤ��λ

#define LINKAGE_SHOW_TYPE_MULTIVIDEO 0 //�໭��չʾ
#define LINKAGE_SHOW_TYPE_ELECMAP 1	//���ӵ�ͼչʾ

/////////////////////////////////////////////////////////////////////////
#define BTNST_COLOR_BK_IN_COLOR RGB(158,195,225)
#define BTNST_COLOR_BK_OUT_COLOR RGB(195,220,242)
#define BTNST_COLOR_BK_FOCUS_COLOR RGB(158,195,225)

//dvr��Ϣ
typedef struct _ass_dvr_info_
{
	int nDvrId;
	char szDvrCode[32];
	char szDvrIp[32];
	int nDvrPort;
	char szDvrUserName[32];
	char szDvrPassword[32];
	char szDvrType[32];
	int nDvrType;
}ASS_DVR_INFO;

//����ͷ��Ϣ
typedef struct _ass_camera_info_
{
	char szCameraCode[32];
	char szCameraName[32];
	int nChannel;
	ASS_DVR_INFO tDvrInfo;
}ASS_CAMERA_INFO;

//�û�������־��¼�ṹ��
typedef struct _ass_user_operate_log
{
	int id;
	int user_id;
	char szUserName[32];
	char ip_address[32];
	char operate_time[64];
	char operate_action[128];
}ASS_USER_OPERATE_LOG;

//��¼���ؽṹ��
typedef struct _login_response
{
	int nResult;
}LOGIN_REPONSE;

//ͨ�õķ�����Ӧ��ֻ�гɹ���ʧ�ܺ�ʧ�ܴ�����
typedef struct _common_response
{
	int nResult;
	int nCode;
}COMMON_RESPONSE;

//���վ��Ϣ���ķ��ؽṹ��
typedef struct _subscribe_station_response
{
	int nResult;
}SUBSCRIBE_STATION_REPONSE;

//���վʵʱ��Ϣ�ṹ
typedef struct _push_data_response
{
	int nRvuId;
	int nSmId;
	int nNodeId;
	float fValue;
	int nType;
	int nStatus;
}PUSH_DATA_RESPONSE;

//�澯ͳ�ƽṹ��
typedef struct _alarm_statistics_
{
	int nStationId;//���վid
	char szStationName[64];//���վ���� 
	int nAlarmCount;//�澯����
}ALARM_STATISTICS;

//�澯����ʵʱ��Ϣ�ṹ
typedef struct _push_alarm_response
{
	int nDevId;
	int nStationId;
	int nAlarmType;
	char szAlarmStartTime[64];
	int nPriorLevel;
}PUSH_ALARM_RESPONSE;

typedef struct _linkage_realtime_info_response_
{
	int nDevID;
	char szCamreaCode[32];
	int nPresetNum;
	char szStartTime[32];
}LINKAGE_REALTIME_INFO_RESPONSE;

//ʵʱ���ݽṹ��
typedef struct _t_sm_realdata_
{
	int station_id;
	int dev_id;//�豸��dev_id
	int rvu_id;//rvu_id,sm_id,node_id,������һ�����ȷ��һ���豸
	int sm_id;
	int node_id;
	float real_value;//ʵʱ����ֵ
	int type;//����,YX,YC,YK��
	int status;//0����,1���ظ澯,2��Ҫ�澯,3һ��澯,4��Ч����
	int relation_video;//0δ������Ƶ��1������Ƶ
	char dev_name[32];//�豸����
}T_SM_REALDATA;

typedef struct _t_linkage_camera_info
{
	int nDevId;
	char szCameraCode[64];
	int nPresetId;
	char szPresetName[64];
}T_LINKAGE_CAMERA_INFO;

typedef struct _t_ass_linkage_realtime_info_
{
	int nDevId;
	int nRelateDevId;
	char szCamreaCode[32];
	int nRelateType;
	int nRelateAction;
	int nPresetNum;
	char szStartTime[32];
}T_ASS_LINKAGE_REALTIME_INFO;

//�������ýṹ��
typedef struct _t_ass_linkage_config_
{
	int nUserId;//�û�id��ÿ���û�����һ������
	int nShowType;//0:�໭�淽ʽչʾ��1�����ӵ�ͼ��ʽչʾ
	int nShowVideo;//0:��չʾ��Ƶ��1:չʾ��Ƶ
	int nChangeTime;//�¼��л�ʱ��
	int nSecurity;//0�������������澯,1:���������澯
	int nFire;//0�������������澯,1:���������澯
	int nDoorAlarm;//0���������Ž�����,1:�����Ž�����
	int nDoorAction;//0���������Ž�������,1:�����Ž�������
}T_ASS_LINKAGE_CONFIG;

typedef struct _t_ass_subscribe_info_
{
	int nId;
	int nUserId;
	int nStatiionId;
}T_ASS_SUBSCRIBE_INFO;

typedef struct _acs_dev_info
{
	int nDevId;
	char szDevName[64];
	int nRelationVideo;
	int nRvuId;
	int nSmId;
}ACS_DEV_INFO;

typedef struct _acs_station_info
{
	int nStationId;
	char szStationName[64];
	int nVolClass;
}ACS_STATION_INFO;

typedef struct _acs_alarm_info_
{
	int nId;
	int nDevId;
	int nStationId;
	char szVolGrade[32];//��ѹ�ȼ�
	char szStationName[32];//���վ����
	char szDevName[32];//�澯�豸����
	int nAlarmType;//�澯����
	char szAlarmTypeName[32];//�澯�������� 
	char szAlarmStartTime[32];//�澯����ʱ��
	char szAlarmProcessTime[32];//�澯����ʱ��
	char szAlarmProcessUser[32];//�澯������Ա
	char szAlarmHideTime[32];//�澯����ʱ��
	int nRelationVideo;//�Ƿ������Ƶ 1��ʾ������Ƶ��0��ʾδ������Ƶ
	int nPriorLevel;//���ȼ�
	int nStatus;//����״̬ 0��ʾ�Ѵ���1��ʾδ����,2��ʾ�������
}ACS_ALARM_INFO;

typedef struct _ass_linkage_list_item_
{
	int nDevId;
	char szDevName[32];
	int nRelateDevId;
	char szRelateDevName[32];
	char szCamreaCode[32];
	char szCameraName[32];
	int nRelateType;
	int nRelateAction;
	int nPresetNum;
	char szStartTime[32];
}ASS_LINKAGE_LIST_ITEM;































#endif