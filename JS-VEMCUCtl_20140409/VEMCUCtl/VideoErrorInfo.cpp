#include "StdAfx.h"
#include "VideoErrorInfo.h"

//////////////////////////////////////////////////////////////////////////
// ���ݿ�����
#pragma comment(lib,"lib\\libmySQL.lib")

//////////////////////////////////////////////////////////////////////////
CVideoErrorInfo g_VideoErrorInfo;
Recv_Buf_Queue g_VideoErrorInfoRecvBufQueue;
volatile bool g_bVideoErrorInfoWriteThreadExitFlag = false;
Recv_Buf_Node_Type g_VideoErrorInfoWritEnNode;
Recv_Buf_Node_Type g_ThreadVideoErrorInfoWriteDeNode;
//////////////////////////////////////////////////////////////////////////

CVideoErrorInfo::CVideoErrorInfo(void)
{
	m_bVideoErrorInfoInitFlag = false;
	m_hVideoErrorInfoThread = NULL;
	m_uVideoErrorInfoThreadID = 0;
	memset(m_szClientIp,0,sizeof(m_szClientIp));
	memset(m_szDBServerIp,0,sizeof(m_szDBServerIp));
	m_nDBServerPort = 0;
	memset(m_szDBName,0,sizeof(m_szDBName));
	memset(m_szDBUserName,0,sizeof(m_szDBUserName));
	memset(m_szDBUserPassword,0,sizeof(m_szDBUserPassword));
	m_pMySql = NULL;
	InitVideoErrorInfo();
}

CVideoErrorInfo::~CVideoErrorInfo(void)
{
	StopVideoErrorInfo();
	UnInitVideoErrorInfo();
	m_bVideoErrorInfoInitFlag = false;
	m_hVideoErrorInfoThread = NULL;
	m_uVideoErrorInfoThreadID = 0;
	memset(m_szDBServerIp,0,sizeof(m_szDBServerIp));
	m_nDBServerPort = 0;
	memset(m_szDBName,0,sizeof(m_szDBName));
	memset(m_szDBUserName,0,sizeof(m_szDBUserName));
	memset(m_szDBUserPassword,0,sizeof(m_szDBUserPassword));
	m_pMySql = NULL;
}

bool CVideoErrorInfo::InitVideoErrorInfo()
{
	if (m_bVideoErrorInfoInitFlag)
		return true;

	InitializeCriticalSection(&m_csVideoErrorInfoLock);

	InitRecvQueue(g_VideoErrorInfoRecvBufQueue);

	memset(&g_VideoErrorInfoWritEnNode,0,sizeof(g_VideoErrorInfoWritEnNode));
	memset(&g_ThreadVideoErrorInfoWriteDeNode,0,sizeof(g_ThreadVideoErrorInfoWriteDeNode));

	m_bVideoErrorInfoInitFlag = true;

	return true;

}

bool CVideoErrorInfo::StartVideoErrorInfo()
{
	g_bVideoErrorInfoWriteThreadExitFlag = false;

	m_hVideoErrorInfoThread = (HANDLE)_beginthreadex(NULL, 0,_VideoErrorInfoWriteThread,(void*)this, 0, &m_uVideoErrorInfoThreadID);
	if (m_hVideoErrorInfoThread == 0)
		return false;
	return true;
}

bool CVideoErrorInfo::StopVideoErrorInfo()
{
	g_bVideoErrorInfoWriteThreadExitFlag = true;

	DWORD dwResult = WaitForSingleObject(m_hVideoErrorInfoThread,6000);
	if (dwResult != WAIT_OBJECT_0)
	{
		TerminateThread(m_hVideoErrorInfoThread,1);
	}

	m_hVideoErrorInfoThread = NULL;
	m_uVideoErrorInfoThreadID = 0;

	DisConnectMySql();

	return true;
}

bool CVideoErrorInfo::UnInitVideoErrorInfo()
{
	if (!m_bVideoErrorInfoInitFlag)
		return true;

	EnterCriticalSection(&m_csVideoErrorInfoLock);

	ClearRecvQueue(g_VideoErrorInfoRecvBufQueue);

	LeaveCriticalSection(&m_csVideoErrorInfoLock);
	DeleteCriticalSection(&m_csVideoErrorInfoLock);

	m_bVideoErrorInfoInitFlag = false;

	return true;
}

bool CVideoErrorInfo::WriteVideoErrorInfo(VIDEO_ERROR_INFO *pVideoErrorInfo)
{
	if (pVideoErrorInfo == NULL)
		return false;

	g_VideoErrorInfoWritEnNode.DataLen = sizeof(VIDEO_ERROR_INFO);
	memcpy(g_VideoErrorInfoWritEnNode.Buf,pVideoErrorInfo,sizeof(VIDEO_ERROR_INFO));

	EnterCriticalSection(&m_csVideoErrorInfoLock);
	RecvEnQueue(g_VideoErrorInfoRecvBufQueue,g_VideoErrorInfoWritEnNode);
	LeaveCriticalSection(&m_csVideoErrorInfoLock);

	return true;
}

// �������ݿ�
bool CVideoErrorInfo::ConnectMySql(void)
{
	Lock();

	if (strlen(m_szDBServerIp) == 0||m_nDBServerPort == 0
		||strlen(m_szDBName) == 0||strlen(m_szDBUserName) == 0
		||strlen(m_szDBUserPassword) == 0)
	{
		Unlock();
		return false;
	}

	do 
	{
		try
		{
			if (m_pMySql != NULL)
			{
				mysql_close(m_pMySql);
				m_pMySql = NULL;
				TRACE("�Ͽ�mysql����!");
			}

			m_pMySql = mysql_init((MYSQL*)NULL);
			if (m_pMySql == NULL)
			{
				TRACE("��ʼ��mysqlʧ��!\n");
				break;
			}

			if (mysql_real_connect(m_pMySql, m_szDBServerIp, m_szDBUserName, m_szDBUserPassword, m_szDBName, m_nDBServerPort, NULL, 0))
			{
				if (mysql_select_db(m_pMySql, m_szDBName) < 0)
				{
					TRACE("�ѳɹ�����mysql, ��ѡ�����ݿ����!\n");
					mysql_close(m_pMySql);
					m_pMySql = NULL;
					break;
				}

				int nValue = 1;
				mysql_options(m_pMySql,MYSQL_OPT_RECONNECT,(char *)&nValue);

				mysql_query(m_pMySql,"SET NAMES GB2312");
				TRACE("�ѳɹ�����mysql!\n");

				Unlock();
				return true;
			}
			else
			{
				TRACE("�޷����ӵ����ݿ�: Error=%s\n",mysql_error(m_pMySql));
				mysql_close(m_pMySql);
				m_pMySql = NULL;
				TRACE("����mysqlʧ��!\n");
				break;
			}
		}
		catch(...)
		{
			m_pMySql = NULL;
		}
	} while (false);

	Unlock();
	return false;
}

// �Ͽ����ݿ�
bool CVideoErrorInfo::DisConnectMySql(void)
{
	Lock();

	try
	{
		if (m_pMySql != NULL)
		{
			mysql_close(m_pMySql);
			m_pMySql = NULL;
			TRACE("�Ͽ�mysql����!");
		}
		Unlock();
		return true;
	}
	catch(...)
	{

	}
	Unlock();
	return false;
}

bool CVideoErrorInfo::CreateVideoErrorInfoTable(char *szVideoErrorInfoTableName)
{
	char sql_buf[1024] = {0};
	int    nResult = 0;
	bool bResult = false;

	sprintf_s(sql_buf,"CREATE TABLE IF NOT EXISTS %s ("
		"id int(8) NOT NULL auto_increment,"
		"node_name char(255) NOT NULL default '',"
		"station_name char(255) NOT NULL default '',"
		"station_code char(64) NOT NULL default '',"
		"camera_name char(255) NOT NULL default '',"
		"camera_code char(64) NOT NULL default '',"
		"state int(8) NOT NULL default '0',"
		"reason int(8) NOT NULL default '0',"
		"flow int(8) NOT NULL default '0',"
		"time char(64) NOT NULL default '',"
		"client_ip char(64) NOT NULL default '',"
		"PRIMARY KEY  (id))",
		szVideoErrorInfoTableName
		);

	nResult = mysql_query(m_pMySql, sql_buf);

	bResult = ((nResult == 0)?true:false);

	return bResult;
}

bool CVideoErrorInfo::Lock()
{
	EnterCriticalSection(&m_csVideoErrorInfoLock);
	return true;
}

bool CVideoErrorInfo::Unlock()
{
	LeaveCriticalSection(&m_csVideoErrorInfoLock);
	return true;
}

//��Ա������ֵ
bool CVideoErrorInfo::SetVideoErrorInfo(char *pClientIp,char *pDBServerIp,int nDBServerPort,char *pDBName,char *pDBUserName,char *pDBUserPassword)
{
	if (pClientIp != NULL)
	{
		strcpy_s(m_szClientIp,sizeof(m_szClientIp),pClientIp);
	}

	if (pDBServerIp != NULL)
	{
		strcpy_s(m_szDBServerIp,sizeof(m_szDBServerIp),pDBServerIp);
	}

	if (nDBServerPort > 0)
	{
		m_nDBServerPort = nDBServerPort;
	}

	if (pDBName != NULL)
	{
		strcpy_s(m_szDBName,sizeof(m_szDBName),pDBName);
	}

	if (pDBUserName != NULL)
	{
		strcpy_s(m_szDBUserName,sizeof(m_szDBUserName),pDBUserName);
	}

	if (pDBUserPassword != NULL)
	{
		strcpy_s(m_szDBUserPassword,sizeof(m_szDBUserPassword),pDBUserPassword);
	}

	return true;
}

bool CVideoErrorInfo::WriteVideoErrorInfoToDB(void *pInfo,int nInfoLen)
{
	if (m_pMySql == NULL)
	{
		ConnectMySql();
	}

	if (m_pMySql == NULL)
		return false;

	if (pInfo == NULL||nInfoLen != sizeof(g_ThreadVideoErrorInfoWriteDeNode))
		return false;

	Recv_Buf_Node_Type *pNodeInfo = (Recv_Buf_Node_Type *)pInfo;

	VIDEO_ERROR_INFO *pVideoInfo  = (VIDEO_ERROR_INFO *)pNodeInfo->Buf;
	int nVideoInfo = pNodeInfo->DataLen;

	if (nVideoInfo != sizeof(VIDEO_ERROR_INFO))
		return false;

	SYSTEMTIME sysTm;

	char sql_buf[1024] = {0};
	char szTableName[255] = {0};

	memset(sql_buf,0,sizeof(sql_buf));
	memset(szTableName,0,sizeof(szTableName));

	try
	{
		::GetLocalTime(&sysTm);
		sprintf_s(szTableName,"ct_history_video_error_%04d",sysTm.wYear);
		sprintf_s(pVideoInfo->time,"%04d-%02d-%02d %02d:%02d:%02d",sysTm.wYear,sysTm.wMonth,sysTm.wDay,sysTm.wHour,sysTm.wMinute,sysTm.wSecond);

		//�����Ƿ����,�������򴴽�
		CreateVideoErrorInfoTable(szTableName);

		sprintf_s(sql_buf, "INSERT INTO %s (node_name,station_name,station_code,camera_name,camera_code,state,reason,flow,time,client_ip) "
			"VALUES ('%s','%s','%s','%s','%s',%d,%d,%d,'%s','%s')",
			szTableName,
			pVideoInfo->node_name,
			pVideoInfo->station_name,
			pVideoInfo->station_code,
			pVideoInfo->camera_name,
			pVideoInfo->camera_code,
			pVideoInfo->state,
			pVideoInfo->reason,
			pVideoInfo->flow,
			pVideoInfo->time,
			m_szClientIp);

		if (mysql_query(m_pMySql, sql_buf))
		{
			return false;
		}

		return true;
	}
	catch(...)
	{

	}

	return false;
}

bool CVideoErrorInfo::WriteVideoErrorInfoFromInfoRecvQueue()
{
	DWORD dwCount = 0;

	EnterCriticalSection(&m_csVideoErrorInfoLock);

	do 
	{
		if (RecvQueueEmpty(g_VideoErrorInfoRecvBufQueue))
		{
			break;
		}

		if(RecvDeQueue(g_VideoErrorInfoRecvBufQueue,g_ThreadVideoErrorInfoWriteDeNode) > 0)
		{
			WriteVideoErrorInfoToDB((void*)&g_ThreadVideoErrorInfoWriteDeNode,sizeof(g_ThreadVideoErrorInfoWriteDeNode));
		}

	} while (true);

	LeaveCriticalSection(&m_csVideoErrorInfoLock);

	return true;
}

unsigned __stdcall _VideoErrorInfoWriteThread(void *arg)
{
	if (arg == NULL)
		return -1;

	CVideoErrorInfo *pVideoErrorInfo = (CVideoErrorInfo *)arg;

	try
	{
		while (1)
		{
			if (g_bVideoErrorInfoWriteThreadExitFlag == true)
			{
				return 0;
			}

			pVideoErrorInfo->WriteVideoErrorInfoFromInfoRecvQueue();

			Sleep(200);
		}
	}
	catch(...)
	{

	}

	return 0;
}




