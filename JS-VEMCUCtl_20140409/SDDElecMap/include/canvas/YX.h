#if !defined(AFX_YX_H__D20F0846_94C1_41E9_92E8_E40F23A19AB3__INCLUDED_)
#define AFX_YX_H__D20F0846_94C1_41E9_92E8_E40F23A19AB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TyBase.h"
//#include "TYTool.h"

#define YX_STRING       "YXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx"
#define YX_MINDISWIDTH   1.5
#define YX_MINDISHEIGHT  2
#define YX_FONTSIZEPERCENT .92
#define YX_FINDDOTDLLNAME "c:\\sunpac\\dll\\Finddot.dll"

// YX.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CYX window

struct Stu_YX
{
   RectStruct rect;//��Χ
   float fontwidth;//������
   float fontheight;//����߶�
   float fontjj;//������
   char ename[17];//Ӣ����
   LOGFONT lgfont;//1����
   COLORREF color1;//1��ɫ  ����:������ɫ ʸ��ͼ��ͳһɫ λͼ��͸��ɫ
   COLORREF color0;//0��ɫ  ����:������ɫ ʸ��ͼ��ͳһɫ λͼ��͸��ɫ
   COLORREF colordis;//��Ч��ɫ  ����:������ɫ ʸ��ͼ��ͳһɫ λͼ��͸��ɫ
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

class CYX : public CTyBase
{
// Construction
	DECLARE_SERIAL(CYX);//֧�����л�
public:
	Stu_YX m_yx;
	BOOL m_recalrect;//���¼��㷶Χ
	BOOL m_recalfont;//���¼��㷶Χ
	CYX(float x0=0,float y0=0,float w=30,float h=10);
	CYX(Stu_YX * yx);
	~CYX();

// Attributes
public:

// Operations
public:
	void setStatus(int status) { m_nStatus = status; }
	int  getStatus() { return m_nStatus; }

private:
	void showPickind_zero(CDC *pDC, CElecMapView *pView,CPoint pt1,CPoint pt3);
	void showPickind_one(CDC *pDC, CElecMapView *pView,CPoint pt1,CPoint pt3);
	void showPickind_two(CDC *pDC, CElecMapView *pView,CPoint pt1,CPoint pt3);
private:
	int m_nStatus;
	BOOL m_bShow;
// Implementation
public:
	virtual void SetFontProp(float height,float width,float jqwidth,BOOL pl,COLORREF color,char font[]);
	virtual BOOL Is_Net_Color_Yx();
	void GetRectFromFont();
	void DrawItText(CDC * pDC,char *s, int count, int jj, int width,int x0, int y0, COLORREF itcolor, int *x1);
	void UnRegisterAllPic();
	void RegisterAllPic();
	void DrawVec(CDC *pDC, CElecMapView *pView,CPoint pt1,CPoint pt3,char* picname);
	void DrawBmp(CDC *pDC, CElecMapView *pView,CPoint pt1,CPoint pt3,char* picname);
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

#endif // !defined(AFX_YX_H__D20F0846_94C1_41E9_92E8_E40F23A19AB3__INCLUDED_)
