// ACSSystem.h : ACSSystem DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CACSSystemApp
// �йش���ʵ�ֵ���Ϣ������� ACSSystem.cpp
//

class CACSSystemApp : public CWinApp
{
public:
	CACSSystemApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
