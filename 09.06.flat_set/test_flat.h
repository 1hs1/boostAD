#pragma once

void test_flat() {
	// flat_set = 정렬되는 vector
	boost::container::flat_set<int> set;
	set.reserve(4096);

	// 추가할 때 정렬이 됨
	for (int i = 0; i < 4000; ++i) {
		set.insert(i);
	}

	// iter@500 - iter@100 의 거리는 400
	// 일차원 집합(상수 시간)이기 때문에 거리 구하는 게 훨씬 빠름 (set은 선형 시간 iter->iter->iter->...)
	assert(set.lower_bound(500) - set.lower_bound(100) == 400);

	// 0을 삭제
	set.erase(0);

	// 5000(없는 값)을 삭제
	set.erase(5000);

	// 900000(없는 값) 찾기
	assert(std::lower_bound(set.cbegin(), set.cend(), 900000) == set.cend());

	// iter@100 을 400 이동시키면 iter@500
	assert(
		set.lower_bound(100) + 400
		==
		set.find(500)
	);
}

