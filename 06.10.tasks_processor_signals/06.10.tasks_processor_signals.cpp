// 06.10.tasks_processor_signals.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include "./tp/tp_full.h"
using namespace tp_full;

// Signal types
/*
// Ctrl-C
#define SIGINT          2   // interrupt

// �ҹ� ��ɾ �����Ҷ� ��������, �� �ñ׳��� ������ �ھ� �����ϰ� ����
#define SIGILL          4   // illegal instruction - invalid function image

// 0���� ������,�ε��Ҽ��� �������� �߻������� ��������, �� �ñ׳��� ������ �ھ� �����ϰ� ����
#define SIGFPE          8   // floating point exception

// �߸��� �޸� �ּҸ� �����ϰ��� �Ҷ� ��������, �� �ñ׳��� ������ �ھ� �����ϰ� ����
#define SIGSEGV         11  // segment violation

// ���μ����� �����Ű�� ���� �ϴ� ���� �����ϰ� ������ ���� �˸��� ������
#define SIGTERM         15  // Software termination signal from kill

// Ctrl-Break
#define SIGBREAK        21  // Ctrl-Break sequence

// abort�Լ��� ȣ���ϸ� ��������, �� �ñ׳��� ������ �ھ� �����ϰ� ����
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
		std::vector<int>{SIGINT, SIGBREAK} // �� �� ���� ��Ҹ� ���� ����
	);

	tasks_processor::get().start();

}
