#pragma once

#include "buffer_stack.hpp"

namespace vcl
{
    // Special case of a buffer_stack with dimension = 2
    //  Internal element can be accessed as x and y
    template <typename T>
    struct buffer_stack<T, 2>
    {
        buffer_stack<T, 2>();
        buffer_stack<T, 2>(T const& x, T const& y);
        template<typename T1,typename T2>
        buffer_stack<T, 2>(T1 const& x, T2 const& y);


        /** Internal data */
        T x, y;
    
        /** Size of the buffer = 2 */
        std::size_t size() const;

        /** Fill all data with the given value */
        buffer_stack<T, 2>& fill(T const& value);

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

    };
}



namespace vcl
{

    template <typename T>  buffer_stack<T, 2>::buffer_stack()
        :x(T()),y(T())
    {}

    template <typename T>  buffer_stack<T, 2>::buffer_stack(T const& x_arg, T const& y_arg)
        :x(x_arg),y(y_arg)
    {}

    template <typename T>
    template <typename T1,typename T2>
    buffer_stack<T, 2>::buffer_stack(T1 const& x_arg, T2 const& y_arg)
        :x(x_arg),y(y_arg)
    {}


    
    template <typename T> std::size_t buffer_stack<T, 2>::size() const
    {
        return 2;
    }



    template <typename T>  buffer_stack<T, 2>& buffer_stack<T, 2>::fill(T const& value)
    {
        x = value;
        y = value;
        return *this;
    }

    template <typename T, size_t N, typename INDEX_TYPE>
    void check_index_bounds(INDEX_TYPE index, buffer_stack<T, 2> const& data)
    {
#ifndef VCL_NO_DEBUG
        if (index < 0 || index>1)
        {
            std::string msg = "\n";
            msg += " - Try access "+type_str(data)+"[" + str(index) + "]\n";
            msg += " - Indexing is limited to 0 or 1";
            error_vcl(msg);
        }
#endif
    }

    template <typename T> T const& buffer_stack<T, 2>::operator[](int index) const
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }

    template <typename T> T& buffer_stack<T, 2>::operator[](int index)
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }

    template <typename T> T const& buffer_stack<T, 2>::operator()(int index) const
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }
    template <typename T> T& buffer_stack<T, 2>::operator()(int index)
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }

    template <typename T> T const& buffer_stack<T, 2>::operator[](std::size_t index) const
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }
    template <typename T> T& buffer_stack<T, 2>::operator[](std::size_t index)
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }

    template <typename T> T const& buffer_stack<T, 2>::operator()(std::size_t index) const
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }
    template <typename T> T& buffer_stack<T, 2>::operator()(std::size_t index)
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }

    template <typename T> T const& buffer_stack<T, 2>::at(std::size_t index) const
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }
    template <typename T> T& buffer_stack<T, 2>::at(std::size_t index)
    {
        check_index_bounds(index, *this);
        return (&x)[index];
    }


    template <typename T> T* buffer_stack<T, 2>::begin() { return &x; }
    template <typename T> T* buffer_stack<T, 2>::end() { return &y+1; }
    template <typename T> T const* buffer_stack<T, 2>::begin() const { return &x; }
    template <typename T> T const* buffer_stack<T, 2>::end() const { return &y+1; }
    template <typename T> T const* buffer_stack<T, 2>::cbegin() const { return &x; }
    template <typename T> T const* buffer_stack<T, 2>::cend() const { return &y+1; }


    template <size_t idx, typename T> T const& get(buffer_stack<T, 2> const& data)
    {
        static_assert(idx < 2, "Incorrect element indexing");
        return (&data.x)[idx];
    }
    template <size_t idx, typename T> T& get(buffer_stack<T, 2>& data)
    {
        static_assert(idx < 2, "Incorrect element indexing");
        return (&data.x)[idx];
    }



    template <typename T> std::string type_str(buffer_stack<T, 2> const&)
    {
        return "buffer_stack2<" + type_str(T()) + ">";
    }
}