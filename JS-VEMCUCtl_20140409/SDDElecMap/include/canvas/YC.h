#if !defined(AFX_YC_H__3D4F5736_CB3C_4C8A_B176_8EF5D05CE364__INCLUDED_)
#define AFX_YC_H__3D4F5736_CB3C_4C8A_B176_8EF5D05CE364__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "canvas/TYBase.h"
//#include "TYTool.h"

#define YC_STRING       "YCXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx"
#define YC_MINDISWIDTH   1.5
#define YC_MINDISHEIGHT  2
#define YC_FINDDOTDLLNAME "c:\\sunpac\\dll\\Finddot.dll"

// YC.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CYC window
struct Stu_YC
{
   RectStruct rect;//��Χ
   float fontwidth;//������
   float fontheight;//����߶�
   float fontjj;//������
   float hintdis;
   float unitdis;
   char ename[17];//Ӣ����
   int digitlength;//�����ܳ���
   char hint[33];//��ʾ
   char unit[17];//��λ
   LOGFONT lgfont;//����
   COLORREF hintcolor;//��ʾ��ɫ;
   COLORREF unitcolor;//��λ��ɫ
   COLORREF levelupcolor;//Խ������ɫ
   COLORREF leveldowncolor;//Խ������ɫ
   COLORREF normalcolor;//������ɫ
   COLORREF disablecolor;//��Ч��ɫ
   BYTE warnupenable;  //Խ�����Ƿ񱨾�
   BYTE warnuplevels; //Խ���ޱ������� //0��5s�Զ��� 1��30s�� 2�������Զ��� 3���ֶ���
   BYTE warnupkind; //Խ���ޱ������� //0λ����ͼ 1λ����˸ 2λ������
   char warnupwave[33]; //Խ���ޱ�������
   BYTE warndownenable;  //Խ�����Ƿ񱨾�
   BYTE warndownlevels; //Խ���ޱ������� 0��5s�Զ��� 1��30s�� 2�������Զ��� 3���ֶ���
   BYTE warndownkind; //Խ���ޱ������� //0λ����ͼ 1λ����˸ 2λ������
   char warndownwave[33]; //Խ���ޱ�������
   BYTE hintenable;//�Ƿ�����ʾ
};


class CYC : public CTyBase
{
// Construction
	DECLARE_SERIAL(CYC);//֧�����л�
public:
	Stu_YC m_yc;
	BOOL m_recalrect;//���¼��㷶Χ
	BOOL m_recalfont;//���¼��㷶Χ
	CYC(float x0=0,float y0=0,float fw=5,float fh=10,float fjj=0);
	CYC(Stu_YC * yc);
	virtual ~CYC();

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual void SetFontProp(float height,float width,float jqwidth,BOOL pl,COLORREF color,char font[]);
	virtual void Set_Ty_Color(COLORREF color,CElecMapView * pView=NULL);
	virtual void DrawText(CDC * pDC,char *s, int count, int jj, int width,int x0, int y0, COLORREF itcolor, int *x1);
	void GetRectFromFont();
	void RefreshIt();
	void GetFontExtractWidth(CDC *pDC,CElecMapView *pView);
	virtual int GetHandleCount();
	virtual PointStruct GetHandle(int nHandle);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual BOOL IntersectRect(float x0, float y0, float x1, float y1);
	virtual DRAW_TY GetTyType();
	virtual void GetRect(float *minX, float *minY, float *maxX, float *maxY);
	virtual void Ty_Move(float xLen, float yLen,CElecMapView * pView);
	virtual void DrawDC(CDC *pDC, CElecMapView *pView);
	virtual void Ty_MoveHandleTo(int nHandle, PointStruct point, CElecMapView *pView,UINT nFlags);
	virtual BOOL PointInObj(float x, float y,float errRange);
	virtual void OnEditProperties(CElecMapView * pView=NULL);
	int  GetCharLen(char *schar,int maxlen,int * hzcount);
	virtual CTyBase * Clone();
	virtual void Ty_Serialize(CArchive &ar);
	virtual void Ty_Save(CFile *file, BOOL Yn);
	virtual void ParamReplace_Ty(CStringList& ruleList);

	// Generated message map functions
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YC_H__3D4F5736_CB3C_4C8A_B176_8EF5D05CE364__INCLUDED_)
