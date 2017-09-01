// 06.03.Network.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <boost/asio/placeholders.hpp>
#include <boost/bind.hpp>

using namespace tp_network;

const unsigned short g_port_num = 65001;
bool g_authed = false;

void send_auth_task() {

	std::cout << "creating connection and connecting" << std::endl;

	detail::tcp_connection_ptr soc = tasks_processor::get().create_connection("127.0.0.1", g_port_num);
	boost::shared_ptr<std::string> data = boost::make_shared<std::string>("auth_name");

	std::cout << "sending packet" << std::endl;

	// 1. ������(write), ������ �Ϸ� ��ٸ� (non-blocking)
	// 2. ������ �Ϸ� �Ǿ��ٸ�, �ޱ� ��� (=recieve_auth_task)
	soc.async_write(
		boost::asio::buffer(*data),
		boost::bind(
			&recieve_auth_task,
			boost::asio::placeholders::error,
			soc,
			data
		)
	);
}

void recieve_auth_task(const boost::system::error_code& err, const detail::tcp_connection_ptr& soc, const boost::shared_ptr<std::string>& data) {
	if (err) {
		std::cerr << "recieve_auth_task: Client error on recieve: " << err.message() << '\n';
		assert(false);
	}

	std::cout << "sent packet" << std::endl;

	std::cout << "receive packet" << std::endl;

	// 1. �ޱ� ��� (non-blocking)
	// 2. �ޱ� �Ϸ�Ǿ��ٸ�, ��Ŷ ó�� (=finsh_socket_auth_task)
	soc.async_read(
		boost::asio::buffer(&(*data)[0], data->size()),
		boost::bind(
			&finsh_socket_auth_task,
			boost::asio::placeholders::error,	// boost::asio::placeholders::error �� ��� _1
			boost::asio::placeholders::bytes_transferred,	// boost::asio::placeholders::bytes_transferred �� ��� _2
			soc,
			data
		),
		1
	);
}

void finsh_socket_auth_task(
	const boost::system::error_code& err,
	std::size_t bytes_transfered,
	const detail::tcp_connection_ptr& soc,
	const boost::shared_ptr<std::string>& data)
{
	if (err && err != boost::asio::error::eof) {
		std::cerr << "finsh_socket_auth_task: Client error on recieve: " << err.message() << '\n';
		assert(false);
	}

	if (bytes_transfered != 2) {
		std::cerr << "finsh_socket_auth_task: wrong bytes count\n";
		assert(false);
	}

	data->resize(bytes_transfered);
	if (*data != "OK") {
		std::cerr << "finsh_socket_auth_task: wrong response: " << *data << '\n';
		assert(false);
	}

	std::cout << "received packet" << std::endl;

	g_authed = true;
	soc.shutdown();
	std::cout << "shuting down" << std::endl;
	tasks_processor::get().stop();
}

int main()
{
	// ��ǥ : TCP ����, ����, �ޱ�

	send_auth_task();

	tasks_processor::get().start();

    return 0;
}

