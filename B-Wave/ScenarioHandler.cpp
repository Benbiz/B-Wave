#include "stdafx.h"
#include "Device.h"
#include "BWave.h"
#include "Command.h"
#include "ScenarioHandler.h"

BoxAPI::Network::ScenarioHandler::ScenarioHandler()
{
	_triggers["sensormultilevel"] = &BoxAPI::Network::ScenarioHandler::findSensorMultiLevelTrigger;
	_triggers["sensorbinary"] = &BoxAPI::Network::ScenarioHandler::findSensorBinaryTrigger;
	_actions["switch"] = &BoxAPI::Network::ScenarioHandler::findSwitchBinaryAction;
	_actions["switchcolor"] = &BoxAPI::Network::ScenarioHandler::findSwitchColorAction;
	_actions["switchmultilevel"] = &BoxAPI::Network::ScenarioHandler::findSwitchMultiLevelAction;
}

BoxAPI::Network::ScenarioHandler::~ScenarioHandler()
{
}

void		BoxAPI::Network::ScenarioHandler::onNewScenario(sio::event &e)
{
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	triggermess;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	idmess;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	logicmess;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	effects;
	std::vector<t_action*>											actions;
	std::string														expr;
	TriggerTree														*t;
	int																id;

	std::cout << "[NET] onNewScenario" << std::endl;
	if (e.get_message()->get_flag() != sio::message::flag::flag_object)
	{
		std::cout << "Message not an object" << std::endl;
		return;
	}
	if ((idmess = e.get_message()->get_map().find("id")) == e.get_message()->get_map().end() || idmess->second->get_flag() != sio::message::flag::flag_integer)
	{
		std::cout << "triggers not an array" << std::endl;
		return;
	}
	id = idmess->second->get_int();
	if ((triggermess = e.get_message()->get_map().find("triggers")) == e.get_message()->get_map().end() || triggermess->second->get_flag() != sio::message::flag::flag_array)
	{
		std::cout << "triggers not an array" << std::endl;
		return;
	}
	std::cout << "DEBUG" << std::endl;
	if (!createTriggers(triggermess->second))
	{
		std::cout << "Unable to get triggers" << std::endl;
		return;
	}
	std::cout << "DEBUG" << std::endl;
	if ((logicmess = e.get_message()->get_map().find("logic")) == e.get_message()->get_map().end() || logicmess->second->get_flag() != sio::message::flag::flag_object)
	{
		std::cout << "logic not a object" << std::endl;
		return;
	}
	std::cout << "DEBUG" << std::endl;
	if ((t = getLogical(logicmess->second)) == nullptr)
	{
		std::cout << "Unable to get triggers" << std::endl;
		return;
	}
	std::cout << "DEBUG" << std::endl;
	if ((effects = e.get_message()->get_map().find("effects")) == e.get_message()->get_map().end() || effects->second->get_flag() != sio::message::flag::flag_array)
	{
		std::cout << "effects not an arry" << std::endl;
		return;
	}
	std::cout << "DEBUG" << std::endl;
	if (!createActions(effects->second, actions))
	{
		std::cout << "Unable to get effects" << std::endl;
		return;
	}
	std::cout << "DEBUG" << std::endl;
	BoxAPI::BWave::Instance().getScenarioMotor().createScenario(id, std::to_string(id), expr, actions, t);
	std::cout << "Scenario expr: \"" << expr << "\"" << std::endl;
}

bool		BoxAPI::Network::ScenarioHandler::createTriggers(sio::message::ptr mess)
{
	std::vector<sio::message::ptr>									&list = mess->get_vector();
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	id;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	module;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	moduleid;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	cmd;
	int																count = 0;

	for (sio::message::ptr m : list)
	{
		std::cout << "DEBUG.1" << std::endl;
		if (m->get_flag() != sio::message::flag::flag_object)
		{
			std::cout << "A trigger is not an object: Ignored" << std::endl;
			continue;
		}
		std::cout << "DEBUG.1" << std::endl;
		if ((id = m->get_map().find("id")) == m->get_map().end() || id->second->get_flag() != sio::message::flag::flag_integer)
		{
			std::cout << "id of trigger not an int" << std::endl;
			continue;
		}
		std::cout << "DEBUG.1" << std::endl;
		if ((module = m->get_map().find("module")) == m->get_map().end() || module->second->get_flag() != sio::message::flag::flag_object)
		{
			std::cout << "module not an object" << std::endl;
			continue;
		}
		std::cout << "DEBUG.1" << std::endl;
		if ((moduleid = module->second->get_map().find("id")) == module->second->get_map().end() || moduleid->second->get_flag() != sio::message::flag::flag_integer)
		{
			std::cout << "module id not an int" << std::endl;
			continue;
		}
		std::cout << "DEBUG.1" << std::endl;
		for (std::pair<std::string, bool(BoxAPI::Network::ScenarioHandler::*)(sio::message::ptr trigger, int uid, int moduleid)> p : _triggers)
		{
			std::cout << "DEBUG.1.1" << std::endl;
			if ((cmd = module->second->get_map().find(p.first)) != module->second->get_map().end() && cmd->second->get_flag() == sio::message::flag::flag_object)
			{
				std::cout << "DEBUG.1.1.1" << std::endl;
				if (!(this->*(p.second))(cmd->second, id->second->get_int(), moduleid->second->get_int()))
					std::cout << "Trigger not defined" << std::endl;
				else
					count++;
			}
		}
	}
	std::cout << "DEBUG.1" << std::endl;
	if (count == 0)
	{
		std::cout << "Error: No triggers found" << std::endl;
		return false;
	}
	return true;
}

bool BoxAPI::Network::ScenarioHandler::createActions(sio::message::ptr mess, std::vector<t_action*> &actions)
{
	std::vector<sio::message::ptr>									&list = mess->get_vector();
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	id;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	module;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	moduleid;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	cmd;
	int																count = 0;

	for (sio::message::ptr m : list)
	{
		if (m->get_flag() != sio::message::flag::flag_object)
		{
			std::cout << "A trigger is not an object: Ignored" << std::endl;
			continue;
		}
		if ((id = m->get_map().find("id")) == m->get_map().end() || id->second->get_flag() != sio::message::flag::flag_integer)
		{
			std::cout << "id of trigger not an int" << std::endl;
			continue;
		}
		if ((module = m->get_map().find("module")) == m->get_map().end() || module->second->get_flag() != sio::message::flag::flag_object)
		{
			std::cout << "module not an object" << std::endl;
			continue;
		}
		if ((moduleid = module->second->get_map().find("id")) == module->second->get_map().end() || moduleid->second->get_flag() != sio::message::flag::flag_integer)
		{
			std::cout << "module id not an int" << std::endl;
			continue;
		}
		for (std::pair<std::string, bool(BoxAPI::Network::ScenarioHandler::*)(sio::message::ptr trigger, int uid, int moduleid, std::vector<t_action*> &actions)> p : _actions)
		{
			if ((cmd = module->second->get_map().find(p.first)) != module->second->get_map().end() && cmd->second->get_flag() == sio::message::flag::flag_object)
			{
				if (!(this->*(p.second))(cmd->second, id->second->get_int(), moduleid->second->get_int(), actions))
					std::cout << "Actions not defined" << std::endl;
				else
					count++;
			}
		}
	}
	if (count == 0)
	{
		std::cout << "Error: No triggers found" << std::endl;
		return false;
	}
	return true;
}

bool BoxAPI::Network::ScenarioHandler::findSwitchBinaryAction(sio::message::ptr trigger, int uid, int moduleid, std::vector<t_action*>& actions)
{
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	value;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	instance;

	if ((instance = trigger->get_map().find("instance")) == trigger->get_map().end() || instance->second->get_flag() != sio::message::flag::flag_integer)
	{
		std::cout << "instance not an int or not found" << std::endl;
		return false;
	}
	if ((value = trigger->get_map().find("value")) == trigger->get_map().end() || value->second->get_flag() != sio::message::flag::flag_boolean)
	{
		std::cout << "value not a bool or not found" << std::endl;
		return false;
	}
	std::shared_ptr<BoxAPI::Device>					dev;

	dev = BoxAPI::BWave::Instance().getController().getDevice(moduleid);
	auto cc = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
		[&](std::shared_ptr<BoxAPI::ICommand> o)
	{
		return (o->getInstance() == instance->second->get_int() && o->getType() == BoxAPI::ICommand::ZSwitchBinary);
	});
	if (cc == dev->getCommands().end())
	{
		std::cout << "Trigger " << uid << " not found in the system" << std::endl;
		return false;
	}
	t_action *a = BoxAPI::BWave::Instance().getScenarioMotor().createAction(uid, moduleid, instance->second->get_int(), -1, BoxAPI::ICommand::ZSwitchBinary, false, 0, value->second->get_bool(), 0, "Switch", "", *cc);
	actions.push_back(a);
	return true;
}

bool BoxAPI::Network::ScenarioHandler::findSwitchMultiLevelAction(sio::message::ptr trigger, int uid, int moduleid, std::vector<t_action*>& actions)
{
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	value;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	instance;

	if ((instance = trigger->get_map().find("instance")) == trigger->get_map().end() || instance->second->get_flag() != sio::message::flag::flag_integer)
	{
		std::cout << "instance not an int or not found" << std::endl;
		return false;
	}
	if ((value = trigger->get_map().find("value")) == trigger->get_map().end() || value->second->get_flag() != sio::message::flag::flag_integer)
	{
		std::cout << "value not an int or not found" << std::endl;
		return false;
	}
	std::shared_ptr<BoxAPI::Device>					dev;

	dev = BoxAPI::BWave::Instance().getController().getDevice(moduleid);
	auto cc = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
		[&](std::shared_ptr<BoxAPI::ICommand> o)
	{
		return (o->getInstance() == instance->second->get_int() && o->getType() == BoxAPI::ICommand::ZSwitchMultiLevel);
	});
	if (cc == dev->getCommands().end())
	{
		std::cout << "Trigger " << uid << " not found in the system" << std::endl;
		return false;
	}
	t_action *a = BoxAPI::BWave::Instance().getScenarioMotor().createAction(uid, moduleid, instance->second->get_int(), -1, BoxAPI::ICommand::ZSwitchMultiLevel, false, 0, false,  value->second->get_int(), "SwitchMultiLevel", "", *cc);
	actions.push_back(a);
	return true;
}

bool BoxAPI::Network::ScenarioHandler::findSwitchColorAction(sio::message::ptr trigger, int uid, int moduleid, std::vector<t_action*>& actions)
{
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	value;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	instance;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	color_id;

	if ((instance = trigger->get_map().find("instance")) == trigger->get_map().end() || instance->second->get_flag() != sio::message::flag::flag_integer)
	{
		std::cout << "instance not an int or not found" << std::endl;
		return false;
	}
	if ((color_id = trigger->get_map().find("color_id")) == trigger->get_map().end() || color_id->second->get_flag() != sio::message::flag::flag_integer)
	{
		std::cout << "color_id not an int or not found" << std::endl;
		return false;
	}
	if ((value = trigger->get_map().find("value")) == trigger->get_map().end() || value->second->get_flag() != sio::message::flag::flag_integer)
	{
		std::cout << "value not an int or not found" << std::endl;
		return false;
	}
	std::shared_ptr<BoxAPI::Device>					dev;

	dev = BoxAPI::BWave::Instance().getController().getDevice(moduleid);
	auto cc = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
		[&](std::shared_ptr<BoxAPI::ICommand> o)
	{
		return (o->getInstance() == instance->second->get_int() && o->getType() == BoxAPI::ICommand::ZSwitchColor && std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(o)->getId() == color_id->second->get_int());
	});
	if (cc == dev->getCommands().end())
	{
		std::cout << "Trigger " << uid << " not found in the system" << std::endl;
		return false;
	}
	t_action *a = BoxAPI::BWave::Instance().getScenarioMotor().createAction(uid, moduleid, instance->second->get_int(), color_id->second->get_int(), BoxAPI::ICommand::ZSwitchColor, false, 0, false, value->second->get_int(), "SwitchColor", "", *cc);
	actions.push_back(a);
	return true;
}

bool BoxAPI::Network::ScenarioHandler::findSensorMultiLevelTrigger(sio::message::ptr trigger, int uid, int moduleid)
{
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	id;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	instance;

	if ((id = trigger->get_map().find("type_id")) == id->second->get_map().end() || id->second->get_flag() != sio::message::flag::flag_integer)
	{
		std::cout << "type_id not an int or not found" << std::endl;
		return false;
	}

	if ((instance = trigger->get_map().find("instance")) == instance->second->get_map().end() || instance->second->get_flag() != sio::message::flag::flag_integer)
	{
		std::cout << "instance not an int or not found" << std::endl;
		return false;
	}
	std::shared_ptr<BoxAPI::Device>					dev;

	dev = BoxAPI::BWave::Instance().getController().getDevice(moduleid);
	auto cc = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
		[&](std::shared_ptr<BoxAPI::ICommand> o)
	{
		return (o->getInstance() == instance->second->get_int() && o->getType() == BoxAPI::ICommand::ZSensorMultiLevel && std::dynamic_pointer_cast<BoxAPI::Command::ZSensorMultiLevel>(o)->getId() == id->second->get_int());
	});
	if (cc == dev->getCommands().end())
	{
		std::cout << "Trigger " << uid << " not found in the system" << std::endl;
		return false;
	}
	BoxAPI::BWave::Instance().getScenarioMotor().createTrigger(uid, moduleid, instance->second->get_int(), id->second->get_int(), BoxAPI::ICommand::ZSensorMultiLevel, "SensorMultiLevel", "Capteur", *cc);
	return true;
}

bool BoxAPI::Network::ScenarioHandler::findSensorBinaryTrigger(sio::message::ptr trigger, int uid, int moduleid)
{
	std::cout << "DEBUG.2" << std::endl;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	id;
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	instance;


	// not in database, going to take the first found
	/*if ((id = trigger->get_map().find("type_id")) == id->second->get_map().end() || id->second->get_flag() != sio::message::flag::flag_integer)
	{
		std::cout << "type_id not an int or not found" << std::endl;
		return false;
	}*/
	std::cout << "DEBUG.2" << std::endl;
	if ((instance = trigger->get_map().find("instance")) == trigger->get_map().end() || instance->second->get_flag() != sio::message::flag::flag_integer)
	{
		std::cout << "instance not an int or not found" << std::endl;
		return false;
	}
	std::shared_ptr<BoxAPI::Device>					dev;
	std::cout << "DEBUG.2" << std::endl;
	dev = BoxAPI::BWave::Instance().getController().getDevice(moduleid);
	auto cc = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
		[&](std::shared_ptr<BoxAPI::ICommand> o)
	{
		return (o->getInstance() == instance->second->get_int() && o->getType() == BoxAPI::ICommand::ZSensorBinary);
	});
	std::cout << "DEBUG.2" << std::endl;
	if (cc == dev->getCommands().end())
	{
		std::cout << "Trigger " << uid << " not found in the system" << std::endl;
		return false;
	}
	std::cout << "DEBUG.2" << std::endl;
	BoxAPI::BWave::Instance().getScenarioMotor().createTrigger(uid, moduleid, instance->second->get_int(), -1, BoxAPI::ICommand::ZSensorBinary, "SensorBinary", "Capteur", *cc);
	return true;
}

TriggerTree		*BoxAPI::Network::ScenarioHandler::getLogical(sio::message::ptr mess)
{
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	logic;
	sio::message::ptr												left;
	sio::message::ptr												right;
	TriggerTree														*lright;
	TriggerTree														*lleft;
	TriggerTree														*ptr;

	if ((logic = mess->get_map().find("and")) != mess->get_map().end() && logic->second->get_flag() == sio::message::flag::flag_array
		&& logic->second->get_vector().size() == 2)
	{
		left = logic->second->get_vector()[0];
		right = logic->second->get_vector()[1];
		if (left->get_flag() != sio::message::flag::flag_object || right->get_flag() != sio::message::flag::flag_object)
			return nullptr;
		lleft = getLogical(left);
		lright = getLogical(right);
		if (lleft == nullptr || lright == nullptr)
			return nullptr;
		ptr = new TriggerTree(lleft, '&', lright);
	}
	else if ((logic = mess->get_map().find("or")) != mess->get_map().end() && logic->second->get_flag() == sio::message::flag::flag_array
		&& logic->second->get_vector().size() == 2)
	{
		left = logic->second->get_vector()[0];
		right = logic->second->get_vector()[1];
		if (left->get_flag() != sio::message::flag::flag_object || right->get_flag() != sio::message::flag::flag_object)
			return nullptr;
		lleft = getLogical(left);
		lright = getLogical(right);
		if (lleft == nullptr || lright == nullptr)
			return nullptr;
		ptr = new TriggerTree(lleft, '|', lright);
	}
	else if ((logic = mess->get_map().find("==")) != mess->get_map().end() && logic->second->get_flag() == sio::message::flag::flag_array
		&& logic->second->get_vector().size() == 2)
	{
		left = logic->second->get_vector()[0];
		right = logic->second->get_vector()[1];
		ptr = getCondition(left, '=', right);
		if (ptr == nullptr)
			return nullptr;
	}
	else if ((logic = mess->get_map().find("<")) != mess->get_map().end() && logic->second->get_flag() == sio::message::flag::flag_array
		&& logic->second->get_vector().size() == 2)
	{
		left = logic->second->get_vector()[0];
		right = logic->second->get_vector()[1];
		ptr = getCondition(left, '<', right);
		if (ptr == nullptr)
			return nullptr;
	}
	else if ((logic = mess->get_map().find(">")) != mess->get_map().end() && logic->second->get_flag() == sio::message::flag::flag_array
		&& logic->second->get_vector().size() == 2)
	{
		left = logic->second->get_vector()[0];
		right = logic->second->get_vector()[1];
		ptr = getCondition(left, '>', right);
		if (ptr == nullptr)
			return nullptr;
	}
	else if ((logic = mess->get_map().find("<=")) != mess->get_map().end() && logic->second->get_flag() == sio::message::flag::flag_array
		&& logic->second->get_vector().size() == 2)
	{
		left = logic->second->get_vector()[0];
		right = logic->second->get_vector()[1];
		ptr = getCondition(left, '-', right);
		if (ptr == nullptr)
			return nullptr;
	}
	else if ((logic = mess->get_map().find(">=")) != mess->get_map().end() && logic->second->get_flag() == sio::message::flag::flag_array
		&& logic->second->get_vector().size() == 2)
	{
		left = logic->second->get_vector()[0];
		right = logic->second->get_vector()[1];
		ptr = getCondition(left, '+', right);
		if (ptr == nullptr)
			return nullptr;
	}
	else if ((logic = mess->get_map().find("!=")) != mess->get_map().end() && logic->second->get_flag() == sio::message::flag::flag_array
		&& logic->second->get_vector().size() == 2)
	{
		left = logic->second->get_vector()[0];
		right = logic->second->get_vector()[1];
		ptr = getCondition(left, '.', right);
		if (ptr == nullptr)
			return nullptr;
	}
	else
		return nullptr;
	return ptr;
}

TriggerTree		*BoxAPI::Network::ScenarioHandler::getCondition(sio::message::ptr left, char cond, sio::message::ptr right)
{
	std::map<std::string, std::shared_ptr<sio::message>>::iterator	ref;
	std::string														refstr;
	std::vector<std::string>										elems;
	int																triggerId;
	std::shared_ptr<BoxAPI::ICommand>								trigger = nullptr;
	t_condition														*condition = nullptr;

	if (left->get_flag() != sio::message::flag::flag_object)
	{
		std::cout << "Left operand avec condition is not an object" << std::endl;
		return nullptr;
	}
	if ((ref = left->get_map().find("$ref")) == left->get_map().end() || ref->second->get_flag() != sio::message::flag::flag_string)
	{
		std::cout << "$ref not a string" << std::endl;
		return nullptr;
	}
	refstr = ref->second->get_string();
	std::stringstream ss;
	ss.str(refstr);
	std::string item;
	while (std::getline(ss, item, '.')) {
		elems.push_back(item);
	}
	if (elems[0] != "triggers")
	{
		std::cout << "$ref doest not refer to a trigger" << std::endl;
		return nullptr;
	}
	triggerId = std::stoi(elems[1]);
	for (std::pair<double, std::shared_ptr<BoxAPI::ICommand>> &c : BoxAPI::BWave::Instance().getScenarioMotor().getPairIdDevice())
	{
		if (c.first == triggerId)
		{
			trigger = c.second;
			break;
		}
	}
	if (trigger == nullptr)
	{
		std::cout << "Ref to unfound trigger" << std::endl;
		return nullptr;
	}
	if (right->get_flag() == sio::message::flag::flag_integer)
		condition = BoxAPI::BWave::Instance().getScenarioMotor().createCondition(right->get_int(), 0, false, cond, '!', '!');
	else if (right->get_flag() == sio::message::flag::flag_boolean)
		condition = BoxAPI::BWave::Instance().getScenarioMotor().createCondition(0, 0, right->get_bool(), '!', '!', cond);
	else
	{
		std::cout << "Unsupported comparaison operand" << std::endl;
		return nullptr;
	}
	std::pair<std::shared_ptr<BoxAPI::ICommand>, t_condition*> pair(trigger, condition);
	return new TriggerTree(pair);
}