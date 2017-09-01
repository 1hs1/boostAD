// 01.02.Program_Option.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <boost/program_options.hpp>
#include <iostream>
#include <conio.h>

namespace opt = boost::program_options;

int main(int argc, char* argv[])
{
	opt::options_description desc("All options");

	desc.add_options()
		("apples,a", opt::value<int>()->default_value(10), "how many apples do you have")
		("oranges,o", opt::value<int>(), "how many oranges do you have")
		("name", opt::value<std::string>(), "your name")
		("help", "produce help message");

	// command line parse
	opt::variables_map vm;
	opt::store(opt::parse_command_line(argc, argv, desc), vm);
	opt::notify(vm);

	if (vm.count("help"))
	{
		std::cout << desc << std::endl;
		return 1;
	}

	// config file(.cfg) parse
	try
	{
		opt::store(opt::parse_config_file<char>("apples_oranges.cfg", desc), vm);
	}
	catch (const opt::reading_file& e)
	{
		std::cout << "Failed to open configuration file 'apples_oranges.cfg':"
			<< e.what() << std::endl;
	}
	opt::notify(vm);

	size_t namecount = vm.count("name");
	if (namecount)
	{
		std::cout << "Hi," << vm["name"].as<std::string>() << "!" << std::endl;
	}

	std::cout << "Fruits count: "
		<< vm["apples"].as<int>() + vm["oranges"].as<int>()
		<< std::endl;

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

