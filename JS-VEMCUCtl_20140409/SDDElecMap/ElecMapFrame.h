#pragma once


// CElecMapFrame ���

class CElecMapFrame : public CMDIFrameWnd
{
	DECLARE_DYNCREATE(CElecMapFrame)
public:
	CElecMapFrame();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CElecMapFrame();

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	CToolBar m_wndToolBar;
	CToolBar m_wndDrawTool;
	CToolBar* m_pTool;

protected:
	afx_msg	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};


