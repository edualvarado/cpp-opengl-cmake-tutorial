#include "vcl/base/base.hpp"
#include "affine_rts.hpp"

#include "../affine_rt/affine_rt.hpp"

namespace vcl
{
	affine_rts::affine_rts()
		:rotate(), translate(), scale(1.0f)
	{}
	affine_rts::affine_rts(affine_rt const& T)
		:rotate(T.rotate), translate(T.translate), scale(1.0f)
	{}
	affine_rts::affine_rts(rotation const& rotate_arg, vec3 const& translate_arg, float scale_arg)
		:rotate(rotate_arg), translate(translate_arg), scale(scale_arg)
	{}

	mat4 affine_rts::matrix() const
	{
		mat3 const& R = rotate.matrix();
		return mat4{ 
			scale * get<0,0>(R), scale * get<0,1>(R)  , scale * get<0,2>(R), translate.x,
			scale * get<1,0>(R), scale * get<1,1>(R)  , scale * get<1,2>(R), translate.y,
			scale * get<2,0>(R), scale * get<2,1>(R)  , scale * get<2,2>(R), translate.z,
			0.0f  ,  0.0f ,  0.0f ,    1.0f     
		};
		
	}

	vec3 operator*(affine_rts const& T, vec3 const& p)
	{
		mat3 const R = T.rotate.matrix();
		
		return vec3{
			T.scale*(get<0,0>(R)*p.x + get<0,1>(R)*p.y + get<0,2>(R)*p.z) + T.translate.x,
			T.scale*(get<1,0>(R)*p.x + get<1,1>(R)*p.y + get<1,2>(R)*p.z) + T.translate.y,
			T.scale*(get<2,0>(R)*p.x + get<2,1>(R)*p.y + get<2,2>(R)*p.z) + T.translate.z
		};
	}
	vec4 operator*(affine_rts const& T, vec4 const& p)
	{
		mat3 const R = T.rotate.matrix();
		return vec4{
			T.scale*(get<0,0>(R)*p.x + get<0,1>(R)*p.y + get<0,2>(R)*p.z) + T.translate.x*p.w,
			T.scale*(get<1,0>(R)*p.x + get<1,1>(R)*p.y + get<1,2>(R)*p.z) + T.translate.y*p.w,
			T.scale*(get<2,0>(R)*p.x + get<2,1>(R)*p.y + get<2,2>(R)*p.z) + T.translate.z*p.w,
			p.w
		};
	}

	affine_rts inverse(affine_rts const& T)
	{
		rotation const R_inv = inverse(T.rotate);
		return affine_rts(R_inv, -(R_inv*T.translate), 1.0f/T.scale);
	}

	affine_rts operator*(affine_rts const& T1, affine_rts const& T2)
	{
		return affine_rts( T1.rotate * T2.rotate, T1.scale*(T1.rotate*T2.translate)+T1.translate, T1.scale*T2.scale);
	}


	affine_rts operator*(affine_rts const& T, rotation const& R)
	{
		/** (T.s T.R | T.t) ( R | 0) = (T.s T.R R | T.t)
		*   (      0 |   1) ( 0 | 1)   (        0 |   1) */
		return affine_rts(T.rotate * R, T.translate, T.scale);
	}
	affine_rts operator*(rotation const& R, affine_rts const& T)
	{
		/** ( R | 0) (T.s T.R | T.t) = (T.s R T.R | R T.t)
		*   ( 0 | 1) (      0 |   1)   (        0 |     1) */
		return affine_rts(R * T.rotate, R*T.translate, T.scale);
	}

	affine_rts operator+(vec3 const& tr, affine_rts const& T)
	{
		return affine_rts(T.rotate, T.translate+tr, T.scale);
	}
	affine_rts operator+(affine_rts const& T, vec3 const& tr)
	{
		return affine_rts(T.rotate, T.translate+tr, T.scale);
	}
	affine_rts operator-(affine_rts const& T, vec3 const& tr)
	{
		return affine_rts(T.rotate, T.translate-tr, T.scale);
	}

	affine_rts operator*(float s, affine_rts const& T)
	{
		return affine_rts(T.rotate, T.translate, T.scale*s);
	}
	affine_rts operator*(affine_rts const& T, float s)
	{
		return affine_rts(T.rotate, T.translate, T.scale*s);
	}
	affine_rts operator/(affine_rts const& T, float s)
	{
		return affine_rts(T.rotate, T.translate, T.scale/s);
	}

	affine_rts operator*(float s, rotation const& r)
	{
		return affine_rts(r, {0,0,0}, s);
	}
	affine_rts operator*(rotation const& r, float s)
	{
		return affine_rts(r, {0,0,0}, s);
	}

	std::string type_str(affine_rts const&)
	{
		return "affine_rt";
	}
	std::string str(affine_rts const& T)
	{
		return str(T.rotate)+" "+str(T.translate)+" "+str(T.scale);
	}
	std::ostream& operator<<(std::ostream& s, affine_rts const& T)
	{
		s << str(T);
		return s;
	}

}