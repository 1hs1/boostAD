// 03.01.Scoped_ptr.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <string>
using namespace std;

class cTest
{
public:
	cTest(std::string s){}
};

bool some_function1(cTest* pTest)
{
	// ...

	if (true)
		return true;
	else
		return false;
}

bool some_function2(cTest* pTest)
{
	// ...

	if (true)
		return true;
	else
		return false;
}

// 예시 코드1
bool foo1()
{
	cTest* p = new cTest("Name");

	bool something_else_happened = some_function1(p);
	if (something_else_happened)
	{
		delete p;
		return false;
	}
	
	some_function2(p);
	delete p;
	return true;
}


// 예시 코드2
bool foo2()
{
	cTest* p = new cTest("Name");

	try
	{
		bool something_else_happened = some_function1(p);
		if (something_else_happened)
		{
			delete p;
			return false;
		}

		some_function2(p);
	}
	catch (...)
	{
		delete p;
		throw;
	}

	delete p;
	return true;
}


#include <boost/scoped_ptr.hpp>

bool foo3()
{
	boost::scoped_ptr<cTest> p(new cTest("name"));

	bool something_else_happend = some_function1(p.get());
	if (something_else_happend)
		return false;

	some_function2(p.get());
	return true;
}

int main()
{
	//foo1();
	//foo2();
	//foo3();

    return 0;
}

