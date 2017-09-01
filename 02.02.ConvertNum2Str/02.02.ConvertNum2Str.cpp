// 02.02.ConvertNum2Str.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

using namespace std;

//- ���ڸ� ���ڿ���
void test1()
{
	string s = boost::lexical_cast<string>(100);
	cout << s << endl;
	//- expected result
	// 100
}

int main()
{
	try {
		test1();
	}
	//- ĳ���� ���н� ����
	catch (boost::bad_lexical_cast& e) {
		cout << e.what() << endl;
	}
	catch (std::exception& e) {
		cout << e.what() << endl;
	}


	//- ������ ��κ��� ��� �� ���� (�񱳴�� - stringstream, sprintf)
	//- http://www.boost.org/doc/libs/1_63_0/doc/html/boost_lexical_cast/performance.html


	//- ����
	sample();


    return 0;
}

