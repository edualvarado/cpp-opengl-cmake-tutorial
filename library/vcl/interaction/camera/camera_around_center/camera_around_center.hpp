#pragma once

#include "vcl/math/math.hpp"
#include "vcl/interaction/camera/camera_base/camera_base.hpp"

namespace vcl
{
	/**
	* Frame matrix =
	* ( orientation | orientation*vec3{0.0f, 0.0f, distance} + center )
	* (      0      |                    1                            )
	*/
	struct camera_around_center : camera_base 
	{
		camera_around_center();

		rotation orientation_camera;
		vec3 center_of_rotation;
		float distance_to_center;

		vec3 position() const;
		rotation orientation() const;

	    void manipulator_rotate_trackball(vec2 const& p0, vec2 const& p1);
		void manipulator_rotate_roll_pitch_yaw(float roll, float pitch, float yaw);
	    void manipulator_scale_distance_to_center(float magnitude);
		void manipulator_translate_in_plane(vec2 const& tr);

		void look_at(vec3 const& eye, vec3 const& center, vec3 const& up);
	};
}