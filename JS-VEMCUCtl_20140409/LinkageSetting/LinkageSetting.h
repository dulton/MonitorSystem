// LinkageSetting.h : LinkageSetting DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLinkageSettingApp
// �йش���ʵ�ֵ���Ϣ������� LinkageSetting.cpp
//

class CLinkageSettingApp : public CWinApp
{
public:
	CLinkageSettingApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
