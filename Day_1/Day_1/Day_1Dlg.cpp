
// Day_1Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Day_1.h"
#include "Day_1Dlg.h"
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


// CDay_1Dlg ��ȭ ����



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


// CDay_1Dlg �޽��� ó����

BOOL CDay_1Dlg::OnInitDialog()
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CDay_1Dlg::OnPaint()
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
HCURSOR CDay_1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*
WinExec
 - 16bit �Լ�, �ɼ� ����
 - �����ڵ� ������
 - ���������� CreateProcess(), WaitForInputIdle(), return ȣ��
*/
void CDay_1Dlg::OnBnClickedExecBtn()
{
	::WinExec("Notepad.exe", SW_SHOWNORMAL);

	CWnd* pWnd = FindWindow(_T("Notepad"), NULL);
	if (pWnd == NULL)
		AfxMessageBox(_T("�޸����� ã�� �� �����ϴ�."));
	else
		AfxMessageBox(_T("�޸����� ã�ҽ��ϴ�."));
}

/*
CreateProcess
 - ���μ��� ���� �� ����
 - ������ ���μ����� ����ϱ� ���� WaitForInputIdle()�� �ʱ�ȭ
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
		AfxMessageBox(_T("�޸����� ã�� �� �����ϴ�."));
	else
		AfxMessageBox(_T("�޸����� ã�ҽ��ϴ�."));
}

/*
ExitProcess
 - ���μ��� ���� ó���� �ٸ� ���μ������� �뺸
 - DLL, ������, �ڵ� ����
*/
void CDay_1Dlg::OnBnClickedExitBtn()
{
	ExitProcess(0);
}

/*
TerminateProcess
 - �ٸ� ���μ��� ���� ����, ���������� ���� ���
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

	AfxMessageBox(_T("��Ʈ�е� ���α׷� ����"));
}

void CDay_1Dlg::OnBnClickedEnumprocessBtn() {}
/*
EnumProcess() 
 - ���� �������� ���μ������� ID�� �迭�� �ε�
 - ���μ����� ���� �����̹Ƿ� ������ �źεǴ� ��찡 ����
ZeroMemory
 - �޸� ������ 0x00���� ä��� ��ũ��
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

	// Process ������ �迭�� ����
	if (::EnumProcesses(pidArray, sizeof(pidArray), &cbNeeded))
	{
		nProcesses = cbNeeded / sizeof(DWORD);
		for (DWORD i = 0; i <= nProcesses; i++)
		{
			HANDLE hProcess;
			DWORD pid = pidArray[i];

			// pid�� ���� �ڵ� ȹ��
			hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

			if (hProcess != NULL)
			{
				// �ʱ�ȭ �� �ڵ��� ���ؼ� ���� �̸� ȹ��
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
 - �ü������ ��Ź�� ������ ����ϴ� ���
 - �ý��� ���μ����鿡 ���� ������ �Ϻ� Ȯ�� ����
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
 - OpenProcess�� ���ؼ� �ش� PID�� ���� ���μ����� �ڵ��� ȹ��
 - �ڵ��� ���� ���μ��� ���� �� �ڵ� �ݱ�
*/
void CDay_1Dlg::OnBnClickedKillprocessBtn()
{
	UpdateData(1);//��Ʈ�� --> ����

	HANDLE hProcess = ::OpenProcess( PROCESS_TERMINATE, FALSE, m_dwPidKill);

	if (hProcess != NULL)
	{
		::TerminateProcess(hProcess, (unsigned)-1);
		::CloseHandle(hProcess);
	}
}

/*
FindWindow
 - ���ڿ� �ش��ϴ� �̸��� ���μ����� ã�´�.
SendMessage
 - FindWindow�� ã�� �����쿡 �޼����� ������.
CreateProcess
 - STARTUPINFO, PROCESS_INFORMATION ����ü�� ���ڷ� �޾� ���μ����� ����
*/
void CDay_1Dlg::OnBnClickedProcessB()
{
	CWnd* pProcB = FindWindow(NULL, _T("ProcB"));
	if (pProcB == NULL)
	{
		AfxMessageBox(_T("ProcB ���� �����ϼ���"));
		return;
	}

	TCHAR strPath[20] = _T("Notepad.exe");
	STARTUPINFO si = { sizeof(STARTUPINFO), };
	PROCESS_INFORMATION pi;
	::CreateProcess(NULL, strPath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	/////////////////////////////
	CString strTemp;
	strTemp.Format(_T("���μ��� �ڵ� %u�� ID %d ����"), pi.hProcess, pi.dwProcessId);
	AfxMessageBox(strTemp);

	pProcB->SendMessage(WM_USER + 1, (WPARAM)pi.dwProcessId, 0);
}
