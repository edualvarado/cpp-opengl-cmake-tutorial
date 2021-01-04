#pragma once

#include <map>
#include <string>
#include "vcl/display/opengl/opengl.hpp"
#include "vcl/shape/mesh/mesh.hpp"
#include "vcl/display/drawable/shading_parameters/shading_parameters.hpp"

namespace vcl
{
	struct mesh_drawable
	{
		mesh_drawable();
		// Send mesh data to GPU and store IDs into vbo. Set also shader and texture.
		explicit mesh_drawable(mesh const& data_to_send, GLuint shader=default_shader, GLuint texture=default_texture, GLuint draw_type=GL_DYNAMIC_DRAW);

		// Stores VBO ID in GPU_elements_id
		std::map<std::string, GLuint> vbo;
		GLuint vao;

		GLuint number_triangles;
		GLuint shader;
		GLuint texture;

		// Uniform
		affine_rts transform;
		shading_parameters_phong shading;
		

		static GLuint default_shader;
		static GLuint default_texture;

		void clear();
		mesh_drawable& update_position(buffer<vec3> const& new_position);
		mesh_drawable& update_normal(buffer<vec3> const& new_normal);
	};

	//void send_data_to_gpu(mesh_drawable& to_fill, mesh const& data_to_send, GLuint draw_type=GL_DYNAMIC_DRAW);

	template <typename SCENE>
	void draw(mesh_drawable const& drawable, SCENE const& scene);

	template <typename SCENE>
	void draw_wireframe(mesh_drawable const& drawable, SCENE const& scene, vec3 const& color={0,0,1});
}


namespace vcl
{
	template <typename SCENE>
	void draw(mesh_drawable const& drawable, SCENE const& scene)
	{
		// Setup shader
		assert_vcl(drawable.shader!=0, "Try to draw mesh_drawable without shader");
		assert_vcl(drawable.texture!=0, "Try to draw mesh_drawable without texture");
		glUseProgram(drawable.shader); opengl_check;

		// Send uniforms for this shader
		opengl_uniform(drawable.shader, scene);
		opengl_uniform(drawable.shader, drawable.shading);
		opengl_uniform(drawable.shader, "model", drawable.transform.matrix());

		// Set texture
		glActiveTexture(GL_TEXTURE0); opengl_check;
		glBindTexture(GL_TEXTURE_2D, drawable.texture); opengl_check;
		opengl_uniform(drawable.shader, "image_texture", 0);  opengl_check;
		
		// Call draw function
		assert_vcl(drawable.number_triangles>0, "Try to draw mesh_drawable with 0 triangles"); opengl_check;
		glBindVertexArray(drawable.vao);   opengl_check;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawable.vbo.at("index")); opengl_check;
		glDrawElements(GL_TRIANGLES, GLsizei(drawable.number_triangles*3), GL_UNSIGNED_INT, nullptr); opengl_check;

		// Clean buffers
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	template <typename SCENE>
	void draw_wireframe(mesh_drawable const& drawable, SCENE const& scene, vec3 const& color)
	{
		mesh_drawable wireframe = drawable;
		wireframe.shading.phong = {1.0f,0.0f,0.0f,64.0f};
		wireframe.shading.color = color;
		wireframe.shading.use_texture = false;
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		glEnable(GL_POLYGON_OFFSET_LINE);
		glPolygonOffset(-1.0, 1.0);
		draw(wireframe, scene);
		glDisable(GL_POLYGON_OFFSET_LINE);
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}
}