#pragma once

#include "defs.h"
#include "color.h"
#include "shader.h"
#include "camera.h"

#include <string>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace jade {
    namespace core {
        struct Config {
            int width = 800, height = 600;
            std::string title = "Jade";
            Color background = Color::black();
            bool vsync = true;
            int fps = 60;
            bool resizable = true;
            bool anti_alias = true;
        };

        struct Callbacks {
            std::function<void(const std::string& msg)> on_err;
            std::function<void(const std::string& msg)> on_warn;
            std::function<void(double dt)> on_update;
            std::function<void()> on_draw;
            std::function<void(input::Key key, input::Action action)> on_key;
            std::function<void(char c)> on_char;
            std::function<void(input::MouseButton mb, input::Action action)> on_mouse_button;
            std::function<void(double x, double y)> on_mouse_moved, on_scroll;
        };

        void init();
        void init(const Config& cfg);
        void init(const Callbacks& cbs);
        void init(const Config& cfg, const Callbacks& cbs);
        void run();
        void terminate();

        void set_callbacks(const Callbacks& cbs);
        void set_error_callback(std::function<void(const std::string& msg)> cb);
        void set_warn_callback(std::function<void(const std::string& msg)> cb);
        void set_update_callback(std::function<void(double dt)> cb);
        void set_draw_callback(std::function<void()> cb);
        void set_key_callback(std::function<void(input::Key key, input::Action action)> cb);
        void set_char_callback(std::function<void(char c)> cb);
        void set_mouse_button_callback(std::function<void(input::MouseButton mb, input::Action action)> cb);
        void set_mouse_moved_callback(std::function<void(double x, double y)> cb);
        void set_scroll_callback(std::function<void(double x, double y)> cb);

        double get_time();
    }

    namespace input {
        bool is_key_down(Key key);
        bool is_mouse_button_down(MouseButton mb);
        double get_mouse_x();
        double get_mouse_y();
    }

    namespace draw {
        void set_wireframe(bool wf);
    }
    
    namespace camera {
        void translate(float x, float y);
        void rotate(float deg);
    }
}
