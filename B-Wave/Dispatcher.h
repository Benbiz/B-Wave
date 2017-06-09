#ifndef DISPATCHER_H_
# define DISPATCHER_H_

#include <functional>
#include <thread>
#include <map>
#include <vector>
#include <queue>
#include <condition_variable>

namespace BoxAPI
{
	namespace Event
	{
		class Dispatcher
		{
		public:
			virtual ~Dispatcher();

		protected:
			Dispatcher();
			Dispatcher& operator=(const Dispatcher&);
			Dispatcher(const Dispatcher&);

			void	dispatch(std::function<void(const Dispatcher *sender)> fct);

		private:
			void	dispatcherThread();

			static std::multimap<const Dispatcher *, std::function<void(const Dispatcher *sender)>>	toDispatch;

			static std::vector<std::thread>			pool;
			static std::condition_variable			poolcond;
			static std::mutex						poolmutex;
			static std::mutex						nbInstanceMutex;
			static int								nbInstance;

			static const int						nbThread = 5;
		};
	}
}

#endif /* !DISPATCHER_H_ */