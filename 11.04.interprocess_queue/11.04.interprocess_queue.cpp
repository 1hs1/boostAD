// 11.04.interprocess_queue.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>

#include <boost/interprocess/managed_shared_memory.hpp>

#include <boost/interprocess/containers/deque.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

#include <boost/optional.hpp>

// 5장 work_queue와 비교하여 std::function을 사용하지 않음.
// 이 클래스에서 포인터를 저장하는데, 공유메모리에서 잘 동작하지 않음.
struct task_structure {
	// ...
	std::size_t value_;
};

class work_queue {
public:
	// 사용자 정의 클래스
	typedef task_structure task_type;

	// 공유메모리 사용
	typedef boost::interprocess::managed_shared_memory
		managed_shared_memory_t;

	// boost::interprocess의 모든 컨테이너가 요소를 할당할 때 써야하는 할당자
	typedef boost::interprocess::allocator<
		task_type,
		managed_shared_memory_t::segment_manager
	> allocator_t;

private:
	managed_shared_memory_t segment_;
	const allocator_t allocator_;

	// workqueue
	typedef boost::interprocess::deque<task_type, allocator_t>
		deque_t;

	typedef boost::interprocess::interprocess_mutex mutex_t;
	typedef boost::interprocess::interprocess_condition
		condition_t;
	typedef boost::interprocess::scoped_lock<mutex_t>
		scoped_lock_t;

	// 객체들이 공유메모리에서 생성됐기 때문에 참조자만 저장.
	deque_t& tasks_;
	mutex_t& mutex_;
	condition_t& cond_;

public:
	explicit work_queue()
		: segment_(
			boost::interprocess::open_or_create,
			"work-queue",
			1024 * 1024 * 64
		)
		, allocator_(segment_.get_segment_manager())
		, tasks_(
			*segment_.find_or_construct<deque_t>
			("work-queue:deque")(allocator_)
		)
		, mutex_(
			*segment_.find_or_construct<mutex_t>
			("work-queue:mutex")()
		)
		, cond_(
			*segment_.find_or_construct<condition_t>
			("work-queue:condition")()
		)
	{
		//mutex_.unlock();
	}

	void del_share_memory()
	{
		segment_.deallocate("work-queue");
	}

	void push_task(const task_type& task) {
		scoped_lock_t lock(mutex_);
		tasks_.push_back(task);
		std::cout << "push_task : " << task.value_ << std::endl;
		lock.unlock();
		cond_.notify_one();
	}

	// 값을 리턴하는 함수에서 유효하지 않은 값을 리턴하기 위해서 enum 또는 define을 사용해
	// 유효하지 않은 값을 정의해야 하는데, 이게 비효율적으로 늘어나고 코딩하기 귀찮고 관리하기도 힘들기 때문에
	// 아주 간단하게 유효하지 않은 값을 리턴할 수 있도록 만듬(boost::optional)
	boost::optional<task_type> try_pop_task() {
		boost::optional<task_type> ret;
		scoped_lock_t lock(mutex_);
		if (!tasks_.empty()) {
			ret = tasks_.front();
			tasks_.pop_front();
		}

		//std::cout << "try_pop_task" << std::endl;
		//if (ret)
		//{
		//	std::cout << "try_pop_task : " << ret->value_ << std::endl;
		//}
		return ret;
	}

	task_type pop_task() {
		scoped_lock_t lock(mutex_);
		while (tasks_.empty()) {
			cond_.wait(lock);
		}

		task_type ret = tasks_.front();
		tasks_.pop_front();

		std::cout << "pop_task : " << ret.value_ << std::endl;

		return ret;
	}
};


int main() {
	try {
		static const std::size_t max_tasks_count = 30000;
		work_queue queue;
		//queue.del_share_memory();

		boost::optional<task_structure> task = queue.try_pop_task();
		if (!task) {
			std::cout << "Filling data" << std::endl;
			task_structure ts;
			for (std::size_t i = 0; i < max_tasks_count; ++i) {
				ts.value_ = i;
				queue.push_task(ts);
			}
		}
		else {
			std::cout << "Gettinging data" << std::endl;
			assert(task->value_ == 0);
			for (std::size_t i = 1; i < max_tasks_count; ++i) {
				assert(queue.pop_task().value_ == i);
			}

			assert(!queue.try_pop_task());
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
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

