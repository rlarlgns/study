// MyDll.h : MyDll DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMyDllApp
// �� Ŭ������ ������ ������ MyDll.cpp�� �����Ͻʽÿ�.
//

class CMyDllApp : public CWinApp
{
public:
	CMyDllApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
