#pragma once

#include "vcl/containers/buffer_stack/buffer_stack.hpp"

namespace vcl
{
	struct quaternion : vec4
	{
        using vec4::vec4;
	};

	std::string type_str(quaternion const&);

    quaternion conjugate(quaternion const& q);
    quaternion inverse(quaternion const& q);

    quaternion& operator*=(quaternion& a, quaternion const& b);
    quaternion  operator*(quaternion const& a, quaternion const& b);
    quaternion  operator*(quaternion const& a, float b);
    quaternion  operator*(float a, quaternion const& b);

    quaternion& operator/=(quaternion& a, quaternion const& b);
    quaternion  operator/(quaternion const& a, quaternion const& b);
    quaternion  operator/(quaternion const& a, float b);
    quaternion  operator/(float a, quaternion const& b);

    quaternion& operator+=(quaternion& a, quaternion const& b);
    quaternion operator+(quaternion const& a, quaternion const& b);
    quaternion& operator-=(quaternion& a, quaternion const& b);
    quaternion operator-(quaternion const& a, quaternion const& b);

    quaternion normalize(quaternion const& q);

	std::istream& operator>>(std::istream& stream, quaternion& data);
}