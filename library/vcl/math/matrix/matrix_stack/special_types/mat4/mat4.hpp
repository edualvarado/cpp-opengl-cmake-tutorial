#pragma once

#include "../../matrix_stack.hpp"


namespace vcl
{
    template <>
	struct matrix_stack<float,4,4>
    {
        /** Internal storage as a 1D buffer */
        buffer_stack< buffer_stack<float, 4>, 4> data;

        /** Constructors */
        matrix_stack();
        matrix_stack(buffer_stack< buffer_stack<float, 4>, 4> const& elements);
        matrix_stack(buffer_stack<float, 16> const& elements);


        // Construct from a matrix with different size.
        //  Consider the min between (N1,N1_arg) and (N2,N2_arg)
        template <size_t N1_arg, size_t N2_arg>
        explicit matrix_stack(matrix_stack<float, N1_arg, N2_arg> const& M);

        matrix_stack(std::initializer_list<float> const& arg);
        matrix_stack(std::initializer_list<buffer_stack<float,4> > const& arg);



        static matrix_stack<float, 4, 4> identity();




        /** Return 16 */
        size_t size() const;
        /** Return {4,4} */
        size_t2 dimension() const;
        /** Fill all elements of the grid_2D with the same element*/
        matrix_stack<float, 4, 4>& fill(float value);


        /** Element access
         * Bound checking is performed unless VCL_NO_DEBUG is defined. */
        vec4 const& operator[](int k2) const; 
        vec4& operator[](int k2);
        vec4 const& operator[](size_t k2) const;
        vec4& operator[](size_t k2);

        vec4 const& operator()(int k2) const;
        vec4& operator()(int k2);
        vec4 const& operator()(size_t k2) const;
        vec4& operator()(size_t k2);

        float const& operator()(int k1, int k2) const;
        float& operator()(int k1, int k2);
        float const& operator()(size_t k1, size_t k2) const;
        float& operator()(size_t k1, size_t k2);

        float const& at_offset(int offset) const;
        float& at_offset(int offset);
        float const& at_offset(size_t offset) const;
        float& at_offset(size_t offset);


        matrix_stack<float, 3, 3> remove_row_column(size_t k1, size_t k2) const;
        
        /** Set a block within the matrix from a specific offset 
        *    @block: the matrix to be copied in the current one
        *    @offset: the offsets where the block has to be writter. Default value are (0,0). The block is written on the top-left corner.
        * Conditions:
        *     offset_1 + N1_arg < N1
        *     offset_2 + N2_arg < N2
        */
        template <size_t N1_arg, size_t N2_arg>
        matrix_stack<float, 4, 4>& set_block(matrix_stack<float, N1_arg, N2_arg> const& block, size_t offset_1 = 0, size_t offset_2 = 0);



        /** Iterators
        *  Iterators compatible with STL syntax and std::array */
        float* begin();
        float* end();
        float const* begin() const;
        float const* end() const;
        float const* cbegin() const;
        float const* cend() const;


        float const& at_unsafe(int k1, int k2) const;
        float& at_unsafe(int k1, int k2);
        float const& at_unsafe(size_t k1, size_t k2) const;
        float& at_unsafe(size_t k1, size_t k2);

        vec4 const& at_unsafe(int k1) const;
        vec4& at_unsafe(int k1);
        vec4 const& at_unsafe(size_t k1) const;
        vec4& at_unsafe(size_t k1);

        float const& at_offset_unsafe(int offset) const;
        float& at_offset_unsafe(int offset);
        float const& at_offset_unsafe(size_t offset) const;
        float& at_offset_unsafe(size_t offset);


        /** Build affine matrix from mat3 and translation parts*/
        static matrix_stack<float, 4, 4> affine(matrix_stack<float, 3, 3> const& linear, vec3 const& tr);
        vec3 translation() const;
        matrix_stack<float, 4, 4>& set_translation(vec3 const& tr);
    };
}


namespace vcl
{
    template <size_t N1_arg, size_t N2_arg>
    matrix_stack<float,4,4>::matrix_stack(matrix_stack<float, N1_arg, N2_arg> const& M)
    {
        size_t const N1m = std::min(size_t(4), N1_arg);
        size_t const N2m = std::min(size_t(4), N2_arg);
        for (size_t k1 = 0; k1 < N1m; ++k1)
            for (size_t k2 = 0; k2 < N2m; ++k2)
                at_unsafe(k1, k2) = M.at_unsafe(k1, k2);
    }

    template <size_t N1_arg, size_t N2_arg>
    matrix_stack<float, 4, 4>& matrix_stack<float, 4, 4>::set_block(matrix_stack<float, N1_arg, N2_arg> const& block, size_t offset_1, size_t offset_2)
    {
        static_assert(N1_arg < 4, "Block size is too large for the current matrix");
        static_assert(N2_arg < 4, "Block size is too large for the current matrix");
        assert_vcl(N1_arg + offset_1 < 4, "Block size exceed current matrix size");
        assert_vcl(N2_arg + offset_2 < 4, "Block size exceed current matrix size");

        for (size_t k1 = 0; k1 < N1_arg; ++k1) {
            size_t const idx_1 = k1 + offset_1;
            for (size_t k2 = 0; k2 < N2_arg; ++k2) {
                size_t const idx_2 = k2 + offset_2;
                at_unsafe(idx_1, idx_2) = block.at_unsafe(k1, k2);
            }
        }
        return *this;
    }
}