
// Day_1Dlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CDay_1Dlg ��ȭ ����
class CDay_1Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CDay_1Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DAY_1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedExecBtn();
	afx_msg void OnBnClickedCreateprocessBtn();
	afx_msg void OnBnClickedExitBtn();
	afx_msg void OnBnClickedTerminateBtn();
	afx_msg void OnBnClickedEnumprocessBtn();
	CListBox m_List;
	afx_msg void OnBnClickedSnapshotBtn();
	afx_msg void OnBnClickedKillprocessBtn();
	DWORD m_dwPidKill;
	afx_msg void OnBnClickedProcessB();
};
