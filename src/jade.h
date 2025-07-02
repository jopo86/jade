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

        // @brief Configuration for the Jade engine.
        struct Config {
            int width = 800, height = 600;
            std::string title = "Jade";
            Color background = Color::black();
            bool vsync = true;
            int fps = 60;
            bool resizable = true;
            bool anti_alias = true;
        };

        // @brief Callback functions for the Jade engine.
        struct Callbacks {

            // @brief Called when an error occurs.
            std::function<void(const std::string& msg)> on_err;

            // @brief Called when a warning occurs.
            std::function<void(const std::string& msg)> on_warn;

            // @brief Called at the start of each frame.
            // @param dt The time in seconds since the last update. FPS = 1/dt.
            std::function<void(double dt)> on_update;

            // @brief Called each frame in between clearing the screen and swapping buffers.
            // This is the only place where `draw()` should be called.
            std::function<void()> on_draw;

            // @brief Called when a key is pressed, released, or repeated.
            // @param key The key that was pressed or released.
            // @param action The action that was performed (press, release, repeat).
            std::function<void(input::Key key, input::Action action)> on_key;

            // @brief Called when a key is pressed that is a printable character (letters, numbers, symbols).
            // @param c The character that was pressed.
            std::function<void(char c)> on_char;

            // @brief Called when a mouse button is pressed or released.
            // @param mb The mouse button that was pressed or released.
            // @param action The action that was performed (press, release).
            std::function<void(input::MouseButton mb, input::Action action)> on_mouse_button;

            // @brief Called when the mouse is moved.
            // @param x The x-coordinate of the mouse cursor (NOT the change since the last update).
            // @param y The y-coordinate of the mouse cursor (NOT the change since the last update).
            std::function<void(double x, double y)> on_mouse_moved;

            // @brief Called when the mouse wheel is scrolled.
            // @param x The amount of horizontal scroll (only nonzero on trackpads).
            // @param y The amount of vertical scroll.
            std::function<void(double x, double y)> on_scroll;

            // @brief Called when the window is resized.
            // @param width The new width of the drawable area of the window in pixels.
            // @param height The new height of the drawable area of the window in pixels.
            std::function<void(int width, int height)> on_resize;

        };

        // @brief Initializes the Jade engine with default configuration and callbacks.
        void init();

        // @brief Initializes the Jade engine with the specified configuration and default callbacks.
        void init(const Config& cfg);

        // @brief Initializes the Jade engine with the default configuration and specified callbacks.
        void init(const Callbacks& cbs);

        // @brief Initializes the Jade engine with the specified configuration and callbacks.
        void init(const Config& cfg, const Callbacks& cbs);

        // @brief Runs the Jade engine.
        // This means opening a window, starting the mainloop, and handling events.
        // The mainloop will run until the window is closed or `terminate()` is called.
        void run();

        // @brief Simply closes the window. 
        // Resources are freed automatically when the program exits.
        // It is not necessary to use this function if the user closes the window manually.
        void terminate();


        // @brief Updates the entire configuration for the Jade engine in real-time.
        void set_config(const Config& cfg);

        // @return The current configuration of the Jade engine.
        const Config& get_config();

        // @brief Updates the width of the window in pixels.
        void set_config_width(int width);

        // @brief Updates the height of the window in pixels.
        void set_config_height(int height);

        // @brief Updates the title of the window.
        void set_config_title(const std::string& title);

        // @brief Updates the background color of the window.
        void set_config_background(const Color& background);

        // @brief Updates whether V-SYNC is enabled.
        void set_config_vsync(bool vsync);

        // @brief Updates the target frames per second.
        void set_config_fps(int fps);

        // @brief Updates whether the window is resizable.
        void set_config_resizable(bool resizable);

        // @brief Updates whether anti-aliasing is enabled.
        void set_config_anti_alias(bool anti_alias);


        // @brief Sets the callback functions for the Jade engine.
        void set_callbacks(const Callbacks& cbs);

        // @return The current callback functions for the Jade engine.
        const Callbacks& get_callbacks();

        // @brief Sets the callback function for error messages.
        // See `Callbacks::on_err`.
        void set_error_callback(std::function<void(const std::string& msg)> fn);

        // @brief Sets the callback function for warning messages.
        // See `Callbacks::on_warn`.
        void set_warn_callback(std::function<void(const std::string& msg)> fn);

        // @brief Sets the callback function for update events.
        // See `Callbacks::on_update`.
        void set_update_callback(std::function<void(double dt)> fn);

        // @brief Sets the callback function for draw events.
        // See `Callbacks::on_draw`.
        void set_draw_callback(std::function<void()> fn);

        // @brief Sets the callback function for key events.
        // See `Callbacks::on_key`.
        void set_key_callback(std::function<void(input::Key key, input::Action action)> fn);

        // @brief Sets the callback function for character input events.
        // See `Callbacks::on_char`.
        void set_char_callback(std::function<void(char c)> fn);

        // @brief Sets the callback function for mouse button events.
        // See `Callbacks::on_mouse_button`.
        void set_mouse_button_callback(std::function<void(input::MouseButton mb, input::Action action)> fn);

        // @brief Sets the callback function for mouse movement events.
        // See `Callbacks::on_mouse_moved`.
        void set_mouse_moved_callback(std::function<void(double x, double y)> fn);

        // @brief Sets the callback function for scroll events.
        // See `Callbacks::on_scroll`.
        void set_scroll_callback(std::function<void(double x, double y)> fn);

        // @brief Sets the callback function for window resize events.
        // See `Callbacks::on_resize`.
        void set_resize_callback(std::function<void(int width, int height)> fn);


        // @brief Centers the window on the primary monitor.
        void center_window();
        // @return The time in seconds since Jade was initialized.
        double get_time();
    }

    namespace input {
        // @return Whether the specified key is currently pressed down.
        bool is_key_down(Key key);

        // @return Whether the specified mouse button is currently pressed down.
        bool is_mouse_button_down(MouseButton mb);

        // @return The current mouse cursor's X position in pixels in window coordinates (where (0, 0) is the bottom-left).
        double get_mouse_x();

        // @return The current mouse cursor's Y position in pixels in window coordinates (where (0, 0) is the bottom-left).
        double get_mouse_y();

        // @brief Sets the mouse cursor mode (visibility and behavior).
        void set_cursor_mode(CursorMode mode);

        // @return The current mouse cursor mode.
        CursorMode get_cursor_mode();
    }

    namespace draw {
        // @brief Sets the draw mode.
        // This changes how elements are rendered (e.g., filled, wireframe, points).
        void set_draw_mode(DrawMode mode);

        // @return The current draw mode.
        DrawMode get_draw_mode();
    }
    
    namespace camera {
        // @brief Changes the camera's position by the specified offsets.
        void translate(float x_offset, float y_offset);

        // @brief Rotates the camera (barrel-roll style) by the specified angle.
        void rotate(float deg);
    }
}
