// 05.05.shared_lock.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <winbase.h>

#include <map>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

class StopWatch
{
public:
	StopWatch(std::string Function) : m_Function(Function)
	{
		QueryPerformanceFrequency(&m_FreqPerSecond);
		QueryPerformanceCounter(&m_StartFreq);
	}

	~StopWatch()
	{
		LARGE_INTEGER NowFreq;
		QueryPerformanceCounter(&NowFreq);
		uint64_t ElapsedTime = (NowFreq.QuadPart - m_StartFreq.QuadPart) / (m_FreqPerSecond.QuadPart / 1000000);	// 마이크로초
		std::cout << "[STOPWATCH] Function : " << m_Function.c_str() << " ElapsedTime : " << static_cast<float>(ElapsedTime / 1000000.f) << std::endl;
	}

private:
	std::string m_Function;

	// 초당 카운트 수
	LARGE_INTEGER m_FreqPerSecond;

	// 시작 카운트 수
	LARGE_INTEGER m_StartFreq;
};

struct user_info {
	std::string address;
	unsigned short age;

	// 다른 파라미터들
	// ...
};

namespace first_example {

	class users_online {
		typedef boost::mutex                mutex_t;
		mutable mutex_t                     users_mutex_;
		std::map<std::string, user_info>    users_;

	public:
		bool is_online(const std::string& username) const {
			boost::lock_guard<mutex_t> lock(users_mutex_);
			return users_.find(username) != users_.end();
		}

		unsigned short get_age(const std::string& username) const {
			boost::lock_guard<mutex_t> lock(users_mutex_);
			return users_.at(username).age;
		}

		void set_online(const std::string& username, const user_info& data) {
			boost::lock_guard<mutex_t> lock(users_mutex_);
			users_.insert(std::make_pair(username, data));
		}

		// 다른 메소드들
		// ...
	};

}

#include <boost/thread/shared_mutex.hpp>

namespace shared_lock_example {

	class users_online {
		typedef boost::shared_mutex         mutex_t;
		mutable mutex_t                     users_mutex_;
		std::map<std::string, user_info>    users_;

	public:
		bool is_online(const std::string& username) const {
			boost::shared_lock<mutex_t> lock(users_mutex_);
			return users_.find(username) != users_.end();
		}

		unsigned short get_age(const std::string& username) const {
			boost::shared_lock<mutex_t> lock(users_mutex_);
			return users_.at(username).age;
		}

		void set_online(const std::string& username, const user_info& data) {
			boost::lock_guard<mutex_t> lock(users_mutex_);
			users_.insert(std::make_pair(username, data));
		}

		// 다른 메소드들
		// ...
	};

}

#include <boost/thread/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

const std::size_t users_count = 100000;

template <class T>
void log_in(T& u, std::size_t count) {
	for (std::size_t i = 0; i < count; ++i) {
		u.set_online(boost::lexical_cast<std::string>(i), user_info());
	}
}

template <class T>
void thread_get_age(T& u) {
	for (std::size_t i = 0; i < users_count; ++i) {
		u.get_age(boost::lexical_cast<std::string>(i));
	}
}

template <class T>
void thread_is_online(T& u) {
	for (std::size_t i = 0; i < users_count; ++i) {
		assert(u.is_online(boost::lexical_cast<std::string>(i)));
	}
}

int main()
{
	{
		StopWatch time("Test1");

		// 네임스페이스 first_example 사용	shared_lock_example
		using namespace shared_lock_example;
		users_online users;

		log_in(users, users_count);

		boost::thread t1(boost::bind(&thread_get_age<users_online>, boost::ref(users)));
		boost::thread t2(boost::bind(&thread_get_age<users_online>, boost::ref(users)));
		boost::thread t3(boost::bind(&thread_is_online<users_online>, boost::ref(users)));
		boost::thread t4(boost::bind(&thread_is_online<users_online>, boost::ref(users)));

		boost::thread t5(boost::bind(&log_in<users_online>, boost::ref(users), 5));
		boost::thread t6(boost::bind(&log_in<users_online>, boost::ref(users), 25));

		t1.join();
		t2.join();
		t3.join();
		t4.join();

		t5.join();
		t6.join();

		assert(1);
	}

	while (1)
	{
		if (_kbhit())
		{
			if (_getch() == 27)	// ESC key
			{
				break;
			}
		}
	}
}

