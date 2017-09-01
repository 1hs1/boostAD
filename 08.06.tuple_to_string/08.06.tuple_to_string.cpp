// 08.06.tuple_to_string.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>

#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>

struct string_functor : boost::noncopyable {
private:
	std::string& result;

public:
	explicit string_functor(std::string& res)
		: result(res)
	{}

	template <class T>
	void operator()(const T& v) const {
		result += boost::lexical_cast<std::string>(v);
	}
};

#include <boost/fusion/include/for_each.hpp>
template <class Sequence>
std::string fusion_Function(const Sequence& seq) {
	std::string result;
	// boost::tuple이나 std::pair에는 begin(), end()가 없어서 std::for_each를 쓸 수 없다.
	// 이럴때 boost::fusion::for_each를 사용
	// tuble이나 pair의 각 요소를 탐색하면서 함수객체에 적용.
	boost::fusion::for_each(seq, string_functor(result));
	return result;
}

struct cat {};
std::ostream& operator << (std::ostream& os, const cat&) {
	return os << "Meow! ";
}

#include <boost/tuple/tuple.hpp>
#include <string>
#include <cassert>

void tuple_example() {
	boost::tuple<int, int, std::string> tup(1, 2, "Meow");

	// 단순한 tuple 테스트
	assert(boost::get<0>(tup) == 1);
	assert(boost::get<2>(tup) == "Meow");
}

#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at_c.hpp>
void fusion_tuple_example() {

	// tuple처럼 쓸 수 있는 fusion::vector<>
	boost::fusion::vector<int, int, std::string> tup(1, 2, "Meow");
	assert(boost::fusion::at_c<0>(tup) == 1);
	assert(boost::fusion::at_c<2>(tup) == "Meow");
}

#include <boost/fusion/adapted/boost_tuple.hpp>
std::string stringize_tup2_example() {
	boost::tuple<cat, int, std::string> tup2(cat(), 0, "_0");

	std::string result;

	// boost::fusion::for_each(seq, fusion_Function(result)); 대신
	// 다음과 같은 코드 쓰기
	{
		string_functor functor(result);
		functor(boost::fusion::at_c<0>(tup2));
		functor(boost::fusion::at_c<1>(tup2));
		functor(boost::fusion::at_c<2>(tup2));
	}
	return result;
}


#include <iostream>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/adapted/boost_array.hpp>

int main() {
	tuple_example();
	fusion_tuple_example();
	stringize_tup2_example();

	boost::fusion::vector<cat, int, std::string> tup1(cat(), 0, "_0");
	boost::tuple<cat, int, std::string> tup2(cat(), 0, "_0");
	std::pair<cat, cat> cats;
	boost::array<cat, 10> many_cats;

	std::cout << fusion_Function(tup1) << '\n'
		<< fusion_Function(tup2) << '\n'
		<< fusion_Function(cats) << '\n'
		<< fusion_Function(many_cats) << '\n';

	while (1)
	{
		if (_kbhit())
		{
			if (_getch() == 27)	// ESC key
			{
				break;
			}
		}
	}
}

