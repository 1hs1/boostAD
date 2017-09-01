// 05.08.thread_group.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <cassert>
#include <boost/atomic.hpp>
#include <boost/thread.hpp>

boost::atomic_int g_count(0);

void some_function() {

	try
	{
		//boost::this_thread::sleep_for(boost::chrono::seconds(1));
		++g_count;
	}
	catch (boost::thread_interrupted& /*e*/) // not std::exception
	{
		std::cout << "thread interrupted!!!!!" << std::endl;
	}
  
}

int main() {
	boost::thread t1(&some_function);
	boost::thread t2(&some_function);
	boost::thread t3(&some_function);
	// ...

	t1.join();
	t2.join();
	t3.join();

	assert(g_count == 3);

	// ������ 10���� ���۽�Ų��
	boost::thread_group threads;
	for (unsigned i = 0; i < 10; ++i) {
		threads.create_thread(&some_function);
	}
	
	//threads.interrupt_all();

	threads.join_all();

	//threads.interrupt_all();

	assert(g_count == 13);
}