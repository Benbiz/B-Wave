#ifndef DEVICE_H_
# define DEVICE_H_

#include "ICommand.h"
#include "DeviceRecord.h"

namespace BoxAPI
{
	class Controller;
	class Device
	{
	public:
		~Device();

		int															getId() const;
		const std::vector<std::shared_ptr<BoxAPI::ICommand>>		&getCommands() const;

		const std::vector<BoxAPI::DeviceRecord>						&getDeviceRecord();
		bool														setDeviceRecord(const std::string &file);

		bool														isInterviewDone() const;

	private:
		friend class BoxAPI::Controller;
		Device(ZWay zway, ZWBYTE deviceId);

		bool				addCommand(BoxAPI::ICommand::CommandType, ZWBYTE);
		bool				addCommand(ZWBYTE type, ZWBYTE instance);
		bool				removeCommand(BoxAPI::ICommand::CommandType);
		bool				removeCommand(ZWBYTE type, ZWBYTE instance);

		template <typename T>
		bool				createGeneric(ZWBYTE);

		template<BoxAPI::ICommand::CommandType CT, typename TC>
		void				CBNewChild(ZWBYTE, ZDataHolder);

		template<BoxAPI::ICommand::CommandType type, typename T>
		bool				createGenericWithId(ZWBYTE);

		void				CBInterviewCCDone();

		ZGuessedProduct																	*_rawRecords;
		std::vector<BoxAPI::DeviceRecord>												_records;
		std::vector<std::shared_ptr<BoxAPI::ICommand>>									_commands;
		static std::map<int, bool(BoxAPI::Device::*)(ZWBYTE)>							_createCommandMap;
		ZWay																			_zway;
		ZWBYTE																			_id;

	};
}

#include "ControllerEvent.h"
#include "Command.h"

template<typename T>
bool BoxAPI::Device::createGeneric(ZWBYTE i)
{
	try
	{
		T	*t = new T(this->_zway, this->_id, i);
		std::shared_ptr<T> ptr(t);
		this->_commands.push_back(ptr);
		BoxAPI::ControllerEvent::EventDispatcher::Instance().dispatchEvent(std::make_shared<BoxAPI::ControllerEvent::Data::Command>(BoxAPI::ControllerEvent::Data::EventType::New, ptr));
		return true;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
}

template<BoxAPI::ICommand::CommandType CT, typename TC>
void BoxAPI::Device::CBNewChild(ZWBYTE i, ZDataHolder data)
{
	std::string	id;

	ZDataIterator child = zdata_first_child(data);
	while (child != NULL)
	{
		id = zdata_get_name(child->data);
		if (isdigit(id[0]))
		{
			int iid = std::stoi(id);
			auto cc = std::find_if(_commands.begin(), _commands.end(),
				[&](std::shared_ptr<BoxAPI::ICommand> o)
			{
				return (o->getInstance() == i && o->getType() == CT && std::dynamic_pointer_cast<TC>(o)->getId() == iid);
			});
			if (cc == _commands.end())
			{
				TC	*t = new TC(this->_zway, this->_id, i, iid);
				std::shared_ptr<TC>	tc(t);
				_commands.push_back(tc);
				BoxAPI::ControllerEvent::EventDispatcher::Instance().dispatchEvent(std::make_shared<BoxAPI::ControllerEvent::Data::Command>(BoxAPI::ControllerEvent::Data::EventType::New, tc));
			}
		}
		child = zdata_next_child(child);
	}
}

template<BoxAPI::ICommand::CommandType type, typename T>
bool BoxAPI::Device::createGenericWithId(ZWBYTE i)
{
	std::string		id;
	ZDataHolder data;
	ZDataHolder	interview;
	ZWError	r;

	zdata_acquire_lock(ZDataRoot(_zway));
	data = zway_find_device_instance_cc_data(this->_zway, _id, i, type, NULL);
	std::function<void(ZDataHolder)> *fct = new std::function<void(ZDataHolder)>(std::bind(&Device::CBNewChild<type, T>, this, i, std::placeholders::_1));

	r = zdata_add_callback(data, [](const ZDataRootObject root, ZWDataChangeType ztype, ZDataHolder data, void *arg)
	{
		std::function<void(ZDataHolder)> *fc = static_cast <std::function<void(ZDataHolder)> *>(arg);
		if (ztype == Deleted)
		{
			std::cout << "Deleted" << std::endl;
			delete fc;
			return ;
		}
		if (ztype != ChildCreated)
			return;

		fc->operator()(data);
	}, FALSE, fct);
	if (r != NoError)
	{
		std::cout << "Unable to bind new command callback" << std::endl;
		zdata_release_lock(ZDataRoot(_zway));
		return false;
	}
	ZDataIterator child = zdata_first_child(data);
	while (child != NULL)
	{
		id = zdata_get_name(child->data);
		if (isdigit(id[0]))
		{
			int iid = std::stoi(id);
			auto cc = std::find_if(_commands.begin(), _commands.end(), [&](std::shared_ptr<BoxAPI::ICommand> o)
			{
				return (o->getInstance() == i && o->getType() == type && std::dynamic_pointer_cast<T>(o)->getId() == iid);
			});
			if (cc == _commands.end())
			{
				zdata_release_lock(ZDataRoot(_zway));
				T	*t = new T(this->_zway, this->_id, i, iid);
				std::shared_ptr<T>	tc(t);
				_commands.push_back(tc);
				BoxAPI::ControllerEvent::EventDispatcher::Instance().dispatchEvent(std::make_shared<BoxAPI::ControllerEvent::Data::Command>(BoxAPI::ControllerEvent::Data::EventType::New, tc));
				zdata_acquire_lock(ZDataRoot(_zway));
			}
		}
		child = zdata_next_child(child);
	}
	interview = zdata_find(data, "interviewDone");
	r = zdata_add_callback(interview, [](const ZDataRootObject root, ZWDataChangeType ztype, ZDataHolder data, void *arg)
	{
		BoxAPI::Device	*d = static_cast<BoxAPI::Device *>(arg);

		d->CBInterviewCCDone();
	}, FALSE, this);
	if (r != NoError)
	{
		std::cout << "Unable to bind interview done callback" << std::endl;
		zdata_release_lock(ZDataRoot(_zway));
		return false;
	}
	zdata_release_lock(ZDataRoot(_zway));

	return true;
}


#endif /* !DEVICE_H8 */