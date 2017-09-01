// 02.03.ConvertNums2Nums.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <iostream>

#include <boost/numeric/conversion/cast.hpp>

using namespace std;

//- �� ��ȯ ���� �� ���ܹ߻�
void test1()
{
	unsigned int src = std::numeric_limits<unsigned int>::max();
	int dest = 0;
	try {
		dest = boost::numeric_cast<int>(src);
	}
	catch (boost::numeric::bad_numeric_cast& e) {		// ...positive_overflow, ...negative_overflow �� �� �������� ������ catch �� �� ����
		cout << e.what() << endl;
		return;
	}

	cout << "result : " << dest << endl;

	//- expected result
	// bad numeric conversion: positive overflow
}







int main()
{
	test1();

	//- ����
	sample();

	//- ������ Ÿ�ӿ� ���� �κ��� �̸� ó��
    return 0;
}

