
// MyDevServer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMyDevServerApp:
// �� Ŭ������ ������ ���ؼ��� MyDevServer.cpp�� �����Ͻʽÿ�.
//

class CMyDevServerApp : public CWinApp
{
public:
	CMyDevServerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMyDevServerApp theApp;