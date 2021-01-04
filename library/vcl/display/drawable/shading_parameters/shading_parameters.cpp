#include "vcl/base/base.hpp"
#include "vcl/display/opengl/opengl.hpp"

#include "shading_parameters.hpp"



namespace vcl
{
	void opengl_uniform(GLuint shader, shading_parameters_phong const& shading)
	{
		opengl_uniform(shader, "color", shading.color);
		opengl_uniform(shader, "alpha", shading.alpha);
		opengl_uniform(shader, "Ka", shading.phong.ambient);
		opengl_uniform(shader, "Kd", shading.phong.diffuse);
		opengl_uniform(shader, "Ks", shading.phong.specular);
		opengl_uniform(shader, "specular_exp", shading.phong.specular_exponent);
		opengl_uniform(shader, "use_texture", shading.use_texture);
		opengl_uniform(shader, "texture_inverse_y", shading.texture_inverse_y);
	}
}