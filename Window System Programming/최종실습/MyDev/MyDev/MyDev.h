// MyDev.h : MyDev DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMyDevApp
// �� Ŭ������ ������ ������ MyDev.cpp�� �����Ͻʽÿ�.
//

class CMyDevApp : public CWinApp
{
public:
	CMyDevApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
