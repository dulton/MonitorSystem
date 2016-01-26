// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��
#define MAIN_TITLE_HEIGHT           140

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE ��
#include <afxodlgs.h>       // MFC OLE �Ի�����
#include <afxdisp.h>        // MFC �Զ�����
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC ���ݿ���
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO ���ݿ���
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "include\\CommonLib.h"
#pragma comment(lib,"lib\\CommonLib.lib")

#pragma comment(lib,"lib\\libmySQL.lib")
#include "include/mysql.h"

#include "DevPlayVideoSdk.h"
#pragma comment(lib,"lib\\DevPlayVideoSdk.lib")

#include "dvr/dhnetsdk.h"
#include "dvr/HCNetSDK.h"
#include "dvr/NetSDK.h"
#include "dvr/MOBOTIXExport.h"
#pragma comment(lib,"dvr\\dhnetsdk.lib")
#pragma comment(lib,"dvr\\HCNetSDK.lib")
#pragma comment(lib,"dvr\\NetSDK.lib")

//#pragma comment(lib,"lib\\ysxml.lib")

#include "tinyxml\\tinyxml.h"

#include "./../SDDElecMap/DLLInterface.h"

#ifdef _DEBUG
#pragma comment(lib, "./../VEMCUCtl/lib/SDDElecMapD.lib")
#else
#pragma comment(lib, "./../VEMCUCtl/lib/SDDElecMap.lib")
#endif

#pragma warning(disable:4996)
#include "ParamDefine.h"
#include "AssSystemDefine.h"
#include "Common.h"

