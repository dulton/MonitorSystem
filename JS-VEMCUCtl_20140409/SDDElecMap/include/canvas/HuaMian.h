// HuaMian.h: interface for the CHuaMian class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HUAMIAN_H__60324C54_3E18_4898_92F6_7F0D36653691__INCLUDED_)
#define AFX_HUAMIAN_H__60324C54_3E18_4898_92F6_7F0D36653691__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "canvas/tybase.h"
#include "canvas/hmlayer.h"
#include "gloable/DataStyle.h"

//������
#define HMT_TEMPLE		0x1		//����ģ��
#define HMT_SCALE			0x2		//��������
#define HMT_BMP				0x4		//���汳��Ϊλͼ


class CHMProject;
class CElecMapView;
class CElecMapDoc;
/*-----------------------------------------------------------------------------
	--------------------		�����ࣺ	����CHuaMian 
 	--------------------		����ߣ�	������
 	--------------------    ���ڣ�		2001-9-18		
	-----------------------------------------------------------------------------


 --------��������----------------------------------------

	BOOL GetScaleProp()
		�����������Ƿ�֧����������

	BOOL GetTempleProp()
		�����������Ƿ��ǻ���ģ������

	CString& GetHMName();
		���������ػ�������

	void GetScaleRange(float * pMinScale,float * pMaxScale);
		���������ػ��������Χ


  --------����㴦��----------------------------------------

	CHMLayer * AddHMLayer(tagHMLayerID *pLayer);
		���������ӻ����
		����:
			pLayer-�������������
		���� ��������

	void ModifyLayerProp(LPCSTR pLayer, tagHMLayerID *pLayerID);
		�������޸Ļ��������
		����:
			pLayer-�����������
			pLayerID-�»������������

	CHMLayer * FindLayer(LPCSTR strLayer);
		���������һ�������
		����:
			strLayer-�����������
		���� strLayer��Ӧ�Ļ�������

	CHMLayer * FindLayer(int LayerID);
		���������һ�������
		����:
			strLayer-������ʶ��
		���� strLayer��Ӧ�Ļ�������

	void ModifyLayerProp(LPCSTR pLayer, tagHMLayerID *pLayerID);
		�������޸Ļ����pLayer����
		����:
			pLayer-�����������
			pLayerID-�������������

	void DeleteLayer(LPCSTR strName);
		������ɾ�������strName
		����:
			strName-�����������

	void ZhenLi()
		����������  �Ѹ���������б�ɾ����ͼԪ�޳�


	void MoveNext(LPCSTR layername);
		������	�����layername�����ƶ�һ��

	void MovePre(LPCSTR layername);
		������	�����layername�����ƶ�һ��


---------
  �¼�
---------

	void OnHMSizeChanged();
		�������������С�����仯���¼�

	void OnDeleteLayer(CHMLayer *pLayer)
		������ɾ��������¼�
		����:
			pLayer-�����������

  void CHuaMian::OnRemoveTyEvent(CTyBase *pTy)
		������ɾ��ͼԪ�¼�
		����:
			pTy-ָ��ͼԪ��ָ��

  void CHuaMian::OnAddTyEvent(CTyBase *pTy)
		����������ͼԪ�¼�
		����:
			pTy-ָ��ͼԪ��ָ��


-----------------------------------------------------------------------------
*/


class CHuaMian : public CObject  
{
	DECLARE_SERIAL(CHuaMian);

private:
	int  m_iLayerIdDef;						   //��������ʼԤ�����
	CElecMapDoc * m_pDoc;				   //ָ���ͼ�ĵ���ָ��

protected:
	DWORD m_dwPICStyle;					//������
	WORD	m_wPicWidth;						//ͼ�����
	WORD	m_wPicHeight;						//ͼ���߶�
	WORD	m_wResolution;					//��Ļ�ֱ��ʵĿ��
	WORD	m_hResolution;					//��Ļ�ֱ��ʵĸ߶�
	float  m_fDefaultScale;				        //Ĭ�ϵĻ�����ʾ����
	CString m_strName;						    //��������

public:
	CHMLayerList  m_HMLayerList;	//�������еĲ����
	CHuaMian(CElecMapDoc* pdoc=NULL);
	CHuaMian(LPCSTR strName,CElecMapDoc* pdoc=NULL,DWORD style=HMT_SCALE,WORD picwidth=1024,WORD picheight=768,WORD wresolution=1024,WORD hresolution=768,float scale=1,int preLayerID=0);

public:
	void GetScaleRange(float * pMinScale,float * pMaxScale);
	void MoveNext(LPCSTR layername);
	void MovePre(LPCSTR layername);
	void ZhenLi();
	float GetDefaultScale();
	BOOL GetBmpBackGroundMode();
	COLORREF m_dwBackColor;				//���汳����ɫ
	DWORD		m_dwBackImageNo;			//����λͼ���

	void OnRemoveTyEvent(CTyBase *pTy);
	void OnDeleteLayer(CHMLayer* pLayer);
	void DeleteLayer(LPCSTR strName);
	CHMLayer * FindLayer(int LayerID);
	CHMLayer * FindLayer(LPCSTR strLayer);
	void ModifyLayerProp(LPCSTR pLayer, tagHMLayerID *pLayerID);
	CHMLayer * AddHMLayer(tagHMLayerID *pLayer);
	void OnHMSizeChanged();

	void DrawDC(CDC *pDC, CElecMapView *pView);

	CSize GetHMSize();
	void SavePicHead(CFile *file,tagHuaMianFileHead* filehead, BOOL Yn);
	void SetHMID( tagHMID *pHMID);
	CElecMapDoc* GetDocument(){return m_pDoc;}; 
	CString GetHMName(void);
	BOOL GetTempleProp(void);
	void Save(CFile *file, BOOL Yn);
	virtual void Serialize(CArchive& ar);
	BOOL GetScaleProp(void);
	void OnAddTyEvent(CTyBase *pTy);
	void ParamReplace(CStringList& ruleList);

	virtual ~CHuaMian();

	static WORD  m_wPicFlag;				//�ļ��ض���־
	static WORD  m_wMVersion;				//�ļ��߰汾��
	static WORD  m_wEVersion;				//�ļ��Ͱ汾��
	friend class CHMLayer;

public:
	///update entity status.
	BOOL updateEntityInAHuamian( char *pRealData, int nCount );
};

#endif // !defined(AFX_HUAMIAN_H__60324C54_3E18_4898_92F6_7F0D36653691__INCLUDED_)
