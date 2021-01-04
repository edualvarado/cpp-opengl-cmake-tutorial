#pragma once

#include "vcl/math/math.hpp"
#include "vcl/interaction/camera/camera_base/camera_base.hpp"

namespace vcl
{
	struct camera_head : camera_base
	{
		camera_head();

		rotation orientation_camera;
		vec3 position_camera;

		vec3 position() const;
		rotation orientation() const;

	    void manipulator_rotate_trackball(vec2 const& p0, vec2 const& p1);
		void manipulator_rotate_roll_pitch_yaw(float roll, float pitch, float yaw);
		void manipulator_translate_in_plane(vec2 const& tr);
	};
}