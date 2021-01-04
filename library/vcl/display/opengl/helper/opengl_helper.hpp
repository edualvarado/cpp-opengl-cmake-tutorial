#pragma once

#include "../glad/glad.hpp"
#include "vcl/display/opengl/debug/debug.hpp"

namespace vcl
{
	template <typename T>
	void opengl_create_gl_buffer_data(GLuint buffer_type, GLuint& vbo, T const& element, GLenum draw_type = GL_DYNAMIC_DRAW);

	template <typename T>
	void opengl_update_gl_subbuffer_data(GLuint vbo, T const& element);

	template <typename T>
	void opengl_create_array_buffer_data(GLuint& vbo, T const& element, GLenum draw_type = GL_DYNAMIC_DRAW);

	void opengl_set_vertex_attribute(GLuint vbo, GLuint index, GLuint size, GLenum type);
}


namespace vcl
{
	template <typename T>
	void opengl_create_gl_buffer_data(GLuint buffer_type, GLuint& vbo, T const& element, GLenum draw_type)
	{
		glGenBuffers(1, &vbo);                                                       opengl_check
		glBindBuffer(buffer_type, vbo);                                              opengl_check
		glBufferData(buffer_type, GLsizeiptr(size_in_memory(element)), ptr(element), draw_type); opengl_check
		glBindBuffer(buffer_type, 0);                                                opengl_check
	}


	template <typename T>
	void opengl_create_array_buffer_data(GLuint& vbo, T const& element, GLenum draw_type)
	{
		opengl_create_gl_buffer_data(GL_ARRAY_BUFFER, vbo, element, draw_type);
	}

	template <typename T>
	void opengl_update_gl_subbuffer_data(GLuint vbo, T const& element)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);                                        opengl_check;
		glBufferSubData(GL_ARRAY_BUFFER, 0, size_in_memory(element), ptr(element));  opengl_check;
	}
}