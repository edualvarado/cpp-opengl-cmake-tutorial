#pragma once

#include "vcl/containers/containers.hpp"
#include "vcl/display/drawable/curve_drawable/curve_drawable.hpp"

namespace vcl
{
	struct trajectory_drawable
	{
		trajectory_drawable(size_t N_max_sample = 100);
		void clear();
		void add(vec3 const& position, float time);


		buffer<vec3> position_record;
		buffer<float> time_record;
		curve_drawable visual;
		size_t N_max_sample;
		size_t current_size;

	};

	template <typename SCENE>
	void draw(trajectory_drawable const& trajectory, SCENE const& scene)
	{
		if(trajectory.current_size>0){
			// Setup shader
			assert_vcl(trajectory.visual.shader!=0, "Try to draw curve_drawable without shader");
			glUseProgram(trajectory.visual.shader); opengl_check;

			// Send uniforms for this shader
			opengl_uniform(trajectory.visual.shader, scene);
			opengl_uniform(trajectory.visual.shader, "color", trajectory.visual.color);
			opengl_uniform(trajectory.visual.shader, "model", trajectory.visual.transform.matrix());

			// Call draw function
		
			glBindVertexArray(trajectory.visual.vao); opengl_check;
			glDrawArrays(GL_LINE_STRIP, 0, GLsizei(trajectory.current_size) ); opengl_check;

			// Clean buffers
			glBindVertexArray(0);
		}
	}
}