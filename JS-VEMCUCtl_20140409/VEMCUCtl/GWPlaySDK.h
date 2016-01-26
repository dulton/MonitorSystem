#ifndef _GW_PLAY_SDK_H_
#define _GW_PLAY_SDK_H_


//////////////////////////////////////////////////////////////////////////
///����������
#define        DES_LEN                128   
///Ĭ���ַ�������
#define        DEFAULT_LEN        128   

///�������ͣ�ʵʱ��
#define        IFC_PLAY_REAL                    0
///�������ͣ���ʷ��
#define        IFC_PLAY_HISTORY              1

//////////////////////////////////////////////////////////////////////////
typedef enum _DEOCDE_DATA_TYPE
{
	T_AUDIO16     = 1,
	T_RGB32         = 2,
	T_YV12            = 3,
}DEOCDE_DATA_TYPE;


// SDK��Ϣ
typedef struct _TPluginInfo
{
	long nSize;//���ݽṹ����          
	char szDesc[DES_LEN];//ģ������            
	char szSoftVersion[DEFAULT_LEN]; //����汾
	char szProvider[DEFAULT_LEN];//������Ϣ    
}TPluginInfo;

// ֡��Ϣ
typedef  struct _TFrameInfo
{
	long nWidth;//�������λ���ء��������Ƶ������Ϊ0                     
	long nHeight;//����ߡ��������Ƶ������Ϊ0                    
	long nStamp;//ʱ����Ϣ����λ����                     
	DEOCDE_DATA_TYPE nDecodeType;//�������ͣ�1��T_AUDIO16����2��T_RGB32���� 3��T_YV12��                      
	long nFrameDuration;//ÿ֡����ʱ��                 
}TFrameInfo;

//����ص�������Ϣ
typedef struct _TDecCallbackParams
{
	BYTE*       pBuf;//��������
	long        nSize;//���ݳ���
	TFrameInfo* pFrameInfo;//֡��Ϣ
	long    nReserved1;//����ֵ
	long    nReserved2;//����ֵ
}TDecCallbackParams;

///��ͼ�ص�������Ϣ
typedef struct _TDrawCallbackParams
{
	HDC     hDc;//��ͼDC
	long    nReserved1;//����ֵ
	long    nReserved2;//����ֵ
}TDrawCallbackParams;

///�ļ�������Ϣ
typedef struct _TFileIndexParams
{
	long    nFrameNo;//֡���
	long    nFilePos;//�ļ�λ��
	long    nFrameTime;//֡ʱ�꣨���룩    
}TFileIndexParams;

///��Ƶ������Ϣ
typedef struct _TVideoParams
{
	int nBrightness;//���ȣ�ȡֵ��0-255��
	int nContrast;//�Աȶȣ�ȡֵ��0-255��
	int nSaturation;//���Ͷȣ�ȡֵ��0-255��
	int nHue;//ɫ����ȡֵ��0-255��
}TVideoParams;

//�����ݲ���
typedef struct _TStreamDataParams
{
	BYTE*   pBuffer;//��������
	long    nSize;//���ݳ���
	long    nReserved1;//����ֵ
	long    nReserved2;//����ֵ
}TStreamDataParams;

//////////////////////////////////////////////////////////////////////////
//����Ƶ����ص�����
typedef void (CALLBACK* PDecCBFun)( HANDLE hHandle, 
								  TDecCallbackParams* pDecCBInfo, 
								  DWORD* dwUser);

//��ͼ�ص�����
typedef void (CALLBACK* PDrawCBFun)(HANDLE hHandle, 
								   TDrawCallbackParams* pDrawCBInfo, 
								   DWORD* dwUser);

//���崦��ص�����
typedef void (CALLBACK * PSourceBufCBFun)(HANDLE hHandle, 
										 DWORD dwBufSize, 
										 DWORD dwUser,
										 void*pResvered);

typedef void (CALLBACK * PFileIndexCBFun)(TFileIndexParams* pFileIndexCBInfo, 
										 DWORD dwUser);

//-----------------------------------------------------------------------------
//     �ӿڶ���
//-----------------------------------------------------------------------------

//IFC_GetLastError ����ָ�붨��
typedef int (__stdcall* PIFC_GetLastError) (HANDLE hHandle);

//IFC_Initialize ����ָ�붨��
typedef BOOL (__stdcall* PIFC_Initialize) ();

//IFC_Uninitialize ����ָ�붨��
typedef void (__stdcall* PIFC_Uninitialize) ();

//IFC_GetPluginInfo ����ָ�붨��
typedef BOOL( __stdcall* PIFC_GetPluginInfo) (TPluginInfo *pInfo);

//IFC_GetFileHeaderLen ����ָ�붨��
typedef int ( __stdcall* PIFC_GetFileHeaderLen) (LPCTSTR lpszLocalFileName);

//-----------------------------------------------------------------------------
//     �����������
//-----------------------------------------------------------------------------

//IFC_CreateHandle ����ָ�붨��
typedef HANDLE ( __stdcall* PIFC_CreateHandle)();

//IFC_DestoryHandle ԭ�Ͷ���
typedef BOOL ( __stdcall* PIFC_DestroyHandle)(HANDLE hHandle);

//-----------------------------------------------------------------------------
//     ���������뷽ʽ����
//-----------------------------------------------------------------------------

//IFC_StreamOpen ����ָ�붨��
typedef BOOL (__stdcall* PIFC_StreamOpen) (HANDLE hHandle, char *pData, int nLen, int nStreamType, long nReserved1);

//IFC_Play ԭ�Ͷ���
typedef BOOL (__stdcall* PIFC_Play) (HANDLE hHandle, HWND hWnd);

//IFC_SetDecCallback ����ָ�붨��
typedef BOOL (__stdcall* PIFC_SetDecCallBack) (HANDLE hHandle, PDecCBFun *pfDecCBFun, DWORD dwUser);

//IFC_SetDrawCallback ����ָ�붨��
typedef BOOL (__stdcall* PIFC_SetDrawCallBack) (HANDLE hHandle, PDrawCBFun *pfDrawCBFun, DWORD dwUser);

//IFC_SetSourceBufCallBack ����ָ�붨��
typedef BOOL (__stdcall* PIFC_SetSourceBufCallBack) (HANDLE hHandle, 
                                                   DWORD dwThreShold,
                                                   PSourceBufCBFun* pfSourceBufCBFun, 
                                                   DWORD dwUser, 
                                                   void *pReserved);

//IFC_SetFileIndexCallBack ����ָ�붨��
typedef HANDLE (__stdcall* PIFC_SetFileIndexCallBack)(LPCTSTR lpszFileName, 
                                                     PFileIndexCBFun* pfFileIndexCBFun, 
                                                     DWORD dwUser);

//IFC_StopFileIndex ����ָ�붨��
typedef HANDLE (__stdcall* PIFC_StopFileIndex)(HANDLE hIndexHandle);

//IFC_StreamSetPlayBuffer ����ָ�붨��
typedef BOOL (__stdcall* PIFC_StreamSetPlayBuffer) ( HANDLE hHandle,  int nBufferLen);

//IFC_StreamInputData ����ָ�붨��
typedef BOOL (__stdcall* PIFC_StreamInputData) (HANDLE hHandle, TStreamDataParams* pStreamInData);

//IFC_StreamResetBuffer ����ָ�붨��
typedef BOOL (__stdcall* PIFC_StreamResetBuffer) (HANDLE hHandle);

//IFC_StreamRefreshPlay ����ָ�붨��
typedef BOOL (__stdcall* PIFC_StreamRefreshPlay) ( HANDLE hHandle);

//IFC_Pause ����ָ�붨��
typedef BOOL (__stdcall* PIFC_Pause) (HANDLE hHandle, BOOL bPause);

//IFC_Fast ����ָ�붨��
typedef BOOL (__stdcall* PIFC_Fast) (HANDLE hHandle);

//IFC_Slow ����ָ�붨��
typedef BOOL (__stdcall* PIFC_Slow) (HANDLE hHandle);

//IFC_SoundOpen ����ָ�붨��
typedef BOOL (__stdcall* PIFC_SoundOpen) (HANDLE hHandle , int nSoundPlayType);

//IFC_SoundClose ����ָ�붨��
typedef BOOL (__stdcall* PIFC_SoundClose) (HANDLE hHandle);

//IFC_SetVolume ����ָ�붨��
typedef BOOL (__stdcall* PIFC_SetVolume) (HANDLE hHandle, DWORD dwVolume);

//IFC_StreamClose ����ָ�붨��
typedef BOOL (__stdcall* PIFC_StreamClose) ( HANDLE hHandle);

//-----------------------------------------------------------------------------
//     �ļ����뷽ʽ����
//-----------------------------------------------------------------------------

//IFC_FileOpen ����ָ�붨��
typedef BOOL (__stdcall* PIFC_FileOpen) (HANDLE hHandle, LPCTSTR lpszFileName);

//IFC_FileClose ����ָ�붨��
typedef BOOL (__stdcall* PIFC_FileClose) (HANDLE hHandle);

//IFC_Stop ����ָ�붨��
typedef BOOL (__stdcall* PIFC_Stop) (HANDLE hHandle);

//IFC_PlayCapturePic ����ָ�붨��
typedef BOOL (__stdcall* PIFC_PlayCapturePic) (HANDLE hHandle, int nPicType, int nPicQuality, LPCTSTR lpszPicFileName);

//IFC_PlayRefresh ����ָ�붨��
typedef BOOL (__stdcall* PIFC_PlayRefresh) (HANDLE hHandle);

//IFC_Pause ����ָ�붨��
typedef BOOL (__stdcall* PIFC_Pause) (HANDLE hHandle,BOOL bPause);

//IFC_FastBack ����ָ�붨��
typedef BOOL (__stdcall* PIFC_FastBack) (HANDLE hHandle);

//IFC_SlowBack ����ָ�붨��
typedef BOOL (__stdcall* PIFC_SlowBack) (HANDLE hHandle);

//IFC_Step ����ָ�붨��
typedef BOOL (__stdcall* PIFC_Step) (HANDLE hHandle);

//IFC_StepBack ����ָ�붨��
typedef BOOL (__stdcall* PIFC_StepBack) (HANDLE hHandle);

//IFC_SetPos ����ָ�붨��
typedef BOOL (__stdcall* PIFC_SetPos) (HANDLE hHandle, float fRealPos);

//IFC_GetPos ����ָ�붨��
typedef BOOL (__stdcall* PIFC_GetPos) (HANDLE hHandle, float *pfRealPos);

//IFC_GetTotalTime ����ָ�붨��
typedef BOOL (__stdcall* PIFC_GetTotalTime) (HANDLE hHandle, DWORD *pdwFileTime);

//IFC_GetPlayedTime ����ָ�붨��
typedef BOOL (__stdcall* PIFC_GetPlayedTime) (HANDLE hHandle, DWORD *pdwPlayedTime);

//IFC_GetTotalFrames ����ָ�붨��
typedef BOOL (__stdcall* PIFC_GetTotalFrames) (HANDLE hHandle, DWORD *pdwTotalFrames);

//IFC_GetFramePosition ����ָ�붨��
typedef BOOL (__stdcall* PIFC_GetFramePosition) (HANDLE hHandle, DWORD dwFrameNo, DWORD *pdwPosition);

//IFC_GetPlayedFrames ����ָ�붨��
typedef BOOL (__stdcall* PIFC_GetPlayedFrames) (HANDLE hHandle, DWORD *pdwPlayedFrames);

//IFC_SetVideoParams ����ָ�붨��
typedef BOOL (__stdcall* PIFC_SetVideoParams)(HANDLE hHandle, TVideoParams* pVideoParams, BOOL bDefault);

//IFC_GetVideoParams ����ָ�붨��
typedef BOOL (__stdcall* PIFC_GetVideoParams)(HANDLE hHandle, TVideoParams* pVideoParams);

//IFC_SetVideoWindows ����ָ�붨��
typedef BOOL (__stdcall* PIFC_SetVideoWindows)(HANDLE hHandle, HWND hWnd, RECT* pstDisplayRect, BOOL bEnable);

//IFC ����ָ��ṹ��
typedef struct _IFC_FUNCTION_PTR_
{
          PIFC_GetLastError                  GetLastError;
          PIFC_Initialize                         Initialize;
          PIFC_Uninitialize                    Uninitialize;
          PIFC_GetPluginInfo                GetPluginInfo;
          PIFC_GetFileHeaderLen         GetFileHeaderLen;
          PIFC_CreateHandle                CreateHandle;
          PIFC_DestroyHandle              DestroyHandle;
          PIFC_StreamOpen                  StreamOpen;
          PIFC_Play                                Play;
          PIFC_SetDecCallBack             SetDecCallBack;
          PIFC_SetDrawCallBack           SetDrawCallBack;
          PIFC_SetSourceBufCallBack   SetSourceBufCallBack;
          PIFC_SetFileIndexCallBack     SetFileIndexCallBack;
          PIFC_StopFileIndex                 StopFileIndex;
          PIFC_StreamSetPlayBuffer     StreamSetPlayBuffer;
          PIFC_StreamInputData           StreamInputData;
          PIFC_StreamResetBuffer        StreamResetBuffer;
          PIFC_StreamRefreshPlay        StreamRefreshPlay;
          PIFC_Pause                              Pause;
          PIFC_Fast                                 Fast;
          PIFC_Slow                                Slow;
          PIFC_SoundOpen                    SoundOpen;
          PIFC_SoundClose                    SoundClose;
          PIFC_SetVolume                     SetVolume;
          PIFC_StreamClose                  StreamClose;
          PIFC_FileOpen                        FileOpen;
          PIFC_FileClose                        FileClose;
          PIFC_Stop                               Stop;
          PIFC_PlayCapturePic             PlayCapturePic;
          PIFC_PlayRefresh                  PlayRefresh;
          PIFC_FastBack                       FastBack;
          PIFC_SlowBack                      SlowBack;
          PIFC_Step                              Step;
          PIFC_StepBack                      StepBack;
          PIFC_SetPos                          SetPos;
          PIFC_GetPos                         GetPos;
          PIFC_GetTotalTime              GetTotalTime;
          PIFC_GetPlayedTime           GetPlayedTime;
          PIFC_GetTotalFrames          GetTotalFrames;
          PIFC_GetFramePosition       GetFramePosition;
          PIFC_GetPlayedFrames       GetPlayedFrames;
          PIFC_SetVideoParams          SetVideoParams;
          PIFC_GetVideoParams         GetVideoParams;
          PIFC_SetVideoWindows       SetVideoWindows;
}IFC_FUNCTION_PTR;

//������Ϣ
typedef struct _GW_DECODE_FUNC_INFO_
{
	int nInitFlag;
	int nCode;
	HMODULE hModule; 
	IFC_FUNCTION_PTR DecodeFunc;
}GW_DECODE_FUNC_INFO;

//////////////////////////////////////////////////////////////////////////
//���ý�����Ϣ
bool SetGWDecFuncInfo(GW_DECODE_FUNC_INFO *pDecFuncInfo,int nCode,HMODULE hModule,IFC_FUNCTION_PTR* pIfcFuncPtr);

//�õ����뺯��
bool GWGetModuleFunc(HMODULE hModule,int nCode);

//��ʼ������
bool InitGWDecFuncInfo(int nCode);

//�õ�������Ϣ
GW_DECODE_FUNC_INFO *GetGWDecFuncInfo(int nCode);

//�ж��Ƿ���ڽ�����Ϣ
BOOL IsExsitGWDecInfo(int nCode);

#endif
