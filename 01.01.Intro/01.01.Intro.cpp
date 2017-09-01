// 01.01.Intro.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <boost/format.hpp>

#include <iostream>

int main()
{
	std::cout << boost::format("im%3% %2% %1%") % "nothing" % "is" % "possible" << std::endl;
    return 0;
}
