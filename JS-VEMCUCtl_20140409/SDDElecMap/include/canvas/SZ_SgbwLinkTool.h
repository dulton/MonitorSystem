// SZ_SgbwLinkTool.h: interface for the CSZ_SgbwLinkTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SZ_SGBWLINKTOOL_H__469B5BC1_3CA7_11D6_A5ED_0080C8F60823__INCLUDED_)
#define AFX_SZ_SGBWLINKTOOL_H__469B5BC1_3CA7_11D6_A5ED_0080C8F60823__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LinkTool.h"

class CSZ_SgbwLinkTool : public CLinkTool  
{
public:
	virtual void OnLButtonDown(CElecMapView *pView, UINT nFlags, const CPoint &point);
	virtual void OnMouseMove(CElecMapView *pView, UINT nFlags, const CPoint &point);
	CSZ_SgbwLinkTool();
	virtual ~CSZ_SgbwLinkTool();

};

#endif // !defined(AFX_SZ_SGBWLINKTOOL_H__469B5BC1_3CA7_11D6_A5ED_0080C8F60823__INCLUDED_)
