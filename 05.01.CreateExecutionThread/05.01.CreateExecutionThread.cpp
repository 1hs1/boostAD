// 05.01.CreateExecutionThread.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <iostream>

//#define BOOST_THREAD_VERSION 4

#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>

// 뮤텍스는 다음 챕터에서 설명됨. 일단 pass
boost::mutex s_mx;

void resource_loader_sample(std::string filename) {

	auto logger = [filename](std::string txt) {
		s_mx.lock();
		std::cout << "\tTID[" << boost::this_thread::get_id() << "] " << filename << " => " << txt << std::endl;
		s_mx.unlock();
	};

	logger("start to load a file");


	auto readFunc = [&](std::string filename) {
		// 파일 리딩이 좀 오래 걸린다고 가정하기 위한 테스트 코드
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
	//- 스레드 생성해서 작업을 수행시킬 수 있습니다.
	std::cout << "let's loading!" << std::endl;

	//- bind는 01.10 참고
	boost::thread(boost::bind(&resource_loader_sample, "3.dat"))
		.detach();

	std::cout << "loading is working on background" << std::endl;

	// Notice : detach 하지 않는다면 boost::thread가 소멸되면 생성된 thread는 소멸(terminate) 시킨다
}

void sample2_create_and_join()
{
	//- 스레드가 끝날 때 까지 기다릴 수 있습니다.
	std::cout << "let's loading! I'll wait until finished" << std::endl;

	boost::thread(boost::bind(&resource_loader_sample, "3.dat"))
		.join();

	std::cout << "loading is ended" << std::endl;

	// Notice : 왠만하면 detach 해서 사용하세요. 참고 : Effective Modern C++ Item #37
}

void sample3_create_only()
{
#if BOOST_THREAD_VERSION != 2
	std::cout << "let's loading! It goona be crashed TT TT" << std::endl;
#else
	std::cout << "let's loading!" << std::endl;
#endif

	//- detach/join 안합니다.
	//- BOOST_THREAD_VERSION 2(default) => 소멸자의 기본 행동은 detach 입니다. 문제 없습니다.
	//- BOOST_THREAD_VERSION 3,4,5 => 소멸자의 기본 행동은 std::teminate(thread) 입니다. abort() 발생합니다.
	boost::thread(boost::bind(&resource_loader_sample, "3.dat"));

	// Notice : BOOST_THREAD_VERSION이 어떻게 변할 지 모르기 때문에 detach/join 을 명확히 사용하도록 합시다.
}

#include <boost/thread/scoped_thread.hpp>
void sample4_scoped_thread()
{
	std::cout << "let's test scope" << std::endl;

	// 스레드가 소멸될 때 액션을 결정 해 준다
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
