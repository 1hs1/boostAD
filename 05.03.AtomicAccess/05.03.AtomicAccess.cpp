// 05.03.AtomicAccess.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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

	// Notice : �����Ϸ��� ���� std::atomic �� boost::atomic ���� �� ���� �� ����

	return 0;
}
