// DlgVideoParSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "DlgVideoParSet.h"
#include "VEMCUCtlDlg.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


// CDlgVideoParSet �Ի���

IMPLEMENT_DYNAMIC(CDlgVideoParSet, CDialog)

CDlgVideoParSet::CDlgVideoParSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVideoParSet::IDD, pParent)
{

}

CDlgVideoParSet::~CDlgVideoParSet()
{
}

void CDlgVideoParSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_BRITE, m_titlebrite);
	DDX_Control(pDX, IDC_STATIC_BAOHE, m_titlebaohe);
	DDX_Control(pDX, IDC_STATIC_DUIBI, m_titleduibi);
	DDX_Control(pDX, IDC_STATIC_SE, m_titlese);
	DDX_Control(pDX, IDC_SLIDER_BRITE, m_sliderbrite);
	DDX_Control(pDX, IDC_SLIDER_BAOHE, m_sliderbaohe);
	DDX_Control(pDX, IDC_SLIDER_SEDU, m_slidersedu);
	DDX_Control(pDX, IDC_SLIDER_DUIBI, m_sliderduibi);
	DDX_Control(pDX, IDC_SETVIEWSET, m_btnSetViewPar);
	DDX_Control(pDX, IDC_GETVIEWSET, m_btnDefaultViewPar);
}


BEGIN_MESSAGE_MAP(CDlgVideoParSet, CDialog)
	ON_COMMAND_RANGE(1000, 2000, OnControlButton)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDlgVideoParSet ��Ϣ�������

BOOL CDlgVideoParSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_titlebrite.SetTransparent(TRUE);					//���ñ���͸��ɫ �����ȡ�
	m_titlebrite.SetTextColor(RGB(41, 41, 53));		//����������ɫ

	m_titlebaohe.SetTransparent(TRUE);					//���ñ���͸��ɫ �����Ͷȡ�
	m_titlebaohe.SetTextColor(RGB(41, 41, 53));		//����������ɫ

	m_titleduibi.SetTransparent(TRUE);					//���ñ���͸��ɫ ���Աȶȡ�
	m_titleduibi.SetTextColor(RGB(41, 41, 53));		//����������ɫ

	m_titlese.SetTransparent(TRUE);					//���ñ���͸��ɫ ��ɫ�ȡ�
	m_titlese.SetTextColor(RGB(41, 41, 53));		//����������ɫ

	//���Ƚ�����
	m_sliderbrite.SetBitmapChannel(IDB_BITMAP_OFF, IDB_BITMAP_ON, TRUE);
	m_sliderbrite.SetRange( 0, 255 );
	m_sliderbrite.SetPos( 127 );
	m_sliderbrite.SetMarginLeft( 4 );
	m_sliderbrite.SetMarginRight( 4 );
	m_sliderbrite.SetPageSize( 25 );
	m_sliderbrite.DrawFocusRect( FALSE );
	
	//���ͶȽ�����
	m_sliderbaohe.SetBitmapChannel(IDB_BITMAP_OFF, IDB_BITMAP_ON, TRUE);
	m_sliderbaohe.SetRange( 0, 255 );
	m_sliderbaohe.SetPos( 127 );
	m_sliderbaohe.SetMarginLeft( 4 );
	m_sliderbaohe.SetMarginRight( 4 );
	m_sliderbaohe.SetPageSize( 25 );
	m_sliderbaohe.DrawFocusRect( FALSE );
	
	//ɫ�Ƚ�����
	m_slidersedu.SetBitmapChannel(IDB_BITMAP_OFF, IDB_BITMAP_ON, TRUE);
	m_slidersedu.SetRange( 0, 255 );
	m_slidersedu.SetPos( 127 );
	m_slidersedu.SetMarginLeft( 4 );
	m_slidersedu.SetMarginRight( 4 );
	m_slidersedu.SetPageSize( 25 );
	m_slidersedu.DrawFocusRect( FALSE );
	
	//�ԱȶȽ�����
	m_sliderduibi.SetBitmapChannel(IDB_BITMAP_OFF, IDB_BITMAP_ON, TRUE);
	m_sliderduibi.SetRange( 0, 255 );
	m_sliderduibi.SetPos( 127 );
	m_sliderduibi.SetMarginLeft( 4 );
	m_sliderduibi.SetMarginRight( 4 );
	m_sliderduibi.SetPageSize( 25 );
	m_sliderduibi.DrawFocusRect( FALSE );

	m_btnSetViewPar.LoadBitmap(IDB_BITMAP_VIEWSET, 0);
	m_btnDefaultViewPar.LoadBitmap(IDB_BITMAP_VIEWGET, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BOOL CDlgVideoParSet::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==0x100   &&   pMsg->wParam==27)//��סESC
		return	TRUE;
	if(pMsg->message==0x100   &&   pMsg->wParam==13)//��סENTER   
		return	TRUE; 
	if(pMsg->message==0x100   &&   pMsg->wParam==VK_SPACE)
		return	TRUE;
	if(pMsg->message==0x100   &&   pMsg->wParam==VK_SPACE)
		return	TRUE;
	if((pMsg->message == WM_KEYDOWN || pMsg->message == WM_KEYUP) 
		&& (pMsg->wParam == 27 || pMsg->wParam== 13 || pMsg->wParam == 32))
		return TRUE;

	return CDialog::PreTranslateMessage(pMsg);
}

//����ؿ��ư�ť����Ϣ���͵����Ի�����д���
void CDlgVideoParSet::OnControlButton(UINT nID)
{
	g_pMainDlg->PostMessage(OM_CONTROLBUTTON, nID,VEM_CONTROL_BUTTON_MESSAGE_TYPE_PAGESERVER);
}
BOOL CDlgVideoParSet::OnEraseBkgnd(CDC* pDC)
{
	CRect   rect;
	GetWindowRect(&rect);
	CBitmap   m_pBmp;
	BITMAP   bm;
	CDC   dcMem;
	CBitmap*   pOldBitmap;

	m_pBmp.LoadBitmap(IDB_BITMAP_TOTAL_BG);
	m_pBmp.GetObject(sizeof(BITMAP),(LPVOID)&bm);
	dcMem.CreateCompatibleDC(pDC);
	pOldBitmap = dcMem.SelectObject(&m_pBmp);

	pDC->StretchBlt(
		rect.left + 2,
		rect.top + 5,
		rect.right - 4,
		rect.bottom - 5,
		&dcMem,
		0,
		0,
		bm.bmWidth,
		bm.bmHeight,
		SRCCOPY);
	(dcMem.SelectObject(pOldBitmap))->DeleteObject();
	dcMem.DeleteDC();

	return true;
}
