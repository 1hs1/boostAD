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
	// ã�⸸ �ϴ� �޼ҵ�
	item* searchItem(int no) {
		boost::lock_guard<decltype(mx_)> lock(mx_);
		auto itr = items_.find(no);
		if (items_.end() == itr)
			return nullptr;

		return itr->second;
	}

	// ã�Ҵٰ� ������ �߰��ϴ� �޼ҵ�
	item* getItem(int no) {
		boost::lock_guard<decltype(mx_)> lock(mx_);

		item* tem = searchItem(no);	// �����. recursive �ʿ�
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

	// Notice : mutex�� WaitForSingleObject���� ����ϸ�,
	//			recursive_mutex�� mutex�� ���� ����.
	//			recursive_mutex�� InterLocked()�� ī������ �ϸ�, Count�� 1 �̻��� ��� �߰��� Lock()�� ���ϴ� ������� �����Ǿ� ����.
	//			(CriticalSection�� Recursiveó�� ����������, recursive_mutex�� CriticalSection���� �����Ǿ� ���� ����)
}
