//***************************************************************************

#ifndef _SYSNETTUOPUAPI_H_
#define _SYSNETTUOPUAPI_H_

#ifdef _x_sysnettuopu_dll_		// ��̬���ӿⶨ��
#define _xdll_ __declspec(dllexport)
#else
#define _xdll_ __declspec(dllimport)
#endif

typedef void (*CALLBACKTRANS) (char* sysid,char* message);

//---------------------------------------------------------------------------
// C���Ա�׼
#ifdef __cplusplus
extern "C" {
#endif
//��ʾ����
_xdll_ void	ShowNetTuopuDlg(HWND parenthwnd,HWND* redlg);
//�������ݿ���
_xdll_ void NetTuopuSetConnect(void* hdbc);
//���﷢�ͻص����
_xdll_ void NetTuopuSetTransactionAPI(CALLBACKTRANS trans);
//������ʾ����
_xdll_ void NetTuopuSetMessage(char* message);
//�����û�
_xdll_ void NetTuopuSetUserNum(char* usernum);
#ifdef __cplusplus
}
#endif
//---------------------------------------------------------------------------
#undef _xdll_
#endif	
