#include "stdafx.h"
#include <cassert>
#include <cstddef>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

int shared_i2 = 0;
boost::mutex i_mutex2;	//

void do_inc2() {
	for (std::size_t i = 0; i < 300000; ++i) {

		boost::lock_guard<boost::mutex> lock(i_mutex2);	//
		const int i_snapshot = ++shared_i2;

	}
}

void do_dec2() {
	for (std::size_t i = 0; i < 300000; ++i) {

		boost::lock_guard<decltype(i_mutex2)> lock(i_mutex2);	//
		const int i_snapshot = --shared_i2;

	}
}

void sample_mutex() {
	boost::thread t1(&do_inc2);
	boost::thread t2(&do_dec2);

	t1.join();
	t2.join();

	assert(shared_i2 == 0); // 동기화 처리됨.
	std::cout << __FUNCTION__ << " shared_i2 == " << shared_i2 << std::endl;
}
