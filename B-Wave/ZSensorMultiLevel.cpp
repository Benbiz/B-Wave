#include "stdafx.h"
#include "Device.h"
#include "ControllerEvent.h"
#include "BWave.h"
#include "ZSensorMultiLevel.h"
#include "ZCallback.h"

BoxAPI::Command::ZSensorMultiLevel::ZSensorMultiLevel(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int id)
	: _zway(zway), _deviceId(node_id), _instanceId(instance_id), _id(id), _path(std::to_string(id) + ".val")
{
	ZDataHolder data;
	ZWError r;
	ZWCSTR value;

	std::cout << "Creating sensormultilevel [" << (int)node_id << "," << (int)instance_id << "," << id << "]" << std::endl;
	zdata_acquire_lock(ZDataRoot(_zway));
	data = zway_find_device_instance_cc_data(_zway, _deviceId, _instanceId, BoxAPI::ICommand::CommandType::ZSensorMultiLevel, _path.c_str());
	r = zdata_add_callback_ex(data, &BoxAPI::Command::ZSensorMultiLevel::CBEvent, FALSE, static_cast<void *>(this));
	if (r != NoError)
	{
		zdata_release_lock(ZDataRoot(_zway));
		throw std::runtime_error("Fail to add data callback");
	}
	zdata_release_lock(ZDataRoot(_zway));
}

BoxAPI::Command::ZSensorMultiLevel::~ZSensorMultiLevel()
{
	ZDataHolder data;
	ZWError r;

	zdata_acquire_lock(ZDataRoot(_zway));
	data = zway_find_device_instance_cc_data(_zway, _deviceId, _instanceId, BoxAPI::ICommand::CommandType::ZSensorMultiLevel, _path.c_str());
	r = zdata_remove_callback_ex(data, &BoxAPI::Command::ZSensorMultiLevel::CBEvent, this);
	if (r != NoError)
	{
		zdata_release_lock(ZDataRoot(_zway));
		return;
	}
	zdata_release_lock(ZDataRoot(_zway));
}

int BoxAPI::Command::ZSensorMultiLevel::getDeviceId() const
{
	return this->_deviceId;
}

BoxAPI::ICommand::CommandType BoxAPI::Command::ZSensorMultiLevel::getType() const
{
	return BoxAPI::ICommand::CommandType::ZSensorMultiLevel;
}

int BoxAPI::Command::ZSensorMultiLevel::getInstance() const
{
	return _instanceId;
}

float	BoxAPI::Command::ZSensorMultiLevel::getValue() const
{
	//ZWError		e;
	ZDataHolder data;
	float		level;
	ZCallback	callback;

	/*if ((e = zway_cc_sensor_multilevel_get(_zway, _deviceId, _instanceId, _id, &ZCallback::successCallback, &ZCallback::failureCallback, &callback) != 0))
		std::cout << "fail to get sensor multilevel (" << (int)e << ")" << std::endl;
	if (callback.wait())
		std::cout << "value get" << std::endl;
	else
	{
		std::cout << "value not get" << std::endl;
	}*/
	zdata_acquire_lock(ZDataRoot(_zway));
	data = zway_find_device_instance_cc_data(_zway, _deviceId, _instanceId, BoxAPI::ICommand::CommandType::ZSensorMultiLevel, _path.c_str());
	zdata_get_float(data, &level);
	zdata_release_lock(ZDataRoot(_zway));
	return level;
}

const std::string &BoxAPI::Command::ZSensorMultiLevel::getScale()
{
	if (_scale == "")
	{
		zdata_acquire_lock(ZDataRoot(_zway));
		ZDataHolder data;
		ZWCSTR		value;

		data = zway_find_device_instance_cc_data(_zway, _deviceId, _instanceId, BoxAPI::ICommand::CommandType::ZSensorMultiLevel, (std::to_string(_id) + ".scaleString").c_str());
		zdata_get_string(data, &value);
		_scale = value;
		zdata_release_lock(ZDataRoot(_zway));
	}
	return _scale;
}

int BoxAPI::Command::ZSensorMultiLevel::getId() const
{
	return _id;
}

void BoxAPI::Command::ZSensorMultiLevel::CBEvent(const ZDataRootObject root, ZWDataChangeType type, ZDataHolder data, void * arg)
{
	ZSensorMultiLevel				*s = static_cast<ZSensorMultiLevel *>(arg);
	BoxAPI::BWave					&b = BoxAPI::BWave::Instance();

	if (type != Updated)
		return;

	std::cout << "[EVENT] Sensor MultiLevel [" << (int)s->_deviceId << ":" << (int)s->_instanceId << "] value = " << s->getValue() << std::endl;
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

bool BoxAPI::Command::ZSensorMultiLevel::isFailed() const
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