#pragma once

#include "vcl/math/rotation/rotation.hpp"

namespace vcl
{
	struct affine_rt;

	struct affine_rts
	{
		rotation rotate;
		vec3 translate;
		float scale;

		affine_rts();
		explicit affine_rts(affine_rt const& T);
		explicit affine_rts(rotation const& rotate, vec3 const& translate, float scale);


		mat4 matrix() const;
	};

	vec3 operator*(affine_rts const& T, vec3 const& p);
	vec4 operator*(affine_rts const& T, vec4 const& p);
	affine_rts operator*(affine_rts const& T1, affine_rts const& T2);
	
	affine_rts operator*(affine_rts const& T, rotation const& R);
	affine_rts operator*(rotation const& R, affine_rts const& T);

	affine_rts operator+(vec3 const& tr, affine_rts const& T);
	affine_rts operator+(affine_rts const& T, vec3 const& tr);
	affine_rts operator-(affine_rts const& T, vec3 const& tr);

	affine_rts operator*(float s, affine_rts const& T);
	affine_rts operator*(affine_rts const& T, float s);
	affine_rts operator/(affine_rts const& T, float s);


	affine_rts operator*(float s, rotation const& r);
	affine_rts operator*(rotation const& r, float s);


	affine_rts inverse(affine_rts const& T);

	std::string type_str(affine_rts const& );
	std::string str(affine_rts const& T);
	std::ostream& operator<<(std::ostream& s, affine_rts const& T);


	
}