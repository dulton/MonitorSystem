// Image.h: interface for the CImage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGE_H__109C7537_062D_477B_B240_514A65F93952__INCLUDED_)
#define AFX_IMAGE_H__109C7537_062D_477B_B240_514A65F93952__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxcoll.h>
#include "MemDCX.h"

class CHandleObj : public CObject  
{
public:
	void StretchBlt(HDC hdcDest,int nXOriginDest,int nYOriginDest,int nWidthDest,int nHeightDest,BOOL blHScale,BOOL blVScale);
	void TransparentBlt(HDC hdcDest, int x, int y, int width, int height, COLORREF crColour,BOOL blHScale,BOOL blVScale);
	void DrawTransparent(CDC * pDC, int x, int y, COLORREF crColour);
	void DrawDIBSection( HDC hDC, int xDest, int yDest );
	CHandleObj(HBITMAP hBmp);
	CSize  GetSize();
	virtual ~CHandleObj();
  int m_count;					//���ü���
	HBITMAP m_handle;			//λͼ���
};


typedef CTypedPtrMap<CMapStringToOb,CString,CHandleObj*> CMapStringtoHandle;

class CImageX  
{
private:
	CMapStringtoHandle m_maplist;
	CHandleObj* AddImage(CString bmpname);
public:
	//������ʾλͼ
	void StretchBlt(LPCSTR bmpname,HDC hdcDest,int nXOriginDest,int nYOriginDest,int nWidthDest,int nHeightDest,BOOL blHScale=TRUE,BOOL blVScale=TRUE);
	//͸�����Ŵ�λͼ
	void TransparentBlt(CString bmpname, HDC hDC, int x, int y,int width,int height, COLORREF crColour,BOOL blHScale=TRUE,BOOL blVScale=TRUE);
	//͸����ʾλͼ
	void DrawTransparent(CString bmpname,CDC *pDC, int x, int y, COLORREF crColour);
	//��ʾλͼ
	void DrawDIBSection(CString bmpname,HDC hdc, int x0, int y0);
	//ע��λͼ
	void UnRegisterImage(CString bmpname);
	//�Ǽ�λͼ
	BOOL RegisterImage(CString bmpname);

	CImageX();
	virtual ~CImageX();
	 
};

extern CImageX g_image;

#endif // !defined(AFX_IMAGE_H__109C7537_062D_477B_B240_514A65F93952__INCLUDED_)
