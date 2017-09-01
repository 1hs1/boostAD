// 03.09.scoped_exit.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>

#include <boost/scope_exit.hpp>
#include <boost/cast.hpp>

// �����޸� �Ҵ�, ���ؽ�, �����ڵ�, ���ҽ��ڵ� ������ �Ҹ������ �������־�߸� �ϴ�
// ��ó���� �ʿ�.

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

		// ���ܸ� �����ų� ��ȯ�ϴ� � �ڵ�
		// ...

    return 0;
}

