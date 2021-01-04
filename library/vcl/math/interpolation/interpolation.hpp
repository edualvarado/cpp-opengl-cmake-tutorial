#pragma once

#include "vcl/containers/containers.hpp"

namespace vcl
{
    /** Interpolate value(x,y) using bilinear interpolation
    * - value: grid_2D - coordinates assumed to be its indices
    * - (x,y): coordinates assumed to be \in [0,value.dimension.x-1] X [0,value.dimension.y]
    */
    template <typename T>
    T interpolation_bilinear(grid_2D<T> const& value, float x, float y);
}

namespace vcl
{
    template <typename T>
    T interpolation_bilinear(grid_2D<T> const& value, float x, float y)
    {
	    int const x0 = int(std::floor(x));
        int const y0 = int(std::floor(y));
        int const x1 = x0+1;
        int const y1 = y0+1;

	    assert_vcl_no_msg(x0>=0 && x0<value.dimension.x);
	    assert_vcl_no_msg(x1>=0 && x1<value.dimension.x);
	    assert_vcl_no_msg(y0>=0 && y0<value.dimension.y);
	    assert_vcl_no_msg(y1>=0 && y1<value.dimension.y);

	    float const dx = x-x0;
        float const dy = y-y0;

	    assert_vcl_no_msg(dx>=0 && dx<1);
        assert_vcl_no_msg(dy>=0 && dy<1);

        T const v =
                (1-dx)*(1-dy)*value(x0,y0) +
                (1-dx)*dy*value(x0,y1) +
                dx*(1-dy)*value(x1,y0) +
                dx*dy*value(x1,y1);

	    return v;
    }
}