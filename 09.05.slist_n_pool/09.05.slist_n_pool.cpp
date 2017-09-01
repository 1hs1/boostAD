// 09.05.slist_n_pool.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <boost/function.hpp>
#include <iostream>

#include "sample_slist.h"
#include "sample_std_list.h"


template <class ListT>
void test_lists() {
	typedef ListT list_t;

	// 10000000 개의 0 삽입
	list_t  list(10000000, 0);

	// 0~999 까지 역순으로 넣기
	for (int i = 0; i < 1000; ++i) {
		list.insert(list.begin(), i);
	}

	// 어떤 값 찾기
	typedef typename list_t::iterator iterator;
	iterator it = std::find(list.begin(), list.end(), 777);
	assert(it != list.end());

	// 몇몇 값 삭제
	for (int i = 0; i < 100; ++i) {
		list.pop_front();
	}

	// 반복자는 여전히 유효하며, 같은 값을 가리키고 있다
	assert(it != list.end());
	assert(*it == 777);

	// 단방향 리스트 때문에 컴파일 에러남
	// --it;

	// 값을 더 삽입
	for (int i = -100; i < 10; ++i) {
		list.insert(list.begin(), i);
	}

	// 반복자는 여전히 유효하며, 같은 값을 가리키고 있다
	assert(it != list.end());
	assert(*it == 777);

	list_specific(list, it);
}

int main()
{
	auto time_checker = [](boost::function<void()> sample) {
		auto const start = std::chrono::system_clock::now();
		sample();
		auto const end = std::chrono::system_clock::now();
		std::cout << "elapsed time : " << std::chrono::duration<double>(end - start).count() << "ms" << std::endl;
	};

	//- release 에서 테스트 해보셈

	time_checker( test_lists<slist_t> );

	time_checker( test_lists<std::list<int> > );

    return 0;
}

