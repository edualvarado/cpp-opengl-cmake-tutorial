#include "image.hpp"

#include "vcl/base/base.hpp"
#include "vcl/files/files.hpp"
#include "third_party/src/lodepng/lodepng.h"
#include "vcl/display/opengl/opengl.hpp"

namespace vcl
{
	image_raw::image_raw()
    :width(0), height(0), color_type(image_color_type::rgb), data()
    {}
    image_raw::image_raw(unsigned int width_arg, unsigned int height_arg, image_color_type color_type_arg, buffer<unsigned char> const& data_arg)
        :width(width_arg), height(height_arg), color_type(color_type_arg), data(data_arg)
    {}


    image_raw image_load_png(const std::string& filename, image_color_type color_type)
    {
        assert_file_exist(filename);

        LodePNGColorType lodepng_color_type;
        if(color_type==image_color_type::rgb)
            lodepng_color_type = LCT_RGB;
        else if(color_type==image_color_type::rgba)
            lodepng_color_type = LCT_RGBA;
        else
        {
            std::cerr<<"Unkown color type for file"<<filename<<std::endl;
            exit(1);
        }

        image_raw im;
        im.color_type = color_type;

        unsigned error = lodepng::decode(im.data.data, im.width, im.height, filename, lodepng_color_type);
        if ( error )
        {
            std::cerr<<"Error Loading png file "<<filename<<std::endl;
            std::cerr<<"Decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
            exit(1);
        }

        return im;
    }

    void image_save_png(const std::string& filename, const image_raw& im)
    {
        LodePNGColorType lodepng_color_type;
        if(im.color_type==image_color_type::rgb)
            lodepng_color_type = LCT_RGB;
        else if(im.color_type==image_color_type::rgba)
            lodepng_color_type = LCT_RGBA;
        else
        {
            std::cerr<<"Unkown color type for file"<<filename<<std::endl;
            exit(1);
        }

        //std::vector<unsigned char> output;
        unsigned error = lodepng::encode(filename, im.data.data, im.width, im.height, lodepng_color_type);
        if ( error )
        {
            std::cerr<<"Error Loading png file "<<filename<<std::endl;
            std::cerr<<"Decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
            exit(1);
        }
    }

    void convert(image_raw const& in, grid_2D<vec3>& out)
    {
        size_t const N = size_t(in.width) * size_t(in.height);
        out.resize(in.width, in.height);
        if (in.color_type == image_color_type::rgb)
        {
            for(size_t k=0; k<N; ++k)
                out[k] = vec3(in.data[3*k+0], in.data[3*k+1], in.data[3*k+2])/255.0f;
        }
        else if (in.color_type == image_color_type::rgba)
        {
            for(size_t k=0; k<N; ++k)
                out[k] = vec3(in.data[4*k+0], in.data[4*k+1], in.data[4*k+2])/255.0f;
        }
    }





}