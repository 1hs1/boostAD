#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/smart_ptr.hpp>

#include <iostream>

namespace detail
{

	class tcp_connection_ptr {
		boost::shared_ptr<boost::asio::ip::tcp::socket> socket_;
	public:
		// �̹� ������ socket�� ������ ���� ������
		explicit tcp_connection_ptr(
			boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
			: socket_(socket)
		{}

		// ���� socket�� �����ϴ� ������
		explicit tcp_connection_ptr(
			boost::asio::io_service& ios,
			const boost::asio::ip::tcp::endpoint& endpoint)
			: socket_(boost::make_shared<boost::asio::ip::tcp::socket>(
				boost::ref(ios)
				))
		{
			try {
				socket_->connect(endpoint);		// ���� �õ�, �񵿱������� async_connect ���
			}
			catch (boost::system::error_code& e) {
				std::cout << e.message() << std::endl;
			}
		}

		template <class Functor>
		void async_write(
			const boost::asio::const_buffers_1& buf, const Functor& func_completed) const
		{
			boost::asio::async_write(*socket_, buf, func_completed);
		}

		template <class Functor>
		void async_write(
			const boost::asio::mutable_buffers_1& buf, const Functor& func_completed) const
		{
			boost::asio::async_write(*socket_, buf, func_completed);
		}

		template <class Functor>
		void async_read(
			const boost::asio::mutable_buffers_1& buf,
			const Functor& f,
			std::size_t at_least_bytes) const
		{
			// at_least : at_least_bytes ��ŭ�̶� read �� �ȴٸ� callback
			boost::asio::async_read(
				*socket_, buf, boost::asio::transfer_at_least(at_least_bytes), f
			);
		}

		void shutdown() const {
			socket_->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
			socket_->close();
		}
	};

}
