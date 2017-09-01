// 03.09.scoped_exit.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>

#include <boost/scope_exit.hpp>
#include <boost/cast.hpp>

// 동적메모리 할당, 뮤텍스, 파일핸들, 리소스핸들 별도의 소멸과정을 정의해주어야만 하는
// 후처리시 필요.

class CTest
{
public:
	CTest(const char* name) { strcpy_s(m_name, sizeof(name), name); std::cout << "consruct : " << m_name << std::endl; }
	~CTest() { std::cout << "destroy" << std::endl; }
	void Run() { std::cout << "run : " << m_name << std::endl; }

private:
	char m_name[10];
};

struct object {
	virtual ~object() {}
};

struct banana : public object {
	void eat() const { std::cout << "banana eat." << std::endl; }
	virtual ~banana() {}
};

struct apple : public object {
	void buy() const { std::cout << "apple buy." << std::endl; }
	virtual ~apple() {}
};

object* try_produce_banana() {
	static apple appl;
	return &appl;
}

int Function() {
	try {
		int a = 10;
		CTest* test = new CTest("KSH");

		BOOST_SCOPE_EXIT(&a, test)
		{
			a = 0;
			delete test;
			std::cout << "boost exit:" << a << std::endl;
		}
		BOOST_SCOPE_EXIT_END;

		const object* obj = try_produce_banana();
		boost::polymorphic_cast<const banana*>(obj)->eat();
		std::cout << "try_eat_banana_impl1 Success" << std::endl;

		return a;
	}
	catch (const std::exception& e) {
		std::cout << "try_eat_banana_impl1 Fail : " << e.what() << std::endl;
	}

	return -1;
}

int main()
{
	int j = Function();

	std::cout << j << std::endl;

	while (1)
	{
		if (_kbhit())
		{
			if (_getch() == 27)	// ESC key
			{
				break;
			}
		}
	}

		// 예외를 던지거나 반환하는 어떤 코드
		// ...

    return 0;
}

