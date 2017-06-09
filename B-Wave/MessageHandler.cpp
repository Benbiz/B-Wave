#include "stdafx.h"
#include "Device.h"
#include "BWave.h"
#include "Command.h"
#include "MessageHandler.h"

BoxAPI::Network::MessageHandler::MessageHandler()
{

}

BoxAPI::Network::MessageHandler::~MessageHandler()
{

}

void BoxAPI::Network::MessageHandler::init(std::shared_ptr<sio::socket> sock)
{
	_sock = sock;
	_sock->on("InclusionMode", sio::socket::event_listener(std::bind(&BoxAPI::Network::ControllerHandler::onInclusionMode, &_controller, std::placeholders::_1)));
	_sock->on("ExclusionMode", sio::socket::event_listener(std::bind(&BoxAPI::Network::ControllerHandler::onExclusionMode, &_controller, std::placeholders::_1)));

	_sock->on("ModuleList", sio::socket::event_listener(std::bind(&BoxAPI::Network::ModuleListHandler::onModuleList, &_modulelist, std::placeholders::_1)));

	_sock->on("Command", sio::socket::event_listener(std::bind(&BoxAPI::Network::CommandHandler::onCommand, &_command, std::placeholders::_1)));

	_sock->on("NewScenario", sio::socket::event_listener(std::bind(&BoxAPI::Network::ScenarioHandler::onNewScenario, &_scenario, std::placeholders::_1)));
}