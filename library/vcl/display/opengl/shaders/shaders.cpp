#include "shaders.hpp"

#include "vcl/base/base.hpp"
#include <iostream>

namespace vcl
{
    static void check_compilation(GLuint shader,std::string const& shader_str)
    {
        GLint is_compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);

        // get info on compilation
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog( static_cast<size_t>(maxLength)+1 );
        glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

        if( maxLength >= 1 )
        {
            std::cout << "[Info from shader compilation]"<< std::endl;
            std::cout << &infoLog[0] << std::endl;
            std::cout << "For shader " << shader_str << std::endl;
        }

        if( is_compiled==GL_FALSE )
        {
            std::cout << "Compilation Failed" <<std::endl;
            glDeleteShader(shader);
            abort();
        }
    }

    static void check_link(GLuint vertex_shader, GLuint fragment_shader, GLuint program)
    {
        GLint is_linked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &is_linked);

        // Get info on Link
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog( static_cast<size_t>(maxLength)+1 );
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        if( maxLength >= 1 )
        {
            std::cout << "[Info from shader Link]"<< std::endl;
            std::cout << &infoLog[0] << std::endl;
        }
        if( is_linked==GL_FALSE ) //if failed link
        {
            // clean memory
            glDeleteProgram( program );
            glDeleteShader( vertex_shader);
            glDeleteShader( fragment_shader);

            std::cout << "Failed to link shader program" << std::endl;
            abort();
        }

    }

	static GLuint compile_shader(std::string const& shader_str, const GLenum shader_type)
    {
        const GLuint shader = glCreateShader(shader_type); 
        assert_vcl( glIsShader(shader), "Error creating shader" );

        char const* const shader_cstring = shader_str.c_str();
        glShaderSource(shader, 1, &shader_cstring, nullptr);

        // Compile shader
        glCompileShader( shader );

        check_compilation(shader, shader_str);

        return shader;
    }

	GLuint opengl_create_shader_program(std::string const& vertex_shader, std::string const& fragment_shader)
	{
		GLuint const vertex_shader_id = compile_shader(vertex_shader, GL_VERTEX_SHADER);
		GLuint const fragment_shader_id = compile_shader(fragment_shader, GL_FRAGMENT_SHADER);

        assert_vcl_no_msg( glIsShader(vertex_shader_id) );
        assert_vcl_no_msg( glIsShader(fragment_shader_id) );

        // Create Program
        GLuint const program_id = glCreateProgram();
        assert_vcl_no_msg( glIsProgram(program_id) );

        // Attach Shader to Program
        glAttachShader( program_id, vertex_shader_id );
        glAttachShader( program_id, fragment_shader_id );

        // Link Program
        glLinkProgram( program_id );

        check_link(vertex_shader_id, fragment_shader_id, program_id);

        // Shader can be detached.
        glDetachShader( program_id, vertex_shader_id);
        glDetachShader( program_id, fragment_shader_id);

        return program_id;
	}
}