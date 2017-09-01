// 01.13.NonCopyAndMovable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string.h>

#include <boost/move/move.hpp>



class descriptor_owner1 {
	std::string descriptor_;	// å �ڵ尡 ������ std::string ���� ����

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
	//desc2 = desc;		// ����� ������ �ȵ�

	// ���� : �̵� ������, �̵� �����ڸ� �����߱� ������
	//		���� ������, ���� �����ڴ� ���� ������ ���ֵ�.
	//		�����ڷ� -> Effective Modern C++ �׸�17:Ư�� ��� �Լ����� �ڵ� �ۼ� ������ �����϶�

	// �뵵 : unique_ptr, thread

	return 0;
}
