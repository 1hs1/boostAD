// 11.03.interprocess_basics.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/atomic.hpp>
#include <iostream>

// atomic ���� mutex�� ����ϴ��� �˻��ϱ� ����
typedef boost::atomic<int> atomic_t;
#if (BOOST_ATOMIC_INT_LOCK_FREE != 2)
// mutex �� ����Ѵٸ� �� ������ ������ ���� �� �� ����
#error "This code requires lock-free boost::atomic<int>"
#endif


int main() {
	// shared memory �ε� (���� ��� ����)
	boost::interprocess::managed_shared_memory
		segment(boost::interprocess::open_or_create, "shm-cache", 1024); // shared memory �̸� �� ũ��

	atomic_t& atomic
		= *segment.find_or_construct<atomic_t> // ���� �ε� (������ �Ҵ�)
		("shm-counter") // shared memory �� ������
		(0)             // �Ҵ� �� ����� �ʱ�ȭ ����
		;

	std::cout << "I have index " << ++atomic << std::endl;	// ++
	system("pause");

	int snapshot = --atomic;	// --

	// 0 �̸� ������ shared memory ���� ����
	if (!snapshot) {
		segment.destroy<atomic_t>("shm-counter");
		boost::interprocess::shared_memory_object
			::remove("shm-cache");

		std::cout << "destroyed counter" << std::endl;
		system("pause");
	}

	// ���� �޸�(shared memory) �� ���μ����� �����͸� share �� �� �ִ� ���� ���� ���
}
