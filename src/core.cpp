#include "core.h"

namespace jade {
    void err(std::string msg) {
        if (context.cfg.err) context.cfg.err(msg);
        else std::cerr << "ERR: " << msg << std::endl;
    }

    void warn(std::string msg) {
        if (context.cfg.warn) context.cfg.warn(msg);
        else std::cerr << "WARN: " << msg << std::endl;
    }
}

jade::Result jade::init(const Config& cfg) {
    context.cfg = cfg;
    
    if (!glfwInit()) {
        err("jade::init(): failed to initialize GLFW");
        return Result::FailedInitGLFW;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef APPLE
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    glfwWindowHint(GLFW_SAMPLES, 4); // MSAA 4x

    context.window = glfwCreateWindow(cfg.width, cfg.height, cfg.title.c_str(), nullptr, nullptr);
    if (!context.window) {
        err("jade::init(): failed to create window");
        return Result::FailedCreateWindow;
    }
    glfwMakeContextCurrent(context.window);
    glfwSwapInterval(1); // V-SYNC

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        err("jade::init(): failed to initialize Glad");
        return Result::FailedInitGlad;
    }

    int fb_width = 0, fb_height = 0;
    glfwGetFramebufferSize(context.window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);

    glEnable(GL_MULTISAMPLE); // MSAA
    glEnable(GL_DEPTH_TEST);

    return Result::Success;
}

void jade::run() {
    float t0 = glfwGetTime();
    while (!glfwWindowShouldClose(context.window)) {
        float t1 = glfwGetTime();
        float dt = t1 - t0;
        t0 = t1;

        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (context.cfg.update) context.cfg.update(dt);
        glfwSwapBuffers(context.window);
    }

    glfwDestroyWindow(context.window);
    glfwTerminate();
}

void jade::terminate() {
    glfwSetWindowShouldClose(context.window, true);
}
