#include "stdafx.h"
#include "Device.h"
#include "ControllerEvent.h"
#include "BWave.h"
#include "ZSwitchBinary.h"
#include "ZCallback.h"

BoxAPI::Command::ZSwitchBinary::ZSwitchBinary(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id)
	: _zway(zway), _deviceId(node_id), _instanceId(instance_id)
{
	ZDataHolder data;
	ZWError r;

	std::cout << "Creating switchbinary [" << (int)node_id << "," << (int)instance_id << "]" << std::endl;
	
	zdata_acquire_lock(ZDataRoot(_zway));
	data = zway_find_device_instance_cc_data(_zway, _deviceId, _instanceId, BoxAPI::ICommand::CommandType::ZSwitchBinary, "level");
	r = zdata_add_callback_ex(data, &BoxAPI::Command::ZSwitchBinary::CBEvent, FALSE, static_cast<void *>(this));
	if (r != NoError)
	{
		zdata_release_lock(ZDataRoot(_zway));
		throw std::runtime_error("Fail to add data callback");
	}
	zdata_release_lock(ZDataRoot(_zway));
}

BoxAPI::Command::ZSwitchBinary::~ZSwitchBinary()
{
	ZDataHolder data;
	ZWError r;
	
	zdata_acquire_lock(ZDataRoot(_zway));
	data = zway_find_device_instance_cc_data(_zway, _deviceId, _instanceId, BoxAPI::ICommand::CommandType::ZSwitchBinary, "level");
	r = zdata_remove_callback_ex(data, &BoxAPI::Command::ZSwitchBinary::CBEvent, this);
	if (r != NoError)
	{
		zdata_release_lock(ZDataRoot(_zway));
		return;
	}
	zdata_release_lock(ZDataRoot(_zway));
}

void BoxAPI::Command::ZSwitchBinary::CBEvent(const ZDataRootObject root, ZWDataChangeType type, ZDataHolder data, void * arg)
{
	ZSwitchBinary					*s= static_cast<ZSwitchBinary *>(arg);
	BoxAPI::BWave					&b = BoxAPI::BWave::Instance();

	if (type != Updated)
		return;

	std::cout << "[EVENT] Switch Binary [" << (int)s->_deviceId << ":" << (int)s->_instanceId << "] value = " << s->getSwitch() << std::endl;

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

int BoxAPI::Command::ZSwitchBinary::getDeviceId() const
{
	return this->_deviceId;
}

BoxAPI::ICommand::CommandType BoxAPI::Command::ZSwitchBinary::getType() const
{
	return BoxAPI::ICommand::CommandType::ZSwitchBinary;
}

int BoxAPI::Command::ZSwitchBinary::getInstance() const
{
	return _instanceId;
}

void BoxAPI::Command::ZSwitchBinary::setSwitch(bool value)
{
	ZWBOOL	v = (value) ? 1 : 0;
	ZWError	e;
	//ZCallback	callback;
	if ((e = zway_cc_switch_binary_set(_zway, _deviceId, _instanceId, v, NULL, NULL, NULL)) != 0)
	{
		std::cout << "fail to set switch (" << (int)e << ")" << std::endl;
		return;
	}
	/*if (callback.wait())
		std::cout << "switch set" << std::endl;
	else
		std::cout << "switch not set" << std::endl;*/
}

bool BoxAPI::Command::ZSwitchBinary::getSwitch() const
{
	ZWError		e;
	ZDataHolder data;
	bool		level;
	ZWBOOL		value;
	ZCallback	callback;

	/*if ((e = zway_cc_switch_binary_get(_zway, _deviceId, _instanceId, &ZCallback::successCallback, &ZCallback::failureCallback, &callback) != 0))
	{
		std::cout << "fail to get switch (" << (int)e << ")" << std::endl;
		return false;
	}
	if (callback.wait())
		std::cout << "switch get" << std::endl;
	else
	{
		std::cout << "switch not get" << std::endl;
		return false;
	}*/
	zdata_acquire_lock(ZDataRoot(_zway));
	data = zway_find_device_instance_cc_data(_zway, _deviceId, _instanceId, BoxAPI::ICommand::CommandType::ZSwitchBinary, "level");
	zdata_get_boolean(data, &value);
	switch (value) {
	case 0:
		level = false;
		break;
	case 1:
		level = true;
		break;
	}
	zdata_release_lock(ZDataRoot(_zway));
	return level;
}

bool BoxAPI::Command::ZSwitchBinary::isFailed() const
{
	ZCallback	callback;
	ZWError		e;
	ZDataHolder data;
	bool		level;
	ZWBOOL		value;

	if ((e = zway_fc_is_failed_node(_zway, _deviceId, ZCallback::successCallback, ZCallback::failureCallback, &callback)) != NoError)
		return true;
	if (!callback.wait())
		return true;
	zdata_acquire_lock(ZDataRoot(_zway));
	data = zway_find_device_data(_zway, _deviceId, "isFailed");
	zdata_get_boolean(data, &value);
	switch (value) {
	case 0:
		level = false;
		break;
	case 1:
		level = true;
		break;
	}
	zdata_release_lock(ZDataRoot(_zway));
	return level;
}

