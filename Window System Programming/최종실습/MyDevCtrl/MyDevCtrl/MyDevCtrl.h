
// MyDevCtrl.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMyDevCtrlApp:
// �� Ŭ������ ������ ���ؼ��� MyDevCtrl.cpp�� �����Ͻʽÿ�.
//

class CMyDevCtrlApp : public CWinApp
{
public:
	CMyDevCtrlApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMyDevCtrlApp theApp;