#pragma once

#define OPEN_CAMERA_BY_PLATFORM 0//ͨ������ƽ̨������ͷ
#define OPEN_CAMERA_BY_DIRECT_DEVICE 1//ֱ���豸������ͷ

class CCameraControl
{
public:
	CCameraControl(void);
	~CCameraControl(void);

public:
	int OpenCameraByDirectDevice(CString strDvrIP, int nDvrPort, CString strUsername, CString strPassword, int nDvrType, int nChannel, HWND playwnd);
	int OpenCamera( CString strDvrIP, int nDvrPort, int nChannel, int nDvrType, CString strUsername, CString strPassword, int nOpenType, HWND playwnd );
};
