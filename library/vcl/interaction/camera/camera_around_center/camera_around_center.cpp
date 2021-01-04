#include "camera_around_center.hpp"

#include "vcl/base/base.hpp"
#include "../common_functions/common_functions.hpp"

namespace vcl
{
	camera_around_center::camera_around_center()
		:orientation_camera(), center_of_rotation({0.0f, 0.0f, 0.0f}), distance_to_center(5.0f)
	{}
	vec3 camera_around_center::position() const
	{
		return orientation_camera * vec3{0.0f, 0.0f, distance_to_center} + center_of_rotation;
	}
	rotation camera_around_center::orientation() const
	{
		return orientation_camera;
	}

	void camera_around_center::manipulator_rotate_trackball(vec2 const& p0, vec2 const& p1)
	{
		rotation const r = trackball_rotation(p0,p1);
		orientation_camera = orientation_camera * inverse(r);
	}
	void camera_around_center::manipulator_rotate_roll_pitch_yaw(float roll, float pitch, float yaw)
	{
		rotation r_roll  = rotation({0,0,-1}, roll);
		rotation r_pitch = rotation({1,0,0}, pitch);
		rotation r_yaw   = rotation({0,1,0}, yaw);

		orientation_camera = orientation_camera * r_yaw * r_pitch * r_roll;
	}

	void camera_around_center::manipulator_scale_distance_to_center(float magnitude)
	{
		distance_to_center *= (1.0f + magnitude);
		distance_to_center = std::max(distance_to_center, 0.01f);
	}
	void camera_around_center::manipulator_translate_in_plane(vec2 const& tr)
	{
		center_of_rotation -= translation_in_plane(tr, orientation_camera);
	}

	void camera_around_center::look_at(vec3 const& eye, vec3 const& center, vec3 const& up)
	{
		frame F = camera_frame_look_at(eye, center, up);
		orientation_camera = F.orientation;
		center_of_rotation = center;
		distance_to_center = norm(eye-center);
	}

}