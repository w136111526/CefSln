#pragma once
#include <cef\include\cef_client.h>

class CCefHandlerImpl:
	public CefClient,
	public CefDisplayHandler,
	public CefLifeSpanHandler,
	public CefLoadHandler
{
public:
	CCefHandlerImpl();
	~CCefHandlerImpl();

	static  CCefHandlerImpl *getInstance();

	IMPLEMENT_REFCOUNTING(CCefHandlerImpl);

};

