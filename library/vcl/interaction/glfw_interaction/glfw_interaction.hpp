#pragma once

#include "vcl/display/display.hpp"

namespace vcl
{
	struct glfw_state
	{
		bool mouse_click_left;
		bool mouse_click_right;
		bool mouse_release_left;
		bool mouse_release_right;
		bool key_ctrl;
		bool key_shift;
	};

	glfw_state glfw_current_state(GLFWwindow* window);
	vec2 glfw_get_mouse_cursor(GLFWwindow* window, double xpos, double ypos);
	vec2 glfw_get_mouse_cursor(GLFWwindow* window);
}