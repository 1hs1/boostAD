// 01.12.NonCopyable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>

#include <boost/noncopyable.hpp>


class descriptor_owner_fixed 
	: private boost::noncopyable	// 복사 생성자, 복사 연산자 삭제됨
{
	std::string txt_;

public:
	descriptor_owner_fixed(std::string txt) : txt_(txt)
	{}
};


int main()
{
	descriptor_owner_fixed d1("O_o");
	descriptor_owner_fixed d2("^_^");
	
	//d2 = d1;	// 컴파일 안됨

	//descriptor_owner_fixed d3(d1);		// 컴파일 안됨

	// 용도 : 절대 1개만 존재해야 하는 객체들. 예를 들어, unique_ptr, thread, singleton...

	return 0;
}

