
// ChildView.cpp : CChildView Ŭ������ ����
//

#include "stdafx.h"
#include "Race.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CChildView �޽��� ó����

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
	
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	
	// �׸��� �޽����� ���ؼ��� CWnd::OnPaint()�� ȣ������ ���ʽÿ�.
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// CChildView

int X;					// �����ڿ�
BOOL Wait = FALSE;		// ���� �÷���
CRITICAL_SECTION crit;	// �������� �����尡 �����ؾ� �ϹǷ�, ��������
HANDLE hMutex;			// ���ؽ� �ڵ�

/*
InitializeCriticalSection
 - CRITICAL_SECTION ����ü�� ���ڷ� �޾� �ʱ�ȭ ��Ŵ
CreateMutex
 - ���ؽ� ����
*/
CChildView::CChildView()
{
	//InitializeCriticalSection(&crit);
	hMutex = CreateMutex(NULL, FALSE, NULL);
}

/*
DeleteCriticalSection
 - ũ��Ƽ�� ���� ����
CloseHandle
 - ���ؽ� �ڵ� ����
*/
CChildView::~CChildView()
{
	// DeleteCriticalSection(&crit);
	CloseHandle(hMutex);
}

/*
EnterCriticalSection, LeaveCriticalSection
 - �Ӱ迵�� ���� �� �ش� ������ �����ڿ��� ��ȣ
WaitForSingleObject
 - �ϳ��� ��ü�� ��ȣ���°� �ɶ����� ��ٸ��� ��� �Լ�
ReleaseMutex
 - �ش� �������� ���ؽ��� �����Ͽ� �ٸ� �����尡 �̸� �������� ��
*/
DWORD WINAPI ThreadDog(LPVOID p)
{
	CChildView *pView = (CChildView*)p;
	CDC* pDC = pView->GetDC();

	for (int i = 0; i<100; i++)
	{
		// ������� - �������� ���
		//while(Wait == TRUE) {;}
		//Wait = TRUE;

		//EnterCriticalSection(&crit);

		WaitForSingleObject(hMutex, INFINITE);

		X = 100;
		Sleep(1);
		pDC->TextOut(X, 100, _T("������"));

		//Wait = FALSE;

		//LeaveCriticalSection(&crit);

		ReleaseMutex(hMutex);
	}
	pView->ReleaseDC(pDC);
	return 0;
}

DWORD WINAPI ThreadCat(LPVOID p)
{
	CChildView *pView = (CChildView*)p;
	CDC* pDC = pView->GetDC();

	for (int i = 0; i<100; i++)
	{
		//while(Wait == TRUE) {;}
		//Wait = TRUE;
		//EnterCriticalSection(&crit);
		WaitForSingleObject(hMutex, INFINITE);

		X = 200;
		Sleep(1);
		pDC->TextOut(X, 200, _T("�����"));

		//Wait = FALSE;
		//LeaveCriticalSection(&crit);
		ReleaseMutex(hMutex);
	}
	pView->ReleaseDC(pDC);
	return 0;
}

/*
OnLButtonDown - MESSAGE
 - ���� ��ư Ŭ�� �� ������ �ΰ��� ����
WaitForMultipleObjects
 - ��� �Լ��� �������� ����ȭ ��ü�� ��ٸ���.
 - �ڵ��� �迭�� �����ϸ� �� �����帶�� ������ ó���� �����ϴ�.
 - TRUE : ��� ��ü�� ����ȭ ��ȣ����
 - FALSE : ��ȣ ������ ����ȭ ��ü�� �ε��� 
*/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	DWORD ThreadID;
	HANDLE hAnimal[2];
	hAnimal[1] = CreateThread(NULL, 0, ThreadDog, this, 0, &ThreadID);
	hAnimal[0] = CreateThread(NULL, 0, ThreadCat, this, 0, &ThreadID);

	DWORD dw = WaitForMultipleObjects(2, hAnimal, FALSE, INFINITE);
	switch (dw)
	{
	case WAIT_OBJECT_0 + 1://dog
		AfxMessageBox(_T("Dog ���� �Ϸ�"));
		break;
	case WAIT_OBJECT_0 + 0://cat
		AfxMessageBox(_T("Cat ���� �Ϸ�"));
		break;
	}

	CloseHandle(hAnimal[0]);
	CloseHandle(hAnimal[1]);

	CWnd::OnLButtonDown(nFlags, point);
}