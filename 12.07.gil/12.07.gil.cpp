// 12.07.gil.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>

#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>
#include <string>

#include <cassert>

struct negate {
	typedef void result_type; // 필요함

	template <class View>
	void operator()(const View& source) const {

		// 책에 맞추기 위해 코드가 안쪽으로 치우쳐져 있음
		boost::gil::gil_function_requires<
			boost::gil::ImageViewConcept<View>
		>();

		// 채널 데이터형 얻기
		typedef typename View::value_type value_type;
		typedef typename boost::gil::channel_type<value_type>::type channel_t;

		// 픽셀 순환
		const std::size_t channels = boost::gil::num_channels<View>::value;
		const channel_t max_val = (std::numeric_limits<channel_t>::max)();

		for (unsigned int y = 0; y < source.height(); ++y) {
			for (unsigned int x = 0; x < source.width(); ++x) {
				for (unsigned int c = 0; c < channels; ++c) {
					source(x, y)[c] = max_val - source(x, y)[c];
				}
			}
		}


	}
}; // negate 구조체의 끝

int main(int argc, char *argv[]) {
	typedef boost::mpl::vector<
		boost::gil::gray8_image_t,
		//boost::gil::gray16_image_t,
		boost::gil::rgb8_image_t
		//boost::gil::rgb8s_image_t,
		//boost::gil::rgb16_image_t,
		//boost::gil::rgb16s_image_t,
		//boost::gil::rgb32_image_t,
		//boost::gil::rgb32s_image_t,
		//boost::gil::rgba16_image_t,
		//boost::gil::rgba16s_image_t,
		//boost::gil::cmyk16_image_t,
		//boost::gil::cmyk16s_image_t
	> img_types;

	// 이미지 읽어오기
	std::string file_name("giltest.png");
	boost::gil::any_image<img_types> source;		// img_types 중 하나의 이미지를 저장
	boost::gil::png_read_image(file_name, source);	// 파일을 읽어서 source에 저장

	// 이미지 조작
	boost::gil::apply_operation(	// boost::apply_visitor
		view(source),	// 이미지를 픽셀의 이차원 배열로 인식
		negate()
	);

	// 이미지 쓰기
	boost::gil::png_write_view("negate_" + file_name, const_view(source));

	while (1)
	{
		if (_kbhit())
		{
			if (_getch() == 27)	// ESC key
			{
				break;
			}
		}
	}
}

