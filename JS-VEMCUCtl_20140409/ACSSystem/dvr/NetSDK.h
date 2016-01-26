#ifndef NETDLSDK_INTERFACE_H
#define NETDLSDK_INTERFACE_H

#ifdef  NETSDK_EXPORTS
#define NET_DLDVR_API __declspec(dllexport)
#else
#define NET_DLDVR_API __declspec(dllimport)
#endif

#define STDCALL __stdcall	

typedef		LONG						LOGIN_HANDLE;
typedef 	LONG						LIVE_HANDLE;
typedef 	LONG						PLAYBACK_HANDLE;
typedef		unsigned int				SOCKET;
typedef  unsigned char		U8;
typedef  unsigned short		U16;
typedef  unsigned int		U32;

typedef struct _MONITOR_INFO
{
	U8			has_audio;		//�Ƿ�����Ƶ 1:����,0:û�а���
	U8			quality;		//���� 0:"��", 1:"��ͨ", 2:"��", 3:"�Ϻ�", 4:"���"
	U8			frame_rate;		//֡�� 0 ~ 25
	U8			video_format;	//��Ƶ��ʽ 0:PAL, 1:NTSC
	U8			resolution;		//�ֱ���
	U32			Mcast_IP;		//�ಥ���ַ(���DVR����ʹ�öಥ��ʽ�򷵻�0)
	U16			Mcast_port;		//�ಥ���ַ(���DVR����ʹ�öಥ��ʽ�򷵻�0)
}MONITOR_INFO;

/************************************************************************/
/* ����ֵ���忪ʼ                                                       */
/************************************************************************/
#define NET_DLDVR_NOERROR 				0     //û�д���



#define NET_DLDVR_ERROR_CREATESOCKET	-10		//����socketʧ��
#define NET_DLDVR_ERROR_CONNECT			-40		//��������ʧ��
#define NET_DLDVR_ERROR_RECV			-50		//��������ʧ��
#define NET_DLDVR_ERROR_STOP_STATUS		-60		//�Ƿ�״̬
#define NET_DLDVR_ERROR_MONITORSTOP		-100	//�رռ���ʧ��
#define NET_DLDVR_ERROR_GETVIDEOEFFECT	-200	//��ȡ��Ƶ����ʧ��
#define NET_DLDVR_ERROR_SETVIDEOEFFECT	-300	//������Ƶ����ʧ��
#define NET_DLDVR_ERROR_GENEIFRAME		-400	//���ɹؼ�֡ʧ��
#define NET_DLDVR_ERROR_PTZCONTROL		-500	//��̨����ʧ��
#define NET_DLDVR_ERROR_TRANSPTZ		-600	//͸����̨����ʧ��
#define NET_DLDVR_ERROR_PTZPRESET		-700	//����Ԥ��λʧ��
#define NET_DLDVR_ERROR_FINDFILEOPEN	-800	//��ʼ�����ļ�ʧ��
#define NET_DLDVR_ERROR_FINDFILENEXT	-900	//������һ���ļ�ʧ��
#define NET_DLDVR_ERROR_FINDFILECLOSE	-1000	//�رղ����ļ�ʧ��

//�����ļ�����־��������ֵ
#define NET_DLDVR_ERROR_FINDFILE_SUCCESS	0	//����ļ���Ϣ
#define NET_DLDVR_ERROR_FILE_NOFIND			-1001	//û���ļ�
#define NET_DLDVR_ERROR_ISFINDING			-1002	//���ڲ����ļ�
#define	NET_DLDVR_ERROR_NOMOREFILE			-1003	//�����ļ�ʱû�и�����ļ�
#define	NET_DLDVR_ERROR_FILE_EXCEPTION		-1004	//�����ļ�ʱ�쳣
#define	NET_DLDVR_ERROR_NO_PLAYSPACE		-1005	//û�лطſռ䣬�����������4�������û�ͬʱ����
#define	NET_DLDVR_ERROR_NO_POTENCE			-1006	//�û�û��Ȩ��
#define NET_DLDVR_ERROR_ENDOF_FILE			-1007	//�ѵ��ļ�β��

#define NET_DLDVR_HTTP_RESPON_ERROR		-1060		//Http��Ӧ����

#define	NET_DLDVR_ERROR_PLAYBYNAME		-1100	//�������ֻط�ʧ��
#define	NET_DLDVR_ERROR_LOCKFILE		-1110	//�����ļ�ʧ��
#define	NET_DLDVR_ERROR_ENTER_CSLOCK	-1111	//���ܻ�û�����
#define NET_DLDVR_ERROR_PLAYBYTIME		-1200	//����ʱ��ط�ʧ��
#define	NET_DLDVR_ERROR_DATA_READ		-1210	//��ȡ¼������ʧ��	
#define NET_DLDVR_ERROR_PLAYSEEK		-1300	//����ʱ�ƶ�λ��ʧ��
#define NET_DLDVR_ERROR_DOWNLOADBYNAME	-1400	//������������ʧ��
#define NET_DLDVR_ERROR_DOWNLOADBYTIME	-1500	//����ʱ������ʧ��
#define NET_DLDVR_ERROR_THREAD_FINISHED -1550	//�����߳��Ѿ�����
#define NET_DLDVR_ERROR_REPORTSTART		-1600	//����ʵʱ�ϱ�ʧ��
#define NET_DLDVR_ERROR_REPORTSTOP		-1700	//�ر�ʵʱ�ϱ�ʧ��
#define NET_DLDVR_ERROR_SETALARMOUT		-1800	//���ø澯���ʧ��
#define NET_DLDVR_ERROR_GETALARMOUT		-1900	//��ȡ�澯���ʧ��
#define NET_DLDVR_ERROR_PANELKEY		-2000	//����Զ����尴ť����
#define NET_DLDVR_ERROR_RECORDSTART		-2100	//��ʼ¼��ʧ��
#define NET_DLDVR_ERROR_RECORDSTOP		-2200	//����¼��ʧ��
#define NET_DLDVR_ERROR_LOGFINDOPEN		-2300	//��ʼ��ѯ��־ʧ��
#define NET_DLDVR_ERROR_LOGFINDNEXT		-2400	//��ѯ��һ����־ʧ��
#define NET_DLDVR_ERROR_LOGFINDCLOSE	-2500	//�رղ�ѯ��־ʧ��
#define NET_DLDVR_ERROR_GETDVRSTATE		-2600	//��ȡDVR״̬ʧ��
#define NET_DLDVR_ERROR_GETDVRVERSION	-2601	//��ȡDVR�汾��Ϣʧ��, 2007-07-27
#define NET_DLDVR_ERROR_RESTOREDVRCFG	-2700	//�ָ�Ĭ��ֵʧ��
#define NET_DLDVR_ERROR_SAVEDVGFLASH	-2800	//���������Flashʧ��
#define NET_DLDVR_ERROR_REBOOTDVR		-2900	//����DVRʧ��
#define NET_DLDVR_ERROR_SHUTDOWNDVR		-3000	//�ر�DVRʧ��
#define NET_DLDVR_ERROR_UPDATEBEGIN		-3100	//��ʼ����ʧ��
#define NET_DLDVR_ERROR_UPDATEDATA		-3200	//��������ʧ��
#define NET_DLDVR_ERROR_UPDATEND		-3300	//��������ʧ��
#define NET_DLDVR_ERROR_FLASHPEPERCENT	-3400	//��ȡdvrдFlash����ʧ��	
#define NET_DLDVR_ERROR_FORMATDISK		-3500	//��ʽ��Ӳ��ʧ��
#define NET_DLDVR_ERROR_FORMATDISKSTOP	-3600	//��ʽ��Ӳ�̽���ʧ��
#define NET_DLDVR_ERROR_FORMATPROGRESS	-3601	//��ȡ��ʽ��Ӳ�̽���ʧ��
#define NET_DLDVR_ERROR_LOCALLOGINMAX		-3700	//���ص�½��DVR���Ѿ����
#define NET_DLDVR_ERROR_DVRREJECTLOGIN  	-3701	//�����ܾ��˵�½����
#define NET_DLDVR_ERROR_CREATEWINDOWEVENT  	-3702	//������ʱ��ʱ�ȴ���������ʧ��
#define NET_DLDVR_ERROR_DVRREJECTTRANSSERIAL_START -3703	//�����ܾ��˽���͸��ͨ��������
#define NET_DLDVR_ERROR_DVRREJECTTRANSSERIAL_CTRL  -3704	//�����ܾ���͸��ͨ���ϵ���������
#define NET_DLDVR_ERROR_DVRREJECTTRANSSERIAL_STOP  -3705	//�����ܾ���ֹͣ͸��ͨ���ϵ�����
#define NET_DLDVR_ERROR_NOLOGIN				-3800	//�û�û�е�½
#define NET_DLDVR_ERROR_MAX_DOWNLOADING		-3900 //�������ص��ļ���Ŀ�Ѿ��ﵽ���ֵ
#define NET_DLDVR_ERROR_MAX_UPGRADING		-4000 //����������Image��Ŀ�Ѿ��ﵽ���ֵ
#define NET_DLDVR_ERROR_MAX_FORMAT			-4001 //���ڸ�ʽ����Ӳ����Ŀ�Ѿ��ﵽ���ֵ
#define NET_DLDVR_ERROR_MAX_SETRESOURCE		-4002 //�������õ��ֿ���Ŀ�Ѿ��ﵽ���ֵ
#define NET_DLDVR_ERROR_PLAYBACK_THROWBFRAME		-4010	//������B֡ʧ��


#define NET_DLDVR_ERROR_SETLANGUAGE_BEGIN			-4100	//��ʼ�����Զ�������ʧ��
#define NET_DLDVR_ERROR_SETLANGUAGE_DATA			-4200	//�����Զ�����������ʧ��
#define NET_DLDVR_ERROR_SETLANGUAGE_END				-4300	//�����Զ�����������ʧ��
#define NET_DLDVR_ERROR_SETLANGUAGE_FLASHPEPERCENT	-4400	//��ȡdvrдFlash����ʧ��
#define NET_DLDVR_ERROR_DOWNLOAD_LANGUAGE			-4410	//��������ʧ��

#define NET_DLDVR_ERROR_SETLOGO_BEGIN			-4500	//��ʼ��������ʧ��
#define NET_DLDVR_ERROR_SETLOGO_DATA			-4510	//��������ʧ��
#define NET_DLDVR_ERROR_SETLOGO_END				-4520	//������������ʧ��
#define NET_DLDVR_ERROR_SETLOGO_FLASHPEPERCENT	-4530	//��ȡdvrдFlash����ʧ��

#define NET_DLDVR_ERROR_SETRESOURCE_BEGIN			-4600	//��ʼ������Դʧ��
#define NET_DLDVR_ERROR_SETRESOURCE_DATA			-4610	//������Դ����ʧ��
#define NET_DLDVR_ERROR_SETRESOURCE_END				-4620	//������Դ����ʧ��
#define NET_DLDVR_ERROR_SETRESOURCE_FLASHPEPERCENT	-4630	//��ȡdvrдFlash����ʧ��

//NVR���еĴ���ֵ
#define NET_DLDVR_ERROR_DOWNLOAD_MAIL	-4700	//����Mailʧ��
#define NET_DLDVR_ERROR_UPLOAD_MAIL		-4800	//�ϴ�Mailʧ��


#define NET_DLDVR_ERROR_SEND			-5000	//��������ʧ��
#define NET_DLDVR_ERROR_UDPBIND			-5001	//��UDP�˿�ʧ��
#define NET_DLDVR_ERROR_MCBIND			-5002	//�󶨶ಥ�˿�ʧ��
#define NET_DLDVR_ERROR_SETTIMEOUT		-5003	//���ó�ʱʱ��ʧ��
#define NET_DLDVR_ERROR_JOINMC			-5004	//����ಥ��ʧ��
#define NET_DLDVR_ERROR_ACCEPT			-5005	//acceptʧ��
#define NET_DLDVR_ERROR_SELECT			-5006	//SELECT����ִ��ʧ��
#define NET_DLDVR_ERROR_CLOSESOCKET		-5007	//�ر��׽���ʧ��
#define NET_DLDVR_ERROR_JOINMUTICAST	-5008	//����ಥ��ʧ��
#define NET_DLDVR_ERROR_STARTUPSOCKET	-5009	//��ʼ���׽��ִ���
#define NET_DLDVR_ERROR_CREATEEVENT		-5010	//�����¼�����
#define NET_DLDVR_ERROR_SELECTEVENT		-5011	//�׽��ְ��¼���ʱ�����
#define NET_DLDVR_ERROR_SETEVENT		-5012	//�����¼���״̬ʱ����
#define NET_DLDVR_ERROR_INVALIDSOCKET	-5013	//������׽���
#define NET_DLDVR_ERROR_TIMEOUT			-5014	//���ͽ��ճ�ʱ
#define NET_DLDVR_ERROR_CONNRESET		-5015	//Զ������ǿ�ȹر������е�����
#define NET_DLDVR_ERROR_CONNABORTED		-5016	//���Ӷ˿�

//��ͨ����
#define NET_DLDVR_ERROR_OPENFILE			-6000	//���ļ�ʧ��
#define NET_DLDVR_ERROR_INVALIDPATH			-6001	//������ļ������ļ���
#define NET_DLDVR_ERROR_INVALIDDLL			-6002	//�޷��Ӷ�̬���ӿ��л�ȡ�ú����ĵ�ַ
#define NET_DLDVR_ERROR_READFILE			-6003	//���ļ�����
#define NET_DLDVR_ERROR_LOADDLL				-6004	//�޷�����ָ����DLL
#define NET_DLDVR_ERROR_LOADTALKDLL			-6005 //��������Talk DLL
#define NET_DLDVR_ERROR_LOADFRAMEDLL		-6006 //��������Frame DLL
#define NET_DLDVR_ERROR_FREEDLL				-6007	//�޷��ͷ�ָ����DLL
#define NET_DLDVR_ERROR_NOFUNCINDLL			-6008	//��dll���Ҳ�����Ҫ�ĺ���
#define NET_DLDVR_ERROR_ALREADSTARTUP		-6009	//DLL�Ѿ���ʼ������
#define NET_DLDVR_ERROR_POORMEMORY			-6010	//�����ڴ�Ĳ���������ϵͳ�ܾ�
#define NET_DLDVR_ERROR_NEEDSTARTUP			-6011	//��ʹ��֮ǰ��Ҫ�ȵ��ó�ʼ������
#define NET_DLDVR_ERROR_INVALIDFILEH		-6012	//������ļ����
#define NET_DLDVR_ERROR_CREATETHREAD		-6013	//�����߳�ʧ��
#define NET_DLDVR_ERROR_CREATETIMER			-6014	//����timerʧ��
#define NET_DLDVR_ERROR_AVIFILEOPEN			-6015	//��һ��AVI�ļ��Ի�ʧ��
#define NET_DLDVR_ERROR_CREATEAVISTREAM		-6016 //����AVI��ʧ��
#define NET_DLDVR_ERROR_CONVERTMP4TOAVI		-6017	//��MP4ת����AVI�Ĺ����з�����һ������
#define NET_DLDVR_ERROR_INVALIDPARA			-6018	//���ݸ���̬��Ĳ�������
#define NET_DLDVR_ERROR_LOADDECODERDLL		-6019 //��������DLLDECODER_H264.dll
#define NET_DLDVR_ERROR_LOADIMAGECONVERTDLL	-6020 //��������ImageConverter_H264.dll
#define NET_DLDVR_ERROR_LOADIJL15DLL		-6021 //��������ijl15.dll
#define NET_DLDVR_ERROR_NOTSUPPORTDVR		-6022 //���Ͳ�֧�ָò���
#define NET_DLDVR_ERROR_FILE_NOTMATCHING	-6023	//�ļ����Ͳ�ƥ��  
#define NET_DLDVR_ERROR_FILE_VERSIOM		-6024	//Ҫ�������ļ��汾��ԭ�ȵ������汾��
#define NET_DLDVR_ERROR_PLAYER_NOTFIND_BYHANDLE		-6030	//����handleû���ҵ�Player���

//�Զ������:
//DVR��������
#define NET_DLDVR_ERROR_INVALIDPWD			-7000	//��½ʱ�������
#define NET_DLDVR_ERROR_TOOMANYUSER			-7001	//��ǰ��½��DVR���û��Ѿ��ﵽ���ֵ��
#define NET_DLDVR_ERROR_POORRIGHT			-7002	//��½ʱȨ�޲���
#define NET_DLDVR_ERROR_STARTMONITOR		-7003	//��DVR������Ƶ����ʧ��
#define NET_DLDVR_ERROR_BROWSEPB			-7004	//�طŵ��µ�Ԥ��ʧ��
#define NET_DLDVR_ERROR_BROWSEHW			-7005 //Ӳ�����µ�Ԥ��ʧ��
#define NET_DLDVR_ERROR_SEARCHRECORD		-7006	//DVR�ܾ��˼���¼���ļ�������
#define NET_DLDVR_ERROR_PLAYBACK			-7007	//DVR�ܾ��˻طŵ�����
#define NET_DLDVR_ERROR_DOWNLOAD			-7008	//DVR�ܾ�������¼���ļ�������
#define NET_DLDVR_ERROR_GETSYSCFG			-7009	//DVR�ܾ��˻�ȡϵͳ����������
#define NET_DLDVR_ERROR_GETPTZPRESET		-7010 //DVR�ܾ��˻�ȡ��̨Ԥ�Ƶ������
#define NET_DLDVR_ERROR_SETPTZPRESET		-7011	//DVR�ܾ���������̨Ԥ�Ƶ������
#define NET_DLDVR_ERROR_REMOVEPTZPRESET		-7012	//DVR�ܾ���ɾ����̨Ԥ�Ƶ������
#define NET_DLDVR_ERROR_CALLPTZPRESET		-7013	//DVR�ܾ��˺�����̨Ԥ�Ƶ������
#define NET_DLDVR_ERROR_STARTCRUISE			-7014	//DVR�ܾ���Ѳ����ʼ������
#define NET_DLDVR_ERROR_STOPCRUISE			-7015	//DVR�ܾ���Ѳ������������

#define NET_DLDVR_ERROR_LOADDEFAULT			-7100	//DVR�ܾ�������������õ�����
#define NET_DLDVR_ERROR_GETCHANNELSTATE		-7101	//DVR�ܾ��˻�ȡͨ��¼��״̬������
#define NET_DLDVR_ERROR_SETCHANNELSTATE		-7102	//DVR�ܾ�������ͨ��¼��״̬������
#define NET_DLDVR_ERROR_GETSWITCHSTATE		-7103	//DVR�ܾ��˻�ȡ��ӿ���״̬������
#define NET_DLDVR_ERROR_SETSWITCHSTATE		-7104	//DVR�ܾ���������ӿ���״̬������
#define NET_DLDVR_ERROR_REJECTNEWIMG		-7105	//DVR�ܾ��˸���ϵͳ���������
#define NET_DLDVR_ERROR_UPGRADESYSTEM		-7106	//DVR�ܾ������µ�ϵͳ���
#define NET_DLDVR_ERROR_UPGRADEWEB			-7107	//DVR�ܾ��˸�����ǶWEB������
#define NET_DLDVR_ERROR_GETALARMLOG			-7108	//DVR�ܾ��˻�ȡ�澯��־������
#define NET_DLDVR_ERROR_GETRUNLOG			-7109	//DVR�ܾ��˻�ȡ������־������
#define NET_DLDVR_ERROR_GETVERSION			-7110	//DVR�ܾ��˻�ȡ�汾��Ϣ������
#define NET_DLDVR_ERROR_GETTIME				-7111	//DVR�ܾ��˻�ȡϵͳʱ�������
#define NET_DLDVR_ERROR_SETTIME				-7112	//DVR�ܾ�������ϵͳʱ�������
#define NET_DLDVR_ERROR_RESTART				-7113	//DVR�ܾ�����������������
#define NET_DLDVR_ERROR_USBBACKUP			-7114	//DVR�ܾ���USB���ݵ�����
#define NET_DLDVR_ERROR_CHECKSUM			-7115	//ϵͳ���µ�ʱ����������У�����
#define NET_DLDVR_ERROR_REJECTRECVDATA		-7116	//ϵͳ���µ�ʱ��dvr��;�ܾ��˽���ӳ��
#define NET_DLDVR_ERROR_UPGRADEING			-7117	//dvr��ִ��ϵͳ���µ�ʱ�򷢳��˾ܾ�ָ��
#define NET_DLDVR_ERROR_TRANSPCHANNEL		-7118	//dvrִ��͸��ͨ����ʱ��ʧ����
#define NET_DLDVR_ERROR_REGALARMUSER		-7119	//dvr�ܾ���ע��澯�����û�
#define NET_DLDVR_ERROR_SYSPARAUPDATE		-7120 //����ϵͳ����ʧ��
#define NET_DLDVR_ERROR_RCDPARAUPDATE		-7121 //����¼�����ʧ��
#define NET_DLDVR_ERROR_NOTOPENDVRCFG		-7122 //û�д�DVR����
#define	NET_DLDVR_ERROR_LOGOUT				-7123
#define NET_DLDVR_ERROR_NOT_SURPPORTED		-7124	//��֧�ָýӿ�

#define NET_DLDVR_ERROR_CREATEOVERLAY	-7200	//���ܴ���Overlay,��ʹ����ͨ��ʽ��ʼ��
#define NET_DLDVR_ERROR_STARTTALK		-7201	//�����Խ�ʧ��
#define NET_DLDVR_ERROR_CONFLICTVF		-7202	//���ͻ����Ƶ��ʽ

#define NET_DLDVR_ERROR_DIRECTDRAWCREATE		-7210//����һ��DirectDraw����ʧ��
#define NET_DLDVR_ERROR_SETCOOPERATIVELEVEL		-7212//ָ��Ӧ�ó�����Ҫ��Ķ���ʾӲ���Ŀ��Ƴ̶�ʧ��
#define NET_DLDVR_ERROR_CREATESURFACE			-7213//������ҳ�����ʧ��
#define NET_DLDVR_ERROR_CREATEBACKSURFACE		-7214//������ҳ�����ʧ��
#define NET_DLDVR_ERROR_CREATECLIPPER			-7215//����DirectDrawClipper�ӿ�ʧ��
#define NET_DLDVR_ERROR_SETCLIPPER				-7216//�������������ӱ���ʧ��

#define NET_DLDVR_ERROR_ALREADYLOADDLL		-7300	//�Ѿ���������Ӧ�Ķ�̬���ӿ�
#define NET_DLDVR_ERROR_INVALIDDLLH			-7301	//���̲�û�������DLL,ȴҪ���ͷŸ�DLL
#define NET_DLDVR_ERROR_PLAYSTARTUP			-7302	//���ſ��ʼ��ʧ��
#define NET_DLDVR_ERROR_FRAMELIBSTARTUP		-7303 //֡�ſ��ʼ����
#define NET_DLDVR_ERROR_NOIDLEPLAYER		-7304	//�������������Ѿ��ﵽ���ֵ
#define NET_DLDVR_ERROR_OPENPLAYER			-7305 //����NetOpenPlayer��ʱ�����
#define NET_DLDVR_ERROR_INVALIDMONITORS		-7306	//��û�д򿪼���,ȴҪ��رռ���
#define NET_DLDVR_ERROR_INVALIDPLAYRS		-7307	//��û�д򿪻ط�,ȴҪ��رջط�
#define NET_DLDVR_ERROR_INVALIDPLAYFS		-7308	//��û�д��ļ�����,ȴҪ��ر�
#define NET_DLDVR_ERROR_INVALIDPLAYHD		-7309	//�����Player���
#define NET_DLDVR_ERROR_INVALIDSPEED		-7310 //��֧�ֵĲ����ٶ�
#define NET_DLDVR_ERROR_INVALIDSTATE		-7311	//��֧�ֵ�״̬
#define NET_DLDVR_ERROR_INVALIDINITTYPE		-7312	//ʹ�øù�����ҪOverlayģʽ
#define NET_DLDVR_ERROR_ALARMCENTERON		-7313	//�澯�����Ѿ�����
#define NET_DLDVR_ERROR_ALARMCENTEROFF		-7314	//�澯���Ļ�û�п���
#define NET_DLDVR_ERROR_REPORTON			-7315 //ʵʱ�ϱ��Ѿ�����
#define NET_DLDVR_ERROR_REPORTOFF			-7316 //ʵʱ�ϱ�δ����
#define NET_DLDVR_ERROR_INVALIDTAIKH		-7320	//����ĶԽ����
#define NET_DLDVR_ERROR_INVALIDTALKS		-7321	//��û�д򿪶Խ�,ȴҪ��ر�

#define NET_DLDVR_ERROR_FORBIDDEN			-7400	//���ӽ�ֹ
#define NET_DLDVR_ERROR_NO_PREREC			-7401	//����û�п�Ԥ¼
#define NET_DLDVR_ERROR_SETIFRAMEONLYCH		-7410	//ѡ��֡��ͨ��ʧ��

#define NET_DLDVR_PASSWORD_ERROR 		-7500       //�û����������
#define NET_DLDVR_NOENOUGHPRI 			-7510       //Ȩ�޲���
#define NET_DLDVR_OPERNOPERMIT			-7520       //�޴�Ȩ��
#define NET_DLDVR_NOINIT 				-7530       //û�г�ʼ��
#define NET_DLDVR_OVER_MAXLINK 			-7540       //���ӵ�DVR�Ŀͻ��˸����������
#define NET_DLDVR_MAX_NUM				-7550	    //�����ﵽ���
#define NET_DLDVR_USERNOTEXIST			-7560	    //�û�������
#define NET_DLDVR_CREATESOCKET_ERROR	-7570	//����SOCKET����
#define NET_DLDVR_NETWORK_FAIL_CONNECT	-7580 //���ӷ�����ʧ��
#define NET_DLDVR_NETWORK_RECV_ERROR	-7590 //�ӷ�������������ʧ��
#define NET_DLDVR_NETWORK_RECV_TIMEOUT	-7600 //�ӷ������������ݳ�ʱ
#define NET_DLDVR_WRITEFLASHERROR		-7610       //дFLASH����
#define NET_DLDVR_NETWORK_SEND_ERROR	-7620       //�����������ʧ��
#define NET_DLDVR_PARAMETER_ERROR 		-7630       //��������
#define	NET_DLDVR_FILEOPENFAIL			-7640       //���ļ�����
#define NET_DLDVR_MAX_USERNUM			-7650	//�û����ﵽ���
#define NET_DLDVR_VERSIONNOMATCH		-8000	//�汾��ƥ��
#define NET_DLDVR_CHANNEL_ERROR 		-8001	//ͨ���Ŵ���
#define NET_DLDVR_NETWORK_ERRORDATA		-8002	//���͵���������
#define NET_DLDVR_ORDER_ERROR			-8003	//���ô������
#define NET_DLDVR_COMMANDTIMEOUT		-8004	//DVR����ִ�г�ʱ
#define NET_DLDVR_ERRORSERIALPORT		-8005	//���ںŴ���
#define NET_DLDVR_ERRORALARMPORT		-8006	//�����˿ڴ���
#define NET_DLDVR_CHAN_EXCEPTION		-8007	//������ͨ�����ڴ���״̬
#define NET_DLDVR_NODISK				-8008	//û��Ӳ��
#define NET_DLDVR_ERRORDISKNUM			-8009	//Ӳ�̺Ŵ���
#define NET_DLDVR_DISK_FULL				-8010	//������Ӳ����
#define NET_DLDVR_DISK_ERROR			-8011	//������Ӳ�̳���
#define NET_DLDVR_NOSUPPORT				-8012	//��������֧��
#define NET_DLDVR_BUSY					-8013	//������æ
#define NET_DLDVR_MODIFY_FAIL			-8014	//�������޸Ĳ��ɹ�
#define NET_DLDVR_PASSWORD_FORMAT_ERROR	-8015	//���������ʽ����ȷ
#define NET_DLDVR_DISK_FORMATING		-8016	//Ӳ�����ڸ�ʽ����������������
#define NET_DLDVR_DVRNORESOURCE			-8017	//DVR��Դ����
#define	NET_DLDVR_DVROPRATEFAILED		-8018	//DVR����ʧ��
#define NET_DLDVR_OPENHOSTSOUND_FAIL 	-8019	//��PC����ʧ��
#define NET_DLDVR_DVRVOICEOPENED 		-8020	//�����������Խ���ռ��
#define	NET_DLDVR_TIMEINPUTERROR		-8021	//ʱ�����벻��ȷ
#define	NET_DLDVR_NOSPECFILE			-8022	//�ط�ʱ������û��ָ�����ļ�
#define NET_DLDVR_CREATEFILE_ERROR		-8023	//�����ļ�����
#define	NET_DLDVR_OPERNOTFINISH			-8024	//�ϴεĲ�����û�����
#define	NET_DLDVR_GETPLAYTIMEFAIL		-8025	//��ȡ��ǰ���ŵ�ʱ�����
#define	NET_DLDVR_PLAYFAIL				-8026	//���ų���
#define NET_DLDVR_FILEFORMAT_ERROR		-8027	//�ļ���ʽ����ȷ
#define NET_DLDVR_DIR_ERROR				-8028	//·������
#define NET_DLDVR_ALLOC_RESOUCE_ERROR	-8029	//��Դ�������
#define NET_DLDVR_AUDIO_MODE_ERROR		-8030	//����ģʽ����
#define NET_DLDVR_NOENOUGH_BUF			-8031	//������̫С
#define NET_DLDVR_SETSOCKET_ERROR		-8032	//����SOCKET����
#define NET_DLDVR_CARDHAVEINIT			-8034	//���뿨�Ѿ���ʼ����
#define NET_DLDVR_PLAYERFAILED			-8035	//�������д���
#define NET_DLDVR_GETLOCALIPANDMACFAIL	-8036	//��ÿͻ��˵�IP��ַ�������ַʧ��
#define NET_DLDVR_NOENCODEING			-8037	//��ͨ��û�б���
#define NET_DLDVR_IPMISMATCH			-8038	//IP��ַ��ƥ��
#define NET_DLDVR_MACMISMATCH			-8039	//MAC��ַ��ƥ��
#define NET_DLDVR_UPGRADELANGMISMATCH	-8040	//�����ļ����Բ�ƥ��

#define NET_DLDVR_UPGRADENETERROR		-8070	//����Ͽ���״̬δ֪
#define NET_DLDVR_UPGRADEFAIL			-8080	//��������ʧ��

#define NET_DLDVR_SETLANGUAGE_NETERROR	-8090	//����Ͽ���״̬δ֪
#define NET_DLDVR_SETLANGUAGE_FAIL		-8091	//�����Զ�������ʧ��

#define NET_DLDVR_SETLOGO_NETERROR		-8093	//����Ͽ���״̬δ֪
#define NET_DLDVR_SETLOGO_FAIL			-8094	//�����Զ�������ʧ��

#define NET_DLDVR_SETRESOURCE_NETERROR	-8095	//����Ͽ���״̬δ֪
#define NET_DLDVR_SETRESOURCE_FAIL		-8096	//������Դʧ��

#define NET_DLDVR_SETFILE_NETERROR		-8097	//����Ͽ���״̬δ֪
#define NET_DLDVR_SETFILE_FAIL			-8098	//�����ļ�ʧ��

//�Խ����	-9000 ~ -9500
#define NET_DLDVR_NOIDLETALKER			-9000		//�Խ����������Ѿ��ﵽ���ֵ

#define NET_DLDVR_ERROR_NOTRIGHT_TYPE	-9010	//�û��Ͳ�֧�ָýӿ�
#define NET_DLDVR_ERROR_TRANSSERIAL_NOTSTART	-9020	//û�н���͸��ͨ��

//2010-03-19 add,DM60���
#define NET_DLDVR_ERROR_NOCMD_TYPE	-9101	//���������ֵ
#define NET_DLDVR_ERROR_GETDMCOLOR	-9102	//�����ܾ��˻�ȡDMColor������
#define NET_DLDVR_ERROR_SETDMCOLOR	-9103	//�����ܾ�������DMColor������	
#define NET_DLDVR_ERROR_SET_DMCOMMAND	-9104	//�����ܾ���DMCommand����
#define NET_DLDVR_ERROR_SET_DMCONFIG	-9105	//�����ܾ�������DMConfig������
#define NET_DLDVR_ERROR_GET_DMCONFIG	-9106	//�����ܾ��˻�ȡDMConfig������
#define NET_DLDVR_ERROR_GET_DMMEASURE	-9107	//�����ܾ��˻�ȡ���²���������
#define NET_DLDVR_ERROR_SET_DMMEASURE	-9108	//�����ܾ������ò��²���������
#define NET_DLDVR_ERROR_PARA	-9120	//����Ĳ�������
#define NET_DLDVR_ERROR_PTZPROTOCOL_NOTSUPPORT	-9121	//��֧�ֵ���̨Э��
#define NET_DLDVR_ERROR_DMMEASURE_TYPE	-9122	//����Ĳ���Ŀ������
#define NET_DLDVR_ERROR_DMMEASURE_INFO	-9123	//������¶���Ϣ

#define NET_DLDVR_ERROR_QUERY_FUNCTION			-9130	//���ܲ�ѯʧ��
#define NET_DLDVR_ERROR_QUERY_FUNCTION_OVERFLOW -9131	//���ܲ�ѯ��ΧԽ��
#define NET_DLDVR_ERROR_SETCHANNELSTREAM_EX		-9132	//һ�������õ�̨���������ͨ������״̬


/************************************************************************/
/* ����ֵ�������                                                       */
/************************************************************************/


#define NET_DLDVR_UPGRADESUCESS			1000	//�����ɹ�
#define NET_DLDVR_UPGRADEING			1010	//��������
#define NET_DLDVR_UPGRADEING_DOWNLOAD	1011	//��������-���ؾ���
#define NET_DLDVR_UPGRADEING_APPLYING	1012	//��������-Ӧ�þ���

#define NET_DLDVR_SETLANGUAGE			1020	//���������Զ�������
#define NET_DLDVR_SETLANGUAGE_DOWNLOAD	1021	//���������Զ�������-���������ļ�
#define NET_DLDVR_SETLANGUAGE_APPLYING	1022	//���������Զ�������-Ӧ�������ļ���дflash��
#define NET_DLDVR_USETLANGUAGE_SUCESS	1023	//�������Գɹ��ɹ�

#define NET_DLDVR_SETLOGO				1030	//���������Զ���LOGO
#define NET_DLDVR_SETLOGO_DOWNLOAD		1031	//���������Զ���LOGO-����Logo�ļ�
#define NET_DLDVR_SETLOGO_APPLYING		1032	//���������Զ���LOGO-Ӧ��Logo�ļ���дflash��
#define NET_DLDVR_USETLOGO_SUCESS		1033	//����LOGO�ɹ��ɹ�

#define NET_DLDVR_SETRESOURCE				1040	//����������Դ
#define NET_DLDVR_SETRESOURCE_DOWNLOAD		1041	//����������Դ-������Դ�ļ�
#define NET_DLDVR_SETRESOURCE_APPLYING		1042	//����������Դ-Ӧ����Դ�ļ���дflash��
#define NET_DLDVR_SETRESOURCE_SUCESS		1043	//������Դ�ɹ�

#define NET_DLDVR_SETFILE				1050	//���������ļ�
#define NET_DLDVR_SETFILE_SUCCESS		1051	//�����ļ��ɹ�

//NET_DLDVR_IsSupport()����ֵ 
//1��9λ�ֱ��ʾ������Ϣ��λ����TRUE)��ʾ֧�֣�
#define NET_DLDVR_SUPPORT_DDRAW			0x01//֧��DIRECTDRAW�������֧�֣��򲥷������ܹ�����
#define NET_DLDVR_SUPPORT_BLT				0x02//�Կ�֧��BLT�����������֧�֣��򲥷������ܹ�����
#define NET_DLDVR_SUPPORT_BLTFOURCC		0x04//�Կ�BLT֧����ɫת���������֧�֣��������������������RGBת����
#define NET_DLDVR_SUPPORT_BLTSHRINKX		0x08//�Կ�BLT֧��X����С�������֧�֣�ϵͳ�����������ת����
#define NET_DLDVR_SUPPORT_BLTSHRINKY		0x10//�Կ�BLT֧��Y����С�������֧�֣�ϵͳ�����������ת����
#define NET_DLDVR_SUPPORT_BLTSTRETCHX		0x20//�Կ�BLT֧��X��Ŵ������֧�֣�ϵͳ�����������ת����
#define NET_DLDVR_SUPPORT_BLTSTRETCHY		0x40//�Կ�BLT֧��Y��Ŵ������֧�֣�ϵͳ�����������ת����
#define NET_DLDVR_SUPPORT_SSE				0x80//CPU֧��SSEָ�Intel Pentium3����֧��SSEָ�
#define NET_DLDVR_SUPPORT_MMX				0x100//CPU֧��MMXָ���Intel Pentium3����֧��SSEָ�

#define DL_SET_PRESET						1	// ����Ԥ�õ� 
#define DL_CLE_PRESET						2	// ���Ԥ�õ� 
#define DL_GOTO_PRESET						3	// ת��Ԥ�õ�

#define DL_LIGHT_PWRON						3	// ��ͨ�ƹ��Դ //2010-10-28   2------->3
#define DL_WIPER_PWRON						2	// ��ͨ��ˢ���� //2010-10-28   3------->2
#define DL_FAN_PWRON						4	// ��ͨ���ȿ��� 
#define DL_HEATER_PWRON					5	// ��ͨ���������� 
#define DL_AUX_PWRON						6	// ��ͨ�����豸���� 

#define PTZ_STOP						10	//ֹͣ��̨����

#define DL_ZOOM_IN							11	// �������ٶ�SS���(���ʱ��) 
#define DL_ZOOM_OUT						12	// �������ٶ�SS��С(���ʱ�С) 
#define DL_FOCUS_NEAR						13	// �������ٶ�SSǰ�� 
#define DL_FOCUS_FAR						14	// �������ٶ�SS��� 
#define DL_IRIS_OPEN						15	// ��Ȧ���ٶ�SS���� 
#define DL_IRIS_CLOSE						16	// ��Ȧ���ٶ�SS��С 
#define DL_TILT_UP							21	// ��̨��SS���ٶ����� 
#define DL_TILT_DOWN						22	// ��̨��SS���ٶ��¸� 
#define DL_PAN_LEFT						23	// ��̨��SS���ٶ���ת 
#define DL_PAN_RIGHT						24	// ��̨��SS���ٶ���ת 
#define DL_PAN_AUTO						29	// ��̨��SS���ٶ������Զ�ɨ�� 

#define FILL_PRE_SEQ	30 // ��Ԥ�õ����Ѳ������ 
#define SET_SEQ_DWELL	31 // ����Ѳ����ͣ��ʱ�� 
#define SET_SEQ_SPEED	32 // ����Ѳ���ٶ� 
#define CLE_PRE_SEQ		33 // ��Ԥ�õ��Ѳ��������ɾ�� 
#define RUN_CRUISE		36	// ��ʼ�켣 
#define RUN_SEQ			37	// ��ʼѲ�� 
#define STOP_SEQ		38	// ֹͣѲ�� 

#define Get_SEQ_ROUTE	39	//��ȡָ��ͨ����Ѳ������


//��ʾģʽ
//enum{NORMALMODE = 0,OVERLAYMODE};

//����ģʽ
//enum{PTOPTCPMODE,PTOPUDPMODE,MULTIMODE,RTPMODE,AUDIODETACH,NOUSEMODE};

#define NET_DLDVR_SYSHEAD 				0xEE	//ϵͳͷ����
#define NET_DLDVR_STREAMDATA 			0xEF	//������
#define NET_DLDVR_STREAMDATA_VIDEO 		0x1		//��׼��Ƶ��
#define NET_DLDVR_STREAMDATA_AUDIO		0x2		//��׼��Ƶ��

//���ſ�������궨�� NET_DLDVR_PlayBackControl,NET_DLDVR_PlayControlLocDisplay,NET_DLDVR_DecPlayBackCtrl�ĺ궨��
#define NET_DLDVR_PLAYSTART					1	//��ʼ����
#define NET_DLDVR_PLAYSTOP					2	//ֹͣ����
#define NET_DLDVR_PLAYPAUSE					3	//��ͣ����
#define NET_DLDVR_PLAYRESTART				4	//�ָ�����
#define NET_DLDVR_PLAYFAST					5	//���(4����)
#define NET_DLDVR_PLAYSLOW					6	//����(1/4����)
#define NET_DLDVR_PLAYNORMAL				7	//�����ٶ�
#define NET_DLDVR_PLAYFRAME					8	//��֡��
#define NET_DLDVR_PLAYSTARTAUDIO			9	//������
#define NET_DLDVR_PLAYSTOPAUDIO				10	//�ر�����
#define NET_DLDVR_PLAYAUDIOVOLUME			11	//��������
#define NET_DLDVR_PLAYSETPOS				12	//�ı��ļ��طŵĽ���
#define NET_DLDVR_PLAYGETPOS				13	//��ȡ�ļ��طŵĽ���
#define NET_DLDVR_PLAYGETTIME				14	//��ȡ��ǰ�Ѿ����ŵ�ʱ��
#define NET_DLDVR_PLAYGETFRAME				15	//��ȡ��ǰ�Ѿ����ŵ�֡��
#define NET_DLDVR_GETTOTALFRAMES  			16	//��ȡ��ǰ�����ļ��ܵ�֡��
#define NET_DLDVR_GETTOTALTIME    			17	//��ȡ��ǰ�����ļ��ܵ�ʱ��
#define NET_DLDVR_THROWBFRAME				20	//��B֡
#define NET_DLDVR_GETPLAYAUDIOVOLUME		21	//��õ�ǰ��������С��2007-12-14��he
#define NET_DLDVR_PLAY_DOUBLESPEED			22	//2����
#define NET_DLDVR_PLAY_HALFSPEED			23	//1/2�ٶ�
#define NET_DLDVR_PLAY_SETPOS_BYTIME		24	//�ط�ʱ��ʱ��ٷֱ���ת��ĳλ��
#define NET_DLDVR_PLAY_OCTUPLESPEED			25	//8����,2010-07-06 add
#define NET_DLDVR_PLAY_SIXTEENSPEED			26	//16����,2010-07-06 add
#define NET_DLDVR_PLAY_32SPEED				27	//32����,2010-07-06 add

//NET_DLDVR_GetDVRConfig,NET_DLDVR_GetDVRConfig�������
#define NET_DLDVR_GET_ALLCFG				0	//������в���
#define NET_DLDVR_SET_ALLCFG				0	//������в���
#define NET_DLDVR_GET_DEVICECFG				1	//��ȡ�豸����
#define NET_DLDVR_SET_DEVICECFG				1	//�����豸����
#define NET_DLDVR_GET_NETCFG				2	//��ȡ�������
#define NET_DLDVR_SET_NETCFG				2	//�����������
#define NET_DLDVR_GET_PICCFG				3	//��ȡͼ�����
#define NET_DLDVR_SET_PICCFG				3	//����ͼ�����
#define NET_DLDVR_GET_COMPRESSCFG			4	//��ȡѹ������
#define NET_DLDVR_SET_COMPRESSCFG			4	//����ѹ������
#define NET_DLDVR_GET_RECORDCFG				5	//��ȡ¼��ʱ�����
#define NET_DLDVR_SET_RECORDCFG				5	//����¼��ʱ�����
#define NET_DLDVR_GET_DECODERCFG			6	//��ȡ����������
#define NET_DLDVR_SET_DECODERCFG			6	//���ý���������
#define NET_DLDVR_GET_RS232CFG 				7	//��ȡ232���ڲ���
#define NET_DLDVR_SET_RS232CFG				7	//����232���ڲ���
#define NET_DLDVR_GET_ALARMINCFG 			8	//��ȡ�����������
#define NET_DLDVR_SET_ALARMINCFG			8	//���ñ����������
#define NET_DLDVR_GET_ALARMOUTCFG 			9	//��ȡ�����������
#define NET_DLDVR_SET_ALARMOUTCFG			9	//���ñ����������
#define NET_DLDVR_GET_TIMECFG 				10	//��ȡDVRʱ��
#define NET_DLDVR_SET_TIMECFG				10	//����DVRʱ��
#define NET_DLDVR_GET_PREVIEWCFG 			11	//��ȡԤ������
#define NET_DLDVR_SET_PREVIEWCFG			11	//����Ԥ������
#define NET_DLDVR_GET_VIDEOOUTCFG 			12	//��ȡ��Ƶ�������
#define NET_DLDVR_SET_VIDEOOUTCFG			12	//������Ƶ�������
#define NET_DLDVR_GET_USERCFG 				13	//��ȡ�û�����
#define NET_DLDVR_SET_USERCFG				13	//�����û�����
#define NET_DLDVR_GET_EXCEPTIONCFG 			14	//��ȡ�쳣����
#define NET_DLDVR_SET_EXCEPTIONCFG			14	//�����쳣����
#define NET_DLDVR_GET_SHOWSTRING			15	//��ȡ�����ַ�����
#define NET_DLDVR_SET_SHOWSTRING			15	//���õ����ַ�����
#define NET_DLDVR_GET_AUXOUTCFG				16	//��ȡ�����������
#define NET_DLDVR_SET_AUXOUTCFG				16	//���ø����������
#define NET_DLDVR_GET_PICCFG_EX				17	//��ȡͼ���������չ��
#define NET_DLDVR_SET_PICCFG_EX				17	//����ͼ���������չ��
#define NET_DLDVR_GET_USERCFG_EX 			18	//��ȡ�û�����
#define NET_DLDVR_SET_USERCFG_EX			18	//�����û�����
#define NET_DLDVR_GET_DEVICEVERSION			19  //��ȡAUX_PARAMETER���� 
#define NET_DLDVR_SET_AUX_PARAMETER			19  //����AUX_PARAMETER����
#define NET_DVR_SET_SEQ_ROUTE				20  //����ָ��ͨ����Ѳ������
#define NET_DVR_GET_SEQ_ROUTE				20  //��ȡָ��ͨ����Ѳ������

//2011-02-23 add, 600��700���ͻָ��������õĲ������ͣ���NET_DLDVR_RestoreConfigByType()�ӿڵ�ConfigTypeֵ���壩
#define NET_DLDVR_RESTORE_SYSTEM 		1	//�������� 
#define NET_DLDVR_RESTORE_DISPLAY		2	//��ʾ����
#define NET_DLDVR_RESTORE_RECORD		3  //¼�����
#define NET_DLDVR_RESTORE_USER			4  //�û�����
#define NET_DLDVR_RESTORE_NETWORK		5 //�������
#define NET_DLDVR_RESTORE_PTZ			6  //��̨����
#define NET_DLDVR_RESTORE_ALLCFG		7  //ȫ������

//2009-01-18, ��������NVR��ȡ/����ϵͳ�������õ�����
#define NET_DVR_GET_SYSTEMCFG_NVR	30       //������еĲ���
#define NET_DVR_GET_RVSCFG_NVR		31     //��ȡ ��ƵԴ����          
#define NET_DVR_GET_ALARMREC_NVR	32    //��ȡ ����¼�����
#define NET_DVR_GET_DEMOCFG_NVR		33    //��ȡ ��̨��ز���

#define NET_DVR_SET_SYSTEMCFG_NVR  30       //�������еĲ���
#define NET_DVR_SET_RVSCFG_NVR     31   //���� ��ƵԴ����
#define NET_DVR_SET_ALARMREC_NVR	32    //��ȡ ����¼�����
#define NET_DVR_SET_DEMOCFG_NVR    33   //���� ��̨��ز���

//2010-03-22,DM60 ����Ŀ�����õ��������
#define NET_DVR_GET_DMMEASURE_POINT	1
#define NET_DVR_SET_DMMEASURE_POINT	1
#define NET_DVR_GET_DMMEASURE_LINE	2
#define NET_DVR_SET_DMMEASURE_LINE	2
#define NET_DVR_GET_DMMEASURE_AREA	3
#define NET_DVR_SET_DMMEASURE_AREA	3
#define NET_DVR_CLEAR_DMMEASURE_POINT	1
#define NET_DVR_CLEAR_DMMEASURE_LINE		2
#define NET_DVR_CLEAR_DMMEASURE_AREA		3

//DM60����Ŀ�������
#define NET_DVR_GET_DMMEASURE_ALL	0
#define NET_DVR_GET_DMMEASURE_POINT	1
#define NET_DVR_GET_DMMEASURE_LINE	2
#define NET_DVR_GET_DMMEASURE_AREA	3

//DM60�������������¶�����
#define NET_DVR_DMMEASURE_POINT	0
#define NET_DVR_DMMEASURE_LINE	1
#define NET_DVR_DMMEASURE_AREA	2


//DM60ԭʼ���ݲɼ���״̬
#define DM60_CAPTUREINFRARED_ING		1	// ���ڲɼ�
#define DM60_CAPTUREINFRARED_OVER		2	// �ɼ����
#define DM60_CAPTUREINFRARED_ERROR		3	// �ɼ�����

//DM60�ļ���������
#define UPDATEFILE_TYPE_DM60_MID		0
#define UPDATEFILE_TYPE_DM60_FIREWARE	1
#define UPDATEFILE_TYPE_DM60_DATA		2

//DM60���ò�������
#define NET_DLDVR_SET_ALLSYSCFG_DM60			0 //��������ϵͳ��������ӦSYSTEMCFG_DM60�ṹ��
#define NET_DLDVR_SET_REVISEPARA_DM60			1 //���ò�������ϵ��
#define NET_DLDVR_SET_REVISETEMP_DM60			2 //���ò��������¶�(��λ��)
#define NET_DLDVR_SET_AIMDISTANCE_DM60			3 //���þ��룬����Ϊ��λ
#define NET_DLDVR_SET_AIMHIMIDITY_DM60			4 //����ʪ��
#define NET_DLDVR_SET_SURROUNDTEMP_DM60			5 //���û����¶�
#define NET_DLDVR_SET_MEASURETEMPCLASS_DM60		6 //���þ�ͷѡ�񼴲��µ�λ
#define NET_DLDVR_SET_AREATYPE_DM60				7 //��������������ͣ�������ƽ��
#define NET_DLDVR_SET_ALARMENABLE_DM60			8 //���ñ���ʹ��
#define NET_DLDVR_SET_ALARMTEMP_DM60			9 //���ñ����¶�
#define NET_DLDVR_SET_ALARMCOLOR_DM60			10//���ñ���ɫ
#define NET_DLDVR_SET_LENSID_DM60				11//���þ�ͷѡ�񼴲��µ�λ�����ں���ͬMeasureTempClass
#define NET_DLDVR_SET_AUTOSAVETIME_DM60			12//�����Զ�������ʱ�䣬����ʱû��
#define NET_DLDVR_SET_AUTOZEROTIME_DM60			13//�����Զ�����ʱ����
#define NET_DLDVR_SET_REFETEMPTYPE_DM60			14//���òο��¶�����0�޲ο����£���
#define NET_DLDVR_SET_REFETEMPVALUE_DM60		15//���òο��¶�ֵ����ѡ��ο�����Ϊ�ο�ʱ�õ�
#define NET_DLDVR_SET_COLORRULED_DM60			16//����ɫ��ѡ����SCR����ͬ��������ֵ����ɫ�꣬�����ı�ɫ��ķ����˳��
#define NET_DLDVR_SET_UPCOLORID_DM60			17//��������ɫ��
#define NET_DLDVR_SET_DOWNCOLORID_DM60			18//��������ɫ��
#define NET_DLDVR_SET_ISOTHERMCOLORID_DM60		19//���õ���ɫ��
#define NET_DLDVR_SET_ISOTHERMTEMP_DM60			20//���õ����¶�
#define NET_DLDVR_SET_ISOTHERMHIGHT_DM60		21//���õ��¸߶�
#define NET_DLDVR_SET_SHOWCOLORRULE_DM60		22//�����Ƿ���ʾɫ��
#define NET_DLDVR_SET_SHOWDATA_DM60				23//�����Ƿ���ʾ����
#define NET_DLDVR_SET_AVGIMAGECOUNT_DM60		24//����ͼ��ƽ������������û��
#define NET_DLDVR_SET_SHOWAREACURSOR_DM60		25//������ʾ������ʹ��
#define NET_DLDVR_SET_LANGUAGETYPE_DM60			26//������������

#define NET_DLDVR_SET_VIDEOOUTTYPE_DM60			28//������Ƶ�����ʽ0:PAL;1:
#define NET_DLDVR_SET_LASERENABLE_DM60			29//���ü��⿪������
#define NET_DLDVR_SET_MEASURETEMPUNIT_DM60		30//�����¶ȵ�λ��0:��;1�H;2K;
#define NET_DLDVR_SET_TRANSMENU_DM60			31//���ò˵��Ƿ�͸��
#define NET_DLDVR_SET_CLOSELEDTIME_DM60			32//���ùر���Ļʱ��
#define NET_DLDVR_SET_CLOSEPOWERTIME_DM60		33//���ùرյ�Դʱ��
#define NET_DLDVR_SET_TEMPDISPLAY_DM60			34//�����¶��Ƿ���ʾYes/No
#define NET_DLDVR_SET_STEERSTARTPOS_DM60		35//���ö����ʼλ��,�ǲ���Ӧ���������ʾ��
#define NET_DLDVR_SET_STEERENDPOS_DM60			36//���ö������λ�ã��ǲ���Ӧ���������ʾ��
#define NET_DLDVR_SET_DIMFITERLEVEL_DM60		37//����˥��Ƭֵ
#define NET_DLDVR_SET_IMAGEMODE_DM60			38//����ͼ��ģʽ

//�ص�����Ϣ����
#define COMM_ALARM						0x1100	//������Ϣ ��Ӧ�ṹ NET_DLDVR_ALARMINFO
#define COMM_ALARM_EX					0x1101	//600���͵ı�����Ϣ ��Ӧ�ṹ NET_DLDVR_ALARMINFO_600
#define COMM_ALARM_NAME					0x1102	//������Ϣ ��Ӧ�ṹNET_DLDVR_ALARMINFO_USERNAME�������û�����Ϣ,2010-0901 add��
#define	COMM_TRADEINFO					0x1500 //ATMDVR�����ϴ�������Ϣ
#define SERIAL_NUMBER					0x1600	//DVR�ϱ������к�,2008-03-12
#define DISKCHANNEL_STATE				0x1700 //������ʱ�ϴ�Ӳ��״̬��ͨ��¼��״̬��Ϣ
#define RVS_INFO						0x1800	//IPCamera�ϴ���RVS��Ϣ,2009-05-15 add
#define EXCEPTION_NOTIFY				0X1900 //�����쳣���ߵ���Ϣ����Ӧ�ṹ NET_DLDVR_EXCEPTION ��Ӧ����֪ͨ��Ϣ
#define DM_TEMP							0x2000	//DM60���͵�ʵʱ������Ϣ����Ӧ�ṹNET_DLDVR_DMTEMP
#define DM_TEMP_EX						0x2001	//DM60���͵�ʵʱ������Ϣ����Ӧ�ṹNET_DLDVR_DMTEMP_EX
#define DMTEMP_ALARM					0x2010	//DM60���͵��¶ȸ澯��Ϣ����Ӧ�ṹNET_DLDVR_DMTEMP_ALARM
#define DM_ANALYS_ALARM					0x2011	//DM60���͵����ܷ����澯��Ϣ����Ӧ�ṹNET_DLDVR_DMANALYS_ALARM
#define	PLAYBACK_OVER					0x2020	//�طŽ�������Ӧ�ṹNET_DLDVR_EXCEPTION����NET_DLDVR_EXCEPTION�е�uMsg��Ӧ����֪ͨ��Ϣ��
#define RESOLUTION_CHANGE				0x2021	//�ֱ��ʸı䣬��Ӧ�ṹNET_DLDVR_EXCEPTION
#define VIDEOFORMAT_CHANGE				0x2022	//��Ƶ��ʽ�ı䣬��Ӧ�ṹNET_DLDVR_EXCEPTION
#define CAPTURE_INFRARED_FRAMENUM 		0x2023	//ԭʼ���ݲɼ���Ϣ����Ӧ�ṹNET_DLDVR_INFRAREDFRAME


//��Ϣ��ʽ
//�쳣����
//SDK֪ͨ��Ϣ 2008-09-01 add
//����Ԥ���������֪ͨ
#define WM_DLDVR_NET_EXCEPTION_NOTIFY		(WM_APP + 800)
//	wParam : ��������ľ����
//	lParam : 0

//�طŽ���֪ͨ��Ϣ
#define WM_DLDVR_PLAYBACK_OVER_NOTIFY		(WM_APP + 801)
//	wParam : the handle of player
//	lParam : 0	

//�Խ�����֪ͨ
#define WM_DLDVR_TALKER_EXCEPTION_NOTIFY	(WM_APP + 802)
//	wParam : ��������ľ����
//	lParam : 0

//�û��ǳ���Ϣ,������ʧȥ����
#define WM_DLDVR_LOGOUT_NOTIFY				(WM_APP + 803)
//	wParam : �ǳ����û�ID
//	lParam : 0

//���ӻ�ط�ʱʱ�ֱ��ʷ����ı��֪ͨ��Ϣ
//���յ�����Ϣʱ�������ͨ������¼��������ȹر�¼������¿�ʼ¼�񣬷���ᵼ��¼���޷���������
#define WM_DLDVR_RESOLUTION_CHANGE_NOTIFY		(WM_APP + 804)
//	wParam : the handle of player
//	lParam : 

//���ӻ�ط�ʱʱ��Ƶ��ʽ�����ı��֪ͨ��Ϣ
//���յ�����Ϣʱ�������ͨ������¼��������ȹر�¼������¿�ʼ¼�񣬷���ᵼ��¼���޷���������
#define WM_DLDVR_VIDEOFORMAT_CHANGE_NOTIFY	(WM_APP + 805)
//	wParam : the handle of player
//	lParam : 

#define DL_NAME_LEN 							32
#define SERIALNO_LEN 						48
#define MACADDR_LEN 						6
#define MAX_ETHERNET 						2
#define PATHNAME_LEN 						128
#define PASSWD_LEN 							16
#define MAX_CHANNUM 						16
#define MAX_ALARMOUT 						4
#define MAX_TIMESEGMENT						4
#define MAX_PRESET							128
#define MAX_DAYS 							7
#define PHONENUMBER_LEN						32
//#define MAX_DISKNUM 						8
#define MAX_WINDOW 							16
#define MAX_VGA 							1
#define MAX_USERNUM 						16
#define MAX_EXCEPTIONNUM					16
#define MAX_LINK 							6
#define MAX_ALARMIN 						16
#define MAX_VIDEOOUT 						2
#define MAX_NAMELEN							16		//DVR���ص�½��
#define MAX_RIGHT							32		//Ȩ��
#define CARDNUM_LEN 						20
#define MAX_SHELTERNUM						4	//�ڵ�������
#define MAX_DECPOOLNUM						4
#define MAX_DECNUM							4
#define MAX_TRANSPARENTNUM					2
#define MAX_STRINGNUM						4
#define MAX_AUXOUT							4
#define MAX_CHANNUM_EX						32

// ����ӿڶ��� 
#define NET_IF_10M_HALF						1					// 10M ethernet 
#define NET_IF_10M_FULL						2
#define NET_IF_100M_HALF					3					// 100M ethernet 
#define NET_IF_100M_FULL					4
#define NET_IF_AUTO							5

//�豸�ͺ�(DVR����)
#define DVR_C							0
#define DVR_L							1
#define DVR_LII							2
#define DVR_MPS							3 
#define DVR_MPF							4 
#define DVR_MPC							5
#define DVR_DVS							6	//����DVS
#define DVR_ENC_H264					7	//H264������
#define DVR_DEC_H264					8	//H264������
#define DVR_400T						9   //�Ϻ�400Tϵ��
#define DVR_IPCamera_GQ					10  //����IpCameara(MG3500)	
#define DVR_NVR							11
#define DVR_400D						12  //����400Dϵ��
#define DVR_MPT							13   //Dm642ϵ�� MPT,����ͨ��ֻ����HD1�ֱ���
#define DVR_IPCamera_MG3512				14   //����IpCameara	(MG3512)
#define DVR_DEC_MP4						15	 //����C/Lϵ�н�����
#define DVR_CMS							16	 //�������
#define DVR_408T4						17   //408T D1�����ܻ���
#define DVR_HISI32						18	//haisi3520ƽ̨�µ�16·����32·��(3520ƽ̨�µ�600ϵ�л���)
#define DVR_DM60						19	//DM60����
#define DVR_HISI106						20	//3520ƽ̨�µ�106�ͻ�����ͼ��ߴ�ϴ󣬹̶�Ϊ1280*1024
#define DVR_400D2						21  //����400D2ϵ��,��400D֮���ϵͳ����������ͬ
#define DVR_716T						22 //2010-10-25 add�� 14CIF+2D1��3520���͡���700����(ͬ��600��3520оƬ��
#define DVR_IPCamera_MG3515				23   //����IpCameara	(MG3515оƬ�� ��3512���͵���������3512����Ƶ�����б���룬3515�Ľ��б���봦��)
#define DVR_401K						24   //401K����(����Ӳ��¼��,�������ú�400D||����������ͬ)
#define DVR_400DX						25	//DVR400Dϵ�У�������һ���½��棬Ŀǰ�ݶ�ΪDVR400DX����4/8/16·
#define DVR_404D4						26	//����DVR404D���ͣ�����ȫD1ѡ�Ŀǰ�ݶ�����DVR404D4

//��Ƶ���뷽ʽ
#define   VIDEO_ENC_MPEG4    0
#define   VIDEO_ENC_H264     1
#define   VIDEO_ENC_DVS      2
#define   VIDEO_ENC_HI		 3 //H.264(��˼)
#define   VIDEO_ENC_IPCamera 4 //IPCamera(MG3500)

//¼������
#define   TIMER_RECORD		0 //��ʱ¼��
#define   MONITION_RECORD   1 //�ƶ����	
#define   ALARM_RECORD      2 //��������
#define   CMD_RECORD		3 //�����
#define   MANUAL_RECORD		4 //�ֶ�¼�� 

#define REAL_PLAY		0	//2007-11-06,ʵʱ����
#define JPEG_PLAY		1	//2007-11-06, JPEG����

#define DEVICE_ID_LENGTH	128

//DM60���͵���������ֵ����ΪNET_DLDVR_SetDMCommand_DM60()������command����
#define NET_DLDVR_CLEARALLPOINT		1	//������е�
#define NET_DLDVR_CLEARALLLINE		2	//���������
#define NET_DLDVR_CLEARALLAREA		3	//�����������
#define NET_DLDVR_ZEROADJUST		4	//�������
#define NET_DLDVR_KEYBOARD			5	//�������Value1�д�ż�����
#define NET_DLDVR_SETFOCUSPOS		6	//���ý���Ԥ��λ
#define NET_DLDVR_CALLFOCUSPOS		7	//���ý���Ԥ��λ
#define NET_DLDVR_FOCUSSTOP			8	//�۽�ֹͣ
#define NET_DLDVR_FOCUSSTEPNEAR		9	//��ǰ�����۽�
#define NET_DLDVR_FOCUSSTEPFAR		10	//��󵥲��۽�
#define NET_DLDVR_FOCUSAUTO			11	//�Զ��۽�
#define NET_DLDVR_FOCUSSTEPS		12	//���������۽���������ǰ���������
#define NET_DLDVR_FOCUSSTEPSNEAR	13	//��ǰ���������۽���ֱ��FocusStop
#define NET_DLDVR_FOCUSSTEPSFAR		14	//������������۽���ֱ��FocusStop
#define NET_DLDVR_VOLTAGELEVEL		15	//���õ�ƽ��Value1������+1, ��ʾ����1�� -1, ��ʾ��С1
#define NET_DLDVR_UPCOLORTEMP		16	//����ɫ���¶����ޣ�Value1ͬVoltageLevel
#define NET_DLDVR_DOWNCOLORTEMP		17	//����ɫ���¶����ޣ�Value1ͬVoltageLevel
#define	NET_DLDVR_IMAGEMODE			18	//����ͼ��ģʽ��0-�ֶ� 1-�Զ�

#pragma pack(1)
typedef struct  
{
	BYTE sSerialNumber[SERIALNO_LEN];	//���к�
	BYTE byAlarmInPortNum;				//DVR�����������
	BYTE byAlarmOutPortNum;				//DVR�����������
	BYTE byDiskNum;						//DVR Ӳ�̸���
	BYTE byDVRType;						/*DVR����
										#define DVR_C							0
										#define DVR_L							1
										#define DVR_LII							2
										#define DVR_MPS							3 
										#define DVR_MPF							4 
										#define DVR_MPC							5
										#define DVR_HI3510						6
										#define DVR_ENC							7	//������
										#define DVR_DEC							8	//������
										#define DVR_HI3511						9   //
										#define IPCamera_GQ						10  //����IpCameara	
										#define NVR								11
										#define DVR400D							12
										#define DVR_MPT							13   //Dm642ϵ�� MPT,����ͨ��ֻ����HD1�ֱ���
										#define DVR_IPCamera_MG3512				14   //����IpCameara	(MG3512)
										#define DVR_DEC_MP4						15	 //����C/Lϵ�н�����
										#define DVR_CMS							16	 //�������
										#define DVR_408T4						17   //408T D1�����ܻ���
										#define DVR_HISI32						18
										#define DVR_DM60						19	//DM60����
										#define DVR_106							20	//3520ϵ���µ�106�ͻ�����ͼ��ߴ�ϴ�1280*1024
										#define DVR_400D2						21  //����400D2ϵ��,��400D֮���ϵͳ����������ͬ
										#define DVR_716T						22 //2010-10-25 add�� 14CIF+2D1��3520���͡���700����(ͬ��600��3520оƬ��
										#define DVR_IPCamera_MG3515				23   //����IpCameara	(MG3515оƬ�� ��3512���͵���������3512����Ƶ�����б���룬3515�Ľ��б���봦��)
	*/
	BYTE byChanNum;						//DVR ͨ������
	BYTE byStartChan;					//IPCͨ��������2010-04-27 modifty
}NET_DLDVR_DEVICEINFO, *LPNET_DLDVR_DEVICEINFO;


typedef struct
{
	LONG lChannel;//ͨ����,��0��ʼ��600������4��IPCͨ����ͨ���Ŵ�0x100+0->0x100+3��
	LONG lLinkMode;//���λ(31)Ϊ0��ʾ��������Ϊ1��ʾ������; ��30λ��ʾ�Ƿ���Ԥ¼ͼ��0-���ǣ�1-�ǣ�0��29λ��ʾ�������ӷ�ʽ: 0��TCP��ʽ,1��UDP��ʽ,2���ಥ��ʽ,3 - RTP��ʽ��4-����Ƶ�ֿ�(TCP)
					//����IPCamera����ʱ�����λ(31)Ϊ0-MajorAV��ʽ��1-MinorAV��ʽ��2-Raw��ʽ��3-YUV��ʽ��Raw��YUVֻ����ԭʼ���ݣ�����ʾͼ��
	HWND hPlayWnd;//���Ŵ��ڵľ��,ΪNULL��ʾ������ͼ��
	CHAR* sMultiCastIP;//�ಥ���ַ
}NET_DLDVR_CLIENTINFO,*LPNET_DLDVR_CLIENTINFO;


typedef struct
{
	DWORD dwYear;		//��
	DWORD dwMonth;		//��
	DWORD dwDay;		//��
	DWORD dwHour;		//ʱ
	DWORD dwMinute;		//��
	DWORD dwSecond;		//��
}NET_DLDVR_TIME,*LPNET_DLDVR_TIME;

typedef struct
{
	//��ʼʱ��
    BYTE byStartHour;
	BYTE byStartMin;
	//����ʱ��
	BYTE byStopHour;
	BYTE byStopMin;
}NET_DLDVR_SCHEDTIME,*LPNET_DLDVR_SCHEDTIME;

//����ʽ
#define NOACTION			0x0				//����Ӧ
#define WARNONMONITOR		0x1				//�������Ͼ���
#define WARNONAUDIOOUT		0x2				//��������
#define UPTOCENTER			0x4				//�ϴ�����
#define TRIGGERALARMOUT		0x8				//�����������

typedef struct
{
	DWORD	dwHandleType;				//����ʽ,����ʽ��"��"���
										//0x00: ����Ӧ
										//0x01: �������Ͼ���
										//0x02: ��������
										//0x04: �ϴ�����
										//0x08: �����������
	BYTE byRelAlarmOut[MAX_ALARMOUT];	//�������������ͨ��,�������������,Ϊ1��ʾ���������
}NET_DLDVR_HANDLEEXCEPTION;

//DVR�豸����
typedef struct
{
	DWORD dwSize;
	BYTE sDVRName[DL_NAME_LEN];		//DVR����
	DWORD dwDVRID;					//DVR ID,����ң����
	DWORD dwRecycleRecord;			//�Ƿ�ѭ��¼��,0:����; 1:��
//���²��ܸ���
	BYTE sSerialNumber[SERIALNO_LEN];	//���к�
	DWORD dwSoftwareVersion;			//����汾��,��16λ�����汾,��16λ�Ǵΰ汾
	DWORD dwSoftwareBuildDate;			//�����������,0xYYYYMMDD
	DWORD dwDSPSoftwareVersion;			//DSP����汾,��16λ�����汾,��16λ�Ǵΰ汾
	DWORD dwDSPSoftwareBuildDate;		// DSP�����������,0xYYYYMMDD
	DWORD dwPanelVersion;				// ǰ���汾,��16λ�����汾,��16λ�Ǵΰ汾
	DWORD dwHardwareVersion;			// Ӳ���汾,��16λ�����汾,��16λ�Ǵΰ汾
	BYTE byAlarmInPortNum;				//DVR�����������
	BYTE byAlarmOutPortNum;				//DVR�����������
	BYTE byRS232Num;					//DVR 232���ڸ���
	BYTE byRS485Num;					//DVR 485���ڸ���
	BYTE byNetworkPortNum;				//����ڸ���
	BYTE byDiskCtrlNum;					//DVR Ӳ�̿���������
	BYTE byDiskNum;						//DVR Ӳ�̸���
	BYTE byDVRType;						//DVR����, 
	BYTE byChanNum;						//DVR ͨ������
	BYTE byStartChan;					//��ʼͨ����,����DVS-1,DVR - 1
	BYTE byDecordChans;					//DVR ����·��
	BYTE byVGANum;						//VGA�ڵĸ���
	BYTE byUSBNum;						//USB�ڵĸ���
	CHAR reservedData[3];				//���� 
}NET_DLDVR_DEVICECFG,*LPNET_DLDVR_DEVICECFG;

typedef struct
{
	WORD	wDiskCount;			//Ӳ�̸���
	WORD	wDiskState[8];			//Ӳ��״̬,1---����,2---������,3������
	WORD	wDiskAddr[8];		//Ӳ�̵�ַ,��8λ��Ӳ�̵�����ַ(0-3),��8λ��Ӳ�̵Ĵӵ�ַ(0��1)
	DWORD	dwTotalSpace[8];	//Ӳ���ܵĿռ�(��λM)
	DWORD	dwFreeSpace[8];		//Ӳ��ʣ��ռ�
	
	WORD	wChannelCount;		//ͨ������
	WORD	wChannelState[16];	//ͨ����Ϣ����8λ��ʾ�Ƿ�����Ƶ�źţ�0---��Ƶ�źŶ�ʧ��1---���ź�
										//��8λ��ʾ�Ƿ���¼��0---����¼��1---��¼��
	DWORD	dwBiteRate[16];	//����
	
	DWORD	dwAlarmInStatus;
	WORD	wAlarmOutStatus;
}NET_DLDVR_DISKCHANNELSTATE;

typedef struct 
{
	CHAR sDVRIP[16];					//DVR IP��ַ
	CHAR sDVRIPMask[16];				// DVR IP��ַ����
	DWORD dwNetInterface;				//����ӿ� 1-10MBase-T 2-10MBase-Tȫ˫�� 3-100MBase-TX 4-100Mȫ˫�� 5-10M/100M����Ӧ
	WORD wDVRPort;						//�˿ں�
	BYTE byMACAddr[MACADDR_LEN];		//�������������ַ
}NET_DLDVR_ETHERNET;

//�������ýṹ
typedef struct
{
	DWORD dwSize;
	NET_DLDVR_ETHERNET struEtherNet[MAX_ETHERNET];		//��̫����
	CHAR sManageHostIP[16];								//Զ�̹���������ַ
	WORD wManageHostPort;								//Զ�̹��������˿ں�
	CHAR sDNSIP[16];									//DNS��������ַ  
	CHAR sMultiCastIP[16];								//�ಥ���ַ
	CHAR sGatewayIP[16];       							//���ص�ַ 
	CHAR sNFSIP[16];									//NAS����IP��ַ	
	BYTE sNFSDirectory[PATHNAME_LEN];					//NASĿ¼
	DWORD dwPPPOE;										//0-������,1-����
	BYTE sPPPoEUser[DL_NAME_LEN];							//PPPoE�û���
	CHAR sPPPoEPassword[PASSWD_LEN];					//PPPoE����
	CHAR sPPPoEIP[16];									//PPPoE IP��ַ(ֻ��)
	WORD wHttpPort;										//HTTP�˿ں�
}NET_DLDVR_NETCFG,*LPNET_DLDVR_NETCFG; 

//ͨ��ͼ��ṹ
//�ƶ����
typedef struct
{
	BYTE byMotionScope[18][22];	//�������,����22*18��С���,Ϊ1��ʾ�ú�����ƶ��������,0-��ʾ����
	BYTE byMotionSensitive;		//�ƶ����������, 0 - 5,Խ��Խ����,0xff�ر�
	BYTE byEnableHandleMotion;	// �Ƿ����ƶ����
	NET_DLDVR_HANDLEEXCEPTION strMotionHandleType;	// ����ʽ
	NET_DLDVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];//����ʱ��
	BYTE byRelRecordChan[MAX_CHANNUM]; //����������¼��ͨ��,Ϊ1��ʾ������ͨ��	
}NET_DLDVR_MOTION,*LPNET_DLDVR_MOTION;

//�ڵ���������Ϊ704*576
//2010-06-25�޸ģ�DM60�����ڵ���������Ϊ640*480
typedef struct
{
	DWORD dwEnableHideAlarm;			// �Ƿ������ڵ����� ,0-��,1-�������� 2-�������� 3-��������
	WORD wHideAlarmAreaTopLeftX;			// �ڵ������x���� 
	WORD wHideAlarmAreaTopLeftY;			// �ڵ������y���� 
	WORD wHideAlarmAreaWidth;			// �ڵ�����Ŀ� 
	WORD wHideAlarmAreaHeight;			//�ڵ�����ĸ�*
	NET_DLDVR_HANDLEEXCEPTION strHideAlarmHandleType;	// ����ʽ 	
	NET_DLDVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];//����ʱ��
}NET_DLDVR_HIDEALARM,*LPNET_DLDVR_HIDEALARM;

//�źŶ�ʧ����
typedef struct
{
	BYTE byEnableHandleVILost;	// �Ƿ����źŶ�ʧ���� 
	NET_DLDVR_HANDLEEXCEPTION strVILostHandleType;	// ����ʽ 	
	NET_DLDVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];//����ʱ��
}NET_DLDVR_VILOST,*LPNET_DLDVR_VILOST;

typedef struct
{
	DWORD dwSize;
	BYTE sChanName[DL_NAME_LEN];
	DWORD dwVideoFormat;	// ֻ������Ƶ��ʽ 1-NTSC 2-PAL*/
	BYTE byBrightness;  	//����,0-255*/
	BYTE byContrast;    	//�Աȶ�,0-255*/	
	BYTE bySaturation;  	//���Ͷ�,0-255 
	BYTE byHue;    			//ɫ��,0-255*/	
	//��ʾͨ����
	DWORD dwShowChanName; // Ԥ����ͼ�����Ƿ���ʾͨ������,0-����ʾ,1-��ʾ ����Ϊ704*576 
	WORD wShowNameTopLeftX;				// ͨ��������ʾλ�õ�x���� 
	WORD wShowNameTopLeftY;				// ͨ��������ʾλ�õ�y���� 
	//�źŶ�ʧ����
	NET_DLDVR_VILOST struVILost;
	//�ƶ����
	NET_DLDVR_MOTION struMotion;	
	//�ڵ�����
	NET_DLDVR_HIDEALARM struHideAlarm;
	//�ڵ�
	DWORD dwEnableHide;		// �Ƿ������ڵ� ,0-��,1-�� ����Ϊ704*576
	////2010-06-25�޸ģ�DM60�����ڵ���������Ϊ640*480
	WORD wHideAreaTopLeftX;				// �ڵ������x���� 
	WORD wHideAreaTopLeftY;				// �ڵ������y���� 
	WORD wHideAreaWidth;				// �ڵ�����Ŀ� 
	WORD wHideAreaHeight;				//�ڵ�����ĸ�
	//OSD
	DWORD dwShowOsd;	// Ԥ����ͼ�����Ƿ���ʾOSD,0-����ʾ,1-��ʾ
	WORD wOSDTopLeftX;				// OSD��x���� 
	WORD wOSDTopLeftY;				// OSD��y���� 
	BYTE byOSDType;					// OSD����(��Ҫ�������ո�ʽ) 
							// 0: XXXX-XX-XX ������ 
							// 1: XX-XX-XXXX ������ 
							// 2: XXXX��XX��XX�� 
							// 3: XX��XX��XXXX�� 
	BYTE byDispWeek;				// �Ƿ���ʾ���� 	
	BYTE byOSDAttrib;				// OSD����:͸������˸ 
									// 1: ͸��,��˸ 	
									// 2: ͸��,����˸ 
									// 3: ��˸,��͸�� 
									// 4: ��͸��,����˸ 
}NET_DLDVR_PICCFG,*LPNET_DLDVR_PICCFG;

typedef struct{
	WORD wHideAreaTopLeftX;				// �ڵ������x���� 
	WORD wHideAreaTopLeftY;				// �ڵ������y���� 
	WORD wHideAreaWidth;				// �ڵ�����Ŀ� 
	WORD wHideAreaHeight;				//�ڵ�����ĸ�
}NET_DLDVR_SHELTER,*LPNET_DLDVR_SHELTER;

//SDK_V14
typedef struct
{
	DWORD dwSize;
	BYTE sChanName[DL_NAME_LEN];
	DWORD dwVideoFormat;	// ֻ�� ��Ƶ��ʽ 1-NTSC 2-PAL*/
	BYTE byBrightness;  	//����,0-255*/
	BYTE byContrast;    	//�Աȶ�,0-255*/	
	BYTE bySaturation;  	//���Ͷ�,0-255 
	BYTE byHue;    			//ɫ��,0-255*/	
	//��ʾͨ����
	DWORD dwShowChanName; // Ԥ����ͼ�����Ƿ���ʾͨ������,0-����ʾ,1-��ʾ �����С704*576
	WORD wShowNameTopLeftX;				// ͨ��������ʾλ�õ�x���� 
	WORD wShowNameTopLeftY;				// ͨ��������ʾλ�õ�y���� 
	//�źŶ�ʧ����
	NET_DLDVR_VILOST struVILost;
	//�ƶ����
	NET_DLDVR_MOTION struMotion;	
	//�ڵ�����
	NET_DLDVR_HIDEALARM struHideAlarm;
	//�ڵ�  �����С704*576
	//2010-06-25�޸ģ�DM60�����ڵ���������Ϊ640*480
	DWORD dwEnableHide;		// �Ƿ������ڵ� ,0-��,1-��
	NET_DLDVR_SHELTER struShelter[MAX_SHELTERNUM]; 
	//OSD
	DWORD dwShowOsd;// Ԥ����ͼ�����Ƿ���ʾOSD,0-����ʾ,1-��ʾ �����С704*576
	WORD wOSDTopLeftX;				// OSD��x���� 
	WORD wOSDTopLeftY;				// OSD��y���� 
	BYTE byOSDType;					// OSD����(��Ҫ�������ո�ʽ) 
	// 0: XXXX-XX-XX ������ 
	// 1: XX-XX-XXXX ������ 
	// 2: XXXX��XX��XX�� 
	// 3: XX��XX��XXXX�� 
	BYTE byDispWeek;				// �Ƿ���ʾ���� 	
	BYTE byOSDAttrib;				// OSD����:͸������˸ 
	// 1: ͸��,��˸ 	
	// 2: ͸��,����˸ 
	// 3: ��˸,��͸�� 
	// 4: ��͸��,����˸ 
}NET_DLDVR_PICCFG_EX,*LPNET_DLDVR_PICCFG_EX;

//ѹ������
typedef struct
{
	BYTE byStreamType;		//��������0-��Ƶ��,1-������
	BYTE byResolution;  	//�ֱ���0-DCIF 1-CIF, 2-QCIF, 3-4CIF, 4-2CIF
	BYTE byBitrateType;		//��������0:�����ʣ�1:������
	BYTE  byPicQuality;		//ͼ������ 0-��� 1-�κ� 2-�Ϻ� 3-һ�� 4-�ϲ� 5-��	
	DWORD dwVideoBitrate; 	//��Ƶ���� 0-���� 1-���� 2-32K 3-48k 4-64K 5-80K 6-96K 7-128K 8-160k 9-192K 10-224K 11-256K 12-320K
				// 13-384K 14-448K 15-512K 16-640K 17-768K 18-896K 19-1024K 20-1280K 21-1536K 22-1792K 23-2048K
				//���λ(31λ)�ó�1��ʾ���Զ�������, 0-30λ��ʾ����ֵ(MIN-16K MAX-8192K)��
	DWORD dwVideoFrameRate;	//֡�� 0-ȫ��; 1-1/16; 2-1/8; 3-1/4; 4-1/2; 5-1; 6-2; 7-4; 8-6; 9-8; 10-10; 11-12; 12-16; 13-20;
}NET_DLDVR_COMPRESSION_INFO,*LPNET_DLDVR_COMPRESSION_INFO;

typedef struct
{
	DWORD dwSize;
	NET_DLDVR_COMPRESSION_INFO struRecordPara; //¼��
	NET_DLDVR_COMPRESSION_INFO struNetPara;	//����
}NET_DLDVR_COMPRESSIONCFG,*LPNET_DLDVR_COMPRESSIONCFG;

//¼��
typedef struct
{
	NET_DLDVR_SCHEDTIME struRecordTime;
	BYTE byRecordType;	//0:��ʱ¼��1:�ƶ���⣬2:����¼�� 3:�����, 4: �ֶ�¼��
	CHAR reservedData[3];
}NET_DLDVR_RECORDSCHED,*LPNET_DLDVR_RECORDSCHED;

typedef struct 
{
	WORD wAllDayRecord;				// �Ƿ�ȫ��¼�� 
	BYTE byRecordType;				// ¼������ 0:��ʱ¼��1:�ƶ���⣬2:����¼�� 3:�����, 4: �ֶ�¼��
	CHAR reservedData;
}NET_DLDVR_RECORDDAY;

typedef struct 
{
	DWORD dwSize;
	DWORD dwRecord;  //�Ƿ�¼�� 0-�� 1-��
	NET_DLDVR_RECORDDAY struRecAllDay[MAX_DAYS];
	NET_DLDVR_RECORDSCHED struRecordSched[MAX_DAYS][MAX_TIMESEGMENT];
	DWORD dwRecordTime;	// ¼��ʱ�䳤�� 
	DWORD dwPreRecordTime;	// Ԥ¼ʱ�� 0-��Ԥ¼ 1-5�� 2-10�� 3-15�� 4-20�� 5-25�� 6-30�� 7-0xffffffff(������Ԥ¼) 
}NET_DLDVR_RECORD,*LPNET_DLDVR_RECORD;

// PTZ type
#define NET_DLDVR_PELCO_P1	0
#define NET_DLDVR_PELCO_P2	1
#define NET_DLDVR_PELCO_D		2
#define NET_DLDVR_DL_0001		3
#define NET_DLDVR_FASTRAX		4	
#define NET_DLDVR_PANASONIC	5
#define NET_DLDVR_ELEC		6
#define NET_DLDVR_SAMSUNG		7
#define NET_DLDVR_KATATEL		8
#define NET_DLDVR_VC			9
#define NET_DLDVR_T3609HD		10
#define NET_DLDVR_LILIN		11
#define NET_DLDVR_PELCO9760	12
#define NET_DLDVR_KRE301		13
#define NET_DLDVR_PIH_1016	14
#define NET_DLDVR_PD_CONST	15
#define NET_DLDVR_PD_NW		16
#define NET_DLDVR_JC4116		17
#define NET_DLDVR_SONY		18
#define NET_DLDVR_YAAN		19
#define NET_DLDVR_ENKEL		20
#define NET_DLDVR_PLD			21
#define NET_DLDVR_P3			22
#define NET_DLDVR_W110		23
#define NET_DLDVR_BFL			24
#define NET_DLDVR_SUNELL		25
#define NET_DLDVR_KTD			26
#define NET_DLDVR_HD600		27

//��̨������
typedef struct
{
	DWORD dwSize;
	DWORD dwBaudRate;//������(bps)��0��1200��1��2400��2��4800��3��9600��4��19200�� 5��38400;;
	BYTE byDataBit;// �����м�λ 0��6λ��1��7λ��2��8λ;
	BYTE byStopBit;// ֹͣλ 0��1λ��1��2λ;
	BYTE byParity;// У�� 0����У�飬1����У�飬2��żУ��;
	BYTE byFlowcontrol;// 0���ޣ�1��������,2-Ӳ����
	WORD wDecoderType;/*����������,
							0-PELCO-P1
							1-PELCO-P2
							2-PELCO-D
							3-DL-0001
							4-FASTRAX
							5-PANASONIC
							6-ELEC
							7-SAMSUNG
							8-KATATEL
							9-VC
							10-T3609HD
							11-LILIN
							12-PELCO9760
							13-KRE301
							14-PIH-1016
							15-PD-CONST
							16-PD-NW
							17-JC4116
							18-SONY
							19-YAAN
							20-ENKEL
							21-PLD
							22-P3
							23-W110
							24-BFL*/
	WORD wDecoderAddress;	//��������ַ:0 - 255*/
	BYTE bySetPreset[MAX_PRESET];		// Ԥ�õ��Ƿ�����,0-û������,1-����
	BYTE bySetCruise[MAX_PRESET];		// Ѳ���Ƿ�����: 0-û������,1-���� 
	BYTE bySetTrack[MAX_PRESET];		// �켣�Ƿ�����,0-û������,1-����
}NET_DLDVR_DECODERCFG,*LPNET_DLDVR_DECODERCFG;

//RS232����
typedef struct
{
	CHAR sRemoteIP[16];            //Զ��IP��ַ
	CHAR sLocalIP[16];             //����IP��ַ
	CHAR sLocalIPMask[16];         //����IP��ַ����
	BYTE sUsername[DL_NAME_LEN];		// �û��� 
	BYTE sPassword[PASSWD_LEN];		// ���� 
	BYTE byPPPMode;            //PPPģʽ, 0��������1������	
	BYTE byRedial;            //�Ƿ�ز� ��0-��,1-��
	BYTE byRedialMode;        //�ز�ģʽ,0-�ɲ�����ָ��,1-Ԥ�ûز�����
	BYTE byDataEncrypt;	     //���ݼ���,0-��,1-��
	DWORD dwMTU;              //MTU
	CHAR sTelephoneNumber[PHONENUMBER_LEN];   //�绰����
}NET_DLDVR_PPPCFG,*LPNET_DLDVR_PPPCFG;

typedef struct
{
	DWORD dwSize;
	DWORD dwBaudRate;//������(bps)��0��1200��1��2400��2��4800��3��9600��4��19200�� 5��38400;
	BYTE byDataBit;// �����м�λ 0��6λ��1��7λ��2��8λ;
	BYTE byStopBit;// ֹͣλ 0��1λ��1��2λ;
	BYTE byParity;// У�� 0����У�飬1����У�飬2��żУ��;
	BYTE byFlowcontrol;// 0���ޣ�1��������,2-Ӳ����
	DWORD dwWorkMode;// ����ģʽ��0��խ������(232��������PPP����)��1������̨(232�������ڲ�������)��2��͸��ͨ��
	NET_DLDVR_PPPCFG struPPPConfig;
}NET_DLDVR_RS232CFG,*LPNET_DLDVR_RS232CFG;

//��������
typedef struct
{
	DWORD dwSize;
	BYTE sAlarmInName[DL_NAME_LEN];	// ���� 
	BYTE byAlarmType;	//����������,0������,1������
	BYTE byAlarmInHandle;	// �Ƿ��� 
	NET_DLDVR_HANDLEEXCEPTION struAlarmHandleType;	// ����ʽ 
	NET_DLDVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT];//����ʱ��
	BYTE byRelRecordChan[MAX_CHANNUM]; //����������¼��ͨ��,Ϊ1��ʾ������ͨ��
	BYTE byEnablePreset[MAX_CHANNUM];		// �Ƿ����Ԥ�õ� 
	BYTE byPresetNo[MAX_CHANNUM];			// ���õ���̨Ԥ�õ����,һ������������Ե��ö��ͨ������̨Ԥ�õ�, 0xff��ʾ������Ԥ�õ㡣
	BYTE byEnableCruise[MAX_CHANNUM];		// �Ƿ����Ѳ�� 
	BYTE byCruiseNo[MAX_CHANNUM];			// Ѳ�� 
	BYTE byEnablePtzTrack[MAX_CHANNUM];		// �Ƿ���ù켣 
	BYTE byPTZTrack[MAX_CHANNUM];			// ���õ���̨�Ĺ켣��� 
}NET_DLDVR_ALARMINCFG,*LPNET_DLDVR_ALARMINCFG;


//2010-10-29 ��������ֵ����
#define ALARMTYPE_SIGNAL_IN			0		//�ź������뱨��	��Ӧ�ṹ NET_DLDVR_ALARMINFO��NET_DLDVR_ALARMINFO_600
#define ALARMTYPE_DISKFULL			1		//Ӳ����			��Ӧ�ṹ NET_DLDVR_ALARMINFO��NET_DLDVR_ALARMINFO_600
#define ALARMTYPE_VIDEOLOST			2	//��Ƶ�źŶ�ʧ			��Ӧ�ṹ NET_DLDVR_ALARMINFO��NET_DLDVR_ALARMINFO_600
#define ALARMTYPE_MOTIONALARM		3	//�ƶ����			��Ӧ�ṹ NET_DLDVR_ALARMINFO��NET_DLDVR_ALARMINFO_600
#define ALARMTYPE_DISK_UNFORMAT		4	//Ӳ��δ��ʽ��			��Ӧ�ṹ NET_DLDVR_ALARMINFO��NET_DLDVR_ALARMINFO_600
#define ALARMTYPE_DISKERROR			5	//Ӳ�̴���			��Ӧ�ṹ NET_DLDVR_ALARMINFO��NET_DLDVR_ALARMINFO_600
#define ALARMTYPE_SHELTERALARM		6	//��Ƶ�ڵ�			��Ӧ�ṹ NET_DLDVR_ALARMINFO��NET_DLDVR_ALARMINFO_600
#define ALARMTYPE_PN_NOT_MATCH		7	//��ʽ��ƥ��			��Ӧ�ṹ NET_DLDVR_ALARMINFO��NET_DLDVR_ALARMINFO_600
#define ALARMTYPE_ILLEGEL_ACCESS	8	//�Ƿ�����				��Ӧ�ṹ NET_DLDVR_ALARMINFO��NET_DLDVR_ALARMINFO_600
#define ALARMTYPE_INTELLEGENCE_TRIPWIRE			10				//����		��Ӧ�ṹ NET_DLDVR_ALARMINFO��NET_DLDVR_ALARMINFO_600
#define ALARMTYPE_INTELLEGENCE_FORBIDDRNZONE	11				//����		��Ӧ�ṹ NET_DLDVR_ALARMINFO��NET_DLDVR_ALARMINFO_600
#define ALARMTYPE_INTELLEGENCE_REMOVAL			12				//���������� ��Ӧ�ṹ NET_DLDVR_ALARMINFO��NET_DLDVR_ALARMINFO_600
#define ALARMTYPE_INTELLEGENCE_GATHER			13				//����       ��Ӧ�ṹ NET_DLDVR_ALARMINFO��NET_DLDVR_ALARMINFO_600
#define ALARMTYPE_INTELLEGENCE_RUSH				14               //���ٱ���	 ��Ӧ�ṹ NET_DLDVR_ALARMINFO��NET_DLDVR_ALARMINFO_600
#define ALARMTYPE_INTELLEGENCE_COUNTER			15				//����ͳ��   ��Ӧ�ṹ NET_DLDVR_ALARMINFO��NET_DLDVR_ALARMINFO_600
#define ALARMTYPE_INTELLEGENCE_HIDE_FACE		16				//����αװ���  ��Ӧ�ṹ NET_DLDVR_ALARMINFO��NET_DLDVR_ALARMINFO_600
#define ALARMTYPE_INTELLEGENCE_OUT_GUARD		17				////�Ѹڼ�⡣600��������   ��Ӧ�ṹ NET_DLDVR_ALARMINFO_600

//�ϴ�������Ϣ
typedef struct
{
	DWORD dwAlarmType;
	DWORD dwAlarmInputNumber;//��������˿�
	DWORD dwAlarmOutputNumber[MAX_ALARMOUT];//��������˿ڶ�Ӧ������˿ڣ���һλΪ1��ʾ��Ӧ��һ�����
	DWORD dwAlarmRelateChannel[MAX_CHANNUM];//��������˿ڶ�Ӧ��¼��ͨ������һλΪ1��ʾ��Ӧ��һ·¼��,dwAlarmRelateChannel[0]��Ӧ��1��ͨ��
	DWORD dwChannel[MAX_CHANNUM];//dwAlarmTypeΪ2��3��10-16ʱ����ʾ�ĸ�ͨ����dwChannel[0]λ��Ӧ��1��ͨ��
	DWORD dwDiskNumber[MAX_DISKNUM];//dwAlarmTypeΪ4ʱ,��ʾ�ĸ�Ӳ��
}NET_DLDVR_ALARMINFO,*LPNET_DLDVR_ALARMINFO;

//�ϴ�������Ϣ,600����ʹ�øýṹ
typedef struct
{
	DWORD dwAlarmType;
	DWORD dwAlarmInputNumber;//��������˿�
	DWORD dwAlarmOutputNumber[MAX_ALARMOUT];//��������˿ڶ�Ӧ������˿ڣ���һλΪ1��ʾ��Ӧ��һ�����
	DWORD dwAlarmRelateChannel[MAX_CHANNUM_EX];//��������˿ڶ�Ӧ��¼��ͨ������һλΪ1��ʾ��Ӧ��һ·¼��,dwAlarmRelateChannel[0]��Ӧ��1��ͨ��
	DWORD dwChannel[MAX_CHANNUM_EX];//dwAlarmTypeΪ2��3��10-16ʱ����ʾ�ĸ�ͨ����dwChannel[0]λ��Ӧ��1��ͨ��
	DWORD dwDiskNumber[MAX_DISKNUM];//dwAlarmTypeΪ4ʱ,��ʾ�ĸ�Ӳ��
}NET_DLDVR_ALARMINFO_600,*LPNET_DLDVR_ALARMINFO_600;

//�ϴ�������Ϣ,���û�����2010-09-01 add
typedef struct
{
	DWORD dwAlarmType;
	DWORD dwAlarmInputNumber;//��������˿�
	DWORD dwAlarmOutputNumber[MAX_ALARMOUT];//��������˿ڶ�Ӧ������˿ڣ���һλΪ1��ʾ��Ӧ��һ�����
	DWORD dwAlarmRelateChannel[MAX_CHANNUM_EX];//��������˿ڶ�Ӧ��¼��ͨ������һλΪ1��ʾ��Ӧ��һ·¼��,dwAlarmRelateChannel[0]��Ӧ��1��ͨ��
	DWORD dwChannel[MAX_CHANNUM_EX];//dwAlarmTypeΪ2��3��10-16ʱ����ʾ�ĸ�ͨ����dwChannel[0]λ��Ӧ��1��ͨ��
	DWORD dwDiskNumber[MAX_DISKNUM];//dwAlarmTypeΪ4ʱ,��ʾ�ĸ�Ӳ��
	BYTE  byUsername[32];	//�û���
}NET_DLDVR_ALARMINFO_USERNAME,*LPNET_DLDVR_ALARMINFO_USERNAME;


//DVR�������
typedef struct
{
	DWORD dwSize;
	BYTE sAlarmOutName[DL_NAME_LEN];	// ���� 
	DWORD dwAlarmOutDelay;	// �������ʱ��(-1Ϊ���ޣ��ֶ��ر�) 
	NET_DLDVR_SCHEDTIME struAlarmOutTime[MAX_DAYS][MAX_TIMESEGMENT];// �����������ʱ��� 				
}NET_DLDVR_ALARMOUTCFG,*LPNET_DLDVR_ALARMOUTCFG;

//DVR����Ԥ������
typedef struct
{
	DWORD dwSize;
	BYTE byPreviewNumber;//Ԥ����Ŀ,0-1����,1-4����,2-9����,3-16����,0xff:�����
	BYTE byEnableAudio;//�Ƿ�����Ԥ��,0-��Ԥ��,1-Ԥ��
	WORD wSwitchTime;//�л�ʱ��,0-���л�,1-5s,2-10s,3-20s,4-60s,5-120s,6-300s
	BYTE bySwitchSeq[MAX_WINDOW];//�л�˳��,���lSwitchSeq[i]Ϊ 0xff��ʾ����
}NET_DLDVR_PREVIEWCFG,*LPNET_DLDVR_PREVIEWCFG;

//DVR��Ƶ���
typedef struct 
{
	WORD wResolution;							// �ֱ��� 
	WORD wFreq;								// ˢ��Ƶ�� 
	DWORD dwBrightness;							// ���� 
}NET_DLDVR_VGAPARA;

typedef struct
{
	WORD wDisplayLogo;						// ��ʾ��Ƶͨ���� 
	WORD wDisplayOsd;						// ��ʾʱ�� 
}NET_DLDVR_MATRIXPARA;

typedef struct
{
	BYTE byVideoFormat;						// �����ʽ,0-PAL,1-N	
	BYTE byMenuAlphaValue;					// �˵��뱳��ͼ��Աȶ� 
	WORD wScreenSaveTime;					// ��Ļ����ʱ�� 
	WORD wVOffset;							// ��Ƶ���ƫ�� 
	WORD wBrightness;						// ��Ƶ������� 
	BYTE byStartMode;						// ��������Ƶ���ģʽ(0:�˵�,1:Ԥ��) 
	CHAR reservedData;
}NET_DLDVR_VOOUT;

typedef struct 
{
	DWORD dwSize;
	NET_DLDVR_VOOUT struVOOut[MAX_VIDEOOUT];
	NET_DLDVR_VGAPARA struVGAPara[MAX_VGA];	// VGA���� 
	NET_DLDVR_MATRIXPARA struMatrixPara;		// MATRIX���� 
}NET_DLDVR_VIDEOOUT,*LPNET_DLDVR_VIDEOOUT;

//DVR�û�����
typedef struct
{
	BYTE sUserName[DL_NAME_LEN];		// �û��� 
	BYTE sPassword[PASSWD_LEN];		// ���� 
	DWORD dwLocalRight[MAX_RIGHT];	// Ȩ�� 
									//����0: ���ؿ�����̨
									//����1: �����ֶ�¼��
									//����2: ���ػط�
									//����3: �������ò���
									//����4: ���ز鿴״̬����־
									//����5: ���ظ߼�����(��������ʽ�����������ػ�)
	DWORD dwRemoteRight[MAX_RIGHT];	// Ȩ�� 
									//����0: Զ�̿�����̨
									//����1: Զ���ֶ�¼��
									//����2: Զ�̻ط�
									//����3: Զ�����ò���
									//����4: Զ�̲鿴״̬����־
									//����5: Զ�̸߼�����(��������ʽ�����������ػ�)
									//����6: Զ�̷��������Խ�
									//����7: Զ��Ԥ��
									//����8: Զ�����󱨾��ϴ����������
									//����9: Զ�̿��ƣ��������
									//����10: Զ�̿��ƴ���
	CHAR sUserIP[16];					// �û�IP��ַ(Ϊ0ʱ��ʾ�����κε�ַ) 
	BYTE byMACAddr[MACADDR_LEN];		// �����ַ 
}NET_DLDVR_USER_INFO,*LPNET_DLDVR_USER_INFO;

typedef struct
{
	DWORD dwSize;
	NET_DLDVR_USER_INFO struUser[MAX_USERNUM];
}NET_DLDVR_USER,*LPNET_DLDVR_USER;

//DVR�û�������չ
typedef struct
{
	BYTE sUserName[DL_NAME_LEN];		// �û��� 
	BYTE sPassword[PASSWD_LEN];		// ���� 
	DWORD dwLocalRight[MAX_RIGHT];	// Ȩ�� 
	//����0: ���ؿ�����̨
	//����1: �����ֶ�¼��
	//����2: ���ػط�
	//����3: �������ò���
	//����4: ���ز鿴״̬����־
	//����5: ���ظ߼�����(��������ʽ�����������ػ�)
	DWORD dwLocalPlaybackRight;		// ���ؿ��Իطŵ�ͨ�� bit0 -- channel 1*/
	DWORD dwRemoteRight[MAX_RIGHT];	// Ȩ�� 
	//����0: Զ�̿�����̨
	//����1: Զ���ֶ�¼��
	//����2: Զ�̻ط� 
	//����3: Զ�����ò���
	//����4: Զ�̲鿴״̬����־
	//����5: Զ�̸߼�����(��������ʽ�����������ػ�)
	//����6: Զ�̷��������Խ�
	//����7: Զ��Ԥ��
	//����8: Զ�����󱨾��ϴ����������
	//����9: Զ�̿��ƣ��������
	//����10: Զ�̿��ƴ���
	DWORD dwNetPreviewRight;		// Զ�̿���Ԥ����ͨ�� bit0 -- channel 1*/
	DWORD dwNetPlaybackRight;		// Զ�̿��Իطŵ�ͨ�� bit0 -- channel 1*/
	CHAR sUserIP[16];				// �û�IP��ַ(Ϊ0ʱ��ʾ�����κε�ַ) 
	BYTE byMACAddr[MACADDR_LEN];	// �����ַ 
}NET_DLDVR_USER_INFO_EX,*LPNET_DLDVR_USER_INFO_EX;

typedef struct
{
	DWORD dwSize;
	NET_DLDVR_USER_INFO_EX struUser[MAX_USERNUM];
}NET_DLDVR_USER_EX,*LPNET_DLDVR_USER_EX;

typedef struct
{
	CHAR sFileName[100];//�ļ���,��ʽΪ%s_%d(����%d��ֵʵ�ʱ�ʾ����¼���Ƿ�������״̬�� 1-���� 0-��������
	NET_DLDVR_TIME struStartTime;//�ļ��Ŀ�ʼʱ��
	NET_DLDVR_TIME struStopTime;//�ļ��Ľ���ʱ��
	DWORD dwFileSize;//�ļ��Ĵ�С
	DWORD dwChannel;//�ļ�������ͨ����2007-11-05����
}NET_DLDVR_FIND_DATA,*LPNET_DLDVR_FIND_DATA;

typedef struct
{
	CHAR sFileName[128];//�ļ���
	U8      cLockStatus;//��ǰ¼���Ƿ�������״̬�� 1-���� 0-������    
	NET_DLDVR_TIME struStartTime;//�ļ��Ŀ�ʼʱ��
	NET_DLDVR_TIME struStopTime;//�ļ��Ľ���ʱ��
	DWORD dwFileSize;//�ļ��Ĵ�С
	DWORD dwChannel;//�ļ�������ͨ��
	U8	  cRecordType;	
}NET_DLDVR_FIND_DATA_EX,*LPNET_DLDVR_FIND_DATA_EX;


//2011-01-11 add,��ʱ�䷽ʽ������ļ�
typedef struct
{
	NET_DLDVR_TIME struStartTime;//�ļ��Ŀ�ʼʱ��
	NET_DLDVR_TIME struStopTime;//�ļ��Ľ���ʱ��
	WORD		Type;	//�ļ�����
}NET_DLDVR_FILEBYTIME_DATA,*LPNET_DLDVR_FILEBYTIME_DATA;

//------------------------

typedef struct {
	BYTE byRecordStatic; //ͨ���Ƿ���¼��,0-��¼��,1-¼��
	BYTE bySignalStatic; //���ӵ��ź�״̬,0-����,1-�źŶ�ʧ
	BYTE byHardwareStatic;//ͨ��Ӳ��״̬,0-����,1-�쳣,����DSP����
	CHAR reservedData;
	DWORD dwBitRate;//ʵ������
	DWORD dwLinkNum;//�ͻ������ӵĸ���
	DWORD dwClientIP[MAX_LINK];//�ͻ��˵�IP��ַ
}NET_DLDVR_CHANNELSTATE,*LPNET_DLDVR_CHANNELSTATE;

typedef struct 
{
	DWORD dwVolume;//Ӳ�̵�����
	DWORD dwFreeSpace;//Ӳ�̵�ʣ��ռ�
	DWORD dwHardDiskStatic; //Ӳ�̵�״̬,����,�,��������
							/*
							1 disk ok
							2 ��Ӳ��
							3 Ӳ��û�и�ʽ��
							4 Ӳ����������
							5 Ӳ�̶�д����
							6 Ӳ�����ڸ�ʽ��
							 */
	WORD	wDiskAddrMajor;	//Ӳ�̵�����ַ
	WORD	wDiskAddrMinor;	//Ӳ�̵Ĵӵ�ַ
}NET_DLDVR_DISKSTATE,*LPNET_DLDVR_DISKSTATE;

typedef struct
{
	DWORD dwDeviceStatic; 	//�豸��״̬,0-����,1-CPUռ����̫��,����85%,2-Ӳ������,���紮������
	NET_DLDVR_DISKSTATE  struHardDiskStatic[MAX_DISKNUM]; 
	NET_DLDVR_CHANNELSTATE struChanStatic[MAX_CHANNUM];//ͨ����״̬
	BYTE  byAlarmInStatic[MAX_ALARMIN]; //�����˿ڵ�״̬,0-û�б���,1-�б���
	BYTE  byAlarmOutStatic[MAX_ALARMOUT]; //��������˿ڵ�״̬,0-û�����,1-�б������
	DWORD  dwLocalDisplay;//������ʾ״̬,0-����,1-������
}NET_DLDVR_WORKSTATE,*LPNET_DLDVR_WORKSTATE;


typedef struct 
{
	DWORD dwVolume;//Ӳ�̵�����
	DWORD dwFreeSpace;//Ӳ�̵�ʣ��ռ�
	DWORD dwHardDiskStatic; //Ӳ�̵�״̬,����,�,��������
							/*
							1 disk ok
							2 ��Ӳ��
							3 Ӳ��û�и�ʽ��
							4 Ӳ����������
							5 Ӳ�̶�д����
							6 Ӳ�����ڸ�ʽ��
							 */
	WORD	wDiskAddrMajor;	//Ӳ�̵�����ַ
	WORD	wDiskAddrMinor;	//Ӳ�̵Ĵӵ�ַ
	CHAR	Vender[10]; //������
	CHAR	Model[32]; //ģʽ
	INT		Temperature;//ʵʱ�¶ȣ����϶ȣ���-1��ʾʧ��
	INT		runningStatus;//Ӳ���Ƿ�����, -1 ��ȡʧ��;  0-idle/sleep;  1-running
}NET_DLDVR_DISKSTATE_EX,*LPNET_DLDVR_DISKSTATE_EX;

typedef struct
{
	NET_DLDVR_DISKSTATE_EX  struHardDiskStatic[MAX_DISKNUM]; 	
}NET_DLDVR_DVRDISKSTATE,*LPNET_DLDVR_DVRDISKSTATE;

//ϵͳ��Ϣ, 2008-04-10 add
typedef struct 
{
    char mac[6]  ;				//mac��ַ
    WORD  sys_id  ;				//ϵͳID
    WORD  channel_num ;            //ͨ������
    WORD  alarm_in_count ;         //�澯����˿���
    WORD  alarm_out_count;         //�澯����˿���
    WORD  epld_version   ;         //EPLD�汾��  
	WORD  Dvr_type;				//0:C�� 1: L�� 2: LII��  3��mps 4:mpf 5:mpc 6: hi3510 7:������ 8�������� 9: hi3511 10:����IPCamera
    BYTE  Audio_enc;				//0:G711 1: G726
	BYTE  Video_enc;				//0:MPEG4 1: H264
}NET_DLDVR_SYSTEMINFO, *LPNET_DLDVR_SYSTEMINFO ;

//2009-08-13,DVR����״̬����չ��
typedef struct
{
	DWORD dwDeviceStatic; 	//�豸��״̬,0-����,1-CPUռ����̫��,����85%,2-Ӳ������,���紮������
	NET_DLDVR_DISKSTATE  struHardDiskStatic[MAX_DISKNUM]; 
	NET_DLDVR_CHANNELSTATE struChanStatic[MAX_CHANNUM_EX];//ͨ����״̬
	BYTE  byAlarmInStatic[MAX_ALARMIN]; //�����˿ڵ�״̬,0-û�б���,1-�б���
	BYTE  byAlarmOutStatic[MAX_ALARMOUT]; //��������˿ڵ�״̬,0-û�����,1-�б������
	DWORD  dwLocalDisplay;//������ʾ״̬,0-����,1-������
}NET_DLDVR_WORKSTATE_EX,*LPNET_DLDVR_WORKSTATE_EX;
//DVR��־

//������
#define MAJOR_All				0x00	// ȫ��
#define MAJOR_ALARM				0x1	// ���� 
#define MAJOR_EXCEPTION			0x2	// �쳣
#define MAJOR_OPERATION			0x3	// ���� 
#define MAJOR_NET				0x4	//������ص���־
#define MAJOR_ACC				0x5 // ������־

// ���� 
//������
#define MINOR_ALARM_IN			0x1		// �������� 
#define MINOR_ALARM_OUT			0x2		// ������� 
#define MINOR_MOTDET_START		0x3		// �ƶ���ⱨ����ʼ 
#define MINOR_MOTDET_STOP		0x4		// �ƶ���ⱨ������ 
#define MINOR_HIDE_ALARM_START	0x5		// �ڵ�������ʼ 
#define MINOR_HIDE_ALARM_STOP	0x6		// �ڵ���������
#define MINOR_ALARM_IN_STOP     0x7     //�ⲿ�澯�������
#define MINOR_ALARM_MOTION_START		0x08	//�������ӿ�ʼ��2009-08-12
#define MINOR_ALARM_MOTION_STOP		0x09	//�������ӽ�����2009-08-12
#define MINOR_ALARM_REC_START		0x10	//����¼��ʼ��2009-08-12
#define MINOR_ALARM_REC_STOP		0x11	//����¼�������2009-08-12
#define MINOR_ALARM_END			0x12	//���������2009-08-12

//2009-12-03 add,���ܷ�����ص���־����
#define MINOR_ALARM_WIRE     0x90 //����
#define MINOR_ALARM_AREA     0x91 //����
#define MINOR_ALARM_ABANDON  0x92 //����
#define MINOR_ALARM_TOGETHER 0x93 //�ۼ�
#define MINOR_ALARM_RUN      0x94 //����
#define MINOR_ALARM_COUNTER      0x95 //����ͳ��
#define MINOR_ALARM_HIDE_FACE      0x96 //����αװ


//������
#define MINOR_VI_LOST			0x21	// �źŶ�ʧ 
#define MINOR_ILLEGAL_ACCESS	0x22	// �Ƿ����� 
#define MINOR_HD_FULL			0x23	// Ӳ���� 
#define MINOR_HD_ERROR			0x24	// Ӳ�̴��� 
#define MINOR_DCD_LOST			0x25	// MODEM ���� 
#define MINOR_IP_CONFLICT		0x26	// IP��ַ��ͻ 
#define MINOR_NET_BROKEN		0x27	// ���߶� 
#define MINOR_VI_RESUME		    0x28	// �źŻָ�
#define MINOR_EXP_PASS		    0x29	// �������2009-08-12
#define MINOR_NO_HDD		    0x30	// û��Ӳ�̣�2009-08-12
#define MINOR_WIRTE_HDD			0x31	// ����Ӳ�̴���2009-08-12
#define MINOR_EXP_THERMAL		0x32	// �¶��쳣��2009-08-12
#define MINOR_EXP_FAN			0x33	// �����쳣��2009-08-12

//������
#define MINOR_START_DVR			0x41	// ���� 
#define MINOR_STOP_DVR			0x42	// �ػ� 
#define MINOR_STOP_ABNORMAL		0x43	// �Ƿ��ػ� 

#define MINOR_LOCAL_LOGIN		0x50	// ���ص�½ 
#define MINOR_LOCAL_LOGOUT		0x51	// ����ע����½ 
#define MINOR_LOCAL_CFG_PARM	0x52	// �������ò��� 
#define MINOR_LOCAL_PLAYBYFILE	0x53	// ���ذ��ļ��ط� 
#define MINOR_LOCAL_PLAYBYTIME	0x54	// ���ذ�ʱ��ط� 
#define MINOR_LOCAL_START_REC	0x55	// ���ؿ�ʼ¼�� 
#define MINOR_LOCAL_STOP_REC	0x56	// ����ֹͣ¼�� 
#define MINOR_LOCAL_PTZCTRL		0x57	// ������̨���� 
#define MINOR_LOCAL_PREVIEW		0x58	// ����Ԥ�� 
#define MINOR_LOCAL_MODIFY_TIME	0x59	// �����޸�ʱ�� 
#define MINOR_LOCAL_UPGRADE		0x5a	// �������� 
//#define MINOR_LOCAL_COPYFILE	0x5b	// ���ر����ļ� 
#define MINOR_LOCAL_REBOOT		0x5c	// ����������2007-12-11
#define MINOR_LOCAL_FORMAYT	    0x5d	// ���ظ�ʽ��Ӳ�̣�2007-12-11
#define MINOR_LOCAL_FACTORY	    0x5e	// ���ػָ��������ã�2009-08-12
#define MINOR_LOCAL_SYSTIME	    0x5f	// ���ظı�ϵͳʱ�䣬2009-08-12

#define MINOR_LOCAL_TIEM_SET	0x60	// ��ʱ¼���趨�����2009-08-12
#define MINOR_LOCAL_ALAM_SET	0x61	// ����¼���趨�����2009-08-12
#define MINOR_LOCAL_HDD_OVER	0x62	// HDD���r�����ǣ�2009-08-12
#define MINOR_LOCAL_USER_LOGOUT	0x63	// �Ͽ��û���2009-08-12
#define MINOR_LOCAL_HDD_SAFETY	0x64	// HDD��ȫģʽͨ����2009-08-12 
#define MINOR_LOCAL_COPY		0x65	// ִ�и��ƣ�2009-08-12
#define MINOR_LOCAL_CLEAR_RVS	0x66	// RVS��ַ�����2009-08-12
#define MINOR_LOCAL_RVS_SET		0x67	// RVS��ַ�����2009-08-12 
#define MINOR_LOCAL_AUTO_DELETE	0x68	// �Զ�ɾ�������趨�����2009-08-12 


#define MINOR_REMOTE_LOGIN		0x70	// Զ�̵�¼ 
#define MINOR_REMOTE_LOGOUT		0x71	// Զ��ע����½ 
#define MINOR_REMOTE_START_REC	0x72	// Զ�̿�ʼ¼�� 
#define MINOR_REMOTE_STOP_REC	0x73	// Զ��ֹͣ¼�� 
#define MINOR_START_TRANS_CHAN	0x74	// ��ʼ͸������ 
#define MINOR_STOP_TRANS_CHAN	0x75	// ֹͣ͸������ 
#define MINOR_REMOTE_GET_PARM	0x76	// Զ�̻�ò��� 
#define MINOR_REMOTE_CFG_PARM	0x77	// Զ�����ò��� 
#define MINOR_REMOTE_GET_STATUS 0x78	// Զ�̻��״̬ 
#define MINOR_REMOTE_ARM		0x79	// Զ�̲��� 
#define MINOR_REMOTE_DISARM		0x7a	// Զ�̳��� 
#define MINOR_REMOTE_REBOOT		0x7b	// Զ������ 
#define MINOR_START_VT			0x7c	// ��ʼ�����Խ� 
#define MINOR_STOP_VT			0x7d	// ֹͣ�����Խ� 
#define MINOR_REMOTE_UPGRADE	0x7e	// Զ������ 
#define MINOR_REMOTE_PLAYBYFILE	0x7f	// Զ�̰��ļ��ط� 
#define MINOR_REMOTE_PLAYBYTIME	0x80	// Զ�̰�ʱ��ط� 
#define MINOR_REMOTE_PTZCTRL	0x81	// Զ����̨���� 
#define MINOR_REMOTE_LOGO_UPDATE       0x82     ///Զ�̸���LOGO  
#define MINOR_REMOTE_LANGUAGE_UPDATE   0x83     //Զ�������Զ�������
#define MINOR_REMOTE_RESOURCE_UPDATE   0x84     //Զ�������Զ�����Դ
#define MINOR_REMOTE_RESOURCE_CLEAR    0x85     //Զ������Զ�����Դ
//#define MINOR_REMOTE_FORMAT_HDD    0x86     //Զ�̸�ʽ��Ӳ�̣�2008-10-15
#define MINOR_REMOTE_COPY    0x87     //Զ�̱��ݣ�2009-08-12

//2009-08-12 add, NVR���������־
#define MINOR_NET_POP3_AUT	0x100	//POP3��֤����
#define MINOR_NET_POP3_SVR	0x101	//�Ҳ���POP3������
#define MINOR_NET_POP3_DNS	0x102	//��DNS�޷�����POP3��������ַ
#define MINOR_NET_SMTP_AUT	0x103	//SMTP��֤����
#define MINOR_NET_SMTP_SVR	0x104	//�Ҳ���SMTP������
#define MINOR_NET_SMTP_DNS	0x105	//��DNS�޷�����SMTP��������ַ
#define MINOR_NET_MAIL_ERR	0x106	//�����ʼ�ʱ�����Ĵ���
#define MINOR_NET_DNS_OTH	0x107	//DNSʹ��ʱ�����Ĵ���
#define MINOR_NET_NTP_OK	0x108	//��NTPʱ��ͬ���ɹ�
#define MINOR_NET_NTP_DNS	0x109	//��DNS�޷�����NTP��������ַ
#define MINOR_NET_NTP_NOANS	0x110	//NTP��������Ӧ��
#define MINOR_NET_NTP_OTH	0x111	//NTPʹ�Õr����������
#define MINOR_NET_DHCP_FAIL	0x112	//DHCP��ַ��Updateʧ��
#define MINOR_NET_DHCP_LOST	0x113	//DHCP��ַ�����ڵ��ڣ���ַʧЧ
#define MINOR_NET_DHCP_OTH	0x114	//DHCPʹ�Õr����������
#define MINOR_DDNSIPADDUPDATE_OK	0x115	//�ɹ�����
#define MINOR_DDNSUSERASS_ERR	0x116	//��������ָ�����������Ե����,�û�������������һ�µ����
#define MINOR_DNSIPADDUPDATE_ERR	0x117	//��DNS������������
#define MINOR_DNSOTHER	0x118	//�����Ĵ���
#define MINOR_DDNSSVRRES_ERR	0x119	//�ӷ�����û��Ӧ������


#define  MINOR_ACCE_LOCAL_MANA_LOGIN    0x121               //���ص�½
#define  MINOR_ACCE_LOCAL_OPER_LOGIN    0x122              //���ص�½
#define  MINOR_ACCE_LOCAL_VIEW_LOGIN    0x123               //���ص�½
#define  MINOR_ACCE_REMOTE_MANA_LOGIN   0x124               //�����½
#define  MINOR_ACCE_REMOTE_OPER_LOGIN   0x125               //�����½
#define  MINOR_ACCE_REMOTE_VIEW_LOGIN   0x126              //�����½
#define  MINOR_ACCE_MANA_AUTO_LOGIN     0x127              //�Զ���¼
#define  MINOR_ACCE_OPER_AUTO_LOGIN     0x128               //�Զ���¼
#define  MINOR_ACCE_VIEW_AUTO_LOGIN     0x129              //�Զ���¼


typedef struct 
{
	NET_DLDVR_TIME strLogTime;
	DWORD	dwMajorType;	//������ 1-����; 2-�쳣; 3-����; 0xff-ȫ��
	DWORD	dwMinorType;//������ 0xff-ȫ��; 
	BYTE	sUser[32]; //���������û���
//	BYTE	sNetUser[MAX_NAMELEN];//����������û���
	CHAR	sRemoteHostAddr[16];//Զ��������ַ
	DWORD	dwParaType;//��������
	DWORD	dwChannel;//ͨ����
	DWORD	dwDiskNumber;//Ӳ�̺�
	DWORD	dwAlarmInPort;//��������˿�
	DWORD	dwAlarmOutPort;//��������˿�		
}NET_DLDVR_LOG,*LPNET_DLDVR_LOG;

typedef struct 
{
	CHAR sRedirectorIP[16];	// ת��������IP��ַ
	WORD wRedirectorPort;	//�˿ں�
}NET_DLDVR_REDIRECTORINFO, *LPNET_DLDVR_REDIRECTORINFO;

typedef struct
{
	BYTE Output[MAX_ALARMOUT];
}NET_DLDVR_ALARMOUTSTATUS,*LPNET_DLDVR_ALARMOUTSTATUS;

typedef struct
{
	USHORT m_Year;
	USHORT m_Month;
	USHORT m_Day;
	USHORT m_Hour;
	USHORT m_Minute;
	USHORT m_Second;
	BYTE DeviceName[24];	//�豸����
	DWORD dwChannelNumer;	//ͨ����
	BYTE CardNumber[32];	//����
	CHAR cTradeType[12];	//��������
	DWORD dwCash;			//���׽��
}NET_DLDVR_TRADEINFO,*LPNET_DLDVR_TRADEINFO;

//����ΪATMר��
//֡��ʽ
typedef struct
{
	BYTE code[12];		// ���� 
}NET_DLDVR_FRAMETYPECODE;

typedef struct
{
	DWORD dwSize;	
	CHAR sATMIP[16];						// ATM IP��ַ 
	DWORD dwATMType;						// ATM���� 
	DWORD dwInputMode;						// ���뷽ʽ		
	DWORD dwFrameSignBeginPos;              // ���ı�־λ����ʼλ��
	DWORD dwFrameSignLength;				// ���ı�־λ�ĳ��� 
	BYTE  byFrameSignContent[12];			// ���ı�־λ������ 
	DWORD dwCardLengthInfoBeginPos;			// ���ų�����Ϣ����ʼλ�� 
	DWORD dwCardLengthInfoLength;			// ���ų�����Ϣ�ĳ��� 
	DWORD dwCardNumberInfoBeginPos;			// ������Ϣ����ʼλ�� 
	DWORD dwCardNumberInfoLength;			// ������Ϣ�ĳ��� 
	DWORD dwBusinessTypeBeginPos;           // �������͵���ʼλ�� 
	DWORD dwBusinessTypeLength;				// �������͵ĳ��� 
	NET_DLDVR_FRAMETYPECODE frameTypeCode[10];// ���� 
}NET_DLDVR_FRAMEFORMAT,*LPNET_DLDVR_FRAMEFORMAT;

//DS-6001D/F 
//�����豸�����붨��
#define NET_DEC_STARTDEC		1
#define NET_DEC_STOPDEC			2
#define NET_DEC_STOPCYCLE		3
#define NET_DEC_CONTINUECYCLE	4
//���ӵ�ͨ������
typedef struct 
{
	CHAR sDVRIP[16];				// DVR IP��ַ 
	WORD wDVRPort;			 		// �˿ں� 
	BYTE sUserName[DL_NAME_LEN];		// �û��� 
	BYTE sPassword[PASSWD_LEN];		// ���� 
	BYTE byChannel;					// ͨ���� 
	BYTE byLinkMode;				// ����ģʽ 	
	BYTE byLinkType;				// �������� 0�������� 1�������� 
}NET_DLDVR_DECCHANINFO, *LPNET_DLDVR_DECCHANINFO;

//ÿ������ͨ��������
typedef struct 
{	
	BYTE	byPoolChans;			//ÿ·����ͨ���ϵ�ѭ��ͨ������, ���4ͨ��
	NET_DLDVR_DECCHANINFO struchanConInfo[MAX_DECPOOLNUM];
	BYTE	byEnablePoll;			//�Ƿ���Ѳ 0-�� 1-��
	BYTE	byPoolTime;				//��Ѳʱ�� 0-���� 1-10�� 2-15�� 3-20�� 4-30�� 5-45�� 6-1���� 7-2���� 8-5���� 	
}NET_DLDVR_DECINFO, *LPNET_DLDVR_DECINFO;

//�����豸��������
typedef struct 
{
	DWORD	dwSize;
	DWORD	dwDecChanNum; 		//����ͨ��������
	NET_DLDVR_DECINFO struDecInfo[MAX_DECNUM];
}NET_DLDVR_DECCFG, *LPNET_DLDVR_DECCFG;
//2005-08-01
// �����豸͸��ͨ������ 
typedef struct 
{
	DWORD dwEnableTransPort;	// �Ƿ�����͸��ͨ�� 0�������� 1������
	CHAR sDecoderIP[16];		// DVR IP��ַ 
	WORD wDecoderPort;			// �˿ں� 
	WORD wDVRTransPort;			// ����ǰ��DVR�Ǵ�485/232�����1��ʾ485����,2��ʾ232���� 		
	CHAR cReserve[4];
}NET_DLDVR_PORTINFO, *LPNET_DLDVR_PORTINFO;

typedef struct 
{
	DWORD dwSize;
	NET_DLDVR_PORTINFO struTransPortInfo[MAX_TRANSPARENTNUM]; // ����0��ʾ485 ����1��ʾ232 
}NET_DLDVR_PORTCFG, *LPNET_DLDVR_PORTCFG;

// ���������ļ��ط� 
typedef struct 
{
	DWORD dwSize;
	CHAR sDecoderIP[16];		// DVR IP��ַ 
	WORD wDecoderPort;			// �˿ں� 
	WORD wLoadMode;				// �ط�����ģʽ 1�������� 2����ʱ�� 
	union
	{
		BYTE byFile[100];		// �طŵ��ļ��� 
		struct 
		{
			DWORD dwChannel;
			BYTE sUserName[DL_NAME_LEN];	//������Ƶ�û���
			BYTE sPassword[PASSWD_LEN];	// ���� 
			NET_DLDVR_TIME struStartTime;	// ��ʱ��طŵĿ�ʼʱ�� 
			NET_DLDVR_TIME struStopTime;	// ��ʱ��طŵĽ���ʱ�� 			
		}bytime;
	}mode_size;
}NET_DLDVR_PLAYREMOTEFILE,*LPNET_DLDVR_PLAYREMOTEFILE;

//��ǰ�豸��������״̬
typedef struct 
{
	DWORD dwWorkType;		//������ʽ��1����Ѳ��2����̬���ӽ��롢3�����ļ��ط� 4����ʱ��ط�
	CHAR sDVRIP[16];		//���ӵ��豸ip*/
	WORD wDVRPort;			//���Ӷ˿ں�
	BYTE byChannel;					// ͨ���� 
	BYTE byLinkMode;				// ����ģʽ 
	DWORD	dwLinkType;		//�������� 0�������� 1��������
	union
	{
		struct 
		{
			BYTE sUserName[DL_NAME_LEN];	//������Ƶ�û���
			BYTE sPassword[PASSWD_LEN];	// ���� 
			CHAR cReserve[52];
		}userInfo;
		struct 
		{			
			BYTE   fileName[100];		
		}fileInfo;
		struct 
		{
			DWORD	dwChannel;
			BYTE	sUserName[DL_NAME_LEN];	//������Ƶ�û���
			BYTE	sPassword[PASSWD_LEN];	// ���� 
			NET_DLDVR_TIME struStartTime;		// ��ʱ��طŵĿ�ʼʱ�� 
			NET_DLDVR_TIME struStopTime;		// ��ʱ��طŵĽ���ʱ�� 	
		}timeInfo;
	}objectInfo;
}NET_DLDVR_DECCHANSTATUS, *LPNET_DLDVR_DECCHANSTATUS;

typedef struct 
{
	DWORD   dwSize;
	NET_DLDVR_DECCHANSTATUS struDecState[MAX_DECNUM];	
}NET_DLDVR_DECSTATUS, *LPNET_DLDVR_DECSTATUS;

//�����ַ�
typedef struct 
{
	WORD wShowString;				// Ԥ����ͼ�����Ƿ���ʾ�ַ�,0-����ʾ,1-��ʾ �����С704*576,�����ַ��Ĵ�СΪ32*32
	WORD wStringSize;				// �����ַ��ĳ��ȣ����ܴ���44���ַ� 
	WORD wShowStringTopLeftX;		// �ַ���ʾλ�õ�x���� 
	WORD wShowStringTopLeftY;		// �ַ�������ʾλ�õ�y���� 
	CHAR sString[44];				// Ҫ��ʾ���ַ����� 
}NET_DLDVR_SHOWSTRINGINFO, *LPNET_DLDVR_SHOWSTRINGINFO;

//�����ַ�
typedef struct 
{
	DWORD dwSize;
	NET_DLDVR_SHOWSTRINGINFO struStringInfo[MAX_STRINGNUM];				// Ҫ��ʾ���ַ����� 
}NET_DLDVR_SHOWSTRING, *LPNET_DLDVR_SHOWSTRING;

//ͼƬ����
typedef struct
{
	WORD	wPicSize;				// 0=CIF, 1=QCIF, 2=D1 
	WORD	wPicQuality;			// ͼƬ����ϵ�� 0-��� 1-�Ϻ� 2-һ�� 
}NET_DLDVR_JPEGPARA, *LPNET_DLDVR_JPEGPARA;

//HS�豸�����������
typedef struct tagAUXOUT
{
	DWORD dwSize;
	DWORD dwAlarmOutChan;                       	// ѡ�񱨾�������������ͨ��: 0:�����/1:��1/2:��2/3:��3/4:��4 
	DWORD dwAlarmChanSwitchTime;                	// ����ͨ���л�ʱ�䣺1:1�� - 10:10�� 
	DWORD dwAuxSwitchTime[MAX_AUXOUT];		// ��������л�ʱ��: 0-���л�,1-5s,2-10s,3-20s,4-30s,5-60s,6-120s,7-300s 
	BYTE  byAuxOrder[MAX_AUXOUT][MAX_WINDOW];	// �������Ԥ��˳��, 0xff��ʾ��Ӧ�Ĵ��ڲ�Ԥ�� 
}NET_DLDVR_AUXOUTCFG, *LPNET_DLDVR_AUXOUTCFG;

//DVR��������汾,2007-07-27����
typedef struct
{
	char version[128];
}NET_DLDVR_DEVICEVERSION,*LPNET_DLDVR_DEVICEVERSION;

//2007-12-11 SY_add 
typedef struct _MONITOR_INFOEX
{
	BYTE		has_audio;		//�Ƿ�����Ƶ 1:����,0:û�а���
	BYTE		quality;		//���� 0:"��", 1:"��ͨ", 2:"��", 3:"�Ϻ�", 4:"���"
	BYTE		frame_rate;		//֡�� 0 ~ 25
	BYTE		video_format;	//��Ƶ��ʽ 0:PAL, 1:NTSC
	BYTE		resolution;		//�ֱ���
	DWORD		Mcast_IP;		//�ಥ���ַ(���DVR����ʹ�öಥ��ʽ�򷵻�0)
	WORD		Mcast_port;		//�ಥ���ַ(���DVR����ʹ�öಥ��ʽ�򷵻�0)
}MONITOR_INFOEX;

//NVR��־�ṹ-------------------------------------------------------------
typedef struct 
{
	unsigned int         log_time ;       //ʱ��
    unsigned int         major_type;      //��־����
    unsigned int         minor_type ;     //��־�¼�
    unsigned int         reason;          //���˿ںţ�ͨ���ţ�Ӳ�̺ţ�Ƶ����,ʱ�䣩
    unsigned int         remote_IP;      //IP ��ַ.2009-04-03 add
    unsigned char		user_name[10];   //��½�û���
	void hton(){
		log_time	= htonl( log_time);
		major_type	= htonl( major_type );
		minor_type	= htonl( minor_type );
		reason		= htonl( reason );
		//	remote_IP   = htonl(remote_IP);
	}
	void ntoh(){
		hton();
	}
}LOG_RECORD_NVR,  *LPLOG_RECORD_NVR ;

//2009-08-19 added for �����쳣���ߵȻص��ṹ
typedef struct
{
	UINT Msg;
	UINT wParam;
	UINT lPara;
	UINT reserve;
}NET_DLDVR_EXCEPTION;

//ԭʼ���ݲɼ���Ϣ�� 2010-09-07
typedef struct
{
	int TotalNum;
	int CurrNum;
}NET_DLDVR_INFRAREDFRAME;

//����NVR�������Ľṹ�� begin------------------------------
#define DECODE_MAX 4
#define MAX_VIDEO_CHANNEL_NVR 32
#define SYS_RVS_MAX   32

#define    MAX_PRESET_NUM          128
#define    MAX_ROUTE_NUM           8
#define    ORIGIN_PRESET_POSITION    1

#define    MAX_VIEWER_USER     20       /*�����Ա�� */
#define    MAX_OPERATOR_USER   8        /*������Ա�� */
#define    MAX_ADMIN_USER      4        /*������Ա�� */

#define    MAX_PASSWORD_MANAGER_CHAR  8 /* manager password max lenght */
#define    MAX_PASSWORD_OPERATOR_CHAR  6        /* operator password max lenght */
#define    MAX_PASSWORD_VIEWER_CHAR  4  /* viewer password max lenght */
#if 0
#define    DISPLAY_SINGLE      0
#define    DISPLAY_SEQUENCE    1
#define    DIAPLAY_BLANK       2
#endif

#define    MAX_SEND_TO_MAIL            4
#define    MAX_ADDRESS_CHAR            256
#define    MAX_MAIL_SUBJECT_CHAR       256
#define    MAX_USER_NAME_CHAR          256
#define    MAX_PASSWORD_CHAR           256

#define PPPOE_PASS           6

#define CHANNEL_NAME_LENGTH 16
#define RVS_PWD_LENGTH      16
#define NET_MAC_LENGTH      6

#define  VIEW_SPLIT_ONE      1  //������
#define  VIEW_SPLIT_TWO      2  //������
#define  VIEW_SPLIT_FOUR     4  //�Ļ���
#define  VIEW_SPLIT_SIX      6  //������
#define  VIEW_SPLIT_NINE     8  //�Ż���

#define SCREEN_TIME     0
#define SCREEN_STAT     1
#define SCREEN_SHORTCUT 2

#define PLAN_REC_ONEDAY     0X01
#define PLAN_REC_EVERYDAY   0X02
#define PLAN_REC_WEEKLY     0X03
#define PLAN_REC_MONTHLY    0X04
#define PLAN_REC_ITEMS_MAX  1024

typedef struct
{
    U16  year  ;
    U8   month ;
    U8   date  ;
}DATE_INFO ;

// struct defined for time 
typedef struct
{
    U8   hour   ;
    U8   minute ;
    U8   second ;
    U8   reserved ;
}TIME_INFO ;

typedef struct
{
    DATE_INFO        date ;
    TIME_INFO        time ;
}DVR_TIME;

struct TIME_PHASE_NVR
{
    TIME_INFO start;        /*��ʼʱ�� */
    TIME_INFO end;          /*����ʱ�� */
    U8 active;              /*0: ON,   1:OFF */

    TIME_PHASE_NVR(){
		memset( this, 0x00, sizeof(TIME_PHASE_NVR) );
	}
};

struct IP
{
    U8 a;
    U8 b;
    U8 c;
    U8 d;

    IP(){
		memset( this, 0x00, sizeof(IP) );
	}
};

struct SUMMER_TIME
{
        /*��������ʱʱ�� */
    U32  in_time  ;     //����ʱ����ʱ��
    U32  out_time ;     //����ʱ��ȥʱ��

    SUMMER_TIME(){
		memset( this, 0x00, sizeof(SUMMER_TIME) );
	}
};


/* ϵͳ���ýṹ */
struct SYSTEM_SETUP_ADV
{
    U8 Date_fmt;            /*���ڸ�ʽ
                                   0 : yyyy-mm-dd  ��-��-��
                                   1 : dd-mm-yyyy  ��-��-��
                                   2 : dd-mmm-yyyy
                                   3 : mm-dd-yyyy  ��-��-��
                                   4 : mmm-dd-yyyy */

    U8 Time_fmt;            /*ʱ���ʽ
                                   0 : 24Сʱ��
                                   1 : 12Сʱ�� */
    U8 auto_time_adjust;    /*�Ƿ��Զ�����ʱ��  1:��;0:��  */
    U8 summer_time;         /*�Ƿ�ִ������ʱ    1:��;0:��  */
    SUMMER_TIME summer_tbl[5];      /*����ʱ�� */

    U16 overlay_days;       /* Ӳ����ǰ�Զ����ǵ����� 0~200�� 0������ */
    U8 search_time;         /* search ʱ�� */
    U8 video_overlay;       /* Ӳ��¼����ʱ���Ƿ��Զ����� 1:�� 0:�� */
    // NTP����
    U8 NTP_time_adjust;     /* �Ƿ�NTPʱ���Զ����� 1:��;0:�� */
    U8 NTP_refresh_interval;        /*NTPʱ�������� *//*
                                           0 : 1h
                                           0 : 2h
                                           0 : 6h
                                           0 : 12h
                                           0 : 24h
                                         */
    U8 NTP_name[64];       /* NTP server ip��ַ�������� */
    U16 NTP_port;
    int enable_sntp;  /*0����������������*/

    SYSTEM_SETUP_ADV(){
		memset( this, 0x00, sizeof(SYSTEM_SETUP_ADV) );
	}
};

struct NET_DLNVR_SYSTEM_SETUP
{
    U8 time_zone;           /* ʱ���� *//*
                                  0 : "GMT-12:00",
                                  1 :  "GMT-11:00",
                                  2 :  "GMT-10:00",
                                  3 :   "GMT-9:00",  
                                  4 :   "GMT-8:00",
                                  5 :   "GMT-7:00",
                                  6 :   "GMT-6:00",
                                  7 :   "GMT-5:00",
                                  8 :   "GMT-4:00",
                                  9 :   "GMT-3:00",
                                  10 :   "GMT-3:30",
                                  11 :  "GMT-2:00",
                                  12 :   "GMT-1:00",
                                  13 :   "GMT+0:00",
                                  14 :   "GMT+1:00",
                                  15 :   "GMT+2:00",
                                  16 :   "GMT+3:00",
                                  17 :   "GMT+3:30",
                                  18 :   "GMT+4:00",
                                  19 :   "GMT+4:30",
                                  20 :   "GMT+5:00",
                                  21 :   "GMT+5:30",
                                  22 :   "GMT+5:45",
                                  23 :   "GMT+6:00",
                                  24 :   "GMT+6:30",
                                  25 :   "GMT+7:00",
                                  26 :   "GMT+8:00",
                                  27 :   "GMT+9:00",
                                  28 :   "GMT+9:30",
                                  29 :   "GMT+10:00",
                                  30 :   "GMT+11:00",
                                  31 :   "GMT+12:00",
                                  32 :  "GMT+13:00",
                                     */

    U32 language;           /* ����ѡ�� *//*
                                   0 �� Ӣ��
                                   1 �� ����
                                   2 �� ����
                                   3 �� custom */

    U32 auto_login_user;    /* �Զ���½��Ĭ���û����� *//*
                                    0 :  ������û�
                                   1 :  �������û�
                                   2 :  �������û�
                                   3:  û���Զ���½
                                 */
    U32 alarm_beep;         /* �澯ʱ����ʱ�� 0~180�� 0��ʾû�з��� */
    U16 auto_lock_time;     /* �޲���ʱ��ϵͳ�˳�ʱ�䣬5~999 �� */
    U8 nvr_name[16];

    U8 address; //DVR��ַ ȱʡֵ��1. 2010-08-05 add

    SYSTEM_SETUP_ADV system_setup_adv;

    NET_DLNVR_SYSTEM_SETUP()
    {
		memset( this, 0x00, sizeof(NET_DLNVR_SYSTEM_SETUP) );
	}
};

struct PLAN_REC_ITEM
{
    U16 year;
    U8  month;
    U8  day;
    U8  stage_check; //ʱ��ѡ�б�־�� ��λѡ�У�0x01:ʱ��һ  0x02: ʱ�ζ� 0x03: ʱ��һ��
    TIME_INFO stage1_start;
    TIME_INFO stage1_end;
    TIME_INFO stage2_start;
    TIME_INFO stage2_end;
    U8  plan_type; //0x01:���� 0x02:ÿ�� 0x03:ÿ�� 0x04:ÿ��

    PLAN_REC_ITEM()
    {
		memset( this, 0x00, sizeof(PLAN_REC_ITEM) );
	}
};

/* ¼��������ýṹ */
struct NET_DLNVR_RECORDING_SETUP {
    PLAN_REC_ITEM plan_rec[MAX_VIDEO_CHANNEL_NVR][PLAN_REC_ITEMS_MAX];
    U16 plan_rec_items_count[MAX_VIDEO_CHANNEL_NVR];

    NET_DLNVR_RECORDING_SETUP()
    {
		memset( this, 0x00, sizeof(NET_DLNVR_RECORDING_SETUP) );
	}
};

/*��ʾ����*/
struct SINGLE {
    U8 single;              /*0:Single   1:Sequence   2: -- */
    U8 channel;             /*Ƶ���� */
    U8 spot;                /*0:��֧�ֱ���  1��֧�ֱ����л� */

    SINGLE(){
		memset( this, 0x00, sizeof(SINGLE) );
	}
};

struct NET_DLNVR_DISPLAY_SETUP
{
    U8 screen_show_type;    /*   */
    U8 seq_dwell[VIEW_SPLIT_NINE];           /*ͨ����Ѳʱ���л�ʱ�� ��Χ:5~30 ��λ:�� */
    SINGLE split9[VIEW_SPLIT_NINE];
    U8 display;             /*720p:1   1080i:2   1080p:2*/
    U8 mg3500;          /*mg3500�ֱ���, Standard:0(�����������ã�   720p:1   1080i:2 */
 //   U32 seq_ch;         /*Ѳ�ఴλ����*/
    U32 seq_ch[VIEW_SPLIT_NINE];         /*Ѳ�ఴλ����*/

    NET_DLNVR_DISPLAY_SETUP(){
		memset( this, 0x00, sizeof(NET_DLNVR_DISPLAY_SETUP) );
	}
};

/*ͨ������PPPOE*/
struct PPPOE_SET
{
    U8 pppoe;               /*0:ON   1:OFF */
    U8 name[16];
    U8 pass[16];
    U32 ip;

    PPPOE_SET(){
		memset( this, 0x00, sizeof(PPPOE_SET) );
	}
};

struct SNTP_SET
{
    U8 sntp_add[256];
    U16 sntp_port;    /*Ĭ��Ϊ123*/
    int enable_sntp;  /*0��������1������*/

    SNTP_SET(){
		memset( this, 0x00, sizeof(SNTP_SET) );
	}
};


struct NETWORK_SETUP
{
    U8 enable_DHCP;         /*�Ƿ�����DHCP 0:ON �� 1:OFF */
    U32 ip_address;         /*����IP��ַ */
    U32 net_mask;           /*�������� */
    U32 net_gateway;        /*���� */

    U8 line_speed;

    U16 server_port;        /* �˿�1~65535 */
    U8 enable_DNS;          /* �Ƿ����������  0:ON,1:OFF */
    U32 DNS_ip_address1;
    U32 DNS_ip_address2;
    U16 http_port;
    U32 alarm_add;
    U8 alarm_port;
    U32 alarm_center_ipaddr;
    U16 alarm_center_port;
   // SNTP_SET sntp_set;            //2009-02-13�Ķ��ĵط�
    PPPOE_SET pppoe_set;

    NETWORK_SETUP(){
		memset( this, 0x00, sizeof(NETWORK_SETUP) );
	}
} ;

/*RS485����*/
struct REMOTE_SETUP
{
    U8 address;
    U8 baud_rate;           // 0:2400 ; 1:4800 ; 2:9600 ; 3:19200 ; 4:38400
    U8 data_bit;            // ����λ  0:6;  1:7;   2:8
    U8 stop_bit;            //ֹͣλ   0:1;  1:2
    U8 parity_bit;          //У��λ   0:��; 1:��У��;  2:żУ��
};

struct NVR_LIST
{
    U32 nvr_ip;
    int nvr_port;
    U8 password[MAX_PASSWORD_MANAGER_CHAR + 1];
    U8 username[10];
    
    NVR_LIST(){
		memset( this, 0x00, sizeof(NVR_LIST) );
	}
};

struct MAIL_SETUP
{
    U8 email;                /*email 0�������� 1������*/
    U8 send_to[MAX_SEND_TO_MAIL][MAX_ADDRESS_CHAR+1] ; /* ?256*/
    U8 TRM[MAX_SEND_TO_MAIL] ;               /* 0 : ; 1 : */
    U8 ERR[MAX_SEND_TO_MAIL] ;               /* 0 : ; 1 : */  
    U8 smtp_server_address[MAX_ADDRESS_CHAR+1] ; /* ?256 */
    U16 smtp_port ;        /* 1~65535 */
    U8 pop_server_address[MAX_ADDRESS_CHAR+1] ; /* ?256 */
    U8 authentication ;    /* 1,OFF;2 : POP ;3 : SMTP */
    U8 user_name[MAX_USER_NAME_CHAR+1] ; /* �û��� */
    U8 password[MAX_PASSWORD_CHAR+1] ;   /* ���� */
    U8 from[MAX_ADDRESS_CHAR+1];
    U8 email_name[MAX_MAIL_SUBJECT_CHAR+1];

    MAIL_SETUP(){
		memset( this, 0x00, sizeof(MAIL_SETUP) );
	}

};

/*������*/
struct DECODE_CHAN
{
    U8 select;     /*ѡ����ӻ���Ѳ�� 00:��û��ѡ�� 01:���� 02:Ѳ��*/
    U8 moni_chan;  /*����Ƶ����*/
    U32 seq_chan;  /*Ѳ��Ƶ���� ��λ����*/
    U16 poll_time;  /*��Ѳʱ��*/

    DECODE_CHAN(){
		memset( this, 0x00, sizeof(DECODE_CHAN) );
	}

};

struct DECODE_SETUP
{
    U16 decode_num;      /*���������*/
    U32 decode_addr;      /*�����ַ*/
    U8  decode_flag;     /*1��IPCAM���� 0:NVR*/
    U16 decode_port;     /*����˿�*/
    U8 decode_pass[16];/*��������*/
    U8 decode_user[32];/*�����û���*/
    U8 decode_resol;     /*�ֱ���*/
  //  U8 channel_sel[6];  /*ͨ��ѡ��*/
 //   U8 decode_display;  /*��ʾ����*/
    U8 split;            /*����ָ�  0 : ��ָ�  01: 1ͨ�����  02: 2ͨ�����*/
    DECODE_CHAN decode_chan[2]; /*������ͨ����ʾ*/
    
    DECODE_SETUP(){
		memset( this, 0x00, sizeof(DECODE_SETUP) );
	}

} ;

struct DDNS_SETUP
{
    U8 ddns_server;
    char ddns_user[16];
    char ddns_pass[8];
    char ddns_domain[24];
    char ddns_server_addr[24];
    U8 ddns_port;

     DDNS_SETUP(){
		memset( this, 0x00, sizeof(DDNS_SETUP) );
	}
};

struct NET_DLNVR_COMMUNICATION_SETUP
{
    NETWORK_SETUP network;  /* �����趨 */
   // REMOTE_SETUP remote;    /* 485���趨 */
    NVR_LIST nvrlist[8];    /*NVR �б� */
    MAIL_SETUP mail_setup; /*email ����, 2009-02-04 add*/
    DECODE_SETUP decode_setup[DECODE_MAX];/*2009-04-08 add */
    DDNS_SETUP ddns;

    NET_DLNVR_COMMUNICATION_SETUP(){
		memset( this, 0x00, sizeof(NET_DLNVR_COMMUNICATION_SETUP) );
	}
};

/*�û�����*/
struct USER_NAME_PASSWORD
{
    U8 name[ MAX_USER_NAME_CHAR];
    U8 password[MAX_PASSWORD_MANAGER_CHAR];
    U32 adv_rights;      /***�߼� ***/
    U32 rec_rights;      /*¼��Ȩ�ޣ���λ����Ƶ��*/
    U32 playback_rights; /*�ط�Ȩ�ޣ���λ����Ƶ��*/

    USER_NAME_PASSWORD(){
		memset( this, 0x00, sizeof(USER_NAME_PASSWORD) );
	}
};

struct NET_DLNVR_USER_MANAGE_SETUP
{
   USER_NAME_PASSWORD name_pass[32];

   NET_DLNVR_USER_MANAGE_SETUP(){
		memset( this, 0x00, sizeof(NET_DLNVR_USER_MANAGE_SETUP) );
	}
};

struct NET_DLNVR_SEARCH_NET_SETUP
{
    U32 from;
    U32 to;

    NET_DLNVR_SEARCH_NET_SETUP(){
		memset( this, 0x00, sizeof(NET_DLNVR_SEARCH_NET_SETUP) );
	}
};

/*RVS�ṹ����*/
struct  NET_DLNVR_SYS_RVS
{
    U32 ip;                             //IP��ַ
    U16  port;                           //���ӵĶ˿ں�
    U8   proto_type;                     // ���ӷ�ʽ TCP��UDP��MC
    U8   type;                           //ipcamera, dvr, dvs��
        //0-IPC5  1-IPC3(�����) 2-������  3-����IPC
  //  U8   can_rec;                        //�Ƿ��ܹ�¼�� 1����  0������
    U8   coder_path;                   //
    U8   name[CHANNEL_NAME_LENGTH];      //����
    U8   password[RVS_PWD_LENGTH];
    U8   alias[CHANNEL_NAME_LENGTH];
    U8   talk_port;                     //�Խ��˿ں�
    
	NET_DLNVR_SYS_RVS(){
		memset( this, 0x00, sizeof(NET_DLNVR_SYS_RVS) );
	}
};

struct ALM_STAGE
{
    U32  start_time;     //��ʼʱ��
    U32  end_time;       //����ʱ��
    int flag;            //1:ѡ��  0��ûѡ
//    U32 input   ;       //�����¼�����λ������ǰ12λΪ�����������Ϊipc����

    ALM_STAGE(){
		memset( this, 0x00, sizeof(ALM_STAGE) );
	}
};

/* ���ظ澯���� */
struct NET_DLNVR_EVENT_SETUP
{
    U32         alm_rec_time ;
    U32         pre_rec_time ;
    ALM_STAGE   stage[4] ;
    U8 ararm_port;       /*��������(1-12)*/
    U8 alarm_beep;         /*�澯ʱ�Ƿ���� */
    U16 monitor_spot;       /*�����л���0-32��0�����л�*/
    U8 alarm_out[4];         /*������� 0:�� 1:��*/
    U16 alarm_time;          /*����ʱ��*/
    U8 alarm_channel[4];
    U8 alarm_in_flag;       /*�������0��OFF ��1��ON*/

    NET_DLNVR_EVENT_SETUP(){
		memset( this, 0x00, sizeof(NET_DLNVR_EVENT_SETUP) );
	}
} ;

/**********************��������************************************************/
struct SERIAL_CONFIG_NVR
{
    U8 baud_rate;   // ������
                        //0 1200
                        //1 2400
                        //2 4800
                        //3 9600
                        //4 19200
                        //5 38400
        /**************************************************************************
        ���ڿ����ֽڣ�Ĭ��ֵΪ0x42�������ض������£�
            7   6   5   4   3   2   1   0
            E   A   A   B   C   C   D   D
        A ���ط�ʽ��0-���أ� 1-Ӳ�����أ� 2-�������
        B ֹͣλ�� 0-1���� 1-2��
        C ��żУ�飬0-���飬 1-��У�飬 2-żУ��
        D ����λ�� 0-6λ��1-7λ�� 2-8λ
        E ����ѡ�� 0-����1�� 1-����1
        **************************************************************************/
    U8  com_config;

     SERIAL_CONFIG_NVR(){
		memset( this, 0x00, sizeof(SERIAL_CONFIG_NVR) );
	}
};


/**********************��̨����************************************************/
struct CRUISE_STRATEGY
{
    U8 route_id;//Ĭ��0xFF��ʾ��Ч·��
    U8 start_hour ;    // ���Կ�ʼʱ��
    U8 start_min ;
    U8 end_hour ;      // ���Խ���ʱ��
    U8 end_min ;

    CRUISE_STRATEGY(){
		memset( this, 0x00, sizeof(CRUISE_STRATEGY) );
	}
};

struct ROUTE_NVR
{
    U8 stay_duration;   // ͣ��ʱ��
    U8 speed;           // ��̨��ת�ٶ�
    U8 cruise[14];      // Ѳ����·

    ROUTE_NVR(){
		memset( this, 0x00, sizeof(ROUTE_NVR) );
	}
};

#define CH_DOME_SPEED  4
//��̨�����趨
struct NET_DLNVR_DOME_CONFIG
{
    SERIAL_CONFIG_NVR serial_cfg;
        /**************************************************************************
        ��̨�����ֽڣ������ض������£�
        7   8   6   5   4   3   2   1   0
                    A   A   B   C   D   E
        A ��̨�ٶ� 0��2
        B ����ת�� 0-�� 1-�ǣ� ��ͬ
        C ��ֱ����
        D ˮƽ����
        E �Ƿ�Ѳ��
        **************************************************************************/
    U8  dome_config;
    U8  type;         //��̨����
                          //��������ǰ��һ��
    U8  addr;         //��̨��ַ ��Χ:0~255
    char preset_name[MAX_PRESET_NUM][32];
    ROUTE_NVR route[MAX_ROUTE_NUM];  // Ѳ��·������
    CRUISE_STRATEGY strategy[4];      //
    U8    is_ext_ptz; //0 : ����  1�� ��

     NET_DLNVR_DOME_CONFIG(){
		memset( this, 0x00, sizeof(NET_DLNVR_DOME_CONFIG) );
	}
};

/******************������������************************************************/
struct LINK_PTZ
{
    U8  type ;    //��������, factory value : 0
                      // 0 : call preset
                      // 1 : call cruise
                      // 2 : call auto cruise
    U8   no;      // ������Ԥ�Ƶ�Ż���Ѳ��·��factory value : 0
    LINK_PTZ(){
		memset( this, 0x00, sizeof(LINK_PTZ) );
	}
};

/* IPCAM�澯���� */
struct NET_DLNVR_ALARM_PARAM
{
    U32         alm_rec_time ;
    U32         pre_rec_time ;
    ALM_STAGE   stage[4] ;
    U8  ararm_enable;        /*0:������1������*/
    U8 alarm_beep;         /*�澯ʱ�Ƿ���� */
    U16 monitor_spot;       /*�����л���0-32��0�����л�*/
    U8 alarm_out[4];         /*������� 0:�� 1:��*/
    U16 alarm_time;          /*����ʱ��*/
    U8 alarm_channel[4];
    U8 enable_link_ptz; //2010-08-05 add
    LINK_PTZ ptz[SYS_RVS_MAX];    //2010-08-05 add

    NET_DLNVR_ALARM_PARAM(){
		memset( this, 0x00, sizeof(NET_DLNVR_ALARM_PARAM) );
	}
};


struct NET_DLNVR_SYSTEM_PARA_SET
{
  //  int run;    //2009-02-04,add���ݲ�ʹ��
    U32 rec;                /*1:Ϊ¼��0��ֹͣ¼�������Լ�ʹ�õı�ʶ����̨��������*/
    U32 para;             //   ��̨�ò�����
    U8 harddisk_alam;
    NET_DLNVR_SYSTEM_SETUP system_setup;
    NET_DLNVR_RECORDING_SETUP rec_setup;
    NET_DLNVR_EVENT_SETUP event_setup[12]; //event_setup[0]��ʾIPCamera������ event_setup[1]-event_setup[12] ��Ӧ��ʾNVR��12���澯���뱨��
    NET_DLNVR_DISPLAY_SETUP display_setup;
    NET_DLNVR_COMMUNICATION_SETUP communication;
    NET_DLNVR_USER_MANAGE_SETUP user_manage_setup;
    NET_DLNVR_SEARCH_NET_SETUP search_net_setup;  //2009-04-08, add
    NET_DLNVR_SYS_RVS rvs_data[SYS_RVS_MAX];
    NET_DLNVR_ALARM_PARAM alarm_para[SYS_RVS_MAX];

    NET_DLNVR_ALARM_PARAM motion_para[SYS_RVS_MAX];    //2010-08-05, add
    NET_DLNVR_DOME_CONFIG yun[SYS_RVS_MAX];       //2009-08-05, add

    NET_DLNVR_SYSTEM_PARA_SET(){
		memset( this, 0x00, sizeof(NET_DLNVR_SYSTEM_PARA_SET) );
	}
};
//NVR�������Ľṹ�� end----------------------------------------------------

//DM60�����������-------------------------------------------------------------
typedef struct 
{
	WORD RevisePara100;	//��������ϵ��*100
	WORD ReviseTemp100;	//���������¶�*100
	WORD AimDistance;	//����Ϊ��λ
	WORD AimHimidity;	//ʪ��
	WORD SurroundTemp;	//�����¶�
	WORD MeasureTempClass;	//��ͷѡ�񼴲��µ�λ
	WORD AreaType;	//����������ͣ�������ƽ��
	WORD AlarmEnable;	//����ʹ�� 1-On 0_OFf
	WORD AlarmTemp100;	//�����¶�
	WORD AlarmColor;	//����ɫ
	WORD LensId;	//��ͷѡ�񼴲��µ�λ�����ں���ͬMeasureTempClass
	WORD AutoSaveTime;	//�Զ�������ʱ�䣬����ʱû��
	WORD AutoZeroTime;	//�Զ�����ʱ����
	WORD RefeTempType;	//�ο��¶�����0�޲ο����£���
	WORD RefeTempValue;	//�ο��¶�ֵ����ѡ��ο�����Ϊ�ο�ʱ�õ�
	WORD ColorRuleId;	//ɫ��ѡ����SCR����ͬ��������ֵ����ɫ�꣬�����ı�ɫ��ķ����˳��
	WORD UpColorId;	//����ɫ��
	WORD DownColorId;	//����ɫ��
	WORD IsoThermColorId;	//����ɫ��
	WORD IsoThermTemp100;	//�����¶�
	WORD IsoThermHight100;	//���¸߶�
	WORD ShowColorRule;	//�Ƿ���ʾɫ��
	WORD ShowData;	//�Ƿ���ʾ����
	WORD AvgImageCount;	//ͼ��ƽ������������û��
	WORD ShowAreaCursor;	//��ʾ������ʹ��
	WORD LanguageType;	//������������
	WORD StorageType;	//�洢����.0:NandFlash��1:CF��
	WORD VideoOutType;	//��Ƶ�����ʽ0:PAL;1:
	WORD LaserEnable;	//���⿪������
	DWORD MeasureTempUnit;	//�¶ȵ�λ��0:��;1�H;2K;
	WORD TransMenu;	//�˵��Ƿ�͸��
	WORD CloseLedTime;	//�ر���Ļʱ��
	WORD ClosePowerTime;	//�رյ�Դʱ��
	WORD TempDisplay;	//�¶��Ƿ���ʾYes/No
	WORD SteerStartPos;	//�����ʼλ��,�ǲ���Ӧ���������ʾ��
	WORD SteerEndPos;	//�������λ�ã��ǲ���Ӧ���������ʾ��
	WORD DimFiterLevel;	//˥��Ƭֵ
	WORD ImageMode;	//ͼ��ģʽ 0 -�ֶ� 1-�Զ�
}SYSTEMCFG_DM60,  *LPSYSTEMCFG_DM60 ;


typedef struct 
{
	int index;	//0��3
	int Enable;	//1-On; 0-Off
	int Mode;	//0-High; 1-Low; 2-Avg
	int StartX;	//Ŀ���������
	int StartY;	//Ŀ���������
	int F;	//������*100
	int Value;//	�¶�ֵ*100(��Ч)
}DMMEASURE_POINT, *LPDMMEASURE_POINT;

typedef struct 
{
	int Enable;	//1-On; 0-Off
	int LineType;	//0-Hori; 1-Vert; 2-Slash
	int Mode;	//0-High; 1-Low; 2-Avg
	int StartX;	//Ŀ���������
	int StartY;	//Ŀ���������
	int EndX;	//Ŀ���յ�����
	int EndY;	//Ŀ���յ�����
	int AnchorX;	//�������еĲ��µ�
	int AnchorY;	//�������еĲ��µ�
	int F;	//������*100
	int Value;//	�¶�ֵ*100(��Ч)
}DMMEASURE_LINE, *LPDMMEASURE_LINE;

typedef struct 
{
	int index;	//0��3
	int Enable;	//1-On; 0-Off
	int Mode;	//0-High; 1-Low; 2-Avg
	int StartX;	//Ŀ���������
	int StartY;	//Ŀ���������
	int EndX;	//Ŀ���յ�����
	int EndY;	//Ŀ���յ�����
	int F;	//������*100
	int Value;//	�¶�ֵ*100(��Ч)
}DMMEASURE_AREA, *LPDMMEASURE_AREA;

//�ϴ�ʵʱ������Ϣ
typedef struct
{
	DWORD dwTempType;//0-Point,1-Line,2-Area
	DWORD Index;//���
	DWORD Gray;//�Ҷ�
	DWORD Temp;//�¶�
}NET_DLDVR_DMTEMP,*LPNET_DLDVR_DMTEMP;

//�ϴ�ʵʱ������Ϣ
typedef struct
{
	DWORD dwTempType;//0-Point,1-Line,2-Area
	DWORD Index;//���
	float Gray;//�Ҷ�
	float Temp;//�¶�
}NET_DLDVR_DMTEMP_EX,*LPNET_DLDVR_DMTEMP_EX;

//�ϴ�ʵʱ������Ϣ
typedef struct
{
	DWORD dwTempNum;//�¶���Ϣ����
	NET_DLDVR_DMTEMP_EX TempValue[8];
}NET_DLDVR_DMTEMP_INFO,*LPNET_DLDVR_DMTEMP_INFO;


//DM60�����¶ȸ澯����-----------------------------------------
#define TEMP_ALARM_SYSTEM	0	//ϵͳ�澯
#define TEMP_ALARM_POINT	1	//���µ�澯
#define TEMP_ALARM_LINE		2	//���µ�澯
#define TEMP_ALARM_AREA		3	//���µ�澯

//�ڸ澯����Ϊsystemʱ�ĸ澯״̬
#define TEMP_ALARM_SYSTEM_OK				0	//ϵͳOK
#define TEMP_ALARM_SYSTEM_SDRAM				1	//SDRAM��ȡʧ��
#define TEMP_ALARM_SYSTEM_FLASH				2	//Flash��ȡʧ�ܣ� 
#define TEMP_ALARM_SYSTEM_VRAM				3	//��ƵоƬ����ʧ�ܣ� 
#define TEMP_ALARM_SYSTEM_INITSOFTWARE		4	//�����ʼ��ʧ�ܣ�
#define TEMP_ALARM_SYSTEM_INITFPGA			5	//FPGA��ʼ��ʧ�ܣ� 
#define TEMP_ALARM_SYSTEM_DECOMPRESSION		6	//���ѹʧ�ܣ� 
#define TEMP_ALARM_SYSTEM_EXCEPTIONAL		7	//����쳣�� 
#define TEMP_ALARM_SYSTEM_SHUTDOWN			8	//���������ػ��� 
#define TEMP_ALARM_SYSTEM_TEMPEXCEPTIONAL	9	//�����ڲ��¶ȳ��¹ػ���
#define TEMP_ALARM_SYSTEM_AREATEMPALARM		10	//������¸��»���±�����

//�ڸ澯���Ͳ���systemʱ�ĸ澯״̬
#define TEMP_ALARM_OK		0	//û�б���
#define TEMP_ALARM_HIGHER	1	//���±���
#define TEMP_ALARM_LOWER	2	//���±���

//DM60ǰ������״̬��������
#define  NET_DVR_SENSORPOWER_ON		0 //������ǰ��
#define  NET_DVR_SENSORPOWER_OFF	1 //�ر�����ǰ��	
#define  NET_DVR_SENSORPOWER_CHG	2 //�ı�����ǰ��״̬

//�ϴ��¶ȸ澯��Ϣ
typedef struct
{
	DWORD dwAlarmType;//0-ϵͳ��1-Point, 2-Line, 3-Area
	DWORD Index;//��ţ�dwAlarmTypeΪ0ʱ�����ֵ��Ч��
	DWORD Status;//״̬
	DWORD AlarmTemp;//�����¶�
	DWORD ReferenceTemp;//�����ο��¶�
}NET_DLDVR_DMTEMP_ALARM,*LPNET_DLDVR_DMTEMP_ALARM;

//DM60���ܷ����澯�ĸ澯����
#define ANALYS_ALARM_WIRE	0	//���߱���
#define ANALYS_ALARM_AREA	1	//��������

typedef struct
{
	DWORD dwAlarmType;//0-����, 1-����
	DWORD Index;//���
	DWORD num;//����Ŀ�����
}NET_DLDVR_DMANALYS_ALARM, *LPNET_DLDVR_DMANALYS_ALARM;

//2009-02-27 added ���й���������õ��豸��Ϣ
struct NET_DLSERVER_DEVICEINFO
{
    char		 DeviceID[DEVICE_ID_LENGTH];        //DVR��ʶID
    char         Name[80];             //��ƵԴ����
    DWORD        AddrType;             //1Ϊ��̬��ַ������ 2Ϊϵͳ����ID�Զ�����
    char         IPAddr[32];           //IP��ַ
    WORD         TCPPort;              //TCP���Ӷ˿�
    DWORD        ChannleNum;           // ͨ������
    char         userName[32];         //20080109 08
    char         ManagePassWord[12];   // ����Ա��������	
	
    char		 ParentID[DEVICE_ID_LENGTH];     //�������ID
    char         ZoneName[32];         //DVR������������Ϣ
};

typedef struct _ST_FUNC_PROPERTY
{
	U8				mainType; 	//�����ͣ�0-�ӿ� 1-���� 2-����
    U16				subType;		//���������Ͳ�ͬ�����嶨��
}NET_DLFUNC_PROPERTY,*LPNET_DLFUNC_PROPERTY;

typedef struct
{
	int	realHandle;	//���Ӿ��
	U8  mainStream;		//0-������ 1-������
	U8	audioPresent;	//0-�ر���Ƶ 1-������Ƶ(Ϊ�˽�ʡ�������䣬����ѡ���Ƿ���Ƶ)
	U8	sendVideo;	//0-ֻ��֡ͷ���� 1-�ָ���Ƶ��������
}NET_DLDVR_STREAMSTATE,*LPNET_DVR_STREAMSTATE;



#pragma pack()

/************************************************************************/
//   �ص���������                                                                  
/************************************************************************/
//2009-02-24 added ��������Ƶ֡�ص���������
//2010-08-26 dwDataType �޸�Ϊ dwFrameRate ��ʾ֡��(1---25)
typedef VOID(CALLBACK *fYUVDataCallBack) (LONG lHandle, DWORD /*dwDataType*/dwFrameRate, BYTE *pBuffer, 
										  DWORD nWidth, DWORD nHeight, int err, DWORD dwUser);

//��Ƶ���ص�����	
//lRealHandle,NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�ķ���ֵ 
//dwDataType, �������� 0xEE��ϵͳͷ����   0xEF��������
//pBuffer,  ��ż������ݵĻ����� 
//dwBufSize��pBuffer�Ĵ�С 
//FrameType, 0x00-��ƵI֡  0x01-��ƵP֡ 0x02-��ƵB֡ 0x03-��Ƶ֡ 0x09-AAC��ʽ��Ƶ֡ 0x81-JPEG����ֵֻ��dwDataTypeΪ0xEFʱ��Ч
//FrameRate,ʵ��֡�ʣ���ÿ�����֡(1---25)����ֵֻ��dwDataTypeΪ0xEFʱ��Ч
//nWidth��ͼ���ȡ���ֵֻ��dwDataTypeΪ0xEFʱ��Ч
//nHeight��ͼ��߶ȡ���ֵֻ��dwDataTypeΪ0xEFʱ��Ч
//time��֡ʱ�䡣��ֵֻ��dwDataTypeΪ0xEFʱ��Ч
//err�������� 
//dwUser���û���������� 
typedef VOID(CALLBACK *fRealDataCallBack_EX)(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize, 
											 INT FrameType, INT FrameRate, DWORD nWidth, DWORD nHeight, 
											 NET_DLDVR_TIME* time, int err, DWORD dwUser);

extern "C"
{
/* 	����˵��:��ʼ��SDK����������SDK����ǰ�����ȵ��øú���
 *	�������: �� 
 *	�������: ��
 *	��������: TRUE:�ɹ� FALSE:ʧ��
 *	˵��: (��)  
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_Init();

/* 	����˵��:�ͷ�SDK��Դ
 *	�������: �� 
 *	�������: ��
 *	��������: TRUE:�ɹ� FALSE:ʧ��
 *	˵��: (��)  
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_Cleanup();

/* 	����˵��:������Ϣ�Ľ��մ��ھ��
 *		��Ϣ���ͣ�#define WM_DLDVR_NET_EXCEPTION_NOTIFY		(WM_APP + 800)	//����Ԥ���������֪ͨ
 *                #define WM_DLDVR_PLAYBACK_OVER_NOTIFY		(WM_APP + 801)	//�طŽ���֪ͨ��Ϣ	
 *	              #define WM_DLDVR_TALKER_EXCEPTION_NOTIFY	(WM_APP + 802)	//�Խ�����֪ͨ
 *				  #define WM_DLDVR_LOGOUT_NOTIFY			(WM_APP + 803)	//�û��ǳ���Ϣ,������ʧȥ����
 *				  #define WM_DLDVR_RESOLUTION_CHANGE_NOTIFY	(WM_APP + 804)//���ӻ�ط�ʱʱ�ֱ��ʷ����ı��֪ͨ��Ϣ
 *			 	  #define WM_DLDVR_VIDEOFORMAT_CHANGE_NOTIFY	(WM_APP + 805)//���ӻ�ط�ʱʱ��Ƶ��ʽ�����ı��֪ͨ��Ϣ
 *	�������: hWnd��������Ϣ�Ĵ��ھ�� 
 *	�������: ��
 *	��������: TRUE:�ɹ� FALSE:ʧ��
 *	˵��: (��)  
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_SetRecvDVRMessageHWnd(HWND hWnd);//2008-09-01Modify

/* 	����˵��:ע��ص������������豸������Ϣ�ȣ�ͬʱ�ص����豸IP���������ֲ�ͬ�豸��
 *	�������: cbMessCallBack���ص�����
				BOOL(CALLBACK *fMessageCallBack)(LONG lCommand, char *sDVRIP, char *pBuf, DWORD dwBufLen);
				lCommandֵ��
					#define COMM_ALARM 0x1100 //������Ϣ ��Ӧ�ṹ NET_DLDVR_ALARMINFO 
					#define COMM_ALARM_EX	 0x1101	//600���͵ı�����Ϣ ��Ӧ�ṹ NET_DLDVR_ALARMINFO_600
					#define COMM_TRADEINFO   0x1500 //ATMDVR�����ϴ�������Ϣ 
					#define SERIAL_NUMBER	 0x1600 //DVR�ϱ������к�
					#define DISKCHANNEL_STATE 0x1700 //������ʱ�ϴ�Ӳ��״̬��ͨ��¼��״̬��Ϣ 
					#define RVS_INFO		 0x1800 //IPCamera�ϴ���RVS��Ϣ
					#define EXCEPTION_NOTIFY 0x1900 //�쳣���ߵ���Ϣ����Ӧ�ṹ NET_DLDVR_EXCEPTION ��Ӧ����֪ͨ��Ϣ 
					#define DM_TEMP			0x2000	//DM60���͵�ʵʱ������Ϣ����Ӧ�ṹNET_DLDVR_DMTEMP
					#define DMTEMP_ALARM	0x2010	//DM60���͵��¶ȸ澯��Ϣ����Ӧ�ṹNET_DLDVR_DMTEMP_ALARM
					#define DM_ANALYS_ALARM		0x2011	//DM60���͵����ܷ����澯��Ϣ����Ӧ�ṹNET_DLDVR_DMANALYS_ALARM
					#define	PLAYBACK_OVER		0x2020	//�طŽ�������Ӧ�ṹNET_DLDVR_EXCEPTION
					#define RESOLUTION_CHANGE	0x2021	//�ֱ��ʸı䣬��Ӧ�ṹNET_DLDVR_EXCEPTION
					#define VIDEOFORMAT_CHANGE				0x2022	//��Ƶ��ʽ�ı䣬��Ӧ�ṹNET_DLDVR_EXCEPTION
				sDVRIP:�豸IP��ַ 
				pBuf:�ص�������Ϣ
				dwBufLen���ص�������Ϣ����
 *	�������: ��
 *	��������: TRUE:�ɹ� FALSE:ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_SetDVRMessCallBack(BOOL (CALLBACK *fMessCallBack)(LONG lCommand,CHAR *sDVRIP,CHAR *pBuf,DWORD dwBufLen));

/* 	����˵��:ע��ص������������豸������Ϣ�ȣ�ͬʱ�ص����û�ID���������ֲ�ͬ�û���
 *	�������: cbMessCallBack���ص�����
				BOOL(CALLBACK *fMessageCallBack)(LONG lCommand, char *sDVRIP, char *pBuf, DWORD dwBufLen);
					lCommandֵ��
						#define COMM_ALARM 0x1100 //������Ϣ ��Ӧ�ṹ NET_DLDVR_ALARMINFO 
						#define COMM_ALARM_EX	 0x1101	//600���͵ı�����Ϣ ��Ӧ�ṹ NET_DLDVR_ALARMINFO_600
						#define COMM_TRADEINFO   0x1500 //ATMDVR�����ϴ�������Ϣ 
						#define SERIAL_NUMBER	 0x1600 //DVR�ϱ������к�
						#define DISKCHANNEL_STATE 0x1700 //������ʱ�ϴ�Ӳ��״̬��ͨ��¼��״̬��Ϣ 
						#define RVS_INFO		 0x1800 //IPCamera�ϴ���RVS��Ϣ
						#define EXCEPTION_NOTIFY 0x1900 //�쳣���ߵ���Ϣ����Ӧ�ṹ NET_DLDVR_EXCEPTION ��Ӧ����֪ͨ��Ϣ 
						#define DM_TEMP			0x2000	//DM60���͵�ʵʱ������Ϣ����Ӧ�ṹNET_DLDVR_DMTEMP
						#define DMTEMP_ALARM	0x2010	//DM60���͵��¶ȸ澯��Ϣ����Ӧ�ṹNET_DLDVR_DMTEMP_ALARM
						#define DM_ANALYS_ALARM					0x2011	//DM60���͵����ܷ����澯��Ϣ����Ӧ�ṹNET_DLDVR_DMANALYS_ALARM
						#define	PLAYBACK_OVER		0x2020	//�طŽ�������Ӧ�ṹNET_DLDVR_EXCEPTION
						#define RESOLUTION_CHANGE	0x2021	//�ֱ��ʸı䣬��Ӧ�ṹNET_DLDVR_EXCEPTION
						#define VIDEOFORMAT_CHANGE				0x2022	//��Ƶ��ʽ�ı䣬��Ӧ�ṹNET_DLDVR_EXCEPTION
					lUserID���û���¼ID����NET_DLDVR_Login�ķ���ֵ 
					pBuf:�ص�������Ϣ
					dwBufLen���ص�������Ϣ����
 *	�������: ��
 *	��������: TRUE:�ɹ� FALSE:ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_SetDVRMessCallBack_EX(BOOL (CALLBACK *fMessCallBack_EX)(LONG lCommand,LONG lUserID,CHAR *pBuf,DWORD dwBufLen));

/* 	����˵��:�����������ӳ�ʱʱ������ӳ��Դ�����
 *	�������: dwWaitTime����ʱʱ�䣬��λ���룬ȡֵ�����300��ʵ�����ʱʱ��Ϊconnect��ʱʱ�䣬����������Ч  
			  dwTryTimes�����ӳ��Դ������ò���������Ŀǰû��ʹ�ã�
 *	�������: ��
 *	��������: TRUE:�ɹ� FALSE:ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_SetConnectTime(DWORD dwWaitTime,DWORD dwTryTimes);

/* 	����˵��:��ȡSDK�İ汾��Ϣ�������ӿڣ�
 *	�������:��
 *	�������: ��
 *	��������: SDK�汾��Ϣ
 *	˵��: Ŀǰ��SDK�汾�޷�ͨ���ýӿڻ�ȡ
 */
NET_DLDVR_API DWORD			STDCALL NET_DLDVR_GetSDKVersion();

/* 	����˵��:���������������豸�����ϴ��ı�������Ϣ��
 *	�������:sLocalIP��PC ����IP ��ַ������������Ŀǰ�ò�����Ч
			 wLocalPort��PC���ؼ����˿ںţ����û�����
 *	�������: ��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_StartListen(CHAR *sLocalIP,WORD wLocalPort);

/* 	����˵��:ֹͣ����
 *	�������:��
 *	�������: ��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_StopListen();

/* 	����˵��:�û���¼��DVR
 *	�������:sDVRIP��DVRIP
			 wDVRPort��DVR�˿�
			 sUserName�� �û���
			 sPassword������
 *	�������: lpDeviceInfo��DVR���豸��Ϣ
 *	��������: �û�ID����ֵ����Ψһ�ԣ��������豸�Ĳ�������Ҫͨ����IDʵ�֡�����¼ʧ���򷵻ظ���
 *	˵��: �ýӿڲ�������DM60�ӿ�
 */
NET_DLDVR_API LOGIN_HANDLE	STDCALL NET_DLDVR_Login(CHAR *sDVRIP,WORD wDVRPort,CHAR *sUserName,CHAR *sPassword,LPNET_DLDVR_DEVICEINFO lpDeviceInfo);

/* 	����˵��:�û��ǳ�DVR
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *	�������: ��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_Logout(LONG lUserID);

/* 	����˵��:���ڻ�ȡ���һ�β����Ĵ�����
 *	�������:��
 *	�������:��
 *	��������:������
 *	˵��: 
 */
NET_DLDVR_API DWORD			STDCALL NET_DLDVR_GetLastError();

/* 	����˵��:��ʼʵʱ����
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 lpClientInfo��Ԥ������ 
 *	�������:��
 *	��������:���Ӿ����������ʾʧ��
 *	˵��: 
 */
NET_DLDVR_API LONG			STDCALL NET_DLDVR_RealPlay(LONG lUserID,LPNET_DLDVR_CLIENTINFO lpClientInfo);

/* 	����˵��:�ر�ʵʱ����
 *	�������:lRealHandle��NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�����ķ���ֵ
 *	�������:��
 *	��������:TRUE���ɹ���FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_StopRealPlay(LONG lRealHandle);

/* 	����˵��:����Ԥ����Ƶ��ʾ����
 *	�������:lRealHandle��NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�����ķ���ֵ
			 dwBrightValue�����ȣ�ȡֵ��Χ0-99 
			 dwContrastValue���Աȶȣ�ȡֵ��Χ0-99 
			 dwSaturationValue�����Ͷȣ�ȡֵ��Χ0-99 
			 dwHueValue��ɫ�ȣ�ȡֵ��Χ0-99 
 *	�������:��
 *	��������:TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_ClientSetVideoEffect(LONG lRealHandle,DWORD dwBrightValue,DWORD dwContrastValue, DWORD dwSaturationValue,DWORD dwHueValue);

/* 	����˵��:��ȡԤ����Ƶ��ʾ����
 *	�������:lRealHandle��NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�����ķ���ֵ
 *	�������:pBrightValue�����ȣ�ȡֵ��Χ0-99 
			 pContrastValue���Աȶȣ�ȡֵ��Χ0-99 
			 pSaturationValue�����Ͷȣ�ȡֵ��Χ0-99 
			 pHueValue��ɫ�ȣ�ȡֵ��Χ0-99 
 *	��������:TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_ClientGetVideoEffect(LONG lRealHandle,DWORD *pBrightValue,DWORD *pContrastValue, DWORD *pSaturationValue,DWORD *pHueValue);

//�ӿ��Ѿ�ʵ��
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_RigisterDrawFun(LONG lRealHandle,VOID (CALLBACK* fDrawFun)(LONG lRealHandle,HDC hDc, INT picWidth, INT picHeight, DWORD dwUser),DWORD dwUser);
/*�����ӿ�*/
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_SetPlayerBufNumber(LONG lRealHandle,DWORD dwBufNum);

/* 	����˵��:��������
 *	�������:lRealHandle����NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�����ķ���ֵ
 *	�������:��
 *	��������:TRUE���ɹ���FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_OpenSoundShare(LONG lRealHandle);

/* 	����˵��:�ر�����
 *	�������:lRealHandle����NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�����ķ���ֵ
 *	�������:��
 *	��������:TRUE���ɹ���FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_CloseSoundShare(LONG lRealHandle);

/* 	����˵��:��ȡ��ǰͨ����������С
 *	�������:lRealHandle����NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�����ķ���ֵ
 *	�������:��
 *	��������:����ֵ��0-100����������ʾʧ��
 *	˵��: 
 */
NET_DLDVR_API INT			STDCALL NET_DLDVR_GetVolume(LONG lRealHandle);	//2008-10-06

/* 	����˵��:���õ�ǰͨ����������С
 *	�������:lRealHandle����NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�����ķ���ֵ
			 wVolume��Ҫ���õ�����ֵ��ȡֵ��Χ0-100
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_SetVolume(LONG lRealHandle,WORD wVolume);	//2008-10-06

/* 	����˵��:���������ݱ��浽ָ�����ļ���
 *	�������:lRealHandle����NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�����ķ���ֵ
			 sFileName��Ҫ������ļ���
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_SaveRealData(LONG lRealHandle,CHAR *sFileName);

/* 	����˵��:ֹͣ�����������
 *	�������:lRealHandle����NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�����ķ���ֵ
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_StopSaveRealData(LONG lRealHandle);

/* 	����˵��:���û�ȡʵʱ�ط���Ƶ���ݵĻص�����
 *	�������:lRealHandle��NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�����ķ���ֵ
			 realDataCallBack����ȡ�������ݵĻص����� 
			 VOID realDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE pBuffer, DWORD dwBufSize, int err, DWORD dwUser);
				lRealHandle,NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�ķ���ֵ 
				dwDataType, �������� 0xEE��ϵͳͷ����  0xEF��������  0x1����׼��Ƶ��  0x2����׼��Ƶ�� 
				pBuffer,  ��ż������ݵĻ����� 
				dwBufSize��pBuffer�Ĵ�С 
				err�������� 
				dwUser���û���������� 
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_SetRealDataCallBack(LONG lRealHandle,VOID(CALLBACK *fRealDataCallBack) (LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize, int err, DWORD dwUser),DWORD dwUser);

/* 	����˵��:�����ڲ��ŵļ��ӻ���ץͼ���浽bmp�ļ���
 *	�������:lRealHandle��NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�����ķ���ֵ
			 sPicFileName��Ҫ�����ͼƬ��������Ŀ������ļ�·������ʱNetSDK����ݵ�ǰʱ���Զ�����һ��bmp�ļ�����Ҳ�������ļ�·��+�ļ���
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_CapturePicture(LONG lRealHandle,CHAR *sPicFileName);

/* 	����˵��:���ɹؼ�֡
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
			 lChannel��ͨ���ţ���0��ʼ
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_MakeKeyFrame(LONG lUserID, LONG lChannel);

/* 	����˵��:��̨���ƣ���Ҫ�Ƚ��м���
 *	�������:lRealHandle��NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�����ķ���ֵ
			 dwPTZCommand������ֵ
				#define LIGHT_PWRON						3	// ��ͨ�ƹ��Դ 
				#define WIPER_PWRON						2	// ��ͨ��ˢ���� 
				#define FAN_PWRON						4	// ��ͨ���ȿ��� 
				#define HEATER_PWRON					5	// ��ͨ���������� 
				#define AUX_PWRON						6	// ��ͨ�����豸���� 

				#define ZOOM_IN							11	// �������ٶ�SS���(���ʱ��) 
				#define ZOOM_OUT						12	// �������ٶ�SS��С(���ʱ�С) 
				#define FOCUS_NEAR						13	// �������ٶ�SSǰ�� 
				#define FOCUS_FAR						14	// �������ٶ�SS��� 
				#define IRIS_OPEN						15	// ��Ȧ���ٶ�SS���� 
				#define IRIS_CLOSE						16	// ��Ȧ���ٶ�SS��С 
				#define TILT_UP							21	// ��̨��SS���ٶ����� 
				#define TILT_DOWN						22	// ��̨��SS���ٶ��¸� 
				#define PAN_LEFT						23	// ��̨��SS���ٶ���ת 
				#define PAN_RIGHT						24	// ��̨��SS���ٶ���ת 
				#define PAN_AUTO						29	// ��̨��SS���ٶ������Զ�ɨ�� 
			 dwAction����ֹ̨ͣ������ʼ������1����ʼ��0��ֹͣ
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_PTZControl(LONG lRealHandle,DWORD dwPTZCommand,DWORD dwAction);

/* 	����˵��:��̨���ƣ�����򿪼���
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
			 lChannel��ͨ����
			 dwPTZCommand������ֵ
					#define LIGHT_PWRON			3	// ��ͨ�ƹ��Դ 
					#define WIPER_PWRON			2	// ��ͨ��ˢ���� 
					#define FAN_PWRON			4	// ��ͨ���ȿ��� 
					#define HEATER_PWRON		5	// ��ͨ���������� 
					#define AUX_PWRON			6	// ��ͨ�����豸���� 
					#define ZOOM_IN				11	// �������ٶ�SS���(���ʱ��) 
					#define ZOOM_OUT			12	// �������ٶ�SS��С(���ʱ�С) 
					#define FOCUS_NEAR			13	// �������ٶ�SSǰ�� 
					#define FOCUS_FAR			14	// �������ٶ�SS��� 
					#define IRIS_OPEN			15	// ��Ȧ���ٶ�SS���� 
					#define IRIS_CLOSE			16	// ��Ȧ���ٶ�SS��С 
					#define TILT_UP				21	// ��̨��SS���ٶ����� 
					#define TILT_DOWN			22	// ��̨��SS���ٶ��¸� 
					#define PAN_LEFT			23	// ��̨��SS���ٶ���ת 
					#define PAN_RIGHT			24	// ��̨��SS���ٶ���ת 
					#define PAN_AUTO			29	// ��̨��SS���ٶ������Զ�ɨ�� 	
			 dwAction����ֹ̨ͣ������ʼ������1����ʼ��0��ֹͣ
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API BOOL	STDCALL NET_DLDVR_PTZControl_Other(LONG lUserID,LONG lChannel,DWORD dwPTZCommand,DWORD dwAction);

/* 	����˵��:͸����̨���ƣ���Ҫ�ȴ򿪼���
 *	�������:lRealHandle�����Ӿ������NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�����ķ���ֵ
			 pPTZCodeBuf����̨��������
			 dwBufSize�������
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR���͡�
 *  ע��Ŀǰ�����л��ǽ�lRealHandle�����ǵ�½��������д���2010-04-01��
 */
NET_DLDVR_API BOOL	STDCALL NET_DLDVR_TransPTZ(LONG lRealHandle,CHAR *pPTZCodeBuf,DWORD dwBufSize);

/* 	����˵��:͸����̨���ƣ�����򿪼���
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
			 lChannel��ͨ����
			 pPTZCodeBuf����̨��������
			 dwBufSize�������
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API BOOL	STDCALL NET_DLDVR_TransPTZ_Other(LONG lUserID,LONG lChannel,CHAR *pPTZCodeBuf,DWORD dwBufSize);

/* 	����˵��:��̨Ԥ��λ���ƣ���Ҫ�ȴ򿪼���
 *	�������:lRealHandle�����Ӿ������NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�����ķ���ֵ
			 dwPTZPresetCmd����̨Ԥ�õ�����
					#define SET_PRESET		1	// ����Ԥ�õ� 
					#define CLE_PRESET		2	// ���Ԥ�õ� 
					#define GOTO_PRESET		3	// ת��Ԥ�õ�
			 dwPresetIndex��Ԥ�õ����ţ����֧��128��Ԥ�õ�
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������600���͡�IPCamera��NVR����
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_PTZPreset(LONG lRealHandle,DWORD dwPTZPresetCmd,DWORD dwPresetIndex);

/* 	����˵��:��̨Ԥ��λ���ƣ�����򿪼���
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
			 lChannel��ͨ���ţ���0��ʼ
			 dwPTZPresetCmd����̨Ԥ�õ�����
					#define SET_PRESET			1	// ����Ԥ�õ� 
					#define CLE_PRESET			2	// ���Ԥ�õ� 
					#define GOTO_PRESET			3	// ת��Ԥ�õ�
			 dwPresetIndex��Ԥ�õ����ţ����֧��128��Ԥ�õ�
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��:�ýӿڲ�������IPCamera��NVR���� 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_PTZPreset_Other(LONG lUserID,LONG lChannel,DWORD dwPTZPresetCmd,DWORD dwPresetIndex);

/* 	����˵��:Ѳ�����ƣ�����򿪼���
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
			 lChannel����Ѳ������̨������ͨ���ţ���0��ʼ
			 PTZCruiseCmd:��̨�������� 
					#define FILL_PRE_SEQ	30 // ��Ԥ�õ����Ѳ������ 
					#define SET_SEQ_DWELL	31 // ����Ѳ����ͣ��ʱ�� 
					#define SET_SEQ_SPEED	32 // ����Ѳ���ٶ� 
					#define CLE_PRE_SEQ		33 // ��Ԥ�õ��Ѳ��������ɾ�� 
					#define RUN_SEQ			37	// ��ʼѲ�� 
					#define STOP_SEQ		38	// ֹͣѲ�� 
			byCruiseRoute��Ѳ��·�������֧��8��·�� 
			byCruisePoint�����֧��14����
			wInput����ͬѲ������ʱ��ֵ��ͬ��Ԥ�õ�(���128)��ʱ��(���255)���ٶ�(���15) 
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_PTZCruise_Other(LONG lUserID,LONG lChannel,DWORD dwPTZCruiseCmd,BYTE byCruiseRoute, BYTE byCruisePoint, WORD wInput);

//���ٶȵ���̨����,dwSpeedֵ:1-3
/* 	����˵��:���ٶȵ���̨���ƣ���Ҫ�ȴ򿪼���
 *	�������:lRealHandle�����Ӿ������NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�����ķ���ֵ
			 dwPTZCommand������ֵ
					#define LIGHT_PWRON			3	// ��ͨ�ƹ��Դ 
					#define WIPER_PWRON			2	// ��ͨ��ˢ���� 
					#define FAN_PWRON			4	// ��ͨ���ȿ��� 
					#define HEATER_PWRON		5	// ��ͨ���������� 
					#define AUX_PWRON			6	// ��ͨ�����豸���� 
					#define ZOOM_IN				11	// �������ٶ�SS���(���ʱ��) 
					#define ZOOM_OUT			12	// �������ٶ�SS��С(���ʱ�С) 
					#define FOCUS_NEAR			13	// �������ٶ�SSǰ�� 
					#define FOCUS_FAR			14	// �������ٶ�SS��� 
					#define IRIS_OPEN			15	// ��Ȧ���ٶ�SS���� 
					#define IRIS_CLOSE			16	// ��Ȧ���ٶ�SS��С 
					#define TILT_UP				21	// ��̨��SS���ٶ����� 
					#define TILT_DOWN			22	// ��̨��SS���ٶ��¸� 
					#define PAN_LEFT			23	// ��̨��SS���ٶ���ת 
					#define PAN_RIGHT			24	// ��̨��SS���ٶ���ת 
					#define PAN_AUTO			29	// ��̨��SS���ٶ������Զ�ɨ�� 	
			 dwAction����ֹ̨ͣ������ʼ������1����ʼ��0��ֹͣ
			 dwSpeed����̨�ٶȣ�ȡֵ��Χ1-3
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_PTZControlWithSpeed(LONG lRealHandle, DWORD dwPTZCommand, DWORD dwAction, DWORD dwSpeed);

/* 	����˵��:���ٶȵ���̨���ƣ�����򿪼���
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
			 lChannel��ͨ���ţ���0��ʼ
			 dwPTZCommand������ֵ
					#define LIGHT_PWRON			3	// ��ͨ�ƹ��Դ 
					#define WIPER_PWRON			2	// ��ͨ��ˢ���� 
					#define FAN_PWRON			4	// ��ͨ���ȿ��� 
					#define HEATER_PWRON		5	// ��ͨ���������� 
					#define AUX_PWRON			6	// ��ͨ�����豸���� 
	
					#define ZOOM_IN				11	// �������ٶ�SS���(���ʱ��) 
					#define ZOOM_OUT			12	// �������ٶ�SS��С(���ʱ�С) 
					#define FOCUS_NEAR			13	// �������ٶ�SSǰ�� 
					#define FOCUS_FAR			14	// �������ٶ�SS��� 
					#define IRIS_OPEN			15	// ��Ȧ���ٶ�SS���� 
					#define IRIS_CLOSE			16	// ��Ȧ���ٶ�SS��С 
					#define TILT_UP				21	// ��̨��SS���ٶ����� 
					#define TILT_DOWN			22	// ��̨��SS���ٶ��¸� 
					#define PAN_LEFT			23	// ��̨��SS���ٶ���ת 
					#define PAN_RIGHT			24	// ��̨��SS���ٶ���ת 
					#define PAN_AUTO			29	// ��̨��SS���ٶ������Զ�ɨ�� 	
			 dwAction����ֹ̨ͣ������ʼ������1����ʼ��0��ֹͣ
			 dwSpeed����̨�ٶȣ�ȡֵ��Χ1-3
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_PTZControlWithSpeed_Other(LONG lUserID, LONG lChannel, DWORD dwPTZCommand, DWORD dwAction, DWORD dwSpeed);

//Զ���ļ��ط�
/* 	����˵��:��ʼ����¼���ļ�
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
			 lChannel��ͨ����,��λ��ʾ
			 dwFileType���ļ�����  
					0xff-ȫ����0-��ʱ¼��1-�ƶ���⣻2-��������(��ʱ��ѯ����¼��������ͨ����¼������ܷ�������¼��)��3-�������4-�ֶ�¼��
			 lpStartTime����ʼʱ��
			 lpStopTime������ʱ��
 *	�������:��
 *	��������:���Ҿ������ΪNET_DVR_FindClose()�Ⱥ����Ĳ��������ظ�����ʾʧ��
 *	˵��: ��������IPCamera����
 */
NET_DLDVR_API LONG			STDCALL NET_DLDVR_FindFile(LONG lUserID,LONG lChannel,DWORD dwFileType, LPNET_DLDVR_TIME lpStartTime, LPNET_DLDVR_TIME lpStopTime);

/* 	����˵��:������һ��¼���ļ�
 *	�������:lFindHandle�����Ҿ������NET_DLDVR_FindFile()�����ķ���ֵ
 *	�������:lpFindData����ѯ�����ļ���Ϣ
 *	��������:0���ɹ������ظ�����ʾʧ��
 *	˵��: 
 */
NET_DLDVR_API LONG			STDCALL NET_DLDVR_FindNextFile(LONG lFindHandle,LPNET_DLDVR_FIND_DATA lpFindData);

/* 	����˵��:�ر��ļ����ҡ�
 *	�������:lFindHandle�����Ҿ������NET_DLDVR_FindFile()�����ķ���ֵ
 *	�������:��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ڲ��ҽ�������ֹ����ʱ������ô˽ӿ�
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_FindClose(LONG lFindHandle);

/* 	����˵��:��¼�����ƽ���Զ�̻ط�
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
			 sPlayBackFileName����Ҫ���лطŵ�¼���ļ���
			 hWnd�����лطŵĴ��ھ��
 *	�������:��
 *	��������: ���ž������ΪNET_DLDVR_StopPlayBack�Ⱥ����Ĳ��������ظ�����ʾʧ��
 *	˵��: �ýӿڲ�������IPCamera����
 */
NET_DLDVR_API LONG			STDCALL NET_DLDVR_PlayBackByName(LONG lUserID,CHAR *sPlayBackFileName, HWND hWnd);

/* 	����˵��:��ʱ��ν���Զ�̻ط�
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
			 lChannel��ͨ���ţ�1,3,0,36���Ժ�İ汾��0��ʼ�� 1,3,0,35����ǰ�İ汾��1��ʼ��2010-09-15 modifty��
			 lpStartTime����ʼʱ��
			 lpStopTime������ʱ��
			 hWnd�����лطŵĴ��ھ��
 *	�������:��
 *	��������: ���ž������ΪNET_DLDVR_StopPlayBack�Ⱥ����Ĳ��������ظ�����ʾʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API LONG			STDCALL NET_DLDVR_PlayBackByTime(LONG lUserID,LONG lChannel, LPNET_DLDVR_TIME lpStartTime, LPNET_DLDVR_TIME lpStopTime, HWND hWnd);

/* 	����˵��:�طſ���
 *	�������:lPlayHandle���طž������NET_DLDVR_PlayBackByName()��NET_DLDVR_PlayBackByTime()�����ķ���ֵ
			 dwControlCode����������
				#define NET_DLDVR_PLAYSTOP					2//ֹͣ����
				#define NET_DLDVR_PLAYPAUSE					3//��ͣ����
				#define NET_DLDVR_PLAYRESTART				4//�ָ�����
				#define NET_DLDVR_PLAYFAST					5//���
				#define NET_DLDVR_PLAYSLOW					6//����
				#define NET_DLDVR_PLAYNORMAL				7//�����ٶ�
				#define NET_DLDVR_PLAYFRAME					8//��֡��
				#define NET_DLDVR_PLAYSTARTAUDIO			9//������
				#define NET_DLDVR_PLAYSTOPAUDIO				10//�ر�����
				#define NET_DLDVR_PLAYAUDIOVOLUME			11//��������
				#define NET_DLDVR_PLAYSETPOS				12//�ı��ļ��طŵĽ���
				#define NET_DLDVR_PLAYGETPOS				13//��ȡ�ļ��طŵĽ���
				#define NET_DLDVR_PLAYGETTIME				14//��ȡ��ǰ�Ѿ����ŵ�ʱ��
				#define NET_DLDVR_GETPLAYAUDIOVOLUME		21//��õ�ǰ��������С
				#define NET_DLDVR_PLAY_DOUBLESPEED			22	//2����
				#define NET_DLDVR_PLAY_HALFSPEED			23	//1/2�ٶ�
				#define NET_DLDVR_PLAY_SETPOS_BYTIME		24 //�ط�ʱ��ʱ��ٷֱ���ת��ĳλ��
				#define NET_DLDVR_PLAY_OCTUPLESPEED			25	//8����,2010-07-06 add
				#define NET_DLDVR_PLAY_SIXTEENSPEED			26	//16����,2010-07-06 add
				#define NET_DLDVR_PLAY_32SPEED				27	//32����,2010-07-06 add
			 dwInValue�����õĲ������������ļ��طŵĽ���(����ֵNET_DLDVR_PLAYSETPOS)ʱ���˲�����ʾ����ֵ
 *	�������: lpOutValue����ȡ�Ĳ��������ȡ������С������ֵNET_DLDVR_GETPLAYAUDIOVOLUME �����˲������ǵ�ǰ������ֵ
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_PlayBackControl(LONG lPlayHandle,DWORD dwControlCode,DWORD dwInValue,DWORD *lpOutValue);

/* 	����˵��:ֹͣԶ�̻ط�
 *	�������:lPlayHandle���طž������NET_DLDVR_PlayBackByName()��NET_DLDVR_PlayBackByTime()�����ķ���ֵ
 *	�������:��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_StopPlayBack(LONG lPlayHandle);


/* 	����˵��:����Զ�̻طŵ����ݵ�ָ���ļ�
 *	�������:lPlayHandle���طž������NET_DLDVR_PlayBackByName()��NET_DLDVR_PlayBackByTime()�����ķ���ֵ
			 sFileName���ļ���
 *	�������:��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_PlayBackSaveData(LONG lPlayHandle,CHAR *sFileName);

/* 	����˵��:ֹͣ����Զ�̻طŵ�����
 *	�������:lPlayHandle���طž������NET_DLDVR_PlayBackByName()��NET_DLDVR_PlayBackByTime()�����ķ���ֵ
 *	�������:��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_StopPlayBackSave(LONG lPlayHandle);

/* 	����˵��:��ȡ¼��ط�ʱ��ʾ��OSDʱ��
 *	�������:lPlayHandle���طž������NET_DLDVR_PlayBackByName()��NET_DLDVR_PlayBackByTime()�����ķ���ֵ
 *	�������:lpOsdTime��OSDʱ��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_GetPlayBackOsdTime(LONG lPlayHandle, LPNET_DLDVR_TIME lpOsdTime);

/* 	����˵��:������Զ�̻طŵĻ���ץͼ���浽bmp�ļ���
 *	�������:lPlayHandle���طž������NET_DLDVR_PlayBackByName()��NET_DLDVR_PlayBackByTime()�����ķ���ֵ
			 sFileName��Ҫ�����ͼƬ��������Ŀ������ļ�·������ʱNetSDK����ݵ�ǰʱ���Զ�����һ��bmp�ļ�����Ҳ�������ļ�·��+�ļ���
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_PlayBackCaptureFile(LONG lPlayHandle,CHAR *sFileName);

/* 	����˵��:����¼���ļ������������ļ�
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
			 sDVRFileName��Ҫ���ص�¼���ļ���
			 sSavedFileName��ϣ�����浽������¼���ļ���
 *	�������:��
 *	��������:���ؾ������ΪNET_DLDVR_StopGetFile()��NET_DLDVR_GetDownloadPos()�Ĳ��������ظ�����ʾʧ��
 *	˵��: �ýӿڲ�������IPCamera����
 */
NET_DLDVR_API LONG			STDCALL NET_DLDVR_GetFileByName(LONG lUserID,CHAR *sDVRFileName,CHAR *sSavedFileName);

/* 	����˵��:����ʱ��������ļ�
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
			 lChannel��ͨ���ţ���0��ʼ(2010-09-17֮ǰ�İ汾ͨ���Ŵ�1��ʼ)
			 lpStartTime����ʼʱ��
			 lpStopTime������ʱ��
			 sSavedFileName��ϣ�����浽������¼���ļ���
 *	�������:��
 *	��������:���ؾ������ΪNET_DLDVR_StopGetFile()��NET_DLDVR_GetDownloadPos()�Ĳ��������ظ�����ʾʧ��
 *	˵��: ���а�����ָ��ʱ����ڵ��ļ��������浽ͬһ���ļ��С��ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API LONG			STDCALL NET_DLDVR_GetFileByTime(LONG lUserID,LONG lChannel, LPNET_DLDVR_TIME lpStartTime, LPNET_DLDVR_TIME lpStopTime, CHAR *sSavedFileName);

/* 	����˵��:ֹͣ����
 *	�������:lFileHandle�����ؾ������NET_DLDVR_GetFileByName()��NET_DLDVR_GetFileByTime()�����ķ���ֵ		 
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera����
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_StopGetFile(LONG lFileHandle);

/* 	����˵��:��ȡ���ؽ���
 *	�������:lFileHandle�����ؾ������NET_DLDVR_GetFileByName()��NET_DLDVR_GetFileByTime()�����ķ���ֵ		 
 *	�������:��
 *	��������:����ֵ��0-100�������ظ�����ʾ��ȡʧ��
 *	˵��: 
 */
NET_DLDVR_API INT			STDCALL NET_DLDVR_GetDownloadPos(LONG lFileHandle);

/* 	����˵��:���ű����ļ�
 *	�������:fileName��Ҫ���ŵ�¼���ļ���
             hWnd�����Ŵ��ھ��
 *	�������:��
 *	��������:���ž������ΪNET_DLDVR_StopPlayFiles()��NET_DLDVR_PlayBackControl()�Ⱥ����Ĳ���
 *	˵��: 
 */
NET_DLDVR_API INT			STDCALL NET_DLDVR_PlayFiles(CHAR* fileName,HWND hWnd);

/* 	����˵��:ֹͣ���ű����ļ�
 *	�������:lFileHandle�����ž������NET_DLDVR_PlayFiles()�����ķ���ֵ
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_StopPlayFiles(LONG lFileHandle);

/* 	����˵��:�ָ���������
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��:
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_RestoreConfig(LONG lUserID);

/* 	����˵��:���������Flash��
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_SaveConfig(LONG lUserID);

/* 	����˵��:Զ������DVR
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera����
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_RebootDVR(LONG lUserID);

/* 	����˵��:Զ�̹ر�DVR
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera����
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_ShutDownDVR(LONG lUserID);

//����
/* 	����˵��:Զ�̸�������ӳ��
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
			 sFileName��Ҫ���µ�ӳ������
 *	�������:��
 *	��������:����ID����ΪNET_DLDVR_GetUpgradeState()�Ⱥ�����������������ظ�����ʾʧ��
 *	˵��:
 */
NET_DLDVR_API LONG			STDCALL NET_DLDVR_Upgrade(LONG lUserID,CHAR *sFileName);

/* 	����˵��:��ȡԶ�̸��µ�״̬
 *	�������:lUpgradeHandle������ID����NET_DLDVR_Upgrade()�����ķ���ֵ
 *	�������:��
 *	��������:״ֵ̬
				#define NET_DLDVR_UPGRADESUCESS			1000	//�����ɹ�
				#define NET_DLDVR_UPGRADEING			1010	//��������
 *	˵��: �ýӿڲ�������IPCamare����
 */
NET_DLDVR_API INT				STDCALL NET_DLDVR_GetUpgradeState(LONG lUpgradeHandle);

/* 	����˵��:��ȡԶ�̸��µ�״̬������
 *	�������:lUpgradeHandle������ID����NET_DLDVR_Upgrade()�����ķ���ֵ
 *	�������:nPostion����ǰ���µĽ��ȣ�0-100
 *	��������:״ֵ̬
				#define NET_DLDVR_UPGRADEING_DOWNLOAD		1011	//��������-���ؾ���
				#define NET_DLDVR_UPGRADEING_APPLYING		1012	//��������-Ӧ�þ���
 *	˵��: �ýӿڲ�������IPCamare����
 */
NET_DLDVR_API INT				STDCALL NET_DLDVR_GetUpgradeSubState(LONG lUpgradeHandle, INT &nPostion);

/* 	����˵��:ȡ������
 *	�������:lUpgradeHandle������ID����NET_DLDVR_Upgrade()�����ķ���ֵ
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��:
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_CloseUpgradeHandle(LONG lUpgradeHandle);


//WEB������2007-09-10
/* 	����˵��:Զ�̸���������web
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
			 sFileName��Ҫ���µ�ӳ������
 *	�������:��
 *	��������:����ID����ΪNET_DLDVR_GetWebUpdateState()�Ⱥ�����������������ظ�����ʾʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR�ӿ�
 */
NET_DLDVR_API LONG			STDCALL NET_DLDVR_WebUpdate(LONG lUserID,CHAR *sFileName);
/* 	����˵��:��ȡweb���µ�״̬
 *	�������:lUpgradeHandle������ID����NET_DLDVR_WebUpdate()�����ķ���ֵ
 *	�������:��
 *	��������:״ֵ̬
				#define NET_DLDVR_UPGRADESUCESS			1000	//�����ɹ�
				#define NET_DLDVR_UPGRADEING				1010	//��������
 *	˵��:�ýӿڲ�������IPCamera��NVR�ӿ� 
 */
NET_DLDVR_API INT				STDCALL NET_DLDVR_GetWebUpdateState(LONG lUpgradeHandle);
/* 	����˵��:��ȡԶ�̸���web��״̬������
 *	�������:lUpgradeHandle������ID����NET_DLDVR_WebUpdate()�����ķ���ֵ
 *	�������:nPostion����ǰ���µĽ��ȣ�0-100
 *	��������:״ֵ̬
				#define NET_DLDVR_UPGRADEING_DOWNLOAD		1011	//��������-���ؾ���
				#define NET_DLDVR_UPGRADEING_APPLYING		1012	//��������-Ӧ�þ���
 *	˵��: �ýӿڲ�������IPCamera��NVR�ӿ�
 */
NET_DLDVR_API INT				STDCALL NET_DLDVR_GetWebUpgradeSubState(LONG lUpgradeHandle, INT &nPostion);
/* 	����˵��:ȡ��web����
 *	�������:lUpgradeHandle������ID����NET_DLDVR_WebUpdate()�����ķ���ֵ
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR�ӿ�
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_CloseWebUpdateHandle(LONG lUpgradeHandle);

/* 	����˵��:Զ�̸�ʽ��Ӳ��
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 lDiskNumber��Ӳ�̺ţ���0 ��ʼ��0xff ��ʾ����Ӳ��	 
 *	�������:��
 *	��������:��ʽ��ID������NET_DLDVR_GetFormatProgress()�����Ĳ���
 *	˵��: �ýӿڲ�������IPCamera��NVR�ӿ�
 */
NET_DLDVR_API LONG			STDCALL NET_DLDVR_FormatDisk(LONG lUserID,LONG lDiskNumber);
/* 	����˵��:��ȡ��ʽ��Ӳ�̵Ľ���
 *	�������:lFormatHandle����ʽ���������NET_DLDVR_FormatDisk()�����ķ���ֵ 
 *	�������:pCurrentFormatDisk,��ǰ���ڽ��и�ʽ����Ӳ�̵�Ӳ�̺�
			 pCurrentDiskPos,��ǰӲ�̵ĸ�ʽ�����ȣ�0-100��
			 pFormatStatic,��ǰӲ�̵ĸ�ʽ��״̬
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR�ӿ�
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_GetFormatProgress(LONG lFormatHandle,LONG *pCurrentFormatDisk,LONG *pCurrentDiskPos,LONG *pFormatStatic);

/* 	����˵��:��������֪ͨ�����ϴ��澯��Ϣ
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *	�������:��
 *	��������:�澯ID����Ϊ��������NET_DLDVR_CloseAlarmChan()�Ĳ���
 *	˵��: 
 */
NET_DLDVR_API LONG			STDCALL NET_DLDVR_SetupAlarmChan(LONG lUserID);
/* 	����˵��:��������֪ͨ���������ϴ��澯��Ϣ
 *	�������:lAlarmHandle���澯ID����NET_DLDVR_SetupAlarmChan()�����ķ���ֵ
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_CloseAlarmChan(LONG lAlarmHandle);

/* 	����˵��:��ȡ�豸�澯�����״̬
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *	�������:lpAlarmOutState���澯���״̬
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera����
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_GetAlarmOut(LONG lUserID,LPNET_DLDVR_ALARMOUTSTATUS lpAlarmOutState);
/* 	����˵��:�����豸�澯�����״̬
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 lAlarmOutPort���澯����˿ںţ���0��ʼ,0xff��ʾȫ��
			 lAlarmOutStatic���澯����˿ڵ�״̬
 *	�������:lpAlarmOutState���澯���״̬��0-�ر� 1-��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera����
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_SetAlarmOut(LONG lUserID,LONG lAlarmOutPort,LONG lAlarmOutStatic);

/* 	����˵��:�������Խ�
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 fVoiceDataCallBack���ص�����
				typedef void(CALLBACK *fVoiceDataCallBack)(LONG lVoiceComHandle, char *pRecvDataBuffer, DWORD dwBufSize, BYTE byAudioFlag,  DWORD dwUser);
					lVoiceComHandle��NET_DLDVR_StartVoiceCom�ķ���ֵ 
					pRecvDataBuffer�������Ƶ���ݵĻ�����ָ�� 
					dwBufSize����Ƶ���ݴ�С 
					byAudioFlag����Ƶ�������ͣ�0�����زɼ������ݣ�����󣩣�1���豸���͹������������ݣ������ 
					dwUser���û����� 
 *	�������:��
 *	��������:�Խ�ID����ΪNET_DLDVR_StopVoiceCom()�����Ĳ���
 *	˵��: 
 */
NET_DLDVR_API LONG			STDCALL NET_DLDVR_StartVoiceCom(LONG lUserID, VOID(CALLBACK *fVoiceDataCallBack)(LONG lVoiceComHandle,CHAR *pRecvDataBuffer,DWORD dwBufSize,BYTE byAudioFlag,DWORD dwUser), DWORD dwUser);

/* 	����˵��:�ر������Խ�
 *	�������:lVoiceComHandle���Խ�ID����NET_DLDVR_StartVoiceCom()�����ķ���ֵ
 *	�������:��
 *	��������:TRUE���ɹ���FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_StopVoiceCom(LONG lVoiceComHandle);

/* 	����˵��:���������㲥��PC�������ɼ�
 *	�������:��
 *	�������:��
 *	��������:�㲥ID�����ظ�����ʾʧ��
 *	˵��: 
 */
NET_DLDVR_API INT			STDCALL NET_DLDVR_ClientAudioStart();
/* 	����˵��:ֹͣ�����㲥��PC�������ɼ�
 *	�������:lVoiceComHandle���㲥ID����NET_DLDVR_ClientAudioStart()�����ķ���ֵ
 *	�������:��
 *	��������:TRUE���ɹ���FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_ClientAudioStop(INT lVoiceComHandle);
/* 	����˵��:��������ӵ����Խ���PC�������Ĺ㲥����
 *	�������:TalkHandle���㲥ID����NET_DLDVR_ClientAudioStart()�����ķ���ֵ
			 lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *	�������:��
 *	��������:���������ڹ㲥���е�ID�����ظ�����ʾʧ��
 *	˵��: 
 */
NET_DLDVR_API INT			STDCALL NET_DLDVR_AddDVR(INT TalkHandle, LONG lUserID);	//2009-06-26 add TalkHandle�� NET_DLDVR_ClientAudioStart�ķ���ֵ��

/* 	����˵��:��ָ���豸�ɽ���PC�������Ĺ㲥����ɾ��
 *	�������:TalkHandle���㲥ID����NET_DLDVR_ClientAudioStart()�����ķ���ֵ
			 dvrIndex�����������ڹ㲥���е�ID����NET_DLDVR_AddDVR()�����ķ���ֵ
 *	�������:��
 *	��������:TRUE���ɹ���FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_DelDVR(LONG TalkHandle, INT dvrIndex);

/* 	����˵��:��������ת������ȡ��������Ƶ����
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 fVoiceDataCallBack���ص�����
				typedef void(CALLBACK *fVoiceDataCallBack)(LONG lVoiceComHandle, char *pRecvDataBuffer, DWORD dwBufSize, BYTE byAudioFlag, DWORD dwUser);
					lVoiceComHandle��NET_DLDVR_StartVoiceCom_MR�ķ���ֵ 
					pRecvDataBuffer�������Ƶ���ݵĻ�����ָ�� 
					dwBufSize����Ƶ���ݴ�С 
					byAudioFlag����Ƶ�������ͣ�1���豸���͹�������Ƶ���� 
					dwUser���û����� 
 *	�������:��
 *	��������:����ת��ID����ΪNET_DLDVR_VoiceComSendData()�Ⱥ����Ĳ���
 *	˵��: 
 */
NET_DLDVR_API LONG			STDCALL NET_DLDVR_StartVoiceCom_MR(LONG lUserID, VOID(CALLBACK *fVoiceDataCallBack)(LONG lVoiceComHandle,CHAR *pRecvDataBuffer,DWORD dwBufSize,BYTE byAudioFlag,DWORD dwUser), DWORD dwUser);
/* 	����˵��:����������Ƶ����ת�����豸
 *	�������:lVoiceComHandle������ת��ID����NET_DLDVR_StartVoiceCom_MR()�����ķ���ֵ
			 pSendBuf����������
			 dwBufSize�� �������ݴ�С 
 *	�������:��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_VoiceComSendData(LONG lVoiceComHandle,CHAR *pSendBuf,DWORD dwBufSize);
////////////////////////////////////////////////////////////

/* 	����˵��:Զ�̿��Ʊ�����ʾ
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 lKeyIndex��������
 *	�������:��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��: Ŀǰ���������ϵĹ���û����ȫ��������Ҫ�������ԡ��ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_ClickKey(LONG lUserID,LONG lKeyIndex);

//Զ�̿����ֶ�¼��
/* 	����˵��:Զ�̴�����¼��
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 lChannel��ͨ���ţ���0��ʼ
			 lRecordType����������
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�����IPCamera����
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_StartDVRRecord(LONG lUserID,LONG lChannel,LONG lRecordType);
/* 	����˵��:Զ�̹ر�����¼��
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 lChannel��ͨ���ţ���0��ʼ
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�����IPCamera����
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_StopDVRRecord(LONG lUserID,LONG lChannel);

/* 	����˵��:Զ�̻�ȡ�豸����״̬
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *	�������:lpWorkState���豸����״̬
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�����IPCamera��NVR���ͺ�hisi3520����
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_GetDVRWorkState(LONG lUserID,LPNET_DLDVR_WORKSTATE lpWorkState);

//��־
/* 	����˵��:��ʼ������־�ļ�
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 lSelectMode����ѯ��ʽ
							0��ȫ��
							1��������
							2����ʱ��
							3����ʱ�������			 
			 dwMajorType����־������
			    #define MAJOR_All		0x00	// ȫ�� 
				#define MAJOR_ALARM		0x1	// ���� 
				#define MAJOR_EXCEPTION 0x2	// �쳣
				#define MAJOR_OPERATION	0x3	// ���� 
				#define MAJOR_NET		0x4   //�������
				#define MAJOR_ACC		0x5 // ������־
			 dwMinorType����־������
			 lpStartTime����ʼʱ��
			 lpStopTime������ʱ��
 *	�������:��
 *	��������:��־���Ҿ������ΪNET_DLDVR_FindNextLog()��NET_DLDVR_FindLogClose()�����Ĳ��������ظ�����ʾʧ��
 *	˵��: �ýӿڲ�������IPCamera���͡��ڴ�������0ʱ������ָ�������͵�������־
 */
NET_DLDVR_API LONG			STDCALL NET_DLDVR_FindDVRLog(LONG lUserID,LONG lSelectMode, DWORD dwMajorType,DWORD dwMinorType, LPNET_DLDVR_TIME lpStartTime, LPNET_DLDVR_TIME lpStopTime);

/* 	����˵��:������һ����־�ļ�
 *	�������:lLogHandle����־���Ҿ������NET_DLDVR_FindDVRLog()�����ķ���ֵ
 *	�������:lpLogData���ҵ�����־��Ϣ
 *	��������:0���ɹ������ظ�����ʾʧ��
 *	˵��: �ýӿڲ�������IPCamera����
 */
NET_DLDVR_API LONG			STDCALL NET_DLDVR_FindNextLog(LONG lLogHandle,LPNET_DLDVR_LOG lpLogData);

/* 	����˵��:�ر���־�ļ����ҡ�
 *	�������:lLogHandle����־���Ҿ������NET_DLDVR_FindDVRLog()�����ķ���ֵ
 *	�������:��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ڲ��ҽ�������ֹ����ʱ������ô˽ӿڣ��ýӿڲ�������IPCamera����
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_FindLogClose(LONG lLogHandle);

//��������
/* 	����˵��:��ȡ�豸��ϵͳ��������
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 dwCommand������ֵ
				#define NET_DLDVR_GET_ALLCFG				0	//������в���
				#define NET_DLDVR_GET_DEVICECFG				1	//��ȡ�豸����
				#define NET_DLDVR_GET_NETCFG				2	//��ȡ�������
				#define NET_DLDVR_GET_PICCFG				3	//��ȡͼ�����
				#define NET_DLDVR_GET_COMPRESSCFG			4	//��ȡѹ������
				#define NET_DLDVR_GET_RECORDCFG				5	//��ȡ¼��ʱ�����
				#define NET_DLDVR_GET_DECODERCFG			6	//��ȡ����������
				#define NET_DLDVR_GET_RS232CFG 				7	//��ȡ232���ڲ���
				#define NET_DLDVR_GET_ALARMINCFG 			8	//��ȡ�����������
				#define NET_DLDVR_GET_ALARMOUTCFG 			9	//��ȡ�����������
				#define NET_DLDVR_GET_TIMECFG 				10	//��ȡDVRʱ��
				#define NET_DLDVR_GET_PREVIEWCFG 			11	//��ȡԤ������
				#define NET_DLDVR_GET_VIDEOOUTCFG 			12	//��ȡ��Ƶ�������
				#define NET_DLDVR_GET_USERCFG 				13	//��ȡ�û�����
				#define NET_DLDVR_GET_EXCEPTIONCFG 			14	//��ȡ�쳣����
				#define NET_DLDVR_GET_SHOWSTRING			15	//��ȡ�����ַ�����
				#define NET_DLDVR_GET_AUXOUTCFG				16	//��ȡ�����������
				#define NET_DLDVR_GET_PICCFG_EX				17	//��ȡͼ���������չ��
				#define NET_DLDVR_GET_USERCFG_EX 			18	//��ȡ�û�����
				#define NET_DLDVR_GET_DEVICEVERSION			19  //��ȡAUX_PARAMETER���� 
				#define NET_DVR_GET_SEQ_ROUTE				20  //��ȡָ��ͨ����Ѳ������
				#define NET_DVR_GET_SYSTEMCFG_NVR	30       //������еĲ���
				#define NET_DVR_GET_RVSCFG_NVR		31     //��ȡ ��ƵԴ����          
				#define NET_DVR_GET_ALARMREC_NVR	32    //��ȡ ����¼�����
				#define NET_DVR_GET_DEMOCFG_NVR		33    //��ȡ ��̨��ز���				
			 lChannel��ͨ���ţ���0��ʼ����������Ҫͨ���ţ��ò�����Ч����Ϊ-1���� 
			 lpOutBuffer���������ݵĻ���ָ�� 
			 dwOutBufferSize���������ݵĻ��峤��(���ֽ�Ϊ��λ) 
 *	�������:			 lpBytesReturned��ʵ���յ������ݳ��� 
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_GetDVRConfig(LONG lUserID, DWORD dwCommand,LONG lChannel, LPVOID lpOutBuffer,DWORD dwOutBufferSize,LPDWORD lpBytesReturned);

/* 	����˵��:��ȡ�豸��ϵͳ��������
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 dwCommand������ֵ
				#define NET_DLDVR_SET_ALLCFG				0	//������в���
				#define NET_DLDVR_SET_DEVICECFG				1	//�����豸����
				#define NET_DLDVR_SET_NETCFG				2	//�����������
				#define NET_DLDVR_SET_PICCFG				3	//����ͼ�����
				#define NET_DLDVR_SET_COMPRESSCFG			4	//����ѹ������
				#define NET_DLDVR_SET_RECORDCFG				5	//����¼��ʱ�����
				#define NET_DLDVR_SET_DECODERCFG			6	//���ý���������
				#define NET_DLDVR_SET_RS232CFG				7	//����232���ڲ���
				#define NET_DLDVR_SET_ALARMINCFG			8	//���ñ����������
				#define NET_DLDVR_SET_ALARMOUTCFG			9	//���ñ����������
				#define NET_DLDVR_SET_TIMECFG				10	//����DVRʱ��
				#define NET_DLDVR_SET_PREVIEWCFG			11	//����Ԥ������
				#define NET_DLDVR_SET_VIDEOOUTCFG			12	//������Ƶ�������
				#define NET_DLDVR_SET_USERCFG				13	//�����û�����
				#define NET_DLDVR_SET_EXCEPTIONCFG			14	//�����쳣����
				#define NET_DLDVR_SET_SHOWSTRING			15	//���õ����ַ�����
				#define NET_DLDVR_SET_AUXOUTCFG				16	//���ø����������
				#define NET_DLDVR_SET_PICCFG_EX				17	//����ͼ���������չ��
				#define NET_DLDVR_SET_USERCFG_EX			18	//�����û�����
				#define NET_DLDVR_SET_AUX_PARAMETER			19  //����AUX_PARAMETER����
				#define NET_DVR_SET_SEQ_ROUTE				20  //����ָ��ͨ����Ѳ������
			 lChannel��ͨ���ţ���0��ʼ����������Ҫͨ���ţ��ò�����Ч����Ϊ-1���� 
			 lpInBuffer���������ݵĻ���ָ�� 
			 dwInBufferSize�� �������ݵĻ��峤��(���ֽ�Ϊ��λ) 
 *	�������:��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_SetDVRConfig(LONG lUserID, DWORD dwCommand,LONG lChannel, LPVOID lpInBuffer,DWORD dwInBufferSize);

/* 	����˵��:�����ſ�ʼ����¼���ļ�
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
			 lChannel��ͨ����,��λ��ʾ
			 dwFileType���ļ�����
				0xff-ȫ����0-��ʱ¼��1-�ƶ���⣻2-����������3-�������4-�ֶ�¼��
			 bNeedCardNum���Ƿ���Ҫ���� 1-�� 0-��
			 sCardNumber�����ţ�ֻ��bNeedCardNumΪ1ʱ��Ч
			 lpStartTime����ʼʱ��
			 lpStopTime������ʱ��
 *	�������:��
 *	��������:���Ҿ������ΪNET_DVR_FindClose()�Ⱥ����Ĳ��������ظ�����ʾʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API LONG			STDCALL NET_DLDVR_FindFileByCard(LONG lUserID,LONG lChannel,DWORD dwFileType, BOOL bNeedCardNum, BYTE *sCardNumber, LPNET_DLDVR_TIME lpStartTime, LPNET_DLDVR_TIME lpStopTime);

//����
NET_DLDVR_API VOID*			STDCALL NET_DLDVR_InitG722Decoder(INT nBitrate);
NET_DLDVR_API VOID			STDCALL NET_DLDVR_ReleaseG722Decoder(VOID *pDecHandle);
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_DecodeG722Frame(VOID *pDecHandle, BYTE* pInBuffer, BYTE* pOutBuffer);
//����
NET_DLDVR_API VOID*			STDCALL NET_DLDVR_InitG722Encoder();
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_EncodeG722Frame(VOID *pEncodeHandle,BYTE* pInBuffer, BYTE* pOutBuffer);
NET_DLDVR_API VOID			STDCALL NET_DLDVR_ReleaseG722Encoder(VOID *pEncodeHandle);

//��������
/* 	����˵��:��ȡ�豸��ϵͳ�������ã������浽�ļ���
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 sFileName��Ҫ������ļ���
 *	�������:��		
 *	��������: TRUE���ɹ���FALSE��ʧ�ܡ�
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_GetConfigFile(LONG lUserID, CHAR *sFileName);

/* 	����˵��:�������ļ�Ӧ�õ��豸��
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 sFileName���ļ���
 *	�������: ��
 *	��������: TRUE���ɹ���FALSE��ʧ�ܡ�
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_SetConfigFile(LONG lUserID, CHAR *sFileName);

/* 	����˵��:��ϵͳ�����Ի���
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 ParentWnd�������ھ��
 *	�������: ��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_OpenDvrCfgDialog(LONG lUserID, HWND ParentWnd);

/* 	����˵��:��ȡ����ӳ��İ汾
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *	�������: buf��Զ�̰汾��Ϣ
 *	��������: 0���ɹ������ظ�����ʾʧ��
 *	˵��: �ýӿڲ�������IPCamera���� 
 */
NET_DLDVR_API INT		STDCALL NET_DLDVR_GetVersion(LONG lUserID, char *buf);	//2007-07-27

/* 	����˵��:��ʼ����JPEGͼƬ
 *	�������: lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			  lChannel��ͨ���ţ���λ��ʾ
			  lpStartTime����ʼʱ��
			  lpStopTime������ʱ��
 *	�������: ��
 *	��������: JPEG���Ҿ������ΪNET_DVR_FindClose()�Ⱥ����Ĳ��������ظ�����ʾʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API LONG	STDCALL NET_DLDVR_FindJPEG( LONG lUserID, LONG lChannel, LPNET_DLDVR_TIME lpStartTime, LPNET_DLDVR_TIME lpStopTime );	//2007-07-27 add

/* 	����˵��:������һ��JPEGͼƬ
 *	�������: lFindHandle��JPEG���Ҿ������NET_DLDVR_FindJPEG()�����ķ���ֵ
 *	�������: lpFindData�����ҵ���jpeg����
 *	��������: ���ش��ڵ���0�ı�ʾ�ɹ������ظ�����ʾʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API LONG	STDCALL NET_DLDVR_FindNextJPEG( LONG lFindHandle, LPNET_DLDVR_FIND_DATA lpFindData );	//2007-07-27 add
/* 	����˵��:ֹͣ����JPEGͼƬ
 *	�������: lFindHandle��JPEG���Ҿ������NET_DLDVR_FindJPEG()�����ķ���ֵ
 *	�������: ��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API BOOL	STDCALL NET_DLDVR_FindJPEGClose( LONG lFindHandle);	//2007-07-27 add

//JPEGͼƬ ��ʾ	
/*	���ܣ���ʼ��������Ϊ�ڴ�������ʾJPEGͼƬ��׼��
 *	���������HWND hWnd����ʾjpegͼƬ�Ĵ��ھ��
 *	�������: ��
 *	�������أ�TRUE���ɹ��� FALSE��ʧ��
 *  ˵��: 
 */ 
NET_DLDVR_API BOOL	STDCALL NET_DLDVR_ShowJPEG_ByName_Init( HWND hWnd );	//2007-10-09 add
/*  ���ܣ��ڴ�������ʾJPEGͼƬ
 *	���������lFindHandle��NET_DLDVR_Login()�ķ���ֵ
			  sJPEGFileName��JPEGͼƬ������
 *	�������: ��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *  ˵��: 
 */ 
NET_DLDVR_API BOOL	STDCALL NET_DLDVR_ShowJPEG_ByName( LONG lFindHandle, char* sJPEGFileName );	//2007-07-27 add
/*  ���ܣ��ͷ���Դ
 *	���������lFindHandle��NET_DLDVR_Login()�ķ���ֵ
			  sJPEGFileName��JPEGͼƬ������
 *	�������: ��
 *  �������أ�TRUE���ɹ��� FALSE��ʧ��
 *	˵��: ��NET_DLDVR_ShowJPEG_ByName()֮�����
 */ 
NET_DLDVR_API BOOL	STDCALL NET_DLDVR_ShowJPEG_ByName_Release( void);	//2007-10-09 add

/*	���ܣ�����ָ����jpeg�ļ��������䱣����ָ���ı����ļ���
 *	���������LONG lFindHandle��NET_DLDVR_Login()�ķ���ֵ
 *		  char* pchJPEGFileName����Ҫ�����JPEGͼƬ��
 *		  char* pchSaveFileName������jpegͼƬ�ı����ļ���
 *	�������: ��
 *  �������أ�TRUE���ɹ��� FALSE��ʧ��
 *	ע�ͣ�
 */
NET_DLDVR_API BOOL	STDCALL NET_DLDVR_SaveJPEG_ByName( LONG lFindHandle, char* pchJPEGFileName, char* pchSaveFileName );	//2007-10-09 add

/* 	����˵��:��ʼJPEG����
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 lpClientInfo��Ԥ������ 
 *	�������:��
 *	��������:JPEG���Ӿ����������ʾʧ��
 *	˵��: DM642����ֻ����NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()���óɹ��Ժ󣬲�����ȷ����JPEG���ӣ�������ղ���JPEG����
 */
NET_DLDVR_API LONG			STDCALL NET_DLDVR_JpegRealPlay(LONG lUserID,LPNET_DLDVR_CLIENTINFO lpClientInfo);
/* 	����˵��: ֹͣJPEG����
 *	�������: lRealHandle������ID����NET_DLDVR_JpegRealPlay()�����ķ���ֵ
 *	�������: ��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_StopJpegRealPlay(LONG lRealHandle);

/* 	����˵��:ǿ�Ƶ�½��DVR���������������û����Ŀ���
 *	�������:sDVRIP��DVR IP
			 wDVRPort��DVR�˿�
			 sUserName�� �û���
			 sPassword������
 *	�������: lpDeviceInfo��DVR���豸��Ϣ
 *	��������: �û�ID����ֵ����Ψһ�ԣ��������豸�Ĳ�������Ҫͨ����IDʵ�֡�����¼ʧ���򷵻ظ���
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API LOGIN_HANDLE	STDCALL NET_DLDVR_ForceLogin(CHAR *sDVRIP,WORD wDVRPort,CHAR *sUserName,CHAR *sPassword,LPNET_DLDVR_DEVICEINFO lpDeviceInfo);

/* 	����˵��:����ý�岥��
 *	�������:hWnd����Ƶ���Ŵ��ھ��
			 sysHead��������ͷ���ݣ�������Ƶʱ���ȶ�ȡ������ͷ���򿪲��������ṹ����ΪDL_MP4FILE_HEAD 
			 len�����ݳ��� 
			 mode����ģʽ��1-ʵʱ��/2-�ļ�����
			 video_enc��DVR����
				#define DVR_C							0
				#define DVR_L							1
				#define DVR_LII							2
				#define DVR_MPS							3 
				#define DVR_MPF							4 
				#define DVR_MPC							5
				#define DVR_DVS							6	//����DVS
				#define DVR_ENC_H264					7	//H264������
				#define DVR_DEC_H264					8	//H264������
				#define DVR_400T						9   //�Ϻ�400Tϵ��
				#define DVR_IPCamera_GQ					10  //����IpCameara(MG3500)	
				#define DVR_NVR							11
				#define DVR_400D						12  //����400Dϵ��
				#define DVR_MPT							13   //Dm642ϵ�� MPT,����ͨ��ֻ����HD1�ֱ���
				#define DVR_IPCamera_MG3512				14   //����IpCameara	(MG3512)
				#define DVR_DEC_MP4						15	 //����C/Lϵ�н�����
				#define DVR_CMS							16	 //�������
				#define DVR_408T4						17   //408T D1�����ܻ���
				#define DVR_HISI32						18
				#define DVR_DM60						19	//DM60����
				#define DVR_106							20	//3520ϵ���µ�106�ͻ�����ͼ��ߴ�ϴ�1280*1024
				#define DVR_400D2						21  //����400D2ϵ��,��400D֮���ϵͳ����������ͬ
				#define DVR_716T						22 //2010-10-25 add�� 14CIF+2D1��3520���͡���700����(ͬ��600��3520оƬ��
				#define DVR_IPCamera_MG3515				23   //����IpCameara	(MG3515оƬ�� ��3512���͵���������3512����Ƶ�����б���룬3515�Ľ��б���봦��)	
				#define DVR_401K						24   //401K����(����Ӳ��¼��,�������ú�400D||����������ͬ)
				#define DVR_400DX						25	//DVR400Dϵ�У�������һ���½��棬Ŀǰ�ݶ�ΪDVR400DX����4/8/16·
				#define DVR_404D4						26	//����DVR404D���ͣ�����ȫD1ѡ�Ŀǰ�ݶ�����DVR404D4
 *	�������: ��
 *	��������: ���ž������ΪNET_DLDVR_CloseStream()�Ⱥ��������������ʧ�ܷ��ظ���
 *	˵��: �ɹ������ͨ��NET_DLDVR_SetStreamBuf������������������Ƶ���ݽ��в���
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_OpenStream(HWND hWnd, BYTE* sysHead, int len, int mode, int video_enc = 1 );	//2008-06-25,�޸Ľӿڣ����ӱ��뷽������

/* 	����˵��:�ر���ý�岥��
 *	�������:handle��NET_DLDVR_OpenStream�ķ���ֵ 
 *	�������: ��
 *	��������: �ɹ�����0��ʧ�ܷ��ظ���
 *	˵��: 
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_CloseStream( LONG handle );

/* 	����˵��:���ò�������������
 *	�������:handle��NET_DLDVR_OpenStream�ķ���ֵ 
			 buf,��Ƶ���� 
			 len,���ݳ��� 
 *	�������: ��
 *	��������: ���ڵ���0��ʾ�ɹ���ʧ�ܷ��ظ���
 *	˵��: 
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_SetStreamBuf(LONG handle, BYTE *buf, int len);

/* 	����˵��:��ղ�������������
 *	�������:handle��NET_DLDVR_OpenStream�ķ���ֵ 
 *	�������: ��
 *	��������: �ɹ����ش��ڵ���0��������ʧ�ܷ��ظ���
 *	˵��: 
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_EmptyStreamBuf(int handle);

/* 	����˵��:��ʼѲ��
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 lChannel����Ѳ������̨������ͨ������0��ʼ
			 CruiseNo��Ѳ���켣��
 *	�������: ��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_StartCruise( LONG lUserID, LONG lChannel, INT CruiseNo );

/* 	����˵��:����Ѳ��
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 lChannel����Ѳ������̨������ͨ������0��ʼ
			 CruiseNo��Ѳ���켣��
 *	�������: ��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��:�ýӿڲ�������IPCamera��NVR���� 
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_StopCruise( LONG lUserID, LONG lChannel, INT CruiseNo );

/* 	����˵��:�����Զ��������ļ�
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 sFileName�������ļ�������
 *	�������: ��
 *	��������: ����������ID������NET_DLDVR_GetCustomLanguageState()��NET_DLDVR_GetCustomLanguageSubState()�Ĳ�����
              �����ظ������ʾ����ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_SetCustomLanguage( LONG lUserID,CHAR *sFileName );
/* 	����˵��:��ȡ�Զ����������õ�״̬
 *	�������:lSetLanguageHandle��NET_DLDVR_SetCustomLanguage()�ķ���ֵ
 *	�������: ��
 *	��������: ״̬��
				#define NET_DLDVR_SETLANGUAGE				1020	//���������Զ�������
				#define NET_DLDVR_USETLANGUAGE_SUCESS		1023	//�������Գɹ��ɹ�
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API INT STDCALL NET_DLDVR_GetCustomLanguageState(LONG lSetLanguageHandle);
/* 	����˵��:��ȡ�Զ����������õ���״̬
 *	�������:lSetLanguageHandle��NET_DLDVR_SetCustomLanguage()�ķ���ֵ
 *	�������: nPostion�����ý���(0-100)
 *	��������: ��״̬��
				#define NET_DLDVR_SETLANGUAGE_DOWNLOAD	1021	//���������Զ�������-���������ļ�
				#define NET_DLDVR_SETLANGUAGE_APPLYING	1022	//���������Զ�������-Ӧ�������ļ���дflash��
 *	˵��: �ýӿڲ�������IPCamera��NVR���� 
 */
NET_DLDVR_API INT STDCALL NET_DLDVR_GetCustomLanguageSubState(LONG lSetLanguageHandle, INT &nPostion);

/* 	����˵��:���ò��Ŵ���
 *	�������:handle�����ž��
			 hWnd�����Ŵ��ھ��
 *	�������: ��
 *	��������: ���ش��ڵ���0�������������ظ�����ʾʧ��
 *	˵��:����򿪲�����ʱ����Ĳ���hWndΪ��,��ô�Ϳ�������Ҫ��ʱ����øú������ô����� 
 */
NET_DLDVR_API INT STDCALL NET_DLDVR_SetPlayHWnd( LONG handle, HWND hWnd );

/* 	����˵��:���������Ϣ
 *	�������:sDVRIP��DVR IP
			 wDVRPort��DVR�˿�
 *	�������: lpSystemInfo��������Ϣ
 *	��������: ���ش��ڵ���0�������������ظ�����ʾʧ��
 *	˵��:�ýӿڲ�������IPCamera����
 */
NET_DLDVR_API DWORD STDCALL NET_DLDVR_GetSystemInfo(CHAR *sDVRIP,WORD wDVRPort, LPNET_DLDVR_SYSTEMINFO lpSystemInfo);

/* 	����˵��:�ص����������ڷ���MP4�ļ�ת����wmv�ļ��Ľ���
 *	�������:pos��ת�����ȣ�0-100��
			 cbpara���û��Զ�������
 *	�������: ��
 *	��������: ���ش��ڵ���0�������������ظ�����ʾʧ��
 *	˵��:�ýӿڲ�������IPCamera��NVR����
 */
typedef INT (__stdcall *ConvertWMVCallBack)( INT pos, void* cbpara );
/* 	����˵��:��mp4�ļ�ת��Ϊ΢��wmv�ļ�
 *	�������:srcFile����Ҫ����ת����MP4�ļ�
			 dstFile��ת����Ŀ���ļ�����wmv�ļ�
			 ConvertProc���ص����������ڷ���MP4�ļ�ת����wmv�ļ��Ľ���
			 cbpara���û��Զ�������
 *	�������: ��
 *	��������: ���ش��ڵ���0�������������ظ�����ʾʧ��
 *	˵��:�ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API INT STDCALL NET_DLDVR_MP4ToWMV(char* srcFile, char* dstFile, ConvertWMVCallBack ConvertProc,
								void* cbpara = 0 );
/* 	����˵��:ֹͣ��mp4�ļ���΢��wmv�ļ���ת��
 *	�������:��
 *	�������: ��
 *	��������: ���ش��ڵ���0�������������ظ�����ʾʧ��
 *	˵��:�ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API INT STDCALL NET_DLDVR_STOPMP4ToWMV();

/* 	����˵��:�����Զ���Ŀ���logo
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 sFileName��logo�ļ�������
 *	�������: ��
 *	��������: ����log��ID������NET_DLDVR_GetCustomLogoState()��NET_DLDVR_GetCustomLogoSubState()�Ĳ�����
              �����ظ������ʾ����ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_SetCustomLogo( LONG lUserID,CHAR *sFileName );
/* 	����˵��:��ȡ����logo���õ�״̬
 *	�������:lSetLogoHandle����NET_DLDVR_SetCustomLogo()�ķ���ֵ
 *	�������: ��
 *	��������: ״̬��
				#define NET_DLDVR_SETLOGO				1030	//���������Զ���LOGO
				#define NET_DLDVR_USETLOGO_SUCESS		1033	//����LOGO�ɹ��ɹ�
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API INT STDCALL NET_DLDVR_GetCustomLogoState(LONG lSetLogoHandle);
/* 	����˵��:��ȡ����logo���õ���״̬
 *	�������:lSetLogoHandle����NET_DLDVR_SetCustomLogo()�ķ���ֵ
 *	�������: nPostion�����ý���(0-100)
 *	��������: ��״̬��
				#define NET_DLDVR_SETLOGO_DOWNLOAD		1031	//���������Զ���LOGO-����Logo�ļ�
				#define NET_DLDVR_SETLOGO_APPLYING		1032	//���������Զ���LOGO-Ӧ��Logo�ļ���дflash��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API INT STDCALL NET_DLDVR_GetCustomLogoSubState(LONG lSetLogoHandle, INT &nPostion);

/* 	����˵��:��DVR�����Զ��������ļ�
 *	�������:lSetLogoHandle����NET_DLDVR_SetCustomLogo()�ķ���ֵ
 *	�������: nPostion�����ý���(0-100)
 *	��������: ���ڵ���0��ʾ�ɹ������ظ�����ʾʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_GetLanguageFile(LONG lUserID, CHAR *sSavedFileName);

/* 	����˵��:�����ֿ�
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 sFileName����Դ�ļ�������
 *	�������: ��
 *	��������: ������Դ�ļ���ID������NET_DLDVR_GetResourceSetState()��NET_DLDVR_GetResourceSetSubState()�Ĳ�����
              �����ظ������ʾ����ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_SetResource(LONG lUserID,CHAR *sFileName);
/* 	����˵��:��ȡ�ֿ����õ�״̬
 *	�������:lSetResourseHandle����NET_DLDVR_SetResource()�ķ���ֵ
 *	�������: ��
 *	��������: ״̬��
				#define NET_DLDVR_SETRESOURCE				1040	//����������Դ
				#define NET_DLDVR_SETRESOURCE_SUCESS		1043	//������Դ�ɹ�
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API INT  STDCALL NET_DLDVR_GetResourceSetState(LONG lSetResourseHandle);
/* 	����˵��:��ȡ�ֿ����õ���״̬
 *	�������:lSetResourseHandle����NET_DLDVR_SetResource()�ķ���ֵ
 *	�������: nPostion������ֵ(0-100)
 *	��������: ��״̬��
				#define NET_DLDVR_SETRESOURCE_DOWNLOAD		1041	//����������Դ-������Դ�ļ�
				#define NET_DLDVR_SETRESOURCE_APPLYING		1042	//����������Դ-Ӧ����Դ�ļ���дflash��
 *	˵��:�ýӿڲ�������IPCamera��NVR���� 
 */
NET_DLDVR_API INT  STDCALL NET_DLDVR_GetResourceSetSubState(LONG lSetResourseHandle, INT &nPostion);

/* 	����˵��:����ֿ�
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *	�������: ��
 *	��������:  ���ڵ���0��ʾ�ɹ������ظ�����ʾʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_ClearResource(LONG lUserID);

/* 	����˵��:����澯
 *	�������:sDVRIP��DVR IP
			 port,DVR�˿�
 *	�������: ��
 *	��������:  ���ڵ���0��ʾ�ɹ������ظ�����ʾʧ��
 *	˵��: 
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_ClearAlarm(CHAR *sDVRIP, WORD port);

/* 	����˵��:���ݿ��ſ�ʼ����JPEGͼƬ
 *	�������: lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			  lChannel��ͨ���ţ���λ��ʾ
			  lpStartTime����ʼʱ��
			  lpStopTime������ʱ��
			  cardNo������
 *	�������: ��
 *	��������: JPEG���Ҿ������ΪNET_DLDVR_FindNextJPEGByCardNo()��NET_DVR_FindClose()������������������ظ�����ʾʧ��
 *	˵��: �ýӿ�ֻ֧��16·���µ�DVR����
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_FindJPEGByCardNo( LONG lUserID, LONG lChannel, LPNET_DLDVR_TIME lpStartTime, LPNET_DLDVR_TIME lpStopTime, LPCTSTR cardNo );
/* 	����˵��:���ݿ��Ų�����һ��JPEGͼƬ
 *	�������: lFindHandle��JPEG���Ҿ������NET_DLDVR_FindJPEGByCardNo()�����ķ���ֵ
			  nCardNo������
 *	�������: lpFindData�����ҵ���jpeg����
 *	��������: ���ش��ڵ���0�ı�ʾ�ɹ������ظ�����ʾʧ��
 *	˵��: 
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_FindNextJPEGByCardNo( LONG lFindHandle, LPNET_DLDVR_FIND_DATA lpFindData, CHAR *nCardNo );


/* 	����˵��:���ݲ��ž�����ý���DVR��Ϣ�Ĵ��ھ��
 *	�������:playHandle�����ž��
			 hWnd��������Ϣ�Ĵ��ھ��
 *	�������: ��
 *	��������: TRUE
 *	˵��:
 */
BOOL STDCALL NET_DLDVR_SetRecvDVRMessageHWndByHandle(long playHandle, HWND hWnd);

/* 	����˵��:����֡������bmp��ʽ���浽��Buf��(BMP��ʽ����bufд���ļ�ֱ�Ӿ���bmp�ļ�) 
 *	�������:lPlayHandle�����ž��
			 bmpBuf��BMP����
			 outBufLen��BMP���ݳ���
 *	�������: ��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��:
 */
BOOL STDCALL NET_DLDVR_CaptureBmpPictureToBuf(LONG lPlayHandle,BYTE* bmpBuf, int* outBufLen);

/* 	����˵��:���ò���ͼ�����Ƶ���� 
 *	�������:lPlayHandle�����ž��
			 nRegionNum����ʾ�������ֻ��һ����ʾ����(ͨ�����)��Ϊ0��
			 nBrightness: ���ȣ�Ĭ��50�� ��Χ0-100��
			 nContrast: �Աȶȣ�Ĭ��50�� ��Χ0-100��
			 nSaturation: ���Ͷȣ�Ĭ��50�� ��Χ0-100��
			 nHue: ɫ����Ĭ��50�� ��Χ0-100��
 *	�������: ��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��:���ȫ��ΪĬ��ֵ����������ɫ���ڣ��ýӿڲ�������IPCamera��NVR
 */
BOOL STDCALL NET_DLDVR_SetColor(LONG lPlayHandle, DWORD nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);
/* 	����˵��:��ȡ����ͼ�����Ƶ���� 
 *	�������:lPlayHandle�����ž��
			 nRegionNum����ʾ�������ֻ��һ����ʾ����(ͨ�����)��Ϊ0��
 *	�������: pBrightness: ���ȣ� ��Χ0-100��
			  pContrast: �Աȶȣ� ��Χ0-100��
			  pSaturation: ���Ͷȣ� ��Χ0-100��
			  pHue: ɫ�� ��Χ0-100��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��:�ýӿڲ�������IPCamera��NVR
 */
BOOL STDCALL NET_DLDVR_GetColor(LONG lPlayHandle, DWORD nRegionNum, int *pBrightness, int *pContrast, int *pSaturation, int *pHue);

/* 	����˵��:��¼��������
 *	�������:csIP��������IP
			 csPort���������˿�
			 sUserName���û���
			 sPassword������
 *	�������: ��
 *	��������: ��¼�������ΪNET_DLSERVER_Logout()�Ⱥ�������������������ظ�����ʾʧ��
 *	˵��:
 */
NET_DLDVR_API LOGIN_HANDLE	STDCALL NET_DLSERVER_Login(CHAR *csIP,WORD csPort,CHAR *sUserName,CHAR *sPassword);
/* 	����˵��:�ǳ�������
 *	�������:lUserID����¼�������NET_DLSERVER_Login()�ķ���ֵ
 *	�������: ��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��:
 */
NET_DLDVR_API BOOL			STDCALL NET_DLSERVER_Logout(LONG lUserID);
//��÷������豸�б�
/* 	����˵��:���ҷ������豸�б�
 *	�������:lUserID����¼�������NET_DLSERVER_Login()�ķ���ֵ
 *	�������: ��
 *	��������: 0���ɹ��� ������ʧ��
 *	˵��:
 */
NET_DLDVR_API LONG			STDCALL NET_DLSERVER_FindSvrDeviceInfo(LONG lUserID);
/* 	����˵��:������һ���������豸��Ϣ
 *	�������: lUserID����¼�������NET_DLSERVER_Login()�ķ���ֵ
 *	�������: lpFindData���������豸��Ϣ
 *	��������: 0���ɹ��� ������ʧ��
 *	˵��:
 */
NET_DLDVR_API LONG			STDCALL NET_DLSERVER_FindSvrNextDeviceInfo(LONG lUserID,NET_DLSERVER_DEVICEINFO* lpFindData);
/* 	����˵��:ֹͣ���ҷ������豸��Ϣ
 *	�������: lUserID����¼�������NET_DLSERVER_Login()�ķ���ֵ
 *	�������: ��
 *	��������: TRUE
 *	˵��:
 */
NET_DLDVR_API BOOL			STDCALL NET_DLSERVER_FindSvrClose(LONG lUserID);

/* 	����˵��:��������YUV��Ƶ�ص��Ļص�����
 *	�������: lRealHandle�����Ӿ������NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�ķ���ֵ
			  yuvDataCallBack���ص����������ڻص�YUV����
			  dwUser���û��Զ�������
 *	�������: ��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��:
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_SetYUVDataCallBack(LONG lRealHandle,fYUVDataCallBack yuvDataCallBack,DWORD dwUser);

//�澯���Ͷ���
#define ALARM_MOTION_TO_SERVER                							0  // �ƶ���ⱨ��
#define ALARM_VIDEO_LOST_TO_SERVER										1  //��Ƶ��ʧ�澯
#define ALARM_VIDEO_RESTORE_TO_SERVER									1  //��Ƶ�ָ�
#define ALARM_HARDDISK_ERROR_TO_SERVER									2  //Ӳ�̴���
#define ALARM_VIDEO_COVER_TO_SERVER										3  //��Ƶ�ڵ�
#define ALARM_EXTERNAL_TO_SERVER										4  //�ź����澯����
#define ALARM_VIDEOSOURCE_ONLINE_TO_SERVER								6  //DVR����
#define ALARM_VIDEOSOURCE_LOST_TO_SERVER								7  //DVR����
#define ALARM_TRIPWIREALARM_TO_SERVER									8  //����ǽ�澯
/* 	����˵��:֪ͨCS�����澯��Ϣ
 *	�������: lUserID����¼�������NET_DLSERVER_Login()�ķ���ֵ
			  alarmDvrIP�������澯��DVR IP
			  alarmType���澯����
			  alarmChannel���澯ͨ��
 *	�������: ��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��:
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_SendAlarmToCS(LONG lUserID, char* alarmDvrIP, short alarmType, int alarmChannel);

/* 	����˵��:����¼���ļ�
 *	�������: lUserID����¼�������NET_DLSERVER_Login()�ķ���ֵ
			  sRecFileName��¼������
 *	�������: ��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��:��������¼���ļ���Ӳ�����Զ����ǵ�ʱ�򲻻ᱻɾ�����ýӿڲ�������IPCamera��NVR����
 */
BOOL STDCALL NET_DLDVR_LockRecFile( LONG lUserID, CHAR *sRecFileName);

/* 	����˵��:��Ӳ�̸�ʽ��ΪJPEG�̣����ڱ���JPEGͼƬ
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 lDiskNumber��Ӳ�̺ţ���0 ��ʼ��0xff ��ʾ����Ӳ��	 
 *	�������:��
 *	��������:��ʽ��ID������NET_DLDVR_GetFormatProgress()�����Ĳ���
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
LONG STDCALL NET_DLDVR_FormatDiskToJPEG(LONG lUserID,LONG lDiskNumber);

/* 	����˵��:��������RVS�Զ��ϱ���Ϣ��
 *	�������:��
 *	�������: ��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������IPCamera����
 */
BOOL STDCALL NET_DLDVR_ListenIPCamera();

/* 	����˵��:�ϴ������ļ�
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 sFileName���ļ���
 *	�������: ��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������IPCamera����
 */
LONG STDCALL NET_DLDVR_UploadConfigFile_IPCamera(LONG lUserID,CHAR *sFileName);

/* 	����˵��:����DVR�ı�������
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *	�������: ��
 *	��������: �ɹ�����lUserIDֵ�� ʧ�ܷ��ظ���
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
LONG STDCALL NET_DLDVR_SetDefend(LONG lUserID);
/* 	����˵��:�ر�DVR�ı�������
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *	�������: ��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
BOOL STDCALL NET_DLDVR_SetUndefend(LONG lUserID);

/* 	����˵��:��ȡDVR�ĵ�ǰ����״̬(�Ƿ����澯����)
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *	�������: ��
 *	��������: 1-������ 0-������ ���ظ�����ʾ��ȡʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR����
 */
INT STDCALL NET_DLDVR_GetDefendStatus(LONG lUserID);

/* 	����˵��:��ȡIPCamera��ӳ����½���
 *	�������:lUpgradeHandle������ID����NET_DLDVR_Upgrade()�����ķ���ֵ
 *	�������:��
 *	��������:��ǰ���µĽ���(0-100)�����ظ�����ʾʧ��
 *	˵��: �ýӿڲ����ó�IPCamare�������������
 */
INT STDCALL NET_DLDVR_GetUpgradePos_IPCamera(LONG lUpgradeHandle);

/* 	����˵��:��NVR��������־
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 sSavedFileName��Ҫ�������־�ļ���
 *	�������:��
 *	��������:�ɹ�����0��ʧ�ܷ��ظ���
 *	˵��: �ýӿڲ������ڳ�NVR�������������
 */
LONG STDCALL NET_DLDVR_GetLog_NVR(LONG lUserID, int LogType, CHAR *sSavedFileName);

/* 	����˵��:�ص����������ڻ�ȡ��NVR����ָ�����ļ��Ľ���
 *	�������:addr����������
			 buf����������
			 percent����ǰ���صİٷֱ�
			 cbpara���û��Զ���ֵ
 *	�������:��
 *	��������:��
 *	˵��: �ýӿڲ������ڳ�NVR�������������
 */
//typedef void (WINAPI *fDownloadCallBack) (LPCTSTR addr, char *buf, int percent, void* cbpara = 0);

/* 	����˵��:��NVR�������ʼ�ģ��
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 type���ʼ�����   0���澯�ʼ�  1�������ʼ�
			 path���ʼ�����·��
			 setupdDataProc���ص�����
			 cbpara���û��Զ���ֵ
 *	�������:��
 *	��������:�ɹ�����0��ʧ�ܷ��ظ���
 *	˵��: �ýӿڲ������ڳ�NVR�������������
 */
//LONG STDCALL NET_DLDVR_DownloadMail_NVR(LONG lUserID, int type, LPCTSTR path, 
//										fDownloadCallBack setupdDataProc, void* cbpara);

#define UPGRADE_UPLOAD_STATE 1 
#define UPGRADE_UPDATE_STATE 2
/* 	����˵��:�ص����������ڻ�ȡ�ϴ��ʼ�ģ�嵽NVR�Ľ���ֵ
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 state���ϴ�״̬
				#define UPGRADE_UPLOAD_STATE 1 
				#define UPGRADE_UPDATE_STATE 2
			 len����ǰ�Ѿ��ϴ��İٷֱ�
			 cbpara���û��Զ���ֵ
 *	�������:��
 *	��������:��
 *	˵��: �ýӿڲ������ڳ�NVR�������������
 */
//typedef void (WINAPI *UpdateCallBack)(LONG lUserID, int state, int len, void* cbpara = 0);
/* 	����˵��:�ϴ��ʼ�ģ�嵽NVR
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 type���ʼ�����   0���澯�ʼ�  1�������ʼ�
			 filename���ļ���
			 UpdateProc���ص����������ڻ�ȡ�ϴ�����
			 cbpara���û��Զ���ֵ
 *	�������:��
 *	��������:��
 *	˵��: �ýӿڲ������ڳ�NVR�������������
 */
//LONG STDCALL NET_DLDVR_UploadMail_NVR(LONG lUserID, int type, const char *filename, 
//									  UpdateCallBack UpdateProc, void* cbpara);

/* 	����˵��:Զ�̻�ȡ�豸����״̬����չͨ������32·��
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *	�������:lpWorkState���豸����״̬
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: NVR��3520������Ҫ���øýӿ�����ȡ�豸����״̬��ͬʱ�ýӿڲ�������IPCamera����,
 */
BOOL STDCALL NET_DLDVR_GetDVRWorkState_EX(LONG lUserID, LPNET_DLDVR_WORKSTATE_EX lpWorkState);

/* 	����˵��:���ص����������ڻ�ȡ��׼����
 *	�������: lRealHandle�����Ӿ������NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�ķ���ֵ
			  dwDataType����������
						#define NET_DLDVR_SYSHEAD 				0xEE //ϵͳͷ����
						#define NET_DLDVR_STREAMDATA 			0xEF //������
						#define NET_DLDVR_STREAMDATA_VIDEO 		0x1	//��׼��Ƶ��
						#define NET_DLDVR_STREAMDATA_AUDIO		0x2 //��׼��Ƶ��
			  pBuffer�����ڴ��¼�����ݵĻ���
			  dwBufSize����������С
			  err�������� 
			  dwUser���û��Զ�������
 *	�������: ��
 *	��������: ��
 *	˵��:
 */
typedef VOID(CALLBACK *fStdDataCallBack) (LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize, int err, DWORD dwUser);

/* 	����˵��:���������ڻ�ȡ��׼�����Ļص�����
 *	�������: lRealHandle�����Ӿ������NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�ķ���ֵ
			  stdDataCallBack���ص����������ڻ�ȡ��׼����
			  dwUser���û��Զ�������
 *	�������: ��
 *	��������: TRUE���ɹ��� FALSE��ʧ��
 *	˵��:
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_SetStandardDataCallBack(LONG lRealHandle, fStdDataCallBack stdDataCallBack, DWORD dwUser);

/* 	����˵��: ������Ƶ��ʾ����ʾ��
 *	�������: playHandle�����ž��
			  nDeviceNum����������� 1:��ʾ��һ����ʾ��     2:��ʾ�ڶ�����ʾ��     3:��ʾ��������ʾ���ȵ�
 *	�������: ��
 *	��������: TRUE���ɹ�  FALSE��ʧ��
 *	˵��:
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_SetDDrawDevice(LONG playHandle, DWORD nDeviceNum );
	
/* 	����˵��:����ȡ����¼���ļ��Ŀ�ʼʱ��ͽ���ʱ��
 *	�������: sfile���ļ���
 *	�������: start_time����ʼʱ��
			  end_time������ʱ��
 *	��������: TRUE���ɹ�  FALSE��ʧ��
 *	˵��:
 */
BOOL STDCALL NET_DLDVR_GetLocalFileTime(CHAR *sfile,  DWORD &start_time, DWORD &end_time);	

/* 	����˵��:�����������͵ķ�ʽ��ʼ����¼���ļ�
 *	�������: lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			  lChannel��ͨ���ţ���λ��ʾ
			  dwFileType��¼���ļ������� 0-��ʱ¼�� 1-�ƶ����	2-��������  3-�����   4-�ֶ�¼�� 
			  dwAlarmType���澯���ͣ�����dwFileTypeΪ2��������¼��ʱ��Ч��
					0x90- ����
					0x91- ����
					0x92- ����
					0x93- �ۼ�
					0x94- ����
 *	�������: start_time����ʼʱ��
			  end_time������ʱ��
 *	��������: TRUE���ɹ�  FALSE��ʧ��
 *	˵��:������ͨ�澯¼��ʱ����NET_DLDVR_FindFile()�ӿڣ��������ܷ����澯¼��ʱ���øýӿ�
 */
LONG STDCALL NET_DLDVR_FindFile_EX(LONG lUserID,LONG lChannel,DWORD dwFileType, DWORD dwAlarmType, 
								 LPNET_DLDVR_TIME lpStartTime, LPNET_DLDVR_TIME lpStopTime);					


/* 	����˵��: ֡��ͨ��ѡ��2010-02-08 add
 *	�������: lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			  lChannel��ͨ���ţ���0��ʼ
			  IFrameOnly���Ƿ���ȫ�������ͣ�0-ȫ������ 1-ֻ��I֡
 *	�������: ��
 *	��������: TRUE���ɹ�  FALSE��ʧ��
 *	˵��:Ŀǰֻ������400ϵ�л���
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_SET_I_FRAME_ONLY_CHANNEL(LONG lUserID,LONG lChannel, DWORD IFrameOnly);					

/* 	����˵��: ����ָ��ͨ����������ʽ��2010-02-28 add
 *	�������: lRealHandle��ʵʱ��Ƶ�������NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�����ķ���ֵ
			  lChannel��ͨ���ţ�����
			  Stream��������ʽ��0-�������� 1-������, 16-ֻ��֡ͷ�� 17-�ָ�
 *	�������: ��
 *	��������: TRUE���ɹ�  FALSE��ʧ��
 *	˵��:�ù���ֻ������400D����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_SetChannelStream_Ex(LONG lRealHandle, LONG lChannel, DWORD Stream );

/* 	����˵��: ��ȡDM60���͵�����ϵͳ������2010-03-19 add
 *	�������: lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			  dwCommand������ֵ
			   dwCommand������ֵ
				#define NET_DLDVR_GET_ALLCFG				0	//������в���
			 lpOutBuffer���������ݵĻ���ָ�� 
			 dwOutBufferSize���������ݵĻ��峤��(���ֽ�Ϊ��λ) 
 *	�������: lpBytesReturned��ʵ�ʽ��յ������ݳ���
 *	��������: TRUE���ɹ�  FALSE��ʧ��
 *	˵��:�ýӿ�ֻ������DM60����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_GetDVRConfig_DM60(LONG lUserID, DWORD dwCommand,
									 LPVOID lpOutBuffer,DWORD dwOutBufferSize,LPDWORD lpBytesReturned);

/* 	����˵��:��ȡDM60�豸��ϵͳ��������
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 dwCommand������ֵ
				#define NET_DLDVR_SET_ALLCFG				0	//������в��� 
			 lpInBuffer���������ݵĻ���ָ�� 
			 dwInBufferSize�� �������ݵĻ��峤��(���ֽ�Ϊ��λ) 
 *	�������:��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_SetDVRConfig_DM60(LONG lUserID, DWORD dwCommand,
									 LPVOID lpInBuffer,DWORD dwInBufferSize);

/* 	����˵��:ִ��DM60�豸������
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 dwCommand������ֵ
				#define NET_DLDVR_CLEARALLPOINT		1	//������е�
				#define NET_DLDVR_CLEARALLLINE		2	//���������
				#define NET_DLDVR_CLEARALLAREA		3	//�����������
				#define NET_DLDVR_ZEROADJUST		4	//�������
				#define NET_DLDVR_KEYBOARD			5	//�������Value1�д�ż�����
				#define NET_DLDVR_SETFOCUSPOS		6	//���ý���Ԥ��λ
				#define NET_DLDVR_CALLFOCUSPOS		7	//���ý���Ԥ��λ
				#define NET_DLDVR_FOCUSSTOP			8	//�۽�ֹͣ
				#define NET_DLDVR_FOCUSSTEPNEAR		9	//��ǰ�����۽�
				#define NET_DLDVR_FOCUSSTEPFAR		10	//��󵥲��۽�
				#define NET_DLDVR_FOCUSAUTO			11	//�Զ��۽�
				#define NET_DLDVR_FOCUSSTEPS		12	//���������۽���������ǰ���������
				#define NET_DLDVR_FOCUSSTEPSNEAR	13	//��ǰ���������۽���ֱ��FocusStop
				#define NET_DLDVR_FOCUSSTEPSFAR		14	//������������۽���ֱ��FocusStop
				#define NET_DLDVR_VOLTAGELEVEL		15	//���õ�ƽ��Value1������+1, ��ʾ����1�� -1, ��ʾ��С1
				#define NET_DLDVR_UPCOLORTEMP		16	//����ɫ���¶����ޣ�Value1ͬVoltageLevel
				#define NET_DLDVR_DOWNCOLORTEMP		17	//����ɫ���¶����ޣ�Value1ͬVoltageLevel
				#define NET_DLDVR_IMAGEMODE			18	//����ͼ��ģʽValue1=Manul/Auto
			 dwValue,Ҫ���õĲ���ֵ������Ҫ��ʱ����0 
 *	�������:��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_SetDMCommand_DM60(LONG lUserID, DWORD dwCommand, INT dwValue);

/* 	����˵��:��ȡ��ǰ����ʹ�õ�ɫ���ɫ���
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *	�������:��
 *	��������: �����ɹ�����ʾɫ��ţ�������ʾʧ��
 *	˵��: �ýӿ�ֻ������DM60����
 */
NET_DLDVR_API INT STDCALL NET_DLDVR_GetDMColor_DM60(LONG lUserID);

/* 	����˵��:���õ�ǰʹ�õ�ɫ�꼰״̬
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 RuleId��ɫ��ţ�0-8
			 Status����ɫ���״̬��1-���ã�0-δ����
 *	�������:��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_SetDMColor_DM60(LONG lUserID, DWORD RuleId, DWORD Status);

/* 	����˵��:��ȡָ������Ŀ��Ĳ���
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *			 dwCommand������ֵ
 *				 #define NET_DVR_GET_DMMEASURE_POINT	1
 *				 #define NET_DVR_GET_DMMEASURE_LINE		2
 *				 #define NET_DVR_GET_DMMEASURE_AREA		3
 *			 Index�����µ����ţ�0-3
 *			 lpOutBuffer���������ݵĻ���ָ�� 
 *			 dwOutBufferSize���������ݵĻ��峤��(���ֽ�Ϊ��λ) 
 *	�������:lpBytesReturned��ʵ���յ������ݳ��� 		
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_GetDMMeasureCfg_DM60(LONG lUserID, DWORD dwCommand, INT Index, LPVOID lpOutBuffer,DWORD dwOutBufferSize, LPDWORD lpBytesReturned);

/* 	����˵��:����ָ�����µ�Ĳ���
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *			 dwCommand������ֵ
 *				#define NET_DVR_SET_DMMEASURE_POINT	1
 *				#define NET_DVR_SET_DMMEASURE_LINE	2
 *				#define NET_DVR_SET_DMMEASURE_AREA	3
 *			 Index�����µ����ţ�0-3
 *			 lpInBuffer���������ݵĻ���ָ�� 
 *			 dwInBufferSize�� �������ݵĻ��峤��(���ֽ�Ϊ��λ) 
 *	�������:��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_SetDMMeasureCfg_DM60(LONG lUserID, DWORD dwCommand, INT Index,LPVOID lpInBuffer,DWORD dwInBufferSize);

/* 	����˵��:���ַ����ķ�ʽ��ȡDM60��������������
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *	�������:cfgBuf,�������������
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_GetConfigString_DM60(LONG lUserID, char *cfgBuf);

/* 	����˵��:���ַ����ķ�ʽ����DM60��������������
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 cfgBuf,�������������
 *	�������:��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_SetConfigString_DM60(LONG lUserID, char *cfgBuf);

/* 	����˵��:���ַ����ķ�ʽ����DM60�����Ĳ���Ŀ��
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 index,���
			 type������Ŀ�����ͣ�����ֵ����
					#define NET_DVR_SET_DMMEASURE_POINT	1
					#define NET_DVR_SET_DMMEASURE_LINE	2
					#define NET_DVR_SET_DMMEASURE_AREA	3
			 DMMeasureBuf,����Ŀ�����
 *	�������:��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_SetDMMeasureString_DM60(LONG lUserID, int index, int type, char *DMMeasureBuf);

/* 	����˵��:���ַ����ķ�ʽ����DM60��������������
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
				type������Ŀ�����ͣ�����ֵ����
					#define NET_DVR_GET_DMMEASURE_POINT	1
					#define NET_DVR_GET_DMMEASURE_LINE	2
					#define NET_DVR_GET_DMMEASURE_AREA	3
				index,���
 *	�������:DMMeasureBuf,����Ŀ�����
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_GetDMMeasureString_DM60(LONG lUserID, int type, int index, char* DMMeasureBuf);

/* 	����˵��:��DM60�����������������ַ�����ʽ��Ӧ�������ṹ��
 *	�������:buf�����������յ������������ַ�����ͨ��NET_DLDVR_GetConfigString_DM60()�������
		     
 *	�������:pSyscfg,��������
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_DM60Config_StringToStruct(char *buf, LPSYSTEMCFG_DM60 pSyscfg);

/* 	����˵��:��DM60���������������������ṹ��ʽ��Ӧ���ַ�����ʽ
 *	�������:pSyscfg,��Ҫ����ת������������	 
 *	�������:buf, ���������ַ���������NET_DLDVR_SetConfigString_DM60()�������������
 *	��������: ��
 *	˵��: �ýӿ�ֻ������DM60����
 */
NET_DLDVR_API VOID STDCALL NET_DLDVR_DM60Config_StructToString( LPSYSTEMCFG_DM60 pSyscfg, char *buf);


/* 	����˵��:��indexָ���Ĳ���Ŀ��(�㡢�ߡ�������Ϊ������״̬
 *	�������:lUserID,�û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 dwCommand������ֵ
				#define NET_DVR_CLEAR_DMMEASURE_POINT	1
				#define NET_DVR_CLEAR_DMMEASURE_LINE	2
				#define NET_DVR_CLEAR_DMMEASURE_AREA	3
			 index������Ŀ���ţ�֧��4�����µ㣨0 - 3����1�������ߣ�0����3����������0-2��
 *	�������:��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_ClearMeasureType_DM60( LONG lUserID, DWORD dwCommand, INT index );

/* 	����˵��:����������IP��ַ
 *	�������:lUserID,�û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *			 IP, IP��ַ
 *	�������:��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60���ͺ�IPCamera����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_SetIPAddr_DM60( LONG lUserID, char* IP, char *SubMask, char *GateWay );

/* 	����˵��:����������MAC��ַ
 *	�������:lUserID,�û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *			 MAC, MAC��ַ
 *	�������:��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60���ͺ�IPCamera����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_SetMACAddr_DM60( LONG lUserID, char* MAC  );

/* 	����˵��:��������ʱ��
 *	�������:lUserID,�û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *			 year			��
 *	   		 month		��
 *			 day			��
 *			 hour		ʱ
 *			 min			��
 *			 sec			��
 *	�������:��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60���ͺ�IPCamera����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_SetDateTime_DM60( LONG lUserID, int year,int month,int day,int hour,int min,int sec  );

/* 	����˵��:��ȡ�����ĵ�ǰʱ��
 *	�������:lUserID,�û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *	�������:DataTime,�ַ�������ʽ��ʽyyyy-mm-dd hh:mm:ss
 *				yyyy	��
 *	   			mm		��
 *				dd		��
 *				hh		ʱ
 *				mm		��
 *				ss		��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60���ͺ�IPCamera����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_GetDateTime_DM60( LONG lUserID, char *DataTime );

/* 	����˵��:�ָ���������
 *	�������:lUserID,�û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *	�������:��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60���ͺ�IPCamera����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_LoadDefault_DM60( LONG lUserID );

/* 	����˵��:��ȡ������ϵͳ��Ϣ
 *	�������:lUserID,�û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *	�������:SysInfo,ϵͳ��Ϣ
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60���ͺ�IPCamera����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_GetSystemInfo_DM60( LONG lUserID, char *SysInfo  );

/* 	����˵��:��ȡ�����и�����Ŀ���ʵʱ�¶�
 *	�������:lUserID,�û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *			 Type, �������ͣ�0-��ȡ���в���Ŀ���ʵʱ�¶� 1-���µ㣻2-�����ߣ�3-��������
 *					//DM60����Ŀ�궨��
 *							#define NET_DVR_GET_DMMEASURE_ALL	0
 *							#define NET_DVR_GET_DMMEASURE_POINT	1
 *							#define NET_DVR_GET_DMMEASURE_LINE	2
 *							#define NET_DVR_GET_DMMEASURE_AREA	3
 *			 index�����(0--3)
 *			 Mode,0������һ���¶�;  1�����������¶ȣ����ʱ���������Զ����ڡ�
 *	�������:��
 *	��������: ���ڵ���0���ɹ���������ʧ��
 *	˵��: �ýӿ�ֻ������DM60���ͣ�ʵʱ�¶�ͨ���ص���������
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_GetDMTEMP_Start(LONG lUserID, int Type, int index,  int Mode);

/* 	����˵��:ֹͣ��ȡ������ʵʱ�¶�
 *	�������:lUserID,�û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *	�������:��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_GetDMTEMP_Stop(LONG lUserID);

/* 	����˵��:����͸��ͨ�����д��ڿ���
 *	�������:lUserID,�û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *			 SerialPort�����ں�, 0-����1�� 1-����2
 *	�������:��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿڲ�������DM60���ͺ�IPCamera����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_TransSerial_Start(LONG lUserID,LONG SerialPort);

/* 	����˵��:ͨ��͸��ͨ�������ڷ�������
 *	�������:lUserID,�û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *			 SerialPort�����ںţ� 0-����1�� 1-����2
 *			 pCmdBuf�������ַ���
 *			 dwCmdBufSize�������С
 *	�������:pOutBuf���Ӵ����յ��Ļ�Ӧ
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿڲ�������DM60���ͺ�IPCamera����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_TransSerial_Ctrl(LONG lUserID,LONG SerialPort,CHAR *pCmdBuf,DWORD dwCmdBufSize, CHAR *pOutBuf);

/* 	����˵��:�ر�͸��ͨ��
 *	�������:lUserID,�û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *			 SerialPort�����ںţ�  0-����1�� 1-����2
 *	�������:��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿڲ�������DM60���ͺ�IPCamera����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_TransSerial_Stop(LONG lUserID,LONG SerialPort);

/* 	����˵��:��¼������Ի���
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 ParentWnd�������ھ��
 *	�������: ��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������400D����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_OpenDvrRecCfgDialog(LONG lUserID, HWND ParentWnd);

/* 	����˵��:ע��ص������������豸��Ϣ�ȣ�ͬʱ�ص����豸IP���������ֲ�ͬ�豸��
 *	�������: cbMessCallBack���ص�����
				BOOL(CALLBACK *fMessageCallBack)(LONG lCommand, char *sDVRIP, char *pBuf, DWORD dwBufLen);
					lCommandֵ��#define COMM_ALARM 0x1100 //������Ϣ ��Ӧ�ṹ NET_DLDVR_ALARMINFO 
								#define COMM_ALARM_EX	 0x1101	//600���͵ı�����Ϣ ��Ӧ�ṹ NET_DLDVR_ALARMINFO_600
								#define COMM_TRADEINFO   0x1500 //ATMDVR�����ϴ�������Ϣ 
								#define SERIAL_NUMBER	 0x1600 //DVR�ϱ������к�
								#define DISKCHANNEL_STATE 0x1700 //������ʱ�ϴ�Ӳ��״̬��ͨ��¼��״̬��Ϣ 
								#define RVS_INFO		 0x1800 //IPCamera�ϴ���RVS��Ϣ
								#define EXCEPTION_NOTIFY 0x1900 //�쳣���ߵ���Ϣ����Ӧ�ṹ NET_DLDVR_EXCEPTION ��Ӧ����֪ͨ��Ϣ 
								#define DM_TEMP			0x2000	//DM60���͵�ʵʱ������Ϣ����Ӧ�ṹNET_DLDVR_DMTEMP
								#define DMTEMP_ALARM	0x2010	//DM60���͵��¶ȸ澯��Ϣ����Ӧ�ṹNET_DLDVR_DMTEMP_ALARM
								#define DM_ANALYS_ALARM		0x2011	//DM60���͵����ܷ����澯��Ϣ����Ӧ�ṹNET_DLDVR_DMANALYS_ALARM
								#define	PLAYBACK_OVER		0x2020	//�طŽ�������Ӧ�ṹNET_DLDVR_EXCEPTION
								#define RESOLUTION_CHANGE	0x2021	//�ֱ��ʸı䣬��Ӧ�ṹNET_DLDVR_EXCEPTION
								#define VIDEOFORMAT_CHANGE				0x2022	//��Ƶ��ʽ�ı䣬��Ӧ�ṹNET_DLDVR_EXCEPTION
					 sDVRIP:�豸IP��ַ 
					pBuf:�ص�������Ϣ
					dwBufLen���ص�������Ϣ����
			  messageType����Ϣ���ͣ�0-��ͨ������Ϣ��1-DM60���͵ģ�ʵʱ������Ϣ���¶ȸ澯��Ϣ��
 *	�������: ��
 *	��������: TRUE:�ɹ� FALSE:ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_SetAllMessCallBack(BOOL (CALLBACK *fMessCallBack)
										   (LONG lCommand,CHAR *sDVRIP,CHAR *pBuf,DWORD dwBufLen), INT messageType =0);

/* 	����˵��:��̨��ʼ������
 *	�������:lUserID,�û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *			 Protocol, ��̨����Э��
 *			 nAddrID, ��̨��ַ
 *	�������:��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_PTZSettings_DM60( LONG lUserID, int Protocol, int nAddrID );

/* 	����˵��:��ȡDVR��Ӳ��״̬��ֻ������600ϵ�л��ͣ�
 *	�������:lUserID,�û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *			 lpDiskState��Ӳ��״̬
 *	�������:��
 *	��������: TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������600ϵ�л���
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_GetDVRDiskState(LONG lUserID, LPNET_DLDVR_DVRDISKSTATE lpDiskState);

/* 	����˵��:���ڻ�ȡ����ӳ��������ͺźͰ汾��Ϣ��ֻ��600������Ҫ���м�⣩
 *	�������:lUserID,�û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *			 sFileName��Ҫ������ӳ���ļ�����
 *	�������:dvrType�������ͺ�
 *			 Version���汾��Ϣ
 *	��������:0���ɹ���-1��ʧ�ܣ�ʧ��ʱ�ɵ���NET_DLDVR_GetLastError()���ʧ��ԭ��
 *	˵��: �ýӿ�ֻ������600ϵ�л��ͣ��������Ͳ����м��ֱ�ӷ���0
 */
NET_DLDVR_API INT STDCALL NET_DLDVR_GetImagefileInfo(LONG lUserID,CHAR *sFileName, char *dvrType, char *Version);

/* 	����˵��:��ȡ��ɫ���������״̬�����ַ�����ʽ����
 *	�������:lUserID,�û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *	�������:buf��ɫ���������״̬
 *	��������:0���ɹ���-1��ʧ�ܣ�ʧ��ʱ�ɵ���NET_DLDVR_GetLastError()���ʧ��ԭ��
 *	˵��: �ýӿ�ֻ������DM60ϵ�л���
 */
NET_DLDVR_API INT STDCALL NET_DLDVR_GetDMColorRuleString_DM60(LONG lUserID, char *buf);

/* 	����˵��:���ַ�����ʽ���ø�ɫ���������״̬
 *	�������:lUserID,�û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *			 buf��Ҫ�������õ�ɫ��״̬
 *	�������:��
 *	��������:TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60ϵ�л���
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_SetDMColorRuleString_DM60(LONG lUserID, char *buf);

/* 	����˵��:��ʼԭʼ���ݲɼ�
 *	�������:lUserID,�û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *			 sFileName,�����ļ����ļ������ļ�����׺Ϊ.dlv)
 *			 Frame����Ҫ�ɼ���ԭʼ����֡����<0ʱһֱ�ɼ�ֱ������NET_DLDVR_StopCaptureInfraredFrame
 * 			 Time��֡��֮֡��ļ��ʱ��(ms) >= 20ms���ұ�����20�ı�����ע�⣺Frame * Time <= 8�롣��Ԥ��������Ŀǰ��Ч��
 *			 streamType��֡���ͣ�2-RAW  3-YUV
 *	�������:��
 *	��������:TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60ϵ�л���
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_CaptureInfraredFrame(LONG lUserID, const char *sFileName, int Frame,int Time, int streamType);

/* 	����˵��:ֹͣԭʼ���ݲɼ�
 *	�������:lRealHandle,�ɼ��������NET_DLDVR_CaptureInfraredFrame()�����ķ���ֵ
 *	�������:��
 *	��������:TRUE���ɹ���FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60ϵ�л���
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_StopCaptureInfraredFrame(LONG lRealHandle);

/* 	����˵��:��̨Ԥ��λ���ƣ���Ҫ�ȴ򿪼���(������600����)
 *	�������:lRealHandle�����Ӿ������NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�����ķ���ֵ
			 dwPTZPresetCmd����̨Ԥ�õ�����
					#define SET_PRESET		1	// ����Ԥ�õ� 
					#define CLE_PRESET		2	// ���Ԥ�õ� 
					#define GOTO_PRESET		3	// ת��Ԥ�õ�
			 dwPresetIndex��Ԥ�õ����ţ����֧��128��Ԥ�õ�
			 sPresetName,Ԥ�õ�����
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������600���ͺ�NVR����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_PTZPreset_600(LONG lRealHandle,DWORD dwPTZPresetCmd,DWORD dwPresetIndex, const char *sPresetName);

/* 	����˵��:��ʼʵʱ����
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 lpClientInfo��Ԥ������ 
 *	�������:info,�򿪼���ʱDVR���ص�һЩ��Ϣ����֡�ʡ��ֱ��ʵ�
 *	��������:���Ӿ����������ʾʧ��
 *	˵��: 
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_RealPlay_EX(LONG lUserID,LPNET_DLDVR_CLIENTINFO lpClientInfo, MONITOR_INFO *info);

/* 	����˵��:��̨����
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 dwPTZCommand����̨������� 0-��̨ 1-��ͷ 2-��Ȧ
			 Movement����̨������
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60���ͺ�IPCamera����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_PTZControl_DM60(LONG lUserID,DWORD dwPTZCommand,DWORD Movement);

/* 	����˵��:��̨Ԥ��λ����
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			 dwPTZCommand����̨Ԥ��λ��������
			 dwPresetIndex����̨Ԥ��λ
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿ�ֻ������DM60���ͺ�IPCamera����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_PTZPreset_DM60(LONG lUserID,DWORD dwPTZPresetCmd, DWORD dwPresetIndex);

/* 	����˵��:��ȡDM60��״̬
 *	�������:lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
 *	�������:��
 *	��������:DM60�ĵ�ǰ״̬
 *	˵��: �ýӿ�ֻ������DM60���ͺ�IPCamera����
 */
NET_DLDVR_API INT STDCALL NET_DLDVR_GetDM60Status(LONG lUserID);

/* 	����˵��:��ȡDM60ԭʼ���ݲɼ���״̬
 *	�������:lRealHandle���ɼ��������NET_DLDVR_CaptureInfraredFrame()�����ķ���ֵ
 *	�������:��
 *	��������:ԭʼ���ݲɼ��ĵ�ǰ״̬
				#define DM60_CAPTUREINFRARED_ING		1	// ���ڲɼ�
				#define DM60_CAPTUREINFRARED_OVER		2	// �ɼ����
				#define DM60_CAPTUREINFRARED_ERROR		3	// �ɼ�����
 *	˵��: �ýӿ�ֻ������DM60����
 */
NET_DLDVR_API INT STDCALL NET_DLDVR_GetCaptureInfraredStatus_DM60(LONG lRealHandle);

/* 	����˵��:��ȡ���ݽ��ջ���Ĵ�С
 *	�������:lRealHandle�����Ӿ����Զ�̻طž��
 *	�������:��
 *	��������:�����С
 *	˵��: 
 */
NET_DLDVR_API INT STDCALL NET_DLDVR_GetRecvCacheSize(LONG lRealHandle);

//600�����ļ��������ļ�����
#define ALARMIN_RINGTONE		0	//�ⲿ�澯�ĸ澯��
#define MOTIONALARM_RINGTONE	1	//�ƶ����澯�ĸ澯��
#define SHELTERALARM_RINGTONE	2	//��Ƶ�ڵ��澯�ĸ澯��
#define VIDEOLOST_RINGTONE		3	//��Ƶ��ʧ�澯�ĸ澯��
#define EXCEPTIONAL_RINGTONE	4	//�쳣�澯�ĸ澯��

/* 	����˵��:Զ�̸��������ļ���600���ͣ�
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
			 sFileName��Ҫ���µ�ӳ������
			 fileType���ļ�����
				0 �ⲿ�澯alarmin
				1 �ƶ����澯
				2 ��Ƶ�ڵ��澯
				3 ��Ƶ��ʧ�澯
				4 �쳣�澯			 
 *	�������:��
 *	��������:����ID����ΪNET_DLDVR_GetUpgradeFileState_EX()������������������ظ�����ʾʧ��
 *	˵��:�ýӿ�ֻ������600����
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_FILE_UPDATE_EX( LONG lUserID, CHAR *sFileName, int fileType );

/* 	����˵��:��ȡ�ļ�Զ�̸��µ�״̬
 *	�������:lUpgradeHandle������ID����NET_DLDVR_FILE_UPDATE_EX()�����ķ���ֵ
 *	�������:��
 *	��������:״ֵ̬
				#define NET_DLDVR_SETFILE_SUCCESS	1051	//�����ɹ�
				#define NET_DLDVR_SETFILE			1050	//��������
				#define NET_DLDVR_SETFILE_NETERROR	-8097	//����Ͽ���״̬δ֪
				#define NET_DLDVR_SETFILE_FAIL		-8098	//�����ļ�ʧ��

 *	˵��: �ýӿ�ֻ������600����
 */
NET_DLDVR_API INT STDCALL NET_DLDVR_GetUpgradeFileState_EX(LONG lUpgradeHandle);

/* 	����˵��:���û�ȡʵʱ�ط���Ƶ���ݵĻص�����
 *	�������:fRealDataCallBack_EX����Ƶ���ݻص�����
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL	STDCALL NET_DLDVR_SetRealDataCallBack_EX(LONG lRealHandle, fRealDataCallBack_EX realDataCallBack, DWORD dwUser);

/* 	
	����˵��:��long���͵�ʱ��ת����NET_DLDVR_TIME�ṹ�ĸ�ʽ
 *	�������:dat��long���͵�ʱ��ֵ ���2000��0ʱ0��0��
 *	�������:time��ת����NET_DLDVR_TIME�ṹ��ʽ��ʱ��
 *	��������:��
 *	˵��: 
 */
NET_DLDVR_API VOID	STDCALL NET_DLDVR_LongToTime( DWORD dat , NET_DLDVR_TIME* time );

/* 	
	����˵��:��NET_DLDVR_TIME��ʽ��ʱ��ת����long���͵�ֵ
 *	�������:time��NET_DLDVR_TIME��ʽ��ʱ��ֵ
 *	�������:��
 *	��������:ת�����ʱ��ֵ ���2000��0ʱ0��0��
 *	˵��: 
 */
NET_DLDVR_API DWORD STDCALL NET_DLDVR_TimeToLong(  NET_DLDVR_TIME* time );


/* 	����˵��:����DM60ָ�����͵��ļ�
 *	�������:lUserID����½���
 *			 sFileName��Ҫ���и��µ��ļ���
 *			 Type���ļ�����
 *				#define UPDATEFILE_TYPE_DM60_MID		0
 *				#define UPDATEFILE_TYPE_DM60_FIREWARE	1
 *				#define UPDATEFILE_TYPE_DM60_DATA		2
 *	�������:��
 *	��������:���ظ�����ʾʧ��
 *	˵��: 
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_UpdateFile_DM60(LONG lUserID,CHAR *sFileName, int Type);

/* 	����˵��:��ȡDM60ָ�������ļ��ĸ��½���
 *	�������:lUpdateHandle�����¾������NET_DLDVR_UpdateFile_DM60���������ķ���ֵ
 *	�������:��
 *	��������:����ֵ��0-100���� ���ظ�����ʾʧ��
 *	˵��: 
 */
NET_DLDVR_API INT STDCALL NET_DLDVR_GetUpdateFilePos_DM60( LONG lUpdateHandle );


/* 	����˵��:��ȡMAC��ַ
 *	�������:lUserID����½���
 *	�������:lpOutBuffer�� MAC��ַ
 *	��������:���ظ�����ʾʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_GetMacAddress_DM60(LONG lUserID, LPVOID lpOutBuffer);


/* 	����˵��:��/�ر�����ǰ��
 *	�������:lUserID����½���
 *			 cmd������ֵ
 *				#define  NET_DVR_SENSORPOWER_ON		0 
 *				#define  NET_DVR_SENSORPOWER_OFF	1	
 *				#define  NET_DVR_SENSORPOWER_CHG	2 
 *	�������:��
 *	��������:���ظ�����ʾʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_SensorPower_DM60( LONG lUserID, int cmd  );

/* 	����˵��:���ػط�ʱ��ת��ָ��ʱ�����в���
 *	�������:lPlayHandle���طž��
 *			 Time��ϣ����ת����ʱ��ֵ
 *	�������:��
 *	��������:���ظ�����ʾʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_PLAYFILE_GotoTime( LONG lPlayHandle, LPNET_DLDVR_TIME Time );


/* 	����˵��:��ʼ���ҵ���ͨ����¼���ļ�
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
			 lChannel��ͨ����,��0��ʼ
			 dwFileType���ļ�����
					0xff-ȫ����0-��ʱ¼��1-�ƶ���⣻2-��������(��ʱ��ѯ����¼��������ͨ����¼������ܷ�������¼��)��3-�������4-�ֶ�¼��
			 lpStartTime����ʼʱ��
			 lpStopTime������ʱ��
 *	�������:��
 *	��������:���Ҿ������ΪNET_DVR_FindClose()�Ⱥ����Ĳ��������ظ�����ʾʧ��
 *	˵��: ��������IPCamera����
 */
NET_DLDVR_API LONG			STDCALL NET_DLDVR_FindFile_OneChanel(LONG lUserID,LONG lChannel,DWORD dwFileType, LPNET_DLDVR_TIME lpStartTime, LPNET_DLDVR_TIME lpStopTime);

/* 	����˵��:������������MTC�ļ�
 *	�������:lUserID���û�ID��NET_DLDVR_Login()�����ķ���ֵ
 *			 path���ļ���Ҫ������·��
 *	�������:��
 *	��������:���Ҿ������ΪNET_DVR_FindClose()�Ⱥ����Ĳ��������ظ�����ʾʧ��
 *	˵��: �ýӿ�ֻ������DM60����
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_DownloadMTC_DM60(LONG lUserID, LPCTSTR path);

/* 	����˵��:�����������͵ķ�ʽ��ʼ����¼���ļ����ɲ�ѯԤ��ͨ����·��
 *	�������: lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			  previewCh,�Ƿ��ѯԤ��ͨ��¼��1-�� 0-��
			  lChannel��ͨ���ţ���λ��ʾ
			  dwFileType��¼���ļ������� 0-��ʱ¼�� 1-�ƶ����	2-��������  3-�����   4-�ֶ�¼�� 
			  dwAlarmType���澯���ͣ�����dwFileTypeΪ2��������¼��ʱ��Ч��
					0x90- ����
					0x91- ����
					0x92- ����
					0x93- �ۼ�
					0x94- ����
			  start_time����ʼʱ��
			  end_time������ʱ��
 *	�������: ��
 *	��������: TRUE���ɹ�  FALSE��ʧ��
 *	˵��:�ýӿ�ֻ������400���ͼ�600����
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_FindFile_WithPreview(LONG lUserID, int previewCh, LONG lChannel,DWORD dwFileType, DWORD dwAlarmType, 
											LPNET_DLDVR_TIME lpStartTime, LPNET_DLDVR_TIME lpStopTime);


/* 	����˵��:������¼���ļ��������ص��ļ�������ʱ���ڵ�ͬ����¼��Ϊ�ֶη�ʽ
 *	�������: lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			  previewCh,�Ƿ��ѯԤ��ͨ��¼��1-�� 0-��
			  lChannel��ͨ���ţ���λ��ʾ
			  start_time����ʼʱ��
			  end_time������ʱ��
			  MaxCount�����ص�����ļ�����
			  buf���ļ������ַ�������СΪMaxCount���ļ��ṹΪNET_DLDVR_FILE_DATA
 *	�������: ��
 *	��������: TRUE���ɹ�  FALSE��ʧ��
 *	˵��:�ýӿ�ֻ������400���ͼ�600����
 */
LONG STDCALL NET_DLDVR_FindFileBYTIME(LONG lUserID,LONG lChannel, LPNET_DLDVR_TIME lpStartTime, LPNET_DLDVR_TIME lpStopTime, 
									  WORD MaxCount, char *buf);

/* 	����˵��:������¼��/JPEG�ļ�
 *	�������: lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			  lChannel��ͨ���ţ���λ��ʾ
			  fileType���ļ�����.0-¼���ļ���1-JPEG�ļ�
			  videoType,¼������.0xff ȫ��	0 �� ��ʱ¼��	1 - �ƶ����	2 �� ��������	3 �������	4 �� �ֶ�¼��  
			  start_time����ʼʱ��
			  end_time������ʱ��
			  MaxCount�����ص�����ļ�����
			  buf���ļ������ַ�������СΪMaxCount���ļ��ṹΪNET_DLDVR_FIND_DATA
 *	�������: ��
 *	��������: TRUE���ɹ�  FALSE��ʧ��
 *	˵��:�ýӿ�ֻ������400���ͼ�600����
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_FindFileOnce(LONG lUserID,LONG lChannel, DWORD fileType, DWORD videoType, LPNET_DLDVR_TIME lpStartTime, LPNET_DLDVR_TIME lpStopTime, 
									WORD MaxCount, char *buf);

/* 	����˵��:��������־�ļ�
 *	�������: lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			  lSelectMode����ѯ��ʽ��ʵ�ʲ���ʹ��
			  dwMajorType,������ 
			  dwMinorType��������
			  start_time����ʼʱ��
			  end_time������ʱ��
			  MaxCount�����ص�����ļ�����
			  buf���ļ������ַ�������СΪMaxCount���ļ��ṹΪNET_DLDVR_LOG
 *	�������: ��
 *	��������: TRUE���ɹ�  FALSE��ʧ��
 *	˵��:�ýӿ�ֻ������400���ͼ�600����
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_FindLogOnce(LONG lUserID,LONG lSelectMode, DWORD dwMajorType,DWORD dwMinorType, 
								   LPNET_DLDVR_TIME lpStartTime, LPNET_DLDVR_TIME lpStopTime, WORD MaxCount, char *buf);


/* 	����˵��:��ΪDM60�������û������ͺͿ��ƶ˿ڣ���ΪDM60����ԭ5000�˿��ϵĵ�½�ӿڽ�ȡ����
 *	�������: sDVRIP������IP
 *     		  wDVRHttpPort�����ƶ˿�
			  sUserName, �û���
			  sPassword������
 *	�������: ��
 *	��������: �û�ID����ֵ����Ψһ�ԣ��������豸�Ĳ�������Ҫͨ����IDʵ�֡����ظ�����ʾʧ��
 *	˵��:�ýӿ�ֻ������DM60����
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_SetDvrType_DM60(CHAR *sDVRIP, WORD wDVRHttpPort, CHAR *sUserName, CHAR *sPassword);


/* 	����˵��:��ΪDM60����������Ƶ�˿�
 *	�������: sDVRIP������IP
			  wDVRPort����Ƶ�˿�
 *	�������: ��
 *	��������: ����0�ɹ������ظ�����ʾʧ��
 *	˵��:�ýӿ�ֻ������DM60����
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_SetVideoPort_DM60(CHAR *sDVRIP, WORD wDVRPort);

/* 	����˵��:�����������ͻָ��������ĳ�������
 *	�������: lUserID���û�ID����NET_DLDVR_Login()�����ķ���ֵ
			  ConfigType���������Ͳ�������
					#define NET_DLDVR_RESTORE_SYSTEM 		1	//�������� 
					#define NET_DLDVR_RESTORE_DISPLAY		2	//��ʾ����
					#define NET_DLDVR_RESTORE_RECORD		3  //¼�����
					#define NET_DLDVR_RESTORE_USER			4  //�û�����
					#define NET_DLDVR_RESTORE_NETWORK		5 //�������
					#define NET_DLDVR_RESTORE_PTZ			6  //��̨����
					#define NET_DLDVR_RESTORE_ALLCFG		7  //ȫ������
 *	�������: ��
 *	��������: TRUE���ɹ�  FALSE��ʧ��
 *	˵��:�ýӿ�ֻ������600��700����
 */
NET_DLDVR_API BOOL STDCALL NET_DLDVR_RestoreConfigByType(LONG lUserID, int ConfigType);


/* 	����˵��:ע��ص������������豸������Ϣ�ȣ�ͬʱ�ص����豸IP���������ֲ�ͬ�豸��
 *	�������: index�����
			  cbMessCallBack���ص�����
				BOOL(CALLBACK *fMessageCallBack)(LONG lCommand, char *sDVRIP, char *pBuf, DWORD dwBufLen);
				lCommandֵ��
					#define COMM_ALARM 0x1100 //������Ϣ ��Ӧ�ṹ NET_DLDVR_ALARMINFO 
					#define COMM_ALARM_EX	 0x1101	//600���͵ı�����Ϣ ��Ӧ�ṹ NET_DLDVR_ALARMINFO_600
					#define COMM_TRADEINFO   0x1500 //ATMDVR�����ϴ�������Ϣ 
					#define SERIAL_NUMBER	 0x1600 //DVR�ϱ������к�
					#define DISKCHANNEL_STATE 0x1700 //������ʱ�ϴ�Ӳ��״̬��ͨ��¼��״̬��Ϣ 
					#define RVS_INFO		 0x1800 //IPCamera�ϴ���RVS��Ϣ
					#define EXCEPTION_NOTIFY 0x1900 //�쳣���ߵ���Ϣ����Ӧ�ṹ NET_DLDVR_EXCEPTION ��Ӧ����֪ͨ��Ϣ 
					#define DM_TEMP			0x2000	//DM60���͵�ʵʱ������Ϣ����Ӧ�ṹNET_DLDVR_DMTEMP
					#define DMTEMP_ALARM	0x2010	//DM60���͵��¶ȸ澯��Ϣ����Ӧ�ṹNET_DLDVR_DMTEMP_ALARM
					#define DM_ANALYS_ALARM		0x2011	//DM60���͵����ܷ����澯��Ϣ����Ӧ�ṹNET_DLDVR_DMANALYS_ALARM
					#define	PLAYBACK_OVER		0x2020	//�طŽ�������Ӧ�ṹNET_DLDVR_EXCEPTION
					#define RESOLUTION_CHANGE	0x2021	//�ֱ��ʸı䣬��Ӧ�ṹNET_DLDVR_EXCEPTION
					#define VIDEOFORMAT_CHANGE				0x2022	//��Ƶ��ʽ�ı䣬��Ӧ�ṹNET_DLDVR_EXCEPTION
				sDVRIP:�豸IP��ַ 
				pBuf:�ص�������Ϣ
				dwBufLen���ص�������Ϣ����
 *	�������: ��
 *	��������: TRUE:�ɹ� FALSE:ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL	STDCALL NET_DLDVR_SetDVRMessCallBack_WithIndex(int index, BOOL (CALLBACK *fMessCallBack)(LONG lCommand,CHAR *sDVRIP,CHAR *pBuf,DWORD dwBufLen));

/* 	����˵��:ע��ص������������豸������Ϣ�ȣ�ͬʱ�ص����û�ID���������ֲ�ͬ�û���
 *	�������: index,���
			  cbMessCallBack���ص�����
				BOOL(CALLBACK *fMessageCallBack)(LONG lCommand, char *sDVRIP, char *pBuf, DWORD dwBufLen);
					lCommandֵ��
						#define COMM_ALARM 0x1100 //������Ϣ ��Ӧ�ṹ NET_DLDVR_ALARMINFO 
						#define COMM_ALARM_EX	 0x1101	//600���͵ı�����Ϣ ��Ӧ�ṹ NET_DLDVR_ALARMINFO_600
						#define COMM_TRADEINFO   0x1500 //ATMDVR�����ϴ�������Ϣ 
						#define SERIAL_NUMBER	 0x1600 //DVR�ϱ������к�
						#define DISKCHANNEL_STATE 0x1700 //������ʱ�ϴ�Ӳ��״̬��ͨ��¼��״̬��Ϣ 
						#define RVS_INFO		 0x1800 //IPCamera�ϴ���RVS��Ϣ
						#define EXCEPTION_NOTIFY 0x1900 //�쳣���ߵ���Ϣ����Ӧ�ṹ NET_DLDVR_EXCEPTION ��Ӧ����֪ͨ��Ϣ 
						#define DM_TEMP			0x2000	//DM60���͵�ʵʱ������Ϣ����Ӧ�ṹNET_DLDVR_DMTEMP
						#define DMTEMP_ALARM	0x2010	//DM60���͵��¶ȸ澯��Ϣ����Ӧ�ṹNET_DLDVR_DMTEMP_ALARM
						#define DM_ANALYS_ALARM					0x2011	//DM60���͵����ܷ����澯��Ϣ����Ӧ�ṹNET_DLDVR_DMANALYS_ALARM
						#define	PLAYBACK_OVER		0x2020	//�طŽ�������Ӧ�ṹNET_DLDVR_EXCEPTION
						#define RESOLUTION_CHANGE	0x2021	//�ֱ��ʸı䣬��Ӧ�ṹNET_DLDVR_EXCEPTION
						#define VIDEOFORMAT_CHANGE				0x2022	//��Ƶ��ʽ�ı䣬��Ӧ�ṹNET_DLDVR_EXCEPTION
					lUserID���û���¼ID����NET_DLDVR_Login�ķ���ֵ 
					pBuf:�ص�������Ϣ
					dwBufLen���ص�������Ϣ����
 *	�������: ��
 *	��������: TRUE:�ɹ� FALSE:ʧ��
 *	˵��: 
 */
NET_DLDVR_API BOOL			STDCALL NET_DLDVR_SetDVRMessCallBack_EX_WithIndex(int index, BOOL (CALLBACK *fMessCallBack_EX)(LONG lCommand,LONG lUserID,CHAR *pBuf,DWORD dwBufLen));


/* 	����˵��:��������
 *	�������: lRealHandle�����Ӿ��
 *	�������: ��
 *	��������: �ɹ��򷵻�lRealHandle�����ظ�����ʾʧ��
 *	˵��: ���øú���ʱ���뱣֤DVRû�е��ߣ������޷��ɹ�����
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_ReMonitor(LONG lRealHandle);

/* 	����˵��:��ѯ�Ƿ�֧��ĳ�ֽӿ�
 *	�������: lUserID����¼���
			  mainType��0-�ӿ� 1-���� 2-���� (Ŀǰֻ֧��0)
			  subType: ����Ľӿڴ��루���ӿڴ����
 *	�������: ��
 *	��������: �ɹ�ʱ������>=0�����ظ�����ʾʧ��
 *	˵��: ��
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_QueryFunction(LONG lUserID, int mainType, int subType);

/* 	����˵��:��ѯ������֧�����нӿ�
 *	�������: lUserID����¼���
			  funcList��NET_DLFUNC_PROPERTY����ָ�루�ϲ��û����÷����ڴ棩
			  size: ����Ԫ�ظ���
 *	�������: ��
 *	��������: �ɹ�ʱ������>=0�����ظ�����ʾʧ��
 *	˵��: ����Ľӿڴ��루���ӿڴ����
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_QueryFunctionAll(LONG lUserID, LPNET_DLFUNC_PROPERTY &funcList, int &size);

/* 	����˵��: һ�������������ļ����û���״̬
 *	�������: state: NET_DLDVR_STREAMSTATE����
			  size: ����Ԫ�ظ���
 *	�������: ��
 *	��������: �ɹ�ʱ������>=0�����ظ�����ʾʧ��
 *	˵��: NET_DLDVR_STREAMSTATE����Ԫ�ض�����������ͬһ̨DVR�����ļ����û�
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_SetMulChannelStream_EX(LPNET_DVR_STREAMSTATE state, int size);

/* 	����˵��: ����������־
 *	�������: sDVRIP,wDVRPort, sUserName, sPassword����ָ��DVR������Ϣ
			dwMajorType����־������
				#define MAJOR_All		0x00	// ȫ�� 
				#define MAJOR_ALARM		0x1	// ���� 
				#define MAJOR_EXCEPTION 0x2	// �쳣
				#define MAJOR_OPERATION	0x3	// ���� 
				#define MAJOR_NET		0x4   //�������
				#define MAJOR_ACC		0x5 // ������־
			dwMinorType����־������
		  	lpStartTime����ʼʱ��
			lpStopTime������ʱ��
			buf��NET_DLDVR_LOG���飨���û������ڴ棩
			nSize: ����Ԫ�ظ���
			nStartPos: ��ʾ�ӵڼ�����¼��ʼ��ѯ����Ҫ���ڶ�β�ѯ���״β�ѯʱ����ֵ��0.
			dwTotalCount:���������˸�ʱ������ܹ��ж�������¼
 *	�������: ��
 *	��������: �ɹ�ʱ������ʵ�ʼ���������־���������ظ�����ʾʧ��
 *	˵��: ��
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_FindLogs_EX(CHAR *sDVRIP,WORD wDVRPort,CHAR *sUserName,CHAR *sPassword,DWORD dwMajorType,DWORD dwMinorType, LPNET_DLDVR_TIME lpStartTime, 
   											  LPNET_DLDVR_TIME lpStopTime, LPNET_DLDVR_LOG buf, int nSize, int nStartPos, int &dwTotalCount);
/* 	����˵��: ��������¼���ļ�
 *	�������: sDVRIP,wDVRPort, sUserName, sPassword����ָ��DVR������Ϣ
			  lChannel��ͨ����,��λ��ʾ
			  dwFileType���ļ����� 0xff-ȫ����0-��ʱ¼��1-�ƶ���⣻2-��������(��ʱ��ѯ����¼��������ͨ����¼������ܷ�������¼��)��3-�������4-�ֶ�¼��
		  	  lpStartTime����ʼʱ��
			  lpStopTime������ʱ��
			  buf��NET_DLDVR_FIND_DATA_EX���飨���û������ڴ棩
			  nSize: ����Ԫ�ظ���
			  nStartPos: ��ʾ�ӵڼ�����¼��ʼ��ѯ����Ҫ���ڶ�β�ѯ���״β�ѯʱ����ֵ��0.
			  dwTotalCount:���������˸�ʱ������ܹ��ж��ٸ��ļ�
 *	�������: ��
 *	��������: �ɹ�ʱ������ʵ�ʼ�������¼���ļ����������ظ�����ʾʧ��
 *	˵��: ��
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_FindFiles_EX(CHAR *sDVRIP,WORD wDVRPort,CHAR *sUserName,CHAR *sPassword,BOOL privewCh, LONG lChannel,DWORD dwFileType,LPNET_DLDVR_TIME lpStartTime, 
												  LPNET_DLDVR_TIME lpStopTime, LPNET_DLDVR_FIND_DATA_EX buf, int nSize, int nStartPos, int &dwTotalCount);
/* 	����˵��:����¼���ļ������������ļ�
 *	�������:sDVRIP,wDVRPort, sUserName, sPassword����ָ��DVR������Ϣ
			 sDVRFileName��Ҫ���ص�¼���ļ���
			 sSavedFileName��ϣ�����浽������¼���ļ���
 *	�������:��
 *	��������:���ؾ������ΪNET_DLDVR_StopGetFile_EX()��NET_DLDVR_GetDownloadPos_EX()�Ĳ��������ظ�����ʾʧ��
 *	˵��: ��
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_GetFileByName_EX(CHAR *sDVRIP,WORD wDVRPort,CHAR *sUserName,CHAR *sPassword,CHAR *sDVRFileName,CHAR *sSavedFileName);

/* 	����˵��:����¼���ļ���ʱ�������ļ�
 *	�������:sDVRIP,wDVRPort, sUserName, sPassword����ָ��DVR������Ϣ
			 lChannel: ͨ���ţ���0��ʼ
			 sSavedFileName��ϣ�����浽������¼���ļ���
 *	�������:��
 *	��������:���ؾ������ΪNET_DLDVR_StopGetFile_EX()��NET_DLDVR_GetDownloadPos_EX()�Ĳ��������ظ�����ʾʧ��
 *	˵��: ��
 */
NET_DLDVR_API LONG STDCALL NET_DLDVR_GetFileByTime_Ex(CHAR *sDVRIP,WORD wDVRPort,CHAR *sUserName,CHAR *sPassword,LONG lChannel, LPNET_DLDVR_TIME lpStartTime, LPNET_DLDVR_TIME lpStopTime, CHAR *sSavedFileName);

/* 	����˵��:ֹͣ����
 *	�������:lFileHandle�����ؾ������NET_DLDVR_GetFileByName()��NET_DLDVR_GetFileByTime()�����ķ���ֵ		 
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera����
 */
NET_DLDVR_API BOOL	STDCALL NET_DLDVR_StopGetFile_EX(LONG lFileHandle);

/* 	����˵��:��ȡ���ؽ���
 *	�������:lFileHandle�����ؾ������NET_DLDVR_GetFileByName_EX()��NET_DLDVR_GetFileByTime_EX()�����ķ���ֵ		 
 *	�������:��
 *	��������:����ֵ��0-100�������ظ�����ʾ��ȡʧ��
 *	˵��: 
 */
NET_DLDVR_API INT	STDCALL NET_DLDVR_GetDownloadPos_EX(LONG lFileHandle);

/*      ����˵��:��¼�����ƽ���Զ�̻ط�
*     �������:lsDVRIP,wDVRPort, sUserName, sPassword����ָ��DVR������Ϣ
               sPlayBackFileName����Ҫ���лطŵ�¼���ļ���
               hWnd�����лطŵĴ��ھ��
			   dwStartPos, ��ʼ����λ��
*     �������:��
*     ��������: ���ž������ΪNET_DLDVR_StopPlayBack�Ⱥ����Ĳ��������ظ�����ʾʧ��
*     ˵��: �ýӿڲ�������IPCamera����
*/
NET_DLDVR_API LONG  STDCALL NET_DLDVR_PlayBackByName_EX(CHAR *sDVRIP,WORD wDVRPort,CHAR *sUserName,CHAR *sPassword,CHAR *sPlayBackFileName, HWND hWnd, DWORD dwStartPos);

/*      ����˵��:��ʱ��ν���Զ�̻ط�
*     �������:sDVRIP,wDVRPort, sUserName, sPassword����ָ��DVR������Ϣ
               lChannel��ͨ���ţ���0��ʼ
               lpStartTime����ʼʱ��
               lpStopTime������ʱ��
               hWnd�����лطŵĴ��ھ��
*     �������:��
*     ��������: ���ž������ΪNET_DLDVR_StopPlayBack�Ⱥ����Ĳ��������ظ�����ʾʧ��
*     ˵��: �ýӿڲ�������IPCamera��NVR����
*/
NET_DLDVR_API LONG  STDCALL NET_DLDVR_PlayBackByTime_EX(CHAR *sDVRIP,WORD wDVRPort,CHAR *sUserName,CHAR *sPassword,LONG lChannel, LPNET_DLDVR_TIME lpStartTime, LPNET_DLDVR_TIME lpStopTime, HWND hWnd, DWORD dwStartPos);

/* 	����˵��:��̨���ƣ���Ҫ�Ƚ��м���
 *	�������:lRealHandle��NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�����ķ���ֵ
			 dwPTZCommand������ֵ
				#define LIGHT_PWRON						3	// ��ͨ�ƹ��Դ 
				#define WIPER_PWRON						2	// ��ͨ��ˢ���� 
				#define FAN_PWRON						4	// ��ͨ���ȿ��� 
				#define HEATER_PWRON					5	// ��ͨ���������� 
				#define AUX_PWRON						6	// ��ͨ�����豸���� 

				#define ZOOM_IN							11	// �������ٶ�SS���(���ʱ��) 
				#define ZOOM_OUT						12	// �������ٶ�SS��С(���ʱ�С) 
				#define FOCUS_NEAR						13	// �������ٶ�SSǰ�� 
				#define FOCUS_FAR						14	// �������ٶ�SS��� 
				#define IRIS_OPEN						15	// ��Ȧ���ٶ�SS���� 
				#define IRIS_CLOSE						16	// ��Ȧ���ٶ�SS��С 
				#define TILT_UP							21	// ��̨��SS���ٶ����� 
				#define TILT_DOWN						22	// ��̨��SS���ٶ��¸� 
				#define PAN_LEFT						23	// ��̨��SS���ٶ���ת 
				#define PAN_RIGHT						24	// ��̨��SS���ٶ���ת 
				#define PAN_AUTO						29	// ��̨��SS���ٶ������Զ�ɨ�� 
			 dwAction����ֹ̨ͣ������ʼ������1����ʼ��0��ֹͣ
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR���ͣ���Ҫ����֧���½ӿ�REMOTE_PTZ_CONTROL_REQUEST_EX������ʹ���������ص�¼�û�ID  
 */
BOOL STDCALL NET_DLDVR_PTZControl_EX(LONG lRealHandle,DWORD dwPTZCommand,DWORD dwStop);

/* 	����˵��:��̨Ԥ��λ���ƣ���Ҫ�ȴ򿪼���
 *	�������:lRealHandle�����Ӿ������NET_DLDVR_RealPlay()��NET_DLDVR_RealPlay_EX()�����ķ���ֵ
			 dwPTZPresetCmd����̨Ԥ�õ�����
					#define SET_PRESET		1	// ����Ԥ�õ� 
					#define CLE_PRESET		2	// ���Ԥ�õ� 
					#define GOTO_PRESET		3	// ת��Ԥ�õ�
			 dwPresetIndex��Ԥ�õ����ţ����֧��128��Ԥ�õ�
			 sPresetName,Ԥ�õ�����
 *	�������:��
 *	��������:TRUE���ɹ��� FALSE��ʧ��
 *	˵��: �ýӿڲ�������IPCamera��NVR���ͣ���Ҫ����֧���½ӿ�REMOTE_PTZPRESET_CONTROL_REQUEST_EX������ʹ���������ص�¼�û�ID
 */
BOOL STDCALL NET_DLDVR_PTZPreset_EX(LONG lRealHandle,DWORD dwPTZPresetCmd,DWORD dwPresetIndex,const char *sPresetName);


}//extern "C"

#endif//#ifndef DLLSDK_INTERFACE_H
