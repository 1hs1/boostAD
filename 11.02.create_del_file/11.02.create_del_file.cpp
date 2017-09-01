// 11.02.create_del_file.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <boost/filesystem/operations.hpp>
#include <cassert>
#include <fstream>
#include <iostream>

int main() {
	boost::system::error_code error;

	// 디렉토리 생성
	boost::filesystem::create_directories("c:/dir/subdir", error);
	assert(!error); // *모든 fs 관련 함수는 error& 를 넘기는 방식보다 try/catch가 더 안정적임*
	system("pause");

	// 파일 생성
	std::ofstream ofs("c:/dir/subdir/file.txt");
	ofs << "Boost.Filesystem is fun!";
	assert(ofs);
	ofs.close();
	system("pause");

	// 심볼릭 링크 생성
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
