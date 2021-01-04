
#include "vcl/base/base.hpp"
#include "special_types.hpp"




namespace vcl
{
    std::string type_str(int2 const&) { return "int2"; }
    std::string type_str(int3 const&) { return "int3"; }
    std::string type_str(int4 const&) { return "int4"; }
    std::string type_str(size_t2 const&) { return "size_t2"; }
    std::string type_str(size_t3 const&) { return "size_t3"; }
    std::string type_str(size_t4 const&) { return "size_t4"; }
    std::string type_str(uint2 const&) { return "uint2"; }
    std::string type_str(uint3 const&) { return "uint3"; }
    std::string type_str(uint4 const&) { return "uint4"; }

    std::string type_str(vec2 const&) { return "vec2"; }
    std::string type_str(vec3 const&) { return "vec3"; }
    std::string type_str(vec4 const&) { return "vec4"; }
}