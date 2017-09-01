#pragma once

#include <list>


typedef std::list<int> stdlist_t;
void list_specific(stdlist_t& list, stdlist_t::iterator it) {
	typedef stdlist_t::iterator iterator;

	// 요소 776 삭제
	++it;
	assert(*it == 776);
	it = list.erase(it);
	assert(*it == 775);
}
