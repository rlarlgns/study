
// BackEvent.h : BackEvent ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CBackEventApp:
// �� Ŭ������ ������ ���ؼ��� BackEvent.cpp�� �����Ͻʽÿ�.
//

class CBackEventApp : public CWinApp
{
public:
	CBackEventApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBackEventApp theApp;
