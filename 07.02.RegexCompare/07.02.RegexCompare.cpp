// 07.02.RegexCompare.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <boost/regex.hpp>
#include <iostream>
using namespace boost;

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

	// ���� ����
	// ���� : http://www.boost.org/doc/libs/1_63_0/libs/regex/doc/html/boost_regex/syntax.html
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
	// ���� ��Ȱ��ȭ
	flag |= boost::regex::no_except;

	// std::cin ����
	std::cin.ignore();
	std::cin.clear();

	std::string regex, str;
	do {
		std::cout << "Input regex (ex. ^a{2,3}$): ";
		if (!std::getline(std::cin, regex) || regex.empty()) {
			return 0;
		}
		// sample : Minimum 8 characters at least 1 Alphabet and 1 Number:
		// ^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{8,}$

		// `boost::regex::no_except` �÷��װ� ������
		// �� �����ڴ� ���ܸ� ���� ���� �ִ�
		const boost::regex e(regex, flag);
		if (e.status()) {
			std::cout << "Incorrect regex pattern!\n";
			continue;
		}

		std::cout << "String to match: ";
		while (std::getline(std::cin, str) && !str.empty()) {
			bool matched = boost::regex_match(str, e);
			std::cout << (matched ? "MATCH\n" : "DOES NOT MATCH\n");
			std::cout << "String to match: ";
		} // `while (std::getline(std::cin, str))`�� ��

		std::cout << '\n';

		// std::cin ����
		std::cin.ignore();
		std::cin.clear();
	} while (1);

    return 0;
}

