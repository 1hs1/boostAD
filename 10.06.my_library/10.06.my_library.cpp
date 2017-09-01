// 10.06.my_library.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
// 이동 가능한 방식으로 함수와 클래스를 내보내고 불러들이기

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

