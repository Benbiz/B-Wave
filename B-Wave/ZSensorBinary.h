#ifndef ZSENSORBINARY_H_
# define ZSENSORBINARY_H_

#include "ICommand.h"

namespace BoxAPI
{
	class Device;
	namespace Command
	{
		class ZSensorBinary : public ICommand
		{
		public:
			virtual	~ZSensorBinary();

			virtual int					getDeviceId() const;
			virtual CommandType			getType() const;
			virtual int					getInstance() const;

			bool						getValue() const;

			int							getId() const;
			bool						isFailed() const;

		private:
			friend class BoxAPI::Device;

			ZSensorBinary(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int id);

			static void	CBEvent(const ZDataRootObject root, ZWDataChangeType type, ZDataHolder data, void *arg);

			ZWay							_zway;
			ZWBYTE							_deviceId;
			ZWBYTE							_instanceId;
			std::string						_path;
			int								_id;
		};
	}
}
#endif /* !ZSENSORBINARY_H_ */