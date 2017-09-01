#include "stdafx.h"
#include <cassert>
#include <cstddef>

#include <boost/thread/thread.hpp>
#include <boost/atomic.hpp>

boost::atomic<int> shared_i3(0);

void do_inc3() {
	for (std::size_t i = 0; i < 300000; ++i) {

		const int i_snapshot = ++shared_i3;

	}
}

void do_dec3() {
	for (std::size_t i = 0; i < 300000; ++i) {

		const int i_snapshot = --shared_i3;

	}
}

void sample_atomic() {
	boost::thread t1(&do_inc3);
	boost::thread t2(&do_dec3);

	t1.join();
	t2.join();

	assert(shared_i3 == 0); // 동기화 처리됨.
	std::cout << __FUNCTION__ << " shared_i3 == " << shared_i3 << std::endl;
}
