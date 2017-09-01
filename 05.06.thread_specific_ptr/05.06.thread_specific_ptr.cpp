// 05.06.thread_specific_ptr.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>

#include <boost/noncopyable.hpp>
#include <boost/thread/thread.hpp>
class connection : boost::noncopyable {
public:
	connection() : open_count_(0)
	{
		std::cout << "construct connection. threadid : " << boost::this_thread::get_id() << std::endl;
	}

	~connection()
	{
		std::cout << "destroy connection threadid : " << boost::this_thread::get_id() << std::endl;
	}

	// ������ ���� �� �ð��� �� �ɸ���
	void open();

	void send_result(int result);

	// �ٸ� �޼ҵ��
	// ...
	int open_count_;
};

// ��� ����
#include <boost/thread/tss.hpp>
connection& get_connection();

// �ҽ� ����
boost::thread_specific_ptr<connection> connection_ptr;
//thread_local boost::shared_ptr<connection> connection_ptr;

connection& get_connection() {
	connection* p = connection_ptr.get();
	if (!p) {
		connection_ptr.reset(new connection);
		p = connection_ptr.get();
		p->open();
	}

	return *p;
}


void task() {
	int result = 2;
	// �� ���� ������ �Ѵ�
	// ...

	// ����� ������
	get_connection().send_result(result);
}

void connection::open() {
	assert(!open_count_);
	open_count_ = 1;
}

void connection::send_result(int /*result*/) {}

void run_tasks() {
	for (std::size_t i = 0; i < 10000; ++i) {
		task();
	}
}

int main()
{
	boost::thread t1(&run_tasks);
	boost::thread t2(&run_tasks);
	boost::thread t3(&run_tasks);
	boost::thread t4(&run_tasks);

	// ��� �۾��� ������ ������ ��ٸ��� 
	t1.join();
	t2.join();
	t3.join();
	t4.join();

	while (1)
	{
		if (_kbhit())
		{
			if (_getch() == 27)	// ESC key
			{
				break;
			}
		}
	}
}

