// 01.05.AnyVariant.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#define BOOST_ANY
#ifdef BOOST_ANY
	#include <boost/any.hpp>
	#include <typeinfo>
#else
	#include <boost/variant.hpp>
#endif
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

#ifdef BOOST_ANY

using cell_t = boost::any;
using db_row_t = vector<cell_t>;

db_row_t get_row(const char* /*query*/)
{
	db_row_t row;
	row.push_back(10);
	row.push_back(10.1f);
	row.push_back(string("hello again"));
	return row;
}

struct db_sum : public std::unary_function<boost::any, void>
{
private:
	double& sum_;

public:
	explicit db_sum(double& sum) : sum_(sum) {}

	void operator()(const cell_t& value)
	{
		const std::type_info& ti = value.type();

		if (ti == typeid(int))
		{
			sum_ += boost::any_cast<int>(value);
		}
		else if (ti == typeid(float))
		{
			sum_ += boost::any_cast<float>(value);
		}
	}
};

int main()
{
	db_row_t row = get_row("Query: Give me some row, please...");

	double res = 0.0;
	std::for_each(row.begin(), row.end(), db_sum(res));

	cout << "Sum of arithmetic types in database row is: " << res << endl;
	int i = 0;
	cin >> i;
	return 0;
}

#else
	
using cell_t = boost::variant<int, float, std::string >;
using db_row_t = std::vector<cell_t>;

db_row_t get_row(const char* /*query*/)
{
	db_row_t row;
	row.push_back(10);
	row.push_back(10.1f);
	row.push_back(string("hello again"));
	return row;
}

struct db_sum_visitor : public boost::static_visitor<double>
{
	double operator()(int value) const
	{
		return value;
	}

	double operator()(float value) const
	{
		return value;
	}

	double operator()(const std::string& /*value*/) const
	{
		return 0.0f;
	}
};

int main()
{
	db_row_t row = get_row("query : give me some row, plz.");

	double res = 0.0;
	for (db_row_t::const_iterator it = row.begin(), end = row.end(); it != end; ++it)
	{
		res += boost::apply_visitor(db_sum_visitor(), *it);
	}

	cout << "sum of .............. is : " << res << endl;
	int i = 0;
	cin >> i;
	return 0;
}

#endif
