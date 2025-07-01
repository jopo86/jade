#pragma once

#include <glm/glm.hpp>

namespace jade::draw {
    class Drawable {
    public:
        Drawable();

        virtual void draw() const = 0;

        void translate(float x_offset, float y_offset, float z_offset = 0.0f);
        void rotate(float degrees);
        void scale(float factor);
        void scale(float x_factor, float y_factor);
        void scale_x(float factor);
        void scale_y(float factor);

        void set_position(float x, float y);
        void set_position(float x, float y, float z);
        void set_x(float x);
        void set_y(float y);
        void set_z(float z);
        void set_scale(float scale);
        void set_scale_x(float scale_x);
        void set_scale_y(float scale_y);
        void set_rotation(float degrees);

        float get_x() const;
        float get_y() const;
        float get_z() const;
        float get_scale_x() const;
        float get_scale_y() const;
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
