#include "mesh_drawable.hpp"

#include "vcl/base/base.hpp"

namespace vcl
{
	GLuint mesh_drawable::default_shader = 0;
	GLuint mesh_drawable::default_texture = 0;


	mesh_drawable::mesh_drawable()
		:vbo(), vao(0), shader(0), texture(0), transform(), shading()
	{}

	mesh_drawable::mesh_drawable(mesh const& data_to_send, GLuint shader_arg, GLuint texture_arg, GLuint draw_type)
		:vbo(), vao(0), shader(shader_arg), texture(texture_arg), transform(), shading()
	{
		// Sanity check OpenGL
		opengl_check;
		// Sanity check before sending mesh data to GPU
		assert_vcl(mesh_check(data_to_send), "Cannot send this mesh data to GPU");

		// Fill vbo for position
		opengl_create_gl_buffer_data(GL_ARRAY_BUFFER, vbo["position"], data_to_send.position, draw_type);
		opengl_create_gl_buffer_data(GL_ARRAY_BUFFER, vbo["normal"], data_to_send.normal, draw_type);
		opengl_create_gl_buffer_data(GL_ARRAY_BUFFER, vbo["color"], data_to_send.color, draw_type);
		opengl_create_gl_buffer_data(GL_ARRAY_BUFFER, vbo["uv"], data_to_send.uv, draw_type);
		opengl_create_gl_buffer_data(GL_ELEMENT_ARRAY_BUFFER, vbo["index"], data_to_send.connectivity, draw_type);

		// Store number of triangles
		number_triangles = static_cast<GLuint>(data_to_send.connectivity.size());

		// Generate VAO
		glGenVertexArrays(1,&vao); opengl_check
		glBindVertexArray(vao);    opengl_check
		opengl_set_vertex_attribute(vbo["position"], 0, 3, GL_FLOAT);
		opengl_set_vertex_attribute(vbo["normal"],   1, 3, GL_FLOAT);
		opengl_set_vertex_attribute(vbo["color"],    2, 3, GL_FLOAT);
		opengl_set_vertex_attribute(vbo["uv"],       3, 2, GL_FLOAT);
		glBindVertexArray(0);      opengl_check
	}


	mesh_drawable& mesh_drawable::update_position(buffer<vec3> const& new_position)
	{
		glBindBuffer(GL_ARRAY_BUFFER,vbo["position"]); opengl_check;
		glBufferSubData(GL_ARRAY_BUFFER,0,size_in_memory(new_position),ptr(new_position));  opengl_check;
		return *this;
	}
	mesh_drawable& mesh_drawable::update_normal(buffer<vec3> const& new_normals)
	{
		glBindBuffer(GL_ARRAY_BUFFER,vbo["normal"]); opengl_check;
		glBufferSubData(GL_ARRAY_BUFFER,0,size_in_memory(new_normals),ptr(new_normals));  opengl_check;
		return *this;
	}

	void mesh_drawable::clear()
	{
		for(auto& buffer : vbo)
			glDeleteBuffers(1, &(buffer.second) ); 
		vbo.clear();

		glDeleteVertexArrays(1, &vao);
		vao = 0;
		opengl_check;
		
		number_triangles = 0;
		shader = 0;
		texture = 0;
		transform = affine_rts();
		shading = shading_parameters_phong();
	}

}