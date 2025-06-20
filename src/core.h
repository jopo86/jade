#pragma once

#include "defs.h"
#include "color.h"

#include <iostream>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace jade {

    struct Config {
        int width = 800, height = 600;
        std::string title = "Jade";
        Color background = Color::black();
        int vsync = true;
        int fps = 60;
        bool resizable = false;
        bool anti_alias = true;
    };

    struct Callbacks {
        std::function<void(std::string msg)> on_err;
        std::function<void(std::string msg)> on_warn;
        std::function<void(double dt)> on_update;
        std::function<void()> on_draw;
        std::function<void(Key key, InputAction action)> on_key;
        std::function<void(char c)> on_char;
        std::function<void(MouseButton mb, InputAction action)> on_mouse_button;
        std::function<void(double x, double y)> on_mouse_moved, on_scroll;
    };

    struct Context {
        Config cfg;
        Callbacks cbs;
        GLFWwindow* window;
    };
    inline Context context;

    Result init();
    Result init(const Config& cfg);
    Result init(const Callbacks& cbs);
    Result init(const Config& cfg, const Callbacks& cbs);
    void run();
    void terminate();

    void set_callbacks(const Callbacks& cbs);
    void set_error_callback(std::function<void(std::string msg)> cb);
    void set_warn_callback(std::function<void(std::string msg)> cb);
    void set_update_callback(std::function<void(double dt)> cb);
    void set_draw_callback(std::function<void()> cb);
    void set_key_callback(std::function<void(Key key, InputAction action)> cb);
    void set_char_callback(std::function<void(char c)> cb);
    void set_mouse_button_callback(std::function<void(MouseButton mb, InputAction action)> cb);
    void set_mouse_moved_callback(std::function<void(double x, double y)> cb);
    void set_scroll_callback(std::function<void(double x, double y)> cb);


}
