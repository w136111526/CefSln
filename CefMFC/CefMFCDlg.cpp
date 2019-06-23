
// CefMFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CefMFC.h"
#include "CefMFCDlg.h"
#include "afxdialogex.h"
#include "CefHelper/CefHandlerImpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CefRefPtr<CCefHandlerImpl>  g_BrowsersHandler = new CCefHandlerImpl;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCefMFCDlg 对话框



CCefMFCDlg::CCefMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCefMFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCefMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCefMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CCefMFCDlg 消息处理程序

BOOL CCefMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	CefWindowInfo info;
	RECT rect;
	GetClientRect(&rect);
	RECT rectnew = rect;
	rectnew.top = rect.top + 30;
	rectnew.bottom = rect.bottom;
	rectnew.left = rect.left;
	rectnew.right = rect.right;
	info.SetAsChild(GetSafeHwnd(), rectnew);
	CefBrowserSettings browserSettings;
	
	CefString csUrl = "https://cn.bing.com/";
	//csUrl = "https://www.bilibili.com/video/av55944365?spm_id_from=333.334.b_62696c695f6164.9";
	//csUrl = "http://www.ip138.com/";
	//csUrl = "https://helpx.adobe.com/flash-player/kb/archived-flash-player-versions.html";
	//csUrl = "http://moni.dhfpp.com/web/login.htm";
	//csUrl = "https://paimai.alltobid.com/bid/b901b3c0ba414c3bb7c08761aedbff50/login.htm?tdsourcetag=s_pcqq_aiomsg";
	csUrl = "https://test.alltobid.com";
	//csUrl = "http://www.radio366.com/bf.asp?bh=1";
	//csUrl = "chrome://plugins";
	//csUrl = "http://www.macromedia.com/support/documentation/en/flashplayer/help/settings_manager04.html";
	//csUrl = "http://localhost/FlashTrace/main.html";
	CefBrowserHost::CreateBrowser(info, g_BrowsersHandler.get(), csUrl, browserSettings, NULL, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCefMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCefMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCefMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCefMFCDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (g_BrowsersHandler.get())
	{
		CefRefPtr<CefBrowser>browser = g_BrowsersHandler->GetBrowser(m_hWnd);
		if (browser)
		{
			CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
			::MoveWindow(hwnd, 0, 60, cx, cy - 60, true);
		}
	}
}


void CCefMFCDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//g_BrowsersHandler->CloseAllBrowsers(true);
	//g_BrowsersHandler->Release();

	CDialogEx::OnClose();
}
