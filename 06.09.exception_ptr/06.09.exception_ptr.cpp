// 06.09.exception_ptr.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"



#include <boost/exception_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "./tp/tp_base.h"
using namespace tp_base;

void func_test2(); // ���� ����

void process_exception(const boost::exception_ptr& exc) {
	try {
		boost::rethrow_exception(exc);
	}
	catch (const boost::bad_lexical_cast& /*e*/) {
		std::cout << "Lexical cast exception detected\n" << std::endl;

		// ������ �ٸ� �۾��� �о�ִ´�
		tasks_processor::get().push_task(&func_test2);
	}
	catch (...) {
		std::cout << "Can not handle such exceptions:\n"
			<< boost::current_exception_diagnostic_information()
			<< std::endl;

		// �ߴ�
		tasks_processor::get().stop();
	}
}

void func_test1() {
	try {
		boost::lexical_cast<int>("oops!");
	}
	catch (...) {
		tasks_processor::get().push_task(boost::bind(
			&process_exception, boost::current_exception()
		));
	}
}

#include <stdexcept>
void func_test2() {
	try {
		// ��� �ڵ带 ���� �д�
		BOOST_THROW_EXCEPTION(std::logic_error("Some fatal logic error"));
		// ��� �ڵ带 ���� �д�
	}
	catch (...) {
		tasks_processor::get().push_task(boost::bind(
			&process_exception, boost::current_exception()
		));
	}
}

void run_throw(boost::exception_ptr& ptr) {
	try {
		// ����� ���� �ڵ带 ���� �д�
		boost::lexical_cast<int>("oops!");
	}
	catch (...) {
		//ptr = boost::current_exception();
		try {
			throw;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
		/*catch (boost::exception_detail::clone_base & e) {
			std::cout << &e << std::endl;
		}*/
	}
}

int main() {
	tasks_processor::get().push_task(&func_test1);
	tasks_processor::get().start();


	boost::exception_ptr ptr;
	// �� ���� ���� ���ÿ� �����Ѵ�
	boost::thread t(boost::bind(
		&run_throw,
		boost::ref(ptr)
	));

	// ��� �ڵ带 ���� �д�
	// ...

	t.join();

	// ���� �˻�
	if (ptr) {
		// �����忡�� ���� �߻�
		boost::rethrow_exception(ptr);
	}
}

