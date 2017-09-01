// 02.06.spirit.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <assert.h>
#include <boost/spirit/include/qi.hpp>
#include <boost/lambda/lambda.hpp>

struct date {
	unsigned short year;
	unsigned short month;
	unsigned short day;
};

void parse_double(const std::string& s)
{
	using boost::spirit::qi::double_;	// 선언

	const char* first = s.data();
	const char* const end = first + s.size();
	bool success = boost::spirit::qi::parse(first, end, double_);

	if (!success || first != end) {
		throw std::logic_error("[parse_double] Parsing failed");
	}

	std::cout << "parse_double Success." << std::endl;
}

void parse_double1(const std::string& s)
{
	using boost::spirit::qi::double_;	// 선언
	using boost::spirit::qi::char_;

	const char* first = s.data();
	const char* const end = first + s.size();
	bool success = boost::spirit::qi::parse(first, end,
		double_ >> char_(',') >> double_ >> char_('-') >> double_);

	if (!success || first != end) {
		throw std::logic_error("[parse_double] Parsing failed");
	}

	std::cout << "parse_double Success." << std::endl;
}

date parse_date_time1(const std::string& s) {
	using boost::spirit::qi::_1;
	using boost::spirit::qi::ushort_;
	using boost::spirit::qi::char_;
	using boost::phoenix::ref;

	date res;
	const char* first = s.data();
	const char* const end = first + s.size();
	bool success = boost::spirit::qi::parse(first, end,
		ushort_[ref(res.year) = _1] >> char_('-') >> ushort_[ref(res.month) = _1] >> char_('-') >> ushort_[ref(res.day) = _1]
	);

	if (!success || first != end) {
		throw std::logic_error("[parse_date_time1] Parsing failed");
	}

	return res;
}

date parse_date_time2(const std::string& s) {
	using boost::spirit::qi::_1;
	using boost::spirit::qi::uint_parser;
	using boost::spirit::qi::char_;
	using boost::phoenix::ref;

	//template <
	//	typename T
	//	, unsigned Radix
	//	, unsigned MinDigits
	//	, int MaxDigits>
	//	struct uint_parser;

	// unsigned short를 출력형으로 사용하며, Radix 10과 2에서부터 2개의 숫자가 필요하다 
	uint_parser<unsigned short, 10, 2, 2> u2_;

	// unsigned short를 출력형으로 사용하며, Radix 10과 4에서부터 4개의 숫자가 필요하다
	uint_parser<unsigned short, 10, 4, 4> u4_;

	date res;
	const char* first = s.data();
	const char* const end = first + s.size();
	bool success = boost::spirit::qi::parse(first, end,
		u4_[ref(res.year) = _1] >> char_('-') >> u2_[ref(res.month) = _1] >> char_('-') >> u2_[ref(res.day) = _1]
	);

	if (!success || first != end) {
		throw std::logic_error("[parse_date_time2] Parsing failed");
	}

	return res;
}

int main()
{
	date d = parse_date_time1("2012-12-31");
	std::cout << "parse_date_time1" << 
		"YEAR : " << d.year << " MONTH : " << d.month << " DAY : " << d.day << std::endl;

	parse_date_time2("2012-12-31");
	std::cout << "parse_date_time2" <<
		"YEAR : " << d.year << " MONTH : " << d.month << " DAY : " << d.day << std::endl;

	try {
		parse_double("1,1-1");
	}
	catch (const std::logic_error& e) 
	{
		std::cout << e.what() << std::endl;
	}

	try {
		parse_double1("1,1-1");
	}
	catch (const std::logic_error& e)
	{
		std::cout << e.what() << std::endl;
	}

	try {
		parse_date_time2("12345-12-31");
		std::cout << "parse_date_time2 Success." << std::endl;
	}
	catch (const std::logic_error& e)
	{
		std::cout << e.what() << std::endl;
	}

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

    return 0;
}

