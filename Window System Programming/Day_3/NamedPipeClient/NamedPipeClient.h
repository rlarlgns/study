
// NamedPipeClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CNamedPipeClientApp:
// �� Ŭ������ ������ ���ؼ��� NamedPipeClient.cpp�� �����Ͻʽÿ�.
//

class CNamedPipeClientApp : public CWinApp
{
public:
	CNamedPipeClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CNamedPipeClientApp theApp;