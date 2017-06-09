#include "stdafx.h"
#include "Device.h"
#include "ControllerEvent.h"
#include "BWave.h"
#include "ZSensorBinary.h"
#include "ZCallback.h"

BoxAPI::Command::ZSensorBinary::ZSensorBinary(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int id)
	: _zway(zway), _deviceId(node_id), _instanceId(instance_id), _id(id), _path(std::to_string(id) + ".level")
{
	ZDataHolder data;
	ZWError r;

	std::cout << "Creating sensorbinary [" << (int)node_id << "," << (int)instance_id << "," << id << "]" << std::endl;
	zdata_acquire_lock(ZDataRoot(_zway));
	data = zway_find_device_instance_cc_data(_zway, _deviceId, _instanceId, BoxAPI::ICommand::CommandType::ZSensorBinary, _path.c_str());
	r = zdata_add_callback_ex(data, &BoxAPI::Command::ZSensorBinary::CBEvent, FALSE, static_cast<void *>(this));
	if (r != NoError)
	{
		zdata_release_lock(ZDataRoot(_zway));
		throw std::runtime_error("Fail to add data callback");
	}
	zdata_release_lock(ZDataRoot(_zway));
}

BoxAPI::Command::ZSensorBinary::~ZSensorBinary()
{
	ZDataHolder data;
	ZWError r;

	zdata_acquire_lock(ZDataRoot(_zway));
	data = zway_find_device_instance_cc_data(_zway, _deviceId, _instanceId, BoxAPI::ICommand::CommandType::ZSensorBinary, _path.c_str());
	r = zdata_remove_callback_ex(data, &BoxAPI::Command::ZSensorBinary::CBEvent, this);
	if (r != NoError)
	{
		zdata_release_lock(ZDataRoot(_zway));
		return;
	}
	zdata_release_lock(ZDataRoot(_zway));
}

int BoxAPI::Command::ZSensorBinary::getDeviceId() const
{
	return this->_deviceId;
}

BoxAPI::ICommand::CommandType BoxAPI::Command::ZSensorBinary::getType() const
{
	return BoxAPI::ICommand::CommandType::ZSensorBinary;
}

int BoxAPI::Command::ZSensorBinary::getInstance() const
{
	return _instanceId;
}

bool	BoxAPI::Command::ZSensorBinary::getValue() const
{
	//ZWError		e;
	ZDataHolder data;
	bool		level;
	ZWBOOL		value;
	ZCallback	callback;

	/*if ((e = zway_cc_switch_binary_get(_zway, _deviceId, _instanceId, &ZCallback::successCallback, &ZCallback::failureCallback, &callback) != 0))
		std::cout << "fail to get sensorbinary (" << (int)e << ")" << std::endl;
	if (callback.wait())
		std::cout << "sensorbinary get" << std::endl;
	else
	{
		std::cout << "sensorbinary not get" << std::endl;
		return false;
	}*/
	zdata_acquire_lock(ZDataRoot(_zway));
	data = zway_find_device_instance_cc_data(_zway, _deviceId, _instanceId, BoxAPI::ICommand::CommandType::ZSensorBinary, _path.c_str());
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

int BoxAPI::Command::ZSensorBinary::getId() const
{
	return _id;
}

void BoxAPI::Command::ZSensorBinary::CBEvent(const ZDataRootObject root, ZWDataChangeType type, ZDataHolder data, void * arg)
{
	ZSensorBinary	*s = static_cast<ZSensorBinary *>(arg);
	BoxAPI::BWave					&b = BoxAPI::BWave::Instance();

	if (type != Updated)
		return;

	std::cout << "[EVENT] SensorBinary [" << (int)s->_deviceId << ":" << (int)s->_instanceId << "] value = " << s->getValue() << std::endl;

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

bool BoxAPI::Command::ZSensorBinary::isFailed() const
{
	ZCallback	callback;
	ZWError		e;
	ZDataHolder data;
	bool		level;
	ZWBOOL		value;

	if ((e = zway_fc_is_failed_node(_zway, _deviceId, ZCallback::successCallback, ZCallback::failureCallback, &callback)) != NoError)
	{
		zdata_release_lock(ZDataRoot(_zway));
		return true;
	}
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