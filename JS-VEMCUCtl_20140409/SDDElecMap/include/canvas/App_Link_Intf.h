#pragma once
#include "tybase.h"
#include "LinkObjectBase.h"


class CLinkTxtFile :
	public CLinkObjectBase
{
	DECLARE_SERIAL(CLinkTxtFile);
private:
	
public:
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual BOOL OnEditProperties();
	virtual void Serialize_Ty(CArchive &ar);
	CLinkTxtFile(CString strname);
	CLinkTxtFile(void);

	~CLinkTxtFile(void);
};


class CLinkWebShot :
	public CLinkObjectBase
{
	DECLARE_SERIAL(CLinkWebShot);
private:
	DWORD m_webIP;					//web��վ��ַ
	DWORD m_ServerIP;				//�м̷�������ַ
	int		m_ServerPort;			//���ƶ˿ں�
	DWORD m_GroupIP;				//�鲥��ַ
	int  m_GroupPort;				//�鲥�˿�
	int  m_unitID;					//���վ�����ID��
  char m_unitName[33];		//���վ������
	int  m_shotID;					//�����ID��
	char m_shotName[33];		//���������

	void SetDefaultProp();
public:
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual BOOL OnEditProperties();
	virtual void Serialize_Ty(CArchive &ar);
	CLinkWebShot(CString strname,DWORD webIP,DWORD serverIP,DWORD serverPort,DWORD groupIP,DWORD groupPort,int unitID,CString unitName);
	CLinkWebShot(void);

	~CLinkWebShot(void);
};
