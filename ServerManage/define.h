//CommonLib--����������
#define DEFAULT_SERVER_NUM 512
#define DEFAULT_CLIENT_NUM 1024
#define DEFAULT_SERVER_CLIENT_NUM 8
#define MAX_ONTHREAD_NUM 64 //�����߳�ͬʱ�����������

//CommonLib--���绺������С
#define DEFAULT_TCP_SERVER_RECV_BUF_SIZE (8*1024)
#define DEFAULT_TCP_SERVER_SOCKET_RECV_BUF_SIZE (64*1024)
#define DEFAULT_TCP_SERVER_SOCKET_SEND_BUF_SIZE (64*1024)

#define DEFAULT_TCP_CLIENT_RECV_BUF_SIZE (8*1024)
#define DEFAULT_TCP_CLIENT_SOCKET_RECV_BUF_SIZE (64*1024)
#define DEFAULT_TCP_CLIENT_SOCKET_SEND_BUF_SIZE (64*1024)

#define SOCKETSENDBUFMAXSIZE	1453
//���ݴ�С
#define MAX_RVU_NUM_PER_STATION 512
#define RECVBUFSIZE 512*1024
#define MAX_SQL_LENTH 1024*2
#define STR_SQL_LENTH 256

#define NAMELENGTH			40	//������������	40	40�ֽڳ�
#define PASSWORDLEN			20	//�����	20	20�ֽڳ�
#define DES_LENGTH			160 //������Ϣ����	160	160�ֽڳ�
#define UNIT_LENGTH			8   //���ݵ�λ�ĳ���	8	8�ֽڳ�
#define VER_LENGTH			40  //�汾�����ĳ���	40	40�ֽڳ�
#define PHONE_LENGTH		20  //�绰���볤��	20	20�ֽڳ�
#define DATA_LENGTH			60  //���ݳ���	60	60�ֽڳ�
#define SDESC_LENGTH		80  //����������	80	80�ֽڳ�
#define CARDLENGTH			20  //���ų���	20	20�ֽڳ�

#define MAX_FRAME_LEN   (1452+8)
#define USER_DATA_OFFSET  30
#define DATA_FRAME_HEADER  8
#define ETHERNET_FRAME_HEADER 14
#define SET_SM_ACK_DATA_OFFSET  30

#define MAX_SM_NUM_PER_STATION  128

#define MAX_STATION_NUM_PER_USER  1024
#define MAX_DVR_NUM_PER_USER      (MAX_STATION_NUM_PER_USER*16)
#define MAX_CAMERA_NUM_PER_USER   (MAX_DVR_NUM_PER_USER*16)

#define MAX_RVU_DEVICE_NUM_PER_STATION 1024

//Э�����Ͷ���
#define REQUEST_RVU_LOGIN                 101
#define RESPONSE_RVU_LOGIN                102
#define REQUEST_RVU_GET_SM                201
#define RESPONSE_RVU_SET_SM               202
#define REQUEST_RVU_GET_NODES             203
#define RESPONSE_RVU_SET_NODES            204
#define REQUEST_RVU_SET_DYN_ACCESS_MODE   301
#define RESPONSE_RVU_DYN_ACCESS_MODE_ACK  302

#define SEND_REALTIME_ALARM             401
#define HEART_BEAT                      601
#define HEART_BEAT_ACK                  602

#define REQUEST_RVU_SET_POINT            501
#define RESPONSE_RVU_SET_POINT_ACK       502


////////////////////////////////////////////////////

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
//XML������Ϣ����
#define ASS_REQUEST_LOGIN           1
#define ASS_REQUEST_STATION          2
#define ASS_KEEPALIVE                3
#define ASS_REQUEST_YK_CONTROL      4
#define ASS_REQUEST_ALARM           5
#define ASS_REQUEST_HIDE            6
#define ASS_REQUEST_TIME            7

/////////////////////////////////////////////////////
typedef struct _recv_packet
{
	char recvbuf[RECVBUFSIZE];
	int size;
	int handle;

}RECV_PACKET;

typedef struct _c_recv_packet
{
	char recvbuf[RECVBUFSIZE];
	int size;
	int handle;
	int Client_Num;
	
}C_RECV_PACKET;


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

/*���ģ������*/
typedef struct t_sm_
{
	long Size;//�����ݽṹ�ĳ���
	long Type;//���ݵ�����
	T_ID ID;//���ݱ�ʶID
	long MemberGropID;//�û�����
	long PortID;//�˿ں�
	short PortMode;//�˿�ģʽ
	short BaudRate;//������
	long Address;//��ַ
	float Longitude;//����
	float Latitude;//ά��
	char Name[NAMELENGTH];//����
	char Desc[SDESC_LENGTH];//����
	long DeviceType;//�豸����
	long DeviceSubType;//�豸������
	char Productor[NAMELENGTH];//������������
	char Version[VER_LENGTH];//�汾����
	long CameraChannel;//����ͷͨ����
	long RVUID;//RVU�ı��
	long Reserver1;
	char Reserver2[NAMELENGTH];
	
}T_SM_;

typedef struct t_sm_load
{
	int count;
	int rvuid;
	T_SM_ *t_sm;

}T_SM_LOAD;
/*��ؽڵ�����*/
typedef struct t_node_
{
	long Size;//����
	long Type;//���ݵ����� 1YC 2YX 3YK 4YT
	T_ID ID;//���ݱ�ʶ
	T_ID VirtuaID;//����
	char Name[NAMELENGTH];//���� 
	char Desc[SDESC_LENGTH];//����
	float MaxVal;//��Ч����
	float MinVal;//��Ч����
	long AlarmEnable;//�澯ʹ�ܱ��
	float HiLimit1;//һ���澯����
	float LoLimit1;//һ���澯����
	float HiLimit2;//�����澯����
	float LoLimit2;//�����澯����
	float HiLimit3;//�����澯����
	float LoLimit3;//�����澯����
	float Percision;//����
	long Saved;//�Ƿ񱣴�
	char Unit[UNIT_LENGTH];//��λ
	long PHYID;//��Ӧ������ڵ�
	long Reserver1;
	long Reserver2;
	long Reserver3;
	long Reserver4;
}T_NODE_;
typedef struct t_node_load
{
	int count;
	int rvuid;
	T_NODE_ *t_node;
	
}T_NODE_LOAD;

typedef struct _t_data_
{
	long type;//���ݵ�����
	T_ID id;//���ݱ�ʶID
	float t_value;//ֵ
	long enumstate;//״̬
	long size;//�����ص����ַ����������ʾ����ַ������ȣ����ʱ��������ΪTtime�Ľṹ��С�����ʱ���������Ϊ0�����治���κ�����
	char* desc;//����
	int changeflag;//���¸ı��־
	int alarmflag;//�澯�ı��־
	int updateflag;//�ϴ���־
	
}TDATA;

typedef struct t_Data_
{
	long type;//���ݵ�����
	T_ID id;//���ݱ�ʶID
	float t_value;//ֵ
	long enumstate;//״̬
	long size;//�����ص����ַ����������ʾ����ַ������ȣ����ʱ��������ΪTtime�Ľṹ��С�����ʱ���������Ϊ0�����治���κ�����
	char* desc;//����
	
}T_DATA_;
typedef struct t_data_load
{
	int count;
	int rvuid;
	T_DATA_ *t_data;
	
}T_data_LOAD;

typedef struct _t_ass_rvu_info_
{
	int rvu_id;
	int station_id;
	char rvu_code[32];
	char rvu_name[32];
	char rvu_ip[16];
	int  rvu_port;
	char rvu_username[41];
	char rvu_password[21];	
	int commnet_handle;
	int lost_heatbeat;
	int login_flag;
	char rvu_type[32];
	//int reconnect;
}_T_ASS_RVU_INFO_;

typedef struct _t_ass_rvu_data_
{
	int rvu_id;
	int station_id;
	int count;
	TDATA t_datas[MAX_SM_NUM_PER_STATION*10];
	int uploadflag;//1��ʾδ�ϴ� 0��ʾ���ϴ�

}T_RVU_DATA;

typedef struct _t_sql_info_
{
	int ID;
	int num;

}_T_SQL_INFO;

typedef struct _t_send_rvu_info_
{
	char rvu_code[32];
	char rvu_ip[16];
	int  rvu_port;
	int rvu_handle;
	char send_buff[RECVBUFSIZE];
	int send_size;
}SEND_RVU_INFO;

typedef struct _t_rvu_node_info_
{
	int rvu_handle;
	int rvu_id;
	char rvu_ip[16];
	int rvu_port;
	TID tids[MAX_SM_NUM_PER_STATION];
	int count;
}RVU_NODE_INFO;


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
	int changeflag;//���±����ʾ
}TALARM;

typedef struct t_talarm_
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
}T_ALARM_;

typedef struct _t_ass_rvu_alarm_
{
	int rvu_id;
	int station_id;
	int count;
	TALARM t_alarms[MAX_SM_NUM_PER_STATION];
	int uploadflag;//1��ʾδ�ϴ� 0��ʾ���ϴ�
	
}T_RVU_ALARM;

typedef struct t_alarm_load
{
	int count;
	int rvuid;
	T_ALARM_ *t_alarm;
	
}T_ALARM_LOAD;
// 

typedef struct DBConfigParam 
{
	char LocalIP[16];
	int  LocalPort;
	char DBServerIP[16];
	int  DBServerPort;
	char DBName[32];
	char DBUserName[32];
	char DBUserPassword[32];
}DBConfigParam;

typedef struct _t_ass_login_user_info_
{
	char rvu_username[41];
	char rvu_password[21];
}_T_ASS_LOGIN_USER_INFO_;

typedef struct _t_ass_station_info_
{
	int user_id;
	int station_id;
}_T_ASS_STATION_INFO_;

typedef struct _t_ass_alarm_set_
{
	int user_id;
	int station_id[MAX_RVU_DEVICE_NUM_PER_STATION];
	int num;
	int type;//0ɾ�� 1����
}_T_ASS_ALARM_SET_;

typedef struct _t_ass_hide_set_
{
	int user_id;
	int devID[MAX_RVU_DEVICE_NUM_PER_STATION];
	int num;
	int hide;//0ɾ�� 1����
}_T_ASS_HIDE_SET_;

typedef struct _t_ass_control_
{
	int rvuid;
	int smid;
	int nodeid;	
	int value;
	int type;
}_T_ASS_CONTROL_;

typedef struct _t_ct_user
{
	int userid;
	int handle;
	int stationID;
	int AlarmStation[MAX_RVU_DEVICE_NUM_PER_STATION];
	int alarmstationNum;
	int devID[MAX_RVU_DEVICE_NUM_PER_STATION];
	int devidNum;
	int login_flag;//��½��ʶ 1����½ 2��δ��½

}_C_LOGIN_USER;

typedef struct _t_dev_id
{
	int devID;
	int rvuid;
	int SmID;
	int NodeID;
	int enumtype;
}_T_DEV_ID;

typedef struct _t_104_yx1
{
	int addressID;
	int status;
}_T_104_YX1;

typedef struct _t_104_yx2
{
	int addressID;
	int status;
	char s_time[10];
}_T_104_YX2;



typedef struct _t_104_yx1e
{
	int addressID;
	int status;
	char cp_time[21];
}_T_104_YX1E;

typedef struct _t_104_buff
{
	BYTE head[1];//��ͷ
	BYTE bufflen[2];//���ĳ���
	BYTE sendflag[1];//���ͱ�־
	BYTE funcode[2];//������
	BYTE datalen[2];//���ݳ���
	BYTE data[32];//������
	BYTE end[1];//������־
}_T_104_BUFF;

typedef struct _t_104_SM
{
	BYTE smid[2];//�豸���
	BYTE nodeid[2];//�ڵ���
	BYTE dev_type[4];//�豸����
	char node_type[32];//�ڵ����� YC YX YK YT
	char devname[64];//�豸����
	char nodename[64];//�ڵ�����
}T_104_SM;

typedef struct _t_104_real
{
	BYTE smid[2];//�豸���
	BYTE nodeid[2];//�ڵ���
	char t_value[32];//�ڵ��ֵ

}T_104_REAL;

typedef struct t_104_sm_load
{
	int count;
	int rvuid;
	T_104_SM t_sm[MAX_SM_NUM_PER_STATION*3];
	
}T_104_SM_LOAD;

typedef struct _c_link
{
	char c_code[20];
	int c_pset;
}C_LINK;

typedef struct _c_linkinfo
{
	int linknum;
	C_LINK c_link[6];
}C_LINKINFO;

typedef struct _c_camerainfo
{
	char ip[32];
	int port;
	char username[16];
	char password[16];
	char dvrtype[16];
	int channel;
}C_CAMERAINFO;

typedef struct _t_linkpush
{
	int handle;
	int devid;
	C_LINKINFO c_linkinfo;
}T_LINKPUSH;


