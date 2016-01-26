#pragma once

#include "tybase.h"

#define YW_DRAW_DOWNUP				0
#define YW_DRAW_UPDOWN				1
#define YW_DRAW_LEFTRIGHT			2
#define YW_DRAW_RIGHTLEFT			3

struct S_TYYCYW
{
	float x0;
	float y0;
	float x1;
	float y1;
	float max;
	float min;
	BYTE drawtype;//0:��������1:��������2:��������3:��������
	char Ename[17];
	COLORREF Color;
	COLORREF DisableColor;
	COLORREF HiLevelColor;
	COLORREF LwLevelColor;
};

class CTy_YcYw :
	public CTyBase
{
	DECLARE_SERIAL(CTy_YcYw);//֧�����л�
public:
	CTy_YcYw(void);
	CTy_YcYw(float x0,float y0,float x1,float y1,char* Ename=NULL);
	CTy_YcYw(S_TYYCYW newVal);
	virtual ~CTy_YcYw(void);
	virtual void OnEditProperties(CElecMapView * pView=NULL);
	virtual DRAW_TY GetTyType();
	virtual void Ty_Serialize(CArchive &ar);
	virtual void Ty_Save(CFile *file, BOOL Yn);
	virtual void Ty_MoveHandleTo(int nHandle, PointStruct point, CElecMapView *pView,UINT nFlags=0);
	virtual void Ty_Move(float xLen, float yLen,CElecMapView * pView=NULL);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual PointStruct GetHandle(int nHandle);
	virtual int GetHandleCount();
	virtual BOOL PointInObj(float x, float y,float errRange);
	virtual BOOL IntersectRect(float x0, float y0, float x1, float y1);
	virtual CTyBase * Clone();
	virtual void GetRect(float *minX, float *minY, float *maxX, float *maxY);
	virtual void DrawDC(CDC *pDC, CElecMapView *pView);
	virtual void ParamReplace_Ty(CStringList& ruleList);

private:
	S_TYYCYW m_para;
};
