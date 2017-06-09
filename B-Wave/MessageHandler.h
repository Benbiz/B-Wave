#ifndef MESSAGEHANDLER_H_
# define MESSAGEHANDLER_H_

#include "ModuleListHandler.h"
#include "ScenarioHandler.h"
#include "ControllerHandler.h"
#include "CommandHandler.h"

namespace BoxAPI
{
	namespace Network
	{
		class MessageHandler
		{
		public:
			MessageHandler();
			~MessageHandler();

			void	init(std::shared_ptr<sio::socket> sock);

		private:

			std::shared_ptr<sio::socket>	_sock;
			CommandHandler					_command;
			ScenarioHandler					_scenario;
			ModuleListHandler				_modulelist;
			ControllerHandler				_controller;
		};
	}
}

#endif /* MESSAGEHANGLER_H_ */