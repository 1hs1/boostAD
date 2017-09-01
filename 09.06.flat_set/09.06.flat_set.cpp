// 09.06.flat_set.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <boost/container/flat_set.hpp>

#include <algorithm>
#include <iostream>
#include <string>

#include "test_flat.h"
#include "test_custom.h"

int main()
{
	test_flat();
	test_custom();

	// flat_set 장정
	// 1. 요소당 소요 메모리 3분의 1
	// 2. 랜덤 access 가능
	// 3. 요소간 거리 구할 시 빠름
	// 4. 검색, 반복 빠름

	// flat_set 단점
	// 1. 삽입,삭제시 정렬이 필요하기 때문에 느림 (선형시간)

    return 0;
}
