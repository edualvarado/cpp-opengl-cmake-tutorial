#include "opengl_helper.hpp"

namespace vcl
{
	void opengl_set_vertex_attribute(GLuint vbo, GLuint index, GLuint size, GLenum type)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);                                   opengl_check
		glEnableVertexAttribArray( index );                                   opengl_check
		glVertexAttribPointer(index, size, type, GL_FALSE, 0, nullptr);       opengl_check
		glBindBuffer(GL_ARRAY_BUFFER, 0);                                     opengl_check
	}
}