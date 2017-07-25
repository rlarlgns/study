
// ChildView.cpp : CChildView Ŭ������ ����
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

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

HANDLE hSema;	// �������� �ڵ�
int Y = 0;

/*
CreateSemaphore
 - 3���� �ڿ� ������ ���� ������� ������
*/
CChildView::CChildView()
{
	hSema = CreateSemaphore(NULL, 3, 3, NULL);
}

/*
CloseHandle
 - �������� �ڵ� ����
*/
CChildView::~CChildView()
{
	CloseHandle(hSema);
}

/*
ThreadDownload()
 - ������ �ٿ�ε� �ϴ� ��Ȳ�� ������ �Լ��̴�.
 - ������� ����Ͽ� ���ÿ� �ִ� 3������ �����尡 �����ϰ� �������� ��ٸ���.
WaitForSingleObject
 - ���������� �ڵ��� ���ڷ� �޾� ��ٸ���.
ReleaseSemaphore
 - ���������� ī��Ʈ�� ������Ű�� �����Ѵ�.
*/
DWORD WINAPI ThreadDownload(LPVOID p)
{
	CChildView* pView = (CChildView*)p;
	CDC* pDC = pView->GetDC();

	srand(GetTickCount());
	int s = rand() % 5 + 1;		// �ٿ�ε� �ӵ��� ����ó�� ���̷��� �������

	Y += 20;
	int y = Y;
	pDC->TextOut(10, y, _T("�����"));
	GdiFlush();
	
	WaitForSingleObject(hSema, INFINITE);

	CString strTemp;
	for (int i = 0; i<100; i++)
	{
		strTemp.Format(_T("�ٿ�ε��� : %d%% �Ϸ�"), i);
		for (int j = 0; j<i; j++)
			strTemp += _T("|");
		pDC->TextOut(10, y, strTemp);
		Sleep(s * 20);//�ð�����
	}

	ReleaseSemaphore(hSema, 1, NULL);

	pDC->TextOut(10, y, _T("�ٿ�ε带 �Ϸ��߽��ϴ�"));
	pView->ReleaseDC(pDC);
	return 0;
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	DWORD ThreadID;
	CloseHandle(CreateThread(NULL, 0, ThreadDownload, this, 0, &ThreadID));

	CWnd::OnLButtonDown(nFlags, point);
}
