
// CSO_HotkeyDlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "CSO_Hotkey.h"
#include "CSO_HotkeyDlg.h"
#include "afxdialogex.h"
#include "CSOScript.h"

CSOScript cs;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCSOHotkeyDlg* g_dlg;
int keySingGim = -1;
int keyDPS_Left = -1;
int keyDPS_Right = -1;

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

DWORD WINAPI GF2Thread(LPVOID lpThreadParameter)
{
	MSG msg = { 0 };
	HWND hConsole = GetActiveWindow();
	while (true)
	{
		if (g_dlg->m_GF2Check.GetCheck())
		{
			RegisterHotKey(hConsole, 1, MOD_NOREPEAT, 'F');
			RegisterHotKey(hConsole, 2, MOD_NOREPEAT | MOD_CONTROL, 'F');
			while (GetMessage(&msg, NULL, 0, 0) != 0)
			{
				if (!g_dlg->m_GF2Check.GetCheck())break;
				if (msg.message == WM_HOTKEY && GetAsyncKeyState('F'))
				{
					switch (msg.wParam)
					{
					case 1:
						cs.GF2(); break;
					case 2:
						cs.GF2(); break;
					default:
						break;
					}
				}
				while (GetAsyncKeyState('F'))Sleep(50);
			}
		}
		else
		{
			UnregisterHotKey(hConsole, 1);
			UnregisterHotKey(hConsole, 2);
			break;
		}
		Sleep(1000);
	}
	return NULL;
}

DWORD WINAPI SingGimThread(LPVOID lpThreadParameter)
{
	g_dlg->SingGim();
	return NULL;
}

DWORD WINAPI SingGimThread_Forcheck(LPVOID lpThreadParameter)
{
	MSG msg = { 0 };
	HWND hConsole = GetActiveWindow();
	while (true)
	{
		if (g_dlg->m_SingGimCheck.GetCheck())
		{
			RegisterHotKey(hConsole, 3, MOD_NOREPEAT, 'V');
			while (GetMessage(&msg, NULL, 0, 0) != 0)
			{
				if (!g_dlg->m_SingGimCheck.GetCheck())break;
				if (msg.message == WM_HOTKEY)
				{
					switch (msg.wParam)
					{
					case 3:
						keySingGim *= -1; break;
					default:
						break;
					}
				}
			}
		}
		else
		{
			UnregisterHotKey(hConsole, 3);
			keySingGim = -1;
			break;
		}
		Sleep(1000);
	}
	return NULL;
}

DWORD WINAPI DPS_Leftthread(LPVOID lpThreadParameter)
{
	g_dlg->DPS_Left();
	return NULL;
}

DWORD WINAPI DPS_Rightthread(LPVOID lpThreadParameter)
{
	g_dlg->DPS_Right();
	return NULL;
}

DWORD WINAPI NumpadCheckthread(LPVOID lpThreadParameter)
{
	MSG msg = { 0 };
	HWND hConsole = GetActiveWindow();
	while (true)
	{
		if (g_dlg->m_NumpadCheck.GetCheck())
		{
			RegisterHotKey(hConsole, 1, MOD_NOREPEAT, 97);//num1
			RegisterHotKey(hConsole, 2, MOD_NOREPEAT, 98);//num2
			while (GetMessage(&msg, NULL, 0, 0) != 0)
			{
				if (!g_dlg->m_NumpadCheck.GetCheck())break;
				if (msg.message == WM_HOTKEY)
				{
					switch (msg.wParam)
					{
					case 1:
						keyDPS_Left *= -1; break;
					case 2:
						keyDPS_Right *= -1; break;
					default:
						break;
					}
				}
			}
		}
		else
		{
			UnregisterHotKey(hConsole, 1);
			UnregisterHotKey(hConsole, 2);
			keyDPS_Left = -1;
			keyDPS_Right = -1;
			break;
		}
		Sleep(1000);
	}
	return NULL;
}

DWORD WINAPI KaahungThread(LPVOID lpThreadParameter)
{
	MSG msg = { 0 };
	HWND hConsole = GetActiveWindow();
	while (true)
	{
		if (g_dlg->m_KaahungCheck.GetCheck())
		{
			RegisterHotKey(hConsole, 1, MOD_NOREPEAT, 'C');
			RegisterHotKey(hConsole, 2, MOD_NOREPEAT | MOD_CONTROL, 'C');
			while (GetMessage(&msg, NULL, 0, 0) != 0)
			{
				if (!g_dlg->m_KaahungCheck.GetCheck())break;
				if (msg.message == WM_HOTKEY && GetAsyncKeyState('C'))
				{
					switch (msg.wParam)
					{
					case 1:
						cs.kaahung(); break;
					case 2:
						cs.kaahung(); break;
					default:
						break;
					}
				}
				while (GetAsyncKeyState('C'))Sleep(250);
			}
		}
		else
		{
			UnregisterHotKey(hConsole, 1);
			UnregisterHotKey(hConsole, 2);
			break;
		}
		Sleep(1000);
	}
	return NULL;
}

void CCSOHotkeyDlg::SingGim()
{
	while (true)
	{
		if (keySingGim == 1)
		{
			cs.Singgimdefence();
		}
		if (!m_SingGimCheck.GetCheck())return;
		if (keySingGim == -1)Sleep(50);
	}
}

void CCSOHotkeyDlg::DPS_Left()
{
	while (true)
	{
		if (keyDPS_Left == 1)
		{
			cs.DPS_Left();
		}
		if (!m_NumpadCheck.GetCheck())return;
		if (keyDPS_Left == -1)Sleep(50);
	}
}

void CCSOHotkeyDlg::DPS_Right()
{
	while (true)
	{
		if (keyDPS_Right == 1)
		{
			cs.DPS_Right();
		}
		if (!m_NumpadCheck.GetCheck())return;
		if (keyDPS_Right == -1)Sleep(50);
	}
}

void CCSOHotkeyDlg::OnBnClickedGf2check()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	if (m_GF2Check.GetCheck())
	{
		m_GF2thread = CreateThread(NULL, NULL, GF2Thread, NULL, NULL, NULL);
	}
	else
	{
		CloseHandle(m_GF2thread);
	}
}


void CCSOHotkeyDlg::OnBnClickedSinggimcheck()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	if (m_SingGimCheck.GetCheck())
	{
		m_SingGimthread = CreateThread(NULL, NULL, SingGimThread, NULL, NULL, NULL);
		m_SingGimthread_Forcheck = CreateThread(NULL, NULL, SingGimThread_Forcheck, NULL, NULL, NULL);
	}
	else
	{
		CloseHandle(m_SingGimthread);
		CloseHandle(m_SingGimthread_Forcheck);
	}
}


void CCSOHotkeyDlg::OnBnClickedNumpadcheck()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	if (m_NumpadCheck.GetCheck())
	{
		m_NumpadCheckthread = CreateThread(NULL, NULL, NumpadCheckthread, NULL, NULL, NULL);
		m_DPS_Leftthread = CreateThread(NULL, NULL, DPS_Leftthread, NULL, NULL, NULL);
		m_DPS_Rightthread = CreateThread(NULL, NULL, DPS_Rightthread, NULL, NULL, NULL);
	}
	else
	{
		CloseHandle(m_NumpadCheckthread);
		CloseHandle(m_DPS_Leftthread);
		CloseHandle(m_DPS_Rightthread);
	}
}


void CCSOHotkeyDlg::OnBnClickedKaahungcheck()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	if (m_KaahungCheck.GetCheck())
	{
		m_KaahungThread = CreateThread(NULL, NULL, KaahungThread, NULL, NULL, NULL);
	}
	else
	{
		CloseHandle(m_GF2thread);
	}
}


void CCSOHotkeyDlg::OnBnClickedSetminpos()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	POINT pos;
	MessageBox(L"請將滑鼠移到最小化\n然後按下Enter", L"提示", MB_TOPMOST);
	GetCursorPos(&pos);
	HWND processHANDLE = ::WindowFromPoint(pos);
	::ScreenToClient(processHANDLE, &pos);
	cs.Setminpos(pos.x, pos.y);
}
