// 01.11.C++11MoveEmulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cassert>
#include <string>

#include <boost/swap.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>

namespace other {
	class characteristics {};
}

struct person_info {

	bool is_male_;
	std::string name_;
	std::string second_name_;
	other::characteristics characteristic_;

private:
	BOOST_COPYABLE_AND_MOVABLE(person_info)	// declare -> operator =, &, const&

public:
	person_info() {}

	person_info(const person_info& p)
		: is_male_(p.is_male_)
		, name_(p.name_)
		, second_name_(p.second_name_)
		, characteristic_(p.characteristic_)
	{}

	person_info(BOOST_RV_REF(person_info) person) {		// 11:&&, 03:template class
		swap(person);
	}

	person_info& operator=(BOOST_COPY_ASSIGN_REF(person_info) person) {		// 11:const &, 03:template class
		if (this != &person) {
			person_info tmp(person);
			swap(tmp);
		}
		return *this;
	}

	person_info& operator=(BOOST_RV_REF(person_info) person) {
		if (this != &person) {
			swap(person);
			person_info tmp;
			tmp.swap(person);
		}
		return *this;
	}

	void swap(person_info& rhs) {
		std::swap(is_male_, rhs.is_male_);
		name_.swap(rhs.name_);
		second_name_.swap(rhs.second_name_);
		boost::swap(characteristic_, rhs.characteristic_);
	}
};

#include <boost/move/algorithm.hpp>
#include <boost/aligned_storage.hpp>

int main()
{
	person_info vasya;
	vasya.name_ = "Vasya";
	vasya.second_name_ = "Snow";
	vasya.is_male_ = true;

	person_info new_vasya(boost::move(vasya));

	vasya = boost::move(new_vasya);

	// 설명 : BOOST_RV_REF 쓰면 r-value 로 파라미터를 받을 수 있고,
	//			boost::move()로 std::move()처럼 쓸 수 있다

	// 의견 : C++ 11 쓰면 걍 C++ r-value 쓰자


	do {
		// boost::move 다른 용도
		const std::size_t ArraySize = 10;
		person_info movable_array[ArraySize];
		person_info movable_array2[ArraySize];

		for (std::size_t i = 0; i < ArraySize; ++i) {
			movable_array2[i].name_ = std::to_string(i);
		}

		//move
		boost::move(&movable_array2[0], &movable_array2[ArraySize], &movable_array[0]);

		// http://www.boost.org/doc/libs/1_63_0/doc/html/move/move_algorithms.html
	} while (0);
	


	return 0;
}
