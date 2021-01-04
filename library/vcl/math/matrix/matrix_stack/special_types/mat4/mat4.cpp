#include "vcl/base/base.hpp"

#include "mat4.hpp"

namespace vcl
{
	matrix_stack<float,4,4>::matrix_stack()
        :data()
    {}
    matrix_stack<float,4,4>::matrix_stack(buffer_stack<float, 16> const& elements)
        :data()
    {
        for (size_t k1 = 0; k1 < 4; ++k1)
            for (size_t k2 = 0; k2 < 4; ++k2)
                at_unsafe(k1, k2) = elements[4*k1+k2];
    }
    matrix_stack<float,4,4>::matrix_stack(buffer_stack< buffer_stack<float, 4>, 4> const& elements)
        :data(elements)
    {}



    matrix_stack<float,4,4>::matrix_stack(std::initializer_list<float> const& arg)
        :data()
    {
        assert_vcl(arg.size() >= 16, "Insufficient size to initialize mat4");
        auto it_arg = arg.begin();

        for (size_t k1 = 0; k1 < 4; ++k1) {
            for (size_t k2 = 0; k2 < 4; ++k2) {
                at_unsafe(k1, k2) = *it_arg;
                ++it_arg;
            }
        }
    }
    matrix_stack<float, 4, 4>::matrix_stack(std::initializer_list<buffer_stack<float, 4> > const& arg)
    {
        assert_vcl(arg.size() >= 4, "Insufficient size to initialize mat4");
        auto it_arg = arg.begin();
        for (size_t k1 = 0; k1 < 4; ++k1) {
            data.at_unsafe(k1) = *it_arg;
            ++it_arg;
        }
    }



    matrix_stack<float, 4, 4> matrix_stack<float, 4, 4>::identity()
    {
        return matrix_stack<float, 4, 4>{
            1.0f, 0.0f, 0.0f, 0.0f, 
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f};
    }

    size_t matrix_stack<float, 4, 4>::size() const { return 16;}
    size_t2 matrix_stack<float, 4, 4>::dimension() const { return {4,4}; }
    matrix_stack<float, 4, 4>& matrix_stack<float, 4, 4>::fill(float value)
    {
        auto it = begin();
        auto const it_end = end();
        for (; it != it_end; ++it)
            *it = value;
        return *this;
    }


    vec4 const& matrix_stack<float, 4, 4>::operator[](int k1) const{
        check_index_bounds(k1, *this);
        return at_unsafe(k1);
    } 
    vec4& matrix_stack<float, 4, 4>::operator[](int k1){
        check_index_bounds(k1, *this);
        return at_unsafe(k1);
    } 
    vec4 const& matrix_stack<float, 4, 4>::operator[](size_t k1) const{
        check_index_bounds(k1, *this);
        return at_unsafe(k1);
    } 
    vec4& matrix_stack<float, 4, 4>::operator[](size_t k1){
        check_index_bounds(k1, *this);
        return at_unsafe(k1);
    } 

    vec4 const& matrix_stack<float, 4, 4>::operator()(int k1) const{
        check_index_bounds(k1, *this);
        return at_unsafe(k1);
    } 
    vec4& matrix_stack<float, 4, 4>::operator()(int k1){
        check_index_bounds(k1, *this);
        return at_unsafe(k1);
    } 
    vec4 const& matrix_stack<float, 4, 4>::operator()(size_t k1) const{
        check_index_bounds(k1, *this);
        return at_unsafe(k1);
    } 
    vec4& matrix_stack<float, 4, 4>::operator()(size_t k1){
        check_index_bounds(k1, *this);
        return at_unsafe(k1);
    } 

    float const& matrix_stack<float, 4, 4>::operator()(int k1, int k2) const{
        check_index_bounds(k1, k2, *this);
        return at_unsafe(k1,k2);
    }
    float& matrix_stack<float, 4, 4>::operator()(int k1, int k2){
        check_index_bounds(k1, k2, *this);
        return at_unsafe(k1,k2);
    }
    float const& matrix_stack<float, 4, 4>::operator()(size_t k1, size_t k2) const{
        check_index_bounds(k1, k2, *this);
        return at_unsafe(k1,k2);
    }
    float& matrix_stack<float, 4, 4>::operator()(size_t k1, size_t k2){
        check_index_bounds(k1, k2, *this);
        return at_unsafe(k1,k2);
    }

    float const& matrix_stack<float, 4, 4>::at_offset(int offset) const{
        check_offset_bounds(offset, *this);
        return at_offset_unsafe(offset);
    }
    float& matrix_stack<float, 4, 4>::at_offset(int offset){
        check_offset_bounds(offset, *this);
        return at_offset_unsafe(offset);
    }
    float const& matrix_stack<float, 4, 4>::at_offset(size_t offset) const{
        check_offset_bounds(offset, *this);
        return at_offset_unsafe(offset);
    }
    float& matrix_stack<float, 4, 4>::at_offset(size_t offset){
        check_offset_bounds(offset, *this);
        return at_offset_unsafe(offset);
    }


    matrix_stack<float, 3, 3> matrix_stack<float, 4, 4>::remove_row_column(size_t idx1, size_t idx2) const
    {
        assert_vcl( (idx1 < 4) && (idx2 < 4), "Incorrect index for removing row and column to matrix");
        matrix_stack<float, 3, 3> res;

        size_t k1_res = 0;
        for (size_t k1 = 0; k1 < 4; ++k1) {
            if (k1 != idx1) {
                size_t k2_res = 0;
                for (size_t k2 = 0; k2 < 4; ++k2) {
                    if (k2 != idx2){
                        res.at_unsafe(k1_res, k2_res) = at_unsafe(k1, k2);
                        ++k2_res;
                    }
                }
                ++k1_res;
            }
        }

        return res;
    }
        





    float* matrix_stack<float,4,4>::begin() { return &at_unsafe(0,0); }
    float* matrix_stack<float,4,4>::end() { return &at_unsafe(3,3)+1; }
    float const* matrix_stack<float,4,4>::begin() const { return &at_unsafe(0,0); }
    float const* matrix_stack<float,4,4>::end() const { return &at_unsafe(3,3)+1; }
    float const* matrix_stack<float,4,4>::cbegin() const { return &at_unsafe(0,0); }
    float const* matrix_stack<float,4,4>::cend() const { return &at_unsafe(3,3)+1; }


    float const& matrix_stack<float,4,4>::at_unsafe(int k1, int k2) const { return data.at_unsafe(k1).at_unsafe(k2); }
    float& matrix_stack<float, 4, 4>::at_unsafe(int k1, int k2) {
        return data.at_unsafe(k1).at_unsafe(k2); }
    float const& matrix_stack<float,4,4>::at_unsafe(size_t k1, size_t k2) const { return data.at_unsafe(k1).at_unsafe(k2); }
    float& matrix_stack<float,4,4>::at_unsafe(size_t k1, size_t k2) { return data.at_unsafe(k1).at_unsafe(k2); }

    vec4 const& matrix_stack<float,4,4>::at_unsafe(int k1) const { return data.at_unsafe(k1); }
    vec4& matrix_stack<float,4,4>::at_unsafe(int k1) { return data.at_unsafe(k1); }
    vec4 const& matrix_stack<float,4,4>::at_unsafe(size_t k1) const { return data.at_unsafe(k1); }
    vec4& matrix_stack<float,4,4>::at_unsafe(size_t k1) { return data.at_unsafe(k1); }

    float const& matrix_stack<float,4,4>::at_offset_unsafe(int offset) const { return begin()[offset];}
    float& matrix_stack<float,4,4>::at_offset_unsafe(int offset) { return begin()[offset];}
    float const& matrix_stack<float,4,4>::at_offset_unsafe(size_t offset) const { return begin()[offset];}
    float& matrix_stack<float,4,4>::at_offset_unsafe(size_t offset) { return begin()[offset];}



    matrix_stack<float, 4, 4> matrix_stack<float, 4, 4>::affine(matrix_stack<float, 3, 3> const& L, vec3 const& T)
    {
        return mat4{ 
            get<0,0>(L), get<0,1>(L), get<0,2>(L), T.x, 
            get<1,0>(L), get<1,1>(L), get<1,2>(L), T.y, 
            get<2,0>(L), get<2,1>(L), get<2,2>(L), T.z, 
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }
    vec3 matrix_stack<float, 4, 4>::translation() const
    {
        return vec3{get<0,3>(*this), get<1,3>(*this), get<2,3>(*this)};
    }
    matrix_stack<float, 4, 4>& matrix_stack<float, 4, 4>::set_translation(vec3 const& tr)
    {
        get<0,3>(*this) = tr.x;
        get<1,3>(*this) = tr.y;
        get<2,3>(*this) = tr.z;
        return *this;
    }
}