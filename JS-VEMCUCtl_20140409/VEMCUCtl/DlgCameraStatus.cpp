// DlgCameraStatus.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VEMCUCtl.h"
#include "DlgCameraStatus.h"


// CDlgCameraStatus �Ի���

IMPLEMENT_DYNAMIC(CDlgCameraStatus, CDialog)

CDlgCameraStatus::CDlgCameraStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCameraStatus::IDD, pParent)
{
	
}

CDlgCameraStatus::CDlgCameraStatus( char *szCameraCode, CWnd* pParent /*= NULL*/ )
	: CDialog(CDlgCameraStatus::IDD, pParent)
{
	memcpy(m_szCameraCode,szCameraCode,20);
	m_pDiagnosisInfo = NULL;
	m_strDiagnosisText1 = "";
	m_strDiagnosisText2 = "";
}

CDlgCameraStatus::~CDlgCameraStatus()
{
	if (m_pDiagnosisInfo!=NULL)
	{
		delete m_pDiagnosisInfo;
	}
}

void CDlgCameraStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CAMERA_STATUS_VALUE, m_strCameraStatusValue);
}


BEGIN_MESSAGE_MAP(CDlgCameraStatus, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgCameraStatus::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDlgCameraStatus ��Ϣ�������

void CDlgCameraStatus::OnBnClickedButton2()
{
	OnOK();
}

BOOL CDlgCameraStatus::OnInitDialog()
{
	CDialog::OnInitDialog();

	//����CameraCode��ȡ������Ϣ
	m_pDiagnosisInfo = GetDiagnosisInfoByCameraCode(m_szCameraCode);
	
	//���ݹ�����Ϣƴ���ַ���
	if (m_pDiagnosisInfo == NULL)
	{	
		m_strDiagnosisText1.Format("%s","û�鵽������ͷ�Ĺ��������Ϣ");
	}
	else
	{
		SpellDiagnosisText(m_pDiagnosisInfo, m_strDiagnosisText1, m_strDiagnosisText2);
	}

	GetDlgItem(IDC_CAMERA_STATUS_VALUE)->SetWindowText(m_strDiagnosisText1);
	GetDlgItem(IDC_STATIC_DIAGNOSIS_INFO)->SetWindowText(m_strDiagnosisText2);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgCameraStatus::SpellDiagnosisText(_T_DIAGNOSIS_INFO* pDiagnosisInfo, CString &strDiagnosisText1, CString &strDiagnosisText2)
{
	//�޹���
	if (pDiagnosisInfo->nTotalResult == 0)
	{
		strDiagnosisText1 += "�޹���";
	}
	//�й���
	if (pDiagnosisInfo->nTotalResult == 1)
	{
		strDiagnosisText1 += "�й���";
		if (pDiagnosisInfo->nLoginErr == 1)
		{
			strDiagnosisText2 += "��½ʧ��,";
		}
		if (pDiagnosisInfo->nOpenVideoErr == 1)
		{
			strDiagnosisText2 += "����Ƶʧ��,";
		}
		if (pDiagnosisInfo->nRecordErr == 1)
		{
			strDiagnosisText2 += "¼��ʧ��,";
		}
		if (pDiagnosisInfo->nLose == 1)
		{
			strDiagnosisText2 += "��Ƶ��ʧ,";
		}
		if (pDiagnosisInfo->nImpluse == 1)
		{
			strDiagnosisText2 += "�����,";
		}
		if (pDiagnosisInfo->nStripe == 1)
		{
			strDiagnosisText2 += "���Ƹ���,";
		}
		if (pDiagnosisInfo->nBright == 1)
		{
			strDiagnosisText2 += "�����쳣,";
		}
		if (pDiagnosisInfo->nVague == 1)
		{
			strDiagnosisText2 += "��Ƶģ��,";
		}
		if (pDiagnosisInfo->nColor == 1)
		{
			strDiagnosisText2 += "��Ƶƫɫ,";
		}
		if (pDiagnosisInfo->nPTZ == 1)
		{
			strDiagnosisText2 += "��̨ʧ��,";
		}
		if (pDiagnosisInfo->nShake == 1)
		{
			strDiagnosisText2 += "����,";
		}
	}
}


_T_DIAGNOSIS_INFO* CDlgCameraStatus::GetDiagnosisInfoByCameraCode(char *szCameraCode)
{
	char sql_buf[1024] = {0};
	MYSQL_RES * res = NULL;
	MYSQL_ROW	row ;
    _T_DIAGNOSIS_INFO *pDiagnosisInfo = NULL; 

	// ��ȡ��ǰ��Ƶƽ̨��������Ϣ
	sprintf_s(sql_buf, "SELECT a.CameraCode,a.TotalResult,a.ResultOfLoginErr,a.ResultOfOpenVideoErr,a.ResultOfRecordErr, "
		" a.ResultOfLose,a.ResultOfImpluse,a.ResultOfStripe,a.ResultOfBright,a.ResultOfVague,a.ResultOfColor, "
	    " a.ResultOfPTZ,a.ResultOfShake FROM vaichannlscheckresults AS a "
	    " where a.CameraCode='%s'", szCameraCode);

	if (!mysql_query(g_mySqlData, sql_buf))
	{
		res = mysql_store_result(g_mySqlData);

		while ( row = mysql_fetch_row( res ) )
		{
			pDiagnosisInfo = new _T_DIAGNOSIS_INFO;
			pDiagnosisInfo->nTotalResult = atoi(row[1]);
			pDiagnosisInfo->nLoginErr = atoi(row[2]);
			pDiagnosisInfo->nOpenVideoErr = atoi(row[3]);
			pDiagnosisInfo->nRecordErr = atoi(row[4]);
			pDiagnosisInfo->nLose = atoi(row[5]);
			pDiagnosisInfo->nImpluse = atoi(row[6]);
			pDiagnosisInfo->nStripe = atoi(row[7]);
			pDiagnosisInfo->nBright = atoi(row[8]);
			pDiagnosisInfo->nVague = atoi(row[9]);
			pDiagnosisInfo->nColor = atoi(row[10]);
			pDiagnosisInfo->nPTZ = atoi(row[11]);
			pDiagnosisInfo->nShake = atoi(row[12]);
		}
		mysql_free_result(res) ;
	}

	return pDiagnosisInfo;
}
