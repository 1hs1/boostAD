// 05.04.work_queue.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <winbase.h>

#include <deque>
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

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

#include <condition_variable>

class work_queue {
public:
	typedef std::function<void()> task_type;

private:
	std::deque<task_type>   tasks_;
	//boost::mutex            tasks_mutex_;
	//boost::condition_variable cond_;
	std::mutex				tasks_mutex_;
	std::condition_variable cond_;

public:
	void push_task(const task_type& task) {
		//boost::unique_lock<boost::mutex> lock(tasks_mutex_);
		std::unique_lock<std::mutex> lock(tasks_mutex_);
		tasks_.push_back(task);
		lock.unlock();
		cond_.notify_one();
	}

	task_type try_pop_task() {
		task_type ret;
		//boost::lock_guard<boost::mutex> lock(tasks_mutex_);
		std::lock_guard<std::mutex> lock(tasks_mutex_);
		if (!tasks_.empty()) {
			ret = tasks_.front();
			tasks_.pop_front();
		}

		return ret;
	}

	task_type pop_task() {
		//boost::unique_lock<boost::mutex> lock(tasks_mutex_);
		std::unique_lock<std::mutex> lock(tasks_mutex_);
		while (tasks_.empty()) {
			cond_.wait(lock);
		}

		task_type ret = tasks_.front();
		tasks_.pop_front();

		return ret;
	}
};

// 테스트
#include <boost/thread/thread.hpp>

work_queue g_queue;
//int i = 0;

void do_nothing() { /*std::cout << i++ << " ThreadID : " << boost::this_thread::get_id() << std::endl;*/ }
const std::size_t tests_tasks_count = 300000;
void pusher() {
	for (std::size_t i = 0; i < tests_tasks_count; ++i) {
		// 아무 일도 안하는 작업 추가
		g_queue.push_task(&do_nothing);
	}

	//std::cout << "push threadid : " << boost::this_thread::get_id() << std::endl;
}

void popper_sync() {
	for (std::size_t i = 0; i < tests_tasks_count; ++i) {
		work_queue::task_type f = g_queue.pop_task(); // 작업 하나를 얻는다
		f(); // 작업을 실행한다
	}

	//std::cout << "put threadid : " << boost::this_thread::get_id() << std::endl;
}

int main()
{
	{
		StopWatch time("Test1");

		//boost::thread pop_sync1(&popper_sync);
		//boost::thread pop_sync2(&popper_sync);
		//boost::thread pop_sync3(&popper_sync);

		//boost::thread push1(&pusher);
		//boost::thread push2(&pusher);
		//boost::thread push3(&pusher);

		//// 모든 작업이 꺼내질 때까지 기다린다
		//pop_sync1.join();
		//pop_sync2.join();
		//pop_sync3.join();

		//push1.join();
		//push2.join();
		//push3.join();
		std::vector<std::thread> vecPoper;
		for (int i = 0; i < 30; ++i)
		{
			std::thread t(&popper_sync);
			vecPoper.emplace_back(std::move(t));
		}

		std::vector<std::thread> vecPusher;
		for (int i = 0; i < 30; ++i)
		{
			std::thread t(&pusher);
			vecPusher.emplace_back(std::move(t));
		}

		for (int i = 0; i < vecPoper.size(); ++i)
		{
			vecPoper[i].join();
		}

		for (int i = 0; i < vecPusher.size(); ++i)
		{
			vecPusher[i].join();
		}

		// 이제 남은 작업이 없어야 하고
		// 멈추는 일 없이 끝까지 실행되야 한다
		assert(!g_queue.try_pop_task());
	}

	g_queue.push_task(&do_nothing);
	// 작업이 하나 있어야 하고
	// 멈추는 일 없이 끝까지 실행되야 한다 
	assert(g_queue.try_pop_task());

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

