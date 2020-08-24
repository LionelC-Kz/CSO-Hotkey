
// CSO_HotkeyDlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "CSO_Hotkey.h"
#include "CSO_HotkeyDlg.h"
#include "afxdialogex.h"
#include "CSOScript.h"
#include "Hotkey.h"

CSOScript cs;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define logbox(fmt, ...)\
CString str; \
str.Format(CString(fmt), __VA_ARGS__); \
AfxMessageBox(str);

CCSOHotkeyDlg* g_dlg;

// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
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


// CCSOHotkeyDlg 對話方塊



CCSOHotkeyDlg::CCSOHotkeyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CSO_HOTKEY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCSOHotkeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GF2Check, m_GF2Check);
	DDX_Control(pDX, IDC_SingGimCheck, m_SingGimCheck);
	DDX_Control(pDX, IDC_NumpadCheck, m_NumpadCheck);
	DDX_Control(pDX, IDC_KaahungCheck, m_KaahungCheck);
}

BEGIN_MESSAGE_MAP(CCSOHotkeyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GF2Check, &CCSOHotkeyDlg::OnBnClickedGf2check)
	ON_BN_CLICKED(IDC_SingGimCheck, &CCSOHotkeyDlg::OnBnClickedSinggimcheck)
	ON_BN_CLICKED(IDC_NumpadCheck, &CCSOHotkeyDlg::OnBnClickedNumpadcheck)
	ON_BN_CLICKED(IDC_KaahungCheck, &CCSOHotkeyDlg::OnBnClickedKaahungcheck)
	ON_BN_CLICKED(IDC_Setminpos, &CCSOHotkeyDlg::OnBnClickedSetminpos)
END_MESSAGE_MAP()


// CCSOHotkeyDlg 訊息處理常式

BOOL CCSOHotkeyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	//SetIcon(m_hIcon, TRUE);			// 設定大圖示
	//SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	g_dlg = this;

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CCSOHotkeyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CCSOHotkeyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CCSOHotkeyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCSOHotkeyDlg::OnBnClickedGf2check()
{
	OnceHotkey* GF2 = new OnceHotkey('F', []()
		{
			cs.GF2();
		}, []()
		{
			return (bool)g_dlg->m_GF2Check.GetCheck();
		});
	if (m_GF2Check.GetCheck())
	{
		GF2->run();
	}
	else
	{
		delete GF2;
	}
}

void CCSOHotkeyDlg::OnBnClickedSinggimcheck()
{
	SwitchHotkey* SingGim = new SwitchHotkey('V', []()
		{
			cs.Singgimdefence();
		}, []()
		{
			return (bool)g_dlg->m_SingGimCheck.GetCheck();
		});
	if (m_SingGimCheck.GetCheck())
	{
		SingGim->run();
	}
	else
	{
		delete SingGim;
	}
}

void CCSOHotkeyDlg::OnBnClickedNumpadcheck()
{
	SwitchHotkey* DPS_Left = new SwitchHotkey(97, []()
		{
			cs.DPS_Left();
		}, []()
		{
			return (bool)g_dlg->m_NumpadCheck.GetCheck();
		}); //num1
	SwitchHotkey* DPS_Right = new SwitchHotkey(98, []()
		{
			cs.DPS_Right();
		}, []()
		{
			return (bool)g_dlg->m_NumpadCheck.GetCheck();
		}); //num2
	if (m_NumpadCheck.GetCheck())
	{
		DPS_Left->run();
		DPS_Right->run();
	}
	else
	{
		delete DPS_Left;
		delete DPS_Right;
	}
}

void CCSOHotkeyDlg::OnBnClickedKaahungcheck()
{
	OnceHotkey* kaahung = new OnceHotkey('C', []()
		{
			cs.kaahung();
		}, []()
		{
			return (bool)g_dlg->m_KaahungCheck.GetCheck();
		});
	if (m_KaahungCheck.GetCheck())
	{
		kaahung->run();
	}
	else
	{
		delete kaahung;
	}
}


void CCSOHotkeyDlg::OnBnClickedSetminpos()
{
	POINT pos;
	MessageBox(L"請將滑鼠移到最小化\n然後按下Enter", L"提示", MB_TOPMOST);
	GetCursorPos(&pos);
	HWND processHANDLE = ::WindowFromPoint(pos);
	::ScreenToClient(processHANDLE, &pos);
	cs.Setminpos(pos.x, pos.y);
}