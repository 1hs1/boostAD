// 12.07.gil.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>

#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>
#include <string>

#include <cassert>

struct negate {
	typedef void result_type; // �ʿ���

	template <class View>
	void operator()(const View& source) const {

		// å�� ���߱� ���� �ڵ尡 �������� ġ������ ����
		boost::gil::gil_function_requires<
			boost::gil::ImageViewConcept<View>
		>();

		// ä�� �������� ���
		typedef typename View::value_type value_type;
		typedef typename boost::gil::channel_type<value_type>::type channel_t;

		// �ȼ� ��ȯ
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
}; // negate ����ü�� ��

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

	// �̹��� �о����
	std::string file_name("giltest.png");
	boost::gil::any_image<img_types> source;		// img_types �� �ϳ��� �̹����� ����
	boost::gil::png_read_image(file_name, source);	// ������ �о source�� ����

	// �̹��� ����
	boost::gil::apply_operation(	// boost::apply_visitor
		view(source),	// �̹����� �ȼ��� ������ �迭�� �ν�
		negate()
	);

	// �̹��� ����
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

