#pragma once

// CDlgViewOut �Ի���
#include "Label.h"
#include "ViewChannel.h"
#include "UtilMedia.h"
#include "SkinButton.h"
#include "GWPlayInfoDef.h"
#include "VideoInfoDlg.h"
#include "afxwin.h"
#include "axismediacontrol1.h"


class CDlgViewOut : public CDialog
{
	DECLARE_DYNAMIC(CDlgViewOut)

public:
	CDlgViewOut(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgViewOut();

public:
	int	InitViewChannel();// ��ʼ��ʵʱ������ͨ��
	void	CloseViewChannel();// �رղ���ͨ��
	bool	SetDefaultViewParameter();// ����Ĭ����Ƶ����
	bool	SetCurrentViewParameter(int liangdu,int duibidu, int baohedu, int sedu);// ���õ�ǰ��Ƶ����

	//////////////////////////////////////////////////////////////////////////
	void ClearViewChannelInfo();//���ͨ����Ϣ

public:
	// �ط���غ���
	BOOL	ReplayOpenFileByVideoPlatform(char *szFileName);
	BOOL	ReplayStartFileByVideoPlatform();
	BOOL	ReplayStopFileByVideoPlatform();

	BOOL   ReplayStartStreamByVideoPlatform(int nDecodeType,char *pSps,int nSpsLen);
	BOOL   ReplayStopStreamByVideoPlatform();

	BOOL	ReplayPauseByVideoPlatform();
	BOOL   ReplayResumeByVideoPlatform();
	BOOL	ReplayFastByVideoPlatform();
	BOOL	ReplaySlowByVideoPlatform();
	float  	ReplayGetFilePosByVideoPlatform();
	BOOL   ReplaySetFilePosByVideoPlatform(float fPos);
	int        ReplayGetFileDecodeTypeByVideoPlatform(char *szFileName);

	//////////////////////////////////////////////////////////////////////////
	BOOL	ReplayOpenFileByDirectDevice(char *szFileName);
	BOOL	ReplayStartFileByDirectDevice();
	BOOL	ReplayStopFileByDirectDevice();

	BOOL	ReplayPauseByDirectDevice();
	BOOL   ReplayResumeByDirectDevice();
	BOOL	ReplayFastByDirectDevice();
	BOOL	ReplaySlowByDirectDevice();
	BOOL   ReplaySetFilePosByDirectDevice(int nPos);
	int        ReplayGetFileDvrTypeByDirectDevice(char *szFileName);

	//////////////////////////////////////////////////////////////////////////

	BOOL   OnStartRecord();
	BOOL   OnStopRecord();

	BOOL   OnStartRecordByVideoPlatform();
	BOOL   SaveRecordFile(void *pData,int nDataLen);
	BOOL   OnStopRecordByVideoPlatform();

	BOOL   OnStartRecordByDirectDevice();
	BOOL   OnStopRecordByDirectDevice();

	void	   FlashChannel();
	BOOL  InitControl();
	BOOL  InitInfo();
	BOOL  LoadSkin();

	BOOL SetLineInfo(int line1_from_x,int line1_from_y,int line1_to_x,int line1_to_y,
		                        int line2_from_x,int line2_from_y,int line2_to_x,int line2_to_y);

	BOOL StartYtLock();
	BOOL StopYtLock();
	BOOL IsYtLock();

	void DrawRect(CDC *pDC,RECT &rect);
	void ModifyControlSizeBySelectFlag(BOOL bSelectedFlag,BOOL bForceFlag=FALSE);

	BOOL RecvVideoFlow(int nVideoFlow);
	BOOL ShowCurrentVideoFlow();
	BOOL HideCurrentVideoFlow();
	BOOL ShowCurrentVideoFlowInfo();

public:
	CLabel		m_strStation;
	CLabel		m_strRelaInfo;
	CLabel     m_strVideoFlow;
	CLabel     m_strWeather;
	CSkinButton m_btnVoice;
	CSkinButton m_btnCapture;
	CSkinButton m_btnRecord;
	CSkinButton m_btnTypeFlag;
	CToolTipCtrl m_TPtool;

	 CBitmap  m_TopBmp;
	 BITMAP    m_TopBm;

	HCURSOR		m_hCursor_up;
	HCURSOR		m_hCursor_down;
	HCURSOR		m_hCursor_left;
	HCURSOR		m_hCursor_right;
	HCURSOR		m_hCursor_up_on;
	HCURSOR		m_hCursor_down_on;
	HCURSOR		m_hCursor_left_on;
	HCURSOR		m_hCursor_right_on;

	CBrush m_brush;

public:
	//��ʾ����ID
	int m_iWinID;

	//��Ƶ��ʾ����
	CViewChannel m_Pic;

	//axis����
	CAxismediacontrol1 m_AxisView;

	//����ͷ�豸��Ϣ��״̬
	VM_VIDEO_VIEW_OUT_INFO m_VideoViewOutInfo;//��ǰ����Ϣ
	VM_VIDEO_VIEW_OUT_INFO m_PreVideoViewOutInfo;//ǰһ�ε���Ϣ

public:
	//���ز����ļ����ͱ�־,1��ʾͨ��ƽ̨,2��ʾֱ������ǰ��
	int       m_nReplayLocalFileTypeFlag;
	
	//���ز����ļ�����
	char     m_szReplayLocalFileName[256];

	//ֱ������ǰ�˻ط�ʱ��ID��
	LONG  m_nReplayLocalFileIDByDirectDevice;

	//ֱ������ǰ�˻ط�ʱ��DVR����
	int  m_nReplayLocalFileDvrTypeyDirectDevice;


	//¼���־λ
	BOOL	m_bRecordFlag;

	//����¼���ļ����
	HANDLE m_hSaveFile;

	// ˽�����ݰ���ͷ
	char		m_Headerbuf[1024];
	int		m_nHeaderLen;

public:
	//////////////////////////////////////////////////////////////////////////
	//Ԥ��λ���ߣ��߿�ʼ������ֵ
	int m_nLine1_from_x;
	int m_nLine1_from_y;
	int m_nLine1_to_x;
	int m_nLine1_to_y;
	int m_nLine2_from_x;
	int m_nLine2_from_y;
	int m_nLine2_to_x;
	int m_nLine2_to_y;

public:
	//////////////////////////////////////////////////////////////////////////
	int		m_CallidVoice;       //����
	bool		m_bYTControl;       //��̨����
	bool		m_bShowVoice;     //�Ƿ���ʾ����
	bool		m_bShowCapture; //�Ƿ���ʾץͼ
	bool		m_bShowRecord;   //�Ƿ���ʾ¼��

	//////////////////////////////////////////////////////////////////////////
	BOOL        m_bSelectedFlag;//����ѡ���־

public:
	//��̨����
	BOOL   m_bYtLockFlag;
	time_t   m_YtLockTime;

	//������̨���
	bool		m_byt_ctl;
	int		m_iyt_pos;

public:
	CRtUtilH264ReFUA* m_pFUA;                                     //�Է�Ƭ�������
	GW_PLAY_CHANNEL_INFO *m_pPlayChannelInfo;      //������
	HANDLE m_hCallResultNotifyEvent;

public:

// �Ի�������
	enum { IDD = IDD_DIALOG_VIEWOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��


	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnBnClickedButtonOpenvoice();
	afx_msg void OnBnClickedButtonCaptureVo();
	afx_msg void OnBnClickedButtonRecordVo();
	afx_msg void OnDestroy();
	DECLARE_EVENTSINK_MAP()
	void OnMouseDownAxismediacontrol1(long nButton, long nShiftState, long fX, long fY);
	void OnDoubleClickAxismediacontrol1(long nButton, long nShiftState, long fX, long fY);
	void OnErrorAxismediacontrol1(long theErrorCode, LPCTSTR theErrorInfo);
	
};
