#include "stdafx.h"
#include <cassert>
#include <cstddef>

#include <boost/thread/thread.hpp>

int shared_i = 0;

void do_inc() {
	for (std::size_t i = 0; i < 30000; ++i) {

		const int i_snapshot = ++shared_i;

	}
}

void do_dec() {
	for (std::size_t i = 0; i < 30000; ++i) {

		const int i_snapshot = --shared_i;

	}
}

void sample_no_mutex() {
	boost::thread t1(&do_inc);
	boost::thread t2(&do_dec);

	t1.join();
	t2.join();

	assert(shared_i == 0); // 0 �� ���� �ְ� �ƴ� ���� �ִ�. ���ڼ��� ������� ����.
	std::cout << __FUNCTION__ << " shared_i == " << shared_i << std::endl;
}