// ImageView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PtuDlg.h"
#include "ImageView.h"


// CImageView

IMPLEMENT_DYNAMIC(CImageView, CWnd)

CImageView::CImageView()
{
	m_strFileName = _T("");
	m_bFileExsit = FALSE;
}

CImageView::~CImageView()
{
}


BEGIN_MESSAGE_MAP(CImageView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_CLOSE_VIDEO, &CImageView::OnCloseVideo)
END_MESSAGE_MAP()



// CImageView ��Ϣ�������



void CImageView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()


	CRect rect;
	GetClientRect(&rect);

	CBrush brush;
	COLORREF color = RGB(0,0,0);

	brush.CreateSolidBrush(color);
	dc.FillRect(rect,&brush);

}


void CImageView::LoadBitmapFile(CString strFileName)
{
	if (strFileName.Find("bmp") == -1)
	{
		return;
	}

	m_strFileName = strFileName;

	HBITMAP hBitmap=(HBITMAP)LoadImage(NULL,strFileName,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE);
	m_bitmap.Detach();
	m_bitmap.Attach(hBitmap);

	Invalidate();
}

BOOL CImageView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//return TRUE;
	return CWnd::OnEraseBkgnd(pDC);
}

void CImageView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}


void CImageView::CreateWnd(CRect& WndRect,CWnd* pParentWnd)
{
	m_WndRect = WndRect;

	CWnd::Create(NULL,NULL,WS_CHILD|WS_VISIBLE,m_WndRect,pParentWnd,0);
	ShowWindow(SW_SHOW);
}

void CImageView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDlgPresetSetting* pDlg = NULL;
	pDlg = (CDlgPresetSetting*)this->GetParent();
	if (pDlg == NULL)
	{
		return ;
	}

	if (pDlg->m_bVideoOpen == false)
	{
		return ;
	}

	CMenu  popMenu;

	popMenu.LoadMenu(IDR_MENU_CLOSE_VIDEO);
	CMenu *pMenu = popMenu.GetSubMenu(0); 

	CPoint posMouse;
	GetCursorPos(&posMouse);

	popMenu.GetSubMenu(0)->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_RIGHTALIGN,  posMouse.x, posMouse.y, this); 

	CWnd::OnRButtonDown(nFlags, point);
}

void CImageView::OnCloseVideo()
{
	// TODO: �ڴ���������������
	GetParent()->PostMessage(WM_CLOSE_VIDEO,0,0);
}
