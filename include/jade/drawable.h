#pragma once

#include <glm/glm.hpp>

namespace jade::draw {
    class Drawable {
    public:
        Drawable();

        /*
            @brief Renders the element to the window.
         !  This should only be called inside the `on_draw` callback.
        */
        virtual void draw() const = 0;

        // @brief Changes the position of the element by the specified offsets.
        void translate(float x_offset, float y_offset, float z_offset = 0.0f);
        // @brief Rotates the element by the specified number of degrees.
        void rotate(float degrees);
        // @brief Scales the element by the specified factor on all axes. This multiplies the scale, it does not add to it.
        void scale(float factor);
        // @brief Scales the element by the specified factor on each axis. This multiplies the scale, it does not add to it.
        void scale(float x_factor, float y_factor);
        // @brief Scales the element by the specified factor on the x-axis. This multiplies the scale, it does not add to it.
        void scale_x(float factor);
        // @brief Scales the element by the specified factor on the y-axis. This multiplies the scale, it does not add to it.
        void scale_y(float factor);

        // @brief Sets the position of the element to the specified coordinates.
        void set_position(float x, float y);
        // @brief Sets the position of the element to the specified coordinates.
        void set_position(float x, float y, float z);
        // @brief Sets the x-coordinate of the element.
        void set_x(float x);
        // @brief Sets the y-coordinate of the element.
        void set_y(float y);
        // @brief Sets the z-coordinate of the element.
        void set_z(float z);
        // @brief Sets the scale of the element to the specified value on all axes.
        void set_scale(float scale);
        // @brief Sets the scale of the element to the specified value on the x-axis.
        void set_scale_x(float scale_x);
        // @brief Sets the scale of the element to the specified value on the y-axis.
        void set_scale_y(float scale_y);
        // @brief Sets the rotation/angle of the element to the specified number of degrees.
        void set_rotation(float degrees);

        // @return The x-coordinate of the element.
        float get_x() const;
        // @return The y-coordinate of the element.
        float get_y() const;
        // @return The z-coordinate of the element.
        float get_z() const;
        // @return The scale of the element on the x-axis.
        float get_scale_x() const;
        // @return The scale of the element on the y-axis.
        float get_scale_y() const;
        // @return The rotation/angle of the element.
        float get_rotation() const;
    
        virtual ~Drawable() = default;

    protected:
        glm::mat4 model;

    private:
        float x, y, z;
        float m_scale_x, m_scale_y;
        float rotation;

        void update_model();
    };
}
