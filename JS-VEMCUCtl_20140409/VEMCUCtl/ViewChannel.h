// ViewChannel.h: interface for the CViewChannel class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _VIEW_CHANNEL_H_
#define _VIEW_CHANNEL_H_

#if _MSC_VER > 1000
#pragma once

#endif // _MSC_VER > 1000
#include "xappany.h"
#include <string>

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CViewChannel window
// ��Ƶͨ����Ƶ��ʾ����
//

class CViewChannel : public CWnd
{
	DECLARE_DYNAMIC( CViewChannel )
// Construction
public:
	CViewChannel();
	virtual ~CViewChannel();

public:
	void FlashChannel();
	BOOL LoadSkin();

public:
	HCURSOR		m_hCursor_up;
	HCURSOR		m_hCursor_down;
	HCURSOR		m_hCursor_left;
	HCURSOR		m_hCursor_right;
	HCURSOR		m_hCursor_up_on;
	HCURSOR		m_hCursor_down_on;
	HCURSOR		m_hCursor_left_on;
	HCURSOR		m_hCursor_right_on;

	CFont   m_font; 

	CBitmap m_BGBmp;
	BITMAP    m_BGBm;
	
public:
	/****************ͨ����ز���***********************/
	//��ʾ����ID
	int		m_iWinID;
	//��Ƶ�Ƿ����
	bool		m_video_opened;
	//������̨���
	bool		m_byt_ctl;
	int		m_iyt_pos;
	//������ʾ��־��Ϊ1��ʾ��ͨ���жϡ�,Ϊ0����ʾ
	int      m_nViewChannelInfoShowFlag;
	
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
public:
	//���ñ���ͼƬ
	void SetBKPicture(CDC *pDC);
};

#endif //_VIEW_CHANNEL_H_
