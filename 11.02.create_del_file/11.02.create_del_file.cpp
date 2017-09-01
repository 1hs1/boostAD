// 11.02.create_del_file.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <boost/filesystem/operations.hpp>
#include <cassert>
#include <fstream>
#include <iostream>

int main() {
	boost::system::error_code error;

	// ���丮 ����
	boost::filesystem::create_directories("c:/dir/subdir", error);
	assert(!error); // *��� fs ���� �Լ��� error& �� �ѱ�� ��ĺ��� try/catch�� �� ��������*
	system("pause");

	// ���� ����
	std::ofstream ofs("c:/dir/subdir/file.txt");
	ofs << "Boost.Filesystem is fun!";
	assert(ofs);
	ofs.close();
	system("pause");

	// �ɺ��� ��ũ ����
	boost::filesystem::create_directory_symlink("c:/dir/subdir", "symlink", error);
	if (!error) {
		std::cerr << "Symlink created\n";
		assert(boost::filesystem::exists("symlink/file.txt"));
	}
	else {
		std::cerr << "Failed to create a symlink - " << error << "\n";
		boost::filesystem::remove("c:/dir/subdir/file.txt", error);
		assert(!error);
	}
	system("pause");
}
