#ifndef SUBSCRIBER_H_
# define SUBSCRIBER_H_

namespace BoxAPI
{
	namespace Event
	{
		class Dispatcher;

		template <typename D, typename T>
		class Subscriber
		{
		public:
			typedef std::function<bool(T)>	Condition;
			typedef std::function<void(T)>	Handler;

			Subscriber(Handler h, Condition c = nullptr);
			Subscriber& operator=(const Subscriber&);
			Subscriber(const Subscriber&);
			virtual ~Subscriber();

			void	setHandler(Handler);
			void	setCondition(Condition);

			void	operator()(const Dispatcher *, T);

		private:
			Handler	mHandler;
			Condition	mCondition;
		};

		template <typename D, typename T >
		inline Subscriber<D, T>::Subscriber(Handler h, Condition c)
			: mHandler(h), mCondition(c)
		{
		}

		template<typename D, typename T>
		inline Subscriber<D, T> & Subscriber<D, T>::operator=(const Subscriber<D, T> &s)
		{
			mHandler(s.mHandler);
			mCondition(s.mCondition);
			return *this;
		}

		template<typename D, typename T>
		inline Subscriber<D, T>::Subscriber(const Subscriber<D, T> &s)
			: mHandler(s.mHandler), mCondition(s.mCondition)
		{
		}

		template <typename D, typename T >
		inline Subscriber<D, T>::~Subscriber()
		{
		}

		template<typename D, typename T>
		inline void Subscriber<D, T>::setHandler(Handler h)
		{
			mHandler = h;
		}

		template<typename D, typename T>
		inline void Subscriber<D, T>::setCondition(Condition c)
		{
			mCondition = c;
		}

		template<typename D, typename T>
		inline void Subscriber<D, T>::operator()(const Dispatcher *d, T data)
		{
			const D	*dispatcher = dynamic_cast<const D *>(d);
			if (dispatcher == nullptr)
				return;
			if (mCondition == nullptr || mCondition(data))
				mHandler(data);
		}
	}
}

#endif /* !SUBSCRIBER_H_ */