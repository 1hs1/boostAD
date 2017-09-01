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

	// Notice : is_lock_free()�� ��Ÿ�ӿ����� ��� ����. (��, static_assert() ���� ������ ����� �� ����)
	//			std::atomic�� POD �ڷ����� ���ؼ��� ���� ������ ������ ������.
	//			������, ����� Ÿ���� ��� Mutex���� ������� ó�� �Ѵٰ� ��. �̴� �����Ϸ����� �ٸ��ٰ� ��.
	//			(�������� ��� mutex�� �ƴϰ� �� �� ������ InterLocked()���� �Լ��� ó����)
}
