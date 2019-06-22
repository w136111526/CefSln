#pragma once
#include <cef\include\cef_app.h>
#include <cef\include\cef_client.h>
#include <cef\include\cef_command_line.h>
#include <cef\include\cef_load_handler.h>
#include <cef\include\cef_browser_process_handler.h>
#include <cef\include\wrapper\cef_helpers.h>
#include <cef\include\views\cef_browser_view.h>
#include <cef\include\views\cef_window.h>
#include <cef\include\wrapper\cef_closure_task.h>
#include <cef\include\capi\cef_app_capi.h>
#include <list>

class CCefHandlerImpl:
	public CefApp,
	public CefClient,
	public CefDisplayHandler,
	public CefLifeSpanHandler,
	public CefLoadHandler,
	public CefBrowserProcessHandler
{
public:
	CCefHandlerImpl();
	~CCefHandlerImpl();

	static  CCefHandlerImpl *getInstance();

	// CefLoadHandler methods
	virtual void OnLoadStart(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		TransitionType transition_type) override;
	virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		int httpStatusCode) override;

	// CefApp methods.
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override
	{
		return this;
	}
	virtual void OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line) OVERRIDE;
	

	// CefBrowserProcessHandler methods:
	virtual void OnContextInitialized() OVERRIDE;
	virtual void OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line) OVERRIDE;

	// Execute Delegate notifications on the main thread.
	void NotifyBrowserCreated(CefRefPtr<CefBrowser> browser);
	void NotifyBrowserClosing(CefRefPtr<CefBrowser> browser);
	void NotifyBrowserClosed(CefRefPtr<CefBrowser> browser);

	// CefClient methods:
	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE{
		return this;
	}
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE{
		return this;
	}
	virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE{ return this; }


	// CefDisplayHandler methods:
	virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
		const CefString& title) OVERRIDE;

	// CefLifeSpanHandler methods:
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

	// CefLoadHandler methods:
	virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		ErrorCode errorCode,
		const CefString& errorText,
		const CefString& failedUrl) OVERRIDE;

	// Request that all existing browser windows close.
	void CloseAllBrowsers(bool force_close);

	bool IsClosing() const { return is_closing_; }

	CefRefPtr<CefBrowser> GetBrowser(HWND hParentWnd); //PP: 根据窗口句柄获取对应的浏览器对象

private:
	// Platform-specific implementation.
	void PlatformTitleChange(CefRefPtr<CefBrowser> browser,
		const CefString& title);

	// True if the application is using the Views framework.
	const bool use_views_;

	// The current number of browsers using this handler.
	int browser_count_;

	// List of existing browser windows. Only accessed on the CEF UI thread.
	typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
	BrowserList browser_list_;

	bool is_closing_;
	IMPLEMENT_REFCOUNTING(CCefHandlerImpl);
};

