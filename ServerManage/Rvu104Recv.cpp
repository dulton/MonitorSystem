#include "StdAfx.h"
#include "Rvu104Recv.h"
#include "DataBaseExcute.h"

RECV_PACKET g_recv_104packet[MAX_SM_NUM_PER_STATION];
int recvflag=0;


extern _T_ASS_RVU_INFO_ g_tAssRVU[MAX_RVU_NUM_PER_STATION]; 
extern int g_nAssRVUNum;
extern COMMONTHREADPOOL g_parse_rvu104_thread ;
extern COMMONTHREADPOOL g_db_datathread;
extern COMMONTHREADPOOL g_db_smthread;
extern T_RVU_DATA g_sRVUData[MAX_RVU_DEVICE_NUM_PER_STATION];
extern int rvu_num;


extern _T_DEV_ID g_devID[MAX_RVU_DEVICE_NUM_PER_STATION];
extern int devnum;


T_104_SM_LOAD t_104_sminfo[MAX_SM_NUM_PER_STATION];
int t_104_num=0;

extern int getMaxnum;//��ȡ�������
extern int getNnum;//��ǰ��ȡ������
extern bool g_bRecvComplete;//�Ƿ������һ��rcu������

//���ջص�����
int recv_104_parse(NETHANDLE handle,char* buf,int size,void* user)
{
	//NETINFO info;
	if ((buf == NULL) || size == 0)
	{
		return 1;
	}
//	printf("\n handlenum is %d",handlenum104);
	int handleflag=0;
	int num=0;
	int i=0;
// 	for (i=0;i<handlenum104;i++)
// 	{
// 		if (handle==g_recv_104packet[i].handle)
// 		{
// 			handleflag=1;
// 			num=i;
// 			break;
// 		}
// 	}
// 	if (handleflag==0)
// 	{
// 		g_recv_104packet[handlenum104].handle=handle;
// 		num=handlenum104;
// 		handlenum104++;
// 	}
// 	//	ComCloseNet(handle,1);
// 	if (g_recv_104packet[num].size + size >RECVBUFSIZE )
// 	{
// 		memset(&g_recv_104packet[num],0,sizeof(RECV_PACKET));
// 		handlenum104--;
// 		return 1;
// 	}
// 	for (i=0;i<size;i++)
// 	{
// 		printf("\n %02x",buf[i]);
// 	}




	bool bFindhead=false;
	int istart=0;
	for (istart=0;istart<size;istart++)
	{
		if (0x68==buf[istart])
		{
			bFindhead=true;
			break;
		}
	}
	if (false==bFindhead)
	{
		return size;
	}
	//�ж��߳������ϴ�����
	if (0x06==buf[istart+4])
	{
		return size;
	}

	FILE* f;
	if((f = fopen("recv.txt", "a+")) == (FILE*)NULL)
	{
		printf("\n �ļ���ʧ��");
		
	}
	
	for(i=0;i<size;i++)
	{
		fprintf(f,"%02x ",buf[i]);
		
	}
	fprintf(f,"\n");
	fclose(f);
	if ((unsigned char)buf[size-1]==0x16)
	{
		printf("\n send is 111111 ");
// 		ComInitThreadPool(&g_parse_rvu104_thread,SINGLEFIFOTHREADPOOL|COPYARG,-1,1,100);
// 		g_recv_104packet.handle = handle;
// 		ComDispatchTask(&g_parse_rvu104_thread,Parse104RVURecvBuf,&g_recv_104packet,sizeof(RECV_PACKET),0);
// 		memset(&g_recv_104packet,0,sizeof(RECV_PACKET));
		recvflag=1;

		for(i=0;i<MAX_SM_NUM_PER_STATION;i++)
		{
			printf("\n size is %d",g_recv_104packet[i].size);
			if(g_recv_104packet[i].size==0)
			{
				memset(g_recv_104packet[i].recvbuf,0,RECVBUFSIZE);
				memcpy(g_recv_104packet[i].recvbuf,&buf[istart],size-istart);
				g_recv_104packet[i].size = size-istart;
				g_recv_104packet[i].handle=handle;
				printf("\n g_recvbuff 1 is %02x size is %d",g_recv_104packet[i].recvbuf[0],g_recv_104packet[i].size);
				break;
			}
			
		}


	}	
	return size;
	
}
/*
BYTE[]תINT����
b:BYTE��Դ
num:�ֽ���
*/
int bytes2Int(BYTE* b,int num)
{  
	int temp = 0;  
	int res = 0; 
	int i;
	for (i = 0; i < num; i++) {  
		res <<= 8;  
		temp = b[i]&0xFF;  
		res |= temp;  
	}  
	return res;  
}  
/*
CP56Time2aתtime����
data:BYTE��Դ
st:time����
*/
void CP56Time2aToTime(unsigned char *data, SYSTEMTIME *st)
{
 
	unsigned int mili = data[0] | data[1]<<8;
	st->wSecond= mili / 1000;
	st->wMilliseconds = mili - st->wSecond*1000;
 

	st->wMinute= data[2] & 0x3F;;
	st->wHour= data[3] & 0x1F;


	st->wDay= data[4] & 0x1F;
	st->wDayOfWeek = (data[4] & 0xE0 ) >> 5;
	if(st->wDayOfWeek)// if zero day of week not used.
	st->wDayOfWeek = (st->wDayOfWeek + 1)%7;
	st->wMonth= data[5] & 0x0F;
	st->wYear= 2000 + (data[6] & 0x7F);

}
/*
//����ң��
void Parse104RVUYX1(int handle,unsigned char* buff,int rvuid)
{
	int i=0,k=0;

	int reserved_index = 0;
	int count = 0;
	//char data[64*1024]={0x0};
	BYTE address[3];
	
	count=buff[7];
	T_DATA_ *pTdata=new T_DATA_[count];
	k=12;
	for(i=0;i<count;i++)
	{
		memset(address,0,3);
		address[2]=buff[k];
		k++;
		address[1]=buff[k];
		k++;
		address[0]=buff[k];
		k++;
		
		
		pTdata[i].type=2;
		pTdata[i].id.SmID=bytes2Int(address,3);
		pTdata[i].id.NodeID=0;
		pTdata[i].t_value=buff[k];
		pTdata[i].size=0;
		pTdata[i].enumstate=0;

		k++;

	}
	//  �湲���ڴ�
	int j=0;
	int changeflag=1;
	//����RVU 
	for (j=0;j<rvu_num;i++);
	{//��ѯ�Ƿ�Ϊ���ݱ��������������
		if (g_sRVUData[j].rvu_id==rvuid)//���ݱ��
		{
			//�ϴ���־��1
			g_sRVUData[j].uploadflag=1;
			for (i=0;i<g_sRVUData[j].count;i++)
			{
				int n=0;
				for(n=0;n<count;n++)
				{
					if ((g_sRVUData[j].t_datas[i].id.SmID==pTdata[n].id.SmID))
					{
						g_sRVUData[j].t_datas[i].t_value=pTdata[n].t_value;
						g_sRVUData[j].t_datas[i].enumstate=pTdata[n].enumstate;
						//���±�־��1
						g_sRVUData[j].t_datas[i].changeflag=1;
						g_sRVUData[j].t_datas[i].alarmflag=1;
						
					}
				}
				
			}
			changeflag=0;
		}
		
	}
	//��������
	if (changeflag==1)
	{
		g_sRVUData[rvu_num].rvu_id=rvuid;
		
		g_sRVUData[rvu_num].count=count;
		for(int i=0;i<g_nAssRVUNum;i++)
		{
			if (g_tAssRVU[i].rvu_id==rvuid)
			{
				g_sRVUData[rvu_num].station_id=g_tAssRVU[i].station_id;
			}
		}
		
		for (i=0;i<count;i++)
		{
			g_sRVUData[rvu_num].t_datas[i].type=pTdata[i].type;
			g_sRVUData[rvu_num].t_datas[i].id.SmID=pTdata[i].id.SmID;
			g_sRVUData[rvu_num].t_datas[i].id.NodeID=0;
			g_sRVUData[rvu_num].t_datas[i].t_value=pTdata[i].t_value;
			g_sRVUData[rvu_num].t_datas[i].enumstate=0;
			g_sRVUData[rvu_num].t_datas[i].size=0;
			strcpy(g_sRVUData[rvu_num].t_datas[i].desc,"");
			//���±�־����
			g_sRVUData[rvu_num].t_datas[i].changeflag=0;
			g_sRVUData[rvu_num].t_datas[i].alarmflag=1;
			
		}
		//�ϴ���־����
		g_sRVUData[rvu_num].uploadflag=0;
		//���ܵ�ʵʱ��Ϣrvu����+1
		rvu_num++;
	}


	T_data_LOAD *t_data_load=new T_data_LOAD;
	t_data_load->count=count;
	t_data_load->rvuid=rvuid;
	
	
	//	t_sm_load.t_sm=(T_SM_*)malloc(sizeof(T_SM_)*count);
	t_data_load->t_data=new T_DATA_[count];
	memset(t_data_load->t_data,0,sizeof(T_DATA_)*count);
	memcpy(t_data_load->t_data,pTdata,sizeof(T_DATA_)*count);
	
	ComDispatchTask(&g_db_datathread,SaveRvuData,t_data_load,sizeof(T_data_LOAD),0);
	
	//   ��Դ����
	if (pTdata != NULL)
	{
		delete pTdata;
		pTdata = NULL;
	}

	if (t_data_load->t_data != NULL)
	{
		delete (t_data_load->t_data);
		t_data_load->t_data = NULL;
		delete t_data_load;
		
	}
}
//����ʱ���ʽ�ĵ���ң��
void Parse104RVUYX2(int handle,unsigned char* buff,int rvuid)
{
	int i=0,k=0;
	
	int reserved_index = 0;
	int count = 0;
	//char data[64*1024]={0x0};
	BYTE address[3];
	BYTE second[2];
	int sec=0;
	int min=0;
	int mils=0;
	
	count=buff[7];
	_T_104_YX2 *pYX2=new _T_104_YX2[count];
	T_DATA_ *pTdata=new T_DATA_[count];
	k=12;
	for(i=0;i<count;i++)
	{
		memset(address,0,3);
		address[2]=buff[k];
		k++;
		address[1]=buff[k];
		k++;
		address[0]=buff[k];
		k++;
		
		pYX2[i].addressID=bytes2Int(address,3);
		pYX2[i].status=buff[k];
		k++;
		memset(second,0,2);
		second[1]=buff[k];
		k++;
		second[0]=buff[k];
		k++;
		sec=bytes2Int(second,2);
		mils=sec%1000;
		sec=sec/1000;

		min=buff[k];
		k++;
		sprintf(pYX2[i].s_time,"%d:%d.%d",min,sec,mils);

		pTdata[i].type=2;
		pTdata[i].id.SmID=pYX2[i].addressID;
		pTdata[i].id.NodeID=0;
		pTdata[i].t_value=pYX2[i].status;
		pTdata[i].size=0;
		pTdata[i].enumstate=1;

	}
	//  �湲���ڴ�
	int j=0;
	int changeflag=1;
	//����RVU 
	for (j=0;j<rvu_num;i++);
	{//��ѯ�Ƿ�Ϊ���ݱ��������������
		if (g_sRVUData[j].rvu_id==rvuid)//���ݱ��
		{
			//�ϴ���־��1
			g_sRVUData[j].uploadflag=1;
			for (i=0;i<g_sRVUData[j].count;i++)
			{
				int n=0;
				for(n=0;n<count;n++)
				{
					if ((g_sRVUData[j].t_datas[i].id.SmID==pTdata[n].id.SmID))
					{
						g_sRVUData[j].t_datas[i].t_value=pTdata[n].t_value;
						g_sRVUData[j].t_datas[i].enumstate=pTdata[n].enumstate;
						//���±�־��1
						g_sRVUData[j].t_datas[i].changeflag=1;
						g_sRVUData[j].t_datas[i].alarmflag=1;
						
					}
				}
				
			}
			changeflag=0;
		}
		
	}

	
	//�����ݿ�
	T_data_LOAD *t_data_load=new T_data_LOAD;
	t_data_load->count=count;
	t_data_load->rvuid=rvuid;
	
	
	//	t_sm_load.t_sm=(T_SM_*)malloc(sizeof(T_SM_)*count);
	t_data_load->t_data=new T_DATA_[count];
	memset(t_data_load->t_data,0,sizeof(T_DATA_)*count);
	memcpy(t_data_load->t_data,pTdata,sizeof(T_DATA_)*count);
	
	ComDispatchTask(&g_db_datathread,SaveRvuData,t_data_load,sizeof(T_data_LOAD),0);
	
	//   ��Դ����
	if (pYX2 != NULL)
	{
		delete pYX2;
		pYX2 = NULL;
	}
	if (pTdata != NULL)
	{
		delete pTdata;
		pTdata = NULL;
	}
	
	if (t_data_load->t_data != NULL)
	{
		delete (t_data_load->t_data);
		t_data_load->t_data = NULL;
		delete t_data_load;
		
	}
}
//CP56Time2a�ĵ���ң��
void Parse104RVUYX1e(int handle,unsigned char* buff,int rvuid)
{
	int i=0,k=0,t=0;
	
	int reserved_index = 0;
	int count = 0;
	//char data[64*1024]={0x0};
	BYTE address[3];
	BYTE Cp_Time[7];
	SYSTEMTIME st;
	count=buff[7];
	_T_104_YX1E *pYX1e=new _T_104_YX1E[count];
	T_DATA_ *pTdata=new T_DATA_[count];
	k=12;
	for(i=0;i<count;i++)
	{
		memset(address,0,3);
		address[2]=buff[k];
		k++;
		address[1]=buff[k];
		k++;
		address[0]=buff[k];
		k++;
		
		pYX1e[i].addressID=bytes2Int(address,3);
		pYX1e[i].status=buff[k];
		k++;
		
		for(t=0;t<7;t++)
		{
			Cp_Time[t]=buff[k];
			k++;
		}
		CP56Time2aToTime(Cp_Time,&st);

		sprintf(pYX1e[i].cp_time,"%d-%d-%d %d:%d:%d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);

		pTdata[i].type=2;
		pTdata[i].id.SmID=pYX1e[i].addressID;
		pTdata[i].id.NodeID=0;
		pTdata[i].t_value=pYX1e[i].status;
		pTdata[i].size=0;
		pTdata[i].enumstate=1;
		

	}
	//  �湲���ڴ�
	int j=0;
	int changeflag=1;
	//����RVU 
	for (j=0;j<rvu_num;i++);
	{//��ѯ�Ƿ�Ϊ���ݱ��������������
		if (g_sRVUData[j].rvu_id==rvuid)//���ݱ��
		{
			//�ϴ���־��1
			g_sRVUData[j].uploadflag=1;
			for (i=0;i<g_sRVUData[j].count;i++)
			{
				int n=0;
				for(n=0;n<count;n++)
				{
					if ((g_sRVUData[j].t_datas[i].id.SmID==pTdata[n].id.SmID))
					{
						g_sRVUData[j].t_datas[i].t_value=pTdata[n].t_value;
						g_sRVUData[j].t_datas[i].enumstate=pTdata[n].enumstate;
						//���±�־��1
						g_sRVUData[j].t_datas[i].changeflag=1;
						g_sRVUData[j].t_datas[i].alarmflag=1;
						
					}
				}
				
			}
			changeflag=0;
		}
		
	}
	
	
	//�����ݿ�
	T_data_LOAD *t_data_load=new T_data_LOAD;
	t_data_load->count=count;
	t_data_load->rvuid=rvuid;
	
	
	//	t_sm_load.t_sm=(T_SM_*)malloc(sizeof(T_SM_)*count);
	t_data_load->t_data=new T_DATA_[count];
	memset(t_data_load->t_data,0,sizeof(T_DATA_)*count);
	memcpy(t_data_load->t_data,pTdata,sizeof(T_DATA_)*count);
	
	ComDispatchTask(&g_db_datathread,SaveRvuData,t_data_load,sizeof(T_data_LOAD),0);
	
	//   ��Դ����
	if (pYX1e != NULL)
	{
		delete pYX1e;
		pYX1e = NULL;
	}
	if (pTdata != NULL)
	{
		delete pTdata;
		pTdata = NULL;
	}
	
	if (t_data_load->t_data != NULL)
	{
		delete (t_data_load->t_data);
		t_data_load->t_data = NULL;
		delete t_data_load;
		
	}
}
*/
//ϵͳ�ṹ��Ϣ����SM
int Parse104RVUSendSM(int handle,unsigned char* buff,int rvuid)
{
	//	TRACE("-----size=%d------\n\n",size);
	
	int i=0,k=0,j=0;

	int type = 0;
	int count = 0;

	int num=0;
	int changeflag=0;

	
//	T_SM* pTsm=NULL;
	T_104_SM *pTsm=NULL;

		
	count = buff[42] | (buff[43]<<8);


	
	

	pTsm = new T_104_SM[count];
	memset(pTsm,0,sizeof(T_104_SM)*count);
	memcpy(pTsm,&buff[44],sizeof(T_104_SM)*count);
		

			
	


	for (j=0; j<count; j++)
	{
		printf("\n node name is %s",pTsm[j].nodename);
		
		/*if (pTSM[j].device_type==12 && pTSM[j].sub_device_type==1)
		{
			continue ;
		}*/

	}
	//   ���ݴ洢���ݿ�

	
//	int result=SaveRvuSM(pTsm,count,rvuid);

	for(i=0;i<t_104_num;i++)
	{
		if (t_104_sminfo[i].rvuid==rvuid)
		{
			num=t_104_sminfo[i].count;
	

			memcpy(t_104_sminfo[i].t_sm+num,pTsm,sizeof(T_104_SM)*count);
		
			t_104_sminfo[i].count+=count;

			changeflag=1;
			break;

		}
	}
	//����RVU�豸
	if (changeflag==0)
	{
		num=t_104_num;
		t_104_sminfo[num].rvuid=rvuid;
		t_104_sminfo[num].count=count;
		memcpy(t_104_sminfo[num].t_sm,pTsm,sizeof(T_104_SM)*count);
		t_104_num++;

	}


//	

//	delete t_sm_load;

// 	if (result!=0)
// 	{
// 		//�洢ʧ��
// 		printf("\n�洢���ģ����Ϣʧ��");
// 		return 0;
// 	}
		
	//   ��Դ����
	if (pTsm != NULL)
	{
		delete pTsm;
		pTsm = NULL;
	}
	

	return 1;
}
/*ʵʱ������Ϣ����
handle ���Ӿ��
buff ��������
rvuid RVU���
enumstate �������� 0Ϊ�������� ����1Ϊ����澯����
*/
int Parse104RVUSendREAL(int handle,unsigned char* buff,int rvuid,int enumstate)
{
	//	TRACE("-----size=%d------\n\n",size);
	
	int i=0,k=0;
	int total_len = 0;
	int index = 0;
	int reserved_index = 0;
	int type = 0;
	int count = 0;
	int result=0;
	int data_index = 0;
	int first_len = 0;
	int data_len = 0;
	int changeflag=0;
	int num=0;
	//char data[64*1024]={0x0};

	T_104_REAL *pReal=NULL;
	
	getMaxnum = buff[40] | (buff[41]<<8);
	count = buff[42] | (buff[43]<<8);
	getNnum+=count;

	printf("\n ��ǰ������ %d,�ۼƽ������� %d ,��ǰ�������� %d",getMaxnum,getNnum,count);
	
	//������һ��rcu����
	if (getMaxnum == getNnum)
	{
		g_bRecvComplete = true;
		getMaxnum = 0;
		getNnum = 0;
	}

	pReal = new T_104_REAL[count];
	memset(pReal,0,sizeof(T_104_REAL)*count);
	memcpy(pReal,&buff[44],sizeof(T_104_REAL)*count);

	T_DATA* pTdata=NULL;

	
	printf("\n ʵʱ��¼����__________ %d",count);

	pTdata=new T_DATA[count];
	for (i=0;i<count;i++)
	{

		pTdata[i].id.SmID=pReal[i].smid[0]|(pReal[i].smid[1]<<8);
		pTdata[i].id.NodeID=pReal[i].nodeid[0]|(pReal[i].nodeid[1]<<8);
		pTdata[i].t_value=atof(pReal[i].t_value);
		pTdata[i].size=0;
		if (atoi(pReal[i].t_value)==1)
		{
			enumstate=1;
		}
		else
			enumstate=0;
		pTdata[i].enumstate=enumstate;

		for (k=0;k<devnum;k++)
		{
			if ((g_devID[k].rvuid==rvuid)&&(g_devID[k].SmID==pTdata[i].id.SmID)&&(g_devID[k].NodeID==pTdata[i].id.NodeID))
			{
				pTdata[i].type=g_devID[k].enumtype;
			}
		}
		printf("\n pTdata smid %d node id %d t_value %f",pTdata[i].id.SmID,pTdata[i].id.NodeID,pTdata[i].t_value);

	}


			

//  �湲���ڴ�
	int j=0;
// �ж����������ݻ��Ǳ������ 

	//����RVU 
	for (j=0;j<MAX_SM_NUM_PER_STATION;j++)
	{
		if (g_sRVUData[j].rvu_id==rvuid)//���ݱ��
		{
	
			printf("\n ���ݸ��� count %d",count);
		
			//�ϴ���־��1
			g_sRVUData[j].uploadflag=1;
			for (i=0;i<g_sRVUData[j].count;i++)
			{
				int n=0;
				for(n=0;n<count;n++)
				{
					if ((g_sRVUData[j].t_datas[i].id.SmID==pTdata[n].id.SmID)&&(g_sRVUData[j].t_datas[i].id.NodeID==pTdata[n].id.NodeID)&&(pTdata[n].type==2))
					{
						printf("\n ���ݱ仯");
						if(g_sRVUData[j].t_datas[i].t_value!=pTdata[n].t_value)
						{
							g_sRVUData[j].t_datas[i].changeflag=1;							
							g_sRVUData[j].t_datas[i].alarmflag=1;
							g_sRVUData[j].t_datas[i].updateflag=1;
						}
					
						g_sRVUData[j].t_datas[i].t_value=pTdata[n].t_value;
						g_sRVUData[j].t_datas[i].enumstate=pTdata[n].enumstate;

						changeflag=1;
					}
				}
				
			}
			printf("\n changeflag is %d",changeflag);
			if(changeflag==0)//��������
			{
				changeflag=2;
				printf("\n �������� count %d",count);
				num=g_sRVUData[j].count;
				for (k=0;k<count;k++)
				{
					if(pTdata[k].type==2)
					{
						g_sRVUData[j].t_datas[num].type=pTdata[k].type;
						g_sRVUData[j].t_datas[num].id=pTdata[k].id;
						g_sRVUData[j].t_datas[num].t_value=pTdata[k].t_value;
						g_sRVUData[j].t_datas[num].enumstate=pTdata[k].enumstate;
						g_sRVUData[j].t_datas[num].size=pTdata[k].size;
						//���±�־����
						g_sRVUData[j].t_datas[num].changeflag=1;
						g_sRVUData[j].t_datas[num].alarmflag=0;
						num++;
					}
				}
				g_sRVUData[j].count=num;
				printf("\n get rvudata  count is %d__________________________________________",num);
			}
			
			break;
		}		
	}
	
	if(changeflag==0)//��������
	{
		printf("\n �������� count %d  rvunum %d",count,rvu_num);
		g_sRVUData[rvu_num].rvu_id=rvuid;
		
		g_sRVUData[rvu_num].count=count;
		for(int i=0;i<g_nAssRVUNum;i++)
		{
			if (g_tAssRVU[i].rvu_id==rvuid)
			{
				g_sRVUData[rvu_num].station_id=g_tAssRVU[i].station_id;
			}
		}
		
		for (i=0;i<count;i++)
		{
			if(pTdata[i].type==2)
			{
				g_sRVUData[rvu_num].t_datas[i].type=pTdata[i].type;
				g_sRVUData[rvu_num].t_datas[i].id=pTdata[i].id;
				g_sRVUData[rvu_num].t_datas[i].t_value=pTdata[i].t_value;
				g_sRVUData[rvu_num].t_datas[i].enumstate=pTdata[i].enumstate;
				g_sRVUData[rvu_num].t_datas[i].size=pTdata[i].size;
		//		strcpy(g_sRVUData[rvu_num].t_datas[i].desc,pTdata[i].desc);
				//���±�־����
				g_sRVUData[rvu_num].t_datas[i].changeflag=1;
				g_sRVUData[rvu_num].t_datas[i].alarmflag=0;	
			}

			
		}
		//�ϴ���־����

		g_sRVUData[rvu_num].uploadflag=0;
		//���ܵ�ʵʱ��Ϣrvu����+1
		rvu_num++;
	
	}


//   ���ݴ洢���ݿ�
//	int result1=SaveRvuData(pTdata,count,rvuid);

// 	T_data_LOAD *t_data_load=new T_data_LOAD;
// 	t_data_load->count=count;
// 	t_data_load->rvuid=rvuid;
	
	
	//	t_sm_load.t_sm=(T_SM_*)malloc(sizeof(T_SM_)*count);
// 	t_data_load->t_data=new T_DATA_[count];
// 	memset(t_data_load->t_data,0,sizeof(T_DATA_)*count);
// 	memcpy(t_data_load->t_data,pTdata,sizeof(T_DATA_)*count);
	
//	ComDispatchTask(&g_db_datathread,SaveRvuData,t_data_load,sizeof(T_data_LOAD),0);
	
// 	if (result1!=0)
// 	{
// 		//�洢ʧ��
// 		printf("\n �洢ʵʱ��Ϣʧ��");
// 		return 0;
// 	}
	
	
	//   ��Դ����
	if (pReal != NULL)
	{
		delete pReal;
		pReal = NULL;
	}

	if (pTdata != NULL)
	{
		delete pTdata;
		pTdata = NULL;
	}
	

// 	if (t_data_load->t_data != NULL)
// 	{
// 		delete (t_data_load->t_data);
// 		t_data_load->t_data = NULL;
// 		delete t_data_load;
// 		
// 	}
	return 1;
}


void Parse104RVURecvBuf(void* arg)
{
	int total_len = 0;
	int index = 0;
	int reserved_index = 0;
	int type = 0;
	//	unsigned char temp_buf[1024*32] = {0x0};
	int i=0;
	int lenth=0;
	int j=0;
	int handlenum=0;
	int handle=0;
	
	while(1)
	{
		
		for (i=0;i<MAX_SM_NUM_PER_STATION;i++)
		{
			
			if (g_recv_104packet[i].size>0)
			{
				printf("\n recv is 111111111");
				BYTE* pBuff = (BYTE*)g_recv_104packet[i].recvbuf;
				int size = g_recv_104packet[i].size;
				g_recv_104packet[i].size=0;//ȡ�����ݺ����
				int rvuid=0;
				char rvuip[16];
				char rvucode[32];
				int rvuport=0;
				int datalen=0;
				handle=g_recv_104packet[i].handle;
				//��������
				//	BYTE zzBuff[16]={0x68,0x0e,0x00,0x00,0x00,0x00,0x64,0x01,0x06,0x00,0x01,0x00,0x00,0x00,0x00,0x14};
				
				
				// �������ݴ���
				_T_104_BUFF *sendBuff;
				
				int i = 0;
				int temp_index = 0;
				
				printf("\n handle is %d  fun is %02x",g_recv_104packet[i].handle,pBuff[4]);
				//�ж��Ƿ�Ϊ���뷽�����ǽ��뷽������
				if (pBuff[3]=0x00)
				{
					return;
				}
				
				memcpy(rvucode,&pBuff[8],32);
				
				printf("\n rvucode is %s",rvucode);
				for (i=0;i<g_nAssRVUNum;i++)
				{
					if (strcmp(g_tAssRVU[i].rvu_code,rvucode)==0)
					{
						printf("\n ��ȡ���ݳɹ�");
						rvuid=g_tAssRVU[i].rvu_id;
						memcpy(rvuip,g_tAssRVU[i].rvu_ip,16);
						rvuport=g_tAssRVU[i].rvu_port;
						handlenum=i;
					}
				}
				//���������ж�
				switch(pBuff[4])
				{
				case 1://���뷽ע��
					{
						
					}
					break;
				case 2://��ȡ����YX/TCֵ
					break;
				case 3://Զ��ң��
					break;
				case 4://����
					try
					{
						Parse104RVUSendREAL(handle,pBuff,rvuid,0);
					}
					catch(...)
					{
						printf("\n��������");
					}
					break;
				case 5://����
					{
					//	g_tAssRVU[handlenum].lost_heatbeat=0;//���յ���������0
					}
					break;
				case 6://��������
					{
					//	Parse104RVUSendREAL(handle,pBuff,rvuid,1);
					}
					break;
				case 7://�ṹ��Ϣ��ȡ
					try
					{
						Parse104RVUSendSM(handle,pBuff,rvuid);
					
					}
					catch(...)
					{
						printf("\n��������");
					}
					break;
				default:
					break;
					
				}
		
			}
			else
			{
			printf("\n û������");
			Sleep(1*1000);
			break;
			}
	
		}
	
			
	}


/*
	//�ж��Ƿ�Ϊ������Ӧ
	if ((pBuff[1]==4)&&(pBuff[2]==0x0b))
	{
		printf("\n ������Ӧ");
		//������������
		ComSendNet(pRecvPacket->handle,NULL,0,0,0,0,0,(char *)zzBuff,16,0);
		return;
		
	}
	//�ж��Ƿ�Ϊ����֡
	if ((pBuff[1]==4)&&(pBuff[2]==0x83))
	{
		printf("\n �������Ӧ");
		return;
		
	}
	//�ж��Ƿ�Ϊ��Ӧ����
	if ((pBuff[6]==0x64)&&(pBuff[8]==0x07))
	{
		printf("\n ������Ӧ");
		return;
		
	}

	//�ж��Ƿ�Ϊ��Ӧ���ٻ�
	if (pBuff[8]==0x14)
	{
		switch(pBuff[6])
		{
		case 0x01://����ң�� 4BYTE
			for (j=0;j<g_nAssRVUNum;j++)
			{
				if (g_tAssRVU[j].commnet_handle==pRecvPacket->handle)
				{
					rvuid=g_tAssRVU[j].rvu_id;
					memcpy(rvuip,g_tAssRVU[j].rvu_ip,16);
					rvuport=g_tAssRVU[j].rvu_port;
				}
			}
			Parse104RVUYX1(pRecvPacket->handle,pBuff,rvuid);
			break;
		default:
			break;
		}
		return;
	}
	//�ж��Ƿ�Ϊ�������ٻ�
	if ((pBuff[8]==0x0a)&&(pBuff[6]==0x64))
	{
		printf("\n ��������");
		return;
	}
	//�ж��Ƿ�Ϊ����������Ϣ
	if (pBuff[8]==0x03)
	{
		switch(pBuff[6])
		{
		case 0x02://��ʱ��ĵ���ң�� 7BYTE
			for (j=0;j<g_nAssRVUNum;j++)
			{
				if (g_tAssRVU[j].commnet_handle==pRecvPacket->handle)
				{
					rvuid=g_tAssRVU[j].rvu_id;
					memcpy(rvuip,g_tAssRVU[j].rvu_ip,16);
					rvuport=g_tAssRVU[j].rvu_port;
				}
			}
			Parse104RVUYX2(pRecvPacket->handle,pBuff,rvuid);
			break;
		case 0x1e://��cp56Time2aʱ��ĵ���ң�� 11BYTE
			for (j=0;j<g_nAssRVUNum;j++)
			{
				if (g_tAssRVU[j].commnet_handle==pRecvPacket->handle)
				{
					rvuid=g_tAssRVU[j].rvu_id;
					memcpy(rvuip,g_tAssRVU[j].rvu_ip,16);
					rvuport=g_tAssRVU[j].rvu_port;
				}
			}
			Parse104RVUYX1e(pRecvPacket->handle,pBuff,rvuid);
			break;
		default:
			break;
		}
		return;
	}

*/

//exit(1);
	
}