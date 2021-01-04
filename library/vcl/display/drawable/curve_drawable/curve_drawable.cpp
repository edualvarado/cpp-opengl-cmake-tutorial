#include "vcl/base/base.hpp"
#include "curve_drawable.hpp"

namespace vcl
{
	GLuint curve_drawable::default_shader = 0;

	curve_drawable::curve_drawable()
		:vbo_position(0), vao(0), number_position(0), shader(0), transform(), color({0,0,0})
	{}

	curve_drawable::curve_drawable(buffer<vec3> const& position, GLuint shader, GLuint draw_type)
		:vbo_position(0), vao(0), number_position(0), shader(shader), transform(), color()
	{
		opengl_create_gl_buffer_data(GL_ARRAY_BUFFER, vbo_position, position, draw_type);
		number_position = static_cast<GLuint>(position.size());

		glGenVertexArrays(1,&vao); opengl_check
		glBindVertexArray(vao);    opengl_check
		opengl_set_vertex_attribute(vbo_position, 0, 3, GL_FLOAT);
		glBindVertexArray(0);      opengl_check
	}
	void curve_drawable::update(buffer<vec3> const& new_position)
	{
		opengl_update_gl_subbuffer_data(vbo_position, new_position);
	}

	void curve_drawable::clear()
	{
		glDeleteBuffers(1, &vbo_position ); 
		vbo_position = 0;

		glDeleteVertexArrays(1, &vao);
		vao = 0;
		opengl_check;
		
		number_position = 0;
		shader = 0;
		transform = affine_rts();
		color = {0,0,0};
	}

}