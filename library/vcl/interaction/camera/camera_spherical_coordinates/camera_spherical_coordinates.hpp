#pragma once

#include "vcl/math/math.hpp"
#include "vcl/interaction/camera/camera_base/camera_base.hpp"

namespace vcl
{
	struct camera_spherical_coordinates: camera_base{

		camera_spherical_coordinates();

		float theta;
		float phi;
		vec3 center_of_rotation;
		float distance_to_center;

		vec3 position() const;
		rotation orientation() const;

		void manipulator_rotate_spherical_coordinates(float theta, float phi);
	    void manipulator_scale_distance_to_center(float magnitude);
		void manipulator_translate_in_plane(vec2 const& tr);

	};
}