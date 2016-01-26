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

#define ACS_DEVICE_REALDATA_COUNT 1024	//һ��������1024���豸ʵʱ����

#define MAX_DEV_RELATION_CAMERA 16  //ÿ���豸����������Ƶ����


#define ACS_RECVBUFSIZE							1024*1024
#define ACS_SOCKETRECVBUFSIZE					1024*1024*16
#define ACS_SOCKETSENDBUFSIZE					1024*1024*16

///////////////////////////////////////�Ҽ��˵�/////////////////////////////////////////
#define ID_LINKAGE_INFO1 10001
#define ID_LINKAGE_INFO2 10002
#define ID_LINKAGE_INFO3 10003
#define ID_LINKAGE_INFO4 10004
#define ID_LINKAGE_INFO5 10005
#define ID_LINKAGE_INFO6 10006
#define ID_LINKAGE_INFO7 10007
#define ID_LINKAGE_INFO8 10008
#define ID_LINKAGE_INFO9 10009
#define ID_LINKAGE_INFO10 10010
#define ID_LINKAGE_INFO11 10011
#define ID_LINKAGE_INFO12 10012
#define ID_LINKAGE_INFO13 10013
#define ID_LINKAGE_INFO14 10014
#define ID_LINKAGE_INFO15 10015
#define ID_LINKAGE_INFO16 10016
////////////////////////////////////////////////////////////////////////////////////////

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
	char szCameraCode[32];
	int nPresetId;
	char szPresetName[64];
}T_LINKAGE_CAMERA_INFO;

#endif