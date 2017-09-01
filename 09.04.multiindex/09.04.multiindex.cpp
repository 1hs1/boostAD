// 09.04.multiindex.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
// 다중 인덱스 컨테이너 생성

#include "stdafx.h"
#include <string>

std::size_t next_id();

struct person {
	std::size_t     id_;
	std::string     name_;
	unsigned int    height_;
	unsigned int    weight_;

	person(std::size_t id, const std::string& name, unsigned int height, unsigned int weight)
		: id_(id)
		, name_(name)
		, height_(height)
		, weight_(weight)
	{}
};

inline bool operator < (const person& p1, const person& p2) {
	return p1.name_ < p2.name_;
}

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>

template <std::size_t IndexNo, class Indexes>
void print(const Indexes& persons) {
	std::cout << IndexNo << ":\n";
	typedef typename Indexes::template nth_index<
		IndexNo
	>::type::const_iterator const_iterator_t;

	for (const_iterator_t it = persons.template get<IndexNo>().begin(),
		iend = persons.template get<IndexNo>().end();
		it != iend;
		++it)
	{
		const person& v = *it;
		std::cout
			<< v.name_ << ", "
			<< v.id_ << ", "
			<< v.height_ << ", "
			<< v.weight_ << '\n'
			;
	}

	std::cout << '\n';
}

void example_main() {
	typedef boost::multi_index::multi_index_container <
		person,
		boost::multi_index::indexed_by <
		// 이름은 고유해야 한다
		boost::multi_index::ordered_unique<
		boost::multi_index::identity<person>
		>,

		// ID는 고유하지 않으며, 정렬할 필요도 없다
		boost::multi_index::hashed_non_unique<
		boost::multi_index::member<
		person, std::size_t, &person::id_
		>
		>,

		// 키는 고유하지 않지만, 정렬되어 있어야 한다
		boost::multi_index::ordered_non_unique<
		boost::multi_index::member<
		person, unsigned int, &person::height_
		>
		>,

		// 무게도 고유하지 않지만 정렬되어 있어야 한다
		boost::multi_index::ordered_non_unique<
		boost::multi_index::member<
		person, unsigned int, &person::weight_
		>
		>
		> // `boost::multi_index::indexed_by<` 끝남
	> indexes_t;

	indexes_t persons;

	// 값 삽입
	persons.insert(person(1, "John Snow", 185, 80));
	persons.insert(person(2, "Vasya Pupkin", 165, 60));
	persons.insert(person(3, "Antony Polukhin", 183, 70));
	// "Antony Polukhin"이라는 동일 인물 삽입
	persons.insert(person(3, "Anton Polukhin", 182, 70));

	print<0>(persons);
	print<1>(persons);
	print<2>(persons);
	print<3>(persons);


	assert(persons.get<1>().find(2)->name_ == "Vasya Pupkin");
	assert(
		persons.find(person(
			77, "Anton Polukhin", 0, 0
		)) != persons.end()
	);

	// 컴파일 되지 않는다
	//assert(persons.get<0>().find("John Snow")->id_ == 1);

	typedef indexes_t::nth_index<0>::type::const_iterator const_iterator_t;
	for (const_iterator_t it = persons.get<0>().begin(),
		iend = persons.get<0>().end();
		it != iend;
		++it)
	{
		const person& v = *it;
		// ...
		(void)v;
	}
}

// 태그를 사용한 코드와 거의 같다.
namespace tag {
	struct name;
	struct id;
	struct height;
	struct weight;
}

void example_2() {
	typedef boost::multi_index::multi_index_container <
		person,
		boost::multi_index::indexed_by <
		// 이름은 고유해야 한다
		boost::multi_index::ordered_unique<
		boost::multi_index::tag<tag::name>,
		boost::multi_index::member<person, std::string, &person::name_>
		>,

		// ID는 고유하지 않으며, 정렬할 필요도 없다 
		boost::multi_index::hashed_non_unique<
		boost::multi_index::tag<tag::id>,
		boost::multi_index::member<person, std::size_t, &person::id_>
		>,

		// 키는 고유하지 않지만, 정렬되어 있어야 한다
		boost::multi_index::ordered_non_unique<
		boost::multi_index::tag<tag::height>,
		boost::multi_index::member<person, unsigned int, &person::height_>
		>,

		// 무게도 고유하지 않지만 정렬되어 있어야 한다
		boost::multi_index::ordered_non_unique<
		boost::multi_index::tag<tag::weight>,
		boost::multi_index::member<person, unsigned int, &person::weight_>
		>
		> // `boost::multi_index::indexed_by<` 끝남
	> indexes_t;

	indexes_t persons;

	// 값 삽입
	persons.insert(person(1, "John Snow", 185, 80));
	persons.insert(person(2, "Vasya Pupkin", 165, 60));
	persons.insert(person(3, "Antony Polukhin", 183, 70));
	// "Antony Polukhin"이라는 동일 인물 삽입
	persons.insert(person(3, "Anton Polukhin", 182, 70));

	// 이제 컴파일된다
	assert(persons.get<tag::name>().find("John Snow")->id_ == 1);

	assert(persons.get<tag::id>().find(2)->name_ == "Vasya Pupkin");

	// `persons.get<0>().find("Anton Polukhin")`라고 하는 것과 같다
	assert(persons.find("Anton Polukhin")->id_ == 3);
}

int main() {
	example_main();
	example_2();
}