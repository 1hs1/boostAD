// 05.03.AtomicAccess.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <chrono>
#include <iostream>

#include <boost/function.hpp>

int main()
{
	auto time_checker = [](boost::function<void()> sample) {
		auto const start = std::chrono::system_clock::now();
		sample();
		auto const end = std::chrono::system_clock::now();
		std::cout << "elapsed time : " << std::chrono::duration<double>(end - start).count() << "ms" << std::endl;
	};

	int cmd = 0;
	while (([&cmd]() { std::cout << "? "; std::cin >> cmd; return (0 != cmd); })())
	{
		switch (cmd) {
		case 1:time_checker(sample_mutex);break;
		case 2:time_checker(sample_atomic);break;
		case 3:sample_is_lock_free();break;
		default: break;
		}
	}

	// Notice : 컴파일러에 따라 std::atomic 이 boost::atomic 보다 더 빠를 수 있음

	return 0;
}
