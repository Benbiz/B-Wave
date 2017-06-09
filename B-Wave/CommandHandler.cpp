#include "stdafx.h"
#include "Device.h"
#include "BWave.h"
#include "Command.h"
#include "CommandHandler.h"

BoxAPI::Network::CommandHandler::CommandHandler()
{
	_commands["switch"] = &BoxAPI::Network::CommandHandler::switchBinary;
	_commands["switchcolor"] = &BoxAPI::Network::CommandHandler::switchColor;
	_commands["switchmultilevel"] = &BoxAPI::Network::CommandHandler::switchMultiLevel;
}

BoxAPI::Network::CommandHandler::~CommandHandler()
{
}

void BoxAPI::Network::CommandHandler::onCommand(sio::event &e)
{
	sio::message::ptr												res;
	sio::message::ptr												mess;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	module;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	command;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	id;
	bool															found = false;

	std::cout << "[NET] onCommand" << std::endl;
	if (e.get_message()->get_flag() != sio::message::flag::flag_object)
	{
		std::cout << "Message not an object" << std::endl;
		return;
	}
	mess = e.get_message();
	res = sio::object_message::create();
	if ((module = mess->get_map().find("module")) == mess->get_map().end() || module->second->get_flag() != sio::message::flag::flag_object)
	{
		std::cout << "Module not an object" << std::endl;
		return;
	}
	if ((id = module->second->get_map().find("id")) == mess->get_map().end() || id->second->get_flag() != sio::message::flag::flag_integer)
	{
		std::cout << "id not an int" << std::endl;
		return;
	}
	for (std::pair<std::string, bool (BoxAPI::Network::CommandHandler::*)(int, std::shared_ptr<sio::message>)> p : _commands)
	{
		if ((command = mess->get_map().find(p.first)) != mess->get_map().end() && command->second->get_flag() == sio::message::flag::flag_object)
		{
			found = true;
			res->get_map()["result"] = sio::bool_message::create((this->*(p.second))(id->second->get_int(), command->second));
			break;
		}
	}
	if (found == false)
	{
		std::cout << "Unknown command name" << std::endl;
		res->get_map()["result"] = sio::bool_message::create(false);
	}
	e.put_ack_message(res);
}

bool BoxAPI::Network::CommandHandler::switchBinary(int moduleid, std::shared_ptr<sio::message> command)
{
	std::cout << "Switching in messageHandler.." << std::endl;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator instance;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator level;

	if ((instance = command->get_map().find("instance")) == command->get_map().end() || instance->second->get_flag() != sio::message::flag::flag_integer)
	{
		std::cout << "instance not int" << std::endl;
		return false;
	}
	if ((level = command->get_map().find("level")) == command->get_map().end() || level->second->get_flag() != sio::message::flag::flag_boolean)
	{
		std::cout << "level not a boolean" << std::endl;
		return false;
	}

	auto devices = BoxAPI::BWave::Instance().getController().getDevices();
	std::vector<std::shared_ptr<BoxAPI::Device>>::const_iterator it = std::find_if(devices.begin(), devices.end(), [&](std::shared_ptr<BoxAPI::Device> d)
	{
		return (d->getId() == moduleid);
	});
	if (it == devices.end())
	{
		std::cout << "Device not found" << std::endl;
		return false;
	}

	std::vector<std::shared_ptr<BoxAPI::ICommand>>::const_iterator iit = std::find_if((*it)->getCommands().begin(), (*it)->getCommands().end(), [&](std::shared_ptr<BoxAPI::ICommand> d)
	{
		return (d->getInstance() == instance->second->get_int() && d->getType() == ICommand::ZSwitchBinary);
	});
	if (iit == (*it)->getCommands().end())
	{
		std::cout << "Switch not found" << std::endl;
		return false;
	}

	std::shared_ptr<ICommand> cmd = (*iit);
	std::shared_ptr<Command::ZSwitchBinary> s = std::dynamic_pointer_cast<Command::ZSwitchBinary>(cmd);
	s->setSwitch(level->second->get_bool());
	return true;
}

bool BoxAPI::Network::CommandHandler::switchColor(int moduleid, std::shared_ptr<sio::message> command)
{
	std::cout << "Switching color in messageHandler.." << std::endl;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator instance;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator colorId;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator level;

	if ((instance = command->get_map().find("instance")) == command->get_map().end() || instance->second->get_flag() != sio::message::flag::flag_integer)
	{
		std::cout << "instance not int" << std::endl;
		return false;
	}
	if ((colorId = command->get_map().find("color_id")) == command->get_map().end() || colorId->second->get_flag() != sio::message::flag::flag_integer)
	{
		std::cout << "color_id not and int" << std::endl;
		return false;
	}
	if ((level = command->get_map().find("level")) == command->get_map().end() || level->second->get_flag() != sio::message::flag::flag_integer)
	{
		std::cout << "level not a int" << std::endl;
		return false;
	}

	auto devices = BoxAPI::BWave::Instance().getController().getDevices();
	std::vector<std::shared_ptr<BoxAPI::Device>>::const_iterator it = std::find_if(devices.begin(), devices.end(), [&](std::shared_ptr<BoxAPI::Device> d)
	{
		return (d->getId() == moduleid);
	});
	if (it == devices.end())
	{
		std::cout << "Device not found" << std::endl;
		return false;
	}

	std::vector<std::shared_ptr<BoxAPI::ICommand>>::const_iterator iit = std::find_if((*it)->getCommands().begin(), (*it)->getCommands().end(), [&](std::shared_ptr<BoxAPI::ICommand> d)
	{
		return (d->getInstance() == instance->second->get_int() && d->getType() == ICommand::ZSwitchColor
			&& std::dynamic_pointer_cast<Command::ZSwitchColor>(d)->getId() == colorId->second->get_int());
	});
	if (iit == (*it)->getCommands().end())
	{
		std::cout << "Switch color not found" << std::endl;
		return false;
	}

	std::shared_ptr<Command::ZSwitchColor> s = std::dynamic_pointer_cast<Command::ZSwitchColor>(*iit);
	s->setValue(level->second->get_int());
	return true;
}

bool BoxAPI::Network::CommandHandler::switchMultiLevel(int moduleid, std::shared_ptr<sio::message> command)
{
	std::cout << "Switching multilevel in messageHandler.." << std::endl;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator instance;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator level;

	if ((instance = command->get_map().find("instance")) == command->get_map().end() || instance->second->get_flag() != sio::message::flag::flag_integer)
	{
		std::cout << "instance not int" << std::endl;
		return false;
	}
	if ((level = command->get_map().find("level")) == command->get_map().end() || level->second->get_flag() != sio::message::flag::flag_integer)
	{
		std::cout << "level not a int" << std::endl;
		return false;
	}

	auto devices = BoxAPI::BWave::Instance().getController().getDevices();
	std::vector<std::shared_ptr<BoxAPI::Device>>::const_iterator it = std::find_if(devices.begin(), devices.end(), [&](std::shared_ptr<BoxAPI::Device> d)
	{
		return (d->getId() == moduleid);
	});
	if (it == devices.end())
	{
		std::cout << "Device not found" << std::endl;
		return false;
	}

	std::vector<std::shared_ptr<BoxAPI::ICommand>>::const_iterator iit = std::find_if((*it)->getCommands().begin(), (*it)->getCommands().end(), [&](std::shared_ptr<BoxAPI::ICommand> d)
	{
		return (d->getInstance() == instance->second->get_int() && d->getType() == ICommand::ZSwitchMultiLevel);
	});
	if (iit == (*it)->getCommands().end())
	{
		std::cout << "Switch multilevel not found" << std::endl;
		return false;
	}

	std::shared_ptr<ICommand> cmd = (*iit);
	std::shared_ptr<Command::ZSwitchMultiLevel> s = std::dynamic_pointer_cast<Command::ZSwitchMultiLevel>(cmd);
	s->setLevel(level->second->get_int());
	return true;
}