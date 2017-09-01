#pragma once

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
	inline task_wrapped<T> make_task_wrapped(const T& task_unwrapped) {
		return task_wrapped<T>(task_unwrapped);
	}

} // namespace detail
