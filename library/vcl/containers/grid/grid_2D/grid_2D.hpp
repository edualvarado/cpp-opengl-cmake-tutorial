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

/** Container for 2D-grid like structure storing numerical element
 *
 * The grid_2D structure provide convenient access for 2D-grid organization where an element can be queried as grid_2D(i,j).
 * Elements of grid_2D are stored contiguously in heap memory and remain fully compatible with std::vector and pointers.
 **/
template <typename T>
struct grid_2D
{
    /** 2D dimension (Nx,Ny) of the container */
    size_t2 dimension;
    /** Internal storage as a 1D buffer */
    buffer<T> data;

    /** Constructors */
    grid_2D();                              // Empty buffer - no elements
    grid_2D(size_t size);                   // Build a grid_2D of squared dimension (size,size)
    grid_2D(size_t2 const& size);           // Build a grid_2D with specified dimension
    grid_2D(size_t size_1, size_t size_2);  // Build a grid_2D with specified dimension

    /** Direct build a grid_2D from a given 1D-buffer and its 2D-dimension
    * \note: the size of the 1D-buffer must satisfy arg.size = size_1 * size_2 */
    static grid_2D<T> from_buffer(buffer<T> const& arg, size_t size_1, size_t size_2);


    /** Remove all elements from the grid_2D */
    void clear();
    /** Total number of elements size = dimension[0] * dimension[1] */
    size_t size() const;
    /** Fill all elements of the grid_2D with the same element*/
    void fill(T const& value);

    /** Resizing grid_2D */
    void resize(size_t size);         // Create a squared grid_2D of dimension (size,size) 
    void resize(size_t2 const& size);
    void resize(size_t size_1, size_t size_2);

    /** Element access
     * Bound checking is performed unless VCL_NO_DEBUG is defined. */
    T const& operator[](int index) const; // Index as an offset in the 1D structure
    T& operator[](int index);            // Index as an offset in the 1D structure
    T const& operator()(int index) const; // Index as an offset in the 1D structure
    T& operator()(int index);            // Index as an offset in the 1D structure

    T const& operator[](size_t index) const; // Index as an offset in the 1D structure
    T & operator[](size_t index);            // Index as an offset in the 1D structure
    T const& operator()(size_t index) const; // Index as an offset in the 1D structure
    T & operator()(size_t index);            // Index as an offset in the 1D structure

    T const& operator[](int2 const& index) const; // grid_2D[ {x,y} ]
    T & operator[](int2 const& index);            // grid_2D[ {x,y} ]
    T const& operator()(int2 const& index) const; // grid_2D( {x,y} )
    T & operator()(int2 const& index);            // grid_2D( {x,y} )

    T const& operator[](size_t2 const& index) const; // grid_2D[ {x,y} ]
    T& operator[](size_t2 const& index);            // grid_2D[ {x,y} ]
    T const& operator()(size_t2 const& index) const; // grid_2D( {x,y} )
    T& operator()(size_t2 const& index);            // grid_2D( {x,y} )

    T const& operator()(int k1, int k2) const; // grid_2D(x, y) 
    T& operator()(int k1, int k2);            // grid_2D(x, y) 
    T const& operator()(size_t k1, size_t k2) const; // grid_2D(x, y)
    T & operator()(size_t k1, size_t k2);            // grid_2D(x, y)


    size_t index_to_offset(int k1, int k2) const;
    int2 offset_to_index(size_t offset) const;

    /** Iterators
     * 1D-type iterators on grid_2D are compatible with STL syntax
     * allows "forall" loops (for(auto& e : buffer) {...}) */
    typename std::vector<T>::iterator begin();
    typename std::vector<T>::iterator end();
    typename std::vector<T>::const_iterator begin() const;
    typename std::vector<T>::const_iterator end() const;
    typename std::vector<T>::const_iterator cbegin() const;
    typename std::vector<T>::const_iterator cend() const;



};


template <typename T> std::string type_str(grid_2D<T> const&);

/** Display all elements of the buffer.*/
template <typename T> std::ostream& operator<<(std::ostream& s, grid_2D<T> const& v);

/** Convert all elements of the buffer to a string.
 * \param buffer: the input buffer
 * \param separator: the separator between each element
 */
template <typename T> std::string str(grid_2D<T> const& v, std::string const& separator=" ", std::string const& begin = "", std::string const& end = "");


/** Equality test between grid_2D */
template <typename T1, typename T2> bool is_equal(grid_2D<T1> const& a, grid_2D<T2> const& b);

/** Math operators
 * Common mathematical operations between buffers, and scalar or element values. */
template <typename T> grid_2D<T>& operator+=(grid_2D<T>& a, grid_2D<T> const& b);

template <typename T> grid_2D<T>& operator+=(grid_2D<T>& a, T const& b);
template <typename T> grid_2D<T>  operator+(grid_2D<T> const& a, grid_2D<T> const& b);
template <typename T> grid_2D<T>  operator+(grid_2D<T> const& a, T const& b);
template <typename T> grid_2D<T>  operator+(T const& a, grid_2D<T> const& b);

template <typename T> grid_2D<T>& operator-=(grid_2D<T>& a, grid_2D<T> const& b);
template <typename T> grid_2D<T>& operator-=(grid_2D<T>& a, T const& b);
template <typename T> grid_2D<T>  operator-(grid_2D<T> const& a, grid_2D<T> const& b);
template <typename T> grid_2D<T>  operator-(grid_2D<T> const& a, T const& b);
template <typename T> grid_2D<T>  operator-(T const& a, grid_2D<T> const& b);

template <typename T> grid_2D<T>& operator*=(grid_2D<T>& a, grid_2D<T> const& b);
template <typename T> grid_2D<T>& operator*=(grid_2D<T>& a, float b);
template <typename T> grid_2D<T>  operator*(grid_2D<T> const& a, grid_2D<T> const& b);
template <typename T> grid_2D<T>  operator*(grid_2D<T> const& a, float b);
template <typename T> grid_2D<T>  operator*(float a, grid_2D<T> const& b);

template <typename T> grid_2D<T>& operator/=(grid_2D<T>& a, grid_2D<T> const& b);
template <typename T> grid_2D<T>& operator/=(grid_2D<T>& a, float b);
template <typename T> grid_2D<T>  operator/(grid_2D<T> const& a, grid_2D<T> const& b);
template <typename T> grid_2D<T>  operator/(grid_2D<T> const& a, float b);



}



/* ************************************************** */
/*           IMPLEMENTATION                           */
/* ************************************************** */

namespace vcl
{



template <typename T>
grid_2D<T>::grid_2D()
    :dimension(size_t2{0,0}),data()
{}

template <typename T>
grid_2D<T>::grid_2D(size_t size)
    :dimension({size,size}),data(size*size)
{}

template <typename T>
grid_2D<T>::grid_2D(size_t2 const& size)
    :dimension(size),data(size[0]*size[1])
{}

template <typename T>
grid_2D<T>::grid_2D(size_t size_1, size_t size_2)
    :dimension({size_1,size_2}),data(size_1*size_2)
{}



template <typename T>
size_t grid_2D<T>::size() const
{
    return dimension[0]*dimension[1];
}

template <typename T>
void grid_2D<T>::clear()
{
    resize(0, 0);
}

template <typename T>
void grid_2D<T>::resize(size_t size)
{
    resize(size,size);
}

template <typename T>
void grid_2D<T>::resize(size_t2 const& size)
{
    dimension = size;
    data.resize(size[0]*size[1]);
}

template <typename T>
void grid_2D<T>::resize(size_t size_1, size_t size_2)
{
    dimension = {size_1,size_2};
    resize({size_1,size_2});
}

template <typename T>
void grid_2D<T>::fill(T const& value)
{
    data.fill(value);
}


template <typename T>
T const& grid_2D<T>::operator[](int index) const
{
    return data[index];
}

template <typename T>
T& grid_2D<T>::operator[](int index)
{
    return data[index];
}

template <typename T>
T const& grid_2D<T>::operator()(int index) const
{
    return data[index];
}

template <typename T>
T& grid_2D<T>::operator()(int index)
{
    return data[index];
}

template <typename T>
T const& grid_2D<T>::operator[](size_t index) const
{
    return data[index];
}

template <typename T>
T & grid_2D<T>::operator[](size_t index)
{
    return data[index];
}

template <typename T>
T const& grid_2D<T>::operator()(size_t index) const
{
    return data[index];
}

template <typename T>
T & grid_2D<T>::operator()(size_t index)
{
    return data[index];
}




template <typename T, typename INDEX_TYPE>
void check_index_bounds(INDEX_TYPE index1, INDEX_TYPE index2, grid_2D<T> const& data)
{
#ifndef VCL_NO_DEBUG
    size_t const N1 = data.dimension.x;
    size_t const N2 = data.dimension.y;
    if (index1 < 0 || index2<0 || size_t(index1)>=N1 || size_t(index2)>=N2)
    {
        std::string msg = "\n";

        msg += "\t> Try to access grid_2D(" + str(index1) + "," + str(index2) + ")\n";
        msg += "\t>    - grid_2D has dimension = (" + str(N1) + "," + str(N2) + ")\n";
        msg += "\t>    - Type of grid_2D: "+type_str(data)+"\n";

        if (index1<0 || index2<0)
        {
            msg += "\t> Buffer cannot be access with negative index.\n";
        }
        else if (N1==0 || N2==0)
        {
            msg += "\t> The buffer is empty, its elements cannot be accessed.\n";
        }
        else if (size_t(index1)==N1 || size_t(index2)==N2)
        {
            msg += "\t> Index reached the maximal size of the buffer \n";
            msg += "\t> The maximal possible indexes should be (" + str(N1-1) + ","+ str(N2 - 1) +") \n";
        }
        else if (size_t(index1)>=N1 || size_t(index2)>=N2)
        {
            msg += "\t> Exceeded buffer dimension \n";
        }


        msg += "\n\t  The function and variable that generated this error can be found in analysis the Call Stack.\n";

        error_vcl(msg);
    }
#endif
}



template <typename T>
T const& grid_2D<T>::operator[](int2 const& index) const
{
    check_index_bounds(index.x, index.y, *this);
    size_t const idx = offset_grid(index.x, index.y, dimension.x);
    return data[idx];
}

template <typename T>
T& grid_2D<T>::operator[](int2 const& index)
{
    check_index_bounds(index.x, index.y, *this);
    size_t const idx = offset_grid(index.x, index.y, dimension.x);

    return data[idx];
}





template <typename T>
T const& grid_2D<T>::operator[](size_t2 const& index) const
{
    check_index_bounds(index.x, index.y, *this);
    size_t const idx = offset_grid(index.x, index.y, dimension.x);

    return data[idx];
}

template <typename T>
T & grid_2D<T>::operator[](size_t2 const& index)
{
    check_index_bounds(index.x, index.y, *this);
    size_t const idx = offset_grid(index.x, index.y, dimension.x);

    return data[idx];
}



template <typename T>
T const& grid_2D<T>::operator()(size_t2 const& index) const
{
    check_index_bounds(index.x, index.y, *this);
    size_t idx = offset_grid(index.x, index.y, dimension.x);

    return data[idx];
}

template <typename T>
T & grid_2D<T>::operator()(size_t2 const& index)
{
    check_index_bounds(index.x, index.y, *this);
    size_t const idx = offset_grid(index.x, index.y, dimension.x);

    return data[idx];
}

template <typename T>
T const& grid_2D<T>::operator()(size_t k1, size_t k2) const
{
    check_index_bounds(k1, k2, *this);
    size_t const idx = offset_grid(k1, k2, dimension.x);

    return data[idx];
}

template <typename T>
T & grid_2D<T>::operator()(size_t k1, size_t k2)
{
    check_index_bounds(k1, k2, *this);
    size_t const idx = offset_grid(k1, k2, dimension.x);

    return data[idx];
}

template <typename T>
T const& grid_2D<T>::operator()(int k1, int k2) const
{
    check_index_bounds(k1, k2, *this);
    size_t const idx = offset_grid(k1, k2, dimension.x);

    return data[idx];
}

template <typename T>
T& grid_2D<T>::operator()(int k1, int k2)
{
    check_index_bounds(k1, k2, *this);
    size_t const idx = offset_grid(k1, k2, dimension.x);

    return data[idx];
}




template <typename T>
typename std::vector<T>::iterator grid_2D<T>::begin()
{
    return data.begin();
}

template <typename T>
typename std::vector<T>::iterator grid_2D<T>::end()
{
    return data.end();
}

template <typename T>
typename std::vector<T>::const_iterator grid_2D<T>::begin() const
{
    return data.begin();
}

template <typename T>
typename std::vector<T>::const_iterator grid_2D<T>::end() const
{
    return data.end();
}

template <typename T>
typename std::vector<T>::const_iterator grid_2D<T>::cbegin() const
{
    return data.cbegin();
}

template <typename T>
typename std::vector<T>::const_iterator grid_2D<T>::cend() const
{
    return data.cend();
}










template <typename T> std::string type_str(grid_2D<T> const&)
{
    return "grid_2D<" + type_str(T()) + ">";
}


template <typename T1, typename T2> bool is_equal(grid_2D<T1> const& a, grid_2D<T2> const& b)
{
    if (is_equal(a.dimension, b.dimension)==false)
        return false;
    return is_equal(a.data, b.data);
}




template <typename T> std::ostream& operator<<(std::ostream& s, grid_2D<T> const& v)
{
    return s << v.data;
}
template <typename T> std::string str(grid_2D<T> const& v, std::string const& separator, std::string const& begin, std::string const& end)
{
    return to_string(v.data, separator, begin, end);
}


template <typename T> grid_2D<T>& operator+=(grid_2D<T>& a, grid_2D<T> const& b)
{
    assert_vcl( is_equal(a.dimension,b.dimension), "Dimension do not agree: a:"+str(a.dimension)+", b:"+str(b.dimension) );
    a.data += b.data;
}
template <typename T> grid_2D<T>& operator+=(grid_2D<T>& a, T const& b)
{
    a.data += b;
}
template <typename T> grid_2D<T>  operator+(grid_2D<T> const& a, grid_2D<T> const& b)
{
    assert_vcl( is_equal(a.dimension,b.dimension), "Dimension do not agree: a:"+str(a.dimension)+", b:"+str(b.dimension) );
    grid_2D<T> res(a.dimension);
    res.data = a.data+b.data;
    return res;

}
template <typename T> grid_2D<T>  operator+(grid_2D<T> const& a, T const& b)
{
    grid_2D<T> res(a.dimension);
    res.data = a.data+b;
    return res;
}
template <typename T> grid_2D<T>  operator+(T const& a, grid_2D<T> const& b)
{
    grid_2D<T> res(b.dimension);
    res.data = a + b.data;
    return res;
}

template <typename T> grid_2D<T>& operator-=(grid_2D<T>& a, grid_2D<T> const& b)
{
    assert_vcl( is_equal(a.dimension,b.dimension), "Dimension do not agree: a:"+str(a.dimension)+", b:"+str(b.dimension) );
    a.data += b.data;
}
template <typename T> grid_2D<T>& operator-=(grid_2D<T>& a, T const& b)
{
    a.data -= b;
}
template <typename T> grid_2D<T>  operator-(grid_2D<T> const& a, grid_2D<T> const& b)
{
    assert_vcl( is_equal(a.dimension,b.dimension), "Dimension do not agree: a:"+str(a.dimension)+", b:"+str(b.dimension) );
    grid_2D<T> res(a.dimension);
    res.data = a.data-b.data;
    return res;
}
template <typename T> grid_2D<T>  operator-(grid_2D<T> const& a, T const& b)
{
    grid_2D<T> res(a.dimension);
    res.data = a.data-b;
    return res;
}
template <typename T> grid_2D<T>  operator-(T const& a, grid_2D<T> const& b)
{
    grid_2D<T> res(a.dimension);
    res.data = a-b.data;
    return res;
}

template <typename T> grid_2D<T>& operator*=(grid_2D<T>& a, grid_2D<T> const& b)
{
    assert_vcl( is_equal(a.dimension,b.dimension), "Dimension do not agree: a:"+str(a.dimension)+", b:"+str(b.dimension) );
    a.data *= b.data;
}
template <typename T> grid_2D<T>& operator*=(grid_2D<T>& a, float b)
{
    a.data *= b;
}
template <typename T> grid_2D<T>  operator*(grid_2D<T> const& a, grid_2D<T> const& b)
{
    assert_vcl( is_equal(a.dimension,b.dimension), "Dimension do not agree: a:"+str(a.dimension)+", b:"+str(b.dimension) );
    grid_2D<T> res(a.dimension);
    res.data = a.data*b.data;
    return res;
}
template <typename T> grid_2D<T>  operator*(grid_2D<T> const& a, float b)
{
    grid_2D<T> res(a.dimension);
    res.data = a.data*b;
    return res;
}
template <typename T> grid_2D<T>  operator*(float a, grid_2D<T> const& b)
{
    grid_2D<T> res(b.dimension);
    res.data = a*b.data;
    return res;
}

template <typename T> grid_2D<T>& operator/=(grid_2D<T>& a, grid_2D<T> const& b)
{
    assert_vcl( is_equal(a.dimension,b.dimension), "Dimension do not agree: a:"+str(a.dimension)+", b:"+str(b.dimension) );
    a.data /= b.data;
}
template <typename T> grid_2D<T>& operator/=(grid_2D<T>& a, float b)
{
    a.data /= b;
}
template <typename T> grid_2D<T>  operator/(grid_2D<T> const& a, grid_2D<T> const& b)
{
    assert_vcl( is_equal(a.dimension,b.dimension), "Dimension do not agree: a:"+str(a.dimension)+", b:"+str(b.dimension) );
    grid_2D<T> res(a.dimension);
    res.data = a.data/b.data;
    return res;
}
template <typename T> grid_2D<T>  operator/(grid_2D<T> const& a, float b)
{
    grid_2D<T> res(a.dimension);
    res.data = a.data/b;
    return res;
}


template <typename T>
grid_2D<T> grid_2D<T>::from_buffer(buffer<T> const& arg, size_t size_1, size_t size_2)
{
    assert_vcl(arg.size()==size_1*size_2, "Incoherent size to generate grid_2D");

    grid_2D<T> b(size_1, size_2);
    b.data = arg;

    return b;
}

template <typename T>
size_t grid_2D<T>::index_to_offset(int k1, int k2) const
{
    return offset_grid(k1,k2,dimension.x);
}
template <typename T>
int2 grid_2D<T>::offset_to_index(size_t offset) const
{
    auto idx = index_grid_from_offset(offset,dimension.x);
    return {idx.first, idx.second};
}


}
