#pragma once

#include "jade.h"

namespace jade::internal {

    struct Context {
        core::Config cfg;
        core::Callbacks cbs;
        GLFWwindow* window;
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

        void free();
    } inline allocs;
}
