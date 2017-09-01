// 03.07.PassLambdaFunc.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <boost/function.hpp>

#include <iostream>
#include <vector>

typedef boost::function<void(int)> fobject_t;

// Now this function may accept functional objects
void process_integers(const fobject_t& f)
{
	f(9999);
}


//void my_ints_function(int i)
//{
//	std::cout << __FUNCTION__ << " - " << i << std::endl;
//}

int main() {
	auto lambda_func = [](int i) {
		std::cout << __FUNCTION__ << " - " << i << std::endl;
	};

	process_integers(lambda_func);

	return 0;
}
