// 08.03.GetFuncsResultType.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

// �Լ� ���ϰ��� ������ Ÿ�� �˾Ƴ���

#include "stdafx.h"

struct s1 { int v; };
struct s2 { int v; };
struct s3 { int v; };

inline s3 operator + (const s1& v1, const s2& v2) {
	return s3{ v1.v + v2.v };
}

inline s3 operator + (const s2& v1, const s1& v2) {
	return s3{ v1.v + v2.v };
}

#include "cpp_11.h"
#include "cpp_14.h"
#include "cpp_03.h"


int main()
{
	int cmd = 0;
	while (([&cmd]() { std::cout << "? "; std::cin >> cmd; return (0 != cmd); })())
	{
		s1 v1{ 1 };
		s2 v2{ 2 };
		s3 v3{ 0 };

		switch (cmd) {
		case 1: v3 = cpp03::my_function_cpp03(v1, v2); break;
		case 2: v3 = cpp11::my_function_cpp11(v1, v2); break;
		case 3: v3 = cpp14::my_function_cpp14(v1, v2); break;
		case 4: v3 = cpp14::my_function_cpp14_lambda(v1, v2); break;
		default: break;
		}

		std::cout << "s3 : " << v3.v << std::endl;
	}

    return 0;
}

