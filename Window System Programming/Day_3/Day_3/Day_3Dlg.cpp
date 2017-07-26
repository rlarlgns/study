
// Day_3Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Day_3.h"
#include "Day_3Dlg.h"
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


// CDay_3Dlg ��ȭ ����



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


// CDay_3Dlg �޽��� ó����

BOOL CDay_3Dlg::OnInitDialog()
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CDay_3Dlg::OnPaint()
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
HCURSOR CDay_3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*
NamedPipeServer BTN
 - ��ư Ŭ�� �� ���ӵ� �������� �����ϰ� Ŭ���̾�Ʈ�� ������ ���
CreateNamedPipe
 - ���ڿ� �̸��� ���� �������� �����Ѵ�.
 - �̸�, �б� ���� ���, ����, �ν��Ͻ� ����, ����� ���� ũ��, ����� �ð�, ���ȼӼ� ���ڷ� ����
ConnectNamedPipe
 - ������ �ڵ��� ���ڷ� ������ �������� �����Ҷ� ���� ����Ѵ�.
FlushFileBuffers, DisconnectNamedPipe, CloseHandle
 - ���۸� ����, ���� ���� ��, �������� ���� �Ѵ�.
*/
void CDay_3Dlg::OnBnClickedStartBtn()
{
	HANDLE hPipe;
	BOOL bConnect;

	//CString strLongMessage = _T("AAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCCC");
	TCHAR *strLongMessage = _T("AAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCCC");

	////////////////////////////////////////////////////////////////////////////////////
	// 1. ������ ����
	SetDlgItemText(IDC_EDIT1, _T("�̸��� �ִ� �������� �����մϴ�."));

	hPipe = CreateNamedPipe(_T("\\\\.\\pipe\\mypipe"),
		PIPE_ACCESS_OUTBOUND,
		PIPE_TYPE_BYTE,
		PIPE_UNLIMITED_INSTANCES, //255
		4096,
		0, 0, NULL);

	////////////////////////////////////////////////////////////////////////////////////
	//2. ���� ���
	SetDlgItemText(IDC_EDIT1, _T("������ ����, Client ���� ��� ��"));

	bConnect = ConnectNamedPipe(hPipe, NULL);
	if ((bConnect == FALSE) && (GetLastError() == ERROR_PIPE_CONNECTED))
		bConnect = TRUE;

	if (bConnect == TRUE)
	{
		SetDlgItemText(IDC_EDIT1, _T("Client ���Ӽ���, Client�� ���ڿ� ����"));

		DWORD dwWritten;
		WriteFile(hPipe,
			strLongMessage,
			(lstrlen(strLongMessage) + 1)*sizeof(TCHAR),
			//strLongMessage.GetLength()*sizeof(TCHAR), 
			&dwWritten, NULL);

		//������ ����
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
 - Ŭ���̾�Ʈ�� ��û�� ó���Ѵ�
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
		// �������� ���� ���� �б�
		bSuccess = ReadFile(hPipe, szInput, 255, &dwRead, NULL);
		if ((bSuccess == FALSE) || (dwRead == 0)) break;

		/////////////////////////////////////////////
		// �������� ������ ���� �����
		if (lstrcmp(szInput, _T("one")) == 0)
			lstrcpy(szOutput, _T("�ϳ�"));
		else if (lstrcmp(szInput, _T("two")) == 0)
			lstrcpy(szOutput, _T("��"));
		else if (lstrcmp(szInput, _T("three")) == 0)
			lstrcpy(szOutput, _T("��"));
		else if (lstrcmp(szInput, _T("four")) == 0)
			lstrcpy(szOutput, _T("��"));
		else if (lstrcmp(szInput, _T("five")) == 0)
			lstrcpy(szOutput, _T("�ټ�"));
		else
			lstrcpy(szOutput, _T("�ؼ��Ұ�"));

		////////////////////////////////////////////
		// �������� ���� ����
		bSuccess = WriteFile(hPipe, szOutput, 
			(lstrlen(szOutput) + 1)*sizeof(TCHAR), &dwWritten, NULL);
		if ((bSuccess == FALSE) || (dwWritten == 0)) break;
	}

	/////////////////////////////////////
	// ������ ����
	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);

	return 0;
}

/*
ListenThread
 - Ŭ���̾�Ʈ�� ������ ����Ͽ�, Ŭ���̾�Ʈ �ϳ��� �ϳ����� �����带 ����
*/
DWORD WINAPI ListenThread(LPVOID p)
{
	for (;;)
	{
		/////////////////////////////////////////////////////////
		// 1. ������ ����
		HANDLE hPipe;
		hPipe = CreateNamedPipe(_T("\\\\.\\pipe\\mymultipipe"),
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_BYTE,
			3,
			4096,
			0, 1, NULL);

		////////////////////////////////////////////////////////////////////////////
		// 2. ���� ���
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
 - Ŭ���̾�Ʈ�� �Է¹��� Listen Thread�� ���� �����Ͽ� ��������� ������ �ʰ� ��
*/
void CDay_3Dlg::OnBnClickedMultipipeStartBtn()
{
	DWORD ThreadID;
	CloseHandle(CreateThread(NULL, 0, ListenThread, NULL, 0, &ThreadID));
}
