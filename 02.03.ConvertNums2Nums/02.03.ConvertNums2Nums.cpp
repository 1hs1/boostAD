// 02.03.ConvertNums2Nums.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <iostream>

#include <boost/numeric/conversion/cast.hpp>

using namespace std;

//- 형 변환 실패 시 예외발생
void test1()
{
	unsigned int src = std::numeric_limits<unsigned int>::max();
	int dest = 0;
	try {
		dest = boost::numeric_cast<int>(src);
	}
	catch (boost::numeric::bad_numeric_cast& e) {		// ...positive_overflow, ...negative_overflow 등 더 세부적인 이유도 catch 할 수 있음
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

	//- 샘플
	sample();

	//- 컴파일 타임에 많은 부분을 미리 처리
    return 0;
}

