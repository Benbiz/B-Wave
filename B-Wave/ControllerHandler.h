#ifndef CONTROLLERHANDLER_H_
# define CONTROLLERHANDLER_H_

namespace BoxAPI
{
	namespace Network
	{
		class MessageHandler;

		class ControllerHandler
		{
		public:
			ControllerHandler();
			~ControllerHandler();

			friend MessageHandler;

		private:
			void		onInclusionMode(sio::event &);
			void		onExclusionMode(sio::event &);
		};
	}
}

#endif /* CONTROLLERHANDLER_H_ */