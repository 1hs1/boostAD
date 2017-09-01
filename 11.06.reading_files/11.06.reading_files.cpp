// 11.06.reading_files.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <fstream>
#include <cassert>

#include<chrono>
#include<boost/noncopyable.hpp>

class ElapsedTime : private boost::noncopyable
{
public:
	ElapsedTime()
	{
		m_nStart = std::chrono::system_clock::now();
	}

	~ElapsedTime()
	{
		m_nEnd = std::chrono::system_clock::now();
		std::cout << std::endl;
		std::cout << "elapsed time : " << std::chrono::duration<double>(m_nEnd - m_nStart).count() << "ms" << std::endl;
	}

private:
	//double m_nStart_Time = static_cast<double>(time(NULL));
	std::chrono::system_clock::time_point m_nStart;
	std::chrono::system_clock::time_point m_nEnd;
};

int main(int argc, char* argv[]) {
	static const std::size_t filesize = 1024 * 1024 * 128;
	const char filename[] = "test_file.txt";

	int cmd = 0;
	while (([&cmd]() { std::cout << "Exit[0] InputNum : "; std::cin >> cmd; return (0 != cmd); })())
	{
		switch (cmd) {
		case 1:
		{
			// 파일 쓰기
			std::ofstream f(filename, std::ofstream::binary);
			std::fill_n(
				std::ostream_iterator<char>(f),
				filesize - 1,
				'\3'
			);

			f << '\1';
		}
		break;
		case 2:
		{
			ElapsedTime etime;
			std::cout << "mapped_region:";
			const boost::interprocess::mode_t mode = boost::interprocess::read_only;
			boost::interprocess::file_mapping fm(filename, mode);	// 전체파일을 한꺼번에 맵핑
			boost::interprocess::mapped_region region(fm, mode, 0, 0);
			//region.advise(boost::interprocess::mapped_region::advice_sequential);

			const char* begin = reinterpret_cast<const char*>(region.get_address());
			const char* pos = std::find(begin, begin + region.get_size(), '\1');
			assert(pos == begin + filesize - 1);
			assert(region.get_size() == filesize);
		}
		break;
		case 3:
		{
			ElapsedTime etime;
			std::cout << "ifstream:";
			static const std::size_t kilobyte = 1024;			// 블럭단위(최적화)
			std::ifstream f(filename, std::ifstream::binary);	// 이진모드(최적화)
			char c[kilobyte];
			char* begin = c;
			char* end = c + sizeof(c);
			char* pos;

			size_t i = 0;
			for (; i < filesize / kilobyte; ++i) {
				f.read(c, kilobyte);
				pos = std::find(begin, end, '\1');
				if (pos != end)
					break;
			}

			assert(pos - begin == kilobyte - 1);
			assert(i == filesize / kilobyte - 1);
		}
		break;
		case 4:
		{
			ElapsedTime etime;
			std::cout << "C:";
			static const std::size_t kilobyte = 1024;
			FILE* f;
			fopen_s(&f, filename, "rb");
			char c[kilobyte];
			char* begin = c;
			char* end = c + sizeof(c);
			char* pos;

			size_t i = 0;
			for (; i < filesize / kilobyte; ++i) {
				std::size_t res = fread(c, 1, kilobyte, f);
				pos = std::find(begin, end, '\1');
				if (pos != end)
					break;
				(void)res;
			}

			assert(pos - begin == kilobyte - 1);
			assert(i == filesize / kilobyte - 1);
			fclose(f);
		}
		break;
		default: break;
		}

		std::cout << '\n';
	}
}

