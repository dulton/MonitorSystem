// DlgPageViewSelect.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "DlgPageViewSelect.h"


// CDlgPageViewSelect �Ի���

IMPLEMENT_DYNAMIC(CDlgPageViewSelect, CDialog)

CDlgPageViewSelect::CDlgPageViewSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPageViewSelect::IDD, pParent)
	, m_nPosType(1)
	, m_strPreStation(_T(""))
	, m_strCurrentStation(_T(""))
	, m_strFirstStation(_T(""))
{

}

CDlgPageViewSelect::~CDlgPageViewSelect()
{
}

void CDlgPageViewSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_RESUME, m_nPosType);
	DDX_Text(pDX, IDC_EDIT_PRE, m_strPreStation);
	DDX_Text(pDX, IDC_EDIT_CURRENT, m_strCurrentStation);
	DDX_Text(pDX, IDC_EDIT_FIRST, m_strFirstStation);
	DDX_Control(pDX, IDC_BTN_START, m_btnStart);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btnCancel);
	DDX_Control(pDX, ID_BTN_EXIT, m_btnExit);
}


BEGIN_MESSAGE_MAP(CDlgPageViewSelect, CDialog)
	ON_BN_CLICKED(IDC_BTN_START, &CDlgPageViewSelect::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CDlgPageViewSelect::OnBnClickedBtnCancel)
	ON_BN_CLICKED(ID_BTN_EXIT, &CDlgPageViewSelect::OnBnClickedBtnExit)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgPageViewSelect ��Ϣ�������

BOOL CDlgPageViewSelect::OnInitDialog()
{
	CDialog::OnInitDialog();

	//////////////////////////////////////////////////////////////////////////

	m_BgBrush.CreateSolidBrush(RGB(189, 231, 231));         // ��������ɫ

	LoadSkin();

	return TRUE; 
}

BOOL CDlgPageViewSelect::LoadSkin()
{
	m_Bmp.LoadBitmap(IDB_BITMAP_PAGEVIEW_SELECT);
	m_Bmp.GetObject(sizeof(BITMAP),(LPVOID)&m_bm);   

	m_btnStart.LoadBitmap(IDB_BITMAP_BTN_START);
	m_btnCancel.LoadBitmap(IDB_BITMAP_CANCEL_PAGEVIEW_TIME);
	m_btnExit.LoadBitmap(IDB_BITMAP_MENU_QUIT);

	return TRUE;
}

void CDlgPageViewSelect::OnBnClickedBtnStart()
{
	UpdateData(TRUE);

	switch(m_nPosType)
	{
	case 0:
		{
			if(m_strPreStation.IsEmpty())
			{
				MessageBox("�ϴν���λ�ñ��վΪ�գ�","�˹�Ѳ��",MB_ICONWARNING);
				return;
			}
		}
		break;

	case 1:
		{
			if(m_strCurrentStation.IsEmpty())
			{
				MessageBox("��ǰѡ��λ�ñ��վΪ�գ�","�˹�Ѳ��",MB_ICONWARNING);
				return;
			}
		}
		break;

	case 2:
		{
			if(m_strFirstStation.IsEmpty())
			{
				MessageBox("��λλ�ñ��վΪ�գ�","�˹�Ѳ��",MB_ICONWARNING);
				return;
			}
		}
		break;

	default:
		return;
	}

	OnOK();
}

void CDlgPageViewSelect::OnBnClickedBtnCancel()
{
	OnCancel();
}

void CDlgPageViewSelect::OnBnClickedBtnExit()
{
	OnCancel();
}

BOOL CDlgPageViewSelect::OnEraseBkgnd(CDC* pDC)
{
	CRect   rect;
	GetClientRect(&rect);
	CDC   dcMem;

	dcMem.CreateCompatibleDC(pDC);   
	CBitmap* pOldBitmap = dcMem.SelectObject(&m_Bmp);   

	pDC->StretchBlt(rect.left,
		rect.top,
		rect.right,
		rect.bottom,
		&dcMem,
		0,
		0,
		m_bm.bmWidth,
		m_bm.bmHeight,
		SRCCOPY);

	dcMem.SelectObject(pOldBitmap);

	return TRUE;
}

HBRUSH CDlgPageViewSelect::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	//////////////////////////////////////////////////////////////////////////
	if (pWnd->GetDlgCtrlID() == IDC_RADIO_RESUME)
	{
		// ����ɫ͸��
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(10,10,10));

		// ���ر���ɫ�Ļ�ˢ
		return m_BgBrush;
	}

	if (pWnd->GetDlgCtrlID() == IDC_RADIO_CURRENT)
	{
		// ����ɫ͸��
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(10,10,10));

		// ���ر���ɫ�Ļ�ˢ
		return m_BgBrush;
	}

	if (pWnd->GetDlgCtrlID() == IDC_RADIO_HEAD)
	{
		// ����ɫ͸��
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(10,10,10));

		// ���ر���ɫ�Ļ�ˢ
		return m_BgBrush;
	}

	if (pWnd->GetDlgCtrlID() == IDC_EDIT_PRE)
	{
		// ����ɫ͸��
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(10,10,10));

		// ���ر���ɫ�Ļ�ˢ
		return m_BgBrush;
	}

	if (pWnd->GetDlgCtrlID() == IDC_EDIT_CURRENT)
	{
		// ����ɫ͸��
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(10,10,10));

		// ���ر���ɫ�Ļ�ˢ
		return m_BgBrush;
	}

	if (pWnd->GetDlgCtrlID() == IDC_EDIT_FIRST)
	{
		// ����ɫ͸��
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(10,10,10));

		// ���ر���ɫ�Ļ�ˢ
		return m_BgBrush;
	}


	//////////////////////////////////////////////////////////////////////////
	return hbr;
}
