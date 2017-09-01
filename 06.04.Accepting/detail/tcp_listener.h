#pragma once

#include <boost/asio/placeholders.hpp>

#include <boost/shared_ptr.hpp>

// = 동작 방식 =
// 1. 접속 대기 (push_task)
// 2. 접속 처리 (handle_accept)
//		외부에서 등록한 핸들러 처리
// 3. 1번 다시

namespace detail {
	class tcp_listener : public boost::enable_shared_from_this<tcp_listener> {	// <=== enable_shared_from_this
		typedef boost::asio::ip::tcp::acceptor acceptor_t;
		acceptor_t acceptor_;
		boost::function<void(tcp_connection_ptr)> func_;
	public:
		template <class Functor>
		tcp_listener(
			boost::asio::io_service& io_service,
			unsigned short port,
			const Functor& task_unwrapped)
			: acceptor_(io_service, boost::asio::ip::tcp::endpoint(
				boost::asio::ip::tcp::v4(), port
			))
			, func_(task_unwrapped)
		{}

		void stop() {
			acceptor_.close();
		}

		void push_task() {
			if (!acceptor_.is_open()) {
				return;
			}

			typedef boost::asio::ip::tcp::socket socket_t;
			boost::shared_ptr<socket_t> socket = boost::make_shared<socket_t>(
				boost::ref(acceptor_.get_io_service())
				);

			acceptor_.async_accept(*socket, boost::bind(
				&tcp_listener::handle_accept,
				this->shared_from_this(),	// <=== shared_from_this
				tcp_connection_ptr(socket),
				boost::asio::placeholders::error
			));
		}

	private:
		void handle_accept(
			const tcp_connection_ptr& new_connection,
			const boost::system::error_code& error)
		{
			push_task();
			if (!error) {
				make_task_wrapped(boost::bind(func_, new_connection))
					(); // Running the task
			}
			else {
				std::cerr << error << '\n';
			}
		}
	}; // class tcp_listener
} // namespace detail
