#pragma once

#include "../glad/glad.hpp"

#include <string>

namespace vcl
{
	/** Create a shader program from a vertex and fragment shader string */
	GLuint opengl_create_shader_program(std::string const& vertex_shader, std::string const& fragment_shader);
}