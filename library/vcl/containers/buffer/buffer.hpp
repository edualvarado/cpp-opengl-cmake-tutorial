#pragma once

#include "vcl/base/base.hpp"

#include <vector>
#include <iostream>

/* ************************************************** */
/*           Header                                   */
/* ************************************************** */

namespace vcl
{

/** Dynamic-sized container for numerical data
 *
 * The buffer structure is a wrapper around an std::vector with additional convenient functionalities
 * - Overloaded operators + - * / as well as common outputs
 * - Strict bound checking with operator [] and () (unless VCL_NO_DEBUG is defined)
 *
 * Buffer follows the main syntax than std::vector
 * Elements in a buffer sotred contiguously in memory (use std::vector internally)
 *
 **/
template <typename T>
struct buffer
{
    /** Internal data stored as std::vector */
    std::vector<T> data;

    // Constructors
    buffer();                             // Empty buffer - no elements 
    buffer(size_t size);                  // Buffer with a given size 
    buffer(std::initializer_list<T> arg); // Inline initialization using { } 
    buffer(std::vector<T> const& arg);    // Direct initialization from std::vector 

    /** Similar to matlab linespace 
    * Linear interpolation between p1 and p2 along N variable */
    static buffer<T> linespace(T const& p1, T const& p2, size_t N);

    /** Container size similar to vector.size() */
    size_t size() const;
    /** Resize container to a new size (similar to vector.resize()) */
    buffer<T>& resize(size_t size);
    /** Resize container to a new size, and clear it initialy to delete previous values */
    buffer<T>& resize_clear(size_t size);
    /** Add an element at the end of the container (similar to vector.push_back()) */
    buffer<T>& push_back(T const& value);
    /** Add an buffer of elements at the end of the container */
    buffer<T>& push_back(buffer<T> const& value);
    /** Remove all elements of the container, new size is 0 (similar to vector.clear()) */
    buffer<T>& clear();
    /** Fill the container with the same element (from index 0 to size-1) */
    buffer<T>& fill(T const& value);

    /** Element access
     * Allows buffer[i], buffer(i), and buffer.at(i)
     * Bound checking is performed unless VCL_NO_DEBUG is defined. */
    T const& operator[](int index) const;
    T& operator[](int index);
    T const& operator()(int index) const;
    T& operator()(int index);

    T const& operator[](unsigned int index) const;
    T & operator[](unsigned int index);
    T const& operator()(unsigned int index) const;
    T & operator()(unsigned int index);

    T const& operator[](size_t index) const;
    T & operator[](size_t index);
    T const& operator()(size_t index) const;
    T & operator()(size_t index);

    T const& at(size_t index) const; // Internal call to std::vector.at
    T & at(size_t index);            // Internal call to std::vector.at

    /** Iterators
     * Iterators on buffer are compatible with STL syntax
     * allows "forall" loops (for(auto& e : buffer) {...}) */
    typename std::vector<T>::iterator begin();
    typename std::vector<T>::iterator end();
    typename std::vector<T>::const_iterator begin() const;
    typename std::vector<T>::const_iterator end() const;
    typename std::vector<T>::const_iterator cbegin() const;
    typename std::vector<T>::const_iterator cend() const;
};

template <typename T> std::string type_str(buffer<T> const&);

/** Display all elements of the buffer.*/
template <typename T> std::ostream& operator<<(std::ostream& s, buffer<T> const& v);

/** Convert all elements of the buffer to a string.
 * \param buffer: the input buffer
 * \param separator: the separator between each element 
 * \param begin/end: character added in the beginning/end of the display
 */
template <typename T> std::string str(buffer<T> const& v, std::string const& separator=" ", std::string const& begin="", std::string const& end="");

template <typename T> size_t size_in_memory(buffer<T> const& v);
template <typename T> auto const* ptr(buffer<T> const& v);

/** Equality check
 * Check equality (element by element) between two buffers.
 * Buffers with different size are always considered as not equal.
 * Only approximated equality is performed for comprison with float (absolute value between floats) */
template <typename T> bool is_equal(buffer<T> const& a, buffer<T> const& b);
/** Allows to check value equality between different type (float and int for instance). */
template <typename T1, typename T2> bool is_equal(buffer<T1> const& a, buffer<T2> const& b);


template <typename T> T max(buffer<T> const& v);
template <typename T> T min(buffer<T> const& v);


/** Compute average value of all elements of the buffer.*/
template <typename T> T average(buffer<T> const& a);


/** Math operators
 * Common mathematical operations between buffers, and scalar or element values. */

template <typename T> buffer<T>  operator-(buffer<T> const& a);

template <typename T> buffer<T>& operator+=(buffer<T>& a, buffer<T> const& b);
template <typename T> buffer<T>& operator+=(buffer<T>& a, T const& b);
template <typename T> buffer<T>  operator+(buffer<T> const& a, buffer<T> const& b);
template <typename T> buffer<T>  operator+(buffer<T> const& a, T const& b); // Componentwise sum: a[i]+b 
template <typename T> buffer<T>  operator+(T const& a, buffer<T> const& b); // Componentwise sum: a+b[i]

template <typename T> buffer<T>& operator-=(buffer<T>& a, buffer<T> const& b);
template <typename T> buffer<T>& operator-=(buffer<T>& a, T const& b);
template <typename T> buffer<T>  operator-(buffer<T> const& a, buffer<T> const& b);
template <typename T> buffer<T>  operator-(buffer<T> const& a, T const& b); // Componentwise substraction: a[i]-b 
template <typename T> buffer<T>  operator-(T const& a, buffer<T> const& b); // Componentwise substraction: a-b[i] 

template <typename T> buffer<T>& operator*=(buffer<T>& a, buffer<T> const& b);
template <typename T> buffer<T>  operator*(buffer<T> const& a, buffer<T> const& b);
template <typename T> buffer<T>& operator*=(buffer<T>& a, float b);
template <typename T> buffer<T>  operator*(buffer<T> const& a, float b);
template <typename T> buffer<T>  operator*(float a, buffer<T> const& b);

template <typename T> buffer<T>& operator/=(buffer<T>& a, buffer<T> const& b);
template <typename T> buffer<T>& operator/=(buffer<T>& a, float b);
template <typename T> buffer<T>  operator/(buffer<T> const& a, buffer<T> const& b);
template <typename T> buffer<T>  operator/(buffer<T> const& a, float b);


}



/* ************************************************** */
/*           IMPLEMENTATION                           */
/* ************************************************** */

namespace vcl
{

template <typename T>
buffer<T>::buffer()
    :data()
{}

template <typename T>
buffer<T>::buffer(size_t size)
    :data(size)
{}

template <typename T>
buffer<T>::buffer(std::initializer_list<T> arg)
    :data(arg)
{}

template <typename T>
buffer<T>::buffer(const std::vector<T>& arg)
    :data(arg)
{}

template <typename T>
size_t buffer<T>::size() const
{
    return data.size();
}

template <typename T>
buffer<T>& buffer<T>::resize(size_t size)
{
    data.resize(size);
    return *this;
}

template <typename T>
buffer<T>& buffer<T>::resize_clear(size_t size)
{
    clear();
    resize(size);
    return *this;
}

template <typename T>
buffer<T>& buffer<T>::push_back(T const& value)
{
    data.push_back(value);
    return *this;
}

template <typename T>
buffer<T>& buffer<T>::push_back(buffer<T> const& value)
{
    for(T const& element : value)
        data.push_back(element);
    return *this;
}

template <typename T>
buffer<T>& buffer<T>::clear()
{
    data.clear();
    return *this;
}

template <typename T>
buffer<T>& buffer<T>::fill(T const& value)
{
    size_t const N = size();
    for (size_t k = 0; k < N; ++k)
        data[k] = value;
    return *this;
}

template <typename T> std::string type_str(buffer<T> const&)
{
    using vcl::type_str;
    return "buffer<" + type_str(T()) + ">";
}



template <typename T, typename INDEX_TYPE>
void check_index_bounds(INDEX_TYPE index, buffer<T> const& data)
{
#ifndef VCL_NO_DEBUG
    size_t const N = data.size();
    if (index < 0 || size_t(index) >= N)
    {
        std::string msg = "\n";

        if (index < 0)
        {
            msg += "\t> Try to access buffer[" + str(index) + "]\n";
            msg += "\t> Buffer cannot be access with negative index.\n";
            msg += "\t  Extra information:\n";
            msg += "\t    - Size of the buffer: " + str(data.size()) + "\n";
            msg += "\t    - Index value: " + str(index) + "\n";
            msg += "\t    - Buffer type: " + type_str(data) + "\n";
            msg += "\t  Help: \n";
            msg += "\t     C++ is not Python, negative indexing doesn't target the end of the buffer. \n";
            msg += "\t     Buffers of data cannot be accessed with negative index. \n";
        }
        else if (N == 0)
        {
            msg += "\t> Try to access buffer[" + str(index) + "]\n";
            msg += "\t> But the buffer (" + type_str(data) + ") is empty. Its elements cannot be accessed.\n";
            msg += "\t  Help: \n";
            msg += "\t     You may have forgotten to intialize the size of this buffer: \n";
            msg += "\t     - use buffer.resize(N) before its use \n";
            msg += "\t     - or use buffer.push_back(element) to add new elements to it \n";
        }
        else if (size_t(index) == N)
        {
            msg += "\t> Try to access buffer[" + str(index) + "] for a buffer of size=" + str(data.size()) + "\n";
            msg += "\t> Index reached the maximal size of the buffer \n";
            msg += "\t> The maximal possible index should be " + str(data.size() - 1) + " \n";
            msg += "\t  Extra information:\n";
            msg += "\t    - Buffer type: " + type_str(data) + "\n";
            msg += "\t  Help: \n";
            msg += "\t     C++ has index starting at 0. \n";
            msg += "\t     Typical loops should go from index=0 to index<buffer.size(). \n";
        }
        else if (size_t(index) >= N)
        {
            msg += "\t> Try to access buffer[" + str(index) + "] for a size=" + str(data.size()) + "\n";
            msg += "\t> Buffer has a size=" + str(data.size()) + ": The index (" + str(index) + ") should be < " + str(data.size()) + "\n";
            msg += "\t  Extra information:\n";
            msg += "\t    - Buffer type: " + type_str(data) + "\n";
        }


        msg += "\t  The function and variable that generated this error can be found in analysis the Call Stack.\n";

        error_vcl(msg);
    }
#endif
}

template <typename T>
T const& buffer<T>::operator[](int index) const
{
    check_index_bounds(index, *this);
    return data[index];
}

template <typename T>
T& buffer<T>::operator[](int index)
{
    check_index_bounds(index, *this);
    return data[index];
}

template <typename T>
T const& buffer<T>::operator()(int index) const
{
    check_index_bounds(index, *this);
    return data[index];
}

template <typename T>
T& buffer<T>::operator()(int index)
{
    check_index_bounds(index, *this);
    return data[index];
}

template <typename T>
T const& buffer<T>::operator[](unsigned int index) const
{
    check_index_bounds(index, *this);
    return data[index];
}

template <typename T>
T & buffer<T>::operator[](unsigned int index)
{
    check_index_bounds(index, *this);
    return data[index];
}

template <typename T>
T const& buffer<T>::operator()(unsigned int index) const
{
    check_index_bounds(index, *this);
    return data[index];
}

template <typename T>
T & buffer<T>::operator()(unsigned int index)
{
    check_index_bounds(index, *this);
    return data[index];
}



template <typename T>
T const& buffer<T>::operator[](size_t index) const
{
    check_index_bounds(index, *this);
    return data[index];
}
template <typename T>
T & buffer<T>::operator[](size_t index)
{
    check_index_bounds(index, *this);
    return data[index];
}

template <typename T>
T const& buffer<T>::operator()(size_t index) const
{
    check_index_bounds(index, *this);
    return data[index];
}

template <typename T>
T & buffer<T>::operator()(size_t index)
{
    check_index_bounds(index, *this);
    return data[index];
}

template <typename T>
T const& buffer<T>::at(size_t index) const
{
    return data.at(index);
}

template <typename T>
T & buffer<T>::at(size_t index)
{
    return data.at(index);
}



template <typename T>
typename std::vector<T>::iterator buffer<T>::begin()
{
    return data.begin();
}

template <typename T>
typename std::vector<T>::iterator buffer<T>::end()
{
    return data.end();
}

template <typename T>
typename std::vector<T>::const_iterator buffer<T>::begin() const
{
    return data.begin();
}

template <typename T>
typename std::vector<T>::const_iterator buffer<T>::end() const
{
    return data.end();
}

template <typename T>
typename std::vector<T>::const_iterator buffer<T>::cbegin() const
{
    return data.cbegin();
}

template <typename T>
typename std::vector<T>::const_iterator buffer<T>::cend() const
{
    return data.cend();
}


template <typename T> std::ostream& operator<<(std::ostream& s, buffer<T> const& v)
{
    std::string const s_out = str(v);
    s << s_out;
    return s;
}
template <typename T> std::string str(buffer<T> const& v, std::string const& separator, std::string const& begin, std::string const& end)
{
    return vcl::detail::str_container(v, separator, begin, end);
}

template <typename T> size_t size_in_memory(buffer<T> const& v)
{
    size_t s = 0;
    size_t const N = v.size();
    for (size_t k = 0; k < N; ++k)
        s += vcl::size_in_memory(v[k]);
    return s;
}

template <typename T> T average(buffer<T> const& a)
{
    size_t const N = a.size();
    assert_vcl(N>0, "Cannot compute average on empty buffer");

    T value = {}; // assume value start at zero
    for(size_t k=0; k<N; ++k)
        value += a[k];
    value /= float(N);

    return value;
}


template <typename T> T max(buffer<T> const& v)
{
    size_t const N = v.size();
    assert_vcl(N>0, "Cannot get max on empty buffer");

    T const& current_max = v[0];
    for (size_t k = 1; k < N; ++k) {
        T const& element = v[k];
        if(element>current_max) 
            current_max = element;
    }
        
    return current_max;
}
template <typename T> T min(buffer<T> const& v)
{
    size_t const N = v.size();
    assert_vcl(N>0, "Cannot get max on empty buffer");

    T const& current_min = v[0];
    for (size_t k = 1; k < N; ++k) {
        T const& element = v[k];
        if(element>current_min) 
            current_min = element;
    }
        
    return current_min;
}


template <typename T>
buffer<T>& operator+=(buffer<T>& a, buffer<T> const& b)
{
    assert_vcl(a.size()>0 && b.size()>0, "Size must be >0");
    assert_vcl(a.size()==b.size(), "Size do not agree");

    const size_t N = a.size();
    for(size_t k=0; k<N; ++k)
        a[k] += b[k];
    return a;
}

template <typename T>
buffer<T>& operator+=(buffer<T>& a, T const& b)
{
    assert_vcl(a.size()>0, "Size must be >0");
    const size_t N = a.size();
    for(size_t k=0; k<N; ++k)
        a[k] += b;
    return a;
}

template <typename T>
buffer<T>  operator+(buffer<T> const& a, buffer<T> const& b)
{
    buffer<T> res = a;
    res += b;
    return res;
}

template <typename T>
buffer<T>  operator+(buffer<T> const& a, T const& b)
{
    buffer<T> res = a;
    res += b;
    return res;
}

template <typename T>
buffer<T>  operator+(T const& a, buffer<T> const& b)
{
    size_t const N = b.size();
    buffer<T> res(N);
    for(size_t k=0; k<N; ++k)
        res[k] = a+b[k];
    return res;
}

template <typename T> buffer<T>  operator-(buffer<T> const& a)
{
    size_t const N = a.size();
    buffer<T> b(N);
    for(size_t k=0; k<N; ++k)
        b[k] = -a[k];
    return b;
}


template <typename T> buffer<T>& operator-=(buffer<T>& a, buffer<T> const& b)
{
    assert_vcl(a.size()>0 && b.size()>0, "Size must be >0");
    assert_vcl(a.size()==b.size(), "Size do not agree");

    const size_t N = a.size();
    for(size_t k=0; k<N; ++k)
        a[k] -= b[k];
    return a;
}
template <typename T> buffer<T>& operator-=(buffer<T>& a, T const& b)
{
    assert_vcl(a.size()>0, "Size must be >0");
    const size_t N = a.size();
    for(size_t k=0; k<N; ++k)
        a[k] -= b;
    return a;
}
template <typename T> buffer<T>  operator-(buffer<T> const& a, buffer<T> const& b)
{
    buffer<T> res = a;
    res -= b;
    return res;
}
template <typename T> buffer<T>  operator-(buffer<T> const& a, T const& b)
{
    buffer<T> res = a;
    res -= b;
    return res;
}
template <typename T> buffer<T>  operator-(T const& a, buffer<T> const& b)
{
    size_t const N = b.size();
    buffer<T> res(N);
    for(size_t k=0; k<N; ++k)
        res[k] = a-b[k];
    return res;
}


template <typename T> buffer<T>& operator*=(buffer<T>& a, buffer<T> const& b)
{
    assert_vcl(a.size()>0 && b.size()>0, "Size must be >0");
    assert_vcl(a.size()==b.size(), "Size do not agree");

    const size_t N = a.size();
    for(size_t k=0; k<N; ++k)
        a[k] *= b[k];
    return a;
}
template <typename T> buffer<T>  operator*(buffer<T> const& a, buffer<T> const& b)
{
    buffer<T> res = a;
    res *= b;
    return res;
}




template <typename T> buffer<T>& operator*=(buffer<T>& a, float b)
{
    size_t const N = a.size();
    for(size_t k=0; k<N; ++k)
        a[k] *= b;
    return a;
}
template <typename T> buffer<T>  operator*(buffer<T> const& a, float b)
{
    size_t const N = a.size();
    buffer<T> res(N);
    for(size_t k=0; k<N; ++k)
        res[k] = a[k]*b;
    return res;
}
template <typename T> buffer<T>  operator*(float a, buffer<T> const& b)
{
    size_t const N = b.size();
    buffer<T> res(N);
    for(size_t k=0; k<N; ++k)
        res[k] = a*b[k];
    return res;
}

template <typename T> buffer<T>& operator/=(buffer<T>& a, buffer<T> const& b)
{
    assert_vcl(a.size()>0 && b.size()>0, "Size must be >0");
    assert_vcl(a.size()==b.size(), "Size do not agree");

    const size_t N = a.size();
    for(size_t k=0; k<N; ++k)
        a[k] /= b[k];
    return a;
}
template <typename T> buffer<T>& operator/=(buffer<T>& a, float b)
{
    assert_vcl(a.size()>0, "Size must be >0");
    const size_t N = a.size();
    for(size_t k=0; k<N; ++k)
        a[k] /= b;
    return a;
}
template <typename T> buffer<T>  operator/(buffer<T> const& a, buffer<T> const& b)
{
    buffer<T> res = a;
    res /= b;
    return res;
}
template <typename T> buffer<T>  operator/(buffer<T> const& a, float b)
{
    buffer<T> res = a;
    res /= b;
    return res;
}



template <typename T1, typename T2> bool is_equal(buffer<T1> const& a, buffer<T2> const& b)
{
    size_t const N = a.size();
    if(b.size()!=N)
        return false;

    using vcl::is_equal;
    for(size_t k=0; k<N; ++k)
        if( is_equal(a[k],b[k])==false )
            return false;
    return true;
}
template <typename T> bool is_equal(buffer<T> const& a, buffer<T> const& b)
{
    return is_equal<T,T>(a,b);
}

template <typename T>
buffer<T> buffer<T>::linespace(T const& p1, T const& p2, size_t N)
{
    buffer<T> buf; 
    buf.resize(N);

    T const increment = (p2 - p1) / float(N - 1);
    T current = p1;
    for (size_t k = 0; k < N; ++k)
    {
        buf[k] = current;
        current = current + increment;
    }
    return buf;

}

template <typename T> auto const* ptr(buffer<T> const& v)
{
    using vcl::ptr;
    return ptr(v[0]);
}

}
