
#include "uniform.hpp"

#include "vcl/base/base.hpp"
#include "vcl/display/opengl/debug/debug.hpp"

#define CHECK_OPENGL_UNIFORM_WARNING

#ifdef CHECK_OPENGL_UNIFORM_STRICT
#define CHECK_OPENGL_UNIFORM(location,name) assert_vcl(location!=-1, "Cannot locate uniform variable "+str(name)+" in shader. \n(Note: the variable may be declared but unused in the shader).");
#else
#ifdef CHECK_OPENGL_UNIFORM_WARNING
#define CHECK_OPENGL_UNIFORM(location,name) if(location==-1){std::cout<< "WARNING: Cannot locate uniform variable ["+str(name)+"] in shader. (Note: the variable may be declared but unused in the shader)."<<std::endl;}
#else
#define CHECK_OPENGL_UNIFORM(location,name)
#endif
#endif

namespace vcl
{
	static bool check_location(GLint location, std::string const& name, GLuint shader, bool expected)
	{
		if (location == -1 && expected == true)
		{
			error_vcl("Try to send uniform variable ["+name+"] to a shader that doesn't use it.\n Either change the uniform variable to expected=false, or correct the associated shader (id="+str(shader)+").");
		}
		if(location==-1 && expected==false)
			return false;
		else
			return true;

	}

	void opengl_uniform(GLuint shader, std::string const& name, int value, bool expected)
	{
		assert_vcl(shader!=0, "Try to send unifor "+name+" to unspecified shader");
		GLint const location = glGetUniformLocation(shader, name.c_str()); opengl_check;
		if(check_location(location, name, shader, expected))
			glUniform1i(location, value); opengl_check;
	}
	void opengl_uniform(GLuint shader, std::string const& name, float value, bool expected)
	{
		assert_vcl(shader!=0, "Try to send unifor "+name+" to unspecified shader");
		GLint const location = glGetUniformLocation(shader, name.c_str()); opengl_check;
		if(check_location(location, name, shader, expected))
			glUniform1f(location, value); opengl_check;
	}
	void opengl_uniform(GLuint shader, std::string const& name, vec3 const& value, bool expected)
	{
		assert_vcl(shader!=0, "Try to send unifor "+name+" to unspecified shader");
		GLint const location = glGetUniformLocation(shader, name.c_str()); opengl_check;
		if(check_location(location, name, shader, expected))
			glUniform3f(location, value.x,value.y, value.z); opengl_check;
	}
	void opengl_uniform(GLuint shader, std::string const& name, vec4 const& value, bool expected)
	{
		assert_vcl(shader!=0, "Try to send unifor "+name+" to unspecified shader");
		GLint const location = glGetUniformLocation(shader, name.c_str()); opengl_check;
		if(check_location(location, name, shader, expected))
			glUniform4f(location, value.x,value.y, value.z, value.w); opengl_check;
	}
	void opengl_uniform(GLuint shader, std::string const& name, float x, float y, float z, bool expected)
	{
		assert_vcl(shader!=0, "Try to send unifor "+name+" to unspecified shader");
		GLint const location = glGetUniformLocation(shader, name.c_str()); opengl_check;
		if(check_location(location, name, shader, expected))
			glUniform3f(location, x, y, z);  opengl_check;
	}
	void opengl_uniform(GLuint shader, std::string const& name, float x, float y, float z, float w, bool expected)
	{
		assert_vcl(shader!=0, "Try to send unifor "+name+" to unspecified shader");
		GLint const location = glGetUniformLocation(shader, name.c_str()); opengl_check;
		if(check_location(location, name, shader, expected))
			glUniform4f(location, x, y, z, w);  opengl_check;
	}
	void opengl_uniform(GLuint shader, std::string const& name, mat4 const& m, bool expected)
	{
		assert_vcl(shader!=0, "Try to send unifor "+name+" to unspecified shader");
		GLint const location = glGetUniformLocation(shader, name.c_str()); opengl_check;
		if(check_location(location, name, shader, expected))
			glUniformMatrix4fv(location, 1, GL_TRUE, ptr(m));  opengl_check;
	}
	void opengl_uniform(GLuint shader, std::string const& name, mat3 const& m, bool expected)
	{
		assert_vcl(shader!=0, "Try to send unifor "+name+" to unspecified shader");
		GLint const location = glGetUniformLocation(shader, name.c_str()); opengl_check;
		if(check_location(location, name, shader, expected))
			glUniformMatrix3fv(location, 1, GL_TRUE, ptr(m)); opengl_check;
	}

}