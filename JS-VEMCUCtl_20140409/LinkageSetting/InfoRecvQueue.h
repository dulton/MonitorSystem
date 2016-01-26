#pragma once

//////////////////////////////////////////////////////////////////////////
#define  RECV_BUF_MAX_COUNT (64*1024)
#define  RECV_BUF_NODE_COUNT (200)
//////////////////////////////////////////////////////////////////////////

typedef struct _b_recv_buf_node_type
{
	int DataLen;
	unsigned char Buf[RECV_BUF_MAX_COUNT];
}Recv_Buf_Node_Type;

//����һ�����ܻ������
typedef struct _recv_buf_queue_
{
	int front;                                        //ͷָ��
	int rear;                                         //βָ��
	int number;                                   //��ǰ���еĽ����
	Recv_Buf_Node_Type Node[RECV_BUF_NODE_COUNT];     //�洢��
}Recv_Buf_Queue;

void InitRecvQueue(Recv_Buf_Queue &RecvQueue);//��ʼ������
void ClearRecvQueue(Recv_Buf_Queue &RecvQueue);//��ն���
BOOL RecvQueueEmpty(Recv_Buf_Queue &RecvQueue);//�ж϶����Ƿ�Ϊ��
BOOL RecvQueueFull(Recv_Buf_Queue &RecvQueue);//�ж϶����Ƿ�����
int  GetRecvHead(Recv_Buf_Queue &RecvQueue,Recv_Buf_Node_Type &Node);//�õ�����ͷ
int  GetRecvNodeNumber(Recv_Buf_Queue &RecvQueue);//�õ���ǰ���еĽ����
int  RecvEnQueue(Recv_Buf_Queue &RecvQueue,Recv_Buf_Node_Type &Node);//�����
int  RecvDeQueue(Recv_Buf_Queue &RecvQueue,Recv_Buf_Node_Type &Node);//������
