// 06.10.tasks_processor_signals.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include "./tp/tp_full.h"
using namespace tp_full;

// Signal types
/*
// Ctrl-C
#define SIGINT          2   // interrupt

// 불법 명령어를 실행할때 보내지며, 이 시그널을 받으면 코어 덤프하고 종료
#define SIGILL          4   // illegal instruction - invalid function image

// 0으로 나누기,부동소수점 오류등이 발생했을때 보내지며, 이 시그널을 받으면 코어 덤프하고 종료
#define SIGFPE          8   // floating point exception

// 잘못된 메모리 주소를 접근하고자 할때 보내지며, 이 시그널을 받으면 코어 덤프하고 종료
#define SIGSEGV         11  // segment violation

// 프로세스를 종료시키기 전에 하던 일을 정리하고 종료할 것을 알릴때 보내짐
#define SIGTERM         15  // Software termination signal from kill

// Ctrl-Break
#define SIGBREAK        21  // Ctrl-Break sequence

// abort함수를 호출하면 보내지며, 이 시그널을 받으면 코어 덤프하고 종료
#define SIGABRT         22  // abnormal termination triggered by abort call
*/


void accept_3_signals_and_stop(int signal) {
	static int signals_count = 0;
	assert(signal == SIGINT || signal == SIGBREAK);
	++signals_count;
	std::cout << "Captured " << signals_count << " SIGINT\n";
	if (signals_count == 3) {
		tasks_processor::get().stop();
	}
}


int main() {
	tasks_processor::get().register_signals_handler(
		&accept_3_signals_and_stop,
		std::vector<int>{SIGINT, SIGBREAK} // 단 한 개의 요소만 갖는 벡터
	);

	tasks_processor::get().start();

}
