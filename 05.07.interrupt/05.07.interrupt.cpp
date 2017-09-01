// 05.07.interrupt.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <boost/thread.hpp>

//#define BOOST_THREAD_DONT_PROVIDE_INTERRUPTIONS

void InterruptionCheck()
{
	std::cout << "thread id : " << boost::this_thread::get_id() << std::endl;
	try
	{
		while (true)
		{
			boost::this_thread::interruption_point();
		}
	}
	catch (boost::thread_interrupted& /*e*/) // not std::exception
	{
		std::cout << "thread interrupted!!!!!" << std::endl;
		system("pause");
	}
}


int main()
{
	boost::thread t(&InterruptionCheck);
	//t.interrupt();
	t.join();

	return 0;
}
