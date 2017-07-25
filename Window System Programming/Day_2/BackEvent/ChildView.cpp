
// ChildView.cpp : CChildView 클래스의 구현
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



// CChildView 메시지 처리기

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
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

HANDLE hEvent;
HANDLE hManualEvent;
/*
CreateEvent
 - 이벤트를 생성한다.
 - 두번째 인자 bManualReset 값에 따라 자동, 수동 이벤트로 결정된다.
*/
CChildView::CChildView()
{
	//자동이벤트
	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	//수동이벤트
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
- 이벤트의 상태를 신호 상태로 바꾼다.
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

	// 계산 스레드가 이벤트를 보내올 때까지 대기
	WaitForSingleObject(hEvent, INFINITE);
	CDC* pDC = GetDC();
	CString str;
	for (int i = 0; i <= 30; i++)
	{
		str.Format(_T("%d 라인은 %d입니다"), i, buf[i]);
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
		pDC->TextOut(500, 50, _T("계산중"));
		GdiFlush();
		Sleep(300);
		pDC->TextOut(500, 50, _T("기다려"));
		GdiFlush();
		Sleep(300);
	}
	MessageBeep(0);
	pDC->TextOut(500, 50, _T("계산완료"));
	pView->ReleaseDC(pDC);
	SetEvent(hManualEvent);
	return 0;
}

/*
ThreadPrint(), Save(), Send()
 - 스레드 시작 시 WaitForSingleObject 만나 대기한다.
 - Calc 스레드에서 SetEvent 함수가 호출되어 신호상태가 되면 수행한다.
WaitForSingleObject
 - 이벤트 핸들을 인자로 받아 값이 들어올때까지 대기한다.
*/
DWORD WINAPI ThreadPrint(LPVOID p)
{
	WaitForSingleObject(hManualEvent, INFINITE);
	CChildView* pView = (CChildView*)p;
	CDC* pDC = pView->GetDC();
	pDC->TextOut(500, 100, _T("인쇄완료"));
	pView->ReleaseDC(pDC);
	return 0;
}

DWORD WINAPI ThreadSave(LPVOID p)
{
	WaitForSingleObject(hManualEvent, INFINITE);
	CChildView* pView = (CChildView*)p;
	CDC* pDC = pView->GetDC();
	pDC->TextOut(500, 200, _T("저장완료"));
	pView->ReleaseDC(pDC);
	return 0;
}

DWORD WINAPI ThreadSend(LPVOID p)
{
	WaitForSingleObject(hManualEvent, INFINITE);
	CChildView* pView = (CChildView*)p;
	CDC* pDC = pView->GetDC();
	pDC->TextOut(500, 300, _T("전송완료"));
	pView->ReleaseDC(pDC);
	return 0;
}

/*
OnRButtonDown()
 - 오른쪽 버튼 클릭시 각기 다른 4개의 스레드를 생성한다.
ResetEvent
 - 이벤트를 비신호 상태로 만들어 초기화 시켰다.
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

