// 01.09.bind.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <algorithm>
#include <vector>
#include <boost/bind.hpp>

using namespace std;

/*
class Number { };
inline Number operator + (Number, Number );

struct mul_2_func_obj : public std::unary_function<Number, Number> {
	Number operator() (Number& n1) const {
		return n1 + n1;
	}
};

using tyNumList = std::vector<Number>;
 void mul_2_impl1(tyNumList& val) {
 	std::for_each(val.begin(), val.end(), mul_2_func_obj());
 }

 void mul_2_impl2(tyNumList& val) {
 	std::for_each(val.begin(), val.end(), boost::bind(std::plus<Number>(), _1, _1));
 }

template <class T>
void mul_2_impl3(std::vector<T>& val) {
	std::for_each(val.begin(), val.end(), boost::bind(std::plus<T>(), _1, _1));
}*/

struct mul_2_func : public std::unary_function<int, void> {
	void operator() (int& n1) const {
		n1*=2;
	}
};

using tyNumList = std::vector<int>;
void mul_2_impl1(tyNumList& val) {
	std::for_each(val.begin(), val.end(), mul_2_func());
}

void mul_2_impl2(tyNumList& val) {
	std::for_each(val.begin(), val.end(), boost::bind(std::plus<int>(), _1, _1));
}

template <class T>
void mul_2_impl3(std::vector<T>& val) {
	std::for_each(val.begin(), val.end(), boost::bind(std::plus<T>(), _1, _1));
}

class Device1 {
private:
	short temperature();
	short wetness();
	int illumination();
	int atomospheric_pressure();

	void wait_for_data();

public:
	template<class T>
	void watch(const T& f) {
		for (;;) {
			wait_for_data();
			f(
				temperature(),
				wetness(),
				illumination(),
				atomospheric_pressure()
			);
		}
	}
};

class Device2 {
private:
	short temperature();
	short wetness();
	int illumination;
	int atomospheric_pressure();

	void wait_for_data();

public:
	template<class T>
	void watch(const T& f) {
		for (;;) {
			wait_for_data();
			f(
				wetness(),
				temperature(),
				atomospheric_pressure()
				illumination,
			);
		}
	}
};

void detect_storm(int wetness, int temperature, int atomospheric_pressure);

int main()
{
/*
	Number n1;
	std::vector<Number> NumList;
	NumList.push_back(n1);

	mul_2_impl1(NumList);
	mul_2_impl2(NumList);
	mul_2_impl3(NumList);*/

	int n1 = 1;
	tyNumList NumList;
	NumList.push_back(n1);
	NumList.push_back(n1);

	mul_2_impl1(NumList);
	mul_2_impl2(NumList);
	mul_2_impl3(NumList);

	system("pause");
/*
	Device1 d1;
	d1.watch(boost::bind(&detect_storm, _2, _1, _4));
	Device1 d2;
	d1.watch(boost::bind(&detect_storm, _1, _2, _3));*/


  return 0;
}

