
// ProcB.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CProcBApp:
// �� Ŭ������ ������ ���ؼ��� ProcB.cpp�� �����Ͻʽÿ�.
//

class CProcBApp : public CWinApp
{
public:
	CProcBApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CProcBApp theApp;