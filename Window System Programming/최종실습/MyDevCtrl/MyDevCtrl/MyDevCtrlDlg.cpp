
// MyDevCtrlDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MyDevCtrl.h"
#include "MyDevCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CMyDevCtrlDlg ��ȭ ����



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


// CMyDevCtrlDlg �޽��� ó����

BOOL CMyDevCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMyDevCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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

	OutputDebugString(_T("Ŭ���̾�Ʈ�� ������ ���� �õ�....."));

	// ������ ������ ������ ���� ���
	CString namePipe = _T("\\\\.\\pipe\\mydevdatapipe");
	HANDLE hPipe;
	for (;;)
	{
		// ������ ������ ����
		if (WaitNamedPipe(namePipe, NMPWAIT_WAIT_FOREVER) == TRUE)
		{
			hPipe = CreateFile(namePipe, GENERIC_READ | GENERIC_WRITE, 0,
				NULL, OPEN_EXISTING, 0, NULL);
			if (hPipe != INVALID_HANDLE_VALUE) break;
		}
	}

	OutputDebugString(_T("Ŭ���̾�Ʈ�� ������ ����!!"));
	// ����� �������� ���� ó���� ������ ����
	DWORD dwRead, dwWritten;
	BOOL bSuccess;
	CString strTmp;

	for (int i = 0; i < MAX_DATA; i++)
	{
		Sleep(100);//���� ó���ϴ� ��...
		strTmp.Format(_T("Client[%d-%d] ����: %d, %d\n"),
			::GetCurrentProcessId(), ::GetCurrentThreadId(),
			pWork[i].x, pWork[i].y);

		// ��û�� ������ ������ ����
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
		Sleep(100); // � �۾��� ���� ���̶�� ����
		pWork[i].x *= 2;
		pWork[i].y *= 2;
		strTmp.Format(_T("ThreadProcessData: %d, %d\n"), pWork[i].x, pWork[i].y);
		OutputDebugString(strTmp);
	}
	
	CloseHandle(CreateThread(NULL, 0, ConnectThread, pWork, 0, 0));
	OutputDebugString(_T("ThreadProcessData ������ ����=========================\n"));

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
			// �������� ���纻�� �����ؼ� ó��������� �ѱ�
			if (nCount == MAX_DATA) {
				
				Node* pCopy = (Node*)malloc(sizeof(Node)*MAX_DATA);
				memcpy(pCopy, arData, sizeof(Node)*MAX_DATA);

				CloseHandle(CreateThread(NULL, 0, ProcessThread, pCopy, 0, 0));

				nCount = 0;
			}
			else // ������ ����
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
			OutputDebugString(_T("��������\n"));
		}
	}
	OutputDebugString(_T("ThreadGetData ������ ����=========================\n"));
	return 0;
}

void CMyDevCtrlDlg::OnBnClickedStartBtn()
{
	if (::InitMyDev(5) == FALSE)
	{
		CString strTmp;
		strTmp.Format(_T("ERROR: ��ġ�� �ʱ�ȭ �� �� �����ϴ�. [%d]"),
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
