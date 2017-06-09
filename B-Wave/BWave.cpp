#include "stdafx.h"
#include "Device.h"
#include "ControllerEvent.h"
#include "BWave.h"


BoxAPI::BWave BoxAPI::BWave::m_instance = BoxAPI::BWave();

BoxAPI::BWave::BWave()
{
}

BoxAPI::BWave & BoxAPI::BWave::operator=(const BWave &)
{

}

BoxAPI::BWave::BWave(const BWave &)
{
}

BoxAPI::BWave::~BWave()
{
}

BoxAPI::BWave & BoxAPI::BWave::Instance()
{
	return m_instance;
}

bool BoxAPI::BWave::init(std::string &host)
{
	if (!_controller.init())
		return false;

	_conn.init();
	_conn.connect(host, "hEaeRtgQrCAtsRlfDavn4SHR4DCSXHoW", "CmiSNldXX4WdvD6Dp779ieUHrM7gRilN");
	
	_scenario.initialize();
	
	return true;
}

bool BoxAPI::BWave::init()
{
	std::cout << "Starting in local mode" << std::endl;
	if (!_controller.init())
		return false;
	_scenario.initialize();
	return true;
}

const BoxAPI::Controller & BoxAPI::BWave::getController()
{
	return _controller;
}

ScenarioMotor & BoxAPI::BWave::getScenarioMotor()
{
	return this->_scenario;
}
