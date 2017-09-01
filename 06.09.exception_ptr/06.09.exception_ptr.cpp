// 06.09.exception_ptr.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"



#include <boost/exception_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "./tp/tp_base.h"
using namespace tp_base;

void func_test2(); // 전방 선언

void process_exception(const boost::exception_ptr& exc) {
	try {
		boost::rethrow_exception(exc);
	}
	catch (const boost::bad_lexical_cast& /*e*/) {
		std::cout << "Lexical cast exception detected\n" << std::endl;

		// 실행할 다른 작업을 밀어넣는다
		tasks_processor::get().push_task(&func_test2);
	}
	catch (...) {
		std::cout << "Can not handle such exceptions:\n"
			<< boost::current_exception_diagnostic_information()
			<< std::endl;

		// 중단
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
		// 몇몇 코드를 여기 둔다
		BOOST_THROW_EXCEPTION(std::logic_error("Some fatal logic error"));
		// 몇몇 코드를 여기 둔다
	}
	catch (...) {
		tasks_processor::get().push_task(boost::bind(
			&process_exception, boost::current_exception()
		));
	}
}

void run_throw(boost::exception_ptr& ptr) {
	try {
		// 상당히 많은 코드를 여기 둔다
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
	// 몇 가지 일을 동시에 실행한다
	boost::thread t(boost::bind(
		&run_throw,
		boost::ref(ptr)
	));

	// 몇몇 코드를 여기 둔다
	// ...

	t.join();

	// 예외 검사
	if (ptr) {
		// 스레드에서 예외 발생
		boost::rethrow_exception(ptr);
	}
}

