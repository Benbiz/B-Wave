#ifndef SCENARIOHANDLER_H_
# define SCENARIOHANDLER_H_

#include "ScenarioMotor.h"

namespace BoxAPI
{
	namespace Network
	{
		class MessageHandler;

		class ScenarioHandler
		{
		public:
			ScenarioHandler();
			~ScenarioHandler();

			friend MessageHandler;
		private:

			void		onNewScenario(sio::event &);
			bool		createTriggers(sio::message::ptr mess);
			bool		findSensorMultiLevelTrigger(sio::message::ptr trigger, int uid, int moduleid);
			bool		findSensorBinaryTrigger(sio::message::ptr trigger, int uid, int moduleid);

			bool		createActions(sio::message::ptr mess, std::vector<t_action*> &actions);
			bool		findSwitchBinaryAction(sio::message::ptr trigger, int uid, int moduleid, std::vector<t_action*> &actions);
			bool		findSwitchMultiLevelAction(sio::message::ptr trigger, int uid, int moduleid, std::vector<t_action*> &actions);
			bool		findSwitchColorAction(sio::message::ptr trigger, int uid, int moduleid, std::vector<t_action*> &actions);

			TriggerTree	*getLogical(sio::message::ptr mess);
			TriggerTree	*getCondition(sio::message::ptr left, char cond, sio::message::ptr right);
			
			std::map<std::string, bool(BoxAPI::Network::ScenarioHandler::*)(sio::message::ptr trigger, int uid, int moduleid)>	_triggers;
			std::map<std::string, bool(BoxAPI::Network::ScenarioHandler::*)(sio::message::ptr trigger, int uid, int moduleid, std::vector<t_action*> &actions)>	_actions;
		};
	}
}
#endif // !SCENARIOHANDLER_H_