#ifndef CONNECTION_H_
# define CONNECTION_H_

#include "Device.h"
#include "ControllerEvent.h"
#include "MessageHandler.h"

namespace BoxAPI
{
	namespace Network
	{
		class Connection
		{
		public:
			enum Status
			{
				Connecting,
				Open,
				Failed,
				NormalClosed,
				Droped,
				Destructed
			};

			Connection();
			~Connection();

			void			init();

			void			connect(const std::string &uri, const std::string &login, const std::string &password);

			void			close();

			void onConnected();
			void onClose(sio::client::close_reason const& reason);
			void onFail();

			Status			getStatus();
		private:

			void	onNewDevice(std::shared_ptr<BoxAPI::ControllerEvent::Data::Device> data);
			void	onDeleteDevice(std::shared_ptr<BoxAPI::ControllerEvent::Data::Device> data);
			void	onNewCommand(std::shared_ptr<BoxAPI::ControllerEvent::Data::Command> data);
			void	onUpdateCommand(std::shared_ptr<BoxAPI::ControllerEvent::Data::Command> data);
			void	onControllerStateChanged(int state);

			Status			m_status;
			sio::client		_client;
			MessageHandler	_handler;

			std::string		_login;
			std::string		_password;
		};
	}
}

#endif /* !CONNECTION_H_ */
