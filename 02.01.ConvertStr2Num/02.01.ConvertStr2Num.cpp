// 02.01.ConvertStr2Num.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <clocale>
#include <locale>
#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

using namespace std;

//- ���ڿ� -> ����
void test1() {
	int v = boost::lexical_cast<int>("100");
	cout << v << endl;
	//- expected result
	// 100
}

//- ���ڿ� ������ ���� ��ŭ�� -> ����
void test2() {
	int v = boost::lexical_cast<int>("100", 2);
	cout << v << endl;
	//- expected result
	// 10
}

//- � ���󿡼��� �Ҽ����� ��ǥ�� ����
void test3() {
	//std::locale::global(std::locale("ru_RU.utf8"));	// not working. bad locale
	std::locale::global(std::locale("German_germany"));	// also can use 'de-AT'. referend : https://msdn.microsoft.com/en-us//library/39cwe7zf.aspx
	float v = boost::lexical_cast<float>("3,14");
	cout << v << endl;
	//- expected result
	// 3.14
}

int main()
{
	try {
		test1();
		test2();
		test3();
	}
	//- ĳ���� ���н� ����
	catch (boost::bad_lexical_cast& e) {
		cout << e.what() << endl;
	}
	catch (std::exception& e) {
		cout << e.what() << endl;
	}
	
    return 0;
}
