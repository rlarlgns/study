
// ChildView.cpp : CChildView Ŭ������ ����
//

#include "stdafx.h"
#include "BackEvent.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
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

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

HANDLE hEvent;
HANDLE hManualEvent;
/*
CreateEvent
 - �̺�Ʈ�� �����Ѵ�.
 - �ι�° ���� bManualReset ���� ���� �ڵ�, ���� �̺�Ʈ�� �����ȴ�.
*/
CChildView::CChildView()
{
	//�ڵ��̺�Ʈ
	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	//�����̺�Ʈ
	hManualEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
}

CChildView::~CChildView()
{
	CloseHandle(hEvent);
	CloseHandle(hManualEvent);
}

int buf[100];
/*
SetEvent
- �̺�Ʈ�� ���¸� ��ȣ ���·� �ٲ۴�.
*/
DWORD WINAPI ThreadFunc(LPVOID p)
{
	for (int i = 0; i<100; i++)
	{
		Sleep(30);
		buf[i] = i;
		if (i == 30) SetEvent(hEvent);
	}
	MessageBeep(0);
	return 0;
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	DWORD ThreadID;
	CloseHandle(CreateThread(NULL, 0, ThreadFunc, this, 0, &ThreadID));

	// ��� �����尡 �̺�Ʈ�� ������ ������ ���
	WaitForSingleObject(hEvent, INFINITE);
	CDC* pDC = GetDC();
	CString str;
	for (int i = 0; i <= 30; i++)
	{
		str.Format(_T("%d ������ %d�Դϴ�"), i, buf[i]);
		pDC->TextOut(10, i * 20, str);
	}
	ReleaseDC(pDC);
	CWnd::OnLButtonDown(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

DWORD WINAPI ThreadCalc(LPVOID p)
{
	CChildView* pView = (CChildView*)p;
	CDC* pDC = pView->GetDC();

	for (int i = 0; i<10; i++)
	{
		pDC->TextOut(500, 50, _T("�����"));
		GdiFlush();
		Sleep(300);
		pDC->TextOut(500, 50, _T("��ٷ�"));
		GdiFlush();
		Sleep(300);
	}
	MessageBeep(0);
	pDC->TextOut(500, 50, _T("���Ϸ�"));
	pView->ReleaseDC(pDC);
	SetEvent(hManualEvent);
	return 0;
}

/*
ThreadPrint(), Save(), Send()
 - ������ ���� �� WaitForSingleObject ���� ����Ѵ�.
 - Calc �����忡�� SetEvent �Լ��� ȣ��Ǿ� ��ȣ���°� �Ǹ� �����Ѵ�.
WaitForSingleObject
 - �̺�Ʈ �ڵ��� ���ڷ� �޾� ���� ���ö����� ����Ѵ�.
*/
DWORD WINAPI ThreadPrint(LPVOID p)
{
	WaitForSingleObject(hManualEvent, INFINITE);
	CChildView* pView = (CChildView*)p;
	CDC* pDC = pView->GetDC();
	pDC->TextOut(500, 100, _T("�μ�Ϸ�"));
	pView->ReleaseDC(pDC);
	return 0;
}

DWORD WINAPI ThreadSave(LPVOID p)
{
	WaitForSingleObject(hManualEvent, INFINITE);
	CChildView* pView = (CChildView*)p;
	CDC* pDC = pView->GetDC();
	pDC->TextOut(500, 200, _T("����Ϸ�"));
	pView->ReleaseDC(pDC);
	return 0;
}

DWORD WINAPI ThreadSend(LPVOID p)
{
	WaitForSingleObject(hManualEvent, INFINITE);
	CChildView* pView = (CChildView*)p;
	CDC* pDC = pView->GetDC();
	pDC->TextOut(500, 300, _T("���ۿϷ�"));
	pView->ReleaseDC(pDC);
	return 0;
}

/*
OnRButtonDown()
 - ������ ��ư Ŭ���� ���� �ٸ� 4���� �����带 �����Ѵ�.
ResetEvent
 - �̺�Ʈ�� ���ȣ ���·� ����� �ʱ�ȭ ���״�.
*/
void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	DWORD ThreadID;
	ResetEvent(hManualEvent);
	CloseHandle(CreateThread(NULL, 0, ThreadCalc, this, 0, &ThreadID));
	CloseHandle(CreateThread(NULL, 0, ThreadSave, this, 0, &ThreadID));
	CloseHandle(CreateThread(NULL, 0, ThreadSend, this, 0, &ThreadID));
	CloseHandle(CreateThread(NULL, 0, ThreadPrint, this, 0, &ThreadID));

	CWnd::OnRButtonDown(nFlags, point);
}

