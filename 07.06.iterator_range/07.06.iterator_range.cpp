// 07.06.iterator_range.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <algorithm>

struct string_functor {
private:
	std::string delimeter;

public:
	explicit string_functor(const std::string& s)
		: delimeter(s){}

	bool operator()(const char c) const
	{
		return delimeter.end() != std::find(std::begin(delimeter), std::end(delimeter), c);
	}
};

int main() {
	const char str[]
		= "This is a long long character array."
		"Please split this character array to sentences!"
		"Do you know, that sentences are separated using period, "
		"exclamation mark and question mark? :-)"
		;

	std::string str1
		= "This is a long long character array."
		"Please split this character array to sentences!"
		"Do you know, that sentences are separated using period, "
		"exclamation mark and question mark? :-)"
		;

	// ������ ����
	// _SCL_SECURE_NO_WARNINGS ����Ͽ� ��� ����
	// make_split_iterator���� ���������� copy�� Ȯ�ε��� ����(boost) iterator�� ����Ͽ� �߻��ϴ� ������ �ľ�
	// https://msdn.microsoft.com/ko-kr/library/aa985965.aspx

	typedef boost::split_iterator<const char*> split_iter_t;
	typedef boost::split_iterator<std::string::iterator> string_split_iter_t;
	//std::string delimeter("?!.");
	//auto predicator = [delimeter](const char c)
	//{
	//	return (delimeter.end() != std::find(std::begin(delimeter), std::end(delimeter), c));
	//};

	split_iter_t sentences = boost::make_split_iterator(str,
		boost::algorithm::token_finder(string_functor("?!."))		// Functor Struct ����, _SCL_SECURE_NO_WARNINGS ������
		//boost::algorithm::token_finder(predicator)				// ���� functor ����, _SCL_SECURE_NO_WARNINGS ������
		//boost::algorithm::token_finder(boost::is_any_of("?!."))	// _SCL_SECURE_NO_WARNINGS ������
	);

	for (unsigned int i = 1; !sentences.eof(); ++sentences, ++i) {
		boost::iterator_range<const char*> range = *sentences;
		std::cout << "Sentence #" << i << " : \t" << range << '\n';
		std::cout << "Sentence has " << range.size() << " characters.\n";
		std::cout
			<< "Sentence has "
			<< std::count(range.begin(), range.end(), ' ')
			<< " whitespaces.\n\n";
	} // for(...) ������ ��

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

} // main()�� ��

