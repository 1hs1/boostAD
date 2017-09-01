// 01.10.bind.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <boost/array.hpp>
#include <boost/bind.hpp>

#include <functional>
#include <iostream>
#include <conio.h>
#include <string>

using namespace std;
int main()
{
	boost::array<int, 12> i_list = { {1,2,3,4,5,6,7,8,9,10,11,12} };

	std::size_t Count0, Count1;
	Count0 = std::count_if(i_list.begin(), i_list.end(),
		std::bind1st(std::less<int>(), 5));

 	Count1 = std::count_if(i_list.begin(), i_list.end(),
 		boost::bind(std::less<int>(), 5, _1));

	std::cout << "i Count0:"<< Count0 << endl;
	std::cout << "i Count1:" << Count1 << endl;

	boost::array<std::string, 3> s_list = { { "We ", "are", " the champions" } };
	Count0 = std::count_if(s_list.begin(), s_list.end(),
		std::mem_fun_ref(&std::string::empty));
	Count1 = std::count_if(s_list.begin(), s_list.end(),
		boost::bind(&std::string::empty, _1));

	std::cout << "s Count0:" << Count0 << endl;
	std::cout << "s Count1:" << Count1 << endl;



	/*Count0 = std::count_if(s_list.begin(), s_list.end(),
		std::bind2nd(
			std::bind1st(
				std::less<std::size_t>(),
				std::mem_fun_ref(&std::string::size)
			)
			, 5
		)
	);*/
	Count1 = std::count_if(s_list.begin(), s_list.end(),
		boost::bind(std::less<std::size_t>(), boost::bind(&std::string::size, _1), 5));


	std::string s("Expensive copy constructor of std::string will be called when binding");
	Count0 = std::count_if(s_list.begin(), s_list.end(),
		std::bind2nd(std::less<std::string>(), s));
	Count1 = std::count_if(s_list.begin(), s_list.end(),
		boost::bind(std::less<std::string>(), _1, s));

	std::cout << "s Count0:" << Count0 << endl;
	std::cout << "s Count1:" << Count1 << endl;


	system("pause");
	
  return 0;
}

