/*************************************************
Use at your own risk!
�ļ����ƣ� MultiTreeCtrl.h
ģ����ƣ� ¬ҵ��
ģ���д�� ¬ҵ��
���ܣ� ����ѡ��Ŀ���ק�����οؼ��࣮
�汾�ţ� V2013.3.13
***************************************************/
#include <vector>
#include "TreeDropTarget.h"
#if !defined(__AN_MULTITREECTRL_H)
#define __AN_MULTITREECTRL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



// ��ѡ��״̬
enum CHECK_STATE
{
STATE_INI   = 0,//δ�趨
STATE_UNSEL = 1,//δѡ��
STATE_SEL   = 2,//ȫѡ��
STATE_PSEL  = 3,//����ѡ��
};

// �ؼ���Ҫ��Ϣ�¼�ID����
const int  DRAG_DELAY   = 60;
const UINT TVN_ENDDRAG  = WM_USER+1001; // �϶��¼���ϢID
const UINT TVN_UPSTATE  = WM_USER+1002; // ����״̬��ϢID
// TVN_ENDLABELEDIT // ��ǩ�༭�¼���ϢID

/////////////////////////////////////////////////////////////////////////////
// CMultiTreeCtrl ���� ���и�ѡ������Ϳؼ�
class CMultiTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CMultiTreeCtrl();

	HTREEITEM     m_hItemClick ;     //������Ľڵ�
	HTREEITEM     m_hItemDrag  ;     //���϶��Ľڵ�
	HTREEITEM     m_hReceved   ;     //�����϶��Ľڵ�
	HTREEITEM     m_hNewParent ;     //���ܲ���ĸ��ڵ�
	HTREEITEM     m_hNewSibling;     //���ܲ���Ľڵ�

    //�����Դ������������ⲿ��ȡ������
	HCURSOR m_hDragLeft  ; // ���ͷ
	HCURSOR m_hDragRight ; // �Ҽ�ͷ
	HCURSOR m_hDragAbove ; // ���ϼ�ͷ
	HCURSOR m_hDragBelow ; // ���¼�ͷ
	HCURSOR m_hDragAppend; // ��ĩβ��ͷ
	HCURSOR m_hDragCancel; // ȡ����ͷ

// Attributes
protected:
	UINT          m_TimerTicks    ;  //��������Ķ�ʱ����������ʱ��
	UINT          m_nScrollTimerID;  //��������Ķ�ʱ��
	CPoint        m_HoverPoint    ;  //���λ��
	UINT          m_nHoverTimerID ;  //������ж�ʱ��
	DWORD         m_dwDragStart   ;  //������������һ�̵�ʱ��
	BOOL          m_bDragging     ;  //��ʶ�Ƿ������϶�������
	CImageList*   m_pDragImage    ;  //�϶�ʱ��ʾ��ͼ���б�

	UINT          m_uClickFlags;     //�����״̬
	UINT          m_uDragFlags ;     //�ڵ��϶�״̬
	CTreeDropTarget m_CTreeDropTarget;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	HTREEITEM FindNextItem(HTREEITEM hItem);
	HTREEITEM FindPrevItem(HTREEITEM hItem);
	void      ResetItemSelState(int nState);
	BOOL      SetItemStateEx(HTREEITEM hItem, UINT nState, BOOL bSearch);
    BOOL      OnMakeDrag(BOOL bRemove); // == UpdateDrag(...);
	void GetCheckItems(std::vector<HTREEITEM>& vecTreeItems, HTREEITEM hTreeItem);
	HTREEITEM AddItem( HTREEITEM hParent, CString csItemName, HTREEITEM hInsAfter, int iSelImage , int iNonSelImage, long lParam );
	virtual   ~CMultiTreeCtrl();
	void SetCBAddItems(CB_ADDITEMS cbAddItems);

	// Generated message map functions
protected:
	//{{AFX_MSG(CMultiTreeCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnStateIconClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void TravelSiblingAndParent(HTREEITEM hItem, int nState);
	void TravelChild(HTREEITEM hItem, int nState);
	HTREEITEM CopyBranch(HTREEITEM htiBranch,HTREEITEM htiNewParent,HTREEITEM htiAfter);
	HTREEITEM CopyItem(HTREEITEM hItem,HTREEITEM htiNewParent,HTREEITEM htiAfter);
}; 

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__AN_MULTITREECTRL_H)
