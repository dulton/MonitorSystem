#pragma once
#include "canvas/tybase.h"

//class CElecMapView;

//class CTyState :
//	public CTyBase
//{
//	DECLARE_SERIAL(CTyState);
//
//private:
//	CTyState(void)
//	{	
//		m_blHScale=TRUE;
//		m_blVScale=TRUE;					
//	};
//	~CTyState(void);
//
//	void SetDefaultProp(CElecMapView *pView);
//
//public:
//	CTyState(float x0,float y0,float x1,float y1, \
//			LPCSTR bmpname,BOOL blTranslate, \
//			COLORREF translatecolor, COLORREF textColor,\
//			BOOL blHScale=TRUE,BOOL blVScale=TRUE,\
//			int vId=0,CHMLayer* pLayer=NULL);
//
//public:
//	//virtual BOOL Is_Net_Color_Bmp();
//	//virtual void OnEditProperties(CElecMapView * pView=NULL);
//	//virtual DRAW_TY GetTyType();
//	//virtual void Ty_Serialize(CArchive &ar);
//	//virtual void Ty_Save(CFile *file, BOOL Yn);
//	//virtual void Ty_MoveHandleTo(int nHandle, PointStruct point, CElecMapView *pView,UINT nFlags=0);
//	//virtual void Ty_Move(float xLen, float yLen,CElecMapView * pView=NULL);
//	//virtual HCURSOR GetHandleCursor(int nHandle);
//	//virtual PointStruct GetHandle(int nHandle);
//	//virtual int GetHandleCount();
//	//virtual BOOL PointInObj(float x, float y,float errRange);
//	virtual BOOL IntersectRect(float x0, float y0, float x1, float y1);
//	virtual CTyBase * Clone();
//	virtual void GetRect(float *minX, float *minY, float *maxX, float *maxY);
//	virtual void DrawDC(CDC *pDC, CElecMapView *pView);
//
//	void setScaleConst();
//
//private: 
//	void drawText(float startX, float startY, float width, float height,\
//					CString  strText,\
//					CDC *pDC, CElecMapView *pView );
//
//public:
//	float m_x0,m_y0,m_x1,m_y1;		//ͼ�������յ�
//	BOOL m_bTranslate;				//�����Ƿ�͸��
//	COLORREF m_TranslateColor;		//����͸��ɫ
//	char m_bmpName[33];				//λͼ����
//	BOOL m_blHScale;				//�Ƿ�ˮƽ��������
//	BOOL m_blVScale;				//�Ƿ�ֱ��������
//	COLORREF m_TextColor;
//};