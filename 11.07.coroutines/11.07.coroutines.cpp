// 11.07.coroutines.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
// �ڷ�ƾ - ���¸� ������ �� ������ ��� �̷��

#include "stdafx.h"

#include <boost/coroutine/coroutine.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include "test_unit.h"

typedef boost::coroutines::coroutine<
	//std::string&(std::size_t max_characters_to_process)
	std::size_t
> corout_t;

void coroutine_task(corout_t::pull_type& caller) {
	std::string result;

	std::cout << "begin coroutine_task" << std::endl;
	// ���� ���α׷����� �ǵ��ư���
	//caller(result);
	caller();

	std::size_t nIncrese = 0;
	while (1) {
		std::size_t max_characters_to_process = caller.get();
		std::cout << "coroutine_task get() :" << max_characters_to_process << std::endl;

		// ���� ó��
		// ...
		result.resize(result.size() + max_characters_to_process);

		std::cout << "coroutine_task loop:" << ++nIncrese << std::endl;

		// ����� ��ȯ
		// ���� ���α׷����� �ǵ��ư�
		//caller(result);
		caller();
	} /*while*/
}


struct spinlock_t {
	bool try_lock() {
		static int i = 0;
		return i++ >= 5;
	}
};

struct port_t {
	bool block_ready() {
		static int i = 0;
		return i++ >= 5;
	}
};

int main() {
	//corout_t coroutine(coroutine_task);
	corout_t::push_type coroutine(coroutine_task);

	// �� ���� �۾�
	// ...
	spinlock_t spinlock;
	port_t port;

	std::size_t nIncrese = 0;
	while (!spinlock.try_lock()) {
		std::cout << "try_lock count:" << ++nIncrese << std::endl;

		// ���� ���(spinlock)�� �ѹ� �� ��ױ� ���� 
		//coroutine(10); // ª�� ���� �ð� �α�
		coroutine(nIncrese);
	}
	// ���� ��� ��ױ�
	// ...
	//assert(coroutine.get().size() == 10 * 100);
	//coroutine.get().clear();

	nIncrese = 0;
	while (!port.block_ready()) {
		std::cout << "block_ready count:" << ++nIncrese << std::endl;

		// �ٽ� �����͸� �������� ����
		//coroutine(300);  // �� ū ���� �ð� �α�
		coroutine(nIncrese);
		//std::string& s = coroutine.get();
		// ...
		//(void)s;
	}

	//assert(coroutine.get().size() == 10 * 300);


/*
	Ctest_unit *pCoroutine_test = new Ctest_unit();
	pCoroutine_test->Init();
	boost::this_thread::sleep_for(boost::chrono::seconds(5));

	delete pCoroutine_test;	

	boost::this_thread::sleep_for(boost::chrono::seconds(2));*/
}