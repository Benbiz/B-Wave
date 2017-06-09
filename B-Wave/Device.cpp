#include "stdafx.h"
#include "Command.h"
#include "DeviceRecord.h"
#include "Device.h"

std::map<int, bool(BoxAPI::Device::*)(ZWBYTE)> BoxAPI::Device::_createCommandMap = std::map<int, bool(BoxAPI::Device::*)(ZWBYTE)>();

BoxAPI::Device::Device(ZWay zway, ZWBYTE deviceId)
	: _zway(zway), _id(deviceId), _rawRecords(NULL)
{
	bool						instancezero = false;
	ZWInstancesList			ilist;
	ZWCommandClassesList	clist;

	std::cout << "Creating device [" << (int)_id << "]" << std::endl;

	if (_createCommandMap.empty())
	{
		_createCommandMap[BoxAPI::ICommand::CommandType::ZSwitchBinary] = &BoxAPI::Device::createGeneric<BoxAPI::Command::ZSwitchBinary>;
		_createCommandMap[BoxAPI::ICommand::CommandType::ZSwitchMultiLevel] = &BoxAPI::Device::createGeneric<BoxAPI::Command::ZSwitchMultiLevel>;
		_createCommandMap[BoxAPI::ICommand::CommandType::ZSwitchColor] = &BoxAPI::Device::createGenericWithId<BoxAPI::ICommand::CommandType::ZSwitchColor, BoxAPI::Command::ZSwitchColor>;
		_createCommandMap[BoxAPI::ICommand::CommandType::ZSensorBinary] = &BoxAPI::Device::createGenericWithId<BoxAPI::ICommand::CommandType::ZSensorBinary, BoxAPI::Command::ZSensorBinary>;
		_createCommandMap[BoxAPI::ICommand::CommandType::ZSensorMultiLevel] = &BoxAPI::Device::createGenericWithId<BoxAPI::ICommand::CommandType::ZSensorMultiLevel, BoxAPI::Command::ZSensorMultiLevel>;
	}
	/*zway_device_awake_queue(_zway, _id);
	if ((ilist = zway_instances_list(_zway, _id)) == NULL)
	{
		std::cout << "Unable to get instance list" << std::endl;
		return;
	}
	for (int n = 0; !instancezero || ilist[n]; n++)
	{
		if (ilist[n] == 0)
			instancezero = true;
		else
		{
			if (ilist[n] != ilist[n - 1] + 1)
				break;
		}
		if ((clist = zway_command_classes_list(_zway, _id, ilist[n])) == NULL)
		{
			std::cout << "Unable to get commandclass list (" << (int)ilist[n] << ")" << std::endl;
			continue;
		}
		for (int j = 0; clist[j]; j++)
			addCommand(static_cast<BoxAPI::ICommand::CommandType>(clist[j]), ilist[n]); // add command
		zway_command_classes_list_free(clist);
	}
	zway_instances_list_free(ilist);*/
}

BoxAPI::Device::~Device()
{
	std::cout << "Removing Device " << (int)_id << std::endl;
	std::cout << "Commands..." << std::endl;
	_commands.clear();
	std::cout << "Records..." << std::endl;
	_records.clear();
	if (_rawRecords != NULL)
		zway_device_guess_free(_rawRecords);
}

int BoxAPI::Device::getId() const
{
	return _id;
}

const std::vector<std::shared_ptr<BoxAPI::ICommand>>& BoxAPI::Device::getCommands() const
{
	return _commands;
}

const std::vector<BoxAPI::DeviceRecord>	&BoxAPI::Device::getDeviceRecord()
{
	if (_rawRecords == NULL)
	{
		_rawRecords = zway_device_guess(_zway, _id);
		for (int i = 0; _rawRecords[i] != NULL; i++)
		{
			DeviceRecord rec(_rawRecords[i]);
			_records.push_back(rec);
		}
	}
	return _records;
}

bool									BoxAPI::Device::setDeviceRecord(const std::string &file)
{
	ZWError	e;

	if (_rawRecords != NULL)
		zway_device_guess_free(_rawRecords);
	e = zway_device_load_xml(_zway, this->_id, file.c_str());
	_rawRecords = zway_device_guess(_zway, _id);
	_records.clear();
	for (int i = 0; _rawRecords[i] != NULL; i++)
	{
		DeviceRecord rec(_rawRecords[i]);
		_records.push_back(rec);
	}
	if (e != NoError)
		return false;
	return true;
}

bool BoxAPI::Device::isInterviewDone() const
{
	if (zway_device_is_interview_done(_zway, _id) == TRUE)
		return true;
	return false;
}

bool BoxAPI::Device::addCommand(BoxAPI::ICommand::CommandType type, ZWBYTE instance)
{
	std::map<int, bool(BoxAPI::Device::*)(ZWBYTE)>::const_iterator it = _createCommandMap.find(type);

	if (it == _createCommandMap.end())
		return false;
	if (!((this->*(it->second))(instance)))
		return false;
	return true;
}

bool BoxAPI::Device::addCommand(ZWBYTE type, ZWBYTE instance)
{
	std::map<int, bool(BoxAPI::Device::*)(ZWBYTE)>::const_iterator it = _createCommandMap.find(type);
	if (it == _createCommandMap.end())
		return false;
	if (!((this->*(it->second))(instance)))
		return false;
	return true;
}

bool BoxAPI::Device::removeCommand(BoxAPI::ICommand::CommandType type)
{
	auto it = std::find_if(_commands.begin(), _commands.end(),
		[&](std::shared_ptr<ICommand> o) { return (o->getType() == type); });
	if (it == _commands.end())
		return false;
	_commands.erase(std::remove_if(_commands.begin(), _commands.end(),
			[&](std::shared_ptr<ICommand> o) { return (o->getType() == type); }),
		_commands.end());
	return true;
}

bool BoxAPI::Device::removeCommand(ZWBYTE type, ZWBYTE instance)
{
	auto it = std::find_if(_commands.begin(), _commands.end(),
		[&](std::shared_ptr<ICommand> o) { return (o->getType() == type); });
	if (it == _commands.end())
		return false;
	_commands.erase(std::remove_if(_commands.begin(), _commands.end(),
		[&](std::shared_ptr<ICommand> o) { return (o->getType() == type); }),
		_commands.end());
	return true;
}

void BoxAPI::Device::CBInterviewCCDone()
{
	if (isInterviewDone())
		std::cout << "Interview done !!! [" << (int)_id << "]" << std::endl;
	else
		std::cout << "Interview not done !!! [" << (int)_id << "]" << std::endl;
}
