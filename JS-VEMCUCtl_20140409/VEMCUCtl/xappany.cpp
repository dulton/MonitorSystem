#include "stdafx.h"
#include "xappany.h"
#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// ȫ�ֱ����ͺ�������

//---------------------------------------------------------------------------

char			 g_DBServerIP[IPADDRESS_LEN] = {0}; //���ݿ�������ĵ�ַ
char          g_HttpServerIP[IPADDRESS_LEN] = {0};//Http��������ַ
char          g_LinkServerIP[IPADDRESS_LEN] = {0};//������������ַ
int             g_nDBServerPort = 0;                        //���ݿ�������˿�
int             g_nHttpServerPort = 0;                      //Http�������˿�
int             g_nLinkServerPort = 0;                       //�����������˿�
MYSQL		*g_mySqlData = NULL;					   //mysql���ݿ����
bool          app_IsUserLogin = false;
char          g_DBName[256] = {0};
char g_AcsServerIp[IPADDRESS_LEN] = {0}; //����ϵͳ�������ĵ�ַ
int	 g_nAcsServerPort = 0;	//����ϵͳ����Ķ˿�
int  g_nShowManagerClient = 0;//�Ƿ���ʾ����ͻ���

//�û������Խ�
int		g_ua_realtalk_callid;
int		g_ua_realtalk_direction;
int		g_ua_realtalk_state;

//��½�û�Ȩ��
PUPR	g_userpower;
int     g_nUserType = 0;//1:��ʾadmin�û�,2:��ʾʡ���û�,3��ʾʡ���û�
int     g_nUserResourceShowType = 0;//1:��ʾ��ʡ����ʽ��ʾ,2:��ʾ��ʡ�����ṹ��ʾ,3:��ʾ��ʡ����ѹ�ȼ���ʾ

//�˹�Ѳ����Ϣ
_T_VIDEOPAGEVIEWINFO g_VideoPageViewInfo;

//ϵͳ��Ϣ�ṹ��
_T_SYSTEM_INFO	g_SystemInfo[TOTALSYSNUM];
int		g_TotalSysNum = 0;

// ��ǰȫ�����������豸��Ϣ�б�
_T_ALARMINFOLIST g_AlarmInfoList[TOTALALARMDEVICENUM];
int		g_TotalAlarmInfoListNum = 0;

// ��Ѳ����
_T_TUNECYCLE_METHODINFO	g_TuneCycle_MehtodInfo;

// ���վ��һ���Ľڵ���Ϣ
_T_STATION_NODE_INFO	g_tStationNode_Info[MAX_STATION_NODE_NUM];
int						g_nStationNode_Num = 0;

// ���б��վ����Ϣ
_T_STATION_INFO		g_tStation_Info[MAX_STATION_NUM];
int					g_nStation_Num = 0;

// ���׹̶�ͷ
BYTE    pDSPHeader[19] = {0X00,0X00,01,0XC6,0X4D ,0X50 ,0X47, 0X34, 0x01, 0x00 ,0X19 ,0X20 ,0XA1 ,0x07 ,0x00 ,0X60 ,0x01, 0X20, 0x01};	

void	*pDecHandle;						//�������
void	*pEncodeHandle;

VEM_USER_CONFIG_INFO g_user_config_info;//�û�������Ϣ
_T_PRESET_SETTING	g_preset_setting[1000];
int					g_total_preset_setting;
