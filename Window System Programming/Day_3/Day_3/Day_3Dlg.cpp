
// Day_3Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Day_3.h"
#include "Day_3Dlg.h"
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


// CDay_3Dlg 대화 상자



CDay_3Dlg::CDay_3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DAY_3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDay_3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDay_3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BTN, &CDay_3Dlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_MULTIPIPE_START_BTN, &CDay_3Dlg::OnBnClickedMultipipeStartBtn)
END_MESSAGE_MAP()


// CDay_3Dlg 메시지 처리기

BOOL CDay_3Dlg::OnInitDialog()
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

void CDay_3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDay_3Dlg::OnPaint()
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
HCURSOR CDay_3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*
NamedPipeServer BTN
 - 버튼 클릭 시 네임드 파이프를 생성하고 클라이언트의 접속을 대기
CreateNamedPipe
 - 문자열 이름을 가진 파이프를 생성한다.
 - 이름, 읽기 쓰기 모드, 유형, 인스턴스 개수, 입출력 버퍼 크기, 대기할 시간, 보안속성 인자로 가짐
ConnectNamedPipe
 - 파이프 핸들을 인자로 받으며 파이프가 접속할때 까지 대기한다.
FlushFileBuffers, DisconnectNamedPipe, CloseHandle
 - 버퍼를 비우고, 접속 종료 후, 파이프를 제거 한다.
*/
void CDay_3Dlg::OnBnClickedStartBtn()
{
	HANDLE hPipe;
	BOOL bConnect;

	//CString strLongMessage = _T("AAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCCC");
	TCHAR *strLongMessage = _T("AAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCCC");

	////////////////////////////////////////////////////////////////////////////////////
	// 1. 파이프 생성
	SetDlgItemText(IDC_EDIT1, _T("이름이 있는 파이프를 생성합니다."));

	hPipe = CreateNamedPipe(_T("\\\\.\\pipe\\mypipe"),
		PIPE_ACCESS_OUTBOUND,
		PIPE_TYPE_BYTE,
		PIPE_UNLIMITED_INSTANCES, //255
		4096,
		0, 0, NULL);

	////////////////////////////////////////////////////////////////////////////////////
	//2. 접속 대기
	SetDlgItemText(IDC_EDIT1, _T("파이프 생성, Client 접속 대기 중"));

	bConnect = ConnectNamedPipe(hPipe, NULL);
	if ((bConnect == FALSE) && (GetLastError() == ERROR_PIPE_CONNECTED))
		bConnect = TRUE;

	if (bConnect == TRUE)
	{
		SetDlgItemText(IDC_EDIT1, _T("Client 접속성공, Client로 문자열 전송"));

		DWORD dwWritten;
		WriteFile(hPipe,
			strLongMessage,
			(lstrlen(strLongMessage) + 1)*sizeof(TCHAR),
			//strLongMessage.GetLength()*sizeof(TCHAR), 
			&dwWritten, NULL);

		//파이프 해제
		FlushFileBuffers(hPipe);
		DisconnectNamedPipe(hPipe);
	}
	CloseHandle(hPipe);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// MultiPipe Server

/* 
ClientThread
 - 클라이언트의 요청을 처리한다
*/
DWORD WINAPI ClientThread(LPVOID p)
{
	HANDLE hPipe = (HANDLE)p;
	TCHAR szInput[255], szOutput[255];
	DWORD dwRead, dwWritten;
	BOOL bSuccess;

	for (;;)
	{
		/////////////////////////////////////////////
		// 파이프로 부터 문자 읽기
		bSuccess = ReadFile(hPipe, szInput, 255, &dwRead, NULL);
		if ((bSuccess == FALSE) || (dwRead == 0)) break;

		/////////////////////////////////////////////
		// 파이프로 내보낼 문자 만들기
		if (lstrcmp(szInput, _T("one")) == 0)
			lstrcpy(szOutput, _T("하나"));
		else if (lstrcmp(szInput, _T("two")) == 0)
			lstrcpy(szOutput, _T("둘"));
		else if (lstrcmp(szInput, _T("three")) == 0)
			lstrcpy(szOutput, _T("셋"));
		else if (lstrcmp(szInput, _T("four")) == 0)
			lstrcpy(szOutput, _T("넷"));
		else if (lstrcmp(szInput, _T("five")) == 0)
			lstrcpy(szOutput, _T("다섯"));
		else
			lstrcpy(szOutput, _T("해석불가"));

		////////////////////////////////////////////
		// 파이프에 문자 쓰기
		bSuccess = WriteFile(hPipe, szOutput, 
			(lstrlen(szOutput) + 1)*sizeof(TCHAR), &dwWritten, NULL);
		if ((bSuccess == FALSE) || (dwWritten == 0)) break;
	}

	/////////////////////////////////////
	// 파이프 해제
	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);

	return 0;
}

/*
ListenThread
 - 클라이언트의 접속을 대기하여, 클라이언트 하나당 하나씩의 스레드를 만듬
*/
DWORD WINAPI ListenThread(LPVOID p)
{
	for (;;)
	{
		/////////////////////////////////////////////////////////
		// 1. 파이프 생성
		HANDLE hPipe;
		hPipe = CreateNamedPipe(_T("\\\\.\\pipe\\mymultipipe"),
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_BYTE,
			3,
			4096,
			0, 1, NULL);

		////////////////////////////////////////////////////////////////////////////
		// 2. 접속 대기
		BOOL bConnect;
		bConnect = ConnectNamedPipe(hPipe, NULL);
		if ((bConnect == FALSE) && (GetLastError() == ERROR_PIPE_CONNECTED))
			bConnect = TRUE;
		if (bConnect == TRUE)
		{
			DWORD ThreadID;
			CloseHandle(CreateThread(NULL, 0, ClientThread, (LPVOID)hPipe, 0, &ThreadID));
		}
		else
			CloseHandle(hPipe);
	}
	return 0;
}

/*
server start btn
 - 클라이언트를 입력받을 Listen Thread를 따로 생성하여 응답없음에 빠지지 않게 함
*/
void CDay_3Dlg::OnBnClickedMultipipeStartBtn()
{
	DWORD ThreadID;
	CloseHandle(CreateThread(NULL, 0, ListenThread, NULL, 0, &ThreadID));
}
