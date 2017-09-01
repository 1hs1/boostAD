// 01.13.NonCopyAndMovable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string.h>

#include <boost/move/move.hpp>



class descriptor_owner1 {
	std::string descriptor_;	// 책 코드가 구려서 std::string 으로 변경

public:
	descriptor_owner1()
		: descriptor_()
	{}

	explicit descriptor_owner1(const char* param)
		: descriptor_(param)
	{}

	descriptor_owner1(BOOST_RV_REF(descriptor_owner1) param)	// descriptor_owner1&&
		: descriptor_(param.descriptor_)
	{
		param.descriptor_.clear();
	}

	descriptor_owner1& operator=(BOOST_RV_REF(descriptor_owner1) param) {	// descriptor_owner1&&
		clear();
		std::swap(descriptor_, param.descriptor_);
		return *this;
	}

	void clear() {
		descriptor_.clear();
	}

	bool empty() const {
		return descriptor_.empty();
	}

	~descriptor_owner1() {
		clear();
	}
};

descriptor_owner1 construct_descriptor2() {
	return descriptor_owner1("Construct using this string");
}



int main()
{
	descriptor_owner1 desc;
	desc = construct_descriptor2();
	assert(!desc.empty());

	descriptor_owner1 desc2;
	//desc2 = desc;		// 복사라서 컴파일 안됨

	// 설명 : 이동 생성자, 이동 연산자만 정의했기 때문에
	//		참조 생성자, 참조 연산자는 없는 것으로 간주됨.
	//		참고자료 -> Effective Modern C++ 항목17:특수 멤버 함수들의 자동 작성 조건을 숙지하라

	// 용도 : unique_ptr, thread

	return 0;
}
