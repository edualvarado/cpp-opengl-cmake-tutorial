#include "camera_head.hpp"

#include "vcl/base/base.hpp"
#include "../common_functions/common_functions.hpp"

namespace vcl
{

	camera_head::camera_head()
		:orientation_camera(), position_camera()
	{}

	vec3 camera_head::position() const
	{
		return position_camera;
	}
	rotation camera_head::orientation() const
	{
		return orientation_camera;
	}

	void camera_head::manipulator_rotate_trackball(vec2 const& p0, vec2 const& p1)
	{
		rotation const r = trackball_rotation(p0,p1);
		orientation_camera = orientation_camera * r;
	}
	void camera_head::manipulator_rotate_roll_pitch_yaw(float roll, float pitch, float yaw)
	{
		rotation r_roll  = rotation({0,0,-1}, roll);
		rotation r_pitch = rotation({1,0,0}, pitch);
		rotation r_yaw   = rotation({0,1,0}, yaw);

		orientation_camera = orientation_camera * r_yaw * r_pitch * r_roll;
	}
	void camera_head::manipulator_translate_in_plane(vec2 const& tr)
	{
		position_camera -= translation_in_plane(tr, orientation());
	}


}