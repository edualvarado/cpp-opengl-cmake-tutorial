#pragma once

#include "vcl/math/rotation/rotation.hpp"

namespace vcl
{
	struct affine_rt
	{
		rotation rotate;
		vec3 translate;

		affine_rt();
		explicit affine_rt(rotation const& rotate);
		explicit affine_rt(rotation const& rotate, vec3 const& translate);

		mat4 matrix() const;
	};

	vec3 operator*(affine_rt const& T, vec3 const& p);
	vec4 operator*(affine_rt const& T, vec4 const& p);
	affine_rt operator*(affine_rt const& T1, affine_rt const& T2);
	
	affine_rt operator*(affine_rt const& T, rotation const& R);
	affine_rt operator*(rotation const& R, affine_rt const& T);

	affine_rt operator+(vec3 const& tr, affine_rt const& T);
	affine_rt operator+(affine_rt const& T, vec3 const& tr);
	affine_rt operator-(affine_rt const& T, vec3 const& tr);


	affine_rt inverse(affine_rt const& T);

	/** Transformation representing a rotation around a given center point.
	*   Transformation matrix corresponds to: 
	*     R (p-center)+center  <=> ( R | -R center + center)
	*                              ( 0 |            1      )
	*/
	affine_rt rotation_around_center(rotation const& R, vec3 const& center);
	
	std::string type_str(affine_rt const& );
	std::string str(affine_rt const& T);
	std::ostream& operator<<(std::ostream& s, affine_rt const& T);
}