
// ChildView.cpp : CChildView 클래스의 구현
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

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// CChildView

int X;					// 경쟁자원
BOOL Wait = FALSE;		// 폴링 플래그
CRITICAL_SECTION crit;	// 복수개의 스레드가 참조해야 하므로, 전역선언
HANDLE hMutex;			// 뮤텍스 핸들

/*
InitializeCriticalSection
 - CRITICAL_SECTION 구조체를 인자로 받아 초기화 시킴
CreateMutex
 - 뮤텍스 생성
*/
CChildView::CChildView()
{
	//InitializeCriticalSection(&crit);
	hMutex = CreateMutex(NULL, FALSE, NULL);
}

/*
DeleteCriticalSection
 - 크리티컬 섹션 정리
CloseHandle
 - 뮤텍스 핸들 정리
*/
CChildView::~CChildView()
{
	// DeleteCriticalSection(&crit);
	CloseHandle(hMutex);
}

/*
EnterCriticalSection, LeaveCriticalSection
 - 임계영역 생성 후 해당 구간의 공유자원을 보호
WaitForSingleObject
 - 하나의 객체가 신호상태가 될때까지 기다리는 대기 함수
ReleaseMutex
 - 해당 스레드의 뮤텍스를 해제하여 다른 스레드가 이를 가지도록 함
*/
DWORD WINAPI ThreadDog(LPVOID p)
{
	CChildView *pView = (CChildView*)p;
	CDC* pDC = pView->GetDC();

	for (int i = 0; i<100; i++)
	{
		// 폴링방식 - 고전적인 방법
		//while(Wait == TRUE) {;}
		//Wait = TRUE;

		//EnterCriticalSection(&crit);

		WaitForSingleObject(hMutex, INFINITE);

		X = 100;
		Sleep(1);
		pDC->TextOut(X, 100, _T("강아지"));

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
		pDC->TextOut(X, 200, _T("고양이"));

		//Wait = FALSE;
		//LeaveCriticalSection(&crit);
		ReleaseMutex(hMutex);
	}
	pView->ReleaseDC(pDC);
	return 0;
}

/*
OnLButtonDown - MESSAGE
 - 왼쪽 버튼 클릭 시 스레드 두개를 생성
WaitForMultipleObjects
 - 대기 함수로 복수개의 동기화 객체를 기다린다.
 - 핸들을 배열로 관리하며 각 스레드마다 별도의 처리가 가능하다.
 - TRUE : 모든 객체가 동기화 신호상태
 - FALSE : 신호 상태인 동기화 객체의 인덱스 
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
		AfxMessageBox(_T("Dog 수행 완료"));
		break;
	case WAIT_OBJECT_0 + 0://cat
		AfxMessageBox(_T("Cat 수행 완료"));
		break;
	}

	CloseHandle(hAnimal[0]);
	CloseHandle(hAnimal[1]);

	CWnd::OnLButtonDown(nFlags, point);
}