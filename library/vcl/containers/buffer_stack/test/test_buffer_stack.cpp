#include "vcl/base/base.hpp"
#include "vcl/containers/buffer_stack/buffer_stack.hpp"


#include <iostream>

namespace vcl_test 
{

	void text_buffer_stack()
	{
		{
			vcl::buffer_stack<int,4> a = { 1,2,3,4 };
			assert_vcl_no_msg(is_equal(a, { 1,2,3,4 }));
			assert_vcl_no_msg(!is_equal(a, vcl::buffer_stack<int, 3>{ 1,2,3 }));
			assert_vcl_no_msg(!is_equal(a, vcl::buffer_stack<int, 5>{ 1, 2, 3, 4, 5 }));
		}

		{
			vcl::buffer_stack<float,3> a = { 1.1f, 2.2f, 3.1f };
			assert_vcl_no_msg(is_equal(a, { 1.1f,2.2f,3.1f }));
			assert_vcl_no_msg(!is_equal(a, vcl::buffer_stack2<float>{ 1.1f,2.2f }));
			assert_vcl_no_msg(!is_equal(a, { 1.1f,2.21f,3.1f }));
		}

		// access size 2
		{
			vcl::buffer_stack<int, 2> a = { 1,2 };
			assert_vcl_no_msg(a[0] == 1); assert_vcl_no_msg(a[1] == 2);
			assert_vcl_no_msg(a(0) == 1); assert_vcl_no_msg(a(1) == 2);
			assert_vcl_no_msg(a.at(0) == 1); assert_vcl_no_msg(a.at(1) == 2);
			assert_vcl_no_msg(vcl::get<0>(a) == 1); assert_vcl_no_msg(vcl::get<1>(a) == 2);
		}

		// access size 3
		{
			vcl::buffer_stack<int,3> a = { 1,2,3 };
			a[0] = -1;
			a[1] = 5;
			a[2] = a[1] + 1;
			assert_vcl_no_msg(is_equal(a, { -1,5,6 }));
			a = { 7,8,-2 };
			assert_vcl_no_msg(is_equal(a, { 7,8,-2 }));

			assert_vcl_no_msg(a[0] == 7); assert_vcl_no_msg(a[1] == 8); assert_vcl_no_msg(a[2] == -2);
			assert_vcl_no_msg(a(0) == 7); assert_vcl_no_msg(a(1) == 8); assert_vcl_no_msg(a(2) == -2);
			assert_vcl_no_msg(a.at(0) == 7); assert_vcl_no_msg(a.at(1) == 8); assert_vcl_no_msg(a.at(2) == -2);
			assert_vcl_no_msg(vcl::get<0>(a) == 7); assert_vcl_no_msg(vcl::get<1>(a) == 8); assert_vcl_no_msg(vcl::get<2>(a) == -2);
		}

		// access size 4
		{
			vcl::buffer_stack<int, 4> a = { 1,2,3,4 };
			assert_vcl_no_msg(a[0] == 1); assert_vcl_no_msg(a[1] == 2); assert_vcl_no_msg(a[2] == 3); assert_vcl_no_msg(a[3] == 4);
			assert_vcl_no_msg(a(0) == 1); assert_vcl_no_msg(a(1) == 2); assert_vcl_no_msg(a(2) == 3); assert_vcl_no_msg(a(3) == 4);
			assert_vcl_no_msg(a.at(0) == 1); assert_vcl_no_msg(a.at(1) == 2); assert_vcl_no_msg(a(2) == 3); assert_vcl_no_msg(a(3) == 4);
			assert_vcl_no_msg(vcl::get<0>(a) == 1); assert_vcl_no_msg(vcl::get<1>(a) == 2); assert_vcl_no_msg(vcl::get<2>(a) == 3); assert_vcl_no_msg(vcl::get<3>(a) == 4);
		}

		{
			vcl::buffer_stack<int,3> const a = { 1,2,3 };
			assert_vcl_no_msg(a[0] == 1); assert_vcl_no_msg(a(0) == 1); assert_vcl_no_msg(a.at(0) == 1);
			assert_vcl_no_msg(a[1] == 2); assert_vcl_no_msg(a(1) == 2); assert_vcl_no_msg(a.at(1) == 2);
			assert_vcl_no_msg(a[2] == 3); assert_vcl_no_msg(a(2) == 3); assert_vcl_no_msg(a.at(2) == 3);
		}

		{
			vcl::buffer_stack<int,3> a = { 1,2,3 };
			a[0] = 5; a[1] = 6; a[2] = 7;
			assert_vcl_no_msg(is_equal(a, { 5,6,7 }));
			a(0) = 2; a(1) = 1; a(2) = -7;
			assert_vcl_no_msg(is_equal(a, { 2,1,-7 }));
			a.at(0) = -1; a.at(1) = 9; a.at(2) = -7;
			assert_vcl_no_msg(is_equal(a, { -1,9,-7 }));
		}


		{
			vcl::buffer_stack<vcl::buffer_stack<int,2>,3> a = { vcl::buffer_stack<int,2>{1,2}, {2,3}, {-1,1} };
			assert_vcl_no_msg(a[0].size() == 2); assert_vcl_no_msg(is_equal(a[0], { 1,2 }));
			assert_vcl_no_msg(a[1].size() == 2); assert_vcl_no_msg(is_equal(a[1], { 2,3 }));
			assert_vcl_no_msg(a[2].size() == 2); assert_vcl_no_msg(is_equal(a[2], { -1,1 }));
		}

		{
			vcl::buffer_stack<float, 16> b; assert_vcl_no_msg(vcl::is_equal(type_str(b), "buffer_stack<float,16>"));
			vcl::buffer_stack<vcl::buffer_stack<int,5>,6> c; assert_vcl_no_msg(vcl::is_equal(type_str(c), "buffer_stack<buffer_stack<int,5>,6>"));
		}

		{
			vcl::buffer_stack<int,3> a = { 4,5,6 };
			assert_vcl_no_msg(vcl::is_equal(str(a), "4 5 6"));
			assert_vcl_no_msg(vcl::is_equal(str(a,","), "4,5,6"));
			assert_vcl_no_msg(vcl::is_equal(str(a, ",","[","]"), "[4,5,6]"));
		}

		{
			vcl::buffer_stack<int,3> a = { 4,5,6 };
			int counter = 0;
			for (int v : a) {
				if (counter == 0) assert_vcl_no_msg(v == 4);
				if (counter == 1) assert_vcl_no_msg(v == 5);
				if (counter == 2) assert_vcl_no_msg(v == 6);
				counter++;
			}
			assert_vcl_no_msg(counter==3);
		}

		{
			vcl::buffer_stack<int,3> a = { 7,5,-1 };
			assert_vcl_no_msg(vcl::size_in_memory(a)==3*sizeof(int));

			vcl::buffer_stack<vcl::buffer_stack<int,2>,3> b = { vcl::buffer_stack<int,2>{1,2},{2,3}, {-1,-1} };
			assert_vcl_no_msg(vcl::size_in_memory(b) == 6 * sizeof(int));
		}

		{
			vcl::buffer_stack<std::string, 2> a = { "hello","world" };
			assert_vcl_no_msg(vcl::is_equal(a[0], "hello"));
			assert_vcl_no_msg(vcl::is_equal(a[1], "world"));
		}

		{
			vcl::int2 a = { 8, 4 };
			assert_vcl_no_msg(a.x==8);
			assert_vcl_no_msg(a.y==4);
			assert_vcl_no_msg(type_str(a) == "int2");
		}

		{
			vcl::int3 a = { 8, 4, -1 };
			assert_vcl_no_msg(a.x == 8);
			assert_vcl_no_msg(a.y == 4);
			assert_vcl_no_msg(a.z == -1);
			assert_vcl_no_msg(type_str(a) == "int3");
		}

		{
			vcl::int4 a = { 8, 4, -1, 5 };
			assert_vcl_no_msg(a.x == 8);
			assert_vcl_no_msg(a.y == 4);
			assert_vcl_no_msg(a.z == -1);
			assert_vcl_no_msg(a.w == 5);
			assert_vcl_no_msg(type_str(a) == "int4");
		}

		{
			vcl::vec2 a = { 1.1f, 2.3f };
			vcl::vec3 b = { 1.1f, 2.3f, -1.1f };
			vcl::vec4 c = { 1.1f, 2.3f, -1.1f, 1.5f };

			assert_vcl_no_msg(type_str(a) == "vec2");
			assert_vcl_no_msg(type_str(b) == "vec3");
			assert_vcl_no_msg(type_str(c) == "vec4");
		}

		{
			vcl::vec3 a(vcl::vec2{ 1.0f,2.0f }, 3.0f);
			assert_vcl_no_msg(is_equal(a, { 1.0f,2.0f,3.0f }));
			vcl::vec3 b(1.0f, vcl::vec2{ 2.0f,3.0f });
			assert_vcl_no_msg(is_equal(b, { 1.0f,2.0f,3.0f }));

		}

	}
}