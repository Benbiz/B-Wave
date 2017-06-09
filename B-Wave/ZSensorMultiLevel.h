#ifndef ZSENSORMULTILEVEL_H_
# define ZSENSORMULTILEVEL_H_

#include "ICommand.h"

namespace BoxAPI
{
	class Device;
	namespace Command
	{
		class ZSensorMultiLevel : public ICommand
		{
		public:
			virtual	~ZSensorMultiLevel();

			virtual int					getDeviceId() const;
			virtual CommandType			getType() const;
			virtual int					getInstance() const;

			float						getValue() const;
			const std::string			&getScale();
			int							getId() const;
			bool						isFailed() const;

		private:
			friend class BoxAPI::Device;

			ZSensorMultiLevel(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int id);

			static void	CBEvent(const ZDataRootObject root, ZWDataChangeType type, ZDataHolder data, void *arg);

			ZWay							_zway;
			ZWBYTE							_deviceId;
			ZWBYTE							_instanceId;
			std::string						_scale;
			std::string						_path;
			int								_id;
		};
	}
}

#endif /* !ZSENSORMULTILEVEL_H_ */