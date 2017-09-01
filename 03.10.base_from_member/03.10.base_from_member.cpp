// 03.10.base_from_member.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <windows.h> // for EXCEPTION_ACCESS_VIOLATION

#include <boost/noncopyable.hpp>
#include <sstream>

class tasks_processor : boost::noncopyable {
	std::string& log_;

protected:
	virtual void do_process() = 0;

public:
	explicit tasks_processor(std::string& log)
		: log_(log)
	{
		std::cout << "tasks_processor construct" << std::endl;

		__try {
			log_ = "success construct";
			std::cout << log_ << std::endl;
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			std::cout << "Fail construct" << std::endl;
		}

	}

	void process() {
		log_ = "Starting data processing";
		std::cout << log_ << std::endl;
		do_process();
	}
};

class fake_tasks_processor : public tasks_processor {
	std::string logger_;

	virtual void do_process() {
		logger_ = "Fake processor processed!";
		std::cout << logger_ << std::endl;
	}

public:
	fake_tasks_processor()
		: tasks_processor(logger_) // 이런! logger_는 여기서 존재하지 않는다
		, logger_()
	{
		std::cout << "fake_tasks_processor construct" << std::endl;
	}

	//fake_tasks_processor()
	//	: logger_() // 이런! logger_ 은 tasks_processor 후에서야 생성된다
	//	, tasks_processor(logger_)
	//{}

};

#include <boost/utility/base_from_member.hpp>
class fake_tasks_processor_fixed
	: boost::base_from_member<std::string>
	, public tasks_processor
{
	typedef boost::base_from_member<std::string> logger_t;

	virtual void do_process() {
		logger_t::member = "Fake processor processed!";
		std::cout << logger_t::member << std::endl;
	}

public:
	fake_tasks_processor_fixed()
		: logger_t()
		, tasks_processor(logger_t::member)
	{}
};

class fake_tasks_processor2
	: boost::base_from_member<std::string, 0>
	, boost::base_from_member<std::string, 1>
	, public tasks_processor
{

	typedef boost::base_from_member<std::string, 0> logger0_t;
	typedef boost::base_from_member<std::string, 1> logger1_t;

	virtual void do_process() {
		logger0_t::member = "0: Fake processor2 processed!";
		logger1_t::member = "1: Fake processor2 processed!";
		std::cout << logger0_t::member << std::endl;
		std::cout << logger1_t::member << std::endl;
	}

public:
	fake_tasks_processor2()
		: logger0_t()
		, logger1_t()
		, tasks_processor(logger0_t::member)
	{}
};

int main()
{
	fake_tasks_processor tp;
	tp.process();

	std::cout << std::endl << std::endl << std::endl;
	

	fake_tasks_processor_fixed tp1;
	tp1.process();

	std::cout << std::endl << std::endl << std::endl;

	fake_tasks_processor2 tp2;
	tp2.process();

	std::cout << std::endl << std::endl << std::endl;

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

	return 0;
}

