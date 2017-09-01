// 01.12.NonCopyable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>

#include <boost/noncopyable.hpp>


class descriptor_owner_fixed 
	: private boost::noncopyable	// ���� ������, ���� ������ ������
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
	
	//d2 = d1;	// ������ �ȵ�

	//descriptor_owner_fixed d3(d1);		// ������ �ȵ�

	// �뵵 : ���� 1���� �����ؾ� �ϴ� ��ü��. ���� ���, unique_ptr, thread, singleton...

	return 0;
}

