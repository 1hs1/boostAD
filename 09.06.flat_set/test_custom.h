#pragma once

// ����� Ÿ�� �� operator ������
struct person {
	int id;
	std::string name;
};
bool operator < (person const& lhs, person const& rhs) {
	return lhs.id < rhs.id;
}

void test_custom() {
	boost::container::flat_set<person> set;

	set.reserve(4096);

	for (int i = 0; i < 4000; ++i) {
		set.insert(person{ i, "person_" + std::to_string(i) });
	}

	// ã�� �͵� ������
	auto & per = *set.lower_bound(person{ 499 });
	std::cout << per.id << " - " << per.name << std::endl;

	std::cout << "=====================" << std::endl;

	// �ݺ��� ������
	auto itr = set.lower_bound(person{ 500 });
	for (int i = 0; i < 10; ++i, ++itr) {
		auto & per = *itr;
		std::cout << per.id << " - " << per.name << std::endl;
	}
}
