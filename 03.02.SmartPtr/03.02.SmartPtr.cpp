// 03.02.SmartPtr.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <iostream>
using namespace std;

class cTest
{
public:
	cTest()
	{
		cout << "cTest()" << endl;
	}
	~cTest()
	{
		cout << "~cTest()" << endl;
	}
};

void process1(const cTest* p){}
void process2(const cTest* p){}
void process3(const cTest* p){}
cTest* get_data() { return nullptr; }

void foo1()
{
	while (cTest* p = get_data())
	{
		boost::thread(boost::bind(&process1, p)).detach();
		boost::thread(boost::bind(&process2, p)).detach();
		boost::thread(boost::bind(&process3, p)).detach();

		delete p;	// ???
	}
}










#include <boost/shared_ptr.hpp>

void process_sp1(const boost::shared_ptr<cTest>& p){}
void process_sp2(const boost::shared_ptr<cTest>& p) {}
void process_sp3(const boost::shared_ptr<cTest>& p) {}

void foo2()
{
	using ptr_t = boost::shared_ptr<cTest>;

	ptr_t p;

	while (p = ptr_t(get_data()))
	{
		boost::thread(boost::bind(&process_sp1, p)).detach();
		boost::thread(boost::bind(&process_sp2, p)).detach();
		boost::thread(boost::bind(&process_sp3, p)).detach();

		// nothing
	}
}





#include <string>
#include <boost/smart_ptr/make_shared.hpp>

void process_str1(boost::shared_ptr<cTest> p)
{
	int i = 0;
}

void process_str2(const boost::shared_ptr<cTest>& p)
{
	int i = 0;
}

void foo3()
{
	boost::shared_ptr<cTest> ps = boost::make_shared<cTest>();

	boost::thread(boost::bind(&process_str1, ps)).detach();
	boost::thread(boost::bind(&process_str2, ps)).detach();
}

int main()
{
	//foo3();

	// 예문
	//boost::shared_ptr<int> p(new int(10));

	// 예문2
	//boost::shared_ptr<int> p = boost::make_shared<int>(10);
	
    return 0;
}

