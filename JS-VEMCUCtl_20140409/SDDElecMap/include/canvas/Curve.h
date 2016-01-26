// Curve.h: interface for the CCurve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURVE_H__F53ED881_D908_11D5_BFC5_0050BABDFD68__INCLUDED_)
#define AFX_CURVE_H__F53ED881_D908_11D5_BFC5_0050BABDFD68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LinkObjectBase.h"

typedef struct
{
	char ename[17];                  //Ӣ����
	char cname[33];                  //������
	float scale;                     //����
	int precission;                  //С������
	COLORREF color;                  //������ɫ
	int width;                       //���߿��
	int reference;                   //��������ϵ
	BOOL compare;                    //�Ƿ���ƻ����߱Ƚ�
	int swing;                       //��ֵ���
}curveinfo;

typedef struct
{
	char curvegroupname[33];           //����������
	int curvegroupstyle;               //��������
	int coordinatestyle;               //����ϵ���
	int curstyle;                      //������ߵķ��
	int firstcount;                    //��һ����������
	int secondcount;                   //�ڶ�����������
//	char firstname[33];                //��һ����������
	float firstleftmin;                //��һ����������������Сֵ
	float firstleftmax;                //��һ�����������������ֵ
	float firstleftinterval;           //��һ����������������
	char firstleftunit[9];             //��һ�������������굥λ
	float firstrightmin;               //��һ����������������Сֵ
	float firstrightmax;               //��һ�����������������ֵ
	float firstrightinterval;          //��һ����������������
	char firstrightunit[9];            //��һ�������������굥λ
//	char secondname[33];               //�ڶ�����������
	float secondleftmin;               //�ڶ�����������������Сֵ
	float secondleftmax;               //�ڶ������������������ֵ
	float secondleftinterval;          //�ڶ�����������������
	char secondleftunit[9];            //�ڶ��������������굥λ
	float secondrightmin;              //�ڶ�����������������Сֵ
	float secondrightmax;              //�ڶ������������������ֵ
	float secondrightinterval;         //�ڶ�����������������
	char secondrightunit[9];           //�ڶ��������������굥λ
	curveinfo firstinfolist[8];        //��һ��������Ϣ����
	curveinfo secondinfolist[8];       //�ڶ���������Ϣ����
} curvegroupinfo;

struct CURVEEXTINFO
{
	BYTE flag;
	float maxValue;
	float minValue;
	int color;//������ɫ
	int mincolor;//������ɫ
	int tpye;
	float width;
};

class CCurve : public CLinkObjectBase  
{
	DECLARE_SERIAL(CCurve);
public:	
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual void Serialize_Ty(CArchive &ar);
	BOOL OnEditProperties();
	CCurve();
	virtual ~CCurve();
	virtual void ParamReplace_Ty(CStringList& ruleList);


	curvegroupinfo m_curvegroupinfo;

	
protected:	
private:
	CURVEEXTINFO m_CurveExtInfo[2];
	void LoadExt(CString name);
	void SaveExt(CString name, int bFlag);
};

#endif // !defined(AFX_CURVE_H__F53ED881_D908_11D5_BFC5_0050BABDFD68__INCLUDED_)
