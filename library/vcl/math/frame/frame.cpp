#include "vcl/base/base.hpp"
#include "frame.hpp"

#include "vcl/math/affine/affine_rt/affine_rt.hpp"

namespace vcl {


		frame::frame()
			:orientation(), position()
		{}


		frame::frame(rotation const& orientation_arg, vec3 const& position_arg)
			:orientation(orientation_arg), position(position_arg)
		{}
		frame::frame(affine_rt const& transformation)
			:orientation(transformation.rotate), position(transformation.translate)
		{}
		frame::frame(vec3 const& ux, vec3 const& uy,vec3 const& position_arg)
			:orientation(rotation_between_vector({1,0,0},{0,1,0},ux,uy)), position(position_arg)
		{}





		vec3 frame::ux() const
		{
			return orientation.matrix_row_x();
		}
		vec3 frame::uy() const
		{
			return orientation.matrix_row_y();
		}
		vec3 frame::uz() const
		{
			return orientation.matrix_row_z();
		}
		mat4 frame::matrix() const
		{
			return mat4::affine(orientation.matrix(), position);
		}

		
		frame inverse(frame const& f)
		{
			rotation const R_inv = inverse(f.orientation);
			return frame(R_inv, -(R_inv*f.position));
		}

		frame operator*(affine_rt const& T, frame const& f)
		{
			return frame( T.rotate * f.orientation, T.rotate*f.position+T.translate );
		}
		frame operator*(rotation const& R, frame const& f)
		{
			return frame( R * f.orientation, R*f.position );
		}

		frame operator+(frame const& f, vec3 const& tr)
		{
			return frame(f.orientation, f.position+tr);
		}
		frame operator+(vec3 const& tr, frame const& f)
		{
			return frame(f.orientation, f.position+tr);
		}
		frame operator-(frame const& f, vec3 const& tr)
		{
			return frame(f.orientation, f.position-tr);
		}



}