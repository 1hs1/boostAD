// 07.06.iterator_range.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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

	// 구분자 설정
	// _SCL_SECURE_NO_WARNINGS 사용하여 경고 해제
	// make_split_iterator에서 내부적으로 copy시 확인되지 않은(boost) iterator를 사용하여 발생하는 것으로 파악
	// https://msdn.microsoft.com/ko-kr/library/aa985965.aspx

	typedef boost::split_iterator<const char*> split_iter_t;
	typedef boost::split_iterator<std::string::iterator> string_split_iter_t;
	//std::string delimeter("?!.");
	//auto predicator = [delimeter](const char c)
	//{
	//	return (delimeter.end() != std::find(std::begin(delimeter), std::end(delimeter), c));
	//};

	split_iter_t sentences = boost::make_split_iterator(str,
		boost::algorithm::token_finder(string_functor("?!."))		// Functor Struct 버전, _SCL_SECURE_NO_WARNINGS 사용안함
		//boost::algorithm::token_finder(predicator)				// 람다 functor 버전, _SCL_SECURE_NO_WARNINGS 사용안함
		//boost::algorithm::token_finder(boost::is_any_of("?!."))	// _SCL_SECURE_NO_WARNINGS 사용버전
	);

	for (unsigned int i = 1; !sentences.eof(); ++sentences, ++i) {
		boost::iterator_range<const char*> range = *sentences;
		std::cout << "Sentence #" << i << " : \t" << range << '\n';
		std::cout << "Sentence has " << range.size() << " characters.\n";
		std::cout
			<< "Sentence has "
			<< std::count(range.begin(), range.end(), ' ')
			<< " whitespaces.\n\n";
	} // for(...) 루프의 끝

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

} // main()의 끝

