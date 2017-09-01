// 09.05.slist_n_pool.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <boost/function.hpp>
#include <iostream>

#include "sample_slist.h"
#include "sample_std_list.h"


template <class ListT>
void test_lists() {
	typedef ListT list_t;

	// 10000000 ���� 0 ����
	list_t  list(10000000, 0);

	// 0~999 ���� �������� �ֱ�
	for (int i = 0; i < 1000; ++i) {
		list.insert(list.begin(), i);
	}

	// � �� ã��
	typedef typename list_t::iterator iterator;
	iterator it = std::find(list.begin(), list.end(), 777);
	assert(it != list.end());

	// ��� �� ����
	for (int i = 0; i < 100; ++i) {
		list.pop_front();
	}

	// �ݺ��ڴ� ������ ��ȿ�ϸ�, ���� ���� ����Ű�� �ִ�
	assert(it != list.end());
	assert(*it == 777);

	// �ܹ��� ����Ʈ ������ ������ ������
	// --it;

	// ���� �� ����
	for (int i = -100; i < 10; ++i) {
		list.insert(list.begin(), i);
	}

	// �ݺ��ڴ� ������ ��ȿ�ϸ�, ���� ���� ����Ű�� �ִ�
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

	//- release ���� �׽�Ʈ �غ���

	time_checker( test_lists<slist_t> );

	time_checker( test_lists<std::list<int> > );

    return 0;
}

