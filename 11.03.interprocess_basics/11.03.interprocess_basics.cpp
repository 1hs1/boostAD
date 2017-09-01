// 11.03.interprocess_basics.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/atomic.hpp>
#include <iostream>

// atomic 에서 mutex를 사용하는지 검사하기 위함
typedef boost::atomic<int> atomic_t;
#if (BOOST_ATOMIC_INT_LOCK_FREE != 2)
// mutex 를 사용한다면 이 예제는 비정상 동작 할 수 있음
#error "This code requires lock-free boost::atomic<int>"
#endif


int main() {
	// shared memory 로드 (없는 경우 생성)
	boost::interprocess::managed_shared_memory
		segment(boost::interprocess::open_or_create, "shm-cache", 1024); // shared memory 이름 과 크기

	atomic_t& atomic
		= *segment.find_or_construct<atomic_t> // 변수 로드 (없으면 할당)
		("shm-counter") // shared memory 내 변수명
		(0)             // 할당 시 사용할 초기화 인자
		;

	std::cout << "I have index " << ++atomic << std::endl;	// ++
	system("pause");

	int snapshot = --atomic;	// --

	// 0 이면 변수를 shared memory 에서 삭제
	if (!snapshot) {
		segment.destroy<atomic_t>("shm-counter");
		boost::interprocess::shared_memory_object
			::remove("shm-cache");

		std::cout << "destroyed counter" << std::endl;
		system("pause");
	}

	// 공유 메모리(shared memory) 는 프로세스간 데이터를 share 할 수 있는 가장 빠른 방법
}
