
// Day_1Dlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CDay_1Dlg 대화 상자
class CDay_1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CDay_1Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DAY_1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
