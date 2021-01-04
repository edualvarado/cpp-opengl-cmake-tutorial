#pragma once

#include "vcl/display/opengl/opengl.hpp"
#include "vcl/shape/mesh/mesh.hpp"

namespace vcl
{
	struct mesh_normal_drawable
	{
		mesh_normal_drawable();
		explicit mesh_normal_drawable(mesh const& data, float normal_length=0.1f, GLuint shader=default_shader, GLuint draw_type=GL_DYNAMIC_DRAW);

		std::map<std::string, GLuint> gpu_elements_id;
		GLuint number_normals;
		GLuint shader;

		affine_rts transform;
		vec3 color;


		static GLuint default_shader;
	};

}

namespace vcl
{
	template <typename SCENE>
	void draw(mesh_normal_drawable const& drawable, SCENE const& scene)
	{
		// Setup shader
		assert_vcl(drawable.shader!=0, "Try to draw mesh_wireframe_drawable without shader");
		glUseProgram(drawable.shader); opengl_check;

		// Send uniforms for this shader
		opengl_uniform(drawable.shader, scene);
		opengl_uniform(drawable.shader, "color", drawable.color);
		opengl_uniform(drawable.shader, "model", drawable.transform.matrix());

		// Call draw function
		assert_vcl(drawable.number_normals>0, "Try to draw mesh_wireframe_drawable with 0 edges"); opengl_check;
		glBindVertexArray(drawable.gpu_elements_id.at("vao")); opengl_check;
		glDrawArrays(GL_LINES, 0, 2*drawable.number_normals); opengl_check;

		// Clean buffers
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}