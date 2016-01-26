// DlgDeviceTypeConfig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LinkageSetting.h"
#include "DlgDeviceTypeConfig.h"
#include "common.h"
#include "DBExcute.h"


// CDlgDeviceTypeConfig �Ի���

IMPLEMENT_DYNAMIC(CDlgDeviceTypeConfig, CDialog)

//��ק������ʱ��Ļص�����
void CB_AddItems(CMultiTreeCtrl *pSrcTree, CMultiTreeCtrl *pDestTree, HTREEITEM hSrcTItem, HTREEITEM hDestTItem, int nImage, int nSelImage)
{
	////�����ק��Ŀ�ĵ����Լ����򷵻�
	//if (pSrcTree == pDestTree)
	//	return;

	//�����ק��Դ�����豸���ͽڵ㷵��
	T_ASS_TREE_NODE* pSrcTreeNode = (T_ASS_TREE_NODE*)pSrcTree->GetItemData(hSrcTItem);
	if (pSrcTreeNode->enumTreeNodeType != ENUM_DEVICE_TYPE_NODE)
		return;

	//�����ק��Ŀ�ĵز�����ϵͳ���򷵻�
	T_ASS_TREE_NODE* pDstTreeNode = (T_ASS_TREE_NODE*)pDestTree->GetItemData(hDestTItem);
	if (pDstTreeNode->enumTreeNodeType != ENUM_SUBSYSTEM_NODE)
		return;

	//���Ŀ�Ľڵ�
	HTREEITEM hChildItem = pDestTree->AddItem(hDestTItem, pSrcTree->GetItemText(hSrcTItem), TVI_LAST, nImage, nSelImage, 0);
	SetTreeItemData(pDestTree, hChildItem, pSrcTreeNode->enumTreeNodeType, (char*)pSrcTreeNode->body, sizeof(T_ASS_DEVICE_TYPE));
	pDestTree->SendMessage(TVM_SELECTITEM, TVGN_DROPHILITE,0);
	pDestTree->Expand(hDestTItem, TVE_EXPAND);

	//�������ݿ�,�����豸���͵���ϵͳ
	T_ASS_SUBSYSTEM *pSubSystem = (T_ASS_SUBSYSTEM*)pDstTreeNode->body;
	int nSubSystemId = pSubSystem->nId;
	UpdateSubSystemOfDeviceType(pSrcTree->GetItemText(hSrcTItem), nSubSystemId);

	//ɾ��Դ�ڵ�
	FreeOneTreeNode(pSrcTree, hSrcTItem);

	return;
}

CDlgDeviceTypeConfig::CDlgDeviceTypeConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDeviceTypeConfig::IDD, pParent)
{

}

CDlgDeviceTypeConfig::~CDlgDeviceTypeConfig()
{
}

void CDlgDeviceTypeConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDeviceTypeConfig, CDialog)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgDeviceTypeConfig ��Ϣ�������

BOOL CDlgDeviceTypeConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitControl();

	InitDeviceTypeTree();

	InitSubSystemTree();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgDeviceTypeConfig::InitControl()
{
	m_pBackBmp = new CBitmap;
	m_pBackBmp->LoadBitmap(IDB_BITMAP_BACK);

	RECT rect = {10,10,210,300};
	m_treeDeviceType.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|TVS_TRACKSELECT
		|TVS_SHOWSELALWAYS, rect, this, 1001);

	RECT rect1 = {10,200,210,300};
	m_treeSubSystem.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|TVS_TRACKSELECT
		|TVS_SHOWSELALWAYS, rect1, this, 1002);

	m_imageList.Create(IDB_BITMAP_TREE,16,0,RGB(255,0,255));
	m_treeDeviceType.SetImageList(&m_imageList, TVSIL_NORMAL);
	m_treeSubSystem.SetImageList(&m_imageList, TVSIL_NORMAL);

	//ע����ק������ʱ���õĻص���������������ã���ʹ��Ĭ�ϴ���
	m_treeSubSystem.SetCBAddItems(CB_AddItems);
	m_treeDeviceType.SetCBAddItems(CB_AddItems);
}

void CDlgDeviceTypeConfig::InitDeviceTypeTree()
{
	//ɾ���������е��豸����
	FreeTreeNode(&m_treeDeviceType, m_treeDeviceType.GetRootItem());

	//��ȡ�豸���Ͳ������ڵ��
	std::vector<T_ASS_DEVICE_TYPE> vecDeviceType = GetDeviceTypeFromDB();
	
	//��ӵ�����
	AddDeviceTypeToTree(vecDeviceType);
} 

void CDlgDeviceTypeConfig::AddDeviceTypeToTree(std::vector<T_ASS_DEVICE_TYPE> vecDeviceType)
{
	HTREEITEM hRootItem = NULL;
	HTREEITEM hChildItem = NULL;
	hRootItem = m_treeDeviceType.InsertItem("ȫ������", 8, 8, TVI_ROOT, NULL);
	SetTreeItemData(&m_treeDeviceType, hRootItem, TREE_NODE_TYPE::ENUM_ROOT_NODE, NULL, 0);
	for (size_t t = 0; t < vecDeviceType.size(); t++)
	{
		if (vecDeviceType.at(t).nParentId == 0)
		{
			hChildItem = m_treeDeviceType.InsertItem(vecDeviceType.at(t).szDeviceTypeName, 8, 8, hRootItem);
			SetTreeItemData(&m_treeDeviceType, hChildItem, TREE_NODE_TYPE::ENUM_DEVICE_TYPE_NODE, (char*)&vecDeviceType.at(t), sizeof(T_ASS_DEVICE_TYPE));
		}
	}
}

void CDlgDeviceTypeConfig::InitSubSystemTree()
{
	//ɾ���������е��豸����
	FreeTreeNode(&m_treeSubSystem, m_treeSubSystem.GetRootItem());

	//��ȡ��ϵͳ
	std::vector<T_ASS_SUBSYSTEM> vecSubSystem = GetSubSystemFromDB();

	//��ӵ�����
	AddSubSystemToTree(vecSubSystem);

	//ȫ��չ��
	ExpandAllItems(&m_treeSubSystem, NULL);
}

void CDlgDeviceTypeConfig::AddSubSystemToTree(std::vector<T_ASS_SUBSYSTEM> vecSubSystem)
{
	//��ȡ��ϵͳ�µ��豸����
	std::vector<T_ASS_DEVICE_TYPE> vecDeviceType = GetDeviceTypeFromDB();

	HTREEITEM hRootItem = NULL;
	HTREEITEM hChildItem = NULL;
	HTREEITEM hDeviceTypeItem = NULL;
	hRootItem = m_treeSubSystem.InsertItem("ȫ����ϵͳ", 8, 8, TVI_ROOT, NULL);
	SetTreeItemData(&m_treeSubSystem, hRootItem, TREE_NODE_TYPE::ENUM_ROOT_NODE, NULL, 0);
	for (size_t t = 0; t < vecSubSystem.size(); t++)
	{
		hChildItem = m_treeSubSystem.InsertItem(vecSubSystem.at(t).szSubSystemName, 8, 8, hRootItem);
		SetTreeItemData(&m_treeSubSystem, hChildItem, TREE_NODE_TYPE::ENUM_SUBSYSTEM_NODE, (char*)&vecSubSystem.at(t), sizeof(T_ASS_SUBSYSTEM));
		
		for (int i=0; i<vecDeviceType.size(); i++)
		{
			if (vecDeviceType.at(i).nParentId == vecSubSystem.at(t).nId)
			{
				hDeviceTypeItem = m_treeSubSystem.InsertItem(vecDeviceType.at(i).szDeviceTypeName, 10, 10, hChildItem);
				SetTreeItemData(&m_treeSubSystem, hDeviceTypeItem, TREE_NODE_TYPE::ENUM_DEVICE_TYPE_NODE, (char*)&vecDeviceType.at(t), sizeof(T_ASS_DEVICE_TYPE));
			}
		}
	}
}

void CDlgDeviceTypeConfig::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect static_rect,winrc,tree_rect;
	GetClientRect(&winrc);
	int nStaticWidth = cx * 0.1;
	int nStaticHeight = 30;

	int nTreeWidth = cx * 0.2;
	int nTreeHeight = cy - nStaticHeight;

	CWnd * pWnd = NULL;
	pWnd = GetDlgItem(IDC_STATIC_DEVICE_TYPE);
	if (pWnd != NULL)
	{
		static_rect.top = winrc.top;
		static_rect.bottom = static_rect.top + nStaticHeight;
		static_rect.left = winrc.left;
		static_rect.right = static_rect.left + nStaticWidth;
		pWnd->MoveWindow(static_rect);
	}

	//pWnd = GetDlgItem(IDC_TREE_DEVICE_TYPE);
	if (m_treeDeviceType)
	{
		static_rect.top = static_rect.bottom;
		static_rect.bottom = static_rect.top + nTreeHeight;
		static_rect.left = winrc.left;
		static_rect.right = static_rect.left + nTreeWidth;
		m_treeDeviceType.MoveWindow(static_rect);
	}

	pWnd = GetDlgItem(IDC_STATIC_SUB_SYSTEM);
	if (pWnd != NULL)
	{
		static_rect.top = winrc.top;
		static_rect.bottom = static_rect.top + nStaticHeight;
		static_rect.left = static_rect.right + 30;
		static_rect.right = static_rect.left + nStaticWidth;
		pWnd->MoveWindow(static_rect);
	}

	//pWnd = GetDlgItem(IDC_TREE_SUB_SYSTEM);
	if (m_treeSubSystem)
	{
		static_rect.top = static_rect.bottom;
		static_rect.bottom = static_rect.top + nTreeHeight;
		static_rect.left = static_rect.left;
		static_rect.right = static_rect.left + nTreeWidth;
		m_treeSubSystem.MoveWindow(static_rect);
	}
}

BOOL CDlgDeviceTypeConfig::OnEraseBkgnd(CDC* pDC)
{
	//���öԻ��򱳾�ɫ
	CBrush backBrush(RGB(218,255,251));
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect;
	pDC->GetClipBox(&rect);

	//����Ҫ������
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//CDC srcDC;
	//srcDC.CreateCompatibleDC(pDC);
	//CBitmap* pOldBmp;
	//BITMAP bmp;
	//CRect winrc;

	//GetClientRect(&winrc);

	//pOldBmp = srcDC.SelectObject(m_pBackBmp);
	//m_pBackBmp->GetBitmap(&bmp);
	//pDC->StretchBlt(0,0,winrc.Width(),winrc.Height(),
	//	&srcDC,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	//srcDC.SelectObject(pOldBmp);
	return TRUE;

	return CDialog::OnEraseBkgnd(pDC);
}

BOOL CDlgDeviceTypeConfig::PreTranslateMessage(MSG* pMsg)
{
	return FALSE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgDeviceTypeConfig::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//m_treeSubSystem.OnMouseMove(nFlags, point);
	//m_treeDeviceType.OnMouseMove(nFlags, point);

	CDialog::OnMouseMove(nFlags, point);
}

void CDlgDeviceTypeConfig::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//m_treeSubSystem.OnLButtonUp(nFlags, point);
	//m_treeDeviceType.OnLButtonUp(nFlags, point);

	CDialog::OnLButtonUp(nFlags, point);
}

HBRUSH CDlgDeviceTypeConfig::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
