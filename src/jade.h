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
            std::function<void(int width, int height)> on_resize;
        };

        void init();
        void init(const Config& cfg);
        void init(const Callbacks& cbs);
        void init(const Config& cfg, const Callbacks& cbs);
        void run();
        void terminate();

        void set_config(const Config& cfg);
        const Config& get_config();
        void set_config_width(int width);
        void set_config_height(int height);
        void set_config_title(const std::string& title);
        void set_config_background(const Color& background);
        void set_config_vsync(bool vsync);
        void set_config_fps(int fps);
        void set_config_resizable(bool resizable);
        void set_config_anti_alias(bool anti_alias);

        void set_callbacks(const Callbacks& cbs);
        const Callbacks& get_callbacks();
        void set_error_callback(std::function<void(const std::string& msg)> fn);
        void set_warn_callback(std::function<void(const std::string& msg)> fn);
        void set_update_callback(std::function<void(double dt)> fn);
        void set_draw_callback(std::function<void()> fn);
        void set_key_callback(std::function<void(input::Key key, input::Action action)> fn);
        void set_char_callback(std::function<void(char c)> fn);
        void set_mouse_button_callback(std::function<void(input::MouseButton mb, input::Action action)> fn);
        void set_mouse_moved_callback(std::function<void(double x, double y)> fn);
        void set_scroll_callback(std::function<void(double x, double y)> fn);
        void set_resize_callback(std::function<void(int width, int height)> fn);

        void center_window();
        double get_time();
    }

    namespace input {
        bool is_key_down(Key key);
        bool is_mouse_button_down(MouseButton mb);
        double get_mouse_x();
        double get_mouse_y();
        void set_cursor_mode(CursorMode mode);
        CursorMode get_cursor_mode();
    }

    namespace draw {
        void set_draw_mode(DrawMode mode);
        DrawMode get_draw_mode();
    }
    
    namespace camera {
        void translate(float x, float y);
        void rotate(float deg);
    }
}
