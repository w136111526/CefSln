
// CefMFCDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCefMFCDlg �Ի���



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


// CCefMFCDlg ��Ϣ�������

BOOL CCefMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCefMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCefMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCefMFCDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//g_BrowsersHandler->CloseAllBrowsers(true);
	//g_BrowsersHandler->Release();

	CDialogEx::OnClose();
}
