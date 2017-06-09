#include "stdafx.h"
#include "Controller.h"
#include "ControllerEvent.h"

BoxAPI::ControllerEvent::EventDispatcher BoxAPI::ControllerEvent::EventDispatcher::m_instance = BoxAPI::ControllerEvent::EventDispatcher();

BoxAPI::ControllerEvent::EventDispatcher::~EventDispatcher()
{

}

BoxAPI::ControllerEvent::EventDispatcher::EventDispatcher()
{

}

BoxAPI::ControllerEvent::EventDispatcher &BoxAPI::ControllerEvent::EventDispatcher::operator=(const EventDispatcher&)
{

}

BoxAPI::ControllerEvent::EventDispatcher::EventDispatcher(const EventDispatcher&)
{

}

BoxAPI::ControllerEvent::EventDispatcher	&BoxAPI::ControllerEvent::EventDispatcher::Instance()
{
	return m_instance;
}
