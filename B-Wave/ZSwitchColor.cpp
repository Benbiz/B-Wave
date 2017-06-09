#include "stdafx.h"
#include "BWave.h"
#include "ControllerEvent.h"
#include "ZSwitchColor.h"
#include "ZCallback.h"

BoxAPI::Command::ZSwitchColor::ZSwitchColor(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int id)
	: _zway(zway), _deviceId(node_id), _instanceId(instance_id), _id(id), _path(std::to_string(id) + ".level"), _color("")
{
	ZDataHolder data;
	ZWError r;
	ZWCSTR value;

	std::cout << "Creating SwitchColor [" << (int)node_id << "," << (int)instance_id << "," << id << "]" << std::endl;
	zdata_acquire_lock(ZDataRoot(_zway));
	data = zway_find_device_instance_cc_data(_zway, _deviceId, _instanceId, BoxAPI::ICommand::CommandType::ZSwitchColor, _path.c_str());
	r = zdata_add_callback_ex(data, &BoxAPI::Command::ZSwitchColor::CBEvent, TRUE, static_cast<void *>(this));
	if (r != NoError)
	{
		zdata_release_lock(ZDataRoot(_zway));
		std::cout << "fail to add switchcolor callback" << std::endl;
		throw std::runtime_error("Fail to add data callback");
	}
	zdata_release_lock(ZDataRoot(_zway));
}

BoxAPI::Command::ZSwitchColor::~ZSwitchColor()
{
	ZDataHolder data;
	ZWError r;

	zdata_acquire_lock(ZDataRoot(_zway));
	data = zway_find_device_instance_cc_data(_zway, _deviceId, _instanceId, BoxAPI::ICommand::CommandType::ZSwitchColor, _path.c_str());
	r = zdata_remove_callback_ex(data, &BoxAPI::Command::ZSwitchColor::CBEvent, this);
	if (r != NoError)
	{
		zdata_release_lock(ZDataRoot(_zway));
		return;
	}
	zdata_release_lock(ZDataRoot(_zway));
}

int BoxAPI::Command::ZSwitchColor::getDeviceId() const
{
	return this->_deviceId;
}

BoxAPI::ICommand::CommandType BoxAPI::Command::ZSwitchColor::getType() const
{
	return BoxAPI::ICommand::CommandType::ZSwitchColor;
}

int BoxAPI::Command::ZSwitchColor::getInstance() const
{
	return _instanceId;
}

int	BoxAPI::Command::ZSwitchColor::getValue() const
{
	//ZWError		e;
	ZDataHolder data;
	int				level;
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
	data = zway_find_device_instance_cc_data(_zway, _deviceId, _instanceId, BoxAPI::ICommand::CommandType::ZSwitchColor, _path.c_str());
	zdata_get_integer(data, &level);
	zdata_release_lock(ZDataRoot(_zway));
	return level;
}

void						BoxAPI::Command::ZSwitchColor::setValue(int val) const
{
	ZWBYTE	v = val;
	ZWError	e;

	if ((e = zway_cc_switch_color_set(_zway, _deviceId, _instanceId, _id, v, 0xff, NULL, NULL, NULL)) != 0)
	{
		std::cout << "fail to set switch color (" << (int)e << ")" << std::endl;
		return;
	}
}

const std::string &BoxAPI::Command::ZSwitchColor::getColor()
{
	if (_color == "")
	{
		zdata_acquire_lock(ZDataRoot(_zway));
		ZDataHolder data;
		ZWCSTR		value;

		data = zway_find_device_instance_cc_data(_zway, _deviceId, _instanceId, BoxAPI::ICommand::CommandType::ZSwitchColor, (std::to_string(_id) + ".capabilityString").c_str());
		zdata_get_string(data, &value);
		_color = value;
		zdata_release_lock(ZDataRoot(_zway));
	}
	return _color;
}

int BoxAPI::Command::ZSwitchColor::getId() const
{
	return _id;
}

void BoxAPI::Command::ZSwitchColor::CBEvent(const ZDataRootObject root, ZWDataChangeType type, ZDataHolder data, void * arg)
{
	ZSwitchColor				*s = static_cast<ZSwitchColor *>(arg);
	BoxAPI::BWave				&b = BoxAPI::BWave::Instance();
	
	if (type == ChildCreated)
	{
		std::string name = zdata_get_name(data);
		ZDataIterator child = zdata_first_child(data);
		while (child != NULL)
		{
			std::string name = zdata_get_name(child->data);
			if (name == "level")
			{
				zdata_remove_callback_ex(data, &BoxAPI::Command::ZSwitchColor::CBEvent, arg);
				zdata_add_callback_ex(child->data, &BoxAPI::Command::ZSwitchColor::CBEvent, FALSE, arg);
				return;
			}
			child = zdata_next_child(child);
		}
	}
	if (type != Updated)
		return;
	std::cout << "[EVENT] SwitchColor [" << (int)s->_deviceId << ":" << (int)s->_instanceId << ":" <<  (int)s->_id << "] value = " << s->getValue() << std::endl;
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