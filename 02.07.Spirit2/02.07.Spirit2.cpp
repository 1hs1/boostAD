// 02.07.Spirit2.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>

struct datetime
{
	enum zone_offsets_t
	{
		OFFSET_NOT_SET,
		OFFSET_Z,
		OFFSET_UTC_PLUS,
		OFFSET_UTC_MINUS,
	};

private:
	unsigned short year;
	unsigned short month;
	unsigned short day;
	unsigned short hours;
	unsigned short minutes;
	unsigned short seconds;
	zone_offsets_t zone_offset_type;
	unsigned int zone_offset_in_min;

	static void dt_assert(bool v, const char* msg)
	{
		if (!v)
		{
			throw std::logic_error("Assertion failed in datetime: " + std::string(msg));
		}
	}

public:
	void set_zone_offset_type(zone_offsets_t type) { zone_offset_type = type; }
	void set_zone_offset_in_min(unsigned int value) { zone_offset_in_min = value; }

	void set_year(unsigned short val) { year = val; }
	void set_month(unsigned short val) { month = val; }
	void set_day(unsigned short val) { day = val; }
	void set_hours(unsigned short val) { hours = val; }
	void set_minutes(unsigned short val) { minutes = val; }
	void set_seconds(unsigned short val) { seconds = val; }

public:
	datetime() : year(0), month(0), day(0), hours(0), minutes(0), seconds(0), zone_offset_type(OFFSET_NOT_SET), zone_offset_in_min(0) {}
};

// �Լ�
void set_zone_offset(datetime& dt, char sign, unsigned short hours, unsigned short minutes)
{
	dt.set_zone_offset_type(sign == '+' ? datetime::OFFSET_UTC_PLUS : datetime::OFFSET_UTC_MINUS);
	dt.set_zone_offset_in_min(hours * 60 + minutes);
}

// �Լ�
datetime parse_datetime(const std::string& s)
{
	using boost::spirit::qi::_1;
	using boost::spirit::qi::_2;
	using boost::spirit::qi::_3;
	using boost::spirit::qi::uint_parser;
	using boost::spirit::qi::char_;
	using boost::phoenix::bind;
	using boost::phoenix::ref;

	// declare)
	datetime returnValue;

	// unsinged short�� ��������� ����ϸ� Radix 10�� 2�������� 2���� ���ڰ� �ʿ��ϴ�.
	uint_parser<unsigned short, 10, 2, 2> u2_;

	// unsigned short�� ��������� ����ϸ�, Radix 10�� 4�������� 4���� ���ڰ� �ʿ��ϴ�.
	uint_parser<unsigned short, 10, 4, 4> u4_;


	// ���������� �����ϴ� �� ���� rule<> ��ü
	boost::spirit::qi::rule< const char*, void() > timezone_parser
		= -(
			// '-' �ϳ��� ������ ���û����̶� ��

			//0 ������
			char_('Z')[boost::phoenix::bind(&datetime::set_zone_offset_type, &returnValue, datetime::OFFSET_Z)]
			|	// Ȥ��
			// Ư�� ���� ������
			( (char_('+') | char_('-') ) >> u2_ >> ':' >> u2_)[boost::phoenix::bind(&set_zone_offset, ref(returnValue), _1, _2, _3)]
			);


	boost::spirit::qi::rule<const char*, void()> date_parser =
		u4_[boost::phoenix::bind(&datetime::set_year, &returnValue, _1)] >> char_('-')
		>> u2_[boost::phoenix::bind(&datetime::set_month, &returnValue, _1)] >> char_('-')
		>> u2_[boost::phoenix::bind(&datetime::set_day, &returnValue, _1)];


	boost::spirit::qi::rule<const char*, void()> time_parser =
		u2_[boost::phoenix::bind(&datetime::set_hours, &returnValue, _1)] >> char_(':')
		>> u2_[boost::phoenix::bind(&datetime::set_minutes, &returnValue, _1)] >> char_(':')
		>> u2_[boost::phoenix::bind(&datetime::set_seconds, &returnValue, _1)];


	const char* first = s.data();
	const char* const end = first + s.size();
	bool success = boost::spirit::qi::parse(first, end,
		((date_parser >> char_('T') >> time_parser) | date_parser | time_parser)
		>> timezone_parser
	);

	if (!success || first != end)
	{
		throw std::logic_error("Parsing of '" + s + "' failed");
	}
	return returnValue;
}


int main()
{
	// �پ��� �Է� ���İ� �ð��� �������� �����ϴ� ��¥-�ð� �ļ��� ����� ����.

	/*
	2017-03-27T14:30:00Z
	2017-03-27T14:30:00
	2017-03-27T14:30:00+09:15
	2017-03-27-09:15
	10:00:09+09:15
	*/

	datetime dt;
	dt = parse_datetime("2017-03-27T14:30:00Z");
	dt = parse_datetime("2017-03-27T14:30:00");
	dt = parse_datetime("2017-03-27T14:30:00+09:15");
	dt = parse_datetime("2017-03-27-09:15");
	dt = parse_datetime("10:00:09+09:15");
    return 0;
}

