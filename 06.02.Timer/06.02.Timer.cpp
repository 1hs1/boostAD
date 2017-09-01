// 06.02.Timer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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

#include <boost/date_time/posix_time/posix_time.hpp>	// boost::posix_time 를 쓰기 위함

int main()
{
	const int seconds_to_wait = 3;	// 3초 뒤에 종료할 것임
	int i = 0;

	// 지금부터 일정시간 뒤에 호출되길 원함
	tasks_processor::get().run_after(
		boost::posix_time::seconds(seconds_to_wait),
		boost::bind(&test_func_finisher, boost::ref(i))
	);

	// 지정된 시각(at) 에 호출되길 원함
	tasks_processor::get().run_at(boost::posix_time::from_time_t(time(NULL) + 1), &test_func1);

	int t1 = static_cast<int>(time(NULL));
	assert(i == 0);

	tasks_processor::get().start();
	assert(i == 1);		// test_func_finisher 에서 1로 세팅함

	int t2 = static_cast<int>(time(NULL));
	assert(t2 - t1 >= seconds_to_wait); // seconds_to_wait 초만큼 지나야 함

    return 0;
}

