#include "mesh_wireframe_drawable.hpp"

namespace vcl
{
	GLuint mesh_wireframe_drawable::default_shader=0;

	mesh_wireframe_drawable::mesh_wireframe_drawable()
		:vbo_position(0), vao(0), number_edges(0), shader(0), transform(), color(vec3{1.0f,0.0f,0.0f})
	{}

	mesh_wireframe_drawable::mesh_wireframe_drawable(mesh const& data, GLuint shader_arg, GLuint draw_type)
	{
		buffer<vec3> edges;

		size_t const N_tri = data.connectivity.size();
		for (size_t k_tri = 0; k_tri < N_tri; ++k_tri)
		{
			auto const& tri = data.connectivity[k_tri];
			vec3 const& p0 = data.position[get<0>(tri)];
			vec3 const& p1 = data.position[get<1>(tri)];
			vec3 const& p2 = data.position[get<2>(tri)];

			edges.push_back(p0).push_back(p1);
			edges.push_back(p1).push_back(p2);
			edges.push_back(p2).push_back(p0);
		}

		shader = shader_arg;

		// Fill vbo for position
		opengl_create_gl_buffer_data(GL_ARRAY_BUFFER, vbo_position, edges, draw_type);

		// Store number of triangles
		number_edges = static_cast<GLuint>(3*N_tri);

		// Generate VAO
		glGenVertexArrays(1,&vao); opengl_check
		glBindVertexArray(vao);    opengl_check
		opengl_set_vertex_attribute(vbo_position, 0, 3, GL_FLOAT);
		glBindVertexArray(0);      opengl_check

	}

	mesh_wireframe_drawable& mesh_wireframe_drawable::update(mesh const& data)
	{
		buffer<vec3> edges;

		size_t const N_tri = data.connectivity.size();
		for (size_t k_tri = 0; k_tri < N_tri; ++k_tri)
		{
			auto const& tri = data.connectivity[k_tri];
			vec3 const& p0 = data.position[get<0>(tri)];
			vec3 const& p1 = data.position[get<1>(tri)];
			vec3 const& p2 = data.position[get<2>(tri)];

			edges.push_back(p0).push_back(p1);
			edges.push_back(p1).push_back(p2);
			edges.push_back(p2).push_back(p0);
		}

		opengl_update_gl_subbuffer_data(vbo_position, edges);
		return *this;
	}

	void mesh_wireframe_drawable::clear()
	{
		glDeleteBuffers(1, &vbo_position); vbo_position = 0; opengl_check;
		glDeleteVertexArrays(1, &vao); vao=0;  opengl_check;
		number_edges = 0;
		shader = 0;
		transform = affine_rts();
	}
}