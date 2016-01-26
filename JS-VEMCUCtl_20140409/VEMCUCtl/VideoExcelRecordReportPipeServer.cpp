// Module Name: VideoExcelRecordReportServer.cpp

#include "StdAfx.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>

#include "VideoExcelRecordReportPipeServer.h"

static HANDLE 	g_hVideoExcelRecordReportPipeHandle = INVALID_HANDLE_VALUE;
static HANDLE 	g_hVideoExcelRecordReportPipeRead = INVALID_HANDLE_VALUE;
static HANDLE 	g_hVideoExcelRecordReportPipeWrite = INVALID_HANDLE_VALUE;
static HANDLE 	g_hVideoExcelRecordReportPipeExit = INVALID_HANDLE_VALUE;

volatile bool g_bVideoExcelRecordReportPipeConnected = false;

void StopVideoExcelRecordReportPipe()
{
	try
	{
		if (g_hVideoExcelRecordReportPipeExit != NULL)
		{
			SetEvent(g_hVideoExcelRecordReportPipeExit);
		}
	}
	catch(...)
	{

	}
}

BOOL StartVideoExcelRecordReportPipe()
{
	try
	{
		HANDLE ThreadHandle = NULL;
		unsigned int ThreadId = 0;

		g_bVideoExcelRecordReportPipeConnected = false;

		do 
		{
			g_hVideoExcelRecordReportPipeRead = CreateEvent(NULL, TRUE, FALSE, NULL);
			if (g_hVideoExcelRecordReportPipeRead == NULL)
			{
				TRACE("CreateEvent for read pipe failed with error %d\n",GetLastError());
				break;
			}

			g_hVideoExcelRecordReportPipeWrite = CreateEvent(NULL, TRUE, FALSE, NULL);
			if (g_hVideoExcelRecordReportPipeWrite == NULL)
			{
				TRACE("CreateEvent for write pipe failed with error %d\n",GetLastError());
				break;
			}

			g_hVideoExcelRecordReportPipeExit = CreateEvent(NULL, TRUE, FALSE, NULL);
			if (g_hVideoExcelRecordReportPipeExit == NULL)
			{
				TRACE("CreateEvent for pipe exit handle failed with error %d\n",GetLastError());
				break;
			}

			ThreadHandle = (HANDLE)_beginthreadex(NULL, 0, VideoExcelRecordReportPipeInstanceProc,NULL, 0, &ThreadId);
			if (ThreadHandle == NULL)
			{
				TRACE("CreateThread failed with error %\n",GetLastError());
				break;
			}

			CloseHandle(ThreadHandle);
			ThreadHandle = NULL;

			return TRUE;

		} while (false);

		if (g_hVideoExcelRecordReportPipeRead != NULL)
		{
			CloseHandle(g_hVideoExcelRecordReportPipeRead);
			g_hVideoExcelRecordReportPipeRead = NULL;
		}

		if (g_hVideoExcelRecordReportPipeWrite != NULL)
		{
			CloseHandle(g_hVideoExcelRecordReportPipeWrite);
			g_hVideoExcelRecordReportPipeWrite = NULL;
		}

		if (g_hVideoExcelRecordReportPipeExit != NULL)
		{
			CloseHandle(g_hVideoExcelRecordReportPipeExit);
			g_hVideoExcelRecordReportPipeExit = NULL;
		}

		if (ThreadHandle != NULL)
		{
			CloseHandle(ThreadHandle);
			ThreadHandle = NULL;
		}

		return FALSE;
	}
	catch(...)
	{

	}
	return FALSE;
}

int VideoExcelRecordReportPipeWriteData(void *buffer, DWORD dwLen )
{
	try
	{
		OVERLAPPED Ovlap;
		memset(&Ovlap,0,sizeof(Ovlap));

		Ovlap.hEvent = g_hVideoExcelRecordReportPipeWrite;

		if (WriteFile(g_hVideoExcelRecordReportPipeHandle, buffer, dwLen , NULL, &Ovlap) == 0)
		{
			if (GetLastError() != ERROR_IO_PENDING)
			{
				TRACE("WriteFile failed with error %d\n",GetLastError());
			}
		}
		return 0;
	}
	catch(...)
	{

	}
	return -1;
}

unsigned _stdcall VideoExcelRecordReportPipeInstanceProc(void *arg)
{
	try
	{
		int i=0;
		DWORD dwResult   = 0;
		DWORD Pipe = 0;
		BOOL  bReadEvent = FALSE;

		OVERLAPPED Ovlap;
		const DWORD dwEventNum = 3;
		DWORD BytesTransferred = 0;
		HANDLE Event[dwEventNum];

		char  strReadBuf[VIDOE_EXCEL_RECORD_REPORT_PIPE_MAX_BUF];
		memset(strReadBuf,0,sizeof(strReadBuf));

		Event[0] = g_hVideoExcelRecordReportPipeRead;
		Event[1] = g_hVideoExcelRecordReportPipeWrite;
		Event[2] = g_hVideoExcelRecordReportPipeExit;

		// ���������ܵ�
		if ((g_hVideoExcelRecordReportPipeHandle = CreateNamedPipe(VIDEO_EXCEL_RECORD_REPORT_PIPE_NAME,
			PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
			PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, 1,
			VIDOE_EXCEL_RECORD_REPORT_PIPE_MAX_BUF, VIDOE_EXCEL_RECORD_REPORT_PIPE_MAX_BUF, 1000, NULL)) == INVALID_HANDLE_VALUE)
		{
			TRACE("������ƵѲ�ӱ���ܵ�%dʧ��,������:%d\n", i, GetLastError());
			return 1;
		}

		memset(&Ovlap,0,sizeof(Ovlap));
		Ovlap.hEvent = Event[0];

		// Listen for client connections using ConnectNamedPipe()
		if (ConnectNamedPipe(g_hVideoExcelRecordReportPipeHandle, &Ovlap) == 0)
		{
			if (GetLastError() != ERROR_IO_PENDING)
			{
				TRACE("ConnectNamedPipe for pipe %d failed with error %d\n", i, GetLastError());

				CloseHandle(g_hVideoExcelRecordReportPipeHandle);
				g_hVideoExcelRecordReportPipeHandle = NULL;

				CloseHandle(g_hVideoExcelRecordReportPipeRead);
				g_hVideoExcelRecordReportPipeRead = NULL;

				CloseHandle(g_hVideoExcelRecordReportPipeWrite);
				g_hVideoExcelRecordReportPipeWrite = NULL;

				CloseHandle(g_hVideoExcelRecordReportPipeExit);
				g_hVideoExcelRecordReportPipeExit = NULL;

				return 3;
			}
		}

		TRACE("Server is now running\n");

		// Read and echo data back to Named Pipe clients forever
		while(true) 
		{
			dwResult = WaitForMultipleObjects(dwEventNum, Event, FALSE, INFINITE);
			if (dwResult == WAIT_FAILED)
			{
				TRACE("WaitForMultipleObjects failed with error %d\n",GetLastError());
				g_bVideoExcelRecordReportPipeConnected = false;

				CloseHandle(g_hVideoExcelRecordReportPipeHandle);
				g_hVideoExcelRecordReportPipeHandle = NULL;

				CloseHandle(g_hVideoExcelRecordReportPipeRead);
				g_hVideoExcelRecordReportPipeRead = NULL;

				CloseHandle(g_hVideoExcelRecordReportPipeWrite);
				g_hVideoExcelRecordReportPipeWrite = NULL;

				CloseHandle(g_hVideoExcelRecordReportPipeExit);
				g_hVideoExcelRecordReportPipeExit = NULL;

				return 4;
			}

			if (dwResult == WAIT_OBJECT_0)//��
			{
				TRACE("\nReceived data or connection request!");
				bReadEvent = FALSE;
			}
			else if (dwResult == WAIT_OBJECT_0 + 1)//д
			{
				TRACE("\nWrite data!");
			}
			else //WAIT_OBJECT_2:application exit - close handle  default:error
			{
				break;
			}

			//�����¼�
			ResetEvent(Event[dwResult-WAIT_OBJECT_0]);

			// Check overlapped results, and if they fail, reestablish 
			// communication for a new client; otherwise, process read 
			// and write operations with the client
			if (GetOverlappedResult(g_hVideoExcelRecordReportPipeHandle, &Ovlap,&BytesTransferred, TRUE) == 0)
			{
				g_bVideoExcelRecordReportPipeConnected = false;

				TRACE("GetOverlapped result failed %d start over\n", GetLastError());

				if (DisconnectNamedPipe(g_hVideoExcelRecordReportPipeHandle) == 0)
				{
					TRACE("DisconnectNamedPipe failed with error %d\n",GetLastError());
					break;
				}

				if (ConnectNamedPipe(g_hVideoExcelRecordReportPipeHandle,&Ovlap) == 0)
				{
					if (GetLastError() != ERROR_IO_PENDING)
					{
						// Severe error on pipe. Close this handle forever.
						TRACE("ConnectNamedPipe for pipe %d failed with error %d\n", i, GetLastError());
						break;
					}
				}
			} 
			else
			{
				g_bVideoExcelRecordReportPipeConnected = true;

				if (!bReadEvent)//��
				{
					//�յ�����������߿ͻ������ݣ�������������
					TRACE("Received %d bytes, echo bytes back\n",BytesTransferred);

					if (ReadFile(g_hVideoExcelRecordReportPipeHandle, strReadBuf,VIDOE_EXCEL_RECORD_REPORT_PIPE_MAX_BUF, NULL, &Ovlap) == 0)
					{
						if (GetLastError() != ERROR_IO_PENDING)
						{
							TRACE("\nReadFile failed with error %d", GetLastError());
						}
					}
				}
				bReadEvent = TRUE;
			}
		}		

		g_bVideoExcelRecordReportPipeConnected = false;

		if (g_hVideoExcelRecordReportPipeHandle != NULL)
		{
			CloseHandle(g_hVideoExcelRecordReportPipeHandle);
			g_hVideoExcelRecordReportPipeHandle = NULL;
		}

		if (g_hVideoExcelRecordReportPipeRead != NULL)
		{
			CloseHandle(g_hVideoExcelRecordReportPipeRead);
			g_hVideoExcelRecordReportPipeRead = NULL;
		}

		if (g_hVideoExcelRecordReportPipeWrite != NULL)
		{
			CloseHandle(g_hVideoExcelRecordReportPipeWrite);
			g_hVideoExcelRecordReportPipeWrite = NULL;
		}

		return 10;
	}
	catch(...)
	{

	}
	return 11;
}


