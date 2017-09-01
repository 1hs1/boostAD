#pragma once

#include <boost/asio/io_service.hpp>

namespace tp_base {

	class tasks_processor : private boost::noncopyable {
	protected:
		boost::asio::io_service         ios_;
		boost::asio::io_service::work   work_;

		tasks_processor()
			: ios_()
			, work_(ios_)
		{}

	public:
		static tasks_processor& get() {
			static tasks_processor s_tasks_processor;
			return s_tasks_processor;
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

		

	}; // tasks_processor

} // namespace base::
