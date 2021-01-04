#include "common_functions.hpp"

namespace vcl
{
	vec3 translation_in_plane(vec2 const& translation, rotation const& plane_orientation)
	{
		return plane_orientation * vec3(translation, 0.0f);
	}

	vec3 trackball_projection(float x, float y, float radius)
	{
		const float d = std::sqrt(x * x + y * y);
		float z = 0;
		if (d < radius / std::sqrt(2.0f))
			z = std::sqrt(radius * radius - d * d) / radius;
		else
			z = radius * radius / (2 * d);

		return { x, y, z };
	}

	rotation trackball_rotation(vec2 const& p0, vec2 const& p1, float radius)
	{
		rotation R;
		const float d = norm(p1-p0);
		if( d > 1e-4f )
		{
			vec3 const s0 = trackball_projection(p0.x, p0.y, radius);
			vec3 const s1 = trackball_projection(p1.x, p1.y, radius);
		
			R = rotation_between_vector(normalize(s0), normalize(s1));
		}
		return R;
	}
}