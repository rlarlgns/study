
// Race.h : Race ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CRaceApp:
// �� Ŭ������ ������ ���ؼ��� Race.cpp�� �����Ͻʽÿ�.
//

class CRaceApp : public CWinApp
{
public:
	CRaceApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRaceApp theApp;
