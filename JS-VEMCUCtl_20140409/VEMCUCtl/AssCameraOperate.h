#ifndef _ASSCAMERAOPERATE_H_
#define _ASSCAMERAOPERATE_H_

//������ͷ
bool AssOpenCamera(char* ip,unsigned short port, char* user, char* password,unsigned short dvrtype,unsigned short dvrid,unsigned short channel,int id ,HWND playwnd);

//����ͷתԤ��λ
bool AssToPreset(char* ip,unsigned short port, char* user, char* password,unsigned short dvrtype,unsigned short dvrid,unsigned short channel,unsigned short control,unsigned short speed);

//�ر�����ͷ
bool AssCloseCamera(int nID);

#endif