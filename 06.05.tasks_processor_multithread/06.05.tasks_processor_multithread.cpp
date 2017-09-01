// 06.05.tasks_processor_multithread.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <conio.h>
#include <iostream>

#include "tasks_processor_multithread.h"
using namespace tp_multithread;

// tasks_processor_base.hpp의 tasks_processor 클래스의 일부 
// 소스 파일의 어딘가에 정의되어야만 한다
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
	// io_service와 OS 에서의 지연 시간을 고려해
	// 1초의 여유를 둔다
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

