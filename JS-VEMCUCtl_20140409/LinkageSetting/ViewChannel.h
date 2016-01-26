// ViewChannel.h: interface for the CViewChannel class.

//����ͷͨ���࣬������Ҫ���DevPlayVideoSdk.dll����ͷ��ʹ��
//
//////////////////////////////////////////////////////////////////////

#ifndef _VIEW_CHANNEL_H_
#define _VIEW_CHANNEL_H_

#if _MSC_VER > 1000
#pragma once

#endif // _MSC_VER > 1000
#include <string>

using namespace std;

#define IDC_STATIC_TITLE 12222
#define IDC_STATIC_VIDEO 12223
#define IDC_MENU_CLOSE_VIDEO 12224
#define IDC_STATIC_TITLE_CAPTION 12225

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
	//����ͷ��Ϣ
	struct T_CAMERA_INFO
	{
		char szDvrIP[32];
		int nDvrPort;
		char szLoginName[32];
		char szLoginPassword[32];
		int nDvrType;
		int nChannel;
		char szCameraName[64];
	};
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
public:
	CStatic m_csTitle;//����picture control
	CStatic m_csVideo;//��Ƶpicture control
	CStatic m_csTitleCaption;//������Ϣ
public:
	//��ʾ����ID
	int	m_iWinID;
	//��Ƶ�Ƿ����
	bool m_video_opened;
	//������̨���
	bool m_byt_ctl;
	int m_iyt_pos;
	//��ǰ��ƵID
	int m_nCurrentVideoId;
	//����ͷ��Ϣ
	T_CAMERA_INFO m_tCameraInfo;
	//��̨�����ٶ�
	int m_nControlSpeed;
	
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
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
private:
	//�ر���Ƶ
	void OnCloseVideo();
	//���ñ���
	void SetBackGround();
	CRect GetDstRect(BITMAP bmpInfo);
	void FillAllDialogBKColor();
	void SetBKPicture();
	void SetTitleBKPicture();
	//�����ؼ�
	void CreateControls();
	//�����Ҽ��˵�
	void PopRightMenu();

public:
	int OpenCamera();//����Ƶ
	void CloseCamera();//�ر���Ƶ
	//������Ƶ��Ϣ
	void SetCameraInfo(T_CAMERA_INFO tCameraInfo);
	//���ñ�������
	void SetTitleCaption(CString strText);
	//ˢ�±���
	void FlashChannel();
	//��̨����
	int CameraControl(int nDirection, int nStartOrStop);
	int CameraControl(unsigned short nCommand);
	//������̨�����ٶ�
	void SetControlSpeed(int nSpeed);
	//תԤ��λ
	void ToPreset(int nPresetNum);
	//����Ԥ��λ
	BOOL SetPreset(int nPresetNum);
	//ɾ��Ԥ��λ
	BOOL DeletePreset(int nPresetNum);
};

#endif //_VIEW_CHANNEL_H_
