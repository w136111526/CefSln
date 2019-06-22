#include "stdafx.h"
#include "CefHandlerImpl.h"


CCefHandlerImpl::CCefHandlerImpl():
use_views_(false), 
is_closing_(false),
browser_count_(0)
{

}


CCefHandlerImpl::~CCefHandlerImpl()
{

}

CCefHandlerImpl* CCefHandlerImpl::getInstance()
{
	static CCefHandlerImpl inst;
	return &inst;
}

void CCefHandlerImpl::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)
{
	CEF_REQUIRE_UI_THREAD();

	if (use_views_) {
		// Set the title of the window using the Views framework.
		CefRefPtr<CefBrowserView> browser_view =
			CefBrowserView::GetForBrowser(browser);
		if (browser_view) {
			CefRefPtr<CefWindow> window = browser_view->GetWindow();
			if (window)
				window->SetTitle(title);
		}
	}
	else {
		// Set the title of the window using platform APIs.
		PlatformTitleChange(browser, title);
	}
}

void CCefHandlerImpl::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();
	browser_count_++;
	HWND hHostWnd = browser->GetHost()->GetWindowHandle(); //PP: 这里获得窗口句柄是浏览器页面的Host句柄，可能是主窗口里的一个子窗口

	// Add to the list of existing browsers.
	browser_list_.push_back(browser);
}

bool CCefHandlerImpl::DoClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();

	// Closing the main window requires special handling. See the DoClose()
	// documentation in the CEF header for a detailed destription of this
	// process.
	if (browser_list_.size() == 1) {
		// Set a flag to indicate that the window close should be allowed.
		is_closing_ = true;
	}

	// Allow the close. For windowed browsers this will result in the OS close
	// event being sent.
	return false;
	//is_closing_ = true;
	//return true;

}

void CCefHandlerImpl::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();

	if (--browser_count_ == 0)
	{

	}

	// Remove from the list of existing browsers.
	BrowserList::iterator bit = browser_list_.begin();
	for (; bit != browser_list_.end(); ++bit) {
		if ((*bit)->IsSame(browser)) {
			browser_list_.erase(bit);
			break;
		}
	}

	if (browser_list_.empty()) {
		// All browser windows have closed. Quit the application message loop.
		//cef_quit_message_loop();
		//CefQuitMessageLoop(); //PP: 控制台程序才需要调用这个函数，如果是MFC应用程序，要把这句注释掉，否则执行到这里会报错！
	}
}

void CCefHandlerImpl::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl)
{
	CEF_REQUIRE_UI_THREAD();

	// Don't display an error for downloaded files.
	if (errorCode == ERR_ABORTED)
		return;

	// Display a load error message.
	std::stringstream ss;
	ss << "<html><body bgcolor=\"white\">"
		"<h2>Failed to load URL "
		<< std::string(failedUrl) << " with error " << std::string(errorText)
		<< " (" << errorCode << ").</h2></body></html>";
	frame->LoadString(ss.str(), failedUrl);
}

void CCefHandlerImpl::CloseAllBrowsers(bool force_close)
{
	if (!CefCurrentlyOn(TID_UI)) {
		// Execute on the UI thread.
		CefPostTask(TID_UI, base::Bind(&CCefHandlerImpl::CloseAllBrowsers, this,force_close));
		return;
	}

	if (browser_list_.empty())
		return;

	BrowserList::const_iterator it = browser_list_.begin();
	for (; it != browser_list_.end(); ++it)
		(*it)->GetHost()->CloseBrowser(force_close);
}

CefRefPtr<CefBrowser> CCefHandlerImpl::GetBrowser(HWND hParentWnd)
{
	BrowserList::const_iterator it = browser_list_.begin();
	for (; it != browser_list_.end(); ++it)
	{
		if (::IsChild(hParentWnd, (*it)->GetHost()->GetWindowHandle())) //浏览器渲染窗口是上层窗口里的一个子窗口
			return *it;

	}
	return NULL;
}

void CCefHandlerImpl::PlatformTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)
{
	CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
	SetWindowText(hwnd, std::wstring(title).c_str());
}

void CCefHandlerImpl::NotifyBrowserCreated(CefRefPtr<CefBrowser> browser)
{
	
}

void CCefHandlerImpl::NotifyBrowserClosing(CefRefPtr<CefBrowser> browser)
{
	
}

void CCefHandlerImpl::NotifyBrowserClosed(CefRefPtr<CefBrowser> browser)
{
	
}

void CCefHandlerImpl::OnContextInitialized()
{
	CEF_REQUIRE_UI_THREAD();
}


void CCefHandlerImpl::OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line)
{
	//AfxMessageBox(_T("CCefHandlerImpl::OnBeforeCommandLineProcessing"));
	//OutputDebugStringA("CCefHandlerImpl::OnBeforeCommandLineProcessing");
	command_line->AppendSwitch("--allow-outdated-plugins"); // 允许允许低版本flash
	command_line->AppendSwitch("--disable-web-security");	// 关闭同源策略
	//command_line->AppendSwitch("--enable-system-flash");	// 使用系统flash
	command_line->AppendSwitchWithValue("--ppapi-flash-version", "32.0.0.207");
	command_line->AppendSwitchWithValue("--ppapi-flash-path", "PepperFlash\\pepflashplayer.dll");

	// 此参数解决多窗口问题
	command_line->AppendSwitch("--process-per-site");
	
	//代理
	//command_line->AppendSwitch("no-proxy-server");
	//command_line->AppendSwitchWithValue("--proxy-server", "127.0.0.1:9999");
	//command_line->AppendSwitchWithValue("--proxy-server", "http://127.0.0.1:9999");
	//command_line->AppendSwitchWithValue("--proxy-server", "http://115.231.130.3:9999");
}

void CCefHandlerImpl::OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line)
{
	OutputDebugStringA("CCefHandlerImpl::OnBeforeChildProcessLaunch");
	
}
