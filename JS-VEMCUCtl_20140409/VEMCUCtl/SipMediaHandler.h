#ifndef   _SIP_MEDIA_HANDLER_H_
#define  _SIP_MEDIA_HANDLER_H_

#include "UtilMedia.h"
#include "SipUtil.h"

/***************************************ý��������غ���***********************************/

//��Ƶ���ݽ��մ�����
bool AudioMediaDataRecvHandler(int  nCID,
							                            void* pData,
														int	 nDataLen,
														unsigned int nMediaPayload,
														bool bMark,
														unsigned int nTimestamp,
														unsigned int nSeqNo);

//��Ƶ���ݽ��մ�����
bool VideoMediaDataRecvHandler(int  nCID,
							                            void* pData,
														int	 nDataLen,
														unsigned int nMediaPayload,
														bool bMark,
														unsigned int nTimestamp,
														unsigned int nSeqNo);

//���
extern CRtUtilH264ReFUA*  g_pRecvH264ReFUA;

#endif