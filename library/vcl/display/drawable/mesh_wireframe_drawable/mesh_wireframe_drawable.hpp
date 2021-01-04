#pragma once

#include "vcl/display/opengl/opengl.hpp"
#include "vcl/shape/mesh/mesh.hpp"

namespace vcl
{
	struct mesh_wireframe_drawable
	{

		mesh_wireframe_drawable();
		explicit mesh_wireframe_drawable(mesh const& data, GLuint shader=default_shader, GLuint draw_type=GL_DYNAMIC_DRAW);

		GLuint vbo_position;
		GLuint vao;
		GLuint number_edges;
		GLuint shader;

		affine_rts transform;
		vec3 color;
				
		static GLuint default_shader;

		void clear();
		mesh_wireframe_drawable& update(mesh const& data);
	};

}

namespace vcl
{
	template <typename SCENE>
	void draw(mesh_wireframe_drawable const& drawable, SCENE const& scene)
	{
		// Setup shader
		assert_vcl(drawable.shader!=0, "Try to draw mesh_wireframe_drawable without shader");
		glUseProgram(drawable.shader); opengl_check;

		// Send uniforms for this shader
		opengl_uniform(drawable.shader, scene);
		opengl_uniform(drawable.shader, "color", drawable.color);
		opengl_uniform(drawable.shader, "model", drawable.transform.matrix());

		// Call draw function
		assert_vcl(drawable.number_edges>0, "Try to draw mesh_wireframe_drawable with 0 edges"); opengl_check;
		glBindVertexArray(drawable.vao); opengl_check;
		glDrawArrays(GL_LINES, 0, 2*drawable.number_edges); opengl_check;

		// Clean buffers
		glBindVertexArray(0);
	}
}