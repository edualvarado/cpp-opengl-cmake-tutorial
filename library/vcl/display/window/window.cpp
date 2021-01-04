#include "../opengl/opengl.hpp"
#include "window.hpp"

#include "vcl/base/base.hpp"
#include <iostream>

#ifndef GLFW_TRUE
#define GLFW_TRUE 1
#define GLFW_FALSE 0
#endif

namespace vcl
{
    static std::string glfw_error_string(int error)
    {
        switch(error)
        {
        case GLFW_NOT_INITIALIZED:
            return "GLFW_NOT_INITIALIZED";
        case GLFW_INVALID_ENUM:
            return "GLFW_INVALID_ENUM";
        case GLFW_INVALID_VALUE:
            return "GLFW_INVALID_VALUE";
        case GLFW_API_UNAVAILABLE:
            return "GLFW_API_UNAVAILABLE";
        case GLFW_VERSION_UNAVAILABLE:
            return "GLFW_VERSION_UNAVAILABLE";
        case GLFW_FORMAT_UNAVAILABLE:
            return "GLFW_FORMAT_UNAVAILABLE";
        case GLFW_PLATFORM_ERROR:
            return "GLFW_PLATFORM_ERROR";
        default:
            return "UNKNOWN GLFW ERROR (Shouldn't happen)";
        }

        return "IMPOSSIBLE GLFW ERROR! (Should never happen)";
    }

    static void glfw_error_callback(int error, const char* description)
    {
        std::cerr<<"Received GLFW error"<<std::endl;
        std::cerr<<"\t Error "<<glfw_error_string(error)<<" ("<<error<<")"<<std::endl;
        std::cerr<<"\t Description - "<<description<<std::endl;
    }

	GLFWwindow* create_window(int width, int height, std::string const& window_title, int opengl_version_major, int opengl_version_minor, GLFWmonitor* monitor, GLFWwindow* share)
	{
        // Set GLFW callback to catch and display error
        glfwSetErrorCallback(glfw_error_callback);

        // Initialize GLFW
        const int glfw_init_value = glfwInit();
        if( glfw_init_value != GLFW_TRUE ) {
            std::string s = "\nError: Failed to Initialize GLFW.\n";
            s += "If you are using WSL or Linux without graphical server, you need to start a X-server\n";
            std::cout<<s<<std::endl;
            abort();
        }

        // Set GLFW parameter before creating the window
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API); // change to GLFW_OPENGL_ES_API for WebGL
        glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE); // Use only modern OpenGL
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_version_major); // Expect OpenGL 3.3 or greater
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_version_minor); 

        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // Required for MacOS
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);  // Allow possible debug
        
        glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE); // Take focuss when created
        glfwWindowHint(GLFW_SAMPLES, 8); // Multisampling
        glfwWindowHint(GLFW_FLOATING, GLFW_FALSE); // Windows is not always on top

        // Creation of the window
        GLFWwindow* window = glfwCreateWindow(width, height, window_title.c_str(), monitor, share);

        if( window==nullptr ) {
            std::cerr<<"Failed to create GLFW Window"<<std::endl;
            std::cerr<<"\t Possible error cause: Incompatible OpenGL version (requesting OpenGL "<<opengl_version_major<<"."<<opengl_version_minor<<")"<<std::endl;
            std::cerr<<"\t Check your current system OpenGL version (ex. glxinfo)"<<std::endl;
            abort();
        }

        glfwMakeContextCurrent(window);

        // Initialize GLAD to get access to OpenGL functions
        const int glad_init_value = gladLoadGL();
        if( glad_init_value == 0 ) {
            std::cout<<"Failed to Init GLAD"<<std::endl;
            abort();
        }

        // Allows RGB texture in simple format
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	    glPixelStorei(GL_PACK_ALIGNMENT, 1);


        return window;
	}


}