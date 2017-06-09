#include "stdafx.h"
#include "Device.h"
#include "ControllerEvent.h"
#include "BWave.h"
#include "ZSwitchMultiLevel.h"
#include "ZCallback.h"


BoxAPI::Command::ZSwitchMultiLevel::ZSwitchMultiLevel(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id)
	: _zway(zway), _deviceId(node_id), _instanceId(instance_id)
{
	ZDataHolder data;
	ZWError r;

	std::cout << "Creating switchmutlilevel [" << (int)node_id << "," << (int)instance_id << "]" << std::endl;

	zdata_acquire_lock(ZDataRoot(_zway));
	data = zway_find_device_instance_cc_data(_zway, _deviceId, _instanceId, BoxAPI::ICommand::CommandType::ZSwitchMultiLevel, "level");
	r = zdata_add_callback_ex(data, &BoxAPI::Command::ZSwitchMultiLevel::CBEvent, FALSE, static_cast<void *>(this));
	if (r != NoError)
	{
		zdata_release_lock(ZDataRoot(_zway));
		throw std::runtime_error("Fail to add data callback");
	}
	zdata_release_lock(ZDataRoot(_zway));
}
BoxAPI::Command::ZSwitchMultiLevel::~ZSwitchMultiLevel()
{
	ZDataHolder data;
	ZWError r;

	zdata_acquire_lock(ZDataRoot(_zway));
	data = zway_find_device_instance_cc_data(_zway, _deviceId, _instanceId, BoxAPI::ICommand::CommandType::ZSwitchMultiLevel, "level");
	r = zdata_remove_callback_ex(data, &BoxAPI::Command::ZSwitchMultiLevel::CBEvent, this);
	if (r != NoError)
	{
		zdata_release_lock(ZDataRoot(_zway));
		return;
	}
	zdata_release_lock(ZDataRoot(_zway));
}

void BoxAPI::Command::ZSwitchMultiLevel::CBEvent(const ZDataRootObject root, ZWDataChangeType type, ZDataHolder data, void * arg)
{
	ZSwitchMultiLevel					*s = static_cast<ZSwitchMultiLevel *>(arg);
	BoxAPI::BWave					&b = BoxAPI::BWave::Instance();

	if (type != Updated)
		return;

	std::cout << "[EVENT] Switch MultiLevel [" << (int)s->_deviceId << ":" << (int)s->_instanceId << "] value = " << s->getLevel() << std::endl;

	std::shared_ptr<BoxAPI::Device> dev = b.getController().getDevice(s->_deviceId);
	if (dev == nullptr)
	{
		std::cout << "[EVENT] Device not in list" << std::endl;
		return;
	}
	auto cc = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
		[&](std::shared_ptr<BoxAPI::ICommand> o)
	{
		return (o.get() == s);
	});
	if (cc == dev->getCommands().end())
	{
		std::cout << "[EVENT] Command not in list" << std::endl;
		return;
	}
	BoxAPI::ControllerEvent::EventDispatcher::Instance().dispatchEvent(std::make_shared<BoxAPI::ControllerEvent::Data::Command>(BoxAPI::ControllerEvent::Data::EventType::Update, std::dynamic_pointer_cast<ICommand>(*cc)));
}

void BoxAPI::Command::ZSwitchMultiLevel::setLevel(int level)
{
	ZWError	e;
	std::cout << "seting level..." << std::endl;
	if ((e = zway_cc_switch_multilevel_set(_zway, _deviceId, _instanceId, level, 0, NULL, NULL, NULL)) != 0)
	{
		std::cout << "fail to set switch multilevel (" << (int)e << ")" << std::endl;
		return;
	}
	std::cout << "seting level done !" << std::endl;

}

int BoxAPI::Command::ZSwitchMultiLevel::getLevel() const
{
	ZWError		e;
	ZDataHolder data;
	int			level;
	ZCallback	callback;

	zdata_acquire_lock(ZDataRoot(_zway));
	data = zway_find_device_instance_cc_data(_zway, _deviceId, _instanceId, BoxAPI::ICommand::CommandType::ZSwitchMultiLevel, "level");
	zdata_get_integer(data, &level);
	zdata_release_lock(ZDataRoot(_zway));
	return level;
}

int BoxAPI::Command::ZSwitchMultiLevel::getDeviceId() const
{
	return this->_deviceId;
}

BoxAPI::ICommand::CommandType BoxAPI::Command::ZSwitchMultiLevel::getType() const
{
	return BoxAPI::ICommand::CommandType::ZSwitchMultiLevel;
}

int BoxAPI::Command::ZSwitchMultiLevel::getInstance() const
{
	return _instanceId;
}
