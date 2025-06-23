#pragma once

#include <glm/glm.hpp>

namespace jade {
    class Camera {
    public:
        glm::vec3 pos, front, up;
        float roll;
        glm::mat4 view, proj;

        Camera();
        Camera(float width, float height);

        void rotate(float deg);
        void translate(float x, float y);

        void resize(float width, float height);
    };
}
