
// Day_1Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Day_1.h"
#include "Day_1Dlg.h"
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


// CDay_1Dlg 대화 상자



CDay_1Dlg::CDay_1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DAY_1_DIALOG, pParent)
	, m_dwPidKill(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDay_1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Text(pDX, IDC_EDIT2, m_dwPidKill);
}

BEGIN_MESSAGE_MAP(CDay_1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXEC_BTN, &CDay_1Dlg::OnBnClickedExecBtn)
	ON_BN_CLICKED(IDC_CREATEPROCESS_BTN, &CDay_1Dlg::OnBnClickedCreateprocessBtn)
	ON_BN_CLICKED(IDC_EXIT_BTN, &CDay_1Dlg::OnBnClickedExitBtn)
	ON_BN_CLICKED(IDC_TERMINATE_BTN, &CDay_1Dlg::OnBnClickedTerminateBtn)
	ON_BN_CLICKED(IDC_ENUMPROCESS_BTN, &CDay_1Dlg::OnBnClickedEnumprocessBtn)
	ON_BN_CLICKED(IDC_SNAPSHOT_BTN, &CDay_1Dlg::OnBnClickedSnapshotBtn)
	ON_BN_CLICKED(IDC_KILLPROCESS_BTN, &CDay_1Dlg::OnBnClickedKillprocessBtn)
	ON_BN_CLICKED(IDC_PROCESS_B, &CDay_1Dlg::OnBnClickedProcessB)
END_MESSAGE_MAP()


// CDay_1Dlg 메시지 처리기

BOOL CDay_1Dlg::OnInitDialog()
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

void CDay_1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDay_1Dlg::OnPaint()
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
HCURSOR CDay_1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*
WinExec
 - 16bit 함수, 옵션 부족
 - 유니코드 미지원
 - 내부적으로 CreateProcess(), WaitForInputIdle(), return 호출
*/
void CDay_1Dlg::OnBnClickedExecBtn()
{
	::WinExec("Notepad.exe", SW_SHOWNORMAL);

	CWnd* pWnd = FindWindow(_T("Notepad"), NULL);
	if (pWnd == NULL)
		AfxMessageBox(_T("메모장을 찾을 수 없습니다."));
	else
		AfxMessageBox(_T("메모장을 찾았습니다."));
}

/*
CreateProcess
 - 프로세스 생성 후 리턴
 - 생성된 프로세스와 통신하기 위해 WaitForInputIdle()로 초기화
*/
void CDay_1Dlg::OnBnClickedCreateprocessBtn()
{
	TCHAR strPath[20] = _T("Notepad.exe");
	STARTUPINFO si = { sizeof(STARTUPINFO), };
	PROCESS_INFORMATION pi;

	::CreateProcess(NULL, strPath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

	WaitForInputIdle(pi.hProcess, INFINITE);

	CWnd* pWnd = FindWindow(_T("Notepad"), NULL);
	if (pWnd == NULL)
		AfxMessageBox(_T("메모장을 찾을 수 없습니다."));
	else
		AfxMessageBox(_T("메모장을 찾았습니다."));
}

/*
ExitProcess
 - 프로세스 종료 처리를 다른 프로세스에게 통보
 - DLL, 스레드, 핸들 종료
*/
void CDay_1Dlg::OnBnClickedExitBtn()
{
	ExitProcess(0);
}

/*
TerminateProcess
 - 다른 프로세스 강제 종료, 비정상적인 종료 방법
*/
void CDay_1Dlg::OnBnClickedTerminateBtn()
{
	TCHAR strPath[20] = _T("Notepad.exe");
	STARTUPINFO si = { sizeof(STARTUPINFO), };
	PROCESS_INFORMATION pi;

	::CreateProcess(NULL, strPath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

	WaitForInputIdle(pi.hProcess, INFINITE);

	Sleep(1000);

	TerminateProcess(pi.hProcess, 0);

	AfxMessageBox(_T("노트패드 프로그램 종료"));
}

void CDay_1Dlg::OnBnClickedEnumprocessBtn() {}
/*
EnumProcess() 
 - 현재 실행중인 프로세스들의 ID를 배열로 로드
 - 프로세스를 통한 접근이므로 접근이 거부되는 경우가 있음
ZeroMemory
 - 메모리 영역을 0x00으로 채우는 매크로
 */
#include <Psapi.h>
#pragma comment(lib, "Psasi")
void CDay_1Dlg::OnBnClickedEnumprocessBtn()
{
	DWORD pidArray[512] = { 0, };
	DWORD cbNeeded;
	DWORD nProcesses;
	TCHAR szBuffer[MAX_PATH + _MAX_FNAME];
	UINT nCounter = 0;
	CString strTemp = _T("");

	if (m_List.GetCount() > 0) m_List.ResetContent();

	// Process 정보를 배열에 삽입
	if (::EnumProcesses(pidArray, sizeof(pidArray), &cbNeeded))
	{
		nProcesses = cbNeeded / sizeof(DWORD);
		for (DWORD i = 0; i <= nProcesses; i++)
		{
			HANDLE hProcess;
			DWORD pid = pidArray[i];

			// pid를 통해 핸들 획득
			hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

			if (hProcess != NULL)
			{
				// 초기화 후 핸들을 통해서 파일 이름 획득
				::ZeroMemory(szBuffer, MAX_PATH + _MAX_FNAME);
				if (::GetModuleFileNameEx(hProcess, NULL, szBuffer, MAX_PATH + _MAX_FNAME) != NULL)
				{
					strTemp.Format(_T("[PID:%d] %s"), pid, szBuffer);
					m_List.AddString(strTemp);
				}
				::CloseHandle(hProcess);
			}
			else
			{
				strTemp.Format(_T("[PID:%d, Error code : %d]"), pid, ::GetLastError());
				m_List.AddString(strTemp);
				continue;
			}
		}
	}
}


/*
CreateToolhelp32Snapshot
 - 운영체제에게 위탁해 정보를 취득하는 방식
 - 시스템 프로세스들에 대한 정보도 일부 확인 가능
*/
#include <TlHelp32.h>
void CDay_1Dlg::OnBnClickedSnapshotBtn()
{
	HANDLE hSnapshot = INVALID_HANDLE_VALUE;
	CString strTemp;

	hSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 pe32 = { sizeof(pe32), };

	if (m_List.GetCount() > 0) m_List.ResetContent();

	BOOL bFlag = ::Process32First(hSnapshot, &pe32);
	for (; bFlag; bFlag = ::Process32Next(hSnapshot, &pe32))
	{
		strTemp.Format(_T("[PID:%d] %s"), pe32.th32ProcessID, pe32.szExeFile);
		m_List.AddString(strTemp);
	}

	if (hSnapshot != INVALID_HANDLE_VALUE)
		::CloseHandle(hSnapshot);
}

/*
Process Kill
 - OpenProcess를 통해서 해당 PID를 가진 프로세스의 핸들을 획득
 - 핸들을 통해 프로세스 종료 및 핸들 닫기
*/
void CDay_1Dlg::OnBnClickedKillprocessBtn()
{
	UpdateData(1);//컨트롤 --> 변수

	HANDLE hProcess = ::OpenProcess( PROCESS_TERMINATE, FALSE, m_dwPidKill);

	if (hProcess != NULL)
	{
		::TerminateProcess(hProcess, (unsigned)-1);
		::CloseHandle(hProcess);
	}
}

/*
FindWindow
 - 인자에 해당하는 이름의 프로세스를 찾는다.
SendMessage
 - FindWindow로 찾은 윈도우에 메세지를 보낸다.
CreateProcess
 - STARTUPINFO, PROCESS_INFORMATION 구조체를 인자로 받아 프로세스를 생성
*/
void CDay_1Dlg::OnBnClickedProcessB()
{
	CWnd* pProcB = FindWindow(NULL, _T("ProcB"));
	if (pProcB == NULL)
	{
		AfxMessageBox(_T("ProcB 먼저 실행하세요"));
		return;
	}

	TCHAR strPath[20] = _T("Notepad.exe");
	STARTUPINFO si = { sizeof(STARTUPINFO), };
	PROCESS_INFORMATION pi;
	::CreateProcess(NULL, strPath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	/////////////////////////////
	CString strTemp;
	strTemp.Format(_T("프로세스 핸들 %u와 ID %d 생성"), pi.hProcess, pi.dwProcessId);
	AfxMessageBox(strTemp);

	pProcB->SendMessage(WM_USER + 1, (WPARAM)pi.dwProcessId, 0);
}
