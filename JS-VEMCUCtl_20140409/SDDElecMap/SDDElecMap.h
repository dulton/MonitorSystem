// SDDElecMap.h : SDDElecMap DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSDDElecMapApp
// �йش���ʵ�ֵ���Ϣ������� SDDElecMap.cpp
//

class CSDDElecMapApp : public CWinApp
{
public:
	CSDDElecMapApp();

	CString getCurrentAppPath();
// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CSDDElecMapApp theApp;