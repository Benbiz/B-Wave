#include "stdafx.h"
#include "ZCallback.h"

BoxAPI::Command::ZCallback::ZCallback()
	: called(false)
{
}

bool BoxAPI::Command::ZCallback::wait()
{
	std::unique_lock<std::mutex> lck(mtx);

	if (called)
		return success;
	cv.wait(lck);
	return success;
}

void BoxAPI::Command::ZCallback::successCallback(const ZWay zway, ZWBYTE functionId, void * arg)
{
	BoxAPI::Command::ZCallback *c = static_cast<BoxAPI::Command::ZCallback *>(arg);

	c->success = true;
	c->called = true;
	c->cv.notify_all();
}

void BoxAPI::Command::ZCallback::failureCallback(const ZWay zway, ZWBYTE functionId, void * arg)
{
	BoxAPI::Command::ZCallback *c = static_cast<BoxAPI::Command::ZCallback *>(arg);

	c->success = false;
	c->called = true;
	c->cv.notify_all();
}
