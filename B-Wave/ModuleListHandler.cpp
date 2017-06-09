#include "stdafx.h"
#include "Device.h"
#include "BWave.h"
#include "Command.h"
#include "ModuleListHandler.h"

BoxAPI::Network::ModuleListHandler::ModuleListHandler()
{
}

BoxAPI::Network::ModuleListHandler::~ModuleListHandler()
{
}

void BoxAPI::Network::ModuleListHandler::onModuleList(sio::event &e)
{
	std::cout << "[NET] Message: ModuleList" << std::endl;
	auto devices = BWave::Instance().getController().getDevices();
	std::shared_ptr<sio::message> mess = sio::object_message::create();

	mess->get_map()["modules"] = sio::array_message::create();
	for (std::shared_ptr<BoxAPI::Device> d : devices)
	{
		if (d->getId() == 1)
			continue;
		std::shared_ptr<sio::message> m = sio::object_message::create();
		m->get_map()["id"] = sio::int_message::create(d->getId());
		m->get_map()["commands"] = sio::object_message::create();
		m->get_map()["commands"]->get_map()["switchs"] = sio::array_message::create();
		m->get_map()["commands"]->get_map()["sensormultilevels"] = sio::array_message::create();
		m->get_map()["commands"]->get_map()["sensorbinarys"] = sio::array_message::create();
		m->get_map()["commands"]->get_map()["switchcolors"] = sio::array_message::create();
		m->get_map()["commands"]->get_map()["switchmultilevels"] = sio::array_message::create();

		for (std::shared_ptr<BoxAPI::ICommand> c : d->getCommands())
		{
			std::shared_ptr<sio::message> cmd = sio::object_message::create();
			if (c->getType() == ICommand::ZSwitchBinary)
			{
				std::shared_ptr<BoxAPI::Command::ZSwitchBinary> zswitch = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchBinary>(c);
				cmd->get_map()["instance"] = sio::int_message::create(zswitch->getInstance());
				cmd->get_map()["level"] = sio::bool_message::create(zswitch->getSwitch());

				m->get_map()["commands"]->get_map()["switchs"]->get_vector().push_back(cmd);
			}
			else if (c->getType() == ICommand::ZSensorMultiLevel)
			{
				std::shared_ptr<BoxAPI::Command::ZSensorMultiLevel> sensor = std::dynamic_pointer_cast<BoxAPI::Command::ZSensorMultiLevel>(c);
				cmd->get_map()["instance"] = sio::int_message::create(sensor->getInstance());
				cmd->get_map()["type_id"] = sio::int_message::create(sensor->getId());
				cmd->get_map()["scale"] = sio::string_message::create(sensor->getScale());
				cmd->get_map()["level"] = sio::int_message::create(round(sensor->getValue()));

				m->get_map()["commands"]->get_map()["sensormultilevels"]->get_vector().push_back(cmd);
			}
			else if (c->getType() == ICommand::ZSensorBinary)
			{
				std::shared_ptr<BoxAPI::Command::ZSensorBinary> sensor = std::dynamic_pointer_cast<BoxAPI::Command::ZSensorBinary>(c);
				cmd->get_map()["instance"] = sio::int_message::create(sensor->getInstance());
				cmd->get_map()["level"] = sio::bool_message::create(sensor->getValue());

				m->get_map()["commands"]->get_map()["sensorbinarys"]->get_vector().push_back(cmd);
			}
			else if (c->getType() == ICommand::ZSwitchColor)
			{
				std::shared_ptr<BoxAPI::Command::ZSwitchColor> switchcolor = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(c);
				cmd->get_map()["instance"] = sio::int_message::create(switchcolor->getInstance());
				cmd->get_map()["color_id"] = sio::int_message::create(switchcolor->getId());
				cmd->get_map()["color"] = sio::string_message::create(switchcolor->getColor());
				cmd->get_map()["level"] = sio::int_message::create(switchcolor->getValue());

				m->get_map()["commands"]->get_map()["switchcolors"]->get_vector().push_back(cmd);
			}
			else if (c->getType() == ICommand::ZSwitchMultiLevel)
			{
				std::shared_ptr<BoxAPI::Command::ZSwitchMultiLevel> switchmultilevel = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchMultiLevel>(c);
				cmd->get_map()["instance"] = sio::int_message::create(switchmultilevel->getInstance());
				cmd->get_map()["level"] = sio::int_message::create(switchmultilevel->getLevel());

				m->get_map()["commands"]->get_map()["switchmultilevels"]->get_vector().push_back(cmd);
			}
		}
		mess->get_map()["modules"]->get_vector().push_back(m);
	}
	e.put_ack_message(mess);
}
