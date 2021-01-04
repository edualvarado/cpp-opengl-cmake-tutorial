#pragma once

#include "vcl/containers/containers.hpp"

namespace vcl
{
	enum class image_color_type {rgb, rgba};
	struct image_raw
	{
		image_raw();
		image_raw(unsigned int width_arg, unsigned int height_arg, image_color_type color_type_arg, buffer<unsigned char> const& data_arg);

		unsigned int width;
		unsigned int height;
		image_color_type color_type;
		buffer<unsigned char> data;
	};

	image_raw image_load_png(const std::string& filename, image_color_type color_type = image_color_type::rgba);
	void image_save_png(const std::string& filename, const image_raw& im);

	void convert(image_raw const& in, grid_2D<vec3>& out);

}