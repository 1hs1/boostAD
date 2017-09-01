// 06.08.nonblocking_barrier.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "./tp/tp_base.h"
using namespace tp_base;

#include <cstddef>
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

static const std::size_t data_length = 10000;

#include <boost/array.hpp>
struct vector_type : public boost::array<std::size_t, data_length> {
	void* alignment;
};

typedef boost::array<vector_type, 4> data_t;

void fill_data(vector_type& data);
void compute_send_data(data_t& data);

#include <boost/thread/barrier.hpp>
void runner(std::size_t thread_index, boost::barrier& data_barrier, data_t& data) {
	for (std::size_t i = 0; i < 1000; ++i) {
		fill_data(data.at(thread_index));
		data_barrier.wait();

		if (!thread_index) {
			compute_send_data(data);
		}
		data_barrier.wait();
	}
}

void clever_implementation();

#include <boost/thread/thread.hpp>
int main() {
	{
		StopWatch a("a");
		// 장벽 초기화
		boost::barrier data_barrier(data_t::static_size);

		// 데이터 초기화
		data_t data;

		// 4개의 스레드로 실행
		boost::thread_group tg;
		for (std::size_t i = 0; i < data_t::static_size; ++i) {
			tg.create_thread(boost::bind(
				&runner,
				i,
				boost::ref(data_barrier),
				boost::ref(data)
			));
		}

		tg.join_all();
	}


	// 똑똑한 구현
	{
		StopWatch b("b");
		clever_implementation();
	}
}



#include <boost/atomic.hpp>
typedef boost::atomic<unsigned int> atomic_count_t;

void clever_runner(
	std::size_t thread_index,
	std::size_t iteration,
	atomic_count_t& counter,
	data_t& data)
{
	fill_data(data.at(thread_index));

	if (++counter == data_t::static_size) {
		compute_send_data(data);

		++iteration;
		if (iteration == 1000) {
			// 1000번 반복했으므로 끝낸다
			tasks_processor::get().stop();
			return;
		}

		counter = 0;
		for (std::size_t i = 0; i < data_t::static_size; ++i) {
			tasks_processor::get().push_task(boost::bind(
				clever_runner,
				i,
				iteration,
				boost::ref(counter),
				boost::ref(data)
			));
		}
	}
}

void clever_implementation() {
	// 카운터 초기화
	atomic_count_t counter(0);

	// 데이터 초기화    
	data_t data;

	// 4개의 스레드로 실행
	tasks_processor& tp = tasks_processor::get();

	boost::thread_group tg;
	for (std::size_t i = 0; i < data_t::static_size; ++i) {
		tg.create_thread(boost::bind(&boost::asio::io_service::run, &tp.ios()));
	}

	for (std::size_t i = 0; i < data_t::static_size; ++i) {
		tp.push_task(boost::bind(
			&clever_runner,
			i,
			0, // 첫번째 실행
			boost::ref(counter),
			boost::ref(data)
		));
	}

	tp.start();
}


// 함수 구현

void fill_data(vector_type& data) {
	for (std::size_t i = 0; i < vector_type::static_size; ++i) {
		data[i] = i;
		data.alignment = 0;
	}
}

void compute_send_data(data_t& data) {
	for (std::size_t i = 0; i < vector_type::static_size; ++i) {
		for (std::size_t j = 0; j < data_t::static_size; ++j) {
			assert(data[j][i] == i);
			data[0][i] *= data[j][i];
		}
	}
}
