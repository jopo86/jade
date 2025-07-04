#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "color.h"

namespace jade::backend {
    class Shader {
    public:
        GLuint prog;

        Shader();
        Shader(const std::string& vert_src, const std::string& frag_src);

        void use() const;

        void set_vec3(const std::string& name, const glm::vec3& val);
        void set_vec4(const std::string& name, const glm::vec4& val);
        void set_color(const std::string& name, const core::Color& val);
        void set_mat4(const std::string& name, const glm::mat4& val);

        static Shader colored();
        static Shader textured();
        static Shader text();

    };
}
