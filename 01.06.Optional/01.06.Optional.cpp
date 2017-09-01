// 01.06.Optional.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <boost/optional.hpp>
#include <iostream>
#include <stdlib.h>
using namespace std;

class locked_device
{
	explicit locked_device(const char* /*param*/)
	{
		cout << "device is locked" << endl;
	}

public:
	~locked_device() {}

	void use()
	{
		cout << "success.." << endl;
	}

	static boost::optional<locked_device> try_lock_device()
	{
		if (rand() % 2)
		{
			return boost::none;
		}
		return locked_device("device name");
	}
};

int main()
{
	//srandom(5);

	for (unsigned i = 0; i < 10; ++i)
	{
		boost::optional<locked_device> t = locked_device::try_lock_device();

		if (t)
		{
			t->use();

			int i = 0;
			cin >> i;

			return 0;
		}
		else
		{
			cout << "...trying again" << endl;
		}
	}
	cout << "fail..." << endl;

    return 0;
}

