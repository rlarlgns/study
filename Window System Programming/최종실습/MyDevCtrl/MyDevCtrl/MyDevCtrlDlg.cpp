
// MyDevCtrlDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MyDevCtrl.h"
#include "MyDevCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyDevCtrlDlg 대화 상자



CMyDevCtrlDlg::CMyDevCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYDEVCTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDevCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyDevCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BTN, &CMyDevCtrlDlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_END_BTN, &CMyDevCtrlDlg::OnBnClickedEndBtn)
	ON_BN_CLICKED(IDC_SUSPEND_BTN, &CMyDevCtrlDlg::OnBnClickedSuspendBtn)
END_MESSAGE_MAP()


// CMyDevCtrlDlg 메시지 처리기

BOOL CMyDevCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMyDevCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMyDevCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMyDevCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

#include "MyDev.h"
#pragma comment (lib, "MyDev.lib")

struct Node
{
	int x, y;
};

HANDLE g_hMonitor;
#define MAX_DATA 100

DWORD WINAPI ConnectThread(LPVOID p)
{
	Node *pWork = (Node*)p;

	OutputDebugString(_T("클라이언트가 서버에 접속 시도....."));

	// 서버가 응답할 때까지 무한 대기
	CString namePipe = _T("\\\\.\\pipe\\mydevdatapipe");
	HANDLE hPipe;
	for (;;)
	{
		// 서버와 파이프 연결
		if (WaitNamedPipe(namePipe, NMPWAIT_WAIT_FOREVER) == TRUE)
		{
			hPipe = CreateFile(namePipe, GENERIC_READ | GENERIC_WRITE, 0,
				NULL, OPEN_EXISTING, 0, NULL);
			if (hPipe != INVALID_HANDLE_VALUE) break;
		}
	}

	OutputDebugString(_T("클라이언트가 서버에 접속!!"));
	// 연결된 파이프를 통해 처리된 데이터 전송
	DWORD dwRead, dwWritten;
	BOOL bSuccess;
	CString strTmp;

	for (int i = 0; i < MAX_DATA; i++)
	{
		Sleep(100);//뭔가 처리하는 중...
		strTmp.Format(_T("Client[%d-%d] 보고: %d, %d\n"),
			::GetCurrentProcessId(), ::GetCurrentThreadId(),
			pWork[i].x, pWork[i].y);

		// 요청을 보내고 응답을 받음
		bSuccess = WriteFile(hPipe, strTmp, (lstrlen(strTmp) + 1)*sizeof(TCHAR), &dwWritten, NULL);
		if ((bSuccess == FALSE) || (dwWritten == 0)) break;
	}

	CloseHandle(hPipe);
	delete pWork;
	return 0;
}

DWORD WINAPI ProcessThread(LPVOID p)
{
	CString strTmp;
	Node *pWork = (Node*)p;

	for (int i = 0; i < MAX_DATA; i++)
	{
		Sleep(100); // 어떤 작업을 수행 중이라고 가정
		pWork[i].x *= 2;
		pWork[i].y *= 2;
		strTmp.Format(_T("ThreadProcessData: %d, %d\n"), pWork[i].x, pWork[i].y);
		OutputDebugString(strTmp);
	}
	
	CloseHandle(CreateThread(NULL, 0, ConnectThread, pWork, 0, 0));
	OutputDebugString(_T("ThreadProcessData 스레드 종료=========================\n"));

	return 0;
}

DWORD WINAPI GetDataThread(LPVOID p)
{
	CString strTmp;
	int x = 0;
	int y = 0;
	int nCount = 0;
	Node arData[402];

	for (;;) 
	{
		Sleep(100);
		if (::GetMyDevPosition(&x, &y) == TRUE)
		{
			// 데이터의 복사본을 생성해서 처리스레드로 넘김
			if (nCount == MAX_DATA) {
				
				Node* pCopy = (Node*)malloc(sizeof(Node)*MAX_DATA);
				memcpy(pCopy, arData, sizeof(Node)*MAX_DATA);

				CloseHandle(CreateThread(NULL, 0, ProcessThread, pCopy, 0, 0));

				nCount = 0;
			}
			else // 데이터 저장
			{
				arData[nCount].x = x;
				arData[nCount].y = y;
				nCount++;

				strTmp.Format(_T("(ThreadGetData : %d, %d)\n"), x, y);
				OutputDebugString(strTmp);
			}
		} 
		else
		{
			OutputDebugString(_T("센서오류\n"));
		}
	}
	OutputDebugString(_T("ThreadGetData 스레드 종료=========================\n"));
	return 0;
}

void CMyDevCtrlDlg::OnBnClickedStartBtn()
{
	if (::InitMyDev(5) == FALSE)
	{
		CString strTmp;
		strTmp.Format(_T("ERROR: 장치를 초기화 할 수 없습니다. [%d]"),
			::GetMyDevError());
		AfxMessageBox(strTmp);
		return;
	}

	g_hMonitor = ::CreateThread(NULL, 0, GetDataThread, 0, 0, 0);
}


void CMyDevCtrlDlg::OnBnClickedEndBtn()
{
	::ReleaseMyDev();
	::TerminateThread(g_hMonitor, 0);
}


void CMyDevCtrlDlg::OnBnClickedSuspendBtn()
{
	static BOOL bSuspend = TRUE;
	if (bSuspend)
	{
		::SuspendThread(g_hMonitor);

		bSuspend = FALSE;
		SetDlgItemText(IDC_SUSPEND_BTN, _T("Resume"));
	}
	else
	{
		::ResumeThread(g_hMonitor);

		bSuspend = TRUE;
		SetDlgItemText(IDC_SUSPEND_BTN, _T("Suspend"));
	}
}
