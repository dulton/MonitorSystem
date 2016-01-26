/*
	�ͻ�������������յ��ķ���˵���Ϣ�ļ�
*/
#ifndef _ACSCLIENTPROCESSMESSAGE_H_
#define _ACSCLIENTPROCESSMESSAGE_H_

void ProcessRecvMessage(void* arg);
void ProcessLoginServerResponse(char* buff);
void ProcessBeatHeartResponse(char* buff);
void ProcessDeviceRealData(char* buff);
int Acs_GetXmlTypeInfo(char *strXml);
int Acs_ParseLoginInfo(LOGIN_REPONSE *pLoginResponse,const char *strXML);
void ProcessSubscribeStationResponse(char *strXml);
int Acs_ParseSubscribeStationResponseInfo(SUBSCRIBE_STATION_REPONSE *pSubscribeStationResponse, char *strXml);
void ProcessPushDataResponse(char *strXml);
int Acs_ParsePushDataResponse(PUSH_DATA_RESPONSE* pPushDataResponse, char* strXml);
void ProcessSubscribeAlarmResponse(char *strXml);
int Acs_ParseSubscribeAlarmResponseInfo(COMMON_RESPONSE *pCommonResponse, char *strXml);
void ProcessHideDevResponse(char *strXml);
int Acs_ParseHideDevResponseInfo(COMMON_RESPONSE *pCommonResponse, char *strXml);
int Acs_ParsePushAlarmResponse(PUSH_ALARM_RESPONSE *pPushAlarmResponse,char *strXml);
void ProcessPushAlarmResponse(char *strXml);
int Acs_ParseLinkageRealtimeInfoResponse(LINKAGE_REALTIME_INFO_RESPONSE *pLinkageRealtimeInfoResponse, char *strXml);
void ProcessLinkageRealtimeInfoResponse(char *strXml);
#endif
