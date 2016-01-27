//---------------------------------------------------------------------------
#ifndef MOBOTIXExportH
#define MOBOTIXExportH
#include "windows.h"

#ifdef MOBOTIX_LIB
#include "RecordConst.h"
#else

#endif
//---------------------------------------------------------------------------

#ifdef MOBOTIX_EXPORTS
#define EN_API extern "C" __declspec(dllexport)
#else
#define EN_API extern "C" __declspec(dllimport)
#endif

#define CC __stdcall

#ifndef CALLBACK_TYPE
#define CALLBACK_TYPE
enum CallBackType
{
    cbtUnknown = 0,     //δ֪����
    cbtSerial = 1,      //���������ϴ��ص�
    cbtVoice = 2,       //���������ϴ��ص�
    cbtVideo = 3,       //��Ƶ�����ϴ��ص�
    cbtMessage = 4      //��Ϣ֪ͨ�ϴ��ص�
};
#endif

#ifndef HANDLE_KIND
#define HANDLE_KIND
enum HandleKind
{
    hkUser = 1,         //�û�ע����
    hkMedia = 2,        //ͨ�����Ӿ��
    hkSerial = 3,       //���ڿ��ƾ��
    hkVioce = 4,        //�����Խ����
    hkAuxOut = 5        //����������
};
#endif

#ifndef NET_DVR_ALARM_INFO
#define NET_DVR_ALARM_INFO
//�ϴ�������Ϣ
struct NetDVRAlarmInfo
{
    DWORD dwDeviceType;                 /*�豸���� MOBOTIX EDVR ����ֵΪ5*/
	DWORD dwAlarmType;                  /*0-�ź�������,1-Ӳ����,2-�źŶ�ʧ��3���ƶ���⣬4��Ӳ��δ��ʽ��,5-��дӲ�̳���,6-�ڵ�����,7-��ʽ��ƥ��, 8-�Ƿ�����*/
	DWORD dwAlarmInputNumber;           /*��������˿�,��0��ʼ*/
	DWORD dwAlarmOutputNumber[4];       /*��������˿ڶ�Ӧ������˿ڣ���һλΪ1��ʾ��Ӧ��һ�����*/
	DWORD dwAlarmRelateChannel[16];     /*��������˿ڶ�Ӧ��¼��ͨ������һλΪ1��ʾ��Ӧ��һ·¼��,dwAlarmRelateChannel[0]��Ӧ��1��ͨ��*/
	DWORD dwChannel[16];                /*dwAlarmTypeΪ2��3ʱ����ʾ�ĸ�ͨ����dwChannel[0]λ��Ӧ��0��ͨ��*/
	DWORD dwDiskNumber[16];             /*dwAlarmTypeΪ4ʱ,��ʾ�ĸ�Ӳ��*/
};                                                    
#endif

//�����������          added in 20070716
#ifndef DECODE_TYPE
#define DECODE_TYPE
enum DecodeType
{
    dtSoftDecode = 1,   //�����
    dtHardDecode = 2    //Ӳ����
};
#endif

//������Ƶ��ʽ          added in 20070720
#ifndef NZ_VIDEO_STANDARD
#define NZ_VIDEO_STANDARD
typedef enum {
   vsNone  = 0x80000000,
   vsNTSC  = 0x00000001,
   vsPAL   = 0x00000002,
   vsSECAM = 0x00000004
} VideoStandard;
#endif

//����Ӳ����ģʽ                added in 20070724
#ifndef HARD_DECODE_MODE
#define HARD_DECODE_MODE
enum HardDecodeMode
{
   hdmBoth                  = 0,        //Ӳ�����ͬʱ�����PC��Ļ�͵���ǽ��
   hdmDecodeOnly            = 1,        //Ӳ�����������PC��Ļ��
   hdmOutputOnly            = 2,        //Ӳ���������������ǽ��
   hdmBothButSoftDecode     = 3         //Ӳ��������������ǽ�������������PC��Ļ��  added in 20080605
};
#endif

//ͨ��״̬                added in 20080523
#ifndef CHANNEL_STATUS
#define CHANNEL_STATUS
struct ChannelStatus
{
    unsigned long   ulNum;
    BOOL            bOpen;                          //�Ƿ��Ѵ�
    BOOL            bVideoPlay;                     //�Ƿ����ڲ�����Ƶ
    BOOL            bRecord;                        //�Ƿ�����¼��
    BOOL            bAudioPlay;                     //�Ƿ����ڲ�����Ƶ
    BOOL            bInAutoConnection;              //�Ƿ����Զ��ָ�֮��
};
#endif

//mobotix����PTZ����Ͷ���added by ligen for mobotix in 20091020
enum VPTZCommandTargetType
{
    ttRemote = 0,  //�����豸
    ttSoftware     //�������
};
//end

#ifdef MOBOTIX_LIB
//¼���ļ���Ϣ
typedef SEC_MSG_QUERY_DVR_RECORD_FILE_INFO RecordFileInfo;
typedef SEC_MSG_QUERY_DVR_RECORD_FILE_INFO_EX RecordFileInfoEx;
#else

#ifndef RECORD_INFO_DEFINED
#define RECORD_INFO_DEFINED

//¼���ļ�����
#define NZIT_DVR_RECORD_TYPE_UNKNOWN     0x00    //δ֪��¼������
#define NZIT_DVR_RECORD_TYPE_NORMAL      0x01    //��ͨ¼��
#define NZIT_DVR_RECORD_TYPE_MOTION      0x02    //��̬���¼��
#define NZIT_DVR_RECORD_TYPE_ALARM       0x03    //����¼��
#define NZIT_DVR_RECORD_TYPE_ALL         0x10    //�������͵�¼��

//¼��ʱ��
#ifndef DEC_RecordTime
#define DEC_RecordTime
typedef struct tag_RecordTime
{
    DWORD m_dwYear;       /* ��*/
    DWORD m_dwMonth;      /* ��*/
    DWORD m_dwDay;        /* ��*/
    DWORD m_dwHour;       /* ʱ*/
    DWORD m_dwMinute;     /* ��*/
    DWORD m_dwSecond;     /* ��*/
}RecordTime;
#endif

//¼���ļ���Ϣ
typedef struct tag_RecordFileInfo
{
    unsigned short  m_usChannelNo;      //ͨ���ţ���1��ʼ����1��ͨ��Ϊ1
    unsigned char   m_ucRecordFileType; //¼���ļ�����
    unsigned char   m_ucReserve;        //����
    unsigned char   m_szPath[64];       //¼���ļ��ľ���·��
    RecordTime      m_rtStart;          //¼���ļ���ʼʱ�䡢����
    RecordTime      m_rtEnd;            //¼���ļ�����ʱ�䡢����
}RecordFileInfo;

//¼���ļ���Ϣ����
typedef struct tag_RecordFileInfoEx
{
    unsigned short  m_usID;             //¼���ļ�ID
    unsigned short  m_usReserve;        //����
    unsigned short  m_usChannelNo;      //ͨ���ţ���1��ʼ����1��ͨ��Ϊ1
    unsigned char   m_ucRecordFileType; //¼���ļ�����
    unsigned char   m_ucReserve2;       //����2
    unsigned char   m_szName[64];       //¼���ļ�·��������
    RecordTime      m_rtStart;          //¼���ļ���ʼʱ�䡢����
    RecordTime      m_rtEnd;            //¼���ļ�����ʱ�䡢����
    unsigned long   m_ulSize;           //¼���ļ���С
}RecordFileInfoEx;

#endif
#endif

//��Ƶ������������Ϣ
struct ConnInfo;

//mobotix ������Ŀ�������, ������mobotix_sdk.h added by ligen for mobotix in 20091020
#ifndef MOBOTIX_EXPORTS
#define MOBOTIX_SDK_BASE                           10000
//����PTZ������
#define MOBOTIX_SDK_VPTZ_BASE                      (MOBOTIX_SDK_BASE + 1000)
#define MOBOTIX_SDK_VPTZ_UP                        (MOBOTIX_SDK_VPTZ_BASE + 1)    //����PTZ����
#define MOBOTIX_SDK_VPTZ_DOWN                      (MOBOTIX_SDK_VPTZ_BASE + 2)    //����PTZ����
#define MOBOTIX_SDK_VPTZ_LEFT                      (MOBOTIX_SDK_VPTZ_BASE + 3)    //����PTZ����
#define MOBOTIX_SDK_VPTZ_RIGHT                     (MOBOTIX_SDK_VPTZ_BASE + 4)    //����PTZ����
#define MOBOTIX_SDK_VPTZ_CENTER_PAN                (MOBOTIX_SDK_VPTZ_BASE + 5)    //����PTZ�ص��м�
#define MOBOTIX_SDK_VPTZ_ZOOMIN                    (MOBOTIX_SDK_VPTZ_BASE + 6)    //����PTZ����
#define MOBOTIX_SDK_VPTZ_ZOOMOUT                   (MOBOTIX_SDK_VPTZ_BASE + 7)    //����PTZ��Զ
#define MOBOTIX_SDK_VPTZ_ZOOM_X1                   (MOBOTIX_SDK_VPTZ_BASE + 8)    //����PTZ�ص�ԭʼ����
#define MOBOTIX_SDK_VPTZ_ROTATE                    (MOBOTIX_SDK_VPTZ_BASE + 9)    //����PTZ˳ʱ����ת
#define MOBOTIX_SDK_VPTZ_ROTATE2                   (MOBOTIX_SDK_VPTZ_BASE + 10)   //����PTZ��ʱ����ת
#define MOBOTIX_SDK_VPTZ_DISPLAYMODE_SIMPLE        (MOBOTIX_SDK_VPTZ_BASE + 11)   //����PTZԭʼ����
#define MOBOTIX_SDK_VPTZ_DISPLAYMODE_SURROUND      (MOBOTIX_SDK_VPTZ_BASE + 12)   //����PTZչƽ����
#define MOBOTIX_SDK_VPTZ_DISPLAYMODE_SWEEP         (MOBOTIX_SDK_VPTZ_BASE + 13)   //����PTZ���ӻ���
#define MOBOTIX_SDK_VPTZ_DISPLAYMODE_PANORAMA      (MOBOTIX_SDK_VPTZ_BASE + 14)   //����PTZȫ������
#define MOBOTIX_SDK_VPTZ_DISPLAYMODE_DOUBLEPANO    (MOBOTIX_SDK_VPTZ_BASE + 15)   //����PTZ˫ȫ������
#define MOBOTIX_SDK_VPTZ_DISPLAYMODE_PANORAMAFOCUS (MOBOTIX_SDK_VPTZ_BASE + 16)   //����PTZȫ�����㻭��
#define MOBOTIX_SDK_VPTZ_DISPLAYMODE_FOUR          (MOBOTIX_SDK_VPTZ_BASE + 17)   //����PTZ�Ļ���
#define MOBOTIX_SDK_VPTZ_SELECT_WINDOW             (MOBOTIX_SDK_VPTZ_BASE + 18)   //����PTZѡ����ƴ���, �໭��ʱ��Ч
#endif // MOBOTIX_EXPORTS
//end

#ifndef GENERAL_CALLBACK
#define GENERAL_CALLBACK
typedef BOOL (CALLBACK* GeneralDataCallBack)(LONG lUserID,CallBackType cbtCallBackType,
        char *pBuf,DWORD dwBufLen,DWORD dwUser);
#endif

//added on 20100104
#ifndef DRAW_CALLBACK
#define DRAW_CALLBACK
typedef void (CALLBACK* DrawCallBack)(LONG lChannelHandle,HDC hDC,int iWidth,
    int iHeight,DWORD dwUser);
#endif

//���÷�ȫ�ֻص�����
EN_API void CC MOBOTIX_SetGeneralDataCallBack2(long lChannelHandle,
											   GeneralDataCallBack pGeneralDataCallBack,
											   DWORD dwUser);
//���ý�������  added in 20070716
EN_API BOOL CC MOBOTIX_SetDecodeType(DecodeType dtType);

EN_API void CC MOBOTIX_SetGeneralDataCallBack(GeneralDataCallBack pGeneralDataCallBack);

EN_API BOOL CC MOBOTIX_InitClient(long lParentHandle);
EN_API BOOL CC MOBOTIX_UnInitClient();

EN_API long CC MOBOTIX_Login(ConnInfo* pCurConnInfo);
EN_API BOOL CC MOBOTIX_Logout(long lLoginHandle);

EN_API long CC MOBOTIX_OpenChannel(const char* pszURL,HardDecodeMode hdmHardDecodeMode);
//ָ��Ӳ����ͨ���ţ��粻ָ�����Զ�����һ��Ӳ����ͨ���� added in 20080701
EN_API long CC MOBOTIX_OpenChannel2(const char* pszURL,
    HardDecodeMode hdmHardDecodeMode,unsigned long ulHardDecodeChannel);
EN_API BOOL CC MOBOTIX_CloseChannel(long lChannelHandle);

//added on 20100104
EN_API BOOL CC MOBOTIX_SetDrawCallBack(long lChannelHandle,
                                       DrawCallBack pDrawCallBack,
                                       DWORD dwUser);

EN_API BOOL CC MOBOTIX_StartVideo(long lChannelHandle,long lDisplayHandle);
EN_API BOOL CC MOBOTIX_StopVideo(long lChannelHandle);
//ˢ��ĳ��ͨ����Ƶ     added in 20090421
EN_API BOOL CC MOBOTIX_RefreshVideo(long lChannelHandle);

EN_API BOOL CC MOBOTIX_StartRecord(long lChannelHandle,const char* pszFileName);
EN_API BOOL CC MOBOTIX_StopRecord(long lChannelHandle);

EN_API BOOL CC MOBOTIX_StartAudio(long lChannelHandle);
EN_API BOOL CC MOBOTIX_StopAudio(long lChannelHandle);

EN_API BOOL CC MOBOTIX_TakePicture(long lChannelHandle,char *pszFileName);

EN_API BOOL CC MOBOTIX_Preview_Control(long lChannelHandle,char *pPTZCodeBuf,
        DWORD dwBufSize,long lCOMPort);
EN_API BOOL CC MOBOTIX_NoPreview_Control(long lChannelHandle,unsigned long ulChannel,
        char *pPTZCodeBuf,DWORD dwBufSize,long lCOMPort);

//lParam1�������������ʱ��ʾ�ٶ�;���������Ԥ�õ�ʱ��ʾԤ�õ�ţ�����������δʹ��
//��������ƵԤ����������£�ͨ�����ڷ����������������  added in 20080508
EN_API BOOL CC MOBOTIX_Preview_SendCmd(long lChannelHandle,
    long lCmdID,long lParam1,long lParam2,long lParam3);
//��δ������ƵԤ����������£�ͨ�����ڷ����������������  added in 20080508
EN_API BOOL CC MOBOTIX_NoPreview_SendCmd(long lChannelHandle,unsigned long ulChannel,
    long lCmdID,long lParam1,long lParam2,long lParam3);

EN_API BOOL CC MOBOTIX_SetAlarmOut(long lChannelHandle, long lOutPort, long lOutStatic);

EN_API BOOL CC MOBOTIX_StartRemoteRecord(long lChannelHandle,LONG lRecordType);
EN_API BOOL CC MOBOTIX_StopRemoteRecord(long lChannelHandle);
EN_API long CC MOBOTIX_GetRemoteRecordState(long lChannelHandle);


//ǰ��¼��������¼
EN_API long CC MOBOTIX_RecordLogin(ConnInfo* pCurConnInfo);
//ǰ��¼������ע��
EN_API BOOL CC MOBOTIX_RecordLogout(long lLoginHandle);
//��¼��ͨ��
EN_API long CC MOBOTIX_RecordChannelOpen(const char* pszURL);
//��¼��ͨ��
EN_API long CC MOBOTIX_RecordChannelOpen2(const char* pszURL,unsigned long ulHardDecodeChannel);
//�ر�¼��ͨ��
EN_API BOOL CC MOBOTIX_RecordChannelClose(long lChannelHandle);

//��ѯ¼���¼
EN_API long  CC MOBOTIX_FindFile(long lChannelHandle,DWORD dwFileType,
    RecordTime* pStartTime, RecordTime* pStopTime,bool bQueryAllChannel);
//������һ��¼���¼
EN_API RecordFileInfo*  CC MOBOTIX_FindNextFile(long lFindHandle);
//�رձ��β�ѯ
EN_API void  CC MOBOTIX_FindClose(long lFindHandle);
//���ļ����ƿ�ʼ����¼��
EN_API BOOL  CC MOBOTIX_StartPlay(long lFindHandle,
                                       RecordFileInfo* pRecordFileInfo,
                                       HWND hWnd);
//��ʱ��ο�ʼ����¼��
EN_API BOOL  CC MOBOTIX_StartPlay2(long lFindHandle,
                                       RecordTime* pStartTime,
                                       RecordTime* pStopTime,
                                       HWND hWnd);

//���ļ�����ʼ����¼��   added in 20080528
EN_API BOOL  CC MOBOTIX_StartPlay3(long lFindHandle,
    const char* pszFileName,HWND hWnd);
//ֹͣ����¼��
EN_API BOOL  CC MOBOTIX_StopPlay(long lFindHandle);
//��ͣ����¼��
EN_API BOOL CC MOBOTIX_PausePlay(long lFindHandle);
//�ָ�����¼��
EN_API BOOL CC MOBOTIX_ResumePlay(long lFindHandle);
//���ٲ���¼��
EN_API BOOL CC MOBOTIX_FastPlay(long lFindHandle);
//�����ٲ���¼��
EN_API BOOL CC MOBOTIX_SlowPlay(long lFindHandle);
//��֡����¼��
EN_API BOOL CC MOBOTIX_OneByOnePlay(long lFindHandle);
//����¼���ļ�ʱ��
EN_API long CC MOBOTIX_GetFileTime(long lFindHandle);
//����¼���ļ��Ѳ���ʱ��
EN_API long CC MOBOTIX_GetPlayedTime(long lFindHandle);
//����¼���ļ�֡��
EN_API long CC MOBOTIX_GetFileFrames(long lFindHandle);
//����¼���ļ��Ѳ���֡��
EN_API long CC MOBOTIX_GetPlayedFrames(long lFindHandle);
//����¼���ļ����Ž���
EN_API float CC MOBOTIX_GetPlayPos(long lFindHandle);
//����¼���ļ����Ž���
EN_API BOOL CC MOBOTIX_SetPlayPos(long lFindHandle,float fPlayPos);
//�ָ�Step��¼���ļ�����
EN_API BOOL CC MOBOTIX_StepResumePlay(long lFindHandle);
//��������
EN_API BOOL CC MOBOTIX_SetVolume(long lFindHandle,long lVolume);
//��������
EN_API BOOL CC MOBOTIX_PlaySound(long lFindHandle);
//ֹͣ��������
EN_API BOOL CC MOBOTIX_StopSound(long lFindHandle);
//��ʼ����¼��
EN_API BOOL CC MOBOTIX_StartDownloadFile(long lFindHandle,
                                              RecordFileInfo* pRecordFileInfo,
                                              char* pszSavedFileName);
//¼���ļ����ؽ���
EN_API int CC MOBOTIX_GetDownloadPos(long lFindHandle);
//ֹͣ����¼���ļ�
EN_API BOOL CC MOBOTIX_StopDownloadFile(long lFindHandle);

//����������¼���ѯ��ֱ�Ӱ��ļ����ƻط�¼����            //add 20080528
EN_API long CC MOBOTIX_RecordPlay(long lChannelHandle);

//ֹͣ������¼���ѯ��ֱ�Ӱ��ļ����ƻط�¼����            //add 20080528
EN_API void CC MOBOTIX_RecordStop(long lFindHandle);

//�����豸ͨ����������豸���Ӿ��
EN_API long CC MOBOTIX_GetUserID(long lChannelHandle);

//�Ƿ��豸�Զ�Уʱ����
EN_API void CC MOBOTIX_SetAjustTime(BOOL bEnabled);

//����ת��ģʽ�»ط�ǰ���豸¼���ļ��Ƿ����ת��ģʽ��
//ȱʡ����ֱ��ģʽ���ʡ��ط�¼��  added in 20080220
EN_API void CC MOBOTIX_SetRecordPlayWithProxy(BOOL bEnabled);

//����¼��״̬��1��ʾ����¼��0��ʾδ¼��-1����״̬ʧ��
EN_API long CC MOBOTIX_GetRecordState(long lChannelHandle);

//������������Χ0-0xffff
EN_API BOOL CC MOBOTIX_SetAudioVolume(long lChannelHandle,
                                           long lVolume);

//���ø�ͨ����Ƶ����
//����ֵ����Χ��0-255��
//�Աȶ�ֵ����Χ��0-255��
//���Ͷ�ֵ����Χ��0-255��
//ɫ��ֵ����Χ��0-255��
EN_API BOOL  CC MOBOTIX_SetVideoParam(long lChannelHandle,
                                           int iBrightness,
                                           int iContrast,
                                           int iSaturation,
                                           int iHue);

//��ȡ��ͨ����Ƶ����
EN_API BOOL  CC MOBOTIX_GetVideoParam(long lChannelHandle,
                                           int* piBrightness,
                                           int* piContrast,
                                           int* piSaturation,
                                           int* piHue);

//�л�����ָ���
EN_API BOOL  CC MOBOTIX_Switch_Camera(long lChannelHandle,
                                           long lCmdID);

//�л�����ָ�����֧��1��16��Ƶ����ͨ��ͨ����1��16��������Ƶ���ͨ���л������Ƶ��
//֧�ֻ��л���4��9��12��16����ͨ����1��16��������Ƶ���ͨ�������Ƶ
//added in 20080222
EN_API BOOL  CC MOBOTIX_Switch_Camera2(long lChannelHandle,long lCmdID,
        long lVideoOutputChannel);

//���ؽ���ͨ������  added in 20070716
EN_API unsigned long CC MOBOTIX_GetDecodeChannelCount();

//������ʾͨ������  added in 20070716
EN_API unsigned long CC MOBOTIX_GetDisplayChannelCount();

//������ʾ����
EN_API BOOL __stdcall MOBOTIX_SetupDisplayRegion(unsigned long ulDisplayChannel,
                                                unsigned long ulDisplayRegionCount);

//�����ʾ����
EN_API BOOL __stdcall MOBOTIX_ClearDisplayRegion(unsigned long ulDisplayChannel);

//����һ·����ͨ����Ƶ�����һ�������
//��Ƶͨ�����      ����һ������ͨ��
//ulPort            ����˿ڣ�0��1��������ѡ��һ
//bOpen             �򿪻�ر�
//ulDisplayChannel  ���ͨ������1��ʼ
//ulDisplayRegion   ��ʾ���򣬴�1��ʼ�����Ϊ16
EN_API BOOL CC MOBOTIX_SetVideoOutput(long lChannelHandle,
                                           unsigned long ulPort,
                                           BOOL bOpen,
                                           unsigned long ulDisplayChannel,
                                           unsigned long ulDisplayRegion,
                                           unsigned long ulDisplayRegionCount);

//����һ·����ͨ����Ƶ�����һ�������
//��Ƶͨ�����      ����һ������ͨ��
//bOpen             �򿪻�ر�
//ulDisplayChannel  ���ͨ������1��ʼ
EN_API BOOL CC MOBOTIX_SetAudioOutput(long lChannelHandle,
                                           BOOL bOpen,
                                           unsigned long ulDisplayChannel);

//�������ģ����Ƶ���ȣ�0��255��
EN_API BOOL CC MOBOTIX_SetDisplayVideoBrightness(unsigned long ulDisplayChannel,
        long lBrightness);

//�������ģ����Ƶ��ʽ
EN_API BOOL CC MOBOTIX_SetDisplayStandard(unsigned long ulDisplayChannel,
                                               VideoStandard vsVideoStandard);

//ˢ��PC��Ļ�����н���ͨ������Ƶ����
EN_API BOOL CC MOBOTIX_RefreshSurface();

//ˢ��PC��Ļ�϶�Ӧָ������ͨ����������Ƶ����
EN_API BOOL CC MOBOTIX_RefreshSurfaceRegion(long lChannelHandle,
                                                 BOOL bFullScreen);

//����ͨ��״̬   addded in 20080523
EN_API BOOL CC MOBOTIX_GetChannelStatus(long lChannelHandle,ChannelStatus* pChannelStatus);

//added by ligen for mobotix in 20091020
//����mobotix���������PTZ����
EN_API BOOL CC MOBOTIX_VPTZControl(VPTZCommandTargetType ttType,
                                   long lChannelHandle,
                                   long lCommand,
                                   long lParam1,
                                   long lParam2);
//end


#endif
