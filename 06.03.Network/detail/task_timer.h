#pragma once

#include "task_wrap.h"

#include <boost/asio/deadline_timer.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/smart_ptr.hpp>

namespace detail {
	typedef boost::asio::deadline_timer::duration_type duration_type;

	// Ÿ�̸� ��ü
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
			, timer_(boost::make_shared<boost::asio::deadline_timer>(		// <=== ���� asio::timer ����
				boost::ref(ios), duration_or_time
				))
		{}

		void push_task() const {
			timer_->async_wait(*this);		// <=== �ٽ�!!! ���⼭ binding �Ǵ� Functor or Function ���� async ȣ���

			//timer_->async_wait(std::bind(callback_timer_func, ...));	// �̷������� �ڵ��ص� ��
		}

		void operator()(const boost::system::error_code& error) const {
			if (!error) {		// true �� cancel �� Ÿ�̸� ��. cancel �Ǵ� ��쿡�� �̰��� ȣ��Ǳ� ������ �����ؼ� ����ؾ� ��
				base_t::operator()();
			}
			else {
				std::cerr << error << '\n';
			}
		}
	};



	// Ÿ�̸Ӹ� �������ִ� �Լ�
	template <class Time, class Functor>
	inline timer_task<Functor> make_timer_task(
		boost::asio::io_service& ios,
		const Time& duration_or_time,
		const Functor& task_unwrapped)
	{
		return timer_task<Functor>(ios, duration_or_time, task_unwrapped);
	}



} // namespace detail
