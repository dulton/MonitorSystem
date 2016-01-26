#pragma once

#include "canvas/tybase.h"
#include "../../ElecMapView.h"


class CTyMonNiYK :
	public CTyBase
{
DECLARE_SERIAL( CTyMonNiYK);//֧�����л�
private:

	void Register();
	void UnRegister();
	void SetDefaultProp(CElecMapView *pView);
	void GetRect_Text(float *minX, float *minY, float *maxX, float *maxY);
	int GetChineseNum(LPCSTR str);
	void DrawDC_Text(CDC *pDC, CElecMapView *pView);
	void DrawDC_Vecter(CDC *pDC, CElecMapView *pView);
	void DrawDC_Bmp(CDC* pDC,CElecMapView * pView);

public:

	CTyMonNiYK(float x0,float y0,float x1,float y1,
					 int display,LPCSTR str1,LPCSTR str2,COLORREF Color1, 
					 COLORREF Color2,BOOL FangXiang,float TextHeight,
					 float TextWidth,float JqWidth,LPCSTR TextFont,BOOL bTranslate1,
					 BOOL bTranslate2,int vId=0,CHMLayer* pLayer=NULL);



	CTyMonNiYK(void);
	~CTyMonNiYK(void);

	virtual void SetFontProp(float height,float width,float jqwidth,BOOL pl,COLORREF color,char font[]);
	virtual void Set_Ty_Color(COLORREF color,CElecMapView * pView=NULL);
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


	float m_x0,m_y0,m_x1,m_y1;	//��ʾ��Χ�������յ�
	int		m_display;			//������ʽ
												// 0��λͼ����
												// 1��ʸ��ͼ����
												// 2�����ֱ���

	char	m_str1[33];			//������ʾ�� λͼ���ƻ�ʸ��ͼ���ƻ�������������ʾ
	char	m_str2[33];			//�쳣��ʾ�� λͼ���ƻ�ʸ��ͼ���ƻ�������������ʾ
	COLORREF	m_color1;		//������ʾ�� λͼ��͸��ɫ��ʸ��ͼ��ǰ��ɫ��������������ɫ
	COLORREF	m_color2;		//�쳣��ʾ�� λͼ��͸��ɫ��ʸ��ͼ��ǰ��ɫ��������������ɫ

  //���ֱ�ʾʱ������ֶ�
	BOOL  m_FangXiang;				//��ע�Ƕ�
														//  TRUE-����  FALSE-����
	float m_TextHeight;				//����߶�
	float m_TextWidth;				//������
	float m_JqWidth;					//������
	char	m_TextFont[16];			//����

	//λͼ
	BOOL	m_bTranslate1;		//λͼ����:	������ʾ��λͼ�����Ƿ�͸��
													//ʸ��ͼ:		������ʾ����ͼ�ɫ�Ƿ��滻
  
	BOOL	m_bTranslate2;		//λͼ���֣��쳣��ʾ��λͼ�����Ƿ�͸��
													//ʸ��ͼ:		�쳣��ʾ����ͼ�ɫ�Ƿ��滻

protected:
	void Set_Size_Text(float cx,float cy);
	void Ty_MoveHandleTo_Text(int nHandle, PointStruct point, CElecMapView *pView,UINT nFlags);

};
