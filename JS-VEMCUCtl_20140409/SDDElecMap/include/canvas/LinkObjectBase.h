// LinkObjectBase.h: interface for the CLinkObjectBase class.
//

//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINKOBJECTBASE_H__5A42B2E7_1E6C_416B_B8CF_875F29FF3C96__INCLUDED_)
#define AFX_LINKOBJECTBASE_H__5A42B2E7_1E6C_416B_B8CF_875F29FF3C96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/*---------------------------------------------------------------------------------
	*								��̬����
	*--------------------------------------------------------------------------------

------------------
���Ӷ������͵Ĺ���
------------------	

		CLinkObjectBase * FindLinkObject(int linktype)
		����:�ҵ���Ӧ����������linktype���������Ͷ���
		����:
			linktype-��������
		����:ָ���������Ͷ����ָ��
	 

------------------
�������������ĵ�
------------------	

		PLINKKEY CLinkObjectBase::MakeOutKey()
		����:�����������������ĵ�
		����һ����ʼ������������������ĵ�

		BOOL OnEditProperties(PLINKKEY pKey)
		����:�༭һ���������������ĵ�
		����:
			pKey-ָ���������������ĵ���ָ��
		���أ��������������ĵ��Ƿ��޸�

------------
ִ����������
------------

		void Jump(HWND hwnd,PLINKKEY pKey)
		����:��ת�������ĵ�ִ�еĽ���
		����:
			pKey-ָ���������������ĵ���ָ��
			hwnd-����ĸ����ھ��


*/

//��̬���Ӷ������
class CTyBase;
class CLinkObjectBase : public CObject  
{
	DECLARE_SERIAL(CLinkObjectBase);
public:
	CLinkObjectBase(){m_pTy = NULL;}

public:
	CLinkObjectBase(int linktype,CString strname);
	virtual ~CLinkObjectBase();
protected:

public:
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual void Serialize_Ty(CArchive &ar);
	virtual CLinkObjectBase * Clone();
	void SetModifiedFlag(BOOL bl);
	void Save(CFile *file, BOOL Yn);
	void Serialize(CArchive &ar);
	virtual void Execute(UINT pos);
	virtual BOOL OnEditProperties();
	void ParamReplace(CStringList& ruleList);
	virtual void ParamReplace_Ty(CStringList& ruleList);

	CTyBase* m_pTy;		
	int m_key;				//���Ӷ��������
	char m_name[33];	//����˵��  wkey+name=Ψһ
};


typedef CTypedPtrArray<CObArray, CLinkObjectBase*> CLinkObjectArray;


#endif // !defined(AFX_LINKOBJECTBASE_H__5A42B2E7_1E6C_416B_B8CF_875F29FF3C96__INCLUDED_)
