#include "stdafx.h"
#include "tinyxml\tinyxml.h"
#include "ACSClientProcessMessage.h"
#include "ACSSystemClient.h"
#include "VEMCUCtlDlg.h"

extern CACSSystemClient *g_pACSClient;

void ProcessRecvMessage(void* arg)
{
	char *strXml = (char*)arg;
	if (strXml == NULL||strlen(strXml) == 0||strlen(strXml) > 64*1024)
		return;

	DEBUG_LOG("recevive ���յ�����˴������ı������ݣ�%s", strXml);

	//��ȡ��������
	int nType = Acs_GetXmlTypeInfo(strXml);
	if (!nType)
		return;

	//������Ϣ
	switch(nType)
	{
	case ACS_LOGIN_SERVER_RESPONSE:
		ProcessLoginServerResponse(strXml);
		break;
	case ACS_BEATHEART_RESPONSE:
		ProcessBeatHeartResponse(strXml);
		break;
	case ACS_SUBSCRIBE_STATION_RESPONSE:
		ProcessSubscribeStationResponse(strXml);
		break;
	case ACS_PUSH_DATA_RESPONSE:
		ProcessPushDataResponse(strXml);
		break;
	case ACS_SUBSCRIBE_ALARM_RESPONSE:
		ProcessSubscribeAlarmResponse(strXml);
		break;
	case ACS_Hide_DEV_RESPONSE:
		ProcessHideDevResponse(strXml);
		break;
	case ACS_PUSH_ALARM_RESPONSE:
		ProcessPushAlarmResponse(strXml);
		break;
	case ACS_LINKAGE_REALTIME_INFO_RESPONSE:
		ProcessLinkageRealtimeInfoResponse(strXml);
		break;
	default:
		break;
	}
}

int Acs_ParseLinkageRealtimeInfoResponse(LINKAGE_REALTIME_INFO_RESPONSE *pLinkageRealtimeInfoResponse, char *strXml)
{
	TiXmlDocument	resXML;
	TiXmlElement	*pElement = NULL;
	TiXmlElement *pSubList = NULL;
	TiXmlElement *pItem = NULL;
	const char		*pResult = NULL;

	char szGB2312Info[1024] = {0};
	int    nGB2312InfoLen = 0;

	if (pLinkageRealtimeInfoResponse == NULL||strXml == NULL)
		return -1;

	try
	{
		memset(pLinkageRealtimeInfoResponse,0,sizeof(pLinkageRealtimeInfoResponse)*ACS_LINKAGE_REALTIME_INFO_COUNT);

		resXML.Parse(strXml);
		pElement = resXML.FirstChildElement("HTTP_XML");
		if (pElement == NULL)
			return -1;

		pResult = pElement->Attribute("EventType");
		if (pResult == NULL)
			return -1;

		if (strcmp(pResult, "Response_LinkageAction") != 0) 
			return -1;

		int nCount = 0;
		pSubList = pElement->FirstChildElement("Item");
		while(pSubList)
		{
			//����
			pResult = pSubList->Attribute("DevID");
			if (pResult != NULL)
				pLinkageRealtimeInfoResponse[nCount].nDevID = atoi(pResult);

			pResult = pSubList->Attribute("CameraCode");
			if (pResult != NULL)
				sprintf_s(pLinkageRealtimeInfoResponse[nCount].szCamreaCode, 32, pResult);

			pResult = pSubList->Attribute("PresetNum");
			if (pResult != NULL)
				pLinkageRealtimeInfoResponse[nCount].nPresetNum = atoi(pResult);

			pResult = pSubList->Attribute("Time");
			if (pResult != NULL)
				sprintf_s(pLinkageRealtimeInfoResponse[nCount].szStartTime, 32, pResult);

			nCount++;

			//����һ�����
			pSubList = pSubList->NextSiblingElement("Item");
		}

		return nCount;
	}
	catch (...)
	{

	}

	return -1;
}

void ProcessLinkageRealtimeInfoResponse(char *strXml)
{
	LINKAGE_REALTIME_INFO_RESPONSE tLinkageRealtimeInfoResponse[ACS_LINKAGE_REALTIME_INFO_COUNT];
	memset(&tLinkageRealtimeInfoResponse,0,sizeof(LINKAGE_REALTIME_INFO_RESPONSE)*ACS_LINKAGE_REALTIME_INFO_COUNT);
	int nLinkageRealtimeInfoCount = 0;

	//��������
	nLinkageRealtimeInfoCount = Acs_ParseLinkageRealtimeInfoResponse(tLinkageRealtimeInfoResponse,strXml);

	if (nLinkageRealtimeInfoCount>0)
	{
		//����澯��������
		g_pMainDlg->m_pDlgAlarmInfo->ProcessLinkageRealtimeInfo((char*)tLinkageRealtimeInfoResponse, nLinkageRealtimeInfoCount);
	}
}

//����澯����
void ProcessPushAlarmResponse(char *strXml)
{
	PUSH_ALARM_RESPONSE tPushAlarmResponse[ACS_PUSH_ALARM_COUNT];
	memset(&tPushAlarmResponse,0,sizeof(PUSH_ALARM_RESPONSE)*ACS_PUSH_ALARM_COUNT);
	int nPushAlarmCount = 0;

	//��������
	nPushAlarmCount = Acs_ParsePushAlarmResponse(tPushAlarmResponse,strXml);

	if (nPushAlarmCount>0)
	{
		//����澯��������
		g_pMainDlg->m_pDlgAlarmInfo->ProcessPushAlarmData((char*)tPushAlarmResponse, nPushAlarmCount);
	}
}

int Acs_ParsePushAlarmResponse(PUSH_ALARM_RESPONSE *pPushAlarmResponse,char *strXml)
{
	TiXmlDocument	resXML;
	TiXmlElement	*pElement = NULL;
	TiXmlElement *pSubList = NULL;
	TiXmlElement *pItem = NULL;
	const char		*pResult = NULL;

	char szGB2312Info[1024] = {0};
	int    nGB2312InfoLen = 0;

	if (pPushAlarmResponse == NULL||strXml == NULL)
		return -1;

	try
	{
		memset(pPushAlarmResponse,0,sizeof(pPushAlarmResponse)*ACS_PUSH_ALARM_COUNT);

		resXML.Parse(strXml);
		pElement = resXML.FirstChildElement("HTTP_XML");
		if (pElement == NULL)
			return -1;

		pResult = pElement->Attribute("EventType");
		if (pResult == NULL)
			return -1;

		if (strcmp(pResult, "Response_Push_Alarm") != 0) 
			return -1;

		int nCount = 0;
		pSubList = pElement->FirstChildElement("Item");
		while(pSubList)
		{
			//����
			pResult = pSubList->Attribute("DevID");
			if (pResult != NULL)
				pPushAlarmResponse[nCount].nDevId = atoi(pResult);

			pResult = pSubList->Attribute("StationID");
			if (pResult != NULL)
				pPushAlarmResponse[nCount].nStationId = atoi(pResult);

			pResult = pSubList->Attribute("AlarmType");
			if (pResult != NULL)
				pPushAlarmResponse[nCount].nAlarmType = atoi(pResult);

			pResult = pSubList->Attribute("AlarmStartTime");
			if (pResult != NULL)
				sprintf_s(pPushAlarmResponse[nCount].szAlarmStartTime, 64, pResult);

			pResult = pSubList->Attribute("PriorLevel");
			if (pResult != NULL)
				pPushAlarmResponse[nCount].nPriorLevel = atoi(pResult);

			nCount++;

			//����һ�����
			pSubList = pSubList->NextSiblingElement("Item");
		}

		return nCount;
	}
	catch (...)
	{

	}

	return -1;
}

void ProcessHideDevResponse(char *strXml)
{
	COMMON_RESPONSE tCommonResponse;
	memset(&tCommonResponse, 0, sizeof(COMMON_RESPONSE));
	Acs_ParseSubscribeAlarmResponseInfo(&tCommonResponse, strXml);

	//������Ϣ
	if (tCommonResponse.nResult == 0)
	{
		//�豸���γɹ�
		SetEvent(g_CommonEvent);
	}
	else
	{
		//�豸����ʧ��
	}
}

int Acs_ParseHideDevResponseInfo(COMMON_RESPONSE *pCommonResponse, char *strXml)
{
	TiXmlDocument	resXML;
	TiXmlElement	*pElement = NULL;
	TiXmlElement *pSubList = NULL;
	TiXmlElement *pItem = NULL;
	const char		*pResult = NULL;

	char szGB2312Info[1024] = {0};
	int    nGB2312InfoLen = 0;

	if (pCommonResponse == NULL||strXml == NULL)
		return -1;

	try
	{
		memset(pCommonResponse,0,sizeof(COMMON_RESPONSE));

		resXML.Parse(strXml);
		pElement = resXML.FirstChildElement("HTTP_XML");
		if (pElement == NULL)
			return -1;

		pResult = pElement->Attribute("EventType");
		if (pResult == NULL)
			return -1;

		if (strcmp(pResult, "Request_Subscribe_Station") != 0) 
			return -1;

		pSubList = pElement->FirstChildElement("Item");
		if (pSubList == NULL)
			return -1;

		pResult = pSubList->Attribute("Result");
		if (pResult != NULL)
			pCommonResponse->nResult = atoi(pResult);

		return 0;
	}
	catch (...)
	{

	}

	return -1;
}

//�����¼�
int Acs_GetXmlTypeInfo(char *strXml)
{
	TiXmlDocument	resXML;
	TiXmlElement	*pElement = NULL;
	const char		*pResult = NULL;
	int nResult = 0;

	try
	{
		resXML.Parse(strXml);
		pElement = resXML.FirstChildElement("HTTP_XML");
		if (pElement == NULL)
			return nResult;

		pResult = pElement->Attribute("EventType");
		if (pResult == NULL)
			return nResult;

		if(strcmp(pResult, "Response_Login") == 0) 
			nResult = ACS_LOGIN_SERVER_RESPONSE;
		else if(strcmp(pResult, "Response_Subscribe_Station") == 0)
			nResult = ACS_SUBSCRIBE_STATION_RESPONSE;
		else if(strcmp(pResult, "Response_Subscribe_Alarm") == 0)
			nResult = ACS_SUBSCRIBE_ALARM_RESPONSE;
		else if(strcmp(pResult, "Response_Hide_Dev") == 0) 
			nResult = ACS_Hide_DEV_RESPONSE;
		else if(strcmp(pResult, "Response_Push_Data") == 0)
			nResult = ACS_PUSH_DATA_RESPONSE;
		else if (strcmp(pResult, "Response_Push_Alarm") == 0)
			nResult = ACS_PUSH_ALARM_RESPONSE;
		else if (strcmp(pResult, "Response_LinkageAction") == 0)
			nResult = ACS_LINKAGE_REALTIME_INFO_RESPONSE;

		return nResult;
	}
	catch(...)
	{

	}

	return nResult;
}

void ProcessPushDataResponse(char *strXml)
{
	PUSH_DATA_RESPONSE tPushDataResponse[ACS_DEVICE_REALDATA_COUNT];
	memset(&tPushDataResponse,0,sizeof(PUSH_DATA_RESPONSE)*ACS_DEVICE_REALDATA_COUNT);
	int nPushDataCount = 0;

	//��������
	nPushDataCount = Acs_ParsePushDataResponse(tPushDataResponse,strXml);

	if (nPushDataCount>0)
	{
		//����dll�ӿ���������Щ����
		ACSSystem_ProcessSMRealData((char*)tPushDataResponse, nPushDataCount);

		//ˢ�µ��ӵ�ͼ�豸״̬
		ElecMap_RefreshYXDevState((char*)tPushDataResponse, nPushDataCount);
	}
}

int Acs_ParsePushDataResponse(PUSH_DATA_RESPONSE* pPushDataResponse, char* strXml)
{
	TiXmlDocument	resXML;
	TiXmlElement	*pElement = NULL;
	TiXmlElement *pSubList = NULL;
	TiXmlElement *pItem = NULL;
	const char		*pResult = NULL;

	char szGB2312Info[1024] = {0};
	int    nGB2312InfoLen = 0;

	if (pPushDataResponse == NULL||strXml == NULL)
		return -1;

	try
	{
		memset(pPushDataResponse,0,sizeof(pPushDataResponse)*ACS_DEVICE_REALDATA_COUNT);

		resXML.Parse(strXml);
		pElement = resXML.FirstChildElement("HTTP_XML");
		if (pElement == NULL)
			return -1;

		pResult = pElement->Attribute("EventType");
		if (pResult == NULL)
			return -1;

		if (strcmp(pResult, "Response_Push_Data") != 0) 
			return -1;

		int nCount = 0;
		pSubList = pElement->FirstChildElement("Item");
		while(pSubList)
		{
			//����
			pResult = pSubList->Attribute("RvuID");
			if (pResult != NULL)
				pPushDataResponse[nCount].nRvuId = atoi(pResult);

			pResult = pSubList->Attribute("SmID");
			if (pResult != NULL)
				pPushDataResponse[nCount].nSmId = atoi(pResult);

			pResult = pSubList->Attribute("NodeID");
			if (pResult != NULL)
				pPushDataResponse[nCount].nNodeId = atoi(pResult);

			pResult = pSubList->Attribute("Value");
			if (pResult != NULL)
				pPushDataResponse[nCount].fValue = atof(pResult);

			pResult = pSubList->Attribute("Type");
			if (pResult != NULL)
				pPushDataResponse[nCount].nType = atoi(pResult);

			pResult = pSubList->Attribute("Status");
			if (pResult != NULL)
				pPushDataResponse[nCount].nStatus = atoi(pResult);

			nCount++;
			
			//����һ�����
			pSubList = pSubList->NextSiblingElement("Item");
		}

		return nCount;
	}
	catch (...)
	{

	}

	return -1;	
}

void ProcessSubscribeStationResponse(char *strXml)
{
	//��������buff
	SUBSCRIBE_STATION_REPONSE tSubscribeStationResponse;
	memset(&tSubscribeStationResponse,0,sizeof(SUBSCRIBE_STATION_REPONSE));
	Acs_ParseSubscribeStationResponseInfo(&tSubscribeStationResponse, strXml);

	//������Ϣ
	if (tSubscribeStationResponse.nResult == 0)
	{
		//���ĳɹ�
	}
	else
	{
		//����ʧ��
	}
}

//����澯����
void ProcessSubscribeAlarmResponse(char *strXml)
{
	COMMON_RESPONSE tCommonResponse;
	memset(&tCommonResponse, 0, sizeof(COMMON_RESPONSE));
	Acs_ParseSubscribeAlarmResponseInfo(&tCommonResponse, strXml);

	//������Ϣ
	if (tCommonResponse.nResult == 0)
	{
		//�澯���ĳɹ�
		SetEvent(g_CommonEvent);
	}
	else
	{
		//�澯����ʧ��
	}
}	

int Acs_ParseSubscribeAlarmResponseInfo(COMMON_RESPONSE *pCommonResponse, char *strXml)
{
	TiXmlDocument	resXML;
	TiXmlElement	*pElement = NULL;
	TiXmlElement *pSubList = NULL;
	TiXmlElement *pItem = NULL;
	const char		*pResult = NULL;

	char szGB2312Info[1024] = {0};
	int    nGB2312InfoLen = 0;

	if (pCommonResponse == NULL||strXml == NULL)
		return -1;

	try
	{
		memset(pCommonResponse,0,sizeof(COMMON_RESPONSE));

		resXML.Parse(strXml);
		pElement = resXML.FirstChildElement("HTTP_XML");
		if (pElement == NULL)
			return -1;

		pResult = pElement->Attribute("EventType");
		if (pResult == NULL)
			return -1;

		if (strcmp(pResult, "Request_Subscribe_Station") != 0) 
			return -1;

		pSubList = pElement->FirstChildElement("Item");
		if (pSubList == NULL)
			return -1;

		pResult = pSubList->Attribute("Result");
		if (pResult != NULL)
			pCommonResponse->nResult = atoi(pResult);

		return 0;
	}
	catch (...)
	{

	}

	return -1;
}

//�������վ������Ϣ
int Acs_ParseSubscribeStationResponseInfo(SUBSCRIBE_STATION_REPONSE *pSubscribeStationResponse, char *strXml)
{
	TiXmlDocument	resXML;
	TiXmlElement	*pElement = NULL;
	TiXmlElement *pSubList = NULL;
	TiXmlElement *pItem = NULL;
	const char		*pResult = NULL;

	char szGB2312Info[1024] = {0};
	int    nGB2312InfoLen = 0;

	if (pSubscribeStationResponse == NULL||strXml == NULL)
		return -1;

	try
	{
		memset(pSubscribeStationResponse,0,sizeof(pSubscribeStationResponse));

		resXML.Parse(strXml);
		pElement = resXML.FirstChildElement("HTTP_XML");
		if (pElement == NULL)
			return -1;

		pResult = pElement->Attribute("EventType");
		if (pResult == NULL)
			return -1;

		if (strcmp(pResult, "Request_Subscribe_Station") != 0) 
			return -1;

		pSubList = pElement->FirstChildElement("Item");
		if (pSubList == NULL)
			return -1;

		pResult = pSubList->Attribute("Result");
		if (pResult != NULL)
			pSubscribeStationResponse->nResult = atoi(pResult);

		return 0;
	}
	catch (...)
	{

	}

	return -1;	
}

//��½���󷵻���Ϣ����
void ProcessLoginServerResponse(char* buff)
{
	//��������buff
	LOGIN_REPONSE tLoginResponse;
	memset(&tLoginResponse,0,sizeof(LOGIN_REPONSE));
	Acs_ParseLoginInfo(&tLoginResponse,buff);

	//������Ϣ
	if (tLoginResponse.nResult == 0)
	{
		g_pACSClient->m_enumLoginStatus = LOGIN;
	}
	else
	{
		g_pACSClient->m_enumLoginStatus = LOGOUT;
	}
}

//������¼
int Acs_ParseLoginInfo(LOGIN_REPONSE *pLoginResponse,const char *strXML)
{
	TiXmlDocument	resXML;
	TiXmlElement	*pElement = NULL;
	TiXmlElement *pSubList = NULL;
	TiXmlElement *pItem = NULL;
	const char		*pResult = NULL;

	char szGB2312Info[1024] = {0};
	int    nGB2312InfoLen = 0;

	if (pLoginResponse == NULL||strXML == NULL)
		return -1;

	try
	{
		memset(pLoginResponse,0,sizeof(pLoginResponse));

		resXML.Parse(strXML);
		pElement = resXML.FirstChildElement("HTTP_XML");
		if (pElement == NULL)
			return -1;

		pResult = pElement->Attribute("EventType");
		if (pResult == NULL)
			return -1;

		if (strcmp(pResult, "Response_Login") != 0) 
			return -1;

		pSubList = pElement->FirstChildElement("Item");
		if (pSubList == NULL)
			return -1;

		pResult = pSubList->Attribute("Result");
		if (pResult != NULL)
			pLoginResponse->nResult = atoi(pResult);

		return 0;
	}
	catch (...)
	{

	}

	return -1;	
}

void ProcessBeatHeartResponse(char* buff)
{
	//������˷���������Ӧ
	ComSendNet(g_pACSClient->m_hClientTcpHandle, g_AcsServerIp, g_nAcsServerPort,0,0,0,0,"������Ϣ",0,0);
}