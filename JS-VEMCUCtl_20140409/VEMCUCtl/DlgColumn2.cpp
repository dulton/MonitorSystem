// DlgColumn2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "DlgColumn2.h"


// CDlgColumn2 �Ի���

IMPLEMENT_DYNAMIC(CDlgColumn2, CDialog)

CDlgColumn2::CDlgColumn2(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgColumn2::IDD, pParent)
{

}

CDlgColumn2::~CDlgColumn2()
{
}

void CDlgColumn2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgColumn2, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgColumn2 ��Ϣ�������

void CDlgColumn2::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(181,212,254));
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}
