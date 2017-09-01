// 06.04.Accepting.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

using namespace tp_network;

const unsigned short g_port_num = 65001;

class authorizer;
typedef boost::shared_ptr<authorizer> authorizer_ptr;

class authorizer : public boost::enable_shared_from_this<authorizer> {		// enable_shared_from_this

	explicit authorizer(const detail::tcp_connection_ptr& connection)
		: connection_(connection)
	{}

public:
	static void on_connection_accpet(const detail::tcp_connection_ptr& connection) {

		std::cout << "connected" << std::endl;

		authorizer_ptr auth(new authorizer(connection));	// �ݵ�� sahred_ptr -> enable_shared_from_this ����� ����

		auth->connection_.async_read(
			boost::asio::buffer(auth->message_),
			boost::bind(
				&authorizer::on_data_recieve,
				auth,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred
			),
			1
		);
	}

	void on_data_recieve(const boost::system::error_code& error, std::size_t bytes_recieved) {

		std::cout << "received : " << bytes_recieved << " bytes" << std::endl;

		if (error) {
			std::cerr << "authorizer.on_data_recieve: error during recieving response: " << error << '\n';
			assert(false);
		}

		if (bytes_recieved == 0) {
			std::cerr << "authorizer.on_data_recieve: zero bytes recieved\n";
			assert(false);
		}

		// `message_`�� �����Ͱ� ������ ���� ��� ���� �۾��� �� �� �ִ� 
		message_[0] = 'O';
		message_[1] = 'K';
		std::size_t bytes_to_send = 2;
		// ...

		// `message_`�� ������ �־������ ��������
		connection_.async_write(
			boost::asio::buffer(message_, bytes_to_send),
			boost::bind(
				&authorizer::on_data_send,
				shared_from_this(),		// shared_from_this
				boost::asio::placeholders::error
			)
		);
	}

	void on_data_send(const boost::system::error_code& error) {
		if (error) {
			std::cerr << "authorizer.on_data_send: error during sending response: " << error << '\n';
			assert(false);
		}

		std::cout << "sent data" << std::endl;

		connection_.shutdown();
	}

private:
	detail::tcp_connection_ptr connection_;
	boost::array<char, 512> message_;
};


int main()
{
	tasks_processor::get().add_listener(g_port_num, &authorizer::on_connection_accpet);
	tasks_processor::get().start();

	// �����ڷ� : https://www.slideshare.net/jacking/kgc-2012boostasio

    return 0;
}

