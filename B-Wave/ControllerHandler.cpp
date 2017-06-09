#include "stdafx.h"
#include "Device.h"
#include "BWave.h"
#include "Command.h"
#include "ControllerHandler.h"

BoxAPI::Network::ControllerHandler::ControllerHandler()
{
}

BoxAPI::Network::ControllerHandler::~ControllerHandler()
{
}

void BoxAPI::Network::ControllerHandler::onInclusionMode(sio::event &e)
{
	bool		val;
	bool		ret;

	val = e.get_message()->get_bool();
	ret = BoxAPI::BWave::Instance().getController().setInclusionMode(val);

	e.put_ack_message(sio::bool_message::create(ret));
}

void BoxAPI::Network::ControllerHandler::onExclusionMode(sio::event &e)
{
	bool		val;
	bool		ret;

	val = e.get_message()->get_bool();
	ret = BoxAPI::BWave::Instance().getController().setExclusionMode(val);
	e.put_ack_message(sio::bool_message::create(ret));
}