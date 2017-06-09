#ifndef MODULELISTHANDLER_H_
# define MODULELISTHANDLER_H_

namespace BoxAPI
{
	namespace Network
	{
		class MessageHandler;

		class ModuleListHandler
		{
		public:
			ModuleListHandler();
			~ModuleListHandler();

			friend MessageHandler;

		private:
			void		onModuleList(sio::event &);
		};
	}
}

#endif /* MODULELISTHANDLER_H_ */