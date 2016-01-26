// QGM.h: interface for the CQGM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QGM_H__EFCBD5FC_63A4_445B_B21F_29CC0756F5D5__INCLUDED_)
#define AFX_QGM_H__EFCBD5FC_63A4_445B_B21F_29CC0756F5D5__INCLUDED_

#include "canvas/TyBase.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*-----------------------------------------------------------------------------
	--------------------		�����ࣺ	�и���CQGM 
 	--------------------		����ߣ�	������
 	--------------------    ���ڣ�		2001-9-18		
	-----------------------------------------------------------------------------
	BOOL IntersectRect(float x0,float y0,float x1,float y1);
  ����:
			�жϸ������Ƿ���и����ཻ
	����:
	void SetBounds(float x0,float y0,float x1,float y1);
  ����:
			�����и��淶Χ
  void RemoveTy(CTyBase *pTy)
  ����:
			����ͼԪpTy
	����:
		pTy-ָ��ͼԪ��ָ�� 


	void Front(CTyBase* pTy);
	����: ͼԪ�Ƶ�ǰ��
	����:
		pTy-ָ��ͼԪ��ָ�� 

	void Back(CTyBase * pTy);
	����: ͼԪ�Ƶ����
	����:
		pTy-ָ��ͼԪ��ָ�� 


	-----------------------------------------------------------------------------
*/


class CQGM : public CObject  
{
	DECLARE_SERIAL(CQGM);

protected:
	CQGM(){};

public:
	void AddTy(CTyBase* pTy);
	void ZhenLi();
	CTyBase * ObjectAt(PointStruct pt,float errRange);
	void Front(CTyBase* pTy);
	void Back(CTyBase* pTy);
	void RemoveTy(CTyBase * pTy);
	void Clear();
	void SetBounds(float x0,float y0,float x1,float y1);
	BOOL IntersectRect(float x0,float y0,float x1,float y1);

	CTyBaseList m_TyBaseList;		//�и�������е�ͼԪ
	CQGM(float x0,float y0,float x1,float y1);
	virtual ~CQGM();

	//�и���ķ�Χ
	float m_fX0;
	float m_fY0;
	float m_fX1;
	float m_fY1;
};

#endif // !defined(AFX_QGM_H__EFCBD5FC_63A4_445B_B21F_29CC0756F5D5__INCLUDED_)
