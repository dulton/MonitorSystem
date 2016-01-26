// JDJH.h: interface for the CLine class.
//  �򵥼�����
//
//
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JDJH_H__6058180F_FC99_408A_BB0E_FB47FEF9155A__INCLUDED_)
#define AFX_JDJH_H__6058180F_FC99_408A_BB0E_FB47FEF9155A__INCLUDED_
#define YCMAXCURVE 8
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "canvas/tybase.h"
#include "canvas/McCurveData.h"
#include "dialog/YMcCurvePage2.h"
#include "dialog/YcCurveDialog.h"

class CHMLayer;

//����
class CLine : public CTyBase  
{
private:
	void SetDefaultProp(CElecMapView * pView);
	DECLARE_SERIAL(CLine);
	CLine(){};

public:
	CLine(float x0,float y0,float x1,float y1, LOGPEN *pLogPen,int vId=0,CHMLayer* pLayer=NULL);
	virtual ~CLine();

public:
	virtual void DrawRect(CDC *pDC,int orgX,int orgY,float offsetX, float offsetY, float scaleX, float scaleY, COLORREF ReplaceColor,COLORREF ToColor, BOOL bReplace = TRUE);
	virtual void Set_Line_Width(int width,CElecMapView * pView = NULL);
	virtual void Set_Ty_Color(COLORREF color,CElecMapView * pView = NULL);
	virtual BOOL Is_Net_Color_Vector();
	virtual void OnEditProperties(CElecMapView * pView = NULL);
	virtual DRAW_TY GetTyType();
	virtual void Ty_Serialize(CArchive &ar);
	virtual void Ty_Save(CFile *file, BOOL Yn);
	virtual void Ty_MoveHandleTo(int nHandle, PointStruct point, CElecMapView *pView,UINT nFlags = 0);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual PointStruct GetHandle(int nHandle);
	virtual int GetHandleCount();
	virtual BOOL PointInObj(float x, float y,float errRange);
	virtual BOOL IntersectRect(float x0, float y0, float x1, float y1);
	virtual CTyBase * Clone();
	virtual void GetRect(float *minX, float *minY, float *maxX, float *maxY);
	virtual void DrawDC(CDC *pDC, CElecMapView *pView);
	virtual void Ty_Move(float xLen, float yLen,CElecMapView * pView = NULL);

public:
	float m_x0,m_y0,m_x1,m_y1;	//ֱ�ߵ������յ�
	LOGPEN m_logpen;
};

//����
class CXLine : public CTyBase  
{
private:
	void SetDefaultProp(CElecMapView *pView);
	DECLARE_SERIAL(CXLine);
	CXLine(){};

public:
	CXLine(float x0,float y0,float x1,float y1,COLORREF Color1, COLORREF Color2, BOOL blTranslate,int nWidth, int Type[4],int vId=0,CHMLayer* pLayer=NULL);
	virtual ~CXLine();

public:
	virtual void Set_Line_Width(int width,CElecMapView * pView=NULL);
	virtual BOOL Is_Net_Color_Vector();
	virtual void GetRect(float *minX, float *minY, float *maxX, float *maxY);
	virtual CTyBase * Clone();
	virtual BOOL IntersectRect(float x0, float y0, float x1, float y1);
	virtual BOOL PointInObj(float x, float y,float errRange);
	virtual void OnEditProperties(CElecMapView * pView=NULL);
	virtual DRAW_TY GetTyType();
	virtual void Ty_Serialize(CArchive &ar);
	virtual void Ty_Save(CFile *file, BOOL Yn);
	virtual void Ty_Move(float xLen, float yLen,CElecMapView * pView);
	virtual void Ty_MoveHandleTo(int nHandle, PointStruct point, CElecMapView *pView,UINT nFlags=0);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual int GetHandleCount();
	virtual PointStruct GetHandle(int nHandle);
	virtual void DrawDC(CDC *pDC, CElecMapView *pView);

public:
	float m_x0,m_y0,m_x1,m_y1;	//ֱ�ߵ������յ�
	int  m_Type[4];							//�������߶εĿ��
	COLORREF m_color1,m_color2; //������ɫ
	int m_iWidth;							//���߿��
	BOOL m_blTranslate;				//��϶�Ƿ�͸��
};


//����
class CRectangle : public CTyBase  
{
private:
	void SetDefaultProp(CElecMapView *pView);
	DECLARE_SERIAL(CRectangle);
	
	CRectangle(){};

public:
	enum RECT_TYPE
	{
		rtRect=0,
		rtRoundRect,
		rtEllipse
	};

	CRectangle(float x0,float y0,float x1,float y1, LOGPEN *pLogPen,BOOL blFill,COLORREF fillcolor,int vId=0,CHMLayer* pLayer = NULL);
	virtual ~CRectangle();

public:
	virtual void Set_Ty_Is_Fill(BOOL bFill,CElecMapView * pView=NULL);
	virtual void Set_Ty_Fill_Color(COLORREF color,CElecMapView * pView=NULL);
	virtual void DrawRect(CDC *pDC,int orgX,int orgY,float offsetX, float offsetY, float scaleX, float scaleY, COLORREF ReplaceColor,COLORREF ToColor, BOOL bReplace=TRUE);
	virtual void Set_Line_Width(int width,CElecMapView * pView=NULL);
	virtual void Set_Ty_Color(COLORREF color,CElecMapView * pView=NULL);
	virtual BOOL Is_Net_Color_Vector();
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

public:
	float m_x0,m_y0,m_x1,m_y1;	//ֱ�ߵ������յ�
	LOGPEN m_logpen;
	BOOL m_bFill;						//�����Ƿ����
	COLORREF m_FillColor;		//�������ɫ
	RECT_TYPE m_rtType;			//������	
};

//�����
class CPolygon : public CTyBase  
{
private:
	BOOL PointInLine(float x, float y,float errRange,float x0,float y0,float x1,float y1);
	void SetDefaultProp(CElecMapView *pView);
	DECLARE_SERIAL(CPolygon);

	CPolygon()
	{
		m_scale = -1;
		m_nPoints = 0; 
		m_nAllocPoints = 0;
		m_bFill = FALSE;
		m_LPoints = NULL;
		m_UPoints = NULL;
	}

public:
	enum POLYGON_TYPE
	{
		Polygon = 0,
		Polyline
	};

	CPolygon(float x0,float y0,float x1,float y1, LOGPEN *pLogPen,BOOL blFill,COLORREF fillcolor,int vId=0,CHMLayer* pLayer = NULL);
	virtual ~CPolygon();

public:
	virtual void Set_Ty_Is_Fill(BOOL bFill, CElecMapView *pView);
	virtual void Set_Ty_Fill_Color(COLORREF color, CElecMapView *pView);
	virtual void DrawRect(CDC *pDC, int orgX,int orgY,float offsetX, float offsetY, float scaleX, float scaleY, COLORREF ReplaceColor,COLORREF ToColor, BOOL bReplace=TRUE);
	virtual void Set_Ty_Color(COLORREF color,CElecMapView * pView=NULL);
	virtual void Set_Line_Width(int width,CElecMapView * pView=NULL);
	virtual BOOL Is_Net_Color_Vector();
	void ClonePoint(int id,CElecMapView *pView);
	void DeletePoint(int id,CElecMapView *pView);
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

	void CalaculateLPoints(CElecMapView *pView);
	void CalaculateBoundsRect();
	void AddPoint(PointStruct point, CElecMapView *pView);

	
public:
	float m_x0,m_y0,m_x1,m_y1;	//ֱ�ߵ������յ�
	LOGPEN m_logpen;
	BOOL m_bFill;							//�����Ƿ����
	COLORREF m_FillColor;			//�������ɫ
	POLYGON_TYPE m_PolyType;	//������	
	int m_nAllocPoints;					//�ѷ���ĵ���
	int m_nPoints;							//ʵ��ʹ�õ���
	PointStruct* m_UPoints;			//�û�����㼯��
	CPoint* m_LPoints;					//�߼�����㼯��
	float m_scale;							//��ǰ��ʾ����
};


//�ı�
class CText : public CTyBase  
{
	DECLARE_SERIAL(CText);
	
private:
	void SetDefaultProp(CElecMapView *pView);
	void SetSize(float width,float height);

public:
	enum TEXT_TYPE
	{
		txtTime=0,
		txtDate,
		txtStatic
	};
	
	CText(){};

	CText(float startX0,float startY0,float txtwidth,float txtheight,BOOL fx,
				float jqwidth,char TextFont[],COLORREF textcolor,
				CString Text,int vId=0,CHMLayer* pLayer = NULL);

	virtual ~CText();

public:
	virtual void Set_Ty_Color(COLORREF color,CElecMapView * pView=NULL);
	virtual void SetFontProp(float height,float width,float jqwidth,BOOL pl,COLORREF color,char font[]);
	int GetChineseNum();
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

public:
	float m_StartX;						//�ı���������
	float m_StartY;						//���������
	BOOL  m_FangXiang;			//��ע�Ƕ� TRUE-����  FALSE-����
	float m_TextHeight;				//����߶�
	float m_TextWidth;				//������
	float m_JqWidth;					//������
	char	m_TextFont[16];			//����
	TEXT_TYPE m_TextType;		//������	
	COLORREF m_TextColor;		//�ı���ɫ
	CString m_Text;					//��ע���ı���Ϣ
};

//λͼ
class CTyBmp : public CTyBase  
{
private:
	DECLARE_SERIAL(CTyBmp);

	CTyBmp()
	{	
		m_blHScale=TRUE;
		m_blVScale=TRUE;					
	};

	void SetDefaultProp(CElecMapView *pView);

public:
	CTyBmp(float x0,float y0,float x1,float y1, LPCSTR bmpname,BOOL blTranslate,COLORREF translatecolor,BOOL blHScale=TRUE,BOOL blVScale=TRUE,int vId=0,CHMLayer* pLayer=NULL);
	virtual ~CTyBmp();

public:
	virtual BOOL Is_Net_Color_Bmp();
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

public:
	float m_x0,m_y0,m_x1,m_y1;	//ͼ�������յ�
	BOOL m_bTranslate;				//�����Ƿ�͸��
	COLORREF m_TranslateColor;	//����͸��ɫ
	char m_bmpName[33];			//λͼ����
	BOOL m_blHScale;					//�Ƿ�ˮƽ��������
	BOOL m_blVScale;					//�Ƿ�ֱ��������
};

//ʸ��ͼ
class CTyVector : public CTyBase  
{
private:
	DECLARE_SERIAL(CTyVector);
	
	CTyVector(){};
	void SetDefaultProp(CElecMapView *pView);

public:
	CTyVector(float x0,float y0,float x1,float y1, LPCSTR vectorname,BOOL blTranslate,COLORREF translatecolor,int vId = 0,CHMLayer* pLayer = NULL);
	virtual ~CTyVector();

public:
	virtual BOOL Is_Net_Color_Vector();
	virtual void OnEditProperties(CElecMapView * pView = NULL);
	virtual DRAW_TY GetTyType();
	virtual void Ty_Serialize(CArchive &ar);
	virtual void Ty_Save(CFile *file, BOOL Yn);
	virtual void Ty_MoveHandleTo(int nHandle, PointStruct point, CElecMapView *pView,UINT nFlags = 0);
	virtual void Ty_Move(float xLen, float yLen,CElecMapView * pView = NULL);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual PointStruct GetHandle(int nHandle);
	virtual int GetHandleCount();
	virtual BOOL PointInObj(float x, float y,float errRange);
	virtual BOOL IntersectRect(float x0, float y0, float x1, float y1);
	virtual CTyBase * Clone();
	virtual void GetRect(float *minX, float *minY, float *maxX, float *maxY);
	virtual void DrawDC(CDC *pDC, CElecMapView *pView);
	virtual void Set_Ty_Color(COLORREF color,CElecMapView * pView=NULL);

public:
	float m_x0,m_y0,m_x1,m_y1;	//ͼ�����յ�
	BOOL m_bTranslate;					//��̬ɫ�Ƿ��滻
	COLORREF m_TranslateColor;	//��̬ɫ���滻ɫ
	char m_vectorName[33];			//λͼ����
};

struct y_info
{
	DWORD y_min ;
	DWORD y_max ;
	DWORD y_scale ;
};

#define YMMAXCURVE	8

//�ۼ�������
class CYMcCurve : public CTyBase  
{
public:
	DECLARE_SERIAL(CYMcCurve);

	CYMcCurve():m_strname(_T("")){};
	CYMcCurve(float x0,float y0,float x1,float y1,int vId=0,CHMLayer* pLayer = NULL);
	virtual ~CYMcCurve();

public:
	virtual void OnEditProperties(CElecMapView * pView);
	virtual DRAW_TY GetTyType();
	virtual void DrawDC(CDC *pDC, CElecMapView *pView);
	virtual void GetRect(float *minX, float *minY, float *maxX, float *maxY);
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
	void DrawString(CDC* pDC, CElecMapView *pView);// ��������
	void RecalcRects(CRect rt);// �����ͼ����С
	void DrawTyRect(CDC* pDC, CElecMapView *pView);// ����ͼԪ����
	void DrawPlotRect(CDC* pDC, CElecMapView *pView);// ���ƻ�ͼ����
	void DrawGrid(CDC* pDC, CElecMapView *pView);// ��������
	void DrawLine(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);// �����߶�

public:
	float m_x0,m_y0,m_x1,m_y1;	     //ֱ�ߵ������յ�
	CRect m_TyRect;                           // ͼԪ����
	CRect m_PlotRect;                         // ��ͼ����	
	COLORREF m_SpaceColor;            // �հ�������ɫ	
	COLORREF m_BackGroundColor;  // ��ͼ������ɫ	
	COLORREF m_GridColor;               // ������ɫ	
	int m_LeftSpace;                            // ���հ�����	
	int m_TopSpace;                            // �����հ�����
	int m_RightSpace;                          // �Ҳ�հ�����	
	int m_BottomSpace;                      // �ײ��հ�����	

private:
	ymcurve_info ymcurves[YMMAXCURVE] ;
	y_info	hourinfo ;//Сʱ����
	y_info  ymin_day ;
	y_info	ymin_month ;
	y_info	ymin_year ;
	BYTE	ymcurvescount ;
	char	ymc_unit[9] ;
	char	ymcname[17] ;//����
	RectStruct rect ;//��Χ
	CString m_strname;
};

//ë�����߾���
struct StringAlign	
{ 
	int HAlign;
	int VAlign; 
};   // ���뷽ʽ

enum   CTextAlign
{ 
	LEFT = 0,
	CENTER = 1, 
	RIGHT = 2, 
	TOP = 0,
	BOTTOM = 2 
};

class CMcCurve : public CTyBase  
{
private:
	void SetDefaultProp(CElecMapView *pView);
	DECLARE_SERIAL(CMcCurve);
	CMcCurve(){};

public:
	CMcCurve(float x0,float y0,float x1,float y1,int vId=0,CHMLayer* pLayer=NULL);
	virtual ~CMcCurve();

public:
	virtual void OnEditProperties(CElecMapView * pView);
	virtual void Ty_Serialize(CArchive &ar);
	virtual void Ty_Save(CFile *file, BOOL Yn);
	virtual void Ty_MoveHandleTo(int nHandle, PointStruct point, CElecMapView *pView,UINT nFlags=0);
	virtual void Ty_Move(float xLen, float yLen,CElecMapView * pView=NULL);
	virtual DRAW_TY GetTyType();
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual PointStruct GetHandle(int nHandle);
	virtual int GetHandleCount();
	virtual BOOL PointInObj(float x, float y,float errRange);
	virtual BOOL IntersectRect(float x0, float y0, float x1, float y1);
	virtual CTyBase * Clone();
	virtual void GetRect(float *minX, float *minY, float *maxX, float *maxY);
	virtual void DrawDC(CDC *pDC, CElecMapView *pView);
	virtual void ParamReplace_Ty(CStringList& ruleList);
	void SetAlign(int HAlign, int VAlign);	// �����ַ����뷽ʽ

public:
	CMcCurveData mccurvedata;
	CMcCurveData mccurvedatabackup;
	float m_x0,m_y0,m_x1,m_y1;	//ֱ�ߵ������յ�

protected:
	int m_TyScale;                          // �Ŵ����	
	CRect m_TyRect;                         // ͼԪ����
	CRect m_PlotRect;                       // ��ͼ����	
	int m_LeftSpace;                        // ���հ�����	
	int m_TopSpace;                         // �����հ�����
	int m_RightSpace;                       // �Ҳ�հ�����	
	int m_BottomSpace;                      // �ײ��հ�����	
	CRect m_PriorButtonRect;                // ��ǰ������ť����	
	CRect m_NextButtonRect;                 // ��������ť����
	COLORREF m_BackGroundColor;             // ��ͼ������ɫ	
	COLORREF m_SpaceColor;                  // �հ�������ɫ	
	COLORREF m_GridColor;                   // ������ɫ		
	StringAlign m_StrAlign;                 // ���ֶ��뷽ʽ

protected:
	// �����ͼ����С
	void RecalcRects(CRect rt);
	// ����ͼԪ����
	void DrawTyRect(CDC* pDC, CElecMapView *pView);
	// ���ƻ�ͼ����
	void DrawPlotRect(CDC* pDC, CElecMapView *pView);
	// ����Y������
	void DrawYTicker(CDC* pDC, CElecMapView *pView);
	// ��������
	void DrawGrid(CDC* pDC, CElecMapView *pView);
	// ����X������
	void DrawXGrid(CDC* pDC);
	// ����Y������
	void DrawYGrid(CDC* pDC);
	// ���ƹ�ͨ�ߺ��Ա�����ʾ����
	void DrawHintWords(CDC* pDC, CElecMapView *pView);
	// ������ǰ��������������ť
	void DrawWayButton(CDC* pDC, CElecMapView *pView);
	// ��������
	void PrintString(CDC* pDC,int x, int y, int theta, const char* fmt);
	// �����߶�
	void DrawLine(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);
};


class CYcCurve:public CTyBase
{
	DECLARE_SERIAL(CYcCurve);

public:
	CYcCurve(){};
	CYcCurve(float x0,float y0,float x1,float y1,int vId=0,CHMLayer* pLayer = NULL);
	virtual ~CYcCurve();

public:
	virtual void OnEditProperties(CElecMapView * pView);
	virtual DRAW_TY GetTyType();
	virtual void DrawDC(CDC *pDC, CElecMapView *pView);
	virtual void GetRect(float *minX, float *minY, float *maxX, float *maxY);
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
	virtual void ParamReplace_Ty(CStringList& ruleList);

	void DrawString(CDC* pDC, CElecMapView *pView);// ��������
	void RecalcRects(CRect rt);// �����ͼ����С
	void DrawTyRect(CDC* pDC, CElecMapView *pView);// ����ͼԪ����
	void DrawPlotRect(CDC* pDC, CElecMapView *pView);// ���ƻ�ͼ����
	void DrawGrid(CDC* pDC, CElecMapView *pView);// ��������
	void DrawLine(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);// �����߶�
	
public:
	float m_x0,m_y0,m_x1,m_y1;//ͼ�����յ�
	float m_yfmin;            //y����Сֵ
	float m_yfmax;            //y�����ֵ
	ycurve_info yccurves[YCMAXCURVE];
	char m_tyname[17];        //ͼԪ����
	float m_ykedu;              //y��̶�
	char m_ydanwei[9];        //y�ᵥλ
	DWORD m_color;            //������ɫ
	float m_ryfmin;           //Ԥ��������Сֵ
	float m_ryfmax;           //Ԥ���������ֵ
    int m_count;              //����ʵ������
	BYTE m_curvetype;         //Ĭ���������� 0-Сʱ���� 1-������ 2-�����ߣ�3-������
	BYTE m_showplan;          //Ĭ���Ƿ���ʾ�ƻ����� 1��ʾ��0����ʾ
	BYTE m_haveplan;          //�������Ƿ��мƻ�����
	COLORREF m_colorPlan;	  //�ƻ����ߵ���ɫ	
	BYTE m_showYestorday;     //�������Ƿ���ʾ��������
	COLORREF m_colorYestorday;//�������ߵ���ɫ	
    byte m_yuliu[16];

	CRect m_TyRect;                          // ͼԪ����
	CRect m_PlotRect;                        // ��ͼ����	
	COLORREF m_SpaceColor;          // �հ�������ɫ	
	COLORREF m_BackGroundColor;// ��ͼ������ɫ	
	COLORREF m_GridColor;             // ������ɫ	
	int m_LeftSpace;                           // ���հ�����	
	int m_TopSpace;                           // �����հ�����
	int m_RightSpace;                         // �Ҳ�հ�����	
	int m_BottomSpace;                     // �ײ��հ�����	
};

extern BOOL GetServer(CString& );


/////////////////////////////////////////////////////////////////
//���վͼ��
/////////////////////////////////////////////////////////////////
class CTyState :
	public CTyBase
{
	DECLARE_SERIAL(CTyState);

private:
	CTyState(void)
	{	
		m_blHScale=TRUE;
		m_blVScale=TRUE;					
	};
	~CTyState(void);

public:
	CTyState(float x0,float y0,float x1,float y1, \
		LPCSTR bmpname,BOOL blTranslate, \
		COLORREF translatecolor, COLORREF textColor,\
		BOOL blHScale=TRUE,BOOL blVScale=TRUE,\
		int vId=0,CHMLayer* pLayer=NULL);

public:
	//virtual BOOL Is_Net_Color_Bmp();
	//virtual void OnEditProperties(CElecMapView * pView=NULL);
	//virtual DRAW_TY GetTyType();
	//virtual void Ty_Serialize(CArchive &ar);
	//virtual void Ty_Save(CFile *file, BOOL Yn);
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

	void setScaleConst();

private: 
	void drawText(float startX, float startY, float width, float height,\
		CString  strText,\
		CDC *pDC, CElecMapView *pView );

public:
	float m_x0,m_y0,m_x1,m_y1;		//ͼ�������յ�
	BOOL m_bTranslate;				//�����Ƿ�͸��
	COLORREF m_TranslateColor;		//����͸��ɫ
	char m_bmpName[33];				//λͼ����
	BOOL m_blHScale;				//�Ƿ�ˮƽ��������
	BOOL m_blVScale;				//�Ƿ�ֱ��������
	COLORREF m_TextColor;
};

#endif // !defined(AFX_JDJH_H__6058180F_FC99_408A_BB0E_FB47FEF9155A__INCLUDED_)
