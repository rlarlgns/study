
// Day_2Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Day_2.h"
#include "Day_2Dlg.h"
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


// CDay_2Dlg ��ȭ ����



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


// CDay_2Dlg �޽��� ó����

BOOL CDay_2Dlg::OnInitDialog()
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CDay_2Dlg::OnPaint()
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
HCURSOR CDay_2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

DWORD TlsIndex;
int nCount;			// Air���� ������ ��
int arData[100];	
int nIndex;			// ������� ���� Air ������ ����
int nFileIndex = 0;		// ������� ���� ������ ����


/*
Start button click
 - OnTimer �Լ� ȣ��
*/
void CDay_2Dlg::OnBnClickedStartBtn()
{
	nIndex = 0;
	// SetTimer(1, 100, NULL);
	 SetTimer(1, 20, NULL); //GetAddNum() ȣ��� ������ ����
}

/*
Finish button click
 - Timer �Լ� Kill
*/
void CDay_2Dlg::OnBnClickedFinishBtn()
{
	KillTimer(1);
}

/*
GetAddNum
 - �����͸� ������ ��Ģ���� ����
*/
int GetAddNum()
{
	// static int m = 0;
	// ��� 2. TLS�� ����Ѵ�.
	// __declspec(thread) static int m = 0;
	int m = (int)TlsGetValue(TlsIndex);

	if (m == 5000) m = 0;
	m += 1000;

	TlsSetValue(TlsIndex, (LPVOID)(m));
	return m;
}

/*
CalcThread
 - 100���� �����͸� �޾Ƽ� ���� �� ���Ͽ� �����ϴ� ������
*/
DWORD WINAPI CalcThread(LPVOID p)
{
	int *arWork = (int*)p;

	//arWork�� �����͸� ����
	for (int i = 0; i<100; i++)
	{
		arWork[i] = arWork[i] * 2;
		arWork[i] = arWork[i] + GetAddNum();
		Sleep(50);//����, ��� ���� ������ �۾��� ������
	}

	//������ arWork�� �����̳� DB�� ����/ �Ǵ� ��Ʈ��ũ�� ����
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

	free(arWork);//��ġ�� �ָ��� ���߿� ����ȭ�� Ǯ��� ��
	return 0;
}

/*
OnTimer
 - ���纻�� ������� �Ѱܼ� ����
 - �����带 ������ ���� ���� ������ �ٷ� CloseHandle
*/
void CDay_2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		arData[nIndex++] = ++nCount;
		if (nIndex == 100)
		{
			// ��� 1.
			// �۾� ���纻�� ����� �浹 ȸ��
			int *arCopy = (int*)malloc(sizeof(arData));
			memcpy(arCopy, arData, sizeof(arData));

			DWORD ThreadID;
			
			// arCopy�� ����Ͽ� �浹�� ����
			// CloseHandle(CreateThread(NULL, 0, CalcThread, arData, 0, &ThreadID));
			CloseHandle(CreateThread(NULL, 0, CalcThread, arCopy, 0, &ThreadID));

			SetDlgItemText(IDC_STATIC_MSG, _T("100���� ������ �Է¿Ϸ�--> ������ ȣ��"));
			Sleep(1000);//���� �����͸� �޾Ƶ��̱� ���� �ణ�� �غ� ������
			nIndex = 0;
			//Sleep(6000);//CalcThread�� ����� ���ð��̶�� �Ǵ���(�ָ���)
			//free(arCopy);//��ġ�� �ָ���
		}
		else
		{
			CString strTemp;
			strTemp.Format(_T("%d��° ������(%d)�� �Է���"), nIndex, nCount);
			SetDlgItemText(IDC_STATIC_MSG, strTemp);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}

/*
OnCreate
 - ���� �� TLS �Ҵ�
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
 - �������Ҷ� TLS free
*/
void CDay_2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	TlsFree(TlsIndex);
}


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
