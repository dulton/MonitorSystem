/*
	����ϵͳ�ͻ�����
*/
#pragma once

/*
�̺߳�-����
0-���ͻ��˻ص�����ʹ��
1-�����߳�
*/
#define THREADPOOLTHREADNUM 10  //�̳߳��е��߳�����

//�ͻ�������״̬
enum LOGIN_STATUS
{
	LOGIN=0,//��½
	LOGOUT=1,//�˳�
	LOGGING=2//���ڵ�½
};

class CACSSystemClient
{
public:
	CACSSystemClient(void);
	~CACSSystemClient(void);
public:
	int m_hClientTcpHandle;//�ͻ��˾��
	int m_nConnectServer;//�Ƿ��½���˷�������0��ʾ�ѵ�½��1��ʾ���ڵ�½��-1��ʾ�˳�
	BOOL m_bConnectFlag;//�Ƿ����ӵ�������
	LOGIN_STATUS m_enumLoginStatus;//��½״̬

private:
	char m_szLocalIp[32];
	int m_nLocalPort;
	char m_szRouteIp[32];
	int m_nRoutePort;

public:
	//��ȡ�����ñ���IP��ַ
	char *GetLocalIp();
	void SetLocalIp(char *szLocalIp);
	//��ȡ�����ñ��ض˿�
	int GetLocalPort();
	void SetLocalPort(int nLocalPort);
	//��ȡ������Զ��IP��ַ
	char *GetRouteIp();
	void SetRouteIp(char *szRouteIp);	
	//��ȡ������Զ�̶˿�
	int GetRoutePort();
	void SetRoutePort(int nRoutePort);
private:
	//��ȡ����IP��ַ
	void GetLocalIp(char *szLocalIp);
public:
	//�ͻ��˳�ʼ��
	BOOL Init();
	//����tcpserver
	BOOL ConnectServer(char *szRoutIp, int nRoutePort);
	//��½����������
	BOOL SendLoginServerRequest(char *username,char *password,int nType);
	//�����豸��������
	BOOL SendHideDevRequest(int nUserId,int nDevId,int nAction);
	//���͸澯��������
	BOOL SendSubscribeAlarmRequest(int nUserId, int nStationId);
	BOOL SendCancelSubscribeAlarmRequest(int nUserId, int nStationId);
};

extern COMMONTHREADPOOL g_AcsThreadPool;

