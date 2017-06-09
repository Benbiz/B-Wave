#ifndef ZSWITCHCOLOR_H_
# define ZSWITCHCOLOR_H_

#include "ICommand.h"

namespace BoxAPI
{
	class Device;
	namespace Command
	{
		class ZSwitchColor : public ICommand
		{
		public:
			virtual	~ZSwitchColor();

			virtual int					getDeviceId() const;
			virtual CommandType			getType() const;
			virtual int					getInstance() const;

			int							getValue() const;
			void						setValue(int) const;

			int							getId() const;
			const std::string			&getColor();

		private:
			friend class BoxAPI::Device;

			ZSwitchColor(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int id);

			static void	CBEvent(const ZDataRootObject root, ZWDataChangeType type, ZDataHolder data, void *arg);

			ZWay							_zway;
			ZWBYTE							_deviceId;
			ZWBYTE							_instanceId;
			std::string						_path;
			std::string						_color;
			int								_id;
		};
	}
}

#endif /* !ZSWITCHCOLOR_H_ */