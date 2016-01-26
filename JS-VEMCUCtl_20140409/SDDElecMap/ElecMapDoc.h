#pragma once
#include "gloable/DataStyle.h"
class CElecMapView;
class CHuaMian;
// CElecMapDoc �ĵ�

class CElecMapDoc : public CDocument
{
	DECLARE_DYNCREATE(CElecMapDoc)

public:
	CElecMapDoc();
	virtual ~CElecMapDoc();

public:
	virtual void Serialize(CArchive& ar);   // Ϊ�ĵ� I/O ��д
	afx_msg void OnFileSave(LPCTSTR lpszPathName);
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);

	BOOL addHMLayerTest();

	void setCurrentView(CElecMapView* view);
	CElecMapView* getCurrentView() const;
	CHuaMian* getHuamianInstance(const CString& strHMName, CElecMapDoc* pDoc);

	void UpdateScale(float scale);
	void DrawDC(CDC *pDC,CElecMapView * pView);

private:
	CElecMapView* m_pElecMapView;
	CString   m_strTittle;

	tagHMID	  m_HMID;

protected:
	DECLARE_MESSAGE_MAP()
};
