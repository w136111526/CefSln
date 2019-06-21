#include "stdafx.h"
#include "CefHandlerImpl.h"


CCefHandlerImpl::CCefHandlerImpl()
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
