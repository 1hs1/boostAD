// 05.02.SyncAccessToCommonRes.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <iostream>

int main()
{
	int cmd = 0;
	while (([&cmd]() { std::cout << "? "; std::cin >> cmd; return (0 != cmd); })())
	{
		switch (cmd) {
		case 1:sample_no_mutex();break;
		case 2:sample_mutex();break;
		case 3:sample_recursive_mutex();break;
		default: break;
		}
	}

	return 0;
}

