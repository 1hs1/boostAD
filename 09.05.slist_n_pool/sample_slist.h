#pragma once

#include <boost/pool/pool_alloc.hpp>
#include <boost/container/slist.hpp>

typedef boost::fast_pool_allocator<int> allocator_t;
typedef boost::container::slist<int, allocator_t> slist_t;


void list_specific(slist_t& list, slist_t::iterator it) {
	typedef slist_t::iterator iterator;

	// 요소 776 삭제
	assert(*(++iterator(it)) == 776);
	assert(*it == 777);
	list.erase_after(it);
	assert(*it == 777);
	assert(*(++iterator(it)) == 775);

	// 메모리 풀어주기. fast_pool_allocator는 내부적으로 singleton_pool을 사용함
	boost::singleton_pool<
		boost::pool_allocator_tag,
		sizeof(int)
	>::release_memory();

	// singleton_pool은 
	// 1. 메모리 할당 시 블럭 단위로(기본 32개) 할당하여 쪼개쓰는 방식
	// 2. 이름처럼 한번만 쓰는 메모리 사용 시 쓰임
	// 3. 쓰다가 마지막에 release_memory() 해주면 그 동안 할당한 메모리 clear됨
}
