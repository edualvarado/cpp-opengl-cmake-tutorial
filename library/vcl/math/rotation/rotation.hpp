#pragma once

#include "../quaternion/quaternion.hpp"
#include "../matrix/matrix.hpp"


namespace vcl
{

	/** Structure handling a rotation.
	* Provides an interface compatible with different representation of rotation (matrix, quaternion, axis/angle)
	* The internal storage of the rotation is a unit quaternion, but its use may not be aware of it.	
	* The structure can be manipulated and "interact" like if it was a matrix: rotation*vec3, rotation*mat3, etc.
	*/
	struct rotation
	{
		quaternion data;

		// Empty constructor: identity, q = [1,0,0,0]
		rotation();
		// Construct rotation from a quaternion representation
		explicit rotation(quaternion const& q);
		// Construct rotation from an (axis,angle) representation
		explicit rotation(vec3 const& axis, float angle);
		// Construct rotation from its matrix representation
		explicit rotation(mat3 const& M);


		mat3 matrix() const;
		quaternion const& quat() const;
		void axis_angle(vec3& axis, float& angle) const;

		vec3 matrix_row_x() const;
		vec3 matrix_row_y() const;
		vec3 matrix_row_z() const;
		vec3 matrix_col_x() const;
		vec3 matrix_col_y() const;
		vec3 matrix_col_z() const;

		// Provide exhaustive conversion between rotation representation
		static mat3 axis_angle_to_matrix(vec3 const& axis, float angle);
		static void matrix_to_axis_angle(mat3 const& m, vec3& axis, float& angle);

		static mat3 quaternion_to_matrix(quaternion const& q);
		static quaternion matrix_to_quaternion(mat3 const& m);
		
		static quaternion axis_angle_to_quaternion(vec3 const& axis, float angle);
		static void quaternion_to_axis_angle(quaternion const& q, vec3& axis, float& angle);

		// Linear interpolation of rotation
		static rotation lerp(rotation const& r1, rotation const& r2, float const alpha);
		// Spherical Linear interpolation of rotation
		//static rotation slerp(rotation const& r1, rotation const& r2, float const alpha);

	};

	// Inverse of the rotation
	rotation inverse(rotation const& r);

	// Composition between rotations r = r1 o r2
	rotation operator*(rotation const& r1, rotation const& r2);
	// Composition r1 = r1 o r2
	rotation& operator*=(rotation& r1, rotation const& r2);

	// Apply rotation to vector
	vec3 operator*(rotation const& r, vec3 const& p);
	// Apply rotation to homogeneous 4D vector 
	vec4 operator*(rotation const& r, vec4 const& p);
	// Multiply rotation matrix to mat3
	mat3 operator*(rotation const& r, mat3 const& M);
	// Multiply rotation matrix to mat4
	mat4 operator*(rotation const& r, mat4 const& M);


	std::string type_str(rotation const& );
	std::string str(rotation const& r);
	std::ostream& operator<<(std::ostream& s, rotation const& r);


	// Compute a rotation R such that R e = e_target
	//  Conditions: ||e||=||e_target||=1
	rotation rotation_between_vector(vec3 const& e0, vec3 const& e_target);
	// Rotation R such that R e1 = e1_target and R e2 = e2_target
	//  Conditions: ||e1||=||e1_target||=1
	//              ||e2||=||e2_target||=1
	//              dot(e1,e2) = 0
	//              dot(e1_target,e2_target) = 0
	rotation rotation_between_vector(vec3 const& e1, vec3 const& e2, vec3 const& e1_target, vec3 const& e2_target);

}
