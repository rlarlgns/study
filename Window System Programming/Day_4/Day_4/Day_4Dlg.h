
// Day_4Dlg.h : ��� ����
//

#pragma once


// CDay_4Dlg ��ȭ ����
class CDay_4Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CDay_4Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DAY_4_DIALOG };
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
