// 10.03.extern_template.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>

#include "header.h"

int main() {
	variant_type v1(0), v2, v3(1.1);

	(void)v1;
	(void)v2;
	(void)v3;

	while (1)
	{
		if (_kbhit())
		{
			if (_getch() == 27)	// ESC key
			{
				break;
			}
		}
	}
}

//http://stackoverflow.com/questions/8130602/using-extern-template-c11/8131212#8131212

