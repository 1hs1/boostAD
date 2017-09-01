// 07.03.RegexFindReplace.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <boost/regex.hpp>
#include <iostream>


int main()
{
	std::cout
		<< "Available regex syntaxes:\n"
		<< "\t[0] Perl\n"
		<< "\t[1] Perl case insensitive\n"
		<< "\t[2] POSIX extended\n"
		<< "\t[3] POSIX extended case insensitive\n"
		<< "\t[4] POSIX basic\n"
		<< "\t[5] POSIX basic case insensitive\n"
		<< "Choose regex syntax: ";

	boost::regex::flag_type flag;
	switch (std::cin.get()) {
	case '0': flag = boost::regex::perl;
		break;

	case '1': flag = boost::regex::perl | boost::regex::icase;
		break;

	case '2': flag = boost::regex::extended;
		break;

	case '3': flag = boost::regex::extended | boost::regex::icase;
		break;

	case '4': flag = boost::regex::basic;
		break;

	case '5': flag = boost::regex::basic | boost::regex::icase;
		break;
	default:
		std::cout << "Inccorect number of regex syntax. Exiting... \n";
		return -1;
	}
	flag |= boost::regex::no_except;

	std::cin.ignore();
	std::cin.clear();

	std::string regex, str, replace_string;
	do {
		std::cout << "\nInput regex: ";
		if (!std::getline(std::cin, regex)) {
			return 0;
		}

		const boost::regex e(regex, flag);
		if (e.status()) {
			std::cout << "Incorrect regex pattern!\n";
			continue;
		}

		std::cout << "String to match: ";
		while (std::getline(std::cin, str) && !str.empty()) {
			boost::smatch results;
			bool matched = regex_search(str, results, e);
			if (matched) {
				std::cout << "MATCH: ";
				std::copy(
					results.begin(),
					results.end(),
					std::ostream_iterator<std::string>(std::cout, ", ")
				);
				// (a|b|c)

				std::cout << "\nReplace pattern: ";
				if (
					std::getline(std::cin, replace_string)
					&& !replace_string.empty())
				{
					std::cout << "RESULT: " << boost::regex_replace(str, e, replace_string);
					//std::cout << "RESULT: " << results.format(replace_string);	// results 의 값을 변경 할 수 있다. 이건 왜 쓰는지?
				}
				else {
					std::cin.ignore();
					std::cin.clear();
				}
			}
			else {
				std::cout << "DOES NOT MATCH";
			}

			std::cout << "\nString to match: ";
		}

		std::cout << '\n';

		std::cin.ignore();
		std::cin.clear();
	} while (1);

    return 0;
}
