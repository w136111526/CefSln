#include "stdafx.h"
#include "CefHandlerImpl.h"


CCefHandlerImpl::CCefHandlerImpl():
use_views_(false), 
is_closing_(false)
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

	HWND hHostWnd = browser->GetHost()->GetWindowHandle(); //PP: �����ô��ھ���������ҳ���Host��������������������һ���Ӵ���

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
}

void CCefHandlerImpl::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();

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
		//CefQuitMessageLoop(); //PP: ����̨�������Ҫ������������������MFCӦ�ó���Ҫ�����ע�͵�������ִ�е�����ᱨ��
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
		if (::IsChild(hParentWnd, (*it)->GetHost()->GetWindowHandle())) //�������Ⱦ�������ϲ㴰�����һ���Ӵ���
			return *it;

	}
	return NULL;
}

void CCefHandlerImpl::PlatformTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)
{
	CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
	SetWindowText(hwnd, std::wstring(title).c_str());
}
