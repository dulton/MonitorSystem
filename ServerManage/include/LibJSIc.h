#ifndef LIBJSIC_H
#define LIBJSIC_H

#define  NAMELENGTH   40
#define  PASSWORDLEN  20
#define  DES_LENGTH   160
#define  UNIT_LENGTH  8
#define  VER_LENGTH   40
#define  PHONE_LENGTH 20
#define  DATA_LENTH   60
#define  SDESC_LENGTH 80
#define  CARDLENGTH   20 

#define  DEV_SUM      50

typedef unsigned char BYTE;


/*ʱ��ṹ*/
typedef struct t_time
{
	short Years;//��
	char Month;//��
	char Day;//��
	char Hour;//ʱ
	char Minute;//��
	char Second;//��
	char Milsecond;//����
}T_TIME;
/*��ر�ŵĽṹ*/
typedef struct t_id
{
	short SmID;//���ģ����  dev��ID ��Ӧyx/yk/yc�� node_code_id
	short NodeID;//��ؽڵ��� yk/yx/yc�� ID
}T_ID;

/*��ؽڵ�����*/
typedef struct t_node
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
}T_NODE;

/*���ģ������*/
typedef struct t_sm
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

}T_SM;


//�澯�ṹ
typedef struct t_alarm
{
	long Type;//���ݵ�����
	T_ID t_ids;//���ݵ�ID
	T_TIME StartTime;//�澯����ʱ��
	T_TIME EndTime;//�澯����ʱ��
	T_TIME ConfirmTime;//�澯ȷ��ʱ��
	T_TIME CancelTime;//�澯ȡ��ʱ��
	long AlarmLevel;//�澯����
	float AlarmValue;//��ֵ
	long EnumAlarmTime;//��ǰ�澯�����ڷ������ǽ�����ȷ�ϻ�ȡ��
	char Description[DATA_LENTH];//�澯ֵ����

}T_ALARM;
typedef struct t_recode
{
	long size;//���ݽṹ�ĳ���
	T_ID ID;//����ͷ�ı��
	T_TIME StartTime;//��ʼʱ��
	T_TIME EndTime;//����ʱ��
	long LiveTime;//����ʱ��
	long RecordFlag;//¼��ԭ��
	long SevialNo;//¼���ļ���ˮ�ţ�Ψһ
	long VideoFormat;//¼��洢��ʽ
	long Reserver1;//����1
	long Reserver2;//����2
	long Reserver3;//����3
	char Reserver4[NAMELENGTH];//����4
}T_RECODE;

typedef struct t_Pro
{
	BYTE txPro[8];//ͨ�Ų�Э��
	BYTE hlPro[18];//����Э��
	BYTE yhPro[1452];//�û�����

}T_PRO;

typedef struct t_Data
{
	long type;//���ݵ�����
	T_ID id;//���ݱ�ʶID
	float t_value;//ֵ
	long enumstate;//״̬
	long size;//�����ص����ַ����������ʾ����ַ������ȣ����ʱ��������ΪTtime�Ľṹ��С�����ʱ���������Ϊ0�����治���κ�����
	char* desc;//����

}T_DATA;
//�����ṹ
typedef struct t_tactivelink
{
	long size;
	long aid;
	T_ID id;
	T_ID linkid;
	long linkmode;
	long ctrl;
	float value;
	float activevalue;
	float unactivevalue;
	long timelength;
	char name[NAMELENGTH];
	long reserver1;
	long reserver2;
	long reserver3;
	long reserver4;

}TACTIVELINK;
//Ԥ�����ýṹ
typedef struct t_presch
{
	long size;
	long PID;
	T_ID ID;
	long startoper;
	long endoper;
	long reserver1;
	long reserver2;
	long reserver3;

}TPRESCHEME;
//Ԥ��λ���ýṹ
typedef struct t_preset
{
	long size;
	t_id ID;
	char No;
	char name[NAMELENGTH];
	short reserver1;
	short reserver2;
	long reserver3;

}TPRESET;

typedef struct t_HlPro
{
	BYTE hlPro[1452];
}T_HLPRO;
//��½
typedef struct js_Login
{
	char username[NAMELENGTH];
	char password[PASSWORDLEN];
	long memberID;
	long enumlog;
	
}JS_LOGIN;
//��½
typedef struct js_ReLogin
{

	long MemberLevel;
	char Desc[DES_LENGTH];
	
}JS_RELOGIN;
typedef struct b_ReLogin
{
	BYTE MemberLevel[4];
	BYTE Desc[DES_LENGTH];
		
}B_RELOGIN;
//ϵͳ�ṹ
typedef struct js_Sys
{
	long cnt;
	struct t_id tids[DEV_SUM];
}JS_SYS;

typedef struct js_ReSysSM
{
	long cnt;
	struct t_sm tsms[DEV_SUM];
}JS_RESYS_SM;
typedef struct js_ReSysNODE
{
	long cnt;
	struct t_node tnodes[DEV_SUM];
}JS_RESYS_NODE;
//ʵʱ����
typedef struct js_Real
{
	long mode;//0:һ��һ�� 1���ı�ʱ�Զ����� 2����ʱ���� 3��ֹͣ����
	long pollingtime;//��ʱ��ʽʱ�ķ��ͼ������
	long cnt;
	struct t_id tids[DEV_SUM];
}JS_REAL;

typedef struct js_ReReal
{
	long result;//�趨�ɹ����ı�־ 0��ʾʧ��
	long cnt;//��������ֵ������
	struct t_Data tdatas[50];//��Ӧ��ֵ��״̬
}JS_REREAL;

typedef struct b_ReReal
{
	BYTE result[4];//�趨�ɹ����ı�־ 0��ʾʧ��
	BYTE cnt[4];//��������ֵ������
	BYTE values[1200];//��Ӧ��ֵ��״̬
}B_ReREAL;

//�澯
typedef struct js_Warning
{
	long cnt;
	struct t_alarm t_alarm[DEV_SUM];
//	T_ALARM t_alarm;
	
}JS_WARNING;
//�澯
typedef struct b_Warning
{
	BYTE cnt[4];
	BYTE values[1024];

}B_WARNING;
//ʱ��ͬ��
typedef struct js_Time
{
	T_TIME t_time;
}JS_TIME;
//ʱ��ͬ��
typedef struct js_ReTime
{
	long result;
	char desc[DES_LENGTH];
}JS_RETIME;
//ʱ��ͬ��
typedef struct b_ReTime
{
	BYTE result[2];
	BYTE desc[DES_LENGTH];
}B_RETIME;

//��������
typedef struct js_Control
{
	T_ID t_id;//�ڵ���
	T_DATA t_data;//����ֵ
}JS_CONTROL;

//��������ظ�
typedef struct js_ReCon
{
	long result;//�ɹ�/ʧ��
	char desc[DES_LENGTH];//����
}JS_RECON;

//��������ظ�
typedef struct b_ReCon
{
	BYTE result[4];
	BYTE desc[DES_LENGTH];
}B_RECON;


extern "C" void quyu(int n,int c,int *s,int *y);
extern "C" int RECV_TYPE(BYTE *t_buff,BYTE *buff,int lenth);
extern "C" void TxProtocol(T_PRO *t_pro,int pk_type,BYTE *yh_buff,int lenth);
extern "C" void HlProtocol(BYTE *hl_buff,int pk_type,int s_num,int lenth);
extern "C" void RVU_RECV_JsLogin(BYTE *l_byte,JS_RELOGIN *js_relogin);
extern "C" void RVU_SEND_JsLogin(JS_LOGIN js_login,BYTE *l_byte,int *lenth);
extern "C" void RVU_SEND_CONN(BYTE *l_byte);
extern "C" void RVU_RECV_JsSys_SM(BYTE *l_byte,JS_RESYS_SM *js_resys);
extern "C" void RVU_RECV_JsSys_NODE(BYTE *l_byte,JS_RESYS_NODE *js_resys);
extern "C" void RVU_SEND_JsSys(JS_SYS js_sys,BYTE *l_byte,int *lenth);
extern "C" void RVU_RECV_JsReal(BYTE *l_byte,JS_REREAL *js_rereal);
extern "C" void RVU_SEND_JsReal(JS_REAL js_real,BYTE *l_byte,int *lenth);
extern "C" void RVU_RECV_JsTime(BYTE *l_byte,JS_RETIME *js_retime);
extern "C" void RVU_SEND_JsTime(JS_TIME js_time,BYTE *l_byte,int *lenth);
extern "C" void RVU_RECV_JsWarn(BYTE *l_byte,JS_WARNING *js_warning);
extern "C" void RVU_SEND_JsControl(JS_CONTROL js_control,BYTE *l_byte,int *lenth);
extern "C" void RVU_RECV_JsControl(BYTE *l_byte,JS_RECON *js_recon);




#endif