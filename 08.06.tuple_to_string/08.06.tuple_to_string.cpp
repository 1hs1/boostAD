// 08.06.tuple_to_string.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
	// boost::tuple�̳� std::pair���� begin(), end()�� ��� std::for_each�� �� �� ����.
	// �̷��� boost::fusion::for_each�� ���
	// tuble�̳� pair�� �� ��Ҹ� Ž���ϸ鼭 �Լ���ü�� ����.
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

	// �ܼ��� tuple �׽�Ʈ
	assert(boost::get<0>(tup) == 1);
	assert(boost::get<2>(tup) == "Meow");
}

#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at_c.hpp>
void fusion_tuple_example() {

	// tupleó�� �� �� �ִ� fusion::vector<>
	boost::fusion::vector<int, int, std::string> tup(1, 2, "Meow");
	assert(boost::fusion::at_c<0>(tup) == 1);
	assert(boost::fusion::at_c<2>(tup) == "Meow");
}

#include <boost/fusion/adapted/boost_tuple.hpp>
std::string stringize_tup2_example() {
	boost::tuple<cat, int, std::string> tup2(cat(), 0, "_0");

	std::string result;

	// boost::fusion::for_each(seq, fusion_Function(result)); ���
	// ������ ���� �ڵ� ����
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

