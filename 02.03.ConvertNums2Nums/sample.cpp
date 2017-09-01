#include "stdafx.h"

#include <iostream>

#include <boost/numeric/conversion/cast.hpp>

using namespace std;

template <typename TYPE_DEST, TYPE_DEST DEFAULT_VALUE = 0, typename TYPE_SRC>
TYPE_DEST num_caster(TYPE_SRC src) {
	try {
		TYPE_DEST dest = boost::numeric_cast<TYPE_DEST>(src);
	}
	catch (boost::numeric::bad_numeric_cast& e) {
		cout << e.what() << endl;
	}

	return DEFAULT_VALUE;
}

void sample()
{
	auto dest1 = num_caster<unsigned int, 181818>(double(-222.333));
	cout << dest1 << endl;
}