// LinkClub.cpp : implementation file
//

#include "stdafx.h"
//#include "sp_draw.h"
#include "canvas/LinkClub.h"
#include "dialog/LinkClub_Prop1.h"
#include "dialog/LinkClub_Prop2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinkClub
IMPLEMENT_SERIAL(CLinkClub,CLinkObjectBase,0)

CLinkClub::CLinkClub()
:CLinkObjectBase(lnkClub,"")
{
	sprintf(m_name,"δ�����ͼ");

	barcount=0;

	LOGFONT initfont;
	initfont.lfHeight=15;
	initfont.lfWidth=5;
	initfont.lfEscapement=0;//��ת�Ƕ�
	initfont.lfOrientation=0;
	initfont.lfWeight=FW_MEDIUM;
	initfont.lfItalic=false;
//		initfont.lfWeight=700;
//		initfont.lfItalic=true;
	initfont.lfUnderline=false;
	initfont.lfStrikeOut=false;//ǿ����
	initfont.lfCharSet=GB2312_CHARSET;
	initfont.lfOutPrecision=OUT_DEFAULT_PRECIS;//�������
	initfont.lfClipPrecision=CLIP_DEFAULT_PRECIS;//���þ���
	initfont.lfQuality=DEFAULT_QUALITY;
	initfont.lfPitchAndFamily=DEFAULT_PITCH;//����������
	sprintf(initfont.lfFaceName,"����");

	sprintf(clubinfo.title,"δ֪����");
	clubinfo.titlefont=initfont;
	clubinfo.titlecolor=0xff0000;
	sprintf(clubinfo.yunit,"δ֪��λ");
	clubinfo.ymax=100;//y�����ֵ
	clubinfo.ymin=0;//y����Сֵ
	clubinfo.yunitfont=initfont;//y�ᵥλ����
	clubinfo.yunitcolor=0xff0000;//Y�ᵥλ��ɫ
	clubinfo.coordinatefont=initfont;//����ϵ����
	clubinfo.coordinatecolor=0xff0000;//����ϵ��ɫ
	clubinfo.backcolor=0x000000;//����ɫ
	clubinfo.allmaxmin=0;//ͳһԽ��ֵ0 not 1 yes
	clubinfo.maxvalue=0;//ͳһ�����ֵ
	clubinfo.minvalue=0;//ͳһ����Сֵ
	clubinfo.clubwidth=25;//�����
	clubinfo.clubspace=10;//�����
}

CLinkClub::~CLinkClub()
{
}


BOOL CLinkClub::OnEditProperties()
{
	CPropertySheet sheet( _T("��ͼ����..") );
	CLinkClub_Prop1 dlg;
	CLinkClub_Prop2 dlg2;
 	dlg.SetPara(m_name,clubinfo);
	dlg2.SetPara(barcount,barinfo);
	sheet.AddPage( (CPropertyPage*)&dlg );
	sheet.AddPage( (CPropertyPage*)&dlg2);
	if (sheet.DoModal() == IDOK)
	{
		dlg.GetPara(m_name,&clubinfo);
    	dlg2.GetPara(&barcount,(STRUCT_SINGLEBAR *)&barinfo);
		return TRUE;
	}
    return FALSE;
}

void CLinkClub::Save_Ty(CFile *file, BOOL Yn)
{
	if(Yn)	//������ڽ��б���
	{
		file->Write((unsigned char *)clubinfo.title,sizeof(char)*33);
		file->Write((unsigned char *)&clubinfo.titlefont,sizeof(LOGFONT));
		file->Write((unsigned char *)&clubinfo.titlecolor,sizeof(COLORREF));
		file->Write((unsigned char *)clubinfo.yunit,sizeof(char)*9);
		file->Write((unsigned char *)&clubinfo.ymax,sizeof(float));
		file->Write((unsigned char *)&clubinfo.ymin,sizeof(float));
		file->Write((unsigned char *)&clubinfo.yunitfont,sizeof(LOGFONT));
		file->Write((unsigned char *)&clubinfo.yunitcolor,sizeof(COLORREF));
		file->Write((unsigned char *)&clubinfo.coordinatefont,sizeof(LOGFONT));
		file->Write((unsigned char *)&clubinfo.coordinatecolor,sizeof(COLORREF));
		file->Write((unsigned char *)&clubinfo.backcolor,sizeof(COLORREF));
		file->Write((unsigned char *)&clubinfo.allmaxmin,sizeof(BYTE));
		file->Write((unsigned char *)&clubinfo.maxvalue,sizeof(float));
		file->Write((unsigned char *)&clubinfo.minvalue,sizeof(float));
		file->Write((unsigned char *)&clubinfo.clubwidth,sizeof(DWORD));
		file->Write((unsigned char *)&clubinfo.clubspace,sizeof(DWORD));

		file->Write((unsigned char *)&barcount,sizeof(BYTE));
		for (int i=0;i<barcount;i++)
		{
			file->Write((unsigned char *)barinfo[i].ename,sizeof(BYTE)*17);
			file->Write((unsigned char *)barinfo[i].cname,sizeof(BYTE)*9);
		}
	}
	else
	{
		file->Read((unsigned char *)clubinfo.title,sizeof(char)*33);
		file->Read((unsigned char *)&clubinfo.titlefont,sizeof(LOGFONT));
		file->Read((unsigned char *)&clubinfo.titlecolor,sizeof(COLORREF));
		file->Read((unsigned char *)clubinfo.yunit,sizeof(char)*9);
		file->Read((unsigned char *)&clubinfo.ymax,sizeof(float));
		file->Read((unsigned char *)&clubinfo.ymin,sizeof(float));
		file->Read((unsigned char *)&clubinfo.yunitfont,sizeof(LOGFONT));
		file->Read((unsigned char *)&clubinfo.yunitcolor,sizeof(COLORREF));
		file->Read((unsigned char *)&clubinfo.coordinatefont,sizeof(LOGFONT));
		file->Read((unsigned char *)&clubinfo.coordinatecolor,sizeof(COLORREF));
		file->Read((unsigned char *)&clubinfo.backcolor,sizeof(COLORREF));
		file->Read((unsigned char *)&clubinfo.allmaxmin,sizeof(BYTE));
		file->Read((unsigned char *)&clubinfo.maxvalue,sizeof(float));
		file->Read((unsigned char *)&clubinfo.minvalue,sizeof(float));
		file->Read((unsigned char *)&clubinfo.clubwidth,sizeof(DWORD));
		file->Read((unsigned char *)&clubinfo.clubspace,sizeof(DWORD));

		file->Read((unsigned char *)&barcount,sizeof(BYTE));
		for (int i=0;i<barcount;i++)
		{
			file->Read((unsigned char *)barinfo[i].ename,sizeof(BYTE)*17);
			file->Read((unsigned char *)barinfo[i].cname,sizeof(BYTE)*9);
		}
	}
}

void CLinkClub::Serialize_Ty(CArchive &ar)
{
	if(ar.IsStoring())  
	{
		ar.Write((unsigned char *)clubinfo.title,sizeof(char)*33);
		ar.Write((unsigned char *)&clubinfo.titlefont,sizeof(LOGFONT));
		ar.Write((unsigned char *)&clubinfo.titlecolor,sizeof(COLORREF));
		ar.Write((unsigned char *)clubinfo.yunit,sizeof(char)*9);
		ar.Write((unsigned char *)&clubinfo.ymax,sizeof(float));
		ar.Write((unsigned char *)&clubinfo.ymin,sizeof(float));
		ar.Write((unsigned char *)&clubinfo.yunitfont,sizeof(LOGFONT));
		ar.Write((unsigned char *)&clubinfo.yunitcolor,sizeof(COLORREF));
		ar.Write((unsigned char *)&clubinfo.coordinatefont,sizeof(LOGFONT));
		ar.Write((unsigned char *)&clubinfo.coordinatecolor,sizeof(COLORREF));
		ar.Write((unsigned char *)&clubinfo.backcolor,sizeof(COLORREF));
		ar.Write((unsigned char *)&clubinfo.allmaxmin,sizeof(BYTE));
		ar.Write((unsigned char *)&clubinfo.maxvalue,sizeof(float));
		ar.Write((unsigned char *)&clubinfo.minvalue,sizeof(float));
		ar.Write((unsigned char *)&clubinfo.clubwidth,sizeof(DWORD));
		ar.Write((unsigned char *)&clubinfo.clubspace,sizeof(DWORD));

		ar.Write((unsigned char *)&barcount,sizeof(BYTE));
		for (int i=0;i<barcount;i++)
		{
			ar.Write((unsigned char *)&barinfo[i].ename,sizeof(BYTE)*17);
			ar.Write((unsigned char *)&barinfo[i].cname,sizeof(BYTE)*9);
		}
	}
	else
	{
		ar.Read((unsigned char *)clubinfo.title,sizeof(char)*33);
		ar.Read((unsigned char *)&clubinfo.titlefont,sizeof(LOGFONT));
		ar.Read((unsigned char *)&clubinfo.titlecolor,sizeof(COLORREF));
		ar.Read((unsigned char *)clubinfo.yunit,sizeof(char)*9);
		ar.Read((unsigned char *)&clubinfo.ymax,sizeof(float));
		ar.Read((unsigned char *)&clubinfo.ymin,sizeof(float));
		ar.Read((unsigned char *)&clubinfo.yunitfont,sizeof(LOGFONT));
		ar.Read((unsigned char *)&clubinfo.yunitcolor,sizeof(COLORREF));
		ar.Read((unsigned char *)&clubinfo.coordinatefont,sizeof(LOGFONT));
		ar.Read((unsigned char *)&clubinfo.coordinatecolor,sizeof(COLORREF));
		ar.Read((unsigned char *)&clubinfo.backcolor,sizeof(COLORREF));
		ar.Read((unsigned char *)&clubinfo.allmaxmin,sizeof(BYTE));
		ar.Read((unsigned char *)&clubinfo.maxvalue,sizeof(float));
		ar.Read((unsigned char *)&clubinfo.minvalue,sizeof(float));
		ar.Read((unsigned char *)&clubinfo.clubwidth,sizeof(DWORD));
		ar.Read((unsigned char *)&clubinfo.clubspace,sizeof(DWORD));

		ar.Read((unsigned char *)&barcount,sizeof(BYTE));
		for (int i=0;i<barcount;i++)
		{
			ar.Read((unsigned char *)&barinfo[i].ename,sizeof(BYTE)*17);
			ar.Read((unsigned char *)&barinfo[i].cname,sizeof(BYTE)*9);
		}
	}

}

/////////////////////////////////////////////////////////////////////////////
// CLinkClub message handlers

//DEL void CLinkClub::On_Show_Club(tagInterface_All &allInt)
//DEL {
//DEL 
//DEL }
