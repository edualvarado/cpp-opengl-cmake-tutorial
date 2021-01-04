#pragma once

#include "vcl/base/base.hpp"
#include "../../buffer/buffer.hpp"
#include "../../buffer_stack/buffer_stack.hpp"
#include "vcl/containers/offset_grid/offset_grid.hpp"


/* ************************************************** */
/*           Header                                   */
/* ************************************************** */

namespace vcl
{

/** Container for 3D-grid like structure storing numerical element
*
* The grid_3D structure provide convenient access for 3D-grid organization where an element can be queried as grid_3D(i,j).
* Elements of grid_3D are stored contiguously in heap memory and remain fully compatible with std::vector and pointers.
**/
template <typename T>
struct grid_3D
{
    /** 3D dimension (Nx,Ny,Nz) of the container */
    size_t3 dimension;
    /** Internal storage as a 1D buffer */
    buffer<T> data;

    /** Constructors */
    grid_3D();
    grid_3D(size_t size);
    grid_3D(size_t3 const& size);
    grid_3D(size_t size_1, size_t size_2, size_t size_3);

    /** Direct build a grid_3D from a given 1D-buffer and its 3D-dimension
    * \note: the size of the 3D-buffer must satisfy arg.size = size_1 * size_2 * size_3 */
    static grid_3D<T> from_vector(buffer<T> const& arg, size_t size_1, size_t size_2, size_t size_3);

    /** Remove all elements from the grid_2D */
    void clear();
    /** Total number of elements size = dimension[0] * dimension[1] * dimension[2] */
    size_t size() const;
    /** Fill all elements of the grid_3D with the same element*/
    void fill(T const& value);

    /** Resizing grid_3D */
    void resize(size_t size); // Create a square grid_3D of dimension NxNXN
    void resize(size_t3 const& size);
    void resize(size_t size_1, size_t size_2, size_t size_3);
    
    /** Element access
     * Bound checking is performed unless VCL_NO_DEBUG is defined. */
    T const& operator[](int index) const;
    T& operator[](int index);            
    T const& operator()(int index) const;
    T& operator()(int index);

    T const& operator[](size_t const& index) const;
    T & operator[](size_t const& index);
    T const& operator()(size_t const& index) const;
    T & operator()(size_t const& index);

    T const& operator[](size_t3 const& index) const;
    T & operator[](size_t3 const& index);
    T const& operator()(size_t3 const& index) const;
    T & operator()(size_t3 const& index);

    T const& operator[](int3 const& index) const;
    T& operator[](int3 const& index);
    T const& operator()(int3 const& index) const;
    T& operator()(int3 const& index);

    T const& operator()(size_t k1, size_t k2, size_t k3) const;
    T & operator()(size_t k1, size_t k2, size_t k3);

    T const& operator()(int k1, int k2, int k3) const;
    T& operator()(int k1, int k2, int k3);

    typename std::vector<T>::iterator begin();
    typename std::vector<T>::iterator end();
    typename std::vector<T>::const_iterator begin() const;
    typename std::vector<T>::const_iterator end() const;
    typename std::vector<T>::const_iterator cbegin() const;
    typename std::vector<T>::const_iterator cend() const;
};

template <typename T> std::string type_str(grid_3D<T> const&);
template <typename T1, typename T2> bool is_equal(grid_3D<T1> const& a, grid_3D<T2> const& b);

template <typename T> std::ostream& operator<<(std::ostream& s, grid_3D<T> const& v);
template <typename T> std::string str(grid_3D<T> const& v, std::string const& separator=" ", std::string const& begin="", std::string const& end="");

template <typename T> grid_3D<T>& operator+=(grid_3D<T>& a, grid_3D<T> const& b);
template <typename T> grid_3D<T>& operator+=(grid_3D<T>& a, T const& b);
template <typename T> grid_3D<T>  operator+(grid_3D<T> const& a, grid_3D<T> const& b);
template <typename T> grid_3D<T>  operator+(grid_3D<T> const& a, T const& b);
template <typename T> grid_3D<T>  operator+(T const& a, grid_3D<T> const& b);

template <typename T> grid_3D<T>& operator-=(grid_3D<T>& a, grid_3D<T> const& b);
template <typename T> grid_3D<T>& operator-=(grid_3D<T>& a, T const& b);
template <typename T> grid_3D<T>  operator-(grid_3D<T> const& a, grid_3D<T> const& b);
template <typename T> grid_3D<T>  operator-(grid_3D<T> const& a, T const& b);
template <typename T> grid_3D<T>  operator-(T const& a, grid_3D<T> const& b);

template <typename T> grid_3D<T>& operator*=(grid_3D<T>& a, grid_3D<T> const& b);
template <typename T> grid_3D<T>& operator*=(grid_3D<T>& a, float b);
template <typename T> grid_3D<T>  operator*(grid_3D<T> const& a, grid_3D<T> const& b);
template <typename T> grid_3D<T>  operator*(grid_3D<T> const& a, float b);
template <typename T> grid_3D<T>  operator*(float a, grid_3D<T> const& b);

template <typename T> grid_3D<T>& operator/=(grid_3D<T>& a, grid_3D<T> const& b);
template <typename T> grid_3D<T>& operator/=(grid_3D<T>& a, float b);
template <typename T> grid_3D<T>  operator/(grid_3D<T> const& a, grid_3D<T> const& b);
template <typename T> grid_3D<T>  operator/(grid_3D<T> const& a, float b);
template <typename T> grid_3D<T>  operator/(float a, grid_3D<T> const& b);

}



/* ************************************************** */
/*           IMPLEMENTATION                           */
/* ************************************************** */

namespace vcl
{



template <typename T>
grid_3D<T>::grid_3D()
    :dimension(size_t3{0,0,0}),data()
{}

template <typename T>
grid_3D<T>::grid_3D(size_t size)
    :dimension({size,size,size}),data(size*size*size)
{}

template <typename T>
grid_3D<T>::grid_3D(size_t3 const& size)
    :dimension(size),data(size[0]*size[1]*size[2])
{}

template <typename T>
grid_3D<T>::grid_3D(size_t size_1, size_t size_2, size_t size_3)
    :dimension({size_1,size_2, size_3}),data(size_1*size_2*size_3)
{}

template <typename T>
size_t grid_3D<T>::size() const
{
    return dimension[0]*dimension[1]*dimension[2];
}

template <typename T>
void grid_3D<T>::resize(size_t size)
{
    resize(size,size,size);
}

template <typename T>
void grid_3D<T>::resize(size_t3 const& size)
{
    dimension = size;
    data.resize(size[0]*size[1]*size[2]);
}

template <typename T>
void grid_3D<T>::resize(size_t size_1, size_t size_2, size_t size_3)
{
    dimension = {size_1, size_2, size_3};
    resize({size_1, size_2, size_3});
}

template <typename T>
void grid_3D<T>::fill(T const& value)
{
    data.fill(value);
}






template <typename T> T const& grid_3D<T>::operator[](int index) const { return data[index]; }
template <typename T> T& grid_3D<T>::operator[](int index) { return data[index]; }
template <typename T> T const& grid_3D<T>::operator()(int index) const { return data[index]; }
template <typename T> T& grid_3D<T>::operator()(int index) { return data[index]; }

template <typename T>
T const& grid_3D<T>::operator[](size_t const& index) const
{
    return data[index];
}

template <typename T>
T & grid_3D<T>::operator[](size_t const& index)
{
    return data[index];
}

template <typename T>
T const& grid_3D<T>::operator()(size_t const& index) const
{
    return data[index];
}

template <typename T>
T & grid_3D<T>::operator()(size_t const& index)
{
    return data[index];
}



template <typename T, typename INDEX_TYPE>
void check_index_bounds(INDEX_TYPE index1, INDEX_TYPE index2, INDEX_TYPE index3, grid_3D<T> const& data)
{
#ifndef VCL_NO_DEBUG
    size_t const N1 = data.dimension.x;
    size_t const N2 = data.dimension.y;
    size_t const N3 = data.dimension.z;
    if (index1 < 0 || index2 < 0 || index3 < 0 || size_t(index1) >= N1 || size_t(index2) >= N2 || size_t(index3) >= N3)
    {
        std::string msg = "\n";

        msg += "\t> Try to access grid_3D(" + str(index1) + "," + str(index2) + "," + str(index3) + ")\n";
        msg += "\t>    - grid_3D has dimension = (" + str(N1) + "," + str(N2) + "," + str(N3) + ")\n";
        msg += "\t>    - Type of grid_3D: " + type_str(data) + "\n";

        if (index1 < 0 || index2 < 0 || index3 < 0)
        {
            msg += "\t> Buffer cannot be access with negative index.\n";
        }
        else if (N1 == 0 || N2 == 0 || N3 == 0)
        {
            msg += "\t> The buffer is empty, its elements cannot be accessed.\n";
        }
        else if (size_t(index1) == N1 || size_t(index2) == N2 || size_t(index3) == N3)
        {
            msg += "\t> Index reached the maximal size of the buffer \n";
            msg += "\t> The maximal possible indexes should be (" + str(N1 - 1) + "," + str(N2 - 1) + "," + str(N3 - 1) + ") \n";
        }
        else if (size_t(index1) >= N1 || size_t(index2) >= N2 || size_t(index3) >= N3)
        {
            msg += "\t> Exceeded buffer dimension \n";
        }


        msg += "\n\t  The function and variable that generated this error can be found in analysis the Call Stack.\n";

        error_vcl(msg);
    }
#endif
}



template <typename T>
T const& grid_3D<T>::operator[](size_t3 const& index) const
{
    check_index_bounds(index.x, index.y, index.z, *this);
    size_t const idx = offset_grid(index.x, index.y, index.z, dimension.x, dimension.y);
    return data[idx];
}

template <typename T>
T & grid_3D<T>::operator[](size_t3 const& index)
{
    check_index_bounds(index.x, index.y, index.z, *this);
    size_t const  idx = offset_grid(index.x, index.y, index.z, dimension.x, dimension.y);
    return data[idx];
}



template <typename T>
T const& grid_3D<T>::operator()(size_t3 const& index) const
{
    check_index_bounds(index.x, index.y, index.z, *this);
    size_t const  idx = offset_grid(index.x, index.y, index.z, dimension.x, dimension.y);
    return data[idx];
}

template <typename T>
T & grid_3D<T>::operator()(size_t3 const& index)
{
    check_index_bounds(index.x, index.y, index.z, *this);
    size_t const  idx = offset_grid(index.x, index.y, index.z, dimension.x, dimension.y);
    return data[idx];
}

template <typename T>
T const& grid_3D<T>::operator()(size_t k1, size_t k2, size_t k3) const
{
    check_index_bounds(k1, k2, k3, *this);
    size_t const  idx = offset_grid(k1, k2, k3, dimension.x, dimension.y);
    return data[idx];
}

template <typename T>
T & grid_3D<T>::operator()(size_t k1, size_t k2, size_t k3)
{
    check_index_bounds(k1, k2, k3, *this);
    size_t const  idx = offset_grid(k1, k2, k3, dimension.x, dimension.y);
    return data[idx];
}


template <typename T> T const& grid_3D<T>::operator[](int3 const& index) const
{
    check_index_bounds(index.x, index.y, index.z, *this);
    size_t const  idx = offset_grid(index.x, index.y, index.z, dimension.x, dimension.y);
    return data[idx];
}
template <typename T> T& grid_3D<T>::operator[](int3 const& index)
{
    check_index_bounds(index.x, index.y, index.z, *this);
    size_t const  idx = offset_grid(index.x, index.y, index.z, dimension.x, dimension.y);
    return data[idx];
}
template <typename T> T const& grid_3D<T>::operator()(int3 const& index) const
{
    check_index_bounds(index.x, index.y, index.z, *this);
    size_t const  idx = offset_grid(index.x, index.y, index.z, dimension.x, dimension.y);
    return data[idx];
}
template <typename T> T& grid_3D<T>::operator()(int3 const& index)
{
    check_index_bounds(index.x, index.y, index.z, *this);
    size_t const  idx = offset_grid(index.x, index.y, index.z, dimension.x, dimension.y);
    return data[idx];
}
template <typename T> T const& grid_3D<T>::operator()(int k1, int k2, int k3) const
{
    check_index_bounds(k1, k2, k3, *this);
    size_t const  idx = offset_grid(k1, k2, k3, dimension.x, dimension.y);
    return data[idx];
}
template <typename T> T& grid_3D<T>::operator()(int k1, int k2, int k3)
{
    check_index_bounds(k1, k2, k3, *this);
    size_t const  idx = offset_grid(k1, k2, k3, dimension.x, dimension.y);
    return data[idx];
}



template <typename T>
typename std::vector<T>::iterator grid_3D<T>::begin()
{
    return data.begin();
}

template <typename T>
typename std::vector<T>::iterator grid_3D<T>::end()
{
    return data.end();
}

template <typename T>
typename std::vector<T>::const_iterator grid_3D<T>::begin() const
{
    return data.begin();
}

template <typename T>
typename std::vector<T>::const_iterator grid_3D<T>::end() const
{
    return data.end();
}

template <typename T>
typename std::vector<T>::const_iterator grid_3D<T>::cbegin() const
{
    return data.cbegin();
}

template <typename T>
typename std::vector<T>::const_iterator grid_3D<T>::cend() const
{
    return data.cend();
}











template <typename T> std::string type_str(grid_3D<T> const&)
{
    return "grid_3D<" + type_str(T()) + ">";
}

template <typename T1, typename T2> bool is_equal(grid_3D<T1> const& a, grid_3D<T2> const& b)
{
    if (is_equal(a.dimension, b.dimension) == false)
        return false;
    return is_equal(a.data, b.data);
}


template <typename T> std::ostream& operator<<(std::ostream& s, grid_3D<T> const& v)
{
    return s << v.data;
}
template <typename T> std::string str(grid_3D<T> const& v, std::string const& separator, std::string const& begin, std::string const& end)
{
    return str(v.data, separator, begin, end);
}


template <typename T> grid_3D<T>& operator+=(grid_3D<T>& a, grid_3D<T> const& b)
{
    assert_vcl( is_equal(a.dimension,b.dimension), "Dimension do not agree: a:"+str(a.dimension)+", b:"+str(b.dimension) );
    a.data += b.data;
}
template <typename T> grid_3D<T>& operator+=(grid_3D<T>& a, T const& b)
{
    a.data += b;
}
template <typename T> grid_3D<T>  operator+(grid_3D<T> const& a, grid_3D<T> const& b)
{
    assert_vcl( is_equal(a.dimension,b.dimension), "Dimension do not agree: a:"+str(a.dimension)+", b:"+str(b.dimension) );
    grid_3D<T> res(a.dimension);
    res.data = a.data+b.data;
    return res;

}
template <typename T> grid_3D<T>  operator+(grid_3D<T> const& a, T const& b)
{
    grid_3D<T> res(a.dimension);
    res.data = a.data+b;
    return res;
}
template <typename T> grid_3D<T>  operator+(T const& a, grid_3D<T> const& b)
{
    grid_3D<T> res(b.dimension);
    res.data = a + b.data;
    return res;
}

template <typename T> grid_3D<T>& operator-=(grid_3D<T>& a, grid_3D<T> const& b)
{
    assert_vcl( is_equal(a.dimension,b.dimension), "Dimension do not agree: a:"+str(a.dimension)+", b:"+str(b.dimension) );
    a.data += b.data;
}
template <typename T> grid_3D<T>& operator-=(grid_3D<T>& a, T const& b)
{
    a.data -= b;
}
template <typename T> grid_3D<T>  operator-(grid_3D<T> const& a, grid_3D<T> const& b)
{
    assert_vcl( is_equal(a.dimension,b.dimension), "Dimension do not agree: a:"+str(a.dimension)+", b:"+str(b.dimension) );
    grid_3D<T> res(a.dimension);
    res.data = a.data-b.data;
    return res;
}
template <typename T> grid_3D<T>  operator-(grid_3D<T> const& a, T const& b)
{
    grid_3D<T> res(a.dimension);
    res.data = a.data-b;
    return res;
}
template <typename T> grid_3D<T>  operator-(T const& a, grid_3D<T> const& b)
{
    grid_3D<T> res(a.dimension);
    res.data = a-b.data;
    return res;
}

template <typename T> grid_3D<T>& operator*=(grid_3D<T>& a, grid_3D<T> const& b)
{
    assert_vcl( is_equal(a.dimension,b.dimension), "Dimension do not agree: a:"+str(a.dimension)+", b:"+str(b.dimension) );
    a.data *= b.data;
}
template <typename T> grid_3D<T>& operator*=(grid_3D<T>& a, float b)
{
    a.data *= b;
}
template <typename T> grid_3D<T>  operator*(grid_3D<T> const& a, grid_3D<T> const& b)
{
    assert_vcl( is_equal(a.dimension,b.dimension), "Dimension do not agree: a:"+str(a.dimension)+", b:"+str(b.dimension) );
    grid_3D<T> res(a.dimension);
    res.data = a.data*b.data;
    return res;
}
template <typename T> grid_3D<T>  operator*(grid_3D<T> const& a, float b)
{
    grid_3D<T> res(a.dimension);
    res.data = a.data*b;
    return res;
}
template <typename T> grid_3D<T>  operator*(float a, grid_3D<T> const& b)
{
    grid_3D<T> res(b.dimension);
    res.data = a*b.data;
    return res;
}

template <typename T> grid_3D<T>& operator/=(grid_3D<T>& a, grid_3D<T> const& b)
{
    assert_vcl( is_equal(a.dimension,b.dimension), "Dimension do not agree: a:"+str(a.dimension)+", b:"+str(b.dimension) );
    a.data /= b.data;
}
template <typename T> grid_3D<T>& operator/=(grid_3D<T>& a, float b)
{
    a.data /= b;
}
template <typename T> grid_3D<T>  operator/(grid_3D<T> const& a, grid_3D<T> const& b)
{
    assert_vcl( is_equal(a.dimension,b.dimension), "Dimension do not agree: a:"+str(a.dimension)+", b:"+str(b.dimension) );
    grid_3D<T> res(a.dimension);
    res.data = a.data/b.data;
    return res;
}
template <typename T> grid_3D<T>  operator/(grid_3D<T> const& a, float b)
{
    grid_3D<T> res(a.dimension);
    res.data = a.data/b;
    return res;
}
template <typename T> grid_3D<T>  operator/(float a, grid_3D<T> const& b)
{
    grid_3D<T> res(b.dimension);
    res.data = a/b.data;
    return res;
}



}
