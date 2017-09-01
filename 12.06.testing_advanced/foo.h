#pragma once
#include <stdexcept>
struct foo {
	int val_;

	operator int() const;
	bool is_not_null() const;
	void throws() const; // std::logic_error 예외 던지기
};