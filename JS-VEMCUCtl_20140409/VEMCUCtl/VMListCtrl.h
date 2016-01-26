#pragma once

#include "VMHeaderCtrl.h"

struct stColor
{
	int nRow;
	int nCol;
	COLORREF rgb;
};

class CVMListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CVMListCtrl)

public:
	CVMListCtrl();
	virtual ~CVMListCtrl();

public:
	void SetHeaderBKColor(int R, int G, int B, int Gradient);// Gradient - ����ϵ�������屳����,���ý�����Ϊ0
	void SetHeaderHeight(float Height);// ���ñ�ͷ�߶�
	bool FindRowColor(int row ,COLORREF &color); //��������ɫ
	bool FindRowByColor(int &row ,COLORREF color); //��������ɫ
	bool FindColColor(int col ,COLORREF &color); //��������ɫ
	bool FindItemColor(int col,int row,COLORREF &color);
	bool FindRowTextColor(int row,COLORREF &color); //������������ɫ
	bool FindRowByTextColor(int &row,COLORREF color); //������������ɫ
	bool FindColTextColor(int col,COLORREF &color); //������������ɫ
	bool FindItemTextColor(int col,int row,COLORREF &color);
	bool ModifyRowColor(int row,COLORREF color);//�޸�����ɫ
	bool ModifyRowColor(int row,int new_row,COLORREF &color);//�޸�����ɫ
	bool ModifyColColor(int col,COLORREF color);//�޸�����ɫ
	bool ModifyItemColor(int col,int row,COLORREF color);//�޸�item��ɫ
	bool ModifyRowTextColor(int row,COLORREF color);//�޸���������ɫ
	bool ModifyRowTextColor(int row,int new_row,COLORREF &color);//�޸���������ɫ
	bool ModifyColTextColor(int col,COLORREF color);//�޸���������ɫ
	bool ModifyItemTextColor(int col,int row,COLORREF color);//�޸�item������ɫ
	void SetRowColor(int row,COLORREF color);  //��������ɫ
	void SetColColor(int col,COLORREF color);  //��������ɫ
	void SetItemColor(int col,int row,COLORREF color); //����Item��ɫ
	void SetRowTextColor(int row,COLORREF color);   //�������ı���ɫ
	void SetColTextColor(int col,COLORREF color);   //�������ı���ɫ
	void SetItemTextColor(int col,int row,COLORREF color);//������������ɫ
	bool DeleteRowColor(int row,COLORREF &color);
	bool DeleteAllRowColor();
	bool DeleteRowTextColor(int row,COLORREF &color);
	bool DeleteAllRowTextColor();
	void SetRowHeigt(int nHeight); //�����и�
	void SetHeaderFontHW(int nHeight,int nWidth); //���ñ�ͷ�����С
	void SetHeaderTextColor(COLORREF color);
	BOOL SetTextColor(COLORREF cr);
	void SetFontHW(int nHeight,int nWidth);  //��������ĸߺͿ�
	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading,int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1);
	BOOL DeleteColumn(int nCol);

public:
	CVMHeaderCtrl m_Header;
	CPtrList m_ptrListCol;  //��������ɫ
	CPtrList m_ptrListItem; //����Item��ɫ��
	CPtrList m_ptrListRow; //��������ɫ 
	CPtrList m_rowTextColor; //������������ɫ 
	CPtrList m_colTextColor; //������������ɫ
	CPtrList m_ItemTextColor; //���浥Ԫ��������ɫ

public:
	int m_nFontHeight;     // ����߶�
	int m_nFontWidth;	     // ������
	int m_nRowHeight;     // �и�
	COLORREF m_color;


protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnLvnInsertitem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnDeleteallitems(NMHDR *pNMHDR, LRESULT *pResult);
};


