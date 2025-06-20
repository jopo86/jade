#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace jade {

    struct Config {
        int width = 800, height = 600;
        std::string title = "Jade";
        void (*err)(std::string) = nullptr;
        void (*warn)(std::string) = nullptr;
        void (*update)(float dt) = nullptr;
    };

    struct Context {
        Config cfg;
        GLFWwindow* window;
    };

    inline Context context;

    enum class Result {
        Success,
        FailedInitGLFW,
        FailedCreateWindow,
        FailedInitGlad,
    };

    Result init(const Config& cfg);
    void run();
    void terminate();

}
