#pragma once

#include "tp_timer.h"

#include "../detail/tcp_connection.h"
#include "../detail/tcp_listener.h"

#include <boost/lexical_cast.hpp>

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


		// listener 추가/삭제 기능 추가
		template <class Functor>
		void add_listener(unsigned short port_num, const Functor& f) {
			listeners_map_t::const_iterator it = listeners_.find(port_num);
			if (it != listeners_.end()) {
				throw std::logic_error(
					"Such listener for port '"
					+ boost::lexical_cast<std::string>(port_num)
					+ "' already created"
				);
			}

			listeners_[port_num] = boost::make_shared<detail::tcp_listener>(boost::ref(ios_), port_num, f);	// 반드시 shared_ptr로

			// accepting 시작
			listeners_[port_num]->push_task();
		}

		void remove_listener(unsigned short port_num) {
			listeners_map_t::iterator it = listeners_.find(port_num);
			if (it == listeners_.end()) {
				throw std::logic_error(
					"No listener for port '"
					+ boost::lexical_cast<std::string>(port_num)
					+ "' created"
				);
			}

			(*it).second->stop();
			listeners_.erase(it);
		}

	private:
		// listener 를 모아두는 container
		typedef std::map<
			unsigned short,
			boost::shared_ptr<detail::tcp_listener>
		> listeners_map_t;
		listeners_map_t listeners_;

	};

} // namespace tp_network
