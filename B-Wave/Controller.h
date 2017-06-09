#ifndef CONTROLLER_H_
# define CONTROLLER_H_

#include "Device.h"

namespace BoxAPI
{
	class BWave;
	class Controller
	{
	public:
		typedef _ZWControllerState ControllerState;

		~Controller();

		const std::vector<std::shared_ptr<BoxAPI::Device>>	&getDevices() const;
		const std::shared_ptr<BoxAPI::Device>				getDevice(int id) const;


		bool												setInclusionMode(bool startStop) const;
		bool												setExclusionMode(bool startStop) const;
		ControllerState										getState() const;

	private:
		friend class BoxAPI::BWave;

		Controller();

		bool			init();
		static void		print_D_I_CC_event(const ZWay zway, ZWDeviceChangeType type, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE command_id, void *arg);
		static void		controllerStateChanged(const ZDataRootObject root, ZWDataChangeType type, ZDataHolder data, void * arg);

		void			newDevice(ZWBYTE id);

		std::vector<std::shared_ptr<BoxAPI::Device>>	_devices;
		ZWLog											_logger;
		ZWay											_zway;

	};
}

#endif /* !CONTROLLER_H_ */