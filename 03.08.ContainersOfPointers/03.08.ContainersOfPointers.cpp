// 03.08.ContainersOfPointers.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <boost/ptr_container/ptr_set.hpp>

#include <iostream>

// 객체 생성/소멸을 프린트 하는 클래스
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
// case 1 : scope 에서 쓰고 버리기
void test___ptr_set() {
	boost::ptr_set<Object> s;
	s.insert(new Object());
	s.insert(new Object());
	// s 컨테이너가 소멸되면서 자동으로 Object 들도 delete 됨
}



// **************************************************************************************
// case 2 : 복제하기
#include <boost/ptr_container/clone_allocator.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

// clone 을 지원하기 위해 정의되어야 함
Object* new_clone(const Object& src) {
	Object* newObj = new Object();
	newObj->setId(src.idx_ * 100);
	return newObj;
}

void test___clone() {
	boost::ptr_vector<Object> s;

	Object* sampleObj = new Object(999);

	// 복사 생성이 될 때 마다 new_clone 이 호출 됨
	s.resize(10, sampleObj);

	delete sampleObj;
}

int main()
{
	test___ptr_set();

	test___clone();


	// Boost.PointerContainer 에는 아래 컨테이너들이 존재함
	// ptr_array, ptr_vector, ptr_set, ptr_multimap 등 기본 컨테이너 거의 제공됨

	// 유의사항
	// resize 또는 assign 등 복사 동작 시, new_clone() 가 정의되어 있지 않다면 memcpy 방식으로 동작함
	// 즉, operator = 이 호출되지 않고, 얕은 복사만 발생하기 때문에 조심해서 사용해야 함
	
	// 용도?
	// shared_ptr 의 atomic 한 lock질 조차 싫다면...
	// stack의 메모리만으로 처리하긴 부족하지만, 현재 scope에서만 처리하고 싶은 처리가 있다면...
	// ...?

	return 0;
}

