#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include "jade.h"

namespace jade::internal {

    struct Context {
        core::Config cfg;
        core::Callbacks cbs;
        GLFWwindow* window;
        FT_Library ft;
        backend::Camera cam;
        backend::Shader sprite_shader, shape_shader, text_shader;
        bool initd = false;
    } inline context;

    struct Allocs {
        std::vector<void*> arrs;
        std::vector<GLuint> vaos;
        std::vector<GLuint> bufs;
        std::vector<GLuint> texs;
        std::vector<GLuint> progs;
        std::vector<FT_Face> faces;

        void free();
    } inline allocs;
}
