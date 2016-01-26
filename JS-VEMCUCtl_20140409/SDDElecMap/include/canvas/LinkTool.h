// LinkTool.h: interface for the CLinkYkTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINKTOOL_H__C5EDAE42_F720_11D5_8B43_444553540000__INCLUDED_)
#define AFX_LINKTOOL_H__C5EDAE42_F720_11D5_8B43_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../resource.h"
#include "canvas/TyTool.h"

class CLinkTool : public CTyTool  
{
public:
	CLinkTool(DRAW_TY type);
	virtual ~CLinkTool();

public:
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
};


class CLinkYkTool : public CLinkTool  
{
public:
	CLinkYkTool();
	virtual ~CLinkYkTool();

public:
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);

public:
	static bool c_bWatchMan;						//�����Ƿ���ü໤�˼໤���Ʒ�ʽ
	static bool c_bGroup;								//�����Ƿ���÷�����Ʒ�ʽ
	static DWORD c_dwFlag;							//����������Щ�����
};


class CLinkZkTool : public CLinkTool  
{
public:
	CLinkZkTool();
	virtual ~CLinkZkTool();

public:
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
};

class CNetColorPowerTool : public CLinkTool  
{
public:
	CNetColorPowerTool();
	virtual ~CNetColorPowerTool();

public:
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
};

class CNetColorVectorTool : public CLinkTool  
{
public:
	CNetColorVectorTool();
	virtual ~CNetColorVectorTool();

public:
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
};

class CNetColorBmpTool : public CLinkTool  
{
public:
	CNetColorBmpTool();
	virtual ~CNetColorBmpTool();

public:
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
};


class CNetColorYxTool : public CLinkTool  
{
public:
	CNetColorYxTool();
	virtual ~CNetColorYxTool();

public:
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
};

class CLinkYTTool : public CLinkTool  
{
public:
	CLinkYTTool();
	virtual ~CLinkYTTool();

public:
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
};

class CLinkYZTYTool : public CLinkTool  
{
public:
	CLinkYZTYTool();
	virtual ~CLinkYZTYTool();

public:
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
};

class CLinkUnitTool : public CLinkTool  
{
public:
	CLinkUnitTool();
	virtual ~CLinkUnitTool();

public:
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
};

class CLinkNodeTool : public CLinkTool
{
public:
	CLinkNodeTool();
	virtual ~CLinkNodeTool();

public:
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
};

class CLinkLineTool : public CLinkTool
{
public:
	CLinkLineTool();
	virtual ~CLinkLineTool();

public:
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
};


class CLinkClubTool : public CLinkTool  
{
public:
	CLinkClubTool();
	virtual ~CLinkClubTool();

public:
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
};


class CLinkTxtFileTool : public CLinkTool  
{
public:
	CLinkTxtFileTool();
	virtual ~CLinkTxtFileTool();

public:
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
};


class CLinkWebShotTool : public CLinkTool  
{
public:
	CLinkWebShotTool();
	virtual ~CLinkWebShotTool();

public:
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);

public:
	static DWORD c_webIP;
	static DWORD c_serverIP;
	static int   c_serverPort;
	static DWORD c_groupIP;
	static int   c_groupPort;
	static int   c_unitID;
	static char  c_unitName[33];
  
};

class CLinkModemTool : public CLinkTool
{
public:
	CLinkModemTool() ;
	virtual ~CLinkModemTool() ;

public:
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
};

class CLinkYT2Tool : public CLinkTool  
{
public:
	CLinkYT2Tool();
	virtual ~CLinkYT2Tool();

public:
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
};

////////////////////////////////////////////////////
//2004.3.29
//pang����ң���������ͼԪ
class CLinkXYBindTool : public CLinkTool
{
public:
	CLinkXYBindTool() ;
	virtual ~CLinkXYBindTool() ;
	
public:
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
} ;

////////////////////////////////////////////////////
//2004.3.30
//pang����Ⱥ������ͼԪ
class CLinkQKTool : public CLinkTool
{
public:
	CLinkQKTool() ;
	virtual ~CLinkQKTool() ;

public:
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
} ;
////////////////////////////////////////////////////
//2004.4.3
//pang���Ӻ�̨����������ͼԪ
class CLinkSoftRepairTool : public CLinkTool
{
public:
	CLinkSoftRepairTool() ;
	virtual ~CLinkSoftRepairTool() ;

public:
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
} ;
////////////////////////////////////////////////////
//pang�����ٻ��¹ʱ�������ͼԪ
class CLinkUnitExtendTool : public CLinkTool  
{
public:
	CLinkUnitExtendTool();
	virtual ~CLinkUnitExtendTool();

public:
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
};

//////////////////////////////////////////////////////
//2004.06.05
//pang�������߿�������ͼԪ
class CLinkKXTool : public CLinkTool  
{
public:
	CLinkKXTool();
	virtual ~CLinkKXTool();

public:
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
};

//////////////////////////////////////////////////////
//2004.06.05
//pang����������������ͼԪ
class CLinkKXSectionTool : public CLinkTool  
{
public:
	CLinkKXSectionTool();
	virtual ~CLinkKXSectionTool();

public:
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
};

////////////////////////////////////////////////////////
//2004.08.03
//st����ˮ��ҵ��������ͼԪ
class CLinkDoubleCtrlTool : public CLinkTool  
{
public:
	CLinkDoubleCtrlTool();
	virtual ~CLinkDoubleCtrlTool();

public:
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);

};
////////////////////////////////////////////
//��Դ����ͳ��
class CLinkPowerGzTjTool : public CLinkTool  
{
public:
	CLinkPowerGzTjTool();
	virtual ~CLinkPowerGzTjTool();

public:
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
};

//��·����ͳ��
class CLinkLineGzTjTool : public CLinkTool  
{
public:
	CLinkLineGzTjTool();
	virtual ~CLinkLineGzTjTool();

public:
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
};
#endif // !defined(AFX_LINKTOOL_H__C5EDAE42_F720_11D5_8B43_444553540000__INCLUDED_)
