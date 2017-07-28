
// Day_4Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Day_4.h"
#include "Day_4Dlg.h"
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


// CDay_4Dlg ��ȭ ����



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


// CDay_4Dlg �޽��� ó����

BOOL CDay_4Dlg::OnInitDialog()
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CDay_4Dlg::OnPaint()
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
HCURSOR CDay_4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*
FILE READ
- �ϵ� ��ũ�� ������ ���� �������� �о�� ���
CreateFile
- �о� �鿩�� ������ �����Ͽ� �� �ڵ� ���� �����´�.
*/
void CDay_4Dlg::OnBnClickedFilereadBtn()
{
	HANDLE hFile = CreateFile(_T("c:\\testfile.txt"),
		GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	// 1. ���� ���� ������Ʈ (���������� ����) �� �����.
	HANDLE hFMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);

	// 2. ���� ���� ������Ʈ��, ���μ����� ����޸��� �ּҰ����� �����Ѵ�.(���Ϻ�)
	TCHAR* PtrUni = (TCHAR *)MapViewOfFile(hFMap, FILE_MAP_READ, 0, 0, 0);

	int nResult;
	// 3. ������ �޸� ó�� ���
	// �ؽ�Ʈ ������ �� 10���ڰ� �����ڵ��� ���
	if (IsTextUnicode(PtrUni, 10, &nResult))
	{
		//������ �޽����ڽ��� ����Ѵ�.
		MessageBoxW(PtrUni, _T("Uni�ڵ�"), MB_OK);
		UnmapViewOfFile(PtrUni);
	}
	else
	{
		char* PtrAnsi = (char *)MapViewOfFile(hFMap, FILE_MAP_READ, 0, 0, 0);
		strcpy(PtrAnsi, ("ansi"));
		MessageBoxA(NULL, PtrAnsi, ("ANSI�ڵ�"), MB_OK);
		UnmapViewOfFile(PtrAnsi);
	}

	//4. ���Ϻ並 �ݴ´�.
	CloseHandle(hFMap);
	CloseHandle(hFile);
}

/*
FILE WRITE
- ������ �ҷ��� �����ϰ� �����͸� ����� ������ ����
*/
void CDay_4Dlg::OnBnClickedFilewriteBtn()
{
	HANDLE hFile;
	hFile = CreateFile(_T("c:\\testfile2.txt"), GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//1. ���� ���� ������Ʈ (���������� ����) �� �����.
	HANDLE hFMap;
	hFMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, NULL);

	//2. ���� ���� ������Ʈ��, ���μ����� ����޸��� �ּҰ����� �����Ѵ�.(���Ϻ�)
	char* PtrInFile;
	PtrInFile = (char *)MapViewOfFile(hFMap, FILE_MAP_WRITE, 0, 0, 0);

	//3. ������ �޸�ó�� ����Ѵ�.
	strcpy(PtrInFile, ("hello"));
	PtrInFile[0] = 'A';

	//4. ���Ϻ並 �ݴ´�.
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
- "MyMemShareMapping" �̸��� ���� ���� ���� ������Ʈ�� �����Ѵ�.
- ���� �ٸ� ���μ������� ������ ���� �޸𸮸� ����Ű���� ��
*/
void CDay_4Dlg::OnBnClickedConnectBtn()
{
	//1. ���� ���� ������Ʈ (���������� ����) �� �����.
	hFMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE,
		0, 1024, _T("MyMemShareMapping"));

	//2. ���� ���� ������Ʈ��, ���μ����� ����޸��� �ּҰ����� �����Ѵ�.(���Ϻ�)
	PtrFile = (TCHAR *)MapViewOfFile(hFMap, FILE_MAP_ALL_ACCESS, 0, 0, 1024);
}

/*
Disconnect
- ���� ���� ������Ʈ ����
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
	// �����͸� ȭ�鿡 ���
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
- �����͸� �ؽ�Ʈ ���Ϸ� �����ϴµ� �񵿱� IO�� �̿��ؼ� ���ÿ� IO�� ó��
*/
void CDay_4Dlg::OnBnClickedEventBtn()
{
	HANDLE hFile;
	TCHAR filename[] = _T("c:\\ABC.txt");
	hFile = CreateFile(filename, GENERIC_WRITE, 0, 0,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);

	/*
	OVERLAPPED ����ü
	- �񵿱� IO�� �ϱ� ���� ����
	- hEvent�� �ڵ鷯�μ� IO�� �ϷḦ �˸��� ���� �̺�Ʈ�� ��´�.
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
	- offset�� �̿��ؼ� ���� �ٸ� ��ġ�� �����͸� ��
	*/
	ov.Offset = 0;
	ov.Offset = strlen(strData) * sizeof(char) * 0;
	WriteFile(hFile, strData, sizeof(strData), &dwWritten, &ov);
	GetOverlappedResult(hFile, &ov, &Trans, FALSE);
	{
		CString strTemp;
		strTemp.Format(_T("���� Write ��� �Ϸ� %u"), Trans);
		AfxMessageBox(strTemp);
	}

	ov1.Offset = strlen(strData) * sizeof(char) * 1;
	WriteFile(hFile, strData, sizeof(strData), &dwWritten, &ov1);
	GetOverlappedResult(hFile, &ov1, &Trans, FALSE);
	{
		CString strTemp;
		strTemp.Format(_T("���� Write ��� �Ϸ� %u"), Trans);
		AfxMessageBox(strTemp);
	}

	ov2.Offset = (strlen(strData) * sizeof(char)) * 2;
	WriteFile(hFile, strData, sizeof(strData), &dwWritten, &ov2);
	GetOverlappedResult(hFile, &ov2, &Trans, FALSE);
	{
		CString strTemp;
		strTemp.Format(_T("���� Write ��� �Ϸ� %u"), Trans);
		AfxMessageBox(strTemp);
	}
	CloseHandle(hFile);
}

VOID WINAPI MyCallBack(DWORD errCode, DWORD numOfByteTransfered,
	LPOVERLAPPED overlapped)
{
	CString strTemp = _T("MyIOCPRoutine");
	strTemp.Format(_T("���� Write ��� �Ϸ� \nerrCode : %u\nnumOfByteTransfered:%u\noverlapped->hEvent:%s"),
		errCode, numOfByteTransfered, (DWORD)overlapped->hEvent);
	AfxMessageBox(strTemp);
}

/*
WriteFileEx
- �񵿱� ���� �Լ��� �ݹ��Լ��� ����ϴ� ���
- APC( Asynchronous Procedure Call ) ť�� �̿��ؼ� �Ϸ� �Լ��� ȣ��
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
- 50MEGA�� �����͸� ����
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

	AfxMessageBox(_T("�ڷḸ��⸦ �Ϸ��߽��ϴ�."));
	SetEvent(hEvent);
	return 0;
}

/*
WriteDataThread
- �̺�Ʈ�� �ޱ���� ��ٸ��� �۾� ����
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
		AfxMessageBox(_T("���� ���⸦ �Ϸ��߽��ϴ�."));
	}
	return 0;
}

/*
Big file btn
- ū ������ ����� �۾��� �����ϴµ� �����͸� ����� �������
���Ͽ� �ۼ��ϴ� ������� ������ �۾��� ����
- �̺�Ʈ�� �����ؼ� ����ȭ ó��
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
- ������ ������ �о�� ���� ���� ������Ʈ�� ����� �񵿱�� ������ ����
*/
void CDay_4Dlg::OnBnClickedMmfBtn()
{
	HANDLE hFileSource;
	hFileSource = CreateFile(_T("bigdata.txt"), GENERIC_READ,
		0,//FILE_SHARE_READ,//�б��� �������
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, 0);

	//0. ���������� ũ�⸦ �����Ѵ�.
	LARGE_INTEGER	llFileSize = { 0 };
	//LARGE_INTEGER	llTotalReadSize = {0};

	if (!GetFileSizeEx(hFileSource, &llFileSize))
	{
		AfxMessageBox(_T("GetFileSizeEx ����"));
		CloseHandle(hFileSource);
		return;
	}

	//1. ���� ���� ������Ʈ (���������� ����) �� �����.
	HANDLE hFMap;
	hFMap = CreateFileMapping(hFileSource, NULL, PAGE_READONLY, 0,
		0,//llFileSize.LowPart, 
		NULL);
	if (hFMap == NULL)
	{
		AfxMessageBox(_T("CreateFileMapping ����"));
		CloseHandle(hFileSource);
		return;
	}

	//2. ���� ���� ������Ʈ��, ���μ����� ����޸��� �ּҰ����� �����Ѵ�.(���Ϻ�)
	BYTE* pMemory;
	pMemory = (BYTE *)MapViewOfFile(hFMap, FILE_MAP_READ, 0, 0,
		0);//llFileSize.LowPart);
	if (pMemory == NULL)
	{
		AfxMessageBox(_T("MapViewOfFile ����"));
		CloseHandle(hFileSource);
		return;
	}

	//3. ������ �޸�ó�� ����Ѵ�.
	HANDLE hFileDest;
	hFileDest = CreateFile(_T("copycopy.txt"), GENERIC_WRITE, 0, 0,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);


	OVERLAPPED ov1 = { 0, };
	ov1.hEvent = (HANDLE)_T("�� ������ ����");
	WriteFileEx(hFileDest, pMemory, llFileSize.LowPart, &ov1, MyCallBack);

	if (GetLastError() == ERROR_IO_PENDING)
		MessageBeep(0);
	SleepEx(INFINITE, TRUE);
	CloseHandle(hFileDest);

	// 4. ���Ϻ並 �ݴ´�.
	UnmapViewOfFile(pMemory);
	CloseHandle(hFMap);
	CloseHandle(hFileSource);
}
