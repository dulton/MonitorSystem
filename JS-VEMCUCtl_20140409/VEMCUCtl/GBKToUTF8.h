#ifndef _GBK_TO_UTF8_H_
#define _GBK_TO_UTF8_H_

BOOL ConvertGBKToUTF8(char *szGBK,char *szUTF8,int nUTF8BufSize,int &nRealLen);//��GBKת����UTF8
BOOL ConvertUTF8ToGBK(char *szUTF8,char *szGBK,int nGBKBufSize,int &nRealLen);//��UTF8ת����GBK

#endif