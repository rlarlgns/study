
// Day_4.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CDay_4App:
// �� Ŭ������ ������ ���ؼ��� Day_4.cpp�� �����Ͻʽÿ�.
//

class CDay_4App : public CWinApp
{
public:
	CDay_4App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CDay_4App theApp;