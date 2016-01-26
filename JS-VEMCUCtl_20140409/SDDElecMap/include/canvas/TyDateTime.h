#if !defined(AFX_TyDateTime_H__3D4F5736_CB3C_4C8A_B176_8EF5D05CE364__INCLUDED_)
#define AFX_TyDateTime_H__3D4F5736_CB3C_4C8A_B176_8EF5D05CE364__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TYBase.h"

#define TyDateTime_MINDISWIDTH   1.5
#define TyDateTime_MINDISHEIGHT  2

// TyDateTime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTyDateTime window
struct Stu_TyDateTime
{
   RectStruct rect;//��Χ
   float fontwidth;//������
   float fontheight;//����߶�
   float fontjj;//������
   LOGFONT lgfont;//����
   COLORREF itcolor;//��ʾ��ɫ;
   BYTE datekind;
   /*
   0:NULL
   1:2002-3-22
	 2002/3/22
	 3/22/2002
	 3.22.2002
	 02.3.22
	 2002��3��
   7:2002��3��22��
*/
   BYTE timekind;
   /*
   0:NULL
   1:16:13:26
	16:13
	16ʱ13��26��
   4:16ʱ13��*/
   BYTE diskind;//0����ǰ  1ʱ��ǰ
};


class CTyDateTime : public CTyBase
{
// Construction
	DECLARE_SERIAL(CTyDateTime);//֧�����л�
public:
	Stu_TyDateTime m_TyDateTime;
	BYTE bMonth,bDay,bHour,bMin,bSec;
	WORD wYear,wMSec;
	CString disstr;
	BOOL m_recalrect;//���¼��㷶Χ
	BOOL m_recalfont;//���¼��㷶Χ
	CTyDateTime(float x0=0,float y0=0,float fw=5,float fh=10,float fjj=0);
	CTyDateTime(Stu_TyDateTime * TyDateTime);
	virtual ~CTyDateTime();

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual void SetFontProp(float height,float width,float jqwidth,BOOL pl,COLORREF color,char font[]);
	virtual void Set_Ty_Color(COLORREF color,CElecMapView * pView);
	void TransDateTimeToStr();
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

	// Generated message map functions
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TyDateTime_H__3D4F5736_CB3C_4C8A_B176_8EF5D05CE364__INCLUDED_)
