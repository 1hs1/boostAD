// 06.06.conveyor.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <winbase.h>

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

#include <boost/thread/thread.hpp>

#include <vector>
struct data_packet { unsigned int value; };
struct decoded_data { unsigned int value; };
struct compressed_data { unsigned int value; };

#include <boost/atomic.hpp>
typedef boost::atomic<unsigned int> atomic_t;

class subsystem1 {
	atomic_t i_;
public:
	subsystem1() :
		i_(0)
	{}

	data_packet get_data() {
		data_packet ret = { ++i_ };
		std::cout << "Get Data : " << ret.value << std::endl;
		return ret;
	}

	static const unsigned int max_runs = 5; // 10 000번 실행

	bool is_stopped() const {
		return i_ == max_runs; // 10 000번 실행
	}
};

#include <cassert>
class subsystem2 {
	atomic_t i_;
public:
	subsystem2() :
		i_(0)
	{}

	void send_data(const compressed_data& data) {
		++i_;
		std::cout << "Send Data : " << i_ << std::endl;
		assert(data.value == i_);
	}

	unsigned int send_packets_count() const {
		return i_;
	}
};

decoded_data decode_data(const data_packet& packet) {
	static unsigned int i = 0;
	++i;
	decoded_data ret = { packet.value };
	std::cout << "Decode Data : " << ret.value << std::endl;
	assert(i == packet.value);
	return ret;
}

compressed_data compress_data(const decoded_data& packet) {
	static unsigned int i = 0;
	++i;
	compressed_data ret = { packet.value };
	std::cout << "Compress Data : " << ret.value << std::endl;
	assert(i == packet.value);
	return ret;
}


// 5장에서 만든 work_queue 클래스
#include <deque>
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/condition_variable.hpp>

class work_queue {
public:
	typedef boost::function<void()> task_type;

private:
	std::deque<task_type>   tasks_;
	boost::mutex            mutex_;
	boost::condition_variable cond_;
	bool                    is_stopped_;

public:
	work_queue()
		: is_stopped_(false)
	{}

	void stop() {
		boost::unique_lock<boost::mutex> lock(mutex_);
		is_stopped_ = true;
		//lock.unlock();
		cond_.notify_all();
	}

	void push_task(const task_type& task) {
		boost::unique_lock<boost::mutex> lock(mutex_);
		if (is_stopped_) {
			return;
		}
		tasks_.push_back(task);
		//lock.unlock();
		cond_.notify_one();
	}

	task_type pop_task() {
		boost::unique_lock<boost::mutex> lock(mutex_);
		while (tasks_.empty()) {
			if (is_stopped_) {
				std::cout << "Thread Stop1 : " << boost::this_thread::get_id() << std::endl;
				return task_type();
			}
			cond_.wait(lock);
		}

		task_type ret = tasks_.front();
		tasks_.pop_front();

		return ret;
	}
};

//#define RUN_BAD_EXAMPLE
#ifdef RUN_BAD_EXAMPLE
// 전역 변수
tasks_queue queue;
subsystem1 subs1;
subsystem2 subs2;

tasks_queue& operator<< (tasks_queue&, data_packet& data) {
	decoded_data d_decoded = decode_data(data);
	compressed_data c_data = compress_data(d_decoded);
	subs2.send_data(c_data);
}

void start_data_accepting() {
	while (!subs1.is_stopped()) {
		queue << subs1.get_data();
	}
}

#include <boost/thread/thread.hpp>
int main() {
	// 첫번째 장치에서 데이터 패킷을 얻어
	// 큐에 넣는다
	boost::thread t(&start_data_accepting);

	// 다중 스레드 환경에서는 어떤 데이터 패킷이 먼저 처리될까?
	// 패킷 1번보다 패킷 2번이 먼저 처리될 수도 있다
	// 도착한 순서대로 패킷이 처리될 거라는 보장은 할 수 없다
	queue.run_multiple();
	t.join();
}

#else

// 전역 변수
work_queue decoding_queue, compressing_queue, sending_queue;
subsystem1 subs1;
subsystem2 subs2;

#include <boost/bind.hpp>
void do_decode(const data_packet& packet);
void start_data_accepting() {
	while (!subs1.is_stopped()) {
		decoding_queue.push_task(boost::bind(
			&do_decode, subs1.get_data()
		));
	}
}

void do_compress(const decoded_data& packet);
void do_decode(const data_packet& packet) {
	compressing_queue.push_task(boost::bind(
		&do_compress, decode_data(packet)
	));
}


void do_compress(const decoded_data& packet) {
	sending_queue.push_task(boost::bind(
		&subsystem2::send_data,
		boost::ref(subs2),
		compress_data(packet)
	));
}

void run_while_not_stopped(work_queue& queue) {
	work_queue::task_type task;
	while (task = queue.pop_task()) {
		task();
	}
	std::cout << "Thread Stop2 : " << boost::this_thread::get_id() << std::endl;
}

#include <boost/thread/thread.hpp>
int main() {
	{
		StopWatch Test("Time");

		// 첫번째 장치에서 데이터 패킷을 얻어 큐에 넣는다
		boost::thread t_data_accepting(&start_data_accepting);
		boost::thread t_data_decoding(boost::bind(
			&run_while_not_stopped, boost::ref(decoding_queue)
		));
		boost::thread t_data_compressing(boost::bind(
			&run_while_not_stopped, boost::ref(compressing_queue)
		));
		boost::thread t_data_sending(boost::bind(
			&run_while_not_stopped, boost::ref(sending_queue)
		));

		t_data_accepting.join();

		decoding_queue.stop();
		std::cout << "Decoding Thread Stop" << std::endl;
		t_data_decoding.join();

		compressing_queue.stop();
		std::cout << "Compressing Thread Stop" << std::endl;
		t_data_compressing.join();

		sending_queue.stop();
		std::cout << "Sending Thread Stop" << std::endl;
		t_data_sending.join();

		assert(subs2.send_packets_count() == subsystem1::max_runs);
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

#endif

