#if !defined(AFX_YDX_H__0A1CA82E_C42F_47FD_A153_47E78E1FC6FC__INCLUDED_)
#define AFX_YDX_H__0A1CA82E_C42F_47FD_A153_47E78E1FC6FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// YDX.h : header file
#include "TyBase.h"
#include "TYTool.h"
//

/////////////////////////////////////////////////////////////////////////////
// CYDX window

#define YDX_STRING       "YXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx"
#define YDX_MINDISWIDTH   1.5
#define YDX_MINDISHEIGHT  2
#define YDX_FONTSIZEPERCENT .92
#define YDX_FINDDOTDLLNAME "c:\\sunpac\\dll\\Finddot.dll"


struct Stu_YDX
{
   RectStruct rect;//��Χ
   float fontwidth;
   float fontheight;
   float fontjj;
   char mainename[17];//Ӣ����
   char slaveename[17];//Ӣ����
   LOGFONT lgfont;//1����
   COLORREF color1;//1��ɫ��ͼ/���֣�
   COLORREF color0;//0��ɫ��ͼ/���֣�
   COLORREF colordis;//��Ч��ɫ��ͼ/���֣�
   char picname1[33],picname0[33],picnamedis[33];//ͼ��/����
   BYTE pickind1,pickind0,pickinddis;//
       //0 λͼ 1 ʸ��ͼ 2 ���� 
   int diskind1,diskind0,diskinddis;//��ʾ����
       //0 �� 1 ͸��ɫ 2 ͳһɫ 4 ��˸
   BYTE warn1enable;  //0->1�Ƿ񱨾�
   BYTE warn1levels; //0->1�������� //0��5s�Զ��� 1��30s�� 2�������Զ��� 3���ֶ���
   BYTE warn1kind; //0->1�������� //0λ����ͼ 1λ����˸ 2λ������
   char warn1wave[33]; //0->1��������
   BYTE warn0enable;  //1->0�Ƿ񱨾�
   BYTE warn0levels; //1->0�������� 0��5s�Զ��� 1��30s�� 2�������Զ��� 3���ֶ���
   BYTE warn0kind; //1->0�������� //0λ����ͼ 1λ����˸ 2λ������
   char warn0wave[33]; //1->0��������
   BYTE handit;//�ֶ�����
};

class CYDX : public CTyBase
{
// Construction
	DECLARE_SERIAL(CYDX);//֧�����л�
public:
	Stu_YDX m_ydx;
	BOOL m_recalrect,m_recalfont;
	CYDX(float x0=0,float y0=0,float x1=30,float y1=10);
	CYDX(Stu_YDX * ydx);
	~CYDX();

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual void SetFontProp(float height,float width,float jqwidth,BOOL pl,COLORREF color,char font[]);
	virtual BOOL Is_Net_Color_Yx();
	void DrawItText(CDC *pDC, char *s, int count, int jj, int width, int x0, int y0, COLORREF itcolor, int *x1);
	void GetRectFromFont();
	void UnRegisterAllPic();
	void RegisterAllPic();
	void DrawVec(CDC *pDC, CElecMapView *pView,CPoint pt1,CPoint pt3);
	void DrawBmp(CDC *pDC, CElecMapView *pView,CPoint pt1,CPoint pt3);
	void RefreshIt();
	void GetFontExtractWidth(CDC * pDC,CElecMapView *pView);
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
	int GetCharLen(char *schar,int maxlen,int * hzcount);
	virtual CTyBase * Clone();
	virtual void Ty_Serialize(CArchive &ar);
	virtual void Ty_Save(CFile *file, BOOL Yn);
	virtual void ParamReplace_Ty(CStringList& ruleList);




	// Generated message map functions
protected:
};


#endif // !defined(AFX_YDX_H__0A1CA82E_C42F_47FD_A153_47E78E1FC6FC__INCLUDED_)
