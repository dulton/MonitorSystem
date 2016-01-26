#pragma once

#include "InfoRecvQueue.h"
#include "include/mysql.h"				//�������ݿ�ͷ�ļ�

typedef struct _ass_user_operate_log
{
	int user_id;
	char ip_address[32];
	char operate_time[64];
	char operate_action[128];
}ASS_USER_OPERATE_LOG;

class CAssUserOperateLog
{
public:
	CAssUserOperateLog(void);
	~CAssUserOperateLog(void);

public:
	bool InitAssUserOperateLog();
	bool StartAssUserOperateLog();
	bool StopAssUserOperateLog();
	bool UnInitAssUserOperateLog();
	bool WriteAssUserOperateLog(ASS_USER_OPERATE_LOG *pAssUserOperateLog);

public:
	bool Lock();//����
	bool Unlock();//����
	bool SetAssUserOperateLog(char *pClientIp,char *pDBServerIp,int nDBServerPort,char *pDBName,char *pDBUserName,char *pDBUserPassword);//��Ա������ֵ
	bool ConnectMySql();	// �������ݿ�
	bool DisConnectMySql();	// �Ͽ����ݿ�
	bool CreateAssUserOperateLogTable(char *szAssUserOperateLogTableName);
	bool WriteAssUserOperateLogFromInfoRecvQueue();
	bool WriteAssUserOperateLogToDB(void *pInfo,int nInfoLen);
public:
	bool m_bAssUserOperateLogInitFlag;
	CRITICAL_SECTION m_csAssUserOperateLogLock;
	HANDLE m_hAssUserOperateLogThread;
	UINT m_uAssUserOperateLogThreadID;
	char  m_szClientIp[64];
	char  m_szDBServerIp[64];
	int   m_nDBServerPort;
	char  m_szDBName[256];
	char  m_szDBUserName[256];
	char  m_szDBUserPassword[64];
	MYSQL *m_pMySql;
	
};

//////////////////////////////////////////////////////////////////////////
unsigned __stdcall _AssUserOperateLogWriteThread(void *arg);

//////////////////////////////////////////////////////////////////////////
extern CAssUserOperateLog g_AssUserOperateLog;
