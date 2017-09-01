// 11.07.coroutines.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
// 코루틴 - 상태를 저장한 후 실행을 잠시 미루기

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
	// 원래 프로그램으로 되돌아가기
	//caller(result);
	caller();

	std::size_t nIncrese = 0;
	while (1) {
		std::size_t max_characters_to_process = caller.get();
		std::cout << "coroutine_task get() :" << max_characters_to_process << std::endl;

		// 문자 처리
		// ...
		result.resize(result.size() + max_characters_to_process);

		std::cout << "coroutine_task loop:" << ++nIncrese << std::endl;

		// 결과를 반환
		// 원래 프로그램으로 되돌아감
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

	// 몇 가지 작업
	// ...
	spinlock_t spinlock;
	port_t port;

	std::size_t nIncrese = 0;
	while (!spinlock.try_lock()) {
		std::cout << "try_lock count:" << ++nIncrese << std::endl;

		// 스핀 잠금(spinlock)을 한번 더 잠그기 전에 
		//coroutine(10); // 짧은 지연 시간 두기
		coroutine(nIncrese);
	}
	// 스핀 잠금 잠그기
	// ...
	//assert(coroutine.get().size() == 10 * 100);
	//coroutine.get().clear();

	nIncrese = 0;
	while (!port.block_ready()) {
		std::cout << "block_ready count:" << ++nIncrese << std::endl;

		// 다시 데이터를 가져오기 전에
		//coroutine(300);  // 좀 큰 지연 시간 두기
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