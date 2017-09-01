#pragma once

#include <boost/pool/pool_alloc.hpp>
#include <boost/container/slist.hpp>

typedef boost::fast_pool_allocator<int> allocator_t;
typedef boost::container::slist<int, allocator_t> slist_t;


void list_specific(slist_t& list, slist_t::iterator it) {
	typedef slist_t::iterator iterator;

	// ��� 776 ����
	assert(*(++iterator(it)) == 776);
	assert(*it == 777);
	list.erase_after(it);
	assert(*it == 777);
	assert(*(++iterator(it)) == 775);

	// �޸� Ǯ���ֱ�. fast_pool_allocator�� ���������� singleton_pool�� �����
	boost::singleton_pool<
		boost::pool_allocator_tag,
		sizeof(int)
	>::release_memory();

	// singleton_pool�� 
	// 1. �޸� �Ҵ� �� �� ������(�⺻ 32��) �Ҵ��Ͽ� �ɰ����� ���
	// 2. �̸�ó�� �ѹ��� ���� �޸� ��� �� ����
	// 3. ���ٰ� �������� release_memory() ���ָ� �� ���� �Ҵ��� �޸� clear��
}
