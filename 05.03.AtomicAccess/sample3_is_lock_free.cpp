#include "stdafx.h"
#include <cassert>
#include <cstddef>

#include <boost/thread/thread.hpp>
#include <boost/atomic.hpp>




struct TEST
{
	int aaa;
	int bbb;
	std::string abc;
};

void sample_is_lock_free() {

	boost::atomic<int> v_int(0);
	std::cout << "pod int - is_lock_free ? " << v_int.is_lock_free() << std::endl;
	//v_int has  fetch_add, fetch_and, fetch_sub, fetch_...
	//v_int uses InterLock... for sync

	boost::atomic<TEST> v_test;
	std::cout << "struct TEST - is_lock_free ? " << v_test.is_lock_free() << std::endl;
	// v_test doesn't have  fetch_...
	//v_test uses ScopedLock(Complex Interlocked)... for sync

	// Notice : is_lock_free()는 런타임에서만 사용 가능. (즉, static_assert() 같은 곳에서 사용할 수 없음)
	//			std::atomic은 POD 자료형에 대해서는 완전 원자적 접근이 가능함.
	//			하지만, 사용자 타입의 경우 Mutex등의 방식으로 처리 한다고 함. 이는 컴파일러마다 다르다고 함.
	//			(윈도우의 경우 mutex는 아니고 좀 더 복잡한 InterLocked()류의 함수로 처리됨)
}
