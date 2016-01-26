// SZ_SgbwLink.h: interface for the CSZ_SgbwLink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SZ_SGBWLINK_H__DF32DB81_3C0A_11D6_A5ED_0080C8F60823__INCLUDED_)
#define AFX_SZ_SGBWLINK_H__DF32DB81_3C0A_11D6_A5ED_0080C8F60823__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LinkObjectBase.h"
#define SZ_SGBW_LINENUM								32			//�¹ʱ�����������

#pragma pack(push,before_SZ_S_SGBWLINEBASE,1)
typedef struct
{
	BYTE TdNo;										//ͨ����
	char DotName[17];								//����
	float Prop;										//����
	BYTE Enum;										//С��λ��
	COLORREF Color;									//��ɫ
	BYTE Zbgt;										//�Աջ��ǹ�ͨ��1�Ագ�2��ͨ
	BYTE UorI;										//�������ǵ�ѹ��1��ѹ��2����
}SZ_S_SGBWLINEBASE;									//�¹ʱ������������ṹ
#pragma pack(pop,before_SZ_S_SGBWLINEBASE,8)

#pragma pack(push,before_SZ_S_SGBWMAINBASE,1)
typedef struct
{
	BOOL Zbgt;										//�Ƿ����Աչ�ͨ��ʽ
	BOOL HaveUandI;									//���޵�����ѹ
	char RtuName[17];								//��Ԫ����
	float MaxU;										//��ѹ���ֵ
	float MinU;										//��ѹ��Сֵ
	float MaxI;										//�������ֵ
	float MinI;										//������Сֵ
}SZ_S_SGBWMAININFO;									//�¹ʱ�������Ϣ�ṹ
#pragma pack(pop,before_SZ_S_SGBWMAINBASE,8)

class CSZ_SgbwLink : public CLinkObjectBase  
{
	DECLARE_SERIAL(CSZ_SgbwLink);
public:
	CSZ_SgbwLink();
public:
	CSZ_SgbwLink(CString name);
	virtual void Serialize_Ty(CArchive &ar);
	virtual BOOL OnEditProperties();
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual ~CSZ_SgbwLink();
	virtual void ParamReplace_Ty(CStringList& ruleList);

private:
	SZ_S_SGBWMAININFO m_sMainInfo;
	SZ_S_SGBWLINEBASE m_sLineInfo[SZ_SGBW_LINENUM];
	int m_nLineCount;
};

#endif // !defined(AFX_SZ_SGBWLINK_H__DF32DB81_3C0A_11D6_A5ED_0080C8F60823__INCLUDED_)
