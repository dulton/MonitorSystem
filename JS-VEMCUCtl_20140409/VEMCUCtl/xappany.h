#ifndef _xappany_H_
#define _xappany_H_

#ifndef   __STACK_H__   
#define   __STACK_H__

#include ".\include\mysql\mysql.h"				//�������ݿ�ͷ�ļ�

//------------------------------------------------------------------------//
//Ԥ����
//------------------------------------------------------------------------//

#define HIKVISION				110
#define DAHUA					111
#define HENGYI					112
#define HANBANG					113
#define LANSEZHIXING			114
#define DLINK					115
#define DALI					116
#define AXIS					117
#define SONY					118
//#define NANZI					119
#define PANASONIC				120
#define AMS						121
#define GRANDSTREAM				122
#define MOBOTIX					124
#define NANZI					125
#define XIANJINYUAN				161		//������Դ

#define	IPADDRESS_LEN			   16		//IP��ַ�ĳ���

#define	CAMERANAMELEN			256		//����ͷ���Ƴ���
#define	CAMERACALLNUMLEN		32			//����ͷ���к��볤��
#define	DVRNUMLEN				        64		//DVR���볤��
#define DVRIPLEN				            32		//DVR IP����
#define	DVRUSERNAMELEN			256		//DVR�û�������
#define	DVRPASSWORDLEN			64			//DVR���볤��

#define	TOTALCAMERANUM			10000	//���֧�ֵ�����ͷ��Ŀ
#define TOTALDVRNUM				2000		//���֧�ֵ�DVR��Ŀ

#define    MAXNODENUM				1024*32

#define    CHANNEL					        1			//�����Խ�g711��������
#define    BITS_PER_SAMPLE			    16			//�����Խ�g711��������
#define    SAMPLES_PER_SECOND    8000		//�����Խ�g711��������
#define	    BITRATE					        16000	//�����Խ�g711��������

#define R_DATE_LEN 				        20			//¼��ָ���е�ʱ�䳤��
#define R_USERNAME_LEN			32			//¼��ָ���е�DVR�û�������
#define R_PASSWORD_LEN 			50			//¼��ָ���е�DVR���볤��

#define DISPACKETBUF			1024*1024	 //���յ������ݰ������Ĵ�С

#define MAXVIEWCH			 9					    //�໭���еĻ���ͨ������
#define MAPVIEWCHA			25						//���ӵ�ͼ��ͨ����A
#define MAPVIEWCHB			30						//���ӵ�ͼ��ͨ����B
#define MAPVIEWCHC			31						//���ӵ�ͼ��ͨ����C
#define MAPVIEWCHD			32						//���ӵ�ͼ��ͨ����D
#define TEMPFAVORITECHA		26				    //��ʱ�ղؼ�ͨ��A
#define TEMPFAVORITECHB		27				    //��ʱ�ղؼ�ͨ��B
#define TEMPFAVORITECHC		28				    //��ʱ�ղؼ�ͨ��C
#define TEMPFAVORITECHD		29	                //��ʱ�ղؼ�ͨ��D
#define REALTALKCHREMOTE	33				    //�����Խ�Զ����Ƶ�˿�
#define REALTALKCHLOCAL		34				    //�����Խ�������Ƶ�˿�
#define REPLAYCH			            35					//�ط���Ƶ�˿�

//////////////////////////////////////////////////////////////////////////
#define	OM_CHANNLECHANGE	OM_MESSAGE				//��Ƶͨ���л�ͨ����Ϣ����
#define   OM_MESSAGE			WM_USER + 200
#define	OM_DBLCHANNEL		 OM_MESSAGE + 1			//��Ƶͨ��˫����Ϣ����
#define	OM_RIGHTCLICKCHANNEL		 OM_MESSAGE + 2			//��Ƶͨ���Ҽ���Ϣ����
#define	OM_CONTROLBUTTON	 OM_MESSAGE + 3		//������֮��İ�ť��Ϣ
#define	OM_YTCONTROL		 OM_MESSAGE + 9			//��̨���ư�ť��Ϣ

/////////////////////////////////////������֮���ͨ��////////////////////////////////
#define OM_ELECTREE_TO_CAMERAANDCONTROL_STATIONID (OM_MESSAGE + 10)//���ӵ�ͼ������Ƶ���ƴ��ڴ����վID

//////////////////////////////////////////////////////////////////////////
#define    WM_MAGIC_VEMCUCTL   9669
#define    WM_SELECT_DEVICE_NOTIFY  (WM_USER+666) //ѡ���豸

//////////////////////////////////////////////////////////////////////////
#define    WM_VIDEO_LINKAGE_MANUAL_MESSAGE  (WM_USER+700) //�ֶ�������Ϣ
#define    WM_VIDEO_LINKAGE_ALARM_MESSAGE     (WM_USER+701)  //�澯������Ϣ
#define    WM_VIDEO_LINKAGE_STATE_MESSAGE       (WM_USER+702)  //״̬��λ��Ϣ
#define    WM_VIDEO_CAMERA_CONTROL_NOTIFY_MESSAGE  (WM_USER+703)  //����ͷ�ƾ�����֪ͨ��Ϣ
#define    WM_VIDEO_WEATHER_WARNING_LINKAGE_MESSAGE  (WM_USER+704) //����澯������Ϣ
#define    WM_VIDEO_WEATHER_FORECAST_LINKAGE_MESSAGE  (WM_USER+705) //����Ԥ��������Ϣ

//////////////////////////////////////////////////////////////////////////
#define WM_SYSTEM_TRAY_ICON_NOTIFY  (WM_USER+766) //ϵͳ������Ϣ

//////////////////////////////////////////////////////////////////////////
#define  WM_DEVICE_VIDEO_CLOSE_MESSAGE (WM_USER+810)                              //��Ƶ�ر���Ϣ
#define  WM_DEVICE_VIDEO_ERROR_REASON_NOTIFY_MESSAGE (WM_USER+811) //��Ƶ����ԭ��֪ͨ��Ϣ
#define  WM_DEVICE_VIDEO_TALK_NOTIFY_MESSAGE (WM_USER+812)                   //��Ƶ��֪ͨ��Ϣ
#define  WM_DEVICE_VIDEO_QUICK_RESTART_MESSAGE (WM_USER+816)               //��Ƶ����������Ϣ
#define  WM_DEVICE_VIDEO_STATUS_ONLINE_NOTIFY_MESSAGE  (WM_USER+817)  //��Ƶ״̬����֪ͨ��Ϣ

//////////////////////////////////////////////////////////////////////////
#define  WM_UPDATE_USER_VIEW_CAMERA_STATUS_MESSAGE  (WM_USER+1019) //��������ͷ״̬��Ϣ
#define  WM_ELECMAP_OPEN_CAMERA_MESSAGE (WM_USER+1020)	//���ӵ�ͼ������ͷ��Ϣ

//////////////////////////////////////////////////////////////////////////
#define  WM_DEVICE_VIDEO_TALK_OPERATE_RESULT_FAIL  11
#define  WM_DEVICE_VIDEO_TALK_OPERATE_RESULT_SUCCESS  12
#define  WM_DEVICE_VIDEO_OPERATE_RESULT_NOTAG_OFFLINE_VIDEO 13
#define  WM_DEVICE_VIDEO_OPERATE_RESULT_NOTAG_ONLINE_VIDEO 14
#define  WM_DEVICE_VIDEO_OPERATE_RESULT_TAG_ONLINE_VIDEO 15
#define  WM_DEVICE_VIDEO_OPERATE_RESULT_TAG_OFFLINE_VIDEO 16


//�Զ�����Ϣ_��ʼ��USB����ͷ
#define WM_INIT_USB_VIDEO (WM_USER+2555)
//�Զ�����Ϣ_�ر�USB����ͷ
#define WM_EXIT_USB_VIDEO (WM_USER+2556)
//�Զ�����Ϣ_�յ�������Ϣ
#define WM_RECEIVED_ALARMINFO (WM_USER+2656)
//�Զ�����Ϣ_�����ĳɹ�
#define WM_SUB_OK (WM_USER+2657)
//�Զ�����Ϣ_������ʧ��
#define WM_SUB_FAIL (WM_USER+2658)

#define   PAGEVIEWHEIGHT 40                     //�ֶ���Ѳ�����߶�
#define   LINKAGEWIDTH     268                   //�������
#define	  CONTROLWIDTH	278				    //��̨�������Ŀ��
#define	  TITLEHIGHT			    0					//�������ĸ߶�
#define   MENUHIGHT			147					//�˵����ĸ߶�
#define   ACCEHIGHT			    0					//�²����ĸ߶�
#define   ALARMHIGHT			200						//�������ĸ߶�
#define   SHOWALARMHIGHT			10						//��ʾ�������Ǹ���ť�ĸ߶�

#define   CYCLENUM			32						    //������Ѳ������Ŀ
#define   VIEWCHANNELMETHOD	6				//��Ѳ�еĶ໭�淽�����Ϊ6

#define	TIMER_MAIN_EVENTID	1						//���Ի������ʱ��ID
#define	TIMER_CYCLE_EVENTID	2				    //���Ի������Ѳʱ��ID
#define TIMER_WEATHER_EVENTID  3              //����ˢ��ʱ��ID  
#define TIMER_YT_LOCK_CHECK_EVENTID 4    //�����̨����ʱ��ID
#define TIMER_VIDEO_FLOW_EVENTID      5     //�������
#define TIMER_SUBSCRIBE_CAMERA_STATUS_EVENTID      6    //��������ͷ״̬
#define TIMER_CHECK_AND_UPDATE_SYSTEM_SOFTWARE_EVENTID     7    //��Ⲣ�Զ�����ϵͳ
#define TIMER_VIDEO_PAGEVIEW_AUTOINFO 8          //�˹��Զ�Ѳ��ʱ��ID

#define TIMER_VIDEO_ERROR_REASON_VIDEO_CHANNEL_0_TIMER  1200		//���Ի������Ƶ����ԭ����Ƶͨ��0
#define TIMER_WEATHER_CHANNEL_0_TIMER  1300       //��Ƶͨ��0ʵʱ����ʱ��ID  
#define TIMER_MICRO_WEATHER_CHANNEL_0_TIMER  1400       //��Ƶͨ��0΢����ʱ��ID  
#define TIMER_HISTORY_WEATHER_CHANNEL_0_TIMER 1500      //��Ƶͨ��0��ʷ����ʱ��ID 
#define TIMER_VIDEO_INFO_SHOW_CHANNEL_0_TIMER 1600      //��Ƶͨ��0��Ƶ��Ϣ��ʾʱ��ID 
#define TIMER_ACSSYSTEM_LOAD_DLL 1700	//����dll��Ķ�ʱ��

#define		TOTALSYSNUM		10						             //֧�ֵ����ϵͳ��
#define		TOTALALARMDEVICENUM		1				//֧�ֵ���󱨾��豸��

// D5000ϵͳ���ı��վ�ڵ���
#define	  MAX_STATION_NODE_NUM		(2*1024)
#define   MAX_STATION_NUM				    (4*1024)

enum
{	
	    REPLAY_NORMALSPEED	= 0,
		REPLAY_2HIGHSPEED,
		REPLAY_4HIGHSPEED,
		REPLAY_8HIGHSPEED,
		REPLAY_2LOWSPEED,
		REPLAY_4LOWSPEED,
		REPLAY_8LOWSPEED
};

enum
{
		REPLAY_PLAY = 0,
		REPLAY_STOP = 1,
		REPLAY_PAUSE = 2
};

enum
{
		SLDVR_CALLEE = 0,		//����dvr
		SLPHONE_CALLEE = 1,	//��������
		EYEBEAM_CALLEE = 2,	//eyebeam
		RTSIP_CALLEE = 3,		    //rtsip�ͻ���
};

enum AMC_POPUPS
{
	/// AMC will not show any Popups.
	AMC_POPUPS_NONE		      =	0L,

	/// AMC will show a Login Dialog if the username or password is incorrect.
	AMC_POPUPS_LOGIN_DIALOG	=	1L,

	/// All messages are shown as Popups.
	AMC_POPUPS_MESSAGES			=	2L,

	/// "No Video" overlay is shown when the stream is stopped.
	AMC_POPUPS_NO_VIDEO  = 4L,

	/// Untrusted certificates will be rejected without prompting the user.
	AMC_POPUPS_SUPPRESS_UNTRUSTED_CERTIFICATE_ALERT  = 8L,
};

enum AMC_STATUS
{
	/// AMC is uninitialized
	AMC_STATUS_NONE                           = 0L,

	/// AMC is initialized and ready.
	AMC_STATUS_INITIALIZED                    = 1L,

	/// A media stream/file is playing.
	AMC_STATUS_PLAYING                        = 2L,

	/// Playing of a media stream/file is paused.
	AMC_STATUS_PAUSED                         = 4L,

	/// A media stream/file is being recorded.
	AMC_STATUS_RECORDING                      = 8L,

	/// AMC is opening a media stream/file.
	AMC_STATUS_OPENING                       = 16L,

	/// AMC is performing reconnection.
	AMC_STATUS_RECONNECTING                  = 32L,

	/// Issuing a Pan, Tilt, Zoom command to the device.
	AMC_STATUS_ISSUING_PTZ_COMMAND          = 512L,

	/// An extended text/message is displayed in the status bar.
	AMC_STATUS_EXTENDED_TEXT               = 1024L,

	/// UIMode is set to ptz-absolute.
	AMC_STATUS_PTZ_UIMODE_ABS              = 2048L,

	/// UIMode is set to ptz-relative or ptz-relative-no-cross.
	AMC_STATUS_PTZ_UIMODE_REL              = 4096L,

	/// The stream for receiveing audio is being opened.
	AMC_STATUS_OPENING_RECEIVE_AUDIO      = 65536L,

	/// AMC is opening the stream for transmitting audio.
	AMC_STATUS_OPENING_TRANSMIT_AUDIO    = 131072L,

	/// Receiving audio.
	AMC_STATUS_RECEIVE_AUDIO             = 262144L,

	/// Transmitting audio.
	AMC_STATUS_TRANSMIT_AUDIO            = 524288L,

	/// An audio file is being transmitted.
	AMC_STATUS_TRANSMIT_AUDIO_FILE      = 1048576L,

	/// Recording audio.
	AMC_STATUS_RECORDING_AUDIO          = 2097152L
};

enum AMC_VIDEO_RENDERER
{
	/// Video Mixing Renderer 7
	AMC_VIDEO_RENDERER_VMR7          = 0x00000,

	/// Video Mixing Renderer 9
	AMC_VIDEO_RENDERER_VMR9          = 0x01000,

	/// Enhanced Video Renderer
	AMC_VIDEO_RENDERER_EVR           = 0x10000
};

/// Option flags for StartRecordMedia
enum AMC_RECORD_FLAG
{
	AMC_RECORD_FLAG_NONE              = 0,

	// Record received audio samples
	AMC_RECORD_FLAG_RECEIVED_AUDIO    = 1,

	// Record transmitted audio samples
	AMC_RECORD_FLAG_TRANSMITTED_AUDIO = 2,

	// If set, audio should be saved in its encoded form. Otherwise in wav(pcm)-format.
	AMC_RECORD_FLAG_ENCODED_AUDIO     = 4,

	// Record video only
	AMC_RECORD_FLAG_VIDEO 			      = 8,

	// Record both video and audio
	AMC_RECORD_FLAG_AUDIO_VIDEO       = 16
};
//------------------------------------------------------------------------//
//�ṹ�嶨��
//------------------------------------------------------------------------//
//�û��豸����Ȩ��
typedef	struct	_t_UserDevicePower
{
	int	view;
	int	ytcontrol;
	int	preset;
	int	viewsetting;
	int	record;
	int	capture;
}PUDPR,*PPUDPR;

//�û�����Ȩ��
typedef	struct	_t_UserControlPower
{
	int	videoview;
	int	ytcontrol;
	int	replay;
	int	historylog;
	int	devicemanage;
	int    tunecycle;
	int    usermanage;
	int    eventlevel;
}PUCPR,*PPUCPR;

//�û��ܵ�Ȩ��
typedef struct _t_UserTotalPower
{
	int	userID;
	char	username[32];
	char	password[32];
	int    logintype;
	int    usertype;
	int    groupno;
	int    subgroupno;
	char   groupname[64];
	int    userlevel;
	PUCPR	userCP;
}PUPR,*PPUPR;

//DVR��Ϣ�ṹ��
typedef struct _T_DVR_INFO
{
	int       dvr_id;                     //DVR���
	int       dvr_type;                 //DVR����
	char	   dvr_name[64];         //DVR����
	char	   dvr_num[32];           //DVR����
	char	   dvr_ip[32];                //DVR��IP��ַ
	int       dvr_port;                  //DVR��PORT�˿�
	char    dvr_user[64];            //DVR���û���
	char	   dvr_password[64];   //DVR������
	int       station_id;                //վ�����
	char    station_num[32];     //վ�����
	char    station_name[64];   //վ������
}_t_dvr_info;

typedef struct _T_DIAGNOSIS_INFO
{
	int nTotalResult;//�Ƿ��й���
	int nLoginErr;//��¼ʧ��   
	int nOpenVideoErr;//����Ƶʧ��
	int nRecordErr;//¼��ʧ��
	int nLose;//��Ƶ��ʧ
	int nImpluse;//���
	int nStripe;//���Ƹ���
	int nBright;//�����쳣
	int nVague;//��Ƶģ��
	int nColor;//��Ƶƫɫ
	int nPTZ;//��̨ʧ��
	int nShake;//����
}_t_diagnosis_info;

//����ͷ��Ϣ�ṹ��
typedef struct _T_CAMERA_INFO
{
	int camera_flag;
	int channel;
	char camera_name[64];
	char camera_num[32];
	//_T_DIAGNOSIS_INFO diagnosis_info;
	_T_DVR_INFO dvr_info;
}_t_camera_info;

// �ڵ���Ϣ������ڵ�
typedef struct node_info
{
	int    node_type;		//0��ʾϵͳ��1��ʾ�ڵ㣬2��ʾվ�㣬3��ʾcamera��4��ʾIO�豸
	char node_num[20];
	char node_name[64];
	int    node_id;
	int    node_status;				        // �ڵ��״̬��0��ʾ�����ã�1��ʾ���ã�2��ʾ�ֶ���עΪ������
	int    node_streamless;              //�ڵ�����,0��ʾ������,1��ʾû������
	float node_longitude;
	float node_latitude;
	int	node_decodetag;				//�ڵ�Ľ����ǩ
	char node_station[64];			    //�ڵ�����վ���վ������
	char node_stationnum[20];		//�ڵ�����վ���վ�����
	_T_CAMERA_INFO camera_info;   //CAMERA��Ϣ
}_T_NODE_INFO, *_PT_NODE_INFO;

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

typedef struct
{
	char szStationName[64];
	int nDoorCount;
	int nAnFangCount;
	int nFireCount;
}_T_ASS_SUBSYSTEM_ALARM_COUNT;

// Ԥ��λ�ڵ���Ϣ
typedef struct node_preset_info
{
	int		node_type;			    // 0��ʾϵͳ��1��ʾ�ڵ㣬2��ʾվ�㣬3��ʾcamera��4��ʾIO�豸��5��ʾԤ��λ��6��ʾ�����飬7��ʾ�豸��
	char	    node_num[20];		// ��ʾվ������������ͷ����
	char	    node_name[64];		// ��ʾվ�����ƻ�������ͷ����
	int		node_id;			        // ��ʾվ�������ͷ�����ݱ��е�id��
	char	    preset_name[64];	// ��ʾԤ��λ������
	int		preset_id;			    // ��ʾԤ��λ�ĺ���
	int		node_status;		    // �ڵ��״̬��0��ʾ�����ã�1��ʾ���ã�2��ʾ�ֶ���עΪ������
	int        node_streamless;  // �ڵ�����,0��ʾ������,1��ʾû������
	float	    node_longitude;	    // ��ʾ����ͷ������
	float	    node_latitude;		    // ��ʾ����ͷ������
	int		node_decodetag;   // ����ͷ�Ľ����ǩ
	char	    node_station[64];    // �ڵ�����վ���վ������
	char  	node_stationnum[20];// �ڵ�����վ���վ�����
	int       line1_from_x;
	int       line1_from_y;
	int       line1_to_x;
	int       line1_to_y;
	int       line2_from_x;
	int       line2_from_y;
	int       line2_to_x;
	int       line2_to_y;
	_T_CAMERA_INFO  camera_info;  //CAMERA��Ϣ
}_T_NODE_PRESET_INFO, *_PT_NODE_PRESET_INFO;

// ��Ѳ�ڵ���Ϣ
typedef struct _tunecycle_node_info_
{
	int    node_type;		                 //0��ʾϵͳ��1��ʾ������2��ʾcamera
	char node_num[20];                   //�ڵ��
	char node_name[64];                 //�ڵ�����
	int    node_status;				         // �ڵ��״̬��0��ʾ�����ã�1��ʾ����
	int    node_streamless;               //�ڵ�����,0��ʾ��������1��ʾû������
	float node_longitude;
	float node_latitude;
	int	 node_decodetag;				//�ڵ�Ľ����ǩ
	char  node_station[64];			    //�ڵ�����վ���վ������
	char  node_stationnum[20];		//�ڵ�����վ���վ�����
	int     nTime;                              //��Ѳʱ��
	int     nCycleNum;                     //��Ѳ��
	_T_CAMERA_INFO  camera_info;  //CAMERA��Ϣ
}_T_TUNECYCLE_NODE_INFO, *_PT_TUNECYCLE_NODE_INFO;

// ���վ�ڵ���Ϣ
typedef struct _t_station_node_info
{
	int		node_id;		//�ڵ�ID��
	int		parent_id;		//���ڵ�ID��
	char	    node_name[64];	//�ڵ�����
	int		order_num;		//�������
	int        ywb_id;           //ʡ��
	int        login_type;      //��¼����
	int        voltage_class; //��ѹ�ȼ�
	char	    notes[64];		//��ע
}_T_STATION_NODE_INFO, *_PT_STATION_NODE_INFO;

// ���վ��Ϣ
typedef struct _t_station_info
{
	int	station_id;		//վ��ID��
	char	station_name_videoplant[64];	//վ������Ƶƽ̨�е�����
	char	station_code_videoplant[20];     //վ������Ƶƽ̨�еĺ���
	char	station_name_d5000[64];           //վ����D5000�е�����
	char	station_code_d5000[20];             //վ����D5000�еĺ���
	char	station_name_oms[64];              //վ����OMS�е�����
	char	station_code_oms[20];               //վ����OMS�еĺ���
	char	station_name_meteo_a[64];       
	char	station_code_meteo_a[20];
	char station_code_weather[64];        //վ���������еĺ���
	char station_code_typhoon[64];        //վ����̨���еĺ���
	char station_code_microclimate[64];//վ����΢�����еĺ���
	int    station_video_status;
	int    voltage_class;                              //��ѹ�ȼ�
	int	node_id;                                       //ʡ��
	int		   node_sd_yw_id;		//ʡ��
	int    node_yw_id;                                //ʡ��
	char notes[256];                                 //��ע
}_T_STATION_INFO, *_PT_STATION_INFO;

// ϵͳ��Ϣ�ṹ�嶨��
typedef struct T_SYSTEM_INFO
{
	char	sysid[20];		//ϵͳ��
	char	sysname[64];	//ϵͳ����
	char	cms_ip[20];		//cms��ip��ַ
	int	cms_port;		//cms�Ķ˿�
	char	http_ip[20];	//http��ip��ַ
	int	http_port;		//http�Ķ˿�
	int	sys_status;		//ϵͳ��״̬
	char	upsysid[20];	//�ϼ�ϵͳ��
	int	localdomain;	//�Ƿ��Ǳ���ϵͳ��1����ʾ����ϵͳ��2����ʾ�ϼ�ϵͳ��0��ʾ�¼�ϵͳ
}_T_SYSTEM_INFO, *_PT_SYSTEM_INFO;

typedef struct _t_Replay_Query_Info
{
	bool	   system_uporlow;			//��ѯ����ϵͳ�����¼�ϵͳ��0��ʾ������1��ʾ�¼�
	int		query_type;				//��ѯ���ͣ�0��ʾ������Ƶͨ����ʱ�䷶Χ��ѯ��1��ʾ���ڸ澯�¼���ѯ
	char	    choose_address[32];		//ѡ�����豸��ַ����
	int		alarm_type;				//�澯����ѡ��choose_addressΪ��Ƶͨ��ʱ��0x0��ʾ��Ƶ��ʧ�澯��0x1��ʾ�ƶ����澯��0x2��ʾ��Ƶ�ڵ��澯
									//				choose_addressΪ�����豸ʱ��0x80��ʾ�豸���¸澯��0x81��ʾ���¸澯��0x82��ʾ���ȹ��ϸ澯��0x83��ʾ���̹��ϸ澯
									//				0xff��ʾ���и澯
	char	start_time[22];			//��ʼʱ��2005-11-10T12:05:10
	char	stop_time[22];			//����ʱ��2005-11-10T12:05:10
}_T_REPLAY_QUERY_INFO, *_PT_REPLAY_QUERY_INFO;

typedef struct _t_VideoPageViewInfo
{
	int nTimeSpan;
	int nStatus;
	char szStationName[256];
	char szFirstStationName[256];
}_T_VIDEOPAGEVIEWINFO,*_PT_VIDEOPAGEVIEWINFO;

typedef struct _t_TuneCycle_MethodInfo
{
	int		MethodID;
	bool  	bState;
	char	    MethodName[64];
	int		TimeInt;
	int		ViewNum;
	int		TotalCameraNum;
	char	    CameraNum[100][20];
	char	    CameraName[100][128];
	int		CameraType[100];
	bool	    PlayFlag[100];
	int		CurrentID;
}_T_TUNECYCLE_METHODINFO, *_PT_TUNECYCLE_METHODINFO;

// ����������Ϣ�б�
typedef struct _t_AlarmInfoList
{
	char	node_name[64];
	char	node_num[20];
	char	node_stationnum[20];
	char	node_stationname[64];
	int		node_type;
	int		dvr_disk;
	int		dvr_temp;
	int		dvr_fan;
	int		camera_videolost;
	int		camera_videomove;
	int		camera_videocover;
	int		io_state;
	bool	dvr_disk_disable;
	bool	dvr_temp_disable;
	bool	dvr_fan_disable;
	bool	camera_videolost_disable;
	bool	camera_videomove_disable;
	bool	camera_videocover_disable;
	bool	io_state_disable;
}_T_ALARMINFOLIST, *_PT_ALARMINFOLIST;

typedef struct _t_AlarmReceivedList
{
	char	node_code[20];
	char	alarm_type[20];
	char	alarm_time[22];
}_T_ALARMRECEIVEDLIST, *_PT_ALARMRECEIVEDLIST;

// �澯��������
typedef struct _t_AlarmLink_Info
{
	char alarmdev_name[64];
	int	alarmdev_type;
	char alarmdev_code[20];
	char linkdev_name[64];
	char linkdev_code[20];
	int linkdev_action;			// ������������
	int linkdev_actionnotes;	// ����ΪԤ��λʱ��ΪԤ��λ�ţ�����Ϊ¼��ʱ��Ϊ¼��ʱ��
	int link_level;
	char notes[64];
	char stationname[64];
}_T_ALARMLINK_INFO, *_PT_ALARMLINK_INFO;

//------------------------------------------------------------------------//
//ȫ�ֱ�������
//------------------------------------------------------------------------//
extern char				g_DBServerIP[IPADDRESS_LEN];			//���ݿ�������ĵ�ַ
extern char               g_HttpServerIP[IPADDRESS_LEN];      //Http��������ַ
extern char               g_LinkServerIP[IPADDRESS_LEN];      //������������ַ
extern int                  g_nDBServerPort;                             //���ݿ�������˿�
extern int                  g_nHttpServerPort;                          //Http�������˿�              
extern int                  g_nLinkServerPort;                           //�����������˿�
extern MYSQL			*g_mySqlData;						            //mysql���ݿ����
extern char               g_DBName[256];
extern char g_AcsServerIp[IPADDRESS_LEN]; //����ϵͳ�������ĵ�ַ
extern int	 g_nAcsServerPort;	//����ϵͳ����Ķ˿�
extern int g_nShowManagerClient;//�Ƿ���ʾ����ͻ���

// �û���¼�ṹ
extern bool				app_IsUserLogin;					// �û���¼״̬
//extern MDCS_USER		app_User;						// ��¼�û�


//�û������Խ�
extern int				g_ua_realtalk_callid;
extern int				g_ua_realtalk_direction;
extern int				g_ua_realtalk_state;

//��½�û�Ȩ��
extern PUPR			g_userpower;
extern int              g_nUserType;//1:��ʾadmin�û�,2:��ʾʡ���û�,3��ʾʡ���û�
extern int              g_nUserResourceShowType;//1:��ʾ��admin��ʽ��ʾ,2:��ʾ��ʡ�����ṹ��ʾ,3:��ʾ��ʡ����ѹ�ȼ���ʾ


//�˹�Ѳ����Ϣ
extern _T_VIDEOPAGEVIEWINFO g_VideoPageViewInfo;

// ϵͳ��Ϣ�ṹ��
extern	_T_SYSTEM_INFO	g_SystemInfo[TOTALSYSNUM];
extern	int		g_TotalSysNum;

// ���������豸��Ϣ�б�
extern	_T_ALARMINFOLIST g_AlarmInfoList[TOTALALARMDEVICENUM];
extern	int		g_TotalAlarmInfoListNum;

// ���׹̶�ͷ
extern BYTE				pDSPHeader[19];

// ��Ѳ����
extern _T_TUNECYCLE_METHODINFO	g_TuneCycle_MehtodInfo;

// ���վ��һ���Ľڵ���Ϣ
extern _T_STATION_NODE_INFO	g_tStationNode_Info[MAX_STATION_NODE_NUM];
extern int					g_nStationNode_Num;

// ���б��վ����Ϣ
extern _T_STATION_INFO		g_tStation_Info[MAX_STATION_NUM];
extern int					g_nStation_Num;


extern void	*pDecHandle;						//�������
extern void	*pEncodeHandle;

typedef struct _t_preset_setting
{
	int id;
	int up_id;
	char camera_name[256];
	char camera_code[20];
	char preset_name[256];
	int preset_code;
	int node_type;			// 1��ʾ�ڵ㣬0��ʾ����ͷ
	int decoder_tag;
}_T_PRESET_SETTING, *_PT_PRESET_SETTING;

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

extern VEM_USER_CONFIG_INFO g_user_config_info;
extern _T_PRESET_SETTING	g_preset_setting[1000];
extern int					g_total_preset_setting;


#endif  // __STACK_H__ 
#endif	// _xappany_H_