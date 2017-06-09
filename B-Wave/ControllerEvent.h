#ifndef CONTROLLEREVENT_H_
#define CONTROLLEREVENT_H_


#include "EventDispatcher.hpp"
#include "ICommand.h"

namespace BoxAPI
{
	class Device;
	class ICommand;
	namespace ControllerEvent
	{
		namespace Data
		{
			enum EventType
			{
				All = -1,
				New = 0,
				Remove = 1,
				Update = 2
			};

			template <typename T>
			struct EventData
			{
				EventData(EventType t, T cmd)
					: type(t), data(cmd)
				{
				}

				EventType							type;
				T									data;
			};

			using Command = Data::EventData<std::shared_ptr<ICommand>>;
			using Device = Data::EventData<std::shared_ptr<Device>>;
		}

		class EventDispatcher :
			public BoxAPI::Event::EventDispatcher<EventDispatcher, std::shared_ptr<Data::Command>>,
			public  BoxAPI::Event::EventDispatcher<EventDispatcher, std::shared_ptr<Data::Device>>,
			public  BoxAPI::Event::EventDispatcher<EventDispatcher, int>
		{
		public:
			~EventDispatcher();

			static EventDispatcher&	Instance();

			using BoxAPI::Event::EventDispatcher<EventDispatcher, std::shared_ptr<Data::Command>>::dispatchEvent;
			using BoxAPI::Event::EventDispatcher<EventDispatcher, std::shared_ptr<Data::Device>>::dispatchEvent;
			using BoxAPI::Event::EventDispatcher<EventDispatcher, int>::dispatchEvent;

			using BoxAPI::Event::EventDispatcher<EventDispatcher, std::shared_ptr<Data::Command>>::subscribe;
			using BoxAPI::Event::EventDispatcher<EventDispatcher, std::shared_ptr<Data::Device>>::subscribe;
			using BoxAPI::Event::EventDispatcher<EventDispatcher, int>::subscribe;

		private:
			EventDispatcher();
			EventDispatcher& operator=(const EventDispatcher&);
			EventDispatcher(const EventDispatcher&);

			static EventDispatcher								m_instance;
		};

		using CommandSubscriber = BoxAPI::Event::EventDispatcher<EventDispatcher, std::shared_ptr<Data::Command>>::EventSubscriber;
		using DeviceSubscriber = BoxAPI::Event::EventDispatcher<EventDispatcher, std::shared_ptr<Data::Device>>::EventSubscriber;
		using ControllerStateSubscriber = BoxAPI::Event::EventDispatcher<EventDispatcher, int>::EventSubscriber;
	}
}

#endif /* !CONTROLLEREVENT_H_ */