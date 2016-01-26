// ViewChannel.cpp: implementation of the CViewChannel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LinkageSetting.h"
#include "ViewChannel.h"
#include "PtuDlg.h"

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
	m_byt_ctl = false;
	m_iyt_pos = 0;

	//��ƵID
	m_nCurrentVideoId = -1;
	m_nControlSpeed = 5;

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
	m_byt_ctl = false;
	m_iyt_pos = 0;
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
	ON_COMMAND(IDC_MENU_CLOSE_VIDEO, &CViewChannel::OnCloseVideo)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CViewChannel message handlers
BOOL CViewChannel::OnEraseBkgnd(CDC* pDC) 
{
	//���ñ���ͼƬ
	SetBackGround();

	return TRUE;
}

void CViewChannel::FillAllDialogBKColor()
{
	CDC *pDC = GetDC();
	CRect rect;
	GetClientRect(&rect);
	CBrush brush;
	brush.CreateSolidBrush(RGB(216,231,229)); 
	pDC->FillRect(rect, &brush);
}

void CViewChannel::SetBKPicture()
{
	CDC *pDC = GetDC();
	CBitmap bmpMem;//����һ��λͼ����
	bmpMem.LoadBitmap(IDB_BITMAP_VIDEO_BG);//�����Լ���bitmap
	BITMAP bmpInfo;
	bmpMem.GetBitmap(&bmpInfo);

	//���������Ļ��ʾ���ݵ��ڴ���ʾ�豸
	CDC dcMem;//���ȶ���һ����ʾ�豸����
	dcMem.CreateCompatibleDC(NULL);
	dcMem.SelectObject(&bmpMem);

	//���㻭��λ��
	CRect rectDst = GetDstRect(bmpInfo);

	//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ
	pDC->BitBlt(rectDst.left, rectDst.top, rectDst.right, rectDst.bottom, &dcMem, 0, 0, SRCCOPY);

	//��ͼƬ������ʾ
	//pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,SRCCOPY);

	//��ͼ��ɺ������
	bmpMem.DeleteObject();
	dcMem.DeleteDC();
}

void CViewChannel::SetBackGround()
{
	//��������������ڵı���ɫ
	FillAllDialogBKColor();

	//���ô�����Ƶ����ı���ͼƬ
	SetBKPicture();

	//���ñ��ⱳ��ͼƬ
	SetTitleBKPicture();
}

void CViewChannel::SetTitleBKPicture()
{
	//���Ʊ��ⱳ��ͼƬ
	/*
	CRect rect;
	m_csTitle.GetWindowRect(&rect);
	ScreenToClient(&rect);

	CDC *pDC = GetDC();
	CBitmap bmp;//����һ��λͼ����
	bmp.LoadBitmap(IDB_BITMAP_TITLE);//�����Լ���bitmap
	CBrush brush;
	brush.CreatePatternBrush(&bmp);
	pDC->SelectObject(&brush);
	pDC->SelectStockObject(NULL_PEN);//ʵ���ޱ߿����
	pDC->Rectangle(rect);

	bmp.DeleteObject();
	*/
	
	//���Ʊ��ⱳ��ͼƬ
	CRect rect;
	m_csTitle.GetWindowRect(&rect);
	ScreenToClient(&rect);
	CDC *pDC = m_csTitle.GetDC();
	CBitmap bmpMem;//����һ��λͼ����
	bmpMem.LoadBitmap(IDB_BITMAP_TITLE);//�����Լ���bitmap
	BITMAP bmpInfo;
	bmpMem.GetBitmap(&bmpInfo);

	//���������Ļ��ʾ���ݵ��ڴ���ʾ�豸
	CDC dcMem;//���ȶ���һ����ʾ�豸����
	dcMem.CreateCompatibleDC(NULL);
	dcMem.SelectObject(&bmpMem);

	//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ
	//pDC->BitBlt(rectDst.left, rectDst.top, rectDst.right, rectDst.bottom, &dcMem, 0, 0, SRCCOPY);

	//��ͼƬ������ʾ
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);

	//��ͼ��ɺ������
	bmpMem.DeleteObject();
	dcMem.DeleteDC();
}

//��ȡ���ı���ͼƬλ��
CRect CViewChannel::GetDstRect(BITMAP bmpInfo)
{
	//��ȡ����ͷ���ڵ�λ��
	CRect rect;
	m_csVideo.GetWindowRect(&rect);
	ScreenToClient(&rect);
	CRect rectDst;

	//����ͷ���ڴ�С
	int nWidth = rect.Width();
	int nHeight = rect.Height();

	if (nWidth < bmpInfo.bmWidth )
	{
		rectDst.left = rect.left;
		rectDst.right = nWidth;
	}
	else
	{
		rectDst.left = rect.left+(nWidth-bmpInfo.bmWidth)/2;
		rectDst.right = bmpInfo.bmWidth;
	}

	if (nHeight < bmpInfo.bmHeight)
	{
		rectDst.top = rect.top;
		rectDst.bottom = rectDst.top + nHeight;
	}
	else
	{
		rectDst.top = rect.top + (nHeight - bmpInfo.bmHeight)/2; ;
		rectDst.bottom = rectDst.top + bmpInfo.bmHeight;
	}

	return rectDst;
}

void CViewChannel::FlashChannel()
{
	//��������������ڵı���ɫ
	FillAllDialogBKColor();

	//���ô�����Ƶ����ı���ͼƬ
	SetBKPicture();

	//���ñ��ⱳ��ͼƬ
	SetTitleBKPicture();
}

/************************************************************************
* ��Ƶͨ���仯
*   �������巢����Ϣ
*    OM_CHANNLECHANGE��  m_iWinID * 0x1000 + 0
************************************************************************/
void CViewChannel::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_byt_ctl == true && m_video_opened == true)
	{
		switch (m_iyt_pos)
		{
		case 1:
			m_iyt_pos = 0;
			m_byt_ctl = false;
			::SetCursor(m_hCursor_up);
			CameraControl(1,0);
			//GetParent()->PostMessage(OM_MESSAGE_CAMERA_CONTROL, 1, 0);
			break;
		case 2:
			m_iyt_pos = 0;
			m_byt_ctl = false;
			::SetCursor(m_hCursor_down);
			CameraControl(2,0);
			//GetParent()->PostMessage(OM_MESSAGE_CAMERA_CONTROL, 2, 0);
			break;
		case 3:
			m_iyt_pos = 0;
			m_byt_ctl = false;
			::SetCursor(m_hCursor_left);
			CameraControl(3,0);
			//GetParent()->PostMessage(OM_MESSAGE_CAMERA_CONTROL, 3, 0);
			break;
		case 4:
			m_iyt_pos = 0;
			m_byt_ctl = false;
			::SetCursor(m_hCursor_right);
			CameraControl(4,0);
			//GetParent()->PostMessage(OM_MESSAGE_CAMERA_CONTROL,4,0);
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
	//g_pMainDlg->SendMessage(OM_DBLCHANNEL, m_iWinID);
	
	CWnd::OnLButtonDblClk(nFlags, point);
}

/************************************************************************
* ��Ƶͨ���Ҽ���������
*   �������巢����Ϣ
*    OM_RIGHTCLICKCHANNEL��  m_iWinID
************************************************************************/
void CViewChannel::OnRButtonUp(UINT nFlags, CPoint point) 
{
	PopRightMenu();
	
	CWnd::OnRButtonUp(nFlags, point);
}

void CViewChannel::PopRightMenu()
{
	CMenu popMenu;
	popMenu.CreatePopupMenu();

	popMenu.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,IDC_MENU_CLOSE_VIDEO,"�ر���Ƶ");

	CPoint point;
	GetCursorPos(&point);

	popMenu.TrackPopupMenu(TPM_RIGHTBUTTON,point.x,point.y,this);
}

void CViewChannel::OnCloseVideo()
{
	CloseCamera();
}

void CViewChannel::OnTimer(UINT nIDEvent) 
{	
	CWnd::OnTimer(nIDEvent);
}

//ֻҪ����ƶ�OnMouseMove�ͻ��Զ�����WM_SETCUROSR��Ϣ���Ӷ�����OnSetCursor
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

			m_csVideo.GetWindowRect(&rc);
			GetCursorPos(&pt);
			
			x0 = 0;
			y0 = 0;
			x1 = rc.right - rc.left;
			y1 = rc.bottom - rc.top;

			xp = pt.x - rc.left;
			yp = pt.y - rc.top;

			posA = yp - (y1 - xp*y1/x1);
			posB = yp - xp*y1/x1;

			if (posA < 0 && posB < 0 && yp < y1/4 && yp > 0)//up
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

	CreateControls();//�����ؼ�

	return 0;
}

void CViewChannel::CreateControls()
{
	m_csTitleCaption.Create("����ͷ����", WS_VISIBLE, CRect(400,400,400,400), this, IDC_STATIC_TITLE_CAPTION);
	m_csTitle.Create(NULL, SS_BLACKFRAME|WS_VISIBLE, CRect(400,400,400,400), this, IDC_STATIC_TITLE);
	m_csVideo.Create(NULL, SS_BLACKFRAME|WS_VISIBLE, CRect(400,400,400,400), this, IDC_STATIC_VIDEO);
}

void CViewChannel::SetTitleCaption(CString strText)
{
	m_csTitleCaption.SetWindowText(strText);

	CRect rect;
	m_csTitleCaption.GetWindowRect(&rect);
	ScreenToClient(&rect);
	InvalidateRect(&rect);//�ֲ�ˢ��
}

void CViewChannel::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//GetParent()->SendMessage(OM_MESSAGE_MULTI_CHANNEL_CHANGE, m_iWinID,0);	//m_iYTID);
	
	Sleep(50);

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

		m_csVideo.GetWindowRect(&rc);
		GetCursorPos(&pt);

		x0 = 0;
		y0 = 0;
		x1 = rc.right - rc.left;
		y1 = rc.bottom - rc.top;

		xp = pt.x - rc.left;
		yp = pt.y - rc.top;

		posA = yp - (y1 - xp*y1/x1);
		posB = yp - xp*y1/x1;

		if (posA < 0 && posB < 0 && yp < y1/4 && yp > 0)//up
		{
			m_byt_ctl = true;
			m_iyt_pos = 1;
			::SetCursor(m_hCursor_up_on);
			CameraControl(1,1);
			//GetParent()->PostMessage(OM_MESSAGE_CAMERA_CONTROL, 1, 1);
			return;
		}

		if (posA > 0 && posB > 0 && yp > 3*y1/4)//down
		{
			m_byt_ctl = true;
			m_iyt_pos = 2;
			::SetCursor(m_hCursor_down_on);
			CameraControl(2,1);
			//GetParent()->PostMessage(OM_MESSAGE_CAMERA_CONTROL, 2, 1);
			return;
		}

		if (posA < 0 && posB > 0 && xp < x1/4)//left
		{
			m_byt_ctl = true;
			m_iyt_pos = 3;
			::SetCursor(m_hCursor_left_on);
			CameraControl(3,1);
			//GetParent()->PostMessage(OM_MESSAGE_CAMERA_CONTROL, 3, 1);
			return;
		}

		if (posA > 0 && posB < 0 && xp > 3*x1/4)//right
		{
			m_byt_ctl = true;
			m_iyt_pos = 4;
			::SetCursor(m_hCursor_right_on);
			CameraControl(4,1);
			//GetParent()->PostMessage(OM_MESSAGE_CAMERA_CONTROL, 4, 1);
			return;
		}
	}
	
	CWnd::OnLButtonDown(nFlags, point);
}

int CViewChannel::CameraControl(unsigned short nCommand)
{
	if (m_video_opened == false)
	{
		return -1;
	}

	DvrPtzControl_Devsdk(m_tCameraInfo.szDvrIP,m_tCameraInfo.nDvrPort,m_tCameraInfo.szLoginName,
		m_tCameraInfo.szLoginPassword,m_tCameraInfo.nDvrType,1,m_tCameraInfo.nChannel,nCommand,m_nControlSpeed);

	return 0;
}

int CViewChannel::CameraControl(int nDirection, int nStartOrStop)
{
	if (m_video_opened == false)
	{
		return -1;
	}

	//�����ֹͣ
	if(nStartOrStop == 0)
	{
		switch (nDirection)
		{
		case 1://��̨������-����
			{
				CameraControl(TILTUPSTOP);
			}
			break;
		case 2://��̨������-����
			{
				CameraControl(TILTDOWNSTOP);
			}
			break;
		case 3://��̨������-����
			{
				CameraControl(PANLEFTSTOP);
			}
			break;
		case 4://��̨������-����
			{
				CameraControl(PANRIGHTSTOP);
			}
			break;
		case 5://����-����
			{
				CameraControl(ZOOMOUTSTOP);
			}
			break;
		case 6://��Զ-����
			{
				CameraControl(ZOOMINSTOP);
			}
			break;
		case 7://��̨���ƽ����-����
			{

			}
			break;
		case 8://��̨���ƽ���Զ-����
			{

			}
			break;
		case 9://��̨���ƹ�ȦС-����
			{

			}
			break;
		case 10://��̨���ƹ�Ȧ��-����
			{

			}
			break;
		case 11://���⿪
			{

			}
			break;
		case 12://�����
			{

			}
			break;
		case 13://���ȿ�
			{

			}
			break;
		case 14:// ���ȹ�
			{
				//ytcommand = 0x0c02;
			}
			break;
		case 15:// �ƹ⿪
			{
				//ytcommand = 0x0b01;
			}
			break;
		case 16:// �ƹ��
			{
				//ytcommand = 0x0b02;
			}
			break;
		case 17:// ��ˢ��
			{
				//ytcommand = 0x0a01;
			}
			break;
		case 18:// ��ˢ��
			{
				//ytcommand = 0x0a02;
			}
			break;
		case 19:
			{
				return 0;
			}
			break;
		}
	}
	else
	{
		switch (nDirection)
		{
		case 1://��̨������-��ʼ
			{
				CameraControl(TILTUP);
			}
			break;
		case 2://��̨������-��ʼ
			{
				CameraControl(TILTDOWN);
			}
			break;
		case 3://��̨������-��ʼ
			{
				CameraControl(PANLEFT);
			}
			break;
		case 4://��̨������-��ʼ
			{
				CameraControl(PANRIGHT);
			}
			break;
		case 5://����-��ʼ
			{
				CameraControl(ZOOMOUT);
			}
			break;
		case 6://��Զ-��ʼ
			{
				CameraControl(ZOOMIN);
			}
			break;
		case 7://��̨���ƽ����-��ʼ
			{
				//ytcommand = 0x0302;
			}
			break;
		case 8://��̨���ƽ���Զ-��ʼ
			{
				//ytcommand = 0x0304;
			}
			break;
		case 9://��̨���ƹ�ȦС-��ʼ
			{
				//ytcommand = 0x0102;
			}
			break;
		case 10://��̨���ƹ�Ȧ��-��ʼ
			{
				//ytcommand = 0x0103;
			}
			break;
		case 11:// ���⿪
			{
				//ytcommand = 0x0d01;
			}
			break;
		case 12:// �����
			{
				//ytcommand = 0x0d02;
			}
			break;
		case 13:// ���ȿ�
			{
				//ytcommand = 0x0c01;
			}
			break;
		case 14:// ���ȹ�
			{
				//ytcommand = 0x0c02;
			}
			break;
		case 15:// �ƹ⿪
			{
				//ytcommand = 0x0b01;
			}
			break;
		case 16:// �ƹ��
			{
				//ytcommand = 0x0b02;
			}
			break;
		case 17:// ��ˢ��
			{
				//ytcommand = 0x0a01;

			}
			break;
		case 18:// ��ˢ��
			{
				//ytcommand = 0x0a02;
			}
			break;
		case 19:
			{
				return 0;
			}
			break;
		}
	}
}

void CViewChannel::ToPreset(int nPresetNum)
{
	if (m_video_opened == false)
	{
		MessageBox("���ȴ�����ͷ��","����ϵͳ");
		return;
	}

	//����ת��Ԥ��λ�ӿں���
	int nRet = DvrPtzControl_Devsdk(m_tCameraInfo.szDvrIP,m_tCameraInfo.nDvrPort,m_tCameraInfo.szLoginName,
		m_tCameraInfo.szLoginPassword,m_tCameraInfo.nDvrType,1,m_tCameraInfo.nChannel,GOTOPRESET,nPresetNum);
	if (nRet == FALSE)
	{
		MessageBox("ת��Ԥ��λʧ�ܣ�","����ϵͳ");
		return ;
	}
}

BOOL CViewChannel::DeletePreset(int nPresetNum)
{
	if (m_video_opened == false)
	{
		MessageBox("���ȴ�����ͷ��","����ϵͳ");
		return FALSE;
	} 
	//������ͷ�ϵ�Ԥ��λɾ��
	int nRet = DvrPtzControl_Devsdk(m_tCameraInfo.szDvrIP,m_tCameraInfo.nDvrPort,m_tCameraInfo.szLoginName,
		m_tCameraInfo.szLoginPassword,m_tCameraInfo.nDvrType,1,m_tCameraInfo.nChannel,CLEPRESET,nPresetNum);

	if (nRet == FALSE)
	{
		MessageBox("Ԥ��λɾ��ʧ�ܣ�","����ϵͳ");
		return FALSE;
	}

	return TRUE;
}

BOOL CViewChannel::SetPreset(int nPresetNum)
{
	if (m_video_opened == false)
	{
		MessageBox("���ȴ�����ͷ��","����ϵͳ");
		return FALSE;
	}

	//�������������Ԥ��λ
	bool bRet = DvrPtzControl_Devsdk(m_tCameraInfo.szDvrIP,m_tCameraInfo.nDvrPort,m_tCameraInfo.szLoginName,
		m_tCameraInfo.szLoginPassword,m_tCameraInfo.nDvrType,1,m_tCameraInfo.nChannel,SETPRESET,nPresetNum);
	if (!bRet)
	{
		MessageBox("Ԥ��λ����ʧ�ܣ�","����ϵͳ");
		return FALSE;
	}

	return TRUE;
}

void CViewChannel::SetControlSpeed(int nSpeed)
{
	m_nControlSpeed = nSpeed;
}

void CViewChannel::OnSize(UINT nType, int cx, int cy) 
{
	int nTitleHeight = 34;
	int nTitleWidth = cx;

	int nVideoHeight = cy - nTitleHeight;
	int nVideoWidth = cx;

	m_csTitle.MoveWindow(CRect(0,0,cx,nTitleHeight));
	m_csTitleCaption.MoveWindow(CRect(0,0,cx,nTitleHeight));
	m_csVideo.MoveWindow(CRect(0,nTitleHeight,cx,cy));
	CWnd::OnSize(nType, cx, cy);
}

HBRUSH CViewChannel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TITLE_CAPTION)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

//������Ƶ��Ϣ
void CViewChannel::SetCameraInfo( T_CAMERA_INFO tCameraInfo )
{
	m_tCameraInfo = tCameraInfo;
}

void CViewChannel::CloseCamera()
{
	if (m_nCurrentVideoId != -1)
	{
		CloseVideo_DevSdk(m_nCurrentVideoId);
		m_nCurrentVideoId = -1;
		m_video_opened = false;
		SetTitleCaption("����ͷ����");

		Sleep(1000);		
	}
}

int CViewChannel::OpenCamera()
{
	CloseCamera();

	int nID = GetID_DevSdk();

	int nRes = OpenVideo_DevSdk(m_tCameraInfo.szDvrIP,
		m_tCameraInfo.nDvrPort,
		m_tCameraInfo.szLoginName,
		m_tCameraInfo.szLoginPassword,
		m_tCameraInfo.nDvrType,
		1,
		m_tCameraInfo.nChannel,
		nID,
		m_csVideo.GetSafeHwnd());

	if (nRes != 0)
	{
		AfxMessageBox("����Ƶʧ�ܣ�");
		return -1;
	}

	m_nCurrentVideoId = nID;
	m_video_opened = true;
	SetTitleCaption(m_tCameraInfo.szCameraName);

	return 0;
}