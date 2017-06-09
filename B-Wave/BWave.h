#ifndef BWAVE_H_
# define BWAVE_H_

#include "Controller.h"
#include "ScenarioMotor.h"
#include "Connection.h"

namespace BoxAPI
{
	class BWave
	{
	public:
		~BWave();
		static BWave&	Instance();

		bool	init(std::string &host);
		bool	init();
		
		const BoxAPI::Controller	&getController();
		ScenarioMotor			&getScenarioMotor();

	private:
		BWave();
		BWave& operator=(const BWave&);
		BWave(const BWave&);

		static BWave								m_instance;

		BoxAPI::Controller			_controller;
		BoxAPI::Network::Connection	_conn;
		ScenarioMotor				_scenario;
	};
}

#endif /* !BWAVE_H_ */