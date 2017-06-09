#ifndef ZCALLBACK_H_
# define ZCALLBACK_H_

namespace BoxAPI
{
	namespace Command
	{
		class ZCallback
		{
		public:
			ZCallback();
			bool		wait();

			static void	successCallback(const ZWay zway, ZWBYTE functionId, void* arg);
			static void	failureCallback(const ZWay zway, ZWBYTE functionId, void* arg);
		private:

			std::mutex						mtx;
			std::condition_variable			cv;
			bool							success;
			bool							called;
		};
	}
}

#endif /* ZCALLBACK_H_ */