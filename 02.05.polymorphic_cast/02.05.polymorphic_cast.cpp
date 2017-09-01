// 02.05.polymorphic_cast.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>

#include <boost/cast.hpp>

struct object {
	virtual ~object() {}
};

struct banana : public object {
	void eat() const { std::cout << "banana eat." << std::endl;  }
	virtual ~banana() {}
};

struct apple : public object {
	void buy() const { std::cout << "apple buy." << std::endl; }
	virtual ~apple() {}
};

object* try_produce_banana();

void try_eat_banana_impl1() {
	const object* obj = try_produce_banana();
	if (!obj) {
		std::cout << "try_eat_banana_impl1 bad_cast" << std::endl;
		throw std::bad_cast();
	}

	dynamic_cast<const banana&>(*obj).eat();
	std::cout << "try_eat_banana_impl1 Success" << std::endl;
}

void try_eat_banana_impl2() {
	const object* obj = try_produce_banana();
	if (!obj) {
		throw std::bad_cast();
	}

	//dynamic_cast<const banana&>(*obj).eat();
	const banana* pbanana = dynamic_cast<const banana*>(obj);
	//const banana* pbanana = static_cast<const banana*>(obj);
	if (pbanana)
	{
		pbanana->eat();
		std::cout << "try_eat_banana_impl2 Success" << std::endl;
	}
	else
	{
		std::cout << "try_eat_banana_impl2 Fail" << std::endl;
	}
}

void try_eat_banana_impl3() {
	const object* obj = try_produce_banana();
	if (!obj) {
		std::cout << "try_eat_banana_impl3 bad_cast" << std::endl;
		return;
	}

	dynamic_cast<const banana&>(*obj).eat();
	std::cout << "try_eat_banana_impl3 Success" << std::endl;
}

void try_eat_banana_impl4() {
	const object* obj = try_produce_banana();
	boost::polymorphic_cast<const banana*>(obj)->eat();
	std::cout << "try_eat_banana_impl4 Success" << std::endl;
}

void try_eat_banana_impl5() {
	const object* obj = try_produce_banana();
	boost::polymorphic_cast<const banana*>(obj)->eat();
	std::cout << "try_eat_banana_impl5 Success" << std::endl;
}

void try_eat_banana_impl6() {
	const object* obj = try_produce_banana();
	boost::polymorphic_cast<const banana*>(obj)->eat();
	std::cout << "try_eat_banana_impl6 Success" << std::endl;
}

object* try_produce_banana() {
	static apple appl;
	static banana banan;
	static int i = 0;
	++i;
	if (i == 3 || i == 6) {
		return 0;
	}
	else if (i == 2 || i == 5) {
		return &appl;
	}
	return &banan;
}

int main()
{
	try_eat_banana_impl1();

	try_eat_banana_impl2();

	try_eat_banana_impl3();

	try_eat_banana_impl4();

	try {
		try_eat_banana_impl5();
	}
	catch(const std::exception& e){
		std::cout << "try_eat_banana_impl5 Fail : " << e.what() << std::endl;
	}
	
	try {
		try_eat_banana_impl6();
	}
	catch (const std::exception& e) {
		std::cout << "try_eat_banana_impl6 Fail : " << e.what() << std::endl;
	}


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

    return 0;
}

