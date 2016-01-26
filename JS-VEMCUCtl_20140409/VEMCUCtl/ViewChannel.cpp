// ViewChannel.cpp: implementation of the CViewChannel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "ViewChannel.h"
#include "VEMCUCtlDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC( CViewChannel, CWnd )
/////////////////////////////////////////////////////////////////////////////
// CViewChannel

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CViewChannel::CViewChannel()
{
	//�������
	m_iWinID = -1;
	m_video_opened = false;

	//��̨�������
	m_video_opened = false;
	m_byt_ctl = false;
	m_iyt_pos = 0;

	m_nViewChannelInfoShowFlag = 0;

	//����
	LOGFONT   logfont;   
	memset(&logfont,0,sizeof(LOGFONT));   
	logfont.lfHeight  = 32;                  //����߶�   
	logfont.lfWidth   = 24;                  //������
	logfont.lfWeight = 1000;              //�Ӵ�
	strcpy(logfont.lfFaceName,"����"); //������
	m_font.CreateFontIndirect(&logfont);
}

CViewChannel::~CViewChannel()
{
	//�������
	m_iWinID = -1;
	m_video_opened = false;

	//��̨�������
	m_video_opened = false;
	m_byt_ctl = false;
	m_iyt_pos = 0;

	m_nViewChannelInfoShowFlag = 0;
}

BEGIN_MESSAGE_MAP(CViewChannel, CWnd)
//{{AFX_MSG_MAP(CViewChannel)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CViewChannel message handlers
BOOL CViewChannel::OnEraseBkgnd(CDC* pDC) 
{
	try
	{
		CRect rect;
		GetClientRect (&rect);

		int nSrcX = 0;
		int nSrcY = 0;
		int nDstX = 0;
		int nDstY = 0;
		int nWidth = 0;
		int nHeight = 0;

		CBrush brush;
		CFont * pOldFont = NULL;

		pOldFont = pDC->SelectObject(&m_font);
		pDC->SetBkColor(RGB(216,231,229));
		pDC->SetTextColor(RGB(20,20,180));

		brush.CreateSolidBrush(RGB(216,231,229)); 
		pDC->FillRect (rect, &brush);

		//if (m_nViewChannelInfoShowFlag == 1)
		//{
		//	pDC->DrawText("�ѱ�עȱ��",rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
		//}
		//else if (m_nViewChannelInfoShowFlag == 2)
		//{
		//	pDC->DrawText("ͨ���ж�",rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
		//}

		pDC->SelectObject(pOldFont);

		CDC   dcMem;
		CBitmap*   pOldBitmap;

		dcMem.CreateCompatibleDC(pDC); 

		if (g_pMainDlg != NULL)
		{
			nWidth = g_pMainDlg->m_ViewOutVideoBGBm.bmWidth;
			nHeight = g_pMainDlg->m_ViewOutVideoBGBm.bmHeight;

			pOldBitmap = dcMem.SelectObject(&g_pMainDlg->m_ViewOutVideoBGBmp);
			
			if (rect.Width() < g_pMainDlg->m_ViewOutVideoBGBm.bmWidth )
			{
				nSrcX = rect.left;
				nDstX = (g_pMainDlg->m_ViewOutVideoBGBm.bmWidth-rect.Width())/2;
				nWidth = rect.Width();
			}
			else
			{
				nSrcX = rect.left+(rect.Width()-g_pMainDlg->m_ViewOutVideoBGBm.bmWidth)/2;
				nDstX = 0;
				nWidth = g_pMainDlg->m_ViewOutVideoBGBm.bmWidth;
			}

			if (rect.Height() < g_pMainDlg->m_ViewOutVideoBGBm.bmHeight)
			{
				nSrcY = rect.top;
				nDstY = (g_pMainDlg->m_ViewOutVideoBGBm.bmHeight-rect.Height())/2;
				nHeight = rect.Height();
			}
			else
			{
				nSrcY = rect.top+(rect.Height()-g_pMainDlg->m_ViewOutVideoBGBm.bmHeight)/2; ;
				nDstY = 0;
				nHeight = g_pMainDlg->m_ViewOutVideoBGBm.bmHeight;
			}

			pDC->BitBlt(nSrcX,nSrcY,
				nWidth,nHeight,
				&dcMem,
				nDstX,nDstY,
				SRCCOPY);

			dcMem.SelectObject(pOldBitmap);
		}
	}
	catch(...)
	{

	}

	return TRUE;
}

void CViewChannel::FlashChannel()
{
	try
	{
		CDC* pDC = GetDC();
		if( pDC == NULL )
			return;

		CRect rect;
		GetClientRect(&rect);
		CBrush brush;

		int nSrcX = 0;
		int nSrcY = 0;
		int nDstX = 0;
		int nDstY = 0;
		int nWidth = 0;
		int nHeight = 0;

		CFont * pOldFont = NULL;

		pOldFont = pDC->SelectObject(&m_font);
		pDC->SetBkColor(RGB(216,231,229));
		pDC->SetTextColor(RGB(20,20,180));

		brush.CreateSolidBrush(RGB(216,231,229)); 
		pDC->FillRect (rect, &brush);

		//if (m_nViewChannelInfoShowFlag == 1)
		//{
		//	pDC->DrawText("�ѱ�עȱ��",rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
		//}
		//else if (m_nViewChannelInfoShowFlag == 2)
		//{
		//	pDC->DrawText("ͨ���ж�",rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
		//}

		CDC   dcMem;
		CBitmap*   pOldBitmap;

		dcMem.CreateCompatibleDC(pDC); 

		if (g_pMainDlg != NULL)
		{
			nWidth = g_pMainDlg->m_ViewOutVideoBGBm.bmWidth;
			nHeight = g_pMainDlg->m_ViewOutVideoBGBm.bmHeight;

			pOldBitmap = dcMem.SelectObject(&g_pMainDlg->m_ViewOutVideoBGBmp);

			if (rect.Width() < g_pMainDlg->m_ViewOutVideoBGBm.bmWidth )
			{
				nSrcX = rect.left;
				nDstX = (g_pMainDlg->m_ViewOutVideoBGBm.bmWidth-rect.Width())/2;
				nWidth = rect.Width();
			}
			else
			{
				nSrcX = rect.left+(rect.Width()-g_pMainDlg->m_ViewOutVideoBGBm.bmWidth)/2;
				nDstX = 0;
				nWidth = g_pMainDlg->m_ViewOutVideoBGBm.bmWidth;
			}

			if (rect.Height() < g_pMainDlg->m_ViewOutVideoBGBm.bmHeight)
			{
				nSrcY = rect.top;
				nDstY = (g_pMainDlg->m_ViewOutVideoBGBm.bmHeight-rect.Height())/2;
				nHeight = rect.Height();
			}
			else
			{
				nSrcY = rect.top+(rect.Height()-g_pMainDlg->m_ViewOutVideoBGBm.bmHeight)/2; ;
				nDstY = 0;
				nHeight = g_pMainDlg->m_ViewOutVideoBGBm.bmHeight;
			}

			pDC->BitBlt(nSrcX,nSrcY,
				nWidth,nHeight,
				&dcMem,
				nDstX,nDstY,
				SRCCOPY);

			dcMem.SelectObject(pOldBitmap);
		}

		ReleaseDC(pDC);
		pDC = NULL;

	}
	catch(...)
	{

	}
}

BOOL CViewChannel::LoadSkin()
{
	//m_BGBmp.LoadBitmap(IDB_BITMAP_VIEW_CHANNEL_BK);
	//m_BGBmp.GetObject(sizeof(BITMAP),(LPVOID)&m_BGBm);

	return TRUE;
}

/************************************************************************
* ��Ƶͨ���仯
*   �������巢����Ϣ
*    OM_CHANNLECHANGE��  m_iWinID * 0x1000 + 0
************************************************************************/
void CViewChannel::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (::GetCapture() == m_hWnd)
	{
		::ReleaseCapture();
	}

	if (m_byt_ctl == true && m_video_opened == true)
	{
		switch (m_iyt_pos)
		{
		case 1:
			m_iyt_pos = 0;
			m_byt_ctl = false;
			::SetCursor(m_hCursor_up);
			g_pMainDlg->PostMessage(OM_YTCONTROL, 1, 0);
			break;
		case 2:
			m_iyt_pos = 0;
			m_byt_ctl = false;
			::SetCursor(m_hCursor_down);
			g_pMainDlg->PostMessage(OM_YTCONTROL, 2, 0);
			break;
		case 3:
			m_iyt_pos = 0;
			m_byt_ctl = false;
			::SetCursor(m_hCursor_left);
			g_pMainDlg->PostMessage(OM_YTCONTROL, 3, 0);
			break;
		case 4:
			m_iyt_pos = 0;
			m_byt_ctl = false;
			::SetCursor(m_hCursor_right);
			g_pMainDlg->PostMessage(OM_YTCONTROL, 4, 0);
			break;
		default:
			break;
		}
	}
	
	CWnd::OnLButtonUp(nFlags, point);
}

/************************************************************************
* ��Ƶͨ��˫��������
*   �������巢����Ϣ
*    OM_DBLCHANNEL��  m_iWinID
************************************************************************/
void CViewChannel::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	g_pMainDlg->SendMessage(OM_DBLCHANNEL, m_iWinID);
	
	CWnd::OnLButtonDblClk(nFlags, point);
}

/************************************************************************
* ��Ƶͨ���Ҽ���������
*   �������巢����Ϣ
*    OM_RIGHTCLICKCHANNEL��  m_iWinID
************************************************************************/
void CViewChannel::OnRButtonUp(UINT nFlags, CPoint point) 
{
	g_pMainDlg->SendMessage(OM_RIGHTCLICKCHANNEL, m_iWinID);
	
	CWnd::OnRButtonUp(nFlags, point);
}

void CViewChannel::OnTimer(UINT nIDEvent) 
{	
	CWnd::OnTimer(nIDEvent);
}

BOOL CViewChannel::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (m_byt_ctl == false)
	{
		if (m_video_opened == true)
		{
			int x0;
			int x1;
			int y0;
			int y1;
			int xp;
			int yp;
			int posA;
			int posB;

			CRect	rc;
			CPoint pt;

			GetWindowRect(&rc);
			GetCursorPos(&pt);
			
			x0 = 0;
			y0 = 0;
			x1 = rc.right - rc.left;
			y1 = rc.bottom - rc.top;

			xp = pt.x - rc.left;
			yp = pt.y - rc.top;

			posA = yp - (y1 - xp*y1/x1);
			posB = yp - xp*y1/x1;

			if (posA < 0 && posB < 0 && yp < y1/4)//up
			{
				::SetCursor(m_hCursor_up);
				return true;
			}

			if (posA > 0 && posB > 0 && yp > 3*y1/4)//down
			{
				::SetCursor(m_hCursor_down);
				return true;
			}

			if (posA < 0 && posB > 0 && xp < x1/4)//left
			{
				::SetCursor(m_hCursor_left);
				return true;
			}

			if (posA > 0 && posB < 0 && xp > 3*x1/4)//right
			{
				::SetCursor(m_hCursor_right);
				return true;
			}
		}

		return CWnd::OnSetCursor(pWnd, nHitTest, message);
	}
	else
	{
		return true;
	}
}

int CViewChannel::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//////////////////////////////////////////////////////////////////////////
	m_hCursor_up = AfxGetApp()->LoadCursor(IDC_CURSOR_YTUP);
	m_hCursor_down = AfxGetApp()->LoadCursor(IDC_CURSOR_YTDOWN);
	m_hCursor_left = AfxGetApp()->LoadCursor(IDC_CURSOR_YTLEFT);
	m_hCursor_right = AfxGetApp()->LoadCursor(IDC_CURSOR_YTRIGHT);
	m_hCursor_up_on = AfxGetApp()->LoadCursor(IDC_CURSOR_YTUP_ON);
	m_hCursor_down_on = AfxGetApp()->LoadCursor(IDC_CURSOR_YTDOWN_ON);
	m_hCursor_left_on = AfxGetApp()->LoadCursor(IDC_CURSOR_YTLEFT_ON);
	m_hCursor_right_on = AfxGetApp()->LoadCursor(IDC_CURSOR_YTRIGHT_ON);
	
	m_iWinID = -1;
	m_video_opened = false;
	m_byt_ctl = false;
	m_iyt_pos = 0;

	LoadSkin();

	return 0;
}

void CViewChannel::OnLButtonDown(UINT nFlags, CPoint point) 
{
	g_pMainDlg->SendMessage(OM_CHANNLECHANGE, m_iWinID * 0x1000 + 0);	//m_iYTID);
	
	Sleep(50);

	::SetCapture(m_hWnd);

	if (m_video_opened == true)
	{
		int x0;
		int x1;
		int y0;
		int y1;
		int xp;
		int yp;
		int posA;
		int posB;

		CRect	rc;
		CPoint pt;

		GetWindowRect(&rc);
		GetCursorPos(&pt);

		x0 = 0;
		y0 = 0;
		x1 = rc.right - rc.left;
		y1 = rc.bottom - rc.top;

		xp = pt.x - rc.left;
		yp = pt.y - rc.top;

		posA = yp - (y1 - xp*y1/x1);
		posB = yp - xp*y1/x1;

		if (posA < 0 && posB < 0 && yp < y1/4)//up
		{
			m_byt_ctl = true;
			m_iyt_pos = 1;
			::SetCursor(m_hCursor_up_on);
			g_pMainDlg->PostMessage(OM_YTCONTROL, 1, 1);
			return;
		}

		if (posA > 0 && posB > 0 && yp > 3*y1/4)//down
		{
			m_byt_ctl = true;
			m_iyt_pos = 2;
			::SetCursor(m_hCursor_down_on);
			g_pMainDlg->PostMessage(OM_YTCONTROL, 2, 1);
			return;
		}

		if (posA < 0 && posB > 0 && xp < x1/4)//left
		{
			m_byt_ctl = true;
			m_iyt_pos = 3;
			::SetCursor(m_hCursor_left_on);
			g_pMainDlg->PostMessage(OM_YTCONTROL, 3, 1);
			return;
		}

		if (posA > 0 && posB < 0 && xp > 3*x1/4)//right
		{
			m_byt_ctl = true;
			m_iyt_pos = 4;
			::SetCursor(m_hCursor_right_on);
			g_pMainDlg->PostMessage(OM_YTCONTROL, 4, 1);
			return;
		}
	}
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CViewChannel::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
}
