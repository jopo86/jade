#include "core.h"

namespace jade {
    void err(std::string msg) {
        if (context.cbs.on_err) context.cbs.on_err(msg);
        else std::cerr << "ERR: " << msg << std::endl;
    }

    void warn(std::string msg) {
        if (context.cbs.on_warn) context.cbs.on_warn(msg);
        else std::cerr << "WARN: " << msg << std::endl;
    }

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (context.cbs.on_key) context.cbs.on_key((Key)key, (InputAction)action);
    }

    void char_callback(GLFWwindow* window, unsigned int codepoint) {
        if (context.cbs.on_char) context.cbs.on_char((char)codepoint);
    }

    void mouse_btn_callback(GLFWwindow* window, int btn, int action, int mods) {
        if (context.cbs.on_mouse_button) context.cbs.on_mouse_button((MouseButton)btn, (InputAction)action);
    }

    void cursor_pos_callback(GLFWwindow* window, double x, double y) {
        if (context.cbs.on_mouse_moved) context.cbs.on_mouse_moved(x, y);
    }

    void scroll_callback(GLFWwindow* window, double x, double y) {
        if (context.cbs.on_scroll) context.cbs.on_scroll(x, y);
    }
}

jade::Result jade::init() {
    return init(context.cfg, context.cbs);
}

jade::Result jade::init(const Config& cfg) {
    return init(cfg, context.cbs);
}

jade::Result jade::init(const Callbacks& cbs) {
    return init(context.cfg, cbs);
}

jade::Result jade::init(const Config& cfg, const Callbacks& cbs) {
    context.cfg = cfg;
    context.cbs = cbs;
    
    if (!glfwInit()) {
        err("jade::init(): failed to initialize GLFW");
        return Result::FailedInitGLFW;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef APPLE
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_RESIZABLE, context.cfg.resizable ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    context.window = glfwCreateWindow(cfg.width, cfg.height, cfg.title.c_str(), nullptr, nullptr);
    if (!context.window) {
        err("jade::init(): failed to create window");
        return Result::FailedCreateWindow;
    }
    glfwMakeContextCurrent(context.window);

    glfwSetKeyCallback(context.window, key_callback);
    glfwSetCharCallback(context.window, char_callback);
    glfwSetMouseButtonCallback(context.window, mouse_btn_callback);
    glfwSetCursorPosCallback(context.window, cursor_pos_callback);
    glfwSetScrollCallback(context.window, scroll_callback);

    glfwSwapInterval(context.cfg.vsync);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        err("jade::init(): failed to initialize Glad");
        return Result::FailedInitGlad;
    }

    int fb_width = 0, fb_height = 0;
    glfwGetFramebufferSize(context.window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);

    context.cfg.anti_alias ? glEnable(GL_MULTISAMPLE) : glDisable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);

    return Result::Success;
}

void jade::run() {
    double t0 = glfwGetTime();
    while (!glfwWindowShouldClose(context.window)) {
        double t1 = glfwGetTime();
        double dt = t1 - t0;
        t0 = t1;

        glfwPollEvents();
        if (context.cbs.on_update) context.cbs.on_update(dt);

        glClearColor(
            context.cfg.background.r,
            context.cfg.background.g,
            context.cfg.background.b,
            context.cfg.background.a
        );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (context.cbs.on_draw) context.cbs.on_draw();
        glfwSwapBuffers(context.window);

        if (!context.cfg.vsync) {
            while (glfwGetTime() - t1 < (1.0 / context.cfg.fps)) {}
        }
    }

    glfwDestroyWindow(context.window);
    glfwTerminate();
}

void jade::terminate() {
    glfwSetWindowShouldClose(context.window, true);
}

void jade::set_callbacks(const Callbacks& cbs) {
    context.cbs = cbs;
}

void jade::set_error_callback(std::function<void(std::string msg)> cb) {
    context.cbs.on_err = cb;
}

void jade::set_warn_callback(std::function<void(std::string msg)> cb) {
    context.cbs.on_warn = cb;
}

void jade::set_update_callback(std::function<void(double dt)> cb) {
    context.cbs.on_update = cb;
}

void jade::set_draw_callback(std::function<void()> cb) {
    context.cbs.on_draw = cb;
}

void jade::set_key_callback(std::function<void(Key key, InputAction action)> cb) {
    context.cbs.on_key = cb;
}

void jade::set_char_callback(std::function<void(char c)> cb) {
    context.cbs.on_char = cb;
}

void jade::set_mouse_button_callback(std::function<void(MouseButton btn, InputAction action)> cb) {
    context.cbs.on_mouse_button = cb;
}

void jade::set_mouse_moved_callback(std::function<void(double x, double y)> cb) {
    context.cbs.on_mouse_moved = cb;
}

void jade::set_scroll_callback(std::function<void(double x, double y)> cb) {
    context.cbs.on_scroll = cb;
}
