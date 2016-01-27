// ServerManage.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RvuRecv.h"
#include "UpClient.h"
#include "DataBaseExcute.h"
#include "Rvu104Recv.h"
#include "DVRPtz.h"





//////////////////////////////////////////////////////////////////////////
//COMMONTHREADPOOL g_CommnThreadPool;

//////////////////////////////////////////////////////////////////////////
//COMMONTHREADPOOL g_netopenthread;

//int g_nNetInitHandle = -1;
NETHANDLE g_ComNetHandle = -1;


NETHANDLE g_CommonRVUServerNetHandle = -1;
NETHANDLE g_CommonClientNetHandle = -1;

COMMONLIST	g_AccessDevList;
COMMONLIST	g_rvu_sendlist;
COMMONLIST	g_client_sendlist;


COMMONTHREADPOOL g_rvu_thread;

COMMONTHREADPOOL g_parse_rvu_thread ;
COMMONTHREADPOOL g_parse_rvu104_thread ;
COMMONTHREADPOOL g_parse_client_thread;

//COMMONTHREADPOOL g_send_rvu_thread ;

COMMONTHREADPOOL g_parsexmlthread ;

COMMONTHREADPOOL g_db_smthread;
COMMONTHREADPOOL g_db_nodethread;
COMMONTHREADPOOL g_db_datathread;
COMMONTHREADPOOL g_db_alarmthread;
COMMONTHREADPOOL g_db_linkthread;

COMMONTHREADPOOL g_c_datathread;
COMMONTHREADPOOL g_c_alarmthread;
COMMONTHREADPOOL g_c_linkthread;

COMMONTHREADPOOL g_sql_insert;
COMMONTHREADPOOL g_user_login;

COMMONTHREADPOOL g_c_tables;

CRITICAL_SECTION g_MaxNum_cs;
CRITICAL_SECTION g_PerNum_cs;




 _T_ASS_RVU_INFO_ g_tAssRVU[MAX_RVU_NUM_PER_STATION]; 
 int g_nAssRVUNum = 0;

_T_SQL_INFO a_tSqlInfo[10];
DBConfigParam g_DBConfigParam;



int size1=0;

// ��ʼ���б��߳�
int InitListAndThread()
{
	g_nAssRVUNum = 0;
	if (ComInitList(&g_AccessDevList, -1) == -1)
		return FALSE;
	if (ComInitList(&g_rvu_sendlist, -1) == -1)
		return FALSE;
	if (ComInitList(&g_client_sendlist, -1) == -1)
		return FALSE;
	//rvu�����߳�
	ComInitThreadPool(&g_rvu_thread,SINGLEFIFOTHREADPOOL|COPYARG,-1,1,100);
	//rvu���ݽ����߳�
	ComInitThreadPool(&g_parse_rvu_thread,SINGLEFIFOTHREADPOOL|COPYARG,-1,MAX_ONTHREAD_NUM,100);
	//rvu104Э�����ݽ����߳�
	ComInitThreadPool(&g_parse_rvu104_thread,SINGLEFIFOTHREADPOOL|COPYARG,-1,1,100);
	//�ͻ������ݽ����߳�
	ComInitThreadPool(&g_parse_client_thread,SINGLEFIFOTHREADPOOL|COPYARG,-1,1,100);
	//rvu���ݷ����߳�
//	ComInitThreadPool(&g_send_rvu_thread,SINGLEFIFOTHREADPOOL|COPYARG,-1,1,100);
	//xml���ݽ����߳�
	ComInitThreadPool(&g_parsexmlthread,SINGLEFIFOTHREADPOOL|COPYARG,-1,5,1000);

	//���ݿ�洢�߳�
	ComInitThreadPool(&g_db_smthread,SINGLEFIFOTHREADPOOL|COPYARG,-1,1,100);
//	ComInitThreadPool(&g_db_nodethread,SINGLEFIFOTHREADPOOL|COPYARG,-1,1,1000);
	ComInitThreadPool(&g_db_datathread,SINGLEFIFOTHREADPOOL|COPYARG,-1,1,100);
	ComInitThreadPool(&g_db_alarmthread,SINGLEFIFOTHREADPOOL|COPYARG,-1,1,1000);
	ComInitThreadPool(&g_db_linkthread,SINGLEFIFOTHREADPOOL|COPYARG,-1,1,1000);
	ComInitThreadPool(&g_sql_insert,SINGLEFIFOTHREADPOOL|COPYARG,-1,1,300);
	//�����߳�
	ComInitThreadPool(&g_c_tables,SINGLEFIFOTHREADPOOL|COPYARG,-1,1,10);

	//ʵʱ��Ϣ�����߳�
	ComInitThreadPool(&g_c_datathread,SINGLEFIFOTHREADPOOL|COPYARG,-1,1,10);
	//�澯��Ϣ�����߳�
	ComInitThreadPool(&g_c_alarmthread,SINGLEFIFOTHREADPOOL|COPYARG,-1,1,10);
	//������Ϣ�����߳�
	ComInitThreadPool(&g_c_linkthread,SINGLEFIFOTHREADPOOL|COPYARG,-1,1,300);

	ComInitThreadPool(&g_user_login,SINGLEFIFOTHREADPOOL|COPYARG,-1,1,10);







	ComInitNet(-1,NET_IOCP,DEFAULT_SERVER_NUM,DEFAULT_CLIENT_NUM);

	
	return TRUE;
}
void freeCommonThread()
{
	ComFreeThreadPool(&g_db_smthread,NULL);
}
/*ȥ���ַ����еĿ���*/
void eat_whitespace(char* str)
{
	char* p;
	int i;
	p=str;
	for(i=0; isspace(p[i]); i++ );
	for( ;*p ;p++)
		*p=p[i];
	p=str;
	for(i=strlen(str)-1;isspace(p[i]);i--)
		p[i]=0;
}
int ReadConfig(char* cfgfile)
{
	FILE* f;
	//char line[256];
	char *line=new char[256];
	char* p=(char*)NULL;
	char con_num[2];
	int dc_num1;

	char ip[16];
	char port[6];
	char dbname[32];
	char dbserverip[16];
	char dbserverport[6];
	char dbusername[32];
	char dbuserpassword[32];




	//�ж��Ƿ��ܴ򿪸��ļ�
	if((f = fopen(cfgfile, "r")) == (FILE*)NULL)
	{
		printf("\n �ļ���ʧ��");
		exit(1);
	}
	while(fgets(line, 256, f)!=(char*)NULL)
	{
		eat_whitespace(line);//ȥ������
		if(line[0]=='#')
			continue;
		
	
		if((p = strstr(line,"localip")))
		{ 
			p=strstr(line,"=");
			eat_whitespace(++p);
			strcpy(ip, p);
			
		}
		else if((p = strstr(line,"localport")))
		{ 
			p=strstr(line,"=");
			eat_whitespace(++p);
			strcpy(port, p);
			
		}
		else if((p = strstr(line,"dbname")))
		{ 
			p=strstr(line,"=");
			eat_whitespace(++p);
			strcpy(dbname, p);
			
		}
		else if((p = strstr(line,"dbserverip")))
		{ 
			p=strstr(line,"=");
			eat_whitespace(++p);
			strcpy(dbserverip, p);
			
		}
		else if((p = strstr(line,"dbserverport")))
		{ 
			p=strstr(line,"=");
			eat_whitespace(++p);
			strcpy(dbserverport, p);
			
		}
		else if((p = strstr(line,"dbusername")))
		{ 
			p=strstr(line,"=");
			eat_whitespace(++p);
			strcpy(dbusername, p);
			
		}
		else if((p = strstr(line,"dbuserpassword")))
		{ 
			p=strstr(line,"=");
			eat_whitespace(++p);
			strcpy(dbuserpassword, p);
			
		}
	}
	delete line;
	fclose(f);
	
	strcpy(g_DBConfigParam.LocalIP,ip);
	g_DBConfigParam.LocalPort=atoi(port);
	strcpy(g_DBConfigParam.DBName,dbname);
	strcpy(g_DBConfigParam.DBServerIP,dbserverip);
	g_DBConfigParam.DBServerPort=atoi(dbserverport);
	strcpy(g_DBConfigParam.DBUserName,dbusername);
	strcpy(g_DBConfigParam.DBUserPassword,dbuserpassword);

	if (g_DBConfigParam.LocalPort>0)
	{
		printf("\n ip is %s",g_DBConfigParam.LocalIP);
		printf("\n dbname is %s",g_DBConfigParam.DBName);
		printf("\n dbip is %s",g_DBConfigParam.DBServerIP);
		printf("\n dbname is %s",g_DBConfigParam.DBUserName);
		printf("\n dbpass is %s",g_DBConfigParam.DBUserPassword);
		return 0;
	}
	else
		return -1;
}

int main(int argc, char* argv[])
{

	
	int recvhand=0;
	int i=0;
	int result=0;
	char cfgfile[]={"config.ini"};

// ��ȡ�����ļ�
	if (ReadConfig(cfgfile)<0)
	{
		printf("\n ��ȡ�����ļ�ʧ�� ʹ��Ĭ������");
//		strcpy(g_DBConfigParam.LocalIP,"26.47.100.15");
		strcpy(g_DBConfigParam.LocalIP,"127.0.0.1");
		g_DBConfigParam.LocalPort=6001;
		strcpy(g_DBConfigParam.DBName,"test");
		strcpy(g_DBConfigParam.DBServerIP,"127.0.0.1");
		g_DBConfigParam.DBServerPort=3306;
		strcpy(g_DBConfigParam.DBUserName,"root");
		strcpy(g_DBConfigParam.DBUserPassword,"mdcs2008");
	}

// ��ʼ��
	InitListAndThread();
	result=connectDB();

// ������Ϣ��ȡ
	if (result<0)
	{
		printf("\n ���ݿ�����ʧ��");
		exit(1);
	}
	else
	{
		GetRVUInfo();
		GetDEVInfo();
//		CreateTables();
	}

	//��ʼ��DVR�豸SDK
	if (initDVRDev()==0)
	{
		printf("\nSDK��ʼ��ʧ��");
		exit(1);
	}
	else
	{
		printf("\nSDK��ʼ���ɹ�");
	}
	

	
	printf("\n testtable ID is %d,rvu number is %d",a_tSqlInfo[0].ID,g_nAssRVUNum);
	
//	ComOpenNet(g_DBConfigParam.LocalIP,0,"127.0.0.1",6002,NETCLIENT,TCP,DEFAULT_TCP_CLIENT_RECV_BUF_SIZE,DEFAULT_TCP_CLIENT_SOCKET_RECV_BUF_SIZE,DEFAULT_TCP_CLIENT_SOCKET_SEND_BUF_SIZE,10,-1,1,recv_104_parse,NULL,10,0);
	
//	ComOpenNet(g_DBConfigParam.LocalIP,0,"127.0.0.1",6003,NETCLIENT,TCP,DEFAULT_TCP_CLIENT_RECV_BUF_SIZE,DEFAULT_TCP_CLIENT_SOCKET_RECV_BUF_SIZE,DEFAULT_TCP_CLIENT_SOCKET_SEND_BUF_SIZE,10,-1,1,recv_104_parse,NULL,10,0);
// ��RVUѭ������clientͨѶ

	ComDispatchTask(&g_rvu_thread,RvuConnect,NULL,0,0);
	ComDispatchTask(&g_parse_rvu104_thread,Parse104RVURecvBuf,NULL,0,0);


// ����RVU���������߳�
//	ComDispatchTask(&g_send_rvu_thread,SendRVUBuf,NULL,0,0);
//	g_CommonRVUServerNetHandle = ComOpenNet(g_DBConfigParam.LocalIP,10012,0,0,NETSERVER,UDP,DEFAULT_TCP_CLIENT_RECV_BUF_SIZE,DEFAULT_TCP_CLIENT_SOCKET_RECV_BUF_SIZE,DEFAULT_TCP_CLIENT_SOCKET_SEND_BUF_SIZE,10,-1,512,recv_104_parse,NULL,10,1);

// ������CLIENT�����
	g_CommonClientNetHandle = ComOpenNet(g_DBConfigParam.LocalIP,g_DBConfigParam.LocalPort,0,0,NETSERVER,TCP,DEFAULT_TCP_CLIENT_RECV_BUF_SIZE,DEFAULT_TCP_CLIENT_SOCKET_RECV_BUF_SIZE,DEFAULT_TCP_CLIENT_SOCKET_SEND_BUF_SIZE,10,-1,1024,tcp_server_cb,NULL,10,1);

// ʵʱ��Ϣ�����߳�
	ComDispatchTask(&g_c_datathread,PushData,NULL,0,0);
//  �澯��Ϣ�����߳�
	ComDispatchTask(&g_c_alarmthread,PushAlarm,NULL,0,0);

//�������ݿ�洢�߳�1
	ComDispatchTask(&g_db_smthread,Save104RvuSM,NULL,0,0);
	ComDispatchTask(&g_db_datathread,Save104RvuData,NULL,0,0);

//���������߳�
//	ComDispatchTask(&g_c_tables,AutoCreat,NULL,0,0);


	while(1)
	{
		Sleep(2*1000);
//		freeCommonThread();

	
	}




	return 0;
}

