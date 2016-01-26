#if !defined(DATASTYLE_H)
#define DATASTYLE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*---------------------------------------------------------------------------------
	*								DRAWTYPE ������Ļ���
	*--------------------------------------------------------------------------------

  drwNULL		����,
	drwJH			�򵥼���ͼ�ι�����,
	drwDH			����������,
	drwTK			ʸ��ͼ/λͼ������,
	drwSZ			��ֵͼԪ������,
	drwSB			�豸ͼԪ������,
	drwQX			���߹�����,
	drwKZ			����ͼԪ������,
	drwZZ			װ��ͼԪ������,
	drwQT			ϵͳ�����๤����
	drwNetColor���綯̬��ɫ������
	drwINTF   Ӧ�ýӿڹ�����
-----------------------------------------------------------------------------------
*/
typedef enum
{
  drwNULL=0,drwJH, drwDH,drwTK,drwSZ,drwSB,drwQX,drwKZ,drwZZ,drwQT,drwNetColor,drwINTF,drwSTAS
} DRAWTYPE;

#define HMC_MAXNUM		8		//����������Ŀ
#define MAX_QGMROW		50
#define MAX_QGMCOL		50

#pragma pack(push,before_tagHuaMianFileHead,1)

//������ʶ
struct tagHMLayerID
{
	int       iLayerNo;						//�����
	char    strLayerName[33];		//�����������
	float    fScale;							//Ĭ����ʾ����
	float	   fStartScale;				    //��ʾ��ʼ��Χ
	float    fEndScale;					    //��ʾ��ֹ��Χ
	int       iOffset;						    //���������ļ���ʼ����ƫ����
	int	   iStartNumber;				//ͼԪ������λ�ñ��
	int	   iEndNumber;					//ͼԪ��ǰ���λ�ñ��	
	int	   IDDef;							//ͼԪ��ʶ����ʼֵ
	BOOL  bHide;							//�Ƿ�������ʾ

	const tagHMLayerID& operator =( const tagHMLayerID& srcHMLayerID);

};

typedef struct tagHMLayerID  tagHMLayerBase;

//�����ļ�ͷ��Ҫ��Ϣ
typedef struct 
{
	WORD	   wPicFlag;									//�ļ��ض���־
	WORD	   wMVersion;								//�ļ��߰汾��
	WORD     wEVersion;								//�ļ��Ͱ汾��
	DWORD  dwPICStyle;								//������
	WORD	   wPicWidth;								//ͼ�����
	WORD	   wPicHeight;								//ͼ���߶�
	WORD	   wResolution;							    //��Ļ�ֱ��ʵĿ��
	WORD	   hResolution;							    //��Ļ�ֱ��ʵĸ߶�
	float        fDefaultScale;						    //Ĭ�ϵĻ�����ʾ����
	COLORREF dwBackColor;						//������ɫ
	DWORD  dwBackImageNo;						//����λͼ���
}tagHuaMianBase;

//�����ļ�ͷ��Ϣ
typedef struct 
{
	tagHuaMianBase recBase;					//�����ļ�ͷ��Ҫ��Ϣ
	BYTE                 	bLayerNum;				//�����ʵ����Ŀ
	int                        iLayerIdDef;				//��������ʼԤ�����
	tagHMLayerBase arrLayer[16];		    //������Ҫ��Ϣ��
	DWORD	            dwEpdYxListOffset;	//����ң�ž����ļ���ʼ����ƫ����
	DWORD               dwEpdYcListOffset;	//����ң������ļ���ʼ����ƫ����	
}tagHuaMianFileHead;	

#pragma pack(pop,before_tagHuaMianFileHead,8)

//�����ʶ
struct tagHMID
{
	char        strHMName[33];		//����������
	DWORD dwflag;						//�����־
	DWORD dwStyle;						//������
	WORD   wWidth;						//������
	WORD   wHeight;						//����߶�
	int          iLayerIdDef;				//��������ʼԤ�����
	WORD   wLayerNum;				//�����Ļ������Ŀ
	float      fScale;							//����Ĭ����ʾ����
	tagHMLayerID ArrHMLayer[HMC_MAXNUM];//�����Ļ������Ϣ

public:
	void Exchange(int i,int j);
	int    FindHMLayerID(LPCSTR strname);
	void DeleteHMLayer(LPCSTR strname);
	void SetHMLayer(LPCSTR strname,tagHMLayerID* pLayer);
	void AddHMLayer(tagHMLayerID*pLayer);
	const tagHMID& operator =( const tagHMID& srcHMID);
};


//�����ʶ��Ϣ��
typedef CTypedPtrList<CPtrList, tagHMID*> tagHMIDList;


#endif 
