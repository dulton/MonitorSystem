#include "stdafx.h"
#include "InfoRecvQueue.h"

void InitRecvQueue(Recv_Buf_Queue &RecvQueue)//��ʼ������
{
	RecvQueue.front  = 0;
	RecvQueue.rear   = 0;
	RecvQueue.number = 0;
	memset(RecvQueue.Node,0,sizeof(RecvQueue.Node));
}

void ClearRecvQueue(Recv_Buf_Queue &RecvQueue)//��ն���
{
	RecvQueue.front  = 0;
	RecvQueue.rear   = 0;
	RecvQueue.number = 0;
	memset(RecvQueue.Node,0,sizeof(RecvQueue.Node));
}

BOOL RecvQueueEmpty(Recv_Buf_Queue &RecvQueue)//�ж϶����Ƿ�Ϊ��
{
	if (RecvQueue.front == RecvQueue.rear)
		return TRUE;
	else
		return FALSE;
}

BOOL RecvQueueFull(Recv_Buf_Queue &RecvQueue)//�ж϶����Ƿ�����
{
	if (((RecvQueue.rear+1)%RECV_BUF_NODE_COUNT) == RecvQueue.front)
		return TRUE;
	else
		return FALSE;
}

int GetRecvHead(Recv_Buf_Queue &RecvQueue,Recv_Buf_Node_Type &Node)//�õ�����ͷ
{
	if (!RecvQueueEmpty(RecvQueue))
	{
		Node.DataLen = RecvQueue.Node[RecvQueue.front].DataLen;
		memcpy(Node.Buf,RecvQueue.Node[RecvQueue.front].Buf,Node.DataLen);
		return 1;
	}	
	return 0;
}

int GetRecvNodeNumber(Recv_Buf_Queue &RecvQueue)//�õ���ǰ���еĽ����
{
	return RecvQueue.number;
}

int  RecvEnQueue(Recv_Buf_Queue &RecvQueue,Recv_Buf_Node_Type &Node)//�����
{
	if (!RecvQueueFull(RecvQueue))
	{
		if ((Node.DataLen > RECV_BUF_MAX_COUNT)||(Node.DataLen < 0))
			RecvQueue.Node[RecvQueue.rear].DataLen = 0;
		else
			RecvQueue.Node[RecvQueue.rear].DataLen = Node.DataLen;
		memcpy(RecvQueue.Node[RecvQueue.rear].Buf,Node.Buf,Node.DataLen);

		RecvQueue.rear = (RecvQueue.rear+1)%RECV_BUF_NODE_COUNT;
		RecvQueue.number++;
		return 1;
	}	
	return 0;
}

int RecvDeQueue(Recv_Buf_Queue &RecvQueue,Recv_Buf_Node_Type &Node)//������
{
	if (!RecvQueueEmpty(RecvQueue))
	{
		Node.DataLen = RecvQueue.Node[RecvQueue.front].DataLen;
		memcpy(Node.Buf,RecvQueue.Node[RecvQueue.front].Buf,Node.DataLen);
		RecvQueue.front = (RecvQueue.front+1)%RECV_BUF_NODE_COUNT;
		RecvQueue.number--;
		return 1;
	}	
	return 0;
}