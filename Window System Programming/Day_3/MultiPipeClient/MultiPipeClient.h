
// MultiPipeClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMultiPipeClientApp:
// �� Ŭ������ ������ ���ؼ��� MultiPipeClient.cpp�� �����Ͻʽÿ�.
//

class CMultiPipeClientApp : public CWinApp
{
public:
	CMultiPipeClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMultiPipeClientApp theApp;