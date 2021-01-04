#include "shaders_preset.hpp"
#include "vcl/base/base.hpp"


namespace vcl
{
	std::string opengl_shader_preset(std::string const& shader_name)
	{
		if (shader_name == "mesh_vertex") {
			#include "mesh/mesh.vert.glsl"
			return s;
		}
		if (shader_name == "mesh_fragment") {
			#include "mesh/mesh.frag.glsl"
			return s;
		}

		if (shader_name == "single_color_vertex") {
			#include "single_color/single_color.vert.glsl"
			return s;
		}
		if (shader_name == "single_color_fragment") {
			#include "single_color/single_color.frag.glsl"
			return s;
		}

		error_vcl("Shader not found");
		return "Error";
	}
}