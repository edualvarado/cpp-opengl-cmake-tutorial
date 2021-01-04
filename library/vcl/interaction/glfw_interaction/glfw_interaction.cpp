#include "glfw_interaction.hpp"

#include "vcl/base/base.hpp"

namespace vcl
{
	glfw_state glfw_current_state(GLFWwindow* window)
	{
		glfw_state state;
		state.mouse_click_left  = (glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT )==GLFW_PRESS);
		state.mouse_click_right = (glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT)==GLFW_PRESS);
		state.key_ctrl          = (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL));
		state.key_shift         = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT));
		return state;
	}



	vec2 glfw_get_mouse_cursor(GLFWwindow* window, double xpos, double ypos)
	{
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		const float w = static_cast<float>(width);
		const float h = static_cast<float>(height);

		return vec2{ 
			2.0f*      float(xpos)/w -1.0f, 
			2.0f*(1.0f-float(ypos)/h)-1.0f };
	}

	vec2 glfw_get_mouse_cursor(GLFWwindow* window)
	{
		double xpos=0, ypos=0;
		glfwGetCursorPos(window, &xpos, &ypos);

		return glfw_get_mouse_cursor(window, xpos, ypos);
	}
}