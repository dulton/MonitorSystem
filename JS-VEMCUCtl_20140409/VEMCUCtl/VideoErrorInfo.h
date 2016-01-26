#pragma once

#include "InfoRecvQueue.h"
#include ".\include\mysql\mysql.h"				//�������ݿ�ͷ�ļ�

typedef struct _video_error_info_
{
	char node_name[256];
	char station_name[256];
	char station_code[64];
	char camera_name[256];
	char camera_code[64];
	int    state;
	int    reason;
	int    flow;
	char time[64];
}VIDEO_ERROR_INFO;

class CVideoErrorInfo
{
public:
	CVideoErrorInfo(void);
	~CVideoErrorInfo(void);

public:
	bool InitVideoErrorInfo();
	bool StartVideoErrorInfo();
	bool StopVideoErrorInfo();
	bool UnInitVideoErrorInfo();
	bool WriteVideoErrorInfo(VIDEO_ERROR_INFO *pVideoErrorInfo);

public:
	bool Lock();//����
	bool Unlock();//����
	bool SetVideoErrorInfo(char *pClientIp,char *pDBServerIp,int nDBServerPort,char *pDBName,char *pDBUserName,char *pDBUserPassword);//��Ա������ֵ
	bool ConnectMySql();	// �������ݿ�
	bool DisConnectMySql();	// �Ͽ����ݿ�
	bool CreateVideoErrorInfoTable(char *szVideoErrorInfoTableName);
	bool WriteVideoErrorInfoFromInfoRecvQueue();
	bool WriteVideoErrorInfoToDB(void *pInfo,int nInfoLen);

public:
	bool m_bVideoErrorInfoInitFlag;
	CRITICAL_SECTION m_csVideoErrorInfoLock;
	HANDLE m_hVideoErrorInfoThread;
	UINT m_uVideoErrorInfoThreadID;
	char  m_szClientIp[64];
	char  m_szDBServerIp[64];
	int     m_nDBServerPort;
	char  m_szDBName[256];
	char  m_szDBUserName[256];
	char  m_szDBUserPassword[64];
	MYSQL *m_pMySql;
};


//////////////////////////////////////////////////////////////////////////
unsigned __stdcall _VideoErrorInfoWriteThread(void *arg);

//////////////////////////////////////////////////////////////////////////
extern CVideoErrorInfo g_VideoErrorInfo;