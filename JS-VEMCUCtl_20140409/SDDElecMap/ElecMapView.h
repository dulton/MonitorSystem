#pragma once
#include "canvas/TyBase.h"
#include "canvas/MemDCX.h"

#include <vector>
using namespace std;

#define HINT_UPDATE_WINDOW      0
#define HINT_UPDATE_TYOBJ		1
#define HINT_UPDATE_SELECTION   2
#define HINT_DELETE_SELECTION   3

#define MENU_MESSAGE_COMMAND	WM_USER+100
#define	MENU_MESSAGE_MAXCOUNT	32L

#define WM_TIMER_UPDATEVIEW_ID 10L
#define WM_TIMER_UPDATEVIEW_VALUE 500L

class CElecMapDoc;
class CHuaMian;

// CElecMapView ��ͼ
class CTipMessage : public CToolTipCtrl
{
public:
	CTipMessage(){
	}
	~CTipMessage(){
	}

public:

private:

protected:

};


class CElecMapView : public CView
{
	DECLARE_DYNCREATE(CElecMapView)

public:
	CElecMapView();
	virtual ~CElecMapView();

public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL DestroyWindow();
	virtual void OnInitialUpdate();
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CElecMapDoc* GetDocument();
	void OnHMSizeChanged();

	void	updateViewWindow();

	void	startUpdateView();
	void	stopUpdateView();
	//=========================================================
	//interface for user------down

	void SelectWithinRect(CRect rect, BOOL bAdd);
	void Deselect(CTyBase * pTy);

	//paint scale
	float getCurrentScale() const { return  m_fScale;}
	void  setCurrentScale(float scale) { m_fScale = scale; }

	void GetFloatRect(float* x0,float *y0,float* x1,float* y1);

	BOOL isViewActive() const { return m_bActive; }
	
	BOOL IsSelected(CTyBase* pTy) const;
	void Select(CTyBase *pTy, BOOL bAdd=TRUE);

	BOOL GetActiveLayerName(char *pBuf, int bufsize);
	CHMLayer* GetActiveHMLayer();

	//get start(end) point coordinate
	float getStartPointX() const {return m_xStart;}
	void  setStartPointX(float xStart) { m_xStart = xStart; }

	float getStartPointY() const {return m_yStart;}
	void  setStartPointY(float yStart) { m_yStart = yStart; }

	float getEndPointX() const {return m_xEnd;}
	void  setEndPointX(float xEnd) { m_xEnd = xEnd; }

	float getEndPointY() const {return m_yEnd;}
	void  setEndPointY(float yEnd) { m_yEnd = yEnd; }
	
	///  /*canvas operation begin:
	void Add_Selection(CTyBase *pTy);
	void InvalidateTy(CTyBase *pTy, BOOL bErase=FALSE);
	void DrawMemDC(CDC *pDC);
	int ULtoLL(float len);
	float LLtoUL(int len);
	CPoint UPtoLP(PointStruct fpt);
	CRect URecttoLRect(RectStruct frt);
	RectStruct LRecttoURect(CRect rt);
	PointStruct LPtoUP(const CPoint pt);
	void LPtoUP(const CPoint pt,float *x,float * y);
	CPoint  UPtoLP(float x0,float y0);
	///  canvas operation end.*/


	//interface for user------up
	//=========================================================

public:
	CTyBaseList	m_selection;	//��ǰѡ���ͼԪ�ļ���
private:
	float	m_fScale;
	BOOL	m_bActive;

	float m_xStart,m_yStart;	//����ͼ��ʱ���������
	float m_xEnd,m_yEnd;		//����ͼ��ʱ���յ�����

	CBrush		m_brush;
	CBitmap*	m_bitmap;
	CMemDCX		m_memDC;		//�ڴ�dc

	int m_nScrollMin;		//����������С������Χ
	int m_nHScrollMax;  //������������Χ
	int m_nHScrollPos;	//�����������ǰλ��
	int m_nVScrollMax;	//������������Χ
	int m_nVScrollPos;	//�����������ǰλ��
	int m_nXPage;				//���������һ���Ĺ�����Χ
	int m_nXLine;				//���������һ�еĹ�����Χ
	int m_nYPage;				//���������һ���Ĺ�����Χ
	int m_nYLine;				//���������һ�еĹ�����Χ

	int m_hScreen,m_wScreen;	//��ǰ��ͼ�ĸ߶ȺͿ��

	static CLIPFORMAT c_clipTy ; //ͼԪ���а��ʽ

	std::vector<CString> m_vecCameraID;
	std::vector<CString> m_vecCameraName;

	CMenu m_pMainMenu;
	CMenu m_pSubMenu;
	UINT m_nIDMessage;

	BOOL m_bSetTimer;

	CToolTipCtrl m_ctrlTipMsg;
	CRect m_rectTipMsgPt;
	CString m_strTipMsg;
	BOOL m_bTracking;

private:
	BOOL initial();
	void InitVScroll();
	void InitHScroll();
	CSize GetHMSize();
	void OnUpdataPopMenu( CPoint Point, BOOL& bFind );
	void MoveSelectedTyTo(CPoint pt);
	void PasteNative(COleDataObject& dataObject);
	BOOL GetSelectTyBoudsRect(RectStruct& rt);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnPostMessageRMenu( UINT nID);

	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();

	DECLARE_MESSAGE_MAP()
};


