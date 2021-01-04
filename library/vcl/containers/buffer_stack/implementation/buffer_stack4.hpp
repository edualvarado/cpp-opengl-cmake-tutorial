#pragma once

#include "buffer_stack.hpp"

namespace vcl
{
    // Special case of a buffer_stack with dimension = 4
    //  Internal element can be accessed as x, y, z and w
    template <typename T>
    struct buffer_stack<T, 4>
    {
        buffer_stack<T, 4>();
        buffer_stack<T, 4>(T const& x, T const& y, T const& z, T const& w);
        buffer_stack<T, 4>(buffer_stack<T, 3> const& xyz, T const& w);
        buffer_stack<T, 4>(T const& x, buffer_stack<T, 3> const& yzw);

        buffer_stack<T, 4>(T const& x, T const& y, buffer_stack<T, 2> const& yz);
        buffer_stack<T, 4>(buffer_stack<T, 2> const& xy, T const& z, T const& w);
        buffer_stack<T, 4>(T const& x, buffer_stack<T, 2> const& yz, T const& w);
        buffer_stack<T, 4>(buffer_stack<T, 2> const& xy, buffer_stack<T, 2> const& zw);


        /** Internal data */
        T x, y, z, w;

        /** Size of the buffer = 4 */
        std::size_t size() const;

        /** Fill all data with the given value */
        buffer_stack<T, 4>& fill(T const& value);

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
        buffer_stack<T, 3> xyz() const;
        buffer_stack<T, 2> xy() const;
        buffer_stack<T, 2> yz() const;
        buffer_stack<T, 2> xz() const;
        
    };
}



namespace vcl
{

    template <typename T> buffer_stack<T, 4>::buffer_stack()
        :x(T()), y(T()), z(T()), w(T())
    {}
    template <typename T> buffer_stack<T, 4>::buffer_stack(T const& x_arg, T const& y_arg, T const& z_arg, T const& w_arg)
        : x(x_arg), y(y_arg), z(z_arg), w(w_arg)
    {}
    template <typename T> buffer_stack<T, 4>::buffer_stack(buffer_stack<T, 3> const& xyz, T const& w_arg)
        : x(get<0>(xyz)), y(get<1>(xyz)), z(get<2>(xyz)), w(w_arg)
    {}
    template <typename T> buffer_stack<T, 4>::buffer_stack(T const& x_arg, buffer_stack<T, 3> const& yzw)
        : x(x_arg), y(get<0>(yzw)), z(get<1>(yzw)), w(get<2>(yzw))
    {}

    template <typename T> buffer_stack<T, 4>::buffer_stack(T const& x_arg, T const& y_arg, buffer_stack<T, 2> const& yz)
        : x(x_arg), y(y_arg), z(get<0>(yz)), w(get<1>(yz))
    {}
    template <typename T> buffer_stack<T, 4>::buffer_stack(buffer_stack<T, 2> const& xy, T const& z_arg, T const& w_arg)
        : x(get<0>(xy)), y(get<1>(xy)), z(z_arg), w(w_arg)
    {}
    template <typename T> buffer_stack<T, 4>::buffer_stack(T const& x_arg, buffer_stack<T, 2> const& yz, T const& w_arg)
        : x(x_arg), y(get<0>(yz)), z(get<1>(yz)), w(w_arg)
    {}
    template <typename T> buffer_stack<T, 4>::buffer_stack(buffer_stack<T, 2> const& xy, buffer_stack<T, 2> const& zw)
        : x(get<0>(xy)), y(get<1>(xy)), z(get<0>(zw)), w(get<1>(zw))
    {}


    template <typename T> std::size_t buffer_stack<T, 4>::size() const
    {
        return 4;
    }



    template <typename T>  buffer_stack<T, 4>& buffer_stack<T, 4>::fill(T const& value)
    {
        x = value;
        y = value;
        z = value;
        w = value;
        return *this;
    }

    template <typename T, size_t N, typename INDEX_TYPE>
    void check_index_bounds(INDEX_TYPE index, buffer_stack<T, 4> const& data)
    {
#ifndef VCL_NO_DEBUG
        if (index < 0 || index>3)
        {
            std::string msg = "\n";
            msg += " - Try access " + type_str(data) + "[" + str(index) + "]\n";
            msg += " - Indexing is limited to 0, 1, 2, 3";
            error_vcl(msg);
        }
#endif
    }

    template <typename T> T const& buffer_stack<T, 4>::operator[](int index) const
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }

    template <typename T> T& buffer_stack<T, 4>::operator[](int index)
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }

    template <typename T> T const& buffer_stack<T, 4>::operator()(int index) const
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }
    template <typename T> T& buffer_stack<T, 4>::operator()(int index)
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }

    template <typename T> T const& buffer_stack<T, 4>::operator[](std::size_t index) const
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }
    template <typename T> T& buffer_stack<T, 4>::operator[](std::size_t index)
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }

    template <typename T> T const& buffer_stack<T, 4>::operator()(std::size_t index) const
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }
    template <typename T> T& buffer_stack<T, 4>::operator()(std::size_t index)
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }

    template <typename T> T const& buffer_stack<T, 4>::at(std::size_t index) const
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }
    template <typename T> T& buffer_stack<T, 4>::at(std::size_t index)
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }


    template <typename T> T* buffer_stack<T, 4>::begin() { return &x; }
    template <typename T> T* buffer_stack<T, 4>::end() { return &w + 1; }
    template <typename T> T const* buffer_stack<T, 4>::begin() const { return &x; }
    template <typename T> T const* buffer_stack<T, 4>::end() const { return &w + 1; }
    template <typename T> T const* buffer_stack<T, 4>::cbegin() const { return &x; }
    template <typename T> T const* buffer_stack<T, 4>::cend() const { return &w + 1; }




    template <typename T> buffer_stack<T, 3> buffer_stack<T, 4>::xyz() const
    {
        return buffer_stack<T, 3>{x, y, z};
    }
    template <typename T> buffer_stack<T, 2> buffer_stack<T, 4>::xy() const
    {
        return buffer_stack<T, 2>{x, y};
    }
    template <typename T> buffer_stack<T, 2> buffer_stack<T, 4>::yz() const
    {
        return buffer_stack<T, 2>{y, z};
    }
    template <typename T> buffer_stack<T, 2> buffer_stack<T, 4>::xz() const
    {
        return buffer_stack<T, 2>{x, z};
    }


    template <size_t idx, typename T> T const& get(buffer_stack<T, 4> const& data)
    {
        static_assert(idx < 4, "Incorrect element indexing");
        return (&data.x)[idx];
    }
    template <size_t idx, typename T> T& get(buffer_stack<T, 4>& data)
    {
        static_assert(idx < 4, "Incorrect element indexing");
        return (&data.x)[idx];
    }

    template <typename T> std::string type_str(buffer_stack<T, 4> const&)
    {
        return "buffer_stack4<" + type_str(T()) + ">";
    }
}