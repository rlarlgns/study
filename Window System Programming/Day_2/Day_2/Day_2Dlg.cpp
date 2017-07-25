
// Day_2Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Day_2.h"
#include "Day_2Dlg.h"
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


// CDay_2Dlg 대화 상자



CDay_2Dlg::CDay_2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DAY_2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDay_2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDay_2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BTN, &CDay_2Dlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_FINISH_BTN, &CDay_2Dlg::OnBnClickedFinishBtn)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDay_2Dlg 메시지 처리기

BOOL CDay_2Dlg::OnInitDialog()
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

void CDay_2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDay_2Dlg::OnPaint()
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
HCURSOR CDay_2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

DWORD TlsIndex;
int nCount;			// Air에서 들어오는 값
int arData[100];	
int nIndex;			// 현재까지 받은 Air 데이터 개수
int nFileIndex = 0;		// 현재까지 만든 파일의 개수


/*
Start button click
 - OnTimer 함수 호출
*/
void CDay_2Dlg::OnBnClickedStartBtn()
{
	nIndex = 0;
	// SetTimer(1, 100, NULL);
	 SetTimer(1, 20, NULL); //GetAddNum() 호출시 간격을 줄임
}

/*
Finish button click
 - Timer 함수 Kill
*/
void CDay_2Dlg::OnBnClickedFinishBtn()
{
	KillTimer(1);
}

/*
GetAddNum
 - 데이터를 일정한 규칙으로 더함
*/
int GetAddNum()
{
	// static int m = 0;
	// 방법 2. TLS를 사용한다.
	// __declspec(thread) static int m = 0;
	int m = (int)TlsGetValue(TlsIndex);

	if (m == 5000) m = 0;
	m += 1000;

	TlsSetValue(TlsIndex, (LPVOID)(m));
	return m;
}

/*
CalcThread
 - 100개의 데이터를 받아서 가공 후 파일에 저장하는 스레드
*/
DWORD WINAPI CalcThread(LPVOID p)
{
	int *arWork = (int*)p;

	//arWork의 데이터를 가공
	for (int i = 0; i<100; i++)
	{
		arWork[i] = arWork[i] * 2;
		arWork[i] = arWork[i] + GetAddNum();
		Sleep(50);//정렬, 통계 등의 복잡한 작업을 가정함
	}

	//가공된 arWork를 파일이나 DB에 저장/ 또는 네트워크로 전송
	CString strFileName;
	strFileName.Format(_T("c:\\Result%d.txt"), ++nFileIndex);

	CString strTemp;
	// error!!
	CFile myFile(strFileName, CFile::modeCreate | CFile::modeReadWrite);
	for (int i = 0; i<100; i++)
	{
		strTemp.Format(_T("[%d] = %d\r\n"), i, arWork[i]);
		myFile.Write(strTemp, lstrlen(strTemp)*sizeof(TCHAR));
	}
	myFile.Close();

	free(arWork);//위치가 애매함 나중에 동기화로 풀어야 됨
	return 0;
}

/*
OnTimer
 - 복사본을 스레드로 넘겨서 동작
 - 스레드를 제어할 일이 없기 때문에 바로 CloseHandle
*/
void CDay_2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		arData[nIndex++] = ++nCount;
		if (nIndex == 100)
		{
			// 방법 1.
			// 작업 복사본을 만들어 충돌 회피
			int *arCopy = (int*)malloc(sizeof(arData));
			memcpy(arCopy, arData, sizeof(arData));

			DWORD ThreadID;
			
			// arCopy를 사용하여 충돌을 막음
			// CloseHandle(CreateThread(NULL, 0, CalcThread, arData, 0, &ThreadID));
			CloseHandle(CreateThread(NULL, 0, CalcThread, arCopy, 0, &ThreadID));

			SetDlgItemText(IDC_STATIC_MSG, _T("100개의 데이터 입력완료--> 스레드 호출"));
			Sleep(1000);//다음 데이터를 받아들이기 위한 약간의 준비를 가정함
			nIndex = 0;
			//Sleep(6000);//CalcThread의 충분한 계산시간이라고 판단함(애매함)
			//free(arCopy);//위치가 애매함
		}
		else
		{
			CString strTemp;
			strTemp.Format(_T("%d번째 데이터(%d)를 입력중"), nIndex, nCount);
			SetDlgItemText(IDC_STATIC_MSG, strTemp);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}

/*
OnCreate
 - 생성 시 TLS 할당
*/
int CDay_2Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	TlsIndex = TlsAlloc();

	return 0;
}

/*
OnDestroy
 - 뒷정리할때 TLS free
*/
void CDay_2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	TlsFree(TlsIndex);
}


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
