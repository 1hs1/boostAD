// 06.02.Timer.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include "tp/tp_timer.h"

using namespace tp_timer;




void test_func_finisher(int& i) {
	i = 1;
	std::cout << "it gonna be stooped !!!" << std::endl;
	tasks_processor::get().stop();
}

void test_func1() {
	throw std::logic_error("It works!");
}

#include <boost/date_time/posix_time/posix_time.hpp>	// boost::posix_time �� ���� ����

int main()
{
	const int seconds_to_wait = 3;	// 3�� �ڿ� ������ ����
	int i = 0;

	// ���ݺ��� �����ð� �ڿ� ȣ��Ǳ� ����
	tasks_processor::get().run_after(
		boost::posix_time::seconds(seconds_to_wait),
		boost::bind(&test_func_finisher, boost::ref(i))
	);

	// ������ �ð�(at) �� ȣ��Ǳ� ����
	tasks_processor::get().run_at(boost::posix_time::from_time_t(time(NULL) + 1), &test_func1);

	int t1 = static_cast<int>(time(NULL));
	assert(i == 0);

	tasks_processor::get().start();
	assert(i == 1);		// test_func_finisher ���� 1�� ������

	int t2 = static_cast<int>(time(NULL));
	assert(t2 - t1 >= seconds_to_wait); // seconds_to_wait �ʸ�ŭ ������ ��

    return 0;
}

