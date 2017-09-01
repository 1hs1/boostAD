// 07.01.LowerUpperCases.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//


// 대/소문자 구분없이 비교하기

#include "stdafx.h"
#include <string>
std::string str1 = "Thanks for reading me!";
std::string str2 = "Thanks for reading ME!";

#include <boost/algorithm/string/predicate.hpp>
void method1() {
	assert(
		boost::iequals(str1, str2)		// <== 이걸로 쓰셈
	);

}

#include <boost/algorithm/string/compare.hpp>
#include <algorithm>
void method2() {
	assert(

		str1.size() == str2.size() && std::equal(
			str1.begin(),
			str1.end(),
			str2.begin(),
			boost::is_iequal()
		)

	);
}

#include <boost/algorithm/string/case_conv.hpp>
void method3() {

	std::string str1_low = boost::to_lower_copy(str1);
	std::string str2_low = boost::to_lower_copy(str2);
	assert(str1_low == str2_low);

}

#include <boost/algorithm/string/case_conv.hpp>
void method4() {

	std::string str1_up = boost::to_upper_copy(str1);
	std::string str2_up = boost::to_upper_copy(str2);
	assert(str1_up == str2_up);

}

#include <boost/algorithm/string/case_conv.hpp>
void method5() {

	boost::to_lower(str1);
	boost::to_lower(str2);
	assert(str1 == str2);

}

int main()
{
	method1();
	method2();
	method3();
	method4();
	method5();


	// 참고로, locale 을 설정해서 비교할수도 있다

	// 일부 플랫폼에서는 std::locale::classic()이
	// std::locale()보다 빠르다
	boost::iequals(str1, str2, std::locale::classic());

	return 0;
}

