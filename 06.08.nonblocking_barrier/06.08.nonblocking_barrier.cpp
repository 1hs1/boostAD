// 06.08.nonblocking_barrier.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
		uint64_t ElapsedTime = (NowFreq.QuadPart - m_StartFreq.QuadPart) / (m_FreqPerSecond.QuadPart / 1000000);	// ����ũ����
		std::cout << "[STOPWATCH] Function : " << m_Function.c_str() << " ElapsedTime : " << static_cast<float>(ElapsedTime / 1000000.f) << std::endl;
	}

private:
	std::string m_Function;

	// �ʴ� ī��Ʈ ��
	LARGE_INTEGER m_FreqPerSecond;

	// ���� ī��Ʈ ��
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
		// �庮 �ʱ�ȭ
		boost::barrier data_barrier(data_t::static_size);

		// ������ �ʱ�ȭ
		data_t data;

		// 4���� ������� ����
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


	// �ȶ��� ����
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
			// 1000�� �ݺ������Ƿ� ������
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
	// ī���� �ʱ�ȭ
	atomic_count_t counter(0);

	// ������ �ʱ�ȭ    
	data_t data;

	// 4���� ������� ����
	tasks_processor& tp = tasks_processor::get();

	boost::thread_group tg;
	for (std::size_t i = 0; i < data_t::static_size; ++i) {
		tg.create_thread(boost::bind(&boost::asio::io_service::run, &tp.ios()));
	}

	for (std::size_t i = 0; i < data_t::static_size; ++i) {
		tp.push_task(boost::bind(
			&clever_runner,
			i,
			0, // ù��° ����
			boost::ref(counter),
			boost::ref(data)
		));
	}

	tp.start();
}


// �Լ� ����

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
