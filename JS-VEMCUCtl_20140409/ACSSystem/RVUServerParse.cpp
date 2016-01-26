#include "stdafx.h"
#include "RVUServerParse.h"
#include "ACSSystemDlg.h"

void ParseRVUResponseSetPointAck(unsigned char* buff,int size)
{
	int nResult = buff[0];

	if (nResult == 1)
	{
		TRACE("----��̨���Ƴɹ�----\n");
	}
	else
	{
		TRACE("----��̨����ʧ��----\n");
	}

	TRACE("---ParseRVUResponseSetPointAck:size=%d----\n\n",size);

	for (int i=4; i<size; i++)
	{
		TRACE("%x",buff[i]);
	}
}

void ParseRVUResponseSetNodes(unsigned char* buff,int size)
{
	TRACE("-----size=%d------\n\n",size);

	int i=0;
	int total_len = 0;
	int index = 0;
	int reserved_index = 0;
	int type = 0;
	int count = 0;
	int data_index = 0;
	int first_len = 0;
	int data_len = 0;
	//char data[512*1024]={0x0};
	char * pData = NULL;
	pData = new char[size];
	memset(pData,0,sizeof(char)*size);

	TNODE* pTNode  = NULL;
	while (i<=size)
	{
		if (buff[i]==0x78 && buff[i+1]==0x87)
		{
			index = buff[i+4];
			reserved_index = buff[i+5];

			if (index == 1)
			{
				total_len = (buff[i+10] | (buff[i+11]<<8) | (buff[i+12]<<16) | (buff[i+13]<<24));
				type = buff[i+22] | (buff[i+23]<<8) | (buff[i+24]<<16) | (buff[i+25]<<24);
				count = buff[i+26] | (buff[i+27]<<8) | (buff[i+28]<<16) | (buff[i+29]<<24);
				if (count == -2)
				{
					TRACE("----�鲻����ӦID��------\n");
					return ;
				}
				else if (count == -1)
				{
					TRACE("----�������ݹ���------\n");
				}

				//first_len = total_len%MAX_FRAME_LEN;
				first_len = size%MAX_FRAME_LEN;
				if (first_len == 0)
				{
					first_len = MAX_FRAME_LEN;
				}

				data_len = first_len - SET_SM_ACK_DATA_OFFSET;

				if (reserved_index == 0)
				{
					pTNode = new TNODE[count];
					memset(pTNode,0,sizeof(TNODE)*count);
					memcpy(pTNode,&buff[i+SET_SM_ACK_DATA_OFFSET],sizeof(TNODE)*count);
					break;
				}
				else
				{
					memcpy(pData,&buff[i+SET_SM_ACK_DATA_OFFSET],data_len);
					for (int j=0; j<reserved_index; j++)
					{
						memcpy(/*&data[data_len+j*(MAX_FRAME_LEN-8)]*/pData+data_len+j*(MAX_FRAME_LEN-8),&buff[i+first_len+j*MAX_FRAME_LEN+8],MAX_FRAME_LEN-8);
					}

					pTNode = new TNODE[count];
					memset(pTNode,0,sizeof(TNODE)*count);
					memcpy(pTNode,pData,sizeof(TNODE)*count);
				}
			}
			break;
		}

		i++;
	}
    
	memset(&g_t_TNODE,0,sizeof(TNODE)*MAX_NODE_NUM_PER_STATION);

	g_nTNODE = count;
	memcpy(&g_t_TNODE,pTNode,sizeof(TNODE)*count);

	CTime time = CTime::GetCurrentTime();
	CString strInfo,strTime;
	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d COMMAND->GET_NODES Cnt:%d",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond(),count);

	if (pTNode != NULL)
	{
		delete pTNode;
		pTNode = NULL;
	}

	if (pData != NULL)
	{
		delete pData;
		pData = NULL;
	}
}

void ParseRVUResponseSetSM(unsigned char* buff,int size)
{
	TRACE("-----size=%d------\n\n",size);

	int i=0;
	int total_len = 0;
	int index = 0;
	int reserved_index = 0;
	int type = 0;
	int count = 0;
	int data_index = 0;
	int first_len = 0;
	int data_len = 0;
	//char data[64*1024]={0x0};

	char * pData = NULL;
	pData = new char[size];
	memset(pData,0,sizeof(char)*size);
	TSM* pTSM  = NULL;
	while (i<=size)
	{
		if (buff[i]==0x78 && buff[i+1]==0x87)
		{
			index = buff[i+4];
			reserved_index = buff[i+5];

			if (index == 1)
			{
				total_len = (buff[i+10] | (buff[i+11]<<8) | (buff[i+12]<<16) | (buff[i+13]<<24));
				type = buff[i+22] | (buff[i+23]<<8) | (buff[i+24]<<16) | (buff[i+25]<<24);
				count = buff[i+26] | (buff[i+27]<<8) | (buff[i+28]<<16) | (buff[i+29]<<24);
				if (count == -2)
				{
					TRACE("----�鲻����ӦID��------\n");
					return ;
				}
				else if (count == -1)
				{
					TRACE("----�������ݹ���------\n");
				}

				first_len = size%MAX_FRAME_LEN;
				if (first_len == 0)
				{
					first_len = MAX_FRAME_LEN;
				}

				data_len = first_len - SET_SM_ACK_DATA_OFFSET;

				if (reserved_index == 0)
				{
					pTSM = new TSM[count];
					memset(pTSM,0,sizeof(TSM)*count);
					memcpy(pTSM,&buff[i+SET_SM_ACK_DATA_OFFSET],sizeof(TSM)*count);
					break;
				}
				else
				{
					memcpy(/*&data*/pData,&buff[i+SET_SM_ACK_DATA_OFFSET],data_len);
					for (int j=0; j<reserved_index; j++)
					{
						memcpy(/*&data[data_len+j*(MAX_FRAME_LEN-8)]*/pData+data_len+j*(MAX_FRAME_LEN-8),&buff[i+first_len+j*MAX_FRAME_LEN+8],MAX_FRAME_LEN-8);
					}

					pTSM = new TSM[count];
					memset(pTSM,0,sizeof(TSM)*count);
					memcpy(pTSM,pData,sizeof(TSM)*count);
				}
			}
			break;
		}

		i++;
	}

	memset(&g_t_TSM,0,sizeof(TSM)*MAX_SM_NUM_PER_STATION);

	g_nTSM = count;
	memcpy(&g_t_TSM,pTSM,sizeof(TSM)*count);
	
	if (pTSM != NULL)
	{
		delete[] pTSM;
		pTSM = NULL;
	}

	if (pData != NULL)
	{
		delete pData;
		pData = NULL;
	}

	SetEvent(g_hGetNodeEvent);
}

void ParseRVUSendRealtimeAlarm(int handle,unsigned char* buff,int size)
{
	TRACE("-----size=%d------\n\n",size);

	int i=0,k=0;
	int total_len = 0;
	int index = 0;
	int reserved_index = 0;
	int type = 0;
	int count = 0;
	int data_index = 0;
	int first_len = 0;
	int data_len = 0;
	//char data[64*1024]={0x0};

	char * pData = NULL;
	pData = new char[size];
	memset(pData,0,sizeof(char)*size);
	TALARM* pTAlarm  = NULL;
	while (i<=size)
	{
		if (buff[i]==0x78 && buff[i+1]==0x87)
		{
			index = buff[i+4];
			reserved_index = buff[i+5];

			if (index == 1)
			{
				total_len = (buff[i+10] | (buff[i+11]<<8) | (buff[i+12]<<16) | (buff[i+13]<<24));
				type = buff[i+22] | (buff[i+23]<<8) | (buff[i+24]<<16) | (buff[i+25]<<24);
				count = buff[i+26] | (buff[i+27]<<8) | (buff[i+28]<<16) | (buff[i+29]<<24);
				if (count == -2)
				{
					TRACE("----�鲻����ӦID��------\n");
					return ;
				}
				else if (count == -1)
				{
					TRACE("----�������ݹ���------\n");
				}

				first_len = size%MAX_FRAME_LEN;
				if (first_len == 0)
				{
					first_len = MAX_FRAME_LEN;
				}

				data_len = first_len - SET_SM_ACK_DATA_OFFSET;

				if (reserved_index == 0)
				{
					pTAlarm = new TALARM[count];
					memset(pTAlarm,0,sizeof(TALARM)*count);
					memcpy(pTAlarm,&buff[i+SET_SM_ACK_DATA_OFFSET],sizeof(TALARM)*count);
					break;
				}
				else
				{
					memcpy(/*&data*/pData,&buff[i+SET_SM_ACK_DATA_OFFSET],data_len);
					for (int j=0; j<reserved_index; j++)
					{
						memcpy(/*&data[data_len+j*(MAX_FRAME_LEN-8)]*/pData+data_len+j*(MAX_FRAME_LEN-8),&buff[i+first_len+j*MAX_FRAME_LEN+8],MAX_FRAME_LEN-8);
					}

					pTAlarm = new TALARM[count];
					memset(pTAlarm,0,sizeof(TALARM)*count);
					memcpy(pTAlarm,pData,sizeof(TALARM)*count);
				}
			}
			break;
		}

		i++;
	}

	CTime time = CTime::GetCurrentTime();
	CString strInfo,strTime,strStationName;
	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());

	if (pTAlarm != NULL)
	{
		delete pTAlarm;
		pTAlarm = NULL;
	}

	if (pData != NULL)
	{
		delete pData;
		pData = NULL;
	}
}

void CheckRVUIsOnLine(int handle)
{
	for (int i=0; i<g_nAssRVUNum; i++)
	{
		if (g_tAssRVU[i].commnet_handle == handle)
		{
			g_tAssRVU[i].lost_heatbeat = 0;
			TRACE("-----recv heart beat,ip=%s,port=%d----\n\n",g_tAssRVU[i].rvu_ip,g_tAssRVU[i].rvu_port);
			break;
		}
	}
}

void ParseRVURecvBuf(void* arg)
{
	int total_len = 0;
	int index = 0;
	int reserved_index = 0;
	int type = 0;
	unsigned char temp_buf[1024*32] = {0x0};

	RECV_PACKET* pRecvPacket = (RECV_PACKET*)arg;

	if (pRecvPacket == NULL)
	{
		return;
	}

	unsigned char* pBuff = (unsigned char*)pRecvPacket->recvbuf;
	int size = pRecvPacket->size;

	//TRACE("----size = %d-----\n",pRecvPacket->size);
	int i = 0;
	int temp_index = 0;
	while (i<=size)
	{
		if (pBuff[i]==0x78 && pBuff[i+1]==0x87)
		{
			total_len = (pBuff[i+2]) | (pBuff[i+3]<<8);
			index = pBuff[i+4];
			reserved_index = pBuff[i+5];

			type = (pBuff[i+22]) | (pBuff[i+23]<<8);

			switch(type)
			{
			case RESPONSE_RVU_SET_POINT_ACK:
				memcpy(&temp_buf,&pBuff[24],size-26);
				ParseRVUResponseSetPointAck(temp_buf,size-26);
				break;
			case RESPONSE_RVU_SET_SM:
				ParseRVUResponseSetSM(pBuff,size);
				break;
			case RESPONSE_RVU_SET_NODES:
				ParseRVUResponseSetNodes(pBuff,size);
				break;
			case SEND_REALTIME_ALARM:
				ParseRVUSendRealtimeAlarm(pRecvPacket->handle,pBuff,size);
				break;
			case HEART_BEAT_ACK:
				CheckRVUIsOnLine(pRecvPacket->handle);
				break;
			default:
				break;
			}
			break;
		}
		i++;
	}

	
	memset(&g_recv_packet,0,sizeof(RECV_PACKET));
}

int recv_parse(NETHANDLE handle,char* buf,int size,void* user)
{
	NETINFO info;

	if ((buf == NULL) || size == 0)
	{
		return 1;
	}

	if (g_recv_packet.size + size > RECVBUFSIZE)
	{
		memset(&g_recv_packet,0,sizeof(RECV_PACKET));
		return 1;
	}

	memcpy(g_recv_packet.recvbuf+g_recv_packet.size,buf,size);
	g_recv_packet.size += size;

	if (((unsigned char)buf[size-1]==0xd8)&&((unsigned char)buf[size-2]==0xd8))
	{
		g_recv_packet.handle = handle;
		ComDispatchTask(&g_parse_rvu_thread,ParseRVURecvBuf,&g_recv_packet,sizeof(RECV_PACKET),0);
	}

	return size;
	//return 0;

}