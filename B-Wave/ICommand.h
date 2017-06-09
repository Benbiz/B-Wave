#ifndef ICOMMAND_H_
# define ICOMMAND_H_

namespace BoxAPI
{
	class ICommand
	{
	public:
		enum CommandType
		{
			ZSwitchBinary = 0x25,
			ZSwitchMultiLevel = 0x26,
			ZSensorBinary = 0x30,
			ZSensorMultiLevel = 0x31,
			ZSwitchColor = 0x33,
			Meter = 0x32
		};

		virtual ~ICommand() {}

		virtual int					getDeviceId() const = 0;
		virtual CommandType			getType() const = 0;
		virtual int					getInstance() const = 0;

	};
}

#endif /* !ICOMMAND_H_ */