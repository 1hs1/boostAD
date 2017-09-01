#pragma once

#include "tp_multithread.h"


#include <boost/asio/signal_set.hpp>
#include <boost/function.hpp>

namespace tp_full {

	class tasks_processor : public tp_base::tasks_processor {
		//: public tp_multithread::tasks_processor {
		/*
		tasks_processor()
		: ios_()
		, work_(ios_)
		, signals_(ios_)
		{}
		*/

		tasks_processor()
			//: tp_multithread::tasks_processor()
			: tp_base::tasks_processor()
			, signals_(ios_)
		{}


	public:
		static tasks_processor& get() {
			static tasks_processor s_tasks_processor;
			return s_tasks_processor;
		};

	private:
		boost::asio::signal_set signals_;
		boost::function<void(int)>   users_signal_handler_;

		// private
		void handle_signals(
			const boost::system::error_code& error,
			int signal_number)
		{
			if (error) {
				std::cerr << "Error in signal handling: " << error << '\n';
			}
			else {
				// 더 이상 기다리는 처리기가 없을 때 신호가 발생한다면,
				// 신호 알림이 큐에 쌓인다.
				// 그래서 users_signal_handler_ 실행하는 동안
				// 신호를 잃어버릴 일은 없다.
				detail::make_task_wrapped(boost::bind(
					boost::ref(users_signal_handler_), signal_number
				))(); // make and run task_wrapped
			}

			signals_.async_wait(boost::bind(
				&tasks_processor::handle_signals, this, _1, _2
			));
		}
	public:

		// 이 함수는 스레드에서 안전하지 않다.
		// start() 호출이 전에 불려야 한다.
		// 단 한번만 불릴 수 있다
		template <class Func>
		void register_signals_handler(
			const Func& f,
			const std::vector<int>& signals_to_wait)
		{
			// Making shure that this is the first call
			assert(!users_signal_handler_);

			users_signal_handler_ = f;
			std::for_each(
				signals_to_wait.begin(),
				signals_to_wait.end(),
				boost::bind(
					&boost::asio::signal_set::add, &signals_, _1
				)
			);

			signals_.async_wait(boost::bind(
				&tasks_processor::handle_signals, this, _1, _2
			));
		}
	};

} // namespace tp_full


