#include "stdafx.h"
#include "Dispatcher.h"

std::multimap<const BoxAPI::Event::Dispatcher *, std::function<void(const BoxAPI::Event::Dispatcher *sender)>>	BoxAPI::Event::Dispatcher::toDispatch;
std::vector<std::thread>																						BoxAPI::Event::Dispatcher::pool;
std::condition_variable																							BoxAPI::Event::Dispatcher::poolcond;
std::mutex																										BoxAPI::Event::Dispatcher::poolmutex;
std::mutex																										BoxAPI::Event::Dispatcher::nbInstanceMutex;
int																												BoxAPI::Event::Dispatcher::nbInstance = 0;

BoxAPI::Event::Dispatcher::Dispatcher()
{
	std::unique_lock<std::mutex> lock(nbInstanceMutex);
	nbInstance++;
	if (nbInstance == 1)
	{
		for (int i = 0; i < nbThread; i++)
			this->pool.push_back(std::thread(std::bind(&BoxAPI::Event::Dispatcher::dispatcherThread, this)));
	}

}

BoxAPI::Event::Dispatcher::~Dispatcher()
{
	std::unique_lock<std::mutex> lock(nbInstanceMutex);
	nbInstance--;
	if (nbInstance == 0)
	{
		poolcond.notify_all();
		for (std::thread &th : pool)
			th.join();
		pool.clear();
	}

	std::unique_lock<std::mutex> locked(this->poolmutex);
	for (auto it = toDispatch.begin(), ite = toDispatch.end(); it != ite;)
	{
		if (it->first == this)
			it = toDispatch.erase(it);
		else
			++it;
	}
}

void BoxAPI::Event::Dispatcher::dispatch(std::function<void(const BoxAPI::Event::Dispatcher *sender)> fct)
{
	std::unique_lock<std::mutex> lock(this->poolmutex);

	this->toDispatch.insert(std::make_pair(this, fct));
	lock.unlock();
	poolcond.notify_one();
}

BoxAPI::Event::Dispatcher & BoxAPI::Event::Dispatcher::operator=(const BoxAPI::Event::Dispatcher &)
{
	return *this;
}

BoxAPI::Event::Dispatcher::Dispatcher(const BoxAPI::Event::Dispatcher &)
{
}

void BoxAPI::Event::Dispatcher::dispatcherThread()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(this->poolmutex);
		while (this->toDispatch.empty() && nbInstance != 0)
			poolcond.wait(lock);
		if (nbInstance == 0)
			return;

		const BoxAPI::Event::Dispatcher *sender = toDispatch.begin()->first;
		std::function<void(const Dispatcher *)>	fct = toDispatch.begin()->second;

		toDispatch.erase(toDispatch.begin());
		lock.unlock();
		fct(sender);
	}
}
