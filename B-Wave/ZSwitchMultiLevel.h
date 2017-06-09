#ifndef ZSWITCHMULTILEVEL_H_
# define ZSWITCHMULTILEVEL_H_

#include "ICommand.h"

namespace BoxAPI
{
	class Device;
	namespace Command
	{
		class ZSwitchMultiLevel : public ICommand
		{

		public:
			~ZSwitchMultiLevel();

			void						setLevel(int level);
			int							getLevel() const;
			virtual int					getDeviceId() const;
			virtual CommandType			getType() const;
			virtual int					getInstance() const;

		private:
			friend class BoxAPI::Device;

			ZSwitchMultiLevel(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id);
			static void	CBEvent(const ZDataRootObject root, ZWDataChangeType type, ZDataHolder data, void *arg);

			ZWay							_zway;
			ZWBYTE							_deviceId;
			ZWBYTE							_instanceId;
			std::string						_path;
			int								_id;
		};
	}
}

#endif /* !ZSWITCHMULTILEVEL_H_ */
