
// MultiPipeClientDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MultiPipeClient.h"
#include "MultiPipeClientDlg.h"
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


// CMultiPipeClientDlg 대화 상자



CMultiPipeClientDlg::CMultiPipeClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MULTIPIPECLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMultiPipeClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMultiPipeClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CLIENT_BTN, &CMultiPipeClientDlg::OnBnClickedClientBtn)
END_MESSAGE_MAP()


// CMultiPipeClientDlg 메시지 처리기

BOOL CMultiPipeClientDlg::OnInitDialog()
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

void CMultiPipeClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMultiPipeClientDlg::OnPaint()
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
HCURSOR CMultiPipeClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*
ConnectThread
 - 서버로 요청을 보내, 결과를 받아온다.
*/
DWORD WINAPI ConnectThread(LPVOID p)
{
	HANDLE hPipe;
	TCHAR szInput[255], szOutput[255];
	DWORD dwRead, dwWritten;
	BOOL bSuccess;

	TCHAR arNumber[5][10] = { _T("one"), _T("two"), _T("three"), _T("four"), _T("five") };

	//////////////////////////////////////////////////////
	// 서버가 파이프를 생성할 때까지 무한 대기한다.
	for (;;)
	{
		if (WaitNamedPipe(_T("\\\\.\\pipe\\mymultipipe"),
			NMPWAIT_WAIT_FOREVER) == TRUE)
		{
			hPipe = CreateFile(_T("\\\\.\\pipe\\mymultipipe"),
				GENERIC_READ | GENERIC_WRITE,
				0, NULL,
				OPEN_EXISTING, 0, NULL);
			if (hPipe != INVALID_HANDLE_VALUE) break;
		}
	}
	//////////////////////////////////////////////////////
	for (;;)
	{
		//one ~ five 중 하나를 난수로 선택한다
		int s = rand() % 5;
		lstrcpy(szInput, arNumber[s]);

		// 사용자가 입력한 숫자를 선택한다
		// int nNumber = *(int*) p;
		// nNumber = nNumber - 1;//0_Based
		// lstrcpy( szInput, arNumber[ nNumber ]);


		//요청을 보낸 후, 응답을 받는다.
		bSuccess = WriteFile(hPipe, szInput, (lstrlen(szInput) + 1)*sizeof(TCHAR), &dwWritten, NULL);
		if ((bSuccess == FALSE) || (dwWritten == 0)) break;

		ReadFile(hPipe, szOutput, 255, &dwRead, NULL);

		//응답을 화면에 출력한다.
		TCHAR Mes[255];
		wsprintf(Mes, _T("%s = %s"), szInput, szOutput);
		//AfxMessageBox(Mes);
		CWnd* pWnd = (CWnd*)p;
		pWnd->SetWindowText(Mes);

		Sleep(500);
	}

	// 서버가 먼저 종료된 경우,
	AfxMessageBox(_T("서버가 종료되었습니다."));
	CloseHandle(hPipe);
	return 0;
}

/*
Client Start
 - Result edit의 값을 스레드에 넘겨서 실행 ( GetDlgItem )
*/
void CMultiPipeClientDlg::OnBnClickedClientBtn()
{
	UpdateData(1);			// 컨트롤 --> 변수(m_nNumber)
	srand(GetTickCount());	// 난수 발생

	DWORD ThreadID;
	CWnd* pWndResult = GetDlgItem(IDC_EDIT_RESULT);
	CloseHandle(CreateThread(NULL, 0, ConnectThread, pWndResult, 0, &ThreadID));
}
