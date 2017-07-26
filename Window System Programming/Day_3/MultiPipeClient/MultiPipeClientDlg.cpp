
// MultiPipeClientDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MultiPipeClient.h"
#include "MultiPipeClientDlg.h"
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


// CMultiPipeClientDlg ��ȭ ����



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


// CMultiPipeClientDlg �޽��� ó����

BOOL CMultiPipeClientDlg::OnInitDialog()
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMultiPipeClientDlg::OnPaint()
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
HCURSOR CMultiPipeClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*
ConnectThread
 - ������ ��û�� ����, ����� �޾ƿ´�.
*/
DWORD WINAPI ConnectThread(LPVOID p)
{
	HANDLE hPipe;
	TCHAR szInput[255], szOutput[255];
	DWORD dwRead, dwWritten;
	BOOL bSuccess;

	TCHAR arNumber[5][10] = { _T("one"), _T("two"), _T("three"), _T("four"), _T("five") };

	//////////////////////////////////////////////////////
	// ������ �������� ������ ������ ���� ����Ѵ�.
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
		//one ~ five �� �ϳ��� ������ �����Ѵ�
		int s = rand() % 5;
		lstrcpy(szInput, arNumber[s]);

		// ����ڰ� �Է��� ���ڸ� �����Ѵ�
		// int nNumber = *(int*) p;
		// nNumber = nNumber - 1;//0_Based
		// lstrcpy( szInput, arNumber[ nNumber ]);


		//��û�� ���� ��, ������ �޴´�.
		bSuccess = WriteFile(hPipe, szInput, (lstrlen(szInput) + 1)*sizeof(TCHAR), &dwWritten, NULL);
		if ((bSuccess == FALSE) || (dwWritten == 0)) break;

		ReadFile(hPipe, szOutput, 255, &dwRead, NULL);

		//������ ȭ�鿡 ����Ѵ�.
		TCHAR Mes[255];
		wsprintf(Mes, _T("%s = %s"), szInput, szOutput);
		//AfxMessageBox(Mes);
		CWnd* pWnd = (CWnd*)p;
		pWnd->SetWindowText(Mes);

		Sleep(500);
	}

	// ������ ���� ����� ���,
	AfxMessageBox(_T("������ ����Ǿ����ϴ�."));
	CloseHandle(hPipe);
	return 0;
}

/*
Client Start
 - Result edit�� ���� �����忡 �Ѱܼ� ���� ( GetDlgItem )
*/
void CMultiPipeClientDlg::OnBnClickedClientBtn()
{
	UpdateData(1);			// ��Ʈ�� --> ����(m_nNumber)
	srand(GetTickCount());	// ���� �߻�

	DWORD ThreadID;
	CWnd* pWndResult = GetDlgItem(IDC_EDIT_RESULT);
	CloseHandle(CreateThread(NULL, 0, ConnectThread, pWndResult, 0, &ThreadID));
}
