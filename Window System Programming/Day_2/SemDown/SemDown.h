
// SemDown.h : SemDown ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CSemDownApp:
// �� Ŭ������ ������ ���ؼ��� SemDown.cpp�� �����Ͻʽÿ�.
//

class CSemDownApp : public CWinApp
{
public:
	CSemDownApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSemDownApp theApp;
