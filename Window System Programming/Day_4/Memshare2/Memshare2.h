
// Memshare2.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMemshare2App:
// �� Ŭ������ ������ ���ؼ��� Memshare2.cpp�� �����Ͻʽÿ�.
//

class CMemshare2App : public CWinApp
{
public:
	CMemshare2App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMemshare2App theApp;