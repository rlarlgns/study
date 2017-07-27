
// Day_4Dlg.h : 헤더 파일
//

#pragma once


// CDay_4Dlg 대화 상자
class CDay_4Dlg : public CDialogEx
{
// 생성입니다.
public:
	CDay_4Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DAY_4_DIALOG };
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
	afx_msg void OnBnClickedFilereadBtn();
	afx_msg void OnBnClickedFilewriteBtn();
	afx_msg void OnBnClickedConnectBtn();
	afx_msg void OnBnClickedDisconnectBtn();
	afx_msg void OnEnChangeEdit1();
	afx_msg LRESULT OnUserMessage1(WPARAM w, LPARAM l);
	afx_msg void OnBnClickedEventBtn();
	afx_msg void OnBnClickedCallbackBtn();
	afx_msg void OnBnClickedBigfileBtn();
	afx_msg void OnBnClickedMmfBtn();
};
