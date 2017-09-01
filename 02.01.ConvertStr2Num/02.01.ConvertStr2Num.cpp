// 02.01.ConvertStr2Num.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <clocale>
#include <locale>
#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

using namespace std;

//- 문자열 -> 숫자
void test1() {
	int v = boost::lexical_cast<int>("100");
	cout << v << endl;
	//- expected result
	// 100
}

//- 문자열 정해진 길이 만큼만 -> 숫자
void test2() {
	int v = boost::lexical_cast<int>("100", 2);
	cout << v << endl;
	//- expected result
	// 10
}

//- 어떤 나라에서는 소수점을 쉼표로 쓴다
void test3() {
	//std::locale::global(std::locale("ru_RU.utf8"));	// not working. bad locale
	std::locale::global(std::locale("German_germany"));	// also can use 'de-AT'. referend : https://msdn.microsoft.com/en-us//library/39cwe7zf.aspx
	float v = boost::lexical_cast<float>("3,14");
	cout << v << endl;
	//- expected result
	// 3.14
}

int main()
{
	try {
		test1();
		test2();
		test3();
	}
	//- 캐스팅 실패시 예외
	catch (boost::bad_lexical_cast& e) {
		cout << e.what() << endl;
	}
	catch (std::exception& e) {
		cout << e.what() << endl;
	}
	
    return 0;
}
