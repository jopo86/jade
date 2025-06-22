#include "shader.h"

#include <glm/gtc/type_ptr.hpp>

namespace jade {
    void err(const std::string&);
}

jade::Shader::Shader() : prog(0) {}

jade::Shader::Shader(const std::string& vert_src, const std::string& frag_src) {
    unsigned int vert = glCreateShader(GL_VERTEX_SHADER);
	unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vert_cstr = vert_src.c_str();
    const char* frag_cstr = frag_src.c_str();

	glShaderSource(vert, 1, &vert_cstr, nullptr);
	glShaderSource(frag, 1, &frag_cstr, nullptr);

	int result;

	glCompileShader(vert);
	glGetShaderiv(vert, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		char buf[256];
		glGetShaderInfoLog(vert, 256, nullptr, buf);
		err("jade::Shader::Shader(): Failed to compile a vertex shader, shader has been disposed. OpenGL output shown below: \n" + std::string(buf) + "\n");
		if (vert) glDeleteShader(vert);
		if (frag) glDeleteShader(frag);
		return;
	}

	glCompileShader(frag);
	glGetShaderiv(frag, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		char buf[256];
		glGetShaderInfoLog(frag, 256, nullptr, buf);
		err("jade::Shader::Shader(): Failed to compile a fragment shader, shader has been disposed. OpenGL output shown below: \n" + std::string(buf) + "\n");
		if (vert) glDeleteShader(vert);
		if (frag) glDeleteShader(frag);
		return;
	}

	prog = glCreateProgram();
	glAttachShader(prog, vert);
	glAttachShader(prog, frag);

	glLinkProgram(prog);
	glGetProgramiv(prog, GL_LINK_STATUS, &result);
	if (!result)
	{
		char buf[256];
		glGetProgramInfoLog(prog, 256, nullptr, buf);
		err("jade::Shader::Shader(): Failed to link a shader program, shader has been disposed. OpenGL output shown below: \n" + std::string(buf) + "\n");
		if (vert) glDeleteShader(vert);
		if (frag) glDeleteShader(frag);
		return;
	}

	glValidateProgram(prog);
	glGetProgramiv(prog, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		char buf[256];
		glGetProgramInfoLog(prog, 256, nullptr, buf);
		err("jade::Shader::Shader(): Failed to validate a shader program, shader has been disposed. OpenGL output shown below: \n" + std::string(buf) + "\n");
		if (vert) glDeleteShader(vert);
		if (frag) glDeleteShader(frag);
		return;
	}

	glDeleteShader(vert);
	glDeleteShader(frag);
}

void jade::Shader::use() {
    glUseProgram(prog);
}

void jade::Shader::set_vec3(const std::string& name, const glm::vec3& val) {
    glUniform3fv(glGetUniformLocation(prog, name.c_str()), 1, glm::value_ptr(val));
}

void jade::Shader::set_vec4(const std::string& name, const glm::vec4& val) {
    glUniform4fv(glGetUniformLocation(prog, name.c_str()), 1, glm::value_ptr(val));
}

void jade::Shader::set_mat4(const std::string& name, const glm::mat4& val) {
    glUniformMatrix4fv(glGetUniformLocation(prog, name.c_str()), 1, false, glm::value_ptr(val));
}
