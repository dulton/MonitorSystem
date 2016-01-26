#pragma once


// CVMHeaderCtrl
class CVMHeaderCtrl : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CVMHeaderCtrl)

public:
	CVMHeaderCtrl();
	virtual ~CVMHeaderCtrl();

public:
	COLORREF m_color;
	CStringArray m_strHeadArray;
	CString m_strFormat; //��ʾ�������͵���������,0��ʾ����룬1��ʾ�м���룬2��ʾ�Ҷ���

public:
	int m_R;
	int m_G;
	int m_B;
	int m_Gradient;	// �����屳��������ϵ��
	float m_fHeight;  //��ͷ�߶ȣ����Ǳ���,
	int m_nFontHeight; //����߶�
	int m_nFontWith;   //������

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	LRESULT OnLayout( WPARAM wParam, LPARAM lParam );
};


