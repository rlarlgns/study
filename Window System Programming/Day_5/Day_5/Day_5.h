
// Day_5.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CDay_5App:
// �� Ŭ������ ������ ���ؼ��� Day_5.cpp�� �����Ͻʽÿ�.
//

class CDay_5App : public CWinApp
{
public:
	CDay_5App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CDay_5App theApp;