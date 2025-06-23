#pragma once

#include <string>

#include <glad/glad.h>

namespace jade {
    class Texture {
    public:
        GLuint tex;
        GLsizei width, height;
        GLint fmt;

        Texture();
        Texture(const std::string& filepath);

        void bind();
    };
}
