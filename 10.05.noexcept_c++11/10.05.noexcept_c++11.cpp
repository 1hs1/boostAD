// 10.05.noexcept_c++11.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
// c++11���� ����� ���� ���������� ������ ���̰� �ڵ� ũ��� ���̱�

#include "stdafx.h"

#include <boost/config.hpp>

// EMC++ : ���ܸ� �������� ���� �Լ��� noexcept�� �����϶�

// int f(int x) throw();   //f�� ���ܸ� ������ ���� : C++98 ���
// int f(int x) noexcept; // f�� ���ܸ� ������ ���� : C++11 ���

// throw() �� ��쿡�� f�� �Ҹ� ���������� callstack�� Ǯ���� �˴ϴ�.
// �׸��� ���� ���� ó���� �ϰ� ����(terminate)�˴ϴ�.
// noexcept�� ��쿡�� ȣ�� ������ Ǯ�� ���� �ְ� �׷��� ���� ���� �ֽ��ϴ�
// ����ȭ : noexcept > throw()

// C++11������ �⺻������ ��� �޸� ���� �Լ��� ��� �Ҹ��� �Լ��� �Ϲ������� noexcept�Դϴ�

class move_nothrow {
	// Ŭ���� ����� ���⿡
	// ...
public:
	move_nothrow() BOOST_NOEXCEPT {}
	// �̵� ������ BOOST_NOEXCEPT �ּ��ص� ���� �ȳ�.
	move_nothrow(move_nothrow&&) BOOST_NOEXCEPT
		// : ��� �ʱ�ȭ
		// ...
	{}

	move_nothrow& operator=(move_nothrow&&) BOOST_NOEXCEPT {
		// ����
		// ...
		return *this;
	}

	move_nothrow(const move_nothrow&);
	move_nothrow& operator=(const move_nothrow&);
};


#include <vector>
int main() {

	std::vector<move_nothrow> v(10);
	v.push_back(move_nothrow());

}

// ��� ���Ͽ�
int foo() BOOST_NOEXCEPT;


// �ҽ� ���Ͽ�
int foo() BOOST_NOEXCEPT {
	return 0;
}
