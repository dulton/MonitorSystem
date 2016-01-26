// DlgPreSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "DlgPreSet.h"
#include "VEMCUCtlDlg.h"
#include "DlgPreSetName.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


// CDlgPreSet �Ի���

IMPLEMENT_DYNAMIC(CDlgPreSet, CDialog)

CDlgPreSet::CDlgPreSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreSet::IDD, pParent)
{

}

CDlgPreSet::~CDlgPreSet()
{
}

void CDlgPreSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PRESET_NAME, m_Combo_PreSet);
}


BEGIN_MESSAGE_MAP(CDlgPreSet, CDialog)
	ON_COMMAND_RANGE(1000, 2000, OnControlButton)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


//����ؿ��ư�ť����Ϣ���͵����Ի�����д���
void CDlgPreSet::OnControlButton(UINT nID)
{
	if (nID != IDC_BUTTON_MODIFYNAME)
	{
		g_pMainDlg->PostMessage(OM_CONTROLBUTTON, nID);
	}
	else
	{
		OnBnClickedButtonModifyName();
	}
}

// CDlgPreSet ��Ϣ�������

BOOL CDlgPreSet::OnEraseBkgnd(CDC* pDC)
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


BOOL CDlgPreSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BOOL CDlgPreSet::PreTranslateMessage(MSG* pMsg)
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

void CDlgPreSet::DisplayPresetName()
{

}

void CDlgPreSet::OnBnClickedButtonModifyName()
{

}