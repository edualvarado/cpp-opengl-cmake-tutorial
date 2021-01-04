#include "vcl/base/base.hpp"
#include "affine_rt.hpp"


namespace vcl
{
	affine_rt::affine_rt()
		:rotate(),translate()
	{}
	affine_rt::affine_rt(rotation const& rotate_arg)
		:rotate(rotate_arg), translate()
	{}
	affine_rt::affine_rt(rotation const& rotate_arg, vec3 const& translate_arg)
		:rotate(rotate_arg), translate(translate_arg)
	{}


	mat4 affine_rt::matrix() const
	{
		return mat4::affine(rotate.matrix(), translate);
	}

	vec3 operator*(affine_rt const& T, vec3 const& p)
	{
		mat3 const R = T.rotate.matrix();
		
		return vec3{get<0,0>(R)*p.x + get<0,1>(R)*p.y + get<0,2>(R)*p.z + T.translate.x,
			get<1,0>(R)*p.x + get<1,1>(R)*p.y + get<1,2>(R)*p.z + T.translate.y,
			get<2,0>(R)*p.x + get<2,1>(R)*p.y + get<2,2>(R)*p.z + T.translate.z
		};
	}
	vec4 operator*(affine_rt const& T, vec4 const& p)
	{
		mat3 const R = T.rotate.matrix();
		return vec4{get<0,0>(R)*p.x + get<0,1>(R)*p.y + get<0,2>(R)*p.z + T.translate.x*p.w,
			get<1,0>(R)*p.x + get<1,1>(R)*p.y + get<1,2>(R)*p.z + T.translate.y*p.w,
			get<2,0>(R)*p.x + get<2,1>(R)*p.y + get<2,2>(R)*p.z + T.translate.z*p.w,
			p.w
		};
	}

	affine_rt inverse(affine_rt const& T)
	{
		rotation const R_inv = inverse(T.rotate);
		return affine_rt(R_inv, -(R_inv*T.translate));
	}

	affine_rt operator*(affine_rt const& T1, affine_rt const& T2)
	{
		return affine_rt(T1.rotate * T2.rotate, T1.rotate*T2.translate+T1.translate);
	}


	affine_rt operator*(affine_rt const& T, rotation const& R)
	{
		/** ( T.R | T.t) ( R | 0) = ( T.R R | T.t)
		*   (   0 |   1) ( 0 | 1)   (     0 |   1) */
		return affine_rt(T.rotate * R, T.translate);
	}
	affine_rt operator*(rotation const& R, affine_rt const& T)
	{
		/** ( R | 0) ( T.R | T.t) = ( R T.R | R T.t)
		*   ( 0 | 1) (   0 |   1)   (     0 |     1) */
		return affine_rt(R * T.rotate, R*T.translate);
	}

	affine_rt operator+(vec3 const& tr, affine_rt const& T)
	{
		return affine_rt(T.rotate, T.translate+tr);
	}
	affine_rt operator+(affine_rt const& T, vec3 const& tr)
	{
		return affine_rt(T.rotate, T.translate+tr);
	}
	affine_rt operator-(affine_rt const& T, vec3 const& tr)
	{
		return affine_rt( T.rotate, T.translate-tr);
	}

	affine_rt rotation_around_center(rotation const& R, vec3 const& center)
	{
		return affine_rt{ R, -(R*center)+center };
	}


	std::string type_str(affine_rt const&)
	{
		return "affine_rt";
	}
	std::string str(affine_rt const& T)
	{
		return str(T.rotate)+" "+str(T.translate);
	}
	std::ostream& operator<<(std::ostream& s, affine_rt const& T)
	{
		s << str(T);
		return s;
	}

}