// SysLinkTy.h: interface for the CLinkYk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSLINKTY_H__9CCA4309_286E_4981_BEF4_03EBCFAEED79__INCLUDED_)
#define AFX_SYSLINKTY_H__9CCA4309_286E_4981_BEF4_03EBCFAEED79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "canvas/LinkObjectBase.h"

#pragma pack(push,before_tagBSItem,1)

//����������
struct tagBSItem
{
  char strYxName[17]; //����ң������
	BYTE bValue;				//������������ֵ
};

#pragma pack(pop,before_tagBSItem,8)


typedef CTypedPtrArray<CPtrArray,tagBSItem*> tagBS_Array;

//ң��ͼԪ
class CLinkYk : public CLinkObjectBase  
{
	DECLARE_SERIAL(CLinkYk);
public:
	CLinkYk();
private:
	char m_Ykname[17];					//��ң�ص�Ӣ������
	BOOL m_bZK;									//TRUE-ֱ�� FALSE-ѡ��
	char m_Yxname_Hang[17];			//ժ/����ң�ŷ�����
	char m_Yxname_FX_Close[17];	//ң�غϷ�У��
	char m_Yxname_FX_Open[17];	//ң�طַ�У��
	char m_Yxname_Yk[17];				//ң�ط�����
	tagBS_Array m_BS_Array;			//������������


	bool m_bWatchMan;						//�����Ƿ���ü໤�˼໤���Ʒ�ʽ
	bool m_bGroup;							//�����Ƿ���÷�����Ʒ�ʽ
	DWORD m_dwFlag;							//����������Щ�����

	void InitMemory();

public:
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual BOOL OnEditProperties();
	virtual void Serialize_Ty(CArchive &ar);
	CLinkYk(CString strname,bool bWatchMan,bool bGroup,DWORD dwFlag);
	virtual ~CLinkYk();
	virtual void ParamReplace_Ty(CStringList& ruleList);

};


//ֱ��ͼԪ
class CLinkZk : public CLinkObjectBase  
{
	DECLARE_SERIAL(CLinkZk);
public:
	CLinkZk();
private:
	int m_node;
	int m_line;
	int m_rtu;
	char m_Yxname_Hang[17];			//ժ/����ң�ŷ�����
	void InitMemory();

public:
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual BOOL OnEditProperties();
	virtual void Serialize_Ty(CArchive &ar);
	CLinkZk(CString strname,bool bWatchMan,bool bGroup,DWORD dwFlag);
	virtual ~CLinkZk();
	virtual void ParamReplace_Ty(CStringList& ruleList);

};

//���綯̬��ɫ��Դ
class CNetColorPower : public CLinkObjectBase  
{
	DECLARE_SERIAL(CNetColorPower);
public:
	CNetColorPower();
private:
	char m_Ycname[17];					//��ң�ص�Ӣ������
	void InitMemory();

public:
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual BOOL OnEditProperties();
	virtual void Serialize_Ty(CArchive &ar);
	virtual ~CNetColorPower();
	virtual void ParamReplace_Ty(CStringList& ruleList);

};

//���綯̬��ɫʸ��ͼԪ
class CNetColorVector : public CLinkObjectBase  
{
	DECLARE_SERIAL(CNetColorVector);
public:
	CNetColorVector();
private:
	COLORREF m_color;					//ʧ����ɫ
	void InitMemory();

public:
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual BOOL OnEditProperties();
	virtual void Serialize_Ty(CArchive &ar);
	virtual ~CNetColorVector();
};


//���綯̬��ɫλͼͼԪ
class CNetColorBitmap : public CLinkObjectBase  
{
	DECLARE_SERIAL(CNetColorBitmap);
public:
	CNetColorBitmap();
private:
	char m_BmpName[33];					//ʧ��λͼ��
	void InitMemory();

public:
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual BOOL OnEditProperties();
	virtual void Serialize_Ty(CArchive &ar);
	virtual ~CNetColorBitmap();
};

//���綯̬��ɫ����ͼԪ
class CNetColorYx : public CLinkObjectBase  
{
	DECLARE_SERIAL(CNetColorYx);
public:
	CNetColorYx();
private:

public:
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual BOOL OnEditProperties();
	virtual void Serialize_Ty(CArchive &ar);
	virtual ~CNetColorYx();
};


class CLinkYT : public CLinkObjectBase  
{
	DECLARE_SERIAL(CLinkYT);
public:
	CLinkYT();
private:
	char m_YTname[17];					//��ң����Ӣ������
	int  m_dataType;					  //�������� 0-12λ ��0-16λ
	char m_Yxname_Yk[17];				//ң�ط�����
	tagBS_Array m_BS_Array;			//������������

	void InitMemory();

public:
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual BOOL OnEditProperties();
	virtual void Serialize_Ty(CArchive &ar);
	CLinkYT(CString strname);
	virtual ~CLinkYT();
	virtual void ParamReplace_Ty(CStringList& ruleList);

};


class CLinkYZTY : public CLinkObjectBase  
{
	DECLARE_SERIAL(CLinkYZTY);
public:
	CLinkYZTY();
private:
	char m_YZTYname_Up[17];			//�����ص�ѹ��ѹ��Ӣ������
	char m_YZTYname_Down[17];		//�����ص�ѹ��ѹ��Ӣ������
	char m_YZTYname_Stop[17];		//�����ص�ѹ��ͣ��Ӣ������
	int m_ActionType_Up;				//�����ص�ѹ��ѹ�㶯����ʽ
	int m_ActionType_Down;			//�����ص�ѹ��ѹ�㶯����ʽ
	int m_ActionType_Stop;			//�����ص�ѹ��ͣ�㶯����ʽ
	char m_Yxname_Yk[17];				//���ص�ѹ������

	void InitMemory();

public:
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual BOOL OnEditProperties();
	virtual void Serialize_Ty(CArchive &ar);
	CLinkYZTY(CString strname);
	virtual ~CLinkYZTY();
	virtual void ParamReplace_Ty(CStringList& ruleList);

};

class CLinkUnit : public CLinkObjectBase  
{
	DECLARE_SERIAL(CLinkUnit);
public:
	CLinkUnit();
private:
	int m_Fun;									//����Ͷ��(0)��Soe��ѯ(1)��yc��ѯ(2)��ycԽ�޲�ѯ(3)��
															//�������ѯ(4)��¼������(5)����ֵ����(6)������(7)
															//PT/CT���(8)
	void InitMemory();

public:
	char m_Unitname[17];				//�õ�Ԫ��Ӣ������
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual BOOL OnEditProperties();
	virtual void Serialize_Ty(CArchive &ar);
	CLinkUnit(CString strname);
	virtual ~CLinkUnit();
	virtual void ParamReplace_Ty(CStringList& ruleList);
};


class CLinkNode : public CLinkObjectBase  
{
	DECLARE_SERIAL(CLinkNode);
public:
	CLinkNode();
private:
	int m_Fun;									//Soe��ѯ(0)��yc��ѯ(1)��ycԽ�޲�ѯ(2)��
															//�������ѯ(3)
															
	void InitMemory();

public:
	char m_Nodename[17];				//�õ�Ԫ��Ӣ������
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual BOOL OnEditProperties();
	virtual void Serialize_Ty(CArchive &ar);
	CLinkNode(CString strname);
	virtual ~CLinkNode();
	virtual void ParamReplace_Ty(CStringList& ruleList);

};

class CLinkLine : public CLinkObjectBase  
{
	DECLARE_SERIAL(CLinkLine);
public:
	CLinkLine();
private:
	int m_Fun;									//Soe��ѯ(0)��yc��ѯ(1)��ycԽ�޲�ѯ(2)��
															//�������ѯ(3)
															
	void InitMemory();

public:
	char m_Linename[17];				//�õ�Ԫ��Ӣ������
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual BOOL OnEditProperties();
	virtual void Serialize_Ty(CArchive &ar);
	CLinkLine(CString strname);
	virtual ~CLinkLine();
	virtual void ParamReplace_Ty(CStringList& ruleList);

};


typedef struct 
{              
	//BYTE	udflag ;//�����־ 0:ͼԪ->modem  1:modem->ͼԪ
	DWORD	adptid ;//������id
	char	telno[12] ;//�绰����
	//BYTE	cmdid ;//����id  0:����  1:�л����Զ���ѯ״̬
	DWORD	dotime ;//����ʱ�䣨��λ�룩 0:������ʱ������
}ModemManualDailEvent ;
//Modem�ֶ�����ͼԪ
class CLinkModem : public CLinkObjectBase
{
	DECLARE_SERIAL(CLinkModem) ;
public:
	virtual BOOL OnEditProperties();
	CLinkModem() ;
	virtual ~CLinkModem() ;
private:
	//����ͼԪ
	CString m_strname ;//����˵��
	ModemManualDailEvent m_modem ;
	void InitMemory();
	virtual void Save_Ty(CFile *file, BOOL Yn);
	
	virtual void Serialize_Ty(CArchive &ar);

};


class CLinkYT2 : public CLinkObjectBase  
{
	DECLARE_SERIAL(CLinkYT2);
public:
	CLinkYT2();
private:
	char m_YTname[17];					//��ң����Ӣ������
	int  m_dataType;					  //�������� 0-12λ ��0-16λ
	char m_Yxname_Yk[17];				//ң�ط�����
	tagBS_Array m_BS_Array;			//������������
	float m_fPianCha;               //ƫ��ֵ
	int m_nXiaoShu;                 //С��λ��
	int m_nBiLi;                    //����

	void InitMemory();

public:
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual BOOL OnEditProperties();
	virtual void Serialize_Ty(CArchive &ar);
	CLinkYT2(CString strname);
	virtual ~CLinkYT2();
	virtual void ParamReplace_Ty(CStringList& ruleList);


};

////////////////////////////////////////////////////
//2004.3.29
//pang����ң���������ͼԪ
class CLinkYXBind : public CLinkObjectBase
{
	DECLARE_SERIAL(CLinkYXBind) ;
public:
	CLinkYXBind() ;
	virtual ~CLinkYXBind() ;
public:
	virtual BOOL OnEditProperties();
	char m_Ename[17] ;//�󶨵�Ӣ����
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual void Serialize_Ty(CArchive &ar);
	virtual void ParamReplace_Ty(CStringList& ruleList);

};

////////////////////////////////////////////////////
//���Ӽ��ģ������ͼԪ
class CLinkYSHBind : public CLinkObjectBase
{
	DECLARE_SERIAL(CLinkYSHBind) ;
public:
	CLinkYSHBind() ;
	virtual ~CLinkYSHBind() ;
public:
	virtual BOOL OnEditProperties();
	char m_Ename[17] ;//�󶨵�Ӣ����
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual void Serialize_Ty(CArchive &ar);
	virtual void ParamReplace_Ty(CStringList& ruleList);

};


//////////////////////////////////////////////////////////
//2004.3.30
//pang����Ⱥ������ͼԪ
class CLinkQK : public CLinkObjectBase
{
	DECLARE_SERIAL(CLinkQK) ;
public:
	CLinkQK() ;
	virtual ~CLinkQK() ;
public:
	virtual BOOL OnEditProperties();
	char m_Ename[17] ;//�󶨵���Ӣ����

	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual void Serialize_Ty(CArchive &ar);

private:
	bool m_bWatchMan;						//�����Ƿ���ü໤�˼໤���Ʒ�ʽ
	bool m_bGroup;							//�����Ƿ���÷�����Ʒ�ʽ
	DWORD m_dwFlag;							//����������Щ�����
};

///////////////////////////////////////////////////////////////
//2004.4.3
//pang���Ӻ�̨������
class CLinkSoftRepair : public CLinkObjectBase
{
	DECLARE_SERIAL(CLinkSoftRepair) ;
public:
	CLinkSoftRepair() ;
	virtual ~CLinkSoftRepair() ;
public:
	virtual BOOL OnEditProperties();
	char m_Ename[17] ;//�󶨵�Ӣ����
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual void Serialize_Ty(CArchive &ar);
	virtual void ParamReplace_Ty(CStringList& ruleList);


} ;
///////////////////////////////////////////////////////////////
//2004.4.3
//pang���ӵ�Ԫ��չ
class CLinkUnitExtend : public CLinkObjectBase
{
	DECLARE_SERIAL(CLinkUnitExtend) ;
public:
	CLinkUnitExtend() ;
private:
	char m_Unitname[17] ;
	int m_nFun ;
	void InitMemory() ;
public:
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual BOOL OnEditProperties();
	virtual void Serialize_Ty(CArchive &ar);
	CLinkUnitExtend(CString strname);
	virtual ~CLinkUnitExtend();
	virtual void ParamReplace_Ty(CStringList& ruleList);

} ;

/////////////////////////////////////////////////////////////////
//2004.06.05
//pang�������߿�������ͼԪ
class CLinkKX : public CLinkObjectBase
{
	DECLARE_SERIAL(CLinkKX) ;
public:
	CLinkKX() ;
	virtual ~CLinkKX() ;
public:
	virtual BOOL OnEditProperties();
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual void Serialize_Ty(CArchive &ar);
private:
	char m_Ename[4] ;
	char m_Cname[13] ;
	char m_kgEname[17] ;
	virtual void ParamReplace_Ty(CStringList& ruleList);

} ;

/////////////////////////////////////////////////////////////////
//2004.06.05
//pang����������������ͼԪ
class CLinkKXSection : public CLinkObjectBase
{
	DECLARE_SERIAL(CLinkKXSection) ;
public:
	CLinkKXSection() ;
	virtual ~CLinkKXSection() ;
public:
	virtual BOOL OnEditProperties();
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual void Serialize_Ty(CArchive &ar);
private:
	char m_ename[4] ;
	char m_cname[13] ;
	char m_qdEname[4] ;
	char m_qdCname[13] ;
	COLORREF m_col1;
	COLORREF m_col2;
	char m_bmpName1[33] ;
	char m_bmpName2[33] ;
} ;

////////////////////////////////////////////////////////////////
//2004.08.03
//st����ˮ��ҵ��������ͼԪ
class CLinkDoubleCtrl : public CLinkObjectBase  
{
	DECLARE_SERIAL(CLinkDoubleCtrl);
public:
	CLinkDoubleCtrl();
private:
	char m_OprtName1[11];
	char m_OprtName2[11];
	char m_YKName1[18];
	char m_YKName2[18];
	int m_nActType1;
	int m_nActType2;
	bool m_bOnceQuit;

	void InitMemory();

public:
	virtual void Save_Ty(CFile *file, BOOL Yn);
	virtual BOOL OnEditProperties();
	virtual void Serialize_Ty(CArchive &ar);
	CLinkDoubleCtrl(CString strname);
	virtual ~CLinkDoubleCtrl();
	virtual void ParamReplace_Ty(CStringList& ruleList);

};

#endif // !defined(AFX_SYSLINKTY_H__9CCA4309_286E_4981_BEF4_03EBCFAEED79__INCLUDED_)
