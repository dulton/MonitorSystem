#pragma once

class CImagePng:public CObject  
{
public:
	CImagePng(void);
	virtual ~CImagePng(void);

public:
	BOOL LoadImagePng(char *szPngName);
	int GetImagePngWidth();
	int GetImagePngHeight();
	BOOL DrawImagePng(HDC hDC,int nXDst,int nYDst,int nWidthDst,int nHeightDst,int nXSrc,int nYSrc,int nWidthSrc,int nHeightSrc,double dbRotateAngle,DWORD dwRop);

public:
	char m_szPngName[256];
	HBITMAP m_hBmp;
	int m_nWidth;
	int m_nHeight;
	int m_nCount;
};

typedef CTypedPtrMap<CMapStringToOb,CString,CImagePng*> CMapPngList;

class CImagePngMapX
{
public:
	CImagePngMapX(void);
	virtual ~CImagePngMapX(void);

public:
	BOOL RegisterImagePng(char *szPngName);//�Ǽ�PNGͼƬ
	void   UnRegisterImagePng(char *szPngName);//ע��PNGͼƬ
	BOOL DrawImagePng(char *szPngName,HDC hDC,int nXDst,int nYDst,int nWidthDst,int nHeightDst,int nXSrc,int nYSrc,int nWidthSrc,int nHeightSrc,double dbRotateAngle,DWORD dwRop);

private:
	CImagePng* AddImagePng(char *szPngName);

private:
	CMapPngList m_MapPngList;
};

//////////////////////////////////////////////////////////////////////////
extern CImagePngMapX g_ImagePngMapX;
