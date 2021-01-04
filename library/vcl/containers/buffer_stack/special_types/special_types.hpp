#pragma once

#include "../implementation/buffer_stack.hpp"
#include "../implementation/buffer_stack2.hpp"
#include "../implementation/buffer_stack3.hpp"
#include "../implementation/buffer_stack4.hpp"



namespace vcl
{
    /* ************************************************** */
    /*        Helper type declaraction                    */
    /* ************************************************** */
    template <typename T> using  buffer_stack2 = buffer_stack<T, 2>;
    template <typename T> using  buffer_stack3 = buffer_stack<T, 3>;
    template <typename T> using  buffer_stack4 = buffer_stack<T, 4>;

    using int2 = buffer_stack2<int>;
    using int3 = buffer_stack3<int>;
    using int4 = buffer_stack4<int>;
    using size_t2 = buffer_stack2<size_t>;
    using size_t3 = buffer_stack3<size_t>;
    using size_t4 = buffer_stack4<size_t>;
    using uint2 = buffer_stack<unsigned int, 2>;
    using uint3 = buffer_stack<unsigned int, 3>;
    using uint4 = buffer_stack<unsigned int, 4>;

    using vec2 = buffer_stack<float, 2>;
    using vec3 = buffer_stack<float, 3>;
    using vec4 = buffer_stack<float, 4>;


    std::string type_str(int2 const&);
    std::string type_str(int3 const&);
    std::string type_str(int4 const&);
    std::string type_str(size_t2 const&);
    std::string type_str(size_t3 const&);
    std::string type_str(size_t4 const&);
    std::string type_str(uint2 const&);
    std::string type_str(uint3 const&);
    std::string type_str(uint4 const&);

    std::string type_str(vec2 const&);
    std::string type_str(vec3 const&);
    std::string type_str(vec4 const&);

}