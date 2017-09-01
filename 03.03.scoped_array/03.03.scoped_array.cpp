// 03.03.scoped_array.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

void may_throw1(const char* buffer);
void may_throw2(const char* buffer);

void foo() {
	// 스택에 10MB에 이르는 메모리는 할당할 수 없다.
	// 그러니 힙에 할당해야한다
	char* buffer = new char[1024 * 1024 * 10];

	// 여기에 예외를 던질 수도 있는 코드 있음
	may_throw1(buffer);
	may_throw2(buffer);

	delete[] buffer;
}

#include <boost/scoped_array.hpp>

void foo_fixed() {
	// 힙에 할당한다
	boost::scoped_array<char> buffer(new char[1024 * 1024 * 10]);

	// 여기에 예외를 던질 수도 있는 코드 있음
	// 하지만 이번에는 메모리가 누출되지 않는다
	may_throw1(buffer.get());
	may_throw2(buffer.get());

	// 'buffer'의 소멸자가 delete[] 호출
}

#include <stdexcept>
#include <assert.h>

int main() {
	//foo(); // 메모리 누출
	try {
		foo_fixed();
	}
	catch (...) {}

	return 0;
}


void may_throw1(const char* /*buffer*/) {
	// 아무 것도 하지 않는다
}

void may_throw2(const char* /*buffer*/) {
	throw std::exception();
}
