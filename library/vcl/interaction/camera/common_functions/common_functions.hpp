#pragma once

#include "vcl/math/math.hpp"

namespace vcl
{
	vec3 translation_in_plane(vec2 const& translation, rotation const& plane_orientation);
	vec3 trackball_projection(float x, float y, float radius);
	rotation trackball_rotation(vec2 const& p0, vec2 const& p1, float radius=1.0f);
}