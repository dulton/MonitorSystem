#ifndef _VIDEO_EXCEL_REPORT_PARSE_DEF_H_
#define _VIDEO_EXCEL_REPORT_PARSE_DEF_H_

#define			VIDOE_EXCEL_REPORT_PIPE_MAX_BUF		3600
#define			VIDOE_EXCEL_REPORT_MAX_DATA_LEN		1024
#define			VIDOE_EXCEL_REPORT_MAX_MSG_LEN		128

#define VIDEO_EXCEL_REPORT_PIPE_NAME "\\\\.\\pipe\\VIDEO_EXCEL_REPORT_PIPE"

///////////////////////////////////////////////////////////////////////
typedef struct _video_excel_report_callback_data_ 
{
	int 	nFlag;								    //�ṹ�������־
	SYSTEMTIME	tmRequest;			//time received the message from the client
	SYSTEMTIME	tmResponse;		//time sent the message to client by the server
	int 	nInBufLen;							//strInBuf �������ĳ���
	int 	nOutBufLen;						//strOutBuf �������ĳ���
	int	nRspCode;							//response code
	char	strCmdReq[VIDOE_EXCEL_REPORT_MAX_MSG_LEN];
	char	strCmdRsp[VIDOE_EXCEL_REPORT_MAX_MSG_LEN];		//��Ӧ����
	char	strInBuf[VIDOE_EXCEL_REPORT_MAX_DATA_LEN];		    //ԭʼ����
	char	strOutBuf[VIDOE_EXCEL_REPORT_MAX_DATA_LEN];	    //server��������Ӧ����
}VidoeExcelReportCbData;

typedef DWORD __stdcall VideoExcelReportPipeDataCallback(VidoeExcelReportCbData *data, void *pAddData);

#endif

