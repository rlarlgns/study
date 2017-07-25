
// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "SemDown.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView


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

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

HANDLE hSema;	// 세마포어 핸들
int Y = 0;

/*
CreateSemaphore
 - 3개의 자원 개수를 가진 세마포어를 생성함
*/
CChildView::CChildView()
{
	hSema = CreateSemaphore(NULL, 3, 3, NULL);
}

/*
CloseHandle
 - 세마포어 핸들 닫음
*/
CChildView::~CChildView()
{
	CloseHandle(hSema);
}

/*
ThreadDownload()
 - 파일을 다운로드 하는 상황을 가정한 함수이다.
 - 세마포어를 사용하여 동시에 최대 3개까지 스레드가 동작하고 나머지는 기다린다.
WaitForSingleObject
 - 세마포어의 핸들을 인자로 받아 기다린다.
ReleaseSemaphore
 - 세마포어의 카운트를 증가시키고 종료한다.
*/
DWORD WINAPI ThreadDownload(LPVOID p)
{
	CChildView* pView = (CChildView*)p;
	CDC* pDC = pView->GetDC();

	srand(GetTickCount());
	int s = rand() % 5 + 1;		// 다운로드 속도를 실제처럼 보이려고 난수사용

	Y += 20;
	int y = Y;
	pDC->TextOut(10, y, _T("대기중"));
	GdiFlush();
	
	WaitForSingleObject(hSema, INFINITE);

	CString strTemp;
	for (int i = 0; i<100; i++)
	{
		strTemp.Format(_T("다운로드중 : %d%% 완료"), i);
		for (int j = 0; j<i; j++)
			strTemp += _T("|");
		pDC->TextOut(10, y, strTemp);
		Sleep(s * 20);//시간지연
	}

	ReleaseSemaphore(hSema, 1, NULL);

	pDC->TextOut(10, y, _T("다운로드를 완료했습니다"));
	pView->ReleaseDC(pDC);
	return 0;
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	DWORD ThreadID;
	CloseHandle(CreateThread(NULL, 0, ThreadDownload, this, 0, &ThreadID));

	CWnd::OnLButtonDown(nFlags, point);
}
