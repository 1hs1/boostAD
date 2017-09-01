// 06.01.manipulating_tasks.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <boost/thread/thread.hpp>

namespace detail {

	template <class T>
	struct task_wrapped {
	private:
		T task_unwrapped_;

	public:
		explicit task_wrapped(const T& task_unwrapped)
			: task_unwrapped_(task_unwrapped)
		{}

		void operator()() const {
			// resetting interruption
			try {
				boost::this_thread::interruption_point();
			}
			catch (const boost::thread_interrupted&) {}

			try {
				// Executing task
				task_unwrapped_();
			}
			catch (const std::exception& e) {
				std::cerr << "Exception: " << e.what() << '\n';
			}
			catch (const boost::thread_interrupted&) {
				std::cerr << "Thread interrupted\n";
			}
			catch (...) {
				std::cerr << "Unknown exception\n";
			}
		}
	};

	template <class T>
	task_wrapped<T> make_task_wrapped(const T& task_unwrapped)
	{
		return task_wrapped<T>(task_unwrapped);
	}

} // namespace detail


#include <boost/asio/io_service.hpp>
class tasks_processor : private boost::noncopyable {
	boost::asio::io_service         ios_;
	boost::asio::io_service::work   work_;
	tasks_processor()
		: ios_()
		, work_(ios_)
	{}
public:
	static tasks_processor& get() {
		static tasks_processor tp;
		return tp;
	};
	
	template <class T>
	inline void push_task(const T& task_unwrapped) {
		ios_.post(detail::make_task_wrapped(task_unwrapped));
	}

	void start() {
		ios_.run();
	}
	void stop() {
		ios_.stop();
	}

	bool stoped() {
		return ios_.stopped();
	}

}; // tasks_processor

int g_val = 0;
void func_test() {
	if (tasks_processor::get().stoped())
		return;

	++g_val;
	if (g_val == 3) {
		throw std::logic_error("Just checking");
	}

	boost::this_thread::interruption_point();
	if (g_val == 10) {
		// Emulation of thread interruption.
		// Will be caught and won't stop execution.
		throw boost::thread_interrupted();
	}
	if (g_val == 90) {
		// 내부적으로 플래그만 수정하는듯 합니다. stoped() 체크해서 사용
		tasks_processor::get().stop();

		// stop() 이후에는 post() 해도 적용되지 않습니다.
		tasks_processor::get().push_task(&func_test);
	}
}

int main() {
	static const std::size_t tasks_count = 100;
	// stop() is called at 90
	BOOST_STATIC_ASSERT(tasks_count > 90);
	for (std::size_t i = 0; i < tasks_count; ++i) {
		tasks_processor::get().push_task(&func_test);
	}

	// We can also use result of boost::bind call
	// as a task
	tasks_processor::get().push_task(
		boost::bind(std::plus<int>(), 2, 2) // counting 2 + 2
	);

	// Processing was not started.
	assert(g_val == 0);

	// Will not throw, but blocks till
	// one of the tasks it is owning
	// calls stop().
	tasks_processor::get().start();
	assert(g_val == 90);
}
