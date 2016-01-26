#pragma once
#include "canvas/LineProp.h"
#include "../../resource.h"
// CNewYC_PROP_DIS �Ի���

class CNewYC_PROP_DIS : public CPropertyPage
{
	DECLARE_DYNAMIC(CNewYC_PROP_DIS)

public:
	CNewYC_PROP_DIS(BYTE kind=1);
	virtual ~CNewYC_PROP_DIS();

	CRTUColorStatic m_normalc;
	CRTUColorStatic m_disablec;
	CRTUColorStatic m_upc;		//����
	CRTUColorStatic m_downc;	//����

	CRTUColorStatic m_uupc;		//������ֵ
	CRTUColorStatic m_ddownc;	//������ֵ

	BYTE itkind;//1 yc 2 ym

	LOGFONT lgfont;//����
    COLORREF levelupcolor;//Խ������ɫ
	COLORREF leveluupcolor;//Խ��������ɫ

    COLORREF leveldowncolor;//Խ������ɫ
	COLORREF levelddowncolor;//Խ��������ɫ

    COLORREF normalcolor;//������ɫ
    COLORREF disablecolor;//��Ч��ɫ


	float rectx0;
	float recty0;
	float fontwidth;
	float fontheight;
	float fontjj;

	//yc
	void GetPara(COLORREF *disablec,COLORREF *normalc,COLORREF *leveluc,COLORREF *leveluuc,
		COLORREF *leveldc,COLORREF *levelddc ,LOGFONT *ff,float *x0,float *y0,float *fontw,
			float *fonth,float *fontj);

	void SetPara(COLORREF disablec,COLORREF normalc,COLORREF leveluc,COLORREF leveluuc,
		COLORREF leveldc,COLORREF levelddc ,LOGFONT ff,float x0,float y0,float fontw,
			float fonth,float fontj);
	//ym
	void GetPara2(COLORREF *disablec,COLORREF *normalc,
		LOGFONT *ff,float *x0,float *y0,float *fontw,float *fonth,float *fontj);
	void SetPara2(COLORREF disablec,COLORREF normalc,
		LOGFONT ff,float x0,float y0,float fontw,float fonth,float fontj);


// �Ի�������
	enum { IDD = CZ_IDD_NEW_YC_DIS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float m_editx0;
	float m_edity0;
	float m_editfh;
	float m_editfw;
	float m_editjj;
	afx_msg void OnBnClickedButtonYcFont();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
};
