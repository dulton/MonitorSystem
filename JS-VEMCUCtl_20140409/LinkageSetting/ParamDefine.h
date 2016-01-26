#ifndef _PARAM_DEFINE_H_
#define _PARAM_DEFINE_H_

#define MAX_RECV_BUFF_SIZE   64*1024
#define MAX_SEND_BUFF_SIZE   64*1024

#define SERVERSOCKET_MAXNUM					100
#define CLIENTSOCKET_MAXNUM					1000

#define RECVBUFSIZE							1024*1024
#define SOCKETRECVBUFSIZE					1024*1024*16
#define SOCKETSENDBUFSIZE					1024*1024*16

#define SOCKETSENDBUFMAXSIZE				1453

#define STOPALL				0	//ֹͣ��ǰ����
#define	TILTUP				1	//����
#define TILTDOWN			2   //����
#define PANLEFT				3	//��ת
#define PANRIGHT			4	//��ת
#define CLOSEIRIS			5	//��Ȧ��
#define OPENIRIS			6	//��Ȧ��
#define FOCUSNEAR			7	//���۽�
#define FOCUSFAR			8   //Զ�۽�
#define ZOOMIN				9	//��С
#define ZOOMOUT				10	//�Ŵ�
#define UPLEFT				17	//���Ϸ����˶�
#define DOWNLEFT			18	//���·����˶�
#define UPRIGHT				19	//���Ϸ����˶�
#define DOWNRIGHT			20	//���·����˶�

#define YT_CLOSEIRISSTOP		0x0101	//��Ȧ��ֹͣ
#define YT_CLOSEIRIS			0x0102	//��Ȧ��
#define YT_OPENIRIS			0x0103	//��Ȧ��
#define YT_OPENIRISSTOP		0x0104	//��Ȧ��ֹͣ
#define YT_FOCUSNEARSTOP		0x0201	//���۽�ֹͣ
#define YT_FOCUSNEAR			0x0202	//���۽�
#define YT_FOCUSFARSTOP		0x0203	//Զ�۽�ֹͣ
#define YT_FOCUSFAR			0x0204  //Զ�۽�
#define YT_ZOOMINSTOP			0x0301  //��Сֹͣ
#define YT_ZOOMIN				0x0302	//��С
#define YT_ZOOMOUTSTOP			0x0303	//�Ŵ�ֹͣ
#define YT_ZOOMOUT				0x0304	//�Ŵ�
#define YT_TILTUPSTOP			0x0401	//����ֹͣ
#define	YT_TILTUP				0x0402	//����
#define YT_TILTDOWNSTOP		0x0403	//����ֹͣ
#define YT_TILTDOWN			0x0404  //����
#define YT_PANRIGHTSTOP		0x0501	//��תֹͣ
#define YT_PANRIGHT			0x0502	//��ת
#define YT_PANLEFTSTOP			0x0503	//��תֹͣ
#define YT_PANLEFT				0x0504	//��ת
#define YT_SETPRESET			0x0601	//Ԥ��λ����
#define YT_GOTOPRESET			0x0602	//Ԥ��λ����
#define YT_CLEPRESET			0x0603	//Ԥ��λɾ��
#define YT_UPLEFTSTOP			0x0701	//���Ϸ����˶�ֹͣ
#define YT_UPLEFT				0x0702	//���Ϸ����˶�
#define YT_DOWNLEFTSTOP		0x0703	//���·����˶�ֹͣ
#define YT_DOWNLEFT			0x0704	//���·����˶�
#define YT_UPRIGHTSTOP			0x0801	//���Ϸ����˶�ֹͣ
#define YT_UPRIGHT				0x0802	//���Ϸ����˶�
#define YT_DOWNRIGHTSTOP		0x0803	//���·����˶�ֹͣ
#define YT_DOWNRIGHT			0x0804	//���·����˶�

#define NAMELENGTH			40	//������������	40	40�ֽڳ�
#define PASSWORDLEN			20	//�����	20	20�ֽڳ�
#define DES_LENGTH			160 //������Ϣ����	160	160�ֽڳ�
#define UNIT_LENGTH			8   //���ݵ�λ�ĳ���	8	8�ֽڳ�
#define VER_LENGTH			40  //�汾�����ĳ���	40	40�ֽڳ�
#define PHONE_LENGTH		20  //�绰���볤��	20	20�ֽڳ�
#define DATA_LENGTH			60  //���ݳ���	60	60�ֽڳ�
#define SDESC_LENGTH		80  //����������	80	80�ֽڳ�
#define CARDLENGTH			20  //���ų���	20	20�ֽڳ�

#define MAIN_TITLE_HEIGHT           140
#define MAIN_BUTTON_WIDTH           131
#define MAIN_BUTTON_HIGHT           27

#define REQUEST_RVU_LOGIN                 101
#define RESPONSE_RVU_LOGIN                102
#define REQUEST_RVU_GET_SM                201
#define RESPONSE_RVU_SET_SM               202
#define REQUEST_RVU_GET_NODES             203
#define RESPONSE_RVU_SET_NODES            204
#define REQUEST_RVU_SET_DYN_ACCESS_MODE   301
#define RESPONSE_RVU_DYN_ACCESS_MODE_ACK  302

#define SEND_REALTIME_ALARM               401
#define HEART_BEAT                      601
#define HEART_BEAT_ACK                  602

#define REQUEST_RVU_SET_POINT            501
#define RESPONSE_RVU_SET_POINT_ACK       502

#define MAX_FRAME_LEN   (1452+8)
#define USER_DATA_OFFSET  30
#define DATA_FRAME_HEADER  8
#define ETHERNET_FRAME_HEADER 14
#define SET_SM_ACK_DATA_OFFSET  30

#define MAX_SM_NUM_PER_STATION  128
#define MAX_NODE_NUM_PER_STATION 256

#define MAX_STATION_NUM_PER_USER  1024
#define MAX_DVR_NUM_PER_USER      (MAX_STATION_NUM_PER_USER*16)
#define MAX_CAMERA_NUM_PER_USER   (MAX_DVR_NUM_PER_USER*16)

#define MAX_RVU_NUM_PER_STATION  16
#define MAX_RVU_DEVICE_NUM_PER_STATION 1024

#define DATABASE_OPERATE_INSERT   1
#define DATABASE_OPERATE_UPDATE   2
#define DATABASE_OPERATE_DELETE   3

#define CAMERA_SUB_SYSTEM	1
#define DOOR_SUB_SYSTEM	2
#define ENVIRONMENT_SUB_SYSTEM	3
#define SECURITY_SUB_SYSTEM	4
#define LIGHT_SUB_SYSTEM	5
#define FIRE_SUB_SYSTEM	6
#define OTHER_SUB_SYSTEM 7

////////////////////////////////////������֮����Ϣ����////////////////////////////////
#define WM_ADD_DEVICE_LEDGER_COMPLETED (WM_USER+10000)

typedef struct _recv_packet_
{
	char recvbuf[RECVBUFSIZE];
	int size;
	int handle;
}RECV_PACKET;

typedef struct _t_ttime_
{
	short years;
	char month;
	char day;
	char hour;
	char minute;
	char second;
	char milsecond;
}TTime;

typedef struct _t_tid_
{
	short sm_id;
	short node_id;
}TID;

typedef struct _t_tsm_
{
	long size;
	long type;
	TID id;
	long member_id;
	long port_id;
	short port_mode;
	short baudrate;
	long address;
	float longitude;
	float latitude;
	char sm_name[NAMELENGTH];
	char desc[SDESC_LENGTH];
	long device_type;
	long sub_device_type;
	char productor[NAMELENGTH];
	char vision[VER_LENGTH];
	long camera_channel;
	long rvu_id;
	long reserve1;
	char reserve2[NAMELENGTH];
}TSM;

typedef struct _t_talarm_
{
	long type;//���ݵ�����
	TID id;//���ݵ�ID
	TTime starttime;//�澯����ʱ��
	TTime endtime;//�澯����ʱ��
	TTime confirmtime;//�澯ȷ��ʱ��
	TTime canceltime;//�澯ȡ��ʱ��
	long alarm_level;//�澯����0-�޸澯�жϣ�1-���ظ澯��2-��Ҫ�澯��3-һ��澯
	float alarm_value;//�澯��ֵ��
	long  alarm_status;//�ϴ��澯�����͡�0-��ʼ��1-������2-ȷ�ϣ�3-ȡ��
	char description[DATA_LENGTH];//�澯ֵ����
}TALARM;

typedef struct _t_tnode_
{
	long size;//�����ݽṹ�ĳ���
	long type;//���ݵ�����
	TID id;//���ݱ�ʶID
	TID virtual_id;//����
	char node_name[NAMELENGTH];
	char desc[SDESC_LENGTH];
	float max_val;//��Ч����
	float min_val;//��Ч����
	long alarm_enable;//�澯ʹ�ܱ��
	float HiLimit1;//һ���澯����
	float LoLimit1;//һ���澯����
	float HiLimit2;//�����澯����
	float LoLimit2;//�����澯����
	float HiLimit3;//�����澯����
	float LoLimit3;//�����澯����
	float percision;//����
	long lSaved;//�Ƿ񱣴�
	char unit[UNIT_LENGTH];//��λ
	long phy_id;//��Ӧ������ڵ�
	long reserver1;//����1
	long reserver2;//����2
	long reserver3;//����3
	long reserver4;//����4
}TNODE;

//typedef struct _recv_packet_ 
//{
//	char recvbuf[MAX_RECV_BUFF_SIZE];
//	int size;
//}RECV_PACKET;

typedef struct DBConfigParam 
{
	char DBServerIP[16];
	int  DBServerPort;
	char DBName[32];
	char DBUserName[32];
	char DBUserPassword[32];
}DBConfigParam;

typedef struct RVUConfig
{
	char rvu_ip[24];
	int  rvu_port;
	char rvu_username[32];
	char rvu_password[32];
}RVUConfig;

typedef  struct StationNode
{
	int station_id;
	char station_code[32];
	char station_name[64];
	int node_type;
	int connect_ptu;//0-��ʾδ���ӣ�1��ʾ����
}StationNode;

typedef struct nodeinfo
{
	int  node_id;
	int  parent_id;
	int  station_id;
	int  dvr_id;
	int  channel_id;
	char node_name[64];
	char node_code[32];
	int node_type;
	int node_level;
}NodeInfo;

typedef struct ACCESS_METHOD_IP 
{
	char ip_addr[32];
	int  ip_protocol;
	int ip_port;
}ACCESS_METHOD_IP;

typedef struct ACCESS_METHOD_SERIAL 
{
	char local_addr[32];
	int local_port;
	char device_addr[32];
	int device_port;
	int serial_bandrate;
	int serial_data;
	int serial_stopdata;
	int serial_parity;
}ACCESS_METHOD_SERIAL;

typedef struct ACCESS_DEVICE_INFO
{
	int id;
	char dev_code_sys[32];
	int node_code_id;
	char dev_name[64];
	int connect_type;
	ACCESS_METHOD_IP access_ip;
	ACCESS_METHOD_SERIAL access_serial;
	char login_name[64];
	char login_password[32];
	int dev_type;
	int factory_type;
	int yx_num;
	int yc_num;
	int yk_num;
	int yt_num;
	int camera_num;
}ACCESS_DEVICE_INFO;

typedef struct _vem_user_config_info_
{
	char szUserName[256];
	char szUserPassword[64];
	char szLocalUdpIp[32];
	int    nLocalUdpPort;
	int    nMinRtpPort;
	int    nMaxRtpPort;
	char szSipServerIp[32];
	int    nSipServerPort;
	char szHttpServerIp[32];
	int    nHttpServerPort;
	char szDBServerIp[32];
	int    nDBServerPort;
	char szDBName[256];
	char szLinkServerIp[32];
	int    nLlinkServerPort;
	int    nPreSetSaveEnable;
	int nAcsTcpHandle;
	char szAcsServerIp[32];
	int nAcsServerPort;
	int nUserId;
}VEM_USER_CONFIG_INFO;

typedef struct CAMERA_INFO
{
	char ip_addr[32];
	int ip_port;
	char login_name[64];
	char login_password[32];
	char szDvrType[32];
	int dvr_type;
	int dvr_id;
	int channel;
}CAMERA_INFO;
//��ϵͳö��
enum SUB_SYSTEM_TYPE
{
	ALL_SUB_SYSTEM         = 1000,//ȫ����ϵͳ
	DOOR_ACCESS            = 1001,//�Ž���ϵͳ
	VIDEO_MONITOR          = 1002,//��Ƶ�����ϵͳ
	ENVIRONMENT_MONITOR    = 1003,//���������ϵͳ
	FIRE_PROTECTING        = 1004,//������ϵͳ
	SECURITY_PROTECTING    = 1005,//������ϵͳ
	LIGHT_CONTROL          = 1006,//�ƹ������ϵͳ
	POWER_MONITOR          = 1007,//��Դ�����ϵͳ
	SCADA_SYSTEM           = 1008,//SCADAϵͳ
	FIVE_PROTECTING        = 1009,//���ϵͳ
	ROUTING_CHECK          = 1010//Ѳ��ϵͳ
}SUB_SYSTEM_TYPE;

//��ϵͳ�豸ö������
enum SUB_SYSTEM_DEVICE_TYPE
{
	DOOR_ACCESS_DEVICE            = 1,//�Ž��豸
	VIDEO_MONITOR_DEVICE          = 2,//��Ƶ�����ϵͳ�豸
	ENVIRONMENT_MONITOR_DEVICE    = 3,//���������ϵͳ
	FIRE_PROTECTING_DEVICE        = 4,//������ϵͳ
	SECURITY_PROTECTING_DEVICE    = 5,//������ϵͳ
	LIGHT_CONTROL_DEVICE          = 6,//�ƹ������ϵͳ
	POWER_MONITOR_DEVICE          = 7,//��Դ�����ϵͳ
	SCADA_SYSTEM_DEVICE           = 8,//SCADAϵͳ
	FIVE_PROTECTING_DEVICE        = 9,//���ϵͳ
	ROUTING_CHECK_DEVICE          = 10//Ѳ��ϵͳ
}SUB_SYSTEM_DEVICE_TYPE;

enum ACCESS_DEVICE_FACTORY
{
	HK_DVR_LESS_8000  =   2000,//����DVR/DVS 8000����
	HK_DVR_MORE_8000,//����DVR/DVS 8000����
	DH_BOARD,//�󻪰忨
	DH_DVR,//��DVR
	HY_BOARD,//���ڰ忨
	HY_DVR,//����DVR/DVS
	HB_BOARD,//����忨
	HB_DVR,//����DVR
	LSZX_BOARD,//��ɫ֮�ǰ忨
	LSZX_DVR,//��ɫ֮��DVR
	DLink_BOARD,//DLink�忨
	DLink_DVR,//DLink DVR
	DL_BOARD,//�����忨
	DL_DVR,//����DVR
	ZY_DVR,//�㶫����DVR
	AXIS_BOARD,//��Ѷ�Ӱ忨
	AXIS_DVR,//��Ѷ��DVR
	MOBOTIX_DVR,//MOBO DVR
	NAZI_BOARD,//������Ϣ�忨
	NAZI_DVR,//������ϢDVR
	PANASONIC_IP_CAMERA,//
	Emerson_DVR,//��Ĭ��DVR
	CL_DVR,//����DVR

	NARI_DOOR_SYSTEM = 2100,//�����Ž�ϵͳ������ֱ�ӶԽ�ϵͳ
	NARI_DOOR_CONTROL_1,//����XX1�ͺ��Ž�������
	NARI_DOOR_CONTROL_2,//����XX2�ͺ��Ž�������
	NAZI_DOOR_SYSTEM,//�����Ž�ϵͳ������ֱ�ӶԽ�ϵͳ
	NAZI_DOOR_CONTROL_1,//����XX1�ͺ��Ž�������
	NAZI_DOOR_CONTROL_2,//����XX2�ͺ��Ž�������
	NBE_DOOR_SYSTEM,//Ŧ�����Ž�ϵͳ������ֱ�ӶԽ�ϵͳ
	NBE_DOOR_CONTROL_1,//Ŧ����XX1�ͺ��Ž�������
	NBE_DOOR_CONTROL_2,//Ŧ����XX2�ͺ��Ž�������
	QF_DOOR_SYSTEM,//����Ž�ϵͳ������ֱ�ӶԽ�ϵͳ
	QF_DOOR_CONTROL_1,//���XX1�ͺ��Ž�������
	QF_DOOR_CONTROL_2,//���XX2�ͺ��Ž�������

	HK_MASTER = 2200,//������������
	NARI_MASTER,//���𻷾�����
	XX_ELECTRIC_FENCE,//XX���ҵ���Χ��
	XX_FIRE_CONTROL_MASTER,//������������
	XX_AIR_CONDITION,//�յ�����
	XX_SECURITY_CONTROL_MASTER,//������������

	XX_LIGHT_CONTROL_MASTER = 2700,//�ƹ��������

	ACCESS_DEVICE_FLAG = 2899
}ACCESS_DEVICE_FACTORY;

//////////////////////////////////////////////////////////////////////////

#define DEVICE_OFF_LINE_TEXT "�豸����"
#define VIDEO_MOTION_DETECT_ALARM_TEXT "�ƶ����澯"
#define VIDEO_SHELTER_ALARM_TEXT "��Ƶ�ڵ��澯"
#define VIDEO_BORDER_DETECT_ALARM_TEXT "��Ƶ�߽���澯"
#define VIDEO_OPEN_TEXT "�û�����Ƶ"

#define DVR_HIGHER_ALARM_TEXT "DVR�豸����"
#define DVR_LOWER_ALARM_TEXT "DVR�豸����"
#define DVR_FUN_ALARM_TEXT "DVR���ȹ���"
#define DVR_HARDDISK_ALARM_TEXT "DVR���̹���"

#define AD_UP_ALARM_TEXT "ģ�������޸澯"
#define AD_UP_UP_ALARM_TEXT "ģ���������޸澯"
#define AD_LOW_ALARM_TEXT "ģ�������޸澯"
#define AD_LOW_LOW_ALARM_TEXT "ģ���������޸澯"

#define STATUES_ALARM_TEXT "״̬���澯"

#define DOOR_CONTROL_LOW_POWER_TEXT "������"
#define DOOR_CONTROL_ILLEGAL_TEXT "�Ƿ�ˢ��"
#define DOOR_CONTROL_OFFLINE_ALARM_TEXT "�ѻ�����"
#define DOOR_CONTROL_STRESSED_TEXT "��в��"
#define DOOR_CONTROL_NO_LOCK_TEXT "δ����"
#define DOOR_CONTROL_FORCE_BREAKIN_TEXT "ǿ�д���"
#define YX_DATA_IS_1_TEXT  "ң������������Ϊ1"
#define YX_DATA_IS_0_TEXT "ң������������Ϊ0"
#define YC_DATA_CHANGE_NORMAL_TEXT "ң�����������仯"
#define YK_EVENT_OPERATE_NORMAL_TEXT "ң���¼���������"

#define DOOR_OPEN_IN_CARD_TEXT "ˢ������"
#define DOOR_OPEN_IN_PASSWORD_TEXT "���뿪��"
#define DOOR_OPEN_IN_REMOTE_CONTROL_TEXT "Զ�̿���"
#define DOOR_OPEN_IN_FORCE_TEXT "ǿ�п���"
//////////////////////////////////////////////////////////////////////////
enum DEVICE_ALARM_INFO
{
	DEVICE_OFF_LINE =2900,//�豸����
	VIDEO_MOTION_DETECT_ALARM,//�ƶ����澯
	VIDEO_SHELTER_ALARM,//��Ƶ�ڵ��澯
	VIDEO_BORDER_DETECT_ALARM,//��Ƶ�߽���澯
	VIDEO_OPEN,//�û�����Ƶ

	DVR_HIGHER_ALARM = 2910,//DVR�豸����
	DVR_LOWER_ALARM,//DVR�豸����
	DVR_FUN_ALARM,//DVR���ȹ���
	DVR_HARDDISK_ALARM,//DVR���̹���

	AD_UP_ALARM = 2920,//ģ�������޸澯
	AD_UP_UP_ALARM,//ģ���������޸澯
	AD_LOW_ALARM,//ģ�������޸澯
	AD_LOW_LOW_ALARM,//ģ���������޸澯

	STATUES_ALARM = 2930,//״̬���澯

	DOOR_CONTROL_LOW_POWER = 2940,//������
	DOOR_CONTROL_ILLEGAL,//�Ƿ�ˢ��
	DOOR_CONTROL_OFFLINE_ALARM,//�ѻ�����
	DOOR_CONTROL_STRESSED,//��в��
	DOOR_CONTROL_NO_LOCK,//δ����
	DOOR_CONTROL_FORCE_BREAKIN//ǿ�д���
}DEVICE_ALARM_INFO;//�豸�澯����

enum DEVICE_EVENT_INFO
{
	YX_DATA_IS_1 = 3000,//ң������������Ϊ1
	YX_DATA_IS_0,//ң������������Ϊ0
	YC_DATA_CHANGE_NORMAL,//ң�����������仯
	YK_EVENT_OPERATE_NORMAL,//ң���¼���������

	DOOR_OPEN_IN_CARD = 3031,//ˢ������
	DOOR_OPEN_IN_PASSWORD,//���뿪��
	DOOR_OPEN_IN_REMOTE_CONTROL,//Զ�̿���
	DOOR_OPEN_IN_FORCE//ǿ�п���
}DEVICE_EVENT_INFO;//�豸�¼�����

enum CU_LINKAGE_EVENT_TYPE
{
	CU_OPEN_VIDEO = 3101,//�����������豸��Ƶ
	CU_VOICE_TALK,//�����Խ�
	CU_LOCAL_RECORD,//����¼��
	CU_CAPITURE_PIC,//ץͼ
	CU_GOTO_PRESET,//ת��Ԥ��λ
	CU_CRUISE,//Ѳ��
	CU_TRAIL,//�켣
	CU_AUTO_TRACK,//�Զ�����
	CU_YK_ADJUST,//ң��������
	CU_AD_ADJUST,//ģ��������
	CU_SOUND_ALARM,//��������
	CU_LIGHT_ALARM,//�ƹⱨ��
	CU_LINKAGE_DATA_DISPLAY,//���������豸����չʾ
	CU_FLASH_2D_EMAP,//�����¼������ڶ�ά���ӵ�ͼ����˸
	CU_FLASH_3D_EMAP//�����¼���������ά���ӵ�ͼ����˸
}CU_LINKAGE_EVENT_TYPE;//�ͻ������������¼�����

enum PTS_LINKAGE_EVENT_TYPE
{
	PTS_LOCAL_RECORD=3201,//����¼��
	PTS_CAPITURE_PIC,//ץͼ
	PTS_GOTO_PRESET,//ת��Ԥ��λ
	PTS_CRUISE,//Ѳ��
	PTS_TRAIL,//�켣
	PTS_AUTO_TRACK,//�Զ�����
	PTS_YK_ADJUST_ON,//ң�������ƿ�
	PTS_YK_ADJUST_OFF,//ģ�������ƹ�
	PTS_AD_ADJUST,//ģ����������һ��
}PTS_LINKAGE_EVENT_TYPE;//��̨���������¼�����

typedef struct _t_ass_login_user_info_
{
	char szUserName[64];
	BYTE usertype;
	BYTE enablectrl_p;
	BYTE realtalk_p;
	BYTE eventlog_p;
	BYTE replay_p;
	BYTE alarm_p;
	BYTE tunecycle_p;
	BYTE usermanage_p;
	BYTE devicemanage_p;
	BYTE videorecord_p;
	BYTE elecmap_p;
	BYTE result;
}_T_ASS_LOGIN_USER_INFO_;

#define ACCESS_DEVICE_NODE         100
#define YX_DEVICE_NODE             200
#define YC_DEVICE_NODE             201
#define YK_DEVICE_NODE             202
#define YT_DEVICE_NODE             203


#define DVR_DEVICE_NODE            210
#define CAMERA_DEVICE_NODE         211
#define CAMERA_PRESET_NODE         212


#define DOOR_CARD_NODE_PARENT      300
#define DOOR_CARD_NODE             301
#define DOOR_CONTROL_DEVICE_NODE   302


#define COMBO_GAIN_VALUE  1001

#define DEPARTMENT_NODE             10
#define USER_NODE                   20
#define POWER_NODE                  30

#define ENABLE_CTRL                 31
#define REALTALK_P                  32
#define EVENTLOG_P                  33
#define REPALY_P                    34
#define ALARM_P                     35
#define TUNECYCLE_P                 36
#define USERMANAGER_P               37
#define DEVICEMANAGER_P             38
#define TIMERECORD_P                39
#define ELECMAP_P                   40

#define USE_SEPRATE_DVR_SDK  1


#define MAX_VIDEO_NUM      9


#define MULTIVIEW_STATION_CAMERA_LIST_WIDTH  200
#define MULTIVIEW_LINKAGE_INTERVAL    15
#define MULTIVIEW_TITLE_HEIGHT        30
#define MULTIVIEW_ALARM_INFO_HEIGHT         200

//////////////////////////////////////////////////////////////////////////
#define MAX_STATION_OB_NODE_NUM    128
#define MAX_STATION_OB_ACCESS_DEV  256
#define MAX_STATION_OB_CAMERA      512
#define MAX_STATION_ST_RELATION    1024
#define MAX_STATION_OB_YK          1024
#define MAX_STATION_OB_YT          1024
#define MAX_STATION_OB_YC          1024
#define MAX_STATION_OB_YX          1024
#define MAX_STATION_OB_CARD        512
#define MAX_STATION_CAMERA_PRESET  2048
#define MAX_STATION_CT_USER        1024
//////////////////////////////////////////////////////////////////////////
//windows��Ϣ�Զ���
#define WM_CLOSE_VIDEO   (WM_USER + 100)
#define WM_YT_CONTROL    (WM_USER + 101)
#define WM_PRESET_ID_CHANGE  (WM_USER + 102)

#define OM_MESSAGE_MULTI_CHANNEL_CHANGE  (WM_USER + 200)
#define OM_MESSAGE_MULTI_YTCONTROL (WM_USER + 201)
#define OM_MESSAGE_MULTI_POPUP_MENU (WM_USER + 202)
#define OM_MESSAGE_SUBSYSTEM_SELECT_CHANGE (WM_USER + 203)
#define OM_MESSAGE_CAMERA_CONTROL (WM_USER + 300)
//////////////////////////////////////////////////////////////////////////
//��ʱ������
#define TIMER_TUNE_CYCLE_AUTO  1
#define TIME_SPAN_TUNE_CYCLE_AUTO   10
//////////////////////////////////////////////////////////////////////////
#define VIEW_CHANNEL_WINDOW_CONTROLID  1000
//////////////////////////////////////////////////////////////////////////
#define MULTIVIEW_CHILD_WINDOW     1
#define ASS_DEVICE_MONITOR_WINDOW  2
#define ELECMAP_CHILD_WINDOW       3
#define HISTORYLOG_CHILD_WINDOW    4
#define REALPLAY_CHILD_WINDOW      5
#define PTU_CHILD_WINDOW           6
#define PLATFORM_SYN_CHILD_WINDOW  7
#define PLATFORM_ASS_LINKAGE_WINDOW 8
//////////////////////////////////////////////////////////////////////////
//XML������Ϣ����
#define ASS_RESPONSE_LOGIN           1
#define ASS_RESPONSE_LOGOUT          2
#define ASS_KEEPALIVE                3
#define ASS_RESPONSE_YK_CONTROL      4
#define ASS_RESPONSE_REALTIMESTATUS   5
//////////////////////////////////////////////////////////////////////////
//�ڵ㶨��
#define ROOT_NODE     0
#define STATION_NODE  1
#define SUBSYSTEM_NODE 2
#define DVR_NODE  3
#define CAMERA_NODE  4
#define RVU_NODE   5
#define RVU_DEVICE_NODE 6
#define PRESET_NODE  7
#define DEVICE_LEDGER_NODE 8

//ÿ���ڵ��������Ӧ�Ľṹ��
enum TREE_NODE_TYPE
{
	ENUM_ROOT_NODE = 0,		//���ڵ�
	ENUM_STATION_NODE = 1,	//���վ�ڵ�
	ENUM_SUBSYSTEM_NODE = 2,	//��ϵͳ�ڵ�
	ENUM_DVR_NODE = 3,	//dvr�ڵ�
	ENUM_CAMERA_NODE = 4,	//����ͷ�ڵ�
	ENUM_RVU_NODE = 5,	//rvu�ڵ�
	ENUM_RVU_DEVICE_NODE = 6,	//rvu�豸�ڵ�
	ENUM_PRESET_NODE = 7,	//Ԥ��λ�ڵ�
	ENUM_DEVICE_LEDGER_NODE = 8,	//�豸̨�˽ڵ�
	ENUM_DEVICE_TYPE_NODE = 9	//�豸���ͽڵ�
};

typedef struct _t_ass_tree_node_
{
	TREE_NODE_TYPE enumTreeNodeType;
	char *body;
}T_ASS_TREE_NODE;

typedef struct _t_ass_device_type_
{
	int nId;
	int nParentId;
	char szDeviceTypeName[32];
	int nDeviceTypeNum;
}T_ASS_DEVICE_TYPE;

typedef struct _t_ass_subsystem_
{
	int nId;
	int nParentId;
	char szSubSystemName[32];
	int nSubSystemNum;
}T_ASS_SUBSYSTEM;

//���ݱ���
typedef struct _t_acs_station_ob_node_
{
	int id;
	int parent_id;
	char node_name[64];
	char node_sysid[32];
	int node_type;
}_T_ACS_STATION_OB_NODE_;

typedef struct _t_ass_station_ob_node_
{
	int id;
	int parent_id;
	char node_name[64];
}_T_ASS_STATION_OB_NODE_;

typedef struct _t_acs_station_ob_access_dev_
{
	int id;
	int parent_id;
	char dev_code_sys[32];
	char dev_name[64];
	BYTE connect_type;
	char ipaddr[24];
	BYTE ip_protocol;
	int ipport;
	char local_addr[32];//���ش��ڵ�ַ
	int local_port;//���ش��ڶ˿�
	char serial_device_addr[32];//�����豸���ڵ�ַ
	int serial_device_port;//�����豸�˿�
	int bandrate;//������
	int data;//����λ
	int stopdata;//ֹͣλ
	int parity;//У��λ
	char username[64];//��½�û���
	char userpassword[32];//��½�û�����
	BYTE dev_type;//�����豸����
	int factory_type;//��������
	int yx_num;//ң���豸����
	int yc_num;//ң���豸����
	int yk_num;//ң���豸����
	int yt_num;//ң���豸����
	int camera_num;//camera����
	BYTE dev_online_state;//�豸״̬
}_T_ACS_STATION_OB_ACCESS_DEV_;

typedef struct _t_acs_station_ob_camera
{
	int id;
	int accessdev_code_id;
	char camera_name[64];
	char camera_code[32];
	BYTE camera_channel;
	BYTE camera_online_state;
}_T_ACS_STATION_OB_CAMERA_;

typedef struct _t_acs_station_linage_relation
{
	int id;//���к�
	int event_access_dev_id;//�����¼�������ϵͳ����Ӧob_acess_dev�е�id
	int event_dev_id;//��Ӧyk��yc��yt��yx��camera�е�id
	int event_type;//�����¼����ͣ�0�¼����� 1�澯����
	int event_reason;//�����¼�ԭ��
	char event_reason_text[64];//�����¼�ԭ������
	int action_access_dev_id;//��������������ϵͳ�е��豸,��Ӧob_access_dev�е�id
	int action_dev_id;//��Ӧyk��yc��yt��yx��camera�е�id
	int action_level;//���������ȼ�
	int action_type;//���������¼�����
	char action_type_text[64];//���������¼������ı�
	int action_pretime;//¼��ץͼԤ¼ʱ��
	int action_time;//¼��ץͼ����ʱ��
	int action_timeinterval;//ץͼʱ����
	int action_digital;//��������Ԥ��λ��ŵ�
	int action_yk;//���������ƣ�һ��Ϊ0��1
	char action_analog[32];//�豸����
}_T_ACS_STATION_LINKAGE_RELATION_;

typedef struct _t_acs_station_ob_yk
{
	int id;//���к�
	char yk_code_sys[32];//ң���豸��ƽ̨�еı���
	int access_code_id;//������ob_access_dev�е�id
	int yk_type;
	char yk_name[64];//ң���豸����
	char yk_addr[32];//ң���豸�š��˿ں�
	int normal_state;//����״ֵ̬
	int current_state;//��ǰ״ֵ̬
	BYTE dev_online_state;//����״̬
}_T_ACS_STATION_OB_YK_;

typedef struct _t_acs_station_ob_yt
{
	int id;//���к�
	char yt_code_sys[32];//ң���豸��ƽ̨�еı���
	int access_code_id;//������ob_access_dev�е�id
	int yt_type;
	char yt_name[64];//ң���豸����
	char yt_addr[32];//ң���豸�š��˿ں�
	float setting_value;//�趨ֵ
	float current_value;//��ǰֵ
	BYTE dev_online_state;//����״̬
}_T_ACS_STATION_OB_YT_;

//�豸
class CRvuDevice
{
public:
	int id;
	int sub_sys_id;
	int rvu_id;
	int sm_id;
	char sm_name[64];
	int node_id;
	int device_type;
	int sub_device_type;
	int type;
};
//yc�豸
class CYcRvuDevice : CRvuDevice
{

};
//yx�豸
class CYxRvuDevice : CRvuDevice
{

};
//yk�豸
class CYkRvuDevice : CRvuDevice
{

};
//yt�豸
class CYtRvuDevice : CRvuDevice
{

};

typedef struct _t_acs_station_ob_yc
{
	int id;//���к�
	char yc_code_sys[32];//ң���豸��ƽ̨�еı���
	int access_code_id;//������ob_access_dev�е�id
	int yc_type;
	char yc_name[64];//ң���豸����
	char yc_addr[32];//ң���豸�š��˿ں�
	float up_up_value;//������ֵ
	float up_value;//����ֵ
	float current_value;//��ǰֵ
	float low_value;//����ֵ
	float low_low_value;//������ֵ
	BYTE dev_online_state;//����״̬
}_T_ACS_STATION_OB_YC_;

typedef struct _t_acs_station_ob_yx
{
	int id;//���к�
	char yx_code_sys[32];//ң���豸��ƽ̨�еı���
	int access_code_id;//������ob_access_dev�е�id
	int yx_type;
	char yx_name[64];//ң���豸����
	char yx_addr[32];//ң���豸�š��˿ں�
	int normal_value;//����״ֵ̬
	int current_value;//��ǰֵ
	BYTE dev_online_state;//����״̬
}_T_ACS_STATION_OB_YX_;

typedef struct _t_acs_station_camera_preset
{
	int id;//���к�
	int camera_id;//�����ID��
	int preset_id;//Ԥ��λ��
	char preset_name[32];//Ԥ��λ����
}_T_ACS_STATION_CAMERA_PRESET_;

typedef struct _t_acs_station_ob_card
{
	int id;//���к�
	char code_door[32];//�ſ����Ž�ϵͳ�еı���
	char code_sys[32];//�ſ���ƽ̨�е�ͳһ����
	char user_name[32];//�ſ��û�������
	char personal_code[32];//�û�����
	char department[32];//�û���������
	int sex;//�Ա�
}_T_ACS_STATION_OB_CARD_;

typedef struct _t_device_list_node_info_ 
{
	int node_id;
	int parent_id;
	char device_code[32];
	char device_name[64];
	BYTE IsOnLine;
	BYTE IsAlarm;
	BYTE IsRelateCamera;
	int relate_camera_id;
	BYTE relate_preset_id;
}_T_DEVICE_LIST_NODE_INFO_;


typedef struct _t_acs_station_ct_user_
{
	int user_id;
	char user_name[64];
	char user_password[32];
	BYTE user_type;
	BYTE enablectrl_p;
	BYTE realtalk_p;
	BYTE eventlog_p;
	BYTE replay_p;
	BYTE alarm_p;
	BYTE tunecycle_p;
	BYTE usermanage_p;
	BYTE devicemanage_p;
	BYTE videorecord_p;
	BYTE elecmap_p;
}_T_ACS_STATION_CT_USER_;

typedef struct _t_acs_rvu_camera_info_
{
	int camera_id;
	int dvr_id;
	char camera_code[32];
	char camera_name[64];
	int channel_id;
	int station_id;
}_T_ACS_RVU_CAMERA_INFO_;

typedef struct _t_acs_rvu_dvr_info_
{
	int dvr_id;
	int station_id;
	char dvr_code[24];
	char dvr_name[64];
	char dvr_type[16];
	char dvr_ip[24];
	int dvr_port;
	char dvr_username[32];
	char dvr_password[32];
}_T_ACS_RVU_DVR_INFO_;

typedef struct _t_acs_rvu_station_info_
{
	int user_id;
	int station_id;
	char station_code[32];
	char station_name[64];
}_T_ACS_RVU_STATION_INFO_;

typedef struct _t_ass_rvu_device_info_
{
	int id;
	char rvu_ip[16];
	int  rvu_port;
	char rvu_loginname[32];
	char rvu_loginpassword[32];
	int sm_id;
	int node_id;
	char node_name[NAMELENGTH];
	char node_code[32];
	int device_type;
	int node_type;
	int rvu_id;
	int station_id;
	int sm_type;
	int sub_sys_id;
}_T_ASS_RVU_DEVICE_INFO_;

typedef struct _t_ass_rvu_info_
{
	int rvu_id;
	char rvu_name[64];
	char rvu_code[32];
	char rvu_ip[16];
	int  rvu_port;
	char rvu_username[32];
	char rvu_userpassword[32];
	int station_id;
	int commnet_handle;
	int lost_heatbeat;
	int node_type;
	char rvu_type[32];
	//int reconnect;
}_T_ASS_RVU_INFO_;

typedef struct _t_ass_device_ledger_
{
	int id;
	int station_id;
	char szStationName[32];
	char device_name[32];
	char device_manufacturer[32];
	char device_ip[32];
	int device_port;
	char login_username[32];
	char login_password[32];
	char protocol_type[32];
	char device_type[32];
	char harddisk_capacity[32];
	int analog_video_num;
	int net_video_num;
}_T_ASS_DEVICE_LEDGER_;

typedef struct _t_tree_node_info
{
	DWORD dwDataPtr;
	int node_type;
	int parent_id;

}_T_TREE_NODE_INFO;

typedef struct _t_ass_rvu_id_handle_
{
	int rvu_id;
	int comnet_handle;
}_T_ASS_RVU_ID_HANDLE;

//�û�����
typedef struct _t_user_
{
	int user_id;
	char szUserName[256];
}T_USER;

#define ID_DELETE_LINKAGE_RECORD 20200
//�豸�ṹ��
typedef struct _t_dev_info_
{
	int nDevId;
	char szDevName[64];
	int nStationId;
	char szStationName[32];
	int nRvuId;
	char szRuvName[32];
	char szRvuIP[32];
	int nRvuPort;
}_T_DEV_INFO_;

//rvu���ͽṹ��
typedef struct
{
	int nId;
	char szRvuType[32];
	char szDescription[128];
}T_ASS_RVU_TYPE;

typedef struct _t_linkage_config_info_
{
	int nId;
	int nDevId;//�豸id
	char szDevName[32];//�豸����
	int nRelateDevId;//�����豸id
	char szRelateCameraCode[32];//��������ͷ
	char szRelateDevName[32];//�����豸����
	int nRelateDevType;//�������ͣ�1���Ž���2������ͷ
	int nRelateDevAction;//����������1���򿪣�2���رգ�3��תԤ��λ
	int nPresetNum;//Ԥ��λ���
	char szPresetName[32];//Ԥ��λ����
	char szRelateCameraName[32];//��������ͷ����
}_T_LINK_CONFIG_INFO_;

typedef struct t_camera_info
{
	int nCameraId;
	char szCameraCode[32];
	char szCameraName[32];
}T_CAMERA_INFO;

typedef struct t_door_info
{
	int nDevId;
	char szDevName[32];
}T_DOOR_INFO;

#endif