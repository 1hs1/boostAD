// 03.07.PassLambdaFunc.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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
