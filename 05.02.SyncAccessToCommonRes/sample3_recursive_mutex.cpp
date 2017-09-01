#include "stdafx.h"
#include <cassert>
#include <cstddef>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/recursive_mutex.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/ptr_container/ptr_map.hpp>



using my_mutex = boost::mutex;
//using my_mutex = boost::recursive_mutex;

struct item
{
	int no;
	std::string name;
	//...

	item(int n)
		: no(n)
		, name(boost::lexical_cast<std::string>(n))
	{}
};

class inventory
{
	my_mutex mx_;

	boost::ptr_map<int, item> items_;

public:
	// 찾기만 하는 메소드
	item* searchItem(int no) {
		boost::lock_guard<decltype(mx_)> lock(mx_);
		auto itr = items_.find(no);
		if (items_.end() == itr)
			return nullptr;

		return itr->second;
	}

	// 찾았다가 없으면 추가하는 메소드
	item* getItem(int no) {
		boost::lock_guard<decltype(mx_)> lock(mx_);

		item* tem = searchItem(no);	// 데드락. recursive 필요
		if (nullptr != tem)
			return tem;
		
		tem = new item(no);
		items_.insert(no, tem);
		return tem;
	}
};

inventory inv;

void thread_item_use_1()
{
	inv.getItem(1000);
}

void thread_item_use_2()
{
	inv.getItem(1000);
}

void sample_recursive_mutex() {
	std::cout << "start" << std::endl;

	boost::thread t1(&thread_item_use_1);
	boost::thread t2(&thread_item_use_2);

	t1.join();
	t2.join();

	std::cout << "ended" << std::endl;

	// Notice : mutex는 WaitForSingleObject류를 사용하며,
	//			recursive_mutex는 mutex에 비해 느림.
	//			recursive_mutex는 InterLocked()로 카운팅을 하며, Count가 1 이상인 경우 추가로 Lock()을 안하는 방식으로 구현되어 있음.
	//			(CriticalSection도 Recursive처럼 동작하지만, recursive_mutex는 CriticalSection으로 구현되어 있지 않음)
}
