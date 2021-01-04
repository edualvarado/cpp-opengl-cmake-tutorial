#include "vcl/base/base.hpp"

#include "intersection.hpp"

namespace vcl
{
	intersection_structure intersection_ray_sphere(vec3 const& p_ray, vec3 const& d_ray, vec3 const& center, float radius)
	{
		intersection_structure inter;

        vec3 const d = p_ray-center;
        float const b = dot(d_ray,d);
        float const c = dot(d,d)-radius*radius;

        float const delta = b*b-c;
        if(delta >= 0)
        {
            float const t0 = -b - std::sqrt(delta);
            float const t1 = -b + std::sqrt(delta);

            float const t = t0>0? t0 : t1;

            if(t>0){
                inter.valid = true;
                inter.position = p_ray + t*d_ray;
                inter.normal = normalize(inter.position - center);
            }
        }

        return inter;
	}

    intersection_structure intersection_ray_spheres_closest(vec3 const& p_ray, vec3 const& d_ray, buffer<vec3> const& centers, float radius, int* shape_index)
    {
        size_t const N = centers.size();
        
        float t_closest = 0.0f;
        int index_closest = 0;
        intersection_structure intersection_closest;
        bool first = true;
        for (size_t k = 0; k < N; ++k)
        {
            vec3 const& c = centers[k];
            intersection_structure const inter = intersection_ray_sphere(p_ray, d_ray, c, radius);
            if (inter.valid)
            {
                float const t = norm(inter.position - p_ray);
                if (first || t_closest > t)
                {
                    first=false;
                    intersection_closest = inter;
                    index_closest = int(k);
                    t_closest = t;
                }
            }
        }

        if(shape_index!=nullptr) 
            *shape_index = index_closest;
        return intersection_closest;
        
    }
}