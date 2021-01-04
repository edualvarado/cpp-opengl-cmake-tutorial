#include "vcl/containers/buffer/buffer.hpp"

namespace vcl_test 
{

	void text_buffer()
	{
		{
			vcl::buffer<int> a = { 1,2,3 };
			assert_vcl_no_msg(is_equal(a, { 1,2,3 }));
			assert_vcl_no_msg(!is_equal(a, { 1,2,3,4 }));
			assert_vcl_no_msg(!is_equal(a, { 1,2 }));
		}

		{
			vcl::buffer<float> a = { 1.1f, 2.2f, 3.1f };
			assert_vcl_no_msg(is_equal(a, { 1.1f,2.2f,3.1f }));
			assert_vcl_no_msg(!is_equal(a, { 1.1f,2.2f,3.1f,4.5f }));
			assert_vcl_no_msg(!is_equal(a, { 1.1f,2.2f }));
			assert_vcl_no_msg(!is_equal(a, { 1.1f,2.21f,3.1f }));
		}

		{
			vcl::buffer<int> a = { 1,2,3 };
			a[0] = -1;
			a[1] = 5;
			a[2] = a[1] + 1;
			assert_vcl_no_msg(is_equal(a, { -1,5,6 }));
			a = { 7,8,-2,3 };
			assert_vcl_no_msg(is_equal(a, { 7,8,-2,3 }));
			a.push_back(9);
			assert_vcl_no_msg(is_equal(a, { 7,8,-2,3,9 }));
			a.resize_clear(2);
			assert_vcl_no_msg(is_equal(a, { 0,0 }));
		}

		{
			vcl::buffer<int> const a = { 1,2,3 };
			assert_vcl_no_msg(a[0] == 1); assert_vcl_no_msg(a(0) == 1); assert_vcl_no_msg(a.at(0) == 1);
			assert_vcl_no_msg(a[1] == 2); assert_vcl_no_msg(a(1) == 2); assert_vcl_no_msg(a.at(1) == 2);
			assert_vcl_no_msg(a[2] == 3); assert_vcl_no_msg(a(2) == 3); assert_vcl_no_msg(a.at(2) == 3);
		}

		{
			vcl::buffer<int> a = { 1,2,3 };
			a[0] = 5; a[1] = 6; a[2] = 7;
			assert_vcl_no_msg(is_equal(a, { 5,6,7 }));
			a(0) = 2; a(1) = 1; a(2) = -7;
			assert_vcl_no_msg(is_equal(a, { 2,1,-7 }));
			a.at(0) = -1; a.at(1) = 9; a.at(2) = -7;
			assert_vcl_no_msg(is_equal(a, { -1,9,-7 }));
		}


		{
			vcl::buffer<vcl::buffer<int>> a = { {1,2},{2,3,4}, {-1} };
			assert_vcl_no_msg(a[0].size() == 2); assert_vcl_no_msg(is_equal(a[0], { 1,2 }));
			assert_vcl_no_msg(a[1].size() == 3); assert_vcl_no_msg(is_equal(a[1], { 2,3,4 }));
			assert_vcl_no_msg(a[2].size() == 1); assert_vcl_no_msg(is_equal(a[2], { -1 }));
			a.push_back(vcl::buffer<int>{ 7,8,9 });
			assert_vcl_no_msg(a[3].size() == 3); assert_vcl_no_msg(is_equal(a[3], { 7,8,9 }));
		}

		{
			vcl::buffer<int> a; assert_vcl_no_msg(vcl::is_equal(type_str(a),"buffer<int>"));
			vcl::buffer<float> b; assert_vcl_no_msg(vcl::is_equal(type_str(b), "buffer<float>"));
			vcl::buffer<vcl::buffer<int>> c; assert_vcl_no_msg(vcl::is_equal(type_str(c), "buffer<buffer<int>>"));
		}

		{
			vcl::buffer<int> a = { 4,5,6 };
			assert_vcl_no_msg(vcl::is_equal(str(a), "4 5 6"));
			assert_vcl_no_msg(vcl::is_equal(str(a,","), "4,5,6"));
			assert_vcl_no_msg(vcl::is_equal(str(a, ",","[","]"), "[4,5,6]"));
		}

		{
			vcl::buffer<int> a = { 4,5,6 };
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
			vcl::buffer<int> a = { 7,5,-1 };
			assert_vcl_no_msg(vcl::size_in_memory(a)==3*sizeof(int));

			vcl::buffer<vcl::buffer<int>> b = { {1,2},{2,3,4}, {-1} };
			assert_vcl_no_msg(vcl::size_in_memory(b) == 6 * sizeof(int));
		}

		// test linspace
		{
			vcl::buffer<float> a = vcl::buffer<float>::linespace(4.5f, 8.2f, 6);
			assert_vcl_no_msg(a.size() == 6);
			assert_vcl_no_msg(vcl::is_equal(a[0], 4.5f));
			assert_vcl_no_msg(vcl::is_equal(a[5], 8.2f));
		}

	}
}