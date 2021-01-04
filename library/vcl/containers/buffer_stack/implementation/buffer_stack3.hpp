#pragma once

#include "buffer_stack.hpp"



namespace vcl
{
    // Special case of a buffer_stack with dimension = 3
    //  Internal element can be accessed as x, y and z
    template <typename T>
    struct buffer_stack<T, 3>
    {
        buffer_stack<T, 3>();
        buffer_stack<T, 3>(T const& x, T const& y, T const& z);
        buffer_stack<T, 3>(buffer_stack<T, 2> const& xy, T const& z);
        buffer_stack<T, 3>(T const& x, buffer_stack<T, 2> const& yz);
        template<typename T1,typename T2, typename T3>
        buffer_stack<T,3>(T1 const& x, T2 const& y, T3 const& z);


        /** Internal data */
        T x, y, z;

        /** Size of the buffer = 3 */
        std::size_t size() const;

        /** Fill all data with the given value */
        buffer_stack<T, 3>& fill(T const& value);

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
        T* begin();
        T* end();
        T const* begin() const;
        T const* end() const;
        T const* cbegin() const;
        T const* cend() const;

        T const& at_unsafe(int index) const { return (&x)[index]; }
        T& at_unsafe(int index) { return (&x)[index]; }
        T const& at_unsafe(size_t index) const { return (&x)[index]; }
        T& at_unsafe(size_t index) { return (&x)[index]; }

        /** Sub-vector */
        buffer_stack<T,2> xy() const;
        buffer_stack<T,2> yz() const;
        buffer_stack<T,2> xz() const;
    };

    /** Cross product between two 3-component vectors */
    template <typename T> buffer_stack<T, 3> cross(buffer_stack<T, 3> const& a, buffer_stack<T, 3> const& b);
}



namespace vcl
{
    template <typename T> buffer_stack<T, 3> cross(buffer_stack<T, 3> const& a, buffer_stack<T, 3> const& b)
    {
        return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
    }

    template <typename T> buffer_stack<T, 3>::buffer_stack()
        :x(T()),y(T()),z(T())
    {}
    template <typename T> buffer_stack<T, 3>::buffer_stack(T const& x_arg, T const& y_arg, T const& z_arg)
        : x(x_arg), y(y_arg), z(z_arg)
    {}
    template <typename T> buffer_stack<T, 3>::buffer_stack(buffer_stack<T, 2> const& xy, T const& z_arg)
        : x(get<0>(xy)), y(get<1>(xy)), z(z_arg)
    {}
    template <typename T> buffer_stack<T, 3>::buffer_stack(T const& x_arg, buffer_stack<T, 2> const& yz)
        : x(x_arg), y(get<0>(yz)), z(get<1>(yz))
    {}

    template <typename T>
    template<typename T1,typename T2, typename T3>
    buffer_stack<T, 3>::buffer_stack(T1 const& x_arg, T2 const& y_arg, T3 const& z_arg)
        :x(T(x_arg)), y(T(y_arg)), z(T(z_arg))
    {}

    template <typename T> std::size_t buffer_stack<T, 3>::size() const
    {
        return 3;
    }



    template <typename T>  buffer_stack<T, 3>& buffer_stack<T, 3>::fill(T const& value)
    {
        x = value;
        y = value;
        z = value;
        return *this;
    }

    template <typename T, size_t N, typename INDEX_TYPE>
    void check_index_bounds(INDEX_TYPE index, buffer_stack<T, 3> const& data)
    {
#ifndef VCL_NO_DEBUG
        if (index < 0 || index>2)
        {
            std::string msg = "\n";
            msg += " - Try access " + type_str(data) + "[" + str(index) + "]\n";
            msg += " - Indexing is limited to 0, 1, 2";
            error_vcl(msg);
        }
#endif
    }

    template <typename T> T const& buffer_stack<T, 3>::operator[](int index) const
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }

    template <typename T> T& buffer_stack<T, 3>::operator[](int index)
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }

    template <typename T> T const& buffer_stack<T, 3>::operator()(int index) const
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }
    template <typename T> T& buffer_stack<T, 3>::operator()(int index)
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }

    template <typename T> T const& buffer_stack<T, 3>::operator[](std::size_t index) const
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }
    template <typename T> T& buffer_stack<T, 3>::operator[](std::size_t index)
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }

    template <typename T> T const& buffer_stack<T, 3>::operator()(std::size_t index) const
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }
    template <typename T> T& buffer_stack<T, 3>::operator()(std::size_t index)
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }

    template <typename T> T const& buffer_stack<T, 3>::at(std::size_t index) const
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }
    template <typename T> T& buffer_stack<T, 3>::at(std::size_t index)
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }


    template <typename T> T* buffer_stack<T, 3>::begin() { return &x; }
    template <typename T> T* buffer_stack<T, 3>::end() { return &z+1; }
    template <typename T> T const* buffer_stack<T, 3>::begin() const { return &x; }
    template <typename T> T const* buffer_stack<T, 3>::end() const { return &z+1; }
    template <typename T> T const* buffer_stack<T, 3>::cbegin() const { return &x; }
    template <typename T> T const* buffer_stack<T, 3>::cend() const { return &z+1; }





    template <typename T> buffer_stack<T,2> buffer_stack<T, 3>::xy() const
    {
        return buffer_stack<T, 2>{x, y};
    }
    template <typename T> buffer_stack<T,2> buffer_stack<T, 3>::yz() const
    {
        return buffer_stack<T, 2>{y, z};
    }
    template <typename T> buffer_stack<T,2> buffer_stack<T, 3>::xz() const
    {
        return buffer_stack<T, 2>{x, z};
    }


    template <size_t idx, typename T> T const& get(buffer_stack<T, 3> const& data)
    {
        static_assert(idx < 3, "Incorrect element indexing");
        return (&data.x)[idx];
    }
    template <size_t idx, typename T> T& get(buffer_stack<T, 3>& data)
    {
        static_assert(idx < 3, "Incorrect element indexing");
        return (&data.x)[idx];
    }


    template <typename T> std::string type_str(buffer_stack<T, 3> const&)
    {
        return "buffer_stack3<" + type_str(T()) + ">";
    }



}