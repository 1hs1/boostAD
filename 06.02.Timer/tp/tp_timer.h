#pragma once

#include "tp_base.h"

#include "../detail/task_timer.h"

namespace tp_timer {

	class tasks_processor : public tp_base::tasks_processor
	{
	public:
		static tasks_processor& get() {
			static tasks_processor s_tasks_processor;
			return s_tasks_processor;
		};

		// 타이머 기능 추가됨
		typedef boost::asio::deadline_timer::duration_type duration_type;

		template <class Functor>
		void run_after(duration_type duration, const Functor& f) {
			detail::make_timer_task(ios_, duration, f)
				.push_task();
		}

		typedef boost::asio::deadline_timer::time_type time_type;

		template <class Functor>
		void run_at(time_type time, const Functor& f) {
			detail::make_timer_task(ios_, time, f)
				.push_task();
		}
	};

}
