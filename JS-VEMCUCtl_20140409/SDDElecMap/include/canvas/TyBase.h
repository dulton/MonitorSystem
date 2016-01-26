/////////////////////////////////////////////////////////////////////
// TyBase.h: interface for the CTyBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TYBASE_H__72E869AE_6422_44B5_9640_628F3F263EC2__INCLUDED_)
#define AFX_TYBASE_H__72E869AE_6422_44B5_9640_628F3F263EC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "canvas/LinkObjectBase.h"
#include <math.h>

#define pi 3.1415926
#define MAXPOINTNUM 500
#define OFFSETX 4
#define OFFSETY 4

#define NET_RENDER 0x80000000


/*---------------------------------------------------------------------------------
	*								DRAW_TY �������Ļ���
	*--------------------------------------------------------------------------------
	tySelect				ѡ��,
	tyZoomOut			�Ŵ�
	tyZoomIn				��С
	tyLine					ֱ��,
	tyXX						����,
	tyHX						����,
	tyZX						����
	tyRect					����,
	tyRoundRect		Բ�Ǿ���,
	tyEllipse				��Բ,
	tyDBX					�����,
	tyArc					����,
	tyText					�ı�,
	tyCL						����
	tyYDX                   ˫ң�� 
	tyBmp					λͼ
	lnkYT					ң��
	lnkYK					ң��
	lnkBHTQ				����Ͷ��
	lnkYZTY				���ص�ѹ
	tyYC                     ң��
	tyYX						ң��
	tyYM					���
	lnkCur					����
	lnkTicket              ����Ʊ
	lnkLB					¼������
	lnk_SZ_SGBW		�¹ʱ���
	lnkNetColorPower  ��̬��ɫ���Դ 
	lnkNetColorVect     ��̬��ɫ��ʸ��ͼԪ
	lnkNetColorBmp     ��̬��ɫ��λͼ
	lnkNetColorYx         ��̬��ɫ�㿪��
	lnkClub					��ͼ
	tyAnimate            λͼ���� 
    lnk_SZ_PHOTO     ͼƬ����
	lnkUnit					��Ԫ����
	tyVector				ʸ��ͼԪ
	lnkTxt					�ı��ļ�����
	tyMonNiYK		    ģ�����ͼԪ
	lnkWebShot			webͼ����ͨ������
	lnk_SZ_SBLOOK		�豸�����������
	lnkMNP_SHXG         �Ϻ��¹�ģ����
	lnkMNP_ZJNH         �㽭����ģ����
	lnkNode					�ڵ�����
	lnkLine					    ��·����
	tymccurve               ë������
	lnkFile					    ��ͨ�ļ�����

-----------------------------------------------------------------------------------
*/


/*---------------------------------------------------------------------------------
	*								���Ӷ��������
	*--------------------------------------------------------------------------------
	
	
*/

typedef enum
{
    tyNone=0,
	tySelect=1,
	tyZoomOut=2,
	tyZoomIn=3,
	tyLine=4,
	tyXX=5,
	tyHX=6,
	tyZX=7,
	tyRect=8,
	tyRoundRect=9,
	tyEllipse=10,
	tyDBX=11,
	tyArc=12,
	tyText=13,
	tyCL=14,
	tyDateTime=15,
	tyYDX=16,
	tyBmp=17,
	lnkYK=18,
	lnkYT=19,
	lnkBHTQ=20,
	lnkYZTY=21,
	tyYC=22,
	tyYX=23,
	tyYM=24,
	tyHmProxy=25,
	lnkCur=26,
	lnkLB=27,
	lnk_SZ_SGBW=28,
	lnkNetColorPower=29,
	lnkNetColorVect=30,
	lnkNetColorBmp=31,
	lnkNetColorYx=32,
	lnkClub=33,
	tyAnimate=34,
	lnk_SZ_PHOTO=35,
	lnkUnit=36,
	tyVector=37,
	lnkTxt=38,
	tyMonNiYK=39,
	lnkWebShot=40,
	lnk_SZ_SBLOOK=41,
	lnkMNP_SHXG=42,
	lnkMNP_ZJNH=43,
	lnkTicket=44,
    lnkNode=45,
	lnkLine=46,
	tymccurve=47,
	lnkFile=48,
	tyYcYw=49,
	tyNewYC = 50,
	lnk_SZ_TIMEYC=51,
	tyYmccurve = 62 ,
	//����ͼԪ
	lnkModem = 63 ,
	lnkYT2 = 64,

	//ң�Ű�ͼԪ
	lnkYXBind = 65 ,

	//���ģ���ͼԪ----add by 20151208
	lnkYSHBind = 106,

	lnkQK = 66 ,
	//��̨������
	lnkSoftRepair = 67 ,
	//��Ԫ��չ
	lnkUnitExtend = 68 ,
	//���߿�������
	lnkKX = 69 ,
	//������������
	lnkKXSection = 70 ,
	//ˮ��ҵ��������
	lnkDoubleCtrl = 71 ,
    tyyccurve=72,
	lnkSupervise = 73,
	lnkPowerGzTj=74,
	lnkLineGzTj=75,
	lnkZK=76,
	tyMove=80,
	tyStationAssistPng=100,

	tyTransSubstation = 101,
	tyCamera =102,// �����
	tyLight  =103,// �ƹ�
	tyGate   =104,// �Ž�
	tyTemp   =105 // �¶�
} DRAW_TY;


/*---------------------------------------------------------------------------------
	*								
	*--------------------------------------------------------------------------------

*/

typedef struct
{
	float x;
	float y;
}PointStruct;

typedef struct
{
	float x0;
	float y0;
	float x1;
	float y1;

	void InflateRect(float x,float y)
	{
		x0-=x;
		y0-=y;
		x1+=x;
		y1+=y;
	}; 

	float Width()
	{
		return (float)fabs(x1-x0);	
	}

	float Height()
	{
		return (float)fabs(y1-y0);	
	}
}RectStruct;


class CElecMapView;

/*
--------
��������:
--------
	float PointLine(float xx,float yy,float x1,float y1,float x2,float y2)
			����������㣨xx,yy)���߶Σ�x1,y1)(x2,y2)�ľ��룬���ؼ���ľ���ֵ

	float CalDisp(float x1,float y1,float x2,float y2)
			�����������(x1,y1)���(x2,y2)��ľ���

	BOOL PointRgn(float x,float y,int Numble,PointStruct *PointList,float blc)
			�������ж�һ�����Ƿ�����������������
			������Numble-�߽������x,y�ǵ�����꣬����ζ���������ڽṹ����PointList��
			���أ�1-���ڶ��������0-����

	BOOL PointInObj(float x,float y,float errRange);
			�������ж�һ�����Ƿ��ڶ���������
			������
					x,y-����û�����
					errRange-��Χ(�û�����)
			���أ�TRUE-���ڶ���������	FALSE-����


--------
ͼԪ����
--------
	void Move(float xLen,float yLen);
			�������ƶ�ͼԪ
			������
					xLen-x����ľ���
					yLen-y����ľ���

--------
�¼�
--------
	void OnEditProperties()
			�������༭ͼԪ����

--------
����
--------
	int GetHandleCount()
			����������ͼԪ�İ�����Ŀ
	
	PointStruct GetHandle(int nHandle);
			�����������ض���ʶ����nHandle������λ��(�û�����)

	CRect GetHandleRect(int nHandleID, CElecMapView* pView);
			�����������ض���ʶ����nHandle�ľ��η�Χ���߼����꣩

	void MoveHandleTo(int nHandle, PointStruct point, CSp_drawView* pView,UINT nFlags);
			�������ƶ��ض���ʶ����nHandle����point(�û����꣩


---------
���Ӷ���
---------
	BOOL OnEditLinkObjectProperties(int pos)
			�������༭��pos�����Ӷ��������
			����:
					pos ���Ӷ����λ��
			����ֵ:�Ƿ��޸� 

	BOOL ExecuteLinkObject(int pos1,int pos2);
	������������pos1�����Ӷ���ĵ�pos2��������ִ��
			����:
					pos1 ���Ӷ����λ��
					pos2-���Ӷ���Ķ������
			����ֵ:��ת�Ƿ�ɹ� 

  void AddLinkObject(CLinkObjectBase *pLink)
			����������һ�����Ӷ���pLink

	void DeleteLinkObject(int pos);
			������ɾ����posλ�õ����Ӷ���

	int Get_LinkTy_Count()
		��������ȡͼԪ������ӵ�е����Ӷ������Ŀ


---------
ͼ�����
---------
	void UnRegisterImage(LPCSTR bmpname);
	     ����: ע��ͼ��bmpname

	void RegisterImage(LPCSTR bmpname);
	     ����: �Ǽ�ͼ��bmpname

	void DrawImage(LPCSTR bmpname,CDC* pDC, int x0, int y0, int nWidth, int nHeight,BOOL bTranslate,COLORREF color,BOOL blHScale=TRUE,BOOL blVScale=TRUE);
	     ����: ��ʾͼ��
			 ������
					bmpname-ͼ������
					x0��y0-��ʾ��ʼ����λ�ã��߼����꣩
          nWidth-��ʾ���
					nHeight-��ʾ�߶�
					bTranslate-�����Ƿ�͸��
					color-͸����ɫ
					blHScale-�Ƿ�ˮƽ��������
					blVScale-�Ƿ�ֱ��������

------------
ʸ��ͼ����
------------
	void UnRegisterVector(LPCSTR vectorname);
	     ����: ע��ʸ��ͼvectorname

	void RegisterVector(LPCSTR vectorname);
	     ����: �Ǽ�ʸ��ͼvectorname

	void DrawVector(LPCSTR vectorname,CDC* pDC,CRect viewRect,CRect clipRect,COLORREF color,BOOL blReplace=TRUE);
	     ����: ��ʾʸ��ͼ
			 ������
					vectorname-ʸ��ͼ����
					viewRect-ʸ��ͼ��ʾ��Χ���߼����꣩
          clipRect-ʸ��ͼ��ʾ���з�Χ���߼����꣩
					color-��̬��ɫ

  CSize Get_Size_Vector(LPCSTR vectorname)
	     ����: ��ȡʸ��ͼ�Ĵ�С
			 ������
					vectorname-ʸ��ͼ����

	void DrawRect(CDC* pDC,int offsetX,int offsetY,float scaleX,float scaleY,COLORREF ReplaceColor,COLORREF ToColor,BOOL bReplace=TRUE)
	     ����: ͼԪ������Ϊʸ��ͼ��һ���ֽ��л���
			 ������
				 pDC-DC
				 offsetX-ͼԪ����ʱ��ƫ����x
				 offsetY-ͼԪ����ʱ��ƫ����y
				 scaleX-X�����ϵı���
				 scaleY-Y�����ϵı���
				 ReplaceColor-���ǰ��ɫ
				 ToColor-�������ɫ
				 bReplace-�Ƿ����
------------------
���綯̬��ɫ��֧��
------------------
   BOOL Is_Net_Color_Vector()
	     ����: ͼԪ������Ϊ��ɫ��ʸ��ͼԪ��
   BOOL Is_Net_Color_Bmp()
	     ����: ͼԪ������Ϊ��ɫ��λͼ��
	 BOOL Is_Net_Color_Power()
	     ����: ͼԪ������Ϊ��ɫ���Դ��
	 BOOL Is_Net_Color_Yx();
	     ����: ͼԪ������Ϊ��ɫ�㿪����

	 BOOL Is_In_Net_Color_Power();
			 ����: �жϸ�ͼԪ�Ƿ�����������Դ
	 BOOL Is_In_Net_Color_Yx();
	     ����: �жϸ�ͼԪ�Ƿ�������ɫ�㿪�أ�
   BOOL Is_In_Net_Color_Bmp()
	     ����: �жϸ�ͼԪ�Ƿ�������ɫ��λͼ��
   BOOL Is_In_Net_Color_Vector()
	     ����: �жϸ�ͼԪ�Ƿ�������ɫ��ʸ��ͼ��


------------------------
���ͼԪ�༭��֧��
------------------------
	virtual void Set_Ty_Color(COLORREF color,CSp_drawView * pView=NULL);
	     ����:����ͼԪ����ɫ

	virtual void Set_Line_Width(int width,CSp_drawView * pView=NULL);
	     ����:���������Ŀ��

  void SetFontProp(float height,float width,float jqwidth,BOOL pl,COLORREF color,char font[]);
	     ����:����������Ϣ

--------------------------
���水��������
--------------------------
	virtual void ParamReplace(CStringList& ruleList);
	����:ͼԪ�����������滻
	�滻���� ��һ���ַ���'0'-��ͨ�ַ��滻��1'-��Ӣ����,��һ���ַ���, '2'-�ڵ�,��·,��Ԫ,���

	int GetEname_From_ReplacRule(CString vDotName,CString& vDstDotName, CStringList& ruleList);
	����:��Ӣ���������滻�����ȡ�µ�Ӣ����
	int GetDot_From_ReplaceRule(BYTE srcNode, BYTE srcLine, BYTE srcRtu, WORD srcDot, BYTE& dstNode, BYTE& dstLine, BYTE& dstRtu, WORD& dstDot, CStringList& ruleList);
	����:�ѵ�Ŵ����滻�����ȡ�µĵ��
	int GetStr_From_ReplacRule(CString srcStr,CString& dstStr, CStringList& ruleList);
	����:���ַ��������滻�����ȡ�µ��ַ���


*/



class CHMLayer;

#define MAXLINKTY_COUNT  8    //ÿһ��ͼԪ���ӵ�е�����ͼԪ����Ŀ


class CTyBase : public CObject  
{
	DECLARE_SERIAL(CTyBase);

public:
	CHMLayer *m_pHMLayer;				//ָ���Լ����ڵĻ�������
	int		   m_Id;								    //ͼ��Ԫ��Ψһ��ʶ���
	int		   m_iNumber;						//ͼԪλ�ñ��
	BOOL	   m_bDelete;						//�Ƿ�ɾ��
	DWORD  m_dwFlag;						//ͼԪ��־
														
	CLinkObjectArray m_LinkArr;          //���Ӷ����б�

public:
	CTyBase (int vId = 0,CHMLayer* pLayer = NULL);
	int GetID();

	virtual void GetRect(float *minX,float *minY,float *maxX,float *maxY);

public:
	virtual void Set_Ty_Is_Fill(BOOL bFill,CElecMapView * pView=NULL);
	virtual void Set_Ty_Fill_Color(COLORREF color,CElecMapView * pView=NULL);
	virtual void Set_Ty_Color(COLORREF color,CElecMapView * pView=NULL);
	virtual void Set_Line_Width(int width,CElecMapView * pView=NULL);
	virtual void SetFontProp(float height,float width,float jqwidth,BOOL pl,COLORREF color,char font[]);
	
	//���綯̬��ɫ��֧��
	BOOL Is_Net_Color_Power();
	virtual BOOL Is_Net_Color_Yx();
	virtual BOOL Is_Net_Color_Bmp();
	virtual BOOL Is_Net_Color_Vector();

	BOOL Is_In_Net_Color_Vector();
	BOOL Is_In_Net_Color_Bmp();
	BOOL Is_In_Net_Color_Yx();
	BOOL Is_In_Net_Color_Power();

	//ʸ��ͼ����
	void UnRegisterVector(LPCSTR vectorname);
	void RegisterVector(LPCSTR vectorname);
	void DrawVector(LPCSTR vectorname,CDC* pDC,CRect viewRect,CRect clipRect,COLORREF color,BOOL blReplace=TRUE);
	static CSize Get_Size_Vector(LPCSTR vectorname);
	virtual void DrawRect(CDC* pDC,int orgX,int orgY,float offsetX, float offsetY,float scaleX,float scaleY,COLORREF ReplaceColor,COLORREF ToColor,BOOL bReplace=TRUE);

	//ͼ�����
	void DrawImage(LPCSTR bmpname,CDC* pDC, int x0, int y0, int nWidth, int nHeight,BOOL bTranslate,COLORREF color,BOOL blHScale=TRUE,BOOL blVScale=TRUE);
	void UnRegisterImage(LPCSTR bmpname);
	void RegisterImage(LPCSTR bmpname);

	//���Ӷ���
	BOOL ExecuteLinkObject(int pos1,int pos2);
	BOOL OnEditLinkObjectProperties(int pos);
	void DeleteLinkObject(int pos);
	void AddLinkObject(CLinkObjectBase* pLink);
	int Get_LinkTy_Count();
	CString GetLinkObjectName(int pos);

	//ͼԪ�޸�֪ͨ
	void SetModifiedFlag(BOOL bl=TRUE);

	//ͼԪ����
	static CTyBase* CreateTy(DRAW_TY tyStyle);
	virtual DRAW_TY GetTyType();

	//����
	void MoveHandleTo(int nHandle, PointStruct point, CElecMapView* pView,UINT nFlags=0);

	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual void Ty_MoveHandleTo(int nHandle, PointStruct point, CElecMapView *pView,UINT nFlags);
	virtual PointStruct GetHandle(int nHandle);
	virtual int GetHandleCount();
	CRect GetHandleLogRect(int nHandleID, CElecMapView* pView);
	
	//ͼԪ������˶�
	void Move(float xLen,float yLen,CElecMapView * pView=NULL);

	virtual void Ty_Move(float xLen, float yLen,CElecMapView * pView);
	virtual void OnEditProperties(CElecMapView * pView=NULL);
	virtual CTyBase* Clone();

	//��ͼ
	void Invalidate();
	virtual void DrawDC(CDC *pDC, CElecMapView *pView);
	enum TrackerState { normal, selected, active };
	virtual void DrawTracker(CDC* pDC, CElecMapView *pView,TrackerState state);

	//����
	void Save(CFile* file,BOOL Yn);
	virtual void Ty_Save(CFile *file, BOOL Yn);
	void LinkObjects_Save(CFile *file, BOOL Yn);
	void Serialize(CArchive& ar);
	virtual void Ty_Serialize(CArchive & ar);
	void LinkObjects_Serialize(CArchive &ar);

	// �����Զ�����
	void ParamReplace(CStringList& ruleList);
	void LinkObjects_ParamReplace(CStringList& ruleList);
	virtual void ParamReplace_Ty(CStringList& ruleList);
	static int GetEname_From_ReplacRule(CString vDotName,CString& vDstDotName, CStringList& ruleList);
	static int GetDot_From_ReplaceRule(BYTE srcNode, BYTE srcLine, BYTE srcRtu, WORD srcDot, BYTE& dstNode, BYTE& dstLine, BYTE& dstRtu, WORD& dstDot, CStringList& ruleList);
	static int GetStr_From_ReplacRule(CString srcStr,CString& dstStr, CStringList& ruleList);

	//�жϺͼ���
	virtual BOOL PointInObj(float x,float y,float errRange);
	int HitTest(PointStruct point, CElecMapView* pView, BOOL bSelected);
	virtual BOOL IntersectRect(float x0, float y0, float x1, float y1);
	static BOOL  PointRgn(float x,float y,int Numble,PointStruct *PointList,float blc);
	static float CalDisp(float x1,float y1,float x2,float y2);
	static float PointLine(float xx,float yy,float x1,float y1,float x2,float y2);
	static BOOL PointInEllipse(float x,float y,RectStruct rt);
	static BOOL PointInRect(float x,float y,RectStruct rt);
	static BOOL IntersectRect2(RectStruct rt1,RectStruct rt2);
	static BOOL URectInURect(RectStruct rt1,RectStruct rt2);

	#ifdef _DEBUG
		void ASSERTValid();
	#endif
	virtual ~CTyBase();

protected:
	friend class CHMLayer;

};

typedef CTypedPtrList<CObList, CTyBase*> CTyBaseList;


#endif // !defined(AFX_TYBASE_H__72E869AE_6422_44B5_9640_628F3F263EC2__INCLUDED_)
