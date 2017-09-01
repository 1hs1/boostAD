#pragma once

#include "task_wrap.h"

#include <boost/asio/deadline_timer.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/smart_ptr.hpp>

namespace detail {
	typedef boost::asio::deadline_timer::duration_type duration_type;

	// 타이머 객체
	template <class Functor>
	struct timer_task : public task_wrapped<Functor> {
	private:
		typedef task_wrapped<Functor> base_t;
		boost::shared_ptr<boost::asio::deadline_timer> timer_;

	public:
		template <class Time>
		explicit timer_task(
			boost::asio::io_service& ios,
			const Time& duration_or_time,
			const Functor& task_unwrapped)
			: base_t(task_unwrapped)
			, timer_(boost::make_shared<boost::asio::deadline_timer>(		// <=== 실제 asio::timer 생성
				boost::ref(ios), duration_or_time
				))
		{}

		void push_task() const {
			timer_->async_wait(*this);		// <=== 핵심!!! 여기서 binding 되는 Functor or Function 으로 async 호출됨

			//timer_->async_wait(std::bind(callback_timer_func, ...));	// 이런식으로 코딩해도 됨
		}

		void operator()(const boost::system::error_code& error) const {
			if (!error) {		// true 면 cancel 된 타이머 임. cancel 되는 경우에도 이곳이 호출되기 때문에 유의해서 사용해야 함
				base_t::operator()();
			}
			else {
				std::cerr << error << '\n';
			}
		}
	};



	// 타이머를 생성해주는 함수
	template <class Time, class Functor>
	inline timer_task<Functor> make_timer_task(
		boost::asio::io_service& ios,
		const Time& duration_or_time,
		const Functor& task_unwrapped)
	{
		return timer_task<Functor>(ios, duration_or_time, task_unwrapped);
	}



} // namespace detail
