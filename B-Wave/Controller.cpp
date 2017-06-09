#include "stdafx.h"
#include "ControllerEvent.h"
#include "Controller.h"

BoxAPI::Controller::~Controller()
{
	_devices.clear();
	zway_stop(_zway);
	zway_terminate(&_zway);
	zlog_close(_logger);
}

BoxAPI::Controller::Controller()
{
}

const std::vector<std::shared_ptr<BoxAPI::Device>>& BoxAPI::Controller::getDevices() const
{
	return _devices;
}

const std::shared_ptr<BoxAPI::Device> BoxAPI::Controller::getDevice(int id) const
{
	auto dev = std::find_if(_devices.begin(), _devices.end(),
		[&](std::shared_ptr<BoxAPI::Device> o)
	{
		return (o->getId() == id);
	});
	if (dev == _devices.end())
	{
		return nullptr;
	}
	return *dev;
}

BoxAPI::Controller::ControllerState										BoxAPI::Controller::getState() const
{
	ZWError		e;
	ZDataHolder data;
	int			value;

	zdata_acquire_lock(ZDataRoot(_zway));
	data = zway_find_controller_data(_zway, "controllerState");
	zdata_get_integer(data, &value);
	zdata_release_lock(ZDataRoot(_zway));
	return static_cast<BoxAPI::Controller::ControllerState>(value);
}

bool BoxAPI::Controller::setInclusionMode(bool startStop) const
{
	ZWError r;
	
	r = zway_controller_add_node_to_network(_zway, startStop);
	if (r != NoError)
		return false;
	return true;
}

bool BoxAPI::Controller::setExclusionMode(bool startStop) const
{
	ZWError r;

	r = zway_controller_remove_node_from_network(_zway, startStop);
	if (r != NoError)
		return false;
	return true;
}

static void print_zway_terminated(ZWay zway, void* arg)
{
	zway_log(zway, Information, ZSTR("Z-Way terminated"));
}

void					BoxAPI::Controller::print_D_I_CC_event(const ZWay zway, ZWDeviceChangeType type, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE command_id, void *arg)
{
	BoxAPI::Controller *c = static_cast<BoxAPI::Controller *>(arg);

	if (node_id == 1)
		return;
	switch (type)
	{
	case DeviceAdded:
	{
		std::cout << "[EVENT] New device [" << (int)node_id << "]" << std::endl;
		c->newDevice(node_id);
		break;
	}
	case DeviceRemoved:
	{
		std::cout << "[EVENT] Device removed [" << (int)node_id << "]" << std::endl;
		c->_devices.erase(std::remove_if(c->_devices.begin(), c->_devices.end(), [&](std::shared_ptr<Device> o)
		{
			if (o->getId() == node_id)
			{
				BoxAPI::ControllerEvent::EventDispatcher::Instance().dispatchEvent(std::make_shared<BoxAPI::ControllerEvent::Data::Device>(BoxAPI::ControllerEvent::Data::EventType::Remove, o));
				return true;
			}
			return false;
		}), c->_devices.end());
		break;
	}
	case CommandAdded:
	{
		std::shared_ptr<Device>	d = c->getDevice(node_id);

		if (d->addCommand(command_id, instance_id))
			std::cout << "[EVENT] New command [" << (int)node_id << "][" << (int)instance_id << "][" << (int)command_id << "]" << std::endl;
		if (d->isInterviewDone())
			std::cout << "Interview Done !" << std::endl;
		break;
	}
	case CommandRemoved:
	{
		std::vector<std::shared_ptr<BoxAPI::Device>>::iterator it = std::find_if(c->_devices.begin(), c->_devices.end(), [&](std::shared_ptr<Device> o)
		{
			return (o->getId() == node_id);
		});

		if (it == c->_devices.end())
		{
			std::cout << "[EVENT] Command removed [" << (int)node_id << "][" << (int)instance_id << "][" << (int)command_id << "] (Already removed of list)" << std::endl;
			return;
		}
		if ((*it)->removeCommand(command_id, instance_id))
			std::cout << "[EVENT] Command removed [" << (int)node_id << "][" << (int)instance_id << "][" << (int)command_id << "]" << std::endl;
		break;
	}
	}
}

bool BoxAPI::Controller::init()
{
	ZDataHolder data;
	ZWError r;

	_logger = zlog_create(stdout, Critical);
	_zway = NULL;
	r = zway_init(&_zway, ZSTR("/dev/ttyAMA0"),
		"/opt/z-way-server/config",
		"/opt/z-way-server/translations",
		"/opt/z-way-server/ZDDX", NULL, _logger);
	if (r != NoError)
	{
		zway_log_error(_zway, Critical, "Failed to init ZWay", r);
		return (false);
	}
	zway_device_add_callback(_zway, DeviceAdded | DeviceRemoved | CommandAdded | CommandRemoved, BoxAPI::Controller::print_D_I_CC_event, static_cast<void*>(this));
	r = zway_start(_zway, print_zway_terminated, nullptr);
	if (r != NoError)
	{
		zway_log_error(_zway, Critical, "Failed to start ZWay", r);
		return false;
	}
	r = zway_discover(_zway);
	if (r != NoError)
	{
		zway_log_error(_zway, Critical, "Failed to negotiate with Z-Wave stick", r);
		return false;
	}


	zdata_acquire_lock(ZDataRoot(_zway));
	data = zway_find_controller_data(_zway, "controllerState");
	r = zdata_add_callback(data, &BoxAPI::Controller::controllerStateChanged, FALSE, static_cast<void *>(this));
	if (r != NoError)
	{
		zdata_release_lock(ZDataRoot(_zway));
		return false;
	}
	zdata_release_lock(ZDataRoot(_zway));
	return (true);
}

void		BoxAPI::Controller::controllerStateChanged(const ZDataRootObject root, ZWDataChangeType type, ZDataHolder data, void * arg)
{
	BoxAPI::Controller *c = static_cast<BoxAPI::Controller *>(arg);

	if (type != Updated)
		return;
	BoxAPI::ControllerEvent::EventDispatcher::Instance().dispatchEvent(c->getState());
	std::cout << "[Event] Controller state changed" << std::endl;
}

void BoxAPI::Controller::newDevice(ZWBYTE id)
{
	Device					*device = new Device(_zway, id);
	std::shared_ptr<Device>	d(device);

	_devices.push_back(d);
	BoxAPI::ControllerEvent::EventDispatcher::Instance().dispatchEvent(std::make_shared<BoxAPI::ControllerEvent::Data::Device>(BoxAPI::ControllerEvent::Data::EventType::New, d));
}