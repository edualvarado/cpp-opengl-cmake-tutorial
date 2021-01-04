#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace vcl
{
	/** Generate a window using GLFW.
	* Warning: This function should be called at the beginning of the program before any OpenGL calls.
	*          The function should only be called once.
	* The function initialize both GLFW and GLAD for OpenGL function access
	*/
	GLFWwindow* create_window(int width=800, int height=600, std::string const& window_title="VCL Display", int opengl_version_major = 3, int opengl_version_minor = 3, GLFWmonitor* monitor=nullptr, GLFWwindow* share=nullptr);

}