
// Day_4Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Day_4.h"
#include "Day_4Dlg.h"
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


// CDay_4Dlg 대화 상자



CDay_4Dlg::CDay_4Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DAY_4_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDay_4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDay_4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FILEREAD_BTN, &CDay_4Dlg::OnBnClickedFilereadBtn)
	ON_BN_CLICKED(IDC_FILEWRITE_BTN, &CDay_4Dlg::OnBnClickedFilewriteBtn)
	ON_BN_CLICKED(IDC_CONNECT_BTN, &CDay_4Dlg::OnBnClickedConnectBtn)
	ON_BN_CLICKED(IDC_DISCONNECT_BTN, &CDay_4Dlg::OnBnClickedDisconnectBtn)
	ON_EN_CHANGE(IDC_EDIT1, &CDay_4Dlg::OnEnChangeEdit1)
	ON_MESSAGE(WM_USER + 1, &CDay_4Dlg::OnUserMessage1)
	ON_BN_CLICKED(IDC_EVENT_BTN, &CDay_4Dlg::OnBnClickedEventBtn)
	ON_BN_CLICKED(IDC_CALLBACK_BTN, &CDay_4Dlg::OnBnClickedCallbackBtn)
	ON_BN_CLICKED(IDC_BIGFILE_BTN, &CDay_4Dlg::OnBnClickedBigfileBtn)
	ON_BN_CLICKED(IDC_MMF_BTN, &CDay_4Dlg::OnBnClickedMmfBtn)
END_MESSAGE_MAP()


// CDay_4Dlg 메시지 처리기

BOOL CDay_4Dlg::OnInitDialog()
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

void CDay_4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDay_4Dlg::OnPaint()
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
HCURSOR CDay_4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*
FILE READ
- 하드 디스크의 파일을 파일 매핑으로 읽어와 출력
CreateFile
- 읽어 들여올 파일을 선택하여 그 핸들 값을 가져온다.
*/
void CDay_4Dlg::OnBnClickedFilereadBtn()
{
	HANDLE hFile = CreateFile(_T("c:\\testfile.txt"),
		GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	// 1. 파일 매핑 오브젝트 (파일정보를 가짐) 를 만든다.
	HANDLE hFMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);

	// 2. 파일 매핑 오브젝트를, 프로세스의 가상메모리의 주소공간에 연결한다.(파일뷰)
	TCHAR* PtrUni = (TCHAR *)MapViewOfFile(hFMap, FILE_MAP_READ, 0, 0, 0);

	int nResult;
	// 3. 파일을 메모리 처럼 사용
	// 텍스트 파일의 앞 10글자가 유니코드일 경우
	if (IsTextUnicode(PtrUni, 10, &nResult))
	{
		//내용을 메시지박스로 출력한다.
		MessageBoxW(PtrUni, _T("Uni코드"), MB_OK);
		UnmapViewOfFile(PtrUni);
	}
	else
	{
		char* PtrAnsi = (char *)MapViewOfFile(hFMap, FILE_MAP_READ, 0, 0, 0);
		strcpy(PtrAnsi, ("ansi"));
		MessageBoxA(NULL, PtrAnsi, ("ANSI코드"), MB_OK);
		UnmapViewOfFile(PtrAnsi);
	}

	//4. 파일뷰를 닫는다.
	CloseHandle(hFMap);
	CloseHandle(hFile);
}

/*
FILE WRITE
- 파일을 불러와 매핑하고 포인터를 사용해 파일을 제어
*/
void CDay_4Dlg::OnBnClickedFilewriteBtn()
{
	HANDLE hFile;
	hFile = CreateFile(_T("c:\\testfile2.txt"), GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//1. 파일 매핑 오브젝트 (파일정보를 가짐) 를 만든다.
	HANDLE hFMap;
	hFMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, NULL);

	//2. 파일 매핑 오브젝트를, 프로세스의 가상메모리의 주소공간에 연결한다.(파일뷰)
	char* PtrInFile;
	PtrInFile = (char *)MapViewOfFile(hFMap, FILE_MAP_WRITE, 0, 0, 0);

	//3. 파일을 메모리처럼 사용한다.
	strcpy(PtrInFile, ("hello"));
	PtrInFile[0] = 'A';

	//4. 파일뷰를 닫는다.
	UnmapViewOfFile(PtrInFile);
	CloseHandle(hFMap);
	CloseHandle(hFile);
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
// MemShare

HANDLE hFMap;
TCHAR* PtrFile;
/*
Create, Connect Pipe
- "MyMemShareMapping" 이름을 가진 파일 매핑 오브젝트를 생성한다.
- 각기 다른 프로세스에서 동일한 가상 메모리를 가리키도록 함
*/
void CDay_4Dlg::OnBnClickedConnectBtn()
{
	//1. 파일 매핑 오브젝트 (파일정보를 가짐) 를 만든다.
	hFMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE,
		0, 1024, _T("MyMemShareMapping"));

	//2. 파일 매핑 오브젝트를, 프로세스의 가상메모리의 주소공간에 연결한다.(파일뷰)
	PtrFile = (TCHAR *)MapViewOfFile(hFMap, FILE_MAP_ALL_ACCESS, 0, 0, 1024);
}

/*
Disconnect
- 파일 매핑 오브젝트 해제
*/
void CDay_4Dlg::OnBnClickedDisconnectBtn()
{
	UnmapViewOfFile(PtrFile);
	CloseHandle(hFMap);
}

void CDay_4Dlg::OnEnChangeEdit1()
{
	GetDlgItemText(IDC_EDIT1, PtrFile, 1024);
	CWnd* pOtherWnd = FindWindow(NULL, _T("MemShare2"));
	if (pOtherWnd) pOtherWnd->PostMessage(WM_USER + 1, 0, 0);
}

afx_msg LRESULT CDay_4Dlg::OnUserMessage1(WPARAM w, LPARAM l)
{
	// 데이터를 화면에 출력
	SetDlgItemText(IDC_EDIT1, PtrFile);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
// MyAsyncIO

char strData[] =
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\r\n"
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\r\n"
"CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\r\n";

/*
Event btn
- 데이터를 텍스트 파일로 저장하는데 비동기 IO를 이용해서 동시에 IO를 처리
*/
void CDay_4Dlg::OnBnClickedEventBtn()
{
	HANDLE hFile;
	TCHAR filename[] = _T("c:\\ABC.txt");
	hFile = CreateFile(filename, GENERIC_WRITE, 0, 0,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);

	/*
	OVERLAPPED 구조체
	- 비동기 IO를 하기 위해 생성
	- hEvent는 핸들러로서 IO의 완료를 알리기 위해 이벤트를 담는다.
	*/
	OVERLAPPED ov = { 0, };
	ov.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);

	OVERLAPPED ov1 = { 0, };
	ov1.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);

	OVERLAPPED ov2 = { 0, };
	ov2.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);


	DWORD dwWritten = 0;
	DWORD Trans;

	/*
	WriteFile
	- offset을 이용해서 서로 다른 위치에 데이터를 씀
	*/
	ov.Offset = 0;
	ov.Offset = strlen(strData) * sizeof(char) * 0;
	WriteFile(hFile, strData, sizeof(strData), &dwWritten, &ov);
	GetOverlappedResult(hFile, &ov, &Trans, FALSE);
	{
		CString strTemp;
		strTemp.Format(_T("파일 Write 결과 완료 %u"), Trans);
		AfxMessageBox(strTemp);
	}

	ov1.Offset = strlen(strData) * sizeof(char) * 1;
	WriteFile(hFile, strData, sizeof(strData), &dwWritten, &ov1);
	GetOverlappedResult(hFile, &ov1, &Trans, FALSE);
	{
		CString strTemp;
		strTemp.Format(_T("파일 Write 결과 완료 %u"), Trans);
		AfxMessageBox(strTemp);
	}

	ov2.Offset = (strlen(strData) * sizeof(char)) * 2;
	WriteFile(hFile, strData, sizeof(strData), &dwWritten, &ov2);
	GetOverlappedResult(hFile, &ov2, &Trans, FALSE);
	{
		CString strTemp;
		strTemp.Format(_T("파일 Write 결과 완료 %u"), Trans);
		AfxMessageBox(strTemp);
	}
	CloseHandle(hFile);
}

VOID WINAPI MyCallBack(DWORD errCode, DWORD numOfByteTransfered,
	LPOVERLAPPED overlapped)
{
	CString strTemp = _T("MyIOCPRoutine");
	strTemp.Format(_T("파일 Write 결과 완료 \nerrCode : %u\nnumOfByteTransfered:%u\noverlapped->hEvent:%s"),
		errCode, numOfByteTransfered, (DWORD)overlapped->hEvent);
	AfxMessageBox(strTemp);
}

/*
WriteFileEx
- 비동기 전용 함수로 콜백함수를 등록하는 방식
- APC( Asynchronous Procedure Call ) 큐를 이용해서 완료 함수를 호출
*/
void CDay_4Dlg::OnBnClickedCallbackBtn()
{
	HANDLE hFile;
	TCHAR filename[] = _T("ABC2.txt");
	hFile = CreateFile(filename, GENERIC_WRITE, 0, 0,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);


	OVERLAPPED ov1 = { 0, };
	OVERLAPPED ov2 = { 0, };
	OVERLAPPED ov3 = { 0, };

	ov1.hEvent = (HANDLE)_T("AAA");
	WriteFileEx(hFile, strData, sizeof(strData), &ov1, MyCallBack);

	ov2.hEvent = (HANDLE)_T("BBB");
	ov2.Offset = (strlen(strData) * sizeof(char)) * 1;
	WriteFileEx(hFile, strData, sizeof(strData), &ov2, MyCallBack);

	ov3.hEvent = (HANDLE)_T("CCC");
	ov3.Offset = (strlen(strData) * sizeof(char)) * 2;
	WriteFileEx(hFile, strData, sizeof(strData), &ov3, MyCallBack);

	SleepEx(INFINITE, TRUE);
	CloseHandle(hFile);
}

#define MEGA 1048576
HANDLE hBigFile;
DWORD len;
char* buf;
char* p;
HANDLE hEvent;

/*
MakeDataThread
- 50MEGA의 데이터를 생성
*/
DWORD WINAPI MakeDataTread(LPVOID param)
{
	buf = (char*)calloc(50, MEGA);
	p = buf;
	char sTmp[256];
	int tlen;
	for (int i = 1;; i++)
	{
		sprintf(sTmp, ("%dLine : this file is a test\r\n"), i);
		tlen = strlen(sTmp);
		if (p - buf + tlen >= 50 * MEGA) break;
		strcpy(p, sTmp);
		p += tlen;
	}
	len = p - buf;

	AfxMessageBox(_T("자료만들기를 완료했습니다."));
	SetEvent(hEvent);
	return 0;
}

/*
WriteDataThread
- 이벤트를 받기까지 기다리다 작업 수행
*/
DWORD WINAPI WriteDataTread(LPVOID param)
{
	WaitForSingleObject(hEvent, INFINITE);

	OVERLAPPED ov;
	memset(&ov, 0, sizeof(ov));
	ov.Offset = 0;
	BOOL bWriteDone = WriteFile(hBigFile, buf, len, NULL, &ov);
	if ((bWriteDone == FALSE) && (GetLastError() == ERROR_IO_PENDING))
	{
		WaitForSingleObject(hBigFile, INFINITE);
		bWriteDone = TRUE;
	}
	if (bWriteDone)
	{
		CloseHandle(hBigFile);
		MessageBeep(0);
		AfxMessageBox(_T("파일 쓰기를 완료했습니다."));
	}
	return 0;
}

/*
Big file btn
- 큰 파일을 만드는 작업을 수행하는데 데이터를 만드는 스레드와
파일에 작성하는 스레드로 나누어 작업을 수행
- 이벤트를 생성해서 동기화 처리
*/
void CDay_4Dlg::OnBnClickedBigfileBtn()
{
	TCHAR filename[] = _T("bigdata.txt");
	hBigFile = CreateFile(filename, GENERIC_WRITE, 0, 0,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);

	hEvent = CreateEvent(NULL, TRUE, 0, NULL);

	DWORD id;
	CreateThread(0, 0, MakeDataTread, 0, 0, &id);
	CreateThread(0, 0, WriteDataTread, 0, 0, &id);
}

/*
MMF btn
- 빅데이터 파일을 읽어와 파일 매핑 오브젝트를 만들고 비동기로 파일을 복사
*/
void CDay_4Dlg::OnBnClickedMmfBtn()
{
	HANDLE hFileSource;
	hFileSource = CreateFile(_T("bigdata.txt"), GENERIC_READ,
		0,//FILE_SHARE_READ,//읽기모드 공유허용
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, 0);

	//0. 원본파일의 크기를 측정한다.
	LARGE_INTEGER	llFileSize = { 0 };
	//LARGE_INTEGER	llTotalReadSize = {0};

	if (!GetFileSizeEx(hFileSource, &llFileSize))
	{
		AfxMessageBox(_T("GetFileSizeEx 실패"));
		CloseHandle(hFileSource);
		return;
	}

	//1. 파일 매핑 오브젝트 (파일정보를 가짐) 를 만든다.
	HANDLE hFMap;
	hFMap = CreateFileMapping(hFileSource, NULL, PAGE_READONLY, 0,
		0,//llFileSize.LowPart, 
		NULL);
	if (hFMap == NULL)
	{
		AfxMessageBox(_T("CreateFileMapping 실패"));
		CloseHandle(hFileSource);
		return;
	}

	//2. 파일 매핑 오브젝트를, 프로세스의 가상메모리의 주소공간에 연결한다.(파일뷰)
	BYTE* pMemory;
	pMemory = (BYTE *)MapViewOfFile(hFMap, FILE_MAP_READ, 0, 0,
		0);//llFileSize.LowPart);
	if (pMemory == NULL)
	{
		AfxMessageBox(_T("MapViewOfFile 실패"));
		CloseHandle(hFileSource);
		return;
	}

	//3. 파일을 메모리처럼 사용한다.
	HANDLE hFileDest;
	hFileDest = CreateFile(_T("copycopy.txt"), GENERIC_WRITE, 0, 0,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);


	OVERLAPPED ov1 = { 0, };
	ov1.hEvent = (HANDLE)_T("빅 데이터 쓰기");
	WriteFileEx(hFileDest, pMemory, llFileSize.LowPart, &ov1, MyCallBack);

	if (GetLastError() == ERROR_IO_PENDING)
		MessageBeep(0);
	SleepEx(INFINITE, TRUE);
	CloseHandle(hFileDest);

	// 4. 파일뷰를 닫는다.
	UnmapViewOfFile(pMemory);
	CloseHandle(hFMap);
	CloseHandle(hFileSource);
}
