#pragma once

#include "vcl/base/base.hpp"
#include <array>
#include <cmath>



namespace vcl
{

    // Implementation of generic size buffer_stack
    //   buffer_stack is a constant size structure (size known at compile time).
    //   Internal data is stored as std::array, and buffer_stack is compatible with std::array syntax.
    template <typename T, size_t N>
    struct buffer_stack
    {
        /** Internal data is a std::array of values */
        std::array<T, N> data;

        //buffer_stack();
        //buffer_stack(buffer_stack<T,N> const& arg);
        //buffer_stack(std::initializer_list<T> const& arg);

        /** Size of the buffer (N - known at compile time) */
        std::size_t size() const;

        /** Fill all data with the given value */
        buffer_stack<T,N>& fill(T const& value);

        /** Element access
         * Allows buffer[i], buffer(i), and buffer.at(i)
         * Bound checking is performed unless VCL_NO_DEBUG is defined. */
        T const& operator[](int index) const;
        T& operator[](int index);

        T const& operator()(int index) const;
        T& operator()(int index);

        T const& operator[](std::size_t index) const;
        T& operator[](std::size_t index);

        T const& operator()(std::size_t index) const;
        T& operator()(std::size_t index);

        T const& at(std::size_t index) const;
        T& at(std::size_t index);


        /** Iterators
         *  Iterators compatible with STL syntax and std::array */
        typename std::array<T, N>::iterator begin();
        typename std::array<T, N>::iterator end();
        typename std::array<T, N>::const_iterator begin() const;
        typename std::array<T, N>::const_iterator end() const;
        typename std::array<T, N>::const_iterator cbegin() const;
        typename std::array<T, N>::const_iterator cend() const;

        T const& at_unsafe(int index) const    { return data[index]; }
        T & at_unsafe(int index)               { return data[index]; }
        T const& at_unsafe(size_t index) const { return data[index]; }
        T& at_unsafe(size_t index)             { return data[index]; }
    };



    /** Display all elements of the buffer. */
    template <typename T, size_t N> std::ostream& operator<<(std::ostream& s, buffer_stack<T, N> const& v);

    /** Direct compiled-checked access to data */
    template <size_t idx, typename T, size_t N> T const& get(buffer_stack<T,N> const& data);
    template <size_t idx, typename T, size_t N> T& get(buffer_stack<T, N>& data);


    /** Convert all elements of the buffer to a string.
     * \param buffer: the input buffer
     * \param separator: the separator between each element */
    template <typename T, size_t N> std::string str(buffer_stack<T, N> const& v, std::string const& separator = " ", std::string const& begin = "", std::string const& end = "");
    template <typename T, size_t N> std::string type_str(buffer_stack<T, N> const&);
    template <typename T, size_t N> size_t size_in_memory(buffer_stack<T, N> const& v);
    template <typename T, size_t N> auto const* ptr(buffer_stack<T,N> const& v);

    /** Equality check
     * Check equality (element by element) between two buffers.
     * Buffers with different size are always considered as not equal.
     * Only approximated equality is performed for comprison with float (absolute value between floats) */
    template <typename T1, typename T2, size_t N1, size_t N2> bool is_equal(buffer_stack<T1, N1> const& a, buffer_stack<T2, N2> const& b);
    template <typename T, size_t N> bool is_equal(buffer_stack<T, N> const& a, buffer_stack<T, N> const& b);

    /** Compute average value of all elements of the buffer. \relates buffer_stack \ingroup container */
    template <typename T, size_t N> T average(buffer_stack<T, N> const& a);

    /** Math operators
     * Common mathematical operations between buffers, and scalar or element values. */
    template <typename T, size_t N> buffer_stack<T, N>  operator-(buffer_stack<T, N> const& a);

    template <typename T, size_t N> buffer_stack<T, N>& operator+=(buffer_stack<T, N>& a, buffer_stack<T, N> const& b);
    template <typename T, size_t N> buffer_stack<T, N>& operator+=(buffer_stack<T, N>& a, T const& b);
    template <typename T, size_t N> buffer_stack<T, N>  operator+(buffer_stack<T, N> const& a, buffer_stack<T, N> const& b);
    template <typename T, size_t N> buffer_stack<T, N>  operator+(buffer_stack<T, N> const& a, T const& b);
    template <typename T, size_t N> buffer_stack<T, N>  operator+(T const& a, buffer_stack<T, N> const& b);

    template <typename T, size_t N> buffer_stack<T, N>& operator-=(buffer_stack<T, N>& a, buffer_stack<T, N> const& b);
    template <typename T, size_t N> buffer_stack<T, N>& operator-=(buffer_stack<T, N>& a, T const& b);
    template <typename T, size_t N> buffer_stack<T, N>  operator-(buffer_stack<T, N> const& a, buffer_stack<T, N> const& b);
    template <typename T, size_t N> buffer_stack<T, N>  operator-(buffer_stack<T, N> const& a, T const& b);
    template <typename T, size_t N> buffer_stack<T, N>  operator-(T const& a, buffer_stack<T, N> const& b);

    template <typename T, size_t N> buffer_stack<T, N>& operator*=(buffer_stack<T, N>& a, buffer_stack<T, N> const& b);
    template <typename T, size_t N> buffer_stack<T, N>& operator*=(buffer_stack<T, N>& a, float b);
    template <typename T, size_t N> buffer_stack<T, N>  operator*(buffer_stack<T, N> const& a, buffer_stack<T, N> const& b);
    template <typename T, size_t N> buffer_stack<T, N>  operator*(buffer_stack<T, N> const& a, float b);
    template <typename T, size_t N> buffer_stack<T, N>  operator*(float a, buffer_stack<T, N> const& b);

    template <typename T, size_t N> buffer_stack<T, N>& operator/=(buffer_stack<T, N>& a, buffer_stack<T, N> const& b);
    template <typename T, size_t N> buffer_stack<T, N>& operator/=(buffer_stack<T, N>& a, float b);
    template <typename T, size_t N> buffer_stack<T, N>  operator/(buffer_stack<T, N> const& a, buffer_stack<T, N> const& b);
    template <typename T, size_t N> buffer_stack<T, N>  operator/(buffer_stack<T, N> const& a, float b);
    template <typename T, size_t N> buffer_stack<T, N>  operator/(float a, buffer_stack<T, N> const& b);


    // Return the unit vector.
    //  Condition: ||v||>0
    template <typename T, size_t N> buffer_stack<T, N> normalize(buffer_stack<T, N> const& v);




}


/***********************************************/
/*           Template implementation           */
/***********************************************/

namespace vcl
{
    //template <typename T, size_t N>
    //buffer_stack<T, N>::buffer_stack()
    //    :data()
    //{}
    //template <typename T, size_t N>
    //buffer_stack<T, N>::buffer_stack(buffer_stack<T, N> const& arg)
    //    : data(arg)
    //{}

    //template <typename T, size_t N>
    //buffer_stack<T, N>::buffer_stack(std::initializer_list<T> const& arg)
    //    :data()
    //{
    //    assert_vcl(arg.size() >= N, "Insufficient initializer_list for buffer_stack");
    //    auto it = arg.begin();
    //    for (size_t k = 0; k < N; ++k)
    //        data[k] = *it;
    //}


    template <typename T, size_t N> std::size_t buffer_stack<T, N>::size() const
    {
        return N;
    }

    template <typename T, size_t N> buffer_stack<T, N>& buffer_stack<T, N>::fill(T const& value)
    {
        for (size_t k = 0; k < N; ++k)
            data[k] = value;
        return *this;
    }


    template <typename T, size_t N, typename INDEX_TYPE>
    void check_index_bounds(INDEX_TYPE index, buffer_stack<T, N> const& data)
    {
#ifndef VCL_NO_DEBUG

        if (index < 0 || index >= INDEX_TYPE(N))
        {
            std::string msg = "\n";
            msg += " - Try access buffer_stack["+str(index)+"]\n";
            msg += " - With container size ="+str(N)+"\n";
            msg += " - Buffer type: " + type_str(data) + "\n";

            if (index < 0)
            {
                msg += "\t> Buffer cannot be access with negative index.\n";
                msg += "\t  Help: \n";
                msg += "\t     Contrary to Python, negative indexing doesn't target the end of the buffer in C++. \n";
            }
            else if (N == 0)
            {
                msg += "\t> The container is empty: Its elements cannot be accessed.\n";
            }
            else if (index == INDEX_TYPE(N))
            {
                msg += "\t> Index reached the maximal size of the buffer \n";
                msg += "\t> The maximal possible index should be " + str(N - 1) + " \n";
                msg += "\t  Help: \n";
                msg += "\t     C++ has index starting at 0. \n";
                msg += "\t     Typical loops should go from index=0 to index<buffer.size(). \n";
            }
            else if (index >= INDEX_TYPE(N))
            {
                msg += "\t> Your index exceeded the size of the container\n";
            }


            msg += "\t  The function and variable that generated this error can be found in analysis the Call Stack.\n\n";

            error_vcl(msg);
        }
#endif
    }

    template <typename T, size_t N> T const& buffer_stack<T, N>::operator[](int index) const
    {
        check_index_bounds(index, *this);
        return data[index];
    }
    template <typename T, size_t N> T& buffer_stack<T, N>::operator[](int index)
    {
        check_index_bounds(index, *this);
        return data[index];
    }

    template <typename T, size_t N> T const& buffer_stack<T, N>::operator()(int index) const
    {
        check_index_bounds(index, *this);
        return data[index];
    }

    template <typename T, size_t N> T& buffer_stack<T, N>::operator()(int index)
    {
        check_index_bounds(index, *this);
        return data[index];
    }

    template <typename T, size_t N> T const& buffer_stack<T, N>::operator[](std::size_t const index) const
    {
        check_index_bounds(index, *this);
        return data[index];
    }
    template <typename T, size_t N> T& buffer_stack<T, N>::operator[](std::size_t const index)
    {
        check_index_bounds(index, *this);
        return data[index];
    }
    template <typename T, size_t N> T const& buffer_stack<T, N>::operator()(std::size_t index) const
    {
        check_index_bounds(index, *this);
        return data[index];
    }

    template <typename T, size_t N> T& buffer_stack<T, N>::operator()(std::size_t index)
    {
        check_index_bounds(index, *this);
        return data[index];
    }


    template <typename T, size_t N> T const& buffer_stack<T, N>::at(std::size_t index) const
    {
        return data.at(index);
    }

    template <typename T, size_t N> T& buffer_stack<T, N>::at(std::size_t index)
    {
        return data.at(index);
    }

    template <typename T, size_t N> typename std::array<T, N>::iterator buffer_stack<T, N>::begin()
    {
        return data.begin();
    }
    template <typename T, size_t N> typename std::array<T, N>::iterator buffer_stack<T, N>::end()
    {
        return data.end();
    }
    template <typename T, size_t N> typename std::array<T, N>::const_iterator buffer_stack<T, N>::begin() const
    {
        return data.begin();
    }
    template <typename T, size_t N> typename std::array<T, N>::const_iterator buffer_stack<T, N>::end() const
    {
        return data.end();
    }
    template <typename T, size_t N> typename std::array<T, N>::const_iterator buffer_stack<T, N>::cbegin() const
    {
        return data.cbegin();
    }
    template <typename T, size_t N> typename std::array<T, N>::const_iterator buffer_stack<T, N>::cend() const
    {
        return data.cend();
    }


    template <size_t idx, typename T, size_t N> T const& get(buffer_stack<T, N> const& data)
    {
        static_assert(idx < N, "Incorrect element indexing");
        return data.data[idx];
    }
    template <size_t idx, typename T, size_t N> T& get(buffer_stack<T, N>& data)
    {
        static_assert(idx < N, "Incorrect element indexing");
        return data.data[idx];
    }






    template <typename T, size_t N> std::string type_str(buffer_stack<T, N> const& )
    {
        return "buffer_stack<" + type_str(T()) + "," + str(N) + ">";
    }


    template <typename T, size_t N> std::ostream& operator<<(std::ostream& s, buffer_stack<T, N> const& v)
    {
        std::string s_out = str(v);
        s << s_out;
        return s;
    }
    template <typename T, size_t N> std::string str(buffer_stack<T, N> const& v, std::string const& separator, std::string const& begin, std::string const& end)
    {
        return vcl::detail::str_container(v, separator, begin, end);
    }

    template <typename T, size_t N> size_t size_in_memory(buffer_stack<T, N> const& v)
    {
        size_t s = 0;
        for (size_t k = 0; k < N; ++k)
            s += vcl::size_in_memory(v[k]);
        return s;
    }

    template <typename T1, typename T2, size_t N1, size_t N2> bool is_equal(buffer_stack<T1, N1> const& a, buffer_stack<T2, N2> const& b)
    {
        if (N1 != N2)
            return false;
        for (size_t k = 0; k < N1; ++k)
            if (is_equal(a[k], b[k]) == false)
                return false;
        return true;
    }

    template <typename T, size_t N> bool is_equal(buffer_stack<T, N> const& a, buffer_stack<T, N> const& b)
    {
        return is_equal<T, T, N, N>(a, b);
    }


    template <typename T, size_t N> T average(buffer_stack<T, N> const& a)
    {
        static_assert(N > 0, "Cannot compute average of empty buffer");

        T value{}; // assume value start at zero
        for (size_t k = 0; k < N; ++k)
            value += a[k];
        value /= float(N);

        return value;
    }


    template <typename T, size_t N> buffer_stack<T, N>  operator-(buffer_stack<T, N> const& a)
    {
        buffer_stack<T, N> res;
        for (size_t k = 0; k < N; ++k)
            res[k] = -a[k];
        return res;
    }

    template <typename T, size_t N> buffer_stack<T, N>& operator+=(buffer_stack<T, N>& a, buffer_stack<T, N> const& b)
    {
        for (size_t k = 0; k < N; ++k)
            a[k] += b[k];
        return a;
    }
    template <typename T, size_t N> buffer_stack<T, N>& operator+=(buffer_stack<T, N>& a, T const& b)
    {
        for (size_t k = 0; k < N; ++k)
            a[k] += b;
        return a;
    }
    template <typename T, size_t N> buffer_stack<T, N>  operator+(buffer_stack<T, N> const& a, buffer_stack<T, N> const& b)
    {
        buffer_stack<T, N> res;
        for (size_t k = 0; k < N; ++k)
            res[k] = a[k] + b[k];
        return res;
    }
    template <typename T, size_t N> buffer_stack<T, N>  operator+(buffer_stack<T, N> const& a, T const& b)
    {
        buffer_stack<T, N> res;
        for (size_t k = 0; k < N; ++k)
            res[k] = a[k] + b;
        return res;
    }
    template <typename T, size_t N> buffer_stack<T, N>  operator+(T const& a, buffer_stack<T, N> const& b)
    {
        buffer_stack<T, N> res;
        for (size_t k = 0; k < N; ++k)
            res[k] = a + b[k];
        return res;
    }

    template <typename T, size_t N> buffer_stack<T, N>& operator-=(buffer_stack<T, N>& a, buffer_stack<T, N> const& b)
    {
        for (size_t k = 0; k < N; ++k)
            a[k] -= b[k];
        return a;
    }
    template <typename T, size_t N> buffer_stack<T, N>& operator-=(buffer_stack<T, N>& a, T const& b)
    {
        for (size_t k = 0; k < N; ++k)
            a[k] -= b;
        return a;
    }
    template <typename T, size_t N> buffer_stack<T, N>  operator-(buffer_stack<T, N> const& a, buffer_stack<T, N> const& b)
    {
        buffer_stack<T, N> res;
        for (size_t k = 0; k < N; ++k)
            res[k] = a[k] - b[k];
        return res;
    }
    template <typename T, size_t N> buffer_stack<T, N>  operator-(buffer_stack<T, N> const& a, T const& b)
    {
        buffer_stack<T, N> res;
        for (size_t k = 0; k < N; ++k)
            res[k] = a[k] - b;
        return res;
    }
    template <typename T, size_t N> buffer_stack<T, N>  operator-(T const& a, buffer_stack<T, N> const& b)
    {
        buffer_stack<T, N> res;
        for (size_t k = 0; k < N; ++k)
            res[k] = a - b[k];
        return res;
    }

    template <typename T, size_t N> buffer_stack<T, N>& operator*=(buffer_stack<T, N>& a, buffer_stack<T, N> const& b)
    {
        for (size_t k = 0; k < N; ++k)
            a[k] *= b[k];
        return a;
    }
    template <typename T, size_t N> buffer_stack<T, N>& operator*=(buffer_stack<T, N>& a, float b)
    {
        for (size_t k = 0; k < N; ++k)
            a[k] *= b;
        return a;
    }
    template <typename T, size_t N> buffer_stack<T, N>  operator*(buffer_stack<T, N> const& a, buffer_stack<T, N> const& b)
    {
        buffer_stack<T, N> res;
        for (size_t k = 0; k < N; ++k)
            res[k] = a[k] * b[k];
        return res;
    }
    template <typename T, size_t N> buffer_stack<T, N>  operator*(buffer_stack<T, N> const& a, float b)
    {
        buffer_stack<T, N> res;
        for (size_t k = 0; k < N; ++k)
            res[k] = a[k] * b;
        return res;
    }
    template <typename T, size_t N> buffer_stack<T, N>  operator*(float a, buffer_stack<T, N> const& b)
    {
        buffer_stack<T, N> res;
        for (size_t k = 0; k < N; ++k)
            res[k] = a * b[k];
        return res;
    }

    template <typename T, size_t N> buffer_stack<T, N>& operator/=(buffer_stack<T, N>& a, buffer_stack<T, N> const& b)
    {
        buffer_stack<T, N> res;
        for (size_t k = 0; k < N; ++k)
            res[k] = a[k] / b[k];
        return res;
    }
    template <typename T, size_t N> buffer_stack<T, N>& operator/=(buffer_stack<T, N>& a, float b)
    {
        for (size_t k = 0; k < N; ++k)
            a[k] /= b;
        return a;
    }
    template <typename T, size_t N> buffer_stack<T, N>  operator/(buffer_stack<T, N> const& a, buffer_stack<T, N> const& b)
    {
        buffer_stack<T, N> res;
        for (size_t k = 0; k < N; ++k)
            res[k] = a[k] / b[k];
        return res;
    }
    template <typename T, size_t N> buffer_stack<T, N>  operator/(buffer_stack<T, N> const& a, float b)
    {
        buffer_stack<T, N> res;
        for (size_t k = 0; k < N; ++k)
            res[k] = a[k] / b;
        return res;
    }
    template <typename T, size_t N> buffer_stack<T, N>  operator/(float a, buffer_stack<T, N> const& b)
    {
        buffer_stack<T, N> res;
        for (size_t k = 0; k < N; ++k)
            res[k] = a / b[k];
        return res;
    }




    template <typename T, size_t N> T dot(buffer_stack<T, N> const& a, buffer_stack<T, N> const& b)
    {
        T s = {};
        for (size_t k = 0; k < N; ++k)
            s += a[k] * b[k];
        return s;
    }
    template <typename T, size_t N> T norm(buffer_stack<T, N> const& a)
    {
        using std::sqrt;
        return sqrt(dot(a, a));
    }

    template <typename T, size_t N> buffer_stack<T, N> normalize(buffer_stack<T, N> const& v)
    {
        float const n = norm(v);

#ifndef VCL_NO_DEBUG
        if ( norm(v)<1e-5f )
        {
            std::string const s = "Tried to normalize a vector " + type_str(v) + "[" + str(v) + "] with very small norm (" + str(norm(v)) + ")";
            error_vcl(s);
        }
#endif
        
        buffer_stack<T, N> vn = v / n;
        return vn;
    }

    template <typename T, size_t N> auto const* ptr(buffer_stack<T, N> const& v)
    {
        return ptr(v[0]);
    }
}
