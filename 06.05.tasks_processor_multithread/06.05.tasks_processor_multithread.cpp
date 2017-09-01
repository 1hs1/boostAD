// 06.05.tasks_processor_multithread.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <conio.h>
#include <iostream>

#include "tasks_processor_multithread.h"
using namespace tp_multithread;

// tasks_processor_base.hpp�� tasks_processor Ŭ������ �Ϻ� 
// �ҽ� ������ ��򰡿� ���ǵǾ�߸� �Ѵ�
tasks_processor& tasks_processor::get() {
	static tasks_processor proc;
	return proc;
}

const std::size_t threads_count = 5;
#include <boost/thread/barrier.hpp>
boost::barrier g_barrier(threads_count);

void multythread_test() {
	std::cout << "multythread_test " << boost::this_thread::get_id() << std::endl;
	g_barrier.wait();
	tasks_processor::get().stop();
}

int main()
{
	std::cout << "Current Thread " << boost::this_thread::get_id() << std::endl;

	for (std::size_t i = 0; i < threads_count; ++i) {
		tasks_processor::get().push_task(&multythread_test);
	}
	time_t t1 = time(NULL);
	tasks_processor::get().start_multiple(threads_count);
	time_t t2 = time(NULL);
	// io_service�� OS ������ ���� �ð��� ������
	// 1���� ������ �д�
	assert(t2 - t1 < 1);

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
