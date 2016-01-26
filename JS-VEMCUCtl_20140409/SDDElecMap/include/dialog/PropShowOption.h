#pragma once

//#include "sp_draw.h"
#include "../../resource.h"
#include "canvas/LineProp.h"

// CPropShowOption �Ի���

class CPropShowOption : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropShowOption)

public:
	CPropShowOption();
	virtual ~CPropShowOption();

// �Ի�������
	enum { IDD = IDD_SHOW_EXPRESS };

	void GetProp(int& display,char* str1,char* str2,COLORREF& color1,COLORREF&  color2,BOOL&   bFangXiang,float& fTextHeight,float& fTextWidth,float& fJqWidth,char* TextFont,BOOL& bTranslate1,BOOL& bTranslate2);
	void SetProp(int display,char str1[33],char str2[33],COLORREF color1,COLORREF color2,BOOL  bFangXiang,float fTextHeight,float fTextWidth,float fJqWidth,char TextFont[16],BOOL bTranslate1,BOOL bTranslate2);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_display;
	CString m_strBmp1;
	CString m_strBmp2;
	CString m_strVect1;
	CString m_strVect2;
	CString m_strText1;
	CString m_strText2;

private:
  COLORREF m_TranslateColor1;
  COLORREF m_TranslateColor2;


	COLORREF m_VectColor1;
	COLORREF m_VectColor2;
  CStaticColor  m_ctrlVectColor1;
  CStaticColor  m_ctrlVectColor2;

	COLORREF m_TextColor1;
	COLORREF m_TextColor2;
  CStaticColor  m_ctrlTextColor1;
  CStaticColor  m_ctrlTextColor2;

  //���ֱ�ʾʱ������ֶ�
	BOOL  m_bFangXiang;				//��ע�Ƕ�
														//  TRUE-����  FALSE-����
	float m_TextHeight;				//����߶�
	float m_TextWidth;				//������
	float m_JqWidth;					//������
	char	m_TextFont[16];			//����

  //λͼ
	BOOL	m_bTranslate1;		//������ʾ��λͼ�����Ƿ�͸��
	BOOL	m_bTranslate2;		//�쳣��ʾ��λͼ�����Ƿ�͸��

public:
	virtual BOOL OnInitDialog();

	afx_msg void OnTextColor1();
	afx_msg void OnTextColor2();
	afx_msg void OnVectColor1();
	afx_msg void OnVectColor2();
	afx_msg void OnFont();
	afx_msg void OnBmp1();
	afx_msg void OnBmp2();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnVect1();
	afx_msg void OnVect2();

private:
	void UpdateUI();


public:
};
