// TWTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MyTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl

CMyTreeCtrl::CMyTreeCtrl()
{
	m_uFlags=0;
}

CMyTreeCtrl::~CMyTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CMyTreeCtrl)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY_REFLECT(NM_CLICK, OnStateIconClick)
	ON_NOTIFY_REFLECT(TVN_KEYDOWN, OnKeydown)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl message handlers

void CMyTreeCtrl::OnStateIconClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_uFlags&TVHT_ONITEMSTATEICON) *pResult=1;
	else *pResult = 0;
}

void CMyTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	HTREEITEM hItem =HitTest(point, &m_uFlags);
	if ( (m_uFlags&TVHT_ONITEMSTATEICON ))
	{
		//nState: 0->��ѡ��ť 1->û��ѡ�� 2->����ѡ�� 3->ȫ��ѡ��
	//	UINT nState = GetItemState( hItem, TVIS_STATEIMAGEMASK );// >> 12;
		BOOL checked = GetCheck(hItem);
		//nState=(nState==3)?1:3;
		SetCheck( hItem, !checked);
	}
	
	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void CMyTreeCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
 	//����ո��
 /*	if(nChar==0x20)
 	{
 		HTREEITEM hItem =GetSelectedItem();
 		UINT nState = GetItemState( hItem, TVIS_STATEIMAGEMASK ) ;//>> 12;
 		if(nState!=0)
 		{
 			//nState=(nState==3)?1:3;
 			SetItemState( hItem, nState, TVIS_STATEIMAGEMASK );
 		}
 	}
	else */
	CTreeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMyTreeCtrl::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_KEYDOWN* pTVKeyDown = (TV_KEYDOWN*)pNMHDR;
	
	*pResult = 0;
}

BOOL CMyTreeCtrl::SetCheck(HTREEITEM hItem, BOOL fCheck)
{
	BOOL bReturn=CTreeCtrl::SetCheck( hItem, fCheck );

	TravelChild(hItem, fCheck);
	TravelSiblingAndParent(hItem,fCheck);
	return bReturn;
}

void CMyTreeCtrl::TravelChild(HTREEITEM hItem, BOOL fCheck)
{
	HTREEITEM hChildItem,hBrotherItem;
	
	//�����ӽڵ㣬û�оͽ���
	hChildItem=GetChildItem(hItem);
	if(hChildItem!=NULL)
	{
		//�����ӽڵ��״̬�뵱ǰ�ڵ��״̬һ��
		CTreeCtrl::SetCheck( hChildItem, fCheck );
		//�ٵݹ鴦���ӽڵ���ӽڵ���ֵܽڵ�
		TravelChild(hChildItem, fCheck);
		
		//�����ӽڵ���ֵܽڵ�����ӽڵ�
		hBrotherItem=GetNextSiblingItem(hChildItem);
		while (hBrotherItem)
		{
			//�����ӽڵ���ֵܽڵ�״̬�뵱ǰ�ڵ��״̬һ��
			CTreeCtrl::SetCheck( hBrotherItem, fCheck );
			//�ٵݹ鴦���ӽڵ���ֵܽڵ���ӽڵ���ֵܽڵ�
			TravelChild(hBrotherItem, fCheck);
			hBrotherItem=GetNextSiblingItem(hBrotherItem);
		}
	}
}

void CMyTreeCtrl::GetCheckItems(std::vector<HTREEITEM>& vecTreeItems, HTREEITEM hTreeItem)
{
	if (hTreeItem == NULL)
	{
		hTreeItem = GetRootItem();
	}

	HTREEITEM hNextItem = GetChildItem(hTreeItem);
	while(hNextItem!=NULL)
	{
		GetCheckItems(vecTreeItems, hNextItem);
		hNextItem = GetNextItem(hNextItem,TVGN_NEXT);
	}

	if (hTreeItem!=NULL)
	{
		//����ýڵ㸴ѡ��ѡ��
		if (GetCheck(hTreeItem))
		{
			vecTreeItems.push_back(hTreeItem);
		}
	}
}

void CMyTreeCtrl::TravelSiblingAndParent(HTREEITEM hItem, BOOL fCheck)
{
	HTREEITEM hNextSiblingItem,hPrevSiblingItem,hParentItem;
	
	//���Ҹ��ڵ㣬û�оͽ���
	hParentItem=GetParentItem(hItem);
	if(hParentItem!=NULL)
	{
		BOOL nChecked1=fCheck;//���ʼֵ����ֹû���ֵܽڵ�ʱ����
		
		//���ҵ�ǰ�ڵ�������ֵܽڵ��״̬
		hNextSiblingItem=GetNextSiblingItem(hItem);
		while(hNextSiblingItem!=NULL)
		{
			nChecked1 = GetCheck( hNextSiblingItem );
			if(nChecked1!=fCheck) 
				break;
			else 
				hNextSiblingItem=GetNextSiblingItem(hNextSiblingItem);
		}
		
		if(nChecked1==fCheck)
		{
			//���ҵ�ǰ�ڵ�������ֵܽڵ��״̬
			hPrevSiblingItem=GetPrevSiblingItem(hItem);
			while(hPrevSiblingItem!=NULL)
			{
				nChecked1 = GetCheck( hPrevSiblingItem );
				if(nChecked1!=fCheck)
					break;
				else 
					hPrevSiblingItem=GetPrevSiblingItem(hPrevSiblingItem);
			}
		}
		
		if(nChecked1==fCheck )
		{
			//���״̬һ�£��򸸽ڵ��״̬�뵱ǰ�ڵ��״̬һ��
			CTreeCtrl::SetCheck( hParentItem, fCheck);
			//�ٵݹ鴦���ڵ���ֵܽڵ���丸�ڵ�
			TravelSiblingAndParent(hParentItem,fCheck);
		}
		else
		{
			//״̬��һ�£���ǰ�ڵ�ĸ��ڵ㡢���ڵ�ĸ��ڵ㡭��״̬��Ϊ����̬
			hParentItem=GetParentItem(hItem);
			while(hParentItem!=NULL)
			{
				nChecked1 = GetCheck( hParentItem) ;
				if(nChecked1!=0)
				{
					CTreeCtrl::SetCheck( hParentItem, fCheck);
				}
				hParentItem=GetParentItem(hParentItem);
			}
		}
	}	
}

