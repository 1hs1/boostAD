#include "stdafx.h"
#include <conio.h>
#include <iostream>

#include <boost/test/unit_test.hpp>
#include "foo.h"

BOOST_AUTO_TEST_CASE(test_no_2) {
	// ...
	foo f1 = { 1 }, f2 = { 2 };
	BOOST_REQUIRE_NE(f1, f2);
	// ...

	std::cout << "test_no_2" << std::endl;

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
} // BOOST_AUTO_TEST_CASE(test_no_2)