// MyDev.cpp : �ش� DLL�� �ʱ�ȭ ��ƾ�� �����մϴ�.
//

#include "stdafx.h"
#include "MyDev.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: �� DLL�� MFC DLL�� ���� �������� ��ũ�Ǿ� �ִ� ���
//		MFC�� ȣ��Ǵ� �� DLL���� ���������� ��� �Լ���
//		���� �κп� AFX_MANAGE_STATE ��ũ�ΰ�
//		��� �־�� �մϴ�.
//
//		��:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �Ϲ����� �Լ� ������ ���⿡ �ɴϴ�.
//		}
//
//		�� ��ũ�δ� MFC�� ȣ���ϱ� ����
//		�� �Լ��� �ݵ�� ��� �־�� �մϴ�.
//		��, ��ũ�δ� �Լ��� ù ��° ���̾�� �ϸ� 
//		��ü ������ �����ڰ� MFC DLL��
//		ȣ���� �� �����Ƿ� ��ü ������ ����Ǳ� ����
//		���;� �մϴ�.
//
//		�ڼ��� ������
//		MFC Technical Note 33 �� 58�� �����Ͻʽÿ�.
//

// CMyDevApp

BEGIN_MESSAGE_MAP(CMyDevApp, CWinApp)
END_MESSAGE_MAP()


// CMyDevApp ����

CMyDevApp::CMyDevApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CMyDevApp ��ü�Դϴ�.

CMyDevApp theApp;


// CMyDevApp �ʱ�ȭ

BOOL CMyDevApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

#define MYEXPORT	extern "C" __declspec(dllexport)

/////////////////////////////////////////////////////////////////////////
//0: �ʱ�ȭ ��(���� ����)
//1: �ʱ�ȭ �Ϸ�
//2: ������ � ���� ����
//3: ���� ���� ��
int g_nDevState = 0;


/////////////////////////////////////////////////////////////////////////
//�����ڵ�
//0: ����
//10: ��ġ�� �ʱ�ȭ ���� �ʾ���.
//20: ���� ����
//30: ���� ����
int g_nErrorCode = 10;

/////////////////////////////////////////////////////////////////////////
//1. ��ġ �ʱ�ȭ
MYEXPORT BOOL InitMyDev(int nLevel)
{
	::Sleep(10);
	if (rand() % 10 == 5)
	{
		g_nErrorCode = 10;		//�ʱ�ȭ ����
		return FALSE;
	}
	g_nErrorCode = 0;			//�������
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////
MYEXPORT int GetMyDevError(void)
{
	return g_nErrorCode;
}

MYEXPORT BOOL GetMyDevPosition(int *x, int *y)
{
	if (rand() % 50 == 5)		//2% Ȯ���� ����
	{
		::Sleep(100);
		g_nErrorCode = 20;

		return FALSE;
	}

	*x = rand() % 101;
	*y = rand() % 101;
	g_nErrorCode = 0;

	return TRUE;
}

MYEXPORT void ReleaseMyDev(void)
{
	g_nErrorCode = 10;
}
