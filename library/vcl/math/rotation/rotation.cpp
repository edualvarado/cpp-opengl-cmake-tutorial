#include "vcl/base/base.hpp"

#include "rotation.hpp"
#include "vcl/math/vec_mat/vec_mat.hpp"
#include <cmath>

namespace vcl
{

	rotation::rotation()
		:data({ 0,0,0,1 })
	{}

	rotation::rotation(quaternion const& q)
		: data(q)
	{}

	rotation::rotation(vec3 const& axis, float angle)
		: data(axis_angle_to_quaternion(axis, angle))
	{}

	rotation::rotation(mat3 const& M)
		: data(matrix_to_quaternion(M))
	{}


	mat3 rotation::matrix() const
	{
		return quaternion_to_matrix(data);
	}
	quaternion const& rotation::quat() const
	{
		return data;
	}
	void rotation::axis_angle(vec3& axis, float& angle) const
	{
		quaternion_to_axis_angle(data, axis, angle);
	}



	mat3 rotation::axis_angle_to_matrix(vec3 const& axis, float angle)
	{
		assert_vcl( std::abs(norm(axis) - 1.0f) < 1e-6f, "rotation axis must have a unit norm");

		float const c = std::cos(angle);
		float const s = std::sin(angle);
		float const x = axis.x;
		float const y = axis.y; 
		float const z = axis.z;

		return mat3{
			c+x*x*(1-c), x*y*(1-c)-z*s, x*z*(1-c)+y*s,
			x*y*(1-c)+z*s, c+y*y*(1-c), y*z*(1-c)-x*s,
			x*z*(1-c)-y*s, y*z*(1-c)+x*s, c+z*z*(1-c)
		};
	}
	void rotation::matrix_to_axis_angle(mat3 const& m, vec3& axis, float& angle)
	{
		rotation(m).axis_angle(axis, angle);
	}

	mat3 rotation::quaternion_to_matrix(quaternion const& q)
	{
		float const x = q.x;
		float const y = q.y;
		float const z = q.z;
		float const w = q.w;

		return mat3{
			1-2*(y*y+z*z), 2*(x*y-w*z), 2*(x*z+w*y),
			2*(x*y+w*z), 1-2*(x*x+z*z), 2*(y*z-w*x),
			2*(x*z-w*y), 2*(y*z+w*x), 1-2*(x*x+y*y)
		};
	}
	quaternion rotation::matrix_to_quaternion(mat3 const& m)
	{
		float const tr = trace(m);
		float const xx = get<0, 0>(m), xy = get<0, 1>(m), xz = get<0, 2>(m);
		float const yx = get<1, 0>(m), yy = get<1, 1>(m), yz = get<1, 2>(m);
		float const zx = get<2, 0>(m), zy = get<2, 1>(m), zz = get<2, 2>(m);

		if (tr > 0)
		{
			float const s = 0.5f / std::sqrt(tr + 1.0f);
			return quaternion{s*(zy-yz), s*(xz-zx), s*(yx-xy), 0.25f/s};
		}
		else
		{
			if (m(0, 0) > m(1, 1) && m(0, 0) > m(2, 2))
			{
				float const s = 2.0f * std::sqrt(1.0f+xx-yy-zz);
				return quaternion{0.25f*s, (xy+yx)/s, (xz+zx)/s, (zy-yz)/s};
			}
			else if (m(1, 1) > m(2, 2))
			{
				float const s = 2.0f * std::sqrt(1.0f + yy - xx - zz);
				return quaternion{ (xy+yx)/s, 0.25f*s, (yz+zy)/s, (xz-zx)/s };
			}
			else
			{
				float const s = 2.0f * std::sqrt(1.0f + zz - xx - yy);
				return quaternion{ (xz+zx)/s, (yz+zy)/s, 0.25f*s, (yx-xy)/s };
			}
		}
	}

	quaternion rotation::axis_angle_to_quaternion(vec3 const& axis, float angle)
	{
		float const c = std::cos(angle / 2.0f);
		float const s = std::sin(angle / 2.0f);
		return quaternion{axis.x*s, axis.y*s, axis.z*s, c};
	}

	void rotation::quaternion_to_axis_angle(quaternion const& q, vec3& axis, float& angle)
	{
		assert_vcl(std::abs(norm(q) - 1.0f) < 1e-6f, "quaternion must be of unit norm to represent rotation");

		vec3 const s = { q.x, q.y, q.z };
		float const c = norm(s);

		if (c < 1e-4f) // rotation angle = 0 
		{
			axis  = vec3{1,0,0};
			angle = 0.0f;
		}
		else
		{
			axis = s/c;
			angle = 2.0f * std::atan2(c, q.w);
		}


	}


	vec3 rotation::matrix_row_x() const
	{
		float const x = data.x, y=data.y, z=data.z, w=data.w;
		return vec3 {1-2*(y*y+z*z), 2*(x*y-w*z), 2*(x*z+w*y)};
	}
	vec3 rotation::matrix_row_y() const
	{
		float const x = data.x, y=data.y, z=data.z, w=data.w;
		return vec3 {2*(x*y+w*z), 1-2*(x*x+z*z), 2*(y*z-w*x)};
	}
	vec3 rotation::matrix_row_z() const
	{
		float const x = data.x, y=data.y, z=data.z, w=data.w;
		return vec3 {2*(x*z-w*y), 2*(y*z+w*x), 1-2*(x*x+y*y)};
	}
	vec3 rotation::matrix_col_x() const
	{
		float const x = data.x, y=data.y, z=data.z, w=data.w;
		return vec3 {1-2*(y*y+z*z), 2*(x*y+w*z), 2*(x*z-w*y)};
	}
	vec3 rotation::matrix_col_y() const
	{
		float const x = data.x, y=data.y, z=data.z, w=data.w;
		return vec3 {2*(x*y-w*z), 1-2*(x*x+z*z), 2*(y*z+w*x)};
	}
	vec3 rotation::matrix_col_z() const
	{
		float const x = data.x, y=data.y, z=data.z, w=data.w;
		return vec3 {2*(x*z+w*y), 2*(y*z-w*x), 1-2*(x*x+y*y)};
	}





	rotation rotation::lerp(rotation const& r1, rotation const& r2, float const alpha)
	{
		quaternion q1 = r1.data;
		quaternion q2 = r2.data;

		if(dot(q1,q2)<0)
			q2 *= -1.0f;

		quaternion q;
		q = (1.0f-alpha)*q1 + alpha*q2;
		q = q / norm(q);
		return rotation{ q };
	}

	//rotation rotation::slerp(rotation const& r1, rotation const& r2, float const alpha);

	rotation inverse(rotation const& r)
	{
		return rotation(conjugate(r.data));
	}


	rotation operator*(rotation const& r1, rotation const& r2)
	{
		quaternion const& q1 = r1.data;
		quaternion const& q2 = r2.data;
		quaternion q;
		q = { q1.x * q2.w + q1.w * q2.x + q1.y * q2.z - q1.z * q2.y,
			q1.y * q2.w + q1.w * q2.y + q1.z * q2.x - q1.x * q2.z,
			q1.z * q2.w + q1.w * q2.z + q1.x * q2.y - q1.y * q2.x,
			q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z };
		return rotation(q);
	}

	rotation& operator*=(rotation& r1, rotation const& r2)
	{
		r1 = r1 * r2;
		return r1;
	}


	vec3 operator*(rotation const& r, vec3 const& p)
	{
		quaternion const qp = quaternion(p.x, p.y, p.z, 0.0f);
		quaternion res = r.data * qp * conjugate(r.data);
		return res.xyz();
	}

	vec4 operator*(rotation const& r, vec4 const& p)
	{
		return { r*p.xyz(), p.w };
	}


	
	mat3 operator*(rotation const& r, mat3 const& M)
	{
		return r.matrix() * M;
	}
	
	mat4 operator*(rotation const& r, mat4 const& M)
	{
		return mat4::identity().set_block(r.matrix()) * M;
	}



	rotation rotation_between_vector(vec3 const& e, vec3 const& e_target)
	{
		assert_vcl(is_equal(norm(e), 1.0f), "Vector e="+str(e)+" must have a unit norm ("+str(norm(e))+")");
		assert_vcl(is_equal(norm(e_target), 1.0f), "Vector e_target="+str(e_target)+" must have a unit norm ("+str(norm(e_target))+")");

		// Case of identity
		if (norm(e - e_target) < 1e-5f)
			return rotation();
		// Case of rotation of pi // need to find an orthogonal vector
		if (norm(e + e_target) < 1e-5f)
		{
			vec3 ortho = orthogonal_vector(e);
			return rotation(ortho, pi);
		}
			

		float const d = dot(e, e_target);
		float const angle = std::acos( clamp(d, -1.0f, 1.0f) );

		vec3 const axis = normalize(cross(e, e_target));
		return rotation(axis, angle);
	}

	rotation rotation_between_vector(vec3 const& e1, vec3 const& e2, vec3 const& e1_target, vec3 const& e2_target)
	{
		assert_vcl(is_equal(norm(e1), 1.0f), "Vector must have a unit norm");
		assert_vcl(is_equal(norm(e2), 1.0f), "Vector must have a unit norm");
		assert_vcl(is_equal(norm(e1_target), 1.0f), "Vector must have a unit norm");
		assert_vcl(is_equal(norm(e2_target), 1.0f), "Vector must have a unit norm");
		assert_vcl(is_equal(dot(e1, e2), 0.0f), "Vectors must be orthogonal");
		assert_vcl(is_equal(dot(e1_target, e2_target), 0.0f), "Vectors must be orthogonal");

		mat3 M = mat3{ e1,e2, cross(e1,e2) };
		mat3 M_target = mat3{ e1_target,e2_target, cross(e1_target,e2_target) };

		return rotation( transpose(M_target) * M);
	}


	std::string type_str(rotation const&)
	{
		return "rotation";
	}
	std::string str(rotation const& r)
	{
		return str(r.data);
	}
	std::ostream& operator<<(std::ostream& s, rotation const& r)
	{
		s << r.data;
		return s;
	}


}
