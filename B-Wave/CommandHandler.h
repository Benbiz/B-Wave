#ifndef COMMANDHANDLER_H_
# define COMMANDHANDLER_H_

namespace BoxAPI
{
	namespace Network
	{
		class MessageHandler;

		class CommandHandler
		{
		public:
			CommandHandler();
			~CommandHandler();

			friend MessageHandler;

		private:

			void		onCommand(sio::event &);
			bool		switchBinary(int moduleid, std::shared_ptr<sio::message> command);
			bool		switchColor(int moduleid, std::shared_ptr<sio::message> command);
			bool		switchMultiLevel(int moduleid, std::shared_ptr<sio::message> command);

			std::map<std::string, bool (BoxAPI::Network::CommandHandler::*)(int, std::shared_ptr<sio::message>)>	_commands;
		};
	}
}
#endif // !COMMANDHANDLER_H_
