#pragma once

#include "linkobjectbase.h"

/*
�¼����ݣ�
1   ���ȵ���   
2   ��̬ �ָ������±���״̬
3   ȷ�� ����״̬Ԫ��ͣ���������
4   �¹�����
5   Ԥ������
6   ������
7   ȫ������
8   ȫ������
9   ȫ������
10  ȫ��
11  ȫ��
12  ȫ��
13  ȫ��
14  ����
15  ����
16  ��ʾ�����
17  ��ʾ����ַ��ʾ
*/

class CMNP_ZJNH :
	public CLinkObjectBase
{
    DECLARE_SERIAL(CMNP_ZJNH);
public:	
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual void Serialize_Ty(CArchive &ar);
	BOOL OnEditProperties();
	CMNP_ZJNH(void);
	~CMNP_ZJNH(void);
protected:
	BOOL Event1_Enable;
	BOOL Event2_Enable;
	BOOL Event3_Enable;
	BOOL Event4_Enable;
	BOOL Event5_Enable;
	BOOL Event6_Enable;
	BOOL Event7_Enable;
	BOOL Event8_Enable;
	BOOL Event9_Enable;
	BOOL Event10_Enable;
	BOOL Event11_Enable;
	BOOL Event12_Enable;
	BOOL Event13_Enable;
	BOOL Event14_Enable;
	BOOL Event15_Enable;
	BOOL Event16_Enable;
	BOOL Event17_Enable;

};
