#include "stdafx.h"
#include <conio.h>
#include <iostream>

#include <boost/test/unit_test.hpp>
#include "foo.h"

BOOST_AUTO_TEST_CASE(test_no_1) {
	// ...
	foo f1 = { 1 }, f2 = { 2 };
	BOOST_CHECK(f1.is_not_null());

	BOOST_CHECK_NE(f1, f2);

	BOOST_CHECK_THROW(f1.throws(), std::logic_error);

	std::cout << "test_no_1" << std::endl;

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
} // BOOST_AUTO_TEST_CASE(test_no_1)