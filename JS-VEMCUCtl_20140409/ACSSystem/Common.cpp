#include "stdafx.h"
#include "Common.h"

//��ȡʵʱ����״̬�ı�
void GetStatusTextByStatus(char *szStatusText, int nStatus)
{
	if (nStatus == 0 || nStatus == 4)
	{
		sprintf_s(szStatusText,32,"�޸澯");
	}
	else
	{
		sprintf_s(szStatusText,32,"�и澯");
	}
}

void GetRelateVideoText(char *szRelateVideoText, int nRelateVideo)
{
	if (nRelateVideo == 0)
	{
		sprintf_s(szRelateVideoText, 32, "�޹�����Ƶ");
	}
	if (nRelateVideo == 1)
	{
		sprintf_s(szRelateVideoText, 32, "�ѹ�����Ƶ");
	}
}

