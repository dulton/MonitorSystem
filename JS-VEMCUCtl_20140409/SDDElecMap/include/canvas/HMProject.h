// HMProject.h: interface for the CHMProject class.
//
//	void Save(void);
//		������	���滭�湤�̶���
//	void Load(void);
//		������	װ�ػ��湤�̶���
//	LPCSTR GetMainHMName(void);	
//		������	��ȡ����������
//	int SetMainHMName(LPCSTR strname);
//		������	��������������
//		����		>=0 �����������ڻ�������е����	<0 �û��治����
//	BOOL DeleteHM(LPCSTR strname);
//		������	ɾ������
//	BOOL SaveHM(LPCSTR hmname);
//		������	���滭�� hmname
//	BOOL OpenHM(LPCSTR strname,LPCSTR layername=NULL);
//		������	�򿪻���strname�Ļ����layername
//	void UpdateAllHMLayer(void);
//		������	�������οؼ����������µĻ������Ϣ
//	void ActiveHM(LPCSTR strname);
//		������	�����strname
//	BOOL ModifyHMprop(LPCSTR strname,tagHMID* pHMID);
//		������	�޸Ļ���strname����
// 	void AddHMLayer(LPCSTR strName,tagHMLayerID*pLayer);
//		������	���ӻ���strname�Ļ����
//	void DeleteHMLayer(LPCSTR pHM,LPCSTR pLayer);
//		������	ɾ������strname�Ļ����pLayer
//	int FindHMLayerID(LPCSTR pHM,LPCSTR pLayer);
//		������	���һ���strname�еĻ����pLayer�������ڸû����е�λ��
//	void SetHMLayer(LPCSTR pHM,LPCSTR pLayer, tagHMLayerID *pLayerID);
//		������	�޸Ļ���strname�Ļ����pLayer������
//	tagHMLayerID * GetHMLayerID(LPCSTR pHM,LPCSTR pLayer);
//		������	��ȡ����strname�еĻ����pLayer������
//  void MovePre(LPCSTR hmname,LPCSTR layername=NULL)
//		������	����hmname�����layername�����ƶ�һ��
//  void MoveNext(LPCSTR hmname,LPCSTR layername=NULL)
//		������	����hmname�����layername�����ƶ�һ��
//	BOOL Get_HmLayer_Names(LPCSTR hmname,CStringList& layerList);
//		������	��ȡ����hmname�����л��������


//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HMPROJECT_H__1F81F7E1_0762_43B4_879B_0DA4F3621537__INCLUDED_)
#define AFX_HMPROJECT_H__1F81F7E1_0762_43B4_879B_0DA4F3621537__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <hash_map>
#include <map>
using namespace std;
using namespace stdext;
#include "gloable/DataStyle.h"
class CHuaMian;
class CWorkspaceBar;
class CTyHMProxyProp;

class CHMProject : public CObject  
{
private:
	//�����ַ����Ƿ����ֶ�strName
	BOOL HitTestSectionName(LPCSTR strSection,LPCSTR strName);
	//��ջ�����Ϣ��
	void InitMemory(void);
	//����str�Ƿ��Ƕ�����
	BOOL HitTestSectionID(LPCSTR str);
	//��ȡ��������Ϣ
	BOOL ReadMainHuaMian(CStdioFile* pfile);
	//��ȡstrSection������strKey�ؽ��ʰ������ı���Ϣ
	BOOL ReadString(CStdioFile *pfile,LPCSTR strSection,LPCSTR strKey, LPSTR buffer,int bufsize);
	//�Ѷ�ָ���Ƶ�strSection������ʼ��
	BOOL SeekSection(CStdioFile *pfile,LPCSTR strSection);
	//��ȡϵͳ�а��������л�����Ϣ
	BOOL ReadHuaMianList(CStdioFile* pfile);
	//����ϵͳ�а��������л�����Ϣ
	BOOL WriteHuaMianList(CStdioFile* pfile);
	//������������Ϣ
	BOOL WriteProjectSection(CStdioFile *pfile);

protected:
	BOOL m_modifyflag;
	BOOL ReadHuaMianFileHead(LPCSTR filepath,tagHMID* pHMID);
	BOOL CloseHM(LPCSTR strname);
	//��ȡ��������Ļ������Ϣ
	BOOL ReadHMLayer(void);
	
	BOOL SaveFile(LPCSTR filepath);
	BOOL LoadFile(LPCSTR filepath);
	tagHMIDList* GetHuaMianNameList(void);
	tagHMIDList m_HMIDList;				//ϵͳ�����Ļ�����Ϣ��
	CString  m_strMainHM;					//����������
	
public:
	friend class CWorkspaceBar;
	friend class CTyHMProxyProp;

public:
	//���Ըû����Ƿ��Ѿ���
	BOOL HitTestOnline(LPCSTR strname);
	BOOL Get_HmLayer_Names(LPCSTR hmname,CStringArray& layerList);
	void SaveHM(LPCSTR hmname);
	void MoveNext(LPCSTR hmname,LPCSTR layername=NULL);
	void MovePre(LPCSTR hmname,LPCSTR layername=NULL);
	tagHMLayerID * GetHMLayerID(LPCSTR pHM,LPCSTR pLayer);
	void DeleteHMLayer(LPCSTR pHM,LPCSTR pLayer);
	int FindHMLayerID(LPCSTR pHM,LPCSTR pLayer);
	void SetHMLayer(LPCSTR pHM,LPCSTR pLayer, tagHMLayerID *pLayerID);
	void AddHMLayer(LPCSTR strName,tagHMLayerID*pLayer);
	BOOL IsModified();

	//�޸Ļ���strname����
	BOOL ModifyHMprop(LPCSTR strname,tagHMID* pHMID);
	tagHMID * FindHMID(LPCSTR strname);
	BOOL AddHuaMian(tagHMID *pHMID);
	void SetModifiedFlag(BOOL bModified=TRUE);
	void UpdateAllHMLayer(void);
	void ActiveHM(LPCSTR strname);
	BOOL DeleteHM(LPCSTR strname);
	BOOL OpenHM(BOOL changeScale,LPCSTR strname,LPCSTR layername=NULL);
	CHuaMian * GetHMObject(LPCSTR strname);
	CHuaMian*  GetHMObjectByID(tagHMID* pHMID);
	int SetMainHMName(LPCSTR strname);
	LPCSTR GetMainHMName(void);
	void Save(void);
	void Load(void);

	// ��ȡϵͳ���ڱ༭�Ļ������Ŀ
	int GetOpenHmCount(void);
	CString m_ComputerName;
	CString GetActiveComputer();


private:
	CHMProject();
	CHMProject(const CHMProject&);
	CHMProject& operator= (const CHMProject&);
	virtual ~CHMProject();
	static CHMProject* m_pInstance;
	class CReleaseObj
	{
	public:
		~CReleaseObj()
		{
			if (CHMProject::getInstance())
				delete CHMProject::m_pInstance;
		}
	};
	static CReleaseObj obj;
	std::map<CString,CHuaMian*> map_IDHuamian;
	CHuaMian* m_pCurActiveHM;
public:
	// ��ȡ����ʵ��
	static CHMProject* getInstance();
	CHuaMian* getCurActiveHuamianInstance();
	void      setCurActiveHuamianInstance(CHuaMian* pHMInstance);

	//@param:  pRealData   struct pointer
	//		   nCount      data count
	BOOL	updateEntityInAHuamian( char *pRealData, int nCount );
};

//extern CHMProject G_HMProject;		//���湤�̶���

#endif // !defined(AFX_HMPROJECT_H__1F81F7E1_0762_43B4_879B_0DA4F3621537__INCLUDED_)
