/********************************************************************
 *
 *	Copyright (c) 2010 by SniffXu.
 *
 *	Name		: UtilMedia.h
 *
 *	Purpose		:�ṩ��Ƶ���ݷְ����麯��
 *
 *
 ********************************************************************/
#ifndef _RT_SIP_STACK_FILE_H_UTIL_VIDEO_MEDIA_
#define _RT_SIP_STACK_FILE_H_UTIL_VIDEO_MEDIA_

#include <stdio.h>
#include <string.h>

#if defined(WIN32)
	#include <windows.h>
#else
	#include  <unistd.h>
	#include  <fcntl.h>
	#include  <sys/types.h>
	#include  <sys/stat.h>
	#include  <stdlib.h>
	#include  <errno.h>
#endif

/**************************************************************
 *	 
 *  ������յ�����Ƶ����
 *
 *************************************************************/
class CRtUtilH264ReFUA
{
public:
	CRtUtilH264ReFUA(unsigned int nMaxFrameLen);
	~CRtUtilH264ReFUA();

	void	  PushData(unsigned char* pData, int nDataLen, bool bMark, unsigned nTS, unsigned nSEQ);
	unsigned  PopFrame(unsigned char** ppFrame);

	void	  PhonePushData(unsigned char* pData, int nDataLen, bool bMark, unsigned nTS, unsigned nSEQ);
	unsigned  PhonePopFrame(unsigned char** ppFrame);

	void	  H264PushData(unsigned char* pData, int nDataLen, bool bMark, unsigned nTS, unsigned nSEQ);
	void	  H264PushData4GrandstreamCL3504Dvs(unsigned char* pData, int nDataLen, bool bMark, unsigned nTS, unsigned nSEQ); //����CL3504 DVS���ú�˼оƬ�ᷢ�ͷǱ�׼FUA��ʽ��RTP��
	unsigned  H264PopFrame(unsigned char** ppFrame);

private:
	bool			    m_bWaitNextPacket;//�Ƿ���Ҫ�ȴ�mark��
	unsigned char*	 m_pInternalAddr;//�ڲ�������
	unsigned		m_nFrameLen;//���ݳ���
	unsigned		m_nCurDataOffset;//��ǰ����ƫ����
	unsigned		m_nTimestamp;//ʱ���
	unsigned		m_nSeqNo;//���к�
	unsigned		m_nMaxBufferSize;//��󻺳�����С
};

#endif //_RT_SIP_STACK_FILE_H_UTIL_VIDEO_MEDIA_

