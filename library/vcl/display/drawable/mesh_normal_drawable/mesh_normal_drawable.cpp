#include "mesh_normal_drawable.hpp"

namespace vcl
{
	GLuint mesh_normal_drawable::default_shader=0;


	mesh_normal_drawable::mesh_normal_drawable()
		:gpu_elements_id(), number_normals(0), shader(0), transform(), color(vec3{1.0f,0.0f,0.0f})
	{}

	mesh_normal_drawable::mesh_normal_drawable(mesh const& data, float normal_length, GLuint shader_arg, GLuint draw_type)
	{

		buffer<vec3> lines;

		size_t const N = data.position.size();
		for (size_t k = 0; k < N; ++k)
		{
			vec3 const& p = data.position[k];
			vec3 const& n = data.normal[k];

			lines.push_back(p).push_back(p+normal_length*n);
		}

		shader = shader_arg;

		// Fill vbo for position
		opengl_create_gl_buffer_data(GL_ARRAY_BUFFER, gpu_elements_id["vbo_position"], lines, draw_type);
		number_normals = static_cast<GLuint>(data.normal.size());

		// Generate VAO
		GLuint& vao = gpu_elements_id["vao"];
		glGenVertexArrays(1,&vao); opengl_check
		glBindVertexArray(vao);    opengl_check
		opengl_set_vertex_attribute(gpu_elements_id["vbo_position"], 0, 3, GL_FLOAT);
		glBindVertexArray(0);      opengl_check

	}
}