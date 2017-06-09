#ifndef ZSWITCHBINARY_H_
# define ZSWITCHBINARY_H_

#include "ICommand.h"

namespace BoxAPI
{
	class Device;
	namespace Command
	{
		class ZSwitchBinary : public ICommand
		{
		public:
			virtual	~ZSwitchBinary();

			virtual int					getDeviceId() const;
			virtual CommandType			getType() const;
			virtual int					getInstance() const;

			void						setSwitch(bool);
			bool						getSwitch() const;
			bool						isFailed() const;

		private:

			friend class BoxAPI::Device;

			ZSwitchBinary(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id);

			static void	CBEvent(const ZDataRootObject root, ZWDataChangeType type, ZDataHolder data, void *arg);

			ZWay							_zway;
			ZWBYTE							_deviceId;
			ZWBYTE							_instanceId;
		};
	}
}

#endif /* !ZSWITCHBINARY_H_ */