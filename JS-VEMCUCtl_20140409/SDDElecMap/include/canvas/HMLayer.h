// HMLayer.h: interface for the CHMLayer class.
//
/*

----------
���캯��
----------

	CHMLayer(float startBL,float endBL, float defBL,int layerID,LPCSTR pStr,CHuaMian *pHuaMian,int sPos,int ePos,int sTyID);
	����:
		startBL-	��ʼ��ʾ���� >=
		endBL-		������ʾ���� <
		defBL-		Ĭ����ʾ����
		layerID-	������ʶ��
		pStr-			�����������
		sPos-			ͼԪ����λ�ñ�ʶ
		ePos-			ͼԪ��ǰ��λ�ñ�ʶ
		sTyID-		ͼԪ��ʼ��ʶ


------------
ͼԪ�Ĺ���
------------

	void Add(CTyBase* pTy);
	����: ���������һ��ͼԪ
	����:
		pTy-ָ��ͼԪ��ָ�� 

	CTyBase * FindTyBase(int id);
	����: ����ͼԪ
	����:
		id-ͼԪ��ʶ�� 
  ����:
      ����ҵ�ͼԪ�򷵻ظ�ͼԪ �Ҳ����򷵻�NULL 

	CTyBase * ObjectAt(PointStruct pt,float errRange)
	����: �����ڸõ�ͶӰ��ͼԪ
	����:
		pt- ����û�����
		errRange- ��Χ
  ����:
      ����ҵ�ͼԪ�򷵻ظ�ͼԪ �Ҳ����򷵻�NULL 


	void Front(CTyBase* pTy);
	����: ͼԪ�Ƶ�ǰ��
	����:
		pTy-ָ��ͼԪ��ָ�� 

	void Back(CTyBase * pTy);
	����: ͼԪ�Ƶ����
	����:
		pTy-ָ��ͼԪ��ָ�� 

	void SelectWithinRect(RectStruct rt, CSp_drawView *pView)
	����: ѡ�����������rt�ڵ�ͼԪ
	����:
		rt-�����û����� 
		pView-ָ����ʾ����ָ��


------------
�������ʾ
------------
 
	BOOL IsInViewBL(float fScale);
	����: �ⶨ��ʾ�����Ƿ��ڸû�������Ұ��Χ��
	����:
		fScale-Ҫ�ⶨ����ʾ���� 
  ����:
			TRUE-����Ұ��Χ��		

---------------------
��������Դ���ķ���
---------------------

	void OnHMLayerDataChanged();
	����:����Ĵ�С�����ı��������仯��Ĵ����¼�

	void ModifyProp( tagHMLayerID *pLayerID);
	����:�޸Ļ��������
	����:
		pLayerID-������������� 

------------
������¼�:
------------
	void OnAddTy(CTyBase *pTy,BOOL blNumberChanged=TRUE);
	����:����һ��ͼԪ�¼�
	����:
		pTy-ָ��ͼԪ��ָ�� 
		blNumberChanged:ͼԪ��λ�ú��Ƿ����

	void OnRemoveTy(CTyBase *pTy);
	����:ɾ��һ��ͼԪ�¼�
	����:
		pTy-ָ��ͼԪ��ָ�� 

  void OnPositionChangedTy(CTyBase *pTy, RectStruct oldRt, RectStruct newRt)
	����:ͼԪλ�ñ仯�¼�
	����:
		pTy-ָ��ͼԪ��ָ�� 
		oldRt-�仯ǰ��λ������
		newRt-�仯���λ������


----------
�и���:
----------
	
	CRect GetArrQGMBoundsRect(float x0,float y0,float x1,float y1);
	����:��ȡһ���û��������и������ĸ�����
	����:
		x0,y0,x1,y1-�û���������
	����:
	  �������и�������еĸ�����

		
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HMLAYER_H__4C315EA3_ADCC_4A42_BDFE_A15F620693CD__INCLUDED_)
#define AFX_HMLAYER_H__4C315EA3_ADCC_4A42_BDFE_A15F620693CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "canvas/tybase.h"
#include "gloable/DataStyle.h"

class CHuaMian; 
class CElecMapDoc;
class CQGM;
class CElecMapView;
class CZoomInTool;
class CZoomOutTool;

class CHMLayer : public CObject  
{
	DECLARE_SERIAL(CHMLayer);

public:
	CHMLayer(float startBL,float endBL, float defBL,int layerID,LPCSTR pStr,CHuaMian *pHuaMian,int sPos=0,int ePos=0,int sTyID=0);
	virtual ~CHMLayer();

private:
	CRect GetArrQGMBoundsRect(float x0,float y0,float x1,float y1);
	int m_iStartNumber;	//ͼԪ������λ�ñ��
	int m_iEndNumber;		//ͼԪ��ǰ���λ�ñ��	
	int m_IDDef;				    //ͼԪ��ʶ����ʼֵ

protected:
	CHMLayer(CHuaMian *pHuaMian = NULL)
	{	
		m_pHuaMian = pHuaMian;
		m_uRow = 0;
		m_uCol = 0;
		ZeroMemory(QGMArr,sizeof(QGMArr));
	}

protected:
	CTyBaseList m_TyList;		//�ò����е�ͼԪ�ļ���
	float m_startViewBL;		//��ʾ��ʼ����
	float m_endViewBL;			//��ʾ��������
	float m_DefaultBL;			//ȱʡ��ʾ����
	int		  m_iLayerNo;		//�����
	CString  m_CName;			//�����������

public:
	void OnPositionChangedTy(CTyBase* pTy,RectStruct oldRt,RectStruct newRt);
	void ZhenLi();
	void SelectWithinRect(RectStruct rt,CElecMapView *pView);
	float GetDefaultScale();
	CTyBase * ObjectAt(PointStruct pt,float errRange);
	
	void Add(CTyBase* pTy,BOOL blNumberChanged = TRUE);
	void Remove(CTyBase * pTy);
	void Front(CTyBase* pTy);
	void Back(CTyBase * pTy);

	CElecMapDoc * GetDocument();
	CTyBase * FindTyBase(int id);
	void ModifyProp( tagHMLayerID *pLayerID);

	void OnAddTy(CTyBase *pTy);
	void OnRemoveTy(CTyBase* pTy);
	void OnHMLayerDataChanged();

	void DrawDC(CDC *pDC, CElecMapView *pView);
	BOOL IsInViewBL(float fScale);
	void Save(CFile *file, BOOL Yn);

	void ParamReplace(CStringList& ruleList);

public:
	CHuaMian*	m_pHuaMian;	//ָ��ò����ڵĻ������	
	CQGM*  QGMArr[MAX_QGMROW][MAX_QGMCOL];//�и���2ά����
	UINT m_uRow;													//���������
	UINT m_uCol;													//���������
	BOOL m_bHide;												//�Ƿ�������ʾ	

public:
	friend class CHuaMian;
	friend class CZoomInTool;
	friend class CZoomOutTool;

	#ifdef _DEBUG
		 void ASSERTValid();
	#endif
};

typedef CTypedPtrList<CObList, CHMLayer*> CHMLayerList;


#endif // !defined(AFX_HMLAYER_H__4C315EA3_ADCC_4A42_BDFE_A15F620693CD__INCLUDED_)
