#pragma once

void test_flat() {
	// flat_set = ���ĵǴ� vector
	boost::container::flat_set<int> set;
	set.reserve(4096);

	// �߰��� �� ������ ��
	for (int i = 0; i < 4000; ++i) {
		set.insert(i);
	}

	// iter@500 - iter@100 �� �Ÿ��� 400
	// ������ ����(��� �ð�)�̱� ������ �Ÿ� ���ϴ� �� �ξ� ���� (set�� ���� �ð� iter->iter->iter->...)
	assert(set.lower_bound(500) - set.lower_bound(100) == 400);

	// 0�� ����
	set.erase(0);

	// 5000(���� ��)�� ����
	set.erase(5000);

	// 900000(���� ��) ã��
	assert(std::lower_bound(set.cbegin(), set.cend(), 900000) == set.cend());

	// iter@100 �� 400 �̵���Ű�� iter@500
	assert(
		set.lower_bound(100) + 400
		==
		set.find(500)
	);
}

