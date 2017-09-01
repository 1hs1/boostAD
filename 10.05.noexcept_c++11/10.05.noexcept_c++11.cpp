// 10.05.noexcept_c++11.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
// c++11에서 사용자 정의 데이터형의 성능은 높이고 코드 크기는 줄이기

#include "stdafx.h"

#include <boost/config.hpp>

// EMC++ : 예외를 방출하지 않을 함수는 noexcept로 선언하라

// int f(int x) throw();   //f는 예외를 던지지 않음 : C++98 방식
// int f(int x) noexcept; // f는 예외를 던지지 않음 : C++11 방식

// throw() 의 경우에는 f가 불린 지점까지의 callstack이 풀리게 됩니다.
// 그리고 나서 뭔가 처리를 하고 종료(terminate)됩니다.
// noexcept의 경우에는 호출 스택이 풀릴 수도 있고 그렇지 않을 수도 있습니다
// 최적화 : noexcept > throw()

// C++11에서는 기본적으로 모든 메모리 해제 함수와 모든 소멸자 함수는 암묵적으로 noexcept입니다

class move_nothrow {
	// 클래스 멤버는 여기에
	// ...
public:
	move_nothrow() BOOST_NOEXCEPT {}
	// 이동 생성자 BOOST_NOEXCEPT 주석해도 에러 안남.
	move_nothrow(move_nothrow&&) BOOST_NOEXCEPT
		// : 멤버 초기화
		// ...
	{}

	move_nothrow& operator=(move_nothrow&&) BOOST_NOEXCEPT {
		// 구현
		// ...
		return *this;
	}

	move_nothrow(const move_nothrow&);
	move_nothrow& operator=(const move_nothrow&);
};


#include <vector>
int main() {

	std::vector<move_nothrow> v(10);
	v.push_back(move_nothrow());

}

// 헤더 파일에
int foo() BOOST_NOEXCEPT;


// 소스 파일에
int foo() BOOST_NOEXCEPT {
	return 0;
}
