// 11.07.coroutines.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
// �ڷ�ƾ - ���¸� ������ �� ������ ��� �̷��

#include "stdafx.h"

#include "test_unit.h"
#include <boost/bind.hpp>
#include <iostream>
#include <boost/variant/get.hpp>

bool bUsed;

Ctest_unit::Ctest_unit()
{
	bUsed = false;
}

Ctest_unit::~Ctest_unit()
{
	bUsed = false;
	std::cout << "delete Ctest_unit" << std::endl;
}

void Ctest_unit::Init()
{
	bUsed = true;
	boost::thread(boost::bind(&Ctest_unit::coroutine_task)).detach();
}


void Ctest_unit::coroutine_task()
{
	corout_test::push_type coroutine(Ctest_unit::coroutine_sub);
	std::cout << "begin coroutine_task()" << std::endl;

	while (bUsed)
	{
		boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
		std::cout << "coroutine_task()" << std::endl;
		coroutine(boost::make_tuple(bUsed, 1));
	}

	coroutine(boost::make_tuple(bUsed, 1));
}

void Ctest_unit::coroutine_sub(corout_test::pull_type& caller)
{
	auto args = caller.get();

	while (boost::get<0>(args) && bUsed)
	{
		auto args = caller.get();

		boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
		std::cout << "coroutine_sub()" << std::endl;
		caller();
	}
}