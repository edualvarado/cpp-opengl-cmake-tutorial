#include "vcl/base/base.hpp"
#include "../matrix_stack/matrix_stack.hpp"


#include <iostream>

namespace vcl_test 
{

	void test_matrix_stack()
	{
		// element access
		{
			using namespace vcl;
			matrix_stack<int, 2, 3> a = { 1,2,3, 4,5,6 };
			
			assert_vcl_no_msg(a(0, 0) == 1); assert_vcl_no_msg(a(0, 1) == 2); assert_vcl_no_msg(a(0, 2) == 3);
			assert_vcl_no_msg(a(1, 0) == 4); assert_vcl_no_msg(a(1, 1) == 5); assert_vcl_no_msg(a(1, 2) == 6);

			assert_vcl_no_msg(a(0)(0) == 1); assert_vcl_no_msg(a(0)(1) == 2); assert_vcl_no_msg(a(0)(2) == 3);
			assert_vcl_no_msg(a(1)(0) == 4); assert_vcl_no_msg(a(1)(1) == 5); assert_vcl_no_msg(a(1)(2) == 6);

			assert_vcl_no_msg(a[0][0] == 1); assert_vcl_no_msg(a[0][1] == 2); assert_vcl_no_msg(a[0][2] == 3);
			assert_vcl_no_msg(a[1][0] == 4); assert_vcl_no_msg(a[1][1] == 5); assert_vcl_no_msg(a[1][2] == 6);


			assert_vcl_no_msg( is_equal(a[0], buffer_stack<int, 3>{ 1,2,3 }) && is_equal(a[1], buffer_stack<int, 3>{ 4,5,6 }) );
			assert_vcl_no_msg( is_equal(a(0), buffer_stack<int, 3>{ 1, 2, 3 }) && is_equal(a(1), buffer_stack<int, 3>{ 4, 5, 6 }));


			assert_vcl_no_msg( is_equal(get<0, 0>(a), 1) ); assert_vcl_no_msg(is_equal(get<0, 1>(a), 2)); assert_vcl_no_msg(is_equal(get<0, 2>(a), 3));
			assert_vcl_no_msg( is_equal(get<1, 0>(a), 4)); assert_vcl_no_msg(is_equal(get<1, 1>(a), 5)); assert_vcl_no_msg(is_equal(get<1, 2>(a), 6));

			assert_vcl_no_msg(is_equal(get_offset<0>(a), 1)); assert_vcl_no_msg(is_equal(get_offset<1>(a), 2)); assert_vcl_no_msg(is_equal(get_offset<2>(a), 3));
			assert_vcl_no_msg(is_equal(get_offset<3>(a), 4)); assert_vcl_no_msg(is_equal(get_offset<4>(a), 5)); assert_vcl_no_msg(is_equal(get_offset<5>(a), 6));

			assert_vcl_no_msg(is_equal(get<0>(a), buffer_stack<int, 3>{ 1,2,3 }) && is_equal(get<1>(a), buffer_stack<int, 3>{ 4,5,6 }) );

			assert_vcl_no_msg(type_str(a) == "matrix_stack<int,2,3>");
		}

		// matrix multiplication
		{
			vcl::matrix_stack<int, 2, 3> a = { 1,2,3, 4,5,6 };
			vcl::matrix_stack<int, 3, 2> b = { 5,-1, 4,8, -2,2 };

			vcl::matrix_stack<int, 2, 2> c = a * b;
			assert_vcl_no_msg(is_equal(c, vcl::matrix_stack<int, 2,2>{7,21,28,48}));
		}


		// matrix componentwise multiplication
		{
			vcl::matrix_stack<int, 2, 3> a = { 1,2,3, 4,5,6 };
			vcl::matrix_stack<int, 2, 3> b = { 5,2,-1, 2,1,-2 };

			vcl::matrix_stack<int, 2, 3> c = vcl::multiply_componentwise(a, b);
			assert_vcl_no_msg(is_equal(c, vcl::matrix_stack<int, 2, 3>{5,4,-3, 8,5,-12}));
		}

		// matrix vector
		{
			vcl::matrix_stack<int, 2, 3> a = { 1,2,3, 4,5,6 };
			vcl::buffer_stack<int, 3> b = { 5,-2,3 };
			vcl::buffer_stack<int, 2> c = a * b;
			assert_vcl_no_msg(is_equal(c, vcl::buffer_stack<int, 2>{10, 28}));
		}


		// remove column row
		{
			vcl::matrix_stack<int, 5, 4> a = { 1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15,16, 17,18,19,20};

			assert_vcl_no_msg( is_equal(a.remove_row_column(1, 2), vcl::matrix_stack<int,4,3>{1,2,4, 9,10,12, 13,14,16, 17,18,20} ) );
			assert_vcl_no_msg( is_equal(a.remove_row_column(0, 0), vcl::matrix_stack<int,4,3>{6,7,8, 10,11,12, 14,15,16, 18,19,20} ) );
			assert_vcl_no_msg( is_equal(a.remove_row_column(4, 3), vcl::matrix_stack<int,4,3>{1,2,3, 5,6,7, 9,10,11, 13,14,15} ) );


		}

		// identity
		{
			assert_vcl_no_msg(is_equal(vcl::matrix_stack<float, 3, 3>::identity(), vcl::matrix_stack<float, 3, 3>{ 1,0,0, 0,1,0, 0,0,1 }));
			assert_vcl_no_msg(is_equal(vcl::matrix_stack<float, 3, 4>::identity(), vcl::matrix_stack<float, 3, 4>{ 1,0,0,0, 0,1,0,0, 0,0,1,0 }));
			assert_vcl_no_msg(is_equal(vcl::matrix_stack<float, 4, 3>::identity(), vcl::matrix_stack<float, 4, 3>{ 1,0,0, 0,1,0, 0,0,1, 0,0,0 }));
		}

		// construct from different size
		{
			using namespace vcl;
			{
				mat3 M1 = { 1,2,3,
							4,5,6,
							7,8,9 };
				mat2 M2 = mat2(M1);
				mat4 M4 = mat4(M1);
				assert_vcl_no_msg(is_equal(M2, mat2{ 1,2,4,5 }));
				assert_vcl_no_msg(is_equal(M4, mat4{ 1,2,3,0, 4,5,6,0, 7,8,9,0, 0,0,0,0 }));
			}
			{
				mat4 M1 = { 1 , 2, 3, 4,
							5 , 6, 7, 8,
							9 ,10,11,12,
							13,14,15,16
				};
				mat2 M2 = mat2(M1);
				mat3 M3 = mat3(M1);
				assert_vcl_no_msg(is_equal(M2, mat2{ 1,2,5,6 }));
				assert_vcl_no_msg(is_equal(M3, mat3{ 1,2,3, 5,6,7, 9,10,11 }));
			}
		}

		// set block
		{
			using namespace vcl;

			assert_vcl_no_msg( is_equal(mat4().set_block(mat2{ 1,2,3,4 }), mat4{ 1,2,0,0, 3,4,0,0, 0,0,0,0, 0,0,0,0 }));
			assert_vcl_no_msg( is_equal(mat4().set_block(mat2{ 1,2,3,4 }, 0, 1), mat4{ 0,1,2,0, 0,3,4,0, 0,0,0,0, 0,0,0,0 }));
			assert_vcl_no_msg( is_equal(mat4().set_block(mat2{ 1,2,3,4 }, 1, 0), mat4{ 0,0,0,0, 1,2,0,0, 3,4,0,0, 0,0,0,0 }));
		}


	}
}