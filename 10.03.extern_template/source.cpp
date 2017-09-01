// 'extern template'이 있는 헤더
#include "stdafx.h"
#include "header.h"

#ifndef BOOST_NO_CXX11_EXTERN_TEMPLATE
template class boost::variant<
	boost::blank,
	int,
	std::string,
	double
>;
#endif


#include <boost/variant.hpp>
#include <boost/blank.hpp>
#include <string>