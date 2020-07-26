
// CSO_HotkeyDlg.h: 標頭檔
//

#pragma once


// CCSOHotkeyDlg 對話方塊
class CCSOHotkeyDlg : public CDialogEx
{
// 建構
public:
	CCSOHotkeyDlg(CWnd* pParent = nullptr);	// 標準建構函式

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CSO_HOTKEY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	HANDLE m_GF2thread;
	HANDLE m_SingGimthread;
	HANDLE m_SingGimthread_Forcheck;
	HANDLE m_NumpadCheckthread;
	HANDLE m_DPS_Leftthread;
	HANDLE m_DPS_Rightthread;
	HANDLE m_KaahungThread;
	void SingGim();
	void DPS_Left();
	void DPS_Right();
	CButton m_GF2Check;
	CButton m_SingGimCheck;
	CButton m_NumpadCheck;
	CButton m_KaahungCheck;
	afx_msg void OnBnClickedGf2check();
	afx_msg void OnBnClickedSinggimcheck();
	afx_msg void OnBnClickedNumpadcheck();
	afx_msg void OnBnClickedKaahungcheck();
};
