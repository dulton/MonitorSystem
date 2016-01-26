/*************************************************
Copyright undefined.
�ļ����ƣ� MultiTreeCtrl.cpp
ģ����ƣ� ¬ҵ��
ģ���д�� ¬ҵ��
���ܣ� ����ѡ�����ק�����οؼ��࣮
�汾�ţ� V2013.3.13
��Ҫ������ 
	void TravelSiblingAndParent(HTREEITEM hItem, int nState);
	void TravelChild(HTREEITEM hItem,int nState);
***************************************************/

#include "stdafx.h"
#include "..\resource.h"
#include "MultiTreeCtrl.h"
//#include "../../ShapeUp/ShapeUp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMultiTreeCtrl

CMultiTreeCtrl::CMultiTreeCtrl()
{
	m_bDragging    = FALSE;
	m_uClickFlags  = 0;
    m_uDragFlags   = 0;
	m_nHoverTimerID = 0;
	m_nScrollTimerID = 0;
	m_hDragLeft    = AfxGetApp()->LoadCursor(IDB_BITMAP_BG  );
	m_hDragRight   = AfxGetApp()->LoadCursor(IDB_BITMAP_BG );
	m_hDragAbove   = AfxGetApp()->LoadCursor(IDB_BITMAP_BG );
	m_hDragBelow   = AfxGetApp()->LoadCursor(IDB_BITMAP_BG );
	m_hDragAppend  = AfxGetApp()->LoadCursor(IDB_BITMAP_BG);
 	m_hDragCancel  = AfxGetApp()->LoadCursor(IDB_BITMAP_BG);
}

CMultiTreeCtrl::~CMultiTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CMultiTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CMultiTreeCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_NOTIFY_REFLECT(NM_CLICK, OnStateIconClick)
//	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiTreeCtrl message handlers

void CMultiTreeCtrl::OnStateIconClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_uClickFlags&TVHT_ONITEMSTATEICON)
	{
		CWnd* pWnd = GetParent();
		pWnd->SendMessage(TVN_UPSTATE);
		*pResult = 1;
	}
	else
	{
		*pResult = 0; 
	}
}

HTREEITEM CMultiTreeCtrl::AddItem( 
									 HTREEITEM hParent, 
									 CString csItemName, 
									 HTREEITEM hInsAfter, 
									 int iSelImage , 
									 int iNonSelImage, 
									 long lParam
									 )
{
	HTREEITEM hItem;
	TV_ITEM tvItem;
	TV_INSERTSTRUCT tvIns;

	tvItem.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	int nLength = csItemName.GetLength() ;
	tvItem.pszText = csItemName.GetBuffer(nLength);
	tvItem.cchTextMax = nLength;
	tvItem.lParam = lParam;

	tvItem.iImage = iNonSelImage;
	tvItem.iSelectedImage = iSelImage;

	tvIns.item = tvItem;
	tvIns.hInsertAfter = hInsAfter;
	tvIns.hParent = hParent;

	hItem = InsertItem(&tvIns);

	return (hItem);
}

void CMultiTreeCtrl::GetCheckItems(std::vector<HTREEITEM>& vecTreeItems, HTREEITEM hTreeItem)
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

/************************************************************
���ܣ�������������Ϣ������ѡ��״̬��
˵����������ص���Ŀ��ѡ��״̬��
ע����¼���ʱ�䣬�Ա㴦��������ק��
*************************************************************/
void CMultiTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_hItemClick = HitTest(point, &m_uClickFlags);

	if ( (m_uClickFlags & TVHT_ONITEMSTATEICON ))
	{
		UINT nState = GetItemState(m_hItemClick, TVIS_STATEIMAGEMASK ) >> 12;
        switch(nState)
        {
        case  STATE_UNSEL: nState = STATE_SEL  ; break;
        case  STATE_PSEL : nState = STATE_SEL  ; break;
        case  STATE_SEL  : nState = STATE_UNSEL; break;
        default:           nState = STATE_UNSEL; break;
        }
		SetItemStateEx(m_hItemClick, nState, TRUE);
	}

	m_dwDragStart = GetTickCount();
	CTreeCtrl::OnLButtonDown(nFlags, point);

}


/**********************************************************************
����ո����Ϣ,�޸Ľڵ��ѡ��״̬
**********************************************************************/
void CMultiTreeCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
 	if(nChar == VK_SPACE/*0x20*/)
 	{
 		HTREEITEM hItem = GetSelectedItem();
 		UINT nState = GetItemState( hItem, TVIS_STATEIMAGEMASK ) >> 12;
 		if(nState != STATE_INI)
 		{
		    nState = (nState == STATE_UNSEL) ? STATE_SEL : STATE_UNSEL;
 			SetItemStateEx( hItem, nState, TRUE);
 		}
 	}
	else CTreeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}


/************************************************************************
���ܣ�����hItem���Լ��������ݵ�״̬ΪnState��
˵������������������ص����ѡ��״̬��
ע����Ҫȷ��ÿ��Item�ڳ�ʼ��ʱ��������Ч��ָ���NULLֵ��
************************************************************************/
BOOL CMultiTreeCtrl::SetItemStateEx(HTREEITEM hItem, UINT nState, BOOL bSearch)
{
	DWORD data = (GetItemData(hItem));
	CTreeCtrl::SetItemState( hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK);
	if(bSearch)
	{
		TravelChild(hItem, nState);
		TravelSiblingAndParent(hItem, nState);
	}
	return TRUE;
}




/**************************************************************
���ܣ����ú��ӽڵ��ѡ��״̬
����Ҫ�󣺱��ֺ��ӽڵ��״̬��nStateһ��
ע��ʹ�õݹ鴦�����еĺ��ӽڵ��Լ����ӵĺ���
**************************************************************/
void CMultiTreeCtrl::TravelChild(HTREEITEM hItem, int nState)
{
	HTREEITEM hChildItem = GetChildItem(hItem);

	if(hChildItem != NULL)
	{
		//�����ӽڵ��״̬�뵱ǰ�ڵ��״̬һ��
        SetItemStateEx( hChildItem, nState, FALSE);

		//�ٵݹ鴦���ӽڵ���ӽڵ���ֵܽڵ�
		TravelChild(hChildItem, nState);
		
		//�����ӽڵ���ֵܽڵ�����ӽڵ�
		HTREEITEM hBrotherItem = GetNextSiblingItem(hChildItem);
		while (hBrotherItem)
		{
			//�����ӽڵ�״̬�뵱ǰ�ڵ��״̬һ��
            SetItemStateEx( hBrotherItem, nState, FALSE);

			//�ٵݹ鴦���ӽڵ���ֵܽڵ���ӽڵ���ֵܽڵ�
			TravelChild(hBrotherItem, nState);
            
			hBrotherItem = GetNextSiblingItem(hBrotherItem);
		}
	}
}

/************************************************************************
���ܣ����ø��׽ڵ��ѡ��״̬
Ҫ�󣺼���ֵܽڵ��״̬������Ӧ�����ø��׽ڵ��״̬��
ע��ʹ�õݹ鴦���׵ĸ���
************************************************************************/
void CMultiTreeCtrl::TravelSiblingAndParent(HTREEITEM hItem, int nState)
{
	HTREEITEM hNextSiblingItem, hPrevSiblingItem, hParentItem;
	
	//���Ҹ��ڵ㣬û�оͽ���
	hParentItem = GetParentItem(hItem);
	if(hParentItem != NULL)
	{
		int nStateSibling = nState;//���ʼֵ����ֹû���ֵܽڵ�ʱ����
		
		//���ҵ�ǰ�ڵ�������ֵܽڵ��״̬
		hNextSiblingItem = GetNextSiblingItem(hItem);
		while(hNextSiblingItem != NULL)
		{
			nStateSibling = GetItemState( hNextSiblingItem, TVIS_STATEIMAGEMASK ) >> 12;
			if(nStateSibling != nState)
            {
                break;
            }
			else
            {
                hNextSiblingItem = GetNextSiblingItem(hNextSiblingItem);
            }
		}
		
		if(nStateSibling == nState)
		{
			//���ҵ�ǰ�ڵ�������ֵܽڵ��״̬
			hPrevSiblingItem = GetPrevSiblingItem(hItem);
			while(hPrevSiblingItem != NULL)
			{
				nStateSibling = GetItemState( hPrevSiblingItem, TVIS_STATEIMAGEMASK ) >> 12;
				if(nStateSibling != nState)
                {
                    break;
                }
				else
                {
                    hPrevSiblingItem = GetPrevSiblingItem(hPrevSiblingItem);
                }
			}
		}
	
		if( nStateSibling != nState )
		{
            nState = STATE_PSEL;
        }

		//�ٵݹ鴦���ڵ���ֵܽڵ���丸�ڵ�
        SetItemStateEx( hParentItem, nState, FALSE);
		TravelSiblingAndParent(hParentItem, nState);
	}	
}



/*************************************************
���ܣ�����������Ŀ��ѡ��״̬
**************************************************/
void CMultiTreeCtrl::ResetItemSelState(int nState)
{
    HTREEITEM hItem = GetRootItem();

	while(NULL != hItem)
	{
		SetItemStateEx(hItem, nState, TRUE);
		hItem = GetNextSiblingItem(hItem);
	}

    return; 
}



void CMultiTreeCtrl::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	*pResult = 0;
	// TODO: Add your control notification handler code here
	if (pTVDispInfo->item.pszText != NULL)
	{
		int nData = GetItemData(pTVDispInfo->item.hItem);
		pTVDispInfo->item.pszText;
	}
}

/**********************************************************************
����ڵ㿪ʼ�Ϸŵ���Ϣ,��ȡ��קͼ���Լ���ק�ڵ���
ע��ͨ����ȡ�ӳ�ʱ�䴦��������ק
**********************************************************************/
void CMultiTreeCtrl::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM hTSelItem = pNMTreeView->itemNew.hItem;
	// Highlight selected item
	SelectItem(hTSelItem);
	Select(hTSelItem, TVGN_DROPHILITE);
	
	COleDataSource *poleSourceObj = new COleDataSource ;
	CTreeDropTarget::m_shWndTreeCtrl = m_hWnd;
	// Begin Drag operation
	DROPEFFECT dropeffect = poleSourceObj->DoDragDrop();
	// Remove the highlighting
	SendMessage(TVM_SELECTITEM, TVGN_DROPHILITE,0);
	// If user is moving item by pressing Shift, delete selected item
	if ( dropeffect == DROPEFFECT_MOVE)
		DeleteItem(hTSelItem); 
	delete poleSourceObj;
	*pResult = 0;
}

int CMultiTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	// Register Tree control as a drop target	
	m_CTreeDropTarget.Register(this);
	return 0;
}

/***********************************************************************
ʵ�������ק�����е����нڵ�ڵ�չ���Լ������б�
***********************************************************************/
void CMultiTreeCtrl::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	//if( nIDEvent == m_nHoverTimerID )
	//{ 
	//	//������нڵ�
	//	KillTimer( m_nHoverTimerID );
	//	m_nHoverTimerID = 0;
	//	HTREEITEM  trItem = 0;
	//	UINT  uFlag = 0;
	//	trItem = HitTest( m_HoverPoint, &uFlag );
	//	if( trItem && m_bDragging )
	//	{
	//		SelectItem( trItem );
	//		Expand( trItem, TVE_EXPAND );
	//	}
	//}
	//else if( nIDEvent == m_nScrollTimerID )
	//{  
	//	//������ҷ�����еĹ�������
	//	m_TimerTicks++;
	//	CPoint  pt;
	//	GetCursorPos( &pt );
	//	CRect  rect;
	//	GetClientRect( &rect );
	//	ClientToScreen( &rect );

	//	if (pt.x > rect.left && pt.x < rect.right)
	//	{
	//		HTREEITEM  hItem = GetFirstVisibleItem();
	//		
	//		if( pt.y < rect.top - 10 )
	//		{
	//			//���Ϲ���
	//			int  slowscroll = 6 - (rect.top + 10 - pt.y )/20;
	//			if( 0 == (m_TimerTicks % ((slowscroll > 0) ? slowscroll : 1)) )
	//			{
	//				CImageList::DragShowNolock ( false );
	//				SendMessage( WM_VSCROLL, SB_LINEUP );
	//				SelectDropTarget( hItem );
	//				m_hNewParent = hItem;
	//				CImageList::DragShowNolock ( true );
	//			}
	//		}
	//		else if( pt.y > rect.bottom + 10 )
	//		{
	//			//���¹���
	//			int  slowscroll = 6 - (pt.y - rect.bottom + 10)/20;
	//			if( 0 == (m_TimerTicks % ((slowscroll > 0) ? slowscroll : 1)) )
	//			{
	//				CImageList::DragShowNolock ( false );
	//				SendMessage( WM_VSCROLL, SB_LINEDOWN );
	//				int  nCount = GetVisibleCount();
	//				for( int i=0 ; i<nCount-1 ; i++ )
	//					hItem = GetNextVisibleItem( hItem );
	//				if( hItem )
	//					SelectDropTarget( hItem );
	//				m_hNewParent = hItem;
	//				CImageList::DragShowNolock ( true );
	//			}
	//		}
	//	}
	//}
	//else
	//{
	//	CTreeCtrl::OnTimer(nIDEvent);
	//}
}

/******************************************************************
����������ͷ���Ϣ
ע����������ק�������������ڷ��ͽڵ���ק����Ϣ��
    �������յ���ק��Ϣ�󣬿���ͨ�����ĳ�Ա��ȡ��ק�Ľڵ�����
******************************************************************/
void CMultiTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CTreeCtrl::OnLButtonUp(nFlags, point);
	//if( m_bDragging )
	//{
	//	m_bDragging = FALSE;
	//	CImageList::DragLeave( this );
	//	CImageList::EndDrag();
	//	ReleaseCapture();
	//	delete m_pDragImage;

	//	SelectDropTarget( NULL );
	//	
	//	if( m_hItemDrag == m_hNewParent )
	//	{
	//		KillTimer( m_nScrollTimerID );
	//		return;
	//	}
	//	
	//	KillTimer( m_nScrollTimerID );
	//	CWnd* pWnd = GetParent();
	//	pWnd->SendMessage(TVN_ENDDRAG);
	//}
}


/***************************************************************
��������϶��¼������ƽڵ��϶�Ч������¼��ק���ܽڵ㡣
ע������ק�����߽磬���ֽڵ�Ϊ����㡣
***************************************************************/
void CMultiTreeCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	////���������ж�ʱ���Ƿ����,���������ɾ��,ɾ�����ٶ�ʱ
	//if( m_nHoverTimerID )
	//{
	//	KillTimer( m_nHoverTimerID );
	//	m_nHoverTimerID = 0;
	//}

	//m_nHoverTimerID = SetTimer( 1, 600, NULL );  //��ʱΪ 0.6 �����Զ�չ��
	//m_HoverPoint    = point;

	//if( m_bDragging )
	//{
	//	CPoint  pt = point;
	//	CImageList::DragMove( pt );//�ƶ������ϷŲ����б��϶���ͼ��

	//	//��꾭��ʱ������ʾ
	//	CImageList::DragShowNolock( false );  //������꾭��ʱ�����ѿ��ĺۼ�
	//	if( (m_hReceved = HitTest(point, &m_uDragFlags)) != NULL )
	//	{
	//		SelectDropTarget( m_hReceved );
	//	}
	//	CImageList::DragShowNolock( true );

 //       
 //       //�жϽ����϶��Ľڵ��뱻�϶��ڵ�Ĳ�ι�ϵ
 //       BOOL bCancel = FALSE;
 //       if(m_hReceved  == m_hItemDrag)
 //       {
 //           bCancel = TRUE;
 //       }
 //       else
 //       {
	//        HTREEITEM  htiParent = m_hReceved;
	//        while( (htiParent = GetParentItem(htiParent)) != NULL )
	//        {
 //               //�����϶��Ľڵ��Ǳ��϶��ڵ���ӽڵ�����
	//	        if( htiParent == m_hItemDrag )
	//	        {
 //                   bCancel = TRUE;
 //                   break;
 //               }
 //           }
 //       }

 //       if(bCancel) // ȡ���Ϸ�
 //       {
 //           m_hReceved     = m_hItemDrag;
 //           m_hNewParent   = m_hItemDrag;
 //           m_hNewSibling  = m_hItemDrag;
 //           ::SetCursor(m_hDragCancel);
 //       }
 //       else if( m_uDragFlags  & TVHT_ONITEMSTATEICON) // ��ӽ��ܽڵ�֮ǰ
 //       {
 //           m_hNewParent   = GetParentItem(m_hReceved);
 //           m_hNewSibling  = m_hReceved;
 //           ::SetCursor(m_hDragAbove  );
 //       }
 //       else if(m_uDragFlags & TVHT_ONITEMICON) // ��ӵ����ܽڵ�֮��
 //       {
	//	    m_hNewParent  = GetParentItem(m_hReceved);
 //           m_hNewSibling = GetNextSiblingItem(m_hReceved);
	//		m_hNewSibling = (m_hNewSibling==NULL)?TVI_LAST:m_hNewSibling;
 //           ::SetCursor(m_hDragBelow);
 //       }
 //       else if(m_uDragFlags & TVHT_ONITEMLABEL) // ���Ϊ���ܽڵ�ĺ��ӽڵ�
 //       {
 //           m_hNewParent  = m_hReceved;
 //           m_hNewSibling = TVI_LAST;
 //           ::SetCursor(m_hDragAppend);
 //       }
 //       else if(m_uDragFlags & TVHT_TORIGHT) // ��ӵ����нڵ�֮��
 //       {
 //           m_hNewParent  = NULL;
 //           m_hNewSibling = TVI_LAST;
 //           ::SetCursor(m_hDragRight);
 //       }
 //       else if(m_uDragFlags & TVHT_TOLEFT) // ��ӵ����нڵ�֮ǰ
 //       {
 //           m_hNewParent  = NULL;
 //           m_hNewSibling = NULL;
 //           ::SetCursor(m_hDragLeft);
 //       }
 //       else if(m_uDragFlags & TVHT_ABOVE) // ��ӵ����нڵ�֮ǰ
 //       {
 //           m_hNewParent  = NULL;
 //           m_hNewSibling = NULL;
 //           ::SetCursor(m_hDragAbove);
 //       }
 //       else if(m_uDragFlags & TVHT_BELOW) // ��ӵ����нڵ�֮��
 //       {
 //           m_hNewParent  = NULL;
 //           m_hNewSibling = TVI_LAST;
 //           ::SetCursor(m_hDragBelow);
 //       }
 //       else // ȡ���Ϸ�
 //       {
 //           m_hReceved    = m_hItemDrag;
 //           m_hNewParent  = m_hItemDrag;
 //           m_hNewSibling = m_hItemDrag;
 //           ::SetCursor(m_hDragCancel);
 //       }
	//}
	
	CTreeCtrl::OnMouseMove(nFlags, point);
}

//��ȡ��һ�����ڵ�item
HTREEITEM CMultiTreeCtrl::FindPrevItem(HTREEITEM hItem)
{
	if (hItem != NULL)
	{
		HTREEITEM hPrev = GetNextItem(hItem, TVGN_PREVIOUS);
		if (hPrev != NULL)
		{
			hItem = GetNextItem(hPrev, TVGN_CHILD);
			while (hItem != NULL)
			{
				while (hItem != NULL)//
				{
					hPrev = hItem;
					hItem = GetNextItem(hPrev, TVGN_NEXT);
				}
				hItem = GetNextItem(hPrev, TVGN_CHILD);
			}
			return hPrev;
		}
		else
		{
			hPrev = GetNextItem(hItem, TVGN_PARENT);

			if (hPrev != NULL)
			{
				return hPrev;
			}
		}
	}
	return NULL;
}


//��ȡ��һ�����ڵ�item
HTREEITEM CMultiTreeCtrl::FindNextItem(HTREEITEM hItem)
{
	if (hItem != NULL)
	{
		HTREEITEM hNext = GetNextItem(hItem, TVGN_CHILD);
		if (hNext != NULL)
		{
			return hNext;
		}
		else
		{
			while (hItem != NULL)
			{
				hNext = GetNextItem(hItem, TVGN_NEXT);
				if (hNext != NULL)
				{
					return hNext;
				}
				else
				{
					hItem = GetNextItem(hItem, TVGN_PARENT);
				}
			}
		}
	}

	return NULL;
}


// ������Ŀ
HTREEITEM CMultiTreeCtrl::CopyItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter)
{
	TV_INSERTSTRUCT  tvstruct;
	HTREEITEM        hNewItem;
	CString          sText;

	// �õ�Դ��Ŀ����Ϣ
	tvstruct.item.hItem = hItem;
	tvstruct.item.mask  = TVIF_CHILDREN|TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
	GetItem( &tvstruct.item );
	sText = GetItemText( hItem );
	tvstruct.item.cchTextMax = sText.GetLength ();
	tvstruct.item.pszText    = sText.LockBuffer ();

	// ����Ŀ���뵽���ʵ�λ��
	tvstruct.hParent         = htiNewParent;
	tvstruct.hInsertAfter    = htiAfter;
	tvstruct.item.mask       = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_PARAM;
	hNewItem = InsertItem( &tvstruct );
	sText.ReleaseBuffer ();

	// ���ƿ�����Ŀ���ݺ���Ŀ״̬
	SetItemData ( hNewItem, GetItemData(hItem) );
	SetItemState( hNewItem, GetItemState(hItem,TVIS_STATEIMAGEMASK),TVIS_STATEIMAGEMASK);

	return hNewItem;
}


// ������֧
HTREEITEM CMultiTreeCtrl::CopyBranch(HTREEITEM htiBranch, HTREEITEM htiNewParent, HTREEITEM htiAfter)
{
	HTREEITEM  hChild;
	HTREEITEM  hNewItem = CopyItem( htiBranch, htiNewParent, htiAfter );
	hChild = GetChildItem( htiBranch );

	while( hChild != NULL )
	{
		CopyBranch( hChild,hNewItem,htiAfter );
		hChild = GetNextSiblingItem( hChild );
	}

	return  hNewItem;
}

//����ڵ��϶���Ϣ
BOOL CMultiTreeCtrl::OnMakeDrag(BOOL bRemove)
{
    //�жϽ����϶��Ľڵ��뱻�϶��ڵ��Ƿ���ͬ
	if( m_hItemDrag == m_hReceved )
	{
		return FALSE;
	}

    //�����϶��Ľڵ㲻�Ǳ��϶��ڵ���ӽڵ��������
    //ֱ�ӿ������϶��ڵ��֧�������϶��Ľڵ���
    if(m_hNewSibling == TVI_LAST || m_hNewSibling == TVI_FIRST)
    {
	    HTREEITEM  htiNew   = CopyBranch( m_hItemDrag, m_hNewParent, m_hNewSibling );
	    SelectItem( htiNew );
    }
    else
    {
        HTREEITEM  hitAfter = GetPrevSiblingItem(m_hNewSibling);
        if(hitAfter == NULL) hitAfter = TVI_FIRST;
	    HTREEITEM  htiNew   = CopyBranch( m_hItemDrag, m_hNewParent, hitAfter );
	    SelectItem( htiNew );
    }

    if(bRemove)
    {
        DeleteItem( m_hItemDrag );
    }
    return TRUE;
}

void CMultiTreeCtrl::SetCBAddItems( CB_ADDITEMS cbAddItems )
{
	m_CTreeDropTarget.SetCBAddItems(cbAddItems);
}