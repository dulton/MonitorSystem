#include "StdAfx.h"
#include "LogManager.h"
#include <stdio.h>
#include <stdarg.h>
//#include <algorithm>
#include <assert.h>

CRITICAL_SECTION g_mMutex;
//-----------------------------------------------------------------------
template<> LogManager* Singleton<LogManager>::ms_Singleton = 0;

void Convert_Data_To_Hex(char* out, int OutSize, char* in,int len)
{
	int iPos = 0;
	int iTmp = 0;

	iTmp = len*3 + (len>>4 +1)*4; //�������ɵ��ַ�����С

	if(iTmp >= OutSize)
	{
		sprintf(out, "Buffer too small: OutSize=%d inSize=%d", OutSize, len);
	}
	else
	{
		iTmp = 0;
		for (int i=0; i<len; i++)
		{
			if (0 == iTmp)
			{
				sprintf(out+iPos, "\t\t\t");
				iPos += 3;
			}
			sprintf(out+iPos, "%02X ", (unsigned char)in[i]);
			iPos += 3;
			iTmp = (i+1)%16;
			if (0 == iTmp && i < len-1)
			{
				sprintf(out+iPos, "\n");
				iPos += 1;
			}
		}
		out[iPos] = '\0';
	}
}
LogManager* LogManager::getSingletonPtr(void)
{
	return ms_Singleton;
}
LogManager& LogManager::getSingleton(void)
{  
	assert(ms_Singleton);  
	return (*ms_Singleton);  
}
//-----------------------------------------------------------------------
LogManager::LogManager()
{
	InitializeCriticalSection(&mMutex);
	InitializeCriticalSection(&g_mMutex);

	mDefaultLog = NULL;
	m_iLogFileSeq = 0;
	m_iLogFileSize = 200;//��־�����С
	m_iLogFileSaveTime = 5;//��־��������
}
//-----------------------------------------------------------------------
LogManager::~LogManager()
{
	DeleteCriticalSection(&mMutex);

	// Destroy all logs
	LogList::iterator i;
	for (i = mLogs.begin(); i != mLogs.end(); ++i)
	{
		delete i->second;
	}
}
//-----------------------------------------------------------------------
//�״δ�����־�ļ�
Log* LogManager::createLog(const std::string& name, bool defaultLog, bool debuggerOutput, 
	bool suppressFileOutput)
{

	//EnterCriticalSection(&mMutex);
	m_strFileName = name;
	
	//�ж��Ƿ�����ļ����������Ѿ�����,��Ҫɾ����
	for(LogList::iterator it = mLogs.begin();it != mLogs.end();)
	{
		time_t curtime = time(0);
		time_t lasttime = curtime-m_iLogFileSaveTime*24*3600;
		struct tm* pm=localtime(&lasttime);
		if (pm == NULL)
		{
			break;
		}
		char szLastTime[80]={0};
		
		strftime(szLastTime,80,"%Y-%m-%d",pm);
		std::string strOldName = it->first;
		std::string strTmpName = strOldName;//�ݴ�һ��׼��ɾ�����ļ���
		strOldName = strOldName.substr(name.length(),strlen("YYYY-MM-dd"));//ȡ��������
		if (strOldName.compare(szLastTime) <= 0)
		{
			//��־�ļ�����ɾ��
			if (mDefaultLog != it->second)
			{
				if(mLogs[it->first])
				{
					delete it->second;
					mLogs[it->first] = NULL;
				}
				
			
				int i = remove(strTmpName.c_str());
				{
					if (i == 0)
					{
						//printf("�ɹ�ɾ����%s\n",strTmpName.c_str());
						it = mLogs.erase(it);
					}
					else
					{
						++it;
						perror("remove");
						printf("\tɾ��%sʧ��:%d:%s\n",strTmpName.c_str(),GetLastError(),strerror(GetLastError()));
					}
				}
				//break;
			}
			else
			{
				++it;
			}
		}
		else
		{
			++it;
		}
	}
	
	Log* newLog = NULL;
	if (mLogs.size() >= 1)//�Ѿ�����־�ļ�
	{
		
			//��Ҫ�����µ���־
			time_t curtime = time(0);
			struct tm* pm=localtime(&curtime);
			if (pm == NULL)
			{
				//LeaveCriticalSection(&mMutex);
				return NULL;
			}
			char szCurTime[80]={0};
			if(pm != NULL)
				strftime(szCurTime,80,"%Y-%m-%d",pm);
			char szNewFileName[512] ={0};
			sprintf(szNewFileName,"%s%s %d.%d.%d",name.c_str(),szCurTime,pm->tm_hour,pm->tm_min,pm->tm_sec);
			newLog = new Log(szNewFileName, debuggerOutput, suppressFileOutput);
			//printf("new log=%x\n",newLog);
			//printf("file name=%s\n",szNewFileName);
			if(!mDefaultLog || defaultLog)
			{
				mDefaultLog = newLog;
			}

			mLogs.insert(LogList::value_type(szNewFileName, newLog));
	}
	else
	{
		//��һ��������־�ļ�
		time_t curtime = time(0);
		struct tm* pm=localtime(&curtime);
		if (pm == NULL)
		{
			//LeaveCriticalSection(&mMutex);
			return NULL;
		}
		char szCurTime[80]={0};
		strftime(szCurTime,80,"%Y-%m-%d",pm);
		char szNewFileName[512] ={0};
		sprintf(szNewFileName,"%s%s %d.%d.%d",name.c_str(),szCurTime,pm->tm_hour,pm->tm_min,pm->tm_sec);
		newLog = new Log(szNewFileName, debuggerOutput, suppressFileOutput);

		if(!mDefaultLog || defaultLog)
		{
			mDefaultLog = newLog;
		}

		mLogs.insert(LogList::value_type(szNewFileName, newLog));
	}
	
	//LeaveCriticalSection(&mMutex);

	return newLog;
}
//-----------------------------------------------------------------------
Log* LogManager::getDefaultLog()
{
	return mDefaultLog;
}
//-----------------------------------------------------------------------
Log* LogManager::setDefaultLog(Log* newLog)
{
	Log* oldLog = mDefaultLog;
	mDefaultLog = newLog;
	return oldLog;
}
//-----------------------------------------------------------------------
//��ȡ��־�ļ���
Log* LogManager::getLog(const std::string& name)
{
	LogList::iterator i = mLogs.find(name);
	if (i != mLogs.end())
		return i->second;
	else
		return NULL;
}
//-----------------------------------------------------------------------
void LogManager::destroyLog(const std::string& name)
{
	EnterCriticalSection(&mMutex);
	LogList::iterator i = mLogs.find(name);
	if (i != mLogs.end())
	{
		if (mDefaultLog == i->second)
		{
			mDefaultLog = 0;
		}
		delete i->second;
		mLogs.erase(i);
	}

	// Set another default log if this one removed
	if (!mDefaultLog && !mLogs.empty())
	{
		mDefaultLog = mLogs.begin()->second;
	}
	LeaveCriticalSection(&mMutex);
}
//-----------------------------------------------------------------------
void LogManager::destroyLog(Log* log)
{
	destroyLog(log->getName());
}
//-----------------------------------------------------------------------
void LogManager::logMessage(const std::string& message, LogMessageLevel lml, bool maskDebug)
{
	if (mDefaultLog)
	{

	EnterCriticalSection(&mMutex);

		CreateNewLog();
		mDefaultLog->logMessage(message, lml, maskDebug);

		LeaveCriticalSection(&mMutex);

	}
}
//-----------------------------------------------------------------------
void LogManager::setLogDetail(LoggingLevel ll)
{
	if (mDefaultLog)
	{
		mDefaultLog->setLogDetail(ll);
	}
}
//��ȡ��־�ļ�����
unsigned int LogManager::getLogNum() const
{
	return mLogs.size();
}

//��ǰ��־�ļ���С�Ѿ��������ޣ������µ���־�ļ�
void LogManager::CreateNewLog()
{
	std::string strLogFileName = m_strFileName ;
	std::string strOldName=this->getDefaultLog()->getName();
	//�жϵ�ǰ��־�ļ���С�Ƿ񳬹�����
	int filesize = 0;
	HANDLE handle = CreateFile(strOldName.c_str(), FILE_READ_EA, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	if (handle != INVALID_HANDLE_VALUE)
	{
		filesize = GetFileSize(handle, NULL);
		CloseHandle(handle);
	}
	if (filesize>= this->GetLogFileSize()*1024*1024)
	{
		//��Ҫ�����µ���־
		this->createLog(strLogFileName,true);
	}
}
