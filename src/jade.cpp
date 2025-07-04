#include <iostream>

#include <jade/jade.h>
#include <jade/internal.h>

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
        context.cam.resize((float)width, (float)height);
        context.sprite_shader.use();
        context.sprite_shader.set_mat4("u_proj", context.cam.proj);
        context.shape_shader.use();
        context.shape_shader.set_mat4("u_proj", context.cam.proj);
        context.text_shader.use();
        context.text_shader.set_mat4("u_proj", context.cam.proj);

        if (context.cbs.on_resize) context.cbs.on_resize(width, height);
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
        int fb_height;
        glfwGetFramebufferSize(context.window, nullptr, &fb_height);
        if (context.cbs.on_mouse_moved) context.cbs.on_mouse_moved(x, fb_height - y);
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
        glfwWindowHint(GLFW_SAMPLES, 16);

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

        glfwMakeContextCurrent(context.window);
        glfwSwapInterval(context.cfg.vsync);
        
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

        context.cam = Camera((float)fb_width, (float)fb_height);
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

    void set_config(const Config& cfg) {
        context.cfg = cfg;
        if (context.initd) {
            glfwSetWindowSize(context.window, cfg.width, cfg.height);
            glfwSetWindowTitle(context.window, cfg.title.c_str());
            glfwSwapInterval(cfg.vsync);
            glfwSetWindowAttrib(context.window, GLFW_RESIZABLE, cfg.resizable);
            context.cfg.anti_alias ? glEnable(GL_MULTISAMPLE) : glDisable(GL_MULTISAMPLE);
        }
    }

    const Config& get_config() {
        return context.cfg;
    }

    void set_config_width(int width) {
        context.cfg.width = width;
        if (context.initd) glfwSetWindowSize(context.window, width, context.cfg.height);
    }

    void set_config_height(int height) {
        context.cfg.height = height;
        if (context.initd) glfwSetWindowSize(context.window, context.cfg.width, height);
    }

    void set_config_title(const std::string& title) {
        context.cfg.title = title;
        if (context.initd) glfwSetWindowTitle(context.window, title.c_str());
    }

    void set_config_background(const Color& background) {
        context.cfg.background = background;
    }

    void set_config_vsync(bool vsync) {
        context.cfg.vsync = vsync;
        if (context.initd) glfwSwapInterval(vsync);
    }

    void set_config_fps(int fps) {
        context.cfg.fps = fps;
    }

    void set_config_resizable(bool resizable) {
        context.cfg.resizable = resizable;
        if (context.initd) glfwSetWindowAttrib(context.window, GLFW_RESIZABLE, resizable);
    }

    void set_config_anti_alias(bool anti_alias) {
        context.cfg.anti_alias = anti_alias;
        if (context.initd) anti_alias ? glEnable(GL_MULTISAMPLE) : glDisable(GL_MULTISAMPLE);
    }

    void set_callbacks(const Callbacks& cbs) {
        context.cbs = cbs;
    }

    const Callbacks& get_callbacks() {
        return context.cbs;
    }

    void set_error_callback(std::function<void(const std::string& msg)> fn) {
        context.cbs.on_err = fn;
    }

    void set_warn_callback(std::function<void(const std::string& msg)> fn) {
        context.cbs.on_warn = fn;
    }

    void set_update_callback(std::function<void(double dt)> fn) {
        context.cbs.on_update = fn;
    }

    void set_draw_callback(std::function<void()> fn) {
        context.cbs.on_draw = fn;
    }

    void set_key_callback(std::function<void(Key key, Action action)> fn) {
        context.cbs.on_key = fn;
    }

    void set_char_callback(std::function<void(char c)> fn) {
        context.cbs.on_char = fn;
    }

    void set_mouse_button_callback(std::function<void(MouseButton btn, Action action)> fn) {
        context.cbs.on_mouse_button = fn;
    }

    void set_mouse_moved_callback(std::function<void(double x, double y)> fn) {
        context.cbs.on_mouse_moved = fn;
    }

    void set_scroll_callback(std::function<void(double x, double y)> fn) {
        context.cbs.on_scroll = fn;
    }

    void set_resize_callback(std::function<void(int width, int height)> fn) {
        context.cbs.on_resize = fn;
    }

    void center_window() {
        assert_initialized("jade::core::center_window()");
        
        struct Monitor {
            int x, y, width, height;
        } monitor;
        glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &monitor.x, &monitor.y, &monitor.width, &monitor.height);
        glfwSetWindowPos(
            context.window,
            monitor.x + monitor.width / 2 - context.cfg.width / 2,
            monitor.y + monitor.height / 2 - context.cfg.height / 2
        );
    }
    
    double get_time() {
        assert_initialized("jade::core::get_time()");
        return glfwGetTime();
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
        int fb_height;
        glfwGetCursorPos(context.window, nullptr, &y);
        glfwGetFramebufferSize(context.window, nullptr, &fb_height);
        return fb_height - y;
    }

    void set_cursor_mode(CursorMode mode) {
        glfwSetInputMode(context.window, GLFW_CURSOR, (int)mode);
    }

    CursorMode get_cursor_mode() {
        return (CursorMode)glfwGetInputMode(context.window, GLFW_CURSOR);
    }
}

namespace jade::draw {
    void set_draw_mode(DrawMode mode) {
        assert_initialized("jade::draw::set_wireframe()");
        glPolygonMode(GL_FRONT_AND_BACK, (GLenum)mode);
    }

    DrawMode get_draw_mode() {
        assert_initialized("jade::draw::set_wireframe()");
        int polygon_mode = 0;
        glGetIntegerv(GL_POLYGON_MODE, &polygon_mode);
        return (DrawMode)polygon_mode;
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
