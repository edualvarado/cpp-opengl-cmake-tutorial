#pragma once

#include "vcl/containers/containers.hpp"

namespace vcl
{
	struct intersection_structure
	{
		bool valid = false;
		vec3 position = {0,0,0}; // position
		vec3 normal   = {0,0,1}; // normal
	};

	intersection_structure intersection_ray_sphere(vec3 const& ray_origin, vec3 const& ray_direction, vec3 const& sphere_center, float sphere_radius);

	intersection_structure intersection_ray_spheres_closest(vec3 const& ray_origin, vec3 const& ray_direction, buffer<vec3> const& sphere_centers, float sphere_radius, int* shape_index=nullptr );
}