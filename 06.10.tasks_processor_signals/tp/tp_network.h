#pragma once

#include "tp_timer.h"

#include "../detail/tcp_connection.h"

namespace tp_network {

	class tasks_processor : public tp_timer::tasks_processor {

	public:
		static tasks_processor& get() {
			static tasks_processor s_tasks_processor;
			return s_tasks_processor;
		};

		detail::tcp_connection_ptr create_connection(const char* addr, unsigned short port_num) {
			return detail::tcp_connection_ptr(ios_, boost::asio::ip::tcp::endpoint(
				boost::asio::ip::address_v4::from_string(addr), port_num
			));
		}
	};

} // namespace tp_network
