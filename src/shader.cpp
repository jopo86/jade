#include "shader.h"
#include "internal.h"

#include <glm/gtc/type_ptr.hpp>

using jade::internal::allocs;

namespace jade::hidden {
    void err(const std::string&);
    void assert_initialized(const std::string&);
} using jade::hidden::err, jade::hidden::assert_initialized;

namespace jade::backend {

    Shader::Shader() : prog(0) {}

    Shader::Shader(const std::string& vert_src, const std::string& frag_src) {
        assert_initialized("jade::backend::Shader::Shader()");
        
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
            err("Shader::Shader(): Failed to compile a vertex shader, shader has been disposed. OpenGL output shown below: \n" + std::string(buf) + "\n");
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
            err("Shader::Shader(): Failed to compile a fragment shader, shader has been disposed. OpenGL output shown below: \n" + std::string(buf) + "\n");
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
            err("Shader::Shader(): Failed to link a shader program, shader has been disposed. OpenGL output shown below: \n" + std::string(buf) + "\n");
            if (vert) glDeleteShader(vert);
            if (frag) glDeleteShader(frag);
            glDeleteProgram(prog);
            return;
        }

        glValidateProgram(prog);
        glGetProgramiv(prog, GL_VALIDATE_STATUS, &result);
        if (!result)
        {
            char buf[256];
            glGetProgramInfoLog(prog, 256, nullptr, buf);
            err("Shader::Shader(): Failed to validate a shader program, shader has been disposed. OpenGL output shown below: \n" + std::string(buf) + "\n");
            if (vert) glDeleteShader(vert);
            if (frag) glDeleteShader(frag);
            glDeleteProgram(prog);
            return;
        }

        glDeleteShader(vert);
        glDeleteShader(frag);
        allocs.progs.push_back(prog);
    }

    void Shader::use() {
        glUseProgram(prog);
    }

    void Shader::set_vec3(const std::string& name, const glm::vec3& val) {
        glUniform3fv(glGetUniformLocation(prog, name.c_str()), 1, glm::value_ptr(val));
    }

    void Shader::set_vec4(const std::string& name, const glm::vec4& val) {
        glUniform4fv(glGetUniformLocation(prog, name.c_str()), 1, glm::value_ptr(val));
    }

    void Shader::set_color(const std::string& name, const core::Color& val) {
        glUniform4f(glGetUniformLocation(prog, name.c_str()), val.r, val.g, val.b, val.a);
    }

    void Shader::set_mat4(const std::string& name, const glm::mat4& val) {
        glUniformMatrix4fv(glGetUniformLocation(prog, name.c_str()), 1, false, glm::value_ptr(val));
    }

    Shader Shader::colored() {
        return Shader(
            R"(
#version 460 core

layout (location = 0) in vec2 i_pos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

void main() {
    gl_Position = u_proj * u_view * u_model * vec4(i_pos, 0.0f, 1.0f);
}
            )",
            R"(
#version 460 core

out vec4 o_col;

uniform vec4 u_col;

void main() {
    o_col = u_col;
}
            )"
        );
    }

    Shader Shader::textured() {
        return Shader(
            R"(
#version 460 core

layout (location = 0) in vec2 i_pos;
layout (location = 1) in vec2 i_tex_coord;

out vec2 io_tex_coord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

void main() {
    gl_Position = u_proj * u_view * u_model * vec4(i_pos, 0.0f, 1.0f);
    io_tex_coord = i_tex_coord;
}
            )",
            R"(
#version 460 core

in vec2 io_tex_coord;

out vec4 o_col;

uniform sampler2D u_tex;

void main() {
    o_col = texture(u_tex, io_tex_coord);
}
            )"
        );
    }
    
    Shader Shader::text() {
        return Shader(
            R"(
#version 460 core

layout (location = 0) in vec4 i_vertex;

out vec2 io_tex_coord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

void main() {
    gl_Position = u_proj * u_view * u_model * vec4(i_vertex.xy, 0.0f, 1.0f);
    io_tex_coord = i_vertex.zw;
}
            )",
            R"(
#version 460 core

in vec2 io_tex_coord;

out vec4 o_col;

uniform sampler2D u_tex;
uniform vec4 u_col;

void main() {
    o_col = u_col * vec4(1.0, 1.0, 1.0, texture(u_tex, io_tex_coord).r);
}
            )"
        );
    }
}
