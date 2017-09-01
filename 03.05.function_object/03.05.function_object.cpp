// 03.05.function_object.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <list>

// std::unary_function<> ���ø����� ���
#include <functional>
// int�� �޾Ƶ��̰� �ƹ� �͵� ��ȯ���� �ʴ� 
// �Լ� �����Ϳ� ���� typedef 
typedef void(*func_t)(int);

// �Լ��� ���� �����͸� �޾� 
// �ڽ��� ���� �� ������ ���� �� �Լ��� ȣ���ϴ� �Լ�
// �Լ� ��ü�� ���� ���Ѵ� :(
void process_integers(func_t f);

// �Լ� ��ü
class int_processor : public std::unary_function<int, void> {
	const int min_;
	const int max_;
	bool& triggered_;

public:
	int_processor(int min, int max, bool& triggered)
		: min_(min)
		, max_(max)
		, triggered_(triggered)
	{}

	void operator()(int i) const {
		if (i < min_ || i > max_) {
			triggered_ = true;
		}
	}
};

#include <boost/function.hpp>
typedef boost::function<void(int)> fobject_t;

// ���� �� �Լ������� �Լ� ��ü�� ���� �� �ִ�
void process_integers(const fobject_t& f);
void process_integers_L(int min, int max, bool& triggered);

int main() {
	bool is_triggered = false;
	int_processor fo(0, 200, is_triggered);
	process_integers(fo);
	process_integers_L(0, 200, is_triggered);
	assert(is_triggered);
}



void foo(const fobject_t& f) {
	// boost::function�� bool�� ��ȯ�� �� �ִ�
	if (f) {
		// 'f'�� ���� �ִٸ�
		// ...
	}
	else {
		// 'f'�� ����ٸ�
		// ...
	}
}

bool g_is_triggered = false;
void set_functional_object(fobject_t& f) {
	int_processor fo(100, 200, g_is_triggered);
	f = fo;
	// ������ ������ 'fo'�� �Ҹ�ȴ�
	// �׷����� 'f'�� ���� ��/�ܿ��� �� �� �ִ�.
}

#include <vector>
#include <algorithm>
#include <boost/bind.hpp>
void foo1() {
	std::vector<int> v;
	std::for_each(v.begin(), v.end(), boost::bind(std::plus<int>(), 10, _1));

	fobject_t f(boost::bind(std::plus<int>(), 10, _1));
	std::for_each(v.begin(), v.end(), f);
}

void process_integers(const fobject_t& f) {
	/*static const int data[] = { 1, 2, 3, 4, 5, 2001 };
	std::for_each(data, data + sizeof(data), f);
	std::for_each(data, data + (sizeof(data)/sizeof(int)), f);
	std::for_each(data, data + _countof(data), f);*/
	std::list<int> data;
	data.clear();
	data.push_back(1);
	data.push_back(2);
	data.push_back(200);
	data.push_back(201);
	std::for_each(data.begin(), data.end(), f);
}

void process_integers_L(int min, int max, bool& triggered)
{
	std::list<int> data;
	data.clear();
	data.push_back(1);
	data.push_back(2);
	data.push_back(200);
	data.push_back(201);
	std::for_each(data.begin(), data.end(), [=,&triggered](int i) {
			if (i < min || i > max) {
				triggered = true;
			}
		}
	);
}