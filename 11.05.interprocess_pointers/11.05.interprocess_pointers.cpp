// 11.05.interprocess_pointers.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>

struct with_pointer {
	int* pointer_;
	// ...
	int value_holder_;
};


#include <boost/interprocess/offset_ptr.hpp>

struct correct_struct {
	boost::interprocess::offset_ptr<int> pointer_;
	// ...
	int value_holder_;
};


#include <boost/interprocess/managed_shared_memory.hpp>

template <class T>
void test() {
	typedef T test_struct;
	static const int ethalon_value = 777;

	boost::interprocess::managed_shared_memory
		segment(boost::interprocess::open_or_create, "segment", 4096);

	test_struct* ptr =
		segment.find<test_struct>("structure").first;

	//segment.destroy<correct_struct>("structure");

	if (ptr) {
		std::cout << "Structure found\n";
		assert(*ptr->pointer_ == ethalon_value);
		std::cout << "*ptr->pointer : " << *ptr->pointer_ <<
			" ethalon_value : " << ethalon_value << std::endl;
		segment.destroy<test_struct>("structure");
	}
	else {
		std::cout << "Creating structure\n";
		test_struct& ref = *segment.construct<test_struct>("structure")();
		ref.pointer_ = &ref.value_holder_;
		assert(ref.pointer_ == &ref.value_holder_);
		std::cout << "ref.pointer_ : " << ref.pointer_ <<
			" &ref.value_holder_ : " << &ref.value_holder_ << std::endl;
		assert(*ref.pointer_ == ref.value_holder_);
		std::cout << "*ref.pointer : " << *ref.pointer_ <<
			" ref.value_holder_ : " << ref.value_holder_ << std::endl;
		ref.value_holder_ = ethalon_value;
		assert(*ref.pointer_ == ethalon_value);
		std::cout << "*ref.pointer : " << *ref.pointer_ <<
			" ethalon_value : " << ethalon_value << std::endl;
	}
}


#include <cassert>

int main() {
	test<correct_struct>(); // 문제 없어야 함
							//test<with_pointer>(); // 실패해야 함

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
}

