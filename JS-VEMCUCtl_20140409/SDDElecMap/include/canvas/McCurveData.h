#pragma once

// CMcCurveData ����Ŀ��
#include<afxtempl.h>

struct TCurve
{
	
	int ncurvecolor;
	BYTE BcurvechannelNO;
	BYTE Bdot;
	float fcurveratio;
	BYTE Bprecision;
	BYTE nlinenode;
	BYTE nlineline;
	BYTE nlinertu;
	char unit[8];			//���
};
typedef CArray<TCurve,TCurve> CURVEARRAY;
class CMcCurveData : public CObject
{
public:
	CString stroldsection;
	CMcCurveData();
public:
	CString strMcename;
	BOOL bonlyrealline;
	int nIprecision;
	int nVprecision;
	float fleftcoord;
	float ftopcoord;
	float frightcoord;
	float fbottomcoord;
	float fImin;
	float fImax;
	float fVmin;
	float fVmax;
	BYTE nNode;
	BYTE nLine;
	BYTE nRtu;
	BOOL bgtmode;
	BOOL bNeedsave;
	CString UpName;
	CString DownName;
	int m_realtime_style;					// ʵʱ������ʾ���������ں����������� 
												//		0-��ʱ���ң������ 1-����ʱ���ң������

	
	CURVEARRAY gtIcurvearray;
	CURVEARRAY gtVcurvearray;
	CURVEARRAY zbIcurvearray;
	CURVEARRAY zbVcurvearray;

//	CURVEARRAY old_gtIcurvearray;
	//CURVEARRAY old_gtVcurvearray;
	//CURVEARRAY old_zbIcurvearray;
	//CURVEARRAY old_zbVcurvearray;
	virtual ~CMcCurveData();
public:
	//void arraybackup();
	//void arrayrestore();
	void WriteCurveData();
	void SetPath(LPCTSTR strpath);
	BOOL ReadCurveData();
	void Duplicate(CMcCurveData*);
private:
	CString strfilepath;
	void extractstring(PCHAR,PTSTR,PTSTR,PTSTR,PTSTR,PTSTR,PTSTR,PTSTR,PTSTR,PTSTR);
public:
//	virtual void Serialize(CArchive& ar);
};


