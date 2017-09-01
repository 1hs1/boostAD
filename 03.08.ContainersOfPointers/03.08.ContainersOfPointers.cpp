// 03.08.ContainersOfPointers.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <boost/ptr_container/ptr_set.hpp>

#include <iostream>

// ��ü ����/�Ҹ��� ����Ʈ �ϴ� Ŭ����
class Object
{
public:
	int idx_;

public:
	Object() {
		static int s_idx = 0;
		idx_ = ++s_idx;

		std::cout << __FUNCTION__ << " - " << idx_ << std::endl;
	}

	Object(const int specificIdx) : idx_(specificIdx) {}

	~Object() {
		std::cout << __FUNCTION__ << " - " << idx_ << std::endl;
	}

	void setId(const int idx) {
		int old = idx_;
		idx_ = idx;
		std::cout << __FUNCTION__ << " - " << old << "->" << idx_ << std::endl;
	}
};

bool operator < (const Object& lhs, const Object& rhs) {
	return lhs.idx_ < rhs.idx_;
}





// **************************************************************************************
// case 1 : scope ���� ���� ������
void test___ptr_set() {
	boost::ptr_set<Object> s;
	s.insert(new Object());
	s.insert(new Object());
	// s �����̳ʰ� �Ҹ�Ǹ鼭 �ڵ����� Object �鵵 delete ��
}



// **************************************************************************************
// case 2 : �����ϱ�
#include <boost/ptr_container/clone_allocator.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

// clone �� �����ϱ� ���� ���ǵǾ�� ��
Object* new_clone(const Object& src) {
	Object* newObj = new Object();
	newObj->setId(src.idx_ * 100);
	return newObj;
}

void test___clone() {
	boost::ptr_vector<Object> s;

	Object* sampleObj = new Object(999);

	// ���� ������ �� �� ���� new_clone �� ȣ�� ��
	s.resize(10, sampleObj);

	delete sampleObj;
}

int main()
{
	test___ptr_set();

	test___clone();


	// Boost.PointerContainer ���� �Ʒ� �����̳ʵ��� ������
	// ptr_array, ptr_vector, ptr_set, ptr_multimap �� �⺻ �����̳� ���� ������

	// ���ǻ���
	// resize �Ǵ� assign �� ���� ���� ��, new_clone() �� ���ǵǾ� ���� �ʴٸ� memcpy ������� ������
	// ��, operator = �� ȣ����� �ʰ�, ���� ���縸 �߻��ϱ� ������ �����ؼ� ����ؾ� ��
	
	// �뵵?
	// shared_ptr �� atomic �� lock�� ���� �ȴٸ�...
	// stack�� �޸𸮸����� ó���ϱ� ����������, ���� scope������ ó���ϰ� ���� ó���� �ִٸ�...
	// ...?

	return 0;
}

