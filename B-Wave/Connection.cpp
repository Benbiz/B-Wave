#include "stdafx.h"
#include "Command.h"
#include "MessageHandler.h"
#include "Connection.h"

BoxAPI::Network::Connection::Connection()
	: m_status(NormalClosed)
{
}

BoxAPI::Network::Connection::~Connection()
{
	close();
}

void			BoxAPI::Network::Connection::init()
{
	BoxAPI::ControllerEvent::CommandSubscriber	newcmd(std::bind(&BoxAPI::Network::Connection::onNewCommand, this, std::placeholders::_1),
		[&](std::shared_ptr<BoxAPI::ControllerEvent::Data::Command> data) -> bool
	{
		return (this->getStatus() == Status::Open && data->type == BoxAPI::ControllerEvent::Data::New);
	});
	BoxAPI::ControllerEvent::EventDispatcher::Instance().subscribe(newcmd);

	BoxAPI::ControllerEvent::DeviceSubscriber	newmodule(std::bind(&BoxAPI::Network::Connection::onNewDevice, this, std::placeholders::_1),
		[&](std::shared_ptr<BoxAPI::ControllerEvent::Data::Device> data) -> bool
	{
		return (this->getStatus() == Status::Open && data->type == BoxAPI::ControllerEvent::Data::New);
	});
	BoxAPI::ControllerEvent::EventDispatcher::Instance().subscribe(newmodule);

	BoxAPI::ControllerEvent::DeviceSubscriber	deletemodule(std::bind(&BoxAPI::Network::Connection::onDeleteDevice, this, std::placeholders::_1),
		[&](std::shared_ptr<BoxAPI::ControllerEvent::Data::Device> data) -> bool
	{
		return (this->getStatus() == Status::Open && data->type == BoxAPI::ControllerEvent::Data::Remove);
	});
	BoxAPI::ControllerEvent::EventDispatcher::Instance().subscribe(deletemodule);

	BoxAPI::ControllerEvent::CommandSubscriber	updatecmd(std::bind(&BoxAPI::Network::Connection::onUpdateCommand, this, std::placeholders::_1),
		[&](std::shared_ptr<BoxAPI::ControllerEvent::Data::Command> data) -> bool
	{
		return (this->getStatus() == Status::Open && data->type == BoxAPI::ControllerEvent::Data::Update);
	});
	BoxAPI::ControllerEvent::EventDispatcher::Instance().subscribe(updatecmd);

	BoxAPI::ControllerEvent::ControllerStateSubscriber	controllerstate(std::bind(&BoxAPI::Network::Connection::onControllerStateChanged, this, std::placeholders::_1));
	BoxAPI::ControllerEvent::EventDispatcher::Instance().subscribe(controllerstate);
}

void			BoxAPI::Network::Connection::connect(const std::string &uri, const std::string &login, const std::string &password)
{
	if (m_status != Status::NormalClosed)
		return;
	_password = password;
	_login = login;
	_client.set_reconnect_attempts(0xFFFFFFFF);
	_client.set_open_listener(std::bind(&BoxAPI::Network::Connection::onConnected, this));
	_client.set_close_listener(std::bind(&BoxAPI::Network::Connection::onClose, this, std::placeholders::_1));
	_client.set_fail_listener(std::bind(&BoxAPI::Network::Connection::onFail, this));
	m_status = Status::Connecting;
	_client.connect(uri);
}

void			BoxAPI::Network::Connection::close()
{
	m_status = Status::NormalClosed;
	_client.set_reconnect_attempts(0);
	if (m_status != Status::Open)
		return;
	_client.socket()->off_all();
	_client.socket()->off_error();
	_client.close();
}

void BoxAPI::Network::Connection::onConnected()
{
	m_status = Status::Open;
	_handler.init(_client.socket());

	std::shared_ptr<sio::message> mess = sio::object_message::create();
	mess->get_map()["login"] = sio::string_message::create(_login);
	mess->get_map()["password"] = sio::string_message::create(_password);
	_client.socket()->emit("authenticate", mess);

	std::cout << "[NET] Connected !" << std::endl;
}

void BoxAPI::Network::Connection::onClose(sio::client::close_reason const& reason)
{
	m_status = Status::NormalClosed;
	if (_client.socket() != nullptr)
	{
		_client.socket()->off_all();
		_client.socket()->off_error();
	}
	if (reason == sio::client::close_reason::close_reason_drop)
	{
		std::cout << "[NET] Connection drop !" << std::endl;
		m_status = Status::Droped;
	}
	else
		std::cout << "[NET] Closed !" << std::endl;
}

void BoxAPI::Network::Connection::onFail()
{
	m_status = Status::Failed;
	if (_client.socket() != nullptr)
	{
		_client.socket()->off_all();
		_client.socket()->off_error();
	}
	std::cout << "[NET] Fail !" << std::endl;
}

BoxAPI::Network::Connection::Status BoxAPI::Network::Connection::getStatus()
{
	return m_status;
}

void	BoxAPI::Network::Connection::onNewDevice(std::shared_ptr<BoxAPI::ControllerEvent::Data::Device> data)
{
	std::cout << "[Net] Sending New Device Event .." << std::endl;
	std::shared_ptr<sio::message> mess = sio::object_message::create();

	mess->get_map()["module"] = sio::object_message::create();
	mess->get_map()["module"]->get_map()["id"] = sio::int_message::create(data->data->getId());
	_client.socket()->emit("NewModule", mess);
}

void	BoxAPI::Network::Connection::onDeleteDevice(std::shared_ptr<BoxAPI::ControllerEvent::Data::Device> data)
{
	std::cout << "[Net] Sending Delete Device Event .." << std::endl;
	std::shared_ptr<sio::message> mess = sio::object_message::create();

	mess->get_map()["module"] = sio::object_message::create();
	mess->get_map()["module"]->get_map()["id"] = sio::int_message::create(data->data->getId());
	_client.socket()->emit("RemoveModule", mess);
}

void	BoxAPI::Network::Connection::onNewCommand(std::shared_ptr<BoxAPI::ControllerEvent::Data::Command> data)
{
	std::cout << "[Net] Sending New Command Event .." << std::endl;
	std::shared_ptr<sio::message> mess = sio::object_message::create();

	mess->get_map()["module"] = sio::object_message::create();
	mess->get_map()["module"]->get_map()["id"] = sio::int_message::create(data->data->getDeviceId());

	if (data->data->getType() == ICommand::ZSwitchBinary)
	{
		mess->get_map()["switchbinary"] = sio::object_message::create();
		std::shared_ptr<BoxAPI::Command::ZSwitchBinary> zswitch = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchBinary>(data->data);

		mess->get_map()["switchbinary"]->get_map()["instance"] = sio::int_message::create(zswitch->getInstance());
		mess->get_map()["switchbinary"]->get_map()["level"] = sio::bool_message::create(zswitch->getSwitch());
	}
	else if (data->data->getType() == ICommand::ZSensorMultiLevel)
	{
		mess->get_map()["sensormultilevel"] = sio::object_message::create();
		std::shared_ptr<BoxAPI::Command::ZSensorMultiLevel> sensor = std::dynamic_pointer_cast<BoxAPI::Command::ZSensorMultiLevel>(data->data);
		mess->get_map()["sensormultilevel"]->get_map()["instance"] = sio::int_message::create(sensor->getInstance());
		mess->get_map()["sensormultilevel"]->get_map()["type_id"] = sio::int_message::create(sensor->getId());
		mess->get_map()["sensormultilevel"]->get_map()["scale"] = sio::string_message::create(sensor->getScale());
		mess->get_map()["sensormultilevel"]->get_map()["level"] = sio::int_message::create(round(sensor->getValue()));
	}
	else if (data->data->getType() == ICommand::ZSensorBinary)
	{
		mess->get_map()["sensorbinarys"] = sio::object_message::create();
		std::shared_ptr<BoxAPI::Command::ZSensorBinary> sensor = std::dynamic_pointer_cast<BoxAPI::Command::ZSensorBinary>(data->data);
		mess->get_map()["sensorbinarys"]->get_map()["instance"] = sio::int_message::create(sensor->getInstance());
		mess->get_map()["sensorbinarys"]->get_map()["level"] = sio::int_message::create(sensor->getValue());
	}
	else if (data->data->getType() == ICommand::ZSwitchColor)
	{
		mess->get_map()["switchcolor"] = sio::object_message::create();
		std::shared_ptr<BoxAPI::Command::ZSwitchColor> switchcolor = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(data->data);
		mess->get_map()["switchcolor"]->get_map()["instance"] = sio::int_message::create(switchcolor->getInstance());
		mess->get_map()["switchcolor"]->get_map()["color_id"] = sio::int_message::create(switchcolor->getId());
		mess->get_map()["switchcolor"]->get_map()["color"] = sio::string_message::create(switchcolor->getColor());
		mess->get_map()["switchcolor"]->get_map()["level"] = sio::int_message::create(switchcolor->getValue());
	}
	else if (data->data->getType() == ICommand::ZSwitchMultiLevel)
	{
		mess->get_map()["switchmultilevel"] = sio::object_message::create();
		std::shared_ptr<BoxAPI::Command::ZSwitchMultiLevel> switchmultilevel = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchMultiLevel>(data->data);

		mess->get_map()["switchmultilevel"]->get_map()["instance"] = sio::int_message::create(switchmultilevel->getInstance());
		mess->get_map()["switchmultilevel"]->get_map()["level"] = sio::int_message::create(switchmultilevel->getLevel());
	}

	_client.socket()->emit("NewCommand", mess);
}

void	BoxAPI::Network::Connection::onUpdateCommand(std::shared_ptr<BoxAPI::ControllerEvent::Data::Command> data)
{
	std::cout << "[Net] Sending Update Command Event .." << std::endl;
	std::shared_ptr<sio::message> mess = sio::object_message::create();

	mess->get_map()["module"] = sio::object_message::create();
	mess->get_map()["module"]->get_map()["id"] = sio::int_message::create(data->data->getDeviceId());

	if (data->data == nullptr)
	{
		std::cout << "null data" << std::endl;
		return;
	}
	if (data->data->getType() == ICommand::ZSwitchBinary)
	{
		mess->get_map()["switch"] = sio::object_message::create();
		std::shared_ptr<BoxAPI::Command::ZSwitchBinary> zswitch = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchBinary>(data->data);

		mess->get_map()["switch"]->get_map()["instance"] = sio::int_message::create(zswitch->getInstance());
		mess->get_map()["switch"]->get_map()["level"] = sio::bool_message::create(zswitch->getSwitch());
	}
	else if (data->data->getType() == ICommand::ZSensorMultiLevel)
	{
		mess->get_map()["sensormultilevel"] = sio::object_message::create();
		std::shared_ptr<BoxAPI::Command::ZSensorMultiLevel> sensor = std::dynamic_pointer_cast<BoxAPI::Command::ZSensorMultiLevel>(data->data);
		mess->get_map()["sensormultilevel"]->get_map()["instance"] = sio::int_message::create(sensor->getInstance());
		mess->get_map()["sensormultilevel"]->get_map()["type_id"] = sio::int_message::create(sensor->getId());
		mess->get_map()["sensormultilevel"]->get_map()["scale"] = sio::string_message::create(sensor->getScale());
		mess->get_map()["sensormultilevel"]->get_map()["level"] = sio::int_message::create(round(sensor->getValue()));
	}
	else if (data->data->getType() == ICommand::ZSensorBinary)
	{
		mess->get_map()["sensorbinary"] = sio::object_message::create();
		std::shared_ptr<BoxAPI::Command::ZSensorBinary> sensor = std::dynamic_pointer_cast<BoxAPI::Command::ZSensorBinary>(data->data);
		mess->get_map()["sensorbinary"]->get_map()["instance"] = sio::int_message::create(sensor->getInstance());
		mess->get_map()["sensorbinary"]->get_map()["level"] = sio::int_message::create(sensor->getValue());
	}
	else if (data->data->getType() == ICommand::ZSwitchColor)
	{
		mess->get_map()["switchcolor"] = sio::object_message::create();
		std::shared_ptr<BoxAPI::Command::ZSwitchColor> switchcolor = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(data->data);
		mess->get_map()["switchcolor"]->get_map()["instance"] = sio::int_message::create(switchcolor->getInstance());
		mess->get_map()["switchcolor"]->get_map()["color_id"] = sio::int_message::create(switchcolor->getId());
		mess->get_map()["switchcolor"]->get_map()["color"] = sio::string_message::create(switchcolor->getColor());
		mess->get_map()["switchcolor"]->get_map()["level"] = sio::int_message::create(switchcolor->getValue());
	}
	else if (data->data->getType() == ICommand::ZSwitchMultiLevel)
	{
		mess->get_map()["switchmultilevel"] = sio::object_message::create();
		std::shared_ptr<BoxAPI::Command::ZSwitchMultiLevel> switchmultilevel = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchMultiLevel>(data->data);

		mess->get_map()["switchmultilevel"]->get_map()["instance"] = sio::int_message::create(switchmultilevel->getInstance());
		mess->get_map()["switchmultilevel"]->get_map()["level"] = sio::int_message::create(switchmultilevel->getLevel());
	}
	_client.socket()->emit("UpdateCommand", mess);
}

void BoxAPI::Network::Connection::onControllerStateChanged(int state)
{
	std::cout << "[NET] Controller changed but sending not implem" << std::endl;
}
