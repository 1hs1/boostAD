// 10.06.my_library.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
// �̵� ������ ������� �Լ��� Ŭ������ �������� �ҷ����̱�

#include "stdafx.h"
#include "my_library.h"
#include <assert.h>
#include <iostream>
int main()
{
	assert(foo() == 0);
	bar b;
	try {
		b.meow();
		//assert(false);
	} catch(const bar_exception& e) { 
		std::cout << e.what();
	}

  return 0;
}

