#pragma once

#include "vcl/math/matrix/matrix.hpp"

namespace vcl
{
	mat4 projection_perspective(float fov, float aspect, float z_near, float z_far);
	mat4 projection_perspective_inverse(float fov, float aspect, float z_near, float z_far);

	mat4 projection_orthographic(float left, float right, float bottom, float top, float z_near, float z_far);
	mat4 projection_orthographic_inverse(float left, float right, float bottom, float top, float z_near, float z_far);
}