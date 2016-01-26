// VMHeaderCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "VMHeaderCtrl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CVMHeaderCtrl

IMPLEMENT_DYNAMIC(CVMHeaderCtrl, CHeaderCtrl)

CVMHeaderCtrl::CVMHeaderCtrl()
{
	m_R = 171;
	m_G = 199;
	m_B = 235;
	m_Gradient = 8;
	
	m_strFormat = "";
	m_fHeight = 1;
	m_nFontHeight = 15;
	m_nFontWith = 0;
	
	m_color = RGB(0,0,0);
}

CVMHeaderCtrl::~CVMHeaderCtrl()
{

}


BEGIN_MESSAGE_MAP(CVMHeaderCtrl, CHeaderCtrl)
	ON_WM_PAINT()
	ON_MESSAGE(HDM_LAYOUT, OnLayout)
END_MESSAGE_MAP()



// CVMHeaderCtrl ��Ϣ�������

void CVMHeaderCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	//////////////////////////////////////////////////////////////////////////
	int nItem = 0; 
	int R,G,B;
	UINT nFormat = 1;
	int ofst = 0;
	
	CRect rc;
	CRect rt;
	CRect rcRect;
	CRect rtRect;
	CRect clientRect;
	
	TEXTMETRIC metric;
	CBrush _brush; 
	CFont NewFont;
	CFont* pOldFont = NULL;

	nItem = GetItemCount();
	
	for(int i = 0; i < nItem;i ++) 
	{ 
		GetItemRect(i,&rc);
		
		R = m_R;
		G = m_G;
		B = m_B;

		rt = rc;//�����ߴ絽�µ������� 
		rt.left++;//�����ָ��ߵĵط� 
		
		//�������屳�� 
		for(int j = rc.top;j <= rc.bottom;j++) 
		{ 
			rt.bottom = rt.top+1; 
		
			_brush.CreateSolidBrush(RGB(R,G,B));//������ˢ 
			dc.FillRect(&rt,&_brush); //��䱳�� 
			_brush.DeleteObject(); //�ͷŻ�ˢ 
			
			R -= m_Gradient;
			G -= m_Gradient;
			B -= m_Gradient;

			if (R<0) R = 0;
			if (G<0) G = 0;
			if (B<0) B= 0;

			rt.top = rt.bottom; 
		} 

		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(m_color);

		NewFont.CreateFont(m_nFontHeight,m_nFontWith,0,0,0,FALSE,FALSE,0,0,0,0,0,0,_TEXT("����"));//�������� 
	    pOldFont = dc.SelectObject(&NewFont);

		nFormat = 1;
		if (m_strFormat[i] == '0')
		{
			nFormat = DT_LEFT;
			rc.left += 3;
		}
		else if (m_strFormat[i] == '1')
		{
			nFormat = DT_CENTER;
		}
		else if (m_strFormat[i] == '2')
		{
			nFormat = DT_RIGHT;
			rc.right -= 3;
		}

		dc.GetTextMetrics(&metric);
		
		ofst = 0;
		ofst = rc.Height() - metric.tmHeight;
		rc.OffsetRect(0,ofst/2);

		dc.DrawText(m_strHeadArray[i],&rc,nFormat);
		
		dc.SelectObject(pOldFont); 
		NewFont.DeleteObject(); //�ͷ����� 
	} 

	//��ͷ��ʣ�ಿ��
	GetItemRect(nItem-1,rcRect);
	GetClientRect(clientRect);

	rcRect.left = rcRect.right+1;
	rcRect.right = clientRect.right;
	
	R = m_R;
	G = m_G;
	B = m_B;
	
	rtRect= rcRect;
	
	//�������屳�� 
	for(int j = rcRect.top;j <= rcRect.bottom;j++) 
	{ 
		rtRect.bottom = rtRect.top+1; 
		
		_brush.CreateSolidBrush(RGB(R,G,B));//������ˢ 
		dc.FillRect(&rtRect,&_brush); //��䱳�� 
		_brush.DeleteObject(); //�ͷŻ�ˢ 
	
		R -= m_Gradient;
		G -= m_Gradient;
		B -= m_Gradient;
		
		if (R<0) R = 0;
		if (G<0) G = 0;
		if (B<0) B= 0;

		rtRect.top = rtRect.bottom; 
	} 
}

LRESULT CVMHeaderCtrl::OnLayout( WPARAM wParam, LPARAM lParam )
{
	LRESULT lResult = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam); 

	HD_LAYOUT &hdl = *(HD_LAYOUT*)lParam; 
	RECT *prc = hdl.prc; 
	WINDOWPOS *pwpos = hdl.pwpos; 

	//��ͷ�߶�Ϊԭ��1.5�������Ҫ��̬�޸ı�ͷ�߶ȵĻ�����1.5���һ��ȫ�ֱ��� 
	int nHeight = (int)(pwpos->cy * m_fHeight);

	pwpos->cy = nHeight; 
	prc->top = nHeight; 

	return lResult; 
}