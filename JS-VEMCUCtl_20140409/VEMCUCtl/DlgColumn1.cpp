// DlgColumn1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "DlgColumn1.h"


// CDlgColumn1 �Ի���

IMPLEMENT_DYNAMIC(CDlgColumn1, CDialog)

CDlgColumn1::CDlgColumn1(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgColumn1::IDD, pParent)
{

}

CDlgColumn1::~CDlgColumn1()
{
}

void CDlgColumn1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgColumn1, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgColumn1 ��Ϣ�������

void CDlgColumn1::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	//�ı䱳��ɫ
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(181,212,254));
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}
