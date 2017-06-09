#include "stdafx.h"
#include "DeviceRecord.h"
#include "Controller.h"
#include "ControllerEvent.h"
#include "Command.h"
#include "BWave.h"
#include <sstream>

void print_list()
{
	BoxAPI::BWave &b = BoxAPI::BWave::Instance();

	std::cout << "List of devices/commands :" << std::endl;
	for (std::shared_ptr<BoxAPI::Device> dev : b.getController().getDevices())
	{
		std::cout << "----- Device [" << dev->getId() << "] (" << dev->getDeviceRecord().front().getVendor() << " | " << dev->getDeviceRecord().front().getProduct() << ") -----" << std::endl;
		for (std::shared_ptr<BoxAPI::ICommand> cmd : dev->getCommands())
		{
			switch (cmd->getType())
			{
			case BoxAPI::ICommand::CommandType::ZSensorBinary:
			{
				std::shared_ptr<BoxAPI::Command::ZSensorBinary> sb = std::dynamic_pointer_cast<BoxAPI::Command::ZSensorBinary>(cmd);
				std::cout << "\t[SensorBinary] [" << cmd->getDeviceId() << ", " << cmd->getInstance() << ", " << sb->getId() << "]\tValue : " << std::boolalpha << sb->getValue() << std::endl;
			}
				break;
			case BoxAPI::ICommand::CommandType::ZSwitchBinary:
			{
				std::shared_ptr<BoxAPI::Command::ZSwitchBinary> sb = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchBinary>(cmd);
				std::cout << "\t[SwitchBinary] [" << cmd->getDeviceId() << ", " << cmd->getInstance() << "]\tValue : " << std::boolalpha << sb->getSwitch() << std::endl;
			}
				break;
			case BoxAPI::ICommand::CommandType::ZSensorMultiLevel:
			{
				std::shared_ptr<BoxAPI::Command::ZSensorMultiLevel> sm = std::dynamic_pointer_cast<BoxAPI::Command::ZSensorMultiLevel>(cmd);
				std::cout << "\t[SensorMultiLevel] [" << cmd->getDeviceId() << ", " << cmd->getInstance() << ", " << sm->getId() << "] Value : " << sm->getValue() << sm->getScale() << std::endl;
			}
				break;
			case BoxAPI::ICommand::CommandType::ZSwitchMultiLevel:
			{
				std::shared_ptr<BoxAPI::Command::ZSwitchMultiLevel> sm = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchMultiLevel>(cmd);
				std::cout << "\t[SwitchMultiLevel] [" << cmd->getDeviceId() << ", " << cmd->getInstance() << "] Value : " << sm->getLevel() << std::endl;
			}
				break;
			case BoxAPI::ICommand::CommandType::ZSwitchColor:
			{
				std::shared_ptr<BoxAPI::Command::ZSwitchColor> sc = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(cmd);
				std::cout << "\t[SwitchColor] [" << cmd->getDeviceId() << ", " << cmd->getInstance() << ", " << sc->getColor() << " (" << sc->getId() << ")] Value : " << sc->getValue() << std::endl;
			}
				break;
			default:
				break;
			}
		}
	}
}

void		print_help()
{
	std::string greencolor = "\033[32m";
	std::string defaultcolor = "\033[39m";

	std::cout << "[HELP] List of available commands :" << std::endl
		<< "----- Controller -----" << std::endl
		<< "\t'" << greencolor << "i [true/false]" << defaultcolor << "' to switch inclusion mode" << std::endl
		<< "\t'" << greencolor << "e [true/false]" << defaultcolor << "' to switch exclusion mode" << std::endl
		<< "\t'" << greencolor << "l"  << defaultcolor <<  "' to print list of device and commands " << std::endl
		<< "\t'" << greencolor << "state" << defaultcolor << "' to know the state of the controller (int value) " << std::endl
		<< "----- Switch Binary -----" << std::endl
		<< "\t'" << greencolor << "sb [device_id] [instance_id] [bool_level]" << defaultcolor << "' to switch" << std::endl
		<< "----- Switch MultiLevel -----" << std::endl
		<< "\t'" << greencolor << "sm [device_id] [instance_id] [int_level]" << defaultcolor << "' to set switch multilevel" << std::endl
		<< "\t'" << greencolor << "sm+ [device_id] [instance_id] [int_relative_level]" << defaultcolor << "' to raise switch multilevel" << std::endl
		<< "\t'" << greencolor << "sm- [device_id] [instance_id] [int_relative_level]" << defaultcolor << "' to down switch mutlilevel" << std::endl
		<< "----- Switch Color -----" << std::endl
		<< "\t'" << greencolor << "sc [device_id] [instance_id] [color_id] [level(0-255)]" << defaultcolor << "' set a color value" << std::endl
		<< "----- Other -----" << std::endl
		<< "\t'" << greencolor << "zddx list [device_id]" << defaultcolor << "' get list of zddx record by descending match score of the specified device" << std::endl
		<< "\t'" << greencolor << "zddx load [device_id] [file_name]" << defaultcolor << "' set the ZDDX file for the specified record" << std::endl
		<< "\t'" << greencolor << "h" << defaultcolor << "' to print this help" << std::endl
		<< "\t'" << greencolor << "x" << defaultcolor << "' to quit" << std::endl;
}

void	setRed(std::shared_ptr<BoxAPI::Device>	dev)
{
	std::cout << "TO RED" << std::endl;
	std::shared_ptr<BoxAPI::Command::ZSwitchColor>	sc;

	auto cc0 = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
		[&](std::shared_ptr<BoxAPI::ICommand> o)
	{
		return (o->getInstance() == 0 && o->getType() == BoxAPI::ICommand::ZSwitchColor && std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(o)->getId() == 0);
	});
	sc = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(*cc0);
	sc->setValue(0);

	auto cc1 = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
		[&](std::shared_ptr<BoxAPI::ICommand> o)
	{
		return (o->getInstance() == 0 && o->getType() == BoxAPI::ICommand::ZSwitchColor && std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(o)->getId() == 1);
	});
	sc = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(*cc1);
	sc->setValue(0);

	auto cc2 = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
		[&](std::shared_ptr<BoxAPI::ICommand> o)
	{
		return (o->getInstance() == 0 && o->getType() == BoxAPI::ICommand::ZSwitchColor && std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(o)->getId() == 2);
	});
	sc = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(*cc2);
	sc->setValue(255);

	auto cc3 = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
		[&](std::shared_ptr<BoxAPI::ICommand> o)
	{
		return (o->getInstance() == 0 && o->getType() == BoxAPI::ICommand::ZSwitchColor && std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(o)->getId() == 3);
	});
	sc = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(*cc3);
	sc->setValue(0);

	auto cc4 = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
		[&](std::shared_ptr<BoxAPI::ICommand> o)
	{
		return (o->getInstance() == 0 && o->getType() == BoxAPI::ICommand::ZSwitchColor && std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(o)->getId() == 4);
	});
	sc = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(*cc4);
	sc->setValue(0);
}

void	setGreen(std::shared_ptr<BoxAPI::Device>	dev)
{
	std::cout << "TO GREEN" << std::endl;
	std::shared_ptr<BoxAPI::Command::ZSwitchColor>	sc;

	auto cc0 = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
		[&](std::shared_ptr<BoxAPI::ICommand> o)
	{
		return (o->getInstance() == 0 && o->getType() == BoxAPI::ICommand::ZSwitchColor && std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(o)->getId() == 0);
	});
	sc = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(*cc0);
	sc->setValue(0);

	auto cc1 = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
		[&](std::shared_ptr<BoxAPI::ICommand> o)
	{
		return (o->getInstance() == 0 && o->getType() == BoxAPI::ICommand::ZSwitchColor && std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(o)->getId() == 1);
	});
	sc = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(*cc1);
	sc->setValue(0);

	auto cc2 = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
		[&](std::shared_ptr<BoxAPI::ICommand> o)
	{
		return (o->getInstance() == 0 && o->getType() == BoxAPI::ICommand::ZSwitchColor && std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(o)->getId() == 2);
	});
	sc = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(*cc2);
	sc->setValue(0);

	auto cc3 = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
		[&](std::shared_ptr<BoxAPI::ICommand> o)
	{
		return (o->getInstance() == 0 && o->getType() == BoxAPI::ICommand::ZSwitchColor && std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(o)->getId() == 3);
	});
	sc = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(*cc3);
	sc->setValue(255);

	auto cc4 = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
		[&](std::shared_ptr<BoxAPI::ICommand> o)
	{
		return (o->getInstance() == 0 && o->getType() == BoxAPI::ICommand::ZSwitchColor && std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(o)->getId() == 4);
	});
	sc = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(*cc4);
	sc->setValue(0);
}

void	onEvent(std::shared_ptr<BoxAPI::ControllerEvent::Data::Command> data)
{

	std::cout << "EVENT MAIN" << std::endl;
	if (data->data->getType() == BoxAPI::ICommand::CommandType::ZSensorBinary && data->data->getDeviceId() == 21)
	{
		std::shared_ptr<BoxAPI::Command::ZSensorBinary> sensor = std::dynamic_pointer_cast<BoxAPI::Command::ZSensorBinary>(data->data);
		std::shared_ptr<BoxAPI::Command::ZSensorBinary> sensor2;

		std::shared_ptr<BoxAPI::Device>					dev;
		dev = BoxAPI::BWave::Instance().getController().getDevice(23);
		auto cc = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
			[&](std::shared_ptr<BoxAPI::ICommand> o)
		{
			return (o->getInstance() == 0 && o->getType() == BoxAPI::ICommand::ZSensorBinary);
		});
		sensor2 = std::dynamic_pointer_cast<BoxAPI::Command::ZSensorBinary>(*cc);
		if (sensor->getValue() == true && sensor2->getValue() == false)
			setRed(BoxAPI::BWave::Instance().getController().getDevice(19));
		else if (sensor->getValue() == false && sensor2->getValue() == true)
			setGreen(BoxAPI::BWave::Instance().getController().getDevice(19));
	}
	else if (data->data->getType() == BoxAPI::ICommand::CommandType::ZSensorBinary && data->data->getDeviceId() == 23)
	{
		std::shared_ptr<BoxAPI::Command::ZSensorBinary> sensor = std::dynamic_pointer_cast<BoxAPI::Command::ZSensorBinary>(data->data);
		std::shared_ptr<BoxAPI::Command::ZSensorBinary> sensor2;

		std::shared_ptr<BoxAPI::Device>					dev;
		dev = BoxAPI::BWave::Instance().getController().getDevice(21);
		auto cc = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
			[&](std::shared_ptr<BoxAPI::ICommand> o)
		{
			return (o->getInstance() == 0 && o->getType() == BoxAPI::ICommand::ZSensorBinary);
		});
		sensor2 = std::dynamic_pointer_cast<BoxAPI::Command::ZSensorBinary>(*cc);
		if (sensor->getValue() == true && sensor2->getValue() == false)
			setGreen(BoxAPI::BWave::Instance().getController().getDevice(19));
		else if (sensor->getValue() == false && sensor2->getValue() == true)
			setRed(BoxAPI::BWave::Instance().getController().getDevice(19));
	}
}

int	main(int ac, char **av)
{
	BoxAPI::BWave						&b = BoxAPI::BWave::Instance();
	std::string							host;
	std::string							line;
	std::string							cmd;
	std::shared_ptr<BoxAPI::Device>		dev;

	if (ac == 2)
	{
		std::cout << "Starting in network mode" << std::endl;
		host = av[1];
	}
	if (ac == 2)
	{
		if (!b.init(host))
		{
			std::cout << "Fail to init B-Wave" << std::endl;
			return 0;
		}
	}
	else if (!b.init())
	{
		std::cout << "Fail to init B-Wave" << std::endl;
		return 0;
	}

	/*BoxAPI::ControllerEvent::CommandSubscriber	newcmd(std::bind(&onEvent, std::placeholders::_1),
		[&](std::shared_ptr<BoxAPI::ControllerEvent::Data::Command> data) -> bool
	{
		return (data->type == BoxAPI::ControllerEvent::Data::Update);
	});
	BoxAPI::ControllerEvent::EventDispatcher::Instance().subscribe(newcmd);*/

	print_help();
	while (true)
	{
		std::cout << "B-Wave > ";
		std::getline(std::cin, line);
		std::istringstream iss(line);

		iss >> cmd;
		if (cmd == "i")
		{
			bool	val;

			iss >> std::boolalpha >> val;
			if (b.getController().setInclusionMode(val))
				std::cout << "Inclusion mode " << ((val == true) ? "enable" : "disable") << std::endl;
			else
				std::cout << "Fail to " << ((val == true) ? "enable" : "disable") << " inclusion mode" << std::endl;
		}
		else if (cmd == "e")
		{
			bool	val;

			iss >> std::boolalpha >> val;
			if (b.getController().setExclusionMode(val))
				std::cout << "Exclusion mode " << ((val == true) ? "enable" : "disable") << std::endl;
			else
				std::cout << "Fail to " << ((val == true) ? "enable" : "disable") << " exclusion mode" << std::endl;
		}
		else if (cmd == "l")
			print_list();
		else if (cmd == "state")
			std::cout << "State = " << b.getController().getState() << std::endl;
		else if (cmd == "sb")
		{
			int												device, instance;
			bool											level;
			std::shared_ptr<BoxAPI::Command::ZSwitchBinary> sb;

			iss >> device >> instance >> std::boolalpha >> level;
			dev = b.getController().getDevice(device);
			auto cc = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
				[&](std::shared_ptr<BoxAPI::ICommand> o)
			{
				return (o->getInstance() == instance && o->getType() == BoxAPI::ICommand::ZSwitchBinary);
			});
			sb = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchBinary>(*cc);
			sb->setSwitch(level);
		}
		else if (cmd == "sm")
		{
			int													device, instance, level;
			std::shared_ptr<BoxAPI::Command::ZSwitchMultiLevel> sb;

			iss >> device >> instance >> level;
			dev = b.getController().getDevice(device);
			auto cc = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
				[&](std::shared_ptr<BoxAPI::ICommand> o)
			{
				return (o->getInstance() == 0 && o->getType() == BoxAPI::ICommand::ZSwitchMultiLevel);
			});
			sb = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchMultiLevel>(*cc);
			sb->setLevel(level);
		}
		else if (cmd == "sm+")
		{
			int													device, instance, level;
			std::shared_ptr<BoxAPI::Command::ZSwitchMultiLevel>	sm;

			iss >> device >> instance >> level;
			dev = b.getController().getDevice(device);
			auto cc = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
				[&](std::shared_ptr<BoxAPI::ICommand> o)
			{
				return (o->getInstance() == 0 && o->getType() == BoxAPI::ICommand::ZSwitchMultiLevel);
			});
			sm = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchMultiLevel>(*cc);
			sm->setLevel(sm->getLevel() + level);
		}
		else if (cmd == "sm-")
		{
			int													device, instance, level;
			std::shared_ptr<BoxAPI::Command::ZSwitchMultiLevel> sm;

			iss >> device >> instance >> level;
			dev = b.getController().getDevice(device);
			auto cc = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
				[&](std::shared_ptr<BoxAPI::ICommand> o)
			{
				return (o->getInstance() == 0 && o->getType() == BoxAPI::ICommand::ZSwitchMultiLevel);
			});
			sm = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchMultiLevel>(*cc);
			sm->setLevel(sm->getLevel() - level);
		}
		else if (cmd == "sc")
		{
			int												device, instance, id, level;
			std::shared_ptr<BoxAPI::Command::ZSwitchColor>	sc;

			iss >> device >> instance >> id >> level;
			dev = b.getController().getDevice(device);
			auto cc = std::find_if(dev->getCommands().begin(), dev->getCommands().end(),
				[&](std::shared_ptr<BoxAPI::ICommand> o)
			{
				return (o->getInstance() == 0 && o->getType() == BoxAPI::ICommand::ZSwitchColor && std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(o)->getId() == id);
			});
			sc = std::dynamic_pointer_cast<BoxAPI::Command::ZSwitchColor>(*cc);
			sc->setValue(level);
		}
		else if (cmd == "zddx")
		{
			std::string	param;

			iss >> param;
			if (param == "list")
			{
				int device;

				iss >> device;
				dev = b.getController().getDevice(device);
				for (const BoxAPI::DeviceRecord &rec : dev->getDeviceRecord())
					std::cout << "Score: " << rec.getScore() << ", Vendor: " << rec.getVendor() << ", Product: " << rec.getProduct() << ", File: " << rec.getFileName() << std::endl;
			}
			else if (param == "load")
			{
				int device;
				std::string file;

				iss >> device >> file;
				dev = b.getController().getDevice(device);
				if (dev->setDeviceRecord(file))
					std::cout << "ZDDX loaded successfully" << std::endl;
				else
					std::cout << "Fail to load ZDDX file" << std::endl;
			}
		}
		else if (cmd == "h")
			print_help();
		else if (cmd == "x")
			return 0;
		else if (cmd != "")
			std::cout << "Unknow command \"" << cmd << "\". Type h for help." << std::endl;
		line = "";
		cmd = "";
	}
}