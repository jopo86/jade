#include "drawable.h"

#include <glm/gtc/matrix_transform.hpp>

namespace jade::draw {
    
    void Drawable::translate(float x, float y, float z) {
        model = glm::translate(model, glm::vec3(x, y, z));
    }

    void Drawable::rotate(float deg) {
        model = glm::rotate(model, glm::radians(deg), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    void Drawable::scale(float xy) {
        scale(xy, xy);
    }

    void Drawable::scale(float x, float y) {
        model = glm::scale(model, glm::vec3(x, y, 0.0f));
    }
}
