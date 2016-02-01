#include "StdAfx.h"
#include "ACSSystemClient.h"
#include "ACSSystemClientCB.h"
#include "ACSClientProcessMessage.h"

/*
�̺߳�-����
0-���ͻ��˻ص�����ʹ��
1-�������߳�
*/
COMMONTHREADPOOL g_AcsThreadPool;//����ϵͳ���̳߳�ָ��

COMMONFIFO g_AcsCommonFifo;//������Ϣ�Ķ���

CACSSystemClient::CACSSystemClient(void)
{
	m_bConnectFlag = FALSE;
	m_enumLoginStatus = LOGOUT;
}

CACSSystemClient::~CACSSystemClient(void)
{
}

/*
	��ʼ��
		1.��ȡ����ip
		2.��ʼ���ͻ���ʹ�õ��̳߳�
*/
BOOL CACSSystemClient::Init()
{
	//��ȡ����IP
	GetLocalIp(m_szLocalIp);
	m_nLocalPort = 0;

	//��ʼ���̳߳�
	int result = ComInitThreadPool(&g_AcsThreadPool,SINGLEFIFOTHREADPOOL|COPYARG,-1,THREADPOOLTHREADNUM,100);
	if (result)
		return FALSE;

	return TRUE;
}

//���ӷ�����
BOOL CACSSystemClient::ConnectServer(char *szRoutIp, int nRoutePort)
{
	if (szRoutIp != NULL)
		memcpy(m_szRouteIp, szRoutIp, 32);

	m_nRoutePort = nRoutePort;

	m_hClientTcpHandle =  ComOpenNet(m_szRouteIp, m_nLocalPort, m_szRouteIp, m_nRoutePort,NETCLIENT,TCP,ACS_RECVBUFSIZE,ACS_SOCKETRECVBUFSIZE,ACS_SOCKETSENDBUFSIZE,10,-1,10,ACS_TcpClientRecvCB,NULL,0,0);
	//m_hClientTcpHandle =  ComOpenNet(m_szLocalIp, m_nLocalPort, m_szRouteIp, m_nRoutePort,NETCLIENT,TCP,ACS_RECVBUFSIZE,ACS_SOCKETRECVBUFSIZE,ACS_SOCKETSENDBUFSIZE,10,-1,10,ACS_TcpClientRecvCB,NULL,0,0);

	if (!m_hClientTcpHandle)
	{
		m_bConnectFlag = FALSE;
		return FALSE;
	}

	m_bConnectFlag = TRUE;

	//���ӳɹ���,����һ���̴߳������˷���������Ϣ
	//ComDispatchTask(&g_AcsThreadPool,ProcessRecvMessage,NULL,0,0);

	return TRUE;
}

void CACSSystemClient::GetLocalIp( char *szLocalIp )
{
	char szHostName[MAX_PATH + 1];
	gethostname(szHostName, MAX_PATH);//���������
	hostent *hn;
	hn = gethostbyname(szHostName);//���ݱ����������õ�����ip
	memcpy(szLocalIp, inet_ntoa(*(in_addr*)hn->h_addr_list[0]), 32);//��ipת�����ַ�����ʽ
}

char * CACSSystemClient::GetLocalIp()
{
	return m_szLocalIp;
}

void CACSSystemClient::SetLocalIp( char *szLocalIp )
{
	if (szLocalIp != NULL)
		sprintf_s(m_szLocalIp, szLocalIp, 32);
}

int CACSSystemClient::GetLocalPort()
{
	return m_nLocalPort;
}

void CACSSystemClient::SetLocalPort(int nLocalPort)
{
	m_nLocalPort = nLocalPort;
}

char * CACSSystemClient::GetRouteIp()
{
	return m_szRouteIp;
}

void CACSSystemClient::SetRouteIp( char *szRouteIp )
{
	if (szRouteIp != NULL)
		sprintf_s(m_szRouteIp, szRouteIp, 32);
}

int CACSSystemClient::GetRoutePort()
{
	return m_nRoutePort;
}

void CACSSystemClient::SetRoutePort(int nRoutePort)
{
	m_nRoutePort = nRoutePort;
}

//��½������
BOOL CACSSystemClient::SendLoginServerRequest(char *username,char *password,int nType)
{
	if (username == NULL||password == NULL||nType != 0)
		return FALSE;

	char send_buf[1024] ={0};

	//ƴ�ӵ�½����
	sprintf_s(send_buf,"<?xml version=1.0 encoding=GB2312?> <HTTP_XML EventType=Request_Login>"
		"<Item UserName='%s' Password='%s' Type='%d' /> </HTTP_XML>",username, password, nType);

	//���͵�½����
	int ret = ComSendNet(m_hClientTcpHandle,0,0,0,0,0,0,send_buf,sizeof(send_buf),0);
	if (ret)
		return FALSE;

	DEBUG_LOG("send ������˷��͵�½�������������ݣ�%s", send_buf);
}

BOOL CACSSystemClient::SendSubscribeAlarmRequest(int nUserId, int nStationId)
{
	char send_buf[1024] ={0};

	//ƴ�Ӹ澯��������
	sprintf_s(send_buf,"<?xml version=1.0 encoding=GB2312?> <HTTP_XML EventType=Request_Subscribe_Alarm>"
		"<Item UserID='%d' StationID='%d' Type='%d' /></HTTP_XML>",nUserId, nStationId, 1);

	//���͵�½����
	int ret = ComSendNet(m_hClientTcpHandle,0,0,0,0,0,0,send_buf,sizeof(send_buf),0);
	if (ret)
		return FALSE;

	DEBUG_LOG("send ������˷��͸澯�����������ݣ�%s", send_buf);
}

BOOL CACSSystemClient::SendCancelSubscribeAlarmRequest(int nUserId, int nStationId)
{
	char send_buf[1024] ={0};

	//ƴ�Ӹ澯��������
	sprintf_s(send_buf,"<?xml version=1.0 encoding=GB2312?> <HTTP_XML EventType=Request_Subscribe_Alarm>"
		"<Item UserID='%d' StationID='%d' Type='%d' /></HTTP_XML>",nUserId, nStationId, 0);

	//���͵�½����
	int ret = ComSendNet(m_hClientTcpHandle,0,0,0,0,0,0,send_buf,sizeof(send_buf),0);
	if (ret)
		return FALSE;

	DEBUG_LOG("send ������˷���ȡ���澯�����������ݣ�%s", send_buf);
}

//֪ͨ��������ĳ���豸
BOOL CACSSystemClient::SendHideDevRequest(int nUserId,int nDevId,int nAction)
{
	if (m_enumLoginStatus != LOGIN)
		return FALSE;

	if (nDevId <= 0 || nUserId <= 0)
		return FALSE;

	char send_buf[1024] ={0};

	//ƴ���豸��������
	sprintf_s(send_buf,"<?xml version=1.0 encoding=GB2312?> <HTTP_XML EventType=Request_Hide_Dev>"
		"<Item UserID='%d' DevID='%d' Hide='%d' /> </HTTP_XML>",nUserId, nDevId, nAction);

	//�����豸��������
	int ret = ComSendNet(m_hClientTcpHandle,0,0,0,0,0,0,send_buf,sizeof(send_buf),0);
	if (ret)
		return FALSE;

	DEBUG_LOG("send ������˷��������������ݣ�%s", send_buf);

}