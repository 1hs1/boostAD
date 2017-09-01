// 05.01.CreateExecutionThread.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <iostream>

//#define BOOST_THREAD_VERSION 4

#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>

// ���ؽ��� ���� é�Ϳ��� �����. �ϴ� pass
boost::mutex s_mx;

void resource_loader_sample(std::string filename) {

	auto logger = [filename](std::string txt) {
		s_mx.lock();
		std::cout << "\tTID[" << boost::this_thread::get_id() << "] " << filename << " => " << txt << std::endl;
		s_mx.unlock();
	};

	logger("start to load a file");


	auto readFunc = [&](std::string filename) {
		// ���� ������ �� ���� �ɸ��ٰ� �����ϱ� ���� �׽�Ʈ �ڵ�
		const int sleepCnt = boost::lexical_cast<int>(std::string(filename.begin(), filename.begin() + filename.find_first_of('.')));

		for (int i = 0; i < sleepCnt; ++i) {
			logger(".");
			boost::this_thread::sleep_for(boost::chrono::seconds(1));
		}
	};
	readFunc(filename);


	logger("ended to load a file");
}

void sample1_create_and_detach()
{
	//- ������ �����ؼ� �۾��� �����ų �� �ֽ��ϴ�.
	std::cout << "let's loading!" << std::endl;

	//- bind�� 01.10 ����
	boost::thread(boost::bind(&resource_loader_sample, "3.dat"))
		.detach();

	std::cout << "loading is working on background" << std::endl;

	// Notice : detach ���� �ʴ´ٸ� boost::thread�� �Ҹ�Ǹ� ������ thread�� �Ҹ�(terminate) ��Ų��
}

void sample2_create_and_join()
{
	//- �����尡 ���� �� ���� ��ٸ� �� �ֽ��ϴ�.
	std::cout << "let's loading! I'll wait until finished" << std::endl;

	boost::thread(boost::bind(&resource_loader_sample, "3.dat"))
		.join();

	std::cout << "loading is ended" << std::endl;

	// Notice : �ظ��ϸ� detach �ؼ� ����ϼ���. ���� : Effective Modern C++ Item #37
}

void sample3_create_only()
{
#if BOOST_THREAD_VERSION != 2
	std::cout << "let's loading! It goona be crashed TT TT" << std::endl;
#else
	std::cout << "let's loading!" << std::endl;
#endif

	//- detach/join ���մϴ�.
	//- BOOST_THREAD_VERSION 2(default) => �Ҹ����� �⺻ �ൿ�� detach �Դϴ�. ���� �����ϴ�.
	//- BOOST_THREAD_VERSION 3,4,5 => �Ҹ����� �⺻ �ൿ�� std::teminate(thread) �Դϴ�. abort() �߻��մϴ�.
	boost::thread(boost::bind(&resource_loader_sample, "3.dat"));

	// Notice : BOOST_THREAD_VERSION�� ��� ���� �� �𸣱� ������ detach/join �� ��Ȯ�� ����ϵ��� �սô�.
}

#include <boost/thread/scoped_thread.hpp>
void sample4_scoped_thread()
{
	std::cout << "let's test scope" << std::endl;

	// �����尡 �Ҹ�� �� �׼��� ���� �� �ش�
	{
		boost::thread t1(boost::bind(&resource_loader_sample, "3.dat"))
			, t2(boost::bind(&resource_loader_sample, "4.dat"))
			, t3(boost::bind(&resource_loader_sample, "5.dat"));

		boost::scoped_thread<boost::interrupt_and_join_if_joinable> st1(boost::move(t1));
		boost::scoped_thread<boost::join_if_joinable> st2(boost::move(t2));
		boost::scoped_thread<boost::detach> st3(boost::move(t3));
	}

	s_mx.lock();
	std::cout << "scope is ended" << std::endl;
	s_mx.unlock();
}


int main()
{
	int cmd = 0;
	while (([&cmd]() { std::cout << "? "; std::cin >> cmd; return (0 != cmd); })())
	{
		switch (cmd) {
		case 1:sample1_create_and_detach();break;
		case 2:sample2_create_and_join();break;
		case 3:sample3_create_only();break;
		case 4:sample4_scoped_thread();break;
		default: break;
		}
	}

	return 0;
}
