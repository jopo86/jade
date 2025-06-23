#include "drawable.h"

#include <glm/gtc/matrix_transform.hpp>

void jade::Drawable::translate(float x, float y, float z) {
    model = glm::translate(model, glm::vec3(x, y, z));
}

void jade::Drawable::rotate(float deg) {
    model = glm::rotate(model, glm::radians(deg), glm::vec3(0.0f, 0.0f, 1.0f));
}

void jade::Drawable::scale(float xy) {
    scale(xy, xy);
}

void jade::Drawable::scale(float x, float y) {
    model = glm::scale(model, glm::vec3(x, y, 0.0f));
}
