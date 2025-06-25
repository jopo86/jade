#pragma once

#include <glm/glm.hpp>

namespace jade::draw {
    class Drawable {
    public:
        virtual void draw() = 0;

        void translate(float x_offset, float y_offset, float z_offset = 0.0f);
        void rotate(float degrees);
        void scale(float factor);
        void scale(float x_factor, float y_factor);
    
        virtual ~Drawable() = default;
    protected:
        glm::mat4 model;
    };
}
