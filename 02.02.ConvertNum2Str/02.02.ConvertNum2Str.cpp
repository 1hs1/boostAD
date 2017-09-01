// 02.02.ConvertNum2Str.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

using namespace std;

//- 숫자를 문자열로
void test1()
{
	string s = boost::lexical_cast<string>(100);
	cout << s << endl;
	//- expected result
	// 100
}

int main()
{
	try {
		test1();
	}
	//- 캐스팅 실패시 예외
	catch (boost::bad_lexical_cast& e) {
		cout << e.what() << endl;
	}
	catch (std::exception& e) {
		cout << e.what() << endl;
	}


	//- 성능은 대부분의 경우 더 좋다 (비교대상 - stringstream, sprintf)
	//- http://www.boost.org/doc/libs/1_63_0/doc/html/boost_lexical_cast/performance.html


	//- 샘플
	sample();


    return 0;
}

