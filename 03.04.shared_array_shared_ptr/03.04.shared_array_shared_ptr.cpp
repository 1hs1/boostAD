// 03.04.shared_array_shared_ptr.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <cstring>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

void do_process(const char* data, std::size_t size);

void do_process_in_background(const char* data, std::size_t size) {
	// 호출자가 언제 데이터를 할당 해지할 지 알 수 없으므로
	// 데이터를 복사해야한다
	char* data_cpy = new char[size];
	std::memcpy(data_cpy, data, size);

	// 데이터를 처리하기 위해 스레드를 시작한다
	boost::thread(boost::bind(&do_process, data_cpy, size));

	// do_process1나 do_process2가 data_cpy를 처리하고 있을 지도 모르므로
	// delete[] data_cpy를 쓸 수 없다	
}

#include <boost/shared_array.hpp>
void do_process_shared_array(const boost::shared_array<char>& data, std::size_t size) {
	do_process(data.get(), size);
}

void do_process_in_background_v1(const char* data, std::size_t size) {
	// 호출자가 언제 데이터를 할당 해지할 지 알 수 없으므로
	// 데이터를 복사해야 한다
	boost::shared_array<char> data_cpy(new char[size]);
	std::memcpy(data_cpy.get(), data, size);

	// 데이터를 처리하기 위해 스레드를 시작한다
	boost::thread(boost::bind(&do_process_shared_array, data_cpy, size))
		.detach();

	// 참조 횟수가 0이 될 경우 data_cpy 소멸자가 알아서 데이터를 해제시키기 때문에 
	// data_cpy에 대해 delete[]를 부를 필요가 없다
}


#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

void do_process_shared_ptr(
	const boost::shared_ptr<char[]>& data,
	std::size_t size)
{
	do_process(data.get(), size);
}

void do_process_in_background_v2(const char* data, std::size_t size) {
	// '첫번째 방법'보다 빠르다
	boost::shared_ptr<char[]> data_cpy = boost::make_shared<char[]>(size);
	std::memcpy(data_cpy.get(), data, size);

	// 데이터를 처리하기 위해 스레드를 시작한다
	boost::thread(boost::bind(&do_process_shared_ptr, data_cpy, size))
		.detach();

	// 참조 횟수가 0이 될 경우 
	// data_cpy 소멸자가 알아서 데이터를 해제
}

void do_process_shared_ptr2(
	const boost::shared_ptr<char>& data,
	std::size_t size)
{
	do_process(data.get(), size);
}

void do_process_in_background_v3(const char* data, std::size_t size) {
	// 첫번째 방법과 속도가 같음
	boost::shared_ptr<char> data_cpy(
		new char[size],
		boost::checked_array_deleter<char>()
	);
	std::memcpy(data_cpy.get(), data, size);

	// 데이터를 처리하기 위해 스레드를 시작한다
	boost::thread(boost::bind(&do_process_shared_ptr2, data_cpy, size))
		.detach();

	// 참조 횟수가 0이 될 경우 
	// data_cpy 소멸자가 알아서 데이터를 해제
}

#include <boost/chrono/duration.hpp>
int main() {
	char ch[] = "Hello dear reader.";
	//do_process_in_background(ch, sizeof(ch)); // 메모리 누수가 일어날 수 있다
	do_process_in_background_v1(ch, sizeof(ch));
	do_process_in_background_v2(ch, sizeof(ch));
	do_process_in_background_v3(ch, sizeof(ch));

	// 모든 스레드에게 끝낼 기회가 부여된다
	// 주의: 정말 끔직한 디자인이지만, 예제니까 써본 것이다
	boost::this_thread::sleep_for(boost::chrono::seconds(2));
	return 0;
}

void do_process(const char* data, std::size_t size) {
	assert(size);
	assert(data);
}
