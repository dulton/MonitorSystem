#ifndef _VM_HISTORY_LOG_H_
#define _VM_HISTORY_LOG_H_
#endif

class CVMHistoryLog
{
public:
	CVMHistoryLog(void);
	virtual ~CVMHistoryLog(void);

public:
	BOOL Lock();//����
	BOOL Unlock();//����
	BOOL SetVMHistoryLogInfo(char *pLogInUserName,char *pDBServerIP,int nDBServerPort,char *pDBName,char *pDBUserName,char *pDBUserPassword);//��Ա������ֵ
	BOOL ConnectMySql(void);	// �������ݿ�
	BOOL DisConnectMySql(void);	// �Ͽ����ݿ�

	BOOL CreateLinkageHistoryLogTable(char *szHistoryLogTableName);
	BOOL CreateLinkageCameraHistoryLogTable(char *szHistoryLogTableName);

	BOOL WriteManualLinkageLog(VIDEO_LINKAGE_INFO *pVideoManualLinkageInfo);
	BOOL WriteAlarmLinkageLog(VIDEO_ALARM_LINKAGE_INFO *pVideoAlarmLinkageInfo);
	BOOL WriteStateLinkageLog(VIDEO_STATE_LINKAGE_INFO *pVideoStateLinkageInfo);
	BOOL WriteCameraControlNotifyLog(VIDEO_CAMERA_CONTROL_NOTIFY_INFO *pVideoCameraControlNotifyInfo);
	BOOL WriteWeatherWarningLinkageLog(VIDEO_WEATHER_WARNING_INFO *pVideoWeatherWarningLinkageInfo);
	BOOL WriteWeatherForecastLinkageLog(VIDEO_WEATHER_FORECAST_INFO *pVideoWeatherForecastLinkageInfo);
	
public:
	CRITICAL_SECTION m_cs;
	char  m_szLogInUserName[256];//��¼�û�
	char	 m_szDBServerIP[20];//���ݿ�������ĵ�ַ
	int     m_nDBServerPort;//�˿�
	char  m_szDBName[256];//���ݿ�����
	char  m_szDBUserName[256];//�û���
	char  m_szDBUserPassword[256];//����
	MYSQL *m_pMySql;//mysql���ݿ����
};

//////////////////////////////////////////////////////////////////////////
extern CVMHistoryLog g_VMHistoryLog;
