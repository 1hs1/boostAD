#pragma once

#include <boost/coroutine/coroutine.hpp>
#include <boost/thread.hpp>
#include <boost/tuple/tuple.hpp>

typedef boost::coroutines::coroutine<
	boost::tuple<bool, std::size_t>
> corout_test;

class Ctest_unit
{
public:
	Ctest_unit();
	~Ctest_unit();

	void Init();
	static void coroutine_sub(corout_test::pull_type& caller);

private:
	

	static void coroutine_task();
	
};
