#pragma once

#include "../glad/glad.hpp"
#include <string>


#define opengl_check {vcl::check_opengl_error(__FILE__, __func__, __LINE__);}

namespace vcl
{
	std::string opengl_info_display();
	void check_opengl_error(const std::string& file, const std::string& function, int line);
}

