#ifndef EVENTDISPATCHER_H_
# define EVENTDISPATCHER_H_

#include "Subscriber.hpp"
#include "Dispatcher.h"

namespace BoxAPI
{
	namespace Event
	{
		template <typename D, typename T>
		class EventDispatcher : public Dispatcher
		{
		public:
			typedef Subscriber<D, T>	EventSubscriber;

			EventDispatcher();
			virtual ~EventDispatcher();

			void			subscribe(const EventSubscriber &);

			void			dispatchEvent(T);

		private:
			std::vector<EventSubscriber>	subscribers;
		};

		template <typename D, typename T>
		inline EventDispatcher<D, T>::EventDispatcher()
			: Dispatcher()
		{
		}

		template <typename D, typename T>
		inline EventDispatcher<D, T>::~EventDispatcher()
		{
		}

		template <typename D, typename T>
		inline void EventDispatcher<D, T>::subscribe(const EventSubscriber &s)
		{
			subscribers.push_back(s);
		}

		template <typename D, typename T>
		inline void EventDispatcher<D, T>::dispatchEvent(T d)
		{
			for (EventSubscriber &s : subscribers)
				this->dispatch(std::bind(&EventSubscriber::operator(), &s, std::placeholders::_1, d));
		}
	}
}

#endif /* !EVENTDISPATCHER_H_ */