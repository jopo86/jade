#include <iostream>

#include "jade.h"
#include "internal.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace jade::internal;
using jade::input::Key, jade::input::MouseButton, jade::input::Action;
using jade::backend::Shader, jade::backend::Camera;

namespace jade::hidden {
    void err(const std::string& msg) {
        if (context.cbs.on_err) context.cbs.on_err(msg);
        else std::cerr << "ERR: " << msg << std::endl;
    }

    void warn(const std::string& msg) {
        if (context.cbs.on_warn) context.cbs.on_warn(msg);
        else std::cerr << "WARN: " << msg << std::endl;
    }

    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
        context.cam.resize(width, height);
        context.sprite_shader.use();
        context.sprite_shader.set_mat4("u_proj", context.cam.proj);
        context.shape_shader.use();
        context.shape_shader.set_mat4("u_proj", context.cam.proj);
        context.text_shader.use();
        context.text_shader.set_mat4("u_proj", context.cam.proj);
    }

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (context.cbs.on_key) context.cbs.on_key((Key)key, (Action)action);
    }

    void char_callback(GLFWwindow* window, unsigned int codepoint) {
        if (context.cbs.on_char) context.cbs.on_char((char)codepoint);
    }

    void mouse_btn_callback(GLFWwindow* window, int btn, int action, int mods) {
        if (context.cbs.on_mouse_button) context.cbs.on_mouse_button((MouseButton)btn, (Action)action);
    }

    void cursor_pos_callback(GLFWwindow* window, double x, double y) {
        if (context.cbs.on_mouse_moved) context.cbs.on_mouse_moved(x, y);
    }

    void scroll_callback(GLFWwindow* window, double x, double y) {
        if (context.cbs.on_scroll) context.cbs.on_scroll(x, y);
    }

    void assert_initialized(const std::string& fn) {
        if (!context.initd) {
            err(fn + ": need to initialize first (jade::core::init())");
            exit(1);
        }
    }
} using namespace jade::hidden;

namespace jade::core {

    void init() {
        init(context.cfg, context.cbs);
    }

    void init(const Config& cfg) {
        init(cfg, context.cbs);
    }

    void init(const Callbacks& cbs) {
        init(context.cfg, cbs);
    }

    void init(const Config& cfg, const Callbacks& cbs) {
        context.cfg = cfg;
        context.cbs = cbs;
        
        if (!glfwInit()) {
            hidden::err("jade::core::init(): failed to initialize GLFW");
            return;
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
            err("jade::core::init(): failed to create window");
            return;
        }

        struct Monitor {
            int x, y, width, height;
        } monitor;
        glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &monitor.x, &monitor.y, &monitor.width, &monitor.height);
        glfwSetWindowPos(
            context.window,
            monitor.x + monitor.width / 2 - cfg.width / 2,
            monitor.y + monitor.height / 2 - cfg.height / 2
        );

        glfwSetFramebufferSizeCallback(context.window, framebuffer_size_callback);
        glfwSetKeyCallback(context.window, key_callback);
        glfwSetCharCallback(context.window, char_callback);
        glfwSetMouseButtonCallback(context.window, mouse_btn_callback);
        glfwSetCursorPosCallback(context.window, cursor_pos_callback);
        glfwSetScrollCallback(context.window, scroll_callback);

        glfwSwapInterval(context.cfg.vsync);

        glfwMakeContextCurrent(context.window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            err("jade::core::init(): failed to initialize Glad");
            return;
        }

        context.initd = true;

        int fb_width = 0, fb_height = 0;
        glfwGetFramebufferSize(context.window, &fb_width, &fb_height);
        glViewport(0, 0, fb_width, fb_height);

        context.cfg.anti_alias ? glEnable(GL_MULTISAMPLE) : glDisable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (FT_Init_FreeType(&context.ft)) {
            err("jade::core::init(): failed to initialize FreeType");
            return;
        }

        context.sprite_shader = Shader::textured();
        context.shape_shader = Shader::colored();
        context.text_shader = Shader::text();

        context.cam = Camera(fb_width, fb_height);
        context.sprite_shader.use();
        context.sprite_shader.set_mat4("u_view", context.cam.view);
        context.sprite_shader.set_mat4("u_proj", context.cam.proj);
        context.shape_shader.use();
        context.shape_shader.set_mat4("u_view", context.cam.view);
        context.shape_shader.set_mat4("u_proj", context.cam.proj);
        context.text_shader.use();
        context.text_shader.set_mat4("u_view", context.cam.view);
        context.text_shader.set_mat4("u_proj", context.cam.proj);

        struct CleanupGuard {
            ~CleanupGuard() {
                glfwDestroyWindow(context.window);
                glfwTerminate();
                allocs.free();
                FT_Done_FreeType(context.ft);
            }
        } static cleanup_guard;

        return;
    }

    void run() {
        assert_initialized("jade::core::run()");

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
    }

    void terminate() {
        assert_initialized("jade::core::terminate()");
        glfwSetWindowShouldClose(context.window, true);
    }
    double get_time() {
        assert_initialized("jade::core::get_time()");
        return glfwGetTime();
    }

    void set_callbacks(const Callbacks& cbs) {
        context.cbs = cbs;
    }

    void set_error_callback(std::function<void(const std::string& msg)> cb) {
        context.cbs.on_err = cb;
    }

    void set_warn_callback(std::function<void(const std::string& msg)> cb) {
        context.cbs.on_warn = cb;
    }

    void set_update_callback(std::function<void(double dt)> cb) {
        context.cbs.on_update = cb;
    }

    void set_draw_callback(std::function<void()> cb) {
        context.cbs.on_draw = cb;
    }

    void set_key_callback(std::function<void(Key key, Action action)> cb) {
        context.cbs.on_key = cb;
    }

    void set_char_callback(std::function<void(char c)> cb) {
        context.cbs.on_char = cb;
    }

    void set_mouse_button_callback(std::function<void(MouseButton btn, Action action)> cb) {
        context.cbs.on_mouse_button = cb;
    }

    void set_mouse_moved_callback(std::function<void(double x, double y)> cb) {
        context.cbs.on_mouse_moved = cb;
    }

    void set_scroll_callback(std::function<void(double x, double y)> cb) {
        context.cbs.on_scroll = cb;
    }
}

namespace jade::input {
    bool is_key_down(Key key) {
        assert_initialized("jade::input::is_key_down()");
        return glfwGetKey(context.window, (int)key) == GLFW_PRESS;
    }

    bool is_mouse_button_down(MouseButton mb) {
        assert_initialized("jade::input::is_mouse_button_down()");
        return glfwGetMouseButton(context.window, (int)mb) == GLFW_PRESS;
    }

    double get_mouse_x() {
        assert_initialized("jade::input::get_mouse_x()");
        double x;
        glfwGetCursorPos(context.window, &x, nullptr);
        return x;
    }

    double get_mouse_y() {
        assert_initialized("jade::input::get_mouse_y()");
        double y;
        glfwGetCursorPos(context.window, nullptr, &y);
        return y;
    }
}

namespace jade::draw {
    void set_wireframe(bool wf) {
        assert_initialized("jade::draw::set_wireframe()");
        glPolygonMode(GL_FRONT_AND_BACK, wf ? GL_LINE : GL_FILL);
    }
}

namespace jade::camera {
    void translate(float x, float y) {
        assert_initialized("jade::camera::translate()");
        context.cam.translate(x, y);
        context.sprite_shader.use();
        context.sprite_shader.set_mat4("u_view", context.cam.view);
        context.shape_shader.use();
        context.shape_shader.set_mat4("u_view", context.cam.view);
        context.text_shader.use();
        context.text_shader.set_mat4("u_view", context.cam.view);
    }

    void rotate(float deg) {
        assert_initialized("jade::camera::rotate()");
        context.cam.rotate(deg);
        context.sprite_shader.use();
        context.sprite_shader.set_mat4("u_view", context.cam.view);
        context.shape_shader.use();
        context.shape_shader.set_mat4("u_view", context.cam.view);
        context.text_shader.use();
        context.text_shader.set_mat4("u_view", context.cam.view);
    }
}
